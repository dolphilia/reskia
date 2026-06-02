# 88 Phase 2 Batch CI: canvas vertices draw handle safety

開始時刻: 2026-05-11 05:23:50 JST

## 目的

`87-phase-2-batch-ch-surface-async-read.md` の「次バッチ候補」から、`SkCanvas` drawVertices handle API の handle 0、無効 handle、paint 必須規約を追加確認する。registry に存在しない非 0 handle が Skia に渡らないようにし、borrowed pointer 版も NULL input no-op 規約を smoke test で固定する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawVertices` は `vertices` が 0、または registry に存在しない handle の場合 no-op にするようにした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawVertices` / `SkCanvas_drawVerticesPtr` の valid handle、borrowed pointer、paint non-null、invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawVertices` の handle 0、無効 handle、paint NULL、正常系 smoke を追加した。
  - `SkCanvas_drawVerticesPtr` の NULL vertices、paint NULL、正常系 smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch CI に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawString / drawStringObject の required string/font/paint と invalid input no-op 規約を追加で確認する。
- `SkImage` asyncRescaleAndReadPixels 系の callback fail path と required srcRect / info / dstSize 規約を `SkSurface` と同じ基準で確認する。
- `SkCanvas` drawPaint / drawPath / drawRegion の required paint/path/region と invalid input no-op 規約を追加で確認する。
