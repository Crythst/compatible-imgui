package com.compatibleimgui.bridge;

import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.Platform;

import java.io.InputStream;
import java.util.Locale;

/**
 * Maps the platform to the directory that contains our rebuilt Dear ImGui JNI
 * libraries and serves those resources to the third-party binding loaders.
 *
 * <p>The binding classes in Axiom/Flashback normally unpack a library that is
 * bundled in their own jars. Those jars only contain desktop x86_64 binaries,
 * so Android, Linux arm64 and Windows arm64 cannot start. This class redirects
 * the classpath lookup to {@code compatibleimgui/native/<platform>/<library>} when a
 * matching build is present. If it is not present we return {@code null} and
 * the original binding loader keeps its old behaviour.</p>
 */
public final class NativeLibraries {

    private static final String ROOT = "compatibleimgui/native/";

    private static volatile String currentPlatform;

    private NativeLibraries() {
    }

    /**
     * @return platform directory key such as {@code linux-x86_64}, or
     *         {@code null} for an unsupported OS/arch.
     */
    public static String currentPlatform() {
        String value = currentPlatform;
        if (value == null) {
            value = detectPlatform();
            currentPlatform = value;
        }
        return value.isEmpty() ? null : value;
    }

    public static boolean hasCurrentPlatform() {
        String platform = currentPlatform();
        if (platform == null) {
            return false;
        }
        return resource(platform, "90") != null || resource(platform, "92") != null;
    }

    private static java.net.URL resource(String platform, String version) {
        String path = ROOT + platform + "/" + fileName(platform, version);
        ClassLoader loader = NativeLibraries.class.getClassLoader();
        return loader == null ? null : loader.getResource(path);
    }

    private static String fileName(String platform, String version) {
        String base = "imgui-moulberry" + version + "-java64";
        if (platform.startsWith("windows-")) {
            return base + ".dll";
        }
        if (platform.startsWith("macos-")) {
            return "lib" + base + ".dylib";
        }
        return "lib" + base + ".so";
    }

    /**
     * Opens the architecture specific replacement for a resource that a
     * binding class is trying to load.
     *
     * @param resourceName original classpath resource, for example
     *                     {@code io/imgui/java/native-bin/libimgui-moulberry92-java64.so}
     * @return replacement stream, or {@code null} when this is not an ImGui
     *         native library or no build exists for the current platform
     */
    public static InputStream open(String resourceName) {
        String platform = currentPlatform();
        if (platform == null || resourceName == null) {
            return null;
        }

        String file = resourceName.substring(resourceName.lastIndexOf('/') + 1);
        if (!file.contains("imgui-moulberry90-java64")
            && !file.contains("imgui-moulberry92-java64")) {
            return null;
        }

        String path = ROOT + platform + "/" + file;
        ClassLoader loader = NativeLibraries.class.getClassLoader();
        InputStream in = loader == null ? null : loader.getResourceAsStream(path);
        if (in == null) {
            in = NativeLibraries.class.getResourceAsStream("/" + path);
        }
        if (in == null) {
            CompatibleImGuiMod.LOGGER.warn("No native build for {} at {}", platform, path);
        }
        return in;
    }

    private static String detectPlatform() {
        String arch = normalizeArch(Platform.arch());
        if (arch == null) {
            return "";
        }

        if (Platform.isAndroid()) {
            return switch (arch) {
                case "aarch64" -> "android-aarch64";
                case "x86_64" -> "android-x86_64";
                case "armv7" -> "android-armv7";
                default -> "";
            };
        }

        String os = Platform.os().toLowerCase(Locale.ROOT);
        if (os.contains("win")) {
            return "windows-" + arch;
        }
        if (os.contains("mac") || os.contains("darwin")) {
            return "macos-" + arch;
        }
        if (os.contains("linux")) {
            return "linux-" + arch;
        }
        return "";
    }

    private static String normalizeArch(String value) {
        if (value == null) {
            return null;
        }
        return switch (value.toLowerCase(Locale.ROOT)) {
            case "amd64", "x86_64", "x64" -> "x86_64";
            case "aarch64", "arm64" -> "aarch64";
            case "arm", "armv7", "armv7l", "armhf" -> "armv7";
            default -> null;
        };
    }
}
