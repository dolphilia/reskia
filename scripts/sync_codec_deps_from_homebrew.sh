#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
INSTALL_DIR="${ROOT_DIR}/third_party/install"
BREW_PREFIX="${HOMEBREW_PREFIX:-/opt/homebrew}"

SRC_LIB_DIR="${BREW_PREFIX}/lib"
SRC_INCLUDE_DIR="${BREW_PREFIX}/include"
DST_LIB_DIR="${INSTALL_DIR}/lib"
DST_INCLUDE_DIR="${INSTALL_DIR}/include"

if [[ ! -d "${SRC_LIB_DIR}" || ! -d "${SRC_INCLUDE_DIR}" ]]; then
  echo "[reskia] Homebrew prefix not found: ${BREW_PREFIX}" >&2
  exit 1
fi

mkdir -p "${DST_LIB_DIR}" "${DST_INCLUDE_DIR}"

link_file() {
  local src="$1"
  local dst="$2"
  if [[ ! -e "${src}" ]]; then
    echo "[reskia] missing: ${src}" >&2
    return 1
  fi
  ln -sfn "${src}" "${dst}"
}

link_dir() {
  local src="$1"
  local dst="$2"
  if [[ ! -e "${src}" ]]; then
    echo "[reskia] missing: ${src}" >&2
    return 1
  fi
  ln -sfn "${src}" "${dst}"
}

required_libs=(
  "libavif.dylib"
  "libjxl.dylib"
  "libjxl_threads.dylib"
  "libjxl_cms.dylib"
)

optional_libs=(
  "libhwy.dylib"
  "liblcms2.dylib"
)

for lib in "${required_libs[@]}"; do
  link_file "${SRC_LIB_DIR}/${lib}" "${DST_LIB_DIR}/${lib}"
done

for lib in "${optional_libs[@]}"; do
  if [[ -e "${SRC_LIB_DIR}/${lib}" ]]; then
    link_file "${SRC_LIB_DIR}/${lib}" "${DST_LIB_DIR}/${lib}"
  fi
done

required_headers=(
  "avif"
  "jxl"
  "hwy"
  "lcms2.h"
  "lcms2_plugin.h"
)

for header in "${required_headers[@]}"; do
  link_dir "${SRC_INCLUDE_DIR}/${header}" "${DST_INCLUDE_DIR}/${header}"
done

cat <<OUT
[reskia] codec deps synced from Homebrew.
  source: ${BREW_PREFIX}
  target: ${INSTALL_DIR}

Next step:
  cmake -S skia -B skia/cmake-build-phase4-source-on \\
    -DRESKIA_DEPS_MODE=source \\
    -DRESKIA_ENABLE_AVIF=ON \\
    -DRESKIA_ENABLE_JPEGXL=ON \\
    -DRESKIA_ENABLE_RAW=ON \\
    -DRESKIA_ENABLE_GIF=ON \\
    -DRESKIA_ENABLE_JPEG_ENCODER=ON \\
    -DRESKIA_ENABLE_WEBP_ENCODER=ON \\
    -DCMAKE_BUILD_TYPE=Debug
  cmake --build skia/cmake-build-phase4-source-on -j 8
OUT
