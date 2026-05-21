# Phase 30 Verification Matrix Hardening

作成時刻: 2026-05-21 20:08:48 JST

## Summary

Phase 29 で `missing 0` / `deferred 0` を final coverage freeze として固定した。

Phase 30 では、以降の作業で coverage freeze を壊したときに早く検出できるよう、generator check と代表 smoke target の verification matrix を整理する。

## Freeze Check

Coverage freeze の最小必須 check:

```sh
python3 scripts/generate_public_api_coverage.py
```

合格条件:

- `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` が再生成できる。
- `missing` / `deferred` / `partial` / `overcovered` が 0 のまま。
- 新しい non-zero 行が出た場合は、同じ変更内で実装、`na` / `false_positive` 分類、または design-required follow-up に routing する。

Phase 30 実行結果:

- `python3 scripts/generate_public_api_coverage.py`: pass

## Representative Smoke Matrix

Phase 30 時点では、全 CTest target の一括実行を freeze gate にしない。

理由:

- `RESKIA_BUILD_TESTS=ON` では多数の smoke が登録されるが、個別 target をまだ build していない build tree では `ctest -N` が未生成 executable warning を大量に出す。
- optional module と GPU backend は feature flag、dependency mode、実行環境に強く依存する。
- coverage freeze regression の検出には、generator check と代表 smoke の組み合わせが最も安定している。

代表 smoke:

| bucket | build tree | build target | run command | expected |
| --- | --- | --- | --- | --- |
| coverage generator | repo root | n/a | `python3 scripts/generate_public_api_coverage.py` | pass, freeze count unchanged |
| GPU Ganesh/Metal C API | `skia/cmake-build-codex-phase9-gpu` | `test_gpu_context_capi_smoke` | `skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke` | pass; Metal device unavailable is `SKIP` then `PASS` |
| GPU surface C API | `skia/cmake-build-codex-phase9-gpu` | `test_gpu_surface_capi_smoke` | `skia/cmake-build-codex-phase9-gpu/test_gpu_surface_capi_smoke` | pass; Metal device unavailable is `SKIP` then `PASS` |
| SVG image/provider C API | `skia/cmake-build-codex-phase3-svg-source` | `test_svg_image_capi_smoke` | `skia/cmake-build-codex-phase3-svg-source/test_svg_image_capi_smoke` | pass |
| SVG value/canvas C API | `skia/cmake-build-codex-phase3-svg-source` | `test_svg_types_capi_smoke` / `test_svg_canvas_capi_smoke` | direct executable run | pass |
| skresources provider C API | `skia/cmake-build-codex-phase3-svg-source` | `test_skresources_capi_smoke` | `skia/cmake-build-codex-phase3-svg-source/test_skresources_capi_smoke` | pass |

## Current Verification Result

実行した build:

```sh
cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke test_gpu_surface_capi_smoke -j 8
cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_image_capi_smoke test_svg_types_capi_smoke test_svg_canvas_capi_smoke test_skresources_capi_smoke -j 8
```

実行した smoke:

```sh
skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke
skia/cmake-build-codex-phase9-gpu/test_gpu_surface_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_image_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_types_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_canvas_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_skresources_capi_smoke
```

結果:

- `test_gpu_context_capi_smoke`: `SKIP: Metal device is unavailable in this environment` の後 `PASS`
- `test_gpu_surface_capi_smoke`: `SKIP: Metal device is unavailable in this environment` の後 `PASS`
- `test_svg_image_capi_smoke`: pass
- `test_svg_types_capi_smoke`: `PASS`
- `test_svg_canvas_capi_smoke`: pass
- `test_skresources_capi_smoke`: pass

## Feature-Gated Smoke Inventory

`cmake/reskia/tests.cmake` の C API smoke は大きく次の条件で分岐する。

| condition | smoke examples | Phase 30 handling |
| --- | --- | --- |
| always when `RESKIA_BUILD_TESTS=ON` | core invalid-input smoke、codec/images/path/paint/font/value object smoke | full sweep candidate, not Phase 30 freeze minimum |
| `APPLE AND TARGET svg` | `test_svg_dom_capi_smoke` | source SVG verification bucket |
| `APPLE AND TARGET svg AND TARGET skresources` | `test_svg_image_capi_smoke` | Phase 30 representative |
| always C API SVG value helpers | `test_svg_types_capi_smoke`, `test_svg_canvas_capi_smoke` | Phase 30 representative |
| `TARGET skresources` | `test_skresources_capi_smoke` | Phase 30 representative |
| `TARGET skunicode` | `test_unicode_capi_smoke` | Phase 33 full sweep candidate |
| `RESKIA_ENABLE_PDF` | `test_pdf_smoke` | optional backend bucket |
| `RESKIA_ENABLE_SKOTTIE` | `test_skottie_smoke` | optional backend bucket |
| `RESKIA_ENABLE_SKSG` | `test_sksg_smoke`, `test_sksg_capi_smoke` | optional backend bucket |
| `RESKIA_ENABLE_SKPARAGRAPH AND TARGET skshaper AND TARGET skunicode` | paragraph C API smoke | optional text stack bucket |
| `APPLE AND RESKIA_ENABLE_GPU_GANESH AND RESKIA_ENABLE_GPU_METAL` | `test_gpu_surface_capi_smoke` | Phase 30 representative with Metal skip allowed |
| `APPLE AND RESKIA_ENABLE_GPU_METAL AND (GANESH OR GRAPHITE)` | `test_gpu_context_capi_smoke` | Phase 30 representative with Metal skip allowed |

## Recommended Gate Order

For routine coverage work:

1. `python3 scripts/generate_public_api_coverage.py`
2. status count audit for `missing/deferred/partial/overcovered == 0`
3. build/run the touched module smoke target
4. if GPU/provider/callback code changed, build/run `test_gpu_context_capi_smoke`

For release-style verification:

1. Run the Phase 30 representative matrix.
2. Add feature-gated optional buckets enabled by the target build tree.
3. Treat GPU Metal device absence as pass only when the smoke prints `SKIP` and exits 0.
4. Do not treat an unavailable optional backend as coverage regression unless the matrix also gains `missing` / `deferred` rows.
