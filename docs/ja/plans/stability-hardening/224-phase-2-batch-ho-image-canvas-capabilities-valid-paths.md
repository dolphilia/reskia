# 224 Phase 2 Batch HO: image canvas capabilities valid paths

開始時刻: 2026-05-13 17:35:07 JST

## 目的

`223-phase-2-batch-hn-async-canvas-gradient-valid-paths.md` の「次バッチ候補」から、重複を避けて次の 5 件を順に確認する。対象は `SkImage` texture/context getters、`SkImage` ref / unique / asLegacyBitmap、`SkCanvas` pixel read/write、`SkCanvas` atlas / patch / vertices / mesh draw、`SkCapabilities` RasterBackend / refcount behavior。

## 変更内容

- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - CPU-raster image の `SkImage_isTextureBacked`、`SkImage_textureSize`、`SkImage_isValid(image, NULL context)` は既存 valid path で確認済みであることを再確認した。
  - raster image に対する `SkImage_unique` の安定呼び出し、`SkImage_ref` / `SkImage_unref` の valid path を追加した。
  - caller-owned `SkBitmap` output storage を渡す `SkImage_asLegacyBitmap` valid path を追加した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - surface-backed canvas に対して `SkCanvas_writePixelsWithImageInfo` で書き込み、`SkCanvas_readPixelsWithImageInfo` で読み戻す valid rowBytes round-trip を追加した。
  - `drawAtlas`、`drawPatch`、`drawVertices`、`drawVerticesPtr` の representative valid draw path は既存 smoke で確認済みであることを再確認した。
  - `drawMesh` は `SkMesh::Result` から `reskia_mesh_t *` を取り出す C API が未整備のため、今回も representative valid path 扱いに留めた。
- `skia/test/test_enum_capabilities_graphics_invalid_input_smoke.cpp`
  - `SkCapabilities_RasterBackend` の const handle から borrowed pointer を取得し、`skslVersion`、`unique`、`ref` / `unref` の valid path を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `image_texture_context_getters`、`image_ref_legacy_bitmap`、`canvas_read_write_pixels`、`capabilities_null_raster_backend` を `covered` valid path に更新した。
  - `canvas_atlas_patch_vertices_mesh` は atlas / patch / vertices valid path を再確認しつつ、mesh の C API 制約を notes に明記して `representative-valid-path` のまま更新した。
  - 簡易列数チェックが引用フィールド内カンマで誤検出しないよう、既存の `canvas_image_rect_lattice_nine_draw` notes をカンマなしの表現に整えた。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke test_canvas_invalid_input_smoke test_enum_capabilities_graphics_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(image_surface|canvas|enum_capabilities_graphics)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。3/3 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。

## 次バッチ候補

次候補は今回の `SkImage` getter/ref、`SkCanvas` pixel/draw、`SkCapabilities` と重複しないよう、詳細台帳の remaining representative / omitted 行から選ぶ。着手時は必ず `rg '<対象API名|detail id>' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` で既存行を確認する。

- `SkGraphics` global cache controls の valid getter/setter/purge 範囲を再確認し、`graphics_global_cache_controls` を fully covered に近づける。
- `SkIRect` / `SkISize` / `SkSize` / `SkPoint` の geometry helper family を分割して valid handle / output pointer path を追加し、`value_handle_geometry_helpers` を fully covered に近づける。
- `SkICC` profile helpers の valid profile data construction 可否を調査し、`icc_profile_helpers` の representative 範囲を縮小する。
- `SkRSXform` / `SkMatrix` / `SkM44` transform helpers の残り valid output path を追加し、`rsxform_matrix_m44_transform_helpers` を fully covered に近づける。
- `SkString` / `SkData` / `SkDataTable` の borrowed buffer / ownership smoke を再確認し、`string_data_buffer_ownership` の remaining representative 範囲を縮小する。
