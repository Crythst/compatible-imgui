package com.compatibleimgui.mixin.flashback;

import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.Platform;
import com.mojang.renderpearl.api.textures.GpuTexture;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Shadow;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

/**
 * Logs the size of the Flashback ImGui font atlas on Android.
 *
 * <p>Font corruption reports are otherwise silent: the atlas upload succeeds
 * but the texture is too large for the device. This log makes the next report
 * actionable without changing rendering behaviour.</p>
 */
@Mixin(targets = "com.moulberry.flashback.editor.ui.CustomImGuiImplB3D", remap = false)
public abstract class MixinCustomImGuiImplB3D {

    @Shadow
    private GpuTexture fontTexture;

    @Inject(method = "updateFontsTexture", at = @At("RETURN"), remap = false)
    private void compatibleimgui$logFontAtlas(CallbackInfo ci) {
        if (!Platform.isAndroid()) {
            return;
        }
        GpuTexture texture = this.fontTexture;
        if (texture != null) {
            CompatibleImGuiMod.LOGGER.info(
                "Flashback ImGui font atlas: {}x{}", texture.getWidth(0), texture.getHeight(0));
        }
    }
}
