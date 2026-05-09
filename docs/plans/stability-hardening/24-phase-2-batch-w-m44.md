# 24 Phase 2 Batch W: M44 C API safety

作業開始日時: 2026-05-09 14:35:58 JST

## 目的

Phase 2 の次バッチとして、`SkM44` 周辺を fail-safe に寄せる。`SkM44` は `SkMatrix` と同じ geometry matrix 系だが、4x4 index、row/col vector、16 要素 raw array、`SkMatrix` / `SkRect` / `SkV3` / `SkV4` pointer を受け取るため、NULL 入力と範囲外 index を C ABI 境界で明示的に落とす。

対象:

- `skia/capi/sk_m_44.h`
- `skia/capi/sk_m_44.cpp`

## 実装変更

各 C API に NULL ガード、4x4 index/range チェック、raw array / vector / rect pointer の整合チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_m_44_t`, `sk_matrix_t`) | `0` |
| vector handle (`sk_v4_t`) | default vector handle |
| `bool` query / mutation | `false` |
| scalar | `0` |
| void mutation / dump / major export | no-op |

## raw array / pointer 規約

ヘッダコメントを補強した。

- `rc(r, c)` / `setRC(r, c)`: `r/c` は `0..3`。範囲外では `0` / no-op。
- `row(i)` / `col(i)` / `setRow(i)` / `setCol(i)`: `i` は `0..3`。範囲外では default vector handle / no-op。
- `getColMajor` / `getRowMajor`: output は 16 要素以上、非 NULL。
- `RowMajor` / `ColMajor`: input は 16 要素以上、非 NULL。
- `Rows` / `Cols`: 4 本の `SkV4` pointer はすべて非 NULL。
- `newFromConcat` / `setConcat` / `preConcat` / `postConcat`: 行列 pointer は非 NULL。
- `newFromMatrix` / `preConcatMatrix`: `SkMatrix` pointer は非 NULL。
- `RectToRect`: `src` / `dst` は非 NULL。
- `LookAt`: `eye` / `center` / `up` は非 NULL。
- `invert`: upstream が許可する optional output pointer は NULL 許可のまま残す。

## smoke test

`test_m44_invalid_input_smoke` を追加し、`ctest` に `c_skia_m44_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkM44` query/mutation/export がクラッシュせず fail-safe 値または no-op になる。
- 4x4 index/range 不正、raw array NULL、rect/vector pointer NULL、factory NULL が `0` / `false` / no-op になる。
- valid default matrix で row-major export、`rc` / `setRC`、row/col mutation が動く。
- valid `Translate`、`transpose`、`asM33`、`RowMajor`、`RectToRect` が handle を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_m44_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_m44_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_m44_invalid_input_smoke` build 成功。
- `c_skia_m44_invalid_input_smoke` 成功。
- C API invalid-input smoke 24 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_m_44.h`
- `skia/capi/sk_m_44.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkV2` / `SkV3` / `SkV4`
- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
