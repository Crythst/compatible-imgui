package com.noimgui.mixin.imgui92;

import com.noimgui.imgui.PureUi;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;

@Mixin(targets = "imgui.moulberry92.ImFontAtlas", remap = false)
public abstract class MixinImFontAtlasNative92 {

    @Overwrite(remap = false)
    static void nInit() {
    }

    @Overwrite(remap = false)
    private long nCreate() {
        return PureUi.newNativeHandle();
    }
}
