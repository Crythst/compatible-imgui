package com.compatibleimgui.audio;

import com.jcraft.jogg.Packet;
import com.jcraft.jogg.Page;
import com.jcraft.jogg.StreamState;
import com.jcraft.jogg.SyncState;
import com.jcraft.jorbis.Block;
import com.jcraft.jorbis.Comment;
import com.jcraft.jorbis.DspState;
import com.jcraft.jorbis.Info;
import javazoom.jl.decoder.Bitstream;
import javazoom.jl.decoder.Decoder;
import javazoom.jl.decoder.Header;
import javazoom.jl.decoder.SampleBuffer;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

/**
 * Pure Java audio decoding for the formats embedded in Flashback replays.
 * WAV, Ogg Vorbis and MP3 are supported. Everything is decoded to signed
 * little-endian 16-bit PCM, which is exactly what Minecraft's SoundBuffer
 * accepts.
 */
public final class PureAudio {

    public record Decoded(byte[] pcm, int sampleRate, int channels, int bits) {
    }

    private PureAudio() {
    }

    public static Decoded decode(InputStream inputStream) {
        try {
            byte[] data = inputStream.readAllBytes();
            return decode(data);
        } catch (IOException e) {
            return null;
        }
    }

    public static Decoded decode(byte[] data) {
        if (data.length < 12) {
            return null;
        }
        if (isRiffWave(data)) {
            return decodeWav(data);
        }
        if (data[0] == 'O' && data[1] == 'g' && data[2] == 'g' && data[3] == 'S') {
            return decodeOgg(data);
        }
        if (looksLikeMp3(data)) {
            return decodeMp3(data);
        }
        return null;
    }

    private static boolean isRiffWave(byte[] data) {
        return data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F'
            && data[8] == 'W' && data[9] == 'A' && data[10] == 'V' && data[11] == 'E';
    }

    private static boolean looksLikeMp3(byte[] data) {
        if (data.length >= 3 && data[0] == 'I' && data[1] == 'D' && data[2] == '3') {
            return true;
        }
        return data.length >= 2 && (data[0] & 0xFF) == 0xFF && (data[1] & 0xE0) == 0xE0;
    }

    // ------------------------------------------------------------------
    // WAV
    // ------------------------------------------------------------------

    private static Decoded decodeWav(byte[] data) {
        try {
            int pos = 12;
            int format = 1;
            int channels = 1;
            int sampleRate = 44100;
            int bits = 16;
            byte[] pcm = null;

            while (pos + 8 <= data.length) {
                String id = new String(data, pos, 4, java.nio.charset.StandardCharsets.US_ASCII);
                int size = readIntLE(data, pos + 4);
                int body = pos + 8;
                if (size < 0 || body + size > data.length) {
                    size = data.length - body;
                }
                if (id.equals("fmt ")) {
                    format = readShortLE(data, body);
                    channels = readShortLE(data, body + 2);
                    sampleRate = readIntLE(data, body + 4);
                    bits = readShortLE(data, body + 14);
                    if (format == 0xFFFE && size >= 40) {
                        format = readShortLE(data, body + 24);
                    }
                } else if (id.equals("data")) {
                    pcm = Arrays.copyOfRange(data, body, body + size);
                }
                pos = body + size + (size & 1);
            }

            if (pcm == null || channels < 1 || channels > 2) {
                return null;
            }

            byte[] converted = convertToS16LE(pcm, format, channels, bits);
            if (converted == null) {
                return null;
            }
            return new Decoded(converted, sampleRate, channels, 16);
        } catch (RuntimeException e) {
            return null;
        }
    }

