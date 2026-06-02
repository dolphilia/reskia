# 50 Phase 2 Batch AW: OpenType SVG decoder C API safety

作業開始日時: 2026-05-10 09:05:28 JST

## 目的

Phase 2 の次バッチとして、`SkOpenTypeSVGDecoder` C API を fail-safe に寄せる。OpenType SVG decoder は object pointer と render target の `SkCanvas` 参照を扱うため、NULL pointer を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_open_type_svg_decoder.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| `size_t` | `0` |
| delete | no-op |

`SkOpenTypeSVGDecoder_approximateSize` は NULL decoder で `0` を返す。

`SkOpenTypeSVGDecoder_render` は `open_type_svg_decoder` / `canvas` を必須にし、どちらかが NULL の場合は `false` を返す。palette span は従来どおり単一 `SkColor` から作る。

## smoke test

`test_open_type_svg_decoder_invalid_input_smoke` を追加し、`ctest` に `c_skia_open_type_svg_decoder_invalid_input_smoke` として登録した。

確認内容:

- NULL decoder の delete が no-op になる。
- NULL decoder の `approximateSize` が `0` になる。
- NULL decoder / NULL canvas の `render` が `false` になる。

補足:

- `sk_open_type_svg_decoder.h` は `SkSpan` 経由で C++17 API を含むため、smoke test target に `cxx_std_17` を明示した。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_open_type_svg_decoder_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_open_type_svg_decoder_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_open_type_svg_decoder_invalid_input_smoke` build 成功。
- `c_skia_open_type_svg_decoder_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 49 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_open_type_svg_decoder.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkImageFilter` / `SkImageFilters` の factory output handle と optional pointer 規約
- `SkShader` / `SkShaders` の factory optional pointer 規約
- `SkBlenders` / `SkColorFilters` の factory input pointer 規約
