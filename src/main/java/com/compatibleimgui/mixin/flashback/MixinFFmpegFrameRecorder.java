package com.compatibleimgui.mixin.flashback;

import com.compatibleimgui.CompatibleImGuiMod;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

@Mixin(targets = "com.moulberry.flashback.exporting.FlashbackFFmpegFrameRecorder", remap = false)
public abstract class MixinFFmpegFrameRecorder {

    @Inject(method = "tryLoad", at = @At("HEAD"), cancellable = true, remap = false)
    private static void compatibleimgui$tryLoad(CallbackInfo ci) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            // Pretend FFmpeg is available. The exporter itself is replaced.
            ci.cancel();
        }
    }
}
