package com.compatibleimgui;

import java.lang.reflect.Method;
import java.util.Arrays;

/** Optional runtime self-test. Enable with {@code -Dcompatibleimgui.selftest=true}. */
public final class SelfTest {

    private SelfTest() {
    }

    public static void run() {
        testZstd();
        testImGui();
        testFlashback();
        testExport();
    }

    private static void testExport() {
        try {
            Class<?> settingsClass = Class.forName("com.moulberry.flashback.exporting.ExportSettings");
            Class<?> projection = Class.forName("com.moulberry.flashback.combo_options.ExportProjection");
            Class<?> container = Class.forName("com.moulberry.flashback.combo_options.VideoContainer");
            Class<?> codec = Class.forName("com.moulberry.flashback.combo_options.VideoCodec");
            Object mp4 = Enum.valueOf((Class<Enum>) container, "MP4");
            Object h264 = Enum.valueOf((Class<Enum>) codec, "H264");
            Object projectionValue = projection.getEnumConstants()[0];
            Class<?> vec3 = Class.forName("net.minecraft.world.phys.Vec3");
            Object zero = vec3.getConstructor(double.class, double.class, double.class).newInstance(0, 0, 0);
            Object settings = settingsClass.getConstructors()[0].newInstance(
                "selftest", null, zero, 0f, 0f, 64, 64, 0, 1, projectionValue, 1f, 30.0,
                false, false, mp4, h264, "purejava-h264", 0, false, false, true,
                false, null, java.nio.file.Path.of("/tmp/ni-export.mp4"), null);

            Class<?> tempInfo = Class.forName("com.moulberry.flashback.exporting.ExportJob$TempFileInfo");
            var ctor = tempInfo.getDeclaredConstructor(String.class, java.nio.file.Path.class, java.nio.file.Path.class);
            ctor.setAccessible(true);
            Object temp = ctor.newInstance("/tmp/ni-export.mp4", java.nio.file.Path.of("/tmp/ni-export.mp4"), java.nio.file.Path.of("/tmp"));

            Class<?> exportJob = Class.forName("com.moulberry.flashback.exporting.ExportJob");
            var create = exportJob.getDeclaredMethod("createVideoWriter", settingsClass, tempInfo);
            create.setAccessible(true);
            Object writer = create.invoke(null, settings, temp);

            Class<?> imageFrame = Class.forName("com.moulberry.flashback.exporting.ImageFrame");
            Object frame = imageFrame.getConstructor(int.class, int.class, Class.forName("com.moulberry.flashback.exporting.ImageFrame$Format"), boolean.class)
                .newInstance(64, 64, Enum.valueOf((Class<Enum>) Class.forName("com.moulberry.flashback.exporting.ImageFrame$Format"), "RGBA_U8"), true);
            long pixels = (long) imageFrame.getField("pixels").get(frame);
            java.nio.ByteBuffer buffer = org.lwjgl.system.MemoryUtil.memByteBuffer(pixels, 64 * 64 * 4);
            for (int i = 0; i < 64 * 64; i++) {
                buffer.put((byte) 30).put((byte) 120).put((byte) 220).put((byte) 255);
            }
            writer.getClass().getMethod("encode", imageFrame).invoke(writer, frame);
            imageFrame.getMethod("close").invoke(frame);
            writer.getClass().getMethod("finish", java.util.function.Consumer.class).invoke(writer, (java.util.function.Consumer<String>) s -> {});
            CompatibleImGuiMod.LOGGER.info("SelfTest export: writer={} size={}",
                writer.getClass().getName(), java.nio.file.Files.size(java.nio.file.Path.of("/tmp/ni-export.mp4")));
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.info("SelfTest export skipped: {}", t.toString());
        }
    }

    @SuppressWarnings({"unchecked", "rawtypes"})
    private static void frameTest(Class<?> imgui, Object io) throws Exception {
        io.getClass().getMethod("setDisplaySize", float.class, float.class).invoke(io, 800f, 600f);
        imgui.getMethod("newFrame").invoke(null);
        Object open = imgui.getMethod("begin", String.class, int.class).invoke(null, "selftest", 0);
        imgui.getMethod("text", String.class).invoke(null, "Hello compatible-imgui");
        imgui.getMethod("button", String.class).invoke(null, "Button");
        imgui.getMethod("end").invoke(null);
        imgui.getMethod("render").invoke(null);
        Object drawData = imgui.getMethod("getDrawData").invoke(null);
        int lists = (int) drawData.getClass().getMethod("getCmdListsCount").invoke(drawData);
        int vertices = (int) drawData.getClass().getMethod("getTotalVtxCount").invoke(drawData);
        int indices = (int) drawData.getClass().getMethod("getTotalIdxCount").invoke(drawData);
        CompatibleImGuiMod.LOGGER.info("SelfTest {} frame: open={} lists={} vertices={} indices={}",
            imgui.getName(), open, lists, vertices, indices);

        io.getClass().getMethod("addKeyEvent", int.class, boolean.class).invoke(io, 526, true);
        imgui.getMethod("newFrame").invoke(null);
        boolean escape = (boolean) imgui.getMethod("isKeyPressed", int.class).invoke(null, 526);
        CompatibleImGuiMod.LOGGER.info("SelfTest {} escapePressed={}", imgui.getName(), escape);
        io.getClass().getMethod("addKeyEvent", int.class, boolean.class).invoke(io, 526, false);
        imgui.getMethod("newFrame").invoke(null);
    }

