# 136 Phase 2 Batch EE: image async callback context

開始時刻: 2026-05-12 23:40:23 JST

## 目的

`134-phase-2-batch-ec-runtime-builder-make-ownership.md` の「次バッチ候補」から、`SkImage` asyncRescaleAndReadPixels / asyncRescaleAndReadPixelsYUV420 callback context と invalid input no-op 規約を再確認する。invalid input では callback があれば NULL result で呼び、callback が NULL なら no-op になることを固定する。

## 変更内容

- `skia/capi/sk_image.h`
  - `SkImage_asyncRescaleAndReadPixels` / `SkImage_asyncRescaleAndReadPixelsYUV420` の NULL callback no-op と nullable context 規約を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - `SkImage_asyncRescaleAndReadPixelsYUV420` の invalid dstSize で callback が呼ばれることを既存 smoke として維持した。
  - YUV420 版で NULL callback が no-op になり、callback count を増やさないことを確認した。
  - YUV420 版で context が NULL でも callback に NULL result が渡ることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` の P2 記録を Batch EE に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke test_image_surface_invalid_input_smoke test_runtime_effect_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|runtime_effect)_invalid_input_smoke' --output-on-failure`
  - 成功。3/3 passed。
- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|auto_canvas_restore_bbox|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure`
  - 成功。66/66 passed。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkRuntimeEffect` makeColorFilter / makeBlender returned handle ownership と data / children optional 規約を再確認する。
