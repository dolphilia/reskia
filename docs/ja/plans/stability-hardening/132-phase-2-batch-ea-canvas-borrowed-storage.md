# 132 Phase 2 Batch EA: canvas borrowed storage

開始時刻: 2026-05-12 23:28:38 JST

## 目的

`131-phase-2-batch-dz-runtime-builder-proxy-handles.md` の「次バッチ候補」から、`SkCanvas` accessTopLayerPixels / peekPixels borrowed storage lifetime と optional out params を再確認する。返される raw pointer / pixmap は canvas 側 storage を借用し、呼び出し側が解放しないことを固定する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_accessTopLayerPixels` が top-layer storage を利用できない場合にも NULL を返すこと、`info` / `rowBytes` / `origin` が optional out params であることを明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - bitmap-backed canvas を作成し、`SkCanvas_accessTopLayerPixels` が borrowed storage pointer と rowBytes を返すことを確認した。
  - `info` / `rowBytes` / `origin` をすべて NULL にしても borrowed pointer を返せることを確認した。
  - `SkCanvas_peekPixels` が valid pixmap out param に borrowed storage を設定して true を返すことを確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EA に更新した。

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
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawImage / drawImageRect の image non-null と sampling / paint optional 規約を再確認する。
- `SkImage` asyncRescaleAndReadPixels / asyncRescaleAndReadPixelsYUV420 callback context と invalid input no-op 規約を再確認する。
- `SkRuntimeEffect` makeShader / makeShaderWithChildPtr returned shader handle ownership と data / children / localMatrix optional 規約を再確認する。
