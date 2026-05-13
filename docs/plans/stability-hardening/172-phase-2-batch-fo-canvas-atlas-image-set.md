# 172 Phase 2 Batch FO: canvas atlas and image set rules

開始時刻: 2026-05-13 09:50:09 JST

## 目的

`171-phase-2-batch-fn-canvas-text-blob-string.md` の「次バッチ候補」から、`SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。`count <= 0` は no-op、`count > 0` では required arrays / sampling / enum を検証し、optional pointer は NULL 許可とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAtlas` が `count <= 0` no-op、`atlas` / `xform` / `tex` / `sampling` required、`colors` / `cullRect` / `paint` optional、`mode` valid enum であることを確認した。
  - `SkCanvas_experimental_DrawEdgeAAImageSet` が `cnt <= 0` no-op、`imageSet` / `sampling` required、`dstClips` / `preViewMatrices` / `paint` optional、`constraint` valid enum であることを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_drawAtlas` に invalid input no-op を明記した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存の NULL canvas、negative count、required pointer NULL、invalid blend mode、optional pointer NULL smoke を確認した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。
- `SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。
- `SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。
