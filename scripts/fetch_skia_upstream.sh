#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LOCK_FILE="${ROOT_DIR}/vendor/skia-source.lock"
DEST_DIR="${ROOT_DIR}/vendor/skia-upstream"

REMOTE_MODE="upstream"
REF_OVERRIDE=""

usage() {
  cat <<USAGE
Usage: scripts/fetch_skia_upstream.sh [options]

Options:
  --remote <upstream|fork>   Clone/fetch source (default: upstream)
  --ref <git-ref>            Override lock ref (commit/tag/branch)
  --dest <path>              Override destination dir (default: vendor/skia-upstream)
  -h, --help                 Show this help

Lock file:
  vendor/skia-source.lock
USAGE
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --remote)
      REMOTE_MODE="$2"
      shift 2
      ;;
    --ref)
      REF_OVERRIDE="$2"
      shift 2
      ;;
    --dest)
      DEST_DIR="$2"
      shift 2
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

if [[ ! -f "${LOCK_FILE}" ]]; then
  echo "Missing lock file: ${LOCK_FILE}" >&2
  exit 1
fi

# shellcheck source=/dev/null
source "${LOCK_FILE}"

REF="${SKIA_REF}"
if [[ -n "${REF_OVERRIDE}" ]]; then
  REF="${REF_OVERRIDE}"
fi

case "${REMOTE_MODE}" in
  upstream)
    ORIGIN_URL="${SKIA_UPSTREAM_URL}"
    ;;
  fork)
    ORIGIN_URL="${SKIA_FORK_URL}"
    ;;
  *)
    echo "--remote must be 'upstream' or 'fork'" >&2
    exit 1
    ;;
esac

mkdir -p "$(dirname "${DEST_DIR}")"

if [[ ! -d "${DEST_DIR}/.git" ]]; then
  git clone "${ORIGIN_URL}" "${DEST_DIR}"
fi

git -C "${DEST_DIR}" remote set-url origin "${ORIGIN_URL}"

if git -C "${DEST_DIR}" remote get-url upstream >/dev/null 2>&1; then
  git -C "${DEST_DIR}" remote set-url upstream "${SKIA_UPSTREAM_URL}"
else
  git -C "${DEST_DIR}" remote add upstream "${SKIA_UPSTREAM_URL}"
fi

if git -C "${DEST_DIR}" remote get-url fork >/dev/null 2>&1; then
  git -C "${DEST_DIR}" remote set-url fork "${SKIA_FORK_URL}"
else
  git -C "${DEST_DIR}" remote add fork "${SKIA_FORK_URL}"
fi

git -C "${DEST_DIR}" fetch --tags origin
git -C "${DEST_DIR}" fetch origin "${REF}"
git -C "${DEST_DIR}" checkout --detach FETCH_HEAD

CURRENT_COMMIT="$(git -C "${DEST_DIR}" rev-parse HEAD)"

cat <<OUT
[reskia] skia vendor sync completed.

Destination:
- ${DEST_DIR}

Origin mode:
- ${REMOTE_MODE}
- ${ORIGIN_URL}

Checked out:
- ${CURRENT_COMMIT}

Lock ref:
- ${SKIA_REF}
OUT
