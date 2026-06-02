# 72 Phase 2 Batch BS: canvas text and glyph array C API safety

開始時刻: 2026-05-10 18:34:07 JST

## 目的

`71-phase-2-batch-br-annotation-android-codec.md` の「次バッチ候補」から、`SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加確認する。`count <= 0` や `byteLength == 0` を no-op とし、配列 pointer が必要な条件を C API 側で明確にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawGlyphs*` 3 件は `count <= 0` を no-op にし、`count > 0` の場合だけ配列 / origin / font / paint を required とした。
  - cluster 付き `SkCanvas_drawGlyphs` は `clusters` を required、`textByteCount < 0` を no-op、`textByteCount > 0` では `utf8text` を required とした。
  - `SkCanvas_drawSimpleText` は `byteLength == 0` を no-op にし、`byteLength > 0` の場合だけ raw text / font / paint を required とした。
- `skia/capi/sk_canvas.h`
  - raw text と glyph array の count / pointer 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - raw text / glyph array の NULL pointer、zero / negative count、negative textByteCount の no-op ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch BS に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_canvas_invalid_input_smoke`: build 成功。
- `c_skia_canvas_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 65/65 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkBBoxHierarchy` / `SkAutoCanvasRestore` など、まだ todo の lifecycle / pointer 規約を確認する。
- `SkCanvas` image set / atlas 周辺の count / optional pointer 規約を追加で確認する。
