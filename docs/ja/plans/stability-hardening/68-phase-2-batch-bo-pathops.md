# 68 Phase 2 Batch BO: pathops C API safety

開始時刻: 2026-05-10 13:31:52 JST

## 目的

`67-phase-2-batch-bn-op-builder.md` の「次バッチ候補」から、`SkPathOps` free functions の path pointer / op enum 規約を確認する。現状 C API に free functions が露出していなかったため、既存 `SkPath` C API に wrapper を追加し、NULL path / result と `SkPathOp` 範囲外 enum を `false` sentinel にする。

## 変更内容

- `skia/capi/sk_path.cpp`
  - `SkPathOps_Op` / `SkPathOps_Simplify` / `SkPathOps_TightBounds` / `SkPathOps_AsWinding` を追加した。
  - NULL path / result は `false` を返すようにした。
  - `SkPathOps_Op` は `SkPathOp` 範囲外 enum で `false` を返すようにした。
- `skia/capi/sk_path.h`
  - `reskia_path_op_t` と pathops wrapper の pointer / enum 規約を追加した。
- `skia/test/test_path_invalid_input_smoke.cpp`
  - pathops wrapper の NULL 入力と invalid enum smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_path.cpp` / `sk_path.h` の P2 記録を Batch BO に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_path_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_path_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|file_stream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_path_invalid_input_smoke`: build 成功。
- `c_skia_path_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 62/62 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkDocument` / `SkDynamicMemoryWStream` の stream / output pointer 規約を確認する。
