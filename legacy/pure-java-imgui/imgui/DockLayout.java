package com.noimgui.imgui;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Standalone, pure-Java port of the layout math used by Dear ImGui docking.
 *
 * <p>The implementation follows {@code DockNodeTreeUpdatePosSize()},
 * {@code DockNodeTreeUpdateSplitter()} (only the position/size part), the
 * {@code SizeRef} ratio rules and {@code DockNodeCalcTabBarLayout()} from
 * {@code imgui.cpp}. It reads and writes the {@code [Docking][Data]} lines of
 * an {@code imgui.ini} file and deliberately has no dependency on the rest of
 * the no-imgui runtime, so it can be adopted by {@code PureUi} incrementally.</p>
 *
 * <p>Coordinates in the parsed ini are the saved logical coordinates. Call
 * {@link #layout(float, float, float, float)} to apply the tree to another
 * rectangle (for example the current display size).</p>
 */
public final class DockLayout {

    public static final int AXIS_X = 0;
    public static final int AXIS_Y = 1;

    /** Split axis of a dock node. */
    public enum Split {
        NONE,
        X,
        Y;

        public int axis() {
            return this == Y ? AXIS_Y : AXIS_X;
        }

        public boolean isHorizontal() {
            return this == X;
        }
    }

    /** Immutable rectangle used for node, tab bar, content and splitter rects. */
    public static final class Rect {
        private final float x;
        private final float y;
        private final float w;
        private final float h;

        public Rect(float x, float y, float w, float h) {
            this.x = x;
            this.y = y;
            this.w = w;
            this.h = h;
        }

        public float x() {
            return this.x;
        }

        public float y() {
            return this.y;
        }

        public float width() {
            return this.w;
        }

        public float height() {
            return this.h;
        }

        public float right() {
            return this.x + this.w;
        }

        public float bottom() {
            return this.y + this.h;
        }

        public boolean contains(float px, float py) {
            // ImRect::Contains() uses an inclusive minimum and exclusive maximum.
            return px >= this.x && py >= this.y && px < this.x + this.w && py < this.y + this.h;
        }

        @Override
        public String toString() {
            return String.format(Locale.ROOT, "Rect(%.1f, %.1f, %.1f, %.1f)", this.x, this.y, this.w, this.h);
        }
    }

    /** A dock node. Child order matches ImGuiDockNode::ChildNodes[0/1]. */
    public static final class Node {
        private final int id;
        private final int parentId;
        private final int parentWindowId;
        private final Split split;
        private final boolean dockSpace;
        private final boolean centralNode;
        private final boolean noResize;
        private final boolean noTabBar;
        private final boolean hiddenTabBar;
        private final boolean noWindowMenuButton;
        private final boolean noCloseButton;
        private final int selectedTabId;
        private final List<Node> children = new ArrayList<>(2);
        private final List<Node> childrenView = Collections.unmodifiableList(this.children);

        private Node parent;
        private float sizeRefX;
        private float sizeRefY;
        private boolean hasCentralNodeChild;
        private boolean visible;
        private boolean wantLockSizeOnce;
        private int windowCount;

        private float x;
        private float y;
        private float w;
        private float h;

        private Node(Raw raw) {
            this.id = raw.id;
            this.parentId = raw.parentId;
            this.parentWindowId = raw.parentWindowId;
            this.split = raw.split;
            this.dockSpace = raw.dockSpace;
            this.centralNode = raw.centralNode;
            this.noResize = raw.noResize;
            this.noTabBar = raw.noTabBar;
            this.hiddenTabBar = raw.hiddenTabBar;
            this.noWindowMenuButton = raw.noWindowMenuButton;
            this.noCloseButton = raw.noCloseButton;
            this.selectedTabId = raw.selectedTabId;
            this.sizeRefX = raw.sizeRefX;
            this.sizeRefY = raw.sizeRefY;
            this.x = raw.posX;
            this.y = raw.posY;
            this.w = raw.sizeX;
            this.h = raw.sizeY;
        }

        public int id() {
            return this.id;
        }

        public int parentId() {
            return this.parentId;
        }

        public Node parent() {
            return this.parent;
        }

        public List<Node> children() {
            return this.childrenView;
        }

        public Node child(int index) {
            return index >= 0 && index < this.children.size() ? this.children.get(index) : null;
        }

        public boolean isLeaf() {
            return this.children.isEmpty();
        }

        public Split split() {
            return this.split;
        }

        public float sizeRefX() {
            return this.sizeRefX;
        }

        public float sizeRefY() {
            return this.sizeRefY;
        }

        public float sizeRef(int axis) {
            return axis == AXIS_Y ? this.sizeRefY : this.sizeRefX;
        }

        public Rect rect() {
            return new Rect(this.x, this.y, this.w, this.h);
        }

        public float x() {
            return this.x;
        }

        public float y() {
            return this.y;
        }

        public float width() {
            return this.w;
        }

        public float height() {
            return this.h;
        }

        public float position(int axis) {
            return axis == AXIS_Y ? this.y : this.x;
        }

        public float size(int axis) {
            return axis == AXIS_Y ? this.h : this.w;
        }

        public boolean visible() {
            return this.visible;
        }

        public boolean isDockSpace() {
            return this.dockSpace;
        }

        public boolean isCentralNode() {
            return this.centralNode;
        }

        public boolean hasCentralNodeChild() {
            return this.hasCentralNodeChild;
        }

        public boolean noResize() {
            return this.noResize;
        }

        public boolean noTabBar() {
            return this.noTabBar;
        }

        public boolean hiddenTabBar() {
            return this.hiddenTabBar;
        }

        public boolean noWindowMenuButton() {
            return this.noWindowMenuButton;
        }

        public boolean noCloseButton() {
            return this.noCloseButton;
        }

        public int selectedTabId() {
            return this.selectedTabId;
        }

        public int windowCount() {
            return this.windowCount;
        }

        public boolean hasWindows() {
            return this.windowCount > 0 || this.selectedTabId != 0;
        }

        @Override
        public String toString() {
            return String.format(Locale.ROOT, "DockNode[0x%08X %s]", this.id, this.rect());
        }
    }

    private static final class Raw {
        int id;
        int parentId;
        int parentWindowId;
        int selectedTabId;
        float posX;
        float posY;
        float sizeX;
        float sizeY;
        float sizeRefX;
        float sizeRefY;
        Split split = Split.NONE;
        boolean dockSpace;
        boolean centralNode;
        boolean noResize;
        boolean noTabBar;
        boolean hiddenTabBar;
        boolean noWindowMenuButton;
        boolean noCloseButton;
    }

    private final LinkedHashMap<Integer, Node> nodes = new LinkedHashMap<>();
    private final List<Node> roots = new ArrayList<>();
    private final List<Node> rootsView = Collections.unmodifiableList(this.roots);
    private final List<Raw> rawNodes = new ArrayList<>();
    private final Map<Integer, Integer> windowCounts = new HashMap<>();

    // Defaults mirror the style values used by PureUi (fontSize 16, FramePadding.y 4,
    // WindowBorderSize 1, FramePadding.x 6, ItemInnerSpacing.x 4, DockingSeparatorSize 2).
    private float dockingSeparatorSize = 2.0f;
    private float windowMinSizeX = 32.0f;
    private float windowMinSizeY = 32.0f;
    private float fontSize = 16.0f;
    private float framePaddingX = 6.0f;
    private float framePaddingY = 4.0f;
    private float itemInnerSpacingX = 4.0f;
    private float windowBorderSize = 1.0f;
    private boolean dockingNodeHasCloseButton = true;
    private boolean windowMenuButtonLeft = true;

    private Node primaryRoot;

    private DockLayout() {
    }

    /**
     * Parse the docking section of an {@code imgui.ini} file and immediately run
     * the layout using the saved root {@code Pos}/{@code Size}.
     */
    public static DockLayout parseIni(Path path) throws IOException {
        return parseText(Files.readString(path, StandardCharsets.UTF_8));
    }

    /** Parse the docking section from an in-memory ini document. */
    public static DockLayout parseText(String text) {
        DockLayout layout = new DockLayout();
        layout.read(text);
        layout.build();
        layout.layout();
        return layout;
    }

    /** Alias for {@link #parseText(String)}. */
    public static DockLayout parse(String text) {
        return parseText(text);
    }

    // ------------------------------------------------------------------
    // Configuration
    // ------------------------------------------------------------------

    public float dockingSeparatorSize() {
        return this.dockingSeparatorSize;
    }

    /** Alias for {@link #dockingSeparatorSize()}. */
    public float separatorThickness() {
        return this.dockingSeparatorSize;
    }

    public void setDockingSeparatorSize(float size) {
        this.dockingSeparatorSize = Math.max(0.0f, size);
    }

    public void setWindowMinSize(float x, float y) {
        this.windowMinSizeX = Math.max(1.0f, x);
        this.windowMinSizeY = Math.max(1.0f, y);
    }

    public float windowMinSize(int axis) {
        return axis == AXIS_Y ? this.windowMinSizeY : this.windowMinSizeX;
    }

    public float tabBarHeight() {
        return this.fontSize + this.framePaddingY * 2.0f;
    }

    public void setTabBarHeight(float height) {
        // TabBarHeight == FontSize + FramePadding.y * 2 in DockNodeCalcTabBarLayout().
        this.fontSize = Math.max(0.0f, height - this.framePaddingY * 2.0f);
    }

    public void setFramePadding(float x, float y) {
        this.framePaddingX = Math.max(0.0f, x);
        this.framePaddingY = Math.max(0.0f, y);
    }

    public void setWindowBorderSize(float size) {
        this.windowBorderSize = Math.max(0.0f, size);
    }

    public void setItemInnerSpacingX(float spacing) {
        this.itemInnerSpacingX = Math.max(0.0f, spacing);
    }

    public void setDockingNodeHasCloseButton(boolean value) {
        this.dockingNodeHasCloseButton = value;
    }

    public void setWindowMenuButtonLeft(boolean value) {
        this.windowMenuButtonLeft = value;
    }

    // ------------------------------------------------------------------
    // Tree access
    // ------------------------------------------------------------------

    public List<Node> roots() {
        return this.rootsView;
    }

    public Node root() {
        return this.primaryRoot;
    }

    public Node node(int nodeId) {
        return this.nodes.get(nodeId);
    }

    public Iterable<Node> nodes() {
        return this.nodes.values();
    }

    /** Returns the node rect, or {@code null} if the id is unknown. */
    public Rect rect(int nodeId) {
        Node node = this.nodes.get(nodeId);
        return node == null ? null : node.rect();
    }

    public boolean hasTabBar(int nodeId) {
        Node node = this.nodes.get(nodeId);
        if (node == null || !node.isLeaf()) {
            return false;
        }
        return node.hasWindows() && !node.noTabBar && !node.hiddenTabBar;
    }

    /**
     * Rect occupied by a leaf node's tab bar, following
     * {@code DockNodeCalcTabBarLayout()}. Returns {@code null} when the node has
     * no visible tab bar.
     */
    public Rect tabBarRect(int nodeId) {
        Node node = this.nodes.get(nodeId);
        if (node == null || !hasTabBar(nodeId)) {
            return null;
        }

        final float tabBarHeight = tabBarHeight();
        float left = node.x + this.windowBorderSize + this.framePaddingX;
        float right = node.x + node.w - this.windowBorderSize - this.framePaddingX;
        final float buttonSize = this.fontSize;

        final boolean hasWindowMenuButton = !node.noWindowMenuButton;
        final boolean hasCloseButton = this.dockingNodeHasCloseButton && !node.noCloseButton;

        if (hasCloseButton) {
            right -= buttonSize + this.itemInnerSpacingX;
        }
        if (hasWindowMenuButton) {
            if (this.windowMenuButtonLeft) {
                left += buttonSize + this.itemInnerSpacingX;
            } else {
                right -= buttonSize + this.itemInnerSpacingX;
            }
        }

        return new Rect(left, node.y, Math.max(0.0f, right - left), tabBarHeight);
    }

    /**
     * Area left for the selected docked window. The tab bar overlays the node in
     * Dear ImGui; this helper returns the remaining content rect.
     */
    public Rect contentRect(int nodeId) {
        Node node = this.nodes.get(nodeId);
        if (node == null) {
            return null;
        }
        if (!hasTabBar(nodeId)) {
            return node.rect();
        }
        final float tabBarHeight = tabBarHeight();
        return new Rect(node.x, node.y + tabBarHeight, node.w, Math.max(0.0f, node.h - tabBarHeight));
    }

    /**
     * The splitter rectangle between the two children, matching the bounding box
     * built by {@code DockNodeTreeUpdateSplitter()}. Returns {@code null} for a
     * leaf node.
     */
    public Rect splitterRect(int nodeId) {
        Node node = this.nodes.get(nodeId);
        if (node == null || node.children.size() < 2) {
            return null;
        }
        Node child0 = node.children.get(0);
        Node child1 = node.children.get(1);
        if (node.split == Split.Y) {
            final float minX = child0.x;
            final float minY = child0.y + child0.h;
            final float maxX = child1.x + child1.w;
            final float maxY = child1.y;
            return new Rect(minX, minY, Math.max(0.0f, maxX - minX), Math.max(0.0f, maxY - minY));
        }
        final float minX = child0.x + child0.w;
        final float minY = child0.y;
        final float maxX = child1.x;
        final float maxY = child1.y + child1.h;
        return new Rect(minX, minY, Math.max(0.0f, maxX - minX), Math.max(0.0f, maxY - minY));
    }

    /** Deepest visible node containing the point, or 0 when none does. */
    public int nodeAt(float x, float y) {
        for (Node root : this.roots) {
            Node hit = findNodeAt(root, x, y);
            if (hit != null) {
                return hit.id;
            }
        }
        return 0;
    }

    // ------------------------------------------------------------------
    // Layout
    // ------------------------------------------------------------------

    /** Lay out every parsed root at its saved position and size. */
    public void layout() {
        for (Node root : this.roots) {
            updatePosSize(root, root.x, root.y, root.w, root.h);
        }
    }

    /** Lay out the primary root into the supplied rectangle. */
    public void layout(float x, float y, float width, float height) {
        if (this.primaryRoot == null) {
            return;
        }
        updatePosSize(this.primaryRoot, x, y, Math.max(0.0f, width), Math.max(0.0f, height));
    }

    public void layout(Rect rect) {
        if (rect != null) {
            layout(rect.x, rect.y, rect.w, rect.h);
        }
    }

    /**
     * Port of {@code DockNodeTreeUpdatePosSize()}. The visibility test mirrors
     * the visibility flag computed by {@code DockNodeUpdateVisibleFlag()} from
     * restored settings.
     */
    private void updatePosSize(Node node, float posX, float posY, float sizeX, float sizeY) {
        node.x = posX;
        node.y = posY;
        node.w = sizeX;
        node.h = sizeY;

        if (node.isLeaf()) {
            return;
        }

        Node child0 = node.children.get(0);
        Node child1 = node.children.size() > 1 ? node.children.get(1) : null;
        float child0X = posX;
        float child0Y = posY;
        float child1X = posX;
        float child1Y = posY;
        float child0W = sizeX;
        float child0H = sizeY;
        float child1W = sizeX;
        float child1H = sizeY;

        if (child1 != null && child0.visible && child1.visible) {
            final float spacing = this.dockingSeparatorSize;
            final int axis = node.split.axis();
            final float sizeAvail = Math.max(node.size(axis) - spacing, 0.0f);
            final float sizeMinEach = trunc(Math.min(sizeAvail, windowMinSize(axis) * 2.0f) * 0.5f);

            // 2) Preserve a locked absolute size during a splitter resize.
            if (child0.wantLockSizeOnce && !child1.wantLockSizeOnce) {
                setAxisLockedSize(child0, axis, Math.min(sizeAvail - 1.0f, child0.size(axis)));
                setAxisLockedSize(child1, axis, sizeAvail - child0.size(axis));
            } else if (child1.wantLockSizeOnce && !child0.wantLockSizeOnce) {
                setAxisLockedSize(child1, axis, Math.min(sizeAvail - 1.0f, child1.size(axis)));
                setAxisLockedSize(child0, axis, sizeAvail - child1.size(axis));
            } else if (child0.wantLockSizeOnce && child1.wantLockSizeOnce) {
                final float sum = child0.size(axis) + child1.size(axis);
                final float splitRatio = sum != 0.0f ? child0.size(axis) / sum : 0.5f;
                setAxisLockedSize(child0, axis, trunc(sizeAvail * splitRatio));
                setAxisLockedSize(child1, axis, sizeAvail - child0.size(axis));
            }
            // 3) A central node takes the remaining space; the other side is explicit.
            //    Note: like the reference, these branches only write Size, not SizeRef.
            else if (child0.sizeRef(axis) != 0.0f && child1.hasCentralNodeChild) {
                setAxisSize(child0, axis, Math.min(sizeAvail - sizeMinEach, child0.sizeRef(axis)));
                setAxisSize(child1, axis, sizeAvail - child0.size(axis));
            } else if (child1.sizeRef(axis) != 0.0f && child0.hasCentralNodeChild) {
                setAxisSize(child1, axis, Math.min(sizeAvail - sizeMinEach, child1.sizeRef(axis)));
                setAxisSize(child0, axis, sizeAvail - child1.size(axis));
            } else {
                // 4) Distribute according to the relative SizeRef ratio.
                final float ref0 = child0.sizeRef(axis);
                final float ref1 = child1.sizeRef(axis);
                final float refSum = ref0 + ref1;
                final float splitRatio = refSum != 0.0f ? ref0 / refSum : 0.5f;
                setAxisSize(child0, axis, Math.max(sizeMinEach, trunc(sizeAvail * splitRatio + 0.5f)));
                setAxisSize(child1, axis, sizeAvail - child0.size(axis));
            }

            if (axis == AXIS_X) {
                child0W = child0.w;
                child1W = child1.w;
                child1X += spacing + child0.w;
            } else {
                child0H = child0.h;
                child1H = child1.h;
                child1Y += spacing + child0.h;
            }
        }

        child0.wantLockSizeOnce = false;
        if (child1 != null) {
            child1.wantLockSizeOnce = false;
        }

        if (child0.visible) {
            updatePosSize(child0, child0X, child0Y, child0W, child0H);
        }
        if (child1 != null && child1.visible) {
            updatePosSize(child1, child1X, child1Y, child1W, child1H);
        }
    }

    private static void setAxisSize(Node node, int axis, float value) {
        final float size = Math.max(0.0f, value);
        if (axis == AXIS_Y) {
            node.h = size;
        } else {
            node.w = size;
        }
    }

    private static void setAxisLockedSize(Node node, int axis, float value) {
        final float size = Math.max(0.0f, value);
        if (axis == AXIS_Y) {
            node.sizeRefY = size;
            node.h = size;
        } else {
            node.sizeRefX = size;
            node.w = size;
        }
    }

    /**
     * Move the splitter of {@code nodeId} by {@code delta} pixels. A positive
     * delta grows child {@code childIndex} (0 or 1). The limits follow
     * {@code DockNodeTreeUpdateSplitter()}: {@code WindowMinSize} plus the
     * minimum sizes of touching descendants on the same axis.
     *
     * @return true when the tree was changed and re-laid out.
     */
    public boolean resizeSplit(int nodeId, int childIndex, float delta) {
        Node node = this.nodes.get(nodeId);
        if (node == null || node.children.size() < 2 || node.split == Split.NONE) {
            return false;
        }
        if (childIndex != 0 && childIndex != 1) {
            throw new IllegalArgumentException("childIndex must be 0 or 1");
        }
        if (delta == 0.0f) {
            return false;
        }

        Node child0 = node.children.get(0);
        Node child1 = node.children.get(1);
        if (!child0.visible || !child1.visible) {
            return false;
        }

        final int axis = node.split.axis();
        final float minSize = windowMinSize(axis);
        final float old0 = child0.size(axis);
        final float old1 = child1.size(axis);

        float limit0 = child0.position(axis) + minSize;
        float limit1 = child1.position(axis) + child1.size(axis) - minSize;

        List<Node> touching0 = new ArrayList<>();
        List<Node> touching1 = new ArrayList<>();
        // Reference: child_0 is searched from its right side (1), child_1 from its left side (0).
        findTouchingNodes(child0, axis, 1, touching0);
        findTouchingNodes(child1, axis, 0, touching1);
        for (Node touching : touching0) {
            limit0 = Math.max(limit0, touching.position(axis) + minSize);
        }
        for (Node touching : touching1) {
            limit1 = Math.min(limit1, touching.position(axis) + touching.size(axis) - minSize);
        }

        final float min0 = Math.max(0.0f, limit0 - child0.position(axis));
        final float min1 = Math.max(0.0f, child1.position(axis) + child1.size(axis) - limit1);

        // SplitterBehavior() applies the delta to child 0 and clamps it against
        // both minimum sizes before applying the resize.
        float mouseDelta = childIndex == 0 ? delta : -delta;
        final float size0MaxDelta = Math.max(0.0f, old0 - min0);
        final float size1MaxDelta = Math.max(0.0f, old1 - min1);
        if (mouseDelta < -size0MaxDelta) {
            mouseDelta = -size0MaxDelta;
        }
        if (mouseDelta > size1MaxDelta) {
            mouseDelta = size1MaxDelta;
        }
        if (mouseDelta == 0.0f) {
            return false;
        }

        final float new0 = Math.max(old0 + mouseDelta, min0);
        final float new1 = Math.max(old1 - mouseDelta, min1);
        if (new0 == old0 && new1 == old1) {
            return false;
        }

        setAxisLockedSize(child0, axis, new0);
        setAxisLockedSize(child1, axis, new1);

        // Keep the boundary position coherent before the two subtree updates.
        if (axis == AXIS_X) {
            child1.x -= new1 - old1;
        } else {
            child1.y -= new1 - old1;
        }

        // Preserve the sizes of siblings along the same split axis, as the
        // reference splitter does through WantLockSizeOnce.
        lockTouchingSiblings(node, child0, 0, touching0, axis);
        lockTouchingSiblings(node, child1, 1, touching1, axis);

        updatePosSize(child0, child0.x, child0.y, child0.w, child0.h);
        updatePosSize(child1, child1.x, child1.y, child1.w, child1.h);
        return true;
    }

    private void lockTouchingSiblings(Node splitNode, Node child, int side, List<Node> touching, int axis) {
        for (Node touchingNode : touching) {
            Node walk = touchingNode;
            while (walk.parent != null && walk.parent != splitNode) {
                if (walk.parent.split.axis() == axis && walk.parent.split != Split.NONE) {
                    Node preserve = walk.parent.child(side);
                    if (preserve != null) {
                        preserve.wantLockSizeOnce = true;
                    }
                }
                walk = walk.parent;
            }
        }
    }

    /** Port of {@code DockNodeTreeUpdateSplitterFindTouchingNode()}. */
    private static void findTouchingNodes(Node node, int axis, int side, List<Node> out) {
        if (node.isLeaf()) {
            out.add(node);
            return;
        }
        Node child0 = node.children.get(0);
        Node child1 = node.children.size() > 1 ? node.children.get(1) : null;
        if (child0.visible) {
            if (node.split.axis() != axis || side == 0 || child1 == null || !child1.visible) {
                findTouchingNodes(child0, axis, side, out);
            }
        }
        if (child1 != null && child1.visible) {
            if (node.split.axis() != axis || side == 1 || !child0.visible) {
                findTouchingNodes(child1, axis, side, out);
            }
        }
    }

    private static Node findNodeAt(Node node, float x, float y) {
        if (!node.visible) {
            return null;
        }
        if (!node.rect().contains(x, y)) {
            return null;
        }
        if (!node.isLeaf()) {
            Node hit = findNodeAt(node.children.get(0), x, y);
            if (hit != null) {
                return hit;
            }
            if (node.children.size() > 1) {
                hit = findNodeAt(node.children.get(1), x, y);
                if (hit != null) {
                    return hit;
                }
            }
        }
        // Hovering a splitter/spacing means the parent node itself is hit.
        return node;
    }

    private static float trunc(float value) {
        // ImTrunc() == (int)value, i.e. truncation toward zero.
        return (float) (int) value;
    }

    // ------------------------------------------------------------------
    // Serialization
    // ------------------------------------------------------------------

    /** Serialize the docking section, including its {@code [Docking][Data]} header. */
    public String toIniData() {
        StringBuilder out = new StringBuilder();
        out.append("[Docking][Data]\n");
        for (Node root : this.roots) {
            appendNode(out, root, 0);
        }
        out.append('\n');
        return out.toString();
    }

    public void writeIniData(Path path) throws IOException {
        Files.writeString(path, toIniData(), StandardCharsets.UTF_8);
    }

    private static void appendNode(StringBuilder out, Node node, int depth) {
        out.append(" ".repeat(Math.max(0, depth) * 2));
        out.append(node.dockSpace ? "DockSpace" : "DockNode");
        out.append(String.format(Locale.ROOT, " ID=0x%08X", node.id));

        if (node.parent != null) {
            out.append(String.format(Locale.ROOT, " Parent=0x%08X SizeRef=%d,%d",
                node.parent.id, (int) node.sizeRefX, (int) node.sizeRefY));
        } else {
            if (node.parentWindowId != 0) {
                out.append(String.format(Locale.ROOT, " Window=0x%08X", node.parentWindowId));
            }
            out.append(String.format(Locale.ROOT, " Pos=%d,%d Size=%d,%d",
                (int) node.x, (int) node.y, (int) node.w, (int) node.h));
        }

        if (node.split != Split.NONE) {
            out.append(" Split=").append(node.split == Split.Y ? 'Y' : 'X');
        }
        if (node.noResize) {
            out.append(" NoResize=1");
        }
        if (node.centralNode) {
            out.append(" CentralNode=1");
        }
        if (node.noTabBar) {
            out.append(" NoTabBar=1");
        }
        if (node.hiddenTabBar) {
            out.append(" HiddenTabBar=1");
        }
        if (node.noWindowMenuButton) {
            out.append(" NoWindowMenuButton=1");
        }
        if (node.noCloseButton) {
            out.append(" NoCloseButton=1");
        }
        if (node.selectedTabId != 0) {
            out.append(String.format(Locale.ROOT, " Selected=0x%08X", node.selectedTabId));
        }
        out.append('\n');

        for (Node child : node.children) {
            appendNode(out, child, depth + 1);
        }
    }

    // ------------------------------------------------------------------
    // Parsing
    // ------------------------------------------------------------------

    private void read(String text) {
        boolean inDocking = false;
        boolean inWindow = false;
        String[] lines = text.split("\\R", -1);
        for (String rawLine : lines) {
            String line = rawLine.trim();
            if (line.isEmpty()) {
                continue;
            }
            if (line.startsWith("[")) {
                inDocking = line.startsWith("[Docking][Data]");
                inWindow = line.startsWith("[Window]");
                continue;
            }
            if (inDocking) {
                if (line.startsWith("DockSpace")) {
                    this.rawNodes.add(parseNodeLine(line, true));
                } else if (line.startsWith("DockNode")) {
                    this.rawNodes.add(parseNodeLine(line, false));
                }
            } else if (inWindow && line.startsWith("DockId=")) {
                String value = line.substring("DockId=".length()).trim();
                int comma = value.indexOf(',');
                if (comma >= 0) {
                    value = value.substring(0, comma);
                }
                int dockId = parseId(value);
                if (dockId != 0) {
                    this.windowCounts.merge(dockId, 1, Integer::sum);
                }
            }
        }
    }

    private static Raw parseNodeLine(String line, boolean dockSpace) {
        Raw raw = new Raw();
        raw.dockSpace = dockSpace;
        Map<String, String> values = parseValues(line);
        raw.id = parseId(values.get("ID"));
        raw.parentId = parseId(values.get("Parent"));
        raw.parentWindowId = parseId(values.get("Window"));
        raw.selectedTabId = parseId(values.get("Selected"));

        float[] pos = parsePair(values.get("Pos"));
        float[] size = parsePair(values.get("Size"));
        float[] sizeRef = parsePair(values.get("SizeRef"));
        raw.posX = pos[0];
        raw.posY = pos[1];
        raw.sizeX = size[0];
        raw.sizeY = size[1];
        raw.sizeRefX = sizeRef[0];
        raw.sizeRefY = sizeRef[1];

        String split = values.get("Split");
        if (split != null && !split.isEmpty()) {
            raw.split = split.charAt(0) == 'Y' ? Split.Y : Split.X;
        }
        raw.noResize = isTrue(values.get("NoResize"));
        raw.centralNode = isTrue(values.get("CentralNode"));
        raw.noTabBar = isTrue(values.get("NoTabBar"));
        raw.hiddenTabBar = isTrue(values.get("HiddenTabBar"));
        raw.noWindowMenuButton = isTrue(values.get("NoWindowMenuButton"));
        raw.noCloseButton = isTrue(values.get("NoCloseButton"));
        return raw;
    }

    private static Map<String, String> parseValues(String line) {
        Map<String, String> values = new HashMap<>();
        int comment = line.indexOf(';');
        if (comment >= 0) {
            line = line.substring(0, comment);
        }
        for (String token : line.trim().split("\\s+")) {
            int equals = token.indexOf('=');
            if (equals > 0) {
                values.put(token.substring(0, equals), token.substring(equals + 1));
            }
        }
        return values;
    }

    private static float[] parsePair(String value) {
        float[] result = new float[2];
        if (value != null) {
            String[] parts = value.split(",");
            if (parts.length > 0) {
                result[0] = parseFloat(parts[0]);
            }
            if (parts.length > 1) {
                result[1] = parseFloat(parts[1]);
            }
        }
        return result;
    }

    private static int parseId(String value) {
        if (value == null || value.isEmpty()) {
            return 0;
        }
        try {
            if (value.startsWith("0x") || value.startsWith("0X")) {
                return (int) Long.parseLong(value.substring(2), 16);
            }
            return (int) Long.parseLong(value);
        } catch (NumberFormatException ignored) {
            return 0;
        }
    }

    private static float parseFloat(String value) {
        try {
            return Float.parseFloat(value);
        } catch (NumberFormatException ignored) {
            return 0.0f;
        }
    }

    private static boolean isTrue(String value) {
        return value != null && !value.isEmpty() && !value.equals("0");
    }

    private void build() {
        // First pass: instantiate every node so parents can appear later in the file.
        for (Raw raw : this.rawNodes) {
            if (raw.id == 0 || this.nodes.containsKey(raw.id)) {
                continue;
            }
            this.nodes.put(raw.id, new Node(raw));
        }

        // Second pass: link parent/child relationships in file order. The ini
        // writes a parent before its children, but the lookup is order-agnostic.
        for (Raw raw : this.rawNodes) {
            Node node = this.nodes.get(raw.id);
            if (node == null) {
                continue;
            }
            node.windowCount = this.windowCounts.getOrDefault(raw.id, 0);
            if (raw.parentId == 0) {
                continue;
            }
            Node parent = this.nodes.get(raw.parentId);
            if (parent == null) {
                continue;
            }
            node.parent = parent;
            if (parent.children.size() < 2) {
                parent.children.add(node);
            }
        }

        for (Raw raw : this.rawNodes) {
            Node node = this.nodes.get(raw.id);
            if (node == null || node.parent != null || node.parentId != 0) {
                continue;
            }
            if (!this.roots.contains(node)) {
                this.roots.add(node);
                if (this.primaryRoot == null) {
                    this.primaryRoot = node;
                }
            }
        }

        for (Node root : this.roots) {
            Node central = findCentralNode(root);
            Node mark = central;
            while (mark != null) {
                mark.hasCentralNodeChild = true;
                mark = mark.parent;
            }
            updateVisible(root);
        }
    }

    private static Node findCentralNode(Node node) {
        if (node.centralNode) {
            return node;
        }
        for (Node child : node.children) {
            Node found = findCentralNode(child);
            if (found != null) {
                return found;
            }
        }
        return null;
    }

    private static boolean updateVisible(Node node) {
        // Port of DockNodeUpdateVisibleFlag().
        boolean visible = node.dockSpace || node.centralNode;
        visible |= node.hasWindows();
        for (Node child : node.children) {
            visible |= updateVisible(child);
        }
        node.visible = visible;
        return visible;
    }
}
