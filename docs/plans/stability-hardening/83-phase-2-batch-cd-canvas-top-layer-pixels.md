# 83 Phase 2 Batch CD: canvas top layer pixels and peekPixels safety

開始時刻: 2026-05-10 22:02:02 JST

## 目的

`82-phase-2-batch-cc-text-blob-text-buffers.md` の「次バッチ候補」から、`SkCanvas` accessTopLayerPixels / peekPixels の borrowed pointer と optional out param 規約を追加確認する。C API 境界で NULL canvas / NULL out param の扱いが固定され、返される pixel storage の寿命がヘッダ上で誤解されないようにする。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_accessTopLayerPixels` は NULL canvas で NULL を返し、返却ポインタは canvas/layer 所有の borrowed raw pixels で、storage 変更までの寿命であることを明記した。
  - `SkCanvas_peekPixels` は pixmap が non-null out param で、返される pixmap は canvas pixels を借用し、invalid input は false を返すことを明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_accessTopLayerPixels(nullptr, ...)` が NULL を返すケースを追加した。
  - `SkCanvas_accessTopLayerPixels(canvas, nullptr, nullptr, nullptr)` と `info/rowBytes` 指定 + NULL origin の optional out param 呼び出しを smoke に追加した。
  - `SkCanvas_peekPixels(nullptr, nullptr)` / `SkCanvas_peekPixels(canvas, nullptr)` が false を返すケースを追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch CD に更新した。

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
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkSurface` readPixels / writePixels の ImageInfo + pixels + rowBytes 規約を `SkCanvas` と同じ基準で確認する。
- `SkCanvas` drawTextBlob handle / pointer API の handle 0、borrowed pointer、paint 必須規約を追加で確認する。
- `SkCanvas` drawDrawable / drawPicture pointer API の optional matrix / paint と required drawable / picture 規約を再確認する。
