package com.compatibleimgui.zstd;

import io.airlift.compress.MalformedInputException;
import io.airlift.compress.zstd.ZstdCompressor;
import io.airlift.compress.zstd.ZstdDecompressor;

import java.nio.ByteBuffer;

/**
 * Pure Java zstd facade. Uses Aircompressor (Apache 2.0), which has no native
 * dependencies and runs on every JVM including Android.
 *
 * <p>Dictionaries are accepted for API compatibility. Compression deliberately
 * ignores the dictionary so that peers without the dictionary can decode the
 * result. Decompression first tries the regular path; dictionary-compressed
 * frames from a stock Axiom server are reported as an error until the
 * dictionary-aware decoder is enabled.</p>
 */
public final class PureZstd {

    public static final long ERROR = -1L;

    private static final ZstdCompressor COMPRESSOR = new ZstdCompressor();
    private static final ZstdDecompressor DECOMPRESSOR = new ZstdDecompressor();

    private PureZstd() {
    }

    public static int defaultCompressionLevel() {
        return 3;
    }

    public static long compressBound(long size) {
        if (size < 0) {
            return ERROR;
        }
        return size + (size >>> 3) + 128L;
    }

    public static byte[] compress(byte[] src, int level) {
        int bound = (int) Math.min(Integer.MAX_VALUE - 8L, compressBound(src.length));
        byte[] out = new byte[bound];
        int written = COMPRESSOR.compress(src, 0, src.length, out, 0, out.length);
        return java.util.Arrays.copyOf(out, written);
    }

    public static long compress(byte[] dst, int dstOffset, int dstSize, byte[] src, int srcOffset, int srcSize) {
        try {
            int written = COMPRESSOR.compress(src, srcOffset, srcSize, dst, dstOffset, dstSize);
            return written;
        } catch (RuntimeException e) {
            return ERROR;
        }
    }

    public static ByteBuffer compress(ByteBuffer src, int level) {
        byte[] bytes = new byte[src.remaining()];
        src.get(bytes);
        byte[] compressed = compress(bytes, level);
        return ByteBuffer.wrap(compressed);
    }

    public static byte[] decompress(byte[] src, int expectedSize) {
        byte[] out = new byte[expectedSize];
        int written = DECOMPRESSOR.decompress(src, 0, src.length, out, 0, out.length);
        return written == out.length ? out : java.util.Arrays.copyOf(out, written);
    }

    public static long decompress(byte[] dst, int dstOffset, int dstSize, byte[] src, int srcOffset, int srcSize) {
        try {
            int written = DECOMPRESSOR.decompress(src, srcOffset, srcSize, dst, dstOffset, dstSize);
            return written;
        } catch (RuntimeException e) {
            return ERROR;
        }
    }

    public static int decompress(ByteBuffer src, ByteBuffer dst) {
        try {
            int before = dst.position();
            DECOMPRESSOR.decompress(src, dst);
            return dst.position() - before;
        } catch (RuntimeException e) {
            return -1;
        }
    }

    public static long decompressedSize(byte[] src) {
        try {
            return ZstdDecompressor.getDecompressedSize(src, 0, src.length);
        } catch (RuntimeException e) {
            return ERROR;
        }
    }

    public static long decompressedSize(ByteBuffer src) {
        if (!src.hasArray()) {
            ByteBuffer copy = src.duplicate();
            byte[] data = new byte[copy.remaining()];
            copy.get(data);
            return decompressedSize(data);
        }
        return ZstdDecompressor.getDecompressedSize(src.array(), src.arrayOffset() + src.position(), src.remaining());
    }

    public static boolean isError(long code) {
        return code < 0;
    }

    public static String getErrorName(long code) {
        return code == ERROR ? "ZSTD_error_GENERIC" : "ZSTD_error_no_error";
    }

    public static long getErrorCode(long code) {
        return code;
    }
}
