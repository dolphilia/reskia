# 147 Phase 2 Batch EP: canvas clip and transform helpers

開始時刻: 2026-05-13 08:17:18 JST

## 目的

`146-phase-2-batch-eo-canvas-save-layer.md` の「次バッチ候補」から、`SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。transform 系の required matrix pointer guard は既存実装で維持し、clip helper 系では `SkClipOp` の範囲外値を no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `valid_clip_op` helper を追加し、`SkClipOp::kDifference` / `SkClipOp::kIntersect` 以外を invalid として扱うようにした。
  - `clipIRect` / `clipPathWithOp` / `clipPathWithOpAA` / `clipRectWithOp` / `clipRectWithOpAA` / `clipRegion` / `clipRRectWithOp` / `clipRRectWithOpAA` / `clipShader` に valid clip op guard を追加した。
- `skia/capi/sk_canvas.h`
  - clip op を受け取る関数に valid `SkClipOp` required と invalid input no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - invalid clip op でも fake geometry pointer を dereference せず no-op になることを各 clip helper 系で確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EP に更新した。

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

- `SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。
- `SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。
- `SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。
- `SkCanvas` draw points / draw point XY 系の point mode enum と count / array 規約をまとめて再確認する。
