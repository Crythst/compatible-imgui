package com.noimgui.imgui;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

/**
 * Standalone keyboard-navigation state machine modelled on Dear ImGui 1.92
 * ({@code NavUpdate}, {@code NavMoveRequest*}, {@code SetKeyboardFocusHere},
 * {@code NavProcessItemForTabbingRequest} and widget focus handling).
 *
 * <p>The host submits focusable items every frame, in the same way an
 * immediate-mode UI submits widgets:</p>
 *
 * <pre>{@code
 * NavState nav = new NavState();
 *
 * // once per host frame, before submitting widgets:
 * nav.beginFrame(keys);          // keys implements NavState.KeySource
 *
 * nav.setWindow(windowId);
 * nav.registerItem(buttonId, NavState.Rect.of(x, y, w, h), true);
 *
 * if (nav.isFocused(buttonId) && nav.activatedId() == buttonId) {
 *     // Enter/Space was pressed on the focused button
 * }
 * }</pre>
 *
 * <p>Navigation inputs are expressed as key <em>down</em> state and key
 * <em>pressed</em> edges. The pressed edge is reported on the initial press
 * and again for every OS key-repeat event, so callers are responsible for
 * translating repeat timing into repeated edges. Navigation never advances
 * merely because a key is held down.</p>
 *
 * <p>Tab and Shift+Tab walk the focusable items in registration order and
 * wrap around. Arrow keys use the same box/center scoring as Dear ImGui's
 * {@code NavScoreItem()}, including the preferred-position bias that makes
 * repeated movement in a direction stick to a column/row. Enter, keypad Enter
 * and Space activate the focused item through {@link #activate()}.</p>
 *
 * <p>Like ImGui, this class keeps the previously submitted item list so a
 * move request processed at the start of a frame can still find the item that
 * was focused on the previous frame. Instances are not thread-safe.</p>
 */
public final class NavState {

    /** Reserved "no item / no window" identifier. */
    public static final long NO_ID = 0L;

    /** Window used by {@link #registerItem(long, Rect, boolean)} until {@link #setWindow(long)} is called. */
    public static final long DEFAULT_WINDOW = 1L;

    // GLFW-compatible key codes, so a backend only needs to forward its key values.
    public static final int KEY_TAB = 258;
    public static final int KEY_ENTER = 257;
    public static final int KEY_KEYPAD_ENTER = 335;
    public static final int KEY_SPACE = 32;
    public static final int KEY_RIGHT = 262;
    public static final int KEY_LEFT = 263;
    public static final int KEY_DOWN = 264;
    public static final int KEY_UP = 265;
    public static final int KEY_SHIFT_LEFT = 340;
    public static final int KEY_SHIFT_RIGHT = 344;

    /** Directional move request. */
    public enum Dir {
        LEFT, RIGHT, UP, DOWN
    }

    /**
     * Rectangle in the same coordinate space for every item of a window.
     * Bounds are normalized by the constructor; helper {@link #of} takes
     * position plus size.
     */
    public record Rect(float minX, float minY, float maxX, float maxY) {

        public Rect {
            if (minX > maxX) {
                float t = minX;
                minX = maxX;
                maxX = t;
            }
            if (minY > maxY) {
                float t = minY;
                minY = maxY;
                maxY = t;
            }
        }

        public static Rect of(float x, float y, float width, float height) {
            return new Rect(x, y, x + width, y + height);
        }

        public float width() {
            return maxX - minX;
        }

        public float height() {
            return maxY - minY;
        }

        public float centerX() {
            return (minX + maxX) * 0.5f;
        }

        public float centerY() {
            return (minY + maxY) * 0.5f;
        }

        public boolean overlaps(Rect other) {
            return minX <= other.maxX && other.minX <= maxX
                    && minY <= other.maxY && other.minY <= maxY;
        }

        public Rect translated(float dx, float dy) {
            return new Rect(minX + dx, minY + dy, maxX + dx, maxY + dy);
        }
    }

