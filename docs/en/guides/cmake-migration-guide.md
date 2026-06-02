# CMake Build Guide

This document describes the standard configure / build workflow for Reskia.

Reskia uses `skia/CMakeLists.txt` as the CMake entry point, not a root-level `CMakeLists.txt`.

## Requirements

- CMake 3.26.4 or newer
- C++17 compiler
- For `source` mode, an environment that can install dependencies under `third_party/install`

macOS / AppleClang is the primary verified environment. Windows and Linux support may vary by feature flag and dependency mode.

## Dependency Modes

Use `RESKIA_DEPS_MODE` to choose how dependencies are resolved.

| mode | Default | Purpose |
| --- | --- | --- |
| `prebuilt` | yes | Use prebuilt or pre-installed dependencies for quick builds. |
| `source` | no | Use dependencies managed under `third_party` for better reproducibility. |
| `system` | no | Use dependencies provided by the OS or package manager. |

You can set the mode at configure time.

```bash
cmake -S skia -B skia/cmake-build-local -DRESKIA_DEPS_MODE=prebuilt
```

## `prebuilt` Mode

This is the shortest path for checking `reskia`.

```bash
cmake -S skia -B skia/cmake-build-prebuilt \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=prebuilt
cmake --build skia/cmake-build-prebuilt -j 8
```

If `RESKIA_DEPS_MODE` is omitted, Reskia defaults to `prebuilt`.

## `source` Mode

Use this mode when you want dependency setup to be reproducible.

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source -j 8
```

When enabling features with extra dependencies, align the dependency build options with the CMake feature flags.

Example:

```bash
scripts/build_third_party.sh --build-type Release --clean --with-avif
cmake -S skia -B skia/cmake-build-avif \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_AVIF=ON
```

## `system` Mode

Use dependencies installed on the system.

```bash
cmake -S skia -B skia/cmake-build-system \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=system
cmake --build skia/cmake-build-system -j 8
```

Set `CMAKE_PREFIX_PATH`, `PKG_CONFIG_PATH`, or package-specific `*_DIR` variables when needed.

## Tests

Tests are disabled by default. Enable them with `RESKIA_BUILD_TESTS=ON`.

```bash
cmake -S skia -B skia/cmake-build-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests -j 8
ctest --test-dir skia/cmake-build-tests --output-on-failure
```

Optional feature smoke tests are registered only when their feature flags and dependencies are available.

## Common Feature Flags

| Area | Main flags |
| --- | --- |
| Codec / encoder | `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_GIF`, `RESKIA_ENABLE_PDF`, `RESKIA_ENABLE_JPEG_ENCODER`, `RESKIA_ENABLE_WEBP_ENCODER` |
| Text / animation | `RESKIA_ENABLE_SKSG`, `RESKIA_ENABLE_SKOTTIE`, `RESKIA_ENABLE_SKPARAGRAPH`, `RESKIA_ENABLE_FONTCONFIG_CAPI` |
| GPU | `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN` |

Common constraints:

- `RESKIA_DEPS_MODE=source` on Windows is not implemented.
- `RESKIA_ENABLE_GPU_METAL=ON` requires an Apple platform.
- `RESKIA_ENABLE_GPU_DAWN=ON` requires `RESKIA_ENABLE_GPU_GRAPHITE=ON`.
- Text-stack features degrade depending on HarfBuzz, ICU, ICU4X, libgrapheme, and CoreText availability.

## Failure Checklist

When configure or build fails, capture at least:

1. The full configure command.
2. The value of `RESKIA_DEPS_MODE`.
3. Enabled `RESKIA_ENABLE_*` flags.
4. Whether dependencies are available under `third_party/install` or the system.
5. Whether platform-specific features were enabled.

Related documents:

- `docs/en/README.md`
- `third_party/README.md`
- `docs/en/guides/repository-structure.md`
