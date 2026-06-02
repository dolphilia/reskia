# 155 Phase 2 Batch EX: canvas read and write pixels rules

開始時刻: 2026-05-13 09:11:03 JST

## 目的

`154-phase-2-batch-ew-canvas-bitmap-pixmap.md` の「次バッチ候補」から、`SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。`has_valid_pixels` による rowBytes guard と caller-owned storage の非保持規約を維持する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - read/write pixels 系の rowBytes guard が `has_valid_pixels` に集約されていることを確認した。
- `skia/capi/sk_canvas.h`
  - read/write pixels 系の storage lifetime コメントが現行実装と一致していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_writePixelsWithImageInfo(nullptr, ...)` が false を返す smoke を追加した。

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

- `SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。
- `SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure 0 規約をまとめて再確認する。
