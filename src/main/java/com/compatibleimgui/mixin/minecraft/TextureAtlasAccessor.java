package com.compatibleimgui.mixin.minecraft;

import net.minecraft.client.renderer.texture.TextureAtlas;
import net.minecraft.client.renderer.texture.TextureAtlasSprite;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.gen.Accessor;

/**
 * Exposes the nullable {@code missingSprite} field of a texture atlas.
 *
 * <p>While a resource reload is running, {@link TextureAtlas#clearTextureData()}
 * sets this field to {@code null} and empties the sprite map. Any GUI that is
 * still being drawn during that window will fail inside
 * {@link TextureAtlas#getSprite}. This accessor lets the GUI guard detect that
 * state without triggering the exception on purpose.</p>
 */
@Mixin(TextureAtlas.class)
public interface TextureAtlasAccessor {

    @Accessor("missingSprite")
    TextureAtlasSprite compatibleimgui$missingSprite();
}