    private static byte[] convertToS16LE(byte[] input, int format, int channels, int bits) {
        int frames = input.length / Math.max(1, (bits / 8) * channels);
        ByteBuffer out = ByteBuffer.allocate(frames * channels * 2).order(ByteOrder.LITTLE_ENDIAN);

        if (format == 1 && bits == 8) {
            for (byte b : input) {
                out.putShort((short) (((b & 0xFF) - 128) << 8));
            }
            return out.array();
        }
        if (format == 1 && bits == 16) {
            return input.clone();
        }
        if (format == 1 && bits == 24) {
            for (int i = 0; i + 2 < input.length; i += 3) {
                int v = (input[i] & 0xFF) | ((input[i + 1] & 0xFF) << 8) | (input[i + 2] << 16);
                out.putShort((short) (v >> 8));
            }
            return out.array();
        }
        if (format == 1 && bits == 32) {
            for (int i = 0; i + 3 < input.length; i += 4) {
                int v = (input[i] & 0xFF) | ((input[i + 1] & 0xFF) << 8)
                    | ((input[i + 2] & 0xFF) << 16) | (input[i + 3] << 24);
                out.putShort((short) (v >> 16));
            }
            return out.array();
        }
        if (format == 3 && bits == 32) {
            for (int i = 0; i + 3 < input.length; i += 4) {
                int v = (input[i] & 0xFF) | ((input[i + 1] & 0xFF) << 8)
                    | ((input[i + 2] & 0xFF) << 16) | (input[i + 3] << 24);
                float f = Float.intBitsToFloat(v);
                out.putShort((short) (Math.max(-1f, Math.min(1f, f)) * 32767f));
            }
            return out.array();
        }
        return null;
    }

    // ------------------------------------------------------------------
    // Ogg Vorbis (JOrbis)
    // ------------------------------------------------------------------

    private static Decoded decodeOgg(byte[] data) {
        try {
            SyncState oy = new SyncState();
            StreamState os = new StreamState();
            Page og = new Page();
            Packet op = new Packet();
            Info vi = new Info();
            Comment vc = new Comment();
            DspState vd = new DspState();
            Block vb = new Block(vd);

            oy.init();
            int index = oy.buffer(4096);
            System.arraycopy(data, 0, oy.data, index, Math.min(4096, data.length));
            oy.wrote(Math.min(4096, data.length));

            int offset = 4096;
            int[] headers = new int[]{0};

            if (oy.pageout(og) != 1) {
                return null;
            }
            os.init(og.serialno());
            vi.init();
            vc.init();
            if (os.pagein(og) < 0) {
                return null;
            }

            boolean ready = false;
            while (headers[0] < 3) {
                int result = os.packetout(op);
                if (result > 0) {
                    if (vi.synthesis_headerin(vc, op) < 0) {
                        return null;
                    }
                    headers[0]++;
                    if (headers[0] == 3) {
                        ready = true;
                        break;
                    }
                } else {
                    while (offset < data.length) {
                        int pageResult = oy.pageout(og);
                        if (pageResult == 0) {
                            index = oy.buffer(4096);
                            int n = Math.min(4096, data.length - offset);
                            if (n <= 0) {
                                break;
                            }
                            System.arraycopy(data, offset, oy.data, index, n);
                            oy.wrote(n);
                            offset += n;
                            continue;
                        }
                        if (pageResult < 0) {
                            return null;
                        }
                        os.pagein(og);
                        break;
                    }
                }
            }

            if (!ready) {
                return null;
            }

            vd.synthesis_init(vi);
            vb.init(vd);

            int channels = vi.channels;
            int rate = vi.rate;
            ByteArrayOutputStream pcmOut = new ByteArrayOutputStream(data.length / 2);
            float[][][] pcm = new float[1][channels][];
            int[] pcmOffset = new int[1];

            while (true) {
                int result = os.packetout(op);
                if (result > 0) {
                    if (vb.synthesis(op) == 0 && vd.synthesis_blockin(vb) == 0) {
                        int samples;
                        while ((samples = vd.synthesis_pcmout(pcm, pcmOffset)) > 0) {
                            writeFloatPcm(pcm[0], pcmOffset[0], samples, channels, pcmOut);
                            vd.synthesis_read(samples);
                        }
                    }
                } else {
                    while (offset < data.length) {
                        int pageResult = oy.pageout(og);
                        if (pageResult == 0) {
                            index = oy.buffer(4096);
                            int n = Math.min(4096, data.length - offset);
                            if (n <= 0) {
                                break;
                            }
                            System.arraycopy(data, offset, oy.data, index, n);
                            oy.wrote(n);
                            offset += n;
                            continue;
                        }
                        if (pageResult < 0) {
                            break;
                        }
                        os.pagein(og);
                        result = os.packetout(op);
                        if (result > 0) {
                            if (vb.synthesis(op) == 0 && vd.synthesis_blockin(vb) == 0) {
                                int samples;
                                while ((samples = vd.synthesis_pcmout(pcm, pcmOffset)) > 0) {
                                    writeFloatPcm(pcm[0], pcmOffset[0], samples, channels, pcmOut);
                                    vd.synthesis_read(samples);
                                }
                            }
                        }
                        break;
                    }
                    if (offset >= data.length) {
                        // flush the decoder
                        boolean any = false;
                        while (vd.synthesis_pcmout(pcm, pcmOffset) > 0) {
                            int samples = vd.synthesis_pcmout(pcm, pcmOffset);
                            writeFloatPcm(pcm[0], pcmOffset[0], samples, channels, pcmOut);
                            vd.synthesis_read(samples);
                            any = true;
                        }
                        if (!any) {
                            break;
                        }
                    }
                }
            }

            return new Decoded(pcmOut.toByteArray(), rate, channels, 16);
        } catch (Throwable t) {
            return null;
        }
    }

