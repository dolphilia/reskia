# 69 Phase 2 Batch BP: document and dynamic stream C API safety

開始時刻: 2026-05-10 13:36:09 JST

## 目的

`68-phase-2-batch-bo-pathops.md` の「次バッチ候補」から、`SkDocument` / `SkDynamicMemoryWStream` の stream / output pointer 規約を確認する。`SkDocument` は NULL lifecycle / beginPage 入力を直接 dereference していたため guard を追加し、`SkDynamicMemoryWStream` は既存 guard のうち smoke で未固定だった null transfer / writer 操作を追加確認する。

## 変更内容

- `skia/capi/sk_document.cpp`
  - `release` / `endPage` / `close` / `abort` / `ref` / `unref` を NULL no-op にした。
  - `beginPage` は NULL `document` で `NULL` を返すようにした。
  - `unique` は NULL `document` で `false` を返すようにした。
- `skia/capi/sk_document.h`
  - document lifecycle の NULL sentinel と、`beginPage` の borrowed canvas / nullable content 規約を明記した。
- `skia/test/test_document_invalid_input_smoke.cpp`
  - NULL document lifecycle / beginPage / unique smoke を追加した。
- `skia/test/test_wstream_invalid_input_smoke.cpp`
  - `SkDynamicMemoryWStream` の null transfer / writer 系操作の smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `c_skia_document_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_document.*` と `sk_dynamic_memory_w_stream.*` の P2 記録を Batch BP に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_document_invalid_input_smoke -j 8
cmake --build skia/cmake-build-stability-tests --target test_wstream_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(document|wstream)_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_document_invalid_input_smoke`: build 成功。
- `test_wstream_invalid_input_smoke`: build 成功。
- `c_skia_document_invalid_input_smoke` / `c_skia_wstream_invalid_input_smoke`: 2/2 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 63/63 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkEncodedOrigin` / `SkCubicMap` / `SkCubicResampler` の enum / value 規約を確認する。
