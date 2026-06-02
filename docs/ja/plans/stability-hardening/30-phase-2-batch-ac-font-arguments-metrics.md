# 30 Phase 2 Batch AC: font arguments / metrics C API safety

作業開始日時: 2026-05-09 22:34:05 JST

## 目的

Phase 2 の次バッチとして、`SkFontArguments` / `SkFontMetrics` 周辺を fail-safe に寄せる。どちらも小さな value/object wrapper だが、setter が handle を返し、metrics helper が output pointer へ書き込むため、NULL 入力・invalid output pointer の規約を C ABI 境界で明示する。

対象:

- `skia/capi/sk_font_arguments.h`
- `skia/capi/sk_font_arguments.cpp`
- `skia/capi/sk_font_metrics.h`
- `skia/capi/sk_font_metrics.cpp`

## 実装変更

各 C API に NULL ガードと最小限の値チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_font_arguments_t`, variation position, palette) | `0` |
| collection index | `0` |
| `bool` query | `false` |
| delete | no-op |

`SkFontArguments_setCollectionIndex` は negative index を invalid として handle `0` を返す。variation position / palette の invalid handle は既存 handle table の default entity 規約に合わせ、default position / palette として扱う。

## output pointer 規約

ヘッダコメントを補強した。

- `SkFontArguments_delete`: NULL 入力では no-op。
- `SkFontArguments_setCollectionIndex`: `collectionIndex >= 0`。invalid 入力では `0`。
- `SkFontArguments_getCollectionIndex`: NULL 入力では `0`。
- `SkFontArguments_getVariationDesignPosition` / `SkFontArguments_getPalette`: NULL 入力では `0`。
- `SkFontMetrics_hasUnderlineThickness` / `hasUnderlinePosition` / `hasStrikeoutThickness` / `hasStrikeoutPosition`: output pointer は非 NULL。invalid 入力では `false`。
- `SkFontMetrics_hasBounds`: NULL 入力では `false`。

## smoke test

`test_font_arguments_metrics_invalid_input_smoke` を追加し、`ctest` に `c_skia_font_arguments_metrics_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkFontArguments` setter/getter が handle `0` / `0` を返す。
- negative collection index が handle `0` になる。
- valid `SkFontArguments` から arguments / variation position / palette handle を取得できる。
- NULL `SkFontMetrics` と NULL output pointer が `false` になる。
- valid `SkFontMetrics` の underline / strikeout / bounds query が期待値を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_arguments_metrics_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_arguments_metrics_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_font_arguments_metrics_invalid_input_smoke` build 成功。
- `c_skia_font_arguments_metrics_invalid_input_smoke` 成功。
- test build 時に Skia private header 由来の C++17 inline variable 警告が出たが、リンクと実行は成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_font_arguments.h`
- `skia/capi/sk_font_arguments.cpp`
- `skia/capi/sk_font_metrics.h`
- `skia/capi/sk_font_metrics.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkDrawable` / flattenable 周辺
- `SkFontMgr` / font family enumeration 周辺
- `SkTypeface_Mac` の Apple 限定 C API
