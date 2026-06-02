# 89 Phase 2 Batch CJ: canvas string draw input rules

開始時刻: 2026-05-11 05:26:18 JST

## 目的

`88-phase-2-batch-ci-canvas-vertices-draw.md` の「次バッチ候補」から、`SkCanvas` drawString / drawStringObject の required string/font/paint と invalid input no-op 規約を追加確認する。既存実装の NULL guard を smoke test で固定し、公開ヘッダのコメントを no-op 規約に揃える。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawString` / `SkCanvas_drawStringObject` の string/font/paint non-null と invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawString` の NULL string、NULL font、NULL paint、正常系 smoke を追加した。
  - `SkCanvas_drawStringObject` の NULL string object、NULL font、NULL paint、正常系 smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.h` の P2 記録を Batch CJ に更新した。

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

- `SkImage` asyncRescaleAndReadPixels 系の callback fail path と required srcRect / info / dstSize 規約を `SkSurface` と同じ基準で確認する。
- `SkCanvas` drawPaint / drawPath / drawRegion の required paint/path/region と invalid input no-op 規約を追加で確認する。
- `SkRuntimeEffect` MakeFor* 系の `sk_string_t` source handle 0 / invalid handle と options required 規約を確認する。
