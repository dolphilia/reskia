# 36 Phase 2 Batch AI: read/write buffer C API safety

作業開始日時: 2026-05-10 00:46:00 JST

## 目的

Phase 2 の次バッチとして、`SkReadBuffer` / `SkWriteBuffer` の flattenable factory 周辺を fail-safe に寄せる。read/write buffer はシリアライズ境界にあり、raw flattenable pointer、handle 化された `sk_sp` 戻り値、raw array、factory/deserial procs を横断するため、C ABI 境界で NULL 入力と出力 pointer の必須条件を明示する。

対象:

- `skia/capi/sk_read_buffer.h`
- `skia/capi/sk_read_buffer.cpp`
- `skia/capi/sk_write_buffer.h`
- `skia/capi/sk_write_buffer.cpp`

## 実装変更

`SkReadBuffer` 後半の flattenable / array / factory / validation 系 API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| raw `SkFlattenable*` | `NULL` |
| handle (`sk_data_t`, `sk_image_t`, filter handles など) | `0` |
| `bool` | `false` |
| count / integer fallback | `0` |
| `SkLegacyFQ` | `-1` |
| pointer borrow | `NULL` |
| setter / mutation | no-op |

`SkWriteBuffer` は writer 本体が NULL の場合に no-op または `0` / `NULL` を返すようにした。upstream が NULL payload を許容する `writeFlattenable`、`writeDataAsByteArray`、`writeTypeface` は payload 側の NULL 許可を維持し、writer 本体だけを必須にした。

## pointer / raw array 規約

ヘッダコメントを補強した。

- `SkReadBuffer_readFlattenable`: NULL buffer または enum 範囲外 type は `NULL`。
- handle 化 read API: NULL buffer または読み出し結果なしは `0`。
- array read API: `size > 0` では出力 array は非 NULL。invalid 入力では `false`。
- `skipByteArray`: `size` out pointer は非 NULL。
- `setTypefaceArray` / `setFactoryPlayback`: `count > 0` では array は非 NULL。`count < 0` は no-op。
- `setDeserialProcs`: `procs` は非 NULL。invalid 入力では no-op。
- `SkWriteBuffer_writePad32` / `writeByteArray`: length が正なら入力 buffer は非 NULL。
- `SkWriteBuffer_writeStream`: stream は非 NULL。invalid 入力では `0`。

## smoke test

`test_read_write_buffer_invalid_input_smoke` を追加し、`ctest` に `c_skia_read_write_buffer_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkReadBuffer` 入力が `NULL` / `0` / `false` / no-op の規約に従う。
- invalid flattenable type が `NULL` になる。
- NULL `SkWriteBuffer` 入力が no-op / `0` / `NULL` の規約に従う。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_read_write_buffer_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_read_write_buffer_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_read_write_buffer_invalid_input_smoke` build 成功。
- `c_skia_read_write_buffer_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 36 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`partial` に変更:

- `skia/capi/sk_read_buffer.h`
- `skia/capi/sk_read_buffer.cpp`
- `skia/capi/sk_write_buffer.h`
- `skia/capi/sk_write_buffer.cpp`

`SkReadBuffer` / `SkWriteBuffer` は前半の primitive read/write や geometry/object reference 系がまだ広く残るため、done ではなく partial とした。

## 次バッチ候補

Phase 2 の次候補:

- `SkTextBlob` / glyph-buffer 周辺
- `SkRegion` / clipping helper 周辺
- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
