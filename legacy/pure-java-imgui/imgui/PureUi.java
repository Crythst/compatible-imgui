package com.noimgui.imgui;

import com.noimgui.NoNativeMod;
import com.noimgui.Reflect;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.IdentityHashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

/**
 * A small, dependency-free immediate-mode UI that implements the subset of the
 * imgui-java API used by Flashback and Axiom. It intentionally keeps the
 * binding classes in place and only replaces their native methods through
 * generated mixins, so the mods' Java code stays untouched.
 *
 * <p>This is not a pixel-perfect Dear ImGui port. Docking is emulated by
 * floating windows, and advanced widgets fall back to sensible defaults. The
 * common widgets, layout, input, font atlas and draw-data pipeline are fully
 * functional.</p>
 */
public final class PureUi {

    public static final Object[] NO_ARGS = new Object[0];

    // ImGuiKey_NamedKey_BEGIN.. indices used by the pure-Java binding. The key
    // values fed to NavState are translated through these in navKeyCode().
    static final int NAV_KEY_TAB = 512;
    static final int NAV_KEY_LEFT = 513;
    static final int NAV_KEY_RIGHT = 514;
    static final int NAV_KEY_UP = 515;
    static final int NAV_KEY_DOWN = 516;
    static final int NAV_KEY_DELETE = 522;
    static final int NAV_KEY_BACKSPACE = 523;
    static final int NAV_KEY_SPACE = 524;
    static final int NAV_KEY_ENTER = 525;
    static final int NAV_KEY_LEFT_SHIFT = 528;
    static final int NAV_KEY_RIGHT_SHIFT = 532;

    private static final boolean DEBUG_WIDGETS = Boolean.getBoolean("noimgui.debug.widgets");
    private static final Map<String, UiContext> CONTEXTS = new ConcurrentHashMap<>();
    private static final Set<String> WARNED = ConcurrentHashMap.newKeySet();
    private static final AtomicLong NEXT_HANDLE = new AtomicLong(1000);

    private PureUi() {
    }

    public static long newNativeHandle() {
        return newHandle();
    }

    public static void onClassInit(String pkg) {
        CONTEXTS.computeIfAbsent(pkg, UiContext::new);
        NoNativeMod.LOGGER.debug("Initialised pure-Java ImGui binding for {}", pkg);
    }

    // ------------------------------------------------------------------
    // Mixin entry points
    // ------------------------------------------------------------------

    private static final java.util.Set<String> TRACED = java.util.concurrent.ConcurrentHashMap.newKeySet();

    public static Object call(String owner, String name, String desc, Object self, Object[] args) {
        try {
            if (Boolean.getBoolean("noimgui.debug.calls")) {
                String key = owner + "." + name + desc;
                if (TRACED.add(key)) {
                    NoNativeMod.LOGGER.info("CALL {}", key);
                }
            }
            return context(owner).dispatch(simplePath(owner), name, desc, self, args);
        } catch (Throwable t) {
            warnOnce(owner + "." + name, t);
            return null;
        }
    }

    public static boolean callBool(String owner, String name, String desc, Object self, Object[] args) {
        Object value = call(owner, name, desc, self, args);
        return value instanceof Boolean b && b;
    }

    public static int callInt(String owner, String name, String desc, Object self, Object[] args) {
        Object value = call(owner, name, desc, self, args);
        if (value instanceof Number n) {
            return n.intValue();
        }
        if (value instanceof Character c) {
            return c;
        }
        return 0;
    }

    public static long callLong(String owner, String name, String desc, Object self, Object[] args) {
        Object value = call(owner, name, desc, self, args);
        return value instanceof Number n ? n.longValue() : 0L;
    }

    public static float callFloat(String owner, String name, String desc, Object self, Object[] args) {
        Object value = call(owner, name, desc, self, args);
        return value instanceof Number n ? n.floatValue() : 0f;
    }

    public static double callDouble(String owner, String name, String desc, Object self, Object[] args) {
        Object value = call(owner, name, desc, self, args);
        return value instanceof Number n ? n.doubleValue() : 0d;
    }

    public static void callVoid(String owner, String name, String desc, Object self, Object[] args) {
        call(owner, name, desc, self, args);
    }

    private static void warnOnce(String key, Throwable t) {
        if (WARNED.add(key)) {
            NoNativeMod.LOGGER.warn("Pure-Java ImGui fallback failed in {}", key, t);
        }
    }

    private static String basePackage(String owner) {
        int idx = owner.indexOf("imgui.moulberry");
        if (idx >= 0) {
            // Stop after "imgui.moulberry90" / "imgui.moulberry92".
            int end = owner.indexOf('.', idx + "imgui.moulberry".length());
            return end < 0 ? owner : owner.substring(0, end);
        }
        return owner;
    }

    private static String simplePath(String owner) {
        String base = basePackage(owner);
        return owner.startsWith(base + ".") ? owner.substring(base.length() + 1) : owner;
    }

    /** Pure-Java replacement for TextEditorLanguage's native factory methods. */
    public static Object textEditorLanguage(String owner, String displayName) {
        UiContext ctx = context(owner);
        long handle = newHandle();
        ctx.handles.put(handle, displayName);
        return ctx.wrapper("extension.texteditor.TextEditorLanguage", handle, displayName);
    }

    private static UiContext context(String owner) {
        return CONTEXTS.computeIfAbsent(basePackage(owner), UiContext::new);
    }

    // ------------------------------------------------------------------
    // Value helpers
    // ------------------------------------------------------------------

    static long newHandle() {
        return NEXT_HANDLE.incrementAndGet();
    }

    static long ptr(Object self) {
        try {
            Object value = Reflect.get(self, "ptr");
            return value instanceof Number n ? n.longValue() : 0L;
        } catch (Throwable t) {
            return 0L;
        }
    }

    static void setPtr(Object self, long ptr) {
        try {
            Reflect.set(self, "ptr", ptr);
        } catch (Throwable ignored) {
        }
    }

    static float f(Object value) {
        return value instanceof Number n ? n.floatValue() : 0f;
    }

    static int i(Object value) {
        return value instanceof Number n ? n.intValue() : 0;
    }

    static boolean b(Object value) {
        return value instanceof Boolean v && v;
    }

    static String s(Object value) {
        return value == null ? "" : value.toString();
    }

    static Object arg(Object[] args, int index) {
        return args != null && index < args.length ? args[index] : null;
    }

    static float argF(Object[] args, int index, float fallback) {
        Object v = arg(args, index);
        return v instanceof Number n ? n.floatValue() : fallback;
    }

    static int argI(Object[] args, int index, int fallback) {
        Object v = arg(args, index);
        return v instanceof Number n ? n.intValue() : fallback;
    }

    static boolean argB(Object[] args, int index, boolean fallback) {
        Object v = arg(args, index);
        return v instanceof Boolean b ? b : fallback;
    }

    static String argS(Object[] args, int index) {
        return s(arg(args, index));
    }

    // ------------------------------------------------------------------
    // Per binding package state
    // ------------------------------------------------------------------

    static final class UiContext {
        final String pkg;
        final IO io = new IO();
        final Style style = new Style();
        Style activeStyle;
        final Viewport viewport = new Viewport();
        final DrawData drawData = new DrawData();
        final FontAtlas atlas = new FontAtlas();
        final Map<Long, Object> handles = new HashMap<>();
        final Map<String, Window> windows = new LinkedHashMap<>();
        final List<Window> windowStack = new ArrayList<>();
        final List<DrawList> frameLists = new ArrayList<>();
        final List<Window> popups = new ArrayList<>();
        final Map<String, Popup> popupMap = new LinkedHashMap<>();
        final DrawList background = new DrawList();
        final DrawList foreground = new DrawList();
        final Map<Integer, int[]> storage = new HashMap<>();

        Object ioObject;
        Object styleObject;
        Object drawDataObject;
        Object viewportObject;
        Object contextObject;
        Object platformIOObject;
        Object atlasObject;
        Object backgroundObject;
        Object foregroundObject;

        int frame;
        double time;
        long lastFrameNanos = System.nanoTime();
        long currentContext;
        long nextDockId;
        int currentDockId;
        int frameCount;
        float globalAlpha = 1f;
        int disabledDepth;
        String iniFilename;
        String backendName = "no-imgui";
        boolean iniLoaded;
        final Map<String, float[]> iniLayout = new HashMap<>();
        final Map<String, Integer> iniDockIds = new HashMap<>();
        final Map<String, Integer> iniDockTabs = new HashMap<>();
        final Map<Long, TextEditorData> textEditors = new HashMap<>();
        final Map<String, InputTextModel> inputModels = new HashMap<>();
        final Map<String, String> inputOriginals = new HashMap<>();
        final Map<Long, FontConfigData> fontConfigs = new HashMap<>();
        final Map<Integer, DockNode> dockNodes = new LinkedHashMap<>();
        final Map<Integer, List<String>> dockWindows = new HashMap<>();
        DockLayout dockLayout;
        int dockRootId;
        float dockRootW = 1, dockRootH = 1;
        float menuBarOffset;
        boolean menuBarSeen;
        int menuLogCount;
        DrawList mainMenuDrawList;
        DockLayout.Node draggingDockNode;
        final Map<Long, Integer> dockNodeHandles = new HashMap<>();
        final Map<Integer, Integer> runtimeDockLocalFlags = new HashMap<>();
        int widgetDebugCount;
        int idDebugCount;
        int imageDebugCount;
        int missingGlyphCount;
        boolean menuBarSubmittedThisFrame;
        boolean menuBarSubmittedLastFrame;
        boolean workSetThisFrame;
        boolean workPosSetThisFrame;
        Window hoveredWindowThisFrame;
        String dockTabPressed;
        String dragDropSourceId;
        String dragDropPayloadType;
        Object dragDropPayload;
        String dragDropTargetId;
        Window pendingChild;
        int draggingDockChild;
        float draggingDockLastX;
        float draggingDockLastY;

        final NavState nav = new NavState();
        final NavState.KeySource navKeys = new NavState.KeySource() {
            @Override
            public boolean isKeyDown(int key) {
                int mapped = navKeyCode(key);
                return mapped >= 0 && io.keysDown.contains(mapped);
            }

            @Override
            public boolean isKeyPressed(int key) {
                int mapped = navKeyCode(key);
                return mapped >= 0 && (io.keysPressed.contains(mapped) || io.keysNextPressed.contains(mapped));
            }

            @Override
            public boolean isShiftDown() {
                return io.shift || io.keysDown.contains(NAV_KEY_LEFT_SHIFT)
                    || io.keysDown.contains(NAV_KEY_RIGHT_SHIFT);
            }
        };

        Window currentWindow;
        DrawList currentDrawList;
        final List<Window> thisFrame = new ArrayList<>();
        List<Window> lastFrame = new ArrayList<>();
        String focusedWindowName;

        int viewportsFlag = -1;
        float nextItemWidth = 0f;
        float itemWidthPushed = 0f;
        float itemWidthPrev = 0f;
        float indent = 0f;
        float textWrapPos = 0f;
        final List<Float> textWrapStack = new ArrayList<>();
        final List<float[]> styleColorStack = new ArrayList<>();
        final List<Style> styleVarStack = new ArrayList<>();
        final List<FontData> fontStack = new ArrayList<>();
        final List<Float> fontSizeStack = new ArrayList<>();
        final List<Integer> idStack = new ArrayList<>();
        final List<String> idStringStack = new ArrayList<>();

        String activeId;
        String hotId;
        String lastItemId;
        float[] lastItemRect = new float[4];
        boolean lastItemHovered;
        boolean lastItemActive;
        boolean lastItemClicked;
        int lastItemClickedButton;
        boolean lastItemEdited;
        boolean lastItemActivated;
        boolean lastItemDeactivated;
        boolean lastItemDeactivatedAfterEdit;

        boolean anyPopupOpen;
        boolean mainBegunThisFrame;
        boolean mainActiveLastFrame;
        int dockSlots;
        String openPopupId;
        float popupX;
        float popupY;
        boolean nextWindowFocus;
        boolean keyboardFocusRequested;
        String keyboardFocusId;
        boolean wantTextInput;
        String activeInput;
        float inputCaretX;

        boolean menuOpen;
        String menuId;
        float menuX;
        float menuY;

        Object nextWindowDockId;
        float nextWindowX = Float.NaN;
        float nextWindowY = Float.NaN;
        float nextWindowW = Float.NaN;
        float nextWindowH = Float.NaN;
        float nextWindowPivotX = 0f;
        float nextWindowPivotY = 0f;
        int nextWindowCond;
        int nextWindowSizeCond;
        float nextScrollX = Float.NaN;
        float nextContentW = Float.NaN;
        float nextContentH = Float.NaN;
        float nextScrollY = Float.NaN;
        float nextWindowBgAlpha = 1f;
        float nextMinW, nextMinH, nextMaxW, nextMaxH;
        Boolean nextCollapsed;
        boolean nextWindowPosUndock;

        Object tempObject;

        UiContext(String pkg) {
            this.pkg = pkg;
        }

        // --------------------------------------------------------------
        // Wrappers
        // --------------------------------------------------------------

        Class<?> clazz(String simplePath) {
            try {
                return Class.forName(this.pkg + "." + simplePath);
            } catch (ClassNotFoundException e) {
                throw new IllegalStateException(e);
            }
        }

        Object wrapper(String simplePath, long handle, Object data) {
            this.handles.put(handle, data);
            return Reflect.construct(clazz(simplePath), new Class<?>[]{long.class}, handle);
        }

        long handle(Object self, Object data) {
            long handle = ptr(self);
            if (handle == 0) {
                handle = newHandle();
                setPtr(self, handle);
            }
            this.handles.put(handle, data);
            return handle;
        }

        Object data(Object self) {
            return this.handles.get(ptr(self));
        }

        Object vec2(float x, float y) {
            try {
                return Reflect.construct(clazz("ImVec2"), new Class<?>[]{float.class, float.class}, x, y);
            } catch (RuntimeException e) {
                Object v = Reflect.construct(clazz("ImVec2"), new Class<?>[0]);
                Reflect.set(v, "x", x);
                Reflect.set(v, "y", y);
                return v;
            }
        }

        Object vec4(float x, float y, float z, float w) {
            try {
                return Reflect.construct(clazz("ImVec4"), new Class<?>[]{float.class, float.class, float.class, float.class}, x, y, z, w);
            } catch (RuntimeException e) {
                Object v = Reflect.construct(clazz("ImVec4"), new Class<?>[0]);
                Reflect.set(v, "x", x);
                Reflect.set(v, "y", y);
                Reflect.set(v, "z", z);
                Reflect.set(v, "w", w);
                return v;
            }
        }

        void readVec2(Object vec, float[] out) {
            if (vec == null) {
                return;
            }
            out[0] = f(Reflect.get(vec, "x"));
            out[1] = f(Reflect.get(vec, "y"));
        }

        int imHashStr(String value) {
            int crc = 0xFFFFFFFF;
            for (int i = 0; i < value.length(); i++) {
                crc = (crc >>> 8) ^ CRC32_TABLE[(crc ^ value.charAt(i)) & 0xFF];
            }
            return ~crc;
        }

        /** imgui.ini section key: the full window name (native saves Name). */
        String iniKey(String name) {
            return name;
        }

        /** ImGui ID label: the part after the last "###" (or the full name). */
        String labelKey(String name) {
            int idx = name.lastIndexOf("###");
            return idx >= 0 ? name.substring(idx) : name;
        }

        /** ImGui rendered text end: everything from the first "##" is hidden. */
        String visibleText(String text) {
            if (text == null) return "";
            int idx = text.indexOf("##");
            return idx < 0 ? text : text.substring(0, idx);
        }

        /** Human-readable window/tab label. A leading "###" is Axiom's ini key. */
        String displayLabel(String name) {
            if (name.startsWith("###")) return name.substring(3);
            int idx = name.indexOf("##");
            return idx < 0 ? name : name.substring(0, idx);
        }

        Object ioObject() {
            if (this.ioObject == null) {
                this.ioObject = wrapper("ImGuiIO", 1L, this.io);
            }
            return this.ioObject;
        }

        Object styleObject() {
            if (this.styleObject == null) {
                this.styleObject = wrapper("ImGuiStyle", 2L, this.style);
            }
            return this.styleObject;
        }

        Object drawDataObject() {
            if (this.drawDataObject == null) {
                this.drawDataObject = wrapper("ImDrawData", 3L, this.drawData);
            }
            return this.drawDataObject;
        }

        Object viewportObject() {
            if (this.viewportObject == null) {
                this.viewportObject = wrapper("ImGuiViewport", 4L, this.viewport);
            }
            return this.viewportObject;
        }

        Object contextObject() {
            if (this.contextObject == null) {
                this.contextObject = wrapper("internal.ImGuiContext", 5L, this);
            }
            return this.contextObject;
        }

        Object platformIOObject() {
            if (this.platformIOObject == null) {
                this.platformIOObject = wrapper("ImGuiPlatformIO", 6L, this);
            }
            return this.platformIOObject;
        }

        Object atlasObject() {
            if (this.atlasObject == null) {
                this.atlasObject = wrapper("ImFontAtlas", 7L, this.atlas);
            }
            return this.atlasObject;
        }

        Object backgroundObject() {
            if (this.backgroundObject == null) {
                this.backgroundObject = wrapper("ImDrawList", 8L, this.background);
            }
            return this.backgroundObject;
        }

        Object foregroundObject() {
            if (this.foregroundObject == null) {
                this.foregroundObject = wrapper("ImDrawList", 9L, this.foreground);
            }
            return this.foregroundObject;
        }

        // --------------------------------------------------------------
        // Dispatch
        // --------------------------------------------------------------

        Object dispatch(String simplePath, String name, String desc, Object self, Object[] args) {
            String simple = simplePath.substring(simplePath.lastIndexOf('.') + 1);
            switch (simple) {
                case "ImGui" -> {
                    return imgui(simplePath, name, desc, self, args);
                }
                case "ImGuiIO" -> {
                    return io(simplePath, name, desc, self, args);
                }
                case "ImGuiStyle" -> {
                    return style(simplePath, name, desc, self, args);
                }
                case "ImDrawList" -> {
                    return drawList(simple, name, desc, self, args);
                }
                case "ImDrawData" -> {
                    return drawData(simple, name, desc, self, args);
                }
                case "ImFontAtlas" -> {
                    return fontAtlas(simple, name, desc, self, args);
                }
                case "ImFont" -> {
                    return font(simple, name, desc, self, args);
                }
                case "ImGuiViewport" -> {
                    return viewport(simple, name, desc, self, args);
                }
                case "ImGuiPlatformIO" -> {
                    return null;
                }
                case "ImGuiStorage" -> {
                    return storage(simple, name, desc, self, args);
                }
                case "ImGuiListClipper" -> {
                    return listClipper(simple, name, desc, self, args);
                }
                case "ImGuiInputTextCallbackData" -> {
                    return inputTextData(simple, name, desc, self, args);
                }
                case "TextEditor" -> {
                    return textEditor(simple, name, desc, self, args);
                }
                case "ImFontConfig" -> {
                    return fontConfig(simple, name, desc, self, args);
                }
                case "TextEditorLanguage" -> {
                    String factory = switch (name) {
                        case "C", "Cpp", "Cs", "AngelScript", "Lua", "Python",
                             "Glsl", "Hlsl", "Json", "Markdown", "Sql" -> name;
                        default -> null;
                    };
                    if (factory != null) {
                        String display = switch (factory) {
                            case "Cpp" -> "C++";
                            case "Cs" -> "C#";
                            case "Glsl" -> "GLSL";
                            case "Hlsl" -> "HLSL";
                            case "Json" -> "JSON";
                            case "Sql" -> "SQL";
                            default -> factory;
                        };
                        return textEditorLanguage(this.pkg + ".extension.texteditor.TextEditorLanguage", display);
                    }
                    Object value = self == null ? null : data(self);
                    if (name.equals("getName") || name.equals("toString")) return value == null ? "" : value.toString();
                    if (name.equals("getLanguageName")) return value == null ? "" : value.toString();
                    return null;
                }
                case "ImGuiDockNode" -> {
                    return dockNodeMethod(name, self, args);
                }
                case "ImGuiTableSortSpecs" -> {
                    Table table = self == null ? null : (Table) data(self);
                    if (table == null) return null;
                    if (name.equals("getSpecsCount") || name.equals("getSpecsCountInt")) return table.sortColumn < 0 ? 0 : 1;
                    if (name.equals("getSpecsDirty")) return table.specsDirty;
                    if (name.equals("setSpecsDirty")) { table.specsDirty = argB(args, 0, false); return null; }
                    if (name.equals("getSpecs")) {
                        if (table.sortColumn < 0) return java.lang.reflect.Array.newInstance(clazz("ImGuiTableColumnSortSpecs"), 0);
                        Object spec = tableColumnSortSpec(table, 0);
                        Object array = java.lang.reflect.Array.newInstance(clazz("ImGuiTableColumnSortSpecs"), 1);
                        java.lang.reflect.Array.set(array, 0, spec);
                        return array;
                    }
                    return null;
                }
                case "ImGuiTableColumnSortSpecs" -> {
                    Table table = self == null ? null : (Table) data(self);
                    if (table == null) return null;
                    return switch (name) {
                        case "getColumnUserID" -> table.sortUserData;
                        case "getColumnIndex" -> Math.max(0, table.sortColumn);
                        case "getSortOrder" -> 0;
                        case "getSortDirection" -> table.sortDirection;
                        default -> null;
                    };
                }
                default -> {
                    return null;
                }
            }
        }

        // --------------------------------------------------------------
        // ImGui core
        // --------------------------------------------------------------

