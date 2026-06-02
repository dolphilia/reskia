# 176 Phase 2 Batch FS: canvas picture draw rules

開始時刻: 2026-05-13 09:50:09 JST

## 目的

`175-phase-2-batch-fr-image-read-scale-pixmap.md` の「次バッチ候補」から、`SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。handle 版は valid picture handle、pointer 版は borrowed non-null pointer、matrix / paint は optional とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawPicture` / `SkCanvas_drawPictureHandleWithMatrixPaint` が invalid handle を no-op にしていることを確認した。
  - pointer 版は borrowed picture pointer NULL を no-op にし、matrix / paint NULL を許容していることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが invalid picture handle no-op、borrowed pointer、optional matrix / paint を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存の NULL canvas、invalid handle、NULL borrowed pointer、optional matrix / paint、valid path smoke を確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch FS に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。
- `SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。
- `SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。
- `SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。
- `SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。
