# 199 Phase 2 Batch GP: canvas clip geometry shader rules

開始時刻: 2026-05-13 10:18:40 JST

## 目的

`198-phase-2-batch-go-image-texture-context-getters.md` の「次バッチ候補」から、`SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約を再確認する。clip 系 void API は invalid input で no-op、geometry pointer は required、`SkClipOp` と shader handle は検証する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_clipRect` / `SkCanvas_clipRRect` / `SkCanvas_clipPath` が NULL geometry で no-op になることを確認した。
  - `SkCanvas_clipRectWithOp*` / `SkCanvas_clipRRectWithOp*` / `SkCanvas_clipPathWithOp*` が invalid `SkClipOp` を no-op にすることを確認した。
  - `SkCanvas_clipShader` が shader handle と `SkClipOp` を検証していることを確認した。
- `skia/capi/sk_canvas.h`
  - 対象 API の required pointer、valid enum / handle、invalid no-op コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL geometry、invalid op、invalid shader handle、有効 clip geometry / shader の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `201-phase-2-batch-gr-canvas-image-draw.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` refEncodedData / encode 系の nullable encoded data handle 規約をまとめて再確認する。
- `SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約をまとめて再確認する。
- `SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約をまとめて再確認する。
