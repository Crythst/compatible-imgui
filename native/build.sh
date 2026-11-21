#!/usr/bin/env bash
#
# Cross-build the Dear ImGui JNI libraries used by Axiom (moulberry92) and
# Flashback (moulberry90).
#
# Desktop targets are built with Zig, which bundles libc/libc++ for every
# target and therefore does not need a macOS SDK or a Windows toolchain.
# Android is built with the Android NDK.
#
#   ./native/build.sh                       # all targets that have a toolchain
#   ./native/build.sh linux-x86_64          # one target
#   ZIG=/opt/zig/zig ./native/build.sh      # explicit Zig
#   STRICT=1 ./native/build.sh              # fail instead of skipping targets
#
# Output: build/native/resources/compatibleimgui/native/<platform>/<library>
# The Gradle build picks that directory up as an extra resource root.
set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
GENERATED=${GENERATED:-"$ROOT/native/generated"}
OUT=${OUT:-"$ROOT/build/native/resources"}
STRICT=${STRICT:-0}

COMMON_FLAGS=(
  -std=c++17
  -O2
  -fPIC
  -fvisibility=hidden
  -DNDEBUG
  -Wno-vla-cxx-extension
  -Wno-delete-incomplete
  -Wno-unused-parameter
  -Wno-deprecated-declarations
  -Wno-missing-field-initializers
  -Wno-unused-variable
)

log()  { printf '\033[1;34m[native]\033[0m %s\n' "$*"; }
warn() { printf '\033[1;33m[native]\033[0m %s\n' "$*" >&2; }
die()  { printf '\033[1;31m[native]\033[0m %s\n' "$*" >&2; exit 1; }

find_zig() {
  if [[ -n "${ZIG:-}" ]]; then
    if [[ -x "$ZIG" ]]; then printf '%s' "$ZIG"; return 0; fi
    if command -v "$ZIG" >/dev/null 2>&1; then command -v "$ZIG"; return 0; fi
    return 1
  fi
  if command -v zig >/dev/null 2>&1; then command -v zig; return 0; fi
  for candidate in \
      "$ROOT/tools/zigpkg/usr/bin/zig" \
      "$ROOT/tools/zig/zig" \
      "$ROOT"/tools/zig/zig-*/zig \
      "$ROOT/build/tools/zig/zig"; do
    if [[ -x "$candidate" ]]; then
      # The Arch package extracted into tools/zigpkg has its LLVM libraries
      # next to it rather than in the system loader path.
      if [[ "$candidate" == "$ROOT/tools/zigpkg/"* ]]; then
        export LD_LIBRARY_PATH="$ROOT/tools/zigpkg/usr/lib:${LD_LIBRARY_PATH:-}"
      fi
      printf '%s' "$candidate"
      return 0
    fi
  done
  return 1
}

find_ndk() {
  local candidates=()
  [[ -n "${ANDROID_NDK_HOME:-}" ]] && candidates+=("$ANDROID_NDK_HOME")
  [[ -n "${ANDROID_NDK_ROOT:-}" ]] && candidates+=("$ANDROID_NDK_ROOT")
  [[ -n "${ANDROID_HOME:-}" ]] && candidates+=("$ANDROID_HOME"/ndk/*)
  [[ -n "${ANDROID_SDK_ROOT:-}" ]] && candidates+=("$ANDROID_SDK_ROOT"/ndk/*)
  candidates+=(/opt/android-sdk/ndk/* /opt/android-ndk* "$HOME"/Android/Sdk/ndk/*)
  local c
  for c in "${candidates[@]}"; do
    [[ -d "$c" ]] || continue
    if compgen -G "$c/toolchains/llvm/prebuilt/*/bin/aarch64-linux-android*-clang++" >/dev/null; then
      printf '%s' "$c"
      return 0
    fi
  done
  return 1
}

java_home() {
  if [[ -n "${JAVA_HOME:-}" && -f "$JAVA_HOME/include/jni.h" ]]; then
    printf '%s' "$JAVA_HOME"
    return 0
  fi
  local javac
  javac=$(command -v javac || true)
  [[ -n "$javac" ]] || return 1
  local home
  home=$(dirname "$(dirname "$(readlink -f "$javac")")")
  [[ -f "$home/include/jni.h" ]] && { printf '%s' "$home"; return 0; }
  return 1
}

sources_for() {
  local dir=$1
  find "$dir" -maxdepth 1 -name '*.cpp' -print | sort | grep -v -E \
    '/(jni_implot\.cpp|.*_extension_(implot|imguizmo|imnodes|imguiknobs|imguifiledialog|nodeditor|memedit)_|.*_lwjgl3_)'
}

lib_name() {
  local version=$1 target=$2
  if [[ "$version" == "90" ]]; then
    case "$target" in
      windows-*) printf 'imgui-moulberry90-java64.dll' ;;
      macos-*)   printf 'libimgui-moulberry90-java64.dylib' ;;
      *)         printf 'libimgui-moulberry90-java64.so' ;;
    esac
  else
    case "$target" in
      windows-*) printf 'imgui-moulberry92-java64.dll' ;;
      macos-*)   printf 'libimgui-moulberry92-java64.dylib' ;;
      *)         printf 'libimgui-moulberry92-java64.so' ;;
    esac
  fi
}

