package com.compatibleimgui.debug;

import com.compatibleimgui.CompatibleImGuiMod;
import net.fabricmc.fabric.api.client.event.lifecycle.v1.ClientTickEvents;
import net.minecraft.client.Minecraft;
import net.minecraft.client.Screenshot;

/**
 * Development helper: capture the game's own framebuffer instead of relying on
 * an external desktop screenshot tool (which may capture the wrong window on
 * Wayland).
 *
 * <p>Enable with {@code -Dcompatibleimgui.screenshot.ticks=1200}. The screenshot is
 * written through Minecraft's normal screenshot path.</p>
 */
public final class ScreenshotHook {

    private static int ticks;
    private static boolean registered;

    private ScreenshotHook() {
    }

    public static void register() {
        if (registered) {
            return;
        }
        registered = true;
        int target = Integer.getInteger("compatibleimgui.screenshot.ticks", 1200);
        ClientTickEvents.END_CLIENT_TICK.register(client -> {
            if (++ticks != target) {
                return;
            }
            try {
                Minecraft minecraft = Minecraft.getInstance();
                if (Boolean.getBoolean("compatibleimgui.screenshot.axiom")) {
                    try {
                        Class<?> editor = Class.forName("com.moulberry.axiom.editor.EditorUI");
                        Object enabled = editor.getMethod("isEnabled").invoke(null);
                        if (!Boolean.TRUE.equals(enabled)) {
                            editor.getMethod("enable").invoke(null);
                        }
                    } catch (Throwable ignored) {
                    }
                }
                if (Boolean.getBoolean("compatibleimgui.screenshot.raise")) {
                    try {
                        long handle = minecraft.getWindow().handle();
                        org.lwjgl.sdl.SDLVideo.SDL_RaiseWindow(handle);
                        org.lwjgl.sdl.SDLVideo.SDL_SetWindowAlwaysOnTop(handle, true);
                    } catch (Throwable ignored) {
                    }
                }
                Screenshot.grab(Minecraft.getInstance(), false);
                CompatibleImGuiMod.LOGGER.info("Captured Minecraft framebuffer screenshot after {} ticks", ticks);
            } catch (Throwable t) {
                CompatibleImGuiMod.LOGGER.warn("Failed to capture Minecraft screenshot", t);
            }
        });
    }
}
