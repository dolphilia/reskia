# 71 Phase 2 Batch BR: annotation and AndroidCodec C API safety

開始時刻: 2026-05-10 18:29:35 JST

## 目的

`70-phase-2-batch-bq-encoded-cubic.md` の「次バッチ候補」から、`SkAnnotation` / `SkAndroidCodec` の pointer / handle 規約を確認する。C API 境界で NULL pointer や handle `0` が Skia API にそのまま渡らないよう、既存 ABI の範囲で sentinel を固定する。

## 変更内容

- `skia/capi/sk_annotation.cpp`
  - annotation helper 3 件は `canvas` / geometry / `data` のいずれかが NULL の場合 no-op にした。
- `skia/capi/sk_annotation.h`
  - 借用 pointer が required であることと、invalid input は no-op であることを明記した。
- `skia/capi/sk_android_codec.cpp`
  - `SkAndroidCodec` NULL object で borrowed pointer は NULL、enum/value は `-1` または `0`、size handle は handle `0` を返すようにした。
  - pixel decode 系は NULL object / `info` / `pixels` で `SkCodec::kInvalidParameters` を返すようにした。
  - static factory は入力 handle `0` または Skia factory failure で AndroidCodec handle `0` を返すようにした。
- `skia/capi/sk_android_codec.h`
  - NULL object、sample size、factory handle `0`、pixel decode invalid sentinel を明記した。
  - `MakeFromStream` / `MakeFromData` の source handle 型を stream/data として明確化した。
- `skia/test/test_annotation_android_codec_invalid_input_smoke.cpp`
  - annotation NULL no-op と AndroidCodec NULL / handle `0` sentinel を smoke 化した。
- `cmake/reskia/tests.cmake`
  - `c_skia_annotation_android_codec_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_annotation.*` / `sk_android_codec.*` の P2 記録を Batch BR に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_annotation_android_codec_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_annotation_android_codec_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|op_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|document|stream|wstream|file_stream|stream_derived|encoded_cubic|annotation_android_codec|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_annotation_android_codec_invalid_input_smoke`: build 成功。
- `c_skia_annotation_android_codec_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 65/65 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkBBoxHierarchy` / `SkAutoCanvasRestore` など、まだ todo の lifecycle / pointer 規約を確認する。
