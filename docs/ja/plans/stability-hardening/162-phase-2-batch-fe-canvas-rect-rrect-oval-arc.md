# 162 Phase 2 Batch FE: canvas rect rrect oval arc draw rules

開始時刻: 2026-05-13 09:29:33 JST

## 目的

`161-phase-2-batch-fd-canvas-state-mutation.md` の「次バッチ候補」から、`SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。void draw API は NULL canvas、required geometry NULL、paint NULL、invalid handle を no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - 対象 API の既存 guard を確認した。`drawArc` / `drawOval` / `drawRoundRect` / `drawRRect` / `drawDRRect` は required pointer NULL を no-op にしている。
  - `drawRect` は `sk_rect_t` handle を `has_rect_handle` で検証している。
- `skia/capi/sk_canvas.h`
  - 対象 API の required geometry / paint と invalid no-op コメントがガイド方針に沿っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas に対する rect / rrect / oval / arc 系 no-op smoke を追加した。
  - 既存の valid canvas 上の NULL geometry / NULL paint / invalid handle smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。
- `SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。
- `SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。
- `SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。
- `SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。
