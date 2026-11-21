package com.noimgui.imgui;

import java.util.ArrayDeque;
import java.util.Objects;
import java.util.function.IntPredicate;

/**
 * Standalone, dependency-free editing model for a single-line text field.
 *
 * <p>This is a Java port of the parts of Dear ImGui 1.92's
 * {@code InputTextEx()}/{@code STB_TEXTEDIT} that own string state: cursor and
 * selection handling, character insertion and deletion, word-wise editing,
 * undo/redo, password masking and horizontal scrolling. It deliberately does
 * not render anything and does not know about windows, draw lists or fonts.
 * Hosts only need to forward key events, call {@link #insertText(String)} for
 * character input, and measure the displayed string through a
 * {@link CharMetrics} callback.</p>
 *
 * <p>The buffer is a UTF-16 {@link String} (the same representation Java uses).
 * Cursor movement, deletion and word boundaries operate on Unicode code points,
 * so surrogate pairs are never split by the built-in editing operations.
 * {@link #setCursorPos(int)} and {@link #setSelection(int, int)} snap indices
 * that fall inside a surrogate pair back to the start of the pair.</p>
 *
 * <p>Key codes are the named {@code ImGuiKey} values used by {@code PureUi} and
 * Dear ImGui:</p>
 *
 * <pre>
 * Tab=512  Left=513  Right=514  Up=515  Down=516  PageUp=517  PageDown=518
 * Home=519 End=520   Insert=521 Delete=522 Backspace=523 Space=524
 * Enter=525 Escape=526
 * LeftCtrl=527 LeftShift=528 LeftAlt=529 LeftSuper=530
 * RightCtrl=531 RightShift=532 RightAlt=533 RightSuper=534 Menu=535
 * 0..9 = 536..545, A..Z = 546..571
 * </pre>
 *
 * <p>Typical usage:</p>
 * <pre>{@code
 * InputTextModel field = new InputTextModel();
 * field.setCharFilter(c -> c >= '0' && c <= '9');
 * boolean changed = field.insertText("42");
 * field.key(InputTextModel.KEY_LEFT, false, true, false); // Shift+Left
 * field.ensureCursorVisible(contentWidth, metrics);
 * String shown = field.displayText();
 * }</pre>
 *
 * <p>Instances are not thread-safe. One instance belongs to one widget.</p>
 */
public final class InputTextModel {
    // ImGuiKey named-key values (see the table in the class Javadoc).
    public static final int KEY_TAB = 512;
    public static final int KEY_LEFT = 513;
    public static final int KEY_RIGHT = 514;
    public static final int KEY_UP = 515;
    public static final int KEY_DOWN = 516;
    public static final int KEY_PAGE_UP = 517;
    public static final int KEY_PAGE_DOWN = 518;
    public static final int KEY_HOME = 519;
    public static final int KEY_END = 520;
    public static final int KEY_INSERT = 521;
    public static final int KEY_DELETE = 522;
    public static final int KEY_BACKSPACE = 523;
    public static final int KEY_SPACE = 524;
    public static final int KEY_ENTER = 525;
    public static final int KEY_ESCAPE = 526;
    public static final int KEY_LEFT_CTRL = 527;
    public static final int KEY_LEFT_SHIFT = 528;
    public static final int KEY_LEFT_ALT = 529;
    public static final int KEY_LEFT_SUPER = 530;
    public static final int KEY_RIGHT_CTRL = 531;
    public static final int KEY_RIGHT_SHIFT = 532;
    public static final int KEY_RIGHT_ALT = 533;
    public static final int KEY_RIGHT_SUPER = 534;
    public static final int KEY_MENU = 535;

    public static final int KEY_0 = 536;
    public static final int KEY_1 = 537;
    public static final int KEY_2 = 538;
    public static final int KEY_3 = 539;
    public static final int KEY_4 = 540;
    public static final int KEY_5 = 541;
    public static final int KEY_6 = 542;
    public static final int KEY_7 = 543;
    public static final int KEY_8 = 544;
    public static final int KEY_9 = 545;

