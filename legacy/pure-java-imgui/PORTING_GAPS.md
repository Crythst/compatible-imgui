> **LEGACY:** this document describes the removed/optional hand-written Java ImGui port.
> The default implementation is now the rebuilt upstream C++ backend; see `native/README.md`.

# PORTING_GAPS

Analysis of `run/calls.txt` against `src/main/java/com/noimgui/imgui/PureUi.java` (dispatcher at `UiContext.dispatch`, per-class handlers) and the generated `imgui90` / `imgui92` mixins.

- Source of truth: 424 unique `owner.method(descriptor)` entries from a real Axiom 6.1.5 + Flashback 0.43.6 run.
- Packages: `imgui.moulberry90` (Flashback) and `imgui.moulberry92` (Axiom).
- No build or `runClient` was executed for this report.

Status legend (per call descriptor, so the same Java method can appear twice with different verdicts):

| Status | Meaning |
|---|---|
| **OK** | Dispatched to a meaningful implementation with the observed descriptor. |
| **PARTIAL** | Dispatched, but semantics are incomplete/wrong for this descriptor or for the mod's use of it. |
| **NO-OP** | Explicitly accepted and ignored, or a handler always returns a constant. |
| **MISSING** | No handler / wrong overload; returns `null`, `0`, `false`, or a fake object. |

Summary: **269 OK, 108 PARTIAL, 31 NO-OP, 16 MISSING** (424 total). The "MISSING" count is small, but several PARTIAL cases are catastrophic for layout (notably `calcTextSize` and the `textColored(int,String)` overload). Priority below is by visible Axiom/Flashback impact, not by count.

Quick list of calls that are ignored or have no handler at all:

- **MISSING**: every `ImFontConfig` method (`create`, `setMergeMode`, `setName`, `setGlyphOffset`, `setOversampleH/V` in both packages), `ImGuiStyle.create`, `TextEditor.create`, `TextEditorLanguage.Lua`, `internal.ImGuiDockNode.addLocalFlags`.
- **NO-OP**: `ImGui.setAssertCallback`, `setCurrentContext`, `init`, `setNextWindowViewport`, `setScrollX`, `setWindowFocus`, `setMouseCursor`, `getMouseCursor`, `beginDragDropSource`, `beginDragDropTarget`, `isItemVisible`, `isRectVisible`, `ImGuiIO.addMouseSourceEvent`, `getMouseDrawCursor`, `setConfigMacOSXBehaviors`, `ImFontAtlas.clearTexData`, `TextEditor.setAutoIndentEnabled`, `setLanguage`, `setShowWhitespacesEnabled`.
- **PARTIAL but visually critical**: `calcTextSize`, `textColored(int,String)`, `ImFontAtlas.addFontFromMemoryTTF`, `beginChild`, `getContentRegionAvailY`, `getWindowContentRegionMaxY`, `pushFont`, `setCursorScreenPos`, all `ImGuiStyle` instance methods, `colorConvertFloat4ToU32(ImVec4)`, `dockBuilderGetCentralNode`, `styleColorsLight`.

---

## Top 10 porting gaps

### 1. `ImGui.calcTextSize(ImVec2 out, String text)` writes nothing

Observed in both packages:

```text
imgui.moulberry90.ImGui.calcTextSize(Limgui/moulberry90/ImVec2;Ljava/lang/String;)V
imgui.moulberry92.ImGui.calcTextSize(Limgui/moulberry92/ImVec2;Ljava/lang/String;)V
```

Axiom `ImGuiHelper.calcTextWidth(String)` and Flashback `ImGuiHelper.calcTextWidth(String)` do:

```java
ImVec2 size = new ImVec2();
ImGui.calcTextSize(size, text);
return size.x;
```

The current dispatcher always treats `args[0]` as the text:

```java
case "calcTextSize": return calcTextSize(argS(args, 0), arg(args, 1), argB(args, 2, true), argF(args, 3, -1));
```

With the out-param overload the text becomes `ImVec2.toString()`, the wrap width becomes `null`, and the output vector is never written. Every `calcTextWidth` returns `0`, which breaks label alignment, right-aligned widgets, tooltip sizing, button widths, etc.

**Exact change** in `UiContext.imgui(...)`:

```java
case "calcTextSize" -> {
    Object first = arg(args, 0);
    if (first != null
            && first.getClass().getSimpleName().equals("ImVec2")
            && args.length >= 2
            && arg(args, 1) instanceof String text) {
        Object measured = calcTextSize(text, null, true, -1f);
        Reflect.set(first, "x", f(Reflect.get(measured, "x")));
        Reflect.set(first, "y", f(Reflect.get(measured, "y")));
        return null;
    }
    return calcTextSize(argS(args, 0), arg(args, 1), argB(args, 2, true), argF(args, 3, -1));
}
```

Also fix the helper to use the active font size (see gap 5) and to honour `hideAfterDoubleHash` by truncating at `##` before measuring:

```java
Object calcTextSize(String text, Object wrapWidth, boolean hideAfterDoubleHash, float scale) {
    if (hideAfterDoubleHash && text != null) {
        int hash = text.indexOf("##");
        if (hash >= 0) text = text.substring(0, hash);
    }
    float size = currentFontSize() * (scale > 0 ? scale : 1);
    float width = this.atlas.measure(text, size);
    float wrap = wrapWidth instanceof Number n ? n.floatValue() : this.textWrapPos;
    if (wrap > 0) width = Math.min(width, wrap);
    return vec2(width, size);
}
```

Semantics: return `ImVec2(measured advance, line height)`; line height should be the font's line height, not a hard-coded font size. Add the equivalent `calcTextSizeX/Y` handling only after the out-param check.

---

### 2. `ImGui.textColored(int packedColor, String text)` draws an empty string

Observed in both packages (Axiom warning labels, `ImGuiHelper.textColored`, etc.):

```text
imgui.moulberry90.ImGui.textColored(ILjava/lang/String;)V
imgui.moulberry92.ImGui.textColored(ILjava/lang/String;)V
```

Current code only understands `(ImVec4,String)` and `(F,F,F,F,String)`:

```java
case "textColored":
    if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec4")) {
        ... argS(args, 1)
    } else {
        textColored(argF(args,0,1), argF(args,1,1), argF(args,2,1), argF(args,3,1), argS(args,4));
    }
```

For `(int,String)` this reads the text from `args[4]` (absent), so it draws `""`. The packed color is also interpreted as a float channel.

**Exact change**:

```java
case "textColored" -> {
    Object a0 = arg(args, 0);

    // ImGui::TextColored(ImU32 col, const char* text) -> IM_COL32 is packed R|G<<8|B<<16|A<<24
    if (desc.startsWith("(I") && args.length >= 2 && a0 instanceof Integer && arg(args, 1) instanceof String text) {
        int c = ((Integer) a0);
        textColored((c & 0xFF) / 255f,
                    ((c >> 8) & 0xFF) / 255f,
                    ((c >> 16) & 0xFF) / 255f,
                    ((c >>> 24) & 0xFF) / 255f,
                    text);
        return null;
    }

    // ImGui::TextColored(int r, int g, int b, int a, const char* text)
    if (desc.startsWith("(IIII") && args.length >= 5) {
        textColored(argI(args,0,255) / 255f, argI(args,1,255) / 255f,
                    argI(args,2,255) / 255f, argI(args,3,255) / 255f, argS(args,4));
        return null;
    }

    if (a0 != null && a0.getClass().getSimpleName().equals("ImVec4")) {
        Object c = a0;
        textColored(f(Reflect.get(c,"x")), f(Reflect.get(c,"y")),
                    f(Reflect.get(c,"z")), f(Reflect.get(c,"w")), argS(args,1));
    } else {
        textColored(argF(args,0,1), argF(args,1,1), argF(args,2,1), argF(args,3,1), argS(args,4));
    }
    return null;
}
```

`textColored(...)` must also use the current font size and call `itemSize(...)` exactly once (see gap 5).

---

### 3. Font pipeline: `ImFontConfig` is completely unported and `addFont` changes the default font

Observed:

```text
ImFontConfig.create()J
ImFontConfig.setGlyphOffset(FF)V
ImFontConfig.setMergeMode(Z)V
ImFontConfig.setName(String)V
ImFontConfig.setOversampleH(I)V
ImFontConfig.setOversampleV(I)V
ImFontAtlas.addFontFromMemoryTTF([BFLconfig;[S)ImFont
ImFontAtlas.build()Z
ImFontAtlas.clearTexData()V
ImFontAtlas.setTexID(J)V
```

Both mods load a font stack like this (Axiom/Flashback `loadFonts`):

1. `Inter` (normal UI font), `mergeMode=false`.
2. `heebo` / `NotoSansJP` / `NotoSansTC/SC` / `NotoSansKR` (CJK), `mergeMode=true`.
3. Material/Axiom icon font, `mergeMode=true`, often with a non-zero `glyphOffset`.
4. `Monocraft` (monospace), then an icon font (Axiom uses `mergeMode=false` for icons and `pushFont(icons, getLegacySize())` when drawing icon glyphs).

Problems:

- `ImFontConfig` has no dispatch case. `create()` returns `0`, so the `ImFontConfig` constructor leaves `ptr == 0`; all setters are dropped. Merge mode, glyph offset, oversampling, name and glyph ranges are lost.
- `FontAtlas.addFont(...)` currently does `this.current = font` unconditionally. After loading, the current font is the **last icon font**, not `Inter`. Axiom never pushes `Inter` around normal text, so normal UI text is rendered with the icon font (and `getFontSize()` returns the icon font size).
- `addFontFromMemoryTTF` ignores the `ImFontConfig` and the trailing `short[] glyphRanges`. `ensureAtlas()` only rasterises ASCII plus `0xE000-0xE0FF`, `0xE900-0xE9FF`, `0xF000-0xF0FF`; many Axiom/Flashback icon codepoints and all CJK codepoints are absent.
- Merged fonts are separate `FontData` entries; `FontAtlas.drawText` only looks in `current`, so CJK/icons never fall back even if their glyphs exist.
- `build()` returns `null` -> `false`. Axiom ignores the result (`pop`), but `build()` should return `true` after validation. `setTexID(J)` truncates through `argI`, and `clear()` leaves `current` pointing at a removed font.

**Exact changes**:

1. Add to `UiContext`:

```java
final Map<Long, FontConfigData> fontConfigs = new HashMap<>();

static final class FontConfigData {
    boolean mergeMode;
    float glyphOffsetX, glyphOffsetY;
    int oversampleH = 1, oversampleV = 1;
    String name = "";
    float sizePixels;
    short[] glyphRanges;
    short[] glyphExcludeRanges;
    boolean pixelSnapH;
    float rasterizerMultiply = 1f;
}
```

2. Add `case "ImFontConfig" -> return fontConfig(name, desc, self, args);` to `dispatch(...)`, and implement:

```java
Object fontConfig(String name, String desc, Object self, Object[] args) {
    if (name.equals("create")) {
        long h = newHandle();
        this.fontConfigs.put(h, new FontConfigData());
        return h;
    }
    FontConfigData cfg = self == null ? null
        : this.fontConfigs.computeIfAbsent(ptr(self), k -> new FontConfigData());
    if (cfg == null) return null;
    switch (name) {
        case "setMergeMode": cfg.mergeMode = argB(args,0,false); return null;
        case "getMergeMode": return cfg.mergeMode;
        case "setGlyphOffset": cfg.glyphOffsetX = argF(args,0,0); cfg.glyphOffsetY = argF(args,1,0); return null;
        case "getGlyphOffsetX": return cfg.glyphOffsetX;
        case "getGlyphOffsetY": return cfg.glyphOffsetY;
        case "setOversampleH": cfg.oversampleH = argI(args,0,1); return null;
        case "setOversampleV": cfg.oversampleV = argI(args,0,1); return null;
        case "getOversampleH": return cfg.oversampleH;
        case "getOversampleV": return cfg.oversampleV;
        case "setName": cfg.name = argS(args,0); return null;
        case "setSizePixels": cfg.sizePixels = argF(args,0,0); return null;
        case "setGlyphRanges": cfg.glyphRanges = (short[]) arg(args,0); return null;
        case "setGlyphExcludeRanges": cfg.glyphExcludeRanges = (short[]) arg(args,0); return null;
        case "setPixelSnapH": cfg.pixelSnapH = argB(args,0,false); return null;
        case "setRasterizerMultiply": cfg.rasterizerMultiply = argF(args,0,1); return null;
        default: return null;
    }
}
```

