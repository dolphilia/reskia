# 213 Phase 2 Batch HD: image texture backend context rules

開始時刻: 2026-05-13 11:26:58 JST

## 目的

`212-phase-2-batch-hc-canvas-surface-context-getters.md` の「次バッチ候補」から、`SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約を再確認する。現状の `sk_image` C API では backend texture / Graphite / Ganesh 専用 getter は公開されていないため、公開済みの texture/context getter を対象にする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_isTextureBacked` が NULL image false を返すことを確認した。
  - `SkImage_textureSize` が NULL image `0` を返すことを確認した。
  - `SkImage_isValid` が NULL image false、context NULL optional として扱われることを確認した。
- `skia/capi/sk_image.h`
  - 対象 API の NULL / invalid return と context optional コメントが揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、raster image、NULL context の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `216-phase-2-batch-hg-canvas-raster-factory.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver 0 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約をまとめて再確認する。
- `SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約をまとめて再確認する。
- `SkCanvas` getBaseLayerSize / getDeviceClipBounds / getLocalClipBounds 系の caller-owned handle と out-param validation 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo / colorSpace 系 getter の caller-owned / borrowed ownership 規約をまとめて再確認する。
