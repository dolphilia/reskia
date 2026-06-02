# 70 Phase 2 Batch BQ: encoded origin and cubic C API safety

開始時刻: 2026-05-10 13:39:12 JST

## 目的

`69-phase-2-batch-bp-document-dynamic-stream.md` の「次バッチ候補」から、`SkEncodedOrigin` / `SkCubicMap` / `SkCubicResampler` の enum / value 規約を確認する。invalid enum や handle `0` が Skia API にそのまま渡らないよう、既存 ABI の範囲で sentinel を固定する。

## 変更内容

- `skia/capi/sk_encoded_origin.cpp`
  - `SkEncodedOrigin` 範囲外 enum では matrix handle `0` / `false` を返すようにした。
- `skia/capi/sk_encoded_origin.h`
  - enum 範囲と invalid sentinel を明記した。
- `skia/capi/sk_cubic_map.cpp`
  - `SkCubicMap_new` / `SkCubicMap_IsLinear` は point handle `0` / invalid handle を拒否するようにした。
  - `computeYFromX` / `computeFromT` は NULL object で `0` / handle `0` を返すようにした。
- `skia/capi/sk_cubic_map.h`
  - point handle と NULL object sentinel を明記した。
- `skia/capi/sk_cubic_resampler.h`
  - NULL delete no-op と factory handle 規約を明記した。
- `skia/test/test_encoded_cubic_invalid_input_smoke.cpp`
  - encoded origin invalid enum、cubic map invalid handles / NULL object、cubic resampler factories を smoke 化した。
- `cmake/reskia/tests.cmake`
  - `c_skia_encoded_cubic_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_encoded_origin.*` / `sk_cubic_map.*` / `sk_cubic_resampler.*` の P2 記録を Batch BQ に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_encoded_cubic_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_encoded_cubic_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_encoded_cubic_invalid_input_smoke`: build 成功。
- `c_skia_encoded_cubic_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 64/64 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkAnnotation` / `SkAndroidCodec` の pointer / enum 規約を確認する。