    private static void writeFloatPcm(float[][] pcm, int offset, int samples, int channels, ByteArrayOutputStream out) {
        for (int i = 0; i < samples; i++) {
            for (int ch = 0; ch < channels; ch++) {
                float value = pcm[ch][offset + i];
                int v = (int) (Math.max(-1f, Math.min(1f, value)) * 32767f);
                out.write(v & 0xFF);
                out.write((v >> 8) & 0xFF);
            }
        }
    }

    // ------------------------------------------------------------------
    // MP3 (JLayer)
    // ------------------------------------------------------------------

    private static Decoded decodeMp3(byte[] data) {
        try {
            Bitstream bitstream = new Bitstream(new ByteArrayInputStream(data));
            Decoder decoder = new Decoder();
            ByteArrayOutputStream out = new ByteArrayOutputStream(data.length / 2);
            int sampleRate = 44100;
            int channels = 2;

            while (true) {
                Header header;
                try {
                    header = bitstream.readFrame();
                } catch (Exception e) {
                    break;
                }
                if (header == null) {
                    break;
                }
                sampleRate = header.frequency();
                channels = header.mode() == Header.SINGLE_CHANNEL ? 1 : 2;
                SampleBuffer output = (SampleBuffer) decoder.decodeFrame(header, bitstream);
                short[] buffer = output.getBuffer();
                int len = output.getBufferLength();
                for (int i = 0; i < len; i++) {
                    short v = buffer[i];
                    out.write(v & 0xFF);
                    out.write((v >> 8) & 0xFF);
                }
                bitstream.closeFrame();
            }
            bitstream.close();
            return new Decoded(out.toByteArray(), sampleRate, channels, 16);
        } catch (Throwable t) {
            return null;
        }
    }

    private static int readIntLE(byte[] data, int offset) {
        return (data[offset] & 0xFF) | ((data[offset + 1] & 0xFF) << 8)
            | ((data[offset + 2] & 0xFF) << 16) | ((data[offset + 3] & 0xFF) << 24);
    }

    private static int readShortLE(byte[] data, int offset) {
        return (data[offset] & 0xFF) | ((data[offset + 1] & 0xFF) << 8);
    }
}
