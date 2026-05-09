# 46 Phase 2 Batch AS: codec C API safety

作業開始日時: 2026-05-10 08:34:57 JST

## 目的

Phase 2 の次バッチとして、`SkCodec` 本体の C API 境界を fail-safe に寄せる。codec は encoded data / stream / pixmap / YUVA output / scanline decode を横断するため、NULL codec、NULL output pointer、invalid stream/data handle、invalid selection policy を upstream の dereference や無意味な handle 生成に渡さない。

対象:

- `skia/capi/sk_codec.h`
- `skia/capi/sk_codec.cpp`

## 実装変更

`SkCodec` query / decode / scanline / frame / static factory API に NULL ガードと invalid handle チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed pointer | `NULL` |
| handle (`sk_image_info_t`, `sk_i_size_t`, `sk_i_rect_t`, tuple/vector/codec handle) | `0` |
| integer / count | `0` |
| scanline position / enum fallback | `-1` |
| `bool` | `false` |
| `SkCodec::Result` | `kInvalidParameters` または `kInvalidInput` |
| delete | no-op |

`SkCodec_MakeFromStream` は valid owned stream handle と valid `SelectionPolicy` を必須にした。invalid stream は `result` に `kInvalidInput`、invalid selection policy は `kInvalidParameters` を書いて handle `0` を返す。

`SkCodec_MakeFromData` は引数型を `sk_data_t` に修正し、invalid `SkData` handle では handle `0` を返す。`SkCodec::MakeFromData` が `nullptr` を返した場合も handle `0` を返し、空 codec handle は作らない。

## smoke test

`test_codec_invalid_input_smoke` を追加し、`ctest` に `c_skia_codec_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkCodec` query / decode / scanline / frame API が fail-safe 値になる。
- NULL `SkImageInfo` / pixmap / YUVA output pointer が dereference されない。
- invalid stream/data handle と invalid selection policy が handle `0` と規約どおりの result になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_codec_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_codec_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_codec_invalid_input_smoke` build 成功。
- `c_skia_codec_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 45 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

補足:

- `cmake --build skia/cmake-build-stability-tests --target test_codec_smoke -j 8` は失敗した。失敗内容は Skia header 側が C++17 機能（`std::is_integral_v`、`std::data`、`template <auto>` など）を要求する一方で、この target が現行設定では C++17 としてコンパイルされていないことによるもの。今回追加した `test_codec_invalid_input_smoke` と Phase 2 invalid-input smoke には影響しない。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_codec.h`
- `skia/capi/sk_codec.cpp`

## 次バッチ候補

Phase 2 の次候補:

- decoder entrypoint (`SkGifDecoder` / `SkPngDecoder` / optional decoder 群) の raw encoded buffer / stream / data handle 規約
- encoder entrypoint (`SkJpegEncoder` / `SkPngEncoder` / `SkWebpEncoder`) の stream / pixmap / option pointer 規約
- `SkImageGenerator` の query / YUVA output pointer 規約
