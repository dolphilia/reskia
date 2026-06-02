# 48 Phase 2 Batch AU: encoder entrypoint C API safety

作業開始日時: 2026-05-10 08:52:53 JST

## 目的

Phase 2 の次バッチとして、encoder entrypoint 群を fail-safe に寄せる。encoder API は borrowed stream、pixmap / YUVA pixmaps / image pointer、options reference、incremental encoder handle、animated frame span を扱うため、NULL pointer や invalid frame handle を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_encoder.{h,cpp}`
- `skia/capi/sk_jpeg_encoder.{h,cpp}`
- `skia/capi/sk_png_encoder.{h,cpp}`
- `skia/capi/sk_webp_encoder.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| `sk_data_t` | `0` |
| `sk_encoder_t` | `0` |
| delete | no-op |

`SkEncoder_encodeRows` は NULL encoder または `numRows <= 0` で `false` を返す。

JPEG / PNG / WebP encoder の stream + pixmap encode と incremental `Make` は `dst` / `src` / `options` を必須にした。image encode は `img` / `options` を必須にし、`ctx` は upstream 規約どおり NULL 許可を維持した。JPEG YUVA encode の `srcColorSpace` は NULL 許可を維持した。

`SkWebpEncoder_EncodeAnimated` は `dst` / `options` と non-empty frame span を必須にした。invalid `const_sk_encoder_frame_t` から得られる empty span は `false` で拒否する。

生成結果が NULL の場合、`static_sk_data_make(nullptr)` / `static_sk_encoder_make(nullptr)` に進まず handle `0` を返す。

## smoke test

`test_encoder_invalid_input_smoke` を追加し、`ctest` に `c_skia_encoder_invalid_input_smoke` として登録した。

確認内容:

- `SkEncoder` NULL / non-positive row count が `false` になる。
- PNG encoder の NULL stream / pixmap / image / options が `false` または handle `0` になる。
- JPEG / WebP encoder は feature enabled 構成で同じ NULL 入力 smoke を実行する。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_encoder_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_encoder_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_encoder_invalid_input_smoke` build 成功。
- `c_skia_encoder_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 47 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

補足:

- 現在の prebuilt 構成では JPEG / WebP encoder C API はリンクされていないため、smoke test の JPEG / WebP 呼び出しは `RESKIA_ENABLE_JPEG_ENCODER` / `RESKIA_ENABLE_WEBP_ENCODER` 有効時だけコンパイルする。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_encoder.{h,cpp}`
- `skia/capi/sk_jpeg_encoder.{h,cpp}`
- `skia/capi/sk_png_encoder.{h,cpp}`
- `skia/capi/sk_webp_encoder.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkImageGenerator` の query / YUVA output pointer 規約
- `SkOpenTypeSVGDecoder` の object / canvas pointer 規約
- `SkImageFilter` / `SkImageFilters` の factory output handle と optional pointer 規約
