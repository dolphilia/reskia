# 145 Phase 2 Batch EN: canvas string and simple text rules

開始時刻: 2026-05-13 07:56:07 JST

## 目的

`144-phase-2-batch-em-canvas-glyph-arrays.md` の「次バッチ候補」から、`SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。`drawSimpleText` は byteLength == 0 を no-op とし、byteLength > 0 では text / font / paint に加えて valid `SkTextEncoding` を要求する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `valid_text_encoding` helper を追加し、`SkCanvas_drawSimpleText` が invalid non-range encoding を no-op にするようにした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawSimpleText` のコメントに valid `SkTextEncoding` と invalid input no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawSimpleText` の invalid encoding / required font / required paint / valid path を確認する smoke を追加した。
  - `drawString` / `drawStringObject` の text / font / paint required smoke は既存確認を維持した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EN に更新した。

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

- `SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。
- `SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。
- `SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。
