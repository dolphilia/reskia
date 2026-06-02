# Testing and Stability Guide

This document summarizes the standard build, smoke, and stability checks for Reskia.

For per-API C safety rules, see `docs/en/guides/c-api-safety-guidelines.md`.

## Purpose

The main instability risks in Reskia are C ABI boundaries, dependency resolution, optional features, and platform differences.

Stability checks should verify that:

1. The `reskia` target builds in the standard configuration.
2. C APIs do not crash on invalid input.
3. Handle APIs safely handle invalid and stale handles.
4. Optional features are clearly disabled or skipped when dependencies are missing.
5. Skia upgrades detect coverage regressions and stale C APIs.

## Standard Build

Even for documentation or CMake-only changes, run configure / build when practical.

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

For dependency or source-list changes, also check `source` mode.

```bash
cmake -S skia -B skia/cmake-build-source-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source-local -j 8
```

## Tests

Enable tests with `RESKIA_BUILD_TESTS=ON`.

```bash
cmake -S skia -B skia/cmake-build-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests -j 8
ctest --test-dir skia/cmake-build-tests --output-on-failure
```

Optional feature tests are registered only when the corresponding feature flags and dependencies are available. Missing dependencies should result in an unregistered test or a clear skip.

## C API Smoke Tests

When changing C APIs, add smoke coverage according to the risk being changed.

Prioritize:

- NULL receiver.
- Required pointer NULL.
- Invalid handle.
- Stale handle.
- Invalid rowBytes / buffer.
- Factory failure.
- Borrowed pointer lifetime.
- Callback NULL no-op.
- Callback context behavior.
- Returned handle delete / release.

Not every API needs every case. Choose the minimum cases that match the API contract.

For `void` APIs, no-crash behavior is the smoke check. For APIs with return values, explicitly check the invalid-input return value.

Tests often have early returns, so release every added handle / pointer on every exit path.

## Coverage Gate

For public API coverage changes, run the coverage generator.

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

The normal goal is to keep `missing` / `deferred` / `partial` / `overcovered` at zero. The stale report should normally contain only the header row.

## Feature Flag Gate

When changing feature flags, check:

- Whether required dependencies are detected during configure.
- Whether missing dependencies disable the feature clearly.
- Whether unsupported platforms fail with a clear message.
- Whether optional tests are not registered accidentally when dependencies are missing.

Examples:

- `RESKIA_ENABLE_GPU_METAL=ON` requires an Apple platform.
- `RESKIA_ENABLE_GPU_DAWN=ON` requires Graphite.
- The text stack degrades depending on HarfBuzz, ICU, ICU4X, libgrapheme, and CoreText availability.

## Sanitizer

For changes involving ownership, callbacks, borrowed pointers, or buffers, run a sanitizer build when practical.

Example:

```bash
cmake -S skia -B skia/cmake-build-asan \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON \
  -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build skia/cmake-build-asan -j 8
ctest --test-dir skia/cmake-build-asan --output-on-failure
```

Some environments require extra work when sanitizer flags are combined with prebuilt dependencies. Record the failure condition when that happens.

## Minimum Checks by Change Type

| Change type | Minimum checks |
| --- | --- |
| docs only | `git diff --check`; standard build when appropriate. |
| CMake source list | configure / build; affected modes for feature flag changes. |
| C API header / implementation | build, relevant smoke tests, coverage matrix. |
| handles | invalid / stale handle smoke tests. |
| upstream Skia sync | candidate coverage, stale report, build / smoke, post-lock regeneration. |
| dependency script | relevant `bootstrap_third_party.sh` / `build_third_party.sh` mode checks. |

## Related Documents

- `docs/en/guides/cmake-migration-guide.md`
- `docs/en/guides/c-api-safety-guidelines.md`
- `docs/en/guides/public-api-coverage-workflow.md`
- `docs/en/guides/skia-upgrade-workflow.md`
