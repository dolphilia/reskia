# 178 Phase 2 Batch FU: canvas image rect lattice nine rules

開始時刻: 2026-05-13 09:55:22 JST

## 目的

`177-phase-2-batch-ft-image-shader-factory.md` の「次バッチ候補」から、`SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。image / geometry / sampling は required、paint は optional、filter / constraint は valid enum とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - image rect / lattice / nine 系が required pointer NULL、invalid image handle、invalid filter、invalid constraint を no-op にしていることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが required geometry pointer、optional paint、filter / constraint valid enum を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存の invalid image handle、NULL geometry、NULL sampling、invalid filter / constraint、valid path smoke を確認した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。
- `SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。
- `SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique 系の NULL no-op と bool failure 規約をまとめて再確認する。
- `SkCanvas` read/write pixels pixmap/bitmap overload 系の rowBytes/storage と bool failure 規約をまとめて再確認する。