    /**
     * Source of key state for one host frame.
     *
     * <p>{@link #isKeyDown(int)} is the continuous held state.
     * {@link #isKeyPressed(int)} is an edge and must be true on the initial
     * press and on every repeat event, but false on frames where the key is
     * merely held down.</p>
     */
    public interface KeySource {

        boolean isKeyDown(int key);

        boolean isKeyPressed(int key);

        default boolean isShiftDown() {
            return isKeyDown(KEY_SHIFT_LEFT) || isKeyDown(KEY_SHIFT_RIGHT);
        }
    }

    /**
     * Convenience mutable {@link KeySource} for tests and simple backends.
     * Call {@link #clearPressed()} once per host frame after
     * {@link NavState#beginFrame(KeySource)}; held keys remain down.
     */
    public static final class FrameInput implements KeySource {

        private final java.util.Set<Integer> down = new java.util.HashSet<>();
        private final java.util.Set<Integer> pressed = new java.util.HashSet<>();

        public void clearPressed() {
            pressed.clear();
        }

        public void clear() {
            down.clear();
            pressed.clear();
        }

        public void setDown(int key, boolean isDown) {
            if (isDown) {
                down.add(key);
            } else {
                down.remove(key);
            }
        }

        /** Reports both the down state and a fresh pressed edge. */
        public void press(int key) {
            down.add(key);
            pressed.add(key);
        }

        /** Clears the down state without producing a pressed edge. */
        public void release(int key) {
            down.remove(key);
        }

        @Override
        public boolean isKeyDown(int key) {
            return down.contains(key);
        }

        @Override
        public boolean isKeyPressed(int key) {
            return pressed.contains(key);
        }
    }

    private static final class Item {

        final long id;
        Rect rect;
        boolean focusable;

        Item(long id, Rect rect, boolean focusable) {
            this.id = id;
            this.rect = rect;
            this.focusable = focusable;
        }
    }

    private static final class WindowState {

        final long id;
        List<Item> current = new ArrayList<>();
        Map<Long, Item> currentById = new LinkedHashMap<>();
        List<Item> previous = List.of();
        long lastNavId = NO_ID;
        Rect lastNavRect = new Rect(0.0f, 0.0f, 0.0f, 0.0f);

        // NavPreferredScoringPosRel in ImGui. Absolute coordinates here because
        // this state machine has no window scroll offset.
        boolean preferredXValid;
        float preferredX;
        boolean preferredYValid;
        float preferredY;

        WindowState(long id) {
            this.id = id;
        }

        void beginFrame() {
            previous = current;
            current = new ArrayList<>();
            currentById = new LinkedHashMap<>();
        }

        List<Item> navigationOrder() {
            return current.isEmpty() ? previous : current;
        }

        Item find(long itemId) {
            Item item = currentById.get(itemId);
            if (item != null) {
                return item;
            }
            for (Item candidate : previous) {
                if (candidate.id == itemId) {
                    return candidate;
                }
            }
            return null;
        }
    }

    private record Score(float distBox, float distCenter, float dbx, float dby) {
    }

    private final Map<Long, WindowState> windows = new LinkedHashMap<>();

    private long currentWindow = DEFAULT_WINDOW;
    private long navWindow = NO_ID;
    private long navId = NO_ID;
    private boolean navActive;

    private long navJustMovedFromId = NO_ID;
    private long navJustMovedToId = NO_ID;

    // ImGui's NavActivateId / NavActivateDownId / NavActivatePressedId.
    private long navActivateId = NO_ID;
    private long navActivateDownId = NO_ID;
    private long navActivatePressedId = NO_ID;
    private long lastActivatedId = NO_ID;

    private long pendingFocusId = NO_ID;
    private long pendingFocusWindow = DEFAULT_WINDOW;

    private int frame;

