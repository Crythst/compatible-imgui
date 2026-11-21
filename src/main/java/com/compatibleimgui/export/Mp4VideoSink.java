package com.compatibleimgui.export;

import org.jcodec.api.SequenceEncoder;
import org.jcodec.common.model.ColorSpace;
import org.jcodec.common.model.Picture;
import org.jcodec.common.model.Rational;
import org.jcodec.common.io.NIOUtils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;

/** Minimal pure-Java H.264/MP4 encoder. */
public final class Mp4VideoSink implements AutoCloseable {

    private final SequenceEncoder encoder;
    private final int width;
    private final int height;
    private final Picture picture;
    private int frame;

    public Mp4VideoSink(Path file, int width, int height, double fps) throws IOException {
        // The MP4/MOV container supports fractional rates through a rational.
        int num = (int) Math.max(1, Math.round(fps * 1000.0));
        this.encoder = SequenceEncoder.createWithFps(NIOUtils.writableChannel(file.toFile()), Rational.R(num, 1000));
        this.width = width;
        this.height = height;
        this.picture = Picture.create(width, height, ColorSpace.RGB);
    }

    public void addRgba(byte[] rgba) throws IOException {
        if (rgba.length < width * height * 4) {
            throw new IllegalArgumentException("Frame buffer too small: " + rgba.length);
        }
        byte[] rgb = picture.getPlaneData(0);
        for (int i = 0, j = 0; i < width * height; i++, j += 4) {
            rgb[i * 3] = rgba[j];
            rgb[i * 3 + 1] = rgba[j + 1];
            rgb[i * 3 + 2] = rgba[j + 2];
        }
        encoder.encodeNativeFrame(picture);
        frame++;
    }

    public int frames() {
        return frame;
    }

    @Override
    public void close() throws IOException {
        encoder.finish();
    }
}
