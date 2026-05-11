# 116 Phase 2 Batch DK: runtime effect find name handles

開始時刻: 2026-05-11 10:14:01 JST

## 目的

`115-phase-2-batch-dj-image-texture-validity-accessors.md` の「次バッチ候補」から、`SkRuntimeEffect` findUniform / findChild の string_view handle 0 / invalid handle 規約を再確認する。name handle は必須入力として扱い、handle 0 や registry に存在しない非 0 handle は Skia API に渡さず NULL に固定する。

## 変更内容

- `skia/handles/static_std_string_view-internal.h`
  - string_view registry の存在確認用に `static_string_view_contains` を公開した。
- `skia/handles/static_std_string_view.cpp`
  - `static_string_view_contains` を実装した。
- `skia/capi/sk_runtime_effect.cpp`
  - `has_string_view_handle` を追加し、`SkRuntimeEffect_findUniform` / `SkRuntimeEffect_findChild` で name handle 0 と未知の非 0 handle を NULL return にした。
- `skia/capi/sk_runtime_effect.h`
  - findUniform / findChild の runtime_effect / name required と invalid input NULL 規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - name handle 0、未知の非 0 handle、valid string_view handle の findUniform / findChild smoke ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.*` の P2 記録を Batch DK に更新した。

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

- `SkCanvas` clipRect / clipIRect / clipRRect / clipPath pointer required と invalid input no-op 規約を再確認する。
- `SkImage` makeNonTextureImage / makeTextureImage / makeColorSpace texture-backed factory failure の handle 0 規約を再確認する。
- `SkRuntimeEffect` makeShader / makeColorFilter / makeBlender の uniform data / child span handle required 規約を再確認する。
