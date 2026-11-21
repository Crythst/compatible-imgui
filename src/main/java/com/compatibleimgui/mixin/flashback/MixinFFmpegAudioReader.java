package com.compatibleimgui.mixin.flashback;

import com.moulberry.flashback.sound.FFmpegAudioReader;
import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.audio.PureAudio;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

import javax.sound.sampled.AudioFormat;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

@Mixin(targets = "com.moulberry.flashback.sound.FFmpegAudioReader", remap = false)
public abstract class MixinFFmpegAudioReader {

    @Inject(method = "read", at = @At("HEAD"), cancellable = true, remap = false)
    private static void compatibleimgui$read(InputStream inputStream, CallbackInfoReturnable<FFmpegAudioReader.RawAudioData> cir) {
        if (!CompatibleImGuiMod.usePureJavaExport()) {
            return;
        }
        PureAudio.Decoded decoded = PureAudio.decode(inputStream);
        if (decoded != null) {
            ByteBuffer buffer = ByteBuffer.allocateDirect(decoded.pcm().length).order(ByteOrder.LITTLE_ENDIAN);
            buffer.put(decoded.pcm());
            buffer.flip();
            AudioFormat format = new AudioFormat(
                decoded.sampleRate(), decoded.bits(), decoded.channels(), true, false);
            cir.setReturnValue(new FFmpegAudioReader.RawAudioData(buffer, format));
        }
    }
}