    /**
     * Starts a new host frame without consuming any keys. If a focus request
     * is still pending and its item was submitted last frame, it is applied
     * here. Call {@link #processKeys(KeySource)} after registering items if
     * the caller wants manual control over input ordering.
     */
    public void beginFrame() {
        frame++;

        navActivateId = NO_ID;
        navActivateDownId = NO_ID;
        navActivatePressedId = NO_ID;
        navJustMovedFromId = NO_ID;
        navJustMovedToId = NO_ID;

        for (WindowState window : windows.values()) {
            window.beginFrame();
        }

        if (pendingFocusId != NO_ID) {
            WindowState window = findWindowContaining(pendingFocusId, pendingFocusWindow);
            if (window != null) {
                applyFocus(window, window.find(pendingFocusId));
                pendingFocusId = NO_ID;
            }
        }

        updateNavActive();
    }

    /**
     * Starts a new frame and immediately processes navigation/activation keys
     * (Tab, Shift+Tab, arrows, Enter, keypad Enter, Space). Move requests use
     * the item list submitted last frame, matching Dear ImGui's frame-start
     * {@code NavUpdate()} ordering.
     */
    public void beginFrame(KeySource keys) {
        beginFrame();
        processKeys(keys);
    }

    /**
     * Processes navigation and activation keys against the current focus.
     * Useful when the host calls {@link #beginFrame()} first, registers items,
     * then feeds input. Pressed edges are required; held keys alone do not
     * move focus. The first Enter/Space activation of a frame sets
     * {@link #activatedId()}.
     */
    public void processKeys(KeySource keys) {
        if (keys == null) {
            return;
        }

        // Activation is evaluated before the move request, as in NavUpdate().
        boolean activateDown = keys.isKeyDown(KEY_ENTER)
                || keys.isKeyDown(KEY_KEYPAD_ENTER)
                || keys.isKeyDown(KEY_SPACE);
        boolean activatePressed = keys.isKeyPressed(KEY_ENTER)
                || keys.isKeyPressed(KEY_KEYPAD_ENTER)
                || keys.isKeyPressed(KEY_SPACE);
        if (navId != NO_ID) {
            if (activateDown) {
                navActivateDownId = navId;
            }
            if (activatePressed) {
                activate();
            }
        }

        // Same order as NavUpdateCreateMoveRequest(): the last pressed
        // direction wins if the host reports more than one in a frame.
        // Arrows take precedence over Tab, as in ImGui.
        Dir dir = null;
        if (keys.isKeyPressed(KEY_LEFT)) {
            dir = Dir.LEFT;
        }
        if (keys.isKeyPressed(KEY_RIGHT)) {
            dir = Dir.RIGHT;
        }
        if (keys.isKeyPressed(KEY_UP)) {
            dir = Dir.UP;
        }
        if (keys.isKeyPressed(KEY_DOWN)) {
            dir = Dir.DOWN;
        }
        if (dir != null) {
            move(dir);
        } else if (keys.isKeyPressed(KEY_TAB)) {
            moveTab(keys.isShiftDown());
        }

        updateNavActive();
    }

    /**
     * Selects the window used by subsequent {@link #registerItem} calls.
     * Existing focus is not changed; use {@link #requestFocus(long)} or
     * navigation to move focus into the new window.
     */
    public void setWindow(long windowId) {
        currentWindow = windowId == NO_ID ? DEFAULT_WINDOW : windowId;
        if (navWindow == NO_ID) {
            navWindow = currentWindow;
        }
    }

    /** Returns the window used by subsequent register calls. */
    public long currentWindow() {
        return currentWindow;
    }

