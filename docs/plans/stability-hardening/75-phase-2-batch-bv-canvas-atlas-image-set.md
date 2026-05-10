# 75 Phase 2 Batch BV: canvas atlas and image set count safety

開始時刻: 2026-05-10 21:17:45 JST

## 目的

`74-phase-2-batch-bu-auto-canvas-restore-bbox.md` の「次バッチ候補」から、`SkCanvas` image set / atlas 周辺の count / optional pointer 規約を追加確認する。`count <= 0` / `cnt <= 0` を no-op とし、配列 pointer が必要な条件を C API 側で明確にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAtlas` は `count <= 0` を no-op にし、`count > 0` の場合だけ atlas / xform / tex / sampling を required とした。
  - `SkCanvas_experimental_DrawEdgeAAImageSet` は `cnt <= 0` を no-op にし、`cnt > 0` の場合だけ imageSet / sampling を required とした。
- `skia/capi/sk_canvas.h`
  - atlas / image set の count と optional pointer 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - atlas / image set の zero / negative count と NULL required pointer no-op ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch BV に更新した。

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

- `SkFont` positions / intercepts 周辺の output pointer と handle origin 規約を追加で確認する。
- `SkCanvas` saveLayer / raster direct 周辺の optional pointer と backing-store lifetime 規約を再確認する。
- `SkCanvas` image / image rect / image lattice 周辺の handle 0 と optional paint 規約を再確認する。
