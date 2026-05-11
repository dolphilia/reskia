# 126 Phase 2 Batch DU: canvas readPixels output storage

開始時刻: 2026-05-11 10:59:49 JST

## 目的

`125-phase-2-batch-dt-runtime-builder-name-handles.md` の「次バッチ候補」から、`SkCanvas` readPixels bitmap / pixmap の required output storage と invalid input false 規約を再確認する。NULL / 未初期化 output storage を false に固定し、raw buffer 版の rowBytes guard と同じ基準で smoke を補強する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_readPixels` / `SkCanvas_readPixelsWithPixmap` の output storage required と invalid input false 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL bitmap に加え、未初期化 bitmap / NULL pixmap / 未初期化 pixmap の false smoke ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch DU に更新した。

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
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkImage` peekPixels / scalePixels pixmap storage の required output pointer と false sentinel 規約を再確認する。
- `SkRuntimeEffect` builder uniforms / children returned handle ownership と delete 規約を再確認する。
- `SkCanvas` writePixels bitmap / pixmap / raw buffer の required input storage と invalid input no-op 規約を再確認する。
