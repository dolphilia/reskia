# 45 Phase 2 Batch AR: read/write buffer C API safety completion

作業開始日時: 2026-05-10 08:27:08 JST

## 目的

Phase 2 Batch AI で `partial` として残っていた `SkReadBuffer` / `SkWriteBuffer` の前半 API を fail-safe に寄せる。対象は primitive read/write、geometry/object reference read/write、memory 入力で、NULL buffer や NULL output pointer を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_read_buffer.h`
- `skia/capi/sk_read_buffer.cpp`
- `skia/capi/sk_write_buffer.h`
- `skia/capi/sk_write_buffer.cpp`

## 実装変更

`SkReadBuffer` の constructor / memory / version / primitive / geometry read API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed pointer | `NULL` |
| handle (`sk_point_t`, `sk_rect_t`, `sk_paint_t`) | `0` |
| integer / scalar / color | `0` |
| `bool` | `false` |
| `eof` | `true` |
| setter / output write | no-op |

`SkReadBuffer_newWithDataAndSize(NULL, size > 0)` は `NULL` を返す。`SkReadBuffer_setMemory` は NULL buffer または `data == NULL && size > 0` を no-op にする。

`SkWriteBuffer` は primitive / array / geometry / object write API の writer 本体 NULL を no-op にした。参照渡し相当の payload は NULL を拒否し、array 系は `count > 0` で入力 pointer を必須にした。upstream が NULL payload を扱う `writeFlattenable`、`writeDataAsByteArray`、`writeImage`、`writeTypeface` は payload NULL 許可を維持した。

## smoke test

既存の `test_read_write_buffer_invalid_input_smoke` を拡張した。

確認内容:

- `SkReadBuffer` の memory / version / primitive / geometry read が NULL 入力で fail-safe 値または no-op になる。
- `SkReadBuffer_newWithDataAndSize(NULL, size > 0)` が `NULL` を返す。
- `SkWriteBuffer` の primitive / array / geometry / object write が NULL writer で no-op になる。
- 既存の flattenable / array / factory / validation 系 NULL 入力確認を維持する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-tests --target test_read_write_buffer_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_read_write_buffer_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
```

結果:

- `test_read_write_buffer_invalid_input_smoke` build 成功。
- `c_skia_read_write_buffer_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 44 件成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_read_buffer.h`
- `skia/capi/sk_read_buffer.cpp`
- `skia/capi/sk_write_buffer.h`
- `skia/capi/sk_write_buffer.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
- codec / encoder / decoder 周辺の raw pointer と optional dependency 入力規約
- image generator / codec YUVA query 周辺の output pointer 規約
