> **LEGACY:** this document describes the removed/optional hand-written Java ImGui port.
> The default implementation is now the rebuilt upstream C++ backend; see `native/README.md`.

# PORTING_LAYOUT_REVIEW

Review of the live pure-Java ImGui port against Dear ImGui 1.92.7
(`reference/imgui-java/include/imgui/imgui.cpp`). Produced read-only; line
numbers refer to the reviewed snapshot (`PureUi.java` ~4666 lines) and have
drifted since, so use the quoted snippets / function names to re-locate.

## Defects

| # | Defect | Severity | Affects |
|---|---|---|---|
| L1 | Dock root rect is `(0, menuBarHeight, displayW, displayH-menuBarHeight)` instead of viewport `WorkPos/WorkSize`; Axiom status-bar inset and Flashback `Pos=0,22` ignored; `menuBarSeen` sticky | Critical | both |
| L2 | `dockSpaceOverViewport()` returns `1`; `setNextWindowDockID(rootId)` not resolved to the central leaf; `isMain` forces `Main` full display; `addLocalFlags(4096)` no-op | Critical | both |
| L3 | Docked content offset by `titleHeight` twice (24 px low), height 16-40 px short; single-window / `NoTabBar` nodes get phantom 24 px title | High | all docked panels |
| L4 | `begin()` uses `multiple` instead of `DockLayout.hasTabBar()`; runtime `NoTabBar`/`HiddenTabBar` not applied | High | Main windows |
| L5 | Splitter drag direction inverted on right/bottom half | High | both |
| L6 | `BeginChild` ignores scroll, padding, scrollbar, parent clip; advances parent cursor too early; `EndChild` never `ItemSize`s actual child | High | panels, timeline |
| L7 | Content size / ScrollMax / auto-resize math wrong (`contentHeight` double counts, `contentH` subtracts twice, no scrollbar reserve) | High | scrolling / auto-size |
| L8 | Main menu bar flags wrong (NoBackground, missing MenuBar), no work-area inset, list never invalidated, drawn last | High | both menus |
| L9 | Draw-list clip replaces instead of intersects; hit-testing ignores clip | Med-High | both |
| L10 | Capture flags lack click ownership, modal-only keyboard capture, tri-state override | Medium | Axiom world input |
| L11 | Wheel scrolls every window with fixed 40 px instead of topmost hovered + `trunc(min(5*FontSize, 0.67*InnerH))` | Medium | both |
| L12 | `SetNextWindowFocus` forces full-screen rect for docked windows; `SetNextWindowPos` never undocks | Medium | popups |
| L13 | `DockLayout` configured with `WindowMinSize(40,40)` instead of style `32x32` | Low-Med | split limits |
| L14 | `iniKey()` drops `label###id` prefixes; tab selection uses one hash rule; tab width hard-coded `+16` | Low | future builds |
| L15 | Menu-bar window gets a scrollbar | Low | menu bar |
| L16 | `render()` appends main menu draw list last (always on top) | Low-Med | floating windows |

## Fix order

1. L2 + L1: real dockspace id, resolve dock id to central leaf, remove
   `isMain` full-screen, install viewport work rect.
2. L3 + L4: docked rect = node rect; title height from
   `NoTabBar/HiddenTabBar` + runtime flags; content `h - titleH - 2*Padding`.
3. L5: splitter sign; style-derived hit expansion.
4. L8 + L16: menu-bar flags/background, per-frame list lifetime, draw order.
5. L6 + L7: child scroll/padding/clip; content/scroll/auto-resize formulas.
6. L9 + L10 + L11: clip intersection and hit gating; click ownership and
   tri-state capture; topmost wheel target.
7. L12-L15: focus/undock semantics, `WindowMinSize=32`, dual hash match, tab
   width.

## Regression warnings

- Do not change `imHashStr` to `###`-reset semantics without the dual-hash
  tab match: Axiom's ini stores full-name CRC32 values, Flashback's stores
  post-`###` values.
- `DockLayout.updatePosSize`, `splitterRect`, `findTouchingNodes`,
  `resizeSplit` already match the reference; limit changes there to the
  caller's `childIndex` sign and `WindowMinSize`.
