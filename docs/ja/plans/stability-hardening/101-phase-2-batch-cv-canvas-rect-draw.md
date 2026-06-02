# 101 Phase 2 Batch CV: canvas rect draw input rules

開始時刻: 2026-05-11 05:58:29 JST

## 目的

`100-phase-2-batch-cu-runtime-effect-result-ownership.md` の「次バッチ候補」から、`SkCanvas` drawIRect / drawOval / drawRect の required rect/paint no-op 規約を追加確認する。`drawRect` の handle API は handle 0 だけでなく registry に存在しない非 0 handle も no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawRect` は `rect` が 0、または registry に存在しない handle の場合 no-op にするようにした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawIRect` / `SkCanvas_drawOval` / `SkCanvas_drawRect` の required input と invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawIRect` / `SkCanvas_drawOval` / `SkCanvas_drawRect` の NULL / invalid handle / NULL paint / 正常系 smoke ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch CV に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke test_runtime_effect_invalid_input_smoke test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(image_surface|runtime_effect|canvas)_invalid_input_smoke' --output-on-failure`
  - 成功。3/3 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkImage` makeColorSpace / reinterpretColorSpace 系の color space handle 0 / invalid handle 規約を再確認する。
- `SkRuntimeEffect` makeShader / makeColorFilter generated shader/filter handle ownership smoke を追加確認する。
- `SkCanvas` drawPoint / drawLine handle point validity と paint required 規約を追加確認する。
