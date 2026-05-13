# 158 Phase 2 Batch FA: image makeRasterImage rules

開始時刻: 2026-05-13 09:25:00 JST

## 目的

`157-phase-2-batch-ez-canvas-draw-path-region-paint.md` の「次バッチ候補」から、`SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。`cachingHint` は既知値のみ許容し、invalid input または factory failure は `0` に正規化する。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_makeRasterImage` / `SkImage_makeRasterImageWithoutContext` に `cachingHint` 範囲検証を追加した。
- `skia/capi/sk_image.h`
  - 両 API の `cachingHint` required enum 規約と failure `0` を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - makeRasterImage 系で範囲外 `cachingHint` が `0` を返す smoke を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` を Batch FA に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` makeSurface / MakeRasterDirect 系の returned handle ownership と borrowed storage lifetime 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の returned handle ownership と failure 0 規約をまとめて再確認する。
- `SkCanvas` save / restore / matrix mutation 系の NULL canvas no-op と numeric return 規約をまとめて再確認する。
- `SkCanvas` draw rect / rrect / oval / arc 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。
