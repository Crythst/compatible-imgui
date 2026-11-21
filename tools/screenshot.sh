#!/usr/bin/env bash
# Capture the active game window. Run the game with:
#   JAVA_TOOL_OPTIONS='-Dcompatibleimgui.screenshot.raise=true' ./gradlew runClient ...
# so the game window is raised/always-on-top before this runs.
set -euo pipefail

OUT="${1:-run/screenshot-active.png}"
DELAY="${2:-60}"

sleep "$DELAY"
cd "$(dirname "$0")/.."
mkdir -p "$(dirname "$OUT")"
spectacle -b -n -a -o "$OUT"
echo "saved $OUT"