    /**
     * Registers or updates an item for the current window. The registration
     * order is the Tab order. Submitting an already-known id updates its
     * rectangle/focusability without changing its position in the order.
     *
     * <p>{@code focusable == false} keeps the item visible to hit-testing and
     * {@link #rectOf(long)} but removes it from Tab and arrow candidates
     * (ImGui's {@code ImGuiItemFlags_NoTabStop} / {@code NoNav}).</p>
     *
     * <p>If a pending {@link #requestFocus(long)} targets this id, focus is
     * applied as soon as the item is submitted, even when it did not exist
     * last frame.</p>
     */
    public void registerItem(long id, Rect rect, boolean focusable) {
        if (id == NO_ID) {
            throw new IllegalArgumentException("item id 0 is reserved (NavState.NO_ID)");
        }
        Objects.requireNonNull(rect, "rect");

        WindowState window = windows.computeIfAbsent(currentWindow, WindowState::new);
        Item item = window.currentById.get(id);
        if (item == null) {
            item = new Item(id, rect, focusable);
            window.current.add(item);
            window.currentById.put(id, item);
        } else {
            item.rect = rect;
            item.focusable = focusable;
        }

        if (navWindow == NO_ID) {
            navWindow = currentWindow;
        }

        // SetKeyboardFocusHere()-style request: apply when the target appears.
        if (pendingFocusId == id && pendingFocusWindow == currentWindow) {
            applyFocus(window, item);
            pendingFocusId = NO_ID;
        }

        if (navId == id) {
            window.lastNavId = id;
            window.lastNavRect = rect;
        }

        updateNavActive();
    }

    /**
     * Requests keyboard focus for an item, without activating it. This is the
     * focus-only part of {@code SetKeyboardFocusHere()} / {@code FocusItem()}.
     *
     * <p>If the item is already known, focus is applied immediately and the
     * current window becomes the nav window. Otherwise the request stays
     * pending until the item is registered (possibly in a later frame).
     * Passing {@link #NO_ID} clears focus and cancels a pending request.</p>
     *
     * @return true when focus was applied immediately, false when the request
     *         is queued for a not-yet-registered item
     */
    public boolean requestFocus(long id) {
        if (id == NO_ID) {
            pendingFocusId = NO_ID;
            clearFocus();
            return true;
        }

        WindowState window = findWindowContaining(id, currentWindow);
        if (window != null) {
            applyFocus(window, window.find(id));
            pendingFocusId = NO_ID;
            return true;
        }

        pendingFocusId = id;
        pendingFocusWindow = currentWindow;
        return false;
    }

    /** True while a request for an item not yet registered is queued. */
    public boolean hasPendingFocusRequest() {
        return pendingFocusId != NO_ID;
    }

    /** Returns the id of the queued focus request, or {@link #NO_ID}. */
    public long pendingFocusId() {
        return pendingFocusId;
    }

    /**
     * Clears the focused item while keeping the nav window. Mirrors Escape /
     * {@code SetKeyboardFocusHere(0)}-style clearing. Does not clear a pending
     * request; use {@code requestFocus(NO_ID)} for that.
     */
    public void clearFocus() {
        if (navId != NO_ID) {
            navJustMovedFromId = navId;
        }
        navId = NO_ID;
        navJustMovedToId = NO_ID;
        updateNavActive();
    }

    /**
     * Tab/Shift+Tab movement in registration order, wrapping at the ends.
     * Non-focusable items are skipped. Does not activate the destination
     * (Enter/Space do that).
     *
     * @param backward true for Shift+Tab
     * @return true if the focused id changed
     */
    public boolean moveTab(boolean backward) {
        WindowState window = navigationWindow();
        if (window == null) {
            return false;
        }

        List<Item> order = window.navigationOrder();
        List<Item> focusable = new ArrayList<>(order.size());
        for (Item item : order) {
            if (item.focusable) {
                focusable.add(item);
            }
        }
        if (focusable.isEmpty()) {
            return false;
        }

        int currentIndex = -1;
        for (int i = 0; i < focusable.size(); i++) {
            if (focusable.get(i).id == navId) {
                currentIndex = i;
                break;
            }
        }

        Item target;
        if (currentIndex < 0) {
            target = backward ? focusable.get(focusable.size() - 1) : focusable.get(0);
        } else {
            int next = currentIndex + (backward ? -1 : 1);
            if (next < 0) {
                next = focusable.size() - 1;
            } else if (next >= focusable.size()) {
                next = 0;
            }
            target = focusable.get(next);
        }

        long previousId = navId;
        applyFocus(window, target);
        return navId != previousId;
    }

