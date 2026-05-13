# 189 Phase 2 Batch GF: canvas clip bounds out param rules

開始時刻: 2026-05-13 10:09:04 JST

## 目的

`188-phase-2-batch-ge-image-color-space-ownership.md` の「次バッチ候補」から、`SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約を再確認する。handle getter は成功時 caller-owned、out-param API は out pointer 必須とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_getBaseProps` / `SkCanvas_getTopProps` / `SkCanvas_imageInfo` / `SkCanvas_getDeviceClipBounds` が NULL canvas で `0` を返すことを確認した。
  - `SkCanvas_getLocalClipBounds` は canvas / bounds いずれか NULL で false を返すことを確認した。
- `skia/capi/sk_canvas.h`
  - clip bounds handle getter は caller-owned handle と NULL canvas `0`、local clip bounds は `bounds` non-null と invalid input false を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL out param、valid handle getter、valid local clip bounds の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `191-phase-2-batch-gh-canvas-save-layer.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約をまとめて再確認する。
- `SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約をまとめて再確認する。
- `SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver 0 規約をまとめて再確認する。
- `SkCanvas` draw point / line / circle 系の geometry と paint required 規約をまとめて再確認する。
