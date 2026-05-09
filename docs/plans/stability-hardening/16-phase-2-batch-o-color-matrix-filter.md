# 16 Phase 2 Batch O: color matrix filter C API safety

作業開始日時: 2026-05-09 10:18:03 JST

## 目的

Phase 2 の次バッチとして、`SkColorMatrixFilter` 周辺を fail-safe に寄せる。`SkColorMatrixFilter` は deprecated な `SkColorFilter` 派生 API であり、実質的には inherited `SkColorFilter` 操作と `MakeLightingFilter` static factory が中心のため、Batch M の `SkColorFilter` 規約を横展開する。

対象:

- `skia/capi/sk_color_matrix_filter.h`
- `skia/capi/sk_color_matrix_filter.cpp`

## 実装変更

各 C API に NULL ガードを追加し、factory 戻り値を `make_color_filter_handle()` 経由に統一した。

戻り規約:

| 戻り値種別 | NULL / 無効入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric/size/type | `0` |
| `bool` query / operation | `false` |
| ref-count mutation / register | no-op |
| `filterColor(NULL, color)` | 入力 `color` を返す |

主な対象:

- inherited `SkColorFilter` query / filter / compose / working color space / serialize / flatten
- `Deserialize`
- flattenable factory name lookup / registration
- `MakeLightingFilter`

## raw buffer / typed pointer 規約

ヘッダコメントを補強した。

- `SkColorMatrixFilter_asAColorMode`: `color` / `mode` は NULL 許可。
- `SkColorMatrixFilter_asAColorMatrix`: `matrix` は 20 要素以上、非 NULL。
- `SkColorMatrixFilter_filterColor4f`: `srcColor` は非 NULL。`srcCS` / `dstCS` は NULL 許可。
- `SkColorMatrixFilter_serialize`: retained data handle。`serial_procs` は NULL 許可。
- `SkColorMatrixFilter_serializeToMemory`: `memory` は `memory_size` バイト以上。サイズ取得は `serialize()` を使う。
- `SkColorMatrixFilter_Deserialize`: `data` は `size` バイト以上、非 NULL。`procs` は NULL 許可。

## smoke test

`test_color_matrix_filter_invalid_input_smoke` を追加し、`ctest` に `c_skia_color_matrix_filter_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkColorMatrixFilter` query/filter/serialize/ref-count がクラッシュせず fail-safe 値または no-op になる。
- NULL factory lookup / register が `0` または no-op になる。
- `MakeLightingFilter` の正常系 handle を最小確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_color_matrix_filter_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_color_matrix_filter_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_color_matrix_filter_invalid_input_smoke` build 成功。
- `c_skia_color_matrix_filter_invalid_input_smoke` 成功。
- C API invalid-input smoke 16 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_color_matrix_filter.h`
- `skia/capi/sk_color_matrix_filter.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkContourMeasure` / path measure 周辺
- `SkFont` / `SkTypeface`
- `SkColor` / `SkColorPriv` 周辺
