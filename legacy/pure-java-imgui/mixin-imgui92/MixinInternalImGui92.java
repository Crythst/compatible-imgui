package com.noimgui.mixin.imgui92;

import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

@Mixin(targets = "imgui.moulberry92.internal.ImGui", remap = false)
public abstract class MixinInternalImGui92 {

    @Inject(method = "<clinit>", at = @At("HEAD"), cancellable = true, remap = false)
    private static void noimgui$skipNative(CallbackInfo ci) {
        ci.cancel();
    }
}
