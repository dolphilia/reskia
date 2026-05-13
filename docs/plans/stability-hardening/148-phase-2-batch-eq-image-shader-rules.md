# 148 Phase 2 Batch EQ: image shader rules

開始時刻: 2026-05-13 08:17:18 JST

## 目的

`147-phase-2-batch-ep-canvas-clip-transform.md` の「次バッチ候補」から、`SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。tile mode を受け取る overload では `SkTileMode` の範囲外値を 0 戻りにし、範囲外 enum を Skia C++ API に渡さない。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `valid_tile_mode` helper を追加し、`SkTileMode::kLastTileMode` までの値だけを有効として扱うようにした。
  - `SkImage_makeShader` / `SkImage_makeShaderWithTileModesAndLocalMatrix` / `SkImage_makeRawShader` / `SkImage_makeRawShaderWithTileModesAndLocalMatrix` に tile mode guard を追加した。
- `skia/capi/sk_image.h`
  - tile mode を受け取る shader overload に valid `SkTileMode` required を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - shader / raw shader の invalid tmx / tmy が 0 を返す smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` の P2 記録を Batch EQ に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_image_surface_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw image rect 系の handle / pointer overload と sampling required 規約をまとめて再確認する。
- `SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。
- `SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。
- `SkCanvas` draw points / draw point XY 系の point mode enum と count / array 規約をまとめて再確認する。
- `SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。
