package com.noimgui.imgui;

/**
 * Palette port of Dear ImGui's {@code ImGui::StyleColorsDark()},
 * {@code ImGui::StyleColorsLight()} and {@code ImGui::StyleColorsClassic()}
 * (imgui_draw.cpp, Dear ImGui 1.92.7).
 *
 * <p>Colours are returned as flat {@code float[]} arrays, index-major:
 * {@code array[index * 4 + channel]} with channels {@code R, G, B, A} in
 * {@code 0..1}. Indices are the {@code ImGuiCol_} enum values, matching the
 * order declared in {@code imgui.h}.</p>
 *
 * <p>Derived entries ({@code Separator}, {@code Tab*}, {@code TextLink},
 * {@code DockingPreview}, ...) are computed with the same single-precision
 * {@code ImLerp} / component-wise multiply arithmetic the C++ source uses, so
 * the values are bit-identical.</p>
 */
public final class StyleColors {
    private StyleColors() {
    }

    // --- ImGuiCol_ enum, verbatim order from imgui.h -------------------------
    public static final int Text = 0;
    public static final int TextDisabled = 1;
    public static final int WindowBg = 2;
    public static final int ChildBg = 3;
    public static final int PopupBg = 4;
    public static final int Border = 5;
    public static final int BorderShadow = 6;
    public static final int FrameBg = 7;
    public static final int FrameBgHovered = 8;
    public static final int FrameBgActive = 9;
    public static final int TitleBg = 10;
    public static final int TitleBgActive = 11;
    public static final int TitleBgCollapsed = 12;
    public static final int MenuBarBg = 13;
    public static final int ScrollbarBg = 14;
    public static final int ScrollbarGrab = 15;
    public static final int ScrollbarGrabHovered = 16;
    public static final int ScrollbarGrabActive = 17;
    public static final int CheckMark = 18;
    public static final int SliderGrab = 19;
    public static final int SliderGrabActive = 20;
    public static final int Button = 21;
    public static final int ButtonHovered = 22;
    public static final int ButtonActive = 23;
    public static final int Header = 24;
    public static final int HeaderHovered = 25;
    public static final int HeaderActive = 26;
    public static final int Separator = 27;
    public static final int SeparatorHovered = 28;
    public static final int SeparatorActive = 29;
    public static final int ResizeGrip = 30;
    public static final int ResizeGripHovered = 31;
    public static final int ResizeGripActive = 32;
    public static final int InputTextCursor = 33;
    public static final int TabHovered = 34;
    public static final int Tab = 35;
    public static final int TabSelected = 36;
    public static final int TabSelectedOverline = 37;
    public static final int TabDimmed = 38;
    public static final int TabDimmedSelected = 39;
    public static final int TabDimmedSelectedOverline = 40;
    public static final int DockingPreview = 41;
    public static final int DockingEmptyBg = 42;
    public static final int PlotLines = 43;
    public static final int PlotLinesHovered = 44;
    public static final int PlotHistogram = 45;
    public static final int PlotHistogramHovered = 46;
    public static final int TableHeaderBg = 47;
    public static final int TableBorderStrong = 48;
    public static final int TableBorderLight = 49;
    public static final int TableRowBg = 50;
    public static final int TableRowBgAlt = 51;
    public static final int TextLink = 52;
    public static final int TextSelectedBg = 53;
    public static final int TreeLines = 54;
    public static final int DragDropTarget = 55;
    public static final int DragDropTargetBg = 56;
    public static final int UnsavedMarker = 57;
    public static final int NavCursor = 58;
    public static final int NavWindowingHighlight = 59;
    public static final int NavWindowingDimBg = 60;
    public static final int ModalWindowDimBg = 61;

    /** Value of {@code ImGuiCol_COUNT} (obsolete aliases excluded). */
    public static final int COUNT = 62;