    public static final int KEY_A = 546;
    public static final int KEY_B = 547;
    public static final int KEY_C = 548;
    public static final int KEY_D = 549;
    public static final int KEY_E = 550;
    public static final int KEY_F = 551;
    public static final int KEY_G = 552;
    public static final int KEY_H = 553;
    public static final int KEY_I = 554;
    public static final int KEY_J = 555;
    public static final int KEY_K = 556;
    public static final int KEY_L = 557;
    public static final int KEY_M = 558;
    public static final int KEY_N = 559;
    public static final int KEY_O = 560;
    public static final int KEY_P = 561;
    public static final int KEY_Q = 562;
    public static final int KEY_R = 563;
    public static final int KEY_S = 564;
    public static final int KEY_T = 565;
    public static final int KEY_U = 566;
    public static final int KEY_V = 567;
    public static final int KEY_W = 568;
    public static final int KEY_X = 569;
    public static final int KEY_Y = 570;
    public static final int KEY_Z = 571;

    /** Maximum number of undo snapshots retained. */
    public static final int MAX_UNDO_HISTORY = 256;

    /** Measures the advance of one UTF-16 code unit of the displayed text. */
    @FunctionalInterface
    public interface CharMetrics {
        float advance(char c);
    }

    /**
     * Clipboard hook. {@link #read()} returns the current clipboard text (may be
     * {@code null} or empty) and {@link #write(String)} stores it.
     */
    public interface Clipboard {
        String read();

        void write(String text);
    }

    private record Snapshot(String text, int cursor, int anchor) {
    }

    private final StringBuilder buffer = new StringBuilder();
    private final ArrayDeque<Snapshot> undoStack = new ArrayDeque<>();
    private final ArrayDeque<Snapshot> redoStack = new ArrayDeque<>();

    private int cursor;
    private int anchor;
    private boolean password;
    private char passwordChar = '*';
    private IntPredicate charFilter;
    private boolean insertMode;
    private boolean readOnly;
    private float scrollX;
    private Clipboard clipboard = new MemoryClipboard();
    private boolean lastKeyHandled;

    /** Creates an empty model with the cursor at position 0. */
    public InputTextModel() {
        this("");
    }

    /**
     * Creates a model with {@code initialText}. The cursor starts at the end of
     * the text, as if the field had just been filled programmatically.
     */
    public InputTextModel(String initialText) {
        setText(initialText);
    }

    // ------------------------------------------------------------------
    // Text and selection
    // ------------------------------------------------------------------

    /**
     * Replaces the buffer and moves the cursor to its end. Undo/redo history is
     * cleared and the horizontal scroll offset is reset to 0. The character
     * filter is not applied to text supplied by the application.
     */
    public void setText(String text) {
        buffer.setLength(0);
        if (text != null) {
            buffer.append(text);
        }
        cursor = buffer.length();
        anchor = cursor;
        scrollX = 0.0f;
        undoStack.clear();
        redoStack.clear();
    }

    /** Returns the current (unmasked) buffer contents. */
    public String getText() {
        return buffer.toString();
    }

    /** Returns the number of UTF-16 code units in the buffer. */
    public int length() {
        return buffer.length();
    }

    /** Returns the cursor position as a UTF-16 index (always on a code point boundary). */
    public int cursorPos() {
        return cursor;
    }

    /** Normalized selection start (the smaller of anchor and cursor). */
    public int selectionStart() {
        return Math.min(anchor, cursor);
    }

    /** Normalized selection end (the larger of anchor and cursor). */
    public int selectionEnd() {
        return Math.max(anchor, cursor);
    }

    /** Returns whether a non-empty selection exists. */
    public boolean hasSelection() {
        return anchor != cursor;
    }

    /** Returns the selected text, or an empty string when nothing is selected. */
    public String selectedText() {
        if (!hasSelection()) {
            return "";
        }
        return buffer.substring(selectionStart(), selectionEnd());
    }

    /** Collapses the selection at the current cursor position. */
    public void clearSelection() {
        anchor = cursor;
    }

