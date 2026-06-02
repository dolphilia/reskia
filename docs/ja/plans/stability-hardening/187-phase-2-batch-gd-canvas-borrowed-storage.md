# 187 Phase 2 Batch GD: canvas borrowed storage rules

開始時刻: 2026-05-13 10:09:04 JST

## 目的

`186-phase-2-batch-gc-image-dimensions-bounds-info.md` の「次バッチ候補」から、`SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約を再確認する。返却される raw pointer / pixmap は canvas 側 storage を借用し、caller が解放しない。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_accessTopLayerPixels` が borrowed raw pixels、NULL canvas / unavailable storage は NULL、`info` / `rowBytes` / `origin` は optional out param、返却 pointer は storage が変わるまで有効と明記済みであることを確認した。
  - `SkCanvas_peekPixels` が non-null pixmap out param、返却 pixmap は canvas pixels を借用し storage 変更まで有効、invalid input は false と明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、optional out params NULL、borrowed storage 成功、`peekPixels` NULL pixmap / 成功の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `191-phase-2-batch-gh-canvas-save-layer.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約をまとめて再確認する。
- `SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約をまとめて再確認する。
- `SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約をまとめて再確認する。
- `SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約をまとめて再確認する。
