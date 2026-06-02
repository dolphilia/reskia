# 171 Phase 2 Batch FN: canvas text blob and string draw rules

開始時刻: 2026-05-13 09:44:58 JST

## 目的

`170-phase-2-batch-fm-image-subset-mipmap-nontexture.md` の「次バッチ候補」から、`SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。text blob handle は valid handle、pointer 版は borrowed non-null、string / font / paint は required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawTextBlob` が valid text blob handle を要求することを確認した。
  - `SkCanvas_drawTextBlobPtr` / `SkCanvas_drawString` / `SkCanvas_drawStringObject` が required pointer NULL を no-op にしていることを確認した。
- `skia/capi/sk_canvas.h`
  - 既存コメントが valid handle / borrowed pointer / required font / required paint を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas の text blob / string 系 no-op smoke を追加した。
  - 既存の valid canvas 上の invalid handle、NULL pointer、NULL font、NULL paint、valid path smoke を維持した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch FN に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw atlas / image set 系の count-array 規約と optional paint/cull pointer 規約をまとめて再確認する。
- `SkImage` alphaType / colorType / colorSpace getter 系の NULL receiver 戻り値と borrowed/retained ownership 規約をまとめて再確認する。
- `SkCanvas` draw glyphs 系の glyph/position/cluster arrays と origin handle 規約をまとめて再確認する。
- `SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。
- `SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。
