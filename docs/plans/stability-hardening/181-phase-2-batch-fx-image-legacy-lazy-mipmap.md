# 181 Phase 2 Batch FX: image legacy bitmap lazy mipmap rules

開始時刻: 2026-05-13 09:55:22 JST

## 目的

`180-phase-2-batch-fw-canvas-clip-shader-geometry.md` の「次バッチ候補」から、`SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。output pointer は required、legacy bitmap mode は valid enum、bool getter は NULL image false とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `valid_legacy_bitmap_mode` を追加し、`SkImage_asLegacyBitmap` で範囲外 mode を false にした。
  - lazy / mipmap / protected getter が NULL image false を返すことを確認した。
- `skia/capi/sk_image.h`
  - `SkImage_asLegacyBitmap` の output pointer required、legacyBitmapMode valid enum、invalid false を明記した。
  - `SkImage_hasMipmaps` / `SkImage_isProtected` / `SkImage_isLazyGenerated` の NULL image false を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image の lazy / mipmap / protected / legacy bitmap smoke を追加した。
  - `SkImage_asLegacyBitmap` の NULL bitmap と invalid legacyBitmapMode smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` を Batch FX に更新した。

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

- `SkImage` ref/unref/release/unique 系の NULL no-op と bool failure 規約をまとめて再確認する。
- `SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。
- `SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure 0 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image 0 規約をまとめて再確認する。
