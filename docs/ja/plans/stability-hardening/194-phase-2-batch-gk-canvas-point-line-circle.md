# 194 Phase 2 Batch GK: canvas point line circle rules

開始時刻: 2026-05-13 10:14:37 JST

## 目的

`193-phase-2-batch-gj-image-numeric-enum-getters.md` の「次バッチ候補」から、`SkCanvas` draw point / line / circle 系の geometry と paint required 規約を再確認する。void draw API は invalid input で no-op とし、handle geometry は valid handle、paint は required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawPoint` / `SkCanvas_drawLine` / `SkCanvas_drawCircle` が point handle と paint を検証していることを確認した。
  - `SkCanvas_drawPointXY` / `SkCanvas_drawLineXY` / `SkCanvas_drawCircleAt` が paint NULL を no-op にすることを確認した。
  - `SkCanvas_drawPoints` が PointMode enum、count と pts、paint を検証していることを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawLineXY` の Skia 署名コメントに `y1` を明記した。
  - point / line / circle / drawPoints の required 入力と invalid no-op コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、invalid point handle、NULL paint、invalid PointMode、count と pts の不整合、有効入力の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `196-phase-2-batch-gm-canvas-color-rules.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約をまとめて再確認する。
- `SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約をまとめて再確認する。
- `SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約をまとめて再確認する。
