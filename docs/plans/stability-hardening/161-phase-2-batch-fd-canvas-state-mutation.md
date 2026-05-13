# 161 Phase 2 Batch FD: canvas save restore matrix mutation rules

開始時刻: 2026-05-13 09:25:00 JST

## 目的

`160-phase-2-batch-fc-canvas-matrix-getters.md` の「次バッチ候補」から、`SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。void mutation は NULL canvas no-op、`save` は NULL canvas `0` とする。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `resetMatrix` / `restore` / `restoreToCount` / `rotate` / `rotateAround` / `scale` / `skew` / `translate` の NULL canvas no-op を明記した。
  - `SkCanvas_save` の NULL canvas `0` を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - save / restore / matrix mutation 系の NULL canvas no-op と `save(nullptr) == 0` smoke を追加した。
  - valid canvas で `save` が正の値を返し、matrix mutation を通してから `restoreToCount` できることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch FD に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。
- `SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。
- `SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。
- `SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。
