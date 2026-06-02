# 203 Phase 2 Batch GT: image shader factory rules

開始時刻: 2026-05-13 11:07:53 JST

## 目的

`202-phase-2-batch-gs-canvas-text-glyphs.md` の「次バッチ候補」から、`SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約を再確認する。shader handle は成功時 caller-owned、invalid input / factory failure は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_makeShader` / `SkImage_makeRawShader` が image / sampling required、tile mode validation、localMatrix optional であることを確認した。
  - `WithTileModesAndLocalMatrix` / `WithSamplingAndLocalMatrix` 系が matrix required で、NULL matrix `0` を返すことを確認した。
  - `WithSampling` 系が sampling required、localMatrix optional であることを確認した。
- `skia/capi/sk_image.h`
  - 対象 API の required / optional matrix、tile mode validation、caller-owned shader handle、failure `0` コメントが揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、NULL sampling、invalid tile mode、required matrix NULL、localMatrix optional 成功、caller-owned shader handle delete の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `206-phase-2-batch-gw-canvas-annotation-data.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約をまとめて再確認する。
- `SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約をまとめて再確認する。
- `SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約をまとめて再確認する。
