package com.noimgui.mixin.imgui90;

import com.noimgui.imgui.PureUi;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry90.ImFontConfig", remap = false)
public abstract class MixinImFontConfigNative90 {
    @Overwrite(remap = false)
    private long nCreate() {
        return PureUi.newNativeHandle();
    }
}
