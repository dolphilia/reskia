# 146 Phase 2 Batch EO: canvas saveLayer rules

開始時刻: 2026-05-13 07:56:07 JST

## 目的

`145-phase-2-batch-en-canvas-string-text.md` の「次バッチ候補」から、`SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。NULL canvas は 0 を返し、optional pointer overload では bounds / paint の NULL を許容する。alpha overload は Skia の期待範囲に合わせ、範囲外入力を 0 戻りにする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_saveLayerAlpha` で alpha > 255 を 0 戻りにした。
  - `SkCanvas_saveLayerAlphaf` で非 finite / 0.0 未満 / 1.0 超過を 0 戻りにした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_saveLayerAlpha` の alpha 範囲を 0..255 と明記した。
  - `SkCanvas_saveLayerAlphaf` の alpha 範囲を finite かつ 0.0..1.0 と明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - optional bounds / paint の正の save count 確認を維持しつつ、invalid alpha が 0 を返す smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EO に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。
- `SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。
- `SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。
