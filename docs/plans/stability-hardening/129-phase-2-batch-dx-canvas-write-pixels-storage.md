# 129 Phase 2 Batch DX: canvas writePixels storage

開始時刻: 2026-05-12 23:06:53 JST

## 目的

`128-phase-2-batch-dw-runtime-builder-spans.md` の「次バッチ候補」から、`SkCanvas` writePixels bitmap / pixmap / raw buffer の required input storage と invalid input no-op 規約を再確認する。現行 C API では pixmap 版 writePixels は露出していないため、bitmap 版と raw buffer 版を対象にする。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_writePixels` の bitmap が non-null input storage であり、invalid input は false を返すことを明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_writePixels(canvas, nullptr, ...)` が false を返すことを確認した。
  - 空の `SkBitmap` input storage でも false で失敗し、クラッシュしないことを確認した。
  - 既存の raw buffer `SkCanvas_writePixelsWithImageInfo` null info / null pixels / invalid rowBytes smoke と合わせて、入力 storage 規約を固定した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch DX に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke test_image_surface_invalid_input_smoke test_runtime_effect_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|runtime_effect)_invalid_input_smoke' --output-on-failure`
  - 成功。3/3 passed。
- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` accessTopLayerPixels / peekPixels borrowed storage lifetime と optional out params を再確認する。
- `SkImage` shader / rawShader returned shader handle ownership と invalid input 0 規約を再確認する。
- `SkRuntimeEffect` builder makeShader / makeColorFilter / makeBlender returned handle ownership と localMatrix optional 規約を再確認する。
