# 167 Phase 2 Batch FJ: canvas experimental edge AA rules

開始時刻: 2026-05-13 09:44:58 JST

## 目的

`166-phase-2-batch-fi-canvas-annotation-data.md` の「次バッチ候補」から、`SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。array pointer は `cnt > 0` のとき required、optional pointer は NULL 許可、範囲外 enum は no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_experimental_DrawEdgeAAImageSet` に `SrcRectConstraint` の範囲検証を追加した。
  - `SkCanvas_experimental_DrawEdgeAAQuad` / `SkCanvas_experimental_DrawEdgeAAQuadU32Color` に `QuadAAFlags` の範囲検証を追加した。
- `skia/capi/sk_canvas.h`
  - image set の `constraint` valid enum と invalid no-op を明記した。
  - edge AA quad 系の `aaFlags` valid range を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas の edge AA quad 系 no-op smoke を追加した。
  - valid canvas 上で invalid `constraint` / `aaFlags` が no-op になる smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。
- `SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。
- `SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。