compile_with() {
  local target=$1 version=$2
  shift 2
  local -a compiler=("$@")

  # The Arch package unpacked into tools/zigpkg keeps its LLVM libraries
  # beside the binary. Set this in the current shell (a command substitution
  # would not propagate the export).
  if [[ "${compiler[0]}" == "$ROOT/tools/zigpkg/"* ]]; then
    export LD_LIBRARY_PATH="$ROOT/tools/zigpkg/usr/lib:${LD_LIBRARY_PATH:-}"
  fi

  local dir="$GENERATED/$version"
  [[ -d "$dir" ]] || { warn "missing $dir; run native/generate.sh first"; return 1; }

  local jhome
  jhome=$(java_home) || { warn "JAVA_HOME/jni.h not found"; return 1; }

  local lib
  lib=$(lib_name "$version" "$target")
  local outdir="$OUT/compatibleimgui/native/$target"
  mkdir -p "$outdir"

  local -a includes=(-I"$dir" -I"$jhome/include")
  local -a platform_flags=()
  case "$target" in
    linux-*)   includes+=(-I"$jhome/include/linux") ;;
    windows-*) includes+=(-I"$ROOT/native/compat/win32") ;;
    macos-*)   includes+=(-I"$ROOT/native/compat/darwin") ;;
    android-*)
      local ndk sysroot prebuilt
      ndk=$(find_ndk) || { warn "Android NDK not found"; return 1; }
      prebuilt=$(find "$ndk/toolchains/llvm/prebuilt" -maxdepth 1 -mindepth 1 -type d | head -1)
      sysroot="$prebuilt/sysroot"
      includes=(-I"$dir" -I"$sysroot/usr/include")
      platform_flags+=(-static-libstdc++)
      ;;
  esac

  local -a link_flags=(-shared -s)
  case "$target" in
    linux-*)   link_flags+=(-Wl,-soname,"$lib" -pthread) ;;
    macos-*)   link_flags+=(-dynamiclib -Wl,-install_name,@rpath/"$lib") ;;
  esac
  # MinGW's driver does not link its C++ runtime statically by default.
  case "${compiler[*]}" in
    *mingw*|*x86_64-w64*|*g++) link_flags+=(-static-libgcc -static-libstdc++) ;;
  esac

  local -a sources
  mapfile -t sources < <(sources_for "$dir")
  [[ ${#sources[@]} -gt 0 ]] || { warn "no sources in $dir"; return 1; }

  log "$version -> $target ($lib, ${#sources[@]} sources)"
  if ! "${compiler[@]}" "${COMMON_FLAGS[@]}" "${platform_flags[@]}" "${includes[@]}" \
      "${sources[@]}" "${link_flags[@]}" -o "$outdir/$lib"; then
    warn "compile failed: $version -> $target"
    return 1
  fi
  [[ -s "$outdir/$lib" ]] || { warn "missing output: $outdir/$lib"; return 1; }
  # Zig emits import libraries / PDBs next to Windows DLLs. They are not
  # runtime artifacts and must not end up in the mod jar.
  find "$outdir" -maxdepth 1 -type f \
    \( -name '*.pdb' -o -name '*.lib' -o -name '*.exp' -o -name '*.ilk' \) -delete
  log "built $outdir/$lib"
}

target_linux_x86_64() {
  local zig
  if zig=$(find_zig); then
    compile_with linux-x86_64 "$1" "$zig" c++ -target x86_64-linux-gnu.2.17
  elif command -v clang++ >/dev/null 2>&1; then
    warn "Zig not found: Linux x86_64 will require the host glibc"
    compile_with linux-x86_64 "$1" clang++
  elif command -v g++ >/dev/null 2>&1; then
    warn "Zig not found: Linux x86_64 will require the host glibc"
    compile_with linux-x86_64 "$1" g++
  else
    return 1
  fi
}

target_linux_aarch64() {
  local zig
  if zig=$(find_zig); then
    compile_with linux-aarch64 "$1" "$zig" c++ -target aarch64-linux-gnu.2.17
  elif command -v aarch64-linux-gnu-g++ >/dev/null 2>&1; then
    compile_with linux-aarch64 "$1" aarch64-linux-gnu-g++
  else
    return 1
  fi
}

target_windows_x86_64() {
  local zig
  if zig=$(find_zig); then
    compile_with windows-x86_64 "$1" "$zig" c++ -target x86_64-windows-gnu
  elif command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
    compile_with windows-x86_64 "$1" x86_64-w64-mingw32-g++
  else
    return 1
  fi
}

target_windows_aarch64() {
  local zig
  zig=$(find_zig) || return 1
  compile_with windows-aarch64 "$1" "$zig" c++ -target aarch64-windows-gnu
}

target_macos_x86_64() {
  local zig
  zig=$(find_zig) || return 1
  compile_with macos-x86_64 "$1" "$zig" c++ -target x86_64-macos.10.15
}

target_macos_aarch64() {
  local zig
  zig=$(find_zig) || return 1
  compile_with macos-aarch64 "$1" "$zig" c++ -target aarch64-macos.11.0
}

target_android_aarch64() {
  local ndk prebuilt cc
  ndk=$(find_ndk) || return 1
  prebuilt=$(find "$ndk/toolchains/llvm/prebuilt" -maxdepth 1 -mindepth 1 -type d | head -1)
  cc=$(compgen -G "$prebuilt/bin/aarch64-linux-android24-clang++" | head -1)
  [[ -n "$cc" ]] || cc=$(compgen -G "$prebuilt/bin/aarch64-linux-android*-clang++" | head -1)
  [[ -n "$cc" ]] || return 1
  compile_with android-aarch64 "$1" "$cc" --target=aarch64-linux-android24
}

declare -A TARGETS=(
  [linux-x86_64]=target_linux_x86_64
  [linux-aarch64]=target_linux_aarch64
  [windows-x86_64]=target_windows_x86_64
  [windows-aarch64]=target_windows_aarch64
  [macos-x86_64]=target_macos_x86_64
  [macos-aarch64]=target_macos_aarch64
  [android-aarch64]=target_android_aarch64
)

if [[ $# -gt 0 ]]; then
  REQUESTED=("$@")
else
  REQUESTED=(linux-x86_64 linux-aarch64 windows-x86_64 windows-aarch64 macos-x86_64 macos-aarch64 android-aarch64)
fi

failed=0
for target in "${REQUESTED[@]}"; do
  fn=${TARGETS[$target]:-}
  [[ -n "$fn" ]] || { warn "unknown target: $target"; failed=1; continue; }
  ok=1
  for version in 90 92; do
    if ! "$fn" "$version"; then
      ok=0
    fi
  done
  if [[ $ok -eq 0 ]]; then
    failed=1
    if [[ "$STRICT" == "1" ]]; then
      die "target $target could not be built"
    else
      warn "skipped target $target (missing toolchain or sources)"
    fi
  fi
done

if [[ $failed -ne 0 && "$STRICT" == "1" ]]; then
  exit 1
fi
log "done: $OUT"
