package com.compatibleimgui.mixin.nativebridge;

import com.compatibleimgui.bridge.NativeLibraries;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

import java.io.InputStream;

/**
 * Redirects Axiom's imgui 1.92 native lookup to the architecture-specific
 * library built by {@code native/build.sh}.
 */
@Mixin(targets = "imgui.moulberry92.ImGui", remap = false)
public abstract class MixinImGuiNativeLoader92 {

    @Redirect(
        method = "tryLoadFromClasspath",
        at = @At(
            value = "INVOKE",
            target = "Ljava/lang/ClassLoader;getResourceAsStream(Ljava/lang/String;)Ljava/io/InputStream;"
        ),
        remap = false
    )
    private static InputStream compatibleimgui$open(ClassLoader loader, String name) {
        InputStream replacement = NativeLibraries.open(name);
        return replacement != null ? replacement : loader.getResourceAsStream(name);
    }
}
