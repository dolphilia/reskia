# 74 Phase 2 Batch BU: auto canvas restore and bbox hierarchy safety

開始時刻: 2026-05-10 21:14:06 JST

## 目的

`73-phase-2-batch-bt-font-widths-bounds.md` の「次バッチ候補」から、`SkAutoCanvasRestore` / `SkBBoxHierarchy` の lifecycle / pointer 規約を確認する。NULL object や invalid result handle が Skia API にそのまま渡らないよう、既存 ABI の範囲で no-op / sentinel を固定する。

## 変更内容

- `skia/capi/sk_auto_canvas_restore.cpp`
  - `SkAutoCanvasRestore_restore` は NULL object で no-op にした。
- `skia/capi/sk_auto_canvas_restore.h`
  - NULL canvas で no-op restore guard を作れること、NULL delete / restore が no-op であることを明記した。
- `skia/capi/sk_b_box_hierarchy.cpp`
  - `release` / `ref` / `unref` は NULL object で no-op にした。
  - `insert` / `insert_withMetadata` は `N <= 0` を no-op、`N > 0` では required pointer を guard するようにした。
  - `search` は hierarchy / query / result vector handle が揃わない場合 no-op にした。
  - `bytesUsed` は NULL object で `0`、`unique` は `false` を返すようにした。
- `skia/capi/sk_b_box_hierarchy.h`
  - lifecycle / pointer / sentinel 規約を明記した。
- `skia/test/test_auto_canvas_restore_bbox_invalid_input_smoke.cpp`
  - NULL restore guard と BBoxHierarchy NULL / invalid handle 経路を smoke 化した。
- `cmake/reskia/tests.cmake`
  - `c_skia_auto_canvas_restore_bbox_invalid_input_smoke` を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_auto_canvas_restore.*` / `sk_b_box_hierarchy.*` の P2 記録を Batch BU に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_auto_canvas_restore_bbox_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_auto_canvas_restore_bbox_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_auto_canvas_restore_bbox_invalid_input_smoke`: build 成功。
- `c_skia_auto_canvas_restore_bbox_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 66/66 passed。
- `git diff --check`: exit 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` image set / atlas 周辺の count / optional pointer 規約を追加で確認する。
- `SkFont` positions / intercepts 周辺の output pointer と handle origin 規約を追加で確認する。
- `SkCanvas` saveLayer / raster direct 周辺の optional pointer と backing-store lifetime 規約を再確認する。
