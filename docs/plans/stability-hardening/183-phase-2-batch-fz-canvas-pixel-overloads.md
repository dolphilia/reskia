# 183 Phase 2 Batch FZ: canvas pixel overload rules

開始時刻: 2026-05-13 10:00:04 JST

## 目的

`182-phase-2-batch-fy-image-ref-unique.md` の「次バッチ候補」から、`SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。bitmap / pixmap / imageInfo / pixels / rowBytes は API ごとの required 条件を満たす必要があり、invalid input は false とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - read/write pixels 系が NULL canvas、required pointer NULL、invalid rowBytes、empty storage を false にしていることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが rowBytes / storage / bool failure 規約を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas に対する `SkCanvas_readPixelsWithPixmap` / `SkCanvas_writePixels` smoke を追加した。
  - 既存の NULL bitmap/pixmap/info/pixels、invalid rowBytes、empty storage smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure 0 規約をまとめて再確認する。
- `SkImage` dimensions / bounds / imageInfo handle getter 系の caller-owned handle と NULL image 0 規約をまとめて再確認する。
- `SkCanvas` accessTopLayerPixels / peekPixels 系の borrowed storage lifetime と optional out param 規約をまとめて再確認する。
- `SkImage` colorSpace / refColorSpace 系の borrowed pointer と retained handle ownership 規約をまとめて再確認する。
