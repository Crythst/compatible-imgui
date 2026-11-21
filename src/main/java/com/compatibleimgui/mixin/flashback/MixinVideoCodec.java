package com.compatibleimgui.mixin.flashback;

import com.moulberry.flashback.combo_options.VideoCodec;
import com.compatibleimgui.CompatibleImGuiMod;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

@Mixin(targets = "com.moulberry.flashback.combo_options.VideoCodec", remap = false)
public abstract class MixinVideoCodec {

    @Inject(method = "getEncoders", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$getEncoders(CallbackInfoReturnable<String[]> cir) {
        if (!CompatibleImGuiMod.usePureJavaExport()) {
            return;
        }
        if ((Object) this == VideoCodec.H264) {
            cir.setReturnValue(new String[]{"purejava-h264"});
        } else if ((Object) this == VideoCodec.PNG) {
            cir.setReturnValue(new String[]{"purejava-png"});
        } else {
            cir.setReturnValue(new String[0]);
        }
    }

    @Inject(method = "supportsTransparency", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$supportsTransparency(CallbackInfoReturnable<Boolean> cir) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            cir.setReturnValue((Object) this == VideoCodec.PNG);
        }
    }
}
