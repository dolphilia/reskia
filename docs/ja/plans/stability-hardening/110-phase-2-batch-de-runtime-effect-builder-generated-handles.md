# 110 Phase 2 Batch DE: runtime effect builder generated handle ownership

開始時刻: 2026-05-11 06:22:29 JST

## 目的

`109-phase-2-batch-dd-image-encoded-data.md` の「次バッチ候補」から、`SkRuntimeEffect` builder generated shader/filter/blender handle ownership smoke を追加確認する。valid runtime effect handle から各 builder を生成し、builder が返す shader / color filter / blender handle が registry に存在し、呼び出し側で delete できることを固定する。

## 変更内容

- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - valid `SkRuntimeEffect::Result::effect` から runtime effect handle を作り、`SkRuntimeShaderBuilder` / `SkRuntimeColorFilterBuilder` / `SkRuntimeBlendBuilder` を生成する smoke ケースを追加した。
  - 各 builder の `make*` が返す handle の registry ownership と delete 可能性を確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - runtime builder 系 `sk_runtime_*_builder.*` の P2 記録を Batch DE に更新した。

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

- `SkCanvas` drawAnnotation data handle 0 / invalid handle と data pointer optional 規約を追加確認する。
- `SkImage` scalePixels required pixmap / sampling 規約を追加確認する。
- `SkRuntimeEffect` uniforms / children returned handle ownership smoke を追加確認する。
