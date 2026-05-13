# 191 Phase 2 Batch GH: canvas saveLayer rules

開始時刻: 2026-05-13 10:09:04 JST

## 目的

`190-phase-2-batch-gg-image-bool-getters.md` の「次バッチ候補」から、`SkCanvas` saveLayer 系の optional bounds/paint と alpha range 規約を再確認する。NULL canvas や required pointer 不足は `0`、optional pointer は NULL 許容、alpha は範囲外を拒否する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_saveLayer` は canvas / layerRec 必須で、invalid input `0` であることを確認した。
  - `SkCanvas_saveLayerWithBoundsPaintRef` は canvas / bounds 必須、paint optional、invalid input `0` であることを確認した。
  - `SkCanvas_saveLayerWithBoundsPaintPtr` は bounds / paint optional、NULL canvas `0` であることを確認した。
  - `SkCanvas_saveLayerAlpha` は alpha `0..255`、`SkCanvas_saveLayerAlphaf` は finite かつ `0.0..1.0` であることを確認した。
- `skia/capi/sk_canvas.h`
  - required pointer、optional pointer、alpha range、NULL canvas `0` のコメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas、required pointer NULL、optional bounds / paint NULL、alpha 範囲外、valid alpha の smoke が揃っていることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch GH、`sk_image.cpp/h` を batch GG の進捗として更新した。

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

- `SkCanvas` matrix transform / concat / setMatrix 系の required matrix pointer と NULL canvas no-op 規約をまとめて再確認する。
- `SkImage` width / height / uniqueID / alphaType / colorType numeric/enum getter 系の NULL receiver 0 規約をまとめて再確認する。
- `SkCanvas` draw point / line / circle 系の geometry と paint required 規約をまとめて再確認する。
- `SkImage` makeRasterImage / makeNonTextureImage / withDefaultMipmaps returned handle 系の factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw color / clear 系の color pointer、blend mode enum、NULL canvas no-op 規約をまとめて再確認する。
