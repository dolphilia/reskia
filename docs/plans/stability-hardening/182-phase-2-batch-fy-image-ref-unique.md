# 182 Phase 2 Batch FY: image ref unique rules

開始時刻: 2026-05-13 10:00:04 JST

## 目的

`181-phase-2-batch-fx-image-legacy-lazy-mipmap.md` の「次バッチ候補」から、`SkImage` ref / unref / release / unique 系の NULL no-op と bool failure 規約をまとめて再確認する。参照カウント操作は NULL no-op、`unique` は NULL image false とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_ref` / `SkImage_unref` / `SkImage_release` が NULL image no-op であることを確認した。
  - `SkImage_unique` が NULL image false を返すことを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_ref` / `SkImage_unref` / `SkImage_unique` の NULL 規約を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - `SkImage_unique(nullptr) == false` の smoke を追加した。
  - 既存の `ref` / `unref` / `release` NULL no-op smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。
- `SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure 0 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image 0 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約をまとめて再確認する。
