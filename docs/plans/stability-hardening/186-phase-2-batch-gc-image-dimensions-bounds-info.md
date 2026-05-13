# 186 Phase 2 Batch GC: image dimensions bounds info rules

開始時刻: 2026-05-13 10:00:04 JST

## 目的

`185-phase-2-batch-gb-canvas-surface-info-getters.md` の「次バッチ候補」から、`SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image `0` 規約をまとめて再確認する。成功時の handle は caller-owned、NULL image は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_imageInfo` / `SkImage_dimensions` / `SkImage_bounds` が NULL image `0` を返し、成功時に static handle を作ることを確認した。
- `skia/capi/sk_image.h`
  - 既存コメントが caller-owned handle と NULL image `0` を明記していることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image getter smoke を確認した。
  - 今回の recorder/properties smoke と同じ image getter batch として記録した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約をまとめて再確認する。
- `SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約をまとめて再確認する。
- `SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約をまとめて再確認する。
- `SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約をまとめて再確認する。
