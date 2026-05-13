# 180 Phase 2 Batch FW: canvas clip shader and geometry rules

開始時刻: 2026-05-13 09:55:22 JST

## 目的

`179-phase-2-batch-fv-image-encoded-texture-getters.md` の「次バッチ候補」から、`SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。geometry pointer は required、shader は valid handle、clip op は valid enum、invalid input は no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - clip geometry 系が required pointer NULL と invalid clip op を no-op にしていることを確認した。
  - `SkCanvas_clipShader` が valid shader handle と valid clip op を要求していることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが required geometry pointer、valid shader handle、valid clip op、invalid no-op を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存の NULL geometry、invalid clip op、invalid shader handle、valid path smoke を確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch FW に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique 系の NULL no-op と bool failure 規約をまとめて再確認する。
- `SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。
- `SkImage` makeSubsetWithRecorder / makeColorSpaceWithRecorder 系の recorder required と properties handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / imageInfo / top props getter 系の handle return と failure 0 規約をまとめて再確認する。
