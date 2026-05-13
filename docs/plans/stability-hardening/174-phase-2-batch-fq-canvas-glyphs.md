# 174 Phase 2 Batch FQ: canvas glyph draw rules

開始時刻: 2026-05-13 09:50:09 JST

## 目的

`173-phase-2-batch-fp-image-getters-color-space.md` の「次バッチ候補」から、`SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。`count <= 0` は no-op、`count > 0` では配列、origin handle、font、paint を required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawGlyphs` が `glyphs` / `positions` / `clusters` / `origin` / `font` / `paint` を検証し、`textByteCount > 0` では `utf8text` required にしていることを確認した。
  - `SkCanvas_drawGlyphsAtPositions` / `SkCanvas_drawGlyphsWithXforms` が `glyphs` / `positions or xforms` / `origin` / `font` / `paint` を検証していることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが count-array と origin handle 規約を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - 既存の NULL canvas、count 0、required array NULL、invalid origin handle、NULL font、NULL paint、valid path smoke を確認した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。
- `SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。
- `SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。
- `SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。
