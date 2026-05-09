# 47 Phase 2 Batch AT: decoder entrypoint C API safety

作業開始日時: 2026-05-10 08:43:17 JST

## 目的

Phase 2 の次バッチとして、codec decoder entrypoint 群を fail-safe に寄せる。decoder API は raw encoded buffer、owned stream handle、`SkData` handle、optional decode context、`SkCodec::Result` output を扱うため、NULL raw buffer や invalid handle を upstream に渡さず、空 codec handle を作らない。

対象:

- `skia/capi/sk_avif_decoder.{h,cpp}`
- `skia/capi/sk_bmp_decoder.{h,cpp}`
- `skia/capi/sk_gif_decoder.{h,cpp}`
- `skia/capi/sk_ico_decoder.{h,cpp}`
- `skia/capi/sk_jpeg_decoder.{h,cpp}`
- `skia/capi/sk_jpegxl_decoder.{h,cpp}`
- `skia/capi/sk_png_decoder.{h,cpp}`
- `skia/capi/sk_raw_decoder.{h,cpp}`
- `skia/capi/sk_wbmp_decoder.{h,cpp}`
- `skia/capi/sk_webp_decoder.{h,cpp}`

## 実装変更

decoder 共通 helper として `skia/capi/sk_decoder_common.h` を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `Is*` bool | `false` |
| codec handle | `0` |
| `SkCodec::Result*` output | 非 NULL なら `kInvalidInput` |
| decode context | NULL 許可 |

`Is*` は `ptr == NULL && size > 0` を拒否して `false` を返す。`Decode` は valid owned stream handle を必須にし、invalid handle なら result に `kInvalidInput` を書いて handle `0` を返す。`DecodeFromData` は valid `SkData` handle を必須にし、invalid handle なら同じく `kInvalidInput` と handle `0` を返す。

`SkBmpDecoder_DecodeFromDataHandle` は実装が `SkData` handle を読む API だったため、引数型を `sk_data_t` に修正した。`SkPngDecoder` / `SkJpegDecoder` / `SkWbmpDecoder` / `SkWebpDecoder` の `int` handle 引数も typed handle に揃えた。

## smoke test

`test_decoder_invalid_input_smoke` を追加し、`ctest` に `c_skia_decoder_invalid_input_smoke` として登録した。

確認内容:

- common decoder の `Is*` が NULL raw buffer を拒否する。
- invalid stream handle の `Decode` が handle `0` と `kInvalidInput` を返す。
- invalid data handle の `DecodeFromData` が handle `0` と `kInvalidInput` を返す。
- AVIF / GIF / JPEG XL / RAW は feature enabled 構成で同じ smoke を実行する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_decoder_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_decoder_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_decoder_invalid_input_smoke` build 成功。
- `c_skia_decoder_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 46 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_avif_decoder.{h,cpp}`
- `skia/capi/sk_bmp_decoder.{h,cpp}`
- `skia/capi/sk_gif_decoder.{h,cpp}`
- `skia/capi/sk_ico_decoder.{h,cpp}`
- `skia/capi/sk_jpeg_decoder.{h,cpp}`
- `skia/capi/sk_jpegxl_decoder.{h,cpp}`
- `skia/capi/sk_png_decoder.{h,cpp}`
- `skia/capi/sk_raw_decoder.{h,cpp}`
- `skia/capi/sk_wbmp_decoder.{h,cpp}`
- `skia/capi/sk_webp_decoder.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- encoder entrypoint (`SkJpegEncoder` / `SkPngEncoder` / `SkWebpEncoder`) の stream / pixmap / option pointer 規約
- `SkImageGenerator` の query / YUVA output pointer 規約
- `SkOpenTypeSVGDecoder` の object / canvas pointer 規約
