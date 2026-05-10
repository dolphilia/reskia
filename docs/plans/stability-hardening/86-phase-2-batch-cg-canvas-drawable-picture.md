# 86 Phase 2 Batch CG: canvas drawable and picture draw safety

開始時刻: 2026-05-11 00:42:04 JST

## 目的

`85-phase-2-batch-cf-canvas-text-blob-draw.md` の「次バッチ候補」から、`SkCanvas` drawDrawable / drawPicture pointer API の optional matrix / paint と required drawable / picture 規約を再確認する。NULL pointer が required 引数として Skia に渡らないこと、valid pointer では NULL matrix / paint が optional として扱われることを smoke で固定する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawDrawable` / `SkCanvas_drawDrawableAt` の drawable を borrowed non-null とし、invalid input は no-op と明記した。
  - `SkCanvas_drawPicturePtr` / `SkCanvas_drawPicturePtrWithMatrixPaint` の picture を borrowed non-null とし、`matrix` / `paint` は NULL 許可、invalid input は no-op と明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkPictureRecorder` で valid `SkPicture` / `SkDrawable` を作成し、handle / pointer drawPicture と drawDrawable の smoke ケースを追加した。
  - `SkCanvas_drawPictureHandleWithMatrixPaint` / `SkCanvas_drawPicturePtrWithMatrixPaint` で NULL matrix / NULL paint と non-null paint の両方を確認した。
  - `SkCanvas_drawDrawable` の NULL matrix と `SkCanvas_drawDrawableAt` の valid drawable 経路を確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.*` の P2 記録を Batch CG に更新した。

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

- `SkSurface` asyncRescaleAndReadPixels 系の callback fail path と required srcRect / info / dstSize 規約を追加で確認する。
- `SkCanvas` drawVertices handle API の handle 0、無効 handle、paint 必須規約を追加で確認する。
- `SkCanvas` drawString / drawStringObject の required string/font/paint と invalid input no-op 規約を追加で確認する。
