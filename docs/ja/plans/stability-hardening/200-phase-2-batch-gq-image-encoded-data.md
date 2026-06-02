# 200 Phase 2 Batch GQ: image encoded data rules

開始時刻: 2026-05-13 10:18:40 JST

## 目的

`199-phase-2-batch-gp-canvas-clip-geometry-shader.md` の「次バッチ候補」から、`SkImage` refEncodedData / encode 系の nullable encoded data handle 規約を再確認する。現状の `sk_image` C API では encode API は公開されていないため、存在する `SkImage_refEncodedData` を対象にする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_refEncodedData` が NULL image で `0` を返し、Skia が encoded data なしを返した場合も `0` に正規化することを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_refEncodedData` が caller-owned retained data handle、削除方法、NULL image / no encoded data `0` を明記済みであることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image と raster snapshot image without encoded data で `0` を返す smoke が揃っていることを確認した。

## 検証

- この batch の検証は `201-phase-2-batch-gr-canvas-image-draw.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約をまとめて再確認する。
- `SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約をまとめて再確認する。
