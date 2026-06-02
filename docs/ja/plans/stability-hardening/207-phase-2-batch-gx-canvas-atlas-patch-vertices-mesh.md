# 207 Phase 2 Batch GX: canvas atlas patch vertices mesh rules

開始時刻: 2026-05-13 11:21:28 JST

## 目的

`206-phase-2-batch-gw-canvas-annotation-data.md` の「次バッチ候補」から、`SkCanvas` draw atlas / patch / vertices / mesh 系の count/array、optional colors、blend mode validation 規約を再確認する。void draw API は invalid input で no-op とし、array は count に応じて required にする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAtlas` が `count <= 0` no-op、`count > 0` で atlas / xform / tex / sampling required、colors / cullRect / paint optional、blend mode validation であることを確認した。
  - `SkCanvas_drawPatch` が cubics / texCoords / paint required、colors optional、blend mode validation であることを確認した。
  - `SkCanvas_drawVertices` / `SkCanvas_drawVerticesPtr` が valid handle / borrowed pointer、paint required、blend mode validation であることを確認した。
  - `SkCanvas_drawMesh` が mesh / paint required、blender handle validation であることを確認した。
- `skia/capi/sk_canvas.h`
  - count、required array、optional colors、valid enum / handle、invalid no-op コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、count <= 0、required pointer NULL、invalid enum / handle、optional colors NULL、有効入力の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `211-phase-2-batch-hb-canvas-state-getters.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` readPixels / scalePixels 系の pixmap/storage、rowBytes、cachingHint validation 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の info/pixmap/storage、rowBytes validation 規約をまとめて再確認する。
- `SkImage` asyncRescaleAndReadPixels 系の callback failure、dstSize、enum validation 規約をまとめて再確認する。
- `SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約をまとめて再確認する。
- `SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約をまとめて再確認する。
