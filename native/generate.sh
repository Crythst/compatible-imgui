#!/usr/bin/env bash
#
# Regenerate native/generated/{90,92} from the pinned upstream sources.
#
# This is only needed when upgrading Dear ImGui / the Moulberry binding.
# The generated C++ is committed, so normal builds (native/build.sh) do not
# need Gradle, Java 17 or network access.
#
# Requirements: curl, tar, python3, JDK 17+, network access.
set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
WORK=${WORK:-"$ROOT/build/native/upstream"}
GEN="$ROOT/native/generated"
LOCK="$ROOT/native/upstream.lock.json"

log()  { printf '\033[1;34m[gen]\033[0m %s\n' "$*"; }
warn() { printf '\033[1;33m[gen]\033[0m %s\n' "$*" >&2; }
die()  { printf '\033[1;31m[gen]\033[0m %s\n' "$*" >&2; exit 1; }

command -v curl >/dev/null || die "curl is required"
command -v tar >/dev/null || die "tar is required"
command -v python3 >/dev/null || die "python3 is required"

# Upstream Gradle only needs a JVM to run its wrapper; the Java toolchain is
# pinned by the project. Prefer Java 17/21 if present.
if [[ -z "${GENERATOR_JAVA_HOME:-}" ]]; then
  for jdk in /usr/lib/jvm/java-17-openjdk /usr/lib/jvm/java-21-openjdk; do
    [[ -x "$jdk/bin/java" ]] && { GENERATOR_JAVA_HOME=$jdk; break; }
  done
fi

download() {
  local url=$1 out=$2
  mkdir -p "$(dirname "$out")"
  if [[ -s "$out" ]] && gzip -t "$out" 2>/dev/null; then
    log "cached $out"
    return 0
  fi
  log "download $url"
  curl -L --retry 5 --retry-delay 3 --continue-at - --output "$out" "$url" || true
  if ! gzip -t "$out" 2>/dev/null; then
    warn "resume failed, restarting $out"
    rm -f "$out"
    curl -L --retry 5 --retry-delay 3 --output "$out" "$url" || true
  fi
  gzip -t "$out" 2>/dev/null || die "download failed: $url"
}

fetch_tar() {
  local url=$1 dest=$2 strip=${3:-1}
  local archive="$WORK/$(printf '%s' "$dest" | tr '/' '_').tar.gz"
  download "$url" "$archive"
  rm -rf "$dest"
  mkdir -p "$dest"
  tar -xzf "$archive" -C "$dest" --strip-components="$strip"
}

json() {
  python3 -c 'import json,sys; d=json.load(open(sys.argv[1])); print(d[sys.argv[2]][sys.argv[3]])' "$LOCK" "$1" "$2"
}

