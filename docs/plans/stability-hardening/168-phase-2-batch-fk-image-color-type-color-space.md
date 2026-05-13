# 168 Phase 2 Batch FK: image color type and color space rules

開始時刻: 2026-05-13 09:44:58 JST

## 目的

`167-phase-2-batch-fj-canvas-experimental-edge-aa.md` の「次バッチ候補」から、`SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。`targetColorType` は valid `SkColorType` に限定し、invalid input または factory failure は `0` にする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `valid_color_type` を追加した。
  - `SkImage_makeColorTypeAndColorSpace` / `SkImage_makeColorTypeAndColorSpaceWithRecorder` に `targetColorType` 範囲検証を追加した。
- `skia/capi/sk_image.h`
  - targetColorType valid enum と returned handle caller-owned 規約を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - invalid `targetColorType` が `0` を返す smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。
- `SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。
- `SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。
- `SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。
