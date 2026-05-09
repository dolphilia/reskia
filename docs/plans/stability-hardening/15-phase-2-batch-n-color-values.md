# 15 Phase 2 Batch N: color values C API safety

作業開始日時: 2026-05-09 09:51:43 JST

## 目的

Phase 2 の次バッチとして、直前の color filter factory から参照される `SkColor4f` / `SkColorMatrix` 周辺を fail-safe に寄せる。ここは値型 handle と raw array pointer が中心であり、NULL 入力時のクラッシュ回避と raw buffer 規約の明文化を優先する。

対象:

- `skia/capi/sk_color_4f.h`
- `skia/capi/sk_color_4f.cpp`
- `skia/capi/sk_color_matrix.h`
- `skia/capi/sk_color_matrix.cpp`

## 実装変更

`SkColor4f` query と `SkColorMatrix` mutation/output API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric/color | `0` |
| float component | `0.0f` |
| `bool` query | `false` |
| mutation / output write | no-op |

主な対象:

- `SkColor4f` component read
- `SkColor4f_vec` / `vecMutable`
- `SkColor4f_isOpaque` / `fitsInBytes`
- `SkColor4f_toSkColor` / `toBytes_RGBA` / `makeOpaque`
- `SkColorMatrix` mutation API
- `SkColorMatrix_setRowMajor` / `getRowMajor`

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkColor4f_vec`: borrowed raw array。4 要素。caller は解放しない。
- `SkColor4f_vecMutable`: borrowed mutable raw array。4 要素。caller は解放しない。
- `SkColorMatrix_setRowMajor`: `src` は 20 要素以上、非 NULL。
- `SkColorMatrix_getRowMajor`: `dst` は 20 要素以上、非 NULL。
- `SkColorMatrix_setConcat` / `preConcat` / `postConcat`: 入力 matrix pointer は非 NULL。

## smoke test

`test_color_values_invalid_input_smoke` を追加し、`ctest` に `c_skia_color_values_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkColor4f` query がクラッシュせず fail-safe 値を返す。
- NULL `SkColorMatrix` mutation/output が no-op になる。
- `SkColorMatrix` の row-major roundtrip が動作する。
- `SkColorMatrix_RGBtoYUV` が handle を返す。
- `SkColor4f_FromColor` / `makeOpaque` の正常系 handle を最小確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_color_values_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_color_values_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_color_values_invalid_input_smoke` build 成功。
- `c_skia_color_values_invalid_input_smoke` 成功。
- C API invalid-input smoke 15 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_color_4f.h`
- `skia/capi/sk_color_4f.cpp`
- `skia/capi/sk_color_matrix.h`
- `skia/capi/sk_color_matrix.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkContourMeasure` / path measure 周辺
- `SkColorMatrixFilter` / color matrix filter 周辺
