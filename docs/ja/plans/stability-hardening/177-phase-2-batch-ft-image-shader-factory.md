# 177 Phase 2 Batch FT: image shader factory rules

開始時刻: 2026-05-13 09:55:22 JST

## 目的

`176-phase-2-batch-fs-canvas-picture-draw.md` の「次バッチ候補」から、`SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。shader factory は `image` / `sampling` required、tile mode は valid enum、localMatrix は API ごとの optional / required に従い、成功時は caller-owned shader handle を返す。

## 変更内容

- `skia/capi/sk_image.cpp`
  - shader / raw shader factory 系が `valid_tile_mode`、required `sampling`、required `lm` を検証し、factory failure を `0` に正規化していることを確認した。
- `skia/capi/sk_image.h`
  - 既存コメントが returned shader ownership、factory failure `0`、localMatrix optional / required を明記していることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image、NULL sampling、invalid tile mode、NULL required matrix、valid returned shader handle smoke を確認した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。
- `SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。
- `SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。
- `SkImage` legacy bitmap / lazy generated / mipmap getter 系の output pointer と bool/numeric failure 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique 系の NULL no-op と bool failure 規約をまとめて再確認する。
