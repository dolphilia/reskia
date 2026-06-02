# 95 Phase 2 Batch CP: canvas patch draw input rules

開始時刻: 2026-05-11 05:38:11 JST

## 目的

`94-phase-2-batch-co-runtime-effect-make-traced.md` の「次バッチ候補」から、`SkCanvas` drawPatch の cubics / texCoords / paint required と colors optional 規約を追加確認する。既存実装の NULL guard を smoke test で固定し、公開ヘッダのコメントを no-op 規約に揃える。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawPatch` の cubics / texCoords / paint required、colors optional、invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawPatch` の NULL cubics、NULL texCoords、NULL paint、colors NULL 正常系 smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.h` の P2 記録を Batch CP に更新した。

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

- `SkImage` readPixels 系の rowBytes validation と pixmap required 規約を再確認する。
- `SkRuntimeEffect` makeShader / makeColorFilter / makeBlender の data handle 0 と child pointer handle validity を再確認する。
- `SkCanvas` drawDRRect / drawRRect / drawRoundRect の required rrect/rect/paint no-op 規約を追加確認する。
