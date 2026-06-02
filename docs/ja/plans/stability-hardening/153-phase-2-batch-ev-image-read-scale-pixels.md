# 153 Phase 2 Batch EV: image read and scale pixels rules

開始時刻: 2026-05-13 09:11:03 JST

## 目的

`152-phase-2-batch-eu-canvas-draw-points.md` の「次バッチ候補」から、`SkImage` scalePixels / readPixels 系の caching hint enum と pixmap / rowBytes 規約をまとめて再確認する。pixmap / rowBytes guard は既存規約を維持し、`SkImage::CachingHint` の範囲外値を false にする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `valid_caching_hint` helper を追加した。
  - `SkImage_readPixels` / `SkImage_readPixelsWithContextPixmap` / `SkImage_readPixelsWithImageInfo` / `SkImage_readPixelsWithPixmap` / `SkImage_scalePixels` に caching hint guard を追加した。
- `skia/capi/sk_image.h`
  - readPixels / scalePixels 系に valid `SkImage::CachingHint` required を明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - readPixels / pixmap read / scalePixels の invalid caching hint が false を返す smoke を追加した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_image_surface_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw bitmap / pixmap 系の required image geometry と sampling optional/required 規約をまとめて再確認する。
- `SkCanvas` readPixels / writePixels 系の rowBytes と storage lifetime 規約をまとめて再確認する。
- `SkCanvas` get clip bounds / quickReject 系の out handle / borrowed geometry 規約をまとめて再確認する。
- `SkCanvas` draw path / region / paint 系の required pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeRasterImage 系の caching hint enum と returned handle 規約をまとめて再確認する。
