#!/usr/bin/env bash
#
# Install the Android NDK used by native/build.sh.
#
# The official Google download was the fastest source on the development
# machine (~47 MB/s). Tencent's Android SDK mirror is used as a fallback.
# No root is required; the NDK is unpacked into the normal SDK layout:
#
#   ${ANDROID_HOME:-$HOME/Android/Sdk}/ndk/27.2.12479018
#
# build.sh already searches that path, so no environment variable is needed.
set -euo pipefail

VERSION="27.2.12479018"
RELEASE="r27c"
SHA1="090e8083a715fdb1a3e402d0763c388abb03fb4e"
URLS=(
  "https://dl.google.com/android/repository/android-ndk-${RELEASE}-linux.zip"
  "https://mirrors.cloud.tencent.com/AndroidSDK/android-ndk-${RELEASE}-linux.zip"
)

SDK="${ANDROID_HOME:-${ANDROID_SDK_ROOT:-$HOME/Android/Sdk}}"
DEST="$SDK/ndk/$VERSION"
TMP="${TMPDIR:-/tmp}/android-ndk-${RELEASE}-linux.zip"

log() { printf '\033[1;34m[ndk]\033[0m %s\n' "$*"; }
die() { printf '\033[1;31m[ndk]\033[0m %s\n' "$*" >&2; exit 1; }

if [[ -f "$DEST/source.properties" ]] \
    && grep -q "Pkg.Revision = $VERSION" "$DEST/source.properties"; then
  log "NDK $VERSION already installed at $DEST"
  exit 0
fi

command -v curl >/dev/null || die "curl is required"
command -v sha1sum >/dev/null || die "sha1sum is required"

download() {
  local url=$1
  log "downloading $url"
  curl -L --retry 5 --retry-delay 3 --continue-at - --output "$TMP" "$url" || return 1
  [[ -s "$TMP" ]] || return 1
  local actual
  actual=$(sha1sum "$TMP" | awk '{print $1}')
  if [[ "$actual" != "$SHA1" ]]; then
    log "checksum mismatch ($actual), discarding partial file"
    rm -f "$TMP"
    return 1
  fi
  return 0
}

installed=0
for url in "${URLS[@]}"; do
  if download "$url"; then
    installed=1
    break
  fi
  log "source failed, trying the next mirror"
done
[[ $installed -eq 1 ]] || die "could not download the NDK"

log "extracting to $DEST"
rm -rf "$DEST"
mkdir -p "$DEST"
if command -v bsdtar >/dev/null; then
  bsdtar -xf "$TMP" -C "$DEST" --strip-components=1
else
  tmpdir=$(mktemp -d)
  unzip -q "$TMP" -d "$tmpdir"
  cp -a "$tmpdir"/android-ndk-"$RELEASE"/. "$DEST"/
  rm -rf "$tmpdir"
fi
rm -f "$TMP"

CLANG="$DEST/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android24-clang++"
[[ -x "$CLANG" ]] || die "unexpected NDK layout: $CLANG not found"

log "installed $VERSION"
log "clang: $("$CLANG" --version | head -1)"
log "build with: ./native/build.sh android-aarch64"
