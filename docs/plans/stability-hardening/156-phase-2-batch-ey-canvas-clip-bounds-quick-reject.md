# 156 Phase 2 Batch EY: canvas clip bounds and quickReject rules

開始時刻: 2026-05-13 09:11:03 JST

## 目的

`155-phase-2-batch-ex-canvas-read-write-pixels.md` の「次バッチ候補」から、`SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。clip bounds handle return は caller-owned、NULL canvas は 0、out param は required とする。quickReject は required geometry pointer の NULL を false にする。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_getDeviceClipBounds` / `SkCanvas_getLocalClipBounds` の caller-owned handle と NULL canvas 0 戻りを明記した。
  - `SkCanvas_getDeviceClipBoundsInto` / `SkCanvas_getLocalClipBoundsInto` の out param required と invalid false を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - clip bounds handle return の NULL / valid path、out param NULL / valid path を確認する smoke を追加した。
  - quickReject / quickRejectRect の NULL geometry false smoke を維持した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EY に更新した。

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

- `SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure 0 規約をまとめて再確認する。
- `SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。
