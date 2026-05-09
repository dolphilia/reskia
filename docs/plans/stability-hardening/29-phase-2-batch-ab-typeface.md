# 29 Phase 2 Batch AB: typeface C API safety

作業開始日時: 2026-05-09 17:30:21 JST

## 目的

Phase 2 の次バッチとして、`SkTypeface` 周辺を fail-safe に寄せる。`SkTypeface` は nullable `sk_sp` factory、stream/data handle、raw text/glyph buffer、output pointer を横断するため、C ABI 境界で NULL 入力・生成不能・count 不整合を明示する。

対象:

- `skia/capi/sk_typeface.h`
- `skia/capi/sk_typeface.cpp`

## 実装変更

各 C API に NULL ガード、raw buffer/count チェック、nullable handle factory helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_typeface_t`, `sk_data_t`, `sk_stream_asset_t`, `sk_rect_t`, `sk_font_style_t`) | `0` |
| borrowed / raw pointer | `NULL` |
| count / scalar / id | `0` |
| variation query error | `-1` |
| `bool` query | `false` |
| mutation / serialize-to-stream / output writer | no-op |

nullable `sk_sp` / `unique_ptr` を handle table に登録しない helper を追加し、生成不能時は handle `0` に統一した。

## raw buffer / output pointer 規約

ヘッダコメントを補強した。

- `SkTypeface_getVariationDesignPosition` / `SkTypeface_getVariationDesignParameters`: output pointer は NULL 許可。negative count や NULL typeface では `-1`。
- `SkTypeface_textToGlyphs`: `byteLength > 0` では `text` は非 NULL。`glyphs` は NULL 許可。`maxGlyphCount < 0` は invalid。
- `SkTypeface_unicharsToGlyphs`: `count > 0` では `uni` / `glyphs` は count 要素以上、非 NULL。
- `SkTypeface_getTableTags`: `tags` は NULL 許可。
- `SkTypeface_getTableData`: `length > 0` では `data` は非 NULL。
- `SkTypeface_getKerningPairAdjustments`: `count == 0` では `glyphs` / `adjustments` NULL 許可。`count > 0` では両方非 NULL。
- `SkTypeface_getFamilyName` / `SkTypeface_getPostScriptName`: output string は非 NULL。
- `SkTypeface_openStream` / `SkTypeface_openExistingStream`: `ttcIndex` は NULL 許可。
- `SkTypeface_getFontDescriptor`: `desc` / `isLocal` は非 NULL。

## smoke test

`test_typeface_invalid_input_smoke` を追加し、`ctest` に `c_skia_typeface_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkTypeface` query/output/factory APIs がクラッシュせず fail-safe 値または no-op になる。
- invalid static factory 入力が handle `0` を返す。
- valid empty typeface の `uniqueID`、`fontStyle`、text-to-glyph count-only、bounds handle を確認する。
- invalid behavior、NULL text with nonzero byte length、NULL output pointer が fail-safe に処理される。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_typeface_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_typeface_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_typeface_invalid_input_smoke` build 成功。
- `c_skia_typeface_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_typeface.h`
- `skia/capi/sk_typeface.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFontArguments` / `SkFontMetrics`
- `SkDrawable` / flattenable 周辺
- `SkFontMgr` / font family enumeration 周辺
- `SkTypeface_Mac` の Apple 限定 C API
