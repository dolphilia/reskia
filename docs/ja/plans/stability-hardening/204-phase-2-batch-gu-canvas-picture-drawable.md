# 204 Phase 2 Batch GU: canvas picture drawable rules

開始時刻: 2026-05-13 11:07:53 JST

## 目的

`203-phase-2-batch-gt-image-shader-factories.md` の「次バッチ候補」から、`SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約を再確認する。picture handle は valid handle、raw pointer は borrowed non-null、matrix / paint は Skia overload が許容する場合 optional とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawPicture` / `SkCanvas_drawPictureHandleWithMatrixPaint` が invalid picture handle で no-op になることを確認した。
  - picture pointer overload が borrowed pointer NULL で no-op になり、matrix / paint NULL を許容することを確認した。
  - `SkCanvas_drawDrawable` が borrowed drawable pointer required、matrix optional であることを確認した。
  - `SkCanvas_drawDrawableAt` が borrowed drawable pointer required であることを確認した。
- `skia/capi/sk_canvas.h`
  - picture pointer の caller must not free、matrix / paint optional、drawable borrowed non-null コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、invalid handle、NULL borrowed pointer、optional matrix / paint NULL、有効 picture / drawable draw の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `206-phase-2-batch-gw-canvas-annotation-data.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約をまとめて再確認する。
- `SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約をまとめて再確認する。
- `SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約をまとめて再確認する。