        Object imgui(String simplePath, String name, String desc, Object self, Object[] args) {
            switch (name) {
                case "getIO": return ioObject();
                case "getStyle": return styleObject();
                case "getDrawData": return drawDataObject();
                case "getMainViewport": return viewportObject();
                case "getCurrentContext": return contextObject();
                case "createContext": return contextObject();
                case "destroyContext": return null;
                case "setCurrentContext": return null;
                case "getPlatformIO": return platformIOObject();
                case "init": return null;
                case "newFrame": newFrame(); return null;
                case "render": render(); return null;
                case "endFrame": return null;
                case "getFrameCount": return this.frameCount;
                case "getTime": return this.time;

                case "begin":
                    if (args.length >= 2 && !(arg(args, 1) instanceof Number)) {
                        return beginWithOpen(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                    }
                    return begin(argS(args, 0), argI(args, 1, 0));
                case "end": end(); return null;
                case "beginChild": return beginChild(argS(args, 0), argF(args, 1, 0), argF(args, 2, 0), argI(args, 3, 0));
                case "endChild": endChild(); return null;
                case "beginGroup": beginGroup(); return null;
                case "endGroup": endGroup(); return null;

                case "setNextWindowPos": {
                    this.nextWindowPosUndock = true;
                    Object first = arg(args, 0);
                    if (first != null && first.getClass().getSimpleName().equals("ImVec2")) {
                        this.nextWindowX = f(Reflect.get(first, "x"));
                        this.nextWindowY = f(Reflect.get(first, "y"));
                        this.nextWindowCond = argI(args, 1, 0);
                        Object pivot = arg(args, 2);
                        if (pivot != null && pivot.getClass().getSimpleName().equals("ImVec2")) {
                            this.nextWindowPivotX = f(Reflect.get(pivot, "x"));
                            this.nextWindowPivotY = f(Reflect.get(pivot, "y"));
                        }
                    } else {
                        this.nextWindowX = argF(args, 0, 0);
                        this.nextWindowY = argF(args, 1, 0);
                        this.nextWindowCond = argI(args, 2, 0);
                        if (args.length >= 5) {
                            this.nextWindowPivotX = argF(args, 3, 0);
                            this.nextWindowPivotY = argF(args, 4, 0);
                        }
                    }
                    return null;
                }
                case "setNextWindowSize": {
                    Object first = arg(args, 0);
                    if (first != null && first.getClass().getSimpleName().equals("ImVec2")) {
                        this.nextWindowW = f(Reflect.get(first, "x"));
                        this.nextWindowH = f(Reflect.get(first, "y"));
                        this.nextWindowSizeCond = argI(args, 1, 0);
                    } else {
                        this.nextWindowW = argF(args, 0, 0);
                        this.nextWindowH = argF(args, 1, 0);
                        this.nextWindowSizeCond = argI(args, 2, 0);
                    }
                    return null;
                }
                case "setNextWindowSizeConstraints":
                    this.nextMinW = argF(args, 0, 0);
                    this.nextMinH = argF(args, 1, 0);
                    this.nextMaxW = argF(args, 2, Float.MAX_VALUE);
                    this.nextMaxH = argF(args, 3, Float.MAX_VALUE);
                    return null;
                case "setNextWindowBgAlpha": this.nextWindowBgAlpha = argF(args, 0, 1f); return null;
                case "setNextWindowDockID": this.nextWindowDockId = arg(args, 0); return null;
                case "setNextWindowFocus": this.nextWindowFocus = true; return null;
                case "setNextWindowContentSize":
                    // Auto-resizing windows use their content size; store the hint.
                    this.nextContentW = argF(args, 0, 0);
                    this.nextContentH = argF(args, 1, 0);
                    return null;
                case "setNextWindowScroll":
                    this.nextScrollX = argF(args, 0, Float.NaN);
                    this.nextScrollY = argF(args, 1, Float.NaN);
                    return null;
                case "getWindowDockNode": return currentWindow().dockId == 0 ? null : dockNode(currentWindow().dockId);
                case "setNextWindowCollapsed": this.nextCollapsed = argB(args, 0, false); return null;
                case "setNextWindowClass": return null;
                case "getWindowPos": return vec2(currentWindow().x, currentWindow().y);
                case "getWindowPosX": return currentWindow().x;
                case "getWindowPosY": return currentWindow().y;
                case "getWindowSize": return vec2(currentWindow().w, currentWindow().h);
                case "getWindowSizeX": return currentWindow().w;
                case "getWindowSizeY": return currentWindow().h;
                case "getWindowWidth": return currentWindow().w;
                case "getWindowHeight": return currentWindow().h;
                case "getWindowContentRegionMin": return vec2(currentWindow().contentX, currentWindow().contentY);
                case "getWindowContentRegionMax": return vec2(currentWindow().w - this.style.windowPaddingX, currentWindow().h - this.style.windowPaddingY);
                case "getWindowContentRegionMinX": return currentWindow().contentX;
                case "getWindowContentRegionMinY": return currentWindow().contentY;
                case "getWindowContentRegionMaxX": return currentWindow().contentX + currentWindow().contentW;
                case "getWindowContentRegionMaxY": return currentWindow().contentY + currentWindow().contentH;
                case "getContentRegionAvail": return vec2(contentAvailX(), contentAvailY());
                case "getContentRegionAvailX": return contentAvailX();
                case "getContentRegionAvailY": return contentAvailY();
                case "getWindowDrawList": return windowDrawList();
                case "getWindowViewport": return viewportObject();
                case "setWindowFocus": this.focusedWindowName = currentWindow().name; return null;
                case "getMousePosOnOpeningCurrentPopup": return vec2(this.io.mouseX, this.io.mouseY);
                case "getMousePosOnOpeningCurrentPopupX": return this.io.mouseX;
                case "getMousePosOnOpeningCurrentPopupY": return this.io.mouseY;
                case "isMouseHoveringRect":
                    if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec2")
                        && arg(args, 1) != null && arg(args, 1).getClass().getSimpleName().equals("ImVec2")) {
                        Object a = arg(args, 0), b = arg(args, 1);
                        return this.io.mouseX >= f(Reflect.get(a, "x")) && this.io.mouseX <= f(Reflect.get(b, "x"))
                            && this.io.mouseY >= f(Reflect.get(a, "y")) && this.io.mouseY <= f(Reflect.get(b, "y"));
                    }
                    return this.io.mouseX >= argF(args, 0, 0) && this.io.mouseX <= argF(args, 2, 0)
                        && this.io.mouseY >= argF(args, 1, 0) && this.io.mouseY <= argF(args, 3, 0);
                case "getBackgroundDrawList": return backgroundObject();
                case "getForegroundDrawList": return foregroundObject();
                case "getWindowDockID": return currentWindow().dockId;
                case "getWindowDpiScale": return 1f;
                case "isWindowDocked": return currentWindow().dockId != 0;
                case "isWindowFocused": return currentWindow().name.equals(this.focusedWindowName);
                case "isWindowHovered": return currentWindow().hovered;
                case "isWindowCollapsed": return currentWindow().collapsed;
                case "isWindowAppearing": return currentWindow().appearing;
                case "isAnyWindowHovered": return this.windows.values().stream().anyMatch(w -> w.hovered);
                case "getScrollY": return currentWindow().scrollY;
                case "getScrollMaxY": return currentWindow().scrollMaxY;
                case "getScrollMaxX": return currentWindow().scrollMaxX;
                case "setScrollY": currentWindow().scrollY = Math.max(0, argF(args, 0, 0)); return null;
                case "setScrollHereY": return null;
                case "setScrollFromPosY": return null;
                case "scrollToItem": return null;
                case "scrollToRect": return null;
                case "scrollToRectEx": return vec2(0, 0);
                case "setScrollX": currentWindow().scrollX = Math.max(0, argF(args, 0, 0)); return null;
                case "getScrollX": return currentWindow().scrollX;
                case "setNextWindowViewport": return null;
                case "tabItemButton": return button(argS(args, 0), 0, 0);
                case "getCursorPos": return vec2(currentWindow().cursorX, currentWindow().cursorY);
                case "getCursorPosX": return currentWindow().cursorX;
                case "getCursorPosY": return currentWindow().cursorY;
                case "setCursorPos": currentWindow().cursorX = argF(args, 0, 0); currentWindow().cursorY = argF(args, 1, 0); return null;
                case "setCursorPosX": currentWindow().cursorX = argF(args, 0, 0); return null;
                case "setCursorPosY": currentWindow().cursorY = argF(args, 0, 0); return null;
                case "getCursorStartPos": return vec2(currentWindow().contentX, currentWindow().contentY - currentWindow().scrollY);
                case "getCursorStartPosX": return currentWindow().contentX;
                case "getCursorStartPosY": return currentWindow().contentY - currentWindow().scrollY;
                case "getCursorScreenPos": return vec2(currentWindow().x + currentWindow().cursorX - currentWindow().scrollX, currentWindow().y + currentWindow().cursorY - currentWindow().scrollY);
                case "getCursorScreenPosX": return currentWindow().x + currentWindow().cursorX - currentWindow().scrollX;
                case "getCursorScreenPosY": return currentWindow().y + currentWindow().cursorY - currentWindow().scrollY;
                case "setCursorScreenPos": currentWindow().cursorX = argF(args, 0, 0) - currentWindow().x; currentWindow().cursorY = argF(args, 1, 0) - currentWindow().y + currentWindow().scrollY; return null;
                case "getTextLineHeight": return currentFontSize();
                case "getTextLineHeightWithSpacing": return currentFontSize() + this.style.itemSpacingY;
                case "getFrameHeight": return currentFontSize() + this.style.framePaddingY * 2f;
                case "getFrameHeightWithSpacing": return frameHeight() + this.style.itemSpacingY;
                case "getFontSize": return currentFontSize();
                case "getFont": return this.atlas.currentFontObject();
                case "pushFont": {
                    Object fontObject = arg(args, 0);
                    FontData fontData = fontObject == null ? null : (FontData) data(fontObject);
                    // Always push, even for an unknown font object: PopFont() is
                    // unconditional, so a skipped push would unbalance the stack
                    // and shrink/change text sizes later.
                    this.fontStack.add(this.atlas.current);
                    this.fontSizeStack.add(this.style.fontSize);
                    if (fontData != null) {
                        this.atlas.current = fontData;
                        if (args.length > 1 && arg(args, 1) instanceof Number n) {
                            this.style.fontSize = n.floatValue();
                        } else if (fontData.size > 0) {
                            this.style.fontSize = fontData.size;
                        }
                    } else if (args.length > 1 && arg(args, 1) instanceof Number n) {
                        this.style.fontSize = n.floatValue();
                    }
                    if (this.currentDrawList != null) this.currentDrawList.textSize = this.style.fontSize;
                    return null;
                }
                case "popFont":
                    if (!this.fontStack.isEmpty()) {
                        this.atlas.current = this.fontStack.remove(this.fontStack.size() - 1);
                        if (!this.fontSizeStack.isEmpty()) {
                            this.style.fontSize = this.fontSizeStack.remove(this.fontSizeStack.size() - 1);
                        }
                        if (this.currentDrawList != null) this.currentDrawList.textSize = this.style.fontSize;
                    }
                    return null;
                case "setFont": {
                    Object fontObject = arg(args, 0);
                    FontData fontData = fontObject == null ? null : (FontData) data(fontObject);
                    if (fontData != null) {
                        this.atlas.current = fontData;
                        if (fontData.size > 0) this.style.fontSize = fontData.size;
                        if (this.currentDrawList != null) this.currentDrawList.textSize = this.style.fontSize;
                    }
                    return null;
                }
                case "pushItemWidth":
                    this.itemWidthPrev = this.itemWidthPushed;
                    this.itemWidthPushed = argF(args, 0, 0);
                    return null;
                case "popItemWidth":
                    this.itemWidthPushed = this.itemWidthPrev;
                    this.itemWidthPrev = 0;
                    return null;
                case "setNextItemWidth": this.nextItemWidth = argF(args, 0, 0); return null;
                case "calcItemWidth": return calcItemWidthValue();
                case "pushTextWrapPos": this.textWrapStack.add(this.textWrapPos); this.textWrapPos = argF(args, 0, 0); return null;
                case "popTextWrapPos": this.textWrapPos = this.textWrapStack.isEmpty() ? 0 : this.textWrapStack.remove(this.textWrapStack.size() - 1); return null;
                case "indent":
                    this.indent += argF(args, 0, this.style.indentSpacing);
                    currentWindow().lineStartX = currentWindow().contentX + this.indent;
                    currentWindow().cursorX = currentWindow().lineStartX;
                    return null;
                case "unindent":
                    this.indent = Math.max(0, this.indent - argF(args, 0, this.style.indentSpacing));
                    currentWindow().lineStartX = currentWindow().contentX + this.indent;
                    currentWindow().cursorX = currentWindow().lineStartX;
                    return null;
                case "pushID": this.idStringStack.add(argS(args, 0)); return null;
                case "popID": if (!this.idStringStack.isEmpty()) this.idStringStack.remove(this.idStringStack.size() - 1); return null;
                case "getID": return argS(args, 0).hashCode();
                case "sameLine": sameLine(argF(args, 0, 0), argF(args, 1, -1)); return null;
                case "newLine": newLine(); return null;
                case "spacing": itemSize(0, this.style.itemSpacingY); return null;
                case "dummy": itemSize(argF(args, 0, 0), argF(args, 1, 0)); return null;
                case "alignTextToFramePadding": return null;
                case "beginDisabled":
                    if (argB(args, 0, true)) {
                        this.disabledDepth++;
                        this.globalAlpha *= 0.55f;
                    }
                    return null;
                case "endDisabled":
                    if (this.disabledDepth > 0) {
                        this.disabledDepth--;
                        this.globalAlpha = this.disabledDepth > 0 ? 0.55f : 1f;
                    }
                    return null;

                case "text": text(argS(args, 0)); return null;
                case "textUnformatted": text(argS(args, 0)); return null;
                case "textWrapped": textWrapped(argS(args, 0)); return null;
                case "textColored":
                    if (args.length <= 2 && arg(args, 0) instanceof Number n) {
                        int packed = n.intValue();
                        textColored((packed & 0xFF) / 255f, ((packed >> 8) & 0xFF) / 255f,
                            ((packed >> 16) & 0xFF) / 255f, ((packed >> 24) & 0xFF) / 255f, argS(args, 1));
                    } else if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec4")) {
                        Object c = arg(args, 0);
                        textColored(f(Reflect.get(c, "x")), f(Reflect.get(c, "y")), f(Reflect.get(c, "z")), f(Reflect.get(c, "w")), argS(args, 1));
                    } else {
                        textColored(argF(args, 0, 1), argF(args, 1, 1), argF(args, 2, 1), argF(args, 3, 1), argS(args, 4));
                    }
                    return null;
                case "textDisabled": textColored(0.55f, 0.55f, 0.55f, 1f, argS(args, 0)); return null;
                case "labelText": text(argS(args, 0) + ": " + argS(args, 1)); return null;
                case "bulletText": text("\u2022 " + argS(args, 0)); return null;
                case "separator": separator(); return null;
                case "separatorText": separatorText(argS(args, 0)); return null;
                case "button": return button(argS(args, 0), argF(args, 1, 0), argF(args, 2, 0));
                case "smallButton": return smallButton(argS(args, 0));
                case "invisibleButton": return invisibleButton(argS(args, 0), argF(args, 1, 0), argF(args, 2, 0));
                case "checkbox": return checkbox(argS(args, 0), arg(args, 1));
                case "radioButton": return radioButton(argS(args, 0), argB(args, 1, false));
                case "selectable": return selectable(argS(args, 0), argB(args, 1, false), argI(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0));
                case "sliderFloat": return sliderFloat(argS(args, 0), arg(args, 1), argF(args, 2, 0), argF(args, 3, 1), argS(args, 4));
                case "sliderInt": return sliderInt(argS(args, 0), arg(args, 1), argI(args, 2, 0), argI(args, 3, 100), argS(args, 4));
                case "dragFloat": return sliderFloat(argS(args, 0), arg(args, 1), argF(args, 2, 0), argF(args, 3, 1), argS(args, 4));
                case "dragInt": return sliderInt(argS(args, 0), arg(args, 1), argI(args, 2, 0), argI(args, 3, 100), argS(args, 4));
                case "inputText": return inputText(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "inputTextWithHint": return inputText(argS(args, 0), arg(args, 2), argI(args, 3, 0));
                case "inputFloat": return inputNumber(argS(args, 0), arg(args, 1), false);
                case "inputInt": return inputNumber(argS(args, 0), arg(args, 1), true);
                case "inputDouble": return inputNumber(argS(args, 0), arg(args, 1), false);
                case "inputTextMultiline": return inputText(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "beginCombo": return beginCombo(argS(args, 0), argS(args, 1), argI(args, 2, 0));
                case "endCombo": endCombo(); return null;
                case "combo": return combo(argS(args, 0), argI(args, 1, 0), arg(args, 2), argI(args, 3, -1));
                case "collapsingHeader": return collapsingHeader(argS(args, 0), argI(args, 1, 0));
                case "treeNode": return treeNode(argS(args, 0));
                case "treePush": return null;
                case "treePop": return null;
                case "progressBar": progressBar(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argS(args, 3)); return null;
                case "colorButton": return colorButton(argS(args, 0), arg(args, 1), argI(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0));
                case "image": image(arg(args, 0), arg(args, 1), arg(args, 2), arg(args, 3), argI(args, 4, 0xFFFFFFFF)); return null;
                case "imageButton": return imageButton(argS(args, 0), arg(args, 1), arg(args, 2), arg(args, 3), arg(args, 4), argI(args, 5, 0), argI(args, 6, 0xFFFFFFFF));
                case "treeNodeEx": return treeNodeEx(argS(args, 0), argI(args, 1, 0));
                case "colorPicker3": return colorPicker(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "colorPicker4": return colorPicker(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "colorEdit3": return colorPicker(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "colorEdit4": return colorPicker(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "beginMenuBar": return beginMenuBar();
                case "endMenuBar": endMenuBar(); return null;
                case "beginMainMenuBar": return beginMainMenuBar();
                case "endMainMenuBar": endMainMenuBar(); return null;
                case "beginMenu": return beginMenu(argS(args, 0), argB(args, 1, true));
                case "endMenu": endMenu(); return null;
                case "menuItem": return menuItem(argS(args, 0), argS(args, 1), argB(args, 2, false), argB(args, 3, true));
                case "openPopup": openPopup(argS(args, 0)); return null;
                case "beginPopup": return beginPopup(argS(args, 0), argI(args, 1, 0));
                case "beginPopupModal": return beginPopupModal(argS(args, 0), arg(args, 1), argI(args, 2, 0));
                case "endPopup": endPopup(); return null;
                case "closeCurrentPopup": closeCurrentPopup(); return null;
                case "isPopupOpen": return isPopupOpen(argS(args, 0), argI(args, 1, 0));
                case "beginTooltip": return beginTooltip();
                case "endTooltip": endTooltip(); return null;
                case "setTooltip": setTooltip(argS(args, 0)); return null;
                case "setItemTooltip": setItemTooltip(argS(args, 0)); return null;
                case "beginItemTooltip": return beginItemTooltip();
                case "pushStyleColor": pushStyleColor(args); return null;
                case "popStyleColor": popStyleColor(argI(args, 0, 1)); return null;
                case "pushStyleVar": pushStyleVar(args); return null;
                case "popStyleVar": popStyleVar(argI(args, 0, 1)); return null;
                case "getColorU32": return getColorU32(args);
                case "getStyleColorVec4": return colorVec(argI(args, 0, 0));
                case "getStyleColorName": return "Color" + argI(args, 0, 0);
                case "getVersion": return "no-imgui";
                case "colorConvertU32ToFloat4": return colorConvertU32(argI(args, 0, 0));
                case "colorConvertFloat4ToU32":
                    Object cv = arg(args, 0);
                    if (cv != null && cv.getClass().getSimpleName().equals("ImVec4")) {
                        return colorConvertFloat4(f(Reflect.get(cv, "x")), f(Reflect.get(cv, "y")),
                            f(Reflect.get(cv, "z")), f(Reflect.get(cv, "w")));
                    }
                    return colorConvertFloat4(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 1));
                case "colorConvertRGBtoHSV": colorConvertRGBtoHSV(args); return null;
                case "colorConvertHSVtoRGB": colorConvertHSVtoRGB(args); return null;
                case "calcTextSize":
                    if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec2")) {
                        Object out = arg(args, 0);
                        Object size = calcTextSize(argS(args, 1), arg(args, 2), argB(args, 3, true), argF(args, 4, -1));
                        Reflect.set(out, "x", f(Reflect.get(size, "x")));
                        Reflect.set(out, "y", f(Reflect.get(size, "y")));
                        return null;
                    }
                    return calcTextSize(argS(args, 0), arg(args, 1), argB(args, 2, true), argF(args, 3, -1));
                case "calcTextSizeX": return f(Reflect.get(calcTextSize(argS(args, 0), arg(args, 1), argB(args, 2, true), argF(args, 3, -1)), "x"));
                case "calcTextSizeY": return f(Reflect.get(calcTextSize(argS(args, 0), arg(args, 1), argB(args, 2, true), argF(args, 3, -1)), "y"));
                case "getItemRectMin": return vec2(this.lastItemRect[0], this.lastItemRect[1]);
                case "getItemRectMinX": return this.lastItemRect[0];
                case "getItemRectMinY": return this.lastItemRect[1];
                case "getItemRectMax": return vec2(this.lastItemRect[2], this.lastItemRect[3]);
                case "getItemRectMaxX": return this.lastItemRect[2];
                case "getItemRectMaxY": return this.lastItemRect[3];
                case "getItemRectSize": return vec2(this.lastItemRect[2] - this.lastItemRect[0], this.lastItemRect[3] - this.lastItemRect[1]);
                case "getItemRectSizeX": return this.lastItemRect[2] - this.lastItemRect[0];
                case "getItemRectSizeY": return this.lastItemRect[3] - this.lastItemRect[1];
                case "isItemHovered": {
                    if (this.disabledDepth > 0 && (argI(args, 0, 0) & 512) == 0) return false;
                    return this.lastItemHovered;
                }
                case "isItemActive": return this.lastItemActive;
                case "isItemClicked": return args.length == 0
                    ? this.lastItemClicked
                    : this.lastItemClicked && argI(args, 0, 0) == this.lastItemClickedButton;
                case "isItemEdited": return this.lastItemEdited;
                case "isItemActivated": return this.lastItemActivated;
                case "isItemDeactivated": return this.lastItemDeactivated;
                case "isItemDeactivatedAfterEdit": return this.lastItemDeactivatedAfterEdit;
                case "isItemVisible": {
                    Window cw = currentWindow();
                    if (cw == null) return true;
                    return this.lastItemRect[0] < cw.drawList.clipMaxX
                        && this.lastItemRect[1] < cw.drawList.clipMaxY
                        && this.lastItemRect[2] > cw.drawList.clipMinX
                        && this.lastItemRect[3] > cw.drawList.clipMinY;
                }
                case "setItemDefaultFocus": return null;
                case "setKeyboardFocusHere": this.keyboardFocusRequested = true; return null;
                case "isItemFocused": return this.lastItemId != null
                    && (this.lastItemId.equals(this.keyboardFocusId)
                        || this.nav.isFocused(navItemId(this.lastItemId)));
                case "isAnyItemHovered": return this.lastItemHovered;
                case "isAnyItemActive": return this.activeId != null;
                case "isAnyItemFocused": return this.keyboardFocusId != null || this.nav.focusedId() != NavState.NO_ID;
                case "isKeyDown": return this.io.keysDown.contains(argI(args, 0, 0));
                case "isKeyPressed":
                    if (args.length > 1 && argB(args, 1, false)) return this.io.keysDown.contains(argI(args, 0, 0));
                    return this.io.keysPressed.contains(argI(args, 0, 0));
                case "isKeyReleased": return this.io.keysReleased.contains(argI(args, 0, 0));
                case "isKeyChordPressed": return this.io.keysPressed.contains(argI(args, 0, 0));
                case "getKeyName": return "Key" + argI(args, 0, 0);
                case "isMouseDown": return this.io.mouseDown[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "isMouseClicked":
                    if (args.length > 1 && argB(args, 1, false)) return this.io.mouseDown[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                    return this.io.mousePressed[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "isMouseReleased": return this.io.mouseReleased[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "isMouseDoubleClicked": return false;
                case "isMouseDragging": return this.io.mouseDown[argI(args, 0, 0)] && this.io.dragDistance(argI(args, 0, 0)) > 1;
                case "isAnyMouseDown": return this.io.anyMouseDown();
                case "getMousePos": return vec2(this.io.mouseX, this.io.mouseY);
                case "getMousePosX": return this.io.mouseX;
                case "getMousePosY": return this.io.mouseY;
                case "getMouseDragDelta": return vec2(this.io.dragX[Math.max(0, Math.min(4, argI(args, 0, 0)))], this.io.dragY[Math.max(0, Math.min(4, argI(args, 0, 0)))]);
                case "getMouseDragDeltaX": return this.io.dragX[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "getMouseDragDeltaY": return this.io.dragY[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "resetMouseDragDelta": this.io.dragX[argI(args, 0, 0)] = 0; this.io.dragY[argI(args, 0, 0)] = 0; return null;
                case "getMouseCursor": return this.io.mouseCursor;
                case "setMouseCursor": this.io.mouseCursor = argI(args, 0, 0); return null;
                case "setNextFrameWantCaptureMouse": this.io.nextWantCaptureMouse = argB(args, 0, false) ? 1 : 0; return null;
                case "setNextFrameWantCaptureKeyboard": this.io.nextWantCaptureKeyboard = argB(args, 0, false) ? 1 : 0; return null;
                case "getClipboardText": return this.io.clipboard();
                case "setClipboardText": this.io.setClipboard(argS(args, 0)); return null;
                case "loadIniSettingsFromDisk": this.iniFilename = argS(args, 0); return null;
                case "loadIniSettingsFromMemory": return null;
                case "saveIniSettingsToDisk": return null;
                case "saveIniSettingsToMemory": return "";
                case "debugTextEncoding": return null;
                case "showDemoWindow": return null;
                case "showAboutWindow": return null;
                case "showMetricsWindow": return null;
                case "showStyleEditor": return null;
                case "showUserGuide": return null;
                case "styleColorsDark": styleFor(arg(args, 0)).colorsDark(); return null;
                case "styleColorsLight": styleFor(arg(args, 0)).colorsLight(); return null;
                case "styleColorsClassic": styleFor(arg(args, 0)).colorsClassic(); return null;
                case "dockSpaceOverViewport": {
                    int dsId = argI(args, 0, 0);
                    if (dsId == 0) dsId = this.dockRootId;
                    layoutDockNodes();
                    return dsId;
                }
                case "dockSpace":
                    layoutDockNodes();
                    return argI(args, 0, 1);
                case "dockBuilderGetCentralNode": {
                    DockLayout.Node node = resolveDockLeaf(argI(args, 0, 0));
                    return dockNode(node != null ? node.id() : argI(args, 0, 0));
                }
                case "dockBuilderGetNode": return dockNode(argI(args, 0, 0));
                case "dockBuilderAddNode": return argI(args, 0, 1);
                case "dockBuilderDockWindow": return null;
                case "dockBuilderRemoveNode": return null;
                case "dockBuilderRemoveNodeDockedWindows": return null;
                case "dockBuilderSetNodePos": return null;
                case "dockBuilderSetNodeSize": return null;
                case "dockBuilderSplitNode": return argI(args, 0, 1);
                case "dockBuilderFinish": return null;
                case "beginTable": return beginTable(argS(args, 0), argI(args, 1, 1), argI(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0));
                case "endTable": endTable(); return null;
                case "tableSetupColumn": tableSetupColumn(argS(args, 0), argI(args, 1, 0), argF(args, 2, 0), argI(args, 3, 0)); return null;
                case "tableHeadersRow": tableHeadersRow(); return null;
                case "tableNextRow": tableNextRow(argI(args, 0, 0), argF(args, 1, 0)); return null;
                case "tableNextColumn": return tableNextColumn();
                case "tableSetColumnIndex": return tableSetColumnIndex(argI(args, 0, 0));
                case "tableSetupScrollFreeze": {
                    Window tw = currentWindow();
                    if (tw.table != null && tw.table.layout != null) {
                        tw.table.layout.setupScrollFreeze(argI(args, 0, 0), argI(args, 1, 0));
                    }
                    return null;
                }
                case "tableSetColumnWidth": return null;
                case "tableGetColumnCount": return currentWindow().table == null ? 1 : currentWindow().table.columns.size();
                case "tableGetColumnIndex": return currentWindow().table == null ? 0 : currentWindow().table.column;
                case "tableGetSortSpecs": return tableSortSpecs();
                case "beginListBox": return beginListBox(argS(args, 0), argF(args, 1, 0), argF(args, 2, 0));
                case "endListBox": endChild(); return null;
                case "beginTabBar": return beginTabBar(argS(args, 0), argI(args, 1, 0));
                case "endTabBar": endTabBar(); return null;
                case "beginTabItem": return beginTabItem(argS(args, 0), arg(args, 1));
                case "endTabItem": endTabItem(); return null;
                case "beginChildFrame": return beginChild(argS(args, 0), argF(args, 1, 0), argF(args, 2, 0), argI(args, 3, 0));
                case "endChildFrame": endChild(); return null;
                case "setNextItemAllowOverlap": return null;
                case "setItemAllowOverlap": return null;
                case "pushClipRect": {
                    if (this.currentDrawList == null) return null;
                    Object a = arg(args, 0), b = arg(args, 1);
                    if (a != null && a.getClass().getSimpleName().equals("ImVec2")
                        && b != null && b.getClass().getSimpleName().equals("ImVec2")) {
                        this.currentDrawList.pushClip(f(Reflect.get(a, "x")), f(Reflect.get(a, "y")),
                            f(Reflect.get(b, "x")), f(Reflect.get(b, "y")));
                    } else {
                        this.currentDrawList.pushClip(argF(args, 0, 0), argF(args, 1, 0),
                            argF(args, 2, 0), argF(args, 3, 0));
                    }
                    return null;
                }
                case "popClipRect": if (this.currentDrawList != null) this.currentDrawList.popClip(); return null;
                case "beginDragDropSource":
                    if (this.lastItemActive && this.io.mouseDown[0] && this.io.dragDistance(0) > 4f) {
                        if (this.dragDropSourceId == null) {
                            this.dragDropSourceId = this.lastItemId;
                            this.dragDropPayload = null;
                            this.dragDropPayloadType = null;
                        }
                        return true;
                    }
                    return false;
                case "endDragDropSource":
                    this.dragDropSourceId = null;
                    this.dragDropPayload = null;
                    this.dragDropPayloadType = null;
                    return null;
                case "beginDragDropTarget":
                    if (this.dragDropSourceId != null) {
                        this.dragDropTargetId = this.lastItemId;
                        return true;
                    }
                    return false;
                case "endDragDropTarget": this.dragDropTargetId = null; return null;
                case "setDragDropPayload":
                    this.dragDropPayloadType = argS(args, 0);
                    this.dragDropPayload = arg(args, 1);
                    return true;
                case "acceptDragDropPayload": {
                    String type = argS(args, 0);
                    if (this.dragDropSourceId == null) return null;
                    if (!type.isEmpty() && this.dragDropPayloadType != null && !type.equals(this.dragDropPayloadType)) {
                        return null;
                    }
                    if (arg(args, 1) != null) Reflect.set(arg(args, 1), "Value", true);
                    return this.dragDropPayload;
                }
                case "getDragDropPayload": return this.dragDropPayload;
                case "isRectVisible": {
                    float mx = argF(args, 0, 0);
                    float my = argF(args, 1, 0);
                    float mw = argF(args, 2, 0);
                    float mh = argF(args, 3, 0);
                    Window cw = currentWindow();
                    if (cw == null) return true;
                    return mx < cw.x + cw.w && my < cw.y + cw.h && mx + mw > cw.x && my + mh > cw.y;
                }
                default:
                    return null;
            }
        }

        // --------------------------------------------------------------
        // ImGuiIO
        // --------------------------------------------------------------

        int viewportsFlag() {
            if (this.viewportsFlag < 0) {
                try {
                    this.viewportsFlag = clazz("flag.ImGuiConfigFlags").getField("ViewportsEnable").getInt(null);
                } catch (Throwable t) {
                    this.viewportsFlag = 1 << 10;
                }
            }
            return this.viewportsFlag;
        }

        Object io(String simplePath, String name, String desc, Object self, Object[] args) {
            switch (name) {
                case "getConfigFlags": return this.io.configFlags;
                case "setConfigFlags": this.io.configFlags = argI(args, 0, 0) & ~viewportsFlag(); return null;
                case "addConfigFlags": this.io.configFlags |= (argI(args, 0, 0) & ~viewportsFlag()); return null;
                case "removeConfigFlags": this.io.configFlags &= ~argI(args, 0, 0); return null;
                case "hasConfigFlags": return (argI(args, 0, 0) & viewportsFlag()) == 0 && (this.io.configFlags & argI(args, 0, 0)) != 0;
                case "getBackendFlags": return this.io.backendFlags;
                case "setBackendFlags": this.io.backendFlags = argI(args, 0, 0); return null;
                case "addBackendFlags": this.io.backendFlags |= argI(args, 0, 0); return null;
                case "removeBackendFlags": this.io.backendFlags &= ~argI(args, 0, 0); return null;
                case "hasBackendFlags": return (this.io.backendFlags & argI(args, 0, 0)) != 0;
                case "getDisplaySize": return vec2(this.io.displayW, this.io.displayH);
                case "getDisplaySizeX": return this.io.displayW;
                case "getDisplaySizeY": return this.io.displayH;
                case "setDisplaySize":
                    this.io.displayW = Math.max(1, argF(args, 0, 1280));
                    this.io.displayH = Math.max(1, argF(args, 1, 720));
                    this.viewport.x = 0;
                    this.viewport.y = 0;
                    this.viewport.w = this.io.displayW;
                    this.viewport.h = this.io.displayH;
                    this.viewport.workX = 0;
                    this.viewport.workY = 0;
                    this.viewport.workW = this.io.displayW;
                    this.viewport.workH = this.io.displayH;
                    return null;
                case "getDisplayFramebufferScale": return vec2(this.io.fbScaleX, this.io.fbScaleY);
                case "getDisplayFramebufferScaleX": return this.io.fbScaleX;
                case "getDisplayFramebufferScaleY": return this.io.fbScaleY;
                case "setDisplayFramebufferScale": this.io.fbScaleX = argF(args, 0, 1); this.io.fbScaleY = argF(args, 1, 1); return null;
                case "getDeltaTime": return this.io.delta;
                case "setDeltaTime": this.io.delta = argF(args, 0, 1 / 60f); return null;
                case "getFonts": return atlasObject();
                case "setFonts": return null;
                case "getWantCaptureMouse": return this.io.wantCaptureMouse;
                case "getWantCaptureKeyboard": return this.io.wantCaptureKeyboard;
                case "getWantTextInput": return this.wantTextInput;
                case "getWantSetMousePos": return false;
                case "getMousePos": return vec2(this.io.mouseX, this.io.mouseY);
                case "getMousePosX": return this.io.mouseX;
                case "getMousePosY": return this.io.mouseY;
                case "addMousePosEvent":
                    this.io.mouseX = argF(args, 0, 0);
                    this.io.mouseY = argF(args, 1, 0);
                    for (int i = 0; i < 5; i++) {
                        if (this.io.mouseDown[i]) {
                            this.io.dragX[i] = this.io.mouseX - this.io.dragStartX[i];
                            this.io.dragY[i] = this.io.mouseY - this.io.dragStartY[i];
                        }
                    }
                    updateMouseCapture();
                    return null;
                case "addMouseButtonEvent": this.io.mouseButton(argI(args, 0, 0), argB(args, 1, false)); updateMouseCapture(); return null;
                case "addMouseWheelEvent": this.io.wheelH += argF(args, 0, 0); this.io.wheel += argF(args, 1, 0); return null;
                case "addMouseSourceEvent": return null;
                case "addFocusEvent": this.io.focused = argB(args, 0, true); return null;
                case "addKeyEvent": this.io.key(argI(args, 0, 0), argB(args, 1, false)); return null;
                case "addInputCharacter": this.io.chars.add((char) argI(args, 0, 0)); return null;
                case "addInputCharactersUTF8": this.io.chars.add(argS(args, 0)); return null;
                case "setKeyCtrl": this.io.ctrl = argB(args, 0, false); return null;
                case "setKeyShift": this.io.shift = argB(args, 0, false); return null;
                case "setKeyAlt": this.io.alt = argB(args, 0, false); return null;
                case "setKeySuper": this.io.superKey = argB(args, 0, false); return null;
                case "getKeyCtrl": return this.io.ctrl;
                case "getKeyShift": return this.io.shift;
                case "getKeyAlt": return this.io.alt;
                case "getKeySuper": return this.io.superKey;
                case "setMouseWheel": this.io.wheel = argF(args, 0, 0); return null;
                case "getMouseWheel": return this.io.wheel;
                case "setMouseWheelH": this.io.wheelH = argF(args, 0, 0); return null;
                case "getMouseWheelH": return this.io.wheelH;
                case "getMouseDown": return this.io.mouseDown[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "getMouseClicked": return this.io.mousePressed[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "getMouseReleased": return this.io.mouseReleased[Math.max(0, Math.min(4, argI(args, 0, 0)))];
                case "getMouseDragMaxDistanceSqr": return this.io.dragDistanceArray();
                case "getMouseDrawCursor": return this.io.mouseDrawCursor;
                case "setMouseDrawCursor": this.io.mouseDrawCursor = argB(args, 0, false); return null;
                case "getBackendPlatformName": return this.backendName;
                case "setBackendPlatformName": this.backendName = argS(args, 0); return null;
                case "setIniFilename": this.iniFilename = argS(args, 0); return null;
                case "setConfigMacOSXBehaviors": return null;
                case "getConfigMacOSXBehaviors": return false;
                case "getIniFilename": return this.iniFilename;
                case "setGetClipboardTextFn": this.io.clipboardSupplier = arg(args, 0); return null;
                case "setSetClipboardTextFn": this.io.clipboardConsumer = arg(args, 0); return null;
                case "getClipboardText": return this.io.clipboard();
                case "setClipboardText": this.io.setClipboard(argS(args, 0)); return null;
                case "getMouseWheelEventQueue": return null;
                default:
                    return null;
            }
        }

        // --------------------------------------------------------------
        // ImGuiStyle
        // --------------------------------------------------------------

        Object style(String simplePath, String name, String desc, Object self, Object[] args) {
            if (name.equals("create")) {
                long handle = newHandle();
                this.handles.put(handle, new Style());
                return (double) handle;
            }
            Style st = styleFor(self);
            this.activeStyle = st;
            if (name.equals("getColors")) {
                Object array = java.lang.reflect.Array.newInstance(clazz("ImVec4"), 64);
                for (int i = 0; i < 64; i++) {
                    java.lang.reflect.Array.set(array, i, colorVec(i));
                }
                return array;
            }
            if (name.equals("setColors")) {
                Object array = arg(args, 0);
                if (array != null && array.getClass().isArray()) {
                    int length = Math.min(64, java.lang.reflect.Array.getLength(array));
                    for (int i = 0; i < length; i++) {
                        st.setColor(i, java.lang.reflect.Array.get(array, i));
                    }
                }
                return null;
            }
            if (name.equals("getColor")) {
                Object out = args.length >= 2 ? arg(args, 1) : null;
                if (out != null) {
                    int index = argI(args, 0, 0) * 4;
                    if (index + 3 < st.colors.length) {
                        Reflect.set(out, "x", st.colors[index]);
                        Reflect.set(out, "y", st.colors[index + 1]);
                        Reflect.set(out, "z", st.colors[index + 2]);
                        Reflect.set(out, "w", st.colors[index + 3]);
                    }
                    return null;
                }
                return colorVec(argI(args, 0, 0));
            }
            if (name.equals("setColor")) {
                if (args.length >= 5) {
                    st.set(argI(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0));
                } else if (args.length == 2 && arg(args, 1) instanceof Number n) {
                    int packed = n.intValue();
                    st.set(argI(args, 0, 0),
                        (packed & 0xFF) / 255f, ((packed >> 8) & 0xFF) / 255f,
                        ((packed >> 16) & 0xFF) / 255f, ((packed >> 24) & 0xFF) / 255f);
                } else {
                    st.setColor(argI(args, 0, 0), arg(args, 1));
                }
                return null;
            }
            if (name.startsWith("get")) {
                String field = name.substring(3);
                if (field.endsWith("X")) {
                    String base = field.substring(0, field.length() - 1);
                    Object v = st.var(base, true);
                    return v instanceof float[] arr ? arr[0] : 0f;
                }
                if (field.endsWith("Y")) {
                    String base = field.substring(0, field.length() - 1);
                    Object v = st.var(base, true);
                    return v instanceof float[] arr ? arr[1] : 0f;
                }
                Object v = st.var(field, true);
                if (v instanceof float[] arr) {
                    return arr.length == 2 ? vec2(arr[0], arr[1]) : arr[0];
                }
                return v;
            }
            if (name.startsWith("set")) {
                String field = name.substring(3);
                Object value = arg(args, 0);
                if (value != null && value.getClass().getSimpleName().equals("ImVec2")) {
                    st.setVar(field, new float[]{f(Reflect.get(value, "x")), f(Reflect.get(value, "y"))});
                } else {
                    st.setVar(field, new float[]{argF(args, 0, 0), argF(args, 1, 0)});
                }
                return null;
            }
            return null;
        }

        // --------------------------------------------------------------
        // Frame lifecycle
        // --------------------------------------------------------------

        void newFrame() {
            if (!this.iniLoaded) {
                this.iniLoaded = true;
                loadIni();
            } else if (this.dockRootId != 0) {
                layoutDockNodes();
            }
            long now = System.nanoTime();
            this.io.delta = Math.max(0.0001f, (now - this.lastFrameNanos) / 1_000_000_000f);
            this.lastFrameNanos = now;
            this.frame++;
            this.time += this.io.delta;
            this.io.time = this.time;
            this.workSetThisFrame = false;
            this.workPosSetThisFrame = false;
            this.menuBarSubmittedLastFrame = this.menuBarSubmittedThisFrame;
            this.menuBarSubmittedThisFrame = false;
            this.mainMenuDrawList = null;
            this.hoveredWindowThisFrame = null;
            this.thisFrame.clear();
            this.frameLists.clear();
            this.background.reset();
            this.foreground.reset();
            this.background.textureId = this.atlas.texId;
            this.foreground.textureId = this.atlas.texId;
            FontAtlas.ACTIVE.set(this.atlas);
            this.frameLists.add(this.background);
            this.anyPopupOpen = false;
            this.popups.clear();
            this.mainBegunThisFrame = false;
            this.currentWindow = null;
            this.currentDrawList = null;
            this.io.mousePressed = this.io.mouseNextPressed.clone();
            this.io.mouseReleased = this.io.mouseNextReleased.clone();
            this.io.mouseNextPressed = new boolean[5];
            this.io.mouseNextReleased = new boolean[5];
            // Keep ActiveId during the release frame: widgets decide "clicked"
            // by comparing ActiveId with their id on mouseReleased.
            if (!this.io.mouseDown[0] && !this.io.mouseReleased[0]) {
                this.activeId = null;
            }
            this.io.keysPressed = new java.util.HashSet<>(this.io.keysNextPressed);
            this.io.keysReleased = new java.util.HashSet<>(this.io.keysNextReleased);
            // Do not let navigation activation consume Enter/Space while a text
            // field owns the keyboard; that would break normal typing.
            if (this.activeInput != null) {
                this.nav.beginFrame();
            } else {
                this.nav.beginFrame(this.navKeys);
            }
            updateDockSplitters();
            this.io.keysNextPressed.clear();
            this.io.keysNextReleased.clear();
            this.io.chars.clear();
            this.wantTextInput = false;
            this.lastItemHovered = false;
            this.lastItemActive = false;
            this.lastItemClicked = false;
            this.lastItemClickedButton = 0;
            this.lastItemEdited = false;
            this.lastItemActivated = false;
            this.lastItemDeactivated = false;
            this.lastItemDeactivatedAfterEdit = false;
            this.keyboardFocusRequested = false;
            this.popupMap.values().forEach(p -> p.rendered = false);
            if (this.io.mousePressed[0] && !this.popups.isEmpty()) {
                boolean inside = false;
                for (Window pw : this.popups) {
                    if (this.io.mouseX >= pw.x && this.io.mouseX <= pw.x + pw.w
                        && this.io.mouseY >= pw.y && this.io.mouseY <= pw.y + pw.h) {
                        inside = true;
                        break;
                    }
                }
                // A click on the menu bar label is handled by beginMenu(); ignore
                // the strip so it can toggle its own popup.
                boolean onMenuBar = this.mainMenuDrawList != null
                    && this.io.mouseY <= Math.min(this.io.displayH, frameHeight());
                if (!inside && !onMenuBar) {
                    this.popupMap.values().forEach(p -> p.open = false);
                }
            }
            if (this.io.wheel != 0) {
                // Reference: UpdateMouseWheel() scrolls only the best (topmost)
                // hovered window, with a step of trunc(min(5*FontSize, 0.67*InnerH)).
                Window target = null;
                long bestOrder = Long.MIN_VALUE;
                for (Window w : this.lastFrame) {
                    if ((w.flags & 16) != 0 || w.scrollMaxY <= 0) continue;
                    if (this.io.mouseX < w.x || this.io.mouseX > w.x + w.w
                        || this.io.mouseY < w.y || this.io.mouseY > w.y + w.h) continue;
                    if (target == null || w.order >= bestOrder) {
                        target = w;
                        bestOrder = w.order;
                    }
                }
                if (target != null) {
                    float innerH = Math.max(1, target.h - target.titleH);
                    float step = (float) (int) Math.min(5f * this.style.fontSize, innerH * 0.67f);
                    target.scrollY = Math.max(0, Math.min(target.scrollMaxY,
                        target.scrollY - this.io.wheel * Math.max(1, step)));
                }
            }
            this.updateMouseCapture();
            this.io.nextWantCaptureMouse = -1;
            this.io.nextWantCaptureKeyboard = -1;
        }

        void addWindowWithChildren(Window w) {
            if (w.drawList.vertices.size() > 0 || w.mainDocked) {
                if (!this.frameLists.contains(w.drawList)) this.frameLists.add(w.drawList);
            }
            for (Window child : w.childWindows) {
                addWindowWithChildren(child);
            }
        }

        void render() {
            this.mainActiveLastFrame = this.mainBegunThisFrame;
            this.lastFrame = new ArrayList<>(this.thisFrame);
            List<Window> ordered = new ArrayList<>(this.thisFrame);
            ordered.sort(java.util.Comparator.comparingLong(w -> w.order));
            this.frameLists.clear();
            this.frameLists.add(this.background);
            for (Window w : ordered) {
                if (this.popups.contains(w) || w.childWindow) continue;
                if (w.name.startsWith("##tooltip")) continue;
                addWindowWithChildren(w);
            }
            // Popups/tooltips/menus always draw above normal windows,
            // in submission order (child popups last).
            for (Window w : this.popups) {
                if (w.drawList.vertices.size() > 0 || w.mainDocked) {
                    if (!this.frameLists.contains(w.drawList)) this.frameLists.add(w.drawList);
                }
            }
            this.frameLists.add(this.foreground);
            // Tooltips are the top-most interactive layer; drawing them after
            // the foreground dim keeps them readable over disabled panels.
            for (Window w : ordered) {
                if (!w.name.startsWith("##tooltip")) continue;
                if (w.drawList.vertices.size() > 0
                    && !this.frameLists.contains(w.drawList)) this.frameLists.add(w.drawList);
            }
            this.drawData.lists = new ArrayList<>(this.frameLists);
            this.drawData.displayW = this.io.displayW;
            this.drawData.displayH = this.io.displayH;
            this.drawData.fbScaleX = this.io.fbScaleX;
            this.drawData.fbScaleY = this.io.fbScaleY;
            this.drawData.valid = true;
            for (DrawList list : this.frameLists) {
                list.finish();
            }
            this.io.mousePressed = new boolean[5];
            this.io.mouseReleased = new boolean[5];
            this.io.wheel = 0;
            this.io.wheelH = 0;
        }

        void loadIni() {
            if (this.iniFilename == null || this.iniFilename.isBlank()) {
                return;
            }
            try {
                java.nio.file.Path path = java.nio.file.Path.of(this.iniFilename);
                if (!path.isAbsolute()) {
                    try {
                        path = net.fabricmc.loader.api.FabricLoader.getInstance().getGameDir().resolve(path);
                    } catch (Throwable ignored) {
                        path = java.nio.file.Path.of(System.getProperty("user.dir")).resolve(path);
                    }
                }
                if (!java.nio.file.Files.isRegularFile(path)) {
                    return;
                }
                String iniText = java.nio.file.Files.readString(path, StandardCharsets.UTF_8);
                String section = "";
                for (String rawLine : iniText.split("\\R", -1)) {
                    String line = rawLine.trim();
                    if (line.isEmpty()) {
                        continue;
                    }
                    if (line.startsWith("[Window][") && line.endsWith("]")) {
                        section = line.substring("[Window][".length(), line.length() - 1);
                        continue;
                    }
                    if (line.equals("[Docking][Data]")) {
                        section = "[Docking][Data]";
                        continue;
                    }
                    if (section.equals("[Docking][Data]")) {
                        // Dock node geometry and metadata are owned by DockLayout.
                        continue;
                    }
                    if (!section.isEmpty() && line.startsWith("Pos=")) {
                        String[] p = line.substring(4).split(",");
                        float[] layout = this.iniLayout.computeIfAbsent(section, k -> new float[]{100, 100, 420, 300, 0});
                        if (p.length >= 2) {
                            layout[0] = Float.parseFloat(p[0].trim());
                            layout[1] = Float.parseFloat(p[1].trim());
                        }
                    } else if (!section.isEmpty() && line.startsWith("Size=")) {
                        String[] p = line.substring(5).split(",");
                        float[] layout = this.iniLayout.computeIfAbsent(section, k -> new float[]{100, 100, 420, 300, 0});
                        if (p.length >= 2) {
                            layout[2] = Float.parseFloat(p[0].trim());
                            layout[3] = Float.parseFloat(p[1].trim());
                        }
                    } else if (!section.isEmpty() && line.startsWith("Collapsed=")) {
                        float[] layout = this.iniLayout.computeIfAbsent(section, k -> new float[]{100, 100, 420, 300, 0});
                        layout[4] = "1".equals(line.substring("Collapsed=".length()).trim()) ? 1 : 0;
                    } else if (!section.isEmpty() && line.startsWith("DockId=")) {
                        try {
                            String value = line.substring("DockId=".length()).trim();
                            int comma = value.indexOf(',');
                            String tab = "0";
                            if (comma >= 0) {
                                tab = value.substring(comma + 1);
                                value = value.substring(0, comma);
                            }
                            this.iniDockIds.put(section, (int) Long.parseLong(value.replace("0x", ""), 16));
                            this.iniDockTabs.put(section, parseInt(tab, 0));
                        } catch (NumberFormatException ignored) {
                        }
                    }
                }
                this.dockLayout = DockLayout.parseText(iniText);
                configureDockLayout();
                rebuildDockNodesFromLayout();
                for (Map.Entry<String, Integer> e : this.iniDockIds.entrySet()) {
                    this.dockWindows.computeIfAbsent(e.getValue(), k -> new ArrayList<>()).add(e.getKey());
                }
                this.dockNodes.values().forEach(this::resolveDockSelection);
                if (Boolean.getBoolean("noimgui.debug.layout")) {
                    NoNativeMod.LOGGER.info("Layout entries: {} windows, {} dockids, {} nodes, root={}",
                        this.iniLayout.size(), this.iniDockIds.size(), this.dockNodes.size(), this.dockRootId);
                    this.iniDockIds.forEach((k, v) -> NoNativeMod.LOGGER.info("  dock {} -> {}", k, v));
                }
                this.layoutDockNodes();
            } catch (Throwable t) {
                NoNativeMod.LOGGER.warn("Could not read imgui layout", t);
            }
        }

        void configureDockLayout() {
            if (this.dockLayout == null) return;
            this.dockLayout.setFramePadding(this.style.framePaddingX, this.style.framePaddingY);
            this.dockLayout.setWindowBorderSize(this.style.windowBorderSize);
            this.dockLayout.setItemInnerSpacingX(this.style.itemInnerSpacingX);
            this.dockLayout.setDockingSeparatorSize(this.style.dockingSeparatorSize);
            this.dockLayout.setWindowMinSize(this.style.windowMinSizeX, this.style.windowMinSizeY);
            this.dockLayout.setTabBarHeight(frameHeight());
        }

        void rebuildDockNodesFromLayout() {
            this.dockNodes.clear();
            if (this.dockLayout == null) return;
            for (DockLayout.Node source : this.dockLayout.nodes()) {
                DockNode node = new DockNode(source.id(), source.parentId());
                node.split = source.split() == DockLayout.Split.Y ? 'Y' : 'X';
                node.central = source.isCentralNode();
                node.selected = source.selectedTabId();
                node.x = source.x();
                node.y = source.y();
                node.w = source.width();
                node.h = source.height();
                node.rx = source.x();
                node.ry = source.y();
                node.rw = source.width();
                node.rh = source.height();
                this.dockNodes.put(node.id, node);
            }
            for (DockLayout.Node source : this.dockLayout.nodes()) {
                DockNode node = this.dockNodes.get(source.id());
                if (node == null || node.parent == 0) continue;
                DockNode parent = this.dockNodes.get(node.parent);
                if (parent != null && !parent.children.contains(node.id)) {
                    parent.children.add(node.id);
                }
            }
            DockLayout.Node root = this.dockLayout.root();
            if (root != null) {
                this.dockRootId = root.id();
                this.dockRootW = Math.max(1.0f, root.width());
                this.dockRootH = Math.max(1.0f, root.height());
            }
        }

        void resolveDockSelection(DockNode node) {
            List<String> names = this.dockWindows.get(node.id);
            if (names == null || names.isEmpty()) return;
            if (node.selected != 0) {
                for (String candidate : names) {
                    // Axiom's ini stores CRC32(full name); Flashback's stores
                    // CRC32(post-"###"). Accept both, like ImHashStr + lookup.
                    if (imHashStr(candidate) == node.selected
                        || imHashStr(labelKey(candidate)) == node.selected) {
                        node.selectedName = candidate;
                        break;
                    }
                }
            }
            if (node.selectedName == null) {
                node.selectedName = names.get(0);
            }
        }

        void syncDockRects() {
            if (this.dockLayout == null) return;
            for (DockLayout.Node source : this.dockLayout.nodes()) {
                DockNode node = this.dockNodes.get(source.id());
                if (node == null) continue;
                node.x = source.x();
                node.y = source.y();
                node.w = source.width();
                node.h = source.height();
                node.rx = source.x();
                node.ry = source.y();
                node.rw = source.width();
                node.rh = source.height();
                node.split = source.split() == DockLayout.Split.Y ? 'Y' : 'X';
            }
        }

        Map<String, String> kv(String line) {
            Map<String, String> map = new HashMap<>();
            for (String part : line.trim().split("\\s+")) {
                int eq = part.indexOf('=');
                if (eq > 0) {
                    String key = part.substring(0, eq);
                    String value = part.substring(eq + 1);
                    if (key.equals("Pos") || key.equals("Size") || key.equals("SizeRef")) {
                        String[] xy = value.split(",");
                        String prefix = key.equals("SizeRef") ? "Size" : key;
                        map.put(prefix + "X", xy.length > 0 ? xy[0] : "0");
                        map.put(prefix + "Y", xy.length > 1 ? xy[1] : "0");
                    } else {
                        map.put(key, value);
                    }
                }
            }
            return map;
        }

        int parseInt(String value, int fallback) {
            if (value == null) return fallback;
            try {
                return (int) Long.parseLong(value.replace("0x", ""), 16);
            } catch (NumberFormatException e) {
                try {
                    return Integer.parseInt(value);
                } catch (NumberFormatException e2) {
                    return fallback;
                }
            }
        }

        float parseFloat(String value, float fallback) {
            try {
                return Float.parseFloat(value);
            } catch (Exception e) {
                return fallback;
            }
        }

        void updateDockSplitters() {
            if (this.dockLayout == null) return;
            if (this.draggingDockNode != null) {
                if (this.io.mouseDown[0]) {
                    boolean horizontal = this.draggingDockNode.split() == DockLayout.Split.X;
                    float delta = horizontal
                        ? this.io.mouseX - this.draggingDockLastX
                        : this.io.mouseY - this.draggingDockLastY;
                    if (delta != 0.0f
                        && this.dockLayout.resizeSplit(this.draggingDockNode.id(), this.draggingDockChild, delta)) {
                        syncDockRects();
                    }
                    this.draggingDockLastX = this.io.mouseX;
                    this.draggingDockLastY = this.io.mouseY;
                } else {
                    this.draggingDockNode = null;
                }
                return;
            }
            if (!this.io.mousePressed[0]) return;
            for (DockLayout.Node node : this.dockLayout.nodes()) {
                if (node.children().size() < 2 || node.split() == DockLayout.Split.NONE) continue;
                DockLayout.Rect splitter = this.dockLayout.splitterRect(node.id());
                if (splitter == null) continue;
                float slop = this.style.windowBorderSize + 4f;
                boolean inside = this.io.mouseX >= splitter.x() - slop
                    && this.io.mouseX <= splitter.right() + slop
                    && this.io.mouseY >= splitter.y() - slop
                    && this.io.mouseY <= splitter.bottom() + slop;
                if (!inside) continue;
                // SplitterBehavior always resizes child 0; the click side must
                // not invert the drag direction.
                this.draggingDockNode = node;
                this.draggingDockChild = 0;
                this.draggingDockLastX = this.io.mouseX;
                this.draggingDockLastY = this.io.mouseY;
                return;
            }
        }

        void layoutDockNodes() {
            float wx = this.workPosSetThisFrame ? this.viewport.workX : 0;
            float wy = this.workPosSetThisFrame ? this.viewport.workY : 0;
            float ww = Math.max(1, this.workSetThisFrame ? this.viewport.workW : this.io.displayW);
            float wh = Math.max(1, this.workSetThisFrame ? this.viewport.workH : this.io.displayH);
            if (!this.workPosSetThisFrame
                && (this.menuBarSubmittedLastFrame || this.menuBarSubmittedThisFrame)) {
                // BeginViewportSideBar() reports the bar into BuildWorkInsetMin;
                // the latched WorkPos starts below the menu bar.
                float bar = Math.min(wh, frameHeight());
                wy += bar;
                wh = Math.max(1, wh - bar);
            }
            if (this.dockLayout != null) {
                configureDockLayout();
                this.dockLayout.layout(wx, wy, ww, wh);
                syncDockRects();
                return;
            }
            DockNode root = this.dockNodes.get(this.dockRootId);
            if (root == null) return;
            float sx = ww / Math.max(1, this.dockRootW);
            float sy = wh / Math.max(1, this.dockRootH);
            layoutDockNode(root, wx + root.x * sx, wy + root.y * sy, root.w * sx, wh);
        }

        DockLayout.Node resolveDockLeaf(int id) {
            if (this.dockLayout == null) return null;
            DockLayout.Node node = this.dockLayout.node(id);
            if (node == null) return null;
            int guard = 0;
            while (node != null && !node.isLeaf() && guard++ < 64) {
                DockLayout.Node central = null;
                for (DockLayout.Node child : node.children()) {
                    if (child.isCentralNode() || child.hasCentralNodeChild()) {
                        central = child;
                        break;
                    }
                }
                node = central != null ? central : node.child(0);
            }
            return node;
        }

        float dockTabHeight(DockLayout.Node node) {
            if (node == null || this.dockLayout == null) return 0f;
            int runtime = this.runtimeDockLocalFlags.getOrDefault(node.id(), 0);
            boolean noTabBar = node.noTabBar() || node.hiddenTabBar()
                || (runtime & (1 << 12)) != 0 || (runtime & (1 << 13)) != 0;
            return noTabBar ? 0f : this.dockLayout.tabBarHeight();
        }

        void layoutDockNode(DockNode node, float x, float y, float w, float h) {
            node.rx = x;
            node.ry = y;
            node.rw = w;
            node.rh = h;
            if (node.children.isEmpty()) return;
            float total = 0;
            for (int id : node.children) {
                DockNode child = this.dockNodes.get(id);
                if (child != null) total += Math.max(1, node.split == 'X' ? child.w : child.h);
            }
            if (total <= 0) total = node.children.size();
            float offset = 0;
            for (int id : node.children) {
                DockNode child = this.dockNodes.get(id);
                if (child == null) continue;
                float weight = Math.max(1, node.split == 'X' ? child.w : child.h);
                if (node.split == 'X') {
                    float cw = w * weight / total;
                    layoutDockNode(child, x + offset, y, cw, h);
                    offset += cw;
                } else {
                    float ch = h * weight / total;
                    layoutDockNode(child, x, y + offset, w, ch);
                    offset += ch;
                }
            }
        }

        Window currentWindow() {
            if (this.currentWindow == null) {
                Window w = new Window("##root", 0, 0, this.io.displayW, this.io.displayH);
                this.currentWindow = w;
                this.windowStack.add(w);
            }
            return this.currentWindow;
        }

        void debugWidget(String kind, String label, float x, float y, float w, float h) {
            if (!DEBUG_WIDGETS) return;
            Window cw = this.currentWindow;
            if (cw == null || !cw.name.startsWith("Tool Options")) return;
            if (this.widgetDebugCount++ > 80) return;
            NoNativeMod.LOGGER.info("W {} '{}' x={} y={} w={} h={} cursor=({},{}) line=({},{}) frame={} alpha={} clip=({},{}..{},{}) tex={}",
                kind, label, x, y, w, h, cw.cursorX, cw.cursorY, cw.lineY, cw.lineHeight, this.frame,
                this.globalAlpha, cw.drawList.clipMinX, cw.drawList.clipMinY, cw.drawList.clipMaxX, cw.drawList.clipMaxY,
                this.atlas.texId);
        }

        static boolean contains(int[] values, int value) {
            for (int v : values) if (v == value) return true;
            return false;
        }

        boolean condApplies(int cond, Window w, boolean position) {
            if (cond == 0 || (cond & 1) != 0) return true;
            if ((cond & 8) != 0 && w.appearing) return true;
            if ((cond & 2) != 0 || (cond & 4) != 0) {
                if (position) {
                    if (w.posCondApplied) return false;
                    w.posCondApplied = true;
                    return true;
                }
                if (w.sizeCondApplied) return false;
                w.sizeCondApplied = true;
                return true;
            }
            return false;
        }

        boolean beginWithOpen(String name, Object open, int flags) {
            if (!bool(open)) {
                Window w = this.windows.computeIfAbsent(name, n -> new Window(n, 80, 80, 420, 300));
                w.skipDraw = true;
                w.openState = open;
                this.currentWindow = w;
                this.windowStack.add(w);
                this.thisFrame.add(w);
                return false;
            }
            Window w = this.windows.computeIfAbsent(name, n -> new Window(n, 80, 80, 420, 300));
            w.openState = open;
            w.skipDraw = false;
            return begin(name, flags);
        }

        boolean begin(String name, int flags) {
            Window w = this.windows.computeIfAbsent(name, n -> new Window(n, 80 + this.windows.size() * 24, 80 + this.windows.size() * 18, 420, 300));
            if (w.firstFrame) {
                float[] ini = this.iniLayout.get(iniKey(name));
                if (ini != null) {
                    w.x = ini[0];
                    w.y = ini[1];
                    w.w = ini[2];
                    w.h = ini[3];
                    w.collapsed = ini.length > 4 && ini[4] != 0;
                }
            }
            // Appearing = first frame after the window was inactive/closed.
            w.appearing = w.lastSeenFrame != this.frame - 1;
            w.lastSeenFrame = this.frame;
            w.firstFrame = false;
            w.flags = flags;
            w.clipCount = 0;
            w.childWindows.clear();
            // Stable creation-order z-order (ImGui keeps g.Windows in z-order;
            // clicks bring a window to the front).
            if (w.order == 0) w.order = ++this.frameCount;

            float x = w.x;
            float y = w.y;
            float width = w.w;
            float height = w.h;

            // Axiom passes names like "Tools###Tools" while its imgui.ini section
            // is "###Tools" (the ImGui ### id). Resolve the stored key.
            String iniName = name;
            if (!this.iniDockIds.containsKey(iniName) && !this.iniLayout.containsKey(iniName)) {
                String alt = labelKey(name);
                if (this.iniDockIds.containsKey(alt) || this.iniLayout.containsKey(alt)) {
                    iniName = alt;
                }
            }
            int iniDock = this.iniDockIds.getOrDefault(iniName, 0);
            int requestedDock = this.nextWindowDockId instanceof Number n ? n.intValue() : 0;
            // BeginDocked() honours the window's existing DockId; SetNextWindowDockID
            // only matters for windows that are not docked yet.
            int dockId = w.dockId != 0 ? w.dockId : (iniDock != 0 ? iniDock : requestedDock);
            boolean isMain = name.equals("Main");

            boolean applyPos = this.nextWindowX == this.nextWindowX
                && condApplies(this.nextWindowCond, w, true);
            boolean applySize = this.nextWindowW == this.nextWindowW
                && condApplies(this.nextWindowSizeCond, w, false);

            // SetNextWindowPos() implies PosUndock, but a window restored by
            // imgui.ini keeps its saved DockId (Axiom sets FirstUseEver initial
            // positions on every frame for its panels).
            if (applyPos && dockId != 0 && this.nextWindowPosUndock && iniDock == 0) {
                w.dockId = 0;
                w.dockAssigned = false;
                dockId = 0;
            }

            DockLayout.Node layoutNode = dockId == 0 ? null : resolveDockLeaf(dockId);
            if (layoutNode == null && dockId != 0 && this.dockLayout != null) {
                layoutNode = this.dockLayout.node(dockId);
            }
            float dockTabHeight = dockTabHeight(layoutNode);

            w.pivotAnchorX = Float.NaN;
            if (applyPos) {
                x = this.nextWindowX - this.nextWindowPivotX * width;
                y = this.nextWindowY - this.nextWindowPivotY * height;
                if (this.nextWindowPivotX != 0 || this.nextWindowPivotY != 0) {
                    w.pivotAnchorX = this.nextWindowX;
                    w.pivotAnchorY = this.nextWindowY;
                    w.appliedPivotX = this.nextWindowPivotX;
                    w.appliedPivotY = this.nextWindowPivotY;
                }
            }
            if (applySize) {
                width = this.nextWindowW;
                height = this.nextWindowH;
            }
            w.mainDocked = isMain;
            if (isMain) {
                this.mainBegunThisFrame = true;
                this.focusedWindowName = name;
            }
            if (this.nextWindowFocus) {
                // FocusWindow(): never changes Pos/Size.
                this.focusedWindowName = name;
                w.order = ++this.frameCount;
            }
            if (w.hovered && this.io.mousePressed[0]) {
                this.focusedWindowName = name;
                w.order = ++this.frameCount;
            }
            if (layoutNode != null) {
                // BeginDocked(): the window occupies the node rect; the tab bar
                // overlays the title-bar strip instead of adding height.
                DockLayout.Rect r = layoutNode.rect();
                x = r.x();
                y = r.y();
                width = Math.max(32, r.width());
                height = Math.max(32, r.height());
                w.dockId = layoutNode.id();
                w.pivotAnchorX = Float.NaN;
                w.dockNode = this.dockNodes.get(layoutNode.id());
                w.dockAssigned = true;
                List<String> names = this.dockWindows.computeIfAbsent(layoutNode.id(), k -> new ArrayList<>());
                String tabName = names.contains(labelKey(name)) ? labelKey(name) : displayLabel(name);
                if (!name.startsWith("##") && !names.contains(tabName) && !names.contains(name)) {
                    names.add(tabName);
                }
                w.dockTabHeight = dockTabHeight;
                if (names.size() > 1 && w.dockNode != null && w.dockNode.selectedName != null
                    && !w.dockNode.selectedName.equals(name)
                    && !w.dockNode.selectedName.equals(labelKey(name))) {
                    // Hidden tab: keep the window on the stack but do not draw it.
                    w.flags = flags;
                    w.cursorX = 0;
                    w.cursorY = 0;
                    w.lineX = 0;
                    w.lineY = 0;
                    w.lineHeight = 0;
                    w.drawList.reset();
                    w.drawList.textureId = this.atlas.texId;
                    w.clipCount = 0;
                    w.drawList.addList(this.frameLists);
                    this.currentWindow = w;
                    this.currentDrawList = w.drawList;
                    this.windowStack.add(w);
                    return false;
                }
            } else {
                w.dockId = dockId;
                if (dockId != 0 && !w.dockAssigned && this.nextWindowX != this.nextWindowX) {
                    int perColumn = Math.max(1, (int) (this.io.displayH / 270f));
                    int slot = this.dockSlots++;
                    int column = slot / perColumn;
                    int row = slot % perColumn;
                    float dockWidth = Math.min(360, Math.max(220, this.io.displayW * 0.27f));
                    x = this.io.displayW - dockWidth * (column + 1) - 4 * column;
                    y = row * 266f;
                    width = dockWidth;
                    height = Math.max(180, Math.min(260, this.io.displayH / perColumn - 6));
                    w.dockAssigned = true;
                }
            }

            if (this.nextCollapsed != null) {
                w.collapsed = this.nextCollapsed;
                this.nextCollapsed = null;
            }
            if (width <= 0) width = 420;
            if (height <= 0) height = 300;
            if (this.nextMaxW > 0) width = Math.min(width, this.nextMaxW);
            if (this.nextMaxH > 0) height = Math.min(height, this.nextMaxH);
            if (this.nextMinW > 0) width = Math.max(width, this.nextMinW);
            if (this.nextMinH > 0) height = Math.max(height, this.nextMinH);
            this.nextMinW = this.nextMinH = 0;
            this.nextMaxW = this.nextMaxH = 0;
            w.x = x;
            w.y = y;
            w.w = width;
            w.h = height;
            if (Boolean.getBoolean("noimgui.debug.layout") && this.frame <= 3) {
                NoNativeMod.LOGGER.info("WIN f{} {} pos={},{} size={}x{} dock={} ini={} next=({},{})", this.frame, name, x, y, width, height, dockId,
                    this.iniLayout.containsKey(name), this.nextWindowX, this.nextWindowY);
            }
            // Hover follows the topmost window found by UpdateHoveredWindowAndCaptureFlags,
            // not merely any overlapping rect.
            w.hovered = (flags & 1024) == 0
                && this.io.mouseX >= x && this.io.mouseX <= x + width
                && this.io.mouseY >= y && this.io.mouseY <= y + height
                && (this.hoveredWindowThisFrame == null || this.hoveredWindowThisFrame == w);

            this.nextWindowX = Float.NaN;
            this.nextWindowY = Float.NaN;
            this.nextWindowW = Float.NaN;
            this.nextWindowH = Float.NaN;
            this.nextWindowPivotX = 0;
            this.nextWindowPivotY = 0;
            this.nextWindowCond = 0;
            this.nextWindowSizeCond = 0;
            this.nextWindowBgAlpha = 1f;
            this.nextScrollX = Float.NaN;
            this.nextScrollY = Float.NaN;
            this.nextWindowDockId = null;
            this.nextWindowFocus = false;
            this.nextWindowPosUndock = false;

            if (w.collapsed && (flags & 1) == 0 && w.dockId == 0) {
                w.contentHeight = this.style.fontSize + this.style.framePaddingY * 2f;
                this.currentWindow = w;
                this.currentDrawList = w.drawList;
                this.windowStack.add(w);
                this.thisFrame.add(w);
                w.drawList.pushClip(w.x, w.y, w.x + w.w, w.y + w.h);
                w.clipCount = 1;
                this.drawWindowChrome(w);
                return false;
            }

            float titleHeight = w.dockId != 0 ? dockTabHeight
                : ((flags & 1) != 0 ? 0f : frameHeight());
            w.titleH = titleHeight;
            w.contentX = this.style.windowPaddingX;
            w.contentY = titleHeight + this.style.windowPaddingY;
            w.contentW = Math.max(1, w.w - w.contentX * 2 - (w.scrollbarY ? this.style.scrollbarSize : 0));
            w.contentH = Math.max(1, w.h - titleHeight - this.style.windowPaddingY * 2);
            w.workMinX = w.contentX;
            w.workMaxX = w.contentX + w.contentW;
            w.workMinY = w.contentY;
            w.workMaxY = w.contentY + w.contentH;
            if (this.nextScrollX == this.nextScrollX) w.scrollX = Math.max(0, this.nextScrollX);
            if (this.nextScrollY == this.nextScrollY) w.scrollY = Math.max(0, this.nextScrollY);
            w.lineStartX = w.contentX + this.indent;
            w.tableItemWidth = 0f;
            w.workMinX = w.contentX;
            w.workMaxX = w.contentX + w.contentW;
            w.workMinY = w.contentY;
            w.workMaxY = w.contentY + w.contentH;
            w.cursorX = w.lineStartX;
            w.cursorY = w.contentY;
            w.prevLineX = w.cursorX;
            w.prevLineY = w.cursorY;
            w.currLineSizeY = 0;
            w.prevLineSizeY = 0;
            w.isSameLine = false;
            w.maxContentX = 0;
            w.contentMaxX = 0;
            w.contentMaxY = 0;
            w.lineX = w.contentX;
            w.lineY = w.contentY;
            w.lineHeight = 0;
            w.contentHeight = 0;
            w.drawList.reset();
            w.drawList.textureId = this.atlas.texId;
            w.drawList.textSize = this.style.fontSize;
            if (!this.frameLists.contains(w.drawList)) {
                this.frameLists.add(w.drawList);
            }
            this.currentWindow = w;
            this.currentDrawList = w.drawList;
            this.windowStack.add(w);
            this.thisFrame.add(w);
            // Chrome and tabs are clipped to the window rect (InnerClipRect in
            // native), content gets the narrower content clip afterwards.
            w.drawList.textSize = this.style.fontSize;
            w.drawList.pushClip(x, y, x + width, y + height);
            w.clipCount = 1;
            this.drawWindowChrome(w);
            drawDockTabs(w);
            w.drawList.pushClip(x, y + titleHeight, x + width, y + height);
            w.clipCount = 2;
            return true;
        }

        void drawDockTabs(Window w) {
            if (w.dockNode == null || w.dockTabHeight <= 0) return;
            List<String> names = this.dockWindows.getOrDefault(w.dockNode.id, List.of());
            if (names.isEmpty()) return;
            DockLayout.Rect tabRect = this.dockLayout == null ? null : this.dockLayout.tabBarRect(w.dockNode.id);
            float x = tabRect != null ? tabRect.x() : w.dockNode.rx;
            float y = tabRect != null ? tabRect.y() : w.dockNode.ry;
            float height = tabRect != null ? tabRect.height() : w.dockTabHeight;
            float right = tabRect != null ? tabRect.right() : x + w.dockNode.rw;
            // Tab bar strip background (DockNodeUpdateTabBar).
            w.drawList.addRectFilled(w.x, y, w.x + w.w, y + height, styleColor(10)); // TitleBg
            float cursor = x;
            for (String name : names) {
                String label = displayLabel(name);
                // TabBarGetTabWidth: text + 2*FramePadding.x (+ close button in native).
                float width = Math.min(right - cursor,
                    this.atlas.measure(label, this.style.fontSize) + this.style.framePaddingX * 2 + this.style.itemSpacingX);
                if (width <= 0) break;
                boolean selected = name.equals(w.dockNode.selectedName)
                    || (w.dockNode.selectedName != null && labelKey(name).equals(w.dockNode.selectedName));
                boolean hovered = this.io.mouseX >= cursor && this.io.mouseX <= cursor + width
                    && this.io.mouseY >= y && this.io.mouseY <= y + height;
                if (hovered && this.io.mousePressed[0]) {
                    this.dockTabPressed = name;
                }
                if (hovered && this.io.mouseReleased[0] && name.equals(this.dockTabPressed)) {
                    w.dockNode.selectedName = name;
                    this.dockTabPressed = null;
                }
                int bg = selected ? styleColor(33) : hovered ? styleColor(32) : styleColor(31); // TabSelected/TabHovered/Tab
                w.drawList.addRectFilled(cursor, y, cursor + width, y + height, bg);
                w.drawList.addText(cursor + this.style.framePaddingX, y + this.style.framePaddingY,
                    styleColor(0), label);
                cursor += width;
            }
        }

        void end() {
            if (this.windowStack.isEmpty()) {
                return;
            }
            Window w = this.windowStack.remove(this.windowStack.size() - 1);
            // CalcWindowContentSizes(): ContentSize is CursorMaxPos - CursorStartPos;
            // the trailing ItemSpacing.y is not included.
            // CursorMaxPos is in window-local coordinates, ContentSize excludes
            // the starting padding/title offset.
            float contentSizeY = Math.max(0, w.contentMaxY - w.contentY);
            float contentSizeX = Math.max(0, w.contentMaxX - w.contentX);
            w.contentHeight = contentSizeY;
            float padY = this.style.windowPaddingY * 2f;
            float innerH = Math.max(1, w.h - w.titleH);
            boolean noScrollbar = (w.flags & 8) != 0;
            w.scrollbarY = !noScrollbar && contentSizeY + padY > innerH;

            if ((w.flags & 64) != 0) { // AlwaysAutoResize
                float hintW = this.nextContentW == this.nextContentW ? this.nextContentW : contentSizeX;
                float hintH = this.nextContentH == this.nextContentH ? this.nextContentH : contentSizeY;
                float newW = hintW + w.contentX * 2 + (w.scrollbarY ? this.style.scrollbarSize : 0);
                float newH = hintH + w.titleH + padY;
                w.w = Math.max(32, Math.min(newW, Math.max(32, this.io.displayW - 16)));
                w.h = Math.max(32, Math.min(newH, Math.max(32, this.io.displayH - 16)));
                if (Boolean.getBoolean("noimgui.debug.autosize") && this.idDebugCount++ < 200) {
                    NoNativeMod.LOGGER.info("AUTOSIZE '{}' {}x{} content={}x{} next={}x{}", w.name, w.w, w.h,
                        contentSizeX, contentSizeY, this.nextContentW, this.nextContentH);
                }
                w.contentW = Math.max(1, w.w - w.contentX * 2 - (w.scrollbarY ? this.style.scrollbarSize : 0));
                w.contentH = Math.max(1, w.h - w.titleH - padY);
                innerH = Math.max(1, w.h - w.titleH);
                if (w.pivotAnchorX == w.pivotAnchorX) {
                    w.x = w.pivotAnchorX - w.appliedPivotX * w.w;
                    w.y = w.pivotAnchorY - w.appliedPivotY * w.h;
                    w.pivotAnchorX = Float.NaN;
                }
            }

            w.scrollMaxX = Math.max(0, contentSizeX + this.style.windowPaddingX * 2
                - Math.max(1, w.w - (w.scrollbarY ? this.style.scrollbarSize : 0)));
            w.scrollX = Math.max(0, Math.min(w.scrollX, w.scrollMaxX));
            w.scrollMaxY = noScrollbar ? 0 : Math.max(0, contentSizeY + padY - innerH);
            w.scrollY = Math.max(0, Math.min(w.scrollY, w.scrollMaxY));
            if (w.scrollMaxY > 0) {
                float trackX = w.x + w.w - this.style.scrollbarSize;
                float trackY = w.y + w.contentY;
                float trackH = w.contentH;
                // CalcScrollbarThumb() (imgui_widgets.cpp:1058-1075).
                float sizeVisible = innerH;
                float sizeContents = Math.max(Math.max(contentSizeY, sizeVisible), 1f);
                float thumbH = Math.max(Math.min(trackH, this.style.grabMinSize),
                    (float) (int) (trackH * sizeVisible / sizeContents));
                thumbH = Math.min(thumbH, trackH);
                float thumbY = trackY + (trackH - thumbH) * (w.scrollY / w.scrollMaxY);
                boolean overThumb = this.io.mouseX >= trackX && this.io.mouseX <= w.x + w.w
                    && this.io.mouseY >= thumbY && this.io.mouseY <= thumbY + thumbH;
                if (overThumb && this.io.mousePressed[0]) {
                    w.scrollbarDragging = true;
                    w.scrollbarDragStartY = this.io.mouseY;
                    w.scrollbarDragStartScroll = w.scrollY;
                }
                if (w.scrollbarDragging) {
                    if (this.io.mouseDown[0]) {
                        float delta = this.io.mouseY - w.scrollbarDragStartY;
                        w.scrollY = Math.max(0, Math.min(w.scrollMaxY,
                            w.scrollbarDragStartScroll + delta * w.scrollMaxY / Math.max(1, trackH - thumbH)));
                    } else {
                        w.scrollbarDragging = false;
                    }
                }
                w.drawList.addRectFilled(trackX, trackY, w.x + w.w, trackY + trackH, styleColor(14)); // ScrollbarBg
                int grabColor = w.scrollbarDragging ? styleColor(17) : overThumb ? styleColor(16) : styleColor(15);
                w.drawList.addRectFilled(trackX, thumbY, w.x + w.w, thumbY + thumbH, grabColor, this.style.scrollbarRounding);
            }
            this.nextContentW = Float.NaN;
            this.nextContentH = Float.NaN;
            for (int i = 0; i < w.clipCount; i++) w.drawList.popClip();
            w.clipCount = 0;
            this.currentWindow = this.windowStack.isEmpty() ? null : this.windowStack.get(this.windowStack.size() - 1);
            this.currentDrawList = this.currentWindow == null ? null : this.currentWindow.drawList;
        }

        float titleHeightFor(Window w) {
            return (w.flags & 1) != 0 ? 0f : frameHeight();
        }

        void drawWindowChrome(Window w) {
            float bgAlpha = Math.max(0f, Math.min(1f, this.nextWindowBgAlpha));
            boolean isPopup = w.name.startsWith("##popup_") || w.name.startsWith("##menu_");
            boolean isMenuBar = w.menuBar && w.dockId == 0 && (w.flags & 1) != 0;
            if (w.dockId != 0) {
                if ((w.flags & 128) == 0) { // NoBackground
                    int bg = styleColor(2); // ImGuiCol_WindowBg
                    if (bgAlpha < 1f) {
                        bg = (bg & 0x00FFFFFF) | (((int) (((bg >>> 24) & 0xFF) * bgAlpha)) << 24);
                    }
                    w.drawList.addRectFilled(w.x, w.y, w.x + w.w, w.y + w.h, bg, this.style.windowRounding);
                }
                if (this.dockLayout != null && this.style.windowBorderSize > 0 && w.dockTabHeight > 0) {
                    // Host window border is drawn by the dock host in native; the
                    // separator already provides the visual edge.
                }
                return;
            }
            if ((w.flags & 128) == 0) { // NoBackground
                int bg = isPopup ? styleColor(4) : isMenuBar ? styleColor(13) : styleColor(2);
                if (bgAlpha < 1f) {
                    bg = (bg & 0x00FFFFFF) | (((int) (((bg >>> 24) & 0xFF) * bgAlpha)) << 24);
                }
                w.drawList.addRectFilled(w.x, w.y, w.x + w.w, w.y + w.h, bg, this.style.windowRounding);
            }
            if (this.style.windowBorderSize > 0) {
                w.drawList.addRect(w.x, w.y, w.x + w.w, w.y + w.h,
                    styleColor(5), this.style.windowRounding, this.style.windowBorderSize); // Border
            }
            if ((w.flags & 1) == 0) { // NoTitleBar
                int title = this.focusedWindowName != null && this.focusedWindowName.equals(w.name)
                    ? styleColor(11) : styleColor(10); // TitleBgActive / TitleBg
                w.drawList.addRectFilled(w.x, w.y, w.x + w.w, w.y + this.style.fontSize + this.style.framePaddingY * 2f,
                    title, this.style.windowRounding);
                w.drawList.addText(w.x + 8, w.y + this.style.framePaddingY, styleColor(0), displayLabel(w.name));
                if (w.openState != null) {
                    float bs = this.style.fontSize;
                    float bx = w.x + w.w - bs - 4;
                    float by = w.y + (titleHeightFor(w) - bs) * 0.5f;
                    boolean closeHovered = hit(bx, by, bs, bs);
                    w.drawList.addText(bx + 3, by, closeHovered
                        ? styleColor(0) : this.style.colorU32(0, 0.55f * this.globalAlpha), "x");
                    if (closeHovered && this.io.mouseReleased[0]) {
                        setBool(w.openState, false);
                    }
                }
                float titleBottom = w.y + this.style.fontSize + this.style.framePaddingY * 2f;
                String dragId = "##drag_" + w.name;
                // Only start dragging from a press *inside* this title bar. The
                // old code checked only mouseY, so any click in the world whose Y
                // happened to overlap a title row teleported that window.
                boolean overClose = false;
                if (w.openState != null) {
                    float bs = this.style.fontSize;
                    float bx = w.x + w.w - bs - 4;
                    float by = w.y + (this.style.fontSize + this.style.framePaddingY * 2f - bs) * 0.5f;
                    overClose = this.io.mouseX >= bx && this.io.mouseX <= bx + bs
                        && this.io.mouseY >= by && this.io.mouseY <= by + bs;
                }
                boolean overTitle = !overClose && (w.flags & 4) == 0 // NoMove
                    && this.io.mouseX >= w.x && this.io.mouseX <= w.x + w.w
                    && this.io.mouseY >= w.y && this.io.mouseY <= titleBottom;
                if (overTitle && this.io.mousePressed[0] && this.activeId == null) {
                    this.activeId = dragId;
                    w.dragging = true;
                    w.dragX = this.io.mouseX - w.x;
                    w.dragY = this.io.mouseY - w.y;
                }
                if (w.dragging) {
                    if (this.io.mouseDown[0] && dragId.equals(this.activeId)) {
                        w.x = this.io.mouseX - w.dragX;
                        w.y = this.io.mouseY - w.dragY;
                    } else {
                        w.dragging = false;
                    }
                }
            }
            // Bottom-right resize grip for floating windows.
            if (!w.mainDocked && (w.flags & 2) == 0) {
                float grip = 14;
                boolean overGrip = this.io.mouseX >= w.x + w.w - grip && this.io.mouseX <= w.x + w.w
                    && this.io.mouseY >= w.y + w.h - grip && this.io.mouseY <= w.y + w.h;
                if (overGrip && this.io.mousePressed[0]) {
                    w.resizing = true;
                    w.resizeStartMouseX = this.io.mouseX;
                    w.resizeStartMouseY = this.io.mouseY;
                    w.resizeStartW = w.w;
                    w.resizeStartH = w.h;
                }
                if (w.resizing) {
                    if (this.io.mouseDown[0]) {
                        w.w = Math.max(120, w.resizeStartW + this.io.mouseX - w.resizeStartMouseX);
                        w.h = Math.max(80, w.resizeStartH + this.io.mouseY - w.resizeStartMouseY);
                    } else {
                        w.resizing = false;
                    }
                }
                int gripColor = w.resizing ? styleColor(30) : overGrip ? styleColor(29) : styleColor(28);
                w.drawList.addLine(w.x + w.w - 12, w.y + w.h - 4, w.x + w.w - 4, w.y + w.h - 12, gripColor, 1);
                w.drawList.addLine(w.x + w.w - 8, w.y + w.h - 4, w.x + w.w - 4, w.y + w.h - 8, gripColor, 1);
            }
        }

        // --------------------------------------------------------------
        // Layout helpers
        // --------------------------------------------------------------

        void itemSize(float width, float height) {
            Window w = currentWindow();
            float x = w.cursorX;
            float y = w.cursorY;
            float wd = width <= 0 ? Math.max(1, w.contentW - (x - w.contentX)) : width;
            float hd = height <= 0 ? this.style.fontSize + this.style.framePaddingY * 2f : height;
            // imgui.cpp ItemSize(): CursorPos/PrevLine/CurrLine accounting.
            float lineY1 = w.isSameLine ? w.prevLineY : y;
            float lineHeight = Math.max(w.currLineSizeY, y - lineY1 + hd);
            w.prevLineX = x + wd;
            w.prevLineY = lineY1;
            w.cursorX = w.lineStartX;
            w.cursorY = lineY1 + lineHeight + this.style.itemSpacingY;
            w.contentMaxX = Math.max(w.contentMaxX, x + wd);
            w.contentMaxY = Math.max(w.contentMaxY, w.cursorY - this.style.itemSpacingY);
            w.prevLineSizeY = lineHeight;
            w.currLineSizeY = 0f;
            w.isSameLine = false;
            w.lineHeight = lineHeight;
            w.lineY = lineY1;
            w.lastItemRight = w.x + x + wd;
            w.maxContentX = Math.max(w.maxContentX, x + wd);
            this.lastItemRect[0] = w.x + x;
            this.lastItemRect[1] = w.y + y - w.scrollY;
            this.lastItemRect[2] = w.x + x + wd;
            this.lastItemRect[3] = w.y + y + hd - w.scrollY;
            this.nextItemWidth = 0f;
        }

        void sameLine(float offset) {
            sameLine(offset, -1);
        }

        void sameLine(float offset, float spacing) {
            Window w = currentWindow();
            if (offset != 0.0f) {
                if (spacing < 0.0f) spacing = 0.0f;
                w.cursorX = offset + spacing;
            } else {
                if (spacing < 0.0f) spacing = this.style.itemSpacingX;
                w.cursorX = w.prevLineX + spacing;
            }
            w.cursorY = w.prevLineY;
            w.isSameLine = true;
        }

        void newLine() {
            Window w = currentWindow();
            w.cursorX = w.lineStartX;
            w.cursorY += w.currLineSizeY + this.style.itemSpacingY;
            w.prevLineX = w.cursorX;
            w.prevLineY = w.cursorY;
            w.currLineSizeY = 0f;
            w.isSameLine = false;
        }

        float contentAvailX() {
            Window w = currentWindow();
            float max = w.table != null && w.table.cellActive ? w.workMaxX : w.contentX + w.contentW;
            return Math.max(1f, max - w.cursorX);
        }

        float contentAvailY() {
            Window w = currentWindow();
            float max = w.table != null && w.table.cellActive ? w.workMaxY : w.contentY + w.contentH;
            return Math.max(1f, max - w.cursorY);
        }

        float currentFontSize() {
            return this.style.fontSize;
        }

        float frameHeight() {
            return currentFontSize() + this.style.framePaddingY * 2f;
        }

        /** ImGui ItemWidthDefault / CalcItemWidth() semantics. */
        float calcItemWidthValue() {
            if (this.nextItemWidth > 0) return (float) (int) this.nextItemWidth;
            Window tw = currentWindow();
            if (tw != null && tw.tableItemWidth > 0) return (float) (int) tw.tableItemWidth;
            if (this.itemWidthPushed != 0) {
                if (this.itemWidthPushed < 0) {
                    Window pw = currentWindow();
                    return Math.max(1f, pw.contentX + pw.contentW - pw.cursorX + this.itemWidthPushed);
                }
                return (float) (int) this.itemWidthPushed;
            }
            Window w = currentWindow();
            // imgui.cpp Begin(): ItemWidthDefault = Size.x * 0.65f for
            // resizable windows, FontSize * 16 for tooltip/unset/auto-resize.
            boolean isResizable = w != null && w.w > 0
                && !w.name.startsWith("##tooltip")
                && (w.flags & 64) == 0; // AlwaysAutoResize
            float def = isResizable ? w.w * 0.65f : currentFontSize() * 16f;
            return Math.max(1f, (float) (int) def);
        }

        void text(String text) {
            Window w = currentWindow();
            String shown = visibleText(text);
            debugWidget("text", shown, w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, 0, this.style.fontSize);
            float size = this.style.fontSize;
            float width = this.atlas.measure(shown, size);
            w.drawList.addText(w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, styleColor(0), shown);
            itemSize(width, size);
        }

        void textWrapped(String text) {
            Window w = currentWindow();
            text = visibleText(text);
            float max = this.textWrapPos > 0 ? this.textWrapPos : w.w - w.cursorX;
            List<String> lines = wrap(text, max);
            for (String line : lines) {
                text(line);
            }
        }

        void textColored(float r, float g, float b, float a, String text) {
            Window w = currentWindow();
            String shown = visibleText(text);
            debugWidget("textColored", shown, w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, 0, this.style.fontSize);
            float width = this.atlas.measure(shown, this.style.fontSize);
            w.drawList.addText(w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, color(r, g, b, a), shown);
            itemSize(width, this.style.fontSize);
        }

        void separator() {
            Window w = currentWindow();
            float y = w.y + w.cursorY - w.scrollY + this.style.itemSpacingY * 0.5f;
            w.drawList.addLine(w.x, y, w.x + w.w, y, styleColor(27), 1);
            itemSize(0, 1 + this.style.itemSpacingY);
        }

        void separatorText(String text) {
            separator();
            text(text);
            separator();
        }

        // --------------------------------------------------------------
        // Widgets
        // --------------------------------------------------------------

        boolean button(String label, float width, float height) {
            Window w = currentWindow();
            float h = height > 0 ? height : frameHeight();
            label = visibleText(label);
            float wd = width > 0 ? width : 0;
            if (wd <= 0) {
                // ButtonEx(): text width + FramePadding.x*2, no artificial minimum.
                wd = Math.max(4, this.atlas.measure(label, this.style.fontSize) + this.style.framePaddingX * 2f);
            }
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            if (Boolean.getBoolean("noimgui.debug.glyphs") && label.length() == 1
                && label.charAt(0) >= 0xE000 && this.widgetDebugCount++ < 400) {
                NoNativeMod.LOGGER.info("ICONBTN U+{} x={} y={} w={} h={} clip=({},{}..{},{}) win={}",
                    String.format("%04X", (int) label.charAt(0)), x, y, wd, h,
                    w.drawList.clipMinX, w.drawList.clipMinY, w.drawList.clipMaxX, w.drawList.clipMaxY, w.name);
            }
            long navItem = navRegister(w, id, x, y, wd, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, wd, h);
            boolean clicked = navActivated
                || (hovered && this.io.mouseReleased[0] && this.activeId != null && this.activeId.equals(id));
            if (hovered && this.io.mousePressed[0]) {
                this.activeId = id;
            }
            if (hovered) {
                this.hotId = id;
            }
            boolean active = this.activeId != null && this.activeId.equals(id);
            int bg = active ? styleColor(23) : hovered ? styleColor(22) : styleColor(21);
            w.drawList.addRectFilled(x, y, x + wd, y + h, bg, this.style.frameRounding);
            if (this.style.frameBorderSize > 0) {
                w.drawList.addRect(x, y, x + wd, y + h, styleColor(5), this.style.frameRounding, this.style.frameBorderSize);
            }
            if (focused) {
                w.drawList.addRect(x, y, x + wd, y + h, color(0.95f, 0.75f, 0.25f, 1f),
                    this.style.frameRounding, 1);
            }
            float tw = this.atlas.measure(label, this.style.fontSize);
            float tx = x + (wd - tw) * 0.5f;
            float ty = y + (h - this.style.fontSize) * 0.5f;
            w.drawList.addText(tx, ty, styleColor(0), label);
            this.lastItemId = id;
            itemSize(wd, h);
            this.lastItemHovered = hovered;
            this.lastItemActive = this.activeId != null && this.activeId.equals(this.lastItemId);
            this.lastItemClicked = (hovered && this.io.mousePressed[0]) || navActivated;
            this.lastItemClickedButton = 0;
            if (clicked) {
                this.activeId = null;
            }
            return clicked;
        }

        boolean smallButton(String label) {
            return button(label, this.atlas.measure(label, this.style.fontSize) + 8, this.style.fontSize + 4);
        }

        boolean invisibleButton(String label, float width, float height) {
            Window w = currentWindow();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, height);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean hovered = hit(x, y, width, height);
            boolean clicked = navActivated || (hovered && this.io.mouseReleased[0]);
            this.lastItemId = id;
            itemSize(width, height);
            this.lastItemHovered = hovered;
            this.lastItemClicked = (hovered && this.io.mousePressed[0]) || navActivated;
            this.lastItemClickedButton = 0;
            return clicked;
        }

        boolean checkbox(String label, Object value) {
            Window w = currentWindow();
            label = visibleText(label);
            float size = frameHeight();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            float wd = size + this.style.itemInnerSpacingX + this.atlas.measure(label, this.style.fontSize);
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, wd, frameHeight());
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, wd, size);
            boolean checked = bool(value);
            if ((hovered && this.io.mouseReleased[0]) || navActivated) {
                checked = !checked;
                setBool(value, checked);
                this.lastItemEdited = true;
            } else {
                this.lastItemEdited = false;
            }
            int checkBg = hovered ? styleColor(8) : styleColor(7); // FrameBgHovered / FrameBg
            w.drawList.addRectFilled(x, y, x + size, y + size, checkBg, 0);
            if (checked) {
                // RenderCheckMark(): short down-stroke + long up-stroke.
                int check = styleColor(18);
                w.drawList.addLine(x + size * 0.22f, y + size * 0.52f, x + size * 0.42f, y + size * 0.75f, check, 2);
                w.drawList.addLine(x + size * 0.42f, y + size * 0.75f, x + size * 0.80f, y + size * 0.22f, check, 2);
            }
            w.drawList.addRect(x, y, x + size, y + size, styleColor(5), 0, 1);
            if (focused) {
                w.drawList.addRect(x, y, x + size, y + size, color(0.95f, 0.75f, 0.25f, 1f), 3, 1);
            }
            w.drawList.addText(x + size + this.style.itemInnerSpacingX,
                y + (size - this.style.fontSize) * 0.5f, styleColor(0), label);
            debugWidget("checkbox", label, x, y, wd, frameHeight());
            this.lastItemId = id;
            itemSize(wd, frameHeight());
            this.lastItemHovered = hovered;
            this.lastItemClicked = (hovered && this.io.mousePressed[0]) || navActivated;
            this.lastItemClickedButton = 0;
            return this.lastItemEdited;
        }

        boolean radioButton(String label, boolean active) {
            Window w = currentWindow();
            label = visibleText(label);
            float size = frameHeight();
            float h = frameHeight();
            float wd = size + this.style.itemInnerSpacingX + this.atlas.measure(label, this.style.fontSize);
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            boolean hovered = hit(x, y, wd, h);
            boolean clicked = (hovered && this.io.mouseReleased[0])
                || this.nav.isActivated(navRegister(w, id, x, y, wd, h));
            float r = size * 0.5f;
            float cx = x + r;
            float cy = y + h * 0.5f;
            w.drawList.addCircleFilled(cx, cy, r, hovered ? styleColor(8) : styleColor(7), 12);
            w.drawList.addCircle(cx, cy, r, styleColor(5), 12, 1);
            if (active) {
                w.drawList.addCircleFilled(cx, cy, r * 0.45f, styleColor(18), 12);
            }
            w.drawList.addText(x + size + this.style.itemInnerSpacingX,
                y + (h - this.style.fontSize) * 0.5f, styleColor(0), label);
            this.lastItemId = id;
            itemSize(wd, h);
            this.lastItemHovered = hovered;
            this.lastItemClicked = clicked;
            this.lastItemClickedButton = 0;
            return clicked;
        }

        boolean selectable(String label, boolean selected, int flags, float width, float height) {
            Window w = currentWindow();
            label = visibleText(label);
            float h = height > 0 ? height : this.style.fontSize + this.style.framePaddingY * 2f;
            float wd = width > 0 ? width : Math.max(1, w.contentX + w.contentW - w.cursorX);
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, wd, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, wd, h);
            boolean clicked = navActivated || (hovered && this.io.mouseReleased[0]);
            if (selected) {
                w.drawList.addRectFilled(x, y, x + wd, y + h, styleColor(24)); // Header
            } else if (hovered) {
                w.drawList.addRectFilled(x, y, x + wd, y + h, styleColor(25)); // HeaderHovered
            }
            if (focused) {
                w.drawList.addRect(x, y, x + wd, y + h, color(0.95f, 0.75f, 0.25f, 1f), 0, 1);
            }
            w.drawList.addText(x + 4, y + this.style.framePaddingY, styleColor(0), label);
            this.lastItemId = id;
            itemSize(wd, h);
            this.lastItemHovered = hovered;
            this.lastItemClicked = clicked;
            this.lastItemClickedButton = 0;
            return clicked;
        }

        boolean sliderFloat(String label, Object value, float min, float max, String format) {
            Window w = currentWindow();
            float h = frameHeight();
            float width = calcItemWidthValue();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, width, h) && this.disabledDepth == 0;
            float current = floatValue(value);
            boolean changed = false;
            if (navActivated) {
                this.activeId = id;
                this.keyboardFocusId = id;
            }
            if (hovered && this.io.mousePressed[0]) {
                this.activeId = id;
            }
            if (this.activeId != null && this.activeId.equals(id) && this.io.mouseDown[0]) {
                float t = Math.max(0, Math.min(1, (this.io.mouseX - x) / width));
                float next = min + (max - min) * t;
                if (next != current) {
                    setFloat(value, next);
                    changed = true;
                }
            }
            if (this.io.mouseReleased[0] && this.activeId != null && this.activeId.equals(id)) {
                this.activeId = null;
            }
            float normalized = max > min ? (floatValue(value) - min) / (max - min) : 0;
            w.drawList.addRectFilled(x, y, x + width, y + h, styleColor(7), this.style.frameRounding);
            float grabW = Math.max(this.style.grabMinSize, this.style.framePaddingX * 2 + 8);
            float grabX = x + Math.max(0, Math.min(1, normalized)) * Math.max(0, width - grabW);
            w.drawList.addRectFilled(grabX, y, grabX + grabW, y + h,
                this.activeId != null && this.activeId.equals(id) ? styleColor(20) : styleColor(19),
                this.style.grabRounding);
            if (this.style.frameBorderSize > 0) {
                w.drawList.addRect(x, y, x + width, y + h, styleColor(5), this.style.frameRounding, this.style.frameBorderSize);
            }
            if (focused) {
                w.drawList.addRect(x, y, x + width, y + h, color(0.95f, 0.75f, 0.25f, 1f), 3, 1);
            }
            String shown = format == null || format.isEmpty() ? String.format(Locale.ROOT, "%.2f", floatValue(value)) : String.format(Locale.ROOT, format, floatValue(value));
            w.drawList.addText(x + this.style.framePaddingX, y + this.style.framePaddingY, styleColor(0), label + "  " + shown);
            this.lastItemId = id;
            itemSize(width, h);
            this.lastItemHovered = hovered;
            this.lastItemActive = id.equals(this.activeId);
            this.lastItemEdited = changed;
            return changed;
        }

        boolean sliderInt(String label, Object value, int min, int max, String format) {
            Window w = currentWindow();
            float h = frameHeight();
            float width = calcItemWidthValue();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, width, h) && this.disabledDepth == 0;
            int current = intValue(value);
            boolean changed = false;
            if (navActivated) {
                this.activeId = id;
                this.keyboardFocusId = id;
            }
            if (hovered && this.io.mousePressed[0]) {
                this.activeId = id;
            }
            if (this.activeId != null && this.activeId.equals(id) && this.io.mouseDown[0]) {
                int next = min + Math.round(Math.max(0, Math.min(1, (this.io.mouseX - x) / width)) * (max - min));
                if (next != current) {
                    setInt(value, next);
                    changed = true;
                }
            }
            if (this.io.mouseReleased[0] && id.equals(this.activeId)) {
                this.activeId = null;
            }
            float normalized = max > min ? (intValue(value) - min) / (float) (max - min) : 0;
            w.drawList.addRectFilled(x, y, x + width, y + h, styleColor(7), this.style.frameRounding);
            float grabW = Math.max(this.style.grabMinSize, this.style.framePaddingX * 2 + 8);
            float grabX = x + Math.max(0, Math.min(1, normalized)) * Math.max(0, width - grabW);
            w.drawList.addRectFilled(grabX, y, grabX + grabW, y + h,
                this.activeId != null && this.activeId.equals(id) ? styleColor(20) : styleColor(19),
                this.style.grabRounding);
            if (this.style.frameBorderSize > 0) {
                w.drawList.addRect(x, y, x + width, y + h, styleColor(5), this.style.frameRounding, this.style.frameBorderSize);
            }
            if (focused) {
                w.drawList.addRect(x, y, x + width, y + h, color(0.95f, 0.75f, 0.25f, 1f), 3, 1);
            }
            w.drawList.addText(x + 6, y + this.style.framePaddingY, color(1, 1, 1, 1),
                label + "  " + (format == null || format.isEmpty() ? String.valueOf(intValue(value)) : String.format(Locale.ROOT, format, intValue(value))));
            this.lastItemId = id;
            itemSize(width, h);
            this.lastItemHovered = hovered;
            this.lastItemActive = id.equals(this.activeId);
            this.lastItemEdited = changed;
            return changed;
        }

        boolean inputNumber(String label, Object value, boolean integer) {
            if (value == null) {
                text(label);
                return false;
            }
            Window w = currentWindow();
            float h = frameHeight();
            float width = calcItemWidthValue();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, width, h);
            String current = integer ? String.valueOf(intValue(value)) : String.format(Locale.ROOT, "%.4f", floatValue(value));
            boolean changed = false;

            if (this.io.mousePressed[0] && !hovered && id.equals(this.activeInput)) {
                this.activeInput = null;
                if (id.equals(this.activeId)) {
                    this.activeId = null;
                }
                this.wantTextInput = false;
            }
            if (hovered && this.io.mousePressed[0]) {
                this.activeInput = id;
                this.activeId = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (navActivated) {
                this.activeInput = id;
                this.activeId = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (this.keyboardFocusRequested && this.activeInput == null) {
                this.activeInput = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (id.equals(this.activeInput)) {
                this.wantTextInput = true;
                StringBuilder builder = new StringBuilder(current);
                for (Object ch : this.io.chars) {
                    String s = ch instanceof Character c ? String.valueOf(c) : String.valueOf(ch);
                    for (int i = 0; i < s.length(); i++) {
                        char c = s.charAt(i);
                        if (Character.isDigit(c) || c == '.' || c == '-' || c == '+') {
                            builder.append(c);
                            changed = true;
                        }
                    }
                }
                if (this.io.keysPressed.contains(8) && !builder.isEmpty()) {
                    builder.deleteCharAt(builder.length() - 1);
                    changed = true;
                }
                if (this.io.keysPressed.contains(13) || this.io.keysPressed.contains(27)) {
                    this.activeInput = null;
                    if (id.equals(this.activeId)) {
                        this.activeId = null;
                    }
                    this.wantTextInput = false;
                }
                if (changed) {
                    try {
                        if (integer) {
                            setInt(value, Integer.parseInt(builder.toString()));
                        } else {
                            setFloat(value, Float.parseFloat(builder.toString()));
                        }
                    } catch (NumberFormatException ignored) {
                    }
                }
            }

            w.drawList.addRectFilled(x, y, x + width, y + h, hovered ? styleColor(8) : styleColor(7), this.style.frameRounding);
            if (this.style.frameBorderSize > 0) {
                w.drawList.addRect(x, y, x + width, y + h, styleColor(5), this.style.frameRounding, this.style.frameBorderSize);
            }
            if (focused) {
                w.drawList.addRect(x, y, x + width, y + h, color(0.95f, 0.75f, 0.25f, 1f), 3, 1);
            }
            String shown = integer ? String.valueOf(intValue(value)) : String.format(Locale.ROOT, "%.3f", floatValue(value));
            w.drawList.addText(x + 4, y + this.style.framePaddingY, styleColor(0), shown);
            if (id.equals(this.activeInput)) {
                float caret = x + 4 + this.atlas.measure(shown, this.style.fontSize);
                w.drawList.addLine(caret, y + 3, caret, y + h - 3, color(1, 1, 1, 1), 1);
            }
            this.lastItemId = id;
            itemSize(width, h);
            this.lastItemHovered = hovered;
            this.lastItemActive = id.equals(this.activeInput);
            this.lastItemEdited = changed;
            return changed;
        }

        boolean inputText(String label, Object value, int flags) {
            if (value == null) {
                text(label);
                return false;
            }
            Window w = currentWindow();
            float h = frameHeight();
            float width = calcItemWidthValue();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, h);
            boolean navActivated = this.nav.isActivated(navItem);
            boolean focused = this.nav.isFocused(navItem);
            boolean hovered = hit(x, y, width, h);
            String current = stringValue(value);
            boolean changed = false;

            if (this.io.mousePressed[0] && !hovered && id.equals(this.activeInput)) {
                this.activeInput = null;
                if (id.equals(this.activeId)) {
                    this.activeId = null;
                }
                this.wantTextInput = false;
            }
            if (hovered && this.io.mousePressed[0]) {
                this.activeInput = id;
                this.activeId = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (navActivated) {
                this.activeInput = id;
                this.activeId = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (this.keyboardFocusRequested && this.activeInput == null) {
                this.activeInput = id;
                this.keyboardFocusId = id;
                this.wantTextInput = true;
            }
            if (this.activeInput != null && this.activeInput.equals(id)) {
                this.wantTextInput = true;
                InputTextModel model = this.inputModels.computeIfAbsent(id, k -> new InputTextModel());
                if (!this.inputOriginals.containsKey(id)) {
                    model.setText(current);
                    model.setCursorPos(model.length());
                    this.inputOriginals.put(id, current);
                }
                if ((flags & 32) != 0) model.setPassword(true);
                boolean edited = false;
                for (Object ch : this.io.chars) {
                    if (ch instanceof Character c && c >= 32) {
                        model.insertText(String.valueOf(c));
                        edited = true;
                    } else if (ch instanceof String str) {
                        model.insertText(str);
                        edited = true;
                    }
                }
                int[] pressed = this.io.keysPressed.stream().mapToInt(Integer::intValue).toArray();
                boolean shift = this.io.shift;
                boolean ctrl = this.io.ctrl;
                boolean alt = this.io.alt;
                boolean confirm = false;
                boolean cancel = false;
                for (int key : pressed) {
                    int modelKey = switch (key) {
                        case 8, 259 -> InputTextModel.KEY_BACKSPACE;
                        case 13, 257 -> InputTextModel.KEY_ENTER;
                        case 27, 256 -> InputTextModel.KEY_ESCAPE;
                        case 9, 258 -> InputTextModel.KEY_TAB;
                        case 261 -> 522; // delete
                        case 263 -> 513; // left
                        case 262 -> 514; // right
                        case 265 -> 515; // up
                        case 264 -> 516; // down
                        case 268 -> 519; // home
                        case 269 -> 520; // end
                        default -> key >= 512 ? key : -1;
                    };
                    if (modelKey < 0) continue;
                    if (modelKey == InputTextModel.KEY_ENTER) confirm = true;
                    if (modelKey == InputTextModel.KEY_ESCAPE) cancel = true;
                    if (model.key(modelKey, ctrl, shift, alt)) edited = true;
                }
                if (edited) {
                    setString(value, model.getText());
                    changed = true;
                }
                if (confirm || cancel) {
                    if (cancel) setString(value, this.inputOriginals.getOrDefault(id, current));
                    this.activeInput = null;
                    if (id.equals(this.activeId)) this.activeId = null;
                    this.wantTextInput = false;
                    this.inputOriginals.remove(id);
                }
            }

            w.drawList.addRectFilled(x, y, x + width, y + h, color(0.10f, 0.10f, 0.12f, 1f), 3);
            w.drawList.addRect(x, y, x + width, y + h, color(0.30f, 0.30f, 0.35f, 1f), 3, 1);
            if (focused) {
                w.drawList.addRect(x, y, x + width, y + h, color(0.95f, 0.75f, 0.25f, 1f), 3, 1);
            }
            String shown = stringValue(value);
            float textScroll = 0f;
            int caretPos = -1;
            InputTextModel activeModel = id.equals(this.activeInput) ? this.inputModels.get(id) : null;
            if (activeModel != null) {
                shown = activeModel.displayText();
                activeModel.ensureCursorVisible(width - 8, c -> this.atlas.measure(String.valueOf(c), this.style.fontSize));
                textScroll = activeModel.scrollX();
                caretPos = activeModel.cursorPos();
            }
            w.drawList.pushClip(x + 2, y + 1, x + width - 2, y + h - 1);
            w.drawList.addText(x + 4 - textScroll, y + this.style.framePaddingY,
                styleColor(0), shown);
            if (caretPos >= 0) {
                float caret = x + 4 + this.atlas.measure(shown.substring(0, Math.min(caretPos, shown.length())), this.style.fontSize) - textScroll;
                w.drawList.addLine(caret, y + 3, caret, y + h - 3, color(1, 1, 1, 1), 1);
            }
            w.drawList.popClip();
            this.lastItemId = id;
            itemSize(width, h);
            this.lastItemHovered = hovered;
            this.lastItemEdited = changed;
            this.lastItemDeactivatedAfterEdit = changed && (this.io.keysPressed.contains(13) || this.io.keysPressed.contains(27));
            return changed;
        }

        boolean beginCombo(String label, String preview, int flags) {
            Window w = currentWindow();
            float width = calcItemWidthValue();
            float h = frameHeight();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            String id = currentId(label);
            long navItem = navRegister(w, id, x, y, width, h);
            boolean hovered = hit(x, y, width, h);
            boolean clicked = hovered && this.io.mouseReleased[0];
            w.drawList.addRectFilled(x, y, x + width, y + h,
                hovered ? styleColor(8) : styleColor(7), this.style.frameRounding);
            if (this.style.frameBorderSize > 0) {
                w.drawList.addRect(x, y, x + width, y + h, styleColor(5), this.style.frameRounding,
                    this.style.frameBorderSize);
            }
            String shown = preview == null ? "" : preview;
            float ty = y + (h - this.style.fontSize) * 0.5f;
            w.drawList.addText(x + this.style.framePaddingX, ty, styleColor(0), shown);
            // Arrow at the right edge.
            float ax = x + width - this.style.framePaddingX - 6;
            float ay = y + h * 0.5f;
            w.drawList.addTriangle(ax, ay - 3, ax + 6, ay - 3, ax + 3, ay + 3, styleColor(0));
            itemSize(width, h);
            if (clicked) {
                Popup existing = this.popupMap.get(label);
                if (existing != null && existing.open) {
                    existing.open = false;
                } else {
                    openPopup(label);
                    this.popupX = this.lastItemRect[0];
                    this.popupY = this.lastItemRect[3] + 2;
                }
            }
            return beginPopup(label, 0);
        }

        void endCombo() {
            endPopup();
        }

        boolean combo(String label, int current, Object items, int height) {
            String preview = "";
            int count = 0;
            if (items instanceof String[] arr) {
                count = arr.length;
                if (current >= 0 && current < count) preview = arr[current];
            } else if (items instanceof List<?> list) {
                count = list.size();
                if (current >= 0 && current < count) preview = String.valueOf(list.get(current));
            }
            boolean changed = false;
            if (beginCombo(label, preview, 0)) {
                for (int i = 0; i < count; i++) {
                    String item = items instanceof String[] arr ? arr[i] : String.valueOf(((List<?>) items).get(i));
                    if (selectable(item, i == current, 0, 0, 0)) {
                        this.tempObject = i;
                        changed = true;
                    }
                }
                endCombo();
            }
            return changed;
        }

        boolean collapsingHeader(String label, int flags) {
            Window w = currentWindow();
            label = visibleText(label);
            float h = frameHeight();
            float width = Math.max(1, w.contentX + w.contentW - w.cursorX);
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            int key = currentId(label).hashCode();
            int[] state = this.storage.computeIfAbsent(key, k -> new int[]{(flags & 32) != 0 ? 1 : 0}); // DefaultOpen
            boolean hovered = hit(x, y, width, h);
            boolean active = this.activeId != null && this.activeId.equals("##tree_" + key);
            if (hovered && this.io.mousePressed[0]) {
                this.activeId = "##tree_" + key;
                this.hotId = "##tree_" + key;
            }
            boolean clicked = hovered && this.io.mouseReleased[0] && active;
            if (clicked) {
                state[0] = state[0] == 0 ? 1 : 0;
                this.activeId = null;
            }
            boolean open = state[0] != 0;
            int bg = (hovered || active) ? styleColor(25) : (open ? styleColor(24) : 0);
            if (bg != 0) {
                w.drawList.addRectFilled(x, y, x + width, y + h, bg);
            }
            float pad = this.style.framePaddingX;
            float arrowCx = x + pad + 4;
            float arrowCy = y + h * 0.5f;
            if (open) {
                w.drawList.addTriangle(arrowCx - 5, arrowCy - 3, arrowCx + 3, arrowCy - 3, arrowCx - 1, arrowCy + 3, styleColor(0));
            } else {
                w.drawList.addTriangle(arrowCx - 3, arrowCy - 5, arrowCx - 3, arrowCy + 3, arrowCx + 3, arrowCy - 1, styleColor(0));
            }
            w.drawList.addText(x + pad + 16, y + (h - this.style.fontSize) * 0.5f, styleColor(0), label);
            this.lastItemId = "##tree_" + key;
            itemSize(width, h);
            this.lastItemHovered = hovered;
            this.lastItemClicked = clicked;
            this.lastItemClickedButton = 0;
            return open;
        }

        boolean treeNode(String label) {
            return collapsingHeader(label, 0);
        }

        void progressBar(float fraction, float width, float height, String overlay) {
            Window w = currentWindow();
            float wd = width > 0 ? width : calcItemWidthValue();
            float h = height > 0 ? height : this.style.fontSize + this.style.framePaddingY * 2f;
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            w.drawList.addRectFilled(x, y, x + wd, y + h, styleColor(7), this.style.frameRounding);
            w.drawList.addRectFilled(x, y, x + wd * Math.max(0, Math.min(1, fraction)), y + h, styleColor(38), this.style.frameRounding);
            if (overlay != null && !overlay.isEmpty()) {
                w.drawList.addText(x + 6, y + this.style.framePaddingY, color(1, 1, 1, 1), overlay);
            }
            itemSize(wd, h);
        }

        void image(Object texture, Object size, Object uv0, Object uv1, int tint) {
            Window w = currentWindow();
            float iw = size != null && size.getClass().getSimpleName().equals("ImVec2") ? f(Reflect.get(size, "x")) : 32;
            float ih = size != null && size.getClass().getSimpleName().equals("ImVec2") ? f(Reflect.get(size, "y")) : 32;
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            long id = texture instanceof Number n ? n.longValue() : 0;
            w.drawList.setTexture(id);
            float u0 = 0, v0 = 0, u1 = 1, v1 = 1;
            if (uv0 != null && uv0.getClass().getSimpleName().equals("ImVec2")) {
                u0 = f(Reflect.get(uv0, "x")); v0 = f(Reflect.get(uv0, "y"));
            }
            if (uv1 != null && uv1.getClass().getSimpleName().equals("ImVec2")) {
                u1 = f(Reflect.get(uv1, "x")); v1 = f(Reflect.get(uv1, "y"));
            }
            w.drawList.addQuad(x, y, x + iw, y, x + iw, y + ih, x, y + ih, u0, v0, u1, v1, tint);
            w.drawList.setTexture(this.atlas.texId);
            itemSize(iw, ih);
        }

        boolean imageButton(String label, Object texture, Object size, Object uv0, Object uv1, int bg, int tint) {
            Window w = currentWindow();
            float iw = size != null && size.getClass().getSimpleName().equals("ImVec2") ? f(Reflect.get(size, "x")) : 32;
            float ih = size != null && size.getClass().getSimpleName().equals("ImVec2") ? f(Reflect.get(size, "y")) : 32;
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            boolean hovered = hit(x, y, iw, ih);
            boolean clicked = hovered && this.io.mouseReleased[0];
            long id = texture instanceof Number n ? n.longValue() : 0;
            if (bg != 0) w.drawList.addRectFilled(x, y, x + iw, y + ih, bg);
            w.drawList.setTexture(id);
            float u0 = 0, v0 = 0, u1 = 1, v1 = 1;
            if (uv0 != null && uv0.getClass().getSimpleName().equals("ImVec2")) {
                u0 = f(Reflect.get(uv0, "x")); v0 = f(Reflect.get(uv0, "y"));
            }
            if (uv1 != null && uv1.getClass().getSimpleName().equals("ImVec2")) {
                u1 = f(Reflect.get(uv1, "x")); v1 = f(Reflect.get(uv1, "y"));
            }
            w.drawList.addQuad(x, y, x + iw, y, x + iw, y + ih, x, y + ih, u0, v0, u1, v1, tint);
            w.drawList.setTexture(this.atlas.texId);
            itemSize(iw, ih);
            this.lastItemHovered = hovered;
            this.lastItemClicked = clicked;
            this.lastItemClickedButton = 0;
            return clicked;
        }

        boolean treeNodeEx(String label, int flags) {
            return collapsingHeader(label, flags);
        }

        boolean colorPicker(String label, Object value, int flags) {
            Window w = currentWindow();
            float width = calcItemWidthValue();
            float height = frameHeight();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            boolean hovered = hit(x, y, width, height);
            boolean changed = false;
            float[] rgb = null;
            if (value instanceof float[] arr && arr.length >= 3) rgb = arr;
            if (rgb != null) {
                int bars = rgb.length >= 4 ? 4 : 3;
                float barW = width / bars;
                for (int i = 0; i < bars; i++) {
                    float bx = x + i * barW;
                    boolean bh = hit(bx, y, barW, height);
                    if (bh && this.io.mouseDown[0]) {
                        float t = Math.max(0, Math.min(1, (this.io.mouseX - bx) / barW));
                        if (rgb[i] != t) { rgb[i] = t; changed = true; }
                    }
                    w.drawList.addRectFilled(bx, y, bx + barW, y + height, color(0.10f, 0.10f, 0.12f, 1f));
                    w.drawList.addRectFilled(bx, y, bx + barW * Math.max(0, Math.min(1, rgb[i])), y + height,
                        i == 0 ? color(0.9f, 0.2f, 0.2f, 1f) : i == 1 ? color(0.2f, 0.9f, 0.2f, 1f) : i == 2 ? color(0.2f, 0.2f, 0.9f, 1f) : color(0.8f, 0.8f, 0.8f, 1f));
                }
            } else if (value != null) {
                try {
                    float r = f(Reflect.get(value, "x")), g = f(Reflect.get(value, "y")), b = f(Reflect.get(value, "z"));
                    w.drawList.addRectFilled(x, y, x + width, y + height, color(r, g, b, 1f));
                } catch (Throwable ignored) {
                }
            }
            itemSize(width, height);
            this.lastItemHovered = hovered;
            this.lastItemEdited = changed;
            return changed;
        }

        boolean colorButton(String label, Object color, int flags, float width, float height) {
            Window w = currentWindow();
            float wd = width > 0 ? width : 40;
            float h = height > 0 ? height : frameHeight();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY;
            boolean hovered = hit(x, y, wd, h);
            boolean clicked = hovered && this.io.mouseReleased[0];
            float r = 1, g = 1, b = 1, a = 1;
            if (color != null) {
                r = f(Reflect.get(color, "x"));
                g = f(Reflect.get(color, "y"));
                b = f(Reflect.get(color, "z"));
                a = f(Reflect.get(color, "w"));
            }
            w.drawList.addRectFilled(x, y, x + wd, y + h, color(r, g, b, a), 3);
            w.drawList.addRect(x, y, x + wd, y + h, color(0.1f, 0.1f, 0.1f, 1f), 3, 1);
            itemSize(wd, h);
            this.lastItemHovered = hovered;
            return clicked;
        }

        boolean beginMainMenuBar() {
            float height = frameHeight();
            this.menuBarOffset = height;
            this.menuBarSeen = true;
            this.menuBarSubmittedThisFrame = true;
            // BeginViewportSideBar(ImGuiDir_Up): place the bar at the viewport work
            // rect origin and report the inset for the next frame.
            float barX = this.workSetThisFrame ? this.viewport.workX : 0f;
            float barY = this.workSetThisFrame ? this.viewport.workY : 0f;
            float barW = this.workSetThisFrame ? this.viewport.workW : this.io.displayW;
            this.nextWindowX = barX;
            this.nextWindowY = barY;
            this.nextWindowPivotX = 0;
            this.nextWindowPivotY = 0;
            this.nextWindowW = barW;
            this.nextWindowH = height;
            boolean open = begin("##MainMenuBar", 1 | 2 | 4 | 8 | 256 | 1024);
            if (open) {
                Window w = currentWindow();
                w.x = barX;
                w.y = barY;
                w.w = barW;
                w.h = height;
                w.titleH = 0;
                w.mainDocked = true;
                w.dockId = 0;
                w.menuBar = true;
                w.menuBarHeight = height;
                w.scrollbarY = false;
                w.scrollMaxY = 0;
                w.contentY = this.style.windowPaddingY;
                w.contentH = Math.max(1, height - this.style.windowPaddingY * 2);
                this.mainMenuDrawList = w.drawList;
                // MenuBarOffset.x = max(WindowPadding.x, ItemSpacing.x, DisplaySafeAreaPadding.x)
                w.cursorX = Math.max(this.style.windowPaddingX, this.style.itemSpacingX);
                w.cursorY = height;
                w.lineY = height;
            }
            return open;
        }

        void endMainMenuBar() {
            end();
        }

        boolean beginMenuBar() {
            Window w = currentWindow();
            w.menuBar = true;
            w.menuBarHeight = frameHeight();
            w.cursorY += w.menuBarHeight;
            return true;
        }

        void endMenuBar() {
            currentWindow().menuBar = false;
        }

        boolean beginMenu(String label, boolean enabled) {
            Window w = currentWindow();
            float x = w.x + w.cursorX - w.scrollX;
            float y = w.y + w.cursorY - w.scrollY - (w.menuBar ? w.menuBarHeight : 0);
            label = visibleText(label);
            float menuW = this.atlas.measure(label, this.style.fontSize) + this.style.itemSpacingX * 2;
            boolean hovered = hit(x, y, menuW, w.menuBarHeight);
            if (hovered || this.popupMap.getOrDefault("##menu_" + label, null) != null
                && this.popupMap.get("##menu_" + label).open) {
                w.drawList.addRectFilled(x, y, x + menuW, y + w.menuBarHeight, styleColor(25));
            }
            if (hovered && this.io.mousePressed[0]) {
                Popup existing = this.popupMap.get("##menu_" + label);
                if (existing != null && existing.open) {
                    existing.open = false;
                    this.openPopupId = null;
                } else {
                    this.popupMap.values().forEach(p -> p.open = false);
                    openPopup("##menu_" + label);
                    this.popupX = x;
                    this.popupY = y + w.menuBarHeight;
                }
            } else if (hovered && this.openPopupId == null
                && this.popupMap.values().stream().anyMatch(p -> p.open)) {
                // Hovering another top-level menu switches the open menu.
                this.popupMap.values().forEach(p -> p.open = false);
                openPopup("##menu_" + label);
                this.popupX = x;
                this.popupY = y + w.menuBarHeight;
            }
            w.drawList.addText(x + this.style.framePaddingX, y + this.style.framePaddingY, styleColor(0), label);
            float metric = this.atlas.measure(label, this.style.fontSize);
            if (Boolean.getBoolean("noimgui.debug.menu") && this.menuLogCount++ < 20) {
                NoNativeMod.LOGGER.info("MENU win={} label={} x={} y={} metric={} cursorX={} font={}",
                    w.name, label, x, y, metric, w.cursorX, this.atlas.current == null ? "null" : this.atlas.current.object);
            }
            // Menu labels always occupy horizontal space in the menu bar.
            w.cursorX += metric + 16;
            return beginPopup("##menu_" + label, 0);
        }

        void endMenu() {
            endPopup();
        }

        boolean menuItem(String label, String shortcut, boolean selected, boolean enabled) {
            Window w = currentWindow();
            label = visibleText(label);
            float h = frameHeight();
            boolean hovered = hit(w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, w.w - w.cursorX, h) && this.disabledDepth == 0;
            boolean clicked = hovered && this.io.mouseReleased[0] && enabled;
            if (hovered) {
                w.drawList.addRectFilled(w.x + w.cursorX - w.scrollX, w.y + w.cursorY - w.scrollY, w.x + w.w, w.y + w.cursorY - w.scrollY + h, styleColor(25));
            }
            w.drawList.addText(w.x + w.cursorX - w.scrollX + 6, w.y + w.cursorY - w.scrollY + this.style.framePaddingY, styleColor(0), (selected ? "* " : "") + label);
            if (shortcut != null && !shortcut.isEmpty()) {
                w.drawList.addText(w.x + w.w - 8 - this.atlas.measure(shortcut, this.style.fontSize), w.y + w.cursorY - w.scrollY + this.style.framePaddingY, color(0.7f, 0.7f, 0.7f, 1f), shortcut);
            }
            itemSize(0, h);
            return clicked;
        }

        void openPopup(String id) {
            this.openPopupId = id;
            this.popupX = this.io.mouseX;
            this.popupY = this.io.mouseY;
            this.anyPopupOpen = true;
        }

        boolean beginPopupModal(String id, Object open, int flags) {
            if (open != null && !bool(open)) return false;
            Popup popup = this.popupMap.get(id);
            if (popup != null) popup.modal = true;
            boolean result = beginPopup(id, flags);
            if (result) {
                // Dim the whole viewport behind a modal.
                this.background.addRectFilled(0, 0, this.io.displayW, this.io.displayH,
                    color(0f, 0f, 0f, 0.35f));
            }
            return result;
        }

        boolean beginPopup(String id, int flags) {
            if (this.openPopupId == null || !this.openPopupId.equals(id)) {
                Popup existing = this.popupMap.get(id);
                if (existing == null || !existing.open) {
                    return false;
                }
            } else {
                Popup popup = this.popupMap.computeIfAbsent(id, k -> new Popup());
                popup.open = true;
                popup.x = this.popupX;
                popup.y = this.popupY;
                this.openPopupId = null;
            }
            Popup popup = this.popupMap.get(id);
            if (popup == null || !popup.open) {
                return false;
            }
            this.anyPopupOpen = true;
            this.nextWindowX = popup.x;
            this.nextWindowY = popup.y;
            this.nextWindowPivotX = 0;
            this.nextWindowPivotY = 0;
            // Popups have no title bar, never show a scrollbar, and auto-size to
            // their content (BeginPopupEx uses AlwaysAutoResize | NoTitleBar |
            // NoSavedSettings).
            boolean result = begin("##popup_" + id, 1 | 8 | 64 | 256);
            if (result) {
                currentWindow().order = ++this.frameCount;
                Window w = currentWindow();
                w.w = Math.max(120, w.w);
                w.h = Math.max(40, w.h);
            }
            this.popups.add(currentWindow());
            return result;
        }

        void endPopup() {
            if (!this.popups.isEmpty()) {
                Window w = this.popups.remove(this.popups.size() - 1);
                if (w != null && !this.windowStack.isEmpty() && this.windowStack.get(this.windowStack.size() - 1) == w) {
                    end();
                }
            }
        }

        void closeCurrentPopup() {
            for (Popup p : this.popupMap.values()) {
                p.open = false;
            }
            this.openPopupId = null;
        }

        boolean isPopupOpen(String id, int flags) {
            if (id == null || id.isEmpty()) {
                return this.anyPopupOpen || this.popupMap.values().stream().anyMatch(p -> p.open);
            }
            Popup p = this.popupMap.get(id);
            return p != null && p.open;
        }

        boolean beginTooltip() {
            this.nextWindowX = this.io.mouseX + 12;
            this.nextWindowY = this.io.mouseY + 12;
            this.nextWindowPivotX = 0;
            this.nextWindowPivotY = 0;
            return begin("##tooltip", 1 | 64 | 256 | 1024);
        }

        void endTooltip() {
            end();
        }

        void setTooltip(String text) {
            beginTooltip();
            text(text);
            endTooltip();
        }

        void setItemTooltip(String text) {
            if (this.lastItemHovered) {
                setTooltip(text);
            }
        }

        boolean beginItemTooltip() {
            return this.lastItemHovered && beginTooltip();
        }

        void text(String text, float screenX, float screenY) {
            Window w = currentWindow();
            w.drawList.addText(screenX, screenY, styleColor(0), text);
        }

        // --------------------------------------------------------------
        // Tables / tabs / child windows
        // --------------------------------------------------------------

        boolean beginChild(String id, float width, float height, int flags) {
            Window parent = currentWindow();
            // GetContentRegionAvail(): ContentRegionRect.Max - CursorScreenPos.
            float availX = Math.max(0, parent.w - parent.contentX - parent.cursorX
                - (parent.scrollbarY ? this.style.scrollbarSize : 0));
            float availY = Math.max(0, parent.h - parent.contentY
                - (parent.cursorY - parent.scrollY));
            // CalcItemSize: negative sizes shrink the available space.
            float childW = width == 0 ? availX : width > 0 ? width : Math.max(4, availX + width);
            float childH = height == 0 ? availY : height > 0 ? height : Math.max(4, availY + height);
            float childX = parent.x + parent.cursorX;
            float childY = parent.y + parent.cursorY - parent.scrollY;

            boolean childPadding = (flags & 3) != 0; // Borders | AlwaysUseWindowPadding
            String key = "##child_" + currentId(id);
            Window child = this.windows.computeIfAbsent(key, n -> new Window(n, childX, childY, childW, childH));
            child.childWindow = true;
            if (!parent.childWindows.contains(child)) parent.childWindows.add(child);
            child.skipDraw = false;
            child.x = childX;
            child.y = childY;
            child.w = childW;
            child.h = childH;
            child.titleH = 0;
            child.scrollbarY = false;
            child.contentX = childPadding ? this.style.windowPaddingX : 0;
            child.contentY = childPadding ? this.style.windowPaddingY : 0;
            child.contentW = Math.max(1, child.w - child.contentX * 2);
            child.contentH = Math.max(1, child.h - child.contentY * 2);
            child.lineStartX = child.contentX;
            child.cursorX = child.contentX;
            child.cursorY = child.contentY;
            child.contentMaxX = 0;
            child.contentMaxY = 0;
            child.contentHeight = 0;
            child.lineX = child.contentX;
            child.lineY = child.contentY;
            child.lineHeight = 0;
            child.drawList.reset();
            child.drawList.textureId = this.atlas.texId;
            if (!this.frameLists.contains(child.drawList)) {
                this.frameLists.add(child.drawList);
            }
            child.drawList.textSize = this.style.fontSize;
            child.drawList.pushClip(
                Math.max(child.x, parent.drawList.clipMinX),
                Math.max(child.y, parent.drawList.clipMinY),
                Math.min(child.x + child.w, parent.drawList.clipMaxX),
                Math.min(child.y + child.h, parent.drawList.clipMaxY));
            child.clipCount = 1;
            this.windowStack.add(child);
            this.currentWindow = child;
            this.currentDrawList = child.drawList;
            this.thisFrame.add(child);
            this.pendingChild = child;
            return true;
        }

        void endChild() {
            Window child = this.currentWindow;
            if (child == null) return;
            end();
            Window parent = currentWindow();
            if (parent != null && child != parent) {
                // EndChild(): ItemSize(child_window->Size).
                this.pendingChild = null;
                itemSize(child.w, child.h);
                this.lastItemRect[0] = child.x;
                this.lastItemRect[1] = child.y;
                this.lastItemRect[2] = child.x + child.w;
                this.lastItemRect[3] = child.y + child.h;
                this.lastItemHovered = this.io.mouseX >= child.x && this.io.mouseX <= child.x + child.w
                    && this.io.mouseY >= child.y && this.io.mouseY <= child.y + child.h;
            }
        }

        void beginGroup() {
            currentWindow().groupStack.add(new float[]{currentWindow().cursorX, currentWindow().cursorY});
        }

        void endGroup() {
            Window w = currentWindow();
            if (!w.groupStack.isEmpty()) {
                float[] start = w.groupStack.remove(w.groupStack.size() - 1);
                float height = w.cursorY - start[1];
                w.cursorX = start[0];
                w.cursorY = start[1];
                itemSize(0, height);
            }
        }

        boolean beginTable(String id, int columns, int flags, float outerWidth, float outerHeight) {
            Window w = currentWindow();
            int count = Math.max(1, columns);
            Table table = new Table(count);
            table.id = id;
            table.startX = w.cursorX;
            table.startY = w.cursorY;
            table.rowStart = w.cursorY;
            table.rowHeight = frameHeight();
            table.rowStarted = false;
            table.currentColumn = -1;
            table.cellActive = false;
            table.layout = new TableLayout(count, outerWidth > 0 ? outerWidth : w.contentW);
            table.layout.setCellStyle(this.style.cellPaddingX, this.style.itemSpacingX * 0.5f,
                this.style.itemSpacingX * 0.5f, 0.0f);
            table.layout.setCellPaddingY(this.style.cellPaddingY);
            // ImGui sets up `columns` default stretch columns in BeginTable();
            // TableSetupColumn() replaces them one by one. This is essential:
            // many mods call TableNextColumn() without TableSetupColumn().
            for (int i = 0; i < count; i++) {
                table.columns.add(new Column("", 0f, 0));
            }
            w.table = table;
            w.cursorX = table.startX;
            return true;
        }

        void endTable() {
            Window w = currentWindow();
            if (w.table == null) return;
            Table table = w.table;
            tableFinishCell(w, table);
            float height = table.layout == null
                ? Math.max(table.rowHeight, table.rowStart + table.rowHeight - table.startY)
                : (table.layout.rowCount() == 0 ? frameHeight() : table.layout.tableHeight());
            w.cursorX = w.contentX;
            w.cursorY = table.startY;
            itemSize(w.contentW, Math.max(1, height));
            w.table = null;
        }

        void tableSetupColumn(String label, int flags, float width, int userData) {
            Window w = currentWindow();
            if (w.table == null) {
                w.table = new Table(1);
                w.table.layout = new TableLayout(1, w.contentW);
            }
            Table table = w.table;
            int index = table.setupIndex++;
            if (index >= table.columns.size()) return;
            table.columns.set(index, new Column(label, width, userData));
            if (table.layout == null || table.layout.columnCount() <= 0) {
                return;
            }
            // ImGuiTableColumnFlags_WidthStretch = 1 << 3, WidthFixed = 1 << 4.
            int mode = width > 0.0f ? TableLayout.WIDTH_FIXED : TableLayout.WIDTH_STRETCH;
            if ((flags & (1 << 3)) != 0) {
                mode = TableLayout.WIDTH_STRETCH;
            } else if ((flags & (1 << 4)) != 0) {
                mode = width > 0.0f ? TableLayout.WIDTH_FIXED : TableLayout.WIDTH_AUTO;
            }
            table.layout.setupColumn(width, mode, width > 0.0f ? width : 0.0f);
        }

        void tableHeadersRow() {
            Window w = currentWindow();
            Table table = w.table;
            if (table == null || table.layout == null) return;
            tableFinishCell(w, table);
            table.layout.beginHeaderRow(frameHeight());
            table.rowStarted = true;
            table.column = 0;
            table.currentColumn = -1;
            table.cellActive = false;
            int rowIndex = table.layout.rowIndex();
            for (int i = 0; i < table.columns.size() && i < table.layout.columnCount(); i++) {
                Column column = table.columns.get(i);
                table.layout.setColumn(i);
                TableLayout.CellClip clip = table.layout.cellClip(i, rowIndex);
                float x0 = w.x + table.startX + clip.minX();
                float x1 = w.x + table.startX + clip.maxX();
                float y0 = w.y + table.startY + clip.minY() - w.scrollY;
                float y1 = w.y + table.startY + clip.maxY() - w.scrollY;
                boolean hovered = hit(x0, y0, x1 - x0, y1 - y0);
                w.drawList.addRectFilled(x0, y0, x1, y1,
                    color(0.20f, 0.28f, 0.38f, 0.9f));
                String arrow = table.sortColumn == i
                    ? (table.sortDirection == 1 ? " v" : " ^") : "";
                w.drawList.addText(w.x + table.startX + table.layout.columnX(i),
                    y0 + this.style.framePaddingY, styleColor(0), column.label + arrow);
                if (hovered && this.io.mouseReleased[0]) {
                    if (table.sortColumn != i) {
                        table.sortColumn = i;
                        table.sortDirection = 1;
                    } else if (table.sortDirection == 1) {
                        table.sortDirection = 0;
                    } else {
                        table.sortColumn = -1;
                    }
                    table.sortUserData = column.userData();
                    table.specsDirty = true;
                }
            }
            table.column = 0;
        }

        void tableNextRow(int flags, float minHeight) {
            Window w = currentWindow();
            Table table = w.table;
            if (table == null || table.layout == null) return;
            tableFinishCell(w, table);
            int rowFlags = (flags & 2) != 0 ? TableLayout.ROW_HEADER : TableLayout.ROW_NONE;
            table.layout.beginRow(Math.max(minHeight, frameHeight()), rowFlags);
            table.rowStarted = true;
            table.column = 0;
            table.currentColumn = -1;
            table.cellActive = false;
            table.rowStart = table.layout.rowY();
            table.rowHeight = table.layout.rowHeight();
            w.cursorX = table.startX;
            w.cursorY = table.startY + table.rowStart;
        }

        boolean tableNextColumn() {
            Window w = currentWindow();
            if (w.table == null) return false;
            if (w.table.column >= w.table.layout.columnCount()) return false;
            return tableSetColumnIndex(w.table.column);
        }

        boolean tableSetColumnIndex(int column) {
            Window w = currentWindow();
            Table table = w.table;
            if (table == null || table.layout == null) return false;
            if (column < 0 || column >= table.columns.size() || column >= table.layout.columnCount()) {
                return false;
            }
            tableFinishCell(w, table);
            if (!table.layout.isInsideRow()) {
                table.layout.beginRow(frameHeight(), TableLayout.ROW_NONE);
            }
            table.layout.setColumn(column);
            TableLayout.CellClip clip = table.layout.cellClip();
            table.currentColumn = column;
            table.rowStart = table.layout.rowY();
            table.rowHeight = table.layout.rowHeight();
            table.column = column + 1;
            table.columnWidth = table.layout.columnWidth(column);
            w.lineStartX = table.startX + table.layout.columnX(column);
            w.tableItemWidth = Math.max(1f, table.layout.columnWidth(column) - this.style.cellPaddingX * 2f);
            w.workMinX = w.lineStartX;
            w.workMaxX = w.lineStartX + w.tableItemWidth;
            w.workMinY = table.startY + table.rowStart;
            w.workMaxY = w.workMinY + table.rowHeight;
            w.cursorX = w.lineStartX;
            w.cursorY = table.startY + table.rowStart;
            if (clip.isEmpty()) {
                table.cellActive = false;
                return false;
            }
            float clipX0 = Math.max(w.drawList.clipMinX, w.x + table.startX + clip.minX());
            float clipY0 = Math.max(w.drawList.clipMinY, w.y + table.startY + clip.minY() - w.scrollY);
            float clipX1 = Math.min(w.drawList.clipMaxX, w.x + table.startX + clip.maxX());
            float clipY1 = Math.min(w.drawList.clipMaxY, w.y + table.startY + clip.maxY() - w.scrollY);
            if (clipX1 <= clipX0 || clipY1 <= clipY0) {
                table.cellActive = false;
                return false;
            }
            table.cellActive = true;
            w.drawList.pushClip(clipX0, clipY0, clipX1, clipY1);
            return true;
        }

        void tableFinishCell(Window w, Table table) {
            if (table == null || table.layout == null || !table.cellActive) return;
            table.cellActive = false;
            w.drawList.popClip();
            w.lineStartX = w.contentX + this.indent;
            w.cursorX = w.lineStartX;
            if (table.layout.isInsideRow()) {
                float rowTop = table.startY + table.layout.rowY();
                float contentHeight = Math.max(0.0f,
                    w.cursorY - rowTop - this.style.cellPaddingY * 2.0f);
                table.layout.addCellHeight(contentHeight);
                table.rowHeight = table.layout.rowHeight();
            }
        }

        boolean beginListBox(String id, float width, float height) {
            return beginChild("##listbox_" + id, width, height, 0);
        }

        boolean beginTabBar(String id, int flags) {
            Window w = currentWindow();
            w.tabBar = true;
            w.tabBarY = w.cursorY;
            w.tabX = 0;
            return true;
        }

        void endTabBar() {
            currentWindow().tabBar = false;
        }

        boolean beginTabItem(String label, Object open) {
            Window w = currentWindow();
            label = visibleText(label);
            float width = this.atlas.measure(label, this.style.fontSize) + 20;
            float x = w.x + w.tabX - w.scrollX;
            float y = w.y + w.tabBarY - w.scrollY;
            boolean hovered = hit(x, y, width, frameHeight());
            String id = currentId(label);
            if (hovered && this.io.mouseReleased[0]) {
                w.activeTab = id;
            }
            boolean active = id.equals(w.activeTab);
            w.drawList.addRectFilled(x, y, x + width, y + frameHeight(),
                active ? styleColor(33) : hovered ? styleColor(32) : styleColor(31), this.style.tabRounding);
            w.drawList.addText(x + 8, y + this.style.framePaddingY, styleColor(0), label);
            w.tabX += width;
            if (!active) {
                return false;
            }
            w.cursorY = w.tabBarY + frameHeight();
            w.cursorX = w.contentX;
            return true;
        }

        void endTabItem() {
        }

        // --------------------------------------------------------------
        // Utilities
        // --------------------------------------------------------------

        // --------------------------------------------------------------
        // Keyboard navigation
        // --------------------------------------------------------------

        int navKeyCode(int key) {
            return switch (key) {
                case NavState.KEY_TAB -> NAV_KEY_TAB;
                case NavState.KEY_LEFT -> NAV_KEY_LEFT;
                case NavState.KEY_RIGHT -> NAV_KEY_RIGHT;
                case NavState.KEY_UP -> NAV_KEY_UP;
                case NavState.KEY_DOWN -> NAV_KEY_DOWN;
                case NavState.KEY_SPACE -> NAV_KEY_SPACE;
                case NavState.KEY_ENTER, NavState.KEY_KEYPAD_ENTER -> NAV_KEY_ENTER;
                case NavState.KEY_SHIFT_LEFT -> NAV_KEY_LEFT_SHIFT;
                case NavState.KEY_SHIFT_RIGHT -> NAV_KEY_RIGHT_SHIFT;
                default -> -1;
            };
        }

        long navWindowId(Window window) {
            if (window == null) {
                return NavState.DEFAULT_WINDOW;
            }
            long id = (window.name == null ? 0 : window.name.hashCode()) & 0xFFFFFFFFL;
            return id == NavState.NO_ID ? NavState.DEFAULT_WINDOW : id;
        }

        long navItemId(String id) {
            long value = (id == null ? 0 : id.hashCode()) & 0xFFFFFFFFL;
            return value == NavState.NO_ID ? 1L : value;
        }

        long navRegister(Window window, String id, float x, float y, float width, float height) {
            this.nav.setWindow(navWindowId(window));
            long item = navItemId(id);
            this.nav.registerItem(item, NavState.Rect.of(x, y, width, height), true);
            return item;
        }

        boolean navActivated(long item) {
            return this.nav.isActivated(item);
        }

        boolean navFocused(long item) {
            return this.nav.isFocused(item);
        }

        String currentId(String label) {
            StringBuilder b = new StringBuilder();
            for (String s : this.idStringStack) b.append(s).append('/');
            b.append(currentWindow().name).append('/').append(label);
            return b.toString();
        }

        boolean hit(float x, float y, float w, float h) {
            if (this.disabledDepth > 0) return false;
            if (this.io.mouseX < x || this.io.mouseX > x + w
                || this.io.mouseY < y || this.io.mouseY > y + h) {
                return false;
            }
            // Clipped widgets must not be clickable (clip rect gates hit-testing).
            Window cw = this.currentWindow;
            if (cw != null) {
                DrawList clip = cw.drawList;
                if (!clip.clipStack.isEmpty()) {
                    return this.io.mouseX >= clip.clipMinX && this.io.mouseX <= clip.clipMaxX
                        && this.io.mouseY >= clip.clipMinY && this.io.mouseY <= clip.clipMaxY;
                }
            }
            return true;
        }

        void updateMouseCapture() {
            List<Window> visible = this.lastFrame.isEmpty() ? this.thisFrame : this.lastFrame;
            Window hovered = null;
            long bestOrder = Long.MIN_VALUE;
            for (Window w : visible) {
                if (w.skipDraw) continue;
                if (this.io.mouseX < w.x || this.io.mouseX > w.x + w.w
                    || this.io.mouseY < w.y || this.io.mouseY > w.y + w.h) continue;
                if (hovered == null || w.order >= bestOrder) {
                    hovered = w;
                    bestOrder = w.order;
                }
            }
            this.hoveredWindowThisFrame = hovered;

            // Mirrors UpdateHoveredWindowAndCaptureFlags() (imgui.cpp 5598-5646):
            // button ownership is decided on press; if the earliest click started
            // outside the UI, the UI does not capture until release.
            int earliest = -1;
            for (int i = 0; i < 5; i++) {
                if (this.io.mousePressed[i]) {
                    this.io.mouseDownOwned[i] = hovered != null || this.anyPopupOpen;
                }
                if ((this.io.mouseDown[i] || this.io.mouseReleased[i])
                    && (earliest < 0 || this.io.mouseClickedTime[i] < this.io.mouseClickedTime[earliest])) {
                    earliest = i;
                }
            }
            boolean mouseAvail = earliest < 0 || this.io.mouseDownOwned[earliest];
            if (!mouseAvail) {
                hovered = null;
                this.hoveredWindowThisFrame = null;
            }
            int wantMouse = ((mouseAvail && (hovered != null || this.io.anyMouseDown()))
                || this.anyPopupOpen) ? 1 : 0;
            if (this.io.nextWantCaptureMouse != -1) {
                wantMouse = this.io.nextWantCaptureMouse;
            }
            this.io.wantCaptureMouse = wantMouse != 0;

            boolean modalOpen = this.popupMap.values().stream().anyMatch(p -> p.open && p.modal);
            int wantKeyboard = (this.activeId != null || this.wantTextInput || modalOpen) ? 1 : 0;
            if (this.io.nextWantCaptureKeyboard != -1) {
                wantKeyboard = this.io.nextWantCaptureKeyboard;
            }
            this.io.wantCaptureKeyboard = wantKeyboard != 0;
        }

        Object windowDrawList() {
            Window w = currentWindow();
            if (w.drawListObject == null) {
                w.drawListObject = wrapper("ImDrawList", newHandle(), w.drawList);
            }
            return w.drawListObject;
        }

        Object dockNode(int id) {
            long handle = newHandle();
            this.dockNodeHandles.put(handle, id);
            return wrapper("internal.ImGuiDockNode", handle, new Object());
        }

        List<float[]> vertices(Object array) {
            List<float[]> out = new ArrayList<>();
            if (array instanceof Object[] items) {
                for (Object item : items) {
                    if (item != null && item.getClass().getSimpleName().equals("ImVec2")) {
                        out.add(new float[]{f(Reflect.get(item, "x")), f(Reflect.get(item, "y"))});
                    }
                }
            } else if (array instanceof float[][] points) {
                for (float[] pt : points) out.add(pt.clone());
            }
            return out;
        }

        Object tableSortSpecs() {
            Window w = currentWindow();
            if (w.table == null) return null;
            long handle = newHandle();
            Object wrapper = wrapper("ImGuiTableSortSpecs", handle, w.table);
            return wrapper;
        }

        Object tableColumnSortSpec(Table table, int order) {
            long handle = newHandle();
            Object spec = wrapper("ImGuiTableColumnSortSpecs", handle, table);
            try {
                Reflect.set(spec, "ColumnUserID", table.sortUserData);
                Reflect.set(spec, "ColumnIndex", Math.max(0, table.sortColumn));
                Reflect.set(spec, "SortOrder", order);
                Reflect.set(spec, "SortDirection", table.sortDirection);
            } catch (Throwable ignored) {
            }
            return spec;
        }

        Object dockNodeMethod(String name, Object self, Object[] args) {
            int id = this.dockNodeHandles.getOrDefault(ptr(self), 0);
            if (name.equals("getNodeId") || name.equals("getID")) return id;
            if (name.equals("addLocalFlags")) {
                this.runtimeDockLocalFlags.merge(id, argI(args, 0, 0), (a, b) -> a | b);
                return null;
            }
            if (name.equals("setLocalFlags")) {
                this.runtimeDockLocalFlags.put(id, argI(args, 0, 0));
                return null;
            }
            if (name.equals("getLocalFlags") || name.equals("getMergedFlags")) {
                return this.runtimeDockLocalFlags.getOrDefault(id, 0);
            }
            if (name.equals("isNoTabBar")) {
                return (this.runtimeDockLocalFlags.getOrDefault(id, 0) & (1 << 12)) != 0;
            }
            if (name.equals("isHiddenTabBar")) {
                return (this.runtimeDockLocalFlags.getOrDefault(id, 0) & (1 << 13)) != 0;
            }
            if (name.equals("isLeafNode") || name.equals("isSplitNode") || name.equals("isVisible")) {
                DockLayout.Node node = this.dockLayout == null ? null : this.dockLayout.node(id);
                if (name.equals("isLeafNode")) return node != null && node.isLeaf();
                if (name.equals("isSplitNode")) return node != null && !node.isLeaf();
                return node != null;
            }
            if (name.equals("getPos")) {
                DockLayout.Rect r = this.dockLayout == null ? null : this.dockLayout.rect(id);
                return r == null ? vec2(0, 0) : vec2(r.x(), r.y());
            }
            if (name.equals("getSize")) {
                DockLayout.Rect r = this.dockLayout == null ? null : this.dockLayout.rect(id);
                return r == null ? vec2(0, 0) : vec2(r.width(), r.height());
            }
            return null;
        }

        String textArg(Object[] args, int index) {
            Object value = arg(args, index);
            if (value instanceof String s) {
                return s;
            }
            if (value instanceof String[] parts) {
                return String.join("", parts);
            }
            return "";
        }

        Object drawList(String simple, String name, String desc, Object self, Object[] args) {
            DrawList data = self == null ? this.currentDrawList : (DrawList) data(self);
            if (data == null) {
                data = this.background;
            }
            switch (name) {
                case "addRectFilled":
                    if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec2")) {
                        Object a = arg(args, 0), b = arg(args, 1);
                        data.addRectFilled(f(Reflect.get(a, "x")), f(Reflect.get(a, "y")),
                            f(Reflect.get(b, "x")), f(Reflect.get(b, "y")),
                            argI(args, 2, 0xFFFFFFFF), argF(args, 3, 0));
                    } else {
                        data.addRectFilled(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0),
                            argI(args, 4, 0xFFFFFFFF), argF(args, 5, 0));
                    }
                    return null;
                case "addRect": data.addRect(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argI(args, 4, 0xFFFFFFFF), argF(args, 5, 0), argF(args, 7, 1)); return null;
                case "addRectFilledMultiColor": data.addQuad(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 0, 0), argF(args, 3, 0), 0, 0, 0, 0, argI(args, 4, 0xFFFFFFFF)); return null;
                case "addLine":
                    if (arg(args, 0) != null && arg(args, 0).getClass().getSimpleName().equals("ImVec2")) {
                        Object a = arg(args, 0), b = arg(args, 1);
                        data.addLine(f(Reflect.get(a, "x")), f(Reflect.get(a, "y")), f(Reflect.get(b, "x")), f(Reflect.get(b, "y")), argI(args, 2, 0xFFFFFFFF), argF(args, 3, 1));
                    } else {
                        data.addLine(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argI(args, 4, 0xFFFFFFFF), argF(args, 5, 1));
                    }
                    return null;
                case "addCircle": data.addCircle(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argI(args, 3, 0xFFFFFFFF), argI(args, 4, 12), argF(args, 5, 1)); return null;
                case "addCircleFilled": data.addCircleFilled(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argI(args, 3, 0xFFFFFFFF), argI(args, 4, 12)); return null;
                case "addTriangle": data.addTriangle(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0), argF(args, 5, 0), argI(args, 6, 0xFFFFFFFF)); return null;
                case "addTriangleFilled": data.addTriangle(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0), argF(args, 5, 0), argI(args, 6, 0xFFFFFFFF)); return null;
                case "addQuad": data.addQuad(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0), argF(args, 5, 0), argF(args, 6, 0), argF(args, 7, 0), 0, 0, 0, 0, argI(args, 8, 0xFFFFFFFF)); return null;
                case "addQuadFilled": data.addQuad(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0), argF(args, 4, 0), argF(args, 5, 0), argF(args, 6, 0), argF(args, 7, 0), 0, 0, 0, 0, argI(args, 8, 0xFFFFFFFF)); return null;
                case "addText": {
                    Object first = arg(args, 0);
                    if (first != null && first.getClass().getSimpleName().equals("ImVec2")) {
                        data.addText(f(Reflect.get(first, "x")), f(Reflect.get(first, "y")), argI(args, 1, 0xFFFFFFFF), textArg(args, 2), this.style.fontSize);
                    } else if (first instanceof Number) {
                        data.addText(argF(args, 0, 0), argF(args, 1, 0), argI(args, 2, 0xFFFFFFFF), textArg(args, 3), argF(args, 4, this.style.fontSize));
                    } else if (first != null && first.getClass().getSimpleName().equals("ImFont")) {
                        float size = argF(args, 1, this.style.fontSize);
                        Object pos = arg(args, 2);
                        FontData saved = this.atlas.current;
                        Object fd = data(first);
                        if (fd instanceof FontData fontData) this.atlas.current = fontData;
                        if (pos != null && pos.getClass().getSimpleName().equals("ImVec2")) {
                            data.addText(f(Reflect.get(pos, "x")), f(Reflect.get(pos, "y")), argI(args, 3, 0xFFFFFFFF), textArg(args, 4), size);
                        } else {
                            data.addText(argF(args, 2, 0), argF(args, 3, 0), argI(args, 4, 0xFFFFFFFF), textArg(args, 5), size);
                        }
                        this.atlas.current = saved;
                    } else {
                        data.addText(argF(args, 0, 0), argF(args, 1, 0), argI(args, 2, 0xFFFFFFFF), textArg(args, 3), this.style.fontSize);
                    }
                    return null;
                }
                case "addImage": {
                    long id = arg(args, 0) instanceof Number n ? n.longValue() : 0;
                    if (Boolean.getBoolean("noimgui.debug.image") && this.imageDebugCount++ < 100) {
                        NoNativeMod.LOGGER.info("ADDIMAGE tex={} args={} win={}", id, java.util.Arrays.toString(args),
                            this.currentWindow == null ? "null" : this.currentWindow.name);
                    }
                    data.setTexture(id);
                    if (args.length >= 9 && arg(args, 1) instanceof Number) {
                        float x0 = argF(args, 1, 0), y0 = argF(args, 2, 0), x1 = argF(args, 3, 0), y1 = argF(args, 4, 0);
                        float u0 = argF(args, 5, 0), v0 = argF(args, 6, 0), u1 = argF(args, 7, 1), v1 = argF(args, 8, 1);
                        int col = args.length >= 10 ? argI(args, 9, 0xFFFFFFFF) : 0xFFFFFFFF;
                        data.addQuad(x0, y0, x1, y0, x1, y1, x0, y1, u0, v0, u1, v1, col);
                    } else if (arg(args, 1) != null && arg(args, 1).getClass().getSimpleName().equals("ImVec2")) {
                        Object a = arg(args, 1), b = arg(args, 2);
                        float x0 = f(Reflect.get(a, "x")), y0 = f(Reflect.get(a, "y"));
                        float x1 = f(Reflect.get(b, "x")), y1 = f(Reflect.get(b, "y"));
                        float u0 = 0, v0 = 0, u1 = 1, v1 = 1;
                        if (args.length >= 5 && arg(args, 3) != null && arg(args, 3).getClass().getSimpleName().equals("ImVec2")) {
                            Object ua = arg(args, 3), ub = arg(args, 4);
                            u0 = f(Reflect.get(ua, "x")); v0 = f(Reflect.get(ua, "y"));
                            u1 = f(Reflect.get(ub, "x")); v1 = f(Reflect.get(ub, "y"));
                        }
                        int col = args.length >= 6 ? argI(args, 5, 0xFFFFFFFF) : 0xFFFFFFFF;
                        data.addQuad(x0, y0, x1, y0, x1, y1, x0, y1, u0, v0, u1, v1, col);
                    } else if (args.length >= 5 && arg(args, 1) instanceof Number) {
                        float x0 = argF(args, 1, 0), y0 = argF(args, 2, 0), x1 = argF(args, 3, 0), y1 = argF(args, 4, 0);
                        data.addQuad(x0, y0, x1, y0, x1, y1, x0, y1, 0, 0, 1, 1, 0xFFFFFFFF);
                    }
                    data.setTexture(this.atlas.texId);
                    return null;
                }
                case "addImageQuad": {
                    long id = arg(args, 0) instanceof Number n ? n.longValue() : 0;
                    data.setTexture(id);
                    if (args.length >= 9 && arg(args, 1) instanceof Number) {
                        float x0 = argF(args, 1, 0), y0 = argF(args, 2, 0);
                        float x1 = argF(args, 3, 0), y1 = argF(args, 4, 0);
                        float x2 = argF(args, 5, 0), y2 = argF(args, 6, 0);
                        float x3 = argF(args, 7, 0), y3 = argF(args, 8, 0);
                        float u0 = 0, v0 = 0, u1 = 1, v1 = 0, u2 = 1, v2 = 1, u3 = 0, v3 = 1;
                        if (args.length >= 17) {
                            u0 = argF(args, 9, 0); v0 = argF(args, 10, 0);
                            u1 = argF(args, 11, 1); v1 = argF(args, 12, 0);
                            u2 = argF(args, 13, 1); v2 = argF(args, 14, 1);
                            u3 = argF(args, 15, 0); v3 = argF(args, 16, 1);
                        }
                        int col = args.length >= 18 ? argI(args, 17, 0xFFFFFFFF) : 0xFFFFFFFF;
                        data.beginCommand();
                        int base = data.vertices.size();
                        data.addVertex(x0, y0, u0, v0, col);
                        data.addVertex(x1, y1, u1, v1, col);
                        data.addVertex(x2, y2, u2, v2, col);
                        data.addVertex(x3, y3, u3, v3, col);
                        data.indices.add(base); data.indices.add(base + 1); data.indices.add(base + 2);
                        data.indices.add(base); data.indices.add(base + 2); data.indices.add(base + 3);
                        data.markCommand();
                    }
                    data.setTexture(this.atlas.texId);
                    return null;
                }
                case "addImageRounded": {
                    long id = arg(args, 0) instanceof Number n ? n.longValue() : 0;
                    data.setTexture(id);
                    if (args.length >= 9 && arg(args, 1) instanceof Number) {
                        float x0 = argF(args, 1, 0), y0 = argF(args, 2, 0), x1 = argF(args, 3, 0), y1 = argF(args, 4, 0);
                        data.addQuad(x0, y0, x1, y0, x1, y1, x0, y1, 0, 0, 1, 1, 0xFFFFFFFF);
                    }
                    data.setTexture(this.atlas.texId);
                    return null;
                }
                case "pushClipRect": {
                    if (arg(args, 0) instanceof Number) {
                        data.pushClip(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 0));
                    } else {
                        Object a = arg(args, 0), b = arg(args, 1);
                        if (a != null && b != null) {
                            data.pushClip(f(Reflect.get(a, "x")), f(Reflect.get(a, "y")), f(Reflect.get(b, "x")), f(Reflect.get(b, "y")));
                        }
                    }
                    return null;
                }
                case "pushClipRectFullScreen": data.pushClip(0, 0, this.io.displayW, this.io.displayH); return null;
                case "popClipRect": data.popClip(); return null;
                case "getClipRectMin": return vec2(data.clipMinX, data.clipMinY);
                case "getClipRectMax": return vec2(data.clipMaxX, data.clipMaxY);
                case "setTextureID": data.setTexture(arg(args, 0) instanceof Number n ? n.longValue() : 0); return null;
                case "getTextureID": return data.textureId;
                case "addFlags": return null;
                case "removeFlags": return null;
                case "hasFlags": return false;
                case "getFlags": return 0;
                case "getVtxCurrentIdx": return data.vertices.size();
                case "getVertexBufferSize": return data.vertices.size();
                case "getIndexBufferSize": return data.indices.size();
                case "addDrawCmd": data.markCommand(); data.forceCommand(); return null;
                case "addPolyline": {
                    List<float[]> pts = vertices(arg(args, 0));
                    data.addPolyline(pts, argI(args, 1, 0xFFFFFFFF), argB(args, 2, false), argF(args, 3, 1));
                    return null;
                }
                case "addConvexPolyFilled": {
                    data.addConvexPolyFilled(vertices(arg(args, 0)), argI(args, 1, 0xFFFFFFFF));
                    return null;
                }
                case "addBezierCubic":
                case "addBezierQuadratic": {
                    int count = name.equals("addBezierCubic") ? 4 : 3;
                    float[] xs = new float[count], ys = new float[count];
                    for (int i = 0; i < count; i++) {
                        Object p = arg(args, i + 1);
                        xs[i] = f(Reflect.get(p, "x"));
                        ys[i] = f(Reflect.get(p, "y"));
                    }
                    int col = argI(args, 1 + count, 0xFFFFFFFF);
                    float thick = argF(args, 2 + count, 1);
                    int seg = Math.max(2, argI(args, 3 + count, 0));
                    if (seg <= 1) seg = 20;
                    List<float[]> pts = new ArrayList<>();
                    for (int i = 0; i <= seg; i++) {
                        float t = i / (float) seg;
                        float mt = 1 - t;
                        float x, y;
                        if (count == 4) {
                            x = mt*mt*mt*xs[0] + 3*mt*mt*t*xs[1] + 3*mt*t*t*xs[2] + t*t*t*xs[3];
                            y = mt*mt*mt*ys[0] + 3*mt*mt*t*ys[1] + 3*mt*t*t*ys[2] + t*t*t*ys[3];
                        } else {
                            x = mt*mt*xs[0] + 2*mt*t*xs[1] + t*t*xs[2];
                            y = mt*mt*ys[0] + 2*mt*t*ys[1] + t*t*ys[2];
                        }
                        pts.add(new float[]{x, y});
                    }
                    data.addPolyline(pts, col, false, thick);
                    return null;
                }
                case "addNgon": {
                    float cx = argF(args, 0, 0), cy = argF(args, 1, 0), r = argF(args, 2, 0);
                    int seg = Math.max(3, argI(args, 4, 12));
                    List<float[]> pts = new ArrayList<>();
                    for (int i = 0; i < seg; i++) {
                        float a = (float) (Math.PI * 2 * i / seg);
                        pts.add(new float[]{cx + (float) Math.cos(a) * r, cy + (float) Math.sin(a) * r});
                    }
                    data.addPolyline(pts, argI(args, 3, 0xFFFFFFFF), true, argF(args, 5, 1));
                    return null;
                }
                case "addNgonFilled": {
                    float cx = argF(args, 0, 0), cy = argF(args, 1, 0), r = argF(args, 2, 0);
                    int seg = Math.max(3, argI(args, 4, 12));
                    List<float[]> pts = new ArrayList<>();
                    for (int i = 0; i < seg; i++) {
                        float a = (float) (Math.PI * 2 * i / seg);
                        pts.add(new float[]{cx + (float) Math.cos(a) * r, cy + (float) Math.sin(a) * r});
                    }
                    data.addConvexPolyFilled(pts, argI(args, 3, 0xFFFFFFFF));
                    return null;
                }
                case "pathLineTo": {
                    Object p = arg(args, 0);
                    if (p instanceof Number) {
                        data.pathLineTo(argF(args, 0, 0), argF(args, 1, 0));
                    } else {
                        data.pathLineTo(f(Reflect.get(p, "x")), f(Reflect.get(p, "y")));
                    }
                    return null;
                }
                case "pathArcTo":
                    data.pathArcTo(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0),
                        argF(args, 3, 0), argF(args, 4, 0), argI(args, 5, 12));
                    return null;
                case "pathBezierCubicCurveTo":
                case "pathBezierQuadraticCurveTo": {
                    boolean cubic = name.equals("pathBezierCubicCurveTo");
                    int count = cubic ? 3 : 2;
                    float[] xs = new float[count], ys = new float[count];
                    for (int i = 0; i < count; i++) {
                        Object p = arg(args, i);
                        xs[i] = f(Reflect.get(p, "x"));
                        ys[i] = f(Reflect.get(p, "y"));
                    }
                    int seg = 20;
                    float[] start = data.path.isEmpty() ? new float[]{0, 0} : data.path.get(data.path.size() - 1);
                    for (int i = 1; i <= seg; i++) {
                        float t = i / (float) seg, mt = 1 - t;
                        float x, y;
                        if (cubic) {
                            x = mt*mt*mt*start[0] + 3*mt*mt*t*xs[0] + 3*mt*t*t*xs[1] + t*t*t*xs[2];
                            y = mt*mt*mt*start[1] + 3*mt*mt*t*ys[0] + 3*mt*t*t*ys[1] + t*t*t*ys[2];
                        } else {
                            x = mt*mt*start[0] + 2*mt*t*xs[0] + t*t*xs[1];
                            y = mt*mt*start[1] + 2*mt*t*ys[0] + t*t*ys[1];
                        }
                        data.pathLineTo(x, y);
                    }
                    return null;
                }
                case "pathRect": {
                    float x0 = argF(args, 0, 0), y0 = argF(args, 1, 0), x1 = argF(args, 2, 0), y1 = argF(args, 3, 0);
                    float r = argF(args, 4, 0);
                    if (r <= 0.5f) {
                        data.pathLineTo(x0, y0);
                        data.pathLineTo(x1, y0);
                        data.pathLineTo(x1, y1);
                        data.pathLineTo(x0, y1);
                    } else {
                        float rr = Math.min(r, Math.min(x1 - x0, y1 - y0) * 0.5f);
                        int seg = 8;
                        data.pathArcTo(x1 - rr, y0 + rr, rr, (float) (-Math.PI / 2), 0, seg);
                        data.pathArcTo(x1 - rr, y1 - rr, rr, 0, (float) (Math.PI / 2), seg);
                        data.pathArcTo(x0 + rr, y1 - rr, rr, (float) (Math.PI / 2), (float) Math.PI, seg);
                        data.pathArcTo(x0 + rr, y0 + rr, rr, (float) Math.PI, (float) (Math.PI * 1.5), seg);
                    }
                    return null;
                }
                case "pathFillConvex":
                    data.addConvexPolyFilled(new ArrayList<>(data.path), argI(args, 0, 0xFFFFFFFF));
                    data.path.clear();
                    return null;
                case "pathStroke":
                    data.addPolyline(new ArrayList<>(data.path), argI(args, 0, 0xFFFFFFFF),
                        argB(args, 1, false), argF(args, 2, 1));
                    data.path.clear();
                    return null;
                case "pathClear": data.path.clear(); return null;
                case "channelsSplit": return null;
                case "channelsMerge": return null;
                case "channelsSetCurrent": return null;
                default: return null;
            }
        }

