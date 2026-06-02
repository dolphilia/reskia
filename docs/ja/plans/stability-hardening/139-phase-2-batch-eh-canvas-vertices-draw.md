# 139 Phase 2 Batch EH: canvas vertices draw rules

開始時刻: 2026-05-13 04:39:38 JST

## 目的

`138-phase-2-batch-eg-runtime-effect-filter-blender.md` の「次バッチ候補」から、`SkCanvas` drawVertices / drawVerticesPtr の handle / borrowed pointer と paint required 規約を再確認する。あわせて `SkBlendMode` 範囲外値を Skia API に渡さず no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawVertices` / `SkCanvas_drawVerticesPtr` に `valid_blend_mode` guard を追加し、範囲外 mode を no-op にした。
- `skia/capi/sk_canvas.h`
  - 両 API の valid vertices、valid `SkBlendMode`、paint required、invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - valid vertices と paint を使った状態で、`mode == -1` と範囲外 mode が no-op になることを smoke に追加した。
  - 既存の handle 0 / invalid handle / NULL pointer / NULL paint / valid path と合わせて入力規約を固定した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EH に更新した。

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
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkCanvas` drawPatch / experimental edge AA quad の BlendMode / pointer required 規約を再確認する。
