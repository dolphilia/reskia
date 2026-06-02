# 144 Phase 2 Batch EM: canvas glyph array rules

開始時刻: 2026-05-13 07:56:07 JST

## 目的

`143-phase-2-batch-el-image-encoded-data.md` の「次バッチ候補」から、`SkCanvas` draw glyph array 系の count / array required と origin handle 規約をまとめて再確認する。count <= 0 は no-op とし、count > 0 では required 配列と font / paint を必須にし、origin は 0 だけでなく存在しない non-zero handle も no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawGlyphs` / `SkCanvas_drawGlyphsAtPositions` / `SkCanvas_drawGlyphsWithXforms` の origin 判定を `origin == 0` から `has_point_handle(origin)` に変更し、invalid non-zero handle を dereference しないようにした。
- `skia/capi/sk_canvas.h`
  - glyph array 系3関数について、count <= 0 no-op、count > 0 の required 配列、origin valid handle、invalid input no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - valid origin / invalid non-zero origin / required font / required paint / valid path を glyph array 系3関数で確認する smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EM に更新した。

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

- `SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。
- `SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。
