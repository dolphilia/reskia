# 91 Phase 2 Batch CL: runtime effect source handle safety

開始時刻: 2026-05-11 05:30:33 JST

## 目的

`90-phase-2-batch-ck-image-async-read.md` の「次バッチ候補」から、`SkRuntimeEffect` MakeFor* 系の `sk_string_t` source handle 0 / invalid handle と options required 規約を確認する。registry に存在しない source handle が `static_sk_string_get_entity` に渡らないようにする。

## 変更内容

- `skia/capi/sk_runtime_effect.cpp`
  - `SkRuntimeEffect_MakeForColorFilter` / `MakeForShader` / `MakeForBlender` と Default 版で、`sk_string_t` が 0、または registry に存在しない handle の場合 `0` を返すようにした。
  - options required 版は source handle と options の両方が valid な場合だけ Skia に渡すようにした。
- `skia/capi/sk_runtime_effect.h`
  - source string valid handle、options non-null、invalid input returns 0 規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - MakeFor* / Default 版の source handle 0、invalid handle smoke ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.*` の P2 記録を Batch CL に更新した。

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

- `SkCanvas` drawPaint / drawPath / drawRegion の required paint/path/region と invalid input no-op 規約を追加で確認する。
- `SkImage` shader / rawShader 系の required sampling と image pointer guard を追加確認する。
- `SkRuntimeEffect_MakeTraced` の shader handle 0 / invalid handle と traceCoord required 規約を確認する。
