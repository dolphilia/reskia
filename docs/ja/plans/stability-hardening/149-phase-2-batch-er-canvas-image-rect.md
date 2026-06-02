# 149 Phase 2 Batch ER: canvas image rect rules

開始時刻: 2026-05-13 08:17:18 JST

## 目的

`148-phase-2-batch-eq-image-shader-rules.md` の「次バッチ候補」から、`SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。handle overload は valid image handle を要求し、pointer overload は borrowed non-null pointer を要求する。src/dst overload では `SkCanvas::SrcRectConstraint` の範囲外値を no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `valid_src_rect_constraint` helper を追加した。
  - `SkCanvas_drawImageRectHandleWithSrcDst` / `SkCanvas_drawImageRectPtrWithSrcDst` に constraint guard を追加した。
- `skia/capi/sk_canvas.h`
  - src/dst image rect overload に valid `SkCanvas::SrcRectConstraint` required を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - pointer overload の valid path、sampling required path、invalid constraint path を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch ER に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。
- `SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。
- `SkCanvas` draw points / draw point XY 系の point mode enum と count / array 規約をまとめて再確認する。
- `SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。
- `SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約をまとめて再確認する。
