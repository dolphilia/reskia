# Phase 33 Full Build Sweep

作成時刻: 2026-05-21 20:18:09 JST

## Summary

Phase 33 は、Phase 29 final coverage freeze 後の代表 build health を確認する closeout phase。

結論:

- `missing 0` / `deferred 0` / `partial 0` / `overcovered 0` は維持。
- prebuilt mode の `reskia` main target は build 成功。
- source mode の `reskia` main target は build 成功。
- GPU prebuilt smoke target は build/run 成功。現在環境では Metal device unavailable を `SKIP` として扱い、exit 0 / `PASS`。
- source SVG/provider smoke target は build/run 成功。

## Coverage Check

Commands:

```sh
python3 scripts/generate_public_api_coverage.py
```

Status count:

| status | count |
| --- | ---: |
| `covered` | 2811 |
| `split_covered` | 33 |
| `false_positive` | 275 |
| `na` | 198 |
| `no_public_methods_found` | 104 |
| `missing` | 0 |
| `deferred` | 0 |
| `partial` | 0 |
| `overcovered` | 0 |
| total | 3421 |

## Main Target Builds

### Prebuilt

Build tree:

- `skia/cmake-build-codex-docrefresh-prebuilt`

Configuration:

- `RESKIA_DEPS_MODE=prebuilt`
- `RESKIA_BUILD_TESTS=OFF`
- GPU/PDF/SKSG/SKOTTIE/SKPARAGRAPH optional flags disabled

Command:

```sh
cmake --build skia/cmake-build-codex-docrefresh-prebuilt --target reskia -j 8
```

Result:

- pass
- linker emitted existing macOS deployment-version warnings for prebuilt `libskresources.a` / `libsvg.a` objects built for macOS 15.1 while linking target macOS 15.0
- no link failure

### Source

Build tree:

- `skia/cmake-build-codex-docrefresh-source`

Configuration:

- `RESKIA_DEPS_MODE=source`
- `RESKIA_BUILD_TESTS=OFF`
- GPU/PDF/SKSG/SKOTTIE/SKPARAGRAPH optional flags disabled

Command:

```sh
cmake --build skia/cmake-build-codex-docrefresh-source --target reskia -j 8
```

Result:

- pass

## Representative Smoke Builds

### GPU Prebuilt Smoke

Build tree:

- `skia/cmake-build-codex-phase9-gpu`

Configuration:

- `RESKIA_DEPS_MODE=prebuilt`
- `RESKIA_BUILD_TESTS=ON`
- `RESKIA_ENABLE_GPU_GANESH=ON`
- `RESKIA_ENABLE_GPU_METAL=ON`
- `RESKIA_ENABLE_GPU_GRAPHITE=OFF`

Command:

```sh
cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke test_gpu_surface_capi_smoke -j 8
```

Result:

- pass

Runtime:

```sh
skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke
skia/cmake-build-codex-phase9-gpu/test_gpu_surface_capi_smoke
```

Result:

- `test_gpu_context_capi_smoke`: `SKIP: Metal device is unavailable in this environment`, then `PASS`
- `test_gpu_surface_capi_smoke`: `SKIP: Metal device is unavailable in this environment`, then `PASS`

This is an expected pass condition for a build host without an available Metal device.

### Source SVG / skresources Smoke

Build tree:

- `skia/cmake-build-codex-phase3-svg-source`

Configuration:

- `RESKIA_DEPS_MODE=source`
- `RESKIA_BUILD_TESTS=ON`
- GPU optional flags disabled

Command:

```sh
cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_image_capi_smoke test_svg_types_capi_smoke test_svg_canvas_capi_smoke test_skresources_capi_smoke -j 8
```

Result:

- pass

Runtime:

```sh
skia/cmake-build-codex-phase3-svg-source/test_svg_image_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_types_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_canvas_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_skresources_capi_smoke
```

Result:

- `test_svg_image_capi_smoke`: pass
- `test_svg_types_capi_smoke`: `PASS`
- `test_svg_canvas_capi_smoke`: pass
- `test_skresources_capi_smoke`: pass

## Remaining Verification Boundaries

These are not coverage gaps:

- Metal runtime path cannot be fully exercised on this host because no Metal device is available. The GPU smoke explicitly treats this as `SKIP` plus `PASS`.
- Optional backend roadmaps for D3D/Vulkan/Dawn/GL loader/Metal allocator remain `na` until their build targets and native dependencies exist.
- Full `ctest` across every registered smoke target is not the Phase 33 gate, because not all test executables are built in each build tree and optional modules are feature-gated. Phase 30 defines the stable representative matrix.

## Closeout

Phase 33 closes the current coverage-expansion plan at:

- `missing 0`
- `deferred 0`
- `partial 0`
- `overcovered 0`

Future work should be tracked as one of:

1. Optional backend enablement with backend-specific build targets.
2. API polish discovered by downstream users.
3. CI/build matrix hardening.
4. Upstream Skia resync and regenerated coverage audit.
