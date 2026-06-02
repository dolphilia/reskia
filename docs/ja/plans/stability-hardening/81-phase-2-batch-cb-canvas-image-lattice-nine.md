# 81 Phase 2 Batch CB: canvas image lattice and nine no-op safety

開始時刻: 2026-05-10 21:46:28 JST

## 目的

`80-phase-2-batch-ca-canvas-pixels-rowbytes.md` の「次バッチ候補」から、`SkCanvas` image lattice / image nine pointer API の `image` / `lattice` / `center` / `dst` 規約を追加確認する。NULL pointer が Skia API の参照引数に渡らないことを smoke で固定し、C API ヘッダ上でも no-op 規約を明示する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawImageLattice` / `SkCanvas_drawImageLatticeWithFilter` / `SkCanvas_drawImageNine` の `image` / `lattice` / `center` / `dst` を non-null borrowed pointer として明記し、invalid input は no-op と記録した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL `image` の lattice / nine no-op ケースを追加した。
  - 実画像ポインタ、`SkRect`、`SkIRect` を用意し、NULL `lattice` / NULL `center` / NULL `dst` が no-op になる smoke ケースを追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch CB に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkTextBlob` / `SkTextBlobBuilder` 周辺の text encoding と buffer length 規約を追加で確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels の borrowed pointer と optional out param 規約を再確認する。
- `SkSurface` readPixels / writePixels の ImageInfo + pixels + rowBytes 規約を `SkCanvas` と同じ基準で確認する。
