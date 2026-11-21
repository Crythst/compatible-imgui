package com.compatibleimgui.export;

import com.moulberry.flashback.combo_options.VideoContainer;
import com.moulberry.flashback.exporting.ExportSettings;
import com.moulberry.flashback.exporting.ImageFrame;
import com.moulberry.flashback.exporting.VideoWriter;
import com.compatibleimgui.CompatibleImGuiMod;
import org.lwjgl.system.MemoryUtil;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Locale;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import java.util.function.Consumer;

/**
 * Drop-in replacement for Flashback's FFmpeg writer. It encodes H.264/MP4 with
 * JCodec and writes PNG sequences with a tiny built-in PNG writer. No native
 * libraries are touched.
 */
public final class PureJavaVideoWriter implements VideoWriter {

    private final ExportSettings settings;
    private final String filename;
    private final boolean png;
    private final ArrayBlockingQueue<Frame> queue = new ArrayBlockingQueue<>(16);
    private final AtomicBoolean finishing = new AtomicBoolean(false);
    private final AtomicBoolean finished = new AtomicBoolean(false);
    private final AtomicReference<Throwable> error = new AtomicReference<>();
    private final Thread thread;

    private int sequence;

    private record Frame(byte[] rgba, int width, int height) {
    }

    public PureJavaVideoWriter(ExportSettings settings, String filename) {
        this.settings = settings;
        this.filename = filename;
        this.png = settings.container().isImageSequence()
            || settings.container() == VideoContainer.PNG_SEQUENCE
            || settings.container() == VideoContainer.GIF
            || settings.container() == VideoContainer.WEBP;
        this.thread = new Thread(this::run, "compatible-imgui-encoder");
        this.thread.setDaemon(true);
        this.thread.start();
    }

    @Override
    public void encode(ImageFrame src) {
        if (finishing.get() || finished.get()) {
            throw new IllegalStateException("Cannot encode after finish");
        }
        byte[] rgba = readRgba(src);
        try {
            while (!this.queue.offer(new Frame(rgba, src.width, src.height), 10, TimeUnit.MILLISECONDS)) {
                checkError();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        }
    }

    private static byte[] readRgba(ImageFrame src) {
        ByteBuffer input = MemoryUtil.memByteBuffer(src.pixels, (int) src.size);
        byte[] rgba = new byte[src.width * src.height * 4];

        switch (src.format) {
            case RGBA_U8 -> input.get(rgba);
            case GRAY_F32 -> {
                for (int i = 0; i < src.width * src.height; i++) {
                    float value = input.getFloat();
                    int gray = (int) (Math.max(0f, Math.min(1f, value)) * 255f);
                    rgba[i * 4] = (byte) gray;
                    rgba[i * 4 + 1] = (byte) gray;
                    rgba[i * 4 + 2] = (byte) gray;
                    rgba[i * 4 + 3] = (byte) 255;
                }
            }
            case CUSTOM -> throw new UnsupportedOperationException("CUSTOM pixel format is not supported by the pure-Java exporter");
        }
        return rgba;
    }

    private void run() {
        try {
            Path output = this.settings.output();
            if (this.png) {
                runPng(output);
            } else {
                runMp4(output);
            }
            this.finished.set(true);
        } catch (Throwable t) {
            this.error.set(t);
            this.finished.set(true);
        }
    }

    private void runMp4(Path output) throws IOException {
        if (output.getParent() != null) {
            Files.createDirectories(output.getParent());
        }
        try (Mp4VideoSink sink = new Mp4VideoSink(output, this.settings.resolutionX(), this.settings.resolutionY(), this.settings.framerate())) {
            while (true) {
                Frame frame = this.queue.poll(10, TimeUnit.MILLISECONDS);
                if (frame == null) {
                    if (this.finishing.get()) {
                        break;
                    }
                    continue;
                }
                sink.addRgba(frame.rgba);
                checkError();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IOException(e);
        }
    }

    private void runPng(Path output) throws IOException {
        boolean outputIsDirectory = Files.isDirectory(output);
        boolean multiple = outputIsDirectory || this.settings.startTick() != this.settings.endTick()
            || this.settings.pngSequenceFormat() != null;

        if (output.getParent() != null && !outputIsDirectory) {
            Files.createDirectories(output.getParent());
        }
        if (outputIsDirectory) {
            Files.createDirectories(output);
        }

        while (true) {
            Frame frame;
            try {
                frame = this.queue.poll(10, TimeUnit.MILLISECONDS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new IOException(e);
            }
            if (frame == null) {
                if (this.finishing.get()) {
                    break;
                }
                continue;
            }

            this.sequence++;
            Path target;
            if (multiple) {
                String format = this.settings.pngSequenceFormat();
                if (format == null) {
                    format = "%04d";
                }
                String name;
                try {
                    name = String.format(Locale.ROOT, format, this.sequence);
                } catch (Exception e) {
                    name = String.format(Locale.ROOT, "%04d", this.sequence);
                }
                if (!name.toLowerCase(Locale.ROOT).endsWith(".png")) {
                    name += ".png";
                }
                if (outputIsDirectory) {
                    target = output.resolve(name);
                } else {
                    String prefix = output.getFileName().toString() + "-";
                    target = output.resolveSibling(prefix + name);
                }
            } else {
                target = output;
                if (!target.getFileName().toString().toLowerCase(Locale.ROOT).endsWith(".png")) {
                    target = target.resolveSibling(target.getFileName() + ".png");
                }
            }

            PngWriter.write(target, frame.rgba, frame.width, frame.height);
            checkError();
        }
    }

    @Override
    public void finish(Consumer<String> wait) {
        this.finishing.set(true);
        while (!this.finished.get()) {
            checkError();
            wait.accept("compatible-imgui encoder");
            java.util.concurrent.locks.LockSupport.parkNanos(100_000L);
        }
        checkError();
    }

    private void checkError() {
        Throwable t = this.error.get();
        if (t != null) {
            if (t instanceof RuntimeException re) {
                throw re;
            }
            if (t instanceof Error e) {
                throw e;
            }
            throw new RuntimeException(t);
        }
    }

    @Override
    public void close() {
        this.finishing.set(true);
    }
}
