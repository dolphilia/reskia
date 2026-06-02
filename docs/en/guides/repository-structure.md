# Reskia Repository Structure

This document explains the main directories in Reskia and their responsibilities.

## Overview

Reskia builds Skia C++ sources with CMake and exposes them through a C ABI for use from other languages.

The repository has three main responsibilities:

1. Build Skia and related modules with CMake.
2. Expose Skia public APIs through `skia/capi` and `skia/handles`.
3. Track upstream Skia incrementally by fixed commit.

## Top Level

| Path | Role |
| --- | --- |
| `skia/` | Build entry point for the `reskia` shared library. Contains Skia sources, C APIs, handles, and tests. |
| `cmake/` | CMake helpers for dependency resolution, source lists, feature flags, and test registration. |
| `scripts/` | Scripts for upstream fetches, dependency builds, coverage generation, and checks. |
| `third_party/` | Dependency source / build / install management. |
| `vendor/` | Skia upstream reference checkout and lock file. |
| `bindings/` | Helper code for external language bindings. |
| `docs/` | Language-specific documentation. English docs live under `docs/en/`. |

The repository root does not contain a `CMakeLists.txt`. Use `skia/CMakeLists.txt`.

## `skia/`

`skia/` is the center of Reskia.

| Path | Role |
| --- | --- |
| `skia/CMakeLists.txt` | Entry point for the CMake project `reskia`. |
| `skia/include/` | Skia public headers. |
| `skia/src/` | Skia implementation sources. |
| `skia/capi/` | Pointer-oriented C API. |
| `skia/handles/` | Integer-handle API and handle table. |
| `skia/modules/` | Module integration for `skcms`, `skresources`, `svg`, `skpath`, and related code. |
| `skia/test/` | C API smoke and regression tests. |
| `skia/lib/` | Libraries used by prebuilt mode. |

The `reskia` target combines Skia sources, selected module sources, `skia/capi/*.cpp`, and `skia/handles/*.cpp` into a shared library.

## C API Layers

Reskia has two C API layers.

### `skia/capi`

`skia/capi` is the pointer-oriented API for using Skia objects from C.

Properties:

- Exposes `extern "C"` functions.
- Uses opaque pointer types such as `reskia_*_t`.
- Converts internally to Skia C++ types such as `SkCanvas*`.
- Documents ownership, NULL input behavior, borrowed pointers, and callback lifetimes in headers.

### `skia/handles`

`skia/handles` is the integer-handle API for language bindings.

Properties:

- Exposes integer handles such as `sk_image_t`.
- Stores objects in an internal `HandleTable`.
- Detects invalid and stale handles.
- Helps bindings avoid exposing raw pointers across language boundaries.

## C API Policy

Reskia exposes Skia public methods, static factories, and helpers where practical.

When adding or changing APIs, check:

- Whether the API exists in upstream Skia public headers.
- Whether it should be exposed through pointer APIs, handle APIs, or both.
- Whether the value is caller-owned, borrowed, retained, or consumed.
- Whether invalid input fails without crashing.
- Whether optional modules or platform dependencies are required.
- Whether the coverage matrix can represent the status.

See `docs/en/guides/c-api-safety-guidelines.md` for detailed safety rules.

## CMake Layout

The main CMake entry point is `skia/CMakeLists.txt`. Supporting definitions live under `cmake/`.

Main files:

- `cmake/deps/ReskiaDeps.cmake`: `RESKIA_DEPS_MODE` and dependency resolution.
- `cmake/reskia/sources-*.cmake`: source lists and feature-specific source registration.
- `cmake/reskia/tests.cmake`: test target registration.

Dependency modes:

- `prebuilt`: default mode using prebuilt dependencies.
- `source`: reproducible mode using `third_party/install`.
- `system`: use system dependencies.

See `docs/en/guides/cmake-migration-guide.md` for build instructions.

## `third_party/`

`third_party/` isolates dependency management.

| Path | Role |
| --- | --- |
| `third_party/src/` | Dependency source checkouts / submodules. |
| `third_party/build/` | Dependency build directories. |
| `third_party/install/` | Install prefix used by Reskia. |

Initialize and build dependencies with:

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
```

## `vendor/`

`vendor/` manages Skia upstream reference state.

| Path | Role |
| --- | --- |
| `vendor/skia-source.lock` | Skia commit accepted by Reskia. |
| `vendor/skia-upstream/` | Reference Skia checkout. Not tracked by Git. |
| `vendor/skia-upstream-candidate/` | Candidate checkout for upgrade probes. Used when needed. |

During Skia upgrades, candidate commits are pinned by hash. `vendor/skia-source.lock` is not updated until probe and verification pass.

## `docs/`

Documentation is organized by language.

| Path | Role |
| --- | --- |
| `docs/en/README.md` | English documentation root. |
| `docs/en/guides/` | Maintained guides for users and contributors. |
| `docs/ja/notes/` | Japanese research, design, and verification notes. |
| `docs/ja/plans/` | Japanese implementation plans, operation plans, and history. |

More translations can be added as `docs/de/`, `docs/fr/`, and so on.

## Frequently Used Files

- `docs/en/README.md`: entry point and basic build.
- `docs/en/guides/architecture-overview.md`: architecture overview.
- `docs/en/guides/cmake-migration-guide.md`: CMake / dependency mode.
- `docs/en/guides/c-api-bindings-overview.md`: C API / handle API overview.
- `docs/en/guides/c-api-safety-guidelines.md`: C API safety rules.
- `docs/en/guides/public-api-coverage-workflow.md`: public API coverage workflow.
- `docs/en/guides/skia-upgrade-workflow.md`: Skia upgrade workflow.
- `docs/en/guides/testing-and-stability.md`: build / smoke / stability checks.
- `scripts/generate_public_api_coverage.py`: public API coverage matrix generator.
- `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`: coverage matrix.
- `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md`: detailed Skia upgrade cycle plan.
