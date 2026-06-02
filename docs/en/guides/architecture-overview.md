# Reskia Architecture Overview

This document explains what Reskia is intended to provide and how its main boundaries are organized. For a directory-level overview, see `docs/en/guides/repository-structure.md`.

## Purpose

Reskia rebuilds Skia through CMake and exposes a C ABI that is easier to use from other languages.

Core ideas:

1. Keep Skia sources under `skia/` and build them as the `reskia` shared library.
2. Bridge Skia C++ APIs to C ABI through `skia/capi` and `skia/handles`.
3. Control dependency resolution and optional features through CMake flags.
4. Track upstream Skia incrementally by fixed commit.

## Main Boundaries

| Boundary | Role |
| --- | --- |
| CMake boundary | `skia/CMakeLists.txt` and `cmake/` collect sources, dependencies, feature flags, and tests. |
| C ABI boundary | `skia/capi` exposes pointer-oriented APIs; `skia/handles` exposes integer-handle APIs. |
| Dependency boundary | `third_party` and `RESKIA_DEPS_MODE` define how dependencies are provided. |
| Upstream boundary | `vendor/skia-source.lock` and `vendor/skia-upstream` separate the accepted commit from the reference checkout. |
| Documentation boundary | `docs/*/guides` contain maintained guides; `notes` and `plans` contain research, planning, and history. |

## Build Flow

The primary CMake entry point is `skia/CMakeLists.txt`.

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

At configure time, choose `RESKIA_DEPS_MODE` and any `RESKIA_ENABLE_*` flags.

- `RESKIA_DEPS_MODE=prebuilt`: default mode using prebuilt dependencies.
- `RESKIA_DEPS_MODE=source`: use dependencies installed under `third_party/install`.
- `RESKIA_DEPS_MODE=system`: use system dependencies.

See `docs/en/guides/cmake-migration-guide.md` for details.

## C API Flow

Reskia converts Skia C++ objects into C ABI surfaces.

```text
caller
  -> skia/capi/*.h
  -> skia/capi/*.cpp
  -> Skia C++ API
```

When using the handle API, a handle table sits between the C API and Skia objects.

```text
caller
  -> skia/handles/static_*.h
  -> HandleTable
  -> Skia C++ object
```

The pointer API is closer to Skia itself. The handle API is better for language bindings that should avoid exposing raw pointers.

## Dependencies and Feature Flags

Reskia does not enable every Skia feature unconditionally. Features are enabled in stages depending on platform support and available dependencies.

Examples:

- PDF, codecs, and encoders depend on related libraries and CMake flags.
- GPU backends depend on platform and backend-specific prerequisites.
- The text stack degrades depending on HarfBuzz, ICU, ICU4X, libgrapheme, and CoreText availability.

When dependencies are missing, Reskia falls back to minimal implementations where possible. Features that cannot degrade should fail clearly at configure time or leave optional tests unregistered.

## Upstream Tracking

Skia tracking uses the fixed commit in `vendor/skia-source.lock` as the current baseline.

Basic rules:

- Pin candidates by commit hash.
- Do not update the lock before the probe passes.
- Check public API coverage and stale C API reports.
- Complete source sync, C API catch-up, and build / smoke checks before closing a cycle.

See `docs/en/guides/skia-upgrade-workflow.md` for details.

## First Documents for Contributors

- `docs/en/README.md`: main entry point.
- `docs/en/guides/repository-structure.md`: directory structure.
- `docs/en/guides/cmake-migration-guide.md`: CMake build.
- `docs/en/guides/c-api-bindings-overview.md`: C API / handle API overview.
- `docs/en/guides/c-api-safety-guidelines.md`: C ABI safety rules.
- `docs/en/guides/public-api-coverage-workflow.md`: coverage matrix workflow.
