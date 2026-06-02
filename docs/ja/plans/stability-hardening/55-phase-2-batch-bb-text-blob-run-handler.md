# 55 Phase 2 Batch BB: text blob run handler C API safety

作業開始日時: 2026-05-10 09:28:05 JST

## 目的

Phase 2 の次バッチとして、`SkTextBlob` / builder 周辺の span / output pointer 規約を再確認する。`SkTextBlob` 本体と `SkTextBlobBuilder` は Batch AK で処理済みだったため、未処理の `SkTextBlobBuilderRunHandler` を対象にした。

対象:

- `skia/capi/sk_text_blob_builder_run_handler.{h,cpp}`
- `skia/test/test_text_blob_run_handler_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| void | no-op |

`SkTextBlobBuilderRunHandler_makeBlob` は NULL handler または NULL `sk_sp<SkTextBlob>` 結果で handle `0` を返す。

`endPoint` は NULL handler で point handle `0` を返す。`beginLine` / `commitRunInfo` / `commitLine` は NULL handler で no-op にした。

`runInfo` / `runBuffer` / `commitRunBuffer` は handler と `RunInfo` を必須にした。NULL 入力では no-op または buffer handle `0` を返す。

`SkTextBlobBuilderRunHandler_new` の `utf8Text` は upstream 実装が NULL を許容し、`runBuffer` で text copy を省略するため NULL 許可を維持した。

## smoke test

`test_text_blob_run_handler_invalid_input_smoke` を追加し、`RESKIA_ENABLE_SKPARAGRAPH` 有効時だけ `ctest` に `c_skia_text_blob_run_handler_invalid_input_smoke` として登録した。

確認内容:

- NULL handler の API が no-op / handle `0` になる。
- `SkTextBlobBuilderRunHandler_new(nullptr, 0)` が handler を返す。
- 空 handler の `makeBlob` が handle `0` を返す。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
ctest --test-dir skia/cmake-build-stability-tests -N -R 'c_skia_text_blob_run_handler_invalid_input_smoke'
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-skparagraph-tests -DRESKIA_DEPS_MODE=source -DRESKIA_ENABLE_SKPARAGRAPH=ON -DRESKIA_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-stability-skparagraph-tests --target test_text_blob_run_handler_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-skparagraph-tests -R 'c_skia_text_blob_run_handler_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- prebuilt test 構成では `RESKIA_ENABLE_SKPARAGRAPH` 無効のため run-handler smoke 登録なし。
- prebuilt Debug build 成功。
- SkParagraph/source test configure 成功。
- `test_text_blob_run_handler_invalid_input_smoke` build 成功。
- `c_skia_text_blob_run_handler_invalid_input_smoke` 成功。
- prebuilt Phase 2 invalid-input smoke 52 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_text_blob_builder_run_handler.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkBlender` instance API の refcount / flattenable 規約
- `SkPathBuilder` の builder pointer / output path 規約
- `SkTiledImageUtils` の required image / rect / sampling pointer 規約
