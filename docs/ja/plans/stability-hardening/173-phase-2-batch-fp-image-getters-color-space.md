# 173 Phase 2 Batch FP: image getters and color space ownership rules

開始時刻: 2026-05-13 09:50:09 JST

## 目的

`172-phase-2-batch-fo-canvas-atlas-image-set.md` の「次バッチ候補」から、`SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。handle getter は caller-owned、borrowed pointer は caller が解放しない、retained handle は caller が delete する。

## 変更内容

- `skia/capi/sk_image.h`
  - `SkImage_imageInfo` / `SkImage_dimensions` / `SkImage_bounds` の caller-owned handle と NULL image `0` を明記した。
  - `SkImage_uniqueID` / `SkImage_alphaType` / `SkImage_colorType` の NULL image `0` を明記した。
  - `SkImage_colorSpace` の borrowed pointer と `SkImage_refColorSpace` の retained caller-owned handle を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image に対する `imageInfo` / `dimensions` / `bounds` / `uniqueID` / `alphaType` / `colorType` smoke を追加した。
  - 既存の borrowed / retained colorSpace valid path smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。
- `SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。
- `SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。