    /** Short enum names, index i == {@code ImGuiCol_<NAMES[i]>}. */
    private static final String[] NAMES = {
        "Text", "TextDisabled", "WindowBg", "ChildBg", "PopupBg", "Border",
        "BorderShadow", "FrameBg", "FrameBgHovered", "FrameBgActive", "TitleBg",
        "TitleBgActive", "TitleBgCollapsed", "MenuBarBg", "ScrollbarBg",
        "ScrollbarGrab", "ScrollbarGrabHovered", "ScrollbarGrabActive",
        "CheckMark", "SliderGrab", "SliderGrabActive", "Button", "ButtonHovered",
        "ButtonActive", "Header", "HeaderHovered", "HeaderActive", "Separator",
        "SeparatorHovered", "SeparatorActive", "ResizeGrip", "ResizeGripHovered",
        "ResizeGripActive", "InputTextCursor", "TabHovered", "Tab", "TabSelected",
        "TabSelectedOverline", "TabDimmed", "TabDimmedSelected",
        "TabDimmedSelectedOverline", "DockingPreview", "DockingEmptyBg",
        "PlotLines", "PlotLinesHovered", "PlotHistogram", "PlotHistogramHovered",
        "TableHeaderBg", "TableBorderStrong", "TableBorderLight", "TableRowBg",
        "TableRowBgAlt", "TextLink", "TextSelectedBg", "TreeLines",
        "DragDropTarget", "DragDropTargetBg", "UnsavedMarker", "NavCursor",
        "NavWindowingHighlight", "NavWindowingDimBg", "ModalWindowDimBg",
    };

    private static final float[] DARK = buildDark();
    private static final float[] LIGHT = buildLight();
    private static final float[] CLASSIC = buildClassic();

    // ---------------------------------------------------------------- public API

    public static int count() {
        return COUNT;
    }

    /** Fresh {@code 4 * ImGuiCol_COUNT} array with the dark palette. */
    public static float[] dark() {
        return DARK.clone();
    }

    /** Fresh {@code 4 * ImGuiCol_COUNT} array with the light palette. */
    public static float[] light() {
        return LIGHT.clone();
    }

    /** Fresh {@code 4 * ImGuiCol_COUNT} array with the classic palette. */
    public static float[] classic() {
        return CLASSIC.clone();
    }

    /** Copies the dark palette verbatim into {@code target}. */
    public static void applyDark(float[] target) {
        copyInto(DARK, target);
    }

    /** Copies the light palette verbatim into {@code target}. */
    public static void applyLight(float[] target) {
        copyInto(LIGHT, target);
    }

    /** Copies the classic palette verbatim into {@code target}. */
    public static void applyClassic(float[] target) {
        copyInto(CLASSIC, target);
    }

    /** Enum name without the {@code ImGuiCol_} prefix, or {@code null} if out of range. */
    public static String name(int index) {
        return index >= 0 && index < COUNT ? NAMES[index] : null;
    }

    /**
     * Resolves a colour name. Accepts both the short form ({@code "WindowBg"})
     * and the full enum spelling ({@code "ImGuiCol_WindowBg"}); returns
     * {@code -1} when unknown.
     */
    public static int indexOf(String name) {
        if (name == null) {
            return -1;
        }
        String shortName = name.startsWith("ImGuiCol_") ? name.substring("ImGuiCol_".length()) : name;
        for (int i = 0; i < COUNT; i++) {
            if (NAMES[i].equals(shortName)) {
                return i;
            }
        }
        return -1;
    }

    // ------------------------------------------------------------------- helpers

    private static void copyInto(float[] source, float[] target) {
        if (target == null) {
            throw new IllegalArgumentException("target must not be null");
        }
        if (target.length < source.length) {
            throw new IllegalArgumentException(
                "target needs " + source.length + " floats, got " + target.length);
        }
        System.arraycopy(source, 0, target, 0, source.length);
    }

    private static float[] blank() {
        return new float[COUNT * 4];
    }

    private static void set(float[] c, int index, float r, float g, float b, float a) {
        int base = index * 4;
        c[base] = r;
        c[base + 1] = g;
        c[base + 2] = b;
        c[base + 3] = a;
    }

    private static void copy(float[] c, int dst, int src) {
        System.arraycopy(c, src * 4, c, dst * 4, 4);
    }

    /** {@code ImLerp(a, b, t)} on ImVec4, single precision like the C++ source. */
    private static void lerp(float[] c, int dst, int a, int b, float t) {
        int d = dst * 4;
        int x = a * 4;
        int y = b * 4;
        for (int i = 0; i < 4; i++) {
            c[d + i] = c[x + i] + (c[y + i] - c[x + i]) * t;
        }
    }

