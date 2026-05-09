# 25 Phase 2 Batch X: vector C API safety

作業開始日時: 2026-05-09 14:42:10 JST

## 目的

Phase 2 の次バッチとして、`SkV2` / `SkV3` / `SkV4` 周辺を fail-safe に寄せる。これらは `SkM44` と geometry 系 API の基礎値型であり、borrowed scalar pointer と vector pointer 入力を返すため、NULL 入力と pointer lifetime を明文化する。

対象:

- `skia/capi/sk_v2.h`
- `skia/capi/sk_v2.cpp`
- `skia/capi/sk_v3.h`
- `skia/capi/sk_v3.cpp`
- `skia/capi/sk_v4.h`
- `skia/capi/sk_v4.cpp`

## 実装変更

各 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| borrowed pointer | `NULL` |
| vector handle (`sk_v2_t`, `sk_v3_t`, `sk_v4_t`) | default vector handle |
| scalar | `0` |
| delete | no-op |

`SkV2` は引数 vector が handle 型のため、handle `0` は既存 handle helper の default vector として扱う。`SkV3` / `SkV4` は raw pointer 入力のため、NULL を明示的に拒否する。

## borrowed pointer 規約

ヘッダコメントを補強した。

- `SkV2_ptr` / `SkV2_ptrMutable`: borrowed 2 要素 pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkV3_ptr` / `SkV3_ptrMutable`: borrowed 3 要素 pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkV4_ptr` / `SkV4_ptrMutable`: borrowed 4 要素 pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkV3_dot` / `SkV3_cross` / static helpers: 入力 vector pointer は非 NULL。NULL 入力では `0` または default vector handle。
- `SkV4_dot` / static helpers: 入力 vector pointer は非 NULL。NULL 入力では `0` または default vector handle。

## smoke test

`test_vector_invalid_input_smoke` を追加し、`ctest` に `c_skia_vector_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkV2` / `SkV3` / `SkV4` query がクラッシュせず fail-safe 値を返す。
- NULL normalize / cross が default vector handle を返す。
- borrowed pointer accessor が NULL 入力では `NULL`、valid 入力では要素 pointer を返す。
- mutable borrowed pointer から valid vector の内容を更新できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_vector_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_vector_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_vector_invalid_input_smoke` build 成功。
- `c_skia_vector_invalid_input_smoke` 成功。
- C API invalid-input smoke 25 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_v2.h`
- `skia/capi/sk_v2.cpp`
- `skia/capi/sk_v3.h`
- `skia/capi/sk_v3.cpp`
- `skia/capi/sk_v4.h`
- `skia/capi/sk_v4.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkVertices` / geometry array input 周辺
