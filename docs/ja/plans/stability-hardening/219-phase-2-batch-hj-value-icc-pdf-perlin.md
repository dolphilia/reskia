# 219 Phase 2 Batch HJ: value ICC PDF Perlin rules

開始時刻: 2026-05-13 12:14:19 JST

## 目的

`218-phase-2-batch-hi-enum-capabilities-codecs-gradient-graphics.md` の「次バッチ候補」から、`SkHighContrastConfig`、value handle geometry helpers、`SkICC`、`SkPDF`、`SkPerlinNoiseShader` の 5 件を順に確認する。NULL pointer、invalid enum、caller-owned handle、optional metadata / tileSize、factory failure `0` の規約を固定する。

## 変更内容

- `skia/capi/sk_high_contrast_config.cpp`
  - `SkHighContrastConfig_newWithGrayscaleInvertStyleContrast` が invalid `invertStyle` で NULL を返すようにした。
  - `isValid(nullptr)` を false にした。
- `skia/capi/sk_i_rect.cpp` / `skia/capi/sk_i_size.cpp` / `skia/capi/sk_size.cpp` / `skia/capi/sk_point.cpp`
  - 代表的な pointer receiver / helper について NULL sentinel と no-op を追加した。
  - `SkISize` / `SkSize` は NULL getter を 0 / true / false に正規化した。
  - `SkIRect_MakeSize` / `SkIRect_Intersects` / `SkSize_MakeFromISize` は NULL input を `0` / false にした。
  - `SkPoint` の vector / point pointer helper は NULL input で `0` または no-op にした。
  - 対象 API 群が大きいため、今回の detail row は representative subset とし、残りの geometry API family は後続 batch 候補に残す。
- `skia/capi/sk_icc.cpp`
  - ICC profile / transfer / matrix input を required とし、invalid input または factory failure を `0` にした。
  - output buffer helper は NULL input を no-op にした。
- `skia/capi/sk_pdf.cpp`
  - `SkPDF_SetNodeId` は NULL canvas no-op にした。
  - document factory は NULL stream で `0` を返すようにした。
  - metadata は optional のままとした。
- `skia/capi/sk_perlin_noise_shader.cpp`
  - base frequency と octave count を positive required にした。
  - `tileSize` は optional のままにし、factory failure は `0` に正規化した。
- `skia/test/test_value_icc_high_contrast_invalid_input_smoke.cpp`
  - high contrast、representative value helpers、ICC invalid input の smoke を追加した。
- `skia/test/test_shader_invalid_input_smoke.cpp`
  - Perlin noise shader factory の invalid numeric input と代表 valid returned handle smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `test_value_icc_high_contrast_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `high_contrast_config_value_object`
  - `value_handle_geometry_helpers`
  - `icc_profile_helpers`
  - `pdf_document_factories`
  - `perlin_noise_shader_factories`
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_high_contrast_config.cpp/h`、`sk_i_rect.cpp/h`、`sk_i_size.cpp/h`、`sk_size.cpp/h`、`sk_point.cpp/h`、`sk_icc.cpp/h`、`sk_pdf.cpp/h`、`sk_perlin_noise_shader.cpp/h` を batch HJ の進捗として更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-tests --target test_value_icc_high_contrast_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-tests --target test_shader_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(value_icc_high_contrast|shader)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkPoint3` / `SkIPoint` / `SkVector` value pointer helper 系の NULL pointer、numeric sentinel、caller-owned handle 規約をまとめて再確認する。
- `SkRSXform` / `SkMatrix` / `SkM44` geometry transform 系の required output array、invalid handle、no-op / `0` 規約をまとめて再確認する。
- `SkString` / `SkData` / `SkDataTable` buffer ownership 系の borrowed pointer、caller-owned handle、NULL input 規約をまとめて再確認する。
- `SkStrokeRec` path stroking helper 系の NULL path / paint style enum / scalar sentinel 規約をまとめて再確認する。
- `SkTraceMemoryDump` callback / dump helper 系の NULL callback、borrowed string、no-op 規約をまとめて再確認する。
