package com.compatibleimgui.mixin.flashback;

import com.moulberry.flashback.exporting.ExportSettings;
import com.moulberry.flashback.exporting.VideoWriter;
import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.Reflect;
import com.compatibleimgui.export.PureJavaVideoWriter;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable;

@Mixin(targets = "com.moulberry.flashback.exporting.ExportJob", remap = false)
public abstract class MixinExportJob {

    @Inject(method = "createVideoWriter", at = @At("RETURN"), cancellable = true, remap = false)
    private static void compatibleimgui$createVideoWriter(CallbackInfoReturnable<VideoWriter> cir) {
        if (!CompatibleImGuiMod.usePureJavaExport()) {
            return;
        }
        VideoWriter original = cir.getReturnValue();
        if (original == null) {
            return;
        }
        try {
            ExportSettings settings = (ExportSettings) Reflect.getDeclared(original, "settings");
            String filename = (String) Reflect.getDeclared(original, "filename");
            cir.setReturnValue(new PureJavaVideoWriter(settings, filename));
        } catch (RuntimeException e) {
            // If Flashback changes the field names, keep the original writer.
            CompatibleImGuiMod.LOGGER.warn("Unable to replace Flashback video writer", e);
        }
    }
}
