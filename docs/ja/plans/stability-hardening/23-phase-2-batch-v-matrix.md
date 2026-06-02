# 23 Phase 2 Batch V: matrix C API safety

作業開始日時: 2026-05-09 14:16:31 JST

## 目的

Phase 2 の次バッチとして、`SkMatrix` 周辺を fail-safe に寄せる。`SkMatrix` は geometry 系の基礎値型であり、raw array、output pointer、count 付き point/vector 配列、rect pointer を広く受け取るため、NULL 入力と範囲外 index を C ABI 境界で明示的に落とす。

対象:

- `skia/capi/sk_matrix.h`
- `skia/capi/sk_matrix.cpp`

## 実装変更

各 C API に NULL ガード、index/range チェック、count と pointer の整合チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_matrix_t`) | `0` |
| rect handle | empty rect handle |
| point handle | default point handle |
| `bool` query / mutation | `false` |
| scalar | `0` |
| min/max scale | `-1` |
| type mask | `-1` |
| void mutation / mapping | no-op |

## raw array / output pointer 規約

ヘッダコメントを補強した。

- `get(index)` / `set(index)`: `index` は `0..8`。範囲外では `0` / handle `0`。
- `rc(r, c)`: `r/c` は `0..2`。範囲外では `0`。
- `get9` / `set9`: `buffer` は 9 要素以上、非 NULL。
- `asAffine` / `setAffine` / `SetAffineIdentity`: `affine` は 6 要素以上、非 NULL。
- `setPolyToPoly`: `count` は `0..4`。`count > 0` では `src` / `dst` は count 要素以上、非 NULL。
- `mapPoints` / `mapVectors` / homogeneous mapping: `count <= 0` は no-op。`count > 0` では入出力配列は count 要素以上、非 NULL。
- `mapRectToQuad`: `dst` は 4 要素以上、`rect` は非 NULL。
- `invert` / `decomposeScale`: upstream が許可する optional output pointer は NULL 許可のまま残す。

## smoke test

`test_matrix_invalid_input_smoke` を追加し、`ctest` に `c_skia_matrix_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkMatrix` query/mutation/mapping がクラッシュせず fail-safe 値または no-op になる。
- index/range 不正、raw array NULL、rect pointer NULL、factory NULL が `0` / `false` / no-op になる。
- valid identity matrix で `get9` / `set9` / `mapXYToPoint` / `mapRect` / `asAffine` が動く。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_matrix_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_matrix_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|matrix|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_matrix_invalid_input_smoke` build 成功。
- `c_skia_matrix_invalid_input_smoke` 成功。
- C API invalid-input smoke 23 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_matrix.h`
- `skia/capi/sk_matrix.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkM44` / `SkMatrix44` が残っていれば geometry matrix 周辺
