# 34 Phase 2 Batch AG: typeface Mac C API safety

作業開始日時: 2026-05-10 00:33:38 JST

## 目的

Phase 2 の次バッチとして、`SkTypeface_Mac` の Apple 限定 C API を fail-safe に寄せる。CoreText bridge は platform object pointer と nullable `sk_sp<SkTypeface>` を扱うため、NULL 入力・生成不能・borrowed pointer 規約を C ABI 境界で明示する。

対象:

- `skia/capi/sk_typeface_mac.h`
- `skia/capi/sk_typeface_mac.cpp`

## 実装変更

NULL `CTFontRef` / NULL `SkTypeface` guard と nullable handle helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_typeface_t`) | `0` |
| borrowed `CTFontRef` pointer | `NULL` |

`Mac_SkMakeTypefaceFromCTFont` は null `sk_sp<SkTypeface>` を handle table に登録せず、C ABI では handle `0` として返す。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `Mac_SkMakeTypefaceFromCTFont`: `fontRef` は非 NULL。生成不能では `0`。
- `Mac_SkTypeface_GetCTFontRef`: `face` は非 NULL。戻り値は borrowed pointer。NULL face や CTFontRef なしでは `NULL`。

## smoke test

Apple 限定で `test_typeface_mac_invalid_input_smoke` を追加し、`ctest` に `c_skia_typeface_mac_invalid_input_smoke` として登録した。

確認内容:

- NULL `CTFontRef` が handle `0` になる。
- NULL typeface からの CTFontRef 取得が `NULL` になる。
- default typeface から borrowed CTFontRef を取得できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_typeface_mac_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_typeface_mac_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_typeface_mac_invalid_input_smoke` build 成功。
- `c_skia_typeface_mac_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_typeface_mac.h`
- `skia/capi/sk_typeface_mac.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkOverdrawCanvas` / drawable callback 周辺
- `SkReadBuffer` / `SkWriteBuffer` の flattenable factory 周辺
- `SkTextBlob` / glyph-buffer 周辺
