# 159 Phase 2 Batch FB: canvas makeSurface and raster direct rules

開始時刻: 2026-05-13 09:25:00 JST

## 目的

`158-phase-2-batch-fa-image-make-raster.md` の「次バッチ候補」から、`SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。raster direct 系は borrowed pixels と rowBytes の関係を実装・コメント・smoke で揃える。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_MakeRasterDirect` で `info` / `pixels` / `rowBytes` を `validRowBytes` 相当でまとめて検証するようにした。
  - `SkCanvas_MakeRasterDirectN32` で `rowBytes >= width * sizeof(SkPMColor)` を要求するようにした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_MakeRasterDirect` / `SkCanvas_MakeRasterDirectN32` の rowBytes 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - raster direct 系の invalid rowBytes が `0` を返す smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure 0 規約をまとめて再確認する。
- `SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。
- `SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。
