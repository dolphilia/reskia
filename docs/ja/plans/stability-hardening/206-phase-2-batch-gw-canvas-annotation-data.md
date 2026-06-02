# 206 Phase 2 Batch GW: canvas annotation data rules

開始時刻: 2026-05-13 11:07:53 JST

## 目的

`205-phase-2-batch-gv-image-subset-color-factories.md` の「次バッチ候補」から、`SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約を再確認する。annotation draw は void API のため invalid input で no-op とし、data handle `0` は optional null data として扱う。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAnnotation` が rect / key required、data handle `0` optional、非 `0` data handle validation を行うことを確認した。
  - `SkCanvas_drawAnnotationWithDataPtr` が rect / key required、value pointer optional であることを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawAnnotationWithDataPtr` に invalid input no-op を明記した。
  - `SkCanvas_drawAnnotation` は data handle `0` optional、非 `0` handle validation、invalid no-op を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL rect、NULL key、data handle `0`、invalid data handle、valid data handle、value pointer NULL / non-NULL の smoke が揃っていることを確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch GW、`sk_image.cpp/h` を batch GV の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約をまとめて再確認する。
- `SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約をまとめて再確認する。
- `SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約をまとめて再確認する。
