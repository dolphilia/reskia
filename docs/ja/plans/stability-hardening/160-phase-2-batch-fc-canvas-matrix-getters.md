# 160 Phase 2 Batch FC: canvas matrix getter rules

開始時刻: 2026-05-13 09:25:00 JST

## 目的

`159-phase-2-batch-fb-canvas-make-surface-raster-direct.md` の「次バッチ候補」から、`SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure `0` 規約をまとめて再確認する。成功時の matrix handle は caller-owned とし、NULL canvas は `0` を返す。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_getLocalToDevice` / `SkCanvas_getLocalToDeviceAs3x3` / `SkCanvas_getTotalMatrix` の caller-owned handle と NULL canvas `0` を複数行コメントで明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 3 API の NULL canvas `0` smoke を追加した。
  - valid canvas で非 0 handle が返り、handle table から pointer を取得できることを確認して delete する smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。
- `SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。
- `SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。