    private static void testFlashback() {
        try {
            Class<?> reader = Class.forName("com.moulberry.flashback.sound.FFmpegAudioReader");
            byte[] wav = new byte[44 + 2000];
            int p = 0;
            for (byte b : "RIFF".getBytes()) wav[p++] = b;
            wav[p++] = 0; wav[p++] = 0; wav[p++] = 0; wav[p++] = 0;
            for (byte b : "WAVEfmt ".getBytes()) wav[p++] = b;
            wav[p++] = 16; wav[p++] = 0; wav[p++] = 0; wav[p++] = 0;
            wav[p++] = 1; wav[p++] = 0; wav[p++] = 1; wav[p++] = 0;
            wav[p++] = (byte) 0x80; wav[p++] = (byte) 0xBB; wav[p++] = 0; wav[p++] = 0;
            wav[p++] = 0; wav[p++] = (byte) 0xEE; wav[p++] = 2; wav[p++] = 0;
            wav[p++] = 2; wav[p++] = 0; wav[p++] = 16; wav[p++] = 0;
            for (byte b : "data".getBytes()) wav[p++] = b;
            wav[p++] = (byte) 0xD0; wav[p++] = 7; wav[p++] = 0; wav[p++] = 0;
            Object data = reader.getMethod("read", java.io.InputStream.class)
                .invoke(null, new java.io.ByteArrayInputStream(wav));
            CompatibleImGuiMod.LOGGER.info("SelfTest flashback audio: {}", data != null ? "ok" : "null");

            Class<?> container = Class.forName("com.moulberry.flashback.combo_options.VideoContainer");
            Object[] containers = (Object[]) container.getMethod("findSupportedContainers", boolean.class).invoke(null, false);
            CompatibleImGuiMod.LOGGER.info("SelfTest flashback containers: {}", Arrays.toString(containers));

            Class<?> codec = Class.forName("com.moulberry.flashback.combo_options.VideoCodec");
            Object h264 = Enum.valueOf((Class<Enum>) codec, "H264");
            String[] encoders = (String[]) codec.getMethod("getEncoders").invoke(h264);
            CompatibleImGuiMod.LOGGER.info("SelfTest flashback encoders: {}", Arrays.toString(encoders));

            Class<?> recorder = Class.forName("com.moulberry.flashback.exporting.FlashbackFFmpegFrameRecorder");
            recorder.getMethod("tryLoad").invoke(null);
            CompatibleImGuiMod.LOGGER.info("SelfTest flashback recorder: tryLoad ok");
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.info("SelfTest flashback skipped: {}", t.toString());
        }
    }

    private static void testZstd() {
        try {
            Class<?> zstd = Class.forName("com.github.luben.zstd.Zstd");
            byte[] input = "compatible-imgui zstd self test".getBytes();
            byte[] compressed = (byte[]) zstd.getMethod("compress", byte[].class).invoke(null, (Object) input);
            byte[] output = (byte[]) zstd.getMethod("decompress", byte[].class, int.class)
                .invoke(null, compressed, input.length);
            CompatibleImGuiMod.LOGGER.info("SelfTest zstd: {} -> {} ok={}", input.length, output.length, Arrays.equals(input, output));

            Class<?> dictCompress = Class.forName("com.github.luben.zstd.ZstdDictCompress");
            Object cd = dictCompress.getConstructor(byte[].class, int.class).newInstance(new byte[]{1, 2, 3, 4}, 3);
            byte[] withDict = (byte[]) zstd.getMethod("compress", byte[].class, dictCompress)
                .invoke(null, input, cd);
            Class<?> dictDecompress = Class.forName("com.github.luben.zstd.ZstdDictDecompress");
            Object dd = dictDecompress.getConstructor(byte[].class).newInstance((Object) new byte[]{1, 2, 3, 4});
            byte[] roundTrip = (byte[]) zstd.getMethod("decompress", byte[].class, dictDecompress, int.class)
                .invoke(null, withDict, dd, input.length);
            CompatibleImGuiMod.LOGGER.info("SelfTest zstd dict: ok={}", Arrays.equals(input, roundTrip));
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.error("SelfTest zstd failed", t);
        }
    }

    private static void testImGui() {
        try {
            Class<?> imgui = Class.forName("imgui.moulberry92.ImGui");
            Object io = imgui.getMethod("getIO").invoke(null);
            Method getDisplaySizeX = io.getClass().getMethod("getDisplaySizeX");
            CompatibleImGuiMod.LOGGER.info("SelfTest imgui92: IO={} displayWidth={}", io, getDisplaySizeX.invoke(io));
            frameTest(imgui, io);
        } catch (Throwable t) {
            // 1.90-only installs are fine.
            CompatibleImGuiMod.LOGGER.info("SelfTest imgui92 skipped: {}", t.toString());
        }
        try {
            Class<?> imgui = Class.forName("imgui.moulberry90.ImGui");
            Object io = imgui.getMethod("getIO").invoke(null);
            Method getDisplaySizeX = io.getClass().getMethod("getDisplaySizeX");
            CompatibleImGuiMod.LOGGER.info("SelfTest imgui90: IO={} displayWidth={}", io, getDisplaySizeX.invoke(io));
            frameTest(imgui, io);
        } catch (Throwable t) {
            CompatibleImGuiMod.LOGGER.info("SelfTest imgui90 skipped: {}", t.toString());
        }
    }
}
