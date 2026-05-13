# 151 Phase 2 Batch ET: canvas line and point handle rules

開始時刻: 2026-05-13 08:17:18 JST

## 目的

`150-phase-2-batch-es-canvas-image-lattice-nine.md` の「次バッチ候補」から、`SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。handle overload は valid point handle と paint を要求し、XY overload は paint を要求する。NULL canvas は no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawLine` / `SkCanvas_drawPoint` / `SkCanvas_drawCircle` は既に `has_point_handle` で invalid non-zero handle を no-op にしていることを確認した。
  - `SkCanvas_drawLineXY` / `SkCanvas_drawPointXY` / `SkCanvas_drawCircleAt` は canvas / paint required の no-op 規約に沿っていることを確認した。
- `skia/capi/sk_canvas.h`
  - line / point / circle 系の valid handle と paint required コメントが現行実装と一致していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas の line / point / circle 系 no-op smoke を追加した。
  - 既存の invalid 0 handle / invalid non-zero handle / NULL paint / valid path smoke を維持した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch ET に更新した。

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

- `SkCanvas` draw points / draw point XY 系の point mode enum と count / array 規約をまとめて再確認する。
- `SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。
- `SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。
- `SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。
