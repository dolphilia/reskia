# 193 Phase 2 Batch GJ: image numeric enum getter rules

開始時刻: 2026-05-13 10:14:37 JST

## 目的

`192-phase-2-batch-gi-canvas-matrix-transform.md` の「次バッチ候補」から、`SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver `0` 規約を再確認する。numeric getter と enum getter は NULL image で `0` を返す。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_width` / `SkImage_height` / `SkImage_uniqueID` / `SkImage_alphaType` / `SkImage_colorType` が NULL image `0` を返すことを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_width` / `SkImage_height` の行末コメントを NULL image `0` 規約に更新した。
  - `uniqueID` / `alphaType` / `colorType` は既に NULL image `0` を明記済みであることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image getter smoke に加え、raster image で width / height / uniqueID / alphaType / colorType の有効入力 smoke を追加した。

## 検証

- この batch の検証は `196-phase-2-batch-gm-canvas-color-rules.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` draw point / line / circle 系の geometry と paint required 規約をまとめて再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約をまとめて再確認する。
- `SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約をまとめて再確認する。
