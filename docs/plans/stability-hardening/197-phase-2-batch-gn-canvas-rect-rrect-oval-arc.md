# 197 Phase 2 Batch GN: canvas rect rrect oval arc rules

開始時刻: 2026-05-13 10:18:40 JST

## 目的

`196-phase-2-batch-gm-canvas-color-rules.md` の「次バッチ候補」から、`SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約を再確認する。void draw API は invalid input で no-op とし、geometry と paint は Skia が NULL を許容しない限り required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawArc` / `SkCanvas_drawOval` / `SkCanvas_drawRoundRect` / `SkCanvas_drawRRect` が geometry pointer と paint を検証していることを確認した。
  - `SkCanvas_drawRect` が rect handle と paint を検証していることを確認した。
- `skia/capi/sk_canvas.h`
  - 対象 API の geometry / paint required と invalid input no-op コメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL geometry、invalid rect handle、NULL paint、有効入力の smoke が揃っていることを確認した。

## 検証

- この batch の検証は `201-phase-2-batch-gr-canvas-image-draw.md` にまとめて記録する。

## 次バッチ候補

- `SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約をまとめて再確認する。
- `SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約をまとめて再確認する。
- `SkImage` refEncodedData / encode 系の nullable encoded data handle 規約をまとめて再確認する。
- `SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約をまとめて再確認する。