    /** Tab forward. Equivalent to {@code moveTab(false)}. */
    public boolean moveNext() {
        return moveTab(false);
    }

    /** Shift+Tab. Equivalent to {@code moveTab(true)}. */
    public boolean movePrevious() {
        return moveTab(true);
    }

    /**
     * Directional move. Uses ImGui's {@code NavScoreItem()} box/center scoring
     * and preferred-position bias. Arrows do not wrap.
     *
     * <p>When there is no current focus, the first focusable item of the nav
     * window is focused (ImGui's init request fallback).</p>
     *
     * @return true if the focused id changed
     */
    public boolean move(Dir dir) {
        if (dir == null) {
            return false;
        }

        WindowState window = navigationWindow();
        if (window == null) {
            return false;
        }

        List<Item> order = window.navigationOrder();
        Item current = findItem(order, navId);
        if (current == null) {
            Item first = firstFocusable(order);
            if (first == null) {
                return false;
            }
            applyFocus(window, first);
            return true;
        }

        boolean vertical = dir == Dir.UP || dir == Dir.DOWN;
        Rect scoringRect = biasedScoringRect(window, current.rect, dir);

        Item best = null;
        Score bestScore = null;
        for (Item candidate : order) {
            if (!candidate.focusable || candidate.id == current.id) {
                continue;
            }
            Score score = score(scoringRect, candidate.rect, candidate.id, dir, current.id);
            if (score == null) {
                continue;
            }
            if (bestScore == null
                    || score.distBox < bestScore.distBox
                    || (score.distBox == bestScore.distBox
                        && (score.distCenter < bestScore.distCenter
                            || (score.distCenter == bestScore.distCenter
                                && (vertical ? score.dby : score.dbx) < 0.0f)))) {
                best = candidate;
                bestScore = score;
            }
        }

        if (best == null) {
            // Failed move clears the preferred position for this axis, as in
            // NavMoveRequestApplyResult().
            if (vertical) {
                window.preferredXValid = false;
            } else {
                window.preferredYValid = false;
            }
            return false;
        }

        long previousId = navId;
        applyFocus(window, best);

        // SetNavID() clears both preferred positions; a successful directional
        // move then restores the center on the axis that was moved.
        window.preferredXValid = false;
        window.preferredYValid = false;
        if (vertical) {
            window.preferredYValid = true;
            window.preferredY = best.rect.centerY();
        } else {
            window.preferredXValid = true;
            window.preferredX = best.rect.centerX();
        }
        return navId != previousId;
    }

    /**
     * Activates the focused item, mirroring ImGui setting
     * {@code NavActivateId / NavActivateDownId / NavActivatePressedId}.
     * Widgets normally test {@link #activatedId()} or {@link #isActivated(long)}
     * during the same frame. Enter/Space call this automatically when their
     * pressed edge is observed.
     *
     * @return true if there was a focused item to activate
     */
    public boolean activate() {
        if (navId == NO_ID) {
            return false;
        }
        navActivateId = navId;
        navActivateDownId = navId;
        navActivatePressedId = navId;
        lastActivatedId = navId;
        return true;
    }

    /** Focused item id, or {@link #NO_ID}. */
    public long focusedId() {
        return navId;
    }

    /** Alias for {@link #focusedId()} using ImGui's NavId terminology. */
    public long navId() {
        return navId;
    }

    /** True when exactly {@code id} is focused. */
    public boolean isFocused(long id) {
        return id != NO_ID && navId == id;
    }

    /** Window that currently owns keyboard navigation, or {@link #NO_ID}. */
    public long navWindow() {
        return navWindow;
    }

    /** True when navigation is enabled and a nav window with items exists. */
    public boolean navActive() {
        return navActive;
    }

    /** Item activated this frame, or {@link #NO_ID}. Resets every frame. */
    public long activatedId() {
        return navActivateId;
    }

    /** True when {@code id} is the activation target for this frame. */
    public boolean isActivated(long id) {
        return id != NO_ID && (navActivateId == id || navActivatePressedId == id);
    }

