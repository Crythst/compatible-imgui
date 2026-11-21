package com.noimgui.mixin.imgui92;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry92.ImGuiPlatformIO", remap = false)
public abstract class MixinImGuiPlatformIONative92 {

    @Overwrite(remap = false)
    private static void nInit(imgui.moulberry92.ImGuiViewport viewport, imgui.moulberry92.ImVec2 vec) {
    }
}
