package com.compatibleimgui.mixin.flashback;

import com.moulberry.flashback.combo_options.AudioCodec;
import com.moulberry.flashback.combo_options.VideoCodec;
import com.moulberry.flashback.combo_options.VideoContainer;
import com.compatibleimgui.CompatibleImGuiMod;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

@Mixin(targets = "com.moulberry.flashback.combo_options.VideoContainer", remap = false)
public abstract class MixinVideoContainer {

    @Inject(method = "getSupportedVideoCodecs", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$getSupportedVideoCodecs(boolean transparency, CallbackInfoReturnable<VideoCodec[]> cir) {
        if (!CompatibleImGuiMod.usePureJavaExport()) {
            return;
        }
        if ((Object) this == VideoContainer.PNG_SEQUENCE) {
            cir.setReturnValue(new VideoCodec[]{VideoCodec.PNG});
        } else if ((Object) this == VideoContainer.MP4 && !transparency) {
            cir.setReturnValue(new VideoCodec[]{VideoCodec.H264});
        } else {
            cir.setReturnValue(new VideoCodec[0]);
        }
    }

    @Inject(method = "getSupportedAudioCodecs", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$getSupportedAudioCodecs(CallbackInfoReturnable<AudioCodec[]> cir) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            cir.setReturnValue(new AudioCodec[0]);
        }
    }

    @Inject(method = "findSupportedContainers", at = @At("HEAD"), cancellable = true, remap = false)
    private static void compatibleimgui$findSupportedContainers(boolean transparency, CallbackInfoReturnable<VideoContainer[]> cir) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            cir.setReturnValue(transparency
                ? new VideoContainer[]{VideoContainer.PNG_SEQUENCE}
                : new VideoContainer[]{VideoContainer.MP4, VideoContainer.PNG_SEQUENCE});
        }
    }

    @Inject(method = "isImageSequence", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$isImageSequence(CallbackInfoReturnable<Boolean> cir) {
        if (CompatibleImGuiMod.usePureJavaExport()) {
            cir.setReturnValue((Object) this == VideoContainer.PNG_SEQUENCE);
        }
    }
}
