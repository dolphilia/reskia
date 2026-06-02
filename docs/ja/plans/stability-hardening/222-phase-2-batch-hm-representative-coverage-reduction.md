# 222 Phase 2 Batch HM: representative coverage reduction

開始時刻: 2026-05-13 16:40:54 JST

## 目的

`221-phase-2-batch-hl-sampling-unpremul-string-stroke-trace.md` の「次バッチ候補」から、P2 `todo` 完了後の詳細台帳を確認し、`representative-valid-path` / `omitted-with-reason` を減らす。今回は `SkCanvas` image lattice / nine draw、`SkImage` raster / texture conversion factory、`SkPDF` document factory、`SkICC` output buffer helpers を中心に、既存 smoke の valid path を補強・再確認する。

## 変更内容

- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_drawImageLattice` の valid lattice draw を追加した。
  - `SkCanvas_drawImageLatticeWithFilter` の valid lattice draw を追加した。
  - `SkCanvas_drawImageNine` の valid center / dst draw を追加した。
  - テスト側では Skia public `SkCanvas.h` を直接 include せず、C ABI と同じ layout の test-only lattice struct を使って C API 境界だけを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の `SkImage_withDefaultMipmaps`、`SkImage_makeNonTextureImage`、`SkImage_makeRasterImage`、`SkImage_makeRasterImageWithoutContext` valid path を再確認した。
  - factory が環境により `0` を返し得る箇所は、成功時の handle ownership を確認する既存方針を維持した。
- `skia/test/test_value_icc_high_contrast_invalid_input_smoke.cpp`
  - `SkICC_SkICCFloatXYZD50ToGrid16Lab` の valid output buffer path を追加した。
  - `SkICC_SkICCFloatToTable16` の valid output buffer path を追加した。
- `SkPDF` feature-gated smoke
  - `RESKIA_ENABLE_PDF=ON` の別 build directory を configure し、`test_pdf_smoke` を build / ctest した。
  - `SkPDF_MakeDocumentWithoutMetadata` と `SkPDF_MakeDocument` の valid PDF byte generation を確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `canvas_image_rect_lattice_nine_draw` を `covered` valid path に更新した。
  - `image_raster_texture_factories` を batch HM で再確認済みに更新した。
  - `icc_profile_helpers` を `omitted-with-reason` から `representative-valid-path` に進めた。
  - `pdf_document_factories` を feature-gated smoke covered / valid path covered に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-pdf-check -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON -DRESKIA_ENABLE_PDF=ON`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-pdf-check --target test_pdf_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-pdf-check -R c_skia_pdf_smoke --output-on-failure`
  - 実行済み。成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke test_value_icc_high_contrast_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|value_icc_high_contrast|image_surface)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。3/3 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkImage` async rescale callback family の minimal valid callback path を追加し、`image_async_rescale` の `omitted-with-reason` を減らせるか確認する。
- `SkCanvas` surface/context getters の `makeSurface` valid path と borrowed getter lifetime smoke を追加し、`canvas_surface_context_getters` を fully covered へ進める。
- `SkCanvas` raster factory family の `MakeRasterDirect` / `MakeRasterDirectN32` valid borrowed-storage smoke を追加し、rowBytes / storage lifetime を再確認する。
- `SkCanvas` state getter / quickReject family の missing valid path を追加し、`canvas_state_getters` を fully covered へ進める。
- `SkGradientShader` radial / two-point / sweep factory の representative valid path を追加し、linear-only coverage を広げる。
