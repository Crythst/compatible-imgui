package com.noimgui.imgui;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Minimal TrueType (glyf) parser + scanline rasterizer.
 *
 * <p>This exists so icon fonts (Material Icons / Axiom's axiomicons.ttf) and CJK
 * fonts can be rendered without a native FreeType/stb_truetype dependency. It
 * intentionally handles the common TrueType tables only; CFF/OTF outlines fall
 * back to the caller's placeholder.</p>
 */
final class TrueTypeFont {

    record Glyph(int width, int height, float bearingX, float bearingY, float advance, byte[] alpha) implements GlyphData {
    }

    private final byte[] data;
    private final int unitsPerEm;
    private final int numGlyphs;
    private final int ascender;
    private final int descender;
    private final int[] loca;
    private final int[] advance;
    private final int glyfOffset;
    private final int headOffset;
    private final boolean shortLoca;
    private final Map<Integer, Integer> cmap = new HashMap<>();
    private final Map<Long, Glyph> cache = new HashMap<>();

    private TrueTypeFont(byte[] data, int unitsPerEm, int numGlyphs, int ascender, int descender,
                         int[] loca, int[] advance, int glyfOffset, int headOffset, boolean shortLoca) {
        this.data = data;
        this.unitsPerEm = unitsPerEm <= 0 ? 1000 : unitsPerEm;
        this.numGlyphs = numGlyphs;
        this.ascender = ascender;
        this.descender = descender;
        this.loca = loca;
        this.advance = advance;
        this.glyfOffset = glyfOffset;
        this.headOffset = headOffset;
        this.shortLoca = shortLoca;
    }

    static TrueTypeFont parse(byte[] data) {
        try {
            if (data.length < 12) return null;
            int numTables = u16(data, 4);
            int head = 0, maxp = 0, hhea = 0, hmtx = 0, cmap = 0, loca = 0, glyf = 0;
            for (int i = 0; i < numTables; i++) {
                int rec = 12 + i * 16;
                if (rec + 16 > data.length) break;
                String tag = new String(data, rec, 4, java.nio.charset.StandardCharsets.US_ASCII);
                long offset = u32(data, rec + 8);
                long length = u32(data, rec + 12);
                if (offset < 0 || offset + length > data.length) continue;
                int o = (int) offset;
                switch (tag) {
                    case "head" -> head = o;
                    case "maxp" -> maxp = o;
                    case "hhea" -> hhea = o;
                    case "hmtx" -> hmtx = o;
                    case "cmap" -> cmap = o;
                    case "loca" -> loca = o;
                    case "glyf" -> glyf = o;
                    default -> {
                    }
                }
            }
            if (head == 0 || maxp == 0 || hhea == 0 || loca == 0 || glyf == 0) {
                return null;
            }
            int unitsPerEm = u16(data, head + 18);
            boolean shortLoca = i16(data, head + 50) == 0;
            int numGlyphs = u16(data, maxp + 4);
            int ascender = i16(data, hhea + 4);
            int descender = i16(data, hhea + 6);
            int numberOfHMetrics = u16(data, hhea + 34);

            int[] locaValues = new int[numGlyphs + 1];
            for (int i = 0; i <= numGlyphs; i++) {
                locaValues[i] = shortLoca ? u16(data, loca + i * 2) * 2 : (int) u32(data, loca + i * 4);
            }

            int[] advances = new int[numGlyphs];
            int lastAdvance = unitsPerEm / 2;
            for (int i = 0; i < numGlyphs; i++) {
                if (i < numberOfHMetrics) {
                    lastAdvance = u16(data, hmtx + i * 4);
                }
                advances[i] = lastAdvance;
            }

            TrueTypeFont font = new TrueTypeFont(data, unitsPerEm, numGlyphs, ascender, descender,
                locaValues, advances, glyf, head, shortLoca);
            if (cmap != 0) {
                font.parseCmap(cmap);
            }
            return font;
        } catch (Throwable t) {
            return null;
        }
    }

    private void parseCmap(int cmapOffset) {
        int numTables = u16(data, cmapOffset + 2);
        int best = 0;
        int bestScore = -1;
        for (int i = 0; i < numTables; i++) {
            int rec = cmapOffset + 4 + i * 8;
            if (rec + 8 > data.length) break;
            int platform = u16(data, rec);
            int encoding = u16(data, rec + 2);
            long off = u32(data, rec + 4);
            if (off < 0 || cmapOffset + off + 2 > data.length) continue;
            int sub = cmapOffset + (int) off;
            int format = u16(data, sub);
            int score = switch (format) {
                case 12 -> 3;
                case 4 -> 2;
                default -> 0;
            };
            if (score == 0) continue;
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
                    int glyph;
                    if (range == 0) {
                        glyph = (c + delta) & 0xFFFF;
                    } else {
                        int idx = idRangeOffset + i * 2 + range + (c - start) * 2;
                        if (idx + 1 >= data.length) continue;
                        glyph = u16(data, idx);
                        if (glyph != 0) glyph = (glyph + delta) & 0xFFFF;
                    }
                    if (glyph != 0) cmap.putIfAbsent(c, glyph);
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

    Glyph glyph(int codepoint, int pixelSize) {
        long key = ((long) codepoint << 32) | (pixelSize & 0xFFFFFFFFL);
        Glyph cached = cache.get(key);
        if (cached != null) return cached;
        Integer glyphIndex = cmap.get(codepoint);
        if (glyphIndex == null || glyphIndex < 0 || glyphIndex >= numGlyphs) {
            return null;
        }
        List<List<Point>> contours = new ArrayList<>();
        collectGlyph(glyphIndex, Transform.IDENTITY, contours, 0);
        // Ignore degenerate contours (e.g. the 3-identical-point contour some
        // fonts use for the space glyph); they have no area.
        contours.removeIf(TrueTypeFont::isDegenerate);
        Glyph glyph;
        if (contours.isEmpty()) {
            // Whitespace (and other mapped-but-empty glyphs) still carries a real
            // advance, which the text layout uses; only the bitmap is empty.
            float scale = pixelScale(pixelSize);
            glyph = new Glyph(0, 0, 0, 0, advance[glyphIndex] * scale, new byte[0]);
        } else {
            glyph = rasterize(contours, advance[glyphIndex], pixelSize);
        }
        if (cache.size() > 4096) cache.clear();
        cache.put(key, glyph);
        return glyph;
    }

    private float pixelScale(int pixelSize) {
        return Math.max(1, pixelSize) / (float) unitsPerEm;
    }

    /** True when a contour cannot enclose any area. */
    private static boolean isDegenerate(List<Point> contour) {
        if (contour.size() < 3) return true;
        float minX = Float.POSITIVE_INFINITY, minY = Float.POSITIVE_INFINITY;
        float maxX = Float.NEGATIVE_INFINITY, maxY = Float.NEGATIVE_INFINITY;
        for (Point point : contour) {
            minX = Math.min(minX, point.x);
            minY = Math.min(minY, point.y);
            maxX = Math.max(maxX, point.x);
            maxY = Math.max(maxY, point.y);
        }
        return maxX - minX <= 0 || maxY - minY <= 0;
    }

    private void collectGlyph(int glyphIndex, Transform transform, List<List<Point>> out, int depth) {
        if (depth > 8 || glyphIndex < 0 || glyphIndex >= numGlyphs) return;
        int start = glyfOffset + loca[glyphIndex];
        int end = glyfOffset + loca[glyphIndex + 1];
        if (end <= start || start < 0 || end > data.length) return;
        int contours = i16(data, start);
        if (contours >= 0) {
            collectSimple(start, contours, transform, out);
        } else {
            collectComposite(start + 10, transform, out, depth);
        }
    }

    private void collectSimple(int start, int contourCount, Transform transform, List<List<Point>> out) {
        int p = start + 10;
        int[] ends = new int[contourCount];
        for (int i = 0; i < contourCount; i++) {
            ends[i] = u16(data, p);
            p += 2;
        }
        int instructionLength = u16(data, p);
        p += 2 + instructionLength;
        int pointCount = ends.length == 0 ? 0 : ends[ends.length - 1] + 1;
        int[] flags = new int[pointCount];
        for (int i = 0; i < pointCount; ) {
            int flag = data[p++] & 0xFF;
            flags[i++] = flag;
            if ((flag & 0x08) != 0) {
                int repeat = data[p++] & 0xFF;
                for (int r = 0; r < repeat && i < pointCount; r++) flags[i++] = flag;
            }
        }
        int[] xs = new int[pointCount];
        int[] ys = new int[pointCount];
        int x = 0;
        for (int i = 0; i < pointCount; i++) {
            int flag = flags[i];
            if ((flag & 0x02) != 0) {
                int v = data[p++] & 0xFF;
                x += (flag & 0x10) != 0 ? v : -v;
            } else if ((flag & 0x10) == 0) {
                x += i16(data, p);
                p += 2;
            }
            xs[i] = x;
        }
        int y = 0;
        for (int i = 0; i < pointCount; i++) {
            int flag = flags[i];
            if ((flag & 0x04) != 0) {
                int v = data[p++] & 0xFF;
                y += (flag & 0x20) != 0 ? v : -v;
            } else if ((flag & 0x20) == 0) {
                y += i16(data, p);
                p += 2;
            }
            ys[i] = y;
        }
        int first = 0;
        for (int end : ends) {
            List<Point> contour = new ArrayList<>();
            for (int i = first; i <= end && i < pointCount; i++) {
                contour.add(new Point(transform.x(xs[i], ys[i]), transform.y(xs[i], ys[i]),
                    (flags[i] & 0x01) != 0));
            }
            if (!contour.isEmpty()) out.add(contour);
            first = end + 1;
        }
    }

    private void collectComposite(int p, Transform parent, List<List<Point>> out, int depth) {
        while (p + 4 <= data.length) {
            int flags = u16(data, p);
            int glyphIndex = u16(data, p + 2);
            p += 4;
            int arg1, arg2;
            if ((flags & 0x0001) != 0) {
                arg1 = i16(data, p);
                arg2 = i16(data, p + 2);
                p += 4;
            } else {
                arg1 = (byte) data[p++];
                arg2 = (byte) data[p++];
            }
            float a = 1, b = 0, c = 0, d = 1;
            if ((flags & 0x0008) != 0) {
                a = d = f2dot14(data, p);
                p += 2;
            } else if ((flags & 0x0040) != 0) {
                a = f2dot14(data, p);
                d = f2dot14(data, p + 2);
                p += 4;
            } else if ((flags & 0x0080) != 0) {
                a = f2dot14(data, p);
                b = f2dot14(data, p + 2);
                c = f2dot14(data, p + 4);
                d = f2dot14(data, p + 6);
                p += 8;
            }

            // Component offset in the parent's coordinate space. When
            // SCALED_COMPONENT_OFFSET is set it is transformed by the
            // component matrix; UNSCALED_COMPONENT_OFFSET (and the common
            // default) keeps it as-is.
            float ox = arg1;
            float oy = arg2;
            if ((flags & 0x0800) != 0) {
                ox = a * arg1 + c * arg2;
                oy = b * arg1 + d * arg2;
            }

            // child(p) = componentMatrix * p + offset, then parent(child(p)).
            Transform child = new Transform(
                parent.a * a + parent.c * b,
                parent.b * a + parent.d * b,
                parent.a * c + parent.c * d,
                parent.b * c + parent.d * d,
                parent.x(ox, oy),
                parent.y(ox, oy));
            collectGlyph(glyphIndex, child, out, depth + 1);
            if ((flags & 0x0020) == 0) break;
        }
    }

    private Glyph rasterize(List<List<Point>> contours, int advanceWidth, int pixelSize) {
        float scale = pixelScale(pixelSize);
        float minX = Float.POSITIVE_INFINITY, minY = Float.POSITIVE_INFINITY;
        float maxX = Float.NEGATIVE_INFINITY, maxY = Float.NEGATIVE_INFINITY;
        for (List<Point> contour : contours) {
            for (Point point : contour) {
                minX = Math.min(minX, point.x);
                minY = Math.min(minY, point.y);
                maxX = Math.max(maxX, point.x);
                maxY = Math.max(maxY, point.y);
            }
        }
        if (!Float.isFinite(minX)) return null;
        float width = Math.max(1, (maxX - minX) * scale + 2);
        float height = Math.max(1, (maxY - minY) * scale + 2);
        int w = Math.min(256, (int) Math.ceil(width));
        int h = Math.min(256, (int) Math.ceil(height));
        byte[] alpha = new byte[w * h];

        List<float[]> edges = new ArrayList<>();
        for (List<Point> contour : contours) {
            List<Point> flat = flatten(contour);
            for (int i = 0; i < flat.size(); i++) {
                Point a = flat.get(i);
                Point b = flat.get((i + 1) % flat.size());
                float ax = (a.x - minX) * scale + 1;
                float ay = (maxY - a.y) * scale + 1;
                float bx = (b.x - minX) * scale + 1;
                float by = (maxY - b.y) * scale + 1;
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
                if (hits > 0) {
                    alpha[py * w + px] = (byte) (hits * 255 / (samples * samples));
                }
            }
        }
        // The bitmap keeps a 1px transparent border; compensate in the bearings
        // so that the outline lands at minX/maxY instead of one pixel inside.
        return new Glyph(w, h, minX * scale - 1, maxY * scale + 1, advanceWidth * scale, alpha);
    }

    private static List<Point> flatten(List<Point> points) {
        int n = points.size();
        if (n == 0) return List.of();

        // Expand the TrueType contour: a midpoint is implied between every two
        // consecutive off-curve points. The result is a sequence where every
        // off-curve control point is followed by an on-curve endpoint.
        List<Point> seq = new ArrayList<>(n + 4);
        for (int i = 0; i < n; i++) {
            Point p = points.get(i);
            seq.add(p);
            if (!p.onCurve) {
                Point next = points.get((i + 1) % n);
                if (!next.onCurve) seq.add(mid(p, next));
            }
        }

        int m = seq.size();
        int start = 0;
        while (start < m && !seq.get(start).onCurve) start++;
        if (start == m) {
            // Contour made only of off-curve points: start at the implied
            // midpoint of the last and first point.
            Point first = mid(points.get(n - 1), points.get(0));
            seq.add(0, first);
            m++;
            start = 0;
        }

        List<Point> out = new ArrayList<>(m * 3);
        Point cur = seq.get(start);
        out.add(cur);
        int offset = 1;
        while (offset < m) {
            Point p = seq.get((start + offset) % m);
            if (p.onCurve) {
                out.add(p);
                cur = p;
                offset++;
            } else {
                Point end = seq.get((start + offset + 1) % m);
                quadratic(out, cur, p, end);
                cur = end;
                offset += 2;
            }
        }
        return out;
    }

    private static void quadratic(List<Point> out, Point p0, Point p1, Point p2) {
        int segments = 8;
        for (int i = 1; i <= segments; i++) {
            float t = i / (float) segments;
            float u = 1 - t;
            float x = u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x;
            float y = u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y;
            out.add(new Point(x, y, true));
        }
    }

    private static Point mid(Point a, Point b) {
        return new Point((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f, true);
    }

    /** Affine transform: x' = a*x + c*y + tx, y' = b*x + d*y + ty. */
    private record Transform(float a, float b, float c, float d, float tx, float ty) {
        static final Transform IDENTITY = new Transform(1, 0, 0, 1, 0, 0);

        float x(float x, float y) {
            return a * x + c * y + tx;
        }

        float y(float x, float y) {
            return b * x + d * y + ty;
        }
    }

    private record Point(float x, float y, boolean onCurve) {
    }

    private static int u16(byte[] data, int offset) {
        return ((data[offset] & 0xFF) << 8) | (data[offset + 1] & 0xFF);
    }

    private static int i16(byte[] data, int offset) {
        return (short) u16(data, offset);
    }

    private static long u32(byte[] data, int offset) {
        return ((long) (data[offset] & 0xFF) << 24)
            | ((long) (data[offset + 1] & 0xFF) << 16)
            | ((long) (data[offset + 2] & 0xFF) << 8)
            | (data[offset + 3] & 0xFF);
    }

    private static float f2dot14(byte[] data, int offset) {
        return i16(data, offset) / 16384f;
    }
}