    /** Activation "down" state, mirroring ImGui's NavActivateDownId. */
    public long navActivateDownId() {
        return navActivateDownId;
    }

    /** Activation pressed state, mirroring ImGui's NavActivatePressedId. */
    public long navActivatePressedId() {
        return navActivatePressedId;
    }

    /** Most recent explicitly activated item (persists across frames). */
    public long lastActivatedId() {
        return lastActivatedId;
    }

    /**
     * Focus destination of this frame's successful move/focus change, or
     * {@link #NO_ID}. Mirrors ImGui's NavJustMovedToId.
     */
    public long navJustMovedToId() {
        return navJustMovedToId;
    }

    /**
     * Focus source of this frame's successful move/focus change, or
     * {@link #NO_ID}. Mirrors ImGui's NavJustMovedFromId.
     */
    public long navJustMovedFromId() {
        return navJustMovedFromId;
    }

    /** Number of completed {@link #beginFrame()} calls since construction/reset. */
    public int frame() {
        return frame;
    }

    /**
     * Focusable item ids of a window in Tab order. Before the window submits
     * its first item in the current frame, this is the previous frame's order.
     */
    public List<Long> focusOrder(long windowId) {
        WindowState window = windows.get(windowId);
        if (window == null) {
            return List.of();
        }
        List<Long> ids = new ArrayList<>();
        for (Item item : window.navigationOrder()) {
            if (item.focusable) {
                ids.add(item.id);
            }
        }
        return Collections.unmodifiableList(ids);
    }

    /** Current rectangle of an item, or null if unknown. */
    public Rect rectOf(long id) {
        WindowState window = findWindowContaining(id, navWindow != NO_ID ? navWindow : currentWindow);
        if (window == null) {
            return null;
        }
        Item item = window.find(id);
        return item != null ? item.rect : null;
    }

    /** Current rectangle of the focused item, or null. */
    public Rect focusedRect() {
        return navId == NO_ID ? null : rectOf(navId);
    }

    /** True when the id has been submitted in the current or previous frame. */
    public boolean isRegistered(long id) {
        return id != NO_ID && findWindowContaining(id, currentWindow) != null;
    }

    /** Clears every window, item, focus request and input-derived state. */
    public void reset() {
        windows.clear();
        currentWindow = DEFAULT_WINDOW;
        navWindow = NO_ID;
        navId = NO_ID;
        navActive = false;
        navJustMovedFromId = NO_ID;
        navJustMovedToId = NO_ID;
        navActivateId = NO_ID;
        navActivateDownId = NO_ID;
        navActivatePressedId = NO_ID;
        lastActivatedId = NO_ID;
        pendingFocusId = NO_ID;
        pendingFocusWindow = DEFAULT_WINDOW;
        frame = 0;
    }

    // ------------------------------------------------------------------
    // Internals
    // ------------------------------------------------------------------

    private void applyFocus(WindowState window, Item item) {
        if (item == null) {
            return;
        }
        if (navId != item.id) {
            navJustMovedFromId = navId;
            navJustMovedToId = item.id;
        }
        navWindow = window.id;
        navId = item.id;
        window.lastNavId = item.id;
        window.lastNavRect = item.rect;

        // SetNavID() clears preferred scoring positions.
        window.preferredXValid = false;
        window.preferredYValid = false;
        updateNavActive();
    }

    private WindowState navigationWindow() {
        WindowState window = windows.get(navWindow);
        if (window != null && !window.navigationOrder().isEmpty()) {
            return window;
        }
        WindowState current = windows.get(currentWindow);
        if (current != null && !current.navigationOrder().isEmpty()) {
            navWindow = current.id;
            return current;
        }
        return window;
    }

    private WindowState findWindowContaining(long id, long preferredWindow) {
        WindowState preferred = windows.get(preferredWindow);
        if (preferred != null && preferred.find(id) != null) {
            return preferred;
        }
        WindowState nav = windows.get(navWindow);
        if (nav != null && nav.find(id) != null) {
            return nav;
        }
        WindowState current = windows.get(currentWindow);
        if (current != null && current.find(id) != null) {
            return current;
        }
        for (WindowState window : windows.values()) {
            if (window.find(id) != null) {
                return window;
            }
        }
        return null;
    }

