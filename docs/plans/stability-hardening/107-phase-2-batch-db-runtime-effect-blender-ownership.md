# 107 Phase 2 Batch DB: runtime effect generated blender ownership

開始時刻: 2026-05-11 06:16:38 JST

## 目的

`106-phase-2-batch-da-image-color-space-accessors.md` の「次バッチ候補」から、`SkRuntimeEffect` MakeForBlender / makeBlender generated blender handle ownership smoke を追加確認する。`SkRuntimeEffect::Result` が保持する有効 effect から生成した blender handle が registry に存在し、呼び出し側で delete できることを固定する。

## 変更内容

- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - 有効な blender SKSL を `SkRuntimeEffect_MakeForBlenderDefault` に渡し、`SkRuntimeEffect::Result::effect` から `makeBlender` を呼ぶ smoke ケースを追加した。
  - 生成された `sk_blender_t` が registry に存在することを確認し、delete できることを固定した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.*` の P2 記録を Batch DB に更新した。

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

- `SkCanvas` drawColor / drawColorU32 の color pointer required と enum range 規約を追加確認する。
- `SkImage` refEncodedData null result ownership を再確認する。
- `SkRuntimeEffect` builder generated shader/filter/blender handle ownership smoke を追加確認する。
