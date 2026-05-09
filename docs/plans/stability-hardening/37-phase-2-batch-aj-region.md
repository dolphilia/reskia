# 37 Phase 2 Batch AJ: region C API safety

作業開始日時: 2026-05-10 07:14:13 JST

## 目的

Phase 2 の次バッチとして、`SkRegion` / clipping helper 周辺を fail-safe に寄せる。`SkRegion` は clip / draw / serialization にまたがって参照されるため、C ABI 境界で NULL 入力、raw array、borrowed pointer、operation enum の扱いを明示する。

対象:

- `skia/capi/sk_region.h`
- `skia/capi/sk_region.cpp`

## 実装変更

`SkRegion` C API 全体に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `SkRegion*` factory | `NULL` |
| borrowed pointer | `NULL` |
| `bool` query / mutation / op | `false` |
| `isEmpty` | `true` |
| complexity / memory size | `0` |
| void mutation | no-op |

`SkRegion::Op` は `kDifference_Op` から `kLastOp` までを有効範囲とし、範囲外 op は `false` を返して upstream を呼ばない。

## pointer / raw array 規約

ヘッダコメントを補強した。

- copy / rect factory: 入力が NULL の場合は `NULL`。
- query 系: NULL 入力は fail-safe 値を返す。`isEmpty` だけは空 region 扱いで `true`。
- `getBounds`: borrowed pointer のため NULL region では `NULL`。
- `setRects`: `count > 0` では rect array は非 NULL。`count < 0` は `false`。
- `setPath`: region / path / clip は非 NULL。
- `translateToRegion`: source / destination は非 NULL。invalid 入力は no-op。
- op 系: region / rect / operand / valid op は必須。
- `writeToMemory`: buffer は Skia のサイズ照会用途として NULL 許可。region NULL は `0`。
- `readFromMemory`: region / buffer は非 NULL。

## smoke test

`test_region_invalid_input_smoke` を追加し、`ctest` に `c_skia_region_invalid_input_smoke` として登録した。

確認内容:

- NULL factory / query / mutation / op / serialization が規約通り fail-safe になる。
- invalid op と invalid rect array count が upstream を呼ばず `false` になる。
- NULL void mutation がクラッシュせず no-op になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_region_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_region_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_region_invalid_input_smoke` build 成功。
- `c_skia_region_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 37 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_region.h`
- `skia/capi/sk_region.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkTextBlob` / glyph-buffer 周辺
- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkRasterHandleAllocator` / allocator callback 周辺
