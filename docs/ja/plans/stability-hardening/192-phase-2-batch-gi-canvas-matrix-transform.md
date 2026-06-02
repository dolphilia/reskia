# 192 Phase 2 Batch GI: canvas matrix transform rules

開始時刻: 2026-05-13 10:14:37 JST

## 目的

`191-phase-2-batch-gh-canvas-save-layer.md` の「次バッチ候補」から、`SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約を再確認する。void mutation は invalid input で no-op とし、matrix pointer は Skia が NULL を許容しないものを required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_concat` / `SkCanvas_concatMatrix` / `SkCanvas_setMatrix` / `SkCanvas_setMatrix3x3` が canvas または matrix NULL で no-op になることを確認した。
  - `SkCanvas_translate` / `SkCanvas_scale` / `SkCanvas_rotate` / `SkCanvas_rotateAround` / `SkCanvas_skew` が NULL canvas で no-op になることを確認した。
- `skia/capi/sk_canvas.h`
  - matrix pointer required と invalid input no-op のコメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas no-op、NULL matrix no-op、有効 matrix での concat / setMatrix smoke が揃っていることを確認した。

## 検証

- この batch の検証は `196-phase-2-batch-gm-canvas-color-rules.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver 0 規約をまとめて再確認する。
- `SkCanvas` draw point / line / circle 系の geometry と paint required 規約をまとめて再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約をまとめて再確認する。
