# 63 Phase 2 Batch BJ: font callback C API safety recheck

開始時刻: 2026-05-10 13:00:34 JST

## 目的

`62-phase-2-batch-bi-canvas-recheck.md` の「次バッチ候補」から、`SkFont` の callback / glyph path 周辺を再確認する。Batch AA で NULL / raw-array guard は追加済みだが、`SkFont_getPaths` の callback bridge とヘッダ上の借用ポインタ規約を明文化し、無効入力時に callback が呼ばれないことを smoke で固定する。

## 変更内容

- `skia/capi/sk_font.cpp`
  - `reskia_font_get_paths_bridge` に NULL callback / NULL proc guard を追加した。
  - `SkFont_getPaths` の既存 guard と合わせ、`font == NULL`、`glyphIDs == NULL`、`count <= 0`、`glyphPathProc == NULL` は no-op のまま維持した。
- `skia/capi/sk_font.h`
  - `SkFont_getPaths` の `glyphIDs` / `glyphPathProc` 非 NULL 条件と、callback 中の `path_or_null` / `matrix` が借用で callback 後に保持不可であることを明記した。
- `skia/test/test_font_invalid_input_smoke.cpp`
  - 有効な `SkFont` に対する `SkFont_getPaths` の `NULL glyphIDs`、`count == 0`、`NULL callback` ケースで callback が呼ばれないことを確認する smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_font.cpp` / `sk_font.h` の P2 記録を Batch BJ に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_font_invalid_input_smoke`: build 成功。
- `c_skia_font_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 58/58 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkMeshSpecification` の runtime child / uniform pointer 規約を再確認する。
- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
