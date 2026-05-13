# 198 Phase 2 Batch GO: image texture context getter rules

開始時刻: 2026-05-13 10:18:40 JST

## 目的

`197-phase-2-batch-gn-canvas-rect-rrect-oval-arc.md` の「次バッチ候補」から、`SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約を再確認する。NULL image は false / `0`、context は Skia が NULL を許容する API では optional とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_isTextureBacked` が NULL image false を返すことを確認した。
  - `SkImage_textureSize` が NULL image `0` を返すことを確認した。
  - `SkImage_isValid` が NULL image false を返し、context NULL を Skia API に渡せる optional 入力として扱うことを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_isValid` コメントを `context may be NULL` と `Invalid input returns false` に揃えた。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、raster image の texture backed false、texture size `0`、NULL context で valid の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `201-phase-2-batch-gr-canvas-image-draw.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約をまとめて再確認する。
- `SkImage` refEncodedData / encode 系の nullable encoded data handle 規約をまとめて再確認する。
- `SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約をまとめて再確認する。
- `SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約をまとめて再確認する。
