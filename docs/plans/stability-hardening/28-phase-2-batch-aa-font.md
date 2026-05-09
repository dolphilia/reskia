# 28 Phase 2 Batch AA: font C API safety

作業開始日時: 2026-05-09 15:57:43 JST

## 目的

Phase 2 の次バッチとして、`SkFont` 周辺を fail-safe に寄せる。`SkFont` は text / glyph / width / bounds / position の raw pointer と count を多く受け取るため、NULL 入力、count 不整合、borrowed pointer、nullable handle の規約を C ABI 境界で明示する。

対象:

- `skia/capi/sk_font.h`
- `skia/capi/sk_font.cpp`

## 実装変更

各 C API に NULL ガード、raw array/count チェック、nullable typeface handle helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| borrowed pointer | `NULL` |
| handle (`sk_font_t`, `sk_typeface_t`, vector handle) | `0` |
| count / scalar query | `0` |
| enum query | `-1` |
| `bool` query | `false` |
| mutation / delete / dump | no-op |

`SkFont_refTypeface` は未設定 typeface や NULL font の場合に null `sk_sp<SkTypeface>` を handle table に登録せず、handle `0` を返す。

## raw array / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkFont_getTypeface`: borrowed pointer。caller は解放しない。NULL font や未設定 typeface では `NULL`。
- `SkFont_textToGlyphs` / `SkFont_countText` / `SkFont_measureText`: `byteLength > 0` では `text` は非 NULL。invalid 入力では `0`。
- `SkFont_textToGlyphs`: `glyphs` は NULL 許可。`maxGlyphCount < 0` は invalid。
- `SkFont_unicharsToGlyphs`: `count > 0` では `uni` / `glyphs` は count 要素以上、非 NULL。
- `SkFont_getWidths` / `SkFont_getWidthsBounds`: `count > 0` では `glyphs` は count 要素以上、非 NULL。`widths` / `bounds` は NULL 許可。
- `SkFont_getWidthsWithoutBounds`: `count > 0` では `glyphs` / `widths` は count 要素以上、非 NULL。
- `SkFont_getBounds`: `count > 0` では `glyphs` / `bounds` は count 要素以上、非 NULL。
- `SkFont_getPos` / `SkFont_getXPos`: `count > 0` では glyph input と output array は count 要素以上、非 NULL。
- `SkFont_getIntercepts`: invalid 入力または空結果では vector handle `0`。
- `SkFont_getPath`: `path` は非 NULL。invalid 入力では `false`。

## smoke test

`test_font_invalid_input_smoke` を追加し、`ctest` に `c_skia_font_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkFont` query/mutation/text/glyph APIs がクラッシュせず fail-safe 値または no-op になる。
- valid default `SkFont` の基本 query、`setSize`、`makeWithSize`、text count、glyph count-only 変換、measure を確認する。
- zero-count glyph APIs が no-op として扱われる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_font_invalid_input_smoke` build 成功。
- `c_skia_font_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_font.h`
- `skia/capi/sk_font.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkTypeface`
- `SkFontArguments` / `SkFontMetrics`
- `SkDrawable` / flattenable 周辺
- `SkFontMgr` / font family enumeration 周辺