    /** Selects the whole buffer (cursor at the end). */
    public void selectAll() {
        anchor = 0;
        cursor = buffer.length();
    }

    /** Moves the cursor and clears the selection. */
    public void setCursorPos(int position) {
        cursor = sanitizeIndex(position);
        anchor = cursor;
    }

    /**
     * Selects {@code start..end} and places the cursor at the end of the range.
     * The arguments may be supplied in either order. Both are clamped.
     */
    public void setSelection(int start, int end) {
        int a = sanitizeIndex(start);
        int b = sanitizeIndex(end);
        anchor = Math.min(a, b);
        cursor = Math.max(a, b);
    }

    /**
     * Returns whether the internal state is consistent: cursor and anchor are
     * in range and both sit on Unicode code point boundaries.
     */
    public boolean isValid() {
        int len = buffer.length();
        return cursor >= 0 && cursor <= len
                && anchor >= 0 && anchor <= len
                && isCodePointBoundary(cursor)
                && isCodePointBoundary(anchor);
    }

    // ------------------------------------------------------------------
    // Editing
    // ------------------------------------------------------------------

    /**
     * Inserts typed text at the cursor, replacing the selection (or one code
     * point in overwrite mode). Control characters are rejected; each remaining
     * code point must be accepted by the configured character filter.
     *
     * @return {@code true} if the buffer changed
     */
    public boolean insertText(String text) {
        if (text == null || text.isEmpty() || readOnly) {
            return false;
        }
        String filtered = filterForInput(text, false);
        return insertFiltered(filtered);
    }

    /**
     * Inserts the clipboard contents, replacing the selection. In this
     * single-line model CR/LF characters from the clipboard become spaces,
     * matching Dear ImGui's behavior.
     *
     * @return {@code true} if the buffer changed
     */
    public boolean paste() {
        if (readOnly || clipboard == null) {
            return false;
        }
        String text = clipboard.read();
        if (text == null || text.isEmpty()) {
            return false;
        }
        String filtered = filterForInput(text, true);
        return insertFiltered(filtered);
    }

    /** Copies the selection to the clipboard. Disabled in password mode. */
    public boolean copy() {
        if (password || clipboard == null || !hasSelection()) {
            return false;
        }
        clipboard.write(selectedText());
        return true;
    }

    /** Copies the selection and deletes it. Disabled in password mode. */
    public boolean cut() {
        if (readOnly || password || clipboard == null || !hasSelection()) {
            return false;
        }
        clipboard.write(selectedText());
        recordUndo();
        deleteSelection();
        return true;
    }

    /** Returns whether an undo snapshot is available. */
    public boolean canUndo() {
        return !undoStack.isEmpty();
    }

    /** Returns whether a redo snapshot is available. */
    public boolean canRedo() {
        return !redoStack.isEmpty();
    }

    /** Restores the state before the most recent edit. */
    public boolean undo() {
        if (undoStack.isEmpty()) {
            return false;
        }
        Snapshot current = snapshot();
        Snapshot previous = undoStack.pop();
        pushBounded(redoStack, current);
        restore(previous);
        return true;
    }

    /** Re-applies the most recently undone edit. */
    public boolean redo() {
        if (redoStack.isEmpty()) {
            return false;
        }
        Snapshot current = snapshot();
        Snapshot next = redoStack.pop();
        pushBounded(undoStack, current);
        restore(next);
        return true;
    }

    /** Clears the undo and redo stacks without touching the text. */
    public void clearUndoHistory() {
        undoStack.clear();
        redoStack.clear();
    }

