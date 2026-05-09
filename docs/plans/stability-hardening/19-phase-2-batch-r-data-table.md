# 19 Phase 2 Batch R: data table C API safety

作業開始日時: 2026-05-09 10:31:17 JST

## 目的

Phase 2 の次バッチとして、`SkDataTable` 周辺を fail-safe に寄せる。`SkDataTable` は immutable table の borrowed entry pointer と raw input array factory を扱うため、NULL 入力・範囲外 index・空 table の規約を明文化する。

対象:

- `skia/capi/sk_data_table.h`
- `skia/capi/sk_data_table.cpp`

## 実装変更

各 C API に NULL ガードと index 範囲チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / 範囲外入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_data_table_t`) | `0` |
| count / size | `0` |
| `isEmpty(NULL)` | `true` |
| `bool` query | `false` |
| ref-count mutation | no-op |

factory 規約:

- `MakeCopyArrays`: `count <= 0` は empty table。`count > 0` で `ptrs` / `sizes` が NULL の場合は `0`。
- `MakeCopyArray`: `count <= 0` は empty table。`count > 0` で `array == NULL` または `elemSize == 0` の場合は `0`。
- `MakeArrayProc`: `count <= 0` は empty table。`count > 0` で `array == NULL` または `elemSize == 0` の場合は `0`。

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkDataTable_at`: borrowed pointer。caller は解放しない。範囲外/NULL 入力では `NULL`、`size` が非 NULL なら `0` を書く。
- `SkDataTable_atStr`: borrowed C string。caller は解放しない。範囲外/NULL 入力では `NULL`。
- `SkDataTable_MakeCopyArrays`: `ptrs` / `sizes` は `count` 要素以上。
- `SkDataTable_MakeCopyArray`: `array` は `elemSize * count` バイト以上。
- `SkDataTable_MakeArrayProc`: `array` ownership を `SkDataTable` に渡す。

## smoke test

`test_data_table_invalid_input_smoke` を追加し、`ctest` に `c_skia_data_table_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkDataTable` query/refcount がクラッシュせず fail-safe 値または no-op になる。
- 範囲外 index が `0` / `NULL` を返す。
- invalid raw input factory が handle `0` を返す。
- `count <= 0` factory が empty table を返す。
- valid copy array / copy arrays で entry と string を取得できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_data_table_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_data_table_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_data_table_invalid_input_smoke` build 成功。
- `c_skia_data_table_invalid_input_smoke` 成功。
- C API invalid-input smoke 19 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_data_table.h`
- `skia/capi/sk_data_table.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkColorTable` / table color helper
