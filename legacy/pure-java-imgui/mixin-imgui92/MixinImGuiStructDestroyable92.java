package com.noimgui.mixin.imgui92;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry92.binding.ImGuiStructDestroyable", remap = false)
public abstract class MixinImGuiStructDestroyable92 {
    @Overwrite(remap = false)
    private void nDestroy(long ptr) {
    }
}
