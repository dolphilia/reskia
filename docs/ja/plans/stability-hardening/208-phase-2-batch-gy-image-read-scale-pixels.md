# 208 Phase 2 Batch GY: image read scale pixels rules

開始時刻: 2026-05-13 11:21:28 JST

## 目的

`207-phase-2-batch-gx-canvas-atlas-patch-vertices-mesh.md` の「次バッチ候補」から、`SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約を再確認する。pixel storage は required、rowBytes は `validRowBytes` 相当を満たし、invalid input は false とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_readPixels` / `SkImage_readPixelsWithImageInfo` が image / dstInfo / dstPixels / dstRowBytes / cachingHint を検証することを確認した。
  - pixmap overload が image / dst pixmap / cachingHint を検証し、context NULL は optional として扱うことを確認した。
  - `SkImage_scalePixels` が image / dst pixmap / sampling / cachingHint を検証することを確認した。
- `skia/capi/sk_image.h`
  - pixmap read overload に dst writable storage を明記した。
  - storage、rowBytes、cachingHint、context optional、invalid false コメントが揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、NULL info/pixels/pixmap/sampling、invalid rowBytes、invalid cachingHint、有効 storage の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `211-phase-2-batch-hb-canvas-state-getters.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約をまとめて再確認する。
- `SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約をまとめて再確認する。
- `SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約をまとめて再確認する。
- `SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約をまとめて再確認する。
- `SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約をまとめて再確認する。
