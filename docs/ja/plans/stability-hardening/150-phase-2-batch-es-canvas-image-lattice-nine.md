# 150 Phase 2 Batch ES: canvas image lattice and nine rules

開始時刻: 2026-05-13 08:17:18 JST

## 目的

`149-phase-2-batch-er-canvas-image-rect.md` の「次バッチ候補」から、`SkCanvas` draw image lattice / nine 系の required geometry pointer と optional paint 規約をまとめて再確認する。image / lattice or center / dst は borrowed non-null pointer とし、filter overload では `SkFilterMode` の範囲外値を no-op にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `valid_filter_mode` helper を追加し、`SkFilterMode::kLast` までの値だけを有効として扱うようにした。
  - `SkCanvas_drawImageLatticeWithFilter` / `SkCanvas_drawImageNine` に filter guard を追加した。
- `skia/capi/sk_canvas.h`
  - lattice with filter / nine overload に valid `SkFilterMode` required を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - invalid filter が no-op になり、required geometry pointer を dereference しないことを確認する smoke を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch ES に更新した。

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

- `SkCanvas` draw line / point handle 系の valid handle guard と invalid no-op 規約をまとめて再確認する。
- `SkCanvas` draw points / draw point XY 系の point mode enum と count / array 規約をまとめて再確認する。
- `SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。
- `SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。
