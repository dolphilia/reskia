# 165 Phase 2 Batch FH: image async rescale enum rules

開始時刻: 2026-05-13 09:29:33 JST

## 目的

`164-phase-2-batch-fg-canvas-drawable-mesh.md` の「次バッチ候補」から、`SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。invalid input は callback がある場合に NULL result で callback を呼び、callback NULL は no-op とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `valid_rescale_gamma` / `valid_rescale_mode` / `valid_yuv_color_space` を追加した。
  - `SkImage_asyncRescaleAndReadPixels` で `rescaleGamma` / `rescaleMode` の範囲外値を callback failure にした。
  - YUV / YUVA async read で `yuvColorSpace` / `rescaleGamma` / `rescaleMode` の範囲外値を callback failure にした。
- `skia/capi/sk_image.h`
  - async rescale read 系の enum valid range と callback failure 規約を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - invalid `rescaleGamma` / `rescaleMode` / `yuvColorSpace` が callback failure になる smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。
- `SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。
- `SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。
- `SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure 0 規約をまとめて再確認する。