    /**
     * Processes one key-press event.
     *
     * <p>Supported bindings: Left/Right (Ctrl for word movement), Up/Down
     * (ignored in single-line mode, as in {@code InputTextEx}), Home/End,
     * Backspace/Delete (Ctrl for whole words), Space (inserts a space),
     * Insert (toggles overwrite mode; Ctrl+Insert copies, Shift+Insert pastes),
     * Ctrl+A select-all, Ctrl+C copy, Ctrl+X cut, Ctrl+V paste, Ctrl+Z undo,
     * Ctrl+Y and Ctrl+Shift+Z redo. Enter, Escape and Tab are left to the host,
     * and Alt is currently reserved (it does not change movement).</p>
     *
     * @return {@code true} if the text buffer changed (cursor/selection-only
     *         actions return {@code false})
     */
    public boolean key(int keyCode, boolean ctrl, boolean shift, boolean alt) {
        lastKeyHandled = true;

        // Ctrl-based editing shortcuts for digits and letters.
        if ((keyCode >= KEY_0 && keyCode <= KEY_9) || (keyCode >= KEY_A && keyCode <= KEY_Z)) {
            if (!ctrl) {
                lastKeyHandled = false;
                return false;
            }
            return switch (keyCode) {
                case KEY_A -> {
                    selectAll();
                    yield false;
                }
                case KEY_C -> {
                    copy();
                    yield false;
                }
                case KEY_X -> cut();
                case KEY_V -> paste();
                case KEY_Z -> {
                    if (readOnly) {
                        yield false;
                    }
                    yield shift ? redo() : undo();
                }
                case KEY_Y -> {
                    if (readOnly) {
                        yield false;
                    }
                    yield redo();
                }
                default -> {
                    lastKeyHandled = false;
                    yield false;
                }
            };
        }

        switch (keyCode) {
            case KEY_LEFT:
                if (ctrl) {
                    moveWordLeft(shift);
                } else {
                    moveCharLeft(shift);
                }
                return false;
            case KEY_RIGHT:
                if (ctrl) {
                    moveWordRight(shift);
                } else {
                    moveCharRight(shift);
                }
                return false;
            case KEY_UP:
            case KEY_DOWN:
            case KEY_PAGE_UP:
            case KEY_PAGE_DOWN:
                // InputTextEx only routes these in multiline mode.
                lastKeyHandled = false;
                return false;
            case KEY_HOME:
                moveToBoundary(0, shift);
                return false;
            case KEY_END:
                moveToBoundary(buffer.length(), shift);
                return false;
            case KEY_INSERT:
                if (ctrl) {
                    copy();
                } else if (shift) {
                    return paste();
                } else {
                    insertMode = !insertMode;
                }
                return false;
            case KEY_DELETE:
                if (readOnly) {
                    return false;
                }
                return ctrl ? deleteWordRight() : deleteNext();
            case KEY_BACKSPACE:
                if (readOnly) {
                    return false;
                }
                return ctrl ? deleteWordLeft() : deletePrevious();
            case KEY_SPACE:
                if (ctrl || readOnly) {
                    lastKeyHandled = false;
                    return false;
                }
                return insertText(" ");
            case KEY_ENTER:
            case KEY_ESCAPE:
            case KEY_TAB:
                // Validation, cancellation and focus traversal belong to the host.
                lastKeyHandled = false;
                return false;
            default:
                lastKeyHandled = false;
                return false;
        }
    }

    /** Returns whether the most recent {@link #key} call was a recognized binding. */
    public boolean lastKeyHandled() {
        return lastKeyHandled;
    }

    // ------------------------------------------------------------------
    // Password mode and filtering
    // ------------------------------------------------------------------

    /** Enables or disables password masking of {@link #displayText()}. */
    public void setPassword(boolean password) {
        this.password = password;
    }

    public boolean isPassword() {
        return password;
    }

    /** Sets the mask glyph used by password mode (default {@code '*'}). */
    public void setPasswordChar(char passwordChar) {
        this.passwordChar = passwordChar;
    }

    public char passwordChar() {
        return passwordChar;
    }

    /** Installs a per-code-point input filter (for decimal/hex fields). */
    public void setCharFilter(IntPredicate charFilter) {
        this.charFilter = charFilter;
    }

    public IntPredicate charFilter() {
        return charFilter;
    }

    /** Enables or disables user edits (programmatic {@link #setText} still works). */
    public void setReadOnly(boolean readOnly) {
        this.readOnly = readOnly;
    }

    public boolean isReadOnly() {
        return readOnly;
    }

    public boolean isInsertMode() {
        return insertMode;
    }