    /** Component-wise {@code lhs * rhs} on ImVec4. */
    private static void mul(float[] c, int dst, int src, float r, float g, float b, float a) {
        int d = dst * 4;
        int s = src * 4;
        c[d] = c[s] * r;
        c[d + 1] = c[s + 1] * g;
        c[d + 2] = c[s + 2] * b;
        c[d + 3] = c[s + 3] * a;
    }

    // ------------------------------------------------------- ImGui::StyleColorsDark
    private static float[] buildDark() {
        float[] c = blank();

        set(c, Text, 1.00f, 1.00f, 1.00f, 1.00f);
        set(c, TextDisabled, 0.50f, 0.50f, 0.50f, 1.00f);
        set(c, WindowBg, 0.06f, 0.06f, 0.06f, 0.94f);
        set(c, ChildBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, PopupBg, 0.08f, 0.08f, 0.08f, 0.94f);
        set(c, Border, 0.43f, 0.43f, 0.50f, 0.50f);
        set(c, BorderShadow, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, FrameBg, 0.16f, 0.29f, 0.48f, 0.54f);
        set(c, FrameBgHovered, 0.26f, 0.59f, 0.98f, 0.40f);
        set(c, FrameBgActive, 0.26f, 0.59f, 0.98f, 0.67f);
        set(c, TitleBg, 0.04f, 0.04f, 0.04f, 1.00f);
        set(c, TitleBgActive, 0.16f, 0.29f, 0.48f, 1.00f);
        set(c, TitleBgCollapsed, 0.00f, 0.00f, 0.00f, 0.51f);
        set(c, MenuBarBg, 0.14f, 0.14f, 0.14f, 1.00f);
        set(c, ScrollbarBg, 0.02f, 0.02f, 0.02f, 0.53f);
        set(c, ScrollbarGrab, 0.31f, 0.31f, 0.31f, 1.00f);
        set(c, ScrollbarGrabHovered, 0.41f, 0.41f, 0.41f, 1.00f);
        set(c, ScrollbarGrabActive, 0.51f, 0.51f, 0.51f, 1.00f);
        set(c, CheckMark, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, SliderGrab, 0.24f, 0.52f, 0.88f, 1.00f);
        set(c, SliderGrabActive, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, Button, 0.26f, 0.59f, 0.98f, 0.40f);
        set(c, ButtonHovered, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, ButtonActive, 0.06f, 0.53f, 0.98f, 1.00f);
        set(c, Header, 0.26f, 0.59f, 0.98f, 0.31f);
        set(c, HeaderHovered, 0.26f, 0.59f, 0.98f, 0.80f);
        set(c, HeaderActive, 0.26f, 0.59f, 0.98f, 1.00f);
        copy(c, Separator, Border);
        set(c, SeparatorHovered, 0.10f, 0.40f, 0.75f, 0.78f);
        set(c, SeparatorActive, 0.10f, 0.40f, 0.75f, 1.00f);
        set(c, ResizeGrip, 0.26f, 0.59f, 0.98f, 0.20f);
        set(c, ResizeGripHovered, 0.26f, 0.59f, 0.98f, 0.67f);
        set(c, ResizeGripActive, 0.26f, 0.59f, 0.98f, 0.95f);
        copy(c, InputTextCursor, Text);
        copy(c, TabHovered, HeaderHovered);
        lerp(c, Tab, Header, TitleBgActive, 0.80f);
        lerp(c, TabSelected, HeaderActive, TitleBgActive, 0.60f);
        copy(c, TabSelectedOverline, HeaderActive);
        lerp(c, TabDimmed, Tab, TitleBg, 0.80f);
        lerp(c, TabDimmedSelected, TabSelected, TitleBg, 0.40f);
        set(c, TabDimmedSelectedOverline, 0.50f, 0.50f, 0.50f, 0.00f);
        mul(c, DockingPreview, HeaderActive, 1.0f, 1.0f, 1.0f, 0.7f);
        set(c, DockingEmptyBg, 0.20f, 0.20f, 0.20f, 1.00f);
        set(c, PlotLines, 0.61f, 0.61f, 0.61f, 1.00f);
        set(c, PlotLinesHovered, 1.00f, 0.43f, 0.35f, 1.00f);
        set(c, PlotHistogram, 0.90f, 0.70f, 0.00f, 1.00f);
        set(c, PlotHistogramHovered, 1.00f, 0.60f, 0.00f, 1.00f);
        set(c, TableHeaderBg, 0.19f, 0.19f, 0.20f, 1.00f);
        set(c, TableBorderStrong, 0.31f, 0.31f, 0.35f, 1.00f);
        set(c, TableBorderLight, 0.23f, 0.23f, 0.25f, 1.00f);
        set(c, TableRowBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, TableRowBgAlt, 1.00f, 1.00f, 1.00f, 0.06f);
        copy(c, TextLink, HeaderActive);
        set(c, TextSelectedBg, 0.26f, 0.59f, 0.98f, 0.35f);
        copy(c, TreeLines, Border);
        set(c, DragDropTarget, 1.00f, 1.00f, 0.00f, 0.90f);
        set(c, DragDropTargetBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, UnsavedMarker, 1.00f, 1.00f, 1.00f, 1.00f);
        set(c, NavCursor, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, NavWindowingHighlight, 1.00f, 1.00f, 1.00f, 0.70f);
        set(c, NavWindowingDimBg, 0.80f, 0.80f, 0.80f, 0.20f);
        set(c, ModalWindowDimBg, 0.80f, 0.80f, 0.80f, 0.35f);

        return c;
    }

