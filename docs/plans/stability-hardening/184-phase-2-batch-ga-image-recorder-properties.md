# 184 Phase 2 Batch GA: image recorder properties rules

開始時刻: 2026-05-13 10:00:04 JST

## 目的

`183-phase-2-batch-fz-canvas-pixel-overloads.md` の「次バッチ候補」から、`SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。recorder は required pointer、properties は valid `SkImage::RequiredProperties` handle、invalid input または factory failure は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `has_required_properties_handle` を追加した。
  - recorder factory 系 3 API で stale / invalid `properties` handle を `0` にした。
- `skia/capi/sk_image.h`
  - recorder factory 系 3 API に valid properties handle 規約を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - fake recorder pointer と invalid properties handle の組み合わせが dereference 前に `0` へ落ちる smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` を Batch GC に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure 0 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image 0 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約をまとめて再確認する。
- `SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約をまとめて再確認する。
- `SkCanvas` getDeviceClipBounds / getLocalClipBounds out-param 系の caller-owned handle と required out param 規約をまとめて再確認する。
