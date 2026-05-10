# 82 Phase 2 Batch CC: text blob text buffer and encoding safety

開始時刻: 2026-05-10 21:54:59 JST

## 目的

`81-phase-2-batch-cb-canvas-image-lattice-nine.md` の「次バッチ候補」から、`SkTextBlob` / `SkTextBlobBuilder` 周辺の text encoding と buffer length 規約を追加確認する。既存の C API guard を smoke で固定し、`byteLength` / `textByteCount` / position buffer の扱いをヘッダ上で明確化する。

## 変更内容

- `skia/capi/sk_text_blob.h`
  - `SkTextBlob_MakeFromText` / `MakeFromString` / `MakeFromPosTextH` / `MakeFromPosText` / `MakeFromRSXform` の `byteLength == 0` と `byteLength > 0` の pointer 規約、encoding 範囲、失敗時 0 を明記した。
- `skia/capi/sk_text_blob_builder.h`
  - `SkTextBlobBuilder_allocRunText*` の `textByteCount >= 0` と caller-filled UTF-8 cluster text bytes 予約の規約を明記した。
- `skia/test/test_text_blob_invalid_input_smoke.cpp`
  - invalid encoding、`byteLength > 0` での NULL position/xpos/xform、builder text run の negative `textByteCount` smoke ケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_text_blob.*` / `sk_text_blob_builder.*` の P2 記録を Batch CC に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_text_blob_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_text_blob_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` accessTopLayerPixels / peekPixels の borrowed pointer と optional out param 規約を再確認する。
- `SkSurface` readPixels / writePixels の ImageInfo + pixels + rowBytes 規約を `SkCanvas` と同じ基準で確認する。
- `SkCanvas` drawTextBlob handle / pointer API の handle 0、borrowed pointer、paint 必須規約を追加で確認する。
