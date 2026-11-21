package com.compatibleimgui.mixin.minecraft;

import com.compatibleimgui.shader.ShaderPatches;
import com.mojang.renderpearl.api.pipeline.ShaderSource;
import net.minecraft.client.renderer.ShaderManager;
import net.minecraft.resources.Identifier;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

/**
 * Applies {@link ShaderPatches} while shader includes are being loaded.
 *
 * <p>A normal resource-pack override is not sufficient here because vanilla
 * packs keep priority for shader includes on some launchers. Replacing the
 * cached include source directly makes the Android workaround deterministic.</p>
 */
@Mixin(ShaderManager.class)
public abstract class MixinShaderManager {

    @Redirect(
        method = "loadInclude",
        at = @At(
            value = "INVOKE",
            target = "Lcom/mojang/renderpearl/api/pipeline/ShaderSource$CachedIncludeSource;create(Lnet/minecraft/resources/Identifier;Ljava/lang/String;)Lcom/mojang/renderpearl/api/pipeline/ShaderSource$CachedIncludeSource;"
        ),
        remap = false
    )
    private static ShaderSource.CachedIncludeSource compatibleimgui$patchInclude(
        Identifier id, String source
    ) {
        return ShaderSource.CachedIncludeSource.create(id, ShaderPatches.patchInclude(id, source));
    }
}
