# 140 Phase 2 Batch EI: canvas draw BlendMode guard sweep

開始時刻: 2026-05-13 07:41:27 JST

## 目的

`139-phase-2-batch-eh-canvas-vertices-draw.md` の「次バッチ候補」から、`SkCanvas` draw 系のうち `SkBlendMode` を受ける API をまとまった規約単位で再確認する。対象は `drawAtlas` / `drawPatch` / `experimental_DrawEdgeAAQuad` / `experimental_DrawEdgeAAQuadU32Color` で、範囲外 `SkBlendMode` を Skia API に渡さず no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAtlas` / `SkCanvas_drawPatch` / `SkCanvas_experimental_DrawEdgeAAQuad` / `SkCanvas_experimental_DrawEdgeAAQuadU32Color` に `valid_blend_mode` guard を追加した。
- `skia/capi/sk_canvas.h`
  - 各 API の valid `SkBlendMode` 規約と invalid input no-op 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - valid inputs を用意したうえで、`mode == -1` と範囲外 mode が no-op になることを smoke に追加した。
  - `drawAtlas` は valid image / xform / tex / sampling、`drawPatch` は valid cubics / texCoords / paint、edge AA quad は valid rect / color で代表 valid path も確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EI に更新した。

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

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkCanvas` drawAtlas / experimental image set の count / array required 規約を再確認する。
- `SkCanvas` draw glyph array 系の count / array required と origin handle 規約をまとめて再確認する。
- `SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。
