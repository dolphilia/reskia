# Reskia

Reskia rebuilds Google Skia with CMake and provides C API bindings that are easier to use from other languages.

Main components:

- `skia/`: build entry point for the `reskia` shared library
- `skia/capi/`: pointer-oriented C API
- `skia/handles/`: integer-handle C API
- `cmake/`: dependency resolution, feature flags, and target helpers
- `third_party/`: source / build / install area for dependencies
- `vendor/`: Skia reference checkout and lock file

## Current Baseline

- Skia lock file: `vendor/skia-source.lock`
- Upstream reference checkout: `vendor/skia-upstream`
- C API coverage: `missing 0`, `deferred 0`, `partial 0`, `overcovered 0`
- The repository root does not contain a `CMakeLists.txt`; use `skia/CMakeLists.txt` as the CMake entry point.

Skia upgrades are handled incrementally. Each upgrade chooses a fixed commit, validates coverage / build / smoke results, and only then updates the lock file. A floating `main` branch is not used as a baseline.

## Build Requirements

- CMake 3.26.4 or newer
- C++17 compiler
- macOS / AppleClang is the primary verified environment

Some features depend on OS support or optional libraries. When dependencies are missing, Reskia falls back to minimal implementations where possible.

## Basic Build

The default dependency mode is `prebuilt`.

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

In `source` mode, prepare dependencies under `third_party/install` before configuring.

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source-local -j 8
```

To enable tests:

```bash
cmake -S skia -B skia/cmake-build-tests-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests-local -j 8
ctest --test-dir skia/cmake-build-tests-local --output-on-failure
```

## Dependency Modes

Use `RESKIA_DEPS_MODE` to choose how dependencies are resolved.

| mode | Purpose |
| --- | --- |
| `prebuilt` | Default. Use prebuilt or pre-installed dependencies for quick checks. |
| `source` | Use dependencies managed under `third_party` for better reproducibility. |
| `system` | Use dependencies provided by the OS or package manager. |

See `docs/en/guides/cmake-migration-guide.md` for details.

## Main Feature Flags

Feature flags are defined mainly in `cmake/deps/ReskiaDeps.cmake`.

- Codec / encoder: `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_GIF`, `RESKIA_ENABLE_PDF`, `RESKIA_ENABLE_JPEG_ENCODER`, `RESKIA_ENABLE_WEBP_ENCODER`
- Text / animation: `RESKIA_ENABLE_SKSG`, `RESKIA_ENABLE_SKOTTIE`, `RESKIA_ENABLE_SKPARAGRAPH`, `RESKIA_ENABLE_FONTCONFIG_CAPI`
- GPU: `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN`

Common constraints:

- `RESKIA_ENABLE_GPU_METAL=ON` requires an Apple platform.
- `RESKIA_ENABLE_GPU_DAWN=ON` requires `RESKIA_ENABLE_GPU_GRAPHITE=ON`.
- `RESKIA_ENABLE_SKPARAGRAPH=ON` requires text-stack dependencies such as HarfBuzz.

## C API Policy

Reskia exposes Skia public classes, public methods, static factories, and helpers through a C ABI where practical.

There are two API boundaries:

- `skia/capi`: pointer-oriented API for direct C usage
- `skia/handles`: integer-handle API for language bindings that should avoid raw pointers

When adding or changing C APIs, document ownership, NULL input behavior, invalid handle behavior, borrowed lifetimes, and callback lifetimes. See `docs/en/guides/c-api-safety-guidelines.md`.

## Skia Upgrades

Skia upgrades use the fixed commit in `vendor/skia-source.lock` as the current baseline.

Basic rules:

- Treat `vendor/skia-upstream` as a reference checkout.
- Pin each candidate by commit hash.
- Do not update `vendor/skia-source.lock` until the probe passes.
- Check the coverage matrix and stale C API report.
- Update the lock only after build and smoke checks pass.

The workflow overview is in `docs/en/guides/skia-upgrade-workflow.md`. The detailed cycle plan remains in `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md`.

## Main Documents

- `docs/en/guides/repository-structure.md`: repository structure
- `docs/en/guides/cmake-migration-guide.md`: CMake and dependency modes
- `docs/en/guides/architecture-overview.md`: architecture overview
- `docs/en/guides/c-api-bindings-overview.md`: C API / handle binding overview
- `docs/en/guides/c-api-safety-guidelines.md`: C API safety rules
- `docs/en/guides/public-api-coverage-workflow.md`: public API coverage workflow
- `docs/en/guides/skia-upgrade-workflow.md`: Skia upgrade workflow
- `docs/en/guides/testing-and-stability.md`: build, smoke, and stability checks
