# 169 Phase 2 Batch FL: canvas vertices draw rules

開始時刻: 2026-05-13 09:44:58 JST

## 目的

`168-phase-2-batch-fk-image-color-type-color-space.md` の「次バッチ候補」から、`SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。handle 版は valid handle、pointer 版は borrowed non-null pointer、blend mode は valid enum、paint は required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawVertices` が `has_vertices_handle` と `valid_blend_mode` を使っていることを確認した。
  - `SkCanvas_drawVerticesPtr` が borrowed pointer NULL と invalid blend mode を no-op にしていることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが valid handle / borrowed pointer / valid blend mode / paint required を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas の vertices 系 no-op smoke を追加した。
  - 既存の invalid handle、NULL pointer、invalid blend mode、NULL paint、valid path smoke を維持した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。
- `SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。
- `SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。
- `SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。
