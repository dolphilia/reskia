# 196 Phase 2 Batch GM: canvas color rules

開始時刻: 2026-05-13 10:14:37 JST

## 目的

`195-phase-2-batch-gl-image-raster-nontexture-mipmap.md` の「次バッチ候補」から、`SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約を再確認する。void draw/mutation API は invalid input で no-op とし、`drawColor` 系は `SkBlendMode` 範囲外を拒否する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_clear` が canvas / color NULL で no-op になることを確認した。
  - `SkCanvas_clearColor` が NULL canvas で no-op になることを確認した。
  - `SkCanvas_drawColor` が canvas / color NULL と invalid blend mode を no-op にすることを確認した。
  - `SkCanvas_drawColorU32` が NULL canvas と invalid blend mode を no-op にすることを確認した。
- `skia/capi/sk_canvas.h`
  - `SkCanvas_clear` に invalid input no-op を明記した。
  - `SkCanvas_clearColor` の行末コメントを NULL canvas no-op に更新した。
  - `drawColor` / `drawColorU32` は color required、blend mode validation、invalid no-op を明記済みであることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、NULL color、invalid blend mode、有効 blend mode の smoke が揃っていることを確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch GM、`sk_image.cpp/h` を batch GL の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw rect / rrect / oval / arc 系の geometry pointer と paint required 規約をまとめて再確認する。
- `SkImage` textureSize / isTextureBacked / isValid 系の GPU/context optional 規約をまとめて再確認する。
- `SkCanvas` clip rect / rrect / path / shader 系の enum/handle validation と no-op 規約をまとめて再確認する。
- `SkImage` refEncodedData / encode 系の nullable encoded data handle 規約をまとめて再確認する。
- `SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約をまとめて再確認する。
