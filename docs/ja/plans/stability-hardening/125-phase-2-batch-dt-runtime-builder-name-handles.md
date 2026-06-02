# 125 Phase 2 Batch DT: runtime builder name handles

開始時刻: 2026-05-11 10:36:07 JST

## 目的

`124-phase-2-batch-ds-image-read-pixels-context.md` の「次バッチ候補」から、`SkRuntimeEffect` builder uniform / child lookup name handle 0 / invalid handle 規約を再確認する。builder は非 NULL、name は valid `string_view_t` handle を必須にし、handle 0 や registry に存在しない非 0 handle を Skia API に渡さず 0 return に固定する。

## 変更内容

- `skia/capi/sk_runtime_shader_builder.cpp`
- `skia/capi/sk_runtime_color_filter_builder.cpp`
- `skia/capi/sk_runtime_blend_builder.cpp`
- `skia/capi/sk_runtime_effect_builder.cpp`
  - `has_string_view_handle` を追加し、uniform / child lookup で name handle 0 と未知の非 0 handle を 0 return にした。
- `skia/capi/sk_runtime_shader_builder.h`
- `skia/capi/sk_runtime_color_filter_builder.h`
- `skia/capi/sk_runtime_blend_builder.h`
- `skia/capi/sk_runtime_effect_builder.h`
  - builder/name required と invalid input 0 return 規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - valid builder に対する name handle 0 / invalid handle の uniform / child smoke ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - runtime builder 系の P2 記録を Batch DT に更新した。

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

- `SkCanvas` readPixels bitmap / pixmap の required output storage と invalid input false 規約を再確認する。
- `SkImage` peekPixels / scalePixels pixmap storage の required output pointer と false sentinel 規約を再確認する。
- `SkRuntimeEffect` builder uniforms / children returned handle ownership と delete 規約を再確認する。
