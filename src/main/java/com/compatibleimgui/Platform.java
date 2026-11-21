package com.compatibleimgui;

import java.util.Locale;

public final class Platform {

    private static final boolean ANDROID;
    private static final String OS;
    private static final String ARCH;

    static {
        String vm = System.getProperty("java.vm.name", "").toLowerCase(Locale.ROOT);
        String runtime = System.getProperty("java.runtime.name", "").toLowerCase(Locale.ROOT);
        String vendor = System.getProperty("java.vendor", "").toLowerCase(Locale.ROOT);
        String os = System.getProperty("os.name", "").toLowerCase(Locale.ROOT);

        ANDROID = vm.contains("dalvik") || runtime.contains("android")
            || vendor.contains("android") || os.contains("android")
            || System.getenv("ANDROID_ROOT") != null
            || System.getenv("ANDROID_DATA") != null
            || System.getenv("ANDROID_STORAGE") != null
            || System.getenv("POJAV_ENVIRON") != null;

        OS = System.getProperty("os.name", "unknown");
        ARCH = System.getProperty("os.arch", "unknown");
    }

    private Platform() {
    }

    public static boolean isAndroid() {
        return ANDROID;
    }

    public static String os() {
        return OS;
    }

    public static String arch() {
        return ARCH;
    }

    public static boolean isArm64() {
        String a = ARCH.toLowerCase(Locale.ROOT);
        return a.equals("aarch64") || a.equals("arm64");
    }

    public static boolean isX86_64() {
        String a = ARCH.toLowerCase(Locale.ROOT);
        return a.equals("amd64") || a.equals("x86_64");
    }

    /**
     * @return whether a rebuilt Dear ImGui native library is bundled for the
     *         current OS/architecture (see {@code native/build.sh}).
     */
    public static boolean hasImGuiNatives() {
        return com.compatibleimgui.bridge.NativeLibraries.hasCurrentPlatform();
    }

    public static boolean hasDesktopFFmpegNatives() {
        if (ANDROID) {
            return false;
        }
        String os = OS.toLowerCase(Locale.ROOT);
        return (os.contains("win") && isX86_64())
            || (os.contains("mac") && (isX86_64() || isArm64()))
            || (os.contains("linux") && isX86_64());
    }
}
