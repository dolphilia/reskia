# 205 Phase 2 Batch GV: image subset color factory rules

開始時刻: 2026-05-13 11:07:53 JST

## 目的

`204-phase-2-batch-gu-canvas-picture-drawable.md` の「次バッチ候補」から、`SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約を再確認する。returned image handle は caller-owned、invalid input / factory failure は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_makeSubset` が image / subset required、direct context optional であることを確認した。
  - recorder 系 factory が image / recorder required、properties handle validation を行うことを確認した。
  - color space handle は `0` を null color space として許容し、非 `0` は valid handle を要求することを確認した。
  - color type factory が targetColorType enum を検証することを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_makeColorSpace` のコメントからこの overload には存在しない properties 記述を削除した。
  - `SkImage_makeColorTypeAndColorSpace` に direct may be NULL を明記した。
  - subset / recorder / properties / returned handle / failure `0` コメントが揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、NULL subset、invalid subset factory failure、invalid properties、invalid color space handle、invalid color type、有効 returned handle の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `206-phase-2-batch-gw-canvas-annotation-data.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約をまとめて再確認する。
- `SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約をまとめて再確認する。
- `SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約をまとめて再確認する。
