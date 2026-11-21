# Native ImGui backend

This directory replaces the hand-written pure-Java ImGui engine with the real
upstream C++ implementation.

```
Axiom / Flashback binding classes (unchanged)
             │  JNI
             ▼
  libimgui-moulberry92-java64.so   ← upstream Dear ImGui 1.92.7 + TextEditor
  libimgui-moulberry90-java64.so   ← upstream Dear ImGui 1.90 + TextEditor
             │
  native/nativebridge mixin picks the matching OS/arch build
```

The Java side is now only a resource redirect (about 100 lines). All layout,
widget, font, docking, table and drawing behaviour comes from upstream
`imgui.cpp`, so it is pixel-compatible by construction.

## Why this replaces the Java port

The archived `legacy/pure-java-imgui/` implementation was ~37,700 lines and
still had 108 partial / 31 no-op / 16 missing calls out of 424 observed calls.
A native rebuild reuses the exact source version that Axiom and Flashback were
compiled against:

| Consumer | Binding | Dear ImGui | Upstream tag |
|---|---|---|---|
| Flashback 0.43.6 | `imgui.moulberry90` | 1.90 | `v1.90.0` (`c8055286`) |
| Axiom 6.1.5 | `imgui.moulberry92` | 1.92.7 | `v1.92-moulberry.2` (`4a281343`) |

Both pin the same submodule versions (see `upstream.lock.json`).

One important difference: upstream 1.90 still uses the `imgui` package, while
Flashback ships it relocated to `imgui.moulberry90`. `generate.sh` therefore
relocates the JNI symbols, `FindClass` names and JNI type descriptors for the
90 build (`Limgui_` → `Limgui_moulberry90_`, `Limgui/` → `Limgui/moulberry90/`,
`Java_imgui_` → `Java_imgui_moulberry90_`). Without this, the library loads but
every method with an ImGui-typed parameter is reported as missing.

## Layout

```
native/
  upstream.lock.json     pinned tags/commits
  generate.sh            regenerate native/generated from upstream (rarely)
  build.sh               cross-compile all targets
  compat/win32/jni_md.h  target JNI definitions (no Windows/macOS JDK needed)
  compat/darwin/jni_md.h
  generated/90/          committed JNI wrappers + ImGui/TextEditor sources
  generated/92/
```

Only these extensions are compiled:

- Dear ImGui core (`imgui.cpp`, `imgui_draw.cpp`, `imgui_tables.cpp`,
  `imgui_widgets.cpp`)
- `ImGuiColorTextEdit` (used by Axiom)
- the Moulberry JNI glue

ImPlot, ImNodes, ImGuizmo, FileDialog, Knobs, node-editor and the LWJGL3 GLFW
backend are **not** compiled. The observed Axiom/Flashback call set
(`run/calls.txt`) does not use them. If a future version starts using one,
remove the corresponding exclusion in `generate.sh` and add its submodule
source to `generated/`.

FreeType is not linked; Dear ImGui uses its built-in `stb_truetype` loader.
The observed call set has no `ImGuiFreeType` calls.

## Requirements

- **Zig 0.14+** for desktop cross builds. Zig bundles libc/libc++ and macOS
  system stubs, so one Linux host can produce Windows, Linux and macOS
  binaries. No macOS SDK or MSVC is required.
- **Android NDK** (r26+) for `android-aarch64`.
- JDK only for `generate.sh` (not for `build.sh`).

If Zig is not installed, `build.sh` still builds Linux x86_64 with the host
`clang++`/`g++`, but that binary inherits the host glibc. Do not ship that as a
release artifact; install Zig for a 2.17 baseline.

The local development machine also accepts an extracted Arch package under
`tools/zigpkg/usr/bin/zig` (gitignored); `build.sh` detects it and sets
`LD_LIBRARY_PATH` automatically. This is not part of the repository.

### Fast Android NDK install (Linux)

The official Google zip was the fastest source here (~47 MB/s, 15 s for
664 MB); Tencent's Android SDK mirror is the fallback. The helper performs the
whole install without root and verifies the SHA1:

```bash
./native/install-ndk.sh
./native/build.sh android-aarch64
```

It installs NDK r27c (`27.2.12479018`) into
`${ANDROID_HOME:-$HOME/Android/Sdk}/ndk/27.2.12479018`; `build.sh` searches
`~/Android/Sdk/ndk/*` automatically. If you install elsewhere, export
`ANDROID_NDK_HOME=/path/to/ndk`.

Manual equivalent:

```bash
curl -L --retry 5 -o /tmp/ndk.zip \
  https://dl.google.com/android/repository/android-ndk-r27c-linux.zip
mkdir -p ~/Android/Sdk/ndk/27.2.12479018
bsdtar -xf /tmp/ndk.zip -C ~/Android/Sdk/ndk/27.2.12479018 --strip-components=1
```

Android's `jni.h` only defines `JNI_VERSION_1_6` (the 1.8 constant is a
desktop-JDK addition). `jni_jvm.cpp` is pinned to 1.6 in `generate.sh`; this is
ABI-compatible with desktop JVMs and the Android runtime.

```bash
# Example: put Zig anywhere and point at it
ZIG=/opt/zig/zig ./native/build.sh linux-x86_64 linux-aarch64 \
    windows-x86_64 windows-aarch64 macos-x86_64 macos-aarch64
ANDROID_NDK_HOME=/opt/android-ndk ./native/build.sh android-aarch64
```

Targets (all six desktop targets were cross-built from Linux x86_64 with
Zig 0.17.1; the artifacts were checked as ELF/PE/Mach-O and their JNI export
counts match the original libraries):

| Target | Compiler | Verified locally |
|---|---|---|
| `linux-x86_64` | `zig c++ -target x86_64-linux-gnu.2.17` | yes (glibc 2.17, no libstdc++ dep) |
| `linux-aarch64` | `zig c++ -target aarch64-linux-gnu.2.17` | yes (ELF aarch64) |
| `windows-x86_64` | `zig c++ -target x86_64-windows-gnu` | yes (PE32+ x86-64, 2248 exports) |
| `windows-aarch64` | `zig c++ -target aarch64-windows-gnu` | yes (PE32+ ARM64) |
| `macos-x86_64` | `zig c++ -target x86_64-macos.10.15` | yes (Mach-O x86_64, libSystem only) |
| `macos-aarch64` | `zig c++ -target aarch64-macos.11.0` | yes (Mach-O arm64) |
| `android-aarch64` | NDK r27c `aarch64-linux-android24-clang++` | yes (ELF Android 24, 2070/2248 exports; device run pending) |

`-s` is passed to the linker, so debug sections and Zig's Windows `.pdb`/`.lib`
side artifacts are not shipped.

## Build and package

```bash
./native/build.sh                 # writes build/native/resources/...
./gradlew buildNatives build      # or run the script then gradle
```

`build.gradle` adds `build/native/resources` as an extra resource root. The
resulting jar contains:

```
compatibleimgui/native/linux-x86_64/libimgui-moulberry92-java64.so
compatibleimgui/native/windows-aarch64/imgui-moulberry90-java64.dll
...
```

`com.compatibleimgui.bridge.NativeLibraries` maps the running OS/arch to that
directory. The two `nativebridge` mixins redirect the binding's
`getResourceAsStream` call only for `imgui-moulberry90/92-java64`; everything
else falls through to the original loader. If no build exists for the current
platform, the binding's original native library is used.

## Regenerating after an upstream bump

```bash
# Update native/upstream.lock.json first, then:
./native/generate.sh
```

This downloads both tags and their `imgui` / `ImGuiColorTextEdit` submodules,
runs the upstream Gradle JNI generator, prunes unused extensions and writes
`native/generated/{90,92}`. Review the diff before building; the generated
wrappers are derived from the binding's native method list.

## Licensing

The generated tree keeps the upstream licenses in `generated/*/LICENSES/`:

- Dear ImGui — MIT
- imgui-java / Moulberry fork — MIT
- ImGuiColorTextEdit — MIT

Rebuilt binaries are distributed under the same licenses as the sources.