    /** Toggles STB-style overwrite mode (the Insert key does this normally). */
    public void setInsertMode(boolean insertMode) {
        this.insertMode = insertMode;
    }

    // ------------------------------------------------------------------
    // Display, measurement and scrolling
    // ------------------------------------------------------------------

    /**
     * Returns the text to draw. In password mode this is one mask glyph per
     * Unicode code point, hiding both content and word boundaries.
     */
    public String displayText() {
        if (!password) {
            return buffer.toString();
        }
        int count = buffer.codePointCount(0, buffer.length());
        if (count == 0) {
            return "";
        }
        char[] masked = new char[count];
        java.util.Arrays.fill(masked, passwordChar);
        return new String(masked);
    }

    /** Measures the displayed string with the supplied character metrics. */
    public float textWidth(CharMetrics metrics) {
        return measure(displayText(), Objects.requireNonNull(metrics, "metrics"));
    }

    /** Measures the displayed text from its start to the cursor. */
    public float cursorX(CharMetrics metrics) {
        Objects.requireNonNull(metrics, "metrics");
        String shown = displayText();
        int index = password ? buffer.codePointCount(0, cursor) : cursor;
        return measure(shown.substring(0, index), metrics);
    }

    /** Current horizontal scroll offset, in pixels. Never negative. */
    public float scrollX() {
        return scrollX;
    }

    /** Sets the horizontal scroll offset. Negative values are clamped to 0. */
    public void setScrollX(float scrollX) {
        this.scrollX = Math.max(0.0f, scrollX);
    }

    /**
     * Scrolls horizontally so that the cursor stays visible, using the same
     * rules as Dear ImGui's single-line {@code InputTextEx}:
     * the offset moves by 25% of the visible width and is truncated to whole
     * pixels. The cursor is left with a small amount of trailing room instead
     * of being pinned to the edge.
     *
     * @param visibleWidth visible content width in pixels
     * @param metrics      character advance callback
     * @return the resulting {@link #scrollX()}
     */
    public float ensureCursorVisible(float visibleWidth, CharMetrics metrics) {
        float width = Math.max(0.0f, visibleWidth);
        float x = cursorX(metrics);
        float increment = width * 0.25f;
        if (x < scrollX) {
            scrollX = Math.max(0.0f, (float) Math.floor(x - increment));
        } else if (x - width >= scrollX) {
            scrollX = (float) Math.floor(x - width + increment);
        }
        if (scrollX < 0.0f) {
            scrollX = 0.0f;
        }
        return scrollX;
    }

    /** Largest useful scroll offset for the displayed text and a visible width. */
    public float maxScrollX(float visibleWidth, CharMetrics metrics) {
        return Math.max(0.0f, textWidth(metrics) - Math.max(0.0f, visibleWidth));
    }

    // ------------------------------------------------------------------
    // Clipboard access
    // ------------------------------------------------------------------

    /** Installs a clipboard hook. A {@code null} hook disables copy/cut/paste. */
    public void setClipboard(Clipboard clipboard) {
        this.clipboard = clipboard;
    }

    public Clipboard clipboard() {
        return clipboard;
    }

    // ------------------------------------------------------------------
    // Internals
    // ------------------------------------------------------------------

    private boolean insertFiltered(String text) {
        if (text.isEmpty()) {
            return false;
        }
        recordUndo();
        if (insertMode && !hasSelection() && cursor < buffer.length()) {
            int end = nextIndex(cursor);
            buffer.delete(cursor, end);
        } else {
            deleteSelection();
        }
        int at = cursor;
        buffer.insert(at, text);
        cursor = at + text.length();
        anchor = cursor;
        return true;
    }

    private boolean deletePrevious() {
        if (hasSelection()) {
            recordUndo();
            deleteSelection();
            return true;
        }
        if (cursor <= 0) {
            return false;
        }
        int start = previousIndex(cursor);
        recordUndo();
        buffer.delete(start, cursor);
        cursor = start;
        anchor = start;
        return true;
    }

