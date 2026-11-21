package com.noimgui.mixin.imgui92;

import com.noimgui.imgui.PureUi;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

@Mixin(targets = "imgui.moulberry92.ImGui", remap = false)
public abstract class MixinImGuiLifecycle92 {

    @Redirect(method = "<clinit>", at = @At(value = "INVOKE", target = "Limgui/moulberry92/ImGui;tryLoadFromClasspath(Ljava/lang/String;)Ljava/lang/String;"), remap = false)
    private static String noimgui$skipClasspath(String name) {
        PureUi.onClassInit("imgui.moulberry92");
        return "no-imgui";
    }

    @Redirect(method = "<clinit>", at = @At(value = "INVOKE", target = "Ljava/lang/System;load(Ljava/lang/String;)V"), remap = false)
    private static void noimgui$skipLoad(String path) {
    }

    @Overwrite(remap = false)
    private static void nInitJni() {
    }

    @Overwrite(remap = false)
    private static void nInitInputTextData() {
    }
}
