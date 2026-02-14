#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
THIRD_PARTY_DIR="${ROOT_DIR}/third_party"
SRC_DIR="${THIRD_PARTY_DIR}/src"
BUILD_DIR="${THIRD_PARTY_DIR}/build"
INSTALL_DIR="${THIRD_PARTY_DIR}/install"

BUILD_TYPE="Release"
JOBS=""
CLEAN=0
WITH_AVIF=0
WITH_HARFBUZZ=0
WITH_LIBGRAPHEME=0

usage() {
  cat <<USAGE
Usage: scripts/build_third_party.sh [options]

Options:
  --build-type <Debug|Release>  Build type (default: Release)
  --jobs <N>                    Parallel jobs (default: auto)
  --clean                       Remove each build directory before configure
  --with-avif                   Build and install libavif (experimental)
  --with-harfbuzz               Build and install harfbuzz (minimal feature set)
  --with-libgrapheme            Build and install libgrapheme
  -h, --help                    Show this help
USAGE
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --build-type)
      BUILD_TYPE="$2"
      shift 2
      ;;
    --jobs)
      JOBS="$2"
      shift 2
      ;;
    --clean)
      CLEAN=1
      shift
      ;;
    --with-avif)
      WITH_AVIF=1
      shift
      ;;
    --with-harfbuzz)
      WITH_HARFBUZZ=1
      shift
      ;;
    --with-libgrapheme)
      WITH_LIBGRAPHEME=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [[ -z "${JOBS}" ]]; then
  if command -v sysctl >/dev/null 2>&1; then
    JOBS="$(sysctl -n hw.ncpu)"
  elif command -v nproc >/dev/null 2>&1; then
    JOBS="$(nproc)"
  else
    JOBS=4
  fi
fi

mkdir -p "${BUILD_DIR}" "${INSTALL_DIR}"

require_dir() {
  if [[ ! -d "$1" ]]; then
    echo "Missing source directory: $1" >&2
    echo "Run: scripts/bootstrap_third_party.sh" >&2
    exit 1
  fi
}

cmake_build_install() {
  local name="$1"
  local src="$2"
  shift 2
  local bdir="${BUILD_DIR}/${name}"

  require_dir "${src}"
  if [[ ${CLEAN} -eq 1 ]]; then
    rm -rf "${bdir}"
  fi

  cmake -S "${src}" -B "${bdir}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
    -DCMAKE_PREFIX_PATH="${INSTALL_DIR}" \
    "$@"

  cmake --build "${bdir}" -j "${JOBS}"
  cmake --install "${bdir}"
}

echo "[reskia] build third-party dependencies"
echo "  build type: ${BUILD_TYPE}"
echo "  jobs:       ${JOBS}"
echo "  prefix:     ${INSTALL_DIR}"

cmake_build_install zlib "${SRC_DIR}/zlib" \
  -DBUILD_SHARED_LIBS=OFF \
  -DZLIB_BUILD_TESTING=OFF

cmake_build_install libpng "${SRC_DIR}/libpng" \
  -DPNG_SHARED=OFF \
  -DPNG_TESTS=OFF \
  -DPNG_EXECUTABLES=OFF \
  -DPNG_TOOLS=OFF

cmake_build_install libjpeg-turbo "${SRC_DIR}/libjpeg-turbo" \
  -DENABLE_SHARED=OFF \
  -DENABLE_STATIC=ON \
  -DWITH_TURBOJPEG=ON \
  -DWITH_JPEG8=ON

cmake_build_install expat "${SRC_DIR}/expat/expat" \
  -DBUILD_SHARED_LIBS=OFF \
  -DEXPAT_BUILD_DOCS=OFF \
  -DEXPAT_BUILD_EXAMPLES=OFF \
  -DEXPAT_BUILD_TESTS=OFF \
  -DEXPAT_BUILD_TOOLS=OFF

cmake_build_install libwebp "${SRC_DIR}/libwebp" \
  -DBUILD_SHARED_LIBS=OFF \
  -DWEBP_BUILD_ANIM_UTILS=OFF \
  -DWEBP_BUILD_CWEBP=OFF \
  -DWEBP_BUILD_DWEBP=OFF \
  -DWEBP_BUILD_GIF2WEBP=OFF \
  -DWEBP_BUILD_IMG2WEBP=OFF \
  -DWEBP_BUILD_VWEBP=OFF \
  -DWEBP_BUILD_WEBPINFO=OFF \
  -DWEBP_BUILD_LIBWEBPMUX=ON \
  -DWEBP_BUILD_LIBWEBPDEMUX=ON

if [[ ${WITH_HARFBUZZ} -eq 1 ]]; then
  cmake_build_install harfbuzz "${SRC_DIR}/harfbuzz" \
    -DBUILD_SHARED_LIBS=OFF \
    -DHB_BUILD_SUBSET=OFF \
    -DHB_BUILD_UTILS=OFF \
    -DHB_HAVE_FREETYPE=OFF \
    -DHB_HAVE_GLIB=OFF \
    -DHB_HAVE_ICU=OFF
fi

if [[ ${WITH_AVIF} -eq 1 ]]; then
  # LOCAL tells libavif to fetch codec deps during configure if needed.
  cmake_build_install libavif "${SRC_DIR}/libavif" \
    -DBUILD_SHARED_LIBS=OFF \
    -DAVIF_BUILD_APPS=OFF \
    -DAVIF_BUILD_TESTS=OFF \
    -DAVIF_CODEC_AOM=LOCAL
fi

if [[ ${WITH_LIBGRAPHEME} -eq 1 ]]; then
  require_dir "${SRC_DIR}/libgrapheme"
  if [[ ${CLEAN} -eq 1 ]]; then
    rm -rf "${BUILD_DIR}/libgrapheme"
  fi
  mkdir -p "${BUILD_DIR}/libgrapheme"
  (
    cd "${SRC_DIR}/libgrapheme"
    ./configure
    make -j "${JOBS}"
    make install PREFIX="${INSTALL_DIR}"
  )
fi

cat <<OUT
[reskia] done.
Installed prefix:
- ${INSTALL_DIR}

Next step:
  cmake -S skia -B skia/cmake-build-source-local -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
  cmake --build skia/cmake-build-source-local -j ${JOBS}
OUT
