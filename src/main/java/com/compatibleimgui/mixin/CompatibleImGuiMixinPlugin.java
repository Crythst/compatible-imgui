package com.compatibleimgui.mixin;

import com.compatibleimgui.CompatibleImGuiMod;
import net.fabricmc.loader.api.FabricLoader;
import org.objectweb.asm.tree.ClassNode;
import org.spongepowered.asm.mixin.extensibility.IMixinConfigPlugin;
import org.spongepowered.asm.mixin.extensibility.IMixinInfo;

import java.util.List;
import java.util.Set;

/**
 * Applies the native ImGui loader redirects and the portable FFmpeg/zstd
 * replacements only when the corresponding target mod is present. The ImGui
 * redirect is additionally gated on a bundled native build for this OS/arch.
 */
public final class CompatibleImGuiMixinPlugin implements IMixinConfigPlugin {

    @Override
    public void onLoad(String mixinPackage) {
        CompatibleImGuiMod.LOGGER.debug("compatible-imgui mixin config loaded (package {})", mixinPackage);
    }

    @Override
    public String getRefMapperConfig() {
        return null;
    }

    @Override
    public boolean shouldApplyMixin(String targetClassName, String mixinClassName) {
        try {
            boolean flashback = FabricLoader.getInstance().isModLoaded("flashback");
            boolean axiom = FabricLoader.getInstance().isModLoaded("axiom");

            // Android GLES shader workarounds. Keep these off desktop clients so
            // a future Minecraft shader refactor cannot break normal startup.
            if (mixinClassName.endsWith(".MixinGlPipelineRecompiler")
                || mixinClassName.endsWith(".MixinGlProgram")
                || mixinClassName.endsWith(".MixinShaderManager")) {
                return shaderCompatEnabled();
            }

            if (mixinClassName.contains(".nativebridge.")) {
                boolean target = mixinClassName.contains("90") ? flashback : axiom;
                return target && com.compatibleimgui.bridge.NativeLibraries.hasCurrentPlatform();
            }
            if (mixinClassName.endsWith(".MixinReplayUIFontRanges")
                || mixinClassName.endsWith(".MixinCustomImGuiImplB3D")) {
                // Font atlas workarounds are independent of the FFmpeg mode.
                return flashback;
            }
            if (mixinClassName.contains(".flashback.")) {
                return flashback && CompatibleImGuiMod.usePureJavaExport();
            }
            if (mixinClassName.contains(".axiom.")) {
                return axiom;
            }
            if (mixinClassName.contains(".zstd.")) {
                return axiom;
            }
            return true;
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.warn("Could not evaluate mixin {}", mixinClassName, t);
            return false;
        }
    }

    private static boolean shaderCompatEnabled() {
        return !Boolean.getBoolean("compatibleimgui.shaderPatch.disable")
            && (com.compatibleimgui.Platform.isAndroid()
                || Boolean.getBoolean("compatibleimgui.debug.shaderPatch"));
    }

    @Override
    public void acceptTargets(Set<String> myTargets, Set<String> otherTargets) {
    }

    @Override
    public List<String> getMixins() {
        return null;
    }

    @Override
    public void preApply(String targetClassName, ClassNode targetClass, String mixinClassName, IMixinInfo mixinInfo) {
    }

    @Override
    public void postApply(String targetClassName, ClassNode targetClass, String mixinClassName, IMixinInfo mixinInfo) {
    }
}
