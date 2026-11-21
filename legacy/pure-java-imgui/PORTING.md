> **LEGACY:** this document describes the removed/optional hand-written Java ImGui port.
> The default implementation is now the rebuilt upstream C++ backend; see `native/README.md`.

# ImGui Java Port Status

参考源码（已 clone 到 `reference/`）：

- `Moulberry/imgui-java`，tag `v1.92-moulberry.2`
- `include/imgui`，Dear ImGui `b1bcb12`（1.92.7）
- 布局审查：`PORTING_LAYOUT_REVIEW.md`
- API 缺口审计：`PORTING_GAPS.md`

Dear ImGui 核心规模：

| 文件 | 行数 |
|---|---:|
| `imgui.cpp` | 24272 |
| `imgui_draw.cpp` | 6756 |
| `imgui_tables.cpp` | 4642 |
| `imgui_widgets.cpp` | 10967 |
| `imgui_internal.h` | 4305 |

**说明：** 这不是逐行照搬的 C++ 翻译，而是按真实源码语义实现的可运行 Java 引擎，API 覆盖以
Axiom 6.1.5 / Flashback 0.43.6 实际调用集合（`run/calls.txt`）为准，并补齐了常用控件。

## 已按源码实现的路径

### 输入 / 捕获

- `UpdateHoveredWindowAndCaptureFlags` 的点击归属：
  - 按下时记录 `MouseDownOwned[i] = HoveredWindow || OpenPopup`
  - 最早按下的按钮决定 `mouse_avail`，在 UI 外开始的拖拽不会被吞掉
  - `WantCaptureMouse` / `WantCaptureKeyboard` 支持 `SetNextFrameWantCapture*` 三态覆盖
- `WantCaptureKeyboard` 只跟随 `ActiveId` / 文本输入 / modal
- 编辑器点击空白结束输入焦点
- 顶层 hovered window 按提交顺序（z-order）选取
- 滚轮只滚动最上层 hovered window，步长 `trunc(min(5*FontSize, 0.67*InnerH))`

### 窗口 / Docking

- 读取真实 `imgui.ini` 的 `[Window]` 与 `[Docking][Data]`
- `DockLayout`（`src/main/java/com/noimgui/imgui/DockLayout.java`）：
  - `DockNodeTreeUpdatePosSize` / `DockNodeTreeUpdateSplitter` 的矩形与 `SizeRef` 数学
  - central node、分隔条、最小尺寸、tab bar 矩形
  - splitter 拖拽（`resizeSplit`，方向与 native 一致）
  - 序列化 / 解析往返测试
- 工作区使用 `ImGuiViewport.WorkPos/WorkSize`；主菜单栏与 Axiom 状态栏的 inset 会扣除
- `dockSpaceOverViewport` 返回真实 dockspace id
- `dockBuilderGetCentralNode` 解析到 central leaf
- `ImGuiDockNode.addLocalFlags` / `localFlags` 保存运行时标志（Axiom 的 `NoTabBar`）
- docked 窗口几何 = node 矩形；tab bar 覆盖 title 区域，不重复扣高度
- `NoTabBar` / `HiddenTabBar` / 单选 tab 自动隐藏
- CRC32 `Selected` 同时匹配完整窗口名和 `###` 后名称（Axiom / Flashback 两种 ini）
- tab 宽度使用 `text + 2*FramePadding.x + ItemSpacing.x`

### 布局 / 尺寸

- `Begin/End`：
  - 窗口栈、`contentX/Y/W/H`、`titleH`
  - 内容尺寸 `CursorMaxPos - CursorStartPos`（不含尾部 ItemSpacing）
  - `ScrollMax = ContentSize + 2*Padding - InnerRect`
  - `AlwaysAutoResize` 尺寸计算
  - scrollbar thumb 使用 native 公式
  - clip rect 与父级相交，clip 外控件不可点击
- `BeginChild/EndChild`：
  - `GetContentRegionAvail` 尺寸、负尺寸 `CalcItemSize` 语义
  - 父窗口滚动、padding、父 clip 交集
  - `EndChild` 才 `ItemSize` 实际子窗口大小
- `SetNextWindowPos/Size` 的 `ImGuiCond`（Always/Once/FirstUseEver/Appearing）
- `SetNextWindowPos` 的 `PosUndock`，但保留 ini 中已 docking 的窗口
- `SetNextWindowFocus` 只改变焦点，不改几何
- 主菜单栏按 `BeginViewportSideBar` 语义放置并上报 inset

### 控件 / 状态

