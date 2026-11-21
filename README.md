# Compatible ImGui（compatible-imgui）

一个面向 **Minecraft 26.3 / Fabric** 的兼容层，让 **Flashback** 与 **Axiom** 不再依赖它们自带的旧 native 库：

- **Dear ImGui**：不再手写 Java 复刻，直接用上游 C++ 源码重新编译（1.90 / 1.92.7），
  通过 JNI 原样替换 binding 加载的 `.so` / `.dll` / `.dylib`。
- **FFmpeg / JavaCV** → JCodec（H.264/MP4）+ 内置 PNG 编码器 + JOrbis/JLayer 音频解码。
- **zstd-jni** → Aircompressor 纯 Java 实现。

目标平台：Windows / Linux / macOS（x86_64、arm64）以及 Android（aarch64）。
Jar 内包含六个桌面目标 + Android aarch64 的 ImGui native 库。
FFmpeg 与 zstd 部分仍保持纯 Java。

> 旧的纯 Java ImGui 引擎（约 37,700 行）已归档到 `legacy/pure-java-imgui/`，
> 不参与构建，仅用于对照。当前实现完全由重建的上游 C++ 提供。
> 原生重建与交叉编译细节见 [`native/README.md`](native/README.md)。

---

## 1. 依赖分析

### Flashback

| 依赖 | 来源 | 用途 | 现在的替换方式 |
|---|---|---|---|
| `imgui-binding-1.90.0.jar` + `imgui-natives.jar` | `deps/` | 回放编辑器 UI | 用上游 1.90 重建 `libimgui-moulberry90-java64` |
| `org.bytedeco:ffmpeg` / `javacv` | `shadow` | 视频导出、音频读取 | `PureJavaVideoWriter` / `PureAudio` |
| LWJGL SDL | Minecraft | 输入/窗口 | 保留 |

### Axiom

| 依赖 | 来源 | 用途 | 现在的替换方式 |
|---|---|---|---|
| `imgui/moulberry92/*` + `io/imgui/java/native-bin/*` | Axiom jar | 编辑器 UI | 用上游 1.92.7 重建 `libimgui-moulberry92-java64` |
| `zstd-jni` + `linux\|win\|darwin/.../libzstd-jni` | Axiom jar | 历史记录 / 方块实体压缩 | `PureZstd` + zstd mixins |
| LWJGL SDL | Minecraft | 输入/窗口 | 保留 |

Axiom 的 `TextEditor`、ImGui docking、字体、表格等全部回到上游实现，不再手写。

---

## 2. 架构

```
Flashback / Axiom 的 imgui.moulberry90/92 调用
        │
        │  binding 类原样保留，只重定向 getResourceAsStream
        ▼
com.compatibleimgui.mixin.nativebridge.MixinImGuiNativeLoader90/92
        │
        ▼
compatibleimgui/native/<os>-<arch>/libimgui-moulberry9x-java64.*
        │
        ▼
上游 Dear ImGui C++ + ImGuiColorTextEdit + Moulberry JNI glue
        │
        ▼
ImDrawData → Flashback/Axiom 原有 GPU 渲染器
```

Java 侧只剩：

- 平台目录选择（`com.compatibleimgui.bridge.NativeLibraries`，约 100 行）；
- 两个 `@Redirect` mixin；
- FFmpeg / 音频 / zstd 的纯 Java 实现。

`imgui.moulberry90` 是 Flashback 对上游 `imgui` 包的重定位版本。
`native/generate.sh` 会把 JNI 符号、`FindClass` 名和类型描述符同步重定位，
否则带 ImGui 参数的方法会在运行时报 `UnsatisfiedLinkError`。

---

## 3. 构建

要求：

- JDK 25（Gradle 构建）
- Gradle wrapper（仓库自带）
- 本地已有 Flashback 源码和 Axiom jar（编译期引用）：
  - `../Flashback/build/classes/java/main`
  - `Axiom-6.1.5-for-MC26.3.jar`
- 构建 native 库时：
  - **Zig 0.14+**（桌面交叉编译，包含 macOS/Windows 目标）
  - **Android NDK r26+**（Android aarch64）

```bash
# 1. Android NDK（一次性，约 15 秒 / 664 MB，自动校验 SHA1）
./native/install-ndk.sh

# 2. 桌面 / Android native
./native/build.sh                         # 所有已安装工具链的目标
./native/build.sh linux-x86_64 windows-aarch64
./native/build.sh android-aarch64         # 自动发现 ~/Android/Sdk/ndk/*

# 3. mod jar
cd ~/IdeaProjects/Flashback && ./gradlew compileJava
cd ~/IdeaProjects/compatible-imgui && ./gradlew build
# 产物：build/libs/compatible-imgui-0.1.0.jar
```

