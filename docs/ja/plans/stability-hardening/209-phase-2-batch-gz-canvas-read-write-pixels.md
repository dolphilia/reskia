# 209 Phase 2 Batch GZ: canvas read write pixels rules

開始時刻: 2026-05-13 11:21:28 JST

## 目的

`208-phase-2-batch-gy-image-read-scale-pixels.md` の「次バッチ候補」から、`SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約を再確認する。canvas pixel I/O は invalid input で false を返し、caller-owned storage は保持しない。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - bitmap overload が canvas / bitmap NULL を false にすることを確認した。
  - image info + raw storage overload が info / pixels / rowBytes をまとめて検証することを確認した。
  - pixmap overload が pixmap NULL を false にすることを確認した。
- `skia/capi/sk_canvas.h`
  - read / write raw storage が caller-owned buffer を保持しないこと、rowBytes validation、invalid false を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL bitmap/info/pixels/pixmap、empty bitmap/pixmap、invalid rowBytes、有効 borrowed top-layer storage smoke が揃っていることを確認した。

## 検証

- この batch の検証は `211-phase-2-batch-hb-canvas-state-getters.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約をまとめて再確認する。
- `SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約をまとめて再確認する。
- `SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約をまとめて再確認する。
- `SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver 0 規約をまとめて再確認する。
