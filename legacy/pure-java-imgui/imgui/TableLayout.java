package com.noimgui.imgui;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Standalone port of the core table layout math from
 * {@code reference/imgui-java/include/imgui/imgui_tables.cpp}
 * ({@code TableUpdateLayout}, {@code TableNextRow}, {@code TableBeginRow},
 * {@code TableEndRow}, {@code TableGetCellBgRect} and the clipping parts of
 * {@code TableBeginCell}).
 *
 * <p>The class only computes geometry. It does not own a window or a draw list,
 * and it does not measure text or widget sizes. Coordinates are table-local:
 * {@code (0, 0)} is the top-left corner of the table content region. The
 * horizontal axis is limited to the width passed to the constructor; the
 * vertical axis grows with the submitted rows.</p>
 *
 * <p>Widths passed to {@link #setupColumn(float, int, float)} are inner widths,
 * exactly like {@code ImGui::TableSetupColumn()}: padding and spacing are added
 * by the layout. For example a fixed column of {@code 100} occupies
 * {@code 100 + cellSpacingX1 + cellSpacingX2 + cellPaddingX * 2} pixels.</p>
 *
 * <p>Typical usage:</p>
 * <pre>{@code
 * TableLayout table = new TableLayout(3, 600.0f);
 * table.setCellStyle(0.0f, 0.0f, 0.0f, 0.0f); // optional, compact style
 * table.setupColumn(120.0f, TableLayout.WIDTH_FIXED, 0.0f);
 * table.setupColumn(0.0f, TableLayout.WIDTH_STRETCH, 1.0f);
 * table.setupColumn(0.0f, TableLayout.WIDTH_STRETCH, 2.0f);
 * table.beginRow(20.0f);
 * for (int i = 0; i < 3; i++) {
 *     table.nextColumn();
 *     float x = table.columnX();
 *     TableLayout.CellClip clip = table.cellClip();
 * }
 * }</pre>
 */
public final class TableLayout {
    /** Fixed sizing policy. A non-positive width means "auto" (content fitted). */
    public static final int WIDTH_FIXED = 1;
    /** Stretch sizing policy. Columns share the remaining width by weight. */
    public static final int WIDTH_STRETCH = 1 << 1;
    /** Fixed sizing policy whose width is taken from the measured auto width. */
    public static final int WIDTH_AUTO = 1 << 2;

    /** Regular row. */
    public static final int ROW_NONE = 0;
    /** Header row. Top header rows are accumulated in {@link #headerRowHeight()}. */
    public static final int ROW_HEADER = 1;

    private static final float ROUNDING_EPSILON = 0.01f;

    private final int columnsCount;
    private final float availableWidth;

    private final int[] columnFlags;
    private final float[] widthRequests;
    private final float[] stretchWeights;
    private final float[] autoWidths;

    private final float[] widthGiven;
    private final float[] columnMinX;
    private final float[] columnMaxX;
    private final float[] workMinX;
    private final float[] workMaxX;

    private final List<Row> rows = new ArrayList<>();

    private int declaredColumns;
    private boolean layoutValid;
    private boolean layoutLocked;
    private float columnsGivenWidth;

    private float minColumnWidth = 1.0f;
    private float cellPaddingX;
    private float cellPaddingY = 2.0f;
    private float cellSpacingX1;
    private float cellSpacingX2;
    private float outerPaddingX;

    private int freezeColumnsRequest;
    private int freezeColumnsCount;
    private int freezeRowsRequest;
    private int freezeRowsCount;
    private float scrollX;
    private float scrollY;

    private boolean insideRow;
    private int currentColumn = -1;

    /**
     * Creates a layout for {@code columns} columns.
     *
     * @param columns        number of columns, must be positive
     * @param availableWidth width of the table content region, clamped to at least 1
     */
    public TableLayout(int columns, float availableWidth) {
        if (columns <= 0) {
            throw new IllegalArgumentException("columns must be positive: " + columns);
        }
        if (Float.isNaN(availableWidth)) {
            throw new IllegalArgumentException("availableWidth must not be NaN");
        }
        this.columnsCount = columns;
        this.availableWidth = Math.max(1.0f, availableWidth);

        this.columnFlags = new int[columns];
        this.widthRequests = new float[columns];
        this.stretchWeights = new float[columns];
        this.autoWidths = new float[columns];
        this.widthGiven = new float[columns];
        this.columnMinX = new float[columns];
        this.columnMaxX = new float[columns];
        this.workMinX = new float[columns];
        this.workMaxX = new float[columns];

        // ImGui's default table sizing policy is SizingStretchSame: columns
        // that were not explicitly setup behave as stretch columns of weight 1.
        Arrays.fill(columnFlags, WIDTH_STRETCH);
        Arrays.fill(widthRequests, -1.0f);
        Arrays.fill(stretchWeights, 1.0f);
    }

    // ------------------------------------------------------------------
    // Configuration
    // ------------------------------------------------------------------

    /**
     * Declares the next column. Must be called in column order and before the
     * first row. Missing declarations fall back to a stretch column of weight 1.
     *
     * @param width  inner width for {@link #WIDTH_FIXED}, a measurement hint for
     *               {@link #WIDTH_AUTO}, and an optional weight fallback for
     *               {@link #WIDTH_STRETCH}. Non-positive means automatic.
     * @param flags  one of {@link #WIDTH_FIXED}, {@link #WIDTH_STRETCH},
     *               {@link #WIDTH_AUTO}; zero defaults to fixed/auto
     * @param weight stretch weight for {@link #WIDTH_STRETCH}; non-positive falls
     *               back to {@code width} and then to 1
     */
    public void setupColumn(float width, int flags, float weight) {
        if (layoutLocked) {
            throw new IllegalStateException("setupColumn() must be called before the first row");
        }
        if (declaredColumns >= columnsCount) {
            throw new IllegalStateException("setupColumn() called more than " + columnsCount + " times");
        }

        int mode = flags & (WIDTH_FIXED | WIDTH_STRETCH | WIDTH_AUTO);
        if (mode == 0) {
            mode = (width > 0.0f) ? WIDTH_FIXED : WIDTH_AUTO;
        } else if ((mode & (mode - 1)) != 0) {
            throw new IllegalArgumentException("Only one width mode may be used: " + flags);
        }

        int index = declaredColumns;
        if ((mode & WIDTH_STRETCH) != 0) {
            float effectiveWeight = weight > 0.0f ? weight : (width > 0.0f ? width : 1.0f);
            stretchWeights[index] = effectiveWeight;
            widthRequests[index] = -1.0f;
            autoWidths[index] = minColumnWidth;
        } else if ((mode & WIDTH_AUTO) != 0 || width <= 0.0f) {
            mode |= WIDTH_AUTO;
            autoWidths[index] = width > 0.0f ? width : minColumnWidth;
            widthRequests[index] = -1.0f;
        } else {
            widthRequests[index] = width;
            autoWidths[index] = width;
        }

        columnFlags[index] = mode;
        declaredColumns++;
        layoutValid = false;
    }

    /** Convenience overload: zero weight, so fixed widths and auto columns work as declared. */
    public void setupColumn(float width, int flags) {
        setupColumn(width, flags, 0.0f);
    }

    /**
     * Supplies the measured content width for a {@link #WIDTH_AUTO} column
     * (or for a fixed column declared with a non-positive width).
     */
    public void setColumnAutoWidth(int column, float width) {
        checkColumn(column);
        if (layoutLocked) {
            throw new IllegalStateException("setColumnAutoWidth() must be called before the first row");
        }
        autoWidths[column] = Math.max(minColumnWidth, width);
        layoutValid = false;
    }

    /**
     * Sets cell padding and spacing values equivalent to the values computed by
     * {@code BeginTable()} from {@code ImGuiStyle::CellPadding} and the border
     * flags.
     *
     * @param paddingX     inner padding on both sides of a cell ({@code CellPaddingX})
     * @param spacingX1    spacing before the cell ({@code CellSpacingX1})
     * @param spacingX2    spacing after the cell ({@code CellSpacingX2})
     * @param outerPadding outer padding before the first / after the last column
     */
    public void setCellStyle(float paddingX, float spacingX1, float spacingX2, float outerPaddingX) {
        if (layoutLocked) {
            throw new IllegalStateException("setCellStyle() must be called before the first row");
        }
        if (paddingX < 0.0f || spacingX1 < 0.0f || spacingX2 < 0.0f || outerPaddingX < 0.0f) {
            throw new IllegalArgumentException("Padding and spacing must be non-negative");
        }
        this.cellPaddingX = paddingX;
        this.cellSpacingX1 = spacingX1;
        this.cellSpacingX2 = spacingX2;
        this.outerPaddingX = outerPaddingX;
        layoutValid = false;
    }

    /** Sets vertical cell padding used by row height defaults. */
    public void setCellPaddingY(float paddingY) {
        if (layoutLocked) {
            throw new IllegalStateException("setCellPaddingY() must be called before the first row");
        }
        if (paddingY < 0.0f) {
            throw new IllegalArgumentException("paddingY must be non-negative");
        }
        this.cellPaddingY = paddingY;
    }

    /** Sets the lower bound applied to every computed column width (ImGui: MinColumnWidth). */
    public void setMinColumnWidth(float width) {
        if (layoutLocked) {
            throw new IllegalStateException("setMinColumnWidth() must be called before the first row");
        }
        if (!(width > 0.0f)) {
            throw new IllegalArgumentException("minColumnWidth must be positive");
        }
        this.minColumnWidth = width;
        layoutValid = false;
    }

    /**
     * Mirror of {@code ImGui::TableSetupScrollFreeze(columns, rows)}. As in
     * ImGui, freezing only becomes active once the corresponding scroll offset
     * is non-zero (see {@link #setScroll(float, float)}).
     *
     * @param columns number of leading frozen columns
     * @param rows    number of leading frozen rows
     */
    public void setupScrollFreeze(int columns, int rows) {
        if (layoutLocked) {
            throw new IllegalStateException("setupScrollFreeze() must be called before the first row");
        }
        this.freezeColumnsRequest = Math.max(0, Math.min(columns, columnsCount));
        this.freezeRowsRequest = Math.max(0, rows);
        updateActiveFreezeCounts();
    }

    /**
     * Updates the scroll offsets. Non-zero offsets activate the freeze requests
     * configured by {@link #setupScrollFreeze(int, int)}.
     */
    public void setScroll(float scrollX, float scrollY) {
        if (Float.isNaN(scrollX) || Float.isNaN(scrollY)) {
            throw new IllegalArgumentException("Scroll offsets must not be NaN");
        }
        this.scrollX = Math.max(0.0f, scrollX);
        this.scrollY = Math.max(0.0f, scrollY);
        updateActiveFreezeCounts();
    }

    private void updateActiveFreezeCounts() {
        freezeColumnsCount = scrollX != 0.0f ? freezeColumnsRequest : 0;
        freezeRowsCount = scrollY != 0.0f ? freezeRowsRequest : 0;
    }

    // ------------------------------------------------------------------
    // Column layout (TableUpdateLayout parts 1-6)
    // ------------------------------------------------------------------

    private void ensureLayout() {
        if (layoutValid) {
            return;
        }

        final int count = columnsCount;
        float sumWidthRequests = 0.0f;
        float sumWeights = 0.0f;

        for (int i = 0; i < count; i++) {
            if ((columnFlags[i] & WIDTH_STRETCH) != 0) {
                float weight = stretchWeights[i] > 0.0f ? stretchWeights[i] : 1.0f;
                stretchWeights[i] = weight;
                sumWeights += weight;
            } else {
                float request;
                if ((columnFlags[i] & WIDTH_AUTO) != 0 || widthRequests[i] <= 0.0f) {
                    request = Math.max(autoWidths[i], minColumnWidth);
                } else {
                    request = widthRequests[i];
                }
                widthRequests[i] = request;
                sumWidthRequests += request;
            }
            // ImGui adds padding for every enabled column, fixed or stretch.
            sumWidthRequests += cellPaddingX * 2.0f;
        }

        final float widthSpacings = outerPaddingX * 2.0f
                + (cellSpacingX1 + cellSpacingX2) * (count - 1);
        final float widthAvailForStretched = availableWidth - widthSpacings - sumWidthRequests;
        float widthRemainingForStretched = widthAvailForStretched;

        columnsGivenWidth = widthSpacings + (cellPaddingX * 2.0f) * count;

        for (int i = 0; i < count; i++) {
            if ((columnFlags[i] & WIDTH_STRETCH) != 0) {
                float ratio = sumWeights > 0.0f ? stretchWeights[i] / sumWeights : 0.0f;
                float requested = (float) Math.floor(
                        Math.max(widthAvailForStretched * ratio, minColumnWidth) + ROUNDING_EPSILON);
                widthRequests[i] = requested;
                widthRemainingForStretched -= requested;
            }

            widthGiven[i] = (float) Math.floor(Math.max(widthRequests[i], minColumnWidth));
            columnsGivenWidth += widthGiven[i];
        }

        // Part 5: distribute rounding remainder right-to-left, like ImGui does.
        if (widthRemainingForStretched >= 1.0f && sumWeights > 0.0f) {
            for (int i = count - 1; i >= 0 && widthRemainingForStretched >= 1.0f; i--) {
                if ((columnFlags[i] & WIDTH_STRETCH) == 0) {
                    continue;
                }
                widthRequests[i] += 1.0f;
                widthGiven[i] += 1.0f;
                columnsGivenWidth += 1.0f;
                widthRemainingForStretched -= 1.0f;
            }
        }

        // Part 6: lock final x offsets.
        float offsetX = outerPaddingX - cellSpacingX1;
        for (int i = 0; i < count; i++) {
            columnMinX[i] = offsetX;
            columnMaxX[i] = offsetX + widthGiven[i]
                    + cellSpacingX1 + cellSpacingX2 + cellPaddingX * 2.0f;
            workMinX[i] = columnMinX[i] + cellPaddingX + cellSpacingX1;
            workMaxX[i] = columnMaxX[i] - cellPaddingX - cellSpacingX2;
            offsetX = columnMaxX[i];
        }

        layoutValid = true;
    }

    // ------------------------------------------------------------------
    // Rows (TableNextRow / TableBeginRow / TableEndRow)
    // ------------------------------------------------------------------

    /**
     * Starts a new row. If a row is currently open it is implicitly finished.
     * The row height is at least {@code minHeight} and at least
     * {@code cellPaddingY * 2} (ImGui adds top and bottom cell padding before
     * honoring the user-provided minimum).
     */
    public void beginRow(float minHeight) {
        beginRow(minHeight, ROW_NONE);
    }

    /**
     * Starts a new row with flags.
     *
     * @param minHeight minimum row height, including implicit cell padding
     * @param flags     {@link #ROW_NONE} or {@link #ROW_HEADER}
     */
    public void beginRow(float minHeight, int flags) {
        if (Float.isNaN(minHeight)) {
            throw new IllegalArgumentException("minHeight must not be NaN");
        }
        ensureLayout();
        if (insideRow) {
            insideRow = false;
            currentColumn = -1;
        }

        float top = rows.isEmpty() ? 0.0f : rows.get(rows.size() - 1).bottom();
        float height = Math.max(minHeight, cellPaddingY * 2.0f);
        Row row = new Row(rows.size(), flags, top, height);
        rows.add(row);

        insideRow = true;
        currentColumn = -1;
        layoutLocked = true;
    }

    /** Starts a header row. */
    public void beginHeaderRow(float minHeight) {
        beginRow(minHeight, ROW_HEADER);
    }

    /** Finishes the current row. The measured height is kept. */
    public void endRow() {
        if (!insideRow) {
            return;
        }
        insideRow = false;
        currentColumn = -1;
    }

    /**
     * Reports the height of the content submitted to the current row, as
     * {@code TableEndCell()} does with {@code window->DC.CursorMaxPos.y}.
     * The value includes the top and bottom cell padding.
     */
    public void addCellHeight(float contentHeight) {
        if (!insideRow || rows.isEmpty()) {
            throw new IllegalStateException("addCellHeight() requires an active row");
        }
        if (contentHeight < 0.0f || Float.isNaN(contentHeight)) {
            throw new IllegalArgumentException("contentHeight must be non-negative");
        }
        Row row = rows.get(rows.size() - 1);
        float required = cellPaddingY * 2.0f + contentHeight;
        row.height = Math.max(row.height, required);
    }

    // ------------------------------------------------------------------
    // Column / cell navigation
    // ------------------------------------------------------------------

    /**
     * Advances to the next cell. Wraps to the first column of a new row after
     * the last column, mirroring {@code ImGui::TableNextColumn()}.
     *
     * @return true when the current cell intersects the visible table area
     */
    public boolean nextColumn() {
        if (!insideRow || currentColumn + 1 >= columnsCount) {
            beginRow(0.0f);
        }
        currentColumn++;
        return isCurrentCellVisible();
    }

    /**
     * Enters a specific column of the current row, creating a row if needed.
     *
     * @return true when the cell intersects the visible table area
     */
    public boolean setColumn(int column) {
        checkColumn(column);
        if (!insideRow) {
            beginRow(0.0f);
        }
        currentColumn = column;
        return isCurrentCellVisible();
    }

    private boolean isCurrentCellVisible() {
        Row row = activeRow();
        if (row == null || currentColumn < 0) {
            return false;
        }
        CellClip clip = computeCellClip(currentColumn, row);
        return !clip.isEmpty();
    }

    // ------------------------------------------------------------------
    // Queries
    // ------------------------------------------------------------------

    /** Content x of the current column, in table-local coordinates. */
    public float columnX() {
        return currentColumn >= 0 ? columnX(currentColumn) : 0.0f;
    }

    /** Content x of a column, in table-local coordinates (scroll applied). */
    public float columnX(int column) {
        checkColumn(column);
        ensureLayout();
        return renderWorkMinX(column);
    }

    /** Right edge of a column's cell rect in table-local coordinates (scroll applied). */
    public float columnRight(int column) {
        checkColumn(column);
        ensureLayout();
        return renderColumnMaxX(column);
    }

    /** Inner width given to a column, excluding padding and spacing. */
    public float columnWidth() {
        return currentColumn >= 0 ? columnWidth(currentColumn) : 0.0f;
    }

    /** Inner width given to a column, excluding padding and spacing. */
    public float columnWidth(int column) {
        checkColumn(column);
        ensureLayout();
        return widthGiven[column];
    }

    /** Top y of the current row, in table-local coordinates (scroll/freeze applied). */
    public float rowY() {
        Row row = activeRowOrLast();
        return row != null ? renderRowTop(row) : 0.0f;
    }

    /** Top y of a row, in table-local coordinates (scroll/freeze applied). */
    public float rowY(int rowIndex) {
        return renderRowTop(getRow(rowIndex));
    }

    /** Height of the current row, or of the last row when no row is active. */
    public float rowHeight() {
        Row row = activeRowOrLast();
        return row != null ? row.height : 0.0f;
    }

    /** Height of a specific row. */
    public float rowHeight(int rowIndex) {
        return getRow(rowIndex).height;
    }

    /** Total table height, rounded up like {@code ImCeil(table->RowPosY2)}. */
    public float tableHeight() {
        if (rows.isEmpty()) {
            return 0.0f;
        }
        Row last = rows.get(rows.size() - 1);
        return (float) Math.ceil(last.bottom());
    }

    /** Sum of all column widths including padding and spacing (ImGui: ColumnsGivenWidth). */
    public float tableWidth() {
        ensureLayout();
        return columnsGivenWidth;
    }

    /** Combined height of consecutive header rows starting at row 0. */
    public float headerRowHeight() {
        float total = 0.0f;
        for (Row row : rows) {
            if ((row.flags & ROW_HEADER) == 0) {
                break;
            }
            total += row.height;
        }
        return total;
    }

    /** True when the current row was started with {@link #ROW_HEADER}. */
    public boolean isHeaderRow() {
        Row row = activeRow();
        return row != null && (row.flags & ROW_HEADER) != 0;
    }

    /** Whether a row is currently open. */
    public boolean isInsideRow() {
        return insideRow;
    }

    /** Current column index, or -1 before the first cell of a row. */
    public int columnIndex() {
        return currentColumn;
    }

    /** Index of the active row, or -1 before the first row. */
    public int rowIndex() {
        return rows.isEmpty() ? -1 : rows.size() - 1;
    }

    /** Number of rows submitted so far (including the active one). */
    public int rowCount() {
        return rows.size();
    }

    public int columnCount() {
        return columnsCount;
    }

    public float availableWidth() {
        return availableWidth;
    }

    public float minColumnWidth() {
        return minColumnWidth;
    }

    public float scrollX() {
        return scrollX;
    }

    public float scrollY() {
        return scrollY;
    }

    /** Active frozen column count (non-zero only while {@link #scrollX()} is non-zero). */
    public int frozenColumnCount() {
        return freezeColumnsCount;
    }

    /** Active frozen row count (non-zero only while {@link #scrollY()} is non-zero). */
    public int frozenRowCount() {
        return freezeRowsCount;
    }

    /** Requested frozen column count from {@link #setupScrollFreeze(int, int)}. */
    public int frozenColumnRequest() {
        return freezeColumnsRequest;
    }

    /** Requested frozen row count from {@link #setupScrollFreeze(int, int)}. */
    public int frozenRowRequest() {
        return freezeRowsRequest;
    }

    // ------------------------------------------------------------------
    // Clipping (column ClipRect + per-cell row bounds)
    // ------------------------------------------------------------------

    /**
     * Clip rectangle of the current cell. The horizontal bounds are the column
     * clip rect from {@code TableUpdateLayout}, shifted by the scroll offset and
     * clipped to the visible table width and to the frozen-column boundary. The
     * vertical bounds are clipped to the row and to the frozen-row boundary.
     */
    public CellClip cellClip() {
        Row row = activeRow();
        if (row == null || currentColumn < 0) {
            throw new IllegalStateException("cellClip() requires an active cell");
        }
        ensureLayout();
        return computeCellClip(currentColumn, row);
    }

    /** Clip rectangle for an arbitrary column/row pair. */
    public CellClip cellClip(int column, int rowIndex) {
        checkColumn(column);
        ensureLayout();
        return computeCellClip(column, getRow(rowIndex));
    }

    private CellClip computeCellClip(int column, Row row) {
        float minX = renderColumnMinX(column);
        float maxX = renderColumnMaxX(column);

        float hostMinX = 0.0f;
        if (freezeColumnsCount > 0 && column >= freezeColumnsCount) {
            // Unfrozen columns are clipped below the frozen column strip.
            hostMinX = Math.max(hostMinX, columnMaxX[freezeColumnsCount - 1]);
        }
        minX = Math.max(minX, hostMinX);
        maxX = Math.max(minX, Math.min(maxX, availableWidth));

        float rowTop = renderRowTop(row);
        float rowBottom = rowTop + row.height;
        float hostMinY = 0.0f;
        if (freezeRowsCount > 0 && row.index >= freezeRowsCount) {
            // Unfrozen rows are clipped below the frozen row strip.
            hostMinY = frozenRowsHeight();
        }
        float minY = Math.max(rowTop, hostMinY);
        float maxY = Math.max(minY, rowBottom);

        return new CellClip(minX, minY, maxX, maxY);
    }

    // ------------------------------------------------------------------
    // Internal helpers
    // ------------------------------------------------------------------

    private float renderColumnMinX(int column) {
        float x = columnMinX[column];
        return isFrozenColumn(column) ? x : x - scrollX;
    }

    private float renderColumnMaxX(int column) {
        float x = columnMaxX[column];
        return isFrozenColumn(column) ? x : x - scrollX;
    }

    private float renderWorkMinX(int column) {
        float x = workMinX[column];
        return isFrozenColumn(column) ? x : x - scrollX;
    }

    private boolean isFrozenColumn(int column) {
        return freezeColumnsCount > 0 && column < freezeColumnsCount;
    }

    private float renderRowTop(Row row) {
        if (freezeRowsCount > 0 && row.index < freezeRowsCount) {
            return row.top;
        }
        return row.top - scrollY;
    }

    private float frozenRowsHeight() {
        if (freezeRowsCount <= 0) {
            return 0.0f;
        }
        float height = 0.0f;
        for (Row row : rows) {
            if (row.index >= freezeRowsCount) {
                break;
            }
            height = Math.max(height, row.bottom());
        }
        return height;
    }

    private Row activeRow() {
        if (!insideRow || rows.isEmpty()) {
            return null;
        }
        return rows.get(rows.size() - 1);
    }

    private Row activeRowOrLast() {
        return rows.isEmpty() ? null : rows.get(rows.size() - 1);
    }

    private Row getRow(int rowIndex) {
        if (rowIndex < 0 || rowIndex >= rows.size()) {
            throw new IndexOutOfBoundsException("rowIndex out of range: " + rowIndex);
        }
        return rows.get(rowIndex);
    }

    private void checkColumn(int column) {
        if (column < 0 || column >= columnsCount) {
            throw new IndexOutOfBoundsException("column out of range: " + column);
        }
    }

    private static final class Row {
        final int index;
        final int flags;
        final float top;
        float height;

        Row(int index, int flags, float top, float height) {
            this.index = index;
            this.flags = flags;
            this.top = top;
            this.height = height;
        }

        float bottom() {
            return top + height;
        }
    }

    /**
     * Table-local clipping rectangle of a cell.
     *
     * @param minX left bound (inclusive)
     * @param minY top bound (inclusive)
     * @param maxX right bound (exclusive in ImGui clipping semantics)
     * @param maxY bottom bound (exclusive in ImGui clipping semantics)
     */
    public record CellClip(float minX, float minY, float maxX, float maxY) {
        public float width() {
            return Math.max(0.0f, maxX - minX);
        }

        public float height() {
            return Math.max(0.0f, maxY - minY);
        }

        public boolean isEmpty() {
            return width() <= 0.0f || height() <= 0.0f;
        }

        @Override
        public String toString() {
            return "CellClip[" + minX + ", " + minY + ", " + maxX + ", " + maxY + "]";
        }
    }
}
