# 142 Phase 2 Batch EK: canvas picture and text blob draw rules

開始時刻: 2026-05-13 07:53:05 JST

## 目的

`141-phase-2-batch-ej-canvas-atlas-image-set-arrays.md` の「次バッチ候補」から、`SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。handle overload は invalid handle を no-op にし、pointer overload は borrowed non-null pointer として扱い、matrix / paint optional overload は NULL を許容する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawPicturePtr` / `SkCanvas_drawPicturePtrWithMatrixPaint` / `SkCanvas_drawTextBlobPtr` について、pointer が borrowed であり、この API 経由では解放しないことを明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存 smoke で `drawPicture` / `drawTextBlob` の handle 0、invalid handle、NULL pointer、NULL paint、valid pointer / handle path、matrix / paint optional path を確認済みであることを再確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EK に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkCanvas` draw glyph array 系の count / array required と origin handle 規約をまとめて再確認する。
- `SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。
- `SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。
