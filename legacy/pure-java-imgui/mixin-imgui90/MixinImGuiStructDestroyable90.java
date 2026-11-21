package com.noimgui.mixin.imgui90;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry90.binding.ImGuiStructDestroyable", remap = false)
public abstract class MixinImGuiStructDestroyable90 {
    @Overwrite(remap = false)
    private void nDestroy(long ptr) {
    }
}
