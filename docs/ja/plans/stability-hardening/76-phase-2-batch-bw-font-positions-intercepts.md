# 76 Phase 2 Batch BW: font positions and intercepts safety

開始時刻: 2026-05-10 21:22:58 JST

## 目的

`75-phase-2-batch-bv-canvas-atlas-image-set.md` の「次バッチ候補」から、`SkFont` positions / intercepts 周辺の output pointer と handle origin 規約を追加確認する。`count <= 0` は no-op / handle `0` とし、正の `count` で required 配列だけを Skia API に渡す。

## 変更内容

- `skia/capi/sk_font.cpp`
  - `SkFont_getPos` / `SkFont_getXPos` / `SkFont_getIntercepts` の glyph 配列条件を `count > 0 && glyphs != nullptr` に統一した。
  - `getPos` / `getXPos` は正の `count` で output pointer を required、`getIntercepts` は正の `count` で glyphs / pos を required とした。
- `skia/capi/sk_font.h`
  - `count <= 0` no-op / handle `0` 規約、`getPos` の origin handle `0` は `{0,0}` として扱うことを明記した。
- `skia/test/test_font_invalid_input_smoke.cpp`
  - positions / x positions / intercepts の NULL pointer、zero / negative count、origin handle `0` ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_font.*` の P2 記録を Batch BW に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_font_invalid_input_smoke`: build 成功。
- `c_skia_font_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 66/66 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` saveLayer / raster direct 周辺の optional pointer と backing-store lifetime 規約を再確認する。
- `SkCanvas` image / image rect / image lattice 周辺の handle 0 と optional paint 規約を再確認する。
- `SkFont` text conversion / measureText 周辺の encoding enum と zero-length text 規約を追加で確認する。
