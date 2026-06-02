# 119 Phase 2 Batch DN: runtime effect child pointer handles

開始時刻: 2026-05-11 10:20:52 JST

## 目的

`118-phase-2-batch-dm-image-texture-factory-failure.md` の「次バッチ候補」から、`SkRuntimeEffect` makeShader / makeColorFilter / makeBlender の uniform data / child span handle required 規約を再確認する。data handle 0 と child pointer handle 0 は空入力として許可し、非 0 handle は registry 実体必須に固定する。

## 変更内容

- `skia/handles/static_sk_runtime_effect_child_ptr-internal.h`
  - child pointer span registry の存在確認用に `static_const_sk_runtime_effect_child_ptr_contains` を公開した。
- `skia/handles/static_sk_runtime_effect_child_ptr.cpp`
  - `static_const_sk_runtime_effect_child_ptr_contains` を実装した。
- `skia/capi/sk_runtime_effect.cpp`
  - `has_optional_child_ptr_handle` を追加し、WithChildPtr 系と `makeBlender` で未知の非 0 child pointer handle を 0 return にした。
- `skia/capi/sk_runtime_effect.h`
  - non-zero data / child pointer handle must be valid の規約を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - valid effect に対する invalid data handle、positive child count with NULL children、invalid child pointer handle の smoke ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.*` の P2 記録を Batch DN に更新した。

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

- `SkCanvas` concat / setMatrix の matrix pointer required と invalid input no-op 規約を再確認する。
- `SkImage` asyncRescaleAndReadPixels callback context の fail callback / NULL context 規約を再確認する。
- `SkRuntimeEffect` makeTracedShader の coordinate/data/child pointer required と trace handle 0 規約を再確認する。
