# 49 Phase 2 Batch AV: image generator C API safety

作業開始日時: 2026-05-10 09:02:52 JST

## 目的

Phase 2 の次バッチとして、`SkImageGenerator` C API を fail-safe に寄せる。image generator は query / decode / YUVA plane 出力で borrowed pointer と output pointer を受け取るため、NULL pointer を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_image_generator.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| `sk_data_t` | `0` |
| `sk_image_info_t` | `0` |
| `reskia_u32_t` | `0` |
| delete | no-op |

`SkImageGenerator_refEncodedData` は generator が NULL、または upstream が encoded data を返さない場合に `static_sk_data_make(nullptr)` へ進まず handle `0` を返す。

`SkImageGenerator_getPixels` は `image_generator` / `info` / `pixels` を必須にした。`SkImageGenerator_getPixelsWithPixmap` は `image_generator` / `pm` を必須にした。

`SkImageGenerator_queryYUVAInfo` は `image_generator` / `supportedDataTypes` / `yuvaPixmapInfo` を必須にした。`SkImageGenerator_getYUVAPlanes` は `image_generator` / `yuvaPixmaps` を必須にした。

`SkImageGenerator_isValid` の `context` は upstream 規約どおり NULL 許可を維持した。

## smoke test

`test_image_generator_invalid_input_smoke` を追加し、`ctest` に `c_skia_image_generator_invalid_input_smoke` として登録した。

確認内容:

- NULL generator の delete が no-op になる。
- query / state / decode / YUVA API が NULL 入力で `false` または handle `0` を返す。
- `SkImageGenerator_isValid(nullptr, nullptr)` が `false` を返す。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_image_generator_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_image_generator_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_image_generator_invalid_input_smoke` build 成功。
- `c_skia_image_generator_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 48 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_image_generator.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkOpenTypeSVGDecoder` の object / canvas pointer 規約
- `SkImageFilter` / `SkImageFilters` の factory output handle と optional pointer 規約
- `SkShader` / `SkShaders` の factory optional pointer 規約
