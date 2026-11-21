package com.compatibleimgui.mixin.zstd;

import com.compatibleimgui.zstd.PureZstd;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

import java.nio.ByteBuffer;

@Mixin(targets = "com.github.luben.zstd.Zstd", remap = false)
public abstract class MixinZstd {

    @Inject(method = "<clinit>", at = @At("HEAD"), cancellable = true, remap = false)
    private static void compatibleimgui$skipNative(CallbackInfo ci) {
        // Do not load libzstd-jni. All call sites used by Axiom are replaced below.
        ci.cancel();
    }

    @Overwrite(remap = false)
    public static int defaultCompressionLevel() {
        return PureZstd.defaultCompressionLevel();
    }

    @Overwrite(remap = false)
    public static long compressBound(long size) {
        return PureZstd.compressBound(size);
    }

    @Overwrite(remap = false)
    public static long compress(byte[] dst, byte[] src, int level, boolean checksum) {
        return PureZstd.compress(dst, 0, dst.length, src, 0, src.length);
    }

    @Overwrite(remap = false)
    public static long compress(byte[] dst, byte[] src, int level) {
        return PureZstd.compress(dst, 0, dst.length, src, 0, src.length);
    }

    @Overwrite(remap = false)
    public static byte[] compress(byte[] src) {
        return PureZstd.compress(src, 3);
    }

    @Overwrite(remap = false)
    public static byte[] compress(byte[] src, int level) {
        return PureZstd.compress(src, level);
    }

    @Overwrite(remap = false)
    public static byte[] compress(byte[] src, com.github.luben.zstd.ZstdDictCompress dict) {
        return PureZstd.compress(src, 3);
    }

    @Overwrite(remap = false)
    public static long compressByteArray(byte[] dst, int dstOffset, int dstSize, byte[] src, int srcOffset, int srcSize, int level, boolean checksum) {
        return PureZstd.compress(dst, dstOffset, dstSize, src, srcOffset, srcSize);
    }

    @Overwrite(remap = false)
    public static long compressByteArray(byte[] dst, int dstOffset, int dstSize, byte[] src, int srcOffset, int srcSize, int level) {
        return PureZstd.compress(dst, dstOffset, dstSize, src, srcOffset, srcSize);
    }

    @Overwrite(remap = false)
    public static byte[] decompress(byte[] src, int originalSize) {
        return PureZstd.decompress(src, originalSize);
    }

    @Overwrite(remap = false)
    public static byte[] decompress(byte[] src) {
        long size = PureZstd.decompressedSize(src);
        if (size < 0 || size > Integer.MAX_VALUE) {
            throw new IllegalStateException("Cannot determine decompressed size");
        }
        return PureZstd.decompress(src, (int) size);
    }

    @Overwrite(remap = false)
    public static byte[] decompress(byte[] src, com.github.luben.zstd.ZstdDictDecompress dict, int originalSize) {
        // Frames produced by compatible-imgui have no dictionary ID. Frames from a stock
        // Axiom server may require dictionary history; the plain decoder reports
        // an error in that case.
        return PureZstd.decompress(src, originalSize);
    }

    @Overwrite(remap = false)
    public static long decompress(byte[] src, byte[] dst) {
        return PureZstd.decompress(dst, 0, dst.length, src, 0, src.length);
    }

    @Overwrite(remap = false)
    public static int decompress(byte[] src, ByteBuffer dst) {
        return PureZstd.decompress(ByteBuffer.wrap(src), dst);
    }

    @Overwrite(remap = false)
    public static int decompress(ByteBuffer src, ByteBuffer dst) {
        return PureZstd.decompress(src, dst);
    }

    @Overwrite(remap = false)
    public static long decompressByteArray(byte[] dst, int dstOffset, int dstSize, byte[] src, int srcOffset, int srcSize) {
        return PureZstd.decompress(dst, dstOffset, dstSize, src, srcOffset, srcSize);
    }

    @Overwrite(remap = false)
    public static long decompressedSize(byte[] src) {
        return PureZstd.decompressedSize(src);
    }

    @Overwrite(remap = false)
    public static long decompressedSize(byte[] src, int offset, int length) {
        if (offset == 0 && length == src.length) {
            return PureZstd.decompressedSize(src);
        }
        byte[] copy = java.util.Arrays.copyOfRange(src, offset, offset + length);
        return PureZstd.decompressedSize(copy);
    }

    @Overwrite(remap = false)
    public static long decompressedSize(byte[] src, int offset) {
        return decompressedSize(src, offset, src.length - offset);
    }

    @Overwrite(remap = false)
    public static long decompressedSize(ByteBuffer src) {
        return PureZstd.decompressedSize(src);
    }

    @Overwrite(remap = false)
    public static ByteBuffer compress(ByteBuffer src, int level) {
        return PureZstd.compress(src, level);
    }

    @Overwrite(remap = false)
    public static boolean isError(long code) {
        return PureZstd.isError(code);
    }

    @Overwrite(remap = false)
    public static String getErrorName(long code) {
        return PureZstd.getErrorName(code);
    }

    @Overwrite(remap = false)
    public static long getErrorCode(long code) {
        return PureZstd.getErrorCode(code);
    }
}