    private void updateNavActive() {
        if (navWindow == NO_ID) {
            navActive = false;
            return;
        }
        WindowState window = windows.get(navWindow);
        if (window == null) {
            navActive = false;
            return;
        }
        navActive = navId != NO_ID || firstFocusable(window.navigationOrder()) != null;
    }

    private static Item findItem(List<Item> items, long id) {
        for (Item item : items) {
            if (item.id == id) {
                return item;
            }
        }
        return null;
    }

    private static Item firstFocusable(List<Item> items) {
        for (Item item : items) {
            if (item.focusable) {
                return item;
            }
        }
        return null;
    }

    private static Rect biasedScoringRect(WindowState window, Rect current, Dir dir) {
        // NavBiasScoringRect(): initialize missing preferred positions on
        // departure, then collapse the scoring box on the movement axis.
        if (!window.preferredXValid) {
            window.preferredX = Math.min(current.minX + 1.0f, current.maxX);
            window.preferredXValid = true;
        }
        if (!window.preferredYValid) {
            window.preferredY = current.centerY();
            window.preferredYValid = true;
        }
        if (dir == Dir.UP || dir == Dir.DOWN) {
            // A zero-width scoring line at the preferred X, spanning the
            // current item's Y range.
            return new Rect(window.preferredX, current.minY,
                    window.preferredX, current.maxY);
        }
        return new Rect(current.minX, window.preferredY,
                current.maxX, window.preferredY);
    }

    /**
     * Direct port of NavScoreItem() minus window clipping/flattening. Returns
     * null when the candidate is not in the requested quadrant.
     */
    private static Score score(Rect current, Rect candidate, long candidateId,
                               Dir dir, long currentId) {
        float dbx = distInterval(candidate.minX, candidate.maxX,
                current.minX, current.maxX);
        float dby = distInterval(
                lerp(candidate.minY, candidate.maxY, 0.2f),
                lerp(candidate.minY, candidate.maxY, 0.8f),
                lerp(current.minY, current.maxY, 0.2f),
                lerp(current.minY, current.maxY, 0.8f));
        if (dby != 0.0f && dbx != 0.0f) {
            dbx = dbx / 1000.0f + (dbx > 0.0f ? 1.0f : -1.0f);
        }
        float distBox = Math.abs(dbx) + Math.abs(dby);

        float dcx = (candidate.minX + candidate.maxX) - (current.minX + current.maxX);
        float dcy = (candidate.minY + candidate.maxY) - (current.minY + current.maxY);
        float distCenter = Math.abs(dcx) + Math.abs(dcy);

        Dir quadrant;
        if (dbx != 0.0f || dby != 0.0f) {
            quadrant = quadrantFromDelta(dbx, dby);
        } else if (dcx != 0.0f || dcy != 0.0f) {
            quadrant = quadrantFromDelta(dcx, dcy);
        } else {
            // Degenerate overlapping boxes with identical centers: break ties
            // by item order, as ImGui does.
            quadrant = candidateId < currentId ? Dir.LEFT : Dir.RIGHT;
        }

        if (quadrant != dir) {
            return null;
        }
        return new Score(distBox, distCenter, dbx, dby);
    }

    private static float distInterval(float candidateMin, float candidateMax,
                                      float currentMin, float currentMax) {
        if (candidateMax < currentMin) {
            return candidateMax - currentMin;
        }
        if (currentMax < candidateMin) {
            return candidateMin - currentMax;
        }
        return 0.0f;
    }

    private static Dir quadrantFromDelta(float dx, float dy) {
        if (Math.abs(dx) > Math.abs(dy)) {
            return dx > 0.0f ? Dir.RIGHT : Dir.LEFT;
        }
        return dy > 0.0f ? Dir.DOWN : Dir.UP;
    }

    private static float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
}