`native/build.sh` 把文件写到 `build/native/resources/compatibleimgui/native/...`，
`build.gradle` 会把它作为额外的资源根打进 jar。没有本地 native 构建时 Gradle
仍可打包，但对应平台会回退到 binding 自带的原生库（Android 等不受支持的目标
必须先运行 `native/build.sh`）。

### 升级上游版本

```bash
# 修改 native/upstream.lock.json 里的 tag/commit 后：
./native/generate.sh
```

脚本会下载对应的 `imgui-java`、`imgui`、`ImGuiColorTextEdit` 源码，运行上游
JNI 生成器，裁剪未使用的扩展，并把结果写入 `native/generated/{90,92}`。
生成结果已提交，普通构建不需要网络和 JDK 17。

---

## 4. 运行与开关

ImGui 始终使用重建的上游 native；`native/build.sh` 会按 OS/arch 选择目录。

```bash
./gradlew runClient
```

只剩 FFmpeg 导出还有开关：

```bash
# 使用原始 FFmpeg 导出
-Dcompatibleimgui.export=native

# 自动：没有对应 native 时使用纯 Java
-Dcompatibleimgui.export=auto
```

### 截图

Axiom/Flashback 的 ImGui overlay 不进入 Minecraft 自身 screenshot target，
所以 `Screenshot.grab` 只能截到世界。使用外部 active-window 截图：

```bash
JAVA_TOOL_OPTIONS='-Dcompatibleimgui.screenshot.raise=true' ./gradlew runClient --args='--username Test'
# 等进入世界、UI 出现后：
spectacle -b -n -a -o run/screenshot-active.png
# 或：
tools/screenshot.sh run/screenshot-active.png 60
```

最新验证截图：`run/screenshot-compatible-imgui.png`（Axiom 编辑器，使用重建的
`libimgui-moulberry92-java64.so`：docked 布局、tab、图标、字体、滚动条、状态栏全部由上游
ImGui 渲染）。归档的纯 Java 版本截图：`run/screenshot-ui16.png`。
Flashback dock 布局在同一批运行日志中验证：
`Main 0,24 1668x730`、`Timeline 0,756 1920x250`、`Visuals 1670,24 250x730`。

运行时必须同时安装 **Flashback** 和/或 **Axiom**；本模组本身不添加游戏内容。
Mixin 插件会检测对应模组是否存在，不存在时不会应用相应替换。

---

## 4.1 实现依据

- `reference/imgui-java`（tag `v1.92-moulberry.2`，Dear ImGui `b1bcb12` / 1.92.7）
- Flashback 的 binding 版本 `1.90.0`，对应上游 tag `v1.90.0` / `c8055286`
- 两个版本的上游源码都由 `native/upstream.lock.json` 固定

ABI 校验：

- 92：重建库与原 Axiom native 的 **核心 JNI 导出符号完全一致**，缺失的只有未使用的
  ImPlot/ImNodes/ImGuizmo/FileDialog/Knobs/node-editor 扩展。
- 90：重建库与原 Flashback native 的核心 JNI 导出符号一致；唯一缺失的是未使用的
  `ImGuiImplGlfwNative.win32hideFromTaskBar`。
- `run/calls.txt` 是从真实 Axiom + Flashback 运行中抓取的调用集合，作为裁剪和验收契约。

---

## 5. 已验证内容

在 Linux x86_64、Minecraft 26.3、Fabric Loader 0.19.5 下：

- 同时加载 Axiom 6.1.5 + Flashback 0.43.6 + 本模组；
- 两个重建库都被 binding 从 `compatibleimgui/native/linux-x86_64/` 提取并加载：
  - `/tmp/imgui-java-natives/1.90.0/libimgui-moulberry90-java64.so`
  - `/tmp/imgui-moulberry92-java-natives/1.92-moulberry.2/libimgui-moulberry92-java64.so`
- 启动、进入世界、Axiom/Flashback 初始化均无 `UnsatisfiedLinkError`；
- Axiom 编辑器完整渲染（`run/screenshot-compatible-imgui.png`）：docked 面板、tab、图标、
  真实 TTF 字体、滚动条、菜单栏、状态栏；
- Axiom docking / Flashback 时间线使用上游 ImGui 实现，布局与原生版本一致；
- 独立测试通过：
  - zstd 压缩/解压往返一致；
  - PNG 写入可被标准工具读取；
  - WAV（PCM16）解码得到 48 kHz 单声道 PCM；
  - JCodec H.264/MP4 写出有效文件。

