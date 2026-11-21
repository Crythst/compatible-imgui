package com.noimgui.imgui;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Minimal OpenType/CFF (Type 2 charstring) support for fonts that do not have
 * a TrueType `glyf` table (Flashback's Material Icons font is CFF/OTF).
 *
 * <p>Only outlines and the common Type 2 operators are implemented. CFF2 and
 * CID-keyed fonts fall back to the placeholder.</p>
 */
final class CffFont {

    record Glyph(int width, int height, float bearingX, float bearingY, float advance, byte[] alpha) implements GlyphData {
    }

    private static final class Index {
        final int count;
        final long[] offsets;

        Index(int count, long[] offsets) {
            this.count = count;
            this.offsets = offsets;
        }
    }

    private final byte[] data;
    private final Index charStrings;
    private final Index globalSubrs;
    private final Index localSubrs;
    private final int unitsPerEm;
    private final int[] advance;
    private final Map<Integer, Integer> cmap = new HashMap<>();
    private final Map<Long, Glyph> cache = new HashMap<>();

    private CffFont(byte[] data, Index charStrings, Index globalSubrs, Index localSubrs,
                    int unitsPerEm, int[] advance) {
        this.data = data;
        this.charStrings = charStrings;
        this.globalSubrs = globalSubrs;
        this.localSubrs = localSubrs;
        this.unitsPerEm = unitsPerEm <= 0 ? 1000 : unitsPerEm;
        this.advance = advance;
    }

    static CffFont parse(byte[] data) {
        try {
            int cff = table(data, "CFF ");
            if (cff < 0) return null;
            int hdrSize = data[cff + 2] & 0xFF;
            Index names = readIndex(data, cff + hdrSize);
            Index topDicts = readIndex(data, (int) names.offsets[names.count]);
            if (topDicts.count == 0) return null;
            int topStart = (int) topDicts.offsets[0];
            int topEnd = (int) topDicts.offsets[1];
            Map<Integer, List<Double>> top = parseDict(data, topStart, topEnd);
            // ROS == 12 30: CID-keyed font. These need FDArray/FDSelect private
            // dicts and are intentionally not supported (caller falls back).
            if (top.containsKey(1230)) return null;

            Index strings = readIndex(data, (int) topDicts.offsets[topDicts.count]);
            int globalOffset = (int) strings.offsets[strings.count];
            Index globalSubrs = readIndex(data, globalOffset);

            List<Double> charStringsLoc = top.get(17);
            if (charStringsLoc == null || charStringsLoc.isEmpty()) return null;
            Index charStrings = readIndex(data, cff + charStringsLoc.get(0).intValue());

            Index localSubrs = null;
            List<Double> priv = top.get(18);
            if (priv != null && priv.size() >= 2) {
                int privOffset = cff + priv.get(1).intValue();
                int privSize = priv.get(0).intValue();
                Map<Integer, List<Double>> privateDict = parseDict(data, privOffset, privOffset + privSize);
                List<Double> subrs = privateDict.get(19);
                if (subrs != null && !subrs.isEmpty()) {
                    localSubrs = readIndex(data, privOffset + subrs.get(0).intValue());
                }
            }

            int head = table(data, "head");
            int maxp = table(data, "maxp");
            int hhea = table(data, "hhea");
            int hmtx = table(data, "hmtx");
            int unitsPerEm = head >= 0 ? u16(data, head + 18) : 1000;
            int numGlyphs = maxp >= 0 ? u16(data, maxp + 4) : charStrings.count;
            int numHMetrics = hhea >= 0 ? u16(data, hhea + 34) : numGlyphs;
            int[] advances = new int[Math.max(numGlyphs, charStrings.count)];
            int last = unitsPerEm / 2;
            if (hmtx >= 0) {
                for (int i = 0; i < advances.length; i++) {
                    if (i < numHMetrics) last = u16(data, hmtx + i * 4);
                    advances[i] = last;
                }
            }

            CffFont font = new CffFont(data, charStrings, globalSubrs, localSubrs, unitsPerEm, advances);
            int cmapTable = table(data, "cmap");
            if (cmapTable >= 0) font.parseCmap(cmapTable);
            return font;
        } catch (Throwable t) {
            return null;
        }
    }

    Glyph glyph(int codepoint, int pixelSize) {
        long key = ((long) codepoint << 32) | (pixelSize & 0xFFFFFFFFL);
        Glyph cached = cache.get(key);
        if (cached != null) return cached;
        Integer gid = cmap.get(codepoint);
        if (gid == null || gid < 0 || gid >= charStrings.count) return null;
        List<List<float[]>> contours = new ArrayList<>();
        Interpreter interpreter = new Interpreter(contours);
        interpreter.run((int) charStrings.offsets[gid], (int) charStrings.offsets[gid + 1]);
        contours.removeIf(CffFont::isDegenerate);
        int advanceWidth = gid < advance.length ? advance[gid] : unitsPerEm / 2;
        Glyph glyph;
        if (contours.isEmpty()) {
            // Whitespace / empty charstrings still carry a real advance.
            glyph = new Glyph(0, 0, 0, 0, advanceWidth * pixelScale(pixelSize), new byte[0]);
        } else {
            glyph = rasterize(contours, advanceWidth, pixelSize);
        }
        if (cache.size() > 4096) cache.clear();
        cache.put(key, glyph);
        return glyph;
    }

    private float pixelScale(int pixelSize) {
        return Math.max(1, pixelSize) / (float) unitsPerEm;
    }

    /** True when a contour cannot enclose any area. */
    private static boolean isDegenerate(List<float[]> contour) {
        if (contour.size() < 3) return true;
        float minX = Float.POSITIVE_INFINITY, minY = Float.POSITIVE_INFINITY;
        float maxX = Float.NEGATIVE_INFINITY, maxY = Float.NEGATIVE_INFINITY;
        for (float[] p : contour) {
            minX = Math.min(minX, p[0]);
            minY = Math.min(minY, p[1]);
            maxX = Math.max(maxX, p[0]);
            maxY = Math.max(maxY, p[1]);
        }
        return maxX - minX <= 0 || maxY - minY <= 0;
    }

    private final class Interpreter {
        final List<List<float[]>> contours;
        final List<Double> stack = new ArrayList<>();
        float x, y;
        float currentX, currentY;
        int stems;
        int depth;

        Interpreter(List<List<float[]>> contours) {
            this.contours = contours;
        }

        void run(int start, int end) {
            execute(start, end);
        }

        private void execute(int start, int end) {
            if (depth > 12) return;
            depth++;
            int i = start;
            while (i < end) {
                int b = data[i++] & 0xFF;
                if (b >= 32 || b == 28) {
                    if (b == 28) {
                        if (i + 2 > end) break;
                        stack.add((double) i16(data, i));
                        i += 2;
                    } else if (b <= 246) {
                        stack.add((double) b - 139);
                    } else if (b <= 250) {
                        if (i >= end) break;
                        stack.add((double) (b - 247) * 256 + (data[i++] & 0xFF) + 108);
                    } else if (b <= 254) {
                        if (i >= end) break;
                        stack.add((double) -(b - 251) * 256 - (data[i++] & 0xFF) - 108);
                    } else {
                        // 255: 16.16 fixed point (reserved in Type 2 but seen in the wild).
                        if (i + 4 > end) break;
                        stack.add((double) ((int) u32(data, i)) / 65536.0);
                        i += 4;
                    }
                    continue;
                }
                switch (b) {
                    case 1, 3, 18, 23 -> { // hstem / vstem / hstemhm / vstemhm
                        if ((stack.size() & 1) != 0) stack.remove(0); // leading width
                        stems += stack.size() / 2;
                        stack.clear();
                    }
                    case 19, 20 -> { // hintmask / cntrmask
                        // Operands still on the stack are implicit vstem hints; an
                        // odd count means a leading width operand.
                        if (!stack.isEmpty()) {
                            if ((stack.size() & 1) != 0) stack.remove(0);
                            stems += stack.size() / 2;
                            stack.clear();
                        }
                        i += (stems + 7) / 8;
                    }
                    case 21 -> { // rmoveto dx dy
                        if (stack.size() < 2) {
                            stack.clear();
                        } else {
                            if (stack.size() > 2) stack.remove(0); // leading width
                            move(stack.get(0), stack.get(1));
                            stack.clear();
                        }
                    }
                    case 22 -> { // hmoveto dx
                        if (stack.isEmpty()) {
                            stack.clear();
                        } else {
                            if (stack.size() > 1) stack.remove(0);
                            move(stack.get(0), 0);
                            stack.clear();
                        }
                    }
                    case 4 -> { // vmoveto dy
                        if (stack.isEmpty()) {
                            stack.clear();
                        } else {
                            if (stack.size() > 1) stack.remove(0);
                            move(0, stack.get(0));
                            stack.clear();
                        }
                    }
                    case 5 -> {
                        while (stack.size() >= 2) line(stack.remove(0), stack.remove(0));
                        stack.clear();
                    }
                    case 6, 7 -> { // hlineto / vlineto (alternating, any argc)
                        boolean horizontal = b == 6;
                        while (!stack.isEmpty()) {
                            double first = stack.remove(0);
                            line(horizontal ? first : 0, horizontal ? 0 : first);
                            horizontal = !horizontal;
                        }
                        stack.clear();
                    }
                    case 8 -> {
                        while (stack.size() >= 6) {
                            curve(stack.remove(0), stack.remove(0), stack.remove(0), stack.remove(0),
                                stack.remove(0), stack.remove(0));
                        }
                        stack.clear();
                    }
                    case 24 -> { // rcurveline: {curve}+ line
                        while (stack.size() >= 8) {
                            curve(stack.remove(0), stack.remove(0), stack.remove(0), stack.remove(0),
                                stack.remove(0), stack.remove(0));
                        }
                        if (stack.size() >= 2) line(stack.remove(0), stack.remove(0));
                        stack.clear();
                    }
                    case 25 -> { // rlinecurve: {line}+ curve
                        while (stack.size() > 6) line(stack.remove(0), stack.remove(0));
                        if (stack.size() >= 6) {
                            curve(stack.remove(0), stack.remove(0), stack.remove(0), stack.remove(0),
                                stack.remove(0), stack.remove(0));
                        }
                        stack.clear();
                    }
                    case 26 -> { // vvcurveto: dx1? {dya dxb dyb dyc}+
                        double dx1 = (stack.size() & 1) != 0 ? stack.remove(0) : 0;
                        while (stack.size() >= 4) {
                            curve(dx1, stack.remove(0), stack.remove(0), stack.remove(0), 0, stack.remove(0));
                            dx1 = 0;
                        }
                        stack.clear();
                    }
                    case 27 -> { // hhcurveto: dy1? {dxa dxb dyb dxc}+
                        double dy1 = (stack.size() & 1) != 0 ? stack.remove(0) : 0;
                        while (stack.size() >= 4) {
                            curve(stack.remove(0), dy1, stack.remove(0), stack.remove(0), stack.remove(0), 0);
                            dy1 = 0;
                        }
                        stack.clear();
                    }
                    case 30, 31 -> { // vhcurveto / hvcurveto
                        boolean horizontal = b == 31;
                        while (stack.size() >= 4) {
                            boolean extra = stack.size() == 5;
                            if (horizontal) {
                                // dx1 dx2 dy2 dy3 [dxf]
                                double dx1 = stack.remove(0);
                                double dx2 = stack.remove(0);
                                double dy2 = stack.remove(0);
                                double dy3 = stack.remove(0);
                                double dx3 = extra ? stack.remove(0) : 0;
                                curve(dx1, 0, dx2, dy2, dx3, dy3);
                            } else {
                                // dy1 dx2 dy2 dx3 [dyf]
                                double dy1 = stack.remove(0);
                                double dx2 = stack.remove(0);
                                double dy2 = stack.remove(0);
                                double dx3 = stack.remove(0);
                                double dy3 = extra ? stack.remove(0) : 0;
                                curve(0, dy1, dx2, dy2, dx3, dy3);
                            }
                            horizontal = !horizontal;
                        }
                        stack.clear();
                    }
                    case 10 -> {
                        if (!stack.isEmpty()) {
                            int index = stack.remove(stack.size() - 1).intValue() + bias(localSubrs);
                            if (localSubrs != null && index >= 0 && index < localSubrs.count) {
                                execute((int) localSubrs.offsets[index], (int) localSubrs.offsets[index + 1]);
                            }
                        }
                    }
                    case 29 -> {
                        if (!stack.isEmpty()) {
                            int index = stack.remove(stack.size() - 1).intValue() + bias(globalSubrs);
                            if (index >= 0 && index < globalSubrs.count) {
                                execute((int) globalSubrs.offsets[index], (int) globalSubrs.offsets[index + 1]);
                            }
                        }
                    }
                    case 11 -> {
                        depth--;
                        return;
                    }
                    case 14 -> {
                        stack.clear();
                        depth--;
                        return;
                    }
                    case 12 -> {
                        int op = i < end ? data[i++] & 0xFF : -1;
                        switch (op) {
                            case 34 -> { // hflex: dx1 dx2 dy2 dx3 dx4 dx5 dx6
                                if (stack.size() >= 7) {
                                    double dx1 = stack.remove(0);
                                    double dx2 = stack.remove(0);
                                    double dy2 = stack.remove(0);
                                    double dx3 = stack.remove(0);
                                    double dx4 = stack.remove(0);
                                    double dx5 = stack.remove(0);
                                    double dx6 = stack.remove(0);
                                    curve(dx1, 0, dx2, dy2, dx3, 0);
                                    curve(dx4, 0, dx5, -dy2, dx6, 0);
                                }
                                stack.clear();
                            }
                            case 35 -> { // flex
                                if (stack.size() >= 13) {
                                    double dx1 = stack.remove(0), dy1 = stack.remove(0);
                                    double dx2 = stack.remove(0), dy2 = stack.remove(0);
                                    double dx3 = stack.remove(0), dy3 = stack.remove(0);
                                    double dx4 = stack.remove(0), dy4 = stack.remove(0);
                                    double dx5 = stack.remove(0), dy5 = stack.remove(0);
                                    double dx6 = stack.remove(0), dy6 = stack.remove(0);
                                    curve(dx1, dy1, dx2, dy2, dx3, dy3);
                                    curve(dx4, dy4, dx5, dy5, dx6, dy6);
                                }
                                stack.clear();
                            }
                            case 36 -> { // flex1: dx1 dy1 .. dx5 dy5 d6
                                if (stack.size() >= 11) {
                                    double dx1 = stack.remove(0), dy1 = stack.remove(0);
                                    double dx2 = stack.remove(0), dy2 = stack.remove(0);
                                    double dx3 = stack.remove(0), dy3 = stack.remove(0);
                                    double dx4 = stack.remove(0), dy4 = stack.remove(0);
                                    double dx5 = stack.remove(0), dy5 = stack.remove(0);
                                    double d6 = stack.remove(0);
                                    double dx = dx1 + dx2 + dx3 + dx4 + dx5;
                                    double dy = dy1 + dy2 + dy3 + dy4 + dy5;
                                    double dx6;
                                    double dy6;
                                    if (Math.abs(dx) > Math.abs(dy)) {
                                        dx6 = d6;
                                        dy6 = -dy;
                                    } else {
                                        dx6 = -dx;
                                        dy6 = d6;
                                    }
                                    curve(dx1, dy1, dx2, dy2, dx3, dy3);
                                    curve(dx4, dy4, dx5, dy5, dx6, dy6);
                                }
                                stack.clear();
                            }
                            case 37 -> { // hflex1: dx1 dy1 dx2 dy2 dx3 dx4 dx5 dy5 dx6
                                if (stack.size() >= 9) {
                                    double dx1 = stack.remove(0), dy1 = stack.remove(0);
                                    double dx2 = stack.remove(0), dy2 = stack.remove(0);
                                    double dx3 = stack.remove(0);
                                    double dx4 = stack.remove(0);
                                    double dx5 = stack.remove(0), dy5 = stack.remove(0);
                                    double dx6 = stack.remove(0);
                                    curve(dx1, dy1, dx2, dy2, dx3, 0);
                                    curve(dx4, 0, dx5, dy5, dx6, -(dy1 + dy2 + dy5));
                                }
                                stack.clear();
                            }
                            default -> stack.clear();
                        }
                    }
                    default -> stack.clear();
                }
            }
            depth--;
        }

        private void move(double dx, double dy) {
            x += (float) dx;
            y += (float) dy;
            currentX = x;
            currentY = y;
            List<float[]> contour = new ArrayList<>();
            contour.add(new float[]{x, y});
            contours.add(contour);
        }

        private void line(double dx, double dy) {
            x += (float) dx;
            y += (float) dy;
            if (contours.isEmpty()) move(0, 0);
            contours.get(contours.size() - 1).add(new float[]{x, y});
        }

        private void curve(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3) {
            float x0 = x, y0 = y;
            float x1 = x0 + (float) dx1, y1 = y0 + (float) dy1;
            float x2 = x1 + (float) dx2, y2 = y1 + (float) dy2;
            float x3 = x2 + (float) dx3, y3 = y2 + (float) dy3;
            List<float[]> contour = contours.isEmpty() ? null : contours.get(contours.size() - 1);
            if (contour == null) {
                contour = new ArrayList<>();
                contour.add(new float[]{x0, y0});
                contours.add(contour);
            }
            for (int s = 1; s <= 8; s++) {
                float t = s / 8f;
                float u = 1 - t;
                float px = u * u * u * x0 + 3 * u * u * t * x1 + 3 * u * t * t * x2 + t * t * t * x3;
                float py = u * u * u * y0 + 3 * u * u * t * y1 + 3 * u * t * t * y2 + t * t * t * y3;
                contour.add(new float[]{px, py});
            }
            x = x3;
            y = y3;
        }
    }

    private Glyph rasterize(List<List<float[]>> contours, int advanceWidth, int pixelSize) {
        float scale = Math.max(1, pixelSize) / (float) unitsPerEm;
        float minX = Float.POSITIVE_INFINITY, minY = Float.POSITIVE_INFINITY;
        float maxX = Float.NEGATIVE_INFINITY, maxY = Float.NEGATIVE_INFINITY;
        for (List<float[]> contour : contours) {
            for (float[] p : contour) {
                minX = Math.min(minX, p[0]);
                minY = Math.min(minY, p[1]);
                maxX = Math.max(maxX, p[0]);
                maxY = Math.max(maxY, p[1]);
            }
        }
        if (!Float.isFinite(minX)) return null;
        int w = Math.min(256, (int) Math.ceil((maxX - minX) * scale + 2));
        int h = Math.min(256, (int) Math.ceil((maxY - minY) * scale + 2));
        byte[] alpha = new byte[Math.max(1, w * h)];
        List<float[]> edges = new ArrayList<>();
        for (List<float[]> contour : contours) {
            for (int i = 0; i < contour.size(); i++) {
                float[] a = contour.get(i);
                float[] b = contour.get((i + 1) % contour.size());
                float ax = (a[0] - minX) * scale + 1;
                float ay = (maxY - a[1]) * scale + 1;
                float bx = (b[0] - minX) * scale + 1;
                float by = (maxY - b[1]) * scale + 1;
                if (ax == bx && ay == by) continue;
                edges.add(new float[]{ax, ay, bx, by});
            }
        }
        int samples = 4;
        for (int py = 0; py < h; py++) {
            for (int px = 0; px < w; px++) {
                int hits = 0;
                for (int sy = 0; sy < samples; sy++) {
                    for (int sx = 0; sx < samples; sx++) {
                        float x = px + (sx + 0.5f) / samples;
                        float y = py + (sy + 0.5f) / samples;
                        int winding = 0;
                        for (float[] e : edges) {
                            if (((e[1] > y) != (e[3] > y))
                                && x < (e[2] - e[0]) * (y - e[1]) / (e[3] - e[1]) + e[0]) {
                                winding += e[3] > e[1] ? 1 : -1;
                            }
                        }
                        if (winding != 0) hits++;
                    }
                }
                if (hits > 0) alpha[py * w + px] = (byte) (hits * 255 / (samples * samples));
            }
        }
        // Compensate for the 1px transparent border in the bitmap.
        return new Glyph(w, h, minX * scale - 1, maxY * scale + 1, advanceWidth * scale, alpha);
    }

    private void parseCmap(int cmapOffset) {
        int numTables = u16(data, cmapOffset + 2);
        int best = 0, bestScore = -1;
        for (int i = 0; i < numTables; i++) {
            int rec = cmapOffset + 4 + i * 8;
            if (rec + 8 > data.length) break;
            int platform = u16(data, rec);
            int encoding = u16(data, rec + 2);
            long off = u32(data, rec + 4);
            if (off < 0 || cmapOffset + off + 2 > data.length) continue;
            int sub = cmapOffset + (int) off;
            int format = u16(data, sub);
            if (format != 4 && format != 12) continue;
            int score = format == 12 ? 3 : 2;
            if (platform == 3 && encoding == 10) score += 2;
            if (platform == 3 && encoding == 1) score += 1;
            if (score > bestScore) {
                bestScore = score;
                best = sub;
            }
        }
        if (best == 0) return;
        int format = u16(data, best);
        if (format == 4) {
            int segCount = u16(data, best + 6) / 2;
            int endCodes = best + 14;
            int startCodes = endCodes + segCount * 2 + 2;
            int idDelta = startCodes + segCount * 2;
            int idRangeOffset = idDelta + segCount * 2;
            for (int i = 0; i < segCount; i++) {
                int end = u16(data, endCodes + i * 2);
                int start = u16(data, startCodes + i * 2);
                int delta = u16(data, idDelta + i * 2);
                int range = u16(data, idRangeOffset + i * 2);
                for (int c = start; c <= end && c != 0xFFFF; c++) {
                    int gid;
                    if (range == 0) {
                        gid = (c + delta) & 0xFFFF;
                    } else {
                        int idx = idRangeOffset + i * 2 + range + (c - start) * 2;
                        if (idx + 1 >= data.length) continue;
                        gid = u16(data, idx);
                        if (gid != 0) gid = (gid + delta) & 0xFFFF;
                    }
                    if (gid != 0) cmap.putIfAbsent(c, gid);
                }
            }
        } else if (format == 12) {
            int groups = (int) u32(data, best + 12);
            for (int i = 0; i < groups; i++) {
                int base = best + 16 + i * 12;
                if (base + 12 > data.length) break;
                long startL = u32(data, base);
                long endL = Math.min(u32(data, base + 4), 0x10FFFF);
                long glyphL = u32(data, base + 8);
                if (startL > endL) continue;
                int start = (int) startL;
                int end = (int) endL;
                for (int c = start; c <= end; c++) {
                    long g = glyphL + (c - start);
                    if (g < 0 || g > 0xFFFF) break;
                    cmap.putIfAbsent(c, (int) g);
                }
            }
        }
    }

    private static int bias(Index index) {
        int count = index == null ? 0 : index.count;
        return count < 1240 ? 107 : count < 33900 ? 1131 : 32768;
    }

    private static Index readIndex(byte[] data, int pos) {
        int count = u16(data, pos);
        if (count == 0) return new Index(0, new long[]{pos + 2});
        int offSize = data[pos + 2] & 0xFF;
        int offPos = pos + 3;
        long base = offPos + (long) (count + 1) * offSize - 1;
        long[] offsets = new long[count + 1];
        for (int i = 0; i <= count; i++) {
            long value = 0;
            for (int b = 0; b < offSize; b++) value = (value << 8) | (data[offPos + i * offSize + b] & 0xFF);
            offsets[i] = base + value;
        }
        return new Index(count, offsets);
    }

    private static Map<Integer, List<Double>> parseDict(byte[] data, int start, int end) {
        Map<Integer, List<Double>> result = new HashMap<>();
        List<Double> operands = new ArrayList<>();
        int i = start;
        while (i < end) {
            int b = data[i++] & 0xFF;
            if (b == 28) {
                operands.add((double) i16(data, i)); i += 2;
            } else if (b == 29) {
                operands.add((double) (int) u32(data, i)); i += 4;
            } else if (b == 30) {
                int[] real = new int[]{0};
                operands.add(parseReal(data, i, real));
                i = real[0];
            } else if (b >= 32 && b <= 246) {
                operands.add((double) b - 139);
            } else if (b >= 247 && b <= 250) {
                operands.add((double) (b - 247) * 256 + (data[i++] & 0xFF) + 108);
            } else if (b >= 251 && b <= 254) {
                operands.add((double) -(b - 251) * 256 - (data[i++] & 0xFF) - 108);
            } else {
                int op = b;
                if (b == 12) op = 1200 + (data[i++] & 0xFF);
                result.put(op, new ArrayList<>(operands));
                operands.clear();
            }
        }
        return result;
    }

    private static double parseReal(byte[] data, int start, int[] end) {
        StringBuilder builder = new StringBuilder();
        int i = start;
        boolean done = false;
        while (i < data.length && !done) {
            int b = data[i++] & 0xFF;
            for (int nibble : new int[]{b >> 4, b & 0xF}) {
                switch (nibble) {
                    case 0xA -> builder.append('.');
                    case 0xB -> builder.append('E');
                    case 0xC -> builder.append("E-");
                    case 0xE -> builder.append('-');
                    case 0xF -> { done = true; }
                    default -> {
                        if (nibble < 10) builder.append((char) ('0' + nibble));
                    }
                }
                if (done) break;
            }
        }
        end[0] = i;
        try {
            return Double.parseDouble(builder.toString());
        } catch (NumberFormatException e) {
            return 0;
        }
    }

    private static int table(byte[] data, String tag) {
        if (data.length < 12) return -1;
        int num = u16(data, 4);
        for (int i = 0; i < num; i++) {
            int rec = 12 + i * 16;
            if (new String(data, rec, 4, java.nio.charset.StandardCharsets.US_ASCII).equals(tag)) {
                return (int) u32(data, rec + 8);
            }
        }
        return -1;
    }

    private static int u16(byte[] data, int offset) {
        return ((data[offset] & 0xFF) << 8) | (data[offset + 1] & 0xFF);
    }

    private static int i16(byte[] data, int offset) {
        return (short) u16(data, offset);
    }

    private static long u32(byte[] data, int offset) {
        return ((long) (data[offset] & 0xFF) << 24) | ((long) (data[offset + 1] & 0xFF) << 16)
            | ((long) (data[offset + 2] & 0xFF) << 8) | (data[offset + 3] & 0xFF);
    }
}
