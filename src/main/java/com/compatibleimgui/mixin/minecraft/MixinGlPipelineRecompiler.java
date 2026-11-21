package com.compatibleimgui.mixin.minecraft;

import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.shader.ShaderPatches;
import org.lwjgl.util.spvc.Spvc;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Makes Minecraft's OpenGL shader recompiler emit GLSL ES on Android.
 *
 * <p>Minecraft 26.3 uses SPIRV-Cross to turn its pipeline SPIR-V back into
 * GLSL. The vanilla options always ask for desktop GLSL 330. Android contexts
 * only provide GLSL ES (MobileGlues / ANGLE), which rejects desktop constructs
 * and, on MobileGlues' ESSL fallback path, mangles identifiers containing the
 * literal word {@code uniform}.</p>
 *
 * <p>The options are adjusted right before they are installed so SPIRV-Cross
 * emits the matching GLSL ES version with explicit default precisions. A real
 * desktop GL context (Zink/GL4ES) keeps Minecraft's vanilla GLSL 330 output.</p>
 */
@Mixin(targets = "com.mojang.renderpearl.backend.opengl.GlPipelineRecompiler", remap = false)
public abstract class MixinGlPipelineRecompiler {

    private static final AtomicBoolean compatibleimgui$loggedEs = new AtomicBoolean();
    private static final AtomicBoolean compatibleimgui$loggedNames = new AtomicBoolean();

    @Redirect(
        method = "decompileShader",
        at = @At(
            value = "INVOKE",
            target = "Lorg/lwjgl/util/spvc/Spvc;spvc_compiler_install_compiler_options(JJ)I"
        ),
        remap = false,
        require = 0
    )
    private static int compatibleimgui$useGlslEsOnAndroid(long compiler, long options) {
        int esVersion = ShaderPatches.preferredGlslEsVersion();
        if (ShaderPatches.isEnabled() && esVersion > 0) {
            try {
                Spvc.spvc_compiler_options_set_uint(
                    options, Spvc.SPVC_COMPILER_OPTION_GLSL_VERSION, esVersion);
                Spvc.spvc_compiler_options_set_bool(
                    options, Spvc.SPVC_COMPILER_OPTION_GLSL_ES, true);
                Spvc.spvc_compiler_options_set_bool(
                    options, Spvc.SPVC_COMPILER_OPTION_GLSL_ES_DEFAULT_FLOAT_PRECISION_HIGHP, true);
                Spvc.spvc_compiler_options_set_bool(
                    options, Spvc.SPVC_COMPILER_OPTION_GLSL_ES_DEFAULT_INT_PRECISION_HIGHP, true);
                if (compatibleimgui$loggedEs.compareAndSet(false, true)) {
                    CompatibleImGuiMod.LOGGER.info(
                        "Using GLSL ES {} shader output for Android OpenGL", esVersion);
                }
            } catch (Throwable t) {
                // Never let a shader compatibility tweak take the game down.
                CompatibleImGuiMod.LOGGER.warn("Could not enable GLSL ES shader output", t);
            }
        }
        return Spvc.spvc_compiler_install_compiler_options(compiler, options);
    }

    @Redirect(
        method = {"renameDescriptors", "renameInterfaceVariables"},
        at = @At(
            value = "INVOKE",
            target = "Lorg/lwjgl/util/spvc/Spvc;spvc_compiler_set_name(JILjava/lang/CharSequence;)V"
        ),
        remap = false,
        require = 0
    )
    private static void compatibleimgui$sanitizeGeneratedName(
        long compiler, int id, CharSequence name
    ) {
        if (ShaderPatches.isEnabled()
            && name != null && !name.isEmpty() && name.charAt(0) == '_'
            && compatibleimgui$loggedNames.compareAndSet(false, true)) {
            CompatibleImGuiMod.LOGGER.info(
                "Using Android-safe shader identifiers (uniform -> ubo)");
        }
        String safe = ShaderPatches.safeName(name);
        if (safe != null) {
            Spvc.spvc_compiler_set_name(compiler, id, safe);
        }
    }
}