- `Button/Checkbox/Radio/Selectable/Slider/Drag/Input/Combo/Menu/Popup/Table/Tab/ListBox`
- `beginDisabled` 嵌套 + 阻止 hit-test
- 文本输入（`InputTextModel`）：光标、选区、Home/End、Ctrl+方向、撤销/重做、剪贴板、密码、字符过滤、水平滚动
- 表格（`TableLayout`）：固定/拉伸/自动列宽、行高、header、冻结行列、cell clip、排序 spec
- 键盘导航（`NavState`）：Tab/Shift+Tab、方向键、Enter/Space、焦点请求
- popup / menu：按下打开、再次点击关闭、点击外部关闭、hover 切换菜单、modal 调暗背景
- popup / tooltip 始终绘制在普通窗口之上
- drag & drop 的最小 payload 路径
- `ImGuiListClipper` 可见区间裁剪

### 绘制 / 字体

- `ImDrawData` 顶点/索引/命令缓冲（imgui-java renderer 契约）
- `ImDrawList`：矩形（圆角/边框）、线、圆、三角、quad、图片、clip、path/polyline/bezier/ngon
- `TrueTypeFont`：
  - cmap 4/12、loca、glyf、hmtx、复合字形、非零环绕填充、隐含中点二次曲线
  - 复合变换、`SCALED_COMPONENT_OFFSET`、空格 advance
- `CffFont`：
  - CFF INDEX / Top DICT / Private DICT / Type2
  - `hvcurveto`/`vhcurveto`、`rcurveline`、`hlineto`/`vlineto`、`vvcurveto`/`hhcurveto`、`flex1`/`hflex`/`hflex1`
  - CID 检测
- 字体 atlas：透明背景 + RGBA 字形、按绘制像素尺寸取字形、merge 字体 fallback
- `ImFontConfig`：merge / glyph offset / ranges / oversample / name
- 真实 dark / light / classic 配色（`StyleColors`，62 个 ImGuiCol）
- 独立 `ImGuiStyle` 实例（`create()` + self 分派）

### 扩展

- `TextEditor`：独立句柄、文本、行号、光标、只读、marker、Lua 等语言工厂
- `TextEditorLanguage` 的 native 静态工厂整体替换为纯 Java

## 已知限制

- 没有真正的多 viewport（`ViewportsEnable` 被屏蔽），`ImGuiViewport` 只有主 viewport
- 没有 docking 拖拽停靠（只支持 ini 布局 + splitter 拖动）
- `ImPlot` / `ImNodes` / `ImGuizmo` 未实现（Axiom / Flashback 当前不调用）
- CFF2、CID-keyed CFF、TrueType point-matching composite 未实现
- 文本整形是逐字符 advance（无 kerning / shaping；Axiom 的字体不需要）
- ini 只读不写回（窗口位置/布局修改不会保存）

## 测试

模块级独立测试（JDK 25，不依赖 Gradle）：

```bash
./run/font-test/run.sh                     # TTF/CFF 解析 + 栅格化
javac -d /tmp/t src/main/java/com/noimgui/imgui/DockLayout.java \
      run/dock-test/DockLayoutTest.java && java -cp /tmp/t DockLayoutTest
javac -d /tmp/t src/main/java/com/noimgui/imgui/NavState.java \
      run/nav-test/com/noimgui/imgui/NavStateTest.java && java -cp /tmp/t com.noimgui.imgui.NavStateTest
javac -d /tmp/t src/main/java/com/noimgui/imgui/TableLayout.java \
      run/table-test/TableLayoutTest.java && java -cp /tmp/t TableLayoutTest
javac -d /tmp/t src/main/java/com/noimgui/imgui/StyleColors.java \
      run/style-test/StyleColorsTest.java && java -cp /tmp/t StyleColorsTest
javac -d /tmp/t src/main/java/com/noimgui/imgui/InputTextModel.java \
      run/input-test/InputTextTest.java && java -cp /tmp/t InputTextTest
```

完整构建与联调：

```bash
./gradlew build
cp build/libs/no-imgui-0.1.0.jar run/mods/
JAVA_TOOL_OPTIONS='-Dnoimgui.screenshot.raise=true -Dnoimgui.screenshot.ticks=20' \
  ./gradlew runClient --args='--username Test'
# 等待进入世界后：
spectacle -b -n -a -o run/screenshot-active.png
```

`ScreenshotHook` 使用 Minecraft 自身 framebuffer，但 Axiom/Flashback 的 ImGui overlay 不进入
该 target，所以只适合看世界渲染；UI 截图请用外部 active-window 方式。
