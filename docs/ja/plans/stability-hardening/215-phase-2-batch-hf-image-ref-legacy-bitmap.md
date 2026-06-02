# 215 Phase 2 Batch HF: image ref legacy bitmap rules

開始時刻: 2026-05-13 11:26:58 JST

## 目的

`214-phase-2-batch-he-canvas-matrix-getters.md` の「次バッチ候補」から、`SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約を再確認する。refcount 操作は NULL image no-op、bool getter は false、output pointer API は required pointer を検証する。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_ref` / `SkImage_unref` / `SkImage_release` が NULL image no-op であることを確認した。
  - `SkImage_unique` が NULL image false を返すことを確認した。
  - `SkImage_asLegacyBitmap` が image / bitmap required、legacyBitmapMode enum validation、invalid false であることを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_asLegacyBitmap` の bitmap が caller-owned output storage であることを明記した。
  - ref/unref/release/unique の NULL 規約が揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL ref/unref/release no-op、NULL image false、NULL bitmap、invalid legacyBitmapMode の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `216-phase-2-batch-hg-canvas-raster-factory.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約をまとめて再確認する。
- `SkCanvas` getBaseLayerSize / getDeviceClipBounds / getLocalClipBounds 系の caller-owned handle と out-param validation 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo / colorSpace 系 getter の caller-owned / borrowed ownership 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約を再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps 系の factory failure `0` と caller-owned handle 規約を再確認する。