    // ---------------------------------------------------- ImGui::StyleColorsClassic
    private static float[] buildClassic() {
        float[] c = blank();

        set(c, Text, 0.90f, 0.90f, 0.90f, 1.00f);
        set(c, TextDisabled, 0.60f, 0.60f, 0.60f, 1.00f);
        set(c, WindowBg, 0.00f, 0.00f, 0.00f, 0.85f);
        set(c, ChildBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, PopupBg, 0.11f, 0.11f, 0.14f, 0.92f);
        set(c, Border, 0.50f, 0.50f, 0.50f, 0.50f);
        set(c, BorderShadow, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, FrameBg, 0.43f, 0.43f, 0.43f, 0.39f);
        set(c, FrameBgHovered, 0.47f, 0.47f, 0.69f, 0.40f);
        set(c, FrameBgActive, 0.42f, 0.41f, 0.64f, 0.69f);
        set(c, TitleBg, 0.27f, 0.27f, 0.54f, 0.83f);
        set(c, TitleBgActive, 0.32f, 0.32f, 0.63f, 0.87f);
        set(c, TitleBgCollapsed, 0.40f, 0.40f, 0.80f, 0.20f);
        set(c, MenuBarBg, 0.40f, 0.40f, 0.55f, 0.80f);
        set(c, ScrollbarBg, 0.20f, 0.25f, 0.30f, 0.60f);
        set(c, ScrollbarGrab, 0.40f, 0.40f, 0.80f, 0.30f);
        set(c, ScrollbarGrabHovered, 0.40f, 0.40f, 0.80f, 0.40f);
        set(c, ScrollbarGrabActive, 0.41f, 0.39f, 0.80f, 0.60f);
        set(c, CheckMark, 0.90f, 0.90f, 0.90f, 0.50f);
        set(c, SliderGrab, 1.00f, 1.00f, 1.00f, 0.30f);
        set(c, SliderGrabActive, 0.41f, 0.39f, 0.80f, 0.60f);
        set(c, Button, 0.35f, 0.40f, 0.61f, 0.62f);
        set(c, ButtonHovered, 0.40f, 0.48f, 0.71f, 0.79f);
        set(c, ButtonActive, 0.46f, 0.54f, 0.80f, 1.00f);
        set(c, Header, 0.40f, 0.40f, 0.90f, 0.45f);
        set(c, HeaderHovered, 0.45f, 0.45f, 0.90f, 0.80f);
        set(c, HeaderActive, 0.53f, 0.53f, 0.87f, 0.80f);
        set(c, Separator, 0.50f, 0.50f, 0.50f, 0.60f);
        set(c, SeparatorHovered, 0.60f, 0.60f, 0.70f, 1.00f);
        set(c, SeparatorActive, 0.70f, 0.70f, 0.90f, 1.00f);
        set(c, ResizeGrip, 1.00f, 1.00f, 1.00f, 0.10f);
        set(c, ResizeGripHovered, 0.78f, 0.82f, 1.00f, 0.60f);
        set(c, ResizeGripActive, 0.78f, 0.82f, 1.00f, 0.90f);
        copy(c, InputTextCursor, Text);
        copy(c, TabHovered, HeaderHovered);
        lerp(c, Tab, Header, TitleBgActive, 0.80f);
        lerp(c, TabSelected, HeaderActive, TitleBgActive, 0.60f);
        copy(c, TabSelectedOverline, HeaderActive);
        lerp(c, TabDimmed, Tab, TitleBg, 0.80f);
        lerp(c, TabDimmedSelected, TabSelected, TitleBg, 0.40f);
        set(c, TabDimmedSelectedOverline, 0.53f, 0.53f, 0.87f, 0.00f);
        mul(c, DockingPreview, Header, 1.0f, 1.0f, 1.0f, 0.7f);
        set(c, DockingEmptyBg, 0.20f, 0.20f, 0.20f, 1.00f);
        set(c, PlotLines, 1.00f, 1.00f, 1.00f, 1.00f);
        set(c, PlotLinesHovered, 0.90f, 0.70f, 0.00f, 1.00f);
        set(c, PlotHistogram, 0.90f, 0.70f, 0.00f, 1.00f);
        set(c, PlotHistogramHovered, 1.00f, 0.60f, 0.00f, 1.00f);
        set(c, TableHeaderBg, 0.27f, 0.27f, 0.38f, 1.00f);
        set(c, TableBorderStrong, 0.31f, 0.31f, 0.45f, 1.00f);
        set(c, TableBorderLight, 0.26f, 0.26f, 0.28f, 1.00f);
        set(c, TableRowBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, TableRowBgAlt, 1.00f, 1.00f, 1.00f, 0.07f);
        copy(c, TextLink, HeaderActive);
        set(c, TextSelectedBg, 0.00f, 0.00f, 1.00f, 0.35f);
        copy(c, TreeLines, Border);
        set(c, DragDropTarget, 1.00f, 1.00f, 0.00f, 0.90f);
        set(c, DragDropTargetBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, UnsavedMarker, 0.90f, 0.90f, 0.90f, 1.00f);
        copy(c, NavCursor, HeaderHovered);
        set(c, NavWindowingHighlight, 1.00f, 1.00f, 1.00f, 0.70f);
        set(c, NavWindowingDimBg, 0.80f, 0.80f, 0.80f, 0.20f);
        set(c, ModalWindowDimBg, 0.20f, 0.20f, 0.20f, 0.35f);

        return c;
    }

