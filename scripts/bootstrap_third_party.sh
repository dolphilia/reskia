#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
THIRD_PARTY_DIR="${ROOT_DIR}/third_party"
SRC_DIR="${THIRD_PARTY_DIR}/src"
BUILD_DIR="${THIRD_PARTY_DIR}/build"
INSTALL_DIR="${THIRD_PARTY_DIR}/install"

mkdir -p "${SRC_DIR}" "${BUILD_DIR}" "${INSTALL_DIR}"

if [[ -d "${ROOT_DIR}/.git" ]]; then
  git -C "${ROOT_DIR}" submodule update --init --recursive \
    third_party/src/zlib \
    third_party/src/libpng \
    third_party/src/libjpeg-turbo \
    third_party/src/libwebp \
    third_party/src/libavif \
    third_party/src/expat \
    third_party/src/harfbuzz \
    third_party/src/icu \
    third_party/src/icu4x \
    third_party/src/libgrapheme
fi

cat <<OUT
[reskia] third_party bootstrap completed.

Prepared directories:
- ${SRC_DIR}
- ${BUILD_DIR}
- ${INSTALL_DIR}

Next step:
  scripts/build_third_party.sh --build-type Release

Optional builds:
  scripts/build_third_party.sh --with-avif --with-harfbuzz --with-libgrapheme --with-icu --with-icu4x
OUT
