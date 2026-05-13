# 188 Phase 2 Batch GE: image color space ownership rules

開始時刻: 2026-05-13 10:09:04 JST

## 目的

`187-phase-2-batch-gd-canvas-borrowed-storage.md` の「次バッチ候補」から、`SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約を再確認する。`colorSpace` は borrowed pointer、`refColorSpace` は caller-owned retained handle とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_colorSpace` が NULL image または color space なしで NULL を返し、成功時に borrowed pointer を返すことを確認した。
  - `SkImage_refColorSpace` が NULL image または color space なしで `0` を返し、成功時に retained handle を返すことを確認した。
- `skia/capi/sk_image.h`
  - borrowed pointer は caller が解放しないこと、retained handle は `static_sk_color_space_delete` で削除することを明記済みであることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image、color space なし image、SRGB color space 付き image の borrowed / retained 両経路の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `191-phase-2-batch-gh-canvas-save-layer.md` にまとめて記録する。

## 次バッチ候補

- `SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約をまとめて再確認する。
- `SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約をまとめて再確認する。
- `SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約をまとめて再確認する。
- `SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver 0 規約をまとめて再確認する。
