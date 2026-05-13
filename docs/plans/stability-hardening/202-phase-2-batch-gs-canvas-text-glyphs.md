# 202 Phase 2 Batch GS: canvas text glyph rules

開始時刻: 2026-05-13 11:07:53 JST

## 目的

`201-phase-2-batch-gr-canvas-image-draw.md` の「次バッチ候補」から、`SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約を再確認する。void draw API は invalid input で no-op とし、byte/count が実データを要求する場合だけ raw buffer を required にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawSimpleText` が `byteLength == 0` no-op、`byteLength > 0` で text / valid encoding / font / paint を required とすることを確認した。
  - `SkCanvas_drawString` / `SkCanvas_drawStringObject` が string / font / paint NULL を no-op にすることを確認した。
  - `SkCanvas_drawGlyphs*` が `count <= 0` no-op、`count > 0` で glyph buffer、position/xform buffer、origin handle、font、paint を検証することを確認した。
  - `SkCanvas_drawTextBlob` / `SkCanvas_drawTextBlobPtr` が text blob handle / borrowed pointer と paint を required とすることを確認した。
- `skia/capi/sk_canvas.h`
  - 対象 API の text buffer、encoding、count、font / paint required、invalid no-op コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、empty input no-op、NULL required pointer、invalid encoding / origin handle、有効入力の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `206-phase-2-batch-gw-canvas-annotation-data.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約をまとめて再確認する。
- `SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約をまとめて再確認する。
- `SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約をまとめて再確認する。
