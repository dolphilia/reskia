# 78 Phase 2 Batch BY: canvas image handle safety

開始時刻: 2026-05-10 21:33:21 JST

## 目的

`77-phase-2-batch-bx-canvas-layer-raster-direct.md` の「次バッチ候補」から、`SkCanvas` image / image rect / image lattice 周辺の handle `0` と optional paint 規約を再確認する。handle 版 image draw API で、`0` だけでなく未知の非 0 handle も C API 境界で no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawImage` / `SkCanvas_drawImageHandleWithSampling` / `SkCanvas_drawImageRect` / `SkCanvas_drawImageRectHandleWithSrcDst` は image handle が handle table に存在しない場合 no-op にした。
- `skia/capi/sk_canvas.h`
  - handle 版 image draw API の invalid image handle no-op と optional paint 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - image handle `0` と未知の非 0 handle の no-op ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch BY に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_canvas_invalid_input_smoke`: build 成功。
- `c_skia_canvas_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 66/66 passed。
- `git diff --check`: exit 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkFont` text conversion / measureText 周辺の encoding enum と zero-length text 規約を追加で確認する。
- `SkCanvas` readPixels / writePixels 周辺の rowBytes / pixel buffer 規約を追加で確認する。
- `SkCanvas` image lattice / image nine pointer API の lattice / center / dst 規約を追加で確認する。
