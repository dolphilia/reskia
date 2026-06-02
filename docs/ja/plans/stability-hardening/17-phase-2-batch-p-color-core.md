# 17 Phase 2 Batch P: color core C API safety

作業開始日時: 2026-05-09 10:22:31 JST

## 目的

Phase 2 の次バッチとして、`SkColor` / `SkColorPriv` 周辺を fail-safe に寄せる。大半は値変換のみだが、HSV 変換 API は raw array pointer を受け取るため、NULL 入力時のクラッシュ回避と配列規約の明文化を行う。

対象:

- `skia/capi/sk_color.h`
- `skia/capi/sk_color.cpp`
- `skia/capi/sk_color_priv.h`
- `skia/capi/sk_color_priv.cpp`

## 実装変更

`SkColor` の HSV raw array API に NULL ガードを追加した。

戻り規約:

| API 種別 | NULL 入力時 |
| --- | --- |
| HSV output write | no-op |
| HSV input conversion | `0` |
| value-only helper | 入力値に従う |

対象:

- `SkColor_SkColorToHSV`
- `SkColor_SkRGBToHSV`
- `SkColor_SkHSVToColor`
- `SkColor_SkHSVToColorWithAlpha`

`SkColorPriv` は pointer 入力を持たない value-only helper としてレビューし、`U8CPU` channel 値の扱いをヘッダに明記した。

## raw buffer 規約

ヘッダコメントを補強した。

- `SkColor_SkColorToHSV`: `hsv` は 3 要素以上、非 NULL。NULL 入力では no-op。
- `SkColor_SkRGBToHSV`: `hsv` は 3 要素以上、非 NULL。NULL 入力では no-op。
- `SkColor_SkHSVToColor`: `hsv` は 3 要素以上、非 NULL。NULL 入力では `0`。
- `SkColor_SkHSVToColorWithAlpha`: `hsv` は 3 要素以上、非 NULL。NULL 入力では `0`。

## smoke test

`test_color_core_invalid_input_smoke` を追加し、`ctest` に `c_skia_color_core_invalid_input_smoke` として登録した。

確認内容:

- HSV output API が NULL で no-op になる。
- HSV input API が NULL で `0` を返す。
- HSV 変換の正常系 roundtrip を最小確認する。
- `SkColorSetA` / `SkColorSetARGB` / premultiply / `SkColorPriv` helper の正常系を最小確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_color_core_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_color_core_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_color_core_invalid_input_smoke` build 成功。
- `c_skia_color_core_invalid_input_smoke` 成功。
- C API invalid-input smoke 17 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_color.h`
- `skia/capi/sk_color.cpp`
- `skia/capi/sk_color_priv.h`
- `skia/capi/sk_color_priv.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkContourMeasure` / path measure 周辺
- `SkFont` / `SkTypeface`
- `SkDataTable` / small table helpers