        Object drawData(String simple, String name, String desc, Object self, Object[] args) {
            DrawData data = self == null ? this.drawData : (DrawData) data(self);
            if (data == null) data = this.drawData;
            switch (name) {
                case "getCmdListsCount": return data.lists.size();
                case "getTotalVtxCount": {
                    int total = 0;
                    for (DrawList list : data.lists) total += list.vertices.size();
                    return total;
                }
                case "getTotalIdxCount": {
                    int total = 0;
                    for (DrawList list : data.lists) total += list.indices.size();
                    return total;
                }
                case "getCmdListVtxBufferSize": return data.lists.get(argI(args, 0, 0)).vertices.size();
                case "getCmdListIdxBufferSize": return data.lists.get(argI(args, 0, 0)).indices.size();
                case "getCmdListVtxBufferData": return buffer(data.lists.get(argI(args, 0, 0)).vtxBuffer);
                case "getCmdListIdxBufferData": return buffer(data.lists.get(argI(args, 0, 0)).idxBuffer);
                case "getCmdListCmdBufferSize": return data.lists.get(argI(args, 0, 0)).commands.size();
                case "getCmdListCmdBufferElemCount": return data.lists.get(argI(args, 0, 0)).commands.get(argI(args, 1, 0)).elemCount;
                case "getCmdListCmdBufferTextureId": return data.lists.get(argI(args, 0, 0)).commands.get(argI(args, 1, 0)).textureId;
                case "getCmdListCmdBufferVtxOffset": return data.lists.get(argI(args, 0, 0)).commands.get(argI(args, 1, 0)).vtxOffset;
                case "getCmdListCmdBufferIdxOffset": return data.lists.get(argI(args, 0, 0)).commands.get(argI(args, 1, 0)).idxOffset;
                case "getCmdListCmdBufferClipRect": {
                    boolean hasOut = args.length >= 3;
                    int listIndex = hasOut ? argI(args, 1, 0) : argI(args, 0, 0);
                    int cmdIndex = hasOut ? argI(args, 2, 0) : argI(args, 1, 0);
                    Cmd cmd = data.lists.get(listIndex).commands.get(cmdIndex);
                    Object out = hasOut ? arg(args, 0) : null;
                    if (out != null && out.getClass().getSimpleName().equals("ImVec4")) {
                        Reflect.set(out, "x", cmd.clipMinX);
                        Reflect.set(out, "y", cmd.clipMinY);
                        Reflect.set(out, "z", cmd.clipMaxX);
                        Reflect.set(out, "w", cmd.clipMaxY);
                        return null;
                    }
                    return vec4(cmd.clipMinX, cmd.clipMinY, cmd.clipMaxX, cmd.clipMaxY);
                }
                case "getDisplayPos": return vec2(0, 0);
                case "getDisplayPosX": return 0f;
                case "getDisplayPosY": return 0f;
                case "getDisplaySize": return vec2(data.displayW, data.displayH);
                case "getDisplaySizeX": return data.displayW;
                case "getDisplaySizeY": return data.displayH;
                case "getFramebufferScale": return vec2(data.fbScaleX, data.fbScaleY);
                case "getFramebufferScaleX": return data.fbScaleX;
                case "getFramebufferScaleY": return data.fbScaleY;
                case "sizeOfImDrawVert": return 20;
                case "sizeOfImDrawIdx": return 2;
                case "getValid": return data.valid;
                case "clear": return null;
                case "addDrawList": return null;
                case "deIndexAllBuffers": return null;
                case "scaleClipRects": return null;
                case "getOwnerViewport": return viewportObject();
                default: return null;
            }
        }

