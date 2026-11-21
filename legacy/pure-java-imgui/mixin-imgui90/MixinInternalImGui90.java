package com.noimgui.mixin.imgui90;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

@Mixin(targets = "imgui.moulberry90.internal.ImGui", remap = false)
public abstract class MixinInternalImGui90 {

    @Inject(method = "<clinit>", at = @At("HEAD"), cancellable = true, remap = false)
    private static void noimgui$skipNative(CallbackInfo ci) {
        ci.cancel();
    }
}
