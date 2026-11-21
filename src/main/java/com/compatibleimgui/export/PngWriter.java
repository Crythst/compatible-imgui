package com.compatibleimgui.export;

import com.compatibleimgui.CompatibleImGuiMod;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.zip.CRC32;
import java.util.zip.Deflater;

/** Dependency-free PNG writer (RGBA8, filter 0). */
public final class PngWriter {

    private static final byte[] SIGNATURE = {(byte) 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};

    private PngWriter() {
    }

    public static void write(Path path, byte[] rgba, int width, int height) throws IOException {
        if (rgba.length < width * height * 4) {
            throw new IllegalArgumentException("RGBA buffer too small");
        }

        ByteArrayOutputStream raw = new ByteArrayOutputStream((width * 4 + 1) * height);
        for (int y = 0; y < height; y++) {
            raw.write(0); // filter type: none
            raw.write(rgba, y * width * 4, width * 4);
        }

        byte[] compressed = deflate(raw.toByteArray());

        ByteArrayOutputStream file = new ByteArrayOutputStream(compressed.length + 128);
        file.write(SIGNATURE);

        ByteArrayOutputStream ihdr = new ByteArrayOutputStream(13);
        DataOutputStream ihdrData = new DataOutputStream(ihdr);
        ihdrData.writeInt(width);
        ihdrData.writeInt(height);
        ihdrData.writeByte(8); // bit depth
        ihdrData.writeByte(6); // colour type RGBA
        ihdrData.writeByte(0); // compression
        ihdrData.writeByte(0); // filter
        ihdrData.writeByte(0); // interlace
        chunk(file, "IHDR", ihdr.toByteArray());
        chunk(file, "IDAT", compressed);
        chunk(file, "IEND", new byte[0]);

        Path parent = path.toAbsolutePath().getParent();
        if (parent != null) {
            Files.createDirectories(parent);
        }
        Files.write(path, file.toByteArray());
    }

    private static byte[] deflate(byte[] data) {
        Deflater deflater = new Deflater(Deflater.BEST_SPEED);
        try {
            deflater.setInput(data);
            deflater.finish();
            ByteArrayOutputStream out = new ByteArrayOutputStream(data.length / 2 + 64);
            byte[] buffer = new byte[8192];
            while (!deflater.finished()) {
                int n = deflater.deflate(buffer);
                out.write(buffer, 0, n);
            }
            return out.toByteArray();
        } finally {
            deflater.end();
        }
    }

    private static void chunk(ByteArrayOutputStream out, String type, byte[] data) {
        try {
            DataOutputStream dos = new DataOutputStream(out);
            dos.writeInt(data.length);
            byte[] name = type.getBytes(java.nio.charset.StandardCharsets.US_ASCII);
            dos.write(name);
            dos.write(data);
            CRC32 crc = new CRC32();
            crc.update(name);
            crc.update(data);
            dos.writeInt((int) crc.getValue());
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
}
