package com.compatibleimgui;

import net.fabricmc.api.ClientModInitializer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Entry point of the portability layer.
 *
 * <p>The mod has no hard dependency on Flashback or Axiom. It installs mixins only
 * when those mods are present. ImGui is served by the architecture-specific native
 * libraries built by {@code native/build.sh}. FFmpeg and zstd are still replaced
 * with portable Java code.</p>
 */
public final class CompatibleImGuiMod implements ClientModInitializer {

    public static final String MOD_ID = "compatibleimgui";
    public static final Logger LOGGER = LoggerFactory.getLogger("compatible-imgui");

    private static volatile boolean initialized;

    @Override
    public void onInitializeClient() {
        if (initialized) {
            return;
        }
        initialized = true;

        boolean hasImGuiNative = Platform.hasImGuiNatives();
        LOGGER.info("Compatible ImGui starting on {} ({}, {}), imgui={} ({}), export={}",
            System.getProperty("os.name"),
            System.getProperty("os.arch"),
            Platform.isAndroid() ? "Android" : "desktop",
            hasImGuiNative ? "native" : "missing",
            hasImGuiNative
                ? com.compatibleimgui.bridge.NativeLibraries.currentPlatform()
                : "no bundled build for this OS/arch",
            usePureJavaExport() ? "pure-java" : "native");

        if (!hasImGuiNative) {
            LOGGER.warn("No rebuilt ImGui native is bundled for {} / {}. "
                + "The binding will fall back to its original native library.",
                System.getProperty("os.name"), System.getProperty("os.arch"));
        }

        if (Boolean.getBoolean("compatibleimgui.selftest")) {
            SelfTest.run();
        }
        if (System.getProperty("compatibleimgui.screenshot.ticks") != null) {
            com.compatibleimgui.debug.ScreenshotHook.register();
        }
    }

    public static boolean usePureJavaExport() {
        String mode = System.getProperty("compatibleimgui.export", "java");
        return switch (mode) {
            case "java", "pure", "true" -> true;
            case "native", "ffmpeg", "false" -> false;
            default -> Platform.isAndroid() || !Platform.hasDesktopFFmpegNatives();
        };
    }
}