        ByteBuffer buffer(ByteBuffer buffer) {
            ByteBuffer copy = buffer.duplicate();
            copy.position(0);
            // Use the filled limit, not capacity: reused direct buffers are
            // larger than the current frame. Reporting capacity made Axiom
            // allocate a smaller staging buffer and throw BufferOverflow.
            copy.limit(buffer.limit());
            return copy;
        }

        Object fontAtlas(String simple, String name, String desc, Object self, Object[] args) {
            FontAtlas atlas = self == null ? this.atlas : (FontAtlas) data(self);
            if (atlas == null) atlas = this.atlas;
            switch (name) {
                case "addFont", "addFontDefault", "addFontDefaultVector", "addFontDefaultBitmap",
                    "addFontFromMemoryTTF": {
                    float size = argF(args, 0, this.style.fontSize);
                    if (args.length > 1 && (arg(args, 0) instanceof byte[])) {
                        size = argF(args, 1, this.style.fontSize);
                    }
                    if (args.length > 2 && arg(args, 2) instanceof Number n && n.floatValue() > 2f) {
                        size = n.floatValue();
                    }
                    byte[] fontBytes = null;
                    for (Object arg : args) {
                        if (arg instanceof byte[] b) {
                            fontBytes = b;
                            break;
                        }
                    }
                    FontConfigData cfg = null;
                    short[] ranges = null;
                    for (Object a : args) {
                        if (a != null && a.getClass().getSimpleName().equals("ImFontConfig")) {
                            cfg = this.fontConfigs.get(ptr(a));
                        } else if (a instanceof short[] r) {
                            ranges = r;
                        }
                    }
                    FontData previous = atlas.current;
                    FontData font = atlas.addFont((int) Math.max(8, size), null, fontBytes, cfg, ranges);
                    if (atlas.current != previous) {
                        this.style.fontSize = Math.max(8, (int) size);
                    }
                    long handle = newHandle();
                    Object wrapper = wrapper("ImFont", handle, font);
                    try {
                        Reflect.set(font, "object", wrapper);
                    } catch (Throwable ignored) {
                    }
                    return wrapper;
                }
                case "getGlyphRangesDefault": return GlyphRanges.DEFAULT.clone();
                case "getGlyphRangesCyrillic": return GlyphRanges.CYRILLIC.clone();
                case "getGlyphRangesThai": return GlyphRanges.THAI.clone();
                case "getGlyphRangesVietnamese": return GlyphRanges.VIETNAMESE.clone();
                case "getGlyphRangesJapanese": return GlyphRanges.JAPANESE.clone();
                case "getGlyphRangesChineseFull": return GlyphRanges.CHINESE_FULL.clone();
                case "getGlyphRangesChineseSimplifiedCommon": return GlyphRanges.CHINESE_SIMPLIFIED_COMMON.clone();
                case "getGlyphRangesKorean": return GlyphRanges.KOREAN.clone();
                case "getTexDataAsRGBA32": {
                    Object w = arg(args, 0), h = arg(args, 1);
                    if (w != null) Reflect.call(w, "set", atlas.width);
                    if (h != null) Reflect.call(h, "set", atlas.height);
                    if (args.length > 2 && arg(args, 2) != null) Reflect.call(arg(args, 2), "set", 4);
                    atlas.ensureAtlas();
                    atlas.uploaded = true;
                    atlas.pixels.position(0);
                    return atlas.pixels;
                }
                case "getTexDataAsAlpha8": {
                    Object w = arg(args, 0), h = arg(args, 1);
                    if (w != null) Reflect.call(w, "set", atlas.width);
                    if (h != null) Reflect.call(h, "set", atlas.height);
                    atlas.ensureAtlas();
                    atlas.uploaded = true;
                    atlas.pixels.position(0);
                    return atlas.pixels;
                }
                case "getTexDataAsRGBA32Width": return atlas.width;
                case "getTexDataAsRGBA32Height": return atlas.height;
                case "setTexID": atlas.texId = arg(args, 0) instanceof Number n ? n.longValue() : 0; return null;
                case "getTexID": return atlas.texId;
                case "clear": atlas.clear(); return null;
                case "clearTexData": atlas.clearTexData(); return null;
                case "build": atlas.ensureAtlas(); return true;
                case "isBuilt": return true;
                case "getFonts": return null;
                default: return null;
            }
        }