    private boolean deleteNext() {
        if (hasSelection()) {
            recordUndo();
            deleteSelection();
            return true;
        }
        if (cursor >= buffer.length()) {
            return false;
        }
        int end = nextIndex(cursor);
        recordUndo();
        buffer.delete(cursor, end);
        anchor = cursor;
        return true;
    }

    private boolean deleteWordLeft() {
        if (hasSelection()) {
            recordUndo();
            deleteSelection();
            return true;
        }
        int start = wordLeft(cursor);
        if (start >= cursor) {
            return false;
        }
        recordUndo();
        buffer.delete(start, cursor);
        cursor = start;
        anchor = start;
        return true;
    }

    private boolean deleteWordRight() {
        if (hasSelection()) {
            recordUndo();
            deleteSelection();
            return true;
        }
        int end = wordRight(cursor);
        if (end <= cursor) {
            return false;
        }
        recordUndo();
        buffer.delete(cursor, end);
        anchor = cursor;
        return true;
    }

    private void deleteSelection() {
        int start = selectionStart();
        int end = selectionEnd();
        buffer.delete(start, end);
        cursor = start;
        anchor = start;
    }

    private void moveCharLeft(boolean shift) {
        if (shift) {
            if (!hasSelection()) {
                anchor = cursor;
            }
            cursor = previousIndex(cursor);
        } else {
            cursor = hasSelection() ? selectionStart() : previousIndex(cursor);
            anchor = cursor;
        }
    }

    private void moveCharRight(boolean shift) {
        if (shift) {
            if (!hasSelection()) {
                anchor = cursor;
            }
            cursor = nextIndex(cursor);
        } else {
            cursor = hasSelection() ? selectionEnd() : nextIndex(cursor);
            anchor = cursor;
        }
    }

    private void moveWordLeft(boolean shift) {
        if (shift) {
            if (!hasSelection()) {
                anchor = cursor;
            }
            cursor = wordLeft(cursor);
        } else {
            cursor = hasSelection() ? selectionStart() : wordLeft(cursor);
            anchor = cursor;
        }
    }

    private void moveWordRight(boolean shift) {
        if (shift) {
            if (!hasSelection()) {
                anchor = cursor;
            }
            cursor = wordRight(cursor);
        } else {
            cursor = hasSelection() ? selectionEnd() : wordRight(cursor);
            anchor = cursor;
        }
    }

    private void moveToBoundary(int position, boolean shift) {
        if (shift) {
            if (!hasSelection()) {
                anchor = cursor;
            }
            cursor = position;
        } else {
            cursor = position;
            anchor = position;
        }
    }

    /**
     * Port of ImGui's {@code STB_TEXTEDIT_MOVEWORDLEFT_IMPL}: move at least one
     * code point, then keep moving until a word boundary is found.
     */
    private int wordLeft(int from) {
        if (password) {
            // ImGui disables word boundaries in password mode so that Ctrl+Arrow
            // cannot leak the structure of the secret.
            return 0;
        }
        int index = previousIndex(from);
        while (index > 0 && !isWordBoundaryFromRight(index)) {
            index = previousIndex(index);
        }
        return Math.max(0, index);
    }

    /**
     * Port of ImGui's Windows {@code STB_TEXTEDIT_MOVEWORDRIGHT_IMPL}: move at
     * least one code point, then until the next boundary.
     */
    private int wordRight(int from) {
        if (password) {
            return buffer.length();
        }
        int length = buffer.length();
        int index = nextIndex(from);
        while (index < length && !isWordBoundaryFromRight(index)) {
            index = nextIndex(index);
        }
        return Math.min(index, length);
    }

    /** ImGui's {@code is_word_boundary_from_right()}. */
    private boolean isWordBoundaryFromRight(int index) {
        if (index <= 0 || index >= buffer.length()) {
            return false;
        }
        int current = buffer.codePointAt(index);
        int previous = buffer.codePointBefore(index);
        boolean currentBlank = isBlank(current);
        boolean previousBlank = isBlank(previous);
        boolean currentSeparator = isSeparator(current);
        boolean previousSeparator = isSeparator(previous);
        return ((previousBlank || previousSeparator) && !(currentSeparator || currentBlank))
                || (currentSeparator && !previousSeparator);
    }

