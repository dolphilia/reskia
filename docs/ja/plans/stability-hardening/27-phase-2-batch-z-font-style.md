# 27 Phase 2 Batch Z: font style C API safety

作業開始日時: 2026-05-09 15:09:02 JST

## 目的

Phase 2 の次バッチとして、`SkFontStyle` / `SkFontStyleSet` 周辺を fail-safe に寄せる。font style set は family/style enumeration と nullable `SkTypeface` 生成を扱うため、NULL 入力、範囲外 index、生成不能時 handle を C ABI 境界で明示する。

対象:

- `skia/capi/sk_font_style.h`
- `skia/capi/sk_font_style.cpp`
- `skia/capi/sk_font_style_set.h`
- `skia/capi/sk_font_style_set.cpp`

## 実装変更

各 C API に NULL ガード、index 範囲チェック、nullable `sk_sp` factory helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_typeface_t`, `sk_font_style_set_t`) | `0` |
| count / scalar query | `0` |
| `SkFontStyle::Slant` query | `-1` |
| `bool` query | `false` |
| delete / ref-count mutation | no-op |

static factory と typeface factory では null `sk_sp` を handle table に登録せず、C ABI では handle `0` として返す。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `SkFontStyle_delete`: NULL 入力では no-op。
- `SkFontStyle_weight` / `SkFontStyle_width`: NULL 入力では `0`。
- `SkFontStyle_slant`: NULL 入力では `-1`。
- `SkFontStyleSet_count`: NULL 入力では `0`。
- `SkFontStyleSet_getStyle`: `font_style_set` は非 NULL、`index` は `0 <= index < count`、`font_style` / `style` はどちらか非 NULL。invalid 入力では no-op。
- `SkFontStyleSet_createTypeface`: valid index でのみ upstream を呼び、invalid 入力や生成不能では handle `0`。
- `SkFontStyleSet_matchStyle`: `font_style_set` / `pattern` は非 NULL。NULL 入力や生成不能では handle `0`。
- `SkFontStyleSet_CreateEmpty`: 生成不能では handle `0`。

`getStyle` は片方の output pointer だけを渡された場合でも upstream 実装へ NULL を渡さないよう、内部 scratch object を使う。

## smoke test

`test_font_style_set_invalid_input_smoke` を追加し、`ctest` に `c_skia_font_style_set_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkFontStyle` query/delete がクラッシュせず fail-safe 値または no-op になる。
- valid default `SkFontStyle` の weight / width / slant を取得できる。
- NULL `SkFontStyleSet` query/refcount/getStyle/factory が fail-safe 値または no-op になる。
- empty `SkFontStyleSet` の count が `0` になり、範囲外 index や null pattern が handle `0` または no-op になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_style_set_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_style_set_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_font_style_set_invalid_input_smoke` build 成功。
- `c_skia_font_style_set_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_font_style.h`
- `skia/capi/sk_font_style.cpp`
- `skia/capi/sk_font_style_set.h`
- `skia/capi/sk_font_style_set.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkFontMgr` / font family enumeration 周辺