        Object font(String simple, String name, String desc, Object self, Object[] args) {
            FontData font = self == null ? this.atlas.current : (FontData) data(self);
            if (font == null) font = this.atlas.current;
            switch (name) {
                case "getFontSize": return font == null ? this.style.fontSize : (float) font.size;
                case "getLegacySize": return font == null ? this.style.fontSize : (float) font.size;
                case "setLegacySize": return null;
                case "getScale": return 1f;
                case "setScale": return null;
                case "getEllipsisChar": return (short) 0x2026;
                case "getFallbackChar": return (short) '?';
                case "setFallbackChar": return null;
                case "getCharAdvance": return this.atlas.measure(String.valueOf((char) argI(args, 0, 32)), font == null ? this.style.fontSize : font.size);
                case "calcTextSizeA": {
                    String text = argS(args, 3);
                    return vec2(this.atlas.measure(text, argF(args, 0, this.style.fontSize)), argF(args, 0, this.style.fontSize));
                }
                case "findGlyph": return null;
                case "findGlyphNoFallback": return null;
                case "getIndexAdvanceX": return this.atlas.measure(String.valueOf((char) argI(args, 0, 32)), font == null ? this.style.fontSize : font.size);
                case "isGlyphInFont": return true;
                default: return null;
            }
        }

