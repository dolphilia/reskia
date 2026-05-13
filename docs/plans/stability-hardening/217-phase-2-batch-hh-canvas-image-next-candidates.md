# 217 Phase 2 Batch HH: canvas and image next candidate rules

開始時刻: 2026-05-13 11:56:01 JST

## 目的

`216-phase-2-batch-hg-canvas-raster-factory.md` の「次バッチ候補」から、先登録済みの 5 件を順に確認する。`SkCanvas` clip bounds / top-layer pixels / image draw 系と、`SkImage` dimensions / colorSpace / raster factory 系について、caller-owned handle、borrowed lifetime、optional out param、factory failure `0`、draw invalid no-op 規約をまとめて固定する。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_getBaseLayerSize` / `SkCanvas_getDeviceClipBounds` / `SkCanvas_getLocalClipBounds` が NULL canvas で `0`、成功時 caller-owned handle であることを確認した。
  - `SkCanvas_getDeviceClipBoundsInto` / `SkCanvas_getLocalClipBoundsInto` が canvas / bounds required、invalid input false であることを確認した。
  - `SkCanvas_accessTopLayerPixels` が canvas required、info / rowBytes / origin optional、返却 pointer は canvas storage borrowed であることを確認した。
  - `SkCanvas_peekPixels` が canvas / pixmap required、pixmap は canvas pixels を borrow することを確認した。
  - `SkCanvas_drawImageLattice` / `SkCanvas_drawImageNine` / `SkCanvas_drawImageRect*` が required image / geometry / sampling / enum を検証し、invalid input no-op、paint optional であることを確認した。
- `skia/capi/sk_image.cpp`
  - `SkImage_imageInfo` / `SkImage_dimensions` / `SkImage_bounds` が NULL image `0`、成功時 caller-owned handle であることを確認した。
  - `SkImage_width` / `SkImage_height` が NULL image `0` を返すことを確認した。
  - `SkImage_colorSpace` が NULL image または color space なしで NULL、成功時 borrowed pointer を返すことを確認した。
  - `SkImage_refColorSpace` が caller-owned retained handle、color space なしでは `0` であることを確認した。
  - `SkImage_withDefaultMipmaps` / `SkImage_makeNonTextureImage` / `SkImage_makeRasterImage*` が invalid input / factory failure `0`、成功時 caller-owned handle であることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_getBaseLayerSize` の valid returned handle smoke を追加し、caller-owned handle を delete することを固定した。
  - 既存の clip bounds out-param、top-layer borrowed storage、image rect/lattice/nine invalid/valid representative smoke が揃っていることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - `SkImage_imageInfo` / `SkImage_dimensions` / `SkImage_bounds` の valid returned handle smoke と delete を追加した。
  - `SkImage_width` / `SkImage_height` の valid image smoke を追加した。
  - 既存の borrowed `SkImage_colorSpace`、retained `SkImage_refColorSpace`、raster / non-texture factory returned handle smoke が揃っていることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `canvas_clip_bounds_getters`
  - `image_dimensions_color_space_getters`
  - `canvas_top_layer_pixels`
  - `image_raster_texture_factories`
  - `canvas_image_rect_lattice_nine_draw`
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` と `sk_image.cpp/h` を batch HH の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkAlphaType` / `SkColorType` / `SkBlendMode` など enum helper 系の invalid value と string / conversion sentinel 規約をまとめて再確認する。
- `SkCapabilities` getter 系の NULL receiver、borrowed pointer、feature flag 依存の sentinel 規約をまとめて再確認する。
- `SkCodecs` factory / result helper 系の data handle ownership、failure `0`、out param validation 規約をまとめて再確認する。
- `SkGradientShader` factory 系の colors / positions / localMatrix optional、tile mode enum validation、failure `0` 規約をまとめて再確認する。
- `SkGraphics` global init / purge / font cache limit 系の process-wide side effect と invalid numeric input 規約をまとめて再確認する。
