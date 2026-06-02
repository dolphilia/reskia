# 154 Phase 2 Batch EW: canvas bitmap and pixmap rules

開始時刻: 2026-05-13 09:11:03 JST

## 目的

`153-phase-2-batch-ev-image-read-scale-pixels.md` の「次バッチ候補」から、`SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約を確認する。現行 C API には直接の drawBitmap / drawPixmap wrapper がないため、bitmap / pixmap 周辺として canvas creation と既存 read/write storage 規約を確認する。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_newFromBitmap` / `SkCanvas_newFromBitmapWithProps` の required pointer、caller-owned canvas pointer、NULL 戻りを複数行コメントで明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_newFromBitmap(nullptr)` / `SkCanvas_newFromBitmapWithProps(nullptr, nullptr)` が NULL を返す smoke を追加した。

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

- `SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。
- `SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。
- `SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。