3. Change `FontAtlas.addFont` so the first real font becomes current and merged fonts do not:

```java
FontData addFont(int size, Object object, byte[] bytes,
                 FontConfigData cfg, short[] ranges) {
    boolean noRealFontYet = this.current == null
        || (this.current.ttf == null && this.current.cff == null);
    FontData font = new FontData(size, object, bytes);
    font.offsetX = cfg == null ? 0 : cfg.glyphOffsetX;
    font.offsetY = cfg == null ? 0 : cfg.glyphOffsetY;
    font.ranges = ranges != null ? ranges : (cfg == null ? null : cfg.glyphRanges);
    this.fonts.add(font);
    if (noRealFontYet) this.current = font;             // Fonts[0] analogue
    if (cfg != null && cfg.mergeMode && this.current != null && this.current != font) {
        this.current.merged.add(font);
    }
    return font;
}
```

Do **not** assign `this.current = font` for every add. Keep `FontData.font.object` wrappers as they are.

4. In `fontAtlas(...)` `addFontFromMemoryTTF`, resolve the config and ranges:

```java
FontConfigData cfg = null;
short[] ranges = null;
for (Object a : args) {
    if (a != null && a.getClass().getSimpleName().equals("ImFontConfig")) {
        cfg = (FontConfigData) data(a);
    } else if (a instanceof short[] s) {
        ranges = s;
    }
}
FontData font = atlas.addFont((int) Math.max(8, size), null, fontBytes, cfg, ranges);
```

Implement `build()` as `atlas.ensureAtlas(); return true;`, `clear()` as `fonts.clear(); current = null; atlasBuilt = false;`, and `setTexID(view) { atlas.texId = arg(args,0) instanceof Number n ? n.longValue() : 0; }` (change `FontAtlas.texId` to `long`).

5. `ensureAtlas` and `drawText` must walk merged fonts:

```java
GlyphEntry glyphEntry(FontData font, int codepoint, int pixelSize) {
    GlyphEntry e = font.glyphs.get(codepoint);
    if (e != null) return e;
    for (FontData merged : font.merged) {
        e = merged.glyphs.get(codepoint);
        if (e != null) return e;
    }
    return null;
}
```

Rasterise the union of `0x20..0x7E`, the explicit `FontConfigData.glyphRanges`, and the PUA ranges actually used by the icon fonts (at minimum `0xE000..0xF8FF`; Axiom also uses axiomicons PUA and Flashback material icons). Apply `offsetX/offsetY` in `drawText` and `measure`.

6. `ImFontAtlas.build()` returning `false` today is not fatal for the observed Axiom call (result popped), but returning `true` is required for other callers and makes the contract honest.

---

### 4. BeginChild / content-region / scroll geometry is systematically too small

Observed:

```text
ImGui.beginChild(String,FFZI)Z          (90)
ImGui.beginChild(String)Z               (92)
ImGui.getContentRegionAvailX/Y()F       (92)
ImGui.getWindowContentRegionMaxX/Y()F   (90+92)
ImGui.setCursorScreenPos(FF)V           (90+92)
ImGui.setScrollX(F)V                    (92)
```

`begin` currently computes:

```java
w.contentY = titleHeight + style.windowPaddingY;
w.contentW = Math.max(1, w.w - w.contentX * 2);
w.contentH = Math.max(1, w.h - titleHeight - w.contentY);   // titleHeight subtracted twice
```

For `h=300, titleHeight=24, paddingY=8`: `contentY=32`, current `contentH=244`, expected `260`. Content region max Y is returned as `h - contentY` (268) instead of `contentY + contentH` (292). Axiom's label/palette layout and Flashback's timeline both read these values.

`beginChild` compounds it:

```java
float childW = width > 0 ? width : Math.max(1, parent.w - parent.cursorX);
float childH = height > 0 ? height : Math.max(1, parent.h - parent.cursorY);
```

This uses the full parent window minus the absolute cursor (not content-region available), so a zero-size child is `paddingX`/`paddingY` too large and overflows. The `(String,FF,Z,I)` descriptor also has a boolean border in `args[3]` and window flags in `args[4]`; the dispatcher calls `argI(args,3,0)`, which ignores the Boolean (it falls back to `0`), and it drops `args[4]`.

**Exact changes**:

```java
// begin(...)
w.contentY = titleHeight + style.windowPaddingY;
w.contentW = Math.max(1, w.w - w.contentX * 2);
w.contentH = Math.max(1, w.h - w.contentY - style.windowPaddingY);
```

```java
case "getWindowContentRegionMaxX": return currentWindow().contentX + currentWindow().contentW;
case "getWindowContentRegionMaxY": return currentWindow().contentY + currentWindow().contentH; // == h - paddingY
case "getContentRegionAvailX":
    return Math.max(1, currentWindow().contentX + currentWindow().contentW - currentWindow().cursorX);
case "getContentRegionAvailY":
    return Math.max(1, currentWindow().contentY + currentWindow().contentH - currentWindow().cursorY);
```

```java
boolean beginChild(String id, float width, float height, int flags, boolean border) {
    Window parent = currentWindow();
    float availW = Math.max(1, parent.contentW - (parent.cursorX - parent.contentX));
    float availH = Math.max(1, parent.contentH - (parent.cursorY - parent.contentY));
    float childW = width > 0 ? width : availW;
    float childH = height > 0 ? height : availH;
    // ... existing child setup ...
    // draw a border if requested rather than treating the bool as flags
}

case "beginChild" -> {
    if (args.length >= 4 && arg(args, 3) instanceof Boolean) {
        return beginChild(argS(args,0), argF(args,1,0), argF(args,2,0),
                          argI(args,4,0), argB(args,3,false));
    }
    return beginChild(argS(args,0), argF(args,1,0), argF(args,2,0), argI(args,3,0), false);
}
```

Scroll fixes:

```java
// Window: add scrollX/scrollMaxX
float scrollX, scrollMaxX;

case "getScrollX": return currentWindow().scrollX;
case "setScrollX": currentWindow().scrollX = argF(args,0,0); return null;
case "getScrollMaxY": return currentWindow().scrollMaxY; // computed in end()
case "getScrollMaxX": return currentWindow().scrollMaxX;

case "getCursorScreenPosX": return currentWindow().x + currentWindow().cursorX - currentWindow().scrollX;
case "setCursorScreenPos":
    currentWindow().cursorX = argF(args,0,0) - currentWindow().x + currentWindow().scrollX;
    currentWindow().cursorY = argF(args,1,0) - currentWindow().y + currentWindow().scrollY;
    return null;
```

`setCursorScreenPos` currently omits `+ scrollY` on the Y axis, so any cursor placement inside a scrolled window is wrong. Apply `- w.scrollX` anywhere `- w.scrollY` is applied (`itemSize`, `text`, all widget draw positions, menus, tables, tabs, popups). In `end()` compute and clamp both:

```java
w.scrollMaxX = Math.max(0, w.maxContentX - w.contentW);
w.scrollX = Math.max(0, Math.min(w.scrollX, w.scrollMaxX));
```

Also fix the auto-resize branch in `end()` (`w.h - w.contentY - w.contentY` should use the same content formula as `begin`).

---

### 5. Text layout ignores the active/pushed font size

Observed:

```text
ImGui.pushFont(ImFont,F)V
ImGui.getFontSize()I
ImGui.getTextLineHeight()F
ImGui.getTextLineHeightWithSpacing()F
ImGui.getFrameHeight()F
ImGui.pushFont(icons, icons.getLegacySize())   // Axiom ToolsWindow
```

`text(...)` draws via the 4-arg `DrawList.addText(x,y,color,text)`, which hard-codes 16:

```java
void addText(float x, float y, int color, String text) {
    addText(x, y, color, text, 16);        // should use active font size
}
```

`text`, `textColored`, `textWrapped`, `button`, `smallButton`, `menuItem`, `collapsingHeader`, `separatorText`, `beginCombo`, `sliderFloat`, `checkbox`, etc. measure with `this.style.fontSize`. `pushFont(font,size)` sets `atlas.current` but ignores the size argument. Consequence: Axiom's `pushFont(icons, getLegacySize())` renders icon glyphs at 16 px instead of the icon font's 2x size; `getTextLineHeight`/`getFrameHeight` disagree with the glyphs actually drawn.

**Exact changes**:

```java
float currentFontSize() {
    return this.atlas.current != null && this.atlas.current.size > 0
        ? this.atlas.current.size
        : this.style.fontSize;
}
```

- Use `currentFontSize()` in `text`, `textWrapped`, `textColored`, `separatorText`, `button`, `smallButton`, `menuItem`, `collapsingHeader`, `beginCombo`, `checkbox`, `sliderFloat`, table/tab labels, `calcTextSize`, `getTextLineHeight`, `getTextLineHeightWithSpacing`, and `getFrameHeight`.
- `DrawList.addText(float x,float y,int color,String text)` must do:

```java
FontAtlas atlas = FontAtlas.ACTIVE.get();
float size = atlas != null && atlas.current != null ? atlas.current.size : 16f;
addText(x, y, color, text, size);
```

- `pushFont(ImFont font, float size)` should store the previous font **and** previous active size, then use `size > 0 ? size : font.size` as the active size. `popFont` restores both. `getFontSize()` must return the active size, not merely `FontData.size`.
- `FontAtlas.measure(text,size)` and `drawText(...,size)` must use the same size for advance and rasterisation; currently `drawText` uses `size/8` for the bitmap fallback and the true glyph size for TTF, which is fine only if the caller passes the same size.

---

### 6. `ImGuiStyle` instances are not independent; `styleColorsLight` is dark

Observed:

```text
ImGuiStyle.create()J
ImGui.styleColorsDark(ImGuiStyle)V
ImGui.styleColorsLight(ImGuiStyle)V
ImGuiStyle.get.../set...  (many)
```

Axiom `BuiltinStyles` does:

```java
ImGuiStyle dark = new ImGuiStyle();
ImGui.styleColorsDark(dark);
ImGuiStyle light = new ImGuiStyle();
ImGui.styleColorsLight(light);
```

`ImGuiStyle.create()` has no handler, so the constructor's `ptr` is `0`. Even if it were non-zero, `UiContext.style(...)` ignores `self` and always mutates the single global `this.style`. Both style objects alias one style; `styleColorsLight(style)` calls `colorsLight()`, which currently is:

```java
void colorsLight() { colorsDark(); }
```

**Exact changes**:

1. `UiContext`: `final Map<Long, Style> styles = new HashMap<>();`
2. In `style(...)`, resolve the target:

```java
Style target;
if (self == null || self == this.styleObject) {
    target = this.style;
} else {
    target = this.styles.computeIfAbsent(ptr(self), k -> new Style());
}
if (name.equals("create")) {
    long h = newHandle();
    this.styles.put(h, new Style());
    return h;
}
```

Use `target` for `getColors`, `setColors`, `getColor`, `setColor`, the dynamic `get*`/`set*` block, and `setVarById`. Register the global wrapper handle (`2L`) in `styles` so `getStyle()` and a `new ImGuiStyle(2)` both map to the same object.

3. In `imgui(...)`:

```java
case "styleColorsDark" -> {
    Style target = styleFor(arg(args,0));
    target.colorsDark();
    return null;
}
case "styleColorsLight" -> {
    Style target = styleFor(arg(args,0));
    target.colorsLight();
    return null;
}
```

4. Replace `colorsLight()` with the real ImGui light palette (a `set(index,...)` sequence for Text, TextDisabled, WindowBg, ChildBg, PopupBg, Border, FrameBg, TitleBg, ScrollbarBg, CheckMark, SliderGrab, Button, Header, Separator, ResizeGrip, Tab, etc.). At minimum do not delegate to `colorsDark()`.

5. Add the missing `scrollbarRounding` field and `ScrollbarRounding` cases in `Style.var`/`setVar`; currently `getScrollbarRounding` returns 0 and `setScrollbarRounding` is silently dropped.

---

### 7. `ImGui.colorConvertFloat4ToU32(ImVec4)` returns black

Observed:

```text
imgui.moulberry92.ImGui.colorConvertFloat4ToU32(Limgui/moulberry92/ImVec4;)I
```

Current handler:

