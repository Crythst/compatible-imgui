package com.compatibleimgui.mixin.flashback;

import com.compatibleimgui.CompatibleImGuiMod;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

@Mixin(targets = "com.moulberry.flashback.combo_options.AudioCodec", remap = false)
public abstract class MixinAudioCodec {

    @Inject(method = "getEncoders", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$getEncoders(CallbackInfoReturnable<String[]> cir) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            // The pure-Java exporter currently writes video-only files. Hiding
            // audio encoders makes the UI consistent with that behaviour.
            cir.setReturnValue(new String[0]);
        }
    }
}
