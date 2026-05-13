# 185 Phase 2 Batch GB: canvas surface info getter rules

開始時刻: 2026-05-13 10:00:04 JST

## 目的

`184-phase-2-batch-ga-image-recorder-properties.md` の「次バッチ候補」から、`SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure `0` 規約をまとめて再確認する。handle getter は caller-owned handle を返し、NULL canvas は `0` または NULL pointer を返す。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_getBaseLayerSize` / `SkCanvas_getBaseProps` / `SkCanvas_getTopProps` / `SkCanvas_imageInfo` の caller-owned handle と NULL canvas `0` を明記した。
  - `SkCanvas_getProps` の invalid false を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas に対する base layer size / base props / getProps / getSurface / top props / imageInfo smoke を追加した。
  - 既存の `makeSurface` NULL canvas / NULL info smoke を維持した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch GB に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image 0 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約をまとめて再確認する。
- `SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約をまとめて再確認する。
- `SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約をまとめて再確認する。
- `SkImage` isAlphaOnly / isOpaque / isProtected 系の bool getter NULL false 規約をまとめて再確認する。
