# 137 Phase 2 Batch EF: runtime effect makeShader

開始時刻: 2026-05-12 23:40:23 JST

## 目的

`134-phase-2-batch-ec-runtime-builder-make-ownership.md` の「次バッチ候補」から、`SkRuntimeEffect` makeShader / makeShaderWithChildPtr returned shader handle ownership と data / children / localMatrix optional 規約を再確認する。data handle 0 と child pointer handle 0 は空入力として許容し、成功時の shader handle は呼び出し側が delete できることを固定する。

## 変更内容

- `skia/capi/sk_runtime_effect.h`
  - `SkRuntimeEffect_makeShader` / `SkRuntimeEffect_makeShaderWithChildPtr` の returned shader handle ownership、localMatrix optional、failure 0 規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - `SkRuntimeEffect_makeShader` の generated handle ownership smoke を維持した。
  - `SkRuntimeEffect_makeShaderWithChildPtr(effect, 0, 0, localMatrix)` が有効 shader handle を返し delete できることを確認した。
  - 既存の invalid data handle / missing children / invalid child pointer handle smoke と合わせて optional input 規約を固定した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.cpp` / `sk_runtime_effect.h` の P2 記録を Batch EF に更新した。

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

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkRuntimeEffect` makeColorFilter / makeBlender returned handle ownership と data / children optional 規約を再確認する。
