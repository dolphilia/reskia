# 141 Phase 2 Batch EJ: canvas atlas and image set array rules

開始時刻: 2026-05-13 07:49:41 JST

## 目的

`140-phase-2-batch-ei-canvas-blend-mode-draw.md` の「次バッチ候補」から、`SkCanvas` drawAtlas / experimental image set の count / array required 規約を再確認する。どちらも `count <= 0` は no-op、`count > 0` では required array / object pointer を C API 境界で確認する規約に揃える。

## 変更内容

- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawAtlas` について、valid image / xform / tex / sampling を用意したうえで、count > 0 時の NULL atlas / xform / tex / sampling が no-op になることを追加確認した。
  - `SkCanvas_experimental_DrawEdgeAAImageSet` について、count > 0 時の NULL sampling が no-op になることを追加確認した。
  - `SkCanvas_experimental_DrawEdgeAAImageSet` の full valid path は、`SkCanvas::ImageSetEntry` を構築する C API がなく、このバッチの目的が required guard 固定であるため省略した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` の P2 記録を Batch EJ に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkCanvas` draw glyph array 系の count / array required と origin handle 規約をまとめて再確認する。
- `SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。
