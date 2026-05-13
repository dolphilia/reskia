# 170 Phase 2 Batch FM: image subset mipmap nontexture rules

開始時刻: 2026-05-13 09:44:58 JST

## 目的

`169-phase-2-batch-fl-canvas-vertices-draw.md` の「次バッチ候補」から、`SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure `0` 規約をまとめて再確認する。成功時は caller-owned image handle、invalid input または factory failure は `0` とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - 対象 API が `make_image_handle` で null `sk_sp` を `0` に正規化していることを確認した。
  - `SkImage_makeSubset` は `subset` required、`direct` optional として維持した。
  - `SkImage_withDefaultMipmaps` / `SkImage_makeNonTextureImage` は NULL image `0` として維持した。
- `skia/capi/sk_image.h`
  - `SkImage_makeSubsetWithRecorder` の returned handle caller-owned を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image、NULL subset、factory failure、valid returned handle smoke を確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` を Batch FM に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。
- `SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。
- `SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。
- `SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。