for version in 90 92; do
  tag=$(json "$version" tag)
  commit=$(json "$version" commit)
  imgui=$(json "$version" imgui)
  textEditor=$(json "$version" textEditor)

  src="$WORK/src-$version"
  log "=== $version ($tag, $commit) ==="

  if [[ ! -f "$src/gradlew" ]]; then
    fetch_tar "https://codeload.github.com/Moulberry/imgui-java/tar.gz/$commit" "$src"
  fi

  # Populate the two submodules that are required by the retained sources.
  fetch_tar "https://codeload.github.com/ocornut/imgui/tar.gz/$imgui" "$src/include/imgui"
  fetch_tar "https://codeload.github.com/goossens/ImGuiColorTextEdit/tar.gz/$textEditor" "$src/include/ImGuiColorTextEdit"

  # Release tarballs have no .git, and the 1.90 build asks Foojay for a JDK 8
  # toolchain. Pin the version and use the installed JDK instead.
  if [[ -f "$src/build.gradle" ]]; then
    sed -i "s|version = 'git describe --tags --always'.execute().text.trim().substring(1)|version = '${tag#v}'|" "$src/build.gradle"
    grep -rl 'JavaLanguageVersion.of(8)' --include='build.gradle' "$src" 2>/dev/null \
      | xargs -r sed -i 's/JavaLanguageVersion.of(8)/JavaLanguageVersion.of(17)/g'
  fi

  pushd "$src" >/dev/null
  if [[ -n "${GENERATOR_JAVA_HOME:-}" ]]; then
    export JAVA_HOME="$GENERATOR_JAVA_HOME"
    export PATH="$JAVA_HOME/bin:$PATH"
  fi

  log "generating JNI wrappers (the upstream native linker step is expected to fail)"
  ./gradlew :imgui-binding:compileJava :imgui-binding:generateLibs \
      -Denvs=linux -Dlocal --console=plain >"$WORK/gradle-$version.log" 2>&1 || true
  popd >/dev/null

  jni="$src/imgui-binding/build/jni"
  [[ -f "$jni/imgui.cpp" ]] || die "JNI generation failed for $version, see $WORK/gradle-$version.log"

  rm -rf "$GEN/$version"
  cp -a "$jni" "$GEN/$version"
  mkdir -p "$GEN/$version/LICENSES"
  cp "$src/LICENSE" "$GEN/$version/LICENSES/imgui-java-LICENSE" 2>/dev/null || true
  cp "$src/include/imgui/LICENSE.txt" "$GEN/$version/LICENSES/imgui-LICENSE.txt" 2>/dev/null || true
  cp "$src/include/ImGuiColorTextEdit/LICENSE" "$GEN/$version/LICENSES/ImGuiColorTextEdit-LICENSE" 2>/dev/null || true

  pushd "$GEN/$version" >/dev/null
  # Extensions that Axiom/Flashback do not call. Keeping them out avoids
  # pulling ImPlot/ImNodes/ImGuizmo/FileDialog/Knobs/node-editor sources into
  # every target. TextEditor is required by Axiom.
  rm -f *extension_implot_* \
        *extension_imguizmo_* \
        *extension_imnodes_* \
        *extension_imguiknobs_* \
        *extension_imguifiledialog_* \
        *extension_nodeditor_* \
        *extension_memedit_* \
        *lwjgl3_* \
        jni_implot.cpp jni_implot.h \
        _implot.h _imguizmo.h _imnodes.h _imguifiledialog.h \
        _imguiknobs.h _nodeeditor.h _memedit.h
  # Ensure the exact TextEditor version wins over any stale copy.
  cp "$src/include/ImGuiColorTextEdit/TextEditor.cpp" ./TextEditor.cpp
  cp "$src/include/ImGuiColorTextEdit/TextEditor.h" ./TextEditor.h

  # Android's jni.h only exposes JNI_VERSION_1_6 (JNI 1.8 is a desktop JDK
  # constant). 1.6 is sufficient for GetEnv and works on all targets.
  sed -i 's/JNI_VERSION_1_8/JNI_VERSION_1_6/g' ./jni_jvm.cpp

  # Flashback's 1.90 binding is the upstream `imgui` package relocated to
  # `imgui.moulberry90`. The native symbols, FindClass names and JNI type
  # descriptors must be relocated as well.
  if [[ "$version" == "90" ]]; then
    find . -type f \( -name '*.cpp' -o -name '*.h' \) -print0 | xargs -0 perl -pi -e '
      s/Java_imgui_(?!moulberry90_)/Java_imgui_moulberry90_/g;
      s{"imgui/(?!moulberry90/)}{"imgui/moulberry90/}g;
      s{Limgui/(?!moulberry90/)}{Limgui/moulberry90/}g;
      s/Limgui_(?!moulberry90_)/Limgui_moulberry90_/g;
    '
  fi
  popd >/dev/null

  log "generated $GEN/$version ($(find "$GEN/$version" -maxdepth 1 -name '*.cpp' | wc -l) sources)"
done

log "done. Review native/generated before committing."