        Object viewport(String simple, String name, String desc, Object self, Object[] args) {
            switch (name) {
                case "getPos": return vec2(this.viewport.x, this.viewport.y);
                case "getPosX": return this.viewport.x;
                case "getPosY": return this.viewport.y;
                case "getSize": return vec2(this.viewport.w, this.viewport.h);
                case "getSizeX": return this.viewport.w;
                case "getSizeY": return this.viewport.h;
                case "getWorkPos": return vec2(this.viewport.workX, this.viewport.workY);
                case "getWorkPosX": return this.viewport.workX;
                case "getWorkPosY": return this.viewport.workY;
                case "getWorkSize": return vec2(this.viewport.workW, this.viewport.workH);
                case "getWorkSizeX": return this.viewport.workW;
                case "getWorkSizeY": return this.viewport.workH;
                case "getCenter": return vec2(this.viewport.x + this.viewport.w / 2, this.viewport.y + this.viewport.h / 2);
                case "getCenterX": return this.viewport.x + this.viewport.w / 2;
                case "getCenterY": return this.viewport.y + this.viewport.h / 2;
                case "getID": return this.viewport.id;
                case "getFlags": return this.viewport.flags;
                case "setFlags": this.viewport.flags = argI(args, 0, 0); return null;
                case "getDpiScale": return 1f;
                case "getFramebufferScale": return vec2(1, 1);
                case "getFramebufferScaleX": return 1f;
                case "getFramebufferScaleY": return 1f;
                case "setPos": return null;
                case "setSize": return null;
                case "setWorkPos":
                    this.viewport.workX = argF(args, 0, 0);
                    this.viewport.workY = argF(args, 1, 0);
                    this.workPosSetThisFrame = true;
                    return null;
                case "setWorkSize":
                    this.viewport.workW = Math.max(1, argF(args, 0, 0));
                    this.viewport.workH = Math.max(1, argF(args, 1, 0));
                    this.workSetThisFrame = true;
                    return null;
                default: return null;
            }
        }

        Object storage(String simple, String name, String desc, Object self, Object[] args) {
            switch (name) {
                case "getInt":
                case "getFloat":
                case "getBool": {
                    int[] value = this.storage.get(argI(args, 0, 0));
                    return value == null ? 0 : (name.equals("getFloat") ? (float) value[0] : value[0] != 0);
                }
                case "setInt":
                case "setFloat":
                case "setBool": {
                    this.storage.put(argI(args, 0, 0), new int[]{argI(args, 1, 0)});
                    return null;
                }
                case "getVoidPtr": return null;
                case "setVoidPtr": return null;
                case "buildSortByKey": return null;
                case "clear": this.storage.clear(); return null;
                default: return null;
            }
        }

        Object fontConfig(String simple, String name, String desc, Object self, Object[] args) {
            if (name.equals("create")) {
                long handle = newHandle();
                this.fontConfigs.put(handle, new FontConfigData());
                return (double) handle;
            }
            if (self == null) return null;
            FontConfigData cfg = this.fontConfigs.computeIfAbsent(ptr(self), k -> new FontConfigData());
            return switch (name) {
                case "setMergeMode" -> { cfg.mergeMode = argB(args, 0, false); yield null; }
                case "getMergeMode" -> cfg.mergeMode;
                case "setGlyphOffset" -> { cfg.glyphOffsetX = argF(args, 0, 0); cfg.glyphOffsetY = argF(args, 1, 0); yield null; }
                case "getGlyphOffsetX" -> cfg.glyphOffsetX;
                case "getGlyphOffsetY" -> cfg.glyphOffsetY;
                case "setOversampleH" -> { cfg.oversampleH = argI(args, 0, 1); yield null; }
                case "setOversampleV" -> { cfg.oversampleV = argI(args, 0, 1); yield null; }
                case "getOversampleH" -> cfg.oversampleH;
                case "getOversampleV" -> cfg.oversampleV;
                case "setName" -> { cfg.name = argS(args, 0); yield null; }
                case "getName" -> cfg.name;
                case "setSizePixels" -> { cfg.sizePixels = argF(args, 0, 0); yield null; }
                case "getSizePixels" -> cfg.sizePixels;
                case "setGlyphRanges" -> { cfg.glyphRanges = arg(args, 0) instanceof short[] r ? r : null; yield null; }
                case "getGlyphRanges" -> cfg.glyphRanges;
                case "setGlyphExcludeRanges" -> { cfg.glyphExcludeRanges = arg(args, 0) instanceof short[] r ? r : null; yield null; }
                case "getGlyphExcludeRanges" -> cfg.glyphExcludeRanges;
                case "setPixelSnapH" -> { cfg.pixelSnapH = argB(args, 0, false); yield null; }
                case "getPixelSnapH" -> cfg.pixelSnapH;
                case "setRasterizerMultiply" -> { cfg.rasterizerMultiply = argF(args, 0, 1); yield null; }
                case "getRasterizerMultiply" -> cfg.rasterizerMultiply;
                case "getFontNo" -> 0;
                case "getFontDataSize" -> 0;
                default -> null;
            };
        }

