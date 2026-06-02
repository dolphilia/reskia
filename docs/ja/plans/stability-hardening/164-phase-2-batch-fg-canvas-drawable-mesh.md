# 164 Phase 2 Batch FG: canvas drawable and mesh draw rules

開始時刻: 2026-05-13 09:29:33 JST

## 目的

`163-phase-2-batch-ff-image-color-space.md` の「次バッチ候補」から、`SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。drawable は borrowed pointer、mesh は borrowed pointer、blender は valid handle として扱い、invalid input は no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `has_blender_handle` を追加し、`SkCanvas_drawMesh` で stale / invalid blender handle を no-op にするようにした。
  - `SkCanvas_drawDrawable` / `SkCanvas_drawDrawableAt` は borrowed drawable pointer NULL を no-op にしていることを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawMesh` の blender valid handle と invalid no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas の drawable / mesh no-op smoke を追加した。
  - valid canvas 上で invalid blender handle が no-op になる smoke を追加した。
  - 既存の drawable valid path smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。
- `SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。
- `SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。
- `SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。
