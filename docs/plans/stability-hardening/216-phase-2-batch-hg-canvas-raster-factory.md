# 216 Phase 2 Batch HG: canvas raster factory rules

開始時刻: 2026-05-13 11:26:58 JST

## 目的

`215-phase-2-batch-hf-image-ref-legacy-bitmap.md` の「次バッチ候補」から、`SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約を再確認する。caller-owned pixel storage を canvas が借用する場合は lifetime を明記し、invalid input / factory failure は NULL / `0` とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_newFromBitmap` が bitmap required、NULL bitmap で NULL を返すことを確認した。
  - `SkCanvas_newFromBitmapWithProps` が bitmap / props required、invalid input NULL であることを確認した。
  - `SkCanvas_MakeRasterDirect` が info / pixels / rowBytes を `validRowBytes` 相当で検証し、props optional、factory failure `0` であることを確認した。
  - `SkCanvas_MakeRasterDirectN32` が dimensions、pixels、rowBytes を検証し、factory failure `0` であることを確認した。
- `skia/capi/sk_canvas.h`
  - `newFromBitmap` / `newFromBitmapWithProps` に bitmap pixel storage must outlive returned canvas を明記した。
  - `MakeRasterDirect` / `MakeRasterDirectN32` は caller-owned backing store lifetime、rowBytes、props optional、failure `0` を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL bitmap、NULL info/pixels、invalid dimensions、invalid rowBytes、borrowed bitmap-backed canvas の smoke が揃っていることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch HG、`sk_image.cpp/h` を batch HF の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` getBaseLayerSize / getDeviceClipBounds / getLocalClipBounds 系の caller-owned handle と out-param validation 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo / colorSpace 系 getter の caller-owned / borrowed ownership 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約を再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps 系の factory failure `0` と caller-owned handle 規約を再確認する。
- `SkCanvas` drawImageRect / drawImageLattice / drawImageNine 系の optional paint、sampling required、enum validation 規約を再確認する。
