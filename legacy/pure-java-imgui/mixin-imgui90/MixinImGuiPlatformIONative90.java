package com.noimgui.mixin.imgui90;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry90.ImGuiPlatformIO", remap = false)
public abstract class MixinImGuiPlatformIONative90 {

    @Overwrite(remap = false)
    private static void nInit(imgui.moulberry90.ImGuiViewport viewport, imgui.moulberry90.ImVec2 vec) {
    }
}
