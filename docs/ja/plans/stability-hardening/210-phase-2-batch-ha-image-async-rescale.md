# 210 Phase 2 Batch HA: image async rescale rules

開始時刻: 2026-05-13 11:21:28 JST

## 目的

`209-phase-2-batch-gz-canvas-read-write-pixels.md` の「次バッチ候補」から、`SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約を再確認する。callback API は invalid input で callback があれば NULL result を渡し、callback NULL は no-op とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_asyncRescaleAndReadPixels` が image / info / srcRect / callback / rescale enum を検証することを確認した。
  - YUV420 / YUVA420 系が image / srcRect / dstSize handle / callback / yuvColorSpace / rescale enum を検証することを確認した。
  - invalid input は `reskia_async_read_pixels_fail` 経由で callback がある場合だけ NULL result callback になることを確認した。
- `skia/capi/sk_image.h`
  - YUVA420 overload に NULL callback no-op を明記した。
  - callback failure、context optional、dstSize handle、enum validation コメントが揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image/info/srcRect/callback、NULL context、invalid dstSize、invalid yuvColorSpace / rescale enum の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `211-phase-2-batch-hb-canvas-state-getters.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約をまとめて再確認する。
- `SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約をまとめて再確認する。
- `SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver 0 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約をまとめて再確認する。