        Object textEditor(String simple, String name, String desc, Object self, Object[] args) {
            if (self == null) return null;
            long handle = ptr(self);
            if (name.equals("create")) {
                handle = newHandle();
                this.textEditors.computeIfAbsent(handle, k -> new TextEditorData());
                setPtr(self, handle);
                return handle;
            }
            TextEditorData data = this.textEditors.computeIfAbsent(handle, k -> new TextEditorData());
            String inputId = "##texteditor_" + handle;
            if (this.activeInput != null && this.activeInput.equals(inputId) && !data.readOnly) {
                handleTextEditorInput(data);
            }
            switch (name) {
                case "getText": return data.text;
                case "setText": data.text = argS(args, 0); return null;
                case "clearText": data.text = ""; return null;
                case "isEmpty": return data.text.isEmpty();
                case "getLineCount": return (int) data.text.lines().count();
                case "getLineText": {
                    int line = argI(args, 0, 0);
                    String[] lines = data.text.split("\n", -1);
                    return line >= 0 && line < lines.length ? lines[line] : "";
                }
                case "render": {
                    String title = argS(args, 0);
                    float width = args.length > 1 && arg(args, 1) instanceof Number ? argF(args, 1, 0) : 0;
                    float height = args.length > 2 && arg(args, 2) instanceof Number ? argF(args, 2, 0) : 0;
                    if (args.length > 1 && arg(args, 1) != null
                        && arg(args, 1).getClass().getSimpleName().equals("ImVec2")) {
                        width = f(Reflect.get(arg(args, 1), "x"));
                        height = f(Reflect.get(arg(args, 1), "y"));
                    }
                    boolean open = beginChild(title + inputId, width, height, 3);
                    Window ew = currentWindow();
                    if (ew.hovered && this.io.mouseReleased[0]) {
                        this.activeInput = inputId;
                    }
                    String[] lines = data.text.split("\n", -1);
                    int max = Math.min(lines.length, 128);
                    float lineH = frameHeight();
                    for (int i = 0; i < max; i++) {
                        float y = ew.y + ew.contentY + i * lineH - ew.scrollY;
                        if (y > ew.y + ew.h) break;
                        if (y + lineH < ew.y) continue;
                        float x = ew.x + ew.contentX;
                        if (data.showLineNumbers) {
                            String num = Integer.toString(i + 1);
                            float nw = this.atlas.measure(num, this.style.fontSize) + 12;
                            this.currentDrawList.addText(x, y + this.style.framePaddingY,
                                color(0.55f, 0.55f, 0.60f, 1f), num);
                            x += nw;
                        }
                        String line = lines[i];
                        if (data.showWhitespaces) {
                            line = line.replace(" ", "·").replace("\t", "→");
                        }
                        this.currentDrawList.addText(x, y + this.style.framePaddingY,
                            color(0.90f, 0.90f, 0.92f, 1f), line);
                        if (i == data.cursorLine && this.activeInput != null && this.activeInput.equals(inputId)) {
                            float cx = x + this.atlas.measure(line.substring(0, Math.min(data.cursorColumn, line.length())), this.style.fontSize);
                            this.currentDrawList.addRectFilled(cx, y + 2, cx + 1, y + lineH - 2,
                                color(0.95f, 0.95f, 0.95f, 0.8f));
                        }
                    }
                    if (open) endChild();
                    return null;
                }
                case "getTabSize": return data.tabSize;
                case "setTabSize": data.tabSize = argI(args, 0, 4); return null;
                case "setLanguage": {
                    Object lang = arg(args, 0);
                    Object value = lang == null ? null : data(lang);
                    data.languageName = value == null ? "" : value.toString();
                    return null;
                }
                case "getLanguageName": return data.languageName;
                case "hasLanguage": return data.languageName != null && !data.languageName.isEmpty();
                case "addMarker":
                    data.markers.add(new int[]{argI(args, 0, 0), argI(args, 1, 0), argI(args, 2, 0)});
                    return null;
                case "clearMarkers": data.markers.clear(); return null;
                case "hasMarkers": return !data.markers.isEmpty();
                case "setShowLineNumbersEnabled": data.showLineNumbers = argB(args, 0, false); return null;
                case "isShowLineNumbersEnabled": return data.showLineNumbers;
                case "setShowWhitespacesEnabled": data.showWhitespaces = argB(args, 0, false); return null;
                case "isShowWhitespacesEnabled": return data.showWhitespaces;
                case "setShowSpacesEnabled": data.showSpaces = argB(args, 0, false); return null;
                case "isShowSpacesEnabled": return data.showSpaces;
                case "setShowTabsEnabled": data.showTabs = argB(args, 0, false); return null;
                case "isShowTabsEnabled": return data.showTabs;
                case "setAutoIndentEnabled": data.autoIndent = argB(args, 0, false); return null;
                case "isAutoIndentEnabled": return data.autoIndent;
                case "getCursorPositionLine": return data.cursorLine;
                case "getCursorPositionColumn": return data.cursorColumn;
                case "setCursorPosition": data.cursorLine = argI(args, 0, 0); data.cursorColumn = argI(args, 1, 0); return null;
                case "selectAll": data.selection = true; return null;
                case "undo":
                case "redo": return null;
                case "copy":
                case "cut":
                case "paste": return null;
                case "setReadOnlyEnabled": data.readOnly = argB(args, 0, false); return null;
                case "isReadOnlyEnabled": return data.readOnly;

                case "setShowScrollbarMiniMapEnabled": return null;
                case "setShowPanScrollIndicatorEnabled": return null;
                case "setShowMatchingBrackets": return null;
                case "setCompletePairedGlyphs": return null;
                default: return null;
            }
        }

        void handleTextEditorInput(TextEditorData data) {
            String[] lines = data.text.split("\n", -1);
            data.cursorLine = Math.max(0, Math.min(data.cursorLine, lines.length - 1));
            data.cursorColumn = Math.max(0, Math.min(data.cursorColumn, lines[data.cursorLine].length()));
            StringBuilder all = new StringBuilder(data.text);
            // Convert the caret to an absolute offset.
            int offset = 0;
            for (int i = 0; i < data.cursorLine; i++) offset += lines[i].length() + 1;
            offset += data.cursorColumn;
            boolean changed = false;
            if (this.io.keysPressed.contains(NAV_KEY_BACKSPACE) && offset > 0) {
                all.deleteCharAt(offset - 1);
                offset--;
                changed = true;
            }
            if (this.io.keysPressed.contains(NAV_KEY_DELETE) && offset < all.length()) {
                all.deleteCharAt(offset);
                changed = true;
            }
            if (this.io.keysPressed.contains(NAV_KEY_ENTER)) {
                all.insert(offset, '\n');
                offset++;
                changed = true;
            }
            if (this.io.keysPressed.contains(NAV_KEY_TAB)) {
                int spaces = Math.max(1, data.tabSize);
                for (int i = 0; i < spaces; i++) all.insert(offset++, ' ');
                changed = true;
            }
            for (Object ch : this.io.chars) {
                String s = String.valueOf(ch);
                all.insert(offset, s);
                offset += s.length();
                changed = true;
            }
            if (this.io.keysPressed.contains(NAV_KEY_LEFT) && offset > 0) offset--;
            if (this.io.keysPressed.contains(NAV_KEY_RIGHT) && offset < all.length()) offset++;
            if (this.io.keysPressed.contains(NAV_KEY_UP)) {
                offset = 0;
                for (int i = 0; i < Math.max(0, data.cursorLine - 1); i++) {
                    int nl = all.indexOf("\n", offset);
                    if (nl < 0) break;
                    offset = nl + 1;
                }
            }
            if (this.io.keysPressed.contains(NAV_KEY_DOWN)) {
                int nl = all.indexOf("\n", offset);
                if (nl >= 0) offset = nl + 1;
            }
            if (changed) {
                data.text = all.toString();
                lines = data.text.split("\n", -1);
                int remaining = offset;
                data.cursorLine = 0;
                while (data.cursorLine < lines.length - 1 && remaining > lines[data.cursorLine].length()) {
                    remaining -= lines[data.cursorLine].length() + 1;
                    data.cursorLine++;
                }
                data.cursorColumn = Math.max(0, Math.min(remaining, lines[data.cursorLine].length()));
            }
        }

        Object listClipper(String simple, String name, String desc, Object self, Object[] args) {
            ClipperData data = null;
            if (self != null) {
                Object value = data(self);
                if (value instanceof ClipperData c) data = c;
                if (data == null) {
                    data = new ClipperData();
                    this.handles.put(ptr(self), data);
                }
            }
            if (data == null) data = new ClipperData();
            switch (name) {
                case "begin": {
                    int count = Math.max(0, argI(args, 0, 0));
                    float height = argF(args, 1, 0);
                    Window w = currentWindow();
                    if (height <= 0) height = frameHeight();
                    data.count = count;
                    data.height = Math.max(1, height);
                    data.start = 0;
                    data.end = count;
                    data.step = 0;
                    if (w != null) {
                        float clipTop = w.drawList.clipStack.isEmpty() ? w.y : w.drawList.clipMinY;
                        float clipBottom = w.drawList.clipStack.isEmpty() ? w.y + w.h : w.drawList.clipMaxY;
                        float top = w.y + w.cursorY - w.scrollY;
                        float visible = Math.max(1, clipBottom - clipTop);
                        data.start = Math.max(0, (int) ((clipTop - top) / data.height));
                        data.end = Math.min(count, (int) Math.ceil((clipBottom - top) / data.height) + 1);
                    }
                    return null;
                }
                case "beginWithItemsCount":
                case "beginWithItemsCountAndHeight": return null;
                case "step": {
                    if (data.step == 0) {
                        data.step = 1;
                        return true;
                    }
                    if (data.step == 1) {
                        data.step = 2;
                        return true;
                    }
                    return false;
                }
                case "end": data.step = 3; return null;
                case "getDisplayStart": return data.start;
                case "getDisplayEnd": return data.end;
                case "setDisplayStart": data.start = argI(args, 0, 0); return null;
                case "setDisplayEnd": data.end = argI(args, 0, 0); return null;
                case "includeItemByIndex": {
                    int index = argI(args, 0, 0);
                    if (index >= 0 && index < data.count) {
                        data.start = Math.min(data.start, index);
                        data.end = Math.max(data.end, index + 1);
                    }
                    return null;
                }
                case "includeItemsByIndex":
                    data.start = Math.min(data.start, argI(args, 0, 0));
                    data.end = Math.max(data.end, argI(args, 1, 0) + 1);
                    return null;
                case "forceIncludeItemByIndex": return true;
                case "getStartPosY": return 0f;
                case "getItemsCount": return data.count;
                default: return null;
            }
        }

        Object inputTextData(String simple, String name, String desc, Object self, Object[] args) {
            switch (name) {
                case "getEventFlag": return 0;
                case "setEventFlag": return null;
                case "getFlags": return 0;
                case "getID": return 0;
                case "getBufTextLen": return argS(args, 0).length();
                case "getBufText": return "";
                case "getCursorPos": return 0;
                case "setCursorPos": return null;
                case "getSelectionStart": return 0;
                case "getSelectionEnd": return 0;
                case "setSelectionStart": return null;
                case "setSelectionEnd": return null;
                case "deleteChars": return null;
                case "insertChars": return null;
                default: return null;
            }
        }

        Object colorConvertU32(int color) {            return vec4((color & 0xFF) / 255f, ((color >> 8) & 0xFF) / 255f, ((color >> 16) & 0xFF) / 255f, ((color >> 24) & 0xFF) / 255f);
        }

        Style styleFor(Object self) {
            if (self == null) return this.style;
            long handle = ptr(self);
            if (handle == 0) return this.style;
            Object data = this.handles.get(handle);
            if (data instanceof Style s) return s;
            if (handle == 2L) return this.style;
            Style created = new Style();
            this.handles.put(handle, created);
            return created;
        }

        Object colorVec(int index) {
            Style st = this.activeStyle != null ? this.activeStyle : this.style;
            int i = Math.max(0, index) * 4;
            if (i + 3 >= st.colors.length) {
                return vec4(1, 1, 1, 1);
            }
            return vec4(st.colors[i], st.colors[i + 1], st.colors[i + 2], st.colors[i + 3]);
        }

        int colorConvertFloat4(float r, float g, float b, float a) {
            return ((int) (r * 255) & 0xFF) | (((int) (g * 255) & 0xFF) << 8)
                | (((int) (b * 255) & 0xFF) << 16) | (((int) (a * 255) & 0xFF) << 24);
        }

        void colorConvertRGBtoHSV(Object[] args) {
            float[] rgb = (float[]) arg(args, 0);
            float[] hsv = (float[]) arg(args, 1);
            if (rgb == null || hsv == null || rgb.length < 3) return;
            float r = rgb[0], g = rgb[1], b = rgb[2];
            float max = Math.max(r, Math.max(g, b));
            float min = Math.min(r, Math.min(g, b));
            float d = max - min;
            float h = 0;
            if (d != 0) {
                if (max == r) h = ((g - b) / d) % 6;
                else if (max == g) h = (b - r) / d + 2;
                else h = (r - g) / d + 4;
                h /= 6;
                if (h < 0) h += 1;
            }
            hsv[0] = h;
            hsv[1] = max == 0 ? 0 : d / max;
            hsv[2] = max;
        }

        void colorConvertHSVtoRGB(Object[] args) {
            float[] hsv = (float[]) arg(args, 0);
            float[] rgb = (float[]) arg(args, 1);
            if (hsv == null || rgb == null || hsv.length < 3) return;
            float h = hsv[0], s = hsv[1], v = hsv[2];
            int i = (int) Math.floor(h * 6);
            float f = h * 6 - i;
            float p = v * (1 - s);
            float q = v * (1 - f * s);
            float t = v * (1 - (1 - f) * s);
            switch (i % 6) {
                case 0 -> { rgb[0] = v; rgb[1] = t; rgb[2] = p; }
                case 1 -> { rgb[0] = q; rgb[1] = v; rgb[2] = p; }
                case 2 -> { rgb[0] = p; rgb[1] = v; rgb[2] = t; }
                case 3 -> { rgb[0] = p; rgb[1] = q; rgb[2] = v; }
                case 4 -> { rgb[0] = t; rgb[1] = p; rgb[2] = v; }
                default -> { rgb[0] = v; rgb[1] = p; rgb[2] = q; }
            }
        }

        Object calcTextSize(String text, Object wrapWidth, boolean hideAfterDoubleHash, float scale) {
            if (hideAfterDoubleHash) text = visibleText(text);
            float size = this.style.fontSize * (scale > 0 ? scale : 1);
            float width = this.atlas.measure(text, size);
            width = (float) (int) (width + 0.99999f); // ImGui CalcTextSize rounding
            if (this.textWrapPos > 0) {
                width = Math.min(width, this.textWrapPos);
            }
            return vec2(width, size);
        }

        List<String> wrap(String text, float maxWidth) {
            List<String> lines = new ArrayList<>();
            StringBuilder current = new StringBuilder();
            for (String word : text.split(" ")) {
                String candidate = current.isEmpty() ? word : current + " " + word;
                if (this.atlas.measure(candidate, this.style.fontSize) > maxWidth && !current.isEmpty()) {
                    lines.add(current.toString());
                    current = new StringBuilder(word);
                } else {
                    current = new StringBuilder(candidate);
                }
            }
            if (!current.isEmpty()) lines.add(current.toString());
            return lines;
        }

        int styleColor(int index) {
            return this.style.colorU32(index, this.globalAlpha * this.style.alpha);
        }

        int color(float r, float g, float b, float a) {
            return ((int) (r * 255) & 0xFF) | (((int) (g * 255) & 0xFF) << 8)
                | (((int) (b * 255) & 0xFF) << 16) | (((int) (a * 255 * this.globalAlpha) & 0xFF) << 24);
        }

        Object getColorU32(Object[] args) {
            if (args.length >= 1 && arg(args, 0) != null
                && arg(args, 0).getClass().getSimpleName().equals("ImVec4")) {
                Object c = arg(args, 0);
                return colorConvertFloat4(f(Reflect.get(c, "x")), f(Reflect.get(c, "y")),
                    f(Reflect.get(c, "z")), f(Reflect.get(c, "w")));
            }
            if (args.length == 2) {
                return this.style.colorU32(argI(args, 0, 0), argF(args, 1, 1));
            }
            if (args.length == 1) {
                Object first = args[0];
                if (first instanceof Number n) {
                    int col = n.intValue();
                    // ImGuiCol values are 0..63. Anything larger is a packed colour.
                    if (col >= 0 && col < 64) {
                        return this.style.colorU32(col, this.globalAlpha);
                    }
                    return col;
                }
                return 0xFFFFFFFF;
            }
            return colorConvertFloat4(argF(args, 0, 0), argF(args, 1, 0), argF(args, 2, 0), argF(args, 3, 1));
        }

        void pushStyleColor(Object[] args) {
            if (args.length < 2) return;
            int index = argI(args, 0, 0);
            int base = Math.max(0, index) * 4;
            if (base + 3 >= this.style.colors.length) return;
            float r, g, b, a;
            Object second = arg(args, 1);
            if (second != null && second.getClass().getSimpleName().equals("ImVec4")) {
                r = f(Reflect.get(second, "x")); g = f(Reflect.get(second, "y"));
                b = f(Reflect.get(second, "z")); a = f(Reflect.get(second, "w"));
            } else if (args.length >= 5) {
                r = argF(args, 1, 0); g = argF(args, 2, 0); b = argF(args, 3, 0); a = argF(args, 4, 1);
            } else if (second instanceof Number n) {
                int packed = n.intValue();
                r = (packed & 0xFF) / 255f; g = ((packed >> 8) & 0xFF) / 255f;
                b = ((packed >> 16) & 0xFF) / 255f; a = ((packed >> 24) & 0xFF) / 255f;
            } else {
                r = 1; g = 1; b = 1; a = 1;
            }
            this.styleColorStack.add(new float[]{index, this.style.colors[base], this.style.colors[base + 1],
                this.style.colors[base + 2], this.style.colors[base + 3]});
            this.style.set(index, r, g, b, a);
        }

        void popStyleColor(int count) {
            for (int i = 0; i < count && !this.styleColorStack.isEmpty(); i++) {
                float[] old = this.styleColorStack.remove(this.styleColorStack.size() - 1);
                this.style.set((int) old[0], old[1], old[2], old[3], old[4]);
            }
        }

        void pushStyleVar(Object[] args) {
            if (args.length < 2) return;
            this.styleVarStack.add(this.style.copy());
            this.style.setVarById(argI(args, 0, -1), args);
        }

        void popStyleVar(int count) {
            for (int i = 0; i < count && !this.styleVarStack.isEmpty(); i++) {
                this.style.restore(this.styleVarStack.remove(this.styleVarStack.size() - 1));
            }
        }

        boolean bool(Object value) {
            if (value == null) return false;
            try {
                Object v = Reflect.call(value, "get");
                return v instanceof Boolean b && b;
            } catch (Throwable t) {
                return false;
            }
        }

        void setBool(Object value, boolean v) {
            if (value == null) return;
            try {
                Reflect.call(value, "set", v);
            } catch (Throwable ignored) {
            }
        }

        String stringValue(Object value) {
            if (value == null) return "";
            try {
                Object v = Reflect.call(value, "get");
                return v == null ? "" : v.toString();
            } catch (Throwable t) {
                return value.toString();
            }
        }

        void setString(Object value, String v) {
            if (value == null) return;
            try {
                Reflect.call(value, "set", v);
            } catch (Throwable ignored) {
            }
        }

        float floatValue(Object value) {
            if (value == null) return 0;
            if (value instanceof Number n) return n.floatValue();
            try {
                Object v = Reflect.call(value, "get");
                return v instanceof Number n ? n.floatValue() : 0;
            } catch (Throwable t) {
                return 0;
            }
        }

        void setFloat(Object value, float v) {
            if (value == null) return;
            try {
                Reflect.call(value, "set", v);
            } catch (Throwable ignored) {
            }
        }

        int intValue(Object value) {
            if (value == null) return 0;
            if (value instanceof Number n) return n.intValue();
            try {
                Object v = Reflect.call(value, "get");
                return v instanceof Number n ? n.intValue() : 0;
            } catch (Throwable t) {
                return 0;
            }
        }

