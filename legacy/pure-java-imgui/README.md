# Legacy: hand-written pure-Java ImGui port (archived)

This directory contains the previous implementation that re-implemented Dear
ImGui in Java and replaced every binding method with generated Mixins:

```
imgui/                 PureUi, DockLayout, TableLayout, fonts, etc.
mixin-imgui90/         generated @Overwrite mixins for Flashback 1.90
mixin-imgui92/         generated @Overwrite mixins for Axiom 1.92
generate_imgui_mixins.py
PORTING*.md            the old porting/gap analyses
```

It is **not** referenced by Gradle (`src/main/java` only), so it is not
compiled or shipped. It is kept only for historical comparison and for the
individual test harnesses under `run/*-test`.

The current implementation rebuilds the upstream C++ libraries and redirects
the two binding loaders; see [`native/README.md`](../../native/README.md) and
the root `README.md`.
