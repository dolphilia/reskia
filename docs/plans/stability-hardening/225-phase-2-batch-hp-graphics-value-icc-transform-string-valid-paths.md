# 225 Phase 2 Batch HP: graphics value ICC transform string valid paths

開始時刻: 2026-05-13 17:49:50 JST

## 目的

`224-phase-2-batch-ho-image-canvas-capabilities-valid-paths.md` の「次バッチ候補」から、重複を避けて次の 5 件を順に確認する。対象は `SkGraphics` global cache controls、`SkIRect` / `SkISize` / `SkSize` / `SkPoint` geometry helpers、`SkICC` profile helpers、`SkRSXform` / `SkMatrix` / `SkM44` transform helpers、`SkString` / `SkData` / `SkDataTable` buffer ownership。

## 変更内容

- `skia/test/test_enum_capabilities_graphics_invalid_input_smoke.cpp`
  - `SkGraphics_GetFontCacheLimit` / `SetFontCacheLimit`、`GetFontCacheCountLimit` / `SetFontCacheCountLimit` の stable set / restore valid path を追加した。
  - resource cache total byte limit と single allocation byte limit の stable set / restore valid path を追加した。
  - cache used / count used getter の最小 valid check を追加した。
- `skia/test/test_value_icc_high_contrast_invalid_input_smoke.cpp`
  - `SkISize` / `SkSize` の valid mutation と returned size handle path を追加した。
  - `SkIRect` の dimensions、topLeft / size returned handle、makeOffset、contains、Intersects valid path を追加した。
  - `SkPoint_scaleTo` の valid output pointer path を追加した。
  - `skcms_sRGB_profile()` を使い、`SkICC_SkWriteICCProfile` と `SkICC_SkWriteICCProfileFromICCProfile` の valid profile data path を追加した。
- `skia/test/test_value_transform_string_stroke_trace_invalid_input_smoke.cpp`
  - `SkRSXform_toTriStrip` と `SkRSXform_MakeFromRadians` の valid path を追加した。
  - `SkString_data` / `SkString_dataMutable` の borrowed buffer path と append / prepend mutation path を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `graphics_global_cache_controls`、`icc_profile_helpers`、`rsxform_matrix_m44_transform_helpers`、`string_data_buffer_ownership` を `covered` valid path に更新した。
  - `value_handle_geometry_helpers` は coverage を拡張したが、対象 family が広いため `representative-valid-path` のまま残し、追加済み範囲を notes に記録した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_enum_capabilities_graphics_invalid_input_smoke test_value_icc_high_contrast_invalid_input_smoke test_value_transform_string_stroke_trace_invalid_input_smoke test_data_invalid_input_smoke test_data_table_invalid_input_smoke test_matrix_invalid_input_smoke test_m44_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(enum_capabilities_graphics|value_icc_high_contrast|value_transform_string_stroke_trace|data|data_table|matrix|m44)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。7/7 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。

## 次バッチ候補

次候補は今回の `SkGraphics`、geometry、ICC、transform、string/data 系と重複しないように選ぶ。着手時は必ず `rg '<対象API名|detail id>' docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` で既存行を確認する。

- `SkImage` async rescale YUV / YUVA callback family の環境依存範囲を再調査し、`image_async_rescale` の representative 残りを縮小する。
- `SkImage` raster / texture conversion factories の factory failure と returned handle valid path を再確認し、`image_raster_texture_factories` の representative 残りを縮小する。
- `SkCodecs` empty header delegation row を decoder-specific evidence と照合し、`codecs_empty_header_decoder_delegation` を完了扱いのまま残すべきか整理する。
- `SkStrokeRec` baseline helper row と paint/path integration row の重複を整理し、`stroke_rec_path_paint_helpers` の representative 残りを縮小する。
- `SkTraceMemoryDump` no-op row と concrete forwarding row の重複を整理し、`trace_memory_dump_noop_helpers` の omitted reason を最新の concrete smoke evidence に合わせて更新する。
