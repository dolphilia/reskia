# 190 Phase 2 Batch GG: image bool getter rules

開始時刻: 2026-05-13 10:09:04 JST

## 目的

`189-phase-2-batch-gf-canvas-clip-bounds-out-param.md` の「次バッチ候補」から、`SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約を再確認する。bool getter は NULL receiver で false を返し、有効 receiver では Skia の状態をそのまま返す。

## 変更内容

- `skia/capi/sk_image.h`
  - `SkImage_isAlphaOnly` / `SkImage_isOpaque` / `SkImage_isProtected` を複数行コメントに整え、NULL image false と Skia 署名を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - raster premul image に対して `SkImage_isAlphaOnly` / `SkImage_isOpaque` が false を返す smoke を追加した。
  - raster image に対して `SkImage_isProtected` が false を返す smoke を追加した。
- `skia/capi/sk_image.cpp`
  - 実装は既に NULL image false を返しており、変更不要だった。

## 検証

- この batch の検証は `191-phase-2-batch-gh-canvas-save-layer.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約をまとめて再確認する。
- `SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約をまとめて再確認する。
- `SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver 0 規約をまとめて再確認する。
- `SkCanvas` draw point / line / circle 系の geometry と paint required 規約をまとめて再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure 0 規約をまとめて再確認する。
