# 134 Phase 2 Batch EC: runtime builder make ownership

開始時刻: 2026-05-12 23:28:38 JST

## 目的

`131-phase-2-batch-dz-runtime-builder-proxy-handles.md` の「次バッチ候補」から、`SkRuntimeEffect` builder makeShader / makeColorFilter / makeBlender returned handle ownership と localMatrix optional 規約を再確認する。成功時の returned handle は呼び出し側が delete でき、builder が NULL または factory が失敗した場合は 0 を返すことを固定する。

## 変更内容

- `skia/capi/sk_runtime_shader_builder.h`
  - `SkRuntimeShaderBuilder_makeShader` の localMatrix optional、returned shader handle ownership、failure 0 規約を明記した。
- `skia/capi/sk_runtime_color_filter_builder.h`
  - `SkRuntimeColorFilterBuilder_makeColorFilter` の returned color filter handle ownership と failure 0 規約を明記した。
- `skia/capi/sk_runtime_blend_builder.h`
  - `SkRuntimeBlendBuilder_makeBlender` の returned blender handle ownership と failure 0 規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - `SkRuntimeShaderBuilder_makeShader(builder, localMatrix)` が有効 shader handle を返し delete できることを確認した。
  - 既存の null localMatrix / makeColorFilter / makeBlender handle ownership smoke と合わせて、builder make 系の返却 handle 規約を固定した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - runtime shader / color filter / blend builder の P2 記録を Batch EC に更新した。

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

- `SkCanvas` drawImage / drawImageRect の image non-null と sampling / paint optional 規約を再確認する。
- `SkImage` asyncRescaleAndReadPixels / asyncRescaleAndReadPixelsYUV420 callback context と invalid input no-op 規約を再確認する。
- `SkRuntimeEffect` makeShader / makeShaderWithChildPtr returned shader handle ownership と data / children / localMatrix optional 規約を再確認する。
