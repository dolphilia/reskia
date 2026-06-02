# 40 Phase 2 Batch AM: ref-count C API safety

作業開始日時: 2026-05-10 07:37:06 JST

## 目的

Phase 2 の次バッチとして、`SkRefCnt` / `SkRefCntBase` の raw ref-count helper 周辺を fail-safe に寄せる。これらは複数の C API object が共有する参照カウント操作の基礎なので、NULL 入力時の no-op / query fallback を明示する。

対象:

- `skia/capi/sk_ref_cnt.h`
- `skia/capi/sk_ref_cnt.cpp`
- `skia/capi/sk_ref_cnt_base.h`
- `skia/capi/sk_ref_cnt_base.cpp`

## 実装変更

`SkRefCnt` / `SkRefCntBase` wrapper に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `unique` | `false` |
| `ref` / `unref` / `release` | no-op |

`SkRefCntBase_new` は従来どおり新規 `SkRefCntBase` を返す。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `release` / `unref`: owned reference を減らす。NULL 入力では no-op。
- `ref`: retained reference を増やす。NULL 入力では no-op。
- `unique`: NULL 入力では `false`。

## smoke test

`test_ref_cnt_invalid_input_smoke` を追加し、`ctest` に `c_skia_ref_cnt_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkRefCnt` wrapper が no-op / `false` になる。
- NULL `SkRefCntBase` wrapper が no-op / `false` になる。
- valid `SkRefCntBase` の `unique -> ref -> unique false -> unref -> unique` を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_ref_cnt_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_ref_cnt_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_ref_cnt_invalid_input_smoke` build 成功。
- `c_skia_ref_cnt_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 40 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_ref_cnt.h`
- `skia/capi/sk_ref_cnt.cpp`
- `skia/capi/sk_ref_cnt_base.h`
- `skia/capi/sk_ref_cnt_base.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
- `SkPixelRef` / `SkMallocPixelRef` 周辺
