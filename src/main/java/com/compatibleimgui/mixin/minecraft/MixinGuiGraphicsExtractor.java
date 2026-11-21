package com.compatibleimgui.mixin.minecraft;

import net.minecraft.client.gui.GuiGraphicsExtractor;
import net.minecraft.client.renderer.texture.TextureAtlas;
import org.spongepowered.asm.mixin.Final;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Shadow;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

/**
 * Prevents GUI sprite blits from crashing while the GUI atlas is being reloaded.
 *
 * <p>Minecraft clears the atlas data at the start of a resource reload. The
 * loading overlay of the previous reload keeps rendering the current screen
 * during its fade-out, so a second (manual) reload can reach
 * {@link TextureAtlas#getSprite} while {@code missingSprite} is still
 * {@code null}. Vanilla then throws
 * {@code IllegalStateException: Tried to lookup sprite, but atlas is not initialized}.
 * On slower platforms such as Android this race is easy to hit during startup.</p>
 *
 * <p>There is no meaningful sprite to draw while the atlas is empty, so the
 * blit is skipped until the reload has finished. The rest of the screen (text,
 * solid fills, the loading overlay itself) still renders normally.</p>
 */
@Mixin(GuiGraphicsExtractor.class)
public abstract class MixinGuiGraphicsExtractor {

    @Shadow
    @Final
    private TextureAtlas guiSprites;

    @Inject(
        method = {
            // blitSprite(RenderPipeline, Identifier, int x, int y, int width, int height, int color)
            "blitSprite(Lcom/mojang/renderpearl/api/pipeline/RenderPipeline;Lnet/minecraft/resources/Identifier;IIIII)V",
            // blitSprite(RenderPipeline, Identifier, int x, int y, int width, int height,
            //            int u, int v, int uWidth, int vHeight, int textureWidth, int textureHeight)
            "blitSprite(Lcom/mojang/renderpearl/api/pipeline/RenderPipeline;Lnet/minecraft/resources/Identifier;IIIIIIIIII)V"
        },
        at = @At("HEAD"),
        cancellable = true
    )
    private void compatibleimgui$skipSpritesWhileAtlasIsReloading(CallbackInfo ci) {
        TextureAtlasAccessor atlas = (TextureAtlasAccessor) (Object) this.guiSprites;
        if (atlas.compatibleimgui$missingSprite() == null) {
            // The atlas is between clearTextureData() and upload(). Nothing can
            // be drawn from it, and looking the sprite up would throw.
            ci.cancel();
        }
    }
}
