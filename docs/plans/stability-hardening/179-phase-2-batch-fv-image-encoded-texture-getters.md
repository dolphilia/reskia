# 179 Phase 2 Batch FV: image encoded data and texture getter rules

開始時刻: 2026-05-13 09:55:22 JST

## 目的

`178-phase-2-batch-fu-canvas-image-rect-lattice-nine.md` の「次バッチ候補」から、`SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。retained data は caller-owned handle、bool getter は false、numeric getter は `0` を invalid input 戻り値にする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_refEncodedData` が NULL image / no encoded data を `0` に正規化していることを確認した。
  - `SkImage_isTextureBacked` / `SkImage_isValid` が NULL image false、`SkImage_textureSize` が NULL image `0` を返すことを確認した。
- `skia/capi/sk_image.h`
  - 既存コメントが retained data handle、bool / numeric failure を明記していることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image、raster image false / `0` / no encoded data smoke を確認した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。
- `SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique 系の NULL no-op と bool failure 規約をまとめて再確認する。
- `SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。
- `SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。
