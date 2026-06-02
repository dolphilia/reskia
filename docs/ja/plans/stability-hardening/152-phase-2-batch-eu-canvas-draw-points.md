# 152 Phase 2 Batch EU: canvas draw points rules

開始時刻: 2026-05-13 09:11:03 JST

## 目的

`151-phase-2-batch-et-canvas-line-point.md` の「次バッチ候補」から、`SkCanvas` draw points 系の point mode enum と count / array 規約をまとめて再確認する。`count == 0` は no-op として扱い、`count > 0` では points 配列と paint を要求する。`PointMode` は Skia の定義範囲だけを有効にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `valid_point_mode` helper を追加し、`kPoints_PointMode` / `kLines_PointMode` / `kPolygon_PointMode` 以外を no-op にした。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawPoints` の count / pts / paint / point mode 規約を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - invalid point mode、NULL pts、NULL paint、count 0、valid points path を確認する smoke を追加した。

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

- `SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。
- `SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。
- `SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。
- `SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。