> Linux x86_64 已完成实机验证（Axiom 编辑器截图见上）。
> 其余桌面目标已在本机用 Zig 0.17.1 从 Linux x86_64 交叉编译并做二进制校验：
> `linux-aarch64`（ELF）、`windows-x86_64` / `windows-aarch64`（PE32+）、
> `macos-x86_64` / `macos-aarch64`（Mach-O）；JNI 导出数量与原始库的核心符号一致。
> `android-aarch64` 已用 NDK r27c（27.2.12479018）构建并完成二进制校验：
> Android 24、ELF aarch64、导出 2070 / 2248 个 JNI 符号，只依赖 `libc` / `libm` / `libdl`，
> 不依赖 `libc++_shared`。真机运行仍待验证；`.github/workflows/natives.yml` 已包含构建任务。

---

## 6. 当前限制

1. **未编译的 ImGui 扩展**
   - ImPlot / ImNodes / ImGuizmo / ImGuiFileDialog / imgui-knobs / node-editor 不进入重建库。
   - 当前 Axiom 6.1.5 / Flashback 0.43.6 不调用它们；如果未来调用，需要把对应 submodule
     加回 `native/generate.sh` 并重新生成。
2. **FreeType**
   - 没有链接 FreeType，使用 Dear ImGui 内置 `stb_truetype`。
   - 当前调用集合中没有 `ImGuiFreeType`；如果需要，可在 cross build 中加入 FreeType。
3. **平台产物**
   - Jar 包含六个桌面目标 + Android aarch64（约 14 MB），体积会明显大于纯 Java 版本。
   - 桌面交叉编译依赖 Zig；Android 依赖 NDK（`.github/workflows/natives.yml` 已配置）。
   - 用非 Zig 的本地 clang 构建 Linux 版时会继承宿主 glibc；发布版请用 Zig 的 2.17 基线。
   - Windows / macOS 产物已完成二进制格式与 JNI 导出校验，但尚未在对应系统上做实机 UI 验证。
   - Android 产物已完成二进制校验，尚未真机运行；binding 仍会把 `.so` 解压到临时目录再
     `System.load`，启动器需要允许从该路径加载 native。
4. **旧 Java 引擎已归档**
   - `legacy/pure-java-imgui/` 保留旧的 `com.compatibleimgui.imgui.*`、`imgui90/92`
     mixins、`generate_imgui_mixins.py` 和 porting 文档。
   - 它不参与 Gradle 构建，只用于行为对照。

---

## 7. 为什么回到原生库

- ImGui 的 Java API 已经被 Flashback/Axiom 写死。换 Rust/Kotlin/Java 重写仍要维护
  同一套 adapter，而且永远追不上上游 5 万行 C++ 的语义。
- 直接重编上游 C++ 是唯一能保证 docking、表格、字体、输入、DrawData 逐像素一致的方案。
- “不用 Java”只能做到 **引擎不用 Java**；最外层仍必须是 JVM 类，因为调用方是 JVM。
  现在这层被压缩到两个 mixin + 一个平台选择类。
- Zig 让 Linux 主机可以一次性交叉编译 Windows/macOS/Linux 的桌面库；Android 用 NDK。

---

## 8. 目录

```
src/main/java/com/compatibleimgui/
  CompatibleImGuiMod.java                 入口/开关
  Platform.java                    平台检测
  bridge/NativeLibraries.java      native 资源定位
  mixin/nativebridge/              binding 加载重定向（90/92）
  export/                          纯 Java 视频/PNG
  audio/PureAudio.java             WAV/OGG/MP3
  zstd/PureZstd.java               zstd
native/
  README.md                        交叉编译说明
  upstream.lock.json               上游 tag/commit
  generate.sh                      重新生成 JNI 源码
  build.sh                         交叉编译目标库
  generated/90/                    已提交的 1.90 JNI + ImGui + TextEditor
  generated/92/                    已提交的 1.92 JNI + ImGui + TextEditor
legacy/pure-java-imgui/            归档的旧 Java 引擎与 porting 文档
```

---

## 许可

本模组代码使用 MIT。内嵌/重建依赖：

- Dear ImGui — MIT
- imgui-java / Moulberry fork — MIT
- ImGuiColorTextEdit — MIT
- Aircompressor — Apache-2.0
- JCodec — BSD-2-Clause
- JOrbis — LGPL-2.1
- JLayer — LGPL-2.1

Flashback 与 Axiom 的代码/资源版权归各自作者所有；本模组不重新分发它们。
