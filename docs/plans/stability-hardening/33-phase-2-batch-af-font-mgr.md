# 33 Phase 2 Batch AF: font manager C API safety

作業開始日時: 2026-05-10 00:27:03 JST

## 目的

Phase 2 の次バッチとして、`SkFontMgr` / font family enumeration 周辺を fail-safe に寄せる。`SkFontMgr` は family index、style set out pointer、nullable typeface factory、stream/data/file 入力を横断するため、NULL 入力・範囲外 index・生成不能を C ABI 境界で明示する。

対象:

- `skia/capi/sk_font_mgr.h`
- `skia/capi/sk_font_mgr.cpp`
- `skia/capi/sk_font_mgr_fontconfig.h`
- `skia/capi/sk_font_mgr_fontconfig.cpp`

## 実装変更

各 C API に NULL ガード、family index 範囲チェック、nullable handle helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_font_mgr_t`, `sk_font_style_set_t`, `sk_typeface_t`) | `0` |
| family count | `0` |
| status + out pointer | out `0` + `RESKIA_STATUS_INVALID_ARGUMENT` / `RESKIA_STATUS_NOT_FOUND` |
| `bool` query | `false` |
| getFamilyName / ref-count mutation | no-op |

nullable `sk_sp` は handle table に登録せず、C ABI では handle `0` として返す。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `SkFontMgr_getFamilyName`: index は `0 <= index < countFamilies()`、familyName は非 NULL。invalid 入力では no-op。
- `SkFontMgr_createStyleSet`: index 範囲内、out pointer 非 NULL。invalid 入力では out `0` + `INVALID_ARGUMENT`。
- `SkFontMgr_matchFamily`: familyName は NULL 許可、out pointer 非 NULL。生成不能では out `0` + `NOT_FOUND`。
- `SkFontMgr_matchFamilyStyle`: familyName は NULL 許可、font_style は非 NULL。
- `SkFontMgr_matchFamilyStyleCharacter`: `bcp47Count > 0` では `bcp47` は非 NULL。
- `makeFromData`: data handle 非 0、ttcIndex >= 0。
- `makeFromStream`: stream handle は consumed、ttcIndex >= 0。
- `makeFromStreamWithArguments`: stream handle は consumed、font arguments は非 NULL。
- `makeFromFile`: path は非 NULL、ttcIndex >= 0。
- `legacyMakeTypeface`: familyName は NULL 許可。
- `CSkia_SkFontMgr_New_FontConfig`: `FcConfig*` は NULL 許可。生成不能では `0`。

## smoke test

`test_font_mgr_invalid_input_smoke` を追加し、`ctest` に `c_skia_font_mgr_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkFontMgr` query/refcount/out-pointer APIs が fail-safe 値または no-op になる。
- out pointer API は invalid 入力時に out を `0` に戻す。
- empty font manager の family count、範囲外 index、nullable typeface factories が fail-safe になる。
- `RefEmpty` が有効な font manager handle を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_font_mgr_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_font_mgr_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_font_mgr_invalid_input_smoke` build 成功。
- `c_skia_font_mgr_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_font_mgr.h`
- `skia/capi/sk_font_mgr.cpp`
- `skia/capi/sk_font_mgr_fontconfig.h`
- `skia/capi/sk_font_mgr_fontconfig.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkTypeface_Mac` の Apple 限定 C API
- `SkOverdrawCanvas` / drawable callback 周辺
- `SkReadBuffer` / `SkWriteBuffer` の flattenable factory 周辺
