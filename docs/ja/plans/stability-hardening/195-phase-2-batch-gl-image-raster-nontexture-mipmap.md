# 195 Phase 2 Batch GL: image raster nontexture mipmap rules

開始時刻: 2026-05-13 10:14:37 JST

## 目的

`194-phase-2-batch-gk-canvas-point-line-circle.md` の「次バッチ候補」から、`SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure `0` 規約を再確認する。成功時の returned handle は caller-owned、NULL image または factory failure は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_withDefaultMipmaps` / `SkImage_makeNonTextureImage` が NULL image `0` を返し、factory failure も `0` に正規化されることを確認した。
  - `SkImage_makeRasterImage` / `SkImage_makeRasterImageWithoutContext` が NULL image または invalid cachingHint で `0` を返すことを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_makeNonTextureImage` に returned handle は caller-owned であることを明記した。
  - `withDefaultMipmaps` / `makeRasterImage` / `makeRasterImageWithoutContext` は既に caller-owned、failure `0`、cachingHint validation を明記済みであることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、invalid cachingHint、有効入力時に非 `0` の場合は handle 実体が取得でき caller が delete する smoke が揃っていることを確認した。

## 検証

- この batch の検証は `196-phase-2-batch-gm-canvas-color-rules.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約をまとめて再確認する。
- `SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約をまとめて再確認する。
- `SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約をまとめて再確認する。
- `SkImage` refEncodedData / encode 系の nullable encoded data handle 規約をまとめて再確認する。
