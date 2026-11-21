package com.compatibleimgui.shader;

import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.Platform;
import net.minecraft.resources.Identifier;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL20;

import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Shader-source compatibility patches for the MobileGlues/ANGLE GLES stack.
 *
 * <p>MobileGlues' GLSL-to-ESSL fallback scans for the literal substring
 * {@code uniform} without checking token boundaries. SPIRV-Cross-generated
 * identifiers such as {@code _uniform_instance_00_00} therefore get rewritten
 * into invalid declarations, producing {@code '_uniform' : undeclared identifier}
 * and {@code '_instance_00_00' : syntax error}. Prefixing alone is not enough:
 * the generated names must not contain the word {@code uniform} at all.</p>
 *
 * <p>The large OIT include is kept as a complete file under
 * {@code compatibleimgui/shaders/} so it can be diffed against vanilla.</p>
 */
public final class ShaderPatches {

    private static final boolean ENABLED =
        !Boolean.getBoolean("compatibleimgui.shaderPatch.disable")
            && (Platform.isAndroid()
                || Boolean.getBoolean("compatibleimgui.debug.shaderPatch"));

    private static final AtomicBoolean warned = new AtomicBoolean();
    private static volatile String oitAddTransmittance;
    private static volatile Identifier oitAddTransmittanceId;

    private ShaderPatches() {
    }

    /**
     * @return replacement source for the given include, or the original source
     *         when no Android workaround applies.
     */
    public static String patchInclude(Identifier id, String source) {
        if (!ENABLED || source == null || id == null || !id.equals(oitAddTransmittanceId())) {
            return source;
        }
        // Do not replace a resource pack's or another mod's custom include.
        if (!source.contains("attachmentIndex")) {
            return source;
        }
        String replacement = oitAddTransmittance;
        if (replacement == null) {
            replacement = load("/compatibleimgui/shaders/oit_add_transmittance.glsl");
            if (replacement == null) {
                return source;
            }
            oitAddTransmittance = replacement;
        }
        if (warned.compareAndSet(false, true)) {
            CompatibleImGuiMod.LOGGER.info(
                "Using Android GLES shader compatibility patch for {}", id);
        }
        return replacement;
    }

    /** Whether the Android GLES shader workarounds should be applied. */
    public static boolean isEnabled() {
        return ENABLED;
    }

    /**
     * Picks the GLSL ES version to ask SPIRV-Cross for.
     *
     * @return {@code 300}/{@code 310}/{@code 320} for a GLES context, or
     *         {@code -1} to keep Minecraft's desktop GLSL 330 output
     */
    public static int preferredGlslEsVersion() {
        Integer override = Integer.getInteger("compatibleimgui.shader.esVersion");
        if (override != null) {
            return override;
        }
        try {
            GL.getCapabilities();
            String version = GL11.glGetString(GL20.GL_SHADING_LANGUAGE_VERSION);
            if (version != null) {
                if (!version.contains("ES")) {
                    // Zink / GL4ES / a real desktop GL driver: keep GLSL 330.
                    return -1;
                }
                if (version.contains("3.20")) {
                    return 320;
                }
                if (version.contains("3.10")) {
                    return 310;
                }
                if (version.contains("3.00") || version.contains("3.0")) {
                    return 300;
                }
            }
        } catch (Throwable ignored) {
            // Shader includes are often prepared off the render thread, where
            // no GL context is current. The Android default below is safe.
        }
        return 320;
    }

    /**
     * Rewrites a generated GLSL identifier so MobileGlues' fallback converter
     * cannot split it. Both the decompiler and {@code GlProgram} reflection use
     * this method, so the names stay in sync.
     */
    public static String safeName(CharSequence name) {
        if (name == null) {
            return null;
        }
        String value = name.toString();
        if (!ENABLED || value.isEmpty() || value.charAt(0) != '_') {
            return value;
        }
        // `_uniform_00_00` -> `cis_ubo_00_00`,
        // `_uniform_instance_00_00` -> `cis_ubo_instance_00_00`.
        return "cis" + value.replace("uniform", "ubo");
    }

    private static Identifier oitAddTransmittanceId() {
        Identifier id = oitAddTransmittanceId;
        if (id == null) {
            id = Identifier.fromNamespaceAndPath("minecraft", "oit_add_transmittance.glsl");
            oitAddTransmittanceId = id;
        }
        return id;
    }

    private static String load(String path) {
        try (InputStream in = ShaderPatches.class.getResourceAsStream(path)) {
            if (in == null) {
                CompatibleImGuiMod.LOGGER.warn("Missing shader compatibility resource {}", path);
                return null;
            }
            return new String(in.readAllBytes(), StandardCharsets.UTF_8);
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.warn("Could not read shader compatibility resource {}", path, t);
            return null;
        }
    }
}
