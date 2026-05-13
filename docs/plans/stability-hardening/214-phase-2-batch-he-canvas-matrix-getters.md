# 214 Phase 2 Batch HE: canvas matrix getter rules

開始時刻: 2026-05-13 11:26:58 JST

## 目的

`213-phase-2-batch-hd-image-texture-backend-context.md` の「次バッチ候補」から、`SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver `0` 規約を再確認する。matrix handle getter は成功時 caller-owned、NULL canvas は `0` とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_getLocalToDevice` / `SkCanvas_getLocalToDeviceAs3x3` / `SkCanvas_getTotalMatrix` が NULL canvas `0` を返し、成功時 static handle を返すことを確認した。
- `skia/capi/sk_canvas.h`
  - 対象 API が caller-owned matrix handle と NULL canvas `0` を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas `0` と valid canvas returned handle の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `216-phase-2-batch-hg-canvas-raster-factory.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約をまとめて再確認する。
- `SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約をまとめて再確認する。
- `SkCanvas` getBaseLayerSize / getDeviceClipBounds / getLocalClipBounds 系の caller-owned handle と out-param validation 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo / colorSpace 系 getter の caller-owned / borrowed ownership 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約を再確認する。
