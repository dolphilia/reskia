# 212 Phase 2 Batch HC: canvas surface context getter rules

開始時刻: 2026-05-13 11:26:58 JST

## 目的

`211-phase-2-batch-hb-canvas-state-getters.md` の「次バッチ候補」から、`SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約を再確認する。handle は成功時 caller-owned、borrowed pointer は caller が解放せず、NULL canvas や unavailable context は fail-safe 値を返す。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_makeSurface` が canvas / info required、props optional、factory failure `0` であることを確認した。
  - `SkCanvas_getSurface` / `SkCanvas_recorder` / `SkCanvas_recordingContext` が NULL canvas で NULL を返すことを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_getSurface` / `SkCanvas_recorder` / `SkCanvas_recordingContext` に NULL canvas / unavailable 時 NULL を明記した。
  - `SkCanvas_makeSurface` は info required、props optional、factory failure `0` を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL info、valid returned handle または factory failure `0` の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `216-phase-2-batch-hg-canvas-raster-factory.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver 0 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約をまとめて再確認する。
- `SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約をまとめて再確認する。
- `SkCanvas` getBaseLayerSize / getDeviceClipBounds / getLocalClipBounds 系の caller-owned handle と out-param validation 規約をまとめて再確認する。
