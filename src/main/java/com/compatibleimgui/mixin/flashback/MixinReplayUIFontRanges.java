package com.compatibleimgui.mixin.flashback;

import com.compatibleimgui.CompatibleImGuiMod;
import com.compatibleimgui.Platform;
import imgui.moulberry90.ImFontAtlas;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Redirect;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Keeps Flashback's ImGui font atlas within Android texture limits.
 *
 * <p>Flashback asks Dear ImGui for the full CJK range
 * ({@code GetGlyphRangesChineseFull}), then merges both Noto Sans TC and SC at
 * a larger pixel size. On desktop that is merely a large atlas; on Android the
 * resulting atlas can exceed the practical texture/upload limits and text is
 * rendered garbled. Axiom uses the "common simplified Chinese" range and works
 * on the same device.</p>
 *
 * <p>Android therefore uses the same common range. Other languages keep their
 * existing ranges and desktop keeps the full range.</p>
 */
@Mixin(targets = "com.moulberry.flashback.editor.ui.ReplayUI", remap = false)
public abstract class MixinReplayUIFontRanges {

    private static final AtomicBoolean compatibleimgui$logged = new AtomicBoolean();

    @Redirect(
        method = "initFonts",
        at = @At(
            value = "INVOKE",
            target = "Limgui/moulberry90/ImFontAtlas;getGlyphRangesChineseFull()[S"
        ),
        remap = false,
        require = 0
    )
    private static short[] compatibleimgui$commonChineseRanges(ImFontAtlas atlas) {
        if (Platform.isAndroid()) {
            if (compatibleimgui$logged.compareAndSet(false, true)) {
                CompatibleImGuiMod.LOGGER.info(
                    "Using common Chinese glyph ranges for the Flashback ImGui atlas on Android");
            }
            return atlas.getGlyphRangesChineseSimplifiedCommon();
        }
        return atlas.getGlyphRangesChineseFull();
    }
}
