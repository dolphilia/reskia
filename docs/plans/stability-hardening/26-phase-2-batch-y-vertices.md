# 26 Phase 2 Batch Y: vertices C API safety

作業開始日時: 2026-05-09 15:02:56 JST

## 目的

Phase 2 の次バッチとして、`SkVertices` 周辺を fail-safe に寄せる。`SkVertices::MakeCopy` は vertex positions、optional tex coords / colors、optional index array を raw pointer と count で受け取るため、NULL 入力・count 不整合・生成不能時 handle を C ABI 境界で明示する。

対象:

- `skia/capi/sk_vertices.h`
- `skia/capi/sk_vertices.cpp`

## 実装変更

各 C API に NULL ガードと raw array/count チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| borrowed pointer | `NULL` |
| handle (`sk_vertices_t`) | `0` |
| id / size | `0` |
| `bool` query | `false` |
| ref-count mutation | no-op |

static factory では null `sk_sp<SkVertices>` を handle table に登録せず、C ABI では handle `0` として返す helper を追加した。

## raw array / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkVertices_bounds`: borrowed pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkVertices_MakeCopy`: `mode` は `0..kLast_VertexMode`。`vertexCount > 0` では `positions` は vertexCount 要素以上、非 NULL。
- `texs` / `colors`: NULL 許可。指定する場合は vertexCount 要素以上。
- `indices`: `indexCount > 0` では indexCount 要素以上、非 NULL。`indexCount == 0` では無視。
- `indexCount < 0`、invalid mode、NULL required pointer、生成不能時は handle `0`。

## smoke test

`test_vertices_invalid_input_smoke` を追加し、`ctest` に `c_skia_vertices_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkVertices` query/refcount がクラッシュせず fail-safe 値または no-op になる。
- invalid mode、empty/negative count、NULL required arrays が handle `0` を返す。
- valid indexed vertices が handle を返し、unique id / bounds / approximate size を取得できる。
- valid non-indexed vertices が handle を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_vertices_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_vertices_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_vertices_invalid_input_smoke` build 成功。
- `c_skia_vertices_invalid_input_smoke` 成功。
- C API invalid-input smoke 26 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_vertices.h`
- `skia/capi/sk_vertices.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkFontStyle` / `SkFontStyleSet`
