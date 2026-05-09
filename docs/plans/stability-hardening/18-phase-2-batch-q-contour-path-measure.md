# 18 Phase 2 Batch Q: contour / path measure C API safety

作業開始日時: 2026-05-09 10:25:55 JST

## 目的

Phase 2 の次バッチとして、`SkContourMeasure` / `SkContourMeasureIter` / `SkPathMeasure` 周辺を fail-safe に寄せる。measure 系は output pointer と iterator 終端の null `sk_sp<SkContourMeasure>` が主なリスクなので、NULL 入力時の戻り規約と handle 0 規約を明文化する。

対象:

- `skia/capi/sk_contour_measure.h`
- `skia/capi/sk_contour_measure.cpp`
- `skia/capi/sk_contour_measure_iter.h`
- `skia/capi/sk_contour_measure_iter.cpp`
- `skia/capi/sk_path_measure.h`
- `skia/capi/sk_path_measure.cpp`

## 実装変更

各 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / 終端時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_contour_measure_t`) | `0` |
| length / numeric | `0` |
| `bool` query / operation | `false` |
| ref-count mutation / reset | no-op |

主な対象:

- `SkContourMeasure` query / output APIs / refcount
- `SkContourMeasureIter_newWithPath` / `reset` / `next`
- `SkPathMeasure` constructor / setPath / query / output APIs

## raw buffer / typed pointer 規約

ヘッダコメントを補強した。

- `SkContourMeasure_getPosTan`: `position` / `tangent` は非 NULL。
- `SkContourMeasure_getMatrix`: `matrix` は非 NULL。
- `SkContourMeasure_getSegment`: `dst` は非 NULL。
- `SkContourMeasureIter_newWithPath`: `path` は非 NULL。NULL 入力では `NULL`。
- `SkContourMeasureIter_next`: iterator 終端または NULL 入力では handle `0`。
- `SkPathMeasure_newWithPathForceClosedAndResScale`: `path == NULL` では空の `SkPathMeasure` を返す。
- `SkPathMeasure_setPath`: `path == NULL` は upstream 同様 reset。`path_measure == NULL` では no-op。
- `SkPathMeasure_getPosTan` / `getMatrix` / `getSegment`: output pointer は非 NULL。

## smoke test

`test_contour_path_measure_invalid_input_smoke` を追加し、`ctest` に `c_skia_contour_path_measure_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkContourMeasure` query/output/refcount がクラッシュせず fail-safe 値または no-op になる。
- NULL `SkContourMeasureIter` / NULL path が fail-safe 値または no-op になる。
- NULL path 付き `SkPathMeasure` が空 measure として生成される。
- NULL `SkPathMeasure` query/output が fail-safe 値を返す。
- 直線 path から contour/path measure を作成し、長さ 10 を取得できる。
- iterator 終端が handle `0` を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_contour_path_measure_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_contour_path_measure_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_contour_path_measure_invalid_input_smoke` build 成功。
- `c_skia_contour_path_measure_invalid_input_smoke` 成功。
- C API invalid-input smoke 18 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_contour_measure.h`
- `skia/capi/sk_contour_measure.cpp`
- `skia/capi/sk_contour_measure_iter.h`
- `skia/capi/sk_contour_measure_iter.cpp`
- `skia/capi/sk_path_measure.h`
- `skia/capi/sk_path_measure.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDataTable` / small table helpers
- `SkDrawable` / flattenable 周辺
