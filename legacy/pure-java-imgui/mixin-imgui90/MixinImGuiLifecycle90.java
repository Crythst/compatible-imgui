package com.noimgui.mixin.imgui90;

import com.noimgui.imgui.PureUi;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

@Mixin(targets = "imgui.moulberry90.ImGui", remap = false)
public abstract class MixinImGuiLifecycle90 {

    @Redirect(method = "<clinit>", at = @At(value = "INVOKE", target = "Ljava/lang/System;load(Ljava/lang/String;)V"), remap = false)
    private static void noimgui$skipLoad(String path) {
        PureUi.onClassInit("imgui.moulberry90");
    }

    @Redirect(method = "<clinit>", at = @At(value = "INVOKE", target = "Ljava/lang/System;loadLibrary(Ljava/lang/String;)V"), remap = false)
    private static void noimgui$skipLoadLibrary(String name) {
        PureUi.onClassInit("imgui.moulberry90");
    }

    @Overwrite(remap = false)
    private static void nInitJni() {
    }

    @Overwrite(remap = false)
    private static void nInitInputTextData() {
    }
}