    // ------------------------------------------------------ ImGui::StyleColorsLight
    private static float[] buildLight() {
        float[] c = blank();

        set(c, Text, 0.00f, 0.00f, 0.00f, 1.00f);
        set(c, TextDisabled, 0.60f, 0.60f, 0.60f, 1.00f);
        set(c, WindowBg, 0.94f, 0.94f, 0.94f, 1.00f);
        set(c, ChildBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, PopupBg, 1.00f, 1.00f, 1.00f, 0.98f);
        set(c, Border, 0.00f, 0.00f, 0.00f, 0.30f);
        set(c, BorderShadow, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, FrameBg, 1.00f, 1.00f, 1.00f, 1.00f);
        set(c, FrameBgHovered, 0.26f, 0.59f, 0.98f, 0.40f);
        set(c, FrameBgActive, 0.26f, 0.59f, 0.98f, 0.67f);
        set(c, TitleBg, 0.96f, 0.96f, 0.96f, 1.00f);
        set(c, TitleBgActive, 0.82f, 0.82f, 0.82f, 1.00f);
        set(c, TitleBgCollapsed, 1.00f, 1.00f, 1.00f, 0.51f);
        set(c, MenuBarBg, 0.86f, 0.86f, 0.86f, 1.00f);
        set(c, ScrollbarBg, 0.98f, 0.98f, 0.98f, 0.53f);
        set(c, ScrollbarGrab, 0.69f, 0.69f, 0.69f, 0.80f);
        set(c, ScrollbarGrabHovered, 0.49f, 0.49f, 0.49f, 0.80f);
        set(c, ScrollbarGrabActive, 0.49f, 0.49f, 0.49f, 1.00f);
        set(c, CheckMark, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, SliderGrab, 0.26f, 0.59f, 0.98f, 0.78f);
        set(c, SliderGrabActive, 0.46f, 0.54f, 0.80f, 0.60f);
        set(c, Button, 0.26f, 0.59f, 0.98f, 0.40f);
        set(c, ButtonHovered, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, ButtonActive, 0.06f, 0.53f, 0.98f, 1.00f);
        set(c, Header, 0.26f, 0.59f, 0.98f, 0.31f);
        set(c, HeaderHovered, 0.26f, 0.59f, 0.98f, 0.80f);
        set(c, HeaderActive, 0.26f, 0.59f, 0.98f, 1.00f);
        set(c, Separator, 0.39f, 0.39f, 0.39f, 0.62f);
        set(c, SeparatorHovered, 0.14f, 0.44f, 0.80f, 0.78f);
        set(c, SeparatorActive, 0.14f, 0.44f, 0.80f, 1.00f);
        set(c, ResizeGrip, 0.35f, 0.35f, 0.35f, 0.17f);
        set(c, ResizeGripHovered, 0.26f, 0.59f, 0.98f, 0.67f);
        set(c, ResizeGripActive, 0.26f, 0.59f, 0.98f, 0.95f);
        copy(c, InputTextCursor, Text);
        copy(c, TabHovered, HeaderHovered);
        lerp(c, Tab, Header, TitleBgActive, 0.90f);
        lerp(c, TabSelected, HeaderActive, TitleBgActive, 0.60f);
        copy(c, TabSelectedOverline, HeaderActive);
        lerp(c, TabDimmed, Tab, TitleBg, 0.80f);
        lerp(c, TabDimmedSelected, TabSelected, TitleBg, 0.40f);
        set(c, TabDimmedSelectedOverline, 0.26f, 0.59f, 1.00f, 0.00f);
        mul(c, DockingPreview, Header, 1.0f, 1.0f, 1.0f, 0.7f);
        set(c, DockingEmptyBg, 0.20f, 0.20f, 0.20f, 1.00f);
        set(c, PlotLines, 0.39f, 0.39f, 0.39f, 1.00f);
        set(c, PlotLinesHovered, 1.00f, 0.43f, 0.35f, 1.00f);
        set(c, PlotHistogram, 0.90f, 0.70f, 0.00f, 1.00f);
        set(c, PlotHistogramHovered, 1.00f, 0.45f, 0.00f, 1.00f);
        set(c, TableHeaderBg, 0.78f, 0.87f, 0.98f, 1.00f);
        set(c, TableBorderStrong, 0.57f, 0.57f, 0.64f, 1.00f);
        set(c, TableBorderLight, 0.68f, 0.68f, 0.74f, 1.00f);
        set(c, TableRowBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, TableRowBgAlt, 0.30f, 0.30f, 0.30f, 0.09f);
        copy(c, TextLink, HeaderActive);
        set(c, TextSelectedBg, 0.26f, 0.59f, 0.98f, 0.35f);
        copy(c, TreeLines, Border);
        set(c, DragDropTarget, 0.26f, 0.59f, 0.98f, 0.95f);
        set(c, DragDropTargetBg, 0.00f, 0.00f, 0.00f, 0.00f);
        set(c, UnsavedMarker, 0.00f, 0.00f, 0.00f, 1.00f);
        copy(c, NavCursor, HeaderHovered);
        set(c, NavWindowingHighlight, 0.70f, 0.70f, 0.70f, 0.70f);
        set(c, NavWindowingDimBg, 0.20f, 0.20f, 0.20f, 0.20f);
        set(c, ModalWindowDimBg, 0.20f, 0.20f, 0.20f, 0.35f);

        return c;
    }
}
