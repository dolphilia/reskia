# 66 Phase 2 Batch BM: file stream C API safety

開始時刻: 2026-05-10 13:23:48 JST

## 目的

`65-phase-2-batch-bl-mesh.md` の「次バッチ候補」から、`SkFILEStream` / `SkFILEWStream` の path / stream 状態規約を確認する。NULL path、NULL stream、NULL raw buffer / output pointer を直接 dereference する箇所があるため、既存 ABI の範囲で sentinel を固定する。

## 変更内容

- `skia/capi/sk_file_stream.cpp`
  - NULL path / NULL `FILE*` constructor input を `NULL` にした。
  - NULL stream getter / 操作を `0` / `false` / `true` / `NULL` sentinel にした。
  - `read` / `peek` は `size > 0` で buffer 非 NULL を必須にした。
  - scalar / integer / bool / packed read は output pointer 非 NULL を必須にした。
  - `Make` は NULL path で handle `0` を返すようにした。
- `skia/capi/sk_file_stream.h`
  - NULL path / stream / buffer / output pointer の規約を明記した。
- `skia/capi/sk_file_w_stream.cpp`
  - NULL path constructor input を `NULL` にした。
  - NULL stream 操作を no-op / `0` / `false` sentinel にした。
  - `write` は `size > 0` で buffer 非 NULLを必須にした。
  - `writeText` / `writeStream` は input pointer 非 NULL を必須にした。
- `skia/capi/sk_file_w_stream.h`
  - NULL path / stream / buffer / text / input stream の規約を明記した。
- `skia/test/test_file_stream_invalid_input_smoke.cpp`
  - FILE stream / FILE write stream の NULL 入力、invalid path、raw buffer sentinel smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `c_skia_file_stream_invalid_input_smoke` を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_file_stream.*` / `sk_file_w_stream.*` の P2 記録を Batch BM に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_file_stream_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_file_stream_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|file_stream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_file_stream_invalid_input_smoke`: build 成功。
- `c_skia_file_stream_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 61/61 passed。
- `git diff --check`: exit 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkOpBuilder` の path pointer / fill type 規約を確認する。