```java
case "colorConvertFloat4ToU32":
    return colorConvertFloat4(argF(args,0,0), argF(args,1,0), argF(args,2,0), argF(args,3,1));
```

`argF` on an `ImVec4` returns the fallback, so the result is `IM_COL32(0,0,0,255)` (or transparent) instead of the converted color.

**Exact change**:

```java
case "colorConvertFloat4ToU32" -> {
    Object c = arg(args, 0);
    if (c != null && c.getClass().getSimpleName().equals("ImVec4")) {
        return colorConvertFloat4(f(Reflect.get(c,"x")), f(Reflect.get(c,"y")),
                                  f(Reflect.get(c,"z")), f(Reflect.get(c,"w")));
    }
    return colorConvertFloat4(argF(args,0,0), argF(args,1,0),
                              argF(args,2,0), argF(args,3,1));
}
```

Semantics: clamp each channel to `0..1`, multiply by 255 with rounding, pack `R | G<<8 | B<<16 | A<<24` (ImGui's `IM_COL32` layout). `colorConvertU32ToFloat4(int)` is already correct.

---

### 8. Input overload flags and disabled/drag-drop semantics

Observed:

```text
ImGui.isItemClicked(I)Z / isItemClicked()Z
ImGui.isItemHovered(I)Z / isItemHovered()Z
ImGui.isKeyPressed(I)Z / (IZ)Z
ImGui.isMouseClicked(I)Z / (IZ)Z
ImGui.beginDragDropSource()Z / beginDragDropTarget()Z
ImGui.beginDisabled()V
```

Current gaps:

- `isItemClicked(I)` ignores the button and returns `lastItemClicked` (button 0).
- `isKeyPressed(I,boolean repeat)` and `isMouseClicked(I,boolean repeat)` ignore `repeat`.
- `isItemHovered(I)` ignores flags.
- `beginDisabled()` only multiplies alpha; it does **not** block clicks/hover, so disabled Axiom/Flashback controls remain interactive. `endDisabled()` unconditionally sets alpha to 1 (breaks nesting).
- `beginDragDropSource`/`beginDragDropTarget` always return `false`, so Axiom's palette/view drag-and-drop and Flashback timeline drags are inert.
- `isRectVisible(FF)` always returns true (culling only, safe but not correct).

**Exact changes**:

```java
// Track which button triggered the last item click.
case "isItemClicked" -> {
    if (args.length == 0) return this.lastItemClicked;
    return this.lastItemClicked && argI(args,0,0) == this.lastItemClickedButton;
}
```

Set `lastItemClickedButton = pressedButton` in `button`, `selectable`, `invisibleButton`, `menuItem`, `tabItemButton`, etc.

```java
// repeat semantics
case "isKeyPressed" -> {
    int key = argI(args,0,0);
    if (!argB(args,1,false)) return this.io.keysPressed.contains(key);
    return this.io.isKeyRepeated(key);       // add press timestamp + repeat delay/rate
}
case "isMouseClicked" -> {
    int btn = argI(args,0,0);
    if (!argB(args,1,false)) return this.io.mousePressed[btn];
    return this.io.isMouseRepeated(btn);
}
```

```java
// disabled stack
void beginDisabled(boolean disabled) {
    this.disabledStack.add(this.disabled);
    this.globalAlpha *= disabled ? 0.55f : 1f;
    this.disabled = this.disabled || disabled;
}
void endDisabled() {
    this.disabled = this.disabledStack.isEmpty() ? false : this.disabledStack.remove(this.disabledStack.size()-1);
    this.globalAlpha = this.disabled ? 0.55f : 1f;
}
boolean hit(...) { return !this.disabled && ...; }
```

Implement a minimal payload store for drag-drop:

```java
String dragDropSourceId;
Object dragDropPayload;
String dragDropTargetId;
// beginDragDropSource: if lastItemActive and mouseDragging(0) -> dragDropSourceId=lastItemId; return true
// setDragDropPayload(type,data): dragDropPayload=data; return true
// beginDragDropTarget: if dragDropSourceId != null && hit(lastItemRect) -> dragDropTargetId=lastItemId; return true
// acceptDragDropPayload(type): if ids match -> return dragDropPayload
// endDragDropSource/Target: clear
```

`isRectVisible(FF)` should use `getCursorScreenPos()` and the supplied size intersected with the current window content rect (or the current draw-list clip rect).

---

### 9. Dock-node API is a stub; `dockBuilderGetCentralNode` reads the wrong argument

Observed:

```text
imgui.moulberry92.internal.ImGui.dockBuilderGetCentralNode(I)LImGuiDockNode;
imgui.moulberry92.internal.ImGuiDockNode.addLocalFlags(I)V
ImGui.dockSpaceOverViewport(ILImGuiViewport;I)I
ImGui.setNextWindowDockID(I)V
```

Current:

```java
case "dockBuilderGetCentralNode": return dockNode(argI(args, 1, 0)); // arg 1 does not exist
...
Object dockNode(int id) {
    long handle = newHandle();
    this.handles.put(handle, new Object());       // no id/flags/rect
    return wrapper("internal.ImGuiDockNode", handle, new Object());
}
```

`dispatch` has `case "ImGuiDockNode" -> return null;`, so `addLocalFlags(4096)` (`NoTabBar`) and every other dock-node accessor are dropped. `dockSpaceOverViewport` always returns `1`; `setNextWindowDockID` ignores condition flags. Axiom calls `dockBuilderGetCentralNode(dockSpaceId).addLocalFlags(4096)` to suppress the central node tab bar.

**Exact changes**:

1. Add `case "ImGuiDockNode" -> return dockNodeApi(name, desc, self, args);`.
2. Add a state object and key it by the returned handle:

```java
static final class DockNodeState {
    int id;
    int localFlags, sharedFlags;
    float x, y, w, h;
    boolean central;
}
final Map<Long, DockNodeState> dockNodeStates = new HashMap<>();

Object dockNode(int id) {
    long handle = newHandle();
    DockNodeState s = new DockNodeState();
    s.id = id;
    this.dockNodeStates.put(handle, s);
    this.handles.put(handle, s);
    return wrapper("internal.ImGuiDockNode", handle, s);
}
```

3. `dockBuilderGetCentralNode` must use `args[0]`:

```java
case "dockBuilderGetCentralNode": return dockNode(argI(args,0,0));
```

4. Implement `dockNodeApi`:

```java
case "addLocalFlags":    s.localFlags |= argI(args,0,0); return null;
case "removeLocalFlags": s.localFlags &= ~argI(args,0,0); return null;
case "hasLocalFlags":    return (s.localFlags & argI(args,0,0)) != 0;
case "getLocalFlags":    return s.localFlags;
case "setLocalFlags":    s.localFlags = argI(args,0,0); return null;
// same for SharedFlags/LocalFlagsInWindows
case "isCentralNode":    return s.central;
case "getID":            return s.id;
case "getPos"/"getSize"/"rect": return the stored rectangle / vec2
default: return null;
```

5. `dockSpaceOverViewport` should return the stable dockspace id actually used by `begin`/`setNextWindowDockID` (currently `1`), and should register the viewport work area. `setNextWindowDockID(int, cond)` should store `cond` and apply it when creating the window; `getWindowDockID`/`isWindowDocked` should use `dockAssigned || dockId != 0`.

This is lower visual priority than gaps 1-8 because the custom dock layout does not implement drag docking, but it is a required API surface and the current argument bug is a direct contract violation.

---

### 10. `TextEditor` lifecycle and rendering are missing

Observed:

```text
TextEditor.create()J
TextEditorLanguage.Lua()LTextEditorLanguage;
TextEditor.setAutoIndentEnabled(Z)V
TextEditor.setLanguage(TextEditorLanguage)V
TextEditor.setShowWhitespacesEnabled(Z)V
TextEditor.setTabSize(I)V
TextEditor.setText(String)V
```

Current `textEditor(...)` has no `create` case, so `create()` returns `0`; the constructor leaves `ptr == 0` and every `TextEditor` instance writes into `textEditors.computeIfAbsent(0, ...)`, i.e. one shared document. `TextEditorLanguage.Lua()` has no dispatch case at all, `setLanguage` is a no-op, and the settings setters (`autoIndent`, `showWhitespaces`) are no-ops whose getters return hard-coded values.

Axiom `ScriptBrushTool` additionally calls `TextEditor.render(String)`, `getText()`, `getLineCount()`, `addMarker(...)`, `clearMarkers()` (the render/marker calls were not in this capture because the script editor was closed, but they are part of the same API).

**Exact changes**:

```java
case "create" -> {
    long h = newHandle();
    this.textEditors.put(h, new TextEditorData());
    return h;
}
```

Add a minimal renderer and state to `TextEditorData`:

```java
static final class TextEditorData {
    String text = "";
    int tabSize = 4;
    boolean readOnly;
    boolean autoIndent = true;
    boolean showWhitespaces;
    int language;                 // 0 = plain, 1 = Lua
    final List<int[]> markers = new ArrayList<>();
    float scrollX, scrollY;
    int cursorLine, cursorColumn;
}
```

```java
case "render" -> {
    String title = argS(args,0);
    float width  = args.length > 1 && arg(args,1) instanceof Number ? argF(args,1,0) : 0;
    float height = args.length > 2 && arg(args,2) instanceof Number ? argF(args,2,0) : 0;
    renderTextEditor(title, width, height, data);
    return null;
}
case "getLineCount" -> { return data.text.isEmpty() ? 1 : data.text.split("\n",-1).length; }
case "addMarker" -> { data.markers.add(new int[]{argI(args,0,0), argI(args,1,0), argI(args,2,0)}); return null; }
case "clearMarkers" -> { data.markers.clear(); return null; }
```

`renderTextEditor` should at minimum `beginChild(title, width, height, 0, true)`, draw each line with `textUnformatted` (using current font), show line numbers/whitespace based on the stored booleans, and, when hovered/focused, consume `io.chars` plus Backspace/Enter/Tab/arrow keys to maintain `data.text` and the cursor. `readOnly` must suppress mutation. Implement the `TextEditorLanguage` class as a dispatch case returning a wrapper/handle (so `Lua()` is non-null) and store the language id in `setLanguage`; syntax coloring can be a later enhancement.

---

## Category audits (requested areas)

### Begin / End / BeginChild / EndChild / content region / scroll

- `begin` and `end` are meaningful: window stack, pos/size, docking tab switching, clip rects, scrollbar, collapsed window push/pop. `end()` always pops even when `begin()` returned `false`; that matches Dear ImGui's "always call End" contract.
- `beginChild`/`endChild` work structurally (`endChild` delegates to `end`), but sizing and the `(String,FF,Z,I)` boolean/window-flags mapping are wrong (gap 4).
- `getWindowContentRegionMaxY`, `getContentRegionAvailY`, and `contentH` are wrong by roughly `titleHeight - paddingY` (gap 4).
- `setCursorScreenPos` ignores `scrollY`; `setScrollX/getScrollX` are no-op/0; `getScrollMaxY` uses `contentHeight - h` rather than the computed `scrollMaxY` (gap 4).
- Minor: `begin` resets `contentHeight` each frame, but `getScrollY` returns the previous frame's clamp until `end`; this matches typical immediate-mode use at the top of a window.

### ImGuiIO input

All 35 observed IO methods have handlers. No critical gap, but these are semantically thin:

- `isKeyPressed(int, boolean repeat)` / `isMouseClicked(int, boolean repeat)` ignore `repeat`.
- `addMouseSourceEvent(int)` and `setConfigMacOSXBehaviors(boolean)` are no-ops.
- `getMouseDrawCursor()` always `false`; `setMouseDrawCursor(boolean)` no-op.
- `setDeltaTime(float)` is overwritten by `newFrame()`'s wall-clock delta.
- `hasConfigFlags(ViewportsEnable)` intentionally returns `false` and `addConfigFlags` masks the viewports bit; this is consistent with the single-viewport implementation.
- `getWantCaptureMouse/Keyboard/TextInput` are recomputed only in `newFrame`/`addMouse*`/`inputText`; widgets that need to override capture must call `setNextFrameWantCapture*`, which is handled.

### ImGuiStyle

- `ImGuiStyle.create()` is MISSING; `style(...)` ignores `self`; `styleColorsLight` is an alias for dark. See gap 6.
- Most individual getters/setters are implemented via `Style.var`/`setVar`. Notable missing property: `ScrollbarRounding` (get returns 0, set is dropped).
- `getColors`/`setColors`/`setColor` are implemented for the global style only.
- `pushStyleVar(I,FF)` and `pushStyleVar(I,F)` both work; `popStyleVar` snapshots/restores the whole `Style`, so nesting is correct.

### ImDrawList / ImDrawData

- Every observed `ImDrawData` method is handled and matches the imgui-java renderer contract: buffer sizes are element counts (not bytes), `sizeOfImDrawVert=20`, `sizeOfImDrawIdx=2`, `Cmd.VtxOffset`/`IdxOffset` are within-list absolute offsets, and `Axiom CustomImGuiImplB3D` adds the per-list accumulated offsets itself.
- `getDisplayPos`/`DisplayPosX/Y` are hard-coded to `0`; correct for the main viewport, wrong if multi-viewport is ever enabled.
- Every observed `ImDrawList` method is handled. Partial cases: `addRectFilled(FFFFII)` ignores rounding and corner flags; `addRect(FFFFI)` ignores rounding; `addImage` restores the atlas texture by creating a possible trailing empty command; `pushClipRect` does not intersect with the existing clip rect.
- Path/polyline helpers (`addPolyline`, `addConvexPolyFilled`, `path*`, `channels*`) return no-op. They are not in this capture, but Axiom/Flashback gizmos may use them later.
- Draw-list text uses `FontAtlas.ACTIVE` and the current font; once gaps 3/5 are fixed, icon/CJK text will render correctly. `addText(FFILjava/lang/String;)V` is OK.

### ImGuiViewport

All observed methods are handled: `getPos/Size/WorkPos/WorkSize`, `getCenter`, `getID` (stable `1`), `getFlags/setFlags`, `getDpiScale` (1.0), `getFramebufferScale` (1,1), and `setWorkSize`. `setPos`/`setSize` exist as no-ops but were not called in this capture. Multi-viewport is deliberately disabled (config flag masked), so `getMainViewport()` being the only viewport is acceptable.

### ImFont / ImFontAtlas / ImFontConfig

- `ImFont.getLegacySize()` is correct (returns the owning `FontData.size`).
- `ImFontAtlas.addFontFromMemoryTTF`, `build`, `clear`, `clearTexData`, `getGlyphRangesDefault`, `getTexDataAsRGBA32`, `setTexID` are all dispatched but have the font-pipeline defects in gap 3.
- `ImFontConfig` is entirely unported (gap 3), including `create()` and the `setName`/`setMergeMode`/`setGlyphOffset`/`setOversample*` calls both mods make.
- `addFont` changes the default font to the last added font; merged CJK/icon fonts are not used as fallbacks; glyph ranges from the config/trailing `short[]` are ignored.
- `build()` returns `false`; `clearTexData()` retains pixels; `setTexID` truncates to `int`.

### TextEditor

See gap 10. In addition to the observed configuration calls, Axiom `ScriptBrushTool` calls `render(String)`, `getText()`, `getLineCount()`, `addMarker(IIILString)`, and `clearMarkers()`. Until `create()` returns a unique handle and `render` exists, the Lua script editor cannot survive multiple instances and will not draw.

### Dock

`dockSpaceOverViewport`, `setNextWindowDockID`, `dockBuilderGetCentralNode`, and `addLocalFlags` are the only observed dock calls. `dockSpaceOverViewport` returns a constant `1`; `dockBuilderGetCentralNode` reads a non-existent second argument and returns an opaque object; `ImGuiDockNode` is not dispatched. The custom dock layout itself (`layoutDockNode`, ini parsing, splitter drag) works independently, but the public dock-node API is effectively a stub. See gap 9.

---

## Full per-call classification

Each row corresponds to one line of `run/calls.txt` (both packages, all overloads). Status follows the legend above.

| # | Package | Class | Method | Descriptor | Status | Finding |
|---:|---|---|---|---|---|---|
| 1 | moulberry90 | ImDrawData | `getCmdListCmdBufferClipRect` | `(II)Limgui/moulberry90/ImVec4;` | OK | returns ImVec4 (list,cmd); renderer contract satisfied |
| 2 | moulberry90 | ImDrawData | `getCmdListCmdBufferElemCount` | `(II)I` | OK | command elemCount |
| 3 | moulberry90 | ImDrawData | `getCmdListCmdBufferIdxOffset` | `(II)I` | OK | absolute index offset within list |
| 4 | moulberry90 | ImDrawData | `getCmdListCmdBufferSize` | `(I)I` | OK | command count |
| 5 | moulberry90 | ImDrawData | `getCmdListCmdBufferTextureId` | `(II)J` | OK | long texture id |
| 6 | moulberry90 | ImDrawData | `getCmdListCmdBufferVtxOffset` | `(II)I` | OK | absolute vertex offset within list |
| 7 | moulberry90 | ImDrawData | `getCmdListIdxBufferData` | `(I)Ljava/nio/ByteBuffer;` | OK | native-order ByteBuffer |
| 8 | moulberry90 | ImDrawData | `getCmdListIdxBufferSize` | `(I)I` | OK | index count |
| 9 | moulberry90 | ImDrawData | `getCmdListsCount` | `()I` | OK | list count |
| 10 | moulberry90 | ImDrawData | `getCmdListVtxBufferData` | `(I)Ljava/nio/ByteBuffer;` | OK | native-order ByteBuffer |
| 11 | moulberry90 | ImDrawData | `getCmdListVtxBufferSize` | `(I)I` | OK | vertex count |
| 12 | moulberry90 | ImDrawData | `getDisplayPos` | `()Limgui/moulberry90/ImVec2;` | OK | hard-coded 0,0; correct for main viewport |
| 13 | moulberry90 | ImDrawData | `getDisplayPosX` | `()F` | OK | 0 |
| 14 | moulberry90 | ImDrawData | `getDisplayPosY` | `()F` | OK | 0 |
| 15 | moulberry90 | ImDrawData | `getDisplaySizeX` | `()F` | OK | io display size |
| 16 | moulberry90 | ImDrawData | `getDisplaySizeY` | `()F` | OK | io display size |
| 17 | moulberry90 | ImDrawData | `getFramebufferScale` | `()Limgui/moulberry90/ImVec2;` | OK | io framebuffer scale |
| 18 | moulberry90 | ImDrawData | `getFramebufferScaleX` | `()F` | OK |  |
| 19 | moulberry90 | ImDrawData | `getFramebufferScaleY` | `()F` | OK |  |
| 20 | moulberry90 | ImDrawData | `getTotalIdxCount` | `()I` | OK |  |
| 21 | moulberry90 | ImDrawData | `getTotalVtxCount` | `()I` | OK |  |
| 22 | moulberry90 | ImDrawData | `sizeOfImDrawIdx` | `()I` | OK | 2 (unsigned short) |
| 23 | moulberry90 | ImDrawData | `sizeOfImDrawVert` | `()I` | OK | 20 bytes |
| 24 | moulberry90 | ImDrawList | `addLine` | `(FFFFI)V` | OK |  |
| 25 | moulberry90 | ImDrawList | `addRect` | `(FFFFI)V` | PARTIAL | rounding argument ignored; four filled bars |
| 26 | moulberry90 | ImDrawList | `addRectFilled` | `(FFFFII)V` | PARTIAL | 6-arg (rounding,flags) overload draws square; flags ignored |
| 27 | moulberry90 | ImDrawList | `addRectFilled` | `(FFFFI)V` | OK | square fill; no rounding requested |
| 28 | moulberry90 | ImDrawList | `addText` | `(FFILjava/lang/String;)V` | OK | draws through FontAtlas; uses supplied size/fallback |
| 29 | moulberry90 | ImDrawList | `addTriangleFilled` | `(FFFFFFI)V` | OK | filled triangle |
| 30 | moulberry90 | ImDrawList | `popClipRect` | `()V` | OK |  |
| 31 | moulberry90 | ImDrawList | `pushClipRect` | `(FFFF)V` | OK |  |
| 32 | moulberry90 | ImFontAtlas | `addFontFromMemoryTTF` | `([BFLimgui/moulberry90/ImFontConfig;[S)Limgui/moulberry90/ImFont;` | PARTIAL | loads bytes+size but ignores ImFontConfig (merge/offset/ranges/name) and always makes the new font current |
| 33 | moulberry90 | ImFontAtlas | `build` | `()Z` | PARTIAL | returns null=>false; no atlas validation/build (Axiom ignores result, getTexData builds lazily) |
| 34 | moulberry90 | ImFontAtlas | `clearTexData` | `()V` | NO-OP | pixel buffer retained; harmless for external GL upload |
| 35 | moulberry90 | ImFontAtlas | `clear` | `()V` | PARTIAL | clears fonts but leaves current pointing at removed font and keeps built pixels |
| 36 | moulberry90 | ImFontAtlas | `getGlyphRangesDefault` | `()[S` | OK | ASCII 0x20-0x7E |
| 37 | moulberry90 | ImFontAtlas | `getTexDataAsRGBA32` | `(Limgui/moulberry90/type/ImInt;Limgui/moulberry90/type/ImInt;)Ljava/nio/ByteBuffer;` | OK | lazy ensureAtlas, returns direct RGBA buffer and fills ImInt w/h |
| 38 | moulberry90 | ImFontAtlas | `setTexID` | `(J)V` | PARTIAL | stores via int truncation, does not update live draw lists (fixed next newFrame) |
| 39 | moulberry90 | ImFontConfig | `create` | `()J` | MISSING | no ImFontConfig dispatch: create() returns 0 -> ptr=0; constructor handle unusable |
| 40 | moulberry90 | ImFontConfig | `setGlyphOffset` | `(FF)V` | MISSING | no dispatch; glyph offset (Flashback icons) dropped |
| 41 | moulberry90 | ImFontConfig | `setMergeMode` | `(Z)V` | MISSING | no dispatch; merge flag dropped, icon/CJK fonts become standalone fonts |
| 42 | moulberry90 | ImFontConfig | `setName` | `(Ljava/lang/String;)V` | MISSING | no dispatch; name dropped |
| 43 | moulberry90 | ImFontConfig | `setOversampleH` | `(I)V` | MISSING | no dispatch; oversampling dropped |
| 44 | moulberry90 | ImFontConfig | `setOversampleV` | `(I)V` | MISSING | no dispatch; oversampling dropped |
| 45 | moulberry90 | ImGui | `beginChild` | `(Ljava/lang/String;FFZI)Z` | PARTIAL | 0 size uses parent.w/h (not content region); bool border read via argI -> 0, windowFlags arg dropped |
| 46 | moulberry90 | ImGui | `beginCombo` | `(Ljava/lang/String;Ljava/lang/String;I)Z` | PARTIAL | button+popup; no keyboard nav/type-ahead |
| 47 | moulberry90 | ImGui | `beginDisabled` | `()V` | PARTIAL | alpha only; does not block input; non-nested (endDisabled resets to 1) |
| 48 | moulberry90 | ImGui | `begin` | `(Ljava/lang/String;I)Z` | OK | window stack, pos/size, dock, title, clip; collapsed pushes window for matching End |
| 49 | moulberry90 | ImGui | `begin` | `(Ljava/lang/String;)Z` | OK | window stack, pos/size, dock, title, clip; collapsed pushes window for matching End |
| 50 | moulberry90 | ImGui | `beginMainMenuBar` | `()Z` | OK | full-width menu window |
| 51 | moulberry90 | ImGui | `beginMenu` | `(Ljava/lang/String;)Z` | PARTIAL | opens popup on mouse press; no hover-to-switch / keyboard nav |
| 52 | moulberry90 | ImGui | `beginPopup` | `(Ljava/lang/String;I)Z` | PARTIAL | custom popup map; one popup id, no modal dimming/stacking |
| 53 | moulberry90 | ImGui | `beginPopupModal` | `(Ljava/lang/String;Limgui/moulberry90/type/ImBoolean;I)Z` | PARTIAL | delegates to beginPopup; no dim background/focus trap |
| 54 | moulberry90 | ImGui | `button` | `(Ljava/lang/String;)Z` | OK |  |
| 55 | moulberry90 | ImGui | `calcTextSize` | `(Limgui/moulberry90/ImVec2;Ljava/lang/String;)V` | PARTIAL | out-param (ImVec2,String) overload not implemented: writes nothing and measures toString of ImVec2 |
| 56 | moulberry90 | ImGui | `checkbox` | `(Ljava/lang/String;Z)Z` | OK | bool-by-value semantics match native overload |
| 57 | moulberry90 | ImGui | `createContext` | `()Limgui/moulberry90/internal/ImGuiContext;` | OK | shared context object |
| 58 | moulberry90 | ImGui | `dockSpaceOverViewport` | `(ILimgui/moulberry90/ImGuiViewport;I)I` | PARTIAL | always returns 1; no dockspace node registration |
| 59 | moulberry90 | ImGui | `dummy` | `(FF)V` | OK |  |
| 60 | moulberry90 | ImGui | `endChild` | `()V` | OK | delegates to end() |
| 61 | moulberry90 | ImGui | `endDisabled` | `()V` | PARTIAL | always alpha=1 (breaks nested disabled) |
| 62 | moulberry90 | ImGui | `endMainMenuBar` | `()V` | OK |  |
| 63 | moulberry90 | ImGui | `end` | `()V` | OK | pops window, clamps scroll, draws scrollbar |
| 64 | moulberry90 | ImGui | `getColorU32` | `(I)I` | OK | ImGuiCol index 0..63 and packed color; packed value <64 is misread as index |
| 65 | moulberry90 | ImGui | `getCurrentContext` | `()Limgui/moulberry90/internal/ImGuiContext;` | OK |  |
| 66 | moulberry90 | ImGui | `getCursorPosX` | `()F` | OK |  |
| 67 | moulberry90 | ImGui | `getCursorPosY` | `()F` | OK |  |
| 68 | moulberry90 | ImGui | `getCursorScreenPosX` | `()F` | OK | scrollX always 0 |
| 69 | moulberry90 | ImGui | `getCursorScreenPosY` | `()F` | OK | applies scrollY |
| 70 | moulberry90 | ImGui | `getDrawData` | `()Limgui/moulberry90/ImDrawData;` | OK |  |
| 71 | moulberry90 | ImGui | `getFontSize` | `()I` | PARTIAL | returns current FontData.size, but every addFont makes the newest font current -> icon font size after load |
| 72 | moulberry90 | ImGui | `getIO` | `()Limgui/moulberry90/ImGuiIO;` | OK |  |
| 73 | moulberry90 | ImGui | `getMainViewport` | `()Limgui/moulberry90/ImGuiViewport;` | OK |  |
| 74 | moulberry90 | ImGui | `getMouseCursor` | `()I` | NO-OP | always 0 (Arrow) |
| 75 | moulberry90 | ImGui | `getScrollY` | `()F` | OK | previous-frame clamped value |
| 76 | moulberry90 | ImGui | `getStyle` | `()Limgui/moulberry90/ImGuiStyle;` | OK | global style |
| 77 | moulberry90 | ImGui | `getTextLineHeight` | `()F` | PARTIAL | style.fontSize, not current font |
| 78 | moulberry90 | ImGui | `getTextLineHeightWithSpacing` | `()F` | PARTIAL | style.fontSize, not current font |
| 79 | moulberry90 | ImGui | `getWindowContentRegionMaxX` | `()F` | OK | w - contentX (= contentX+contentW) |
| 80 | moulberry90 | ImGui | `getWindowContentRegionMaxY` | `()F` | PARTIAL | h - contentY; should be contentY+contentH (= h - paddingY), short by titleHeight |
| 81 | moulberry90 | ImGui | `getWindowContentRegionMinX` | `()F` | OK | contentX |
| 82 | moulberry90 | ImGui | `getWindowContentRegionMinY` | `()F` | OK | titleHeight+paddingY |
| 83 | moulberry90 | ImGui | `getWindowDrawList` | `()Limgui/moulberry90/ImDrawList;` | OK | per-window list |
| 84 | moulberry90 | ImGui | `getWindowPosX` | `()F` | OK |  |
| 85 | moulberry90 | ImGui | `getWindowPosY` | `()F` | OK |  |
| 86 | moulberry90 | ImGui | `getWindowSizeX` | `()F` | OK |  |
| 87 | moulberry90 | ImGui | `init` | `()V` | NO-OP | binding already initialised by mixin static init |
| 88 | moulberry90 | ImGuiIO | `addBackendFlags` | `(I)V` | OK |  |
| 89 | moulberry90 | ImGuiIO | `addConfigFlags` | `(I)V` | OK | ViewportsEnable masked out deliberately |
| 90 | moulberry90 | ImGuiIO | `addFocusEvent` | `(Z)V` | OK | sets focused flag |
| 91 | moulberry90 | ImGuiIO | `addMouseButtonEvent` | `(IZ)V` | OK | mouseDown + next pressed/released + drag start |
| 92 | moulberry90 | ImGuiIO | `addMousePosEvent` | `(FF)V` | OK | mouse position + capture update |
| 93 | moulberry90 | ImGuiIO | `addMouseSourceEvent` | `(I)V` | NO-OP | source (mouse/touch/pen) ignored; harmless here |
| 94 | moulberry90 | ImGuiIO | `getFonts` | `()Limgui/moulberry90/ImFontAtlas;` | OK | atlas wrapper |
| 95 | moulberry90 | ImGuiIO | `getKeyAlt` | `()Z` | OK |  |
| 96 | moulberry90 | ImGuiIO | `getKeyCtrl` | `()Z` | OK |  |
| 97 | moulberry90 | ImGuiIO | `getKeyShift` | `()Z` | OK |  |
| 98 | moulberry90 | ImGuiIO | `getKeySuper` | `()Z` | OK |  |
| 99 | moulberry90 | ImGuiIO | `getMouseDrawCursor` | `()Z` | NO-OP | always false |
| 100 | moulberry90 | ImGuiIO | `getMousePosX` | `()F` | OK |  |
| 101 | moulberry90 | ImGuiIO | `getMousePosY` | `()F` | OK |  |
| 102 | moulberry90 | ImGuiIO | `getMouseWheel` | `()F` | OK |  |
| 103 | moulberry90 | ImGuiIO | `getWantCaptureMouse` | `()Z` | OK | computed in updateMouseCapture |
| 104 | moulberry90 | ImGuiIO | `getWantTextInput` | `()Z` | OK | set by inputText |
| 105 | moulberry90 | ImGuiIO | `hasConfigFlags` | `(I)Z` | OK |  |
| 106 | moulberry90 | ImGuiIO | `removeConfigFlags` | `(I)V` | OK |  |
| 107 | moulberry90 | ImGuiIO | `setBackendPlatformName` | `(Ljava/lang/String;)V` | OK |  |
| 108 | moulberry90 | ImGuiIO | `setConfigMacOSXBehaviors` | `(Z)V` | NO-OP | shortcut behavior flag ignored |
| 109 | moulberry90 | ImGuiIO | `setDeltaTime` | `(F)V` | OK | stored, overwritten by newFrame wall clock |
| 110 | moulberry90 | ImGuiIO | `setDisplayFramebufferScale` | `(FF)V` | OK |  |
| 111 | moulberry90 | ImGuiIO | `setDisplaySize` | `(FF)V` | OK | also updates viewport/work size |
| 112 | moulberry90 | ImGuiIO | `setGetClipboardTextFn` | `(Limgui/moulberry90/callback/ImStrSupplier;)V` | OK | supplier.get() |
| 113 | moulberry90 | ImGuiIO | `setIniFilename` | `(Ljava/lang/String;)V` | OK | used by loadIni, no save |
| 114 | moulberry90 | ImGuiIO | `setKeyAlt` | `(Z)V` | OK |  |
| 115 | moulberry90 | ImGuiIO | `setKeyCtrl` | `(Z)V` | OK |  |
| 116 | moulberry90 | ImGuiIO | `setKeyShift` | `(Z)V` | OK |  |
| 117 | moulberry90 | ImGuiIO | `setKeySuper` | `(Z)V` | OK |  |
| 118 | moulberry90 | ImGuiIO | `setSetClipboardTextFn` | `(Limgui/moulberry90/callback/ImStrConsumer;)V` | OK | consumer.accept() |
| 119 | moulberry90 | ImGui | `isAnyMouseDown` | `()Z` | OK |  |
| 120 | moulberry90 | ImGui | `isKeyPressed` | `(I)Z` | OK | edge-triggered; no repeat requested |
| 121 | moulberry90 | ImGui | `isKeyPressed` | `(IZ)Z` | PARTIAL | repeat flag ignored; only transition frame |
| 122 | moulberry90 | ImGui | `isMouseClicked` | `(I)Z` | OK | edge-triggered; no repeat requested |
| 123 | moulberry90 | ImGui | `isMouseDragging` | `(I)Z` | OK | distance threshold |
| 124 | moulberry90 | ImGui | `isPopupOpen` | `(Ljava/lang/String;I)Z` | OK |  |
| 125 | moulberry90 | ImGui | `isPopupOpen` | `(Ljava/lang/String;)Z` | OK |  |
| 126 | moulberry90 | ImGui | `isRectVisible` | `(FF)Z` | NO-OP | always true; safe but culling ineffective |
| 127 | moulberry90 | ImGui | `isWindowFocused` | `()Z` | PARTIAL | compares current window with last LinkedHashMap entry, not real focus |
| 128 | moulberry90 | ImGui | `isWindowHovered` | `()Z` | PARTIAL | flags ignored |
| 129 | moulberry90 | ImGui | `menuItem` | `(Ljava/lang/String;)Z` | OK |  |
| 130 | moulberry90 | ImGui | `newFrame` | `()V` | OK | io delta, input latch, wheel scroll, capture |
| 131 | moulberry90 | ImGui | `popStyleVar` | `()V` | OK | copies saved Style |
| 132 | moulberry90 | ImGui | `popTextWrapPos` | `()V` | OK |  |
| 133 | moulberry90 | ImGui | `pushStyleVar` | `(IFF)V` | OK |  |
| 134 | moulberry90 | ImGui | `pushTextWrapPos` | `(F)V` | OK |  |
| 135 | moulberry90 | ImGui | `render` | `()V` | OK | builds cmd lists/buffers |
| 136 | moulberry90 | ImGui | `sameLine` | `()V` | PARTIAL | offset interpreted as gap from lastItemRight rather than offset-from-start-x |
| 137 | moulberry90 | ImGui | `separator` | `()V` | OK |  |
| 138 | moulberry90 | ImGui | `setAssertCallback` | `(Limgui/moulberry90/assertion/ImAssertCallback;)V` | NO-OP | callback ignored (default assertions disabled) |
| 139 | moulberry90 | ImGui | `setCurrentContext` | `(Limgui/moulberry90/internal/ImGuiContext;)V` | NO-OP | one context per moulberryXX package |
| 140 | moulberry90 | ImGui | `setCursorPosX` | `(F)V` | OK |  |
| 141 | moulberry90 | ImGui | `setCursorPosY` | `(F)V` | OK |  |
| 142 | moulberry90 | ImGui | `setCursorScreenPos` | `(FF)V` | PARTIAL | Y ignores scrollY (should add scrollY) |
| 143 | moulberry90 | ImGui | `setItemTooltip` | `(Ljava/lang/String;)V` | OK | immediate tooltip |
| 144 | moulberry90 | ImGui | `setNextFrameWantCaptureMouse` | `(Z)V` | OK |  |
| 145 | moulberry90 | ImGui | `setNextItemWidth` | `(F)V` | OK |  |
| 146 | moulberry90 | ImGui | `setNextWindowBgAlpha` | `(F)V` | OK |  |
| 147 | moulberry90 | ImGui | `setNextWindowDockID` | `(I)V` | PARTIAL | condition flags ignored |
| 148 | moulberry90 | ImGui | `setNextWindowPos` | `(FFIFF)V` | OK | float and ImVec2/pivot forms |
| 149 | moulberry90 | ImGui | `setNextWindowSize` | `(FF)V` | OK |  |
| 150 | moulberry90 | ImGui | `setWindowFocus` | `()V` | NO-OP | does not change focus |
| 151 | moulberry90 | ImGui | `smallButton` | `(Ljava/lang/String;)Z` | OK |  |
| 152 | moulberry90 | ImGui | `styleColorsDark` | `(Limgui/moulberry90/ImGuiStyle;)V` | PARTIAL | argument style ignored; always resets global style |
| 153 | moulberry90 | ImGuiStyle | `getIndentSpacing` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 154 | moulberry90 | ImGuiStyle | `getItemSpacingX` | `()F` | PARTIAL | dynamic ItemSpacing; handler always uses global Style, self/ptr ignored |
| 155 | moulberry90 | ImGuiStyle | `getItemSpacingY` | `()F` | PARTIAL | dynamic ItemSpacing; handler always uses global Style, self/ptr ignored |
| 156 | moulberry90 | ImGuiStyle | `setColor` | `(II)V` | PARTIAL | accepts packed int or ImVec4 (global style only); handler always uses global Style, self/ptr ignored |
| 157 | moulberry90 | ImGui | `textColored` | `(ILjava/lang/String;)V` | PARTIAL | (int,String) overload draws empty string with nonsense color |
| 158 | moulberry90 | ImGui | `textUnformatted` | `(Ljava/lang/String;)V` | OK |  |
| 159 | moulberry90 | ImGuiViewport | `getCenter` | `()Limgui/moulberry90/ImVec2;` | OK | pos+size/2 |
| 160 | moulberry90 | ImGuiViewport | `getCenterX` | `()F` | OK |  |
| 161 | moulberry90 | ImGuiViewport | `getCenterY` | `()F` | OK |  |
| 162 | moulberry90 | ImGuiViewport | `getSizeX` | `()F` | OK |  |
| 163 | moulberry90 | ImGuiViewport | `getSizeY` | `()F` | OK |  |
| 164 | moulberry90.internal | ImGui | `dockBuilderGetCentralNode` | `(I)Limgui/moulberry90/internal/ImGuiDockNode;` | PARTIAL | reads arg 1 (does not exist) instead of arg 0; returns opaque node with no state |
| 165 | moulberry90.internal | ImGuiDockNode | `addLocalFlags` | `(I)V` | MISSING | dispatch case returns null; dock node flags lost (4096=NoTabBar) |
| 166 | moulberry90.internal | ImGui | `init` | `()V` | NO-OP | binding already initialised by mixin static init |
| 167 | moulberry92.extension.texteditor | TextEditor | `create` | `()J` | MISSING | returns 0; constructor ptr=0 -> all TextEditor instances share textEditors[0] |
| 168 | moulberry92.extension.texteditor | TextEditorLanguage | `Lua` | `()Limgui/moulberry92/extension/texteditor/TextEditorLanguage;` | MISSING | no dispatch for TextEditorLanguage: static call returns null |
| 169 | moulberry92.extension.texteditor | TextEditor | `setAutoIndentEnabled` | `(Z)V` | NO-OP | value not stored; getter always true |
| 170 | moulberry92.extension.texteditor | TextEditor | `setLanguage` | `(Limgui/moulberry92/extension/texteditor/TextEditorLanguage;)V` | NO-OP | language not stored; TextEditorLanguage.Lua() also returns null |
| 171 | moulberry92.extension.texteditor | TextEditor | `setShowWhitespacesEnabled` | `(Z)V` | NO-OP | value not stored |
| 172 | moulberry92.extension.texteditor | TextEditor | `setTabSize` | `(I)V` | OK | per-ptr TextEditorData |
| 173 | moulberry92.extension.texteditor | TextEditor | `setText` | `(Ljava/lang/String;)V` | OK | per-ptr TextEditorData |
| 174 | moulberry92 | ImDrawData | `getCmdListCmdBufferClipRect` | `(II)Limgui/moulberry92/ImVec4;` | OK | returns ImVec4 (list,cmd); renderer contract satisfied |
| 175 | moulberry92 | ImDrawData | `getCmdListCmdBufferElemCount` | `(II)I` | OK | command elemCount |
| 176 | moulberry92 | ImDrawData | `getCmdListCmdBufferIdxOffset` | `(II)I` | OK | absolute index offset within list |
| 177 | moulberry92 | ImDrawData | `getCmdListCmdBufferSize` | `(I)I` | OK | command count |
| 178 | moulberry92 | ImDrawData | `getCmdListCmdBufferTextureId` | `(II)J` | OK | long texture id |
| 179 | moulberry92 | ImDrawData | `getCmdListCmdBufferVtxOffset` | `(II)I` | OK | absolute vertex offset within list |
| 180 | moulberry92 | ImDrawData | `getCmdListIdxBufferData` | `(I)Ljava/nio/ByteBuffer;` | OK | native-order ByteBuffer |
| 181 | moulberry92 | ImDrawData | `getCmdListIdxBufferSize` | `(I)I` | OK | index count |
| 182 | moulberry92 | ImDrawData | `getCmdListsCount` | `()I` | OK | list count |
| 183 | moulberry92 | ImDrawData | `getCmdListVtxBufferData` | `(I)Ljava/nio/ByteBuffer;` | OK | native-order ByteBuffer |
| 184 | moulberry92 | ImDrawData | `getCmdListVtxBufferSize` | `(I)I` | OK | vertex count |
| 185 | moulberry92 | ImDrawData | `getDisplayPos` | `()Limgui/moulberry92/ImVec2;` | OK | hard-coded 0,0; correct for main viewport |
| 186 | moulberry92 | ImDrawData | `getDisplayPosX` | `()F` | OK | 0 |
| 187 | moulberry92 | ImDrawData | `getDisplayPosY` | `()F` | OK | 0 |
| 188 | moulberry92 | ImDrawData | `getDisplaySizeX` | `()F` | OK | io display size |
| 189 | moulberry92 | ImDrawData | `getDisplaySizeY` | `()F` | OK | io display size |
| 190 | moulberry92 | ImDrawData | `getFramebufferScale` | `()Limgui/moulberry92/ImVec2;` | OK | io framebuffer scale |
| 191 | moulberry92 | ImDrawData | `getFramebufferScaleX` | `()F` | OK |  |
| 192 | moulberry92 | ImDrawData | `getFramebufferScaleY` | `()F` | OK |  |
| 193 | moulberry92 | ImDrawData | `getTotalIdxCount` | `()I` | OK |  |
| 194 | moulberry92 | ImDrawData | `getTotalVtxCount` | `()I` | OK |  |
| 195 | moulberry92 | ImDrawData | `sizeOfImDrawIdx` | `()I` | OK | 2 (unsigned short) |
| 196 | moulberry92 | ImDrawData | `sizeOfImDrawVert` | `()I` | OK | 20 bytes |
| 197 | moulberry92 | ImDrawList | `addImage` | `(JFFFFFFFF)V` | PARTIAL | draws quad and restores atlas texture; creates trailing empty command if image tex != atlas |
| 198 | moulberry92 | ImDrawList | `addLine` | `(FFFFI)V` | OK |  |
| 199 | moulberry92 | ImDrawList | `addRectFilled` | `(FFFFI)V` | OK | square fill; no rounding requested |
| 200 | moulberry92 | ImFontAtlas | `addFontFromMemoryTTF` | `([BFLimgui/moulberry92/ImFontConfig;[S)Limgui/moulberry92/ImFont;` | PARTIAL | loads bytes+size but ignores ImFontConfig (merge/offset/ranges/name) and always makes the new font current |
| 201 | moulberry92 | ImFontAtlas | `build` | `()Z` | PARTIAL | returns null=>false; no atlas validation/build (Axiom ignores result, getTexData builds lazily) |
| 202 | moulberry92 | ImFontAtlas | `clearTexData` | `()V` | NO-OP | pixel buffer retained; harmless for external GL upload |
| 203 | moulberry92 | ImFontAtlas | `clear` | `()V` | PARTIAL | clears fonts but leaves current pointing at removed font and keeps built pixels |
| 204 | moulberry92 | ImFontAtlas | `getGlyphRangesDefault` | `()[S` | OK | ASCII 0x20-0x7E |
| 205 | moulberry92 | ImFontAtlas | `getTexDataAsRGBA32` | `(Limgui/moulberry92/type/ImInt;Limgui/moulberry92/type/ImInt;)Ljava/nio/ByteBuffer;` | OK | lazy ensureAtlas, returns direct RGBA buffer and fills ImInt w/h |
| 206 | moulberry92 | ImFontAtlas | `setTexID` | `(J)V` | PARTIAL | stores via int truncation, does not update live draw lists (fixed next newFrame) |
| 207 | moulberry92 | ImFontConfig | `create` | `()J` | MISSING | no ImFontConfig dispatch: create() returns 0 -> ptr=0; constructor handle unusable |
| 208 | moulberry92 | ImFontConfig | `setMergeMode` | `(Z)V` | MISSING | no dispatch; merge flag dropped, icon/CJK fonts become standalone fonts |
| 209 | moulberry92 | ImFontConfig | `setName` | `(Ljava/lang/String;)V` | MISSING | no dispatch; name dropped |
| 210 | moulberry92 | ImFontConfig | `setOversampleH` | `(I)V` | MISSING | no dispatch; oversampling dropped |
| 211 | moulberry92 | ImFontConfig | `setOversampleV` | `(I)V` | MISSING | no dispatch; oversampling dropped |
| 212 | moulberry92 | ImFont | `getLegacySize` | `()F` | OK | returns owning FontData.size |
| 213 | moulberry92 | ImGui | `beginChild` | `(Ljava/lang/String;)Z` | PARTIAL | 0 size uses parent.w/h (not content region); overflows by content padding |
| 214 | moulberry92 | ImGui | `beginDisabled` | `()V` | PARTIAL | alpha only; does not block input; non-nested (endDisabled resets to 1) |
| 215 | moulberry92 | ImGui | `beginDragDropSource` | `()Z` | NO-OP | always false; Axiom/Flashback drag/drop targets inert |
| 216 | moulberry92 | ImGui | `beginDragDropTarget` | `()Z` | NO-OP | always false |
| 217 | moulberry92 | ImGui | `beginGroup` | `()V` | OK | saves cursor |
| 218 | moulberry92 | ImGui | `begin` | `(Ljava/lang/String;I)Z` | OK | window stack, pos/size, dock, title, clip; collapsed pushes window for matching End |
| 219 | moulberry92 | ImGui | `begin` | `(Ljava/lang/String;Limgui/moulberry92/type/ImBoolean;I)Z` | OK | window stack, pos/size, dock, title, clip; collapsed pushes window for matching End |
| 220 | moulberry92 | ImGui | `beginMainMenuBar` | `()Z` | OK | full-width menu window |
| 221 | moulberry92 | ImGui | `beginMenuBar` | `()Z` | OK | offsets cursor |
| 222 | moulberry92 | ImGui | `beginMenu` | `(Ljava/lang/String;)Z` | PARTIAL | opens popup on mouse press; no hover-to-switch / keyboard nav |
| 223 | moulberry92 | ImGui | `beginPopup` | `(Ljava/lang/String;I)Z` | PARTIAL | custom popup map; one popup id, no modal dimming/stacking |
| 224 | moulberry92 | ImGui | `beginPopup` | `(Ljava/lang/String;)Z` | PARTIAL | custom popup map; one popup id, no modal dimming/stacking |
| 225 | moulberry92 | ImGui | `beginPopupModal` | `(Ljava/lang/String;Limgui/moulberry92/type/ImBoolean;I)Z` | PARTIAL | delegates to beginPopup; no dim background/focus trap |
| 226 | moulberry92 | ImGui | `beginTabBar` | `(Ljava/lang/String;I)Z` | PARTIAL | custom tab strip; no reorder/close/scroll |
| 227 | moulberry92 | ImGui | `beginTable` | `(Ljava/lang/String;II)Z` | PARTIAL | simple column row layout, no borders/sizing/scroll |
| 228 | moulberry92 | ImGui | `button` | `(Ljava/lang/String;FF)Z` | OK |  |
| 229 | moulberry92 | ImGui | `button` | `(Ljava/lang/String;)Z` | OK |  |
| 230 | moulberry92 | ImGui | `calcTextSize` | `(Limgui/moulberry92/ImVec2;Ljava/lang/String;)V` | PARTIAL | out-param (ImVec2,String) overload not implemented: writes nothing and measures toString of ImVec2 |
| 231 | moulberry92 | ImGui | `collapsingHeader` | `(Ljava/lang/String;)Z` | OK | state stored by currentId hashCode |
| 232 | moulberry92 | ImGui | `createContext` | `()Limgui/moulberry92/internal/ImGuiContext;` | OK | shared context object |
| 233 | moulberry92 | ImGui | `dockSpaceOverViewport` | `(ILimgui/moulberry92/ImGuiViewport;I)I` | PARTIAL | always returns 1; no dockspace node registration |
| 234 | moulberry92 | ImGui | `dummy` | `(FF)V` | OK |  |
| 235 | moulberry92 | ImGui | `endChild` | `()V` | OK | delegates to end() |
| 236 | moulberry92 | ImGui | `endDisabled` | `()V` | PARTIAL | always alpha=1 (breaks nested disabled) |
| 237 | moulberry92 | ImGui | `endGroup` | `()V` | OK | rewinds cursor and sizes group |
| 238 | moulberry92 | ImGui | `endMainMenuBar` | `()V` | OK |  |
| 239 | moulberry92 | ImGui | `endMenuBar` | `()V` | OK |  |
| 240 | moulberry92 | ImGui | `endTabBar` | `()V` | OK | clears flag |
| 241 | moulberry92 | ImGui | `endTable` | `()V` | OK | sizes table |
| 242 | moulberry92 | ImGui | `end` | `()V` | OK | pops window, clamps scroll, draws scrollbar |
| 243 | moulberry92 | ImGui | `getBackgroundDrawList` | `()Limgui/moulberry92/ImDrawList;` | OK |  |
| 244 | moulberry92 | ImGui | `getColorU32` | `(I)I` | OK | ImGuiCol index 0..63 and packed color; packed value <64 is misread as index |
| 245 | moulberry92 | ImGui | `getContentRegionAvailX` | `()F` | PARTIAL | contentW is correct; based on contentH for Y which is 16-24px short |
| 246 | moulberry92 | ImGui | `getContentRegionAvailY` | `()F` | PARTIAL | contentH subtracts title twice; too small by (titleHeight-paddingY) |
| 247 | moulberry92 | ImGui | `getCurrentContext` | `()Limgui/moulberry92/internal/ImGuiContext;` | OK |  |
| 248 | moulberry92 | ImGui | `getCursorPosX` | `()F` | OK |  |
| 249 | moulberry92 | ImGui | `getCursorPosY` | `()F` | OK |  |
| 250 | moulberry92 | ImGui | `getCursorScreenPos` | `()Limgui/moulberry92/ImVec2;` | OK |  |
| 251 | moulberry92 | ImGui | `getCursorScreenPosX` | `()F` | OK | scrollX always 0 |
| 252 | moulberry92 | ImGui | `getCursorScreenPosY` | `()F` | OK | applies scrollY |
| 253 | moulberry92 | ImGui | `getDrawData` | `()Limgui/moulberry92/ImDrawData;` | OK |  |
| 254 | moulberry92 | ImGui | `getFontSize` | `()I` | PARTIAL | returns current FontData.size, but every addFont makes the newest font current -> icon font size after load |
| 255 | moulberry92 | ImGui | `getForegroundDrawList` | `()Limgui/moulberry92/ImDrawList;` | OK |  |
| 256 | moulberry92 | ImGui | `getFrameHeight` | `()F` | PARTIAL | uses style.fontSize, not current/pushed font size |
| 257 | moulberry92 | ImGui | `getID` | `(Ljava/lang/String;)I` | PARTIAL | String.hashCode instead of ImGui CRC; consistent internally but not with currentId() |
| 258 | moulberry92 | ImGui | `getIO` | `()Limgui/moulberry92/ImGuiIO;` | OK |  |
| 259 | moulberry92 | ImGui | `getMainViewport` | `()Limgui/moulberry92/ImGuiViewport;` | OK |  |
| 260 | moulberry92 | ImGui | `getMouseCursor` | `()I` | NO-OP | always 0 (Arrow) |
| 261 | moulberry92 | ImGui | `getStyle` | `()Limgui/moulberry92/ImGuiStyle;` | OK | global style |
| 262 | moulberry92 | ImGui | `getWindowContentRegionMaxX` | `()F` | OK | w - contentX (= contentX+contentW) |
| 263 | moulberry92 | ImGui | `getWindowContentRegionMaxY` | `()F` | PARTIAL | h - contentY; should be contentY+contentH (= h - paddingY), short by titleHeight |
| 264 | moulberry92 | ImGui | `getWindowContentRegionMinX` | `()F` | OK | contentX |
| 265 | moulberry92 | ImGui | `getWindowContentRegionMinY` | `()F` | OK | titleHeight+paddingY |
| 266 | moulberry92 | ImGui | `getWindowDpiScale` | `()F` | OK | 1.0 |
| 267 | moulberry92 | ImGui | `getWindowDrawList` | `()Limgui/moulberry92/ImDrawList;` | OK | per-window list |
| 268 | moulberry92 | ImGui | `getWindowHeight` | `()F` | OK |  |
| 269 | moulberry92 | ImGui | `getWindowPos` | `()Limgui/moulberry92/ImVec2;` | OK |  |
| 270 | moulberry92 | ImGui | `getWindowPosX` | `()F` | OK |  |
| 271 | moulberry92 | ImGui | `getWindowPosY` | `()F` | OK |  |
| 272 | moulberry92 | ImGui | `getWindowSize` | `()Limgui/moulberry92/ImVec2;` | OK |  |
| 273 | moulberry92 | ImGui | `getWindowSizeX` | `()F` | OK |  |
| 274 | moulberry92 | ImGui | `getWindowWidth` | `()F` | OK |  |
| 275 | moulberry92 | ImGui | `init` | `()V` | NO-OP | binding already initialised by mixin static init |
| 276 | moulberry92 | ImGui | `invisibleButton` | `(Ljava/lang/String;FFI)Z` | OK |  |
| 277 | moulberry92 | ImGuiIO | `addBackendFlags` | `(I)V` | OK |  |
| 278 | moulberry92 | ImGuiIO | `addConfigFlags` | `(I)V` | OK | ViewportsEnable masked out deliberately |
| 279 | moulberry92 | ImGuiIO | `addFocusEvent` | `(Z)V` | OK | sets focused flag |
| 280 | moulberry92 | ImGuiIO | `addKeyEvent` | `(IZ)V` | OK | keysDown/keysNextPressed/Released |
| 281 | moulberry92 | ImGuiIO | `addMouseButtonEvent` | `(IZ)V` | OK | mouseDown + next pressed/released + drag start |
| 282 | moulberry92 | ImGuiIO | `addMousePosEvent` | `(FF)V` | OK | mouse position + capture update |
| 283 | moulberry92 | ImGuiIO | `addMouseSourceEvent` | `(I)V` | NO-OP | source (mouse/touch/pen) ignored; harmless here |
| 284 | moulberry92 | ImGuiIO | `getFonts` | `()Limgui/moulberry92/ImFontAtlas;` | OK | atlas wrapper |
| 285 | moulberry92 | ImGuiIO | `getKeyAlt` | `()Z` | OK |  |
| 286 | moulberry92 | ImGuiIO | `getKeyCtrl` | `()Z` | OK |  |
| 287 | moulberry92 | ImGuiIO | `getKeyShift` | `()Z` | OK |  |
| 288 | moulberry92 | ImGuiIO | `getKeySuper` | `()Z` | OK |  |
| 289 | moulberry92 | ImGuiIO | `getMouseDown` | `(I)Z` | OK |  |
| 290 | moulberry92 | ImGuiIO | `getMouseDrawCursor` | `()Z` | NO-OP | always false |
| 291 | moulberry92 | ImGuiIO | `getMousePosX` | `()F` | OK |  |
| 292 | moulberry92 | ImGuiIO | `getMousePosY` | `()F` | OK |  |
| 293 | moulberry92 | ImGuiIO | `getMouseWheel` | `()F` | OK |  |
| 294 | moulberry92 | ImGuiIO | `getMouseWheelH` | `()F` | OK |  |
| 295 | moulberry92 | ImGuiIO | `getWantCaptureKeyboard` | `()Z` | OK | computed in updateMouseCapture |
| 296 | moulberry92 | ImGuiIO | `getWantCaptureMouse` | `()Z` | OK | computed in updateMouseCapture |
| 297 | moulberry92 | ImGuiIO | `getWantTextInput` | `()Z` | OK | set by inputText |
| 298 | moulberry92 | ImGuiIO | `hasConfigFlags` | `(I)Z` | OK |  |
| 299 | moulberry92 | ImGuiIO | `removeConfigFlags` | `(I)V` | OK |  |
| 300 | moulberry92 | ImGuiIO | `setBackendPlatformName` | `(Ljava/lang/String;)V` | OK |  |
| 301 | moulberry92 | ImGuiIO | `setConfigMacOSXBehaviors` | `(Z)V` | NO-OP | shortcut behavior flag ignored |
| 302 | moulberry92 | ImGuiIO | `setDeltaTime` | `(F)V` | OK | stored, overwritten by newFrame wall clock |
| 303 | moulberry92 | ImGuiIO | `setDisplayFramebufferScale` | `(FF)V` | OK |  |
| 304 | moulberry92 | ImGuiIO | `setDisplaySize` | `(FF)V` | OK | also updates viewport/work size |
| 305 | moulberry92 | ImGuiIO | `setGetClipboardTextFn` | `(Limgui/moulberry92/callback/ImStrSupplier;)V` | OK | supplier.get() |
| 306 | moulberry92 | ImGuiIO | `setIniFilename` | `(Ljava/lang/String;)V` | OK | used by loadIni, no save |
| 307 | moulberry92 | ImGuiIO | `setKeyAlt` | `(Z)V` | OK |  |
| 308 | moulberry92 | ImGuiIO | `setKeyCtrl` | `(Z)V` | OK |  |
| 309 | moulberry92 | ImGuiIO | `setKeyShift` | `(Z)V` | OK |  |
| 310 | moulberry92 | ImGuiIO | `setKeySuper` | `(Z)V` | OK |  |
| 311 | moulberry92 | ImGuiIO | `setSetClipboardTextFn` | `(Limgui/moulberry92/callback/ImStrConsumer;)V` | OK | consumer.accept() |
| 312 | moulberry92 | ImGui | `isAnyMouseDown` | `()Z` | OK |  |
| 313 | moulberry92 | ImGui | `isItemClicked` | `(I)Z` | PARTIAL | button argument ignored (all buttons use lastItemClicked) |
| 314 | moulberry92 | ImGui | `isItemClicked` | `()Z` | OK | no flag argument |
| 315 | moulberry92 | ImGui | `isItemHovered` | `(I)Z` | PARTIAL | flags argument ignored |
| 316 | moulberry92 | ImGui | `isItemHovered` | `()Z` | OK | no flag argument |
| 317 | moulberry92 | ImGui | `isItemVisible` | `()Z` | NO-OP | always true |
| 318 | moulberry92 | ImGui | `isKeyDown` | `(I)Z` | OK |  |
| 319 | moulberry92 | ImGui | `isKeyPressed` | `(I)Z` | OK | edge-triggered; no repeat requested |
| 320 | moulberry92 | ImGui | `isKeyPressed` | `(IZ)Z` | PARTIAL | repeat flag ignored; only transition frame |
| 321 | moulberry92 | ImGui | `isMouseClicked` | `(I)Z` | OK | edge-triggered; no repeat requested |
| 322 | moulberry92 | ImGui | `isMouseClicked` | `(IZ)Z` | PARTIAL | repeat flag ignored |
| 323 | moulberry92 | ImGui | `isMouseDown` | `(I)Z` | OK |  |
| 324 | moulberry92 | ImGui | `isPopupOpen` | `(Ljava/lang/String;I)Z` | OK |  |
| 325 | moulberry92 | ImGui | `isPopupOpen` | `(Ljava/lang/String;)Z` | OK |  |
| 326 | moulberry92 | ImGui | `isRectVisible` | `(FF)Z` | NO-OP | always true; safe but culling ineffective |
| 327 | moulberry92 | ImGui | `isWindowDocked` | `()Z` | PARTIAL | dockId!=0; custom docking only |
| 328 | moulberry92 | ImGui | `isWindowFocused` | `()Z` | PARTIAL | compares current window with last LinkedHashMap entry, not real focus |
| 329 | moulberry92 | ImGui | `isWindowHovered` | `()Z` | PARTIAL | flags ignored |
| 330 | moulberry92 | ImGui | `menuItem` | `(Ljava/lang/String;)Z` | OK |  |
| 331 | moulberry92 | ImGui | `newFrame` | `()V` | OK | io delta, input latch, wheel scroll, capture |
| 332 | moulberry92 | ImGui | `popFont` | `()V` | OK |  |
| 333 | moulberry92 | ImGui | `popID` | `()V` | OK |  |
| 334 | moulberry92 | ImGui | `popStyleColor` | `()V` | OK |  |
| 335 | moulberry92 | ImGui | `popStyleVar` | `()V` | OK | copies saved Style |
| 336 | moulberry92 | ImGui | `popTextWrapPos` | `()V` | OK |  |
| 337 | moulberry92 | ImGui | `pushFont` | `(Limgui/moulberry92/ImFont;F)V` | PARTIAL | size override ignored; text layout still uses style.fontSize |
| 338 | moulberry92 | ImGui | `pushID` | `(I)V` | PARTIAL | int overload becomes decimal String; String stack only |
| 339 | moulberry92 | ImGui | `pushID` | `(Ljava/lang/String;)V` | OK | string ID stack |
| 340 | moulberry92 | ImGui | `pushStyleColor` | `(II)V` | OK |  |
| 341 | moulberry92 | ImGui | `pushStyleVar` | `(IFF)V` | OK |  |
| 342 | moulberry92 | ImGui | `pushStyleVar` | `(IF)V` | OK |  |
| 343 | moulberry92 | ImGui | `pushTextWrapPos` | `()V` | OK |  |
| 344 | moulberry92 | ImGui | `render` | `()V` | OK | builds cmd lists/buffers |
| 345 | moulberry92 | ImGui | `sameLine` | `(FF)V` | PARTIAL | offset interpreted as gap from lastItemRight rather than offset-from-start-x |
| 346 | moulberry92 | ImGui | `sameLine` | `(F)V` | PARTIAL | offset interpreted as gap from lastItemRight rather than offset-from-start-x |
| 347 | moulberry92 | ImGui | `sameLine` | `()V` | PARTIAL | offset interpreted as gap from lastItemRight rather than offset-from-start-x |
| 348 | moulberry92 | ImGui | `separator` | `()V` | OK |  |
| 349 | moulberry92 | ImGui | `setAssertCallback` | `(Limgui/moulberry92/assertion/ImAssertCallback;)V` | NO-OP | callback ignored (default assertions disabled) |
| 350 | moulberry92 | ImGui | `setCurrentContext` | `(Limgui/moulberry92/internal/ImGuiContext;)V` | NO-OP | one context per moulberryXX package |
| 351 | moulberry92 | ImGui | `setCursorPos` | `(FF)V` | OK |  |
| 352 | moulberry92 | ImGui | `setCursorPosX` | `(F)V` | OK |  |
| 353 | moulberry92 | ImGui | `setCursorPosY` | `(F)V` | OK |  |
| 354 | moulberry92 | ImGui | `setCursorScreenPos` | `(FF)V` | PARTIAL | Y ignores scrollY (should add scrollY) |
| 355 | moulberry92 | ImGui | `setMouseCursor` | `(I)V` | NO-OP | cursor shape ignored |
| 356 | moulberry92 | ImGui | `setNextFrameWantCaptureMouse` | `(Z)V` | OK |  |
| 357 | moulberry92 | ImGui | `setNextItemWidth` | `(F)V` | OK |  |
| 358 | moulberry92 | ImGui | `setNextWindowBgAlpha` | `(F)V` | OK |  |
| 359 | moulberry92 | ImGui | `setNextWindowDockID` | `(I)V` | PARTIAL | condition flags ignored |
| 360 | moulberry92 | ImGui | `setNextWindowPos` | `(FFIFF)V` | OK | float and ImVec2/pivot forms |
| 361 | moulberry92 | ImGui | `setNextWindowPos` | `(FFI)V` | OK | float and ImVec2/pivot forms |
| 362 | moulberry92 | ImGui | `setNextWindowPos` | `(FF)V` | OK | float and ImVec2/pivot forms |
| 363 | moulberry92 | ImGui | `setNextWindowSize` | `(FFI)V` | OK |  |
| 364 | moulberry92 | ImGui | `setNextWindowSize` | `(FF)V` | OK |  |
| 365 | moulberry92 | ImGui | `setNextWindowViewport` | `(I)V` | NO-OP | multi-viewport disabled |
| 366 | moulberry92 | ImGui | `setScrollX` | `(F)V` | NO-OP | no horizontal scroll state |
| 367 | moulberry92 | ImGui | `setWindowFocus` | `()V` | NO-OP | does not change focus |
| 368 | moulberry92 | ImGui | `sliderFloat` | `(Ljava/lang/String;[FFFLjava/lang/String;)Z` | PARTIAL | format honoured; click/drag sets value, no ctrl+click input |
| 369 | moulberry92 | ImGui | `smallButton` | `(Ljava/lang/String;)Z` | OK |  |
| 370 | moulberry92 | ImGui | `styleColorsDark` | `(Limgui/moulberry92/ImGuiStyle;)V` | PARTIAL | argument style ignored; always resets global style |
| 371 | moulberry92 | ImGui | `styleColorsLight` | `(Limgui/moulberry92/ImGuiStyle;)V` | PARTIAL | argument ignored AND colorsLight() == colorsDark() |
| 372 | moulberry92 | ImGuiStyle | `create` | `()J` | MISSING | no case: constructor ptr=0; every new ImGuiStyle aliases the global style and cannot be selected/copied |
| 373 | moulberry92 | ImGuiStyle | `getCellPaddingX` | `()F` | PARTIAL | dynamic Style.var CellPadding; handler always uses global Style, self/ptr ignored |
| 374 | moulberry92 | ImGuiStyle | `getCellPaddingY` | `()F` | PARTIAL | dynamic Style.var CellPadding; handler always uses global Style, self/ptr ignored |
| 375 | moulberry92 | ImGuiStyle | `getChildBorderSize` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 376 | moulberry92 | ImGuiStyle | `getChildRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 377 | moulberry92 | ImGuiStyle | `getColors` | `()[Limgui/moulberry92/ImVec4;` | PARTIAL | returns ImVec4[64]; handler always uses global Style, self/ptr ignored |
| 378 | moulberry92 | ImGuiStyle | `getFrameBorderSize` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 379 | moulberry92 | ImGuiStyle | `getFramePaddingX` | `()F` | PARTIAL | dynamic FramePadding; handler always uses global Style, self/ptr ignored |
| 380 | moulberry92 | ImGuiStyle | `getFramePaddingY` | `()F` | PARTIAL | dynamic FramePadding; handler always uses global Style, self/ptr ignored |
| 381 | moulberry92 | ImGuiStyle | `getFrameRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 382 | moulberry92 | ImGuiStyle | `getGrabRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 383 | moulberry92 | ImGuiStyle | `getIndentSpacing` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 384 | moulberry92 | ImGuiStyle | `getItemSpacingX` | `()F` | PARTIAL | dynamic ItemSpacing; handler always uses global Style, self/ptr ignored |
| 385 | moulberry92 | ImGuiStyle | `getPopupBorderSize` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 386 | moulberry92 | ImGuiStyle | `getPopupRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 387 | moulberry92 | ImGuiStyle | `getScrollbarRounding` | `()F` | PARTIAL | dynamic, but Style has no scrollbarRounding field -> returns default 0; handler always uses global Style, self/ptr ignored |
| 388 | moulberry92 | ImGuiStyle | `getTabBorderSize` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 389 | moulberry92 | ImGuiStyle | `getTabRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 390 | moulberry92 | ImGuiStyle | `getWindowBorderSize` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 391 | moulberry92 | ImGuiStyle | `getWindowPaddingY` | `()F` | PARTIAL | dynamic WindowPadding; handler always uses global Style, self/ptr ignored |
| 392 | moulberry92 | ImGuiStyle | `getWindowRounding` | `()F` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 393 | moulberry92 | ImGuiStyle | `setChildBorderSize` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 394 | moulberry92 | ImGuiStyle | `setChildRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 395 | moulberry92 | ImGuiStyle | `setColors` | `([Limgui/moulberry92/ImVec4;)V` | PARTIAL | ImVec4[64] (global style only); handler always uses global Style, self/ptr ignored |
| 396 | moulberry92 | ImGuiStyle | `setFrameBorderSize` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 397 | moulberry92 | ImGuiStyle | `setFrameRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 398 | moulberry92 | ImGuiStyle | `setGrabRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 399 | moulberry92 | ImGuiStyle | `setPopupBorderSize` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 400 | moulberry92 | ImGuiStyle | `setPopupRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 401 | moulberry92 | ImGuiStyle | `setScrollbarRounding` | `(F)V` | PARTIAL | setVar has no ScrollbarRounding branch -> silently dropped |
| 402 | moulberry92 | ImGuiStyle | `setTabBorderSize` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 403 | moulberry92 | ImGuiStyle | `setTabRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 404 | moulberry92 | ImGuiStyle | `setWindowBorderSize` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 405 | moulberry92 | ImGuiStyle | `setWindowRounding` | `(F)V` | PARTIAL | dynamic scalar; handler always uses global Style, self/ptr ignored |
| 406 | moulberry92 | ImGui | `tabItemButton` | `(Ljava/lang/String;I)Z` | PARTIAL | renders a button; no tab selection/close semantics |
| 407 | moulberry92 | ImGui | `tableNextColumn` | `()Z` | PARTIAL | simple column advance |
| 408 | moulberry92 | ImGui | `textColored` | `(ILjava/lang/String;)V` | PARTIAL | (int,String) overload draws empty string with nonsense color |
| 409 | moulberry92 | ImGui | `textDisabled` | `(Ljava/lang/String;)V` | OK | fixed grey |
| 410 | moulberry92 | ImGui | `textUnformatted` | `(Ljava/lang/String;)V` | OK |  |
| 411 | moulberry92 | ImGuiViewport | `getCenter` | `()Limgui/moulberry92/ImVec2;` | OK | pos+size/2 |
| 412 | moulberry92 | ImGuiViewport | `getCenterX` | `()F` | OK |  |
| 413 | moulberry92 | ImGuiViewport | `getCenterY` | `()F` | OK |  |
| 414 | moulberry92 | ImGuiViewport | `getID` | `()I` | OK | stable id 1 |
| 415 | moulberry92 | ImGuiViewport | `getPosX` | `()F` | OK |  |
| 416 | moulberry92 | ImGuiViewport | `getPosY` | `()F` | OK |  |
| 417 | moulberry92 | ImGuiViewport | `getSizeX` | `()F` | OK |  |
| 418 | moulberry92 | ImGuiViewport | `getSizeY` | `()F` | OK |  |
| 419 | moulberry92 | ImGuiViewport | `getWorkPos` | `()Limgui/moulberry92/ImVec2;` | OK |  |
| 420 | moulberry92 | ImGuiViewport | `getWorkSize` | `()Limgui/moulberry92/ImVec2;` | OK |  |
| 421 | moulberry92 | ImGuiViewport | `setWorkSize` | `(FF)V` | OK | updates workW/H |
| 422 | moulberry92.internal | ImGui | `dockBuilderGetCentralNode` | `(I)Limgui/moulberry92/internal/ImGuiDockNode;` | PARTIAL | reads arg 1 (does not exist) instead of arg 0; returns opaque node with no state |
| 423 | moulberry92.internal | ImGuiDockNode | `addLocalFlags` | `(I)V` | MISSING | dispatch case returns null; dock node flags lost (4096=NoTabBar) |
| 424 | moulberry92.internal | ImGui | `init` | `()V` | NO-OP | binding already initialised by mixin static init |

---

## Method notes / caveats

- Status is per descriptor. For example `ImGui.textColored` is **PARTIAL** for `(ILjava/lang/String;)V` (draws nothing) but meaningful for `(Limgui/.../ImVec4;Ljava/lang/String;)V`; `ImDrawList.addRectFilled` is OK for `(FFFFI)V` and PARTIAL for `(FFFFII)V`.
- "OK" means the call has a real handler and the observed return shape is usable; it does not mean pixel-identical Dear ImGui behavior. Tables, tabs, popups, menus and docking are simplified implementations by design.
- `ImGuiStyle` getters/setters are marked PARTIAL even though their individual property logic exists, because `UiContext.style(...)` ignores the `self` argument and always edits the global style. This is only harmless when the caller uses `ImGui.getStyle()`; Axiom's `BuiltinStyles` creates independent dark/light `ImGuiStyle` objects.
- The full table is generated from `run/calls.txt`; the 90/92 packages are kept separate because their descriptors and mixins differ.
- All proposed changes are local to `PureUi.java` unless a mixin is stated otherwise. No mixin regeneration is required for the changes in gaps 1-10 because the affected mixins already forward to `PureUi.call*`.
