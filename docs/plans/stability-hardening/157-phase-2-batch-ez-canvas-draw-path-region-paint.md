# 157 Phase 2 Batch EZ: canvas draw path region paint rules

開始時刻: 2026-05-13 09:25:00 JST

## 目的

`156-phase-2-batch-ey-canvas-clip-bounds-quick-reject.md` の「次バッチ候補」から、`SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。draw 系は NULL canvas または required pointer NULL で no-op とし、戻り値を持たない API は crash させない。

## 変更内容

- `skia/capi/sk_canvas.h`
  - `SkCanvas_private_draw_shadow_rec` の `path` / `rec` required と invalid no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas に対する `SkCanvas_drawRegion` / `SkCanvas_drawPaint` / `SkCanvas_private_draw_shadow_rec` の no-op smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - 後続バッチ完了後の最新状態として `sk_canvas.cpp` / `sk_canvas.h` を Batch FD に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure 0 規約をまとめて再確認する。
- `SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。