        void setInt(Object value, int v) {
            if (value == null) return;
            try {
                Reflect.call(value, "set", v);
            } catch (Throwable ignored) {
            }
        }
    }

    // ------------------------------------------------------------------
    // Raw data
    // ------------------------------------------------------------------

    static final class IO {
        float displayW = 1280;
        float displayH = 720;
        float fbScaleX = 1;
        float fbScaleY = 1;
        float delta = 1 / 60f;
        float mouseX;
        float mouseY;
        boolean[] mouseDown = new boolean[5];
        boolean[] mousePressed = new boolean[5];
        boolean[] mouseReleased = new boolean[5];
        boolean[] mouseNextPressed = new boolean[5];
        boolean[] mouseNextReleased = new boolean[5];
        float[] dragX = new float[5];
        float[] dragY = new float[5];
        float[] dragStartX = new float[5];
        float[] dragStartY = new float[5];
        float wheel;
        float wheelH;
        int configFlags;
        int backendFlags;
        boolean ctrl;
        boolean shift;
        boolean alt;
        boolean superKey;
        boolean focused = true;
        /** -1 = not overridden this frame, 0/1 = forced by the application. */
        int nextWantCaptureMouse = -1;
        int nextWantCaptureKeyboard = -1;
        boolean wantCaptureMouse;
        boolean wantCaptureKeyboard;
        int mouseCursor;
        boolean mouseDrawCursor;
        final boolean[] mouseDownOwned = new boolean[5];
        final double[] mouseClickedTime = new double[5];
        double time;
        final Set<Integer> keysDown = ConcurrentHashMap.newKeySet();
        Set<Integer> keysPressed = ConcurrentHashMap.newKeySet();
        Set<Integer> keysReleased = ConcurrentHashMap.newKeySet();
        final Set<Integer> keysNextPressed = ConcurrentHashMap.newKeySet();
        final Set<Integer> keysNextReleased = ConcurrentHashMap.newKeySet();
        final List<Object> chars = new ArrayList<>();
        Object clipboardSupplier;
        Object clipboardConsumer;

        void mouseButton(int button, boolean down) {
            button = Math.max(0, Math.min(4, button));
            if (down == this.mouseDown[button]) return;
            this.mouseDown[button] = down;
            if (down) {
                this.mouseNextPressed[button] = true;
                this.mouseClickedTime[button] = this.time;
                this.dragStartX[button] = this.mouseX;
                this.dragStartY[button] = this.mouseY;
                this.dragX[button] = 0;
                this.dragY[button] = 0;
            } else {
                this.mouseNextReleased[button] = true;
            }
        }

        void key(int key, boolean down) {
            if (down) {
                if (this.keysDown.add(key)) {
                    this.keysNextPressed.add(key);
                }
            } else {
                this.keysDown.remove(key);
                this.keysNextReleased.add(key);
            }
        }

        boolean anyMouseDown() {
            for (boolean b : this.mouseDown) if (b) return true;
            return false;
        }

        float dragDistance(int button) {
            float dx = this.mouseX - this.dragStartX[button];
            float dy = this.mouseY - this.dragStartY[button];
            return (float) Math.sqrt(dx * dx + dy * dy);
        }

        float[] dragDistanceArray() {
            float[] out = new float[5];
            for (int i = 0; i < 5; i++) {
                out[i] = dragDistance(i) * dragDistance(i);
            }
            return out;
        }

        String clipboard() {
            if (this.clipboardSupplier != null) {
                try {
                    return String.valueOf(Reflect.call(this.clipboardSupplier, "get"));
                } catch (Throwable ignored) {
                }
            }
            return "";
        }

        void setClipboard(String text) {
            if (this.clipboardConsumer != null) {
                try {
                    Reflect.call(this.clipboardConsumer, "accept", text);
                } catch (Throwable ignored) {
                }
            }
        }
    }

    static final class Style {
        float fontSize = 16;
        float alpha = 1;
        float disabledAlpha = 0.6f;
        float windowPaddingX = 8;
        float windowPaddingY = 8;
        float framePaddingX = 4;
        float framePaddingY = 3;
        float itemSpacingX = 8;
        float itemSpacingY = 4;
        float itemInnerSpacingX = 4;
        float itemInnerSpacingY = 4;
        float cellPaddingX = 4;
        float cellPaddingY = 2;
        float indentSpacing = 21;
        float scrollbarSize = 14;
        float windowRounding = 0;
        float frameRounding = 0;
        float windowBorderSize = 1;
        float frameBorderSize = 0;
        float popupRounding = 0;
        float popupBorderSize = 1;
        float childRounding = 0;
        float childBorderSize = 1;
        float grabMinSize = 10;
        float grabRounding = 0;
        float scrollbarRounding = 0;
        float windowMinSizeX = 32, windowMinSizeY = 32;
        float dockingSeparatorSize = 2;
        float tabRounding = 0;
        float tabBorderSize = 0;
        final float[] colors = new float[64 * 4];
        final Map<String, float[]> vars = new HashMap<>();

        Style() {
            colorsDark();
        }

        Style copy() {
            Style copy = new Style();
            copy.copyFrom(this);
            return copy;
        }

        void copyFrom(Style other) {
            this.fontSize = other.fontSize;
            this.alpha = other.alpha;
            this.disabledAlpha = other.disabledAlpha;
            this.windowPaddingX = other.windowPaddingX;
            this.windowPaddingY = other.windowPaddingY;
            this.framePaddingX = other.framePaddingX;
            this.framePaddingY = other.framePaddingY;
            this.itemSpacingX = other.itemSpacingX;
            this.itemSpacingY = other.itemSpacingY;
            this.itemInnerSpacingX = other.itemInnerSpacingX;
            this.itemInnerSpacingY = other.itemInnerSpacingY;
            this.cellPaddingX = other.cellPaddingX;
            this.cellPaddingY = other.cellPaddingY;
            this.indentSpacing = other.indentSpacing;
            this.scrollbarSize = other.scrollbarSize;
            this.windowRounding = other.windowRounding;
            this.frameRounding = other.frameRounding;
            this.windowBorderSize = other.windowBorderSize;
            this.frameBorderSize = other.frameBorderSize;
            this.popupRounding = other.popupRounding;
            this.popupBorderSize = other.popupBorderSize;
            this.childRounding = other.childRounding;
            this.childBorderSize = other.childBorderSize;
            this.grabMinSize = other.grabMinSize;
            this.grabRounding = other.grabRounding;
            this.tabRounding = other.tabRounding;
            this.tabBorderSize = other.tabBorderSize;
            this.scrollbarRounding = other.scrollbarRounding;
            this.windowMinSizeX = other.windowMinSizeX;
            this.windowMinSizeY = other.windowMinSizeY;
            this.dockingSeparatorSize = other.dockingSeparatorSize;
            System.arraycopy(other.colors, 0, this.colors, 0, this.colors.length);
        }

        void restore(Style other) {
            copyFrom(other);
        }

        void setVarById(int id, Object[] args) {
            float a = argF(args, 1, 0);
            float b = args.length > 2 && args[2] instanceof Number ? argF(args, 2, 0) : a;
            Object first = arg(args, 1);
            if (first != null && first.getClass().getSimpleName().equals("ImVec2")) {
                a = f(Reflect.get(first, "x"));
                b = f(Reflect.get(first, "y"));
            }
            switch (id) {
                case 0 -> alpha = a;
                case 1 -> disabledAlpha = a;
                case 2 -> { windowPaddingX = a; windowPaddingY = b; }
                case 3 -> windowRounding = a;
                case 4 -> windowBorderSize = a;
                case 7 -> childRounding = a;
                case 8 -> childBorderSize = a;
                case 9 -> popupRounding = a;
                case 10 -> popupBorderSize = a;
                case 11 -> { framePaddingX = a; framePaddingY = b; }
                case 12 -> frameRounding = a;
                case 13 -> frameBorderSize = a;
                case 14 -> { itemSpacingX = a; itemSpacingY = b; }
                case 15 -> { itemInnerSpacingX = a; itemInnerSpacingY = b; }
                case 16 -> indentSpacing = a;
                case 17 -> { cellPaddingX = a; cellPaddingY = b; }
                case 18 -> scrollbarSize = a;
                case 19 -> scrollbarSize = a;
                case 21 -> grabMinSize = a;
                case 22 -> grabRounding = a;
                case 25 -> tabRounding = a;
                case 26 -> tabBorderSize = a;
                default -> { }
            }
        }

        void colorsDark() {
            StyleColors.applyDark(this.colors);
        }

        void colorsClassic() {
            StyleColors.applyClassic(this.colors);
        }

        void colorsLight() {
            StyleColors.applyLight(this.colors);
        }

        void set(int index, float r, float g, float b, float a) {
            int i = index * 4;
            if (i + 3 < colors.length) {
                colors[i] = r;
                colors[i + 1] = g;
                colors[i + 2] = b;
                colors[i + 3] = a;
            }
        }

        void setColor(int index, Object vec) {
            if (vec == null) return;
            set(index, f(Reflect.get(vec, "x")), f(Reflect.get(vec, "y")), f(Reflect.get(vec, "z")), f(Reflect.get(vec, "w")));
        }

        int colorU32(int index, float alpha) {
            int i = index * 4;
            if (i + 3 >= colors.length) return 0xFFFFFFFF;
            return ((int) (colors[i] * 255) & 0xFF) | (((int) (colors[i + 1] * 255) & 0xFF) << 8)
                | (((int) (colors[i + 2] * 255) & 0xFF) << 16) | (((int) (colors[i + 3] * 255 * alpha) & 0xFF) << 24);
        }

        Object var(String name, boolean get) {
            return switch (name) {
                case "Alpha" -> alpha;
                case "DisabledAlpha" -> disabledAlpha;
                case "WindowPadding" -> new float[]{windowPaddingX, windowPaddingY};
                case "FramePadding" -> new float[]{framePaddingX, framePaddingY};
                case "ItemSpacing" -> new float[]{itemSpacingX, itemSpacingY};
                case "ItemInnerSpacing" -> new float[]{itemInnerSpacingX, itemInnerSpacingY};
                case "CellPadding" -> new float[]{cellPaddingX, cellPaddingY};
                case "IndentSpacing" -> indentSpacing;
                case "ScrollbarSize" -> scrollbarSize;
                case "WindowRounding" -> windowRounding;
                case "FrameRounding" -> frameRounding;
                case "WindowBorderSize" -> windowBorderSize;
                case "FrameBorderSize" -> frameBorderSize;
                case "PopupRounding" -> popupRounding;
                case "PopupBorderSize" -> popupBorderSize;
                case "ChildRounding" -> childRounding;
                case "ChildBorderSize" -> childBorderSize;
                case "GrabMinSize" -> grabMinSize;
                case "GrabRounding" -> grabRounding;
                case "ScrollbarRounding" -> scrollbarRounding;
                case "DockingSeparatorSize" -> dockingSeparatorSize;
                case "TabRounding" -> tabRounding;
                case "TabBorderSize" -> tabBorderSize;
                case "WindowMinSize" -> new float[]{windowMinSizeX, windowMinSizeY};
                case "WindowTitleAlign" -> new float[]{0, 0.5f};
                case "ButtonTextAlign" -> new float[]{0.5f, 0.5f};
                case "SelectableTextAlign" -> new float[]{0, 0};
                case "SeparatorTextAlign" -> new float[]{0, 0.5f};
                case "SeparatorTextPadding" -> new float[]{20, 3};
                case "DisplayWindowPadding" -> new float[]{19, 19};
                case "DisplaySafeAreaPadding" -> new float[]{3, 3};
                default -> 0f;
            };
        }

        void setVar(String name, float[] value) {
            if (value.length >= 2) {
                switch (name) {
                    case "WindowPadding" -> { windowPaddingX = value[0]; windowPaddingY = value[1]; }
                    case "FramePadding" -> { framePaddingX = value[0]; framePaddingY = value[1]; }
                    case "ItemSpacing" -> { itemSpacingX = value[0]; itemSpacingY = value[1]; }
                    case "ItemInnerSpacing" -> { itemInnerSpacingX = value[0]; itemInnerSpacingY = value[1]; }
                    case "CellPadding" -> { cellPaddingX = value[0]; cellPaddingY = value[1]; }
                    case "WindowMinSize" -> { windowMinSizeX = value[0]; windowMinSizeY = value[1]; }
                    default -> { }
                }
            } else {
                switch (name) {
                    case "Alpha" -> alpha = value[0];
                    case "DisabledAlpha" -> disabledAlpha = value[0];
                    case "IndentSpacing" -> indentSpacing = value[0];
                    case "ScrollbarSize" -> scrollbarSize = value[0];
                    case "WindowRounding" -> windowRounding = value[0];
                    case "FrameRounding" -> frameRounding = value[0];
                    case "WindowBorderSize" -> windowBorderSize = value[0];
                    case "FrameBorderSize" -> frameBorderSize = value[0];
                    case "PopupBorderSize" -> popupBorderSize = value[0];
                    case "ChildBorderSize" -> childBorderSize = value[0];
                    case "PopupRounding" -> popupRounding = value[0];
                    case "ChildRounding" -> childRounding = value[0];
                    case "GrabRounding" -> grabRounding = value[0];
                    case "ScrollbarRounding" -> scrollbarRounding = value[0];
                    case "DockingSeparatorSize" -> dockingSeparatorSize = value[0];
                    case "TabRounding" -> tabRounding = value[0];
                    case "TabBorderSize" -> tabBorderSize = value[0];
                    default -> { }
                }
            }
        }
    }

    static final class Viewport {
        float x, y;
        float w = 1280, h = 720;
        float workX, workY;
        float workW = 1280, workH = 720;
        int id = 1;
        int flags;
    }

    static final class DrawList {
        final List<Vertex> vertices = new ArrayList<>();
        final List<Integer> indices = new ArrayList<>();
        final List<Cmd> commands = new ArrayList<>();
        final List<List<DrawList>> frameOwner = new ArrayList<>();
        float clipMinX = 0, clipMinY = 0, clipMaxX = 10000, clipMaxY = 10000;
        float textSize = 16f;
        final List<float[]> path = new ArrayList<>();
        long textureId = 0;
        final List<float[]> clipStack = new ArrayList<>();
        ByteBuffer vtxBuffer = ByteBuffer.allocateDirect(0);
        ByteBuffer idxBuffer = ByteBuffer.allocateDirect(0);
        int cmdStartIdx = 0;

        void addList(List<DrawList> list) {
            if (!frameOwner.contains(list)) {
                // This indirection is only used to make reset() safe when the
                // frame list is cleared. The list itself is owned by UiContext.
                frameOwner.add(list);
            }
        }

        void reset() {
            vertices.clear();
            indices.clear();
            commands.clear();
            clipStack.clear();
            clipMinX = 0; clipMinY = 0; clipMaxX = 10000; clipMaxY = 10000;
            textureId = 0;
            cmdStartIdx = 0;
        }

        void finish() {
            // Reuse the direct buffers: allocating new ones every frame leaks
            // native memory until the GC frees them (IMGUI sessions are long).
            int vtxBytes = vertices.size() * 20;
            if (vtxBuffer.capacity() < vtxBytes) {
                vtxBuffer = ByteBuffer.allocateDirect(Math.max(vtxBytes, vtxBuffer.capacity() * 2))
                    .order(ByteOrder.nativeOrder());
            }
            vtxBuffer.clear();
            for (Vertex v : vertices) {
                vtxBuffer.putFloat(v.x);
                vtxBuffer.putFloat(v.y);
                vtxBuffer.putFloat(v.u);
                vtxBuffer.putFloat(v.v);
                vtxBuffer.putInt(v.color);
            }
            vtxBuffer.flip();

            int idxBytes = indices.size() * 2;
            if (idxBuffer.capacity() < idxBytes) {
                idxBuffer = ByteBuffer.allocateDirect(Math.max(idxBytes, idxBuffer.capacity() * 2))
                    .order(ByteOrder.nativeOrder());
            }
            idxBuffer.clear();
            for (int index : indices) {
                idxBuffer.putShort((short) index);
            }
            idxBuffer.flip();
        }

        // Un-textured primitives must sample the atlas white pixel, not (0,0)
        // (which is transparent). Same contract as ImGui's TexUvWhitePixel.
        static boolean finite(float... values) {
            for (float v : values) if (!Float.isFinite(v)) return false;
            return true;
        }

        static final float WHITE_U = 0.5f / 2048f;
        static final float WHITE_V = 0.5f / 2048f;

        static float whiteU() {
            FontAtlas atlas = FontAtlas.ACTIVE.get();
            return 0.5f / (atlas == null || atlas.width <= 0 ? 2048f : atlas.width);
        }

        static float whiteV() {
            FontAtlas atlas = FontAtlas.ACTIVE.get();
            return 0.5f / (atlas == null || atlas.height <= 0 ? 2048f : atlas.height);
        }

        int addVertex(float x, float y, float u, float v, int color) {
            int index = vertices.size();
            vertices.add(new Vertex(x, y, u, v, color));
            return index;
        }

        void addTriangle(float x0, float y0, float x1, float y1, float x2, float y2, int color) {
            if (!finite(x0, y0, x1, y1, x2, y2)) return;
            beginCommand();
            int base = vertices.size();
            addVertex(x0, y0, whiteU(), whiteV(), color);
            addVertex(x1, y1, whiteU(), whiteV(), color);
            addVertex(x2, y2, whiteU(), whiteV(), color);
            indices.add(base);
            indices.add(base + 1);
            indices.add(base + 2);
            markCommand();
        }

        void addQuad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3,
                     float u0, float v0, float u1, float v1, int color) {
            if (!finite(x0, y0, x1, y1, x2, y2, x3, y3, u0, v0, u1, v1)) return;
            beginCommand();
            if (u0 == 0f && v0 == 0f && u1 == 0f && v1 == 0f) {
                u0 = u1 = whiteU();
                v0 = v1 = whiteV();
            }
            int base = vertices.size();
            addVertex(x0, y0, u0, v0, color);
            addVertex(x1, y1, u1, v0, color);
            addVertex(x2, y2, u1, v1, color);
            addVertex(x3, y3, u0, v1, color);
            indices.add(base); indices.add(base + 1); indices.add(base + 2);
            indices.add(base); indices.add(base + 2); indices.add(base + 3);
            markCommand();
        }

        void addRectFilled(float x0, float y0, float x1, float y1, int color) {
            addQuad(x0, y0, x1, y0, x1, y1, x0, y1, 0, 0, 0, 0, color);
        }

        void addRectFilled(float x0, float y0, float x1, float y1, int color, float rounding) {
            if (rounding <= 0.5f) {
                addRectFilled(x0, y0, x1, y1, color);
                return;
            }
            float r = Math.min(rounding, Math.min(x1 - x0, y1 - y0) * 0.5f);
            addRectFilled(x0 + r, y0, x1 - r, y1, color);
            addRectFilled(x0, y0 + r, x0 + r, y1 - r, color);
            addRectFilled(x1 - r, y0 + r, x1, y1 - r, color);
            addCircleFilled(x0 + r, y0 + r, r, color, 8);
            addCircleFilled(x1 - r, y0 + r, r, color, 8);
            addCircleFilled(x0 + r, y1 - r, r, color, 8);
            addCircleFilled(x1 - r, y1 - r, r, color, 8);
        }

        void addRect(float x0, float y0, float x1, float y1, int color, float rounding, float thickness) {
            float t = Math.max(1, thickness);
            if (rounding <= 0.5f) {
                addRectFilled(x0, y0, x1, y0 + t, color);
                addRectFilled(x0, y1 - t, x1, y1, color);
                addRectFilled(x0, y0, x0 + t, y1, color);
                addRectFilled(x1 - t, y0, x1, y1, color);
                return;
            }
            float r = Math.min(rounding, Math.min(x1 - x0, y1 - y0) * 0.5f);
            addRectFilled(x0 + r, y0, x1 - r, y0 + t, color);
            addRectFilled(x0 + r, y1 - t, x1 - r, y1, color);
            addRectFilled(x0, y0 + r, x0 + t, y1 - r, color);
            addRectFilled(x1 - t, y0 + r, x1, y1 - r, color);
            int seg = Math.max(4, (int) (r * 0.5f) + 4);
            addArcBorder(x0 + r, y0 + r, r, (float) Math.PI, (float) (Math.PI * 1.5f), color, t, seg);
            addArcBorder(x1 - r, y0 + r, r, (float) (Math.PI * 1.5f), (float) (Math.PI * 2), color, t, seg);
            addArcBorder(x1 - r, y1 - r, r, 0, (float) (Math.PI * 0.5f), color, t, seg);
            addArcBorder(x0 + r, y1 - r, r, (float) (Math.PI * 0.5f), (float) Math.PI, color, t, seg);
        }

        void addArcBorder(float cx, float cy, float radius, float a0, float a1, int color, float thickness, int segments) {
            int seg = Math.max(2, segments);
            for (int i = 0; i < seg; i++) {
                float s0 = a0 + (a1 - a0) * i / seg;
                float s1 = a0 + (a1 - a0) * (i + 1) / seg;
                addLine(cx + (float) Math.cos(s0) * radius, cy + (float) Math.sin(s0) * radius,
                    cx + (float) Math.cos(s1) * radius, cy + (float) Math.sin(s1) * radius, color, thickness);
            }
        }

        void addLine(float x0, float y0, float x1, float y1, int color, float thickness) {
            float dx = x1 - x0;
            float dy = y1 - y0;
            float len = (float) Math.sqrt(dx * dx + dy * dy);
            if (len < 0.0001f) return;
            float nx = -dy / len * thickness * 0.5f;
            float ny = dx / len * thickness * 0.5f;
            addQuad(x0 + nx, y0 + ny, x1 + nx, y1 + ny, x1 - nx, y1 - ny, x0 - nx, y0 - ny, 0, 0, 0, 0, color);
        }

        void addCircleFilled(float x, float y, float radius, int color, int segments) {
            if (!finite(x, y, radius)) return;
            beginCommand();
            int seg = Math.max(6, segments);
            float step = (float) (Math.PI * 2 / seg);
            int base = vertices.size();
            addVertex(x, y, whiteU(), whiteV(), color);
            for (int i = 0; i <= seg; i++) {
                float a = i * step;
                addVertex(x + (float) Math.cos(a) * radius, y + (float) Math.sin(a) * radius, whiteU(), whiteV(), color);
            }
            for (int i = 0; i < seg; i++) {
                indices.add(base);
                indices.add(base + 1 + i);
                indices.add(base + 2 + i);
            }
            markCommand();
        }

        void addCircle(float x, float y, float radius, int color, int segments, float thickness) {
            int seg = Math.max(6, segments);
            float step = (float) (Math.PI * 2 / seg);
            for (int i = 0; i < seg; i++) {
                float a0 = i * step;
                float a1 = (i + 1) * step;
                addLine(x + (float) Math.cos(a0) * radius, y + (float) Math.sin(a0) * radius,
                    x + (float) Math.cos(a1) * radius, y + (float) Math.sin(a1) * radius, color, thickness);
            }
        }

        void pathLineTo(float x, float y) {
            if (this.path.isEmpty()) {
                this.path.add(new float[]{x, y});
            } else {
                float[] last = this.path.get(this.path.size() - 1);
                if (last[0] != x || last[1] != y) this.path.add(new float[]{x, y});
            }
        }

        void pathArcTo(float cx, float cy, float radius, float a0, float a1, int segments) {
            int seg = Math.max(2, segments);
            for (int i = 0; i <= seg; i++) {
                float a = a0 + (a1 - a0) * i / seg;
                pathLineTo(cx + (float) Math.cos(a) * radius, cy + (float) Math.sin(a) * radius);
            }
        }

        void addConvexPolyFilled(List<float[]> points, int color) {
            if (points.size() < 3) return;
            beginCommand();
            int base = vertices.size();
            for (float[] pt : points) addVertex(pt[0], pt[1], whiteU(), whiteV(), color);
            for (int i = 1; i < points.size() - 1; i++) {
                indices.add(base);
                indices.add(base + i);
                indices.add(base + i + 1);
            }
            markCommand();
        }

        void addPolyline(List<float[]> points, int color, boolean closed, float thickness) {
            if (points.size() < 2) return;
            for (int i = 0; i < points.size() - 1; i++) {
                float[] a = points.get(i);
                float[] b = points.get(i + 1);
                addLine(a[0], a[1], b[0], b[1], color, thickness);
            }
            if (closed) {
                float[] a = points.get(points.size() - 1);
                float[] b = points.get(0);
                addLine(a[0], a[1], b[0], b[1], color, thickness);
            }
        }

        void addText(float x, float y, int color, String text) {
            addText(x, y, color, text, this.textSize > 0 ? this.textSize : 16f);
        }

        void addText(float x, float y, int color, String text, float size) {
            FontAtlas atlas = FontAtlas.ACTIVE.get();
            if (atlas == null) return;
            atlas.drawText(this, x, y, color, text, size);
        }

        void pushClip(float x0, float y0, float x1, float y1) {
            clipStack.add(new float[]{clipMinX, clipMinY, clipMaxX, clipMaxY});
            // PushClipRect(..., intersect_with_current=true)
            clipMinX = Math.max(clipMinX, x0);
            clipMinY = Math.max(clipMinY, y0);
            clipMaxX = Math.min(clipMaxX, x1);
            clipMaxY = Math.min(clipMaxY, y1);
            markCommand();
        }

        void popClip() {
            if (!clipStack.isEmpty()) {
                float[] c = clipStack.remove(clipStack.size() - 1);
                clipMinX = c[0];
                clipMinY = c[1];
                clipMaxX = c[2];
                clipMaxY = c[3];
                markCommand();
            }
        }

        void setTexture(long id) {
            if (id != textureId) {
                textureId = id;
                markCommand();
            }
        }

        /**
         * Start a primitive: create the command *before* its vertices/indices
         * are appended. Creating it afterwards (as the old code did) made the
         * renderer skip the primitive and reuse stale offsets, which produced
         * flickering/ghost geometry.
         */
        void beginCommand() {
            boolean needNew = commands.isEmpty();
            if (!needNew) {
                Cmd last = commands.get(commands.size() - 1);
                needNew = last.textureId != textureId
                    || last.clipMinX != clipMinX || last.clipMinY != clipMinY
                    || last.clipMaxX != clipMaxX || last.clipMaxY != clipMaxY;
            }
            if (needNew) {
                Cmd cmd = new Cmd();
                cmd.elemCount = 0;
                cmd.clipMinX = clipMinX;
                cmd.clipMinY = clipMinY;
                cmd.clipMaxX = clipMaxX;
                cmd.clipMaxY = clipMaxY;
                cmd.textureId = textureId;
                cmd.startIdx = indices.size();
                cmd.vtxOffset = vertices.size();
                cmd.idxOffset = indices.size();
                commands.add(cmd);
            }
        }

        void forceCommand() {
            Cmd cmd = new Cmd();
            cmd.elemCount = 0;
            cmd.clipMinX = clipMinX;
            cmd.clipMinY = clipMinY;
            cmd.clipMaxX = clipMaxX;
            cmd.clipMaxY = clipMaxY;
            cmd.textureId = textureId;
            cmd.startIdx = indices.size();
            cmd.vtxOffset = vertices.size();
            cmd.idxOffset = indices.size();
            commands.add(cmd);
        }

        void markCommand() {
            if (commands.isEmpty()) return;
            Cmd last = commands.get(commands.size() - 1);
            last.elemCount = indices.size() - last.startIdx;
        }
    }

    record Vertex(float x, float y, float u, float v, int color) {
    }

    static final class Cmd {
        int elemCount;
        float clipMinX, clipMinY, clipMaxX, clipMaxY;
        long textureId;
        int startIdx;
        int vtxOffset;
        int idxOffset;
    }

    static final class DrawData {
        List<DrawList> lists = new ArrayList<>();
        float displayW = 1280;
        float displayH = 720;
        float fbScaleX = 1;
        float fbScaleY = 1;
        boolean valid = true;
    }

    record GlyphEntry(GlyphData glyph, float u0, float v0, float u1, float v1, int pixelSize) {
    }

    static final class ClipperData {
        int count;
        float height = 16;
        int start;
        int end;
        int step;
    }

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

    static final class FontData {
        final int size;
        final TrueTypeFont ttf;
        final CffFont cff;
        final Map<Integer, GlyphEntry> glyphs = new HashMap<>();
        Object object;
        float lineHeight;
        float offsetX, offsetY;
        short[] ranges;
        final List<FontData> merged = new ArrayList<>();

        FontData(int size, Object object, byte[] bytes) {
            this.size = size;
            this.object = object;
            this.lineHeight = size;
            TrueTypeFont parsedTtf = bytes == null ? null : TrueTypeFont.parse(bytes);
            this.ttf = parsedTtf;
            this.cff = parsedTtf == null && bytes != null ? CffFont.parse(bytes) : null;
        }

        GlyphData glyph(int codepoint, int pixelSize) {
            if (this.ttf != null) return this.ttf.glyph(codepoint, pixelSize);
            if (this.cff != null) return this.cff.glyph(codepoint, pixelSize);
            return null;
        }
    }

    /**
     * Very small built-in font. It is deliberately simple: the goal is to keep
     * the UI usable without native libraries. A TrueType atlas loader can be
     * plugged in later without changing any mod code.
     */
    static final class FontAtlas {
        static final ThreadLocal<FontAtlas> ACTIVE = new ThreadLocal<>();
        final List<FontData> fonts = new ArrayList<>();
        FontData current;
        long texId;
        int width = 2048;
        int height = 2048;
        ByteBuffer pixels = ByteBuffer.allocateDirect(width * height * 4);
        boolean atlasBuilt;
        boolean uploaded;
        int missingGlyphCount;

        FontAtlas() {
            ACTIVE.set(this);
            // Transparent background: alpha 0 is what makes glyph quads
            // invisible outside the rasterized contours.
            for (int i = 0; i < this.pixels.capacity(); i++) {
                this.pixels.put(i, (byte) 0);
            }
            this.pixels.position(0);
            FontData fallback = new FontData(16, null, null);
            this.fonts.add(fallback);
            this.current = fallback;
        }

        FontData addFont(int size, Object object, byte[] bytes) {
            return addFont(size, object, bytes, null, null);
        }

        FontData addFont(int size, Object object, byte[] bytes, FontConfigData cfg, short[] ranges) {
            FontData font = new FontData(size, object, bytes);
            font.offsetX = cfg == null ? 0 : cfg.glyphOffsetX;
            font.offsetY = cfg == null ? 0 : cfg.glyphOffsetY;
            font.ranges = ranges != null ? ranges : (cfg == null ? null : cfg.glyphRanges);
            boolean noRealFontYet = this.current == null
                || (this.current.ttf == null && this.current.cff == null);
            this.fonts.add(font);
            if (noRealFontYet) {
                this.current = font;
            } else if (cfg != null && cfg.mergeMode) {
                this.current.merged.add(font);
            }
            // Once the backend has uploaded the texture, rebuilding the atlas
            // would invalidate every UV. Late fonts then use the on-demand
            // rasterizer instead of silently sampling a stale texture.
            if (!this.uploaded) this.atlasBuilt = false;
            ACTIVE.set(this);
            return font;
        }

        void clear() {
            this.fonts.clear();
            FontData fallback = new FontData(16, null, null);
            this.fonts.add(fallback);
            this.current = fallback;
            this.atlasBuilt = false;
            clearTexData();
        }

        void clearTexData() {
            for (int i = 0; i < this.pixels.capacity(); i++) this.pixels.put(i, (byte) 0);
            this.pixels.position(0);
        }

        Object currentFontObject() {
            return this.current == null ? null : this.current.object;
        }

        float measure(String text, float size) {
            if (text == null) return 0;
            if (this.current != null && (this.current.ttf != null || this.current.cff != null)) {
                float width = 0;
                for (int i = 0; i < text.length(); i++) {
                    char c = text.charAt(i);
                    GlyphData glyph = this.current.glyph(c, (int) size);
                    if (glyph == null) {
                        for (FontData merged : this.current.merged) {
                            glyph = merged.glyph(c, (int) size);
                            if (glyph != null) break;
                        }
                    }
                    if (glyph == null) {
                        for (FontData fallback : this.fonts) {
                            if (fallback == this.current) continue;
                            glyph = fallback.glyph(c, (int) size);
                            if (glyph != null) break;
                        }
                    }
                    width += glyph != null ? glyph.advance() : size * 0.55f;
                }
                return width;
            }
            return text.length() * size * 0.55f;
        }

        void ensureAtlas() {
            if (this.atlasBuilt) return;
            this.atlasBuilt = true;

            // Build the codepoint set per font: ASCII + configured glyph ranges
            // + the PUA blocks used by icon fonts. CJK ranges need a bigger
            // atlas, otherwise their glyphs would fall back to per-pixel quads.
            java.util.LinkedHashMap<FontData, java.util.LinkedHashSet<Integer>> work = new java.util.LinkedHashMap<>();
            int total = 0;
            for (FontData font : this.fonts) {
                if (font.ttf == null && font.cff == null) continue;
                java.util.LinkedHashSet<Integer> codepoints = new java.util.LinkedHashSet<>();
                for (int c = 32; c <= 126; c++) codepoints.add(c);
                if (font.ranges != null) {
                    // CJK ranges contain thousands of glyphs; baking them all
                    // costs tens of seconds. Keep the atlas small and let the
                    // renderer rasterize uncommon glyphs on demand.
                    int rangeCount = 0;
                    for (int i = 0; i + 1 < font.ranges.length; i += 2) {
                        int from = font.ranges[i] & 0xFFFF;
                        int to = font.ranges[i + 1] & 0xFFFF;
                        if (from == 0 && to == 0) break;
                        if (to >= from) rangeCount += to - from + 1;
                    }
                    if (rangeCount <= 1024) {
                        for (int i = 0; i + 1 < font.ranges.length; i += 2) {
                            int from = font.ranges[i] & 0xFFFF;
                            int to = font.ranges[i + 1] & 0xFFFF;
                            if (from == 0 && to == 0) break;
                            if (to < from) continue;
                            for (int c = from; c <= to && c <= 0xFFFF; c++) codepoints.add(c);
                        }
                    }
                }
                for (int c = 0xE000; c <= 0xE0FF; c++) codepoints.add(c);
                for (int c = 0xE900; c <= 0xE9FF; c++) codepoints.add(c);
                for (int c = 0xF000; c <= 0xF0FF; c++) codepoints.add(c);
                work.put(font, codepoints);
                total += codepoints.size();
            }

            int size = total > 6000 ? 4096 : 2048;
            this.width = size;
            this.height = size;
            int w = size;
            int h = size;
            ByteBuffer buffer = ByteBuffer.allocateDirect(w * h * 4);
            for (int i = 0; i < w * h; i++) {
                buffer.putInt(i * 4, 0);
            }
            buffer.putInt(0, 0xFFFFFFFF); // TexUvWhitePixel

            int penX = 1;
            int penY = 0;
            int rowHeight = 0;
            for (var entry : work.entrySet()) {
                FontData font = entry.getKey();
                for (int cp : entry.getValue()) {
                    GlyphData glyph = font.glyph(cp, font.size);
                    if (glyph == null || glyph.width() <= 0 || glyph.height() <= 0) continue;
                    if (penX + glyph.width() >= w) {
                        penX = 1;
                        penY += rowHeight + 1;
                        rowHeight = 0;
                    }
                    if (penY + glyph.height() >= h) break;
                    byte[] alpha = glyph.alpha();
                    for (int py = 0; py < glyph.height(); py++) {
                        for (int px = 0; px < glyph.width(); px++) {
                            int a = alpha[py * glyph.width() + px] & 0xFF;
                            if (a == 0) continue;
                            int idx = ((penY + py) * w + penX + px) * 4;
                            buffer.put(idx, (byte) 255);
                            buffer.put(idx + 1, (byte) 255);
                            buffer.put(idx + 2, (byte) 255);
                            buffer.put(idx + 3, (byte) a);
                        }
                    }
                    float u0 = penX / (float) w;
                    float v0 = penY / (float) h;
                    float u1 = (penX + glyph.width()) / (float) w;
                    float v1 = (penY + glyph.height()) / (float) h;
                    font.glyphs.put(cp, new GlyphEntry(glyph, u0, v0, u1, v1, font.size));
                    penX += glyph.width() + 1;
                    rowHeight = Math.max(rowHeight, glyph.height());
                }
            }
            this.pixels = buffer;
        }

        void drawText(DrawList list, float x, float y, int color, String text, float size) {
            if (text == null) return;
            float cx = x;
            float scale = size / 8f;
            for (int i = 0; i < text.length(); i++) {
                char c = text.charAt(i);
                if (c == '\n') {
                    cx = x;
                    y += size + 2;
                    continue;
                }
                if (this.current != null && (this.current.ttf != null || this.current.cff != null)) {
                    GlyphEntry entry = this.texId != 0 ? this.current.glyphs.get((int) c) : null;
                    if (entry != null && Math.abs(entry.pixelSize() - size) > 0.75f) entry = null;
                    GlyphData g = entry != null ? entry.glyph : this.current.glyph(c, (int) size);
                    if (g == null) {
                        for (FontData fallback : this.current.merged) {
                            if (this.texId != 0) {
                                entry = fallback.glyphs.get((int) c);
                                if (entry != null && Math.abs(entry.pixelSize() - size) > 0.75f) entry = null;
                            }
                            g = entry != null ? entry.glyph : fallback.glyph(c, (int) size);
                            if (g != null) break;
                        }
                    }
                    if (g == null) {
                        for (FontData fallback : this.fonts) {
                            if (fallback == this.current) continue;
                            if (this.texId != 0) {
                                entry = fallback.glyphs.get((int) c);
                                if (entry != null && Math.abs(entry.pixelSize() - size) > 0.75f) entry = null;
                            }
                            g = entry != null ? entry.glyph : fallback.glyph(c, (int) size);
                            if (g != null) break;
                        }
                    }
                    if (Boolean.getBoolean("noimgui.debug.glyphs") && c >= 0xE000
                        && this.missingGlyphCount++ < 300) {
                        int alphaSum = 0;
                        if (g != null && g.alpha() != null) {
                            for (byte b : g.alpha()) alphaSum += b & 0xFF;
                        }
                        NoNativeMod.LOGGER.info("ICON U+{} glyph={} size={}x{} alphaSum={} entry={} font={}",
                            String.format("%04X", (int) c), g != null,
                            g == null ? -1 : g.width(), g == null ? -1 : g.height(), alphaSum,
                            entry != null, this.current == null ? -1 : this.current.size);
                    }
                    if (g != null) {
                        float baseline = y + size * 0.8f;
                        float gx = cx + g.bearingX();
                        float gy = baseline - g.bearingY();
                        if (entry != null) {
                            list.addQuad(gx, gy, gx + g.width(), gy, gx + g.width(), gy + g.height(), gx, gy + g.height(),
                                entry.u0, entry.v0, entry.u1, entry.v1, color);
                        } else {
                            int alpha = (color >>> 24) & 0xFF;
                            for (int py = 0; py < g.height(); py++) {
                                for (int px = 0; px < g.width(); px++) {
                                    int a = g.alpha()[py * g.width() + px] & 0xFF;
                                    if (a == 0) continue;
                                    int c2 = (color & 0xFFFFFF) | (((alpha * a) / 255) << 24);
                                    list.addRectFilled(gx + px, gy + py, gx + px + 1, gy + py + 1, c2);
                                }
                            }
                        }
                        float adv = g.advance();
                        cx += Float.isFinite(adv) ? adv : size * 0.55f;
                        continue;
                    }
                }
                if (Boolean.getBoolean("noimgui.debug.glyphs")
                    && this.missingGlyphCount++ < 200) {
                    NoNativeMod.LOGGER.info("MISSING GLYPH U+{} in '{}' (font {})",
                        String.format("%04X", (int) c), text,
                        this.current == null ? "null" : this.current.size);
                }
                String[] rows = glyph(c);
                if (rows == null) {
                    list.addRectFilled(cx, y + 2, cx + size * 0.5f, y + size - 2, color);
                    cx += size * 0.6f;
                    continue;
                }
                for (int row = 0; row < 7; row++) {
                    String bits = rows[row];
                    for (int col = 0; col < 5; col++) {
                        if (bits.charAt(col) == '1') {
                            float px = cx + col * scale;
                            float py = y + row * scale;
                            list.addRectFilled(px, py, px + scale, py + scale, color);
                        }
                    }
                }
                cx += 6 * scale;
            }
        }

        private static String[] glyph(char c) {
            if (c >= 'a' && c <= 'z') {
                c = (char) (c - 32);
            }
            return switch (c) {
                case ' ' -> new String[]{"00000","00000","00000","00000","00000","00000","00000"};
                case '0' -> new String[]{"01110","10001","10011","10101","11001","10001","01110"};
                case '1' -> new String[]{"00100","01100","00100","00100","00100","00100","01110"};
                case '2' -> new String[]{"01110","10001","00001","00010","00100","01000","11111"};
                case '3' -> new String[]{"11111","00010","00100","00010","00001","10001","01110"};
                case '4' -> new String[]{"00010","00110","01010","10010","11111","00010","00010"};
                case '5' -> new String[]{"11111","10000","11110","00001","00001","10001","01110"};
                case '6' -> new String[]{"00110","01000","10000","11110","10001","10001","01110"};
                case '7' -> new String[]{"11111","00001","00010","00100","01000","01000","01000"};
                case '8' -> new String[]{"01110","10001","10001","01110","10001","10001","01110"};
                case '9' -> new String[]{"01110","10001","10001","01111","00001","00010","01100"};
                case 'A' -> new String[]{"01110","10001","10001","11111","10001","10001","10001"};
                case 'B' -> new String[]{"11110","10001","10001","11110","10001","10001","11110"};
                case 'C' -> new String[]{"01110","10001","10000","10000","10000","10001","01110"};
                case 'D' -> new String[]{"11100","10010","10001","10001","10001","10010","11100"};
                case 'E' -> new String[]{"11111","10000","10000","11110","10000","10000","11111"};
                case 'F' -> new String[]{"11111","10000","10000","11110","10000","10000","10000"};
                case 'G' -> new String[]{"01110","10001","10000","10111","10001","10001","01111"};
                case 'H' -> new String[]{"10001","10001","10001","11111","10001","10001","10001"};
                case 'I' -> new String[]{"01110","00100","00100","00100","00100","00100","01110"};
                case 'J' -> new String[]{"00111","00010","00010","00010","00010","10010","01100"};
                case 'K' -> new String[]{"10001","10010","10100","11000","10100","10010","10001"};
                case 'L' -> new String[]{"10000","10000","10000","10000","10000","10000","11111"};
                case 'M' -> new String[]{"10001","11011","10101","10101","10001","10001","10001"};
                case 'N' -> new String[]{"10001","11001","10101","10011","10001","10001","10001"};
                case 'O' -> new String[]{"01110","10001","10001","10001","10001","10001","01110"};
                case 'P' -> new String[]{"11110","10001","10001","11110","10000","10000","10000"};
                case 'Q' -> new String[]{"01110","10001","10001","10001","10101","10010","01101"};
                case 'R' -> new String[]{"11110","10001","10001","11110","10100","10010","10001"};
                case 'S' -> new String[]{"01111","10000","10000","01110","00001","00001","11110"};
                case 'T' -> new String[]{"11111","00100","00100","00100","00100","00100","00100"};
                case 'U' -> new String[]{"10001","10001","10001","10001","10001","10001","01110"};
                case 'V' -> new String[]{"10001","10001","10001","10001","10001","01010","00100"};
                case 'W' -> new String[]{"10001","10001","10001","10101","10101","10101","01010"};
                case 'X' -> new String[]{"10001","10001","01010","00100","01010","10001","10001"};
                case 'Y' -> new String[]{"10001","10001","01010","00100","00100","00100","00100"};
                case 'Z' -> new String[]{"11111","00001","00010","00100","01000","10000","11111"};
                case '.' -> new String[]{"00000","00000","00000","00000","00000","00110","00110"};
                case ',' -> new String[]{"00000","00000","00000","00000","00110","00110","00100"};
                case ':' -> new String[]{"00000","00110","00110","00000","00110","00110","00000"};
                case ';' -> new String[]{"00000","00110","00110","00000","00110","00110","00100"};
                case '!' -> new String[]{"00100","00100","00100","00100","00100","00000","00100"};
                case '?' -> new String[]{"01110","10001","00001","00010","00100","00000","00100"};
                case '-' -> new String[]{"00000","00000","00000","11111","00000","00000","00000"};
                case '_' -> new String[]{"00000","00000","00000","00000","00000","00000","11111"};
                case '+' -> new String[]{"00000","00100","00100","11111","00100","00100","00000"};
                case '=' -> new String[]{"00000","00000","11111","00000","11111","00000","00000"};
                case '/' -> new String[]{"00001","00010","00010","00100","01000","01000","10000"};
                case '\\' -> new String[]{"10000","01000","01000","00100","00010","00010","00001"};
                case '(' -> new String[]{"00010","00100","01000","01000","01000","00100","00010"};
                case ')' -> new String[]{"01000","00100","00010","00010","00010","00100","01000"};
                case '[' -> new String[]{"01110","01000","01000","01000","01000","01000","01110"};
                case ']' -> new String[]{"01110","00010","00010","00010","00010","00010","01110"};
                case '<' -> new String[]{"00010","00100","01000","10000","01000","00100","00010"};
                case '>' -> new String[]{"01000","00100","00010","00001","00010","00100","01000"};
                case '|' -> new String[]{"00100","00100","00100","00100","00100","00100","00100"};
                case '#' -> new String[]{"01010","01010","11111","01010","11111","01010","01010"};
                case '%' -> new String[]{"11001","11010","00010","00100","01000","01011","10011"};
                case '&' -> new String[]{"01100","10010","10100","01000","10101","10010","01101"};
                case '*' -> new String[]{"00000","10101","01110","11111","01110","10101","00000"};
                case '@' -> new String[]{"01110","10001","10111","10101","10111","10000","01110"};
                case '\'' -> new String[]{"00100","00100","00000","00000","00000","00000","00000"};
                case '"' -> new String[]{"01010","01010","00000","00000","00000","00000","00000"};
                case '`' -> new String[]{"01000","00100","00000","00000","00000","00000","00000"};
                case '~' -> new String[]{"00000","00000","01001","10110","00000","00000","00000"};
                case '^' -> new String[]{"00100","01010","10001","00000","00000","00000","00000"};
                default -> null;
            };
        }

        // 5x7 bitmap data for ASCII 32..126. Rows are stored in the low 7 bits.
        private static final int[] FONT5X7 = buildFont();

        private static int[] buildFont() {
            int[] data = new int[(127 - 32) * 5];
            // The font is intentionally rough, but every printable character
            // gets a stable bitmap. Selecting 0x1F for all glyphs gives a
            // readable block font instead of invisible text.
            for (int i = 0; i < data.length; i++) {
                data[i] = 0x1F;
            }
            return data;
        }
    }

    static final class Window {
        final String name;
        float x, y, w, h;
        float cursorX, cursorY;
        float lineStartX;
        float tableItemWidth;
        float workMinX, workMaxX, workMinY, workMaxY;
        float prevLineX, prevLineY;
        float currLineSizeY, prevLineSizeY;
        boolean isSameLine;
        float contentX, contentY, contentW, contentH;
        float lineX, lineY, lineHeight;
        float lastItemRight;
        float contentHeight;
        float contentMaxX, contentMaxY;
        float titleH;
        boolean scrollbarY;
        int clipCount;
        float scrollX, scrollMaxX;
        float scrollY;
        float scrollMaxY;
        float maxContentX;
        boolean scrollbarDragging;
        float scrollbarDragStartY;
        float scrollbarDragStartScroll;
        long order;
        Object openState;
        boolean skipDraw;
        boolean resizing;
        boolean dragging;
        float pivotAnchorX = Float.NaN, pivotAnchorY;
        float appliedPivotX, appliedPivotY;
        float resizeStartMouseX, resizeStartMouseY;
        float resizeStartW, resizeStartH;
        int flags;
        int dockId;
        boolean hovered;
        boolean collapsed;
        boolean appearing;
        int lastSeenFrame = -1000;
        boolean firstFrame = true;
        boolean menuBar;
        boolean mainDocked;
        boolean dockAssigned;
        boolean childWindow;
        final List<Window> childWindows = new ArrayList<>();
        boolean posCondApplied;
        boolean sizeCondApplied;
        DockNode dockNode;
        float dockTabHeight;
        float menuBarHeight;
        float dragX, dragY;
        final DrawList drawList = new DrawList();
        Object drawListObject;
        final List<float[]> groupStack = new ArrayList<>();
        Table table;
        boolean tabBar;
        float tabBarY;
        float tabX;
        String activeTab;

        Window(String name, float x, float y, float w, float h) {
            this.name = name;
            this.x = x;
            this.y = y;
            this.w = w;
            this.h = h;
        }
    }

    static final class Table {
        final List<Column> columns = new ArrayList<>();
        TableLayout layout;
        int column;
        int currentColumn = -1;
        int setupIndex;
        float startX;
        float startY;
        float rowStart;
        float rowHeight;
        float columnWidth;
        boolean rowStarted;
        boolean cellActive;
        int sortColumn = -1;
        int sortDirection;
        int sortUserData;
        boolean specsDirty;
        String id;
        float y;

        Table(int columns) {
        }
    }

    record Column(String label, float width, int userData) {
    }

    private static final int[] CRC32_TABLE = new int[256];
    static {
        for (int n = 0; n < 256; n++) {
            int c = n;
            for (int k = 0; k < 8; k++) {
                c = (c & 1) != 0 ? (c >>> 1) ^ 0xEDB88320 : c >>> 1;
            }
            CRC32_TABLE[n] = c;
        }
    }

    static final class TextEditorData {
        String text = "";
        int tabSize = 4;
        boolean readOnly;
        boolean autoIndent = true;
        boolean showWhitespaces;
        boolean showSpaces;
        boolean showTabs;
        boolean showLineNumbers = true;
        boolean selection;
        String languageName = "";
        int cursorLine;
        int cursorColumn;
        final List<int[]> markers = new ArrayList<>();
    }

    static final class DockNode {
        final int id;
        final int parent;
        final List<Integer> children = new ArrayList<>();
        float x, y, w, h;
        float rx, ry, rw, rh;
        char split = 'X';
        int selected;
        String selectedName;
        boolean central;

        DockNode(int id, int parent) {
            this.id = id;
            this.parent = parent;
        }
    }

    static final class Popup {
        boolean open;
        boolean modal;
        boolean rendered;
        float x;
        float y;
    }
}
