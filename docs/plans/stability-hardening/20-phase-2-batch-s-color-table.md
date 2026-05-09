# 20 Phase 2 Batch S: color table C API safety

作業開始日時: 2026-05-09 10:38:45 JST

## 目的

Phase 2 の次バッチとして、`SkColorTable` 周辺を fail-safe に寄せる。`SkColorTable` は 256 要素の borrowed channel table と nullable identity table を扱うため、NULL 入力・生成不能時 handle・借用 pointer の規約を明文化する。

対象:

- `skia/capi/sk_color_table.h`
- `skia/capi/sk_color_table.cpp`

## 実装変更

各 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / 生成不能入力時 |
| --- | --- |
| borrowed pointer | `NULL` |
| handle (`sk_color_table_t`) | `0` |
| `bool` query | `false` |
| ref-count mutation | no-op |
| `flatten` | no-op |

static factory では null `sk_sp<SkColorTable>` を handle table に登録せず、C ABI では handle `0` として返す helper を追加した。

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkColorTable_alphaTable` / `redTable` / `greenTable` / `blueTable`: borrowed 256 要素 pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkColorTable_Make`: `table` は 256 要素以上かつ非 NULL。NULL 入力では `0`。
- `SkColorTable_MakeARGBTables`: 各 table は NULL 許可で、Skia 側の identity table として扱う。全 table が identity の場合は生成不要として `0` を返すことがある。
- `SkColorTable_Deserialize`: `buffer` は非 NULL。NULL 入力や生成不能時は `0`。

## smoke test

`test_color_table_invalid_input_smoke` を追加し、`ctest` に `c_skia_color_table_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkColorTable` query/refcount/flatten がクラッシュせず fail-safe 値または no-op になる。
- `SkColorTable_Make(NULL)` と `SkColorTable_Deserialize(NULL)` が handle `0` を返す。
- valid 256 要素 table から borrowed channel table を取得できる。
- `MakeARGBTables(NULL, NULL, NULL, NULL)` が生成不要時に `0` を返す規約を固定する。
- 一部 channel table 指定時、指定 channel と identity channel の内容が取得できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_color_table_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_color_table_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_color_table_invalid_input_smoke` build 成功。
- `c_skia_color_table_invalid_input_smoke` 成功。
- C API invalid-input smoke 20 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_color_table.h`
- `skia/capi/sk_color_table.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkTableMaskFilter` / mask table helper
