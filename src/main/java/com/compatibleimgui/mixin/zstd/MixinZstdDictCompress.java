package com.compatibleimgui.mixin.zstd;

import com.compatibleimgui.zstd.DictionaryData;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Overwrite;
import org.spongepowered.asm.mixin.Shadow;
import org.spongepowered.asm.mixin.Unique;

import java.nio.ByteBuffer;
import java.util.Arrays;

@Mixin(targets = "com.github.luben.zstd.ZstdDictCompress", remap = false)
public abstract class MixinZstdDictCompress implements DictionaryData {

    @Shadow
    private long nativePtr;

    @Unique
    private byte[] compatibleimgui$dictionary = new byte[0];

    @Override
    public byte[] compatibleimgui$dictionary() {
        return this.compatibleimgui$dictionary;
    }

    @Overwrite(remap = false)
    private void init(byte[] dict, int offset, int length, int level) {
        this.compatibleimgui$dictionary = Arrays.copyOfRange(dict, offset, offset + length);
        this.nativePtr = 1L;
    }

    @Overwrite(remap = false)
    private void initDirect(ByteBuffer dict, int offset, int length, int level, int byReference) {
        ByteBuffer copy = dict.duplicate();
        copy.position(offset);
        copy.limit(offset + length);
        byte[] bytes = new byte[length];
        copy.get(bytes);
        this.compatibleimgui$dictionary = bytes;
        this.nativePtr = 1L;
    }

    @Overwrite(remap = false)
    private void free() {
        this.nativePtr = 0L;
        this.compatibleimgui$dictionary = new byte[0];
    }
}