    private static boolean isBlank(int codePoint) {
        return codePoint == ' ' || codePoint == '\t' || codePoint == 0x3000;
    }

    /** ImGui's {@code ImCharIsSeparatorW()} list. */
    private static boolean isSeparator(int codePoint) {
        return switch (codePoint) {
            case ',', 0x3001, '.', 0x3002, ';', 0xFF1B,
                    '(', 0xFF08, ')', 0xFF09, '{', 0xFF5B, '}', 0xFF5D,
                    '[', 0x300C, ']', 0x300D, '|', 0xFF5C, '!', 0xFF01,
                    '\\', 0xFFE5, '/', 0x30FB, 0xFF0F, '\n', '\r' -> true;
            default -> false;
        };
    }

    /**
     * Filters input the way {@code InputTextFilterCharacter()} does, minus the
     * named ImGui flags: controls, DEL and private-use characters are dropped,
     * clipboard newlines become spaces, and the custom predicate decides the
     * rest. Unpaired surrogates are rejected as well.
     */
    private String filterForInput(String raw, boolean fromClipboard) {
        StringBuilder out = new StringBuilder(raw.length());
        for (int i = 0; i < raw.length(); ) {
            int codePoint = raw.codePointAt(i);
            i += Character.charCount(codePoint);
            if (fromClipboard && (codePoint == '\r' || codePoint == '\n')) {
                codePoint = ' ';
            }
            if (codePoint < 0x20 || codePoint == 0x7F) {
                continue;
            }
            if (codePoint >= Character.MIN_SURROGATE && codePoint <= Character.MAX_SURROGATE) {
                continue;
            }
            if (codePoint >= 0xE000 && codePoint <= 0xF8FF) {
                continue;
            }
            if (charFilter != null && !charFilter.test(codePoint)) {
                continue;
            }
            out.appendCodePoint(codePoint);
        }
        return out.toString();
    }

    private static float measure(String text, CharMetrics metrics) {
        float width = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            width += metrics.advance(text.charAt(i));
        }
        return width;
    }

    private int nextIndex(int index) {
        if (index >= buffer.length()) {
            return buffer.length();
        }
        return index + Character.charCount(buffer.codePointAt(index));
    }

    private int previousIndex(int index) {
        if (index <= 0) {
            return 0;
        }
        return index - Character.charCount(buffer.codePointBefore(index));
    }

    private int sanitizeIndex(int index) {
        int length = buffer.length();
        int clamped = Math.max(0, Math.min(index, length));
        if (clamped > 0 && clamped < length
                && Character.isLowSurrogate(buffer.charAt(clamped))
                && Character.isHighSurrogate(buffer.charAt(clamped - 1))) {
            clamped--;
        }
        return clamped;
    }

    private boolean isCodePointBoundary(int index) {
        return index <= 0 || index >= buffer.length()
                || !(Character.isLowSurrogate(buffer.charAt(index))
                && Character.isHighSurrogate(buffer.charAt(index - 1)));
    }

    private Snapshot snapshot() {
        return new Snapshot(buffer.toString(), cursor, anchor);
    }

    private void recordUndo() {
        pushBounded(undoStack, snapshot());
        redoStack.clear();
    }

    private static void pushBounded(ArrayDeque<Snapshot> stack, Snapshot snapshot) {
        stack.push(snapshot);
        while (stack.size() > MAX_UNDO_HISTORY) {
            stack.removeLast();
        }
    }

    private void restore(Snapshot snapshot) {
        buffer.setLength(0);
        buffer.append(snapshot.text());
        cursor = sanitizeIndex(snapshot.cursor());
        anchor = sanitizeIndex(snapshot.anchor());
    }

    /** Simple in-memory default clipboard used when no host hook is installed. */
    private static final class MemoryClipboard implements Clipboard {
        private String value = "";

        @Override
        public String read() {
            return value;
        }

        @Override
        public void write(String text) {
            value = text == null ? "" : text;
        }
    }
}
