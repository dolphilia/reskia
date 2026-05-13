# 218 Phase 2 Batch HI: enum capabilities codecs gradient graphics rules

開始時刻: 2026-05-13 12:03:57 JST

## 目的

`217-phase-2-batch-hh-canvas-image-next-candidates.md` の「次バッチ候補」から、enum helper、`SkCapabilities`、`SkCodecs`、`SkGradientShader`、`SkGraphics` の 5 件を順に確認する。invalid enum / NULL receiver / factory failure / process-wide side effect の規約を C API 境界で固定し、同じ候補を再確認しないよう詳細台帳へ残す。

## 変更内容

- `skia/capi/sk_alpha_type.cpp` / `skia/capi/sk_blend_mode.cpp`
  - `SkAlphaType_SkAlphaTypeIsOpaque` が範囲外 enum を false にするようにした。
  - `SkBlendMode_SkBlendMode_AsCoeff` が範囲外 enum または NULL out params を false にするようにした。
  - `SkBlendMode_SkBlendMode_Name` が範囲外 enum を NULL にするようにした。
- `skia/capi/sk_capabilities.cpp`
  - `ref` / `unref` / `release` を NULL no-op にした。
  - `skslVersion` / `unique` を NULL で `0` / false にした。
  - `RasterBackend` は caller-owned const capabilities handle を返す規約として確認した。
- `skia/capi/sk_codecs.h`
  - 現状 `SkCodecs` の直接 C API 関数はなく、decoder-specific API に規約が分散していることを明記した。
- `skia/capi/sk_gradient_shader.cpp`
  - gradient factory 全体に geometry / colors / count / tile mode / interpolation guard を追加した。
  - Skia factory failure は NULL `sk_sp` を registry handle 化せず `0` に正規化するようにした。
  - `pos` / `localMatrix` は optional のままとした。
- `skia/capi/sk_graphics.cpp`
  - `SkGraphics_SetFontCacheCountLimit` の負値を拒否し、現在値を返すようにした。
  - `SkGraphics_DumpMemoryStatistics` を NULL dump no-op にした。
  - process-wide cache setter / purge 系の副作用規約をヘッダに明記した。
- `skia/test/test_enum_capabilities_graphics_invalid_input_smoke.cpp`
  - enum helper invalid / valid、capabilities NULL / raster backend handle、graphics negative count / NULL dump / purge no-op smoke を追加した。
- `skia/test/test_shader_invalid_input_smoke.cpp`
  - gradient factory invalid input と代表 valid `MakeLinear` returned handle smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `test_enum_capabilities_graphics_invalid_input_smoke` を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `enum_helper_sentinel_rules`
  - `capabilities_null_raster_backend`
  - `codecs_empty_header_decoder_delegation`
  - `gradient_shader_factories`
  - `graphics_global_cache_controls`
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_alpha_type.cpp/h`、`sk_blend_mode.cpp/h`、`sk_capabilities.cpp/h`、`sk_codecs.cpp/h`、`sk_gradient_shader.cpp/h`、`sk_graphics.cpp/h` を batch HI の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_enum_capabilities_graphics_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_shader_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_codec_invalid_input_smoke test_decoder_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(enum_capabilities_graphics|shader|codec|decoder)_invalid_input_smoke' --output-on-failure`
  - 成功。4/4 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkHighContrastConfig` value object / enum field setter 系の invalid enum と default value 規約をまとめて再確認する。
- `SkIRect` / `SkISize` / `SkSize` / `SkPoint` value handle 系の caller-owned handle、NULL pointer helper、numeric sentinel 規約をまとめて再確認する。
- `SkICC` profile factory / data handle 系の data ownership、failure `0`、NULL input 規約をまとめて再確認する。
- `SkPDF` document factory / metadata / stream ownership 系の NULL stream、optional metadata、factory failure 規約をまとめて再確認する。
- `SkPerlinNoiseShader` factory 系の required numeric / optional localMatrix、tile size sentinel、failure `0` 規約をまとめて再確認する。
