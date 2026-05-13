# 223 Phase 2 Batch HN: async canvas gradient valid paths

開始時刻: 2026-05-13 17:19:36 JST

## 目的

`222-phase-2-batch-hm-representative-coverage-reduction.md` の「次バッチ候補」から、重複を避けて不足している valid path だけを補強する。対象は `SkImage` async rescale callback、`SkCanvas` surface/context getters、`SkCanvas` raster factory、`SkCanvas` state getter / quickReject、`SkGradientShader` radial / two-point / sweep factory の 5 件。

## 変更内容

- `SkImage` async rescale callback family
  - 既存の `test_phase_d_async_read_smoke.cpp` が `SkImage_asyncRescaleAndReadPixels` の minimal valid callback path を既に持っているため、新規実装は追加せず、詳細台帳を重複なしで更新した。
  - YUV / YUVA valid path は環境依存が強いため、今回の fully covered ではなく representative valid path とした。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - surface-backed canvas で `SkCanvas_getSurface` の borrowed pointer valid path を追加した。
  - surface-backed canvas で `SkCanvas_makeSurface` の caller-owned returned surface handle valid path を追加した。
  - `SkCanvas_MakeRasterDirect` / `SkCanvas_MakeRasterDirectN32` の valid borrowed-storage path を追加した。
  - `SkCanvas_quickRejectRect` / `SkCanvas_quickReject` の valid input path を追加した。戻り値は device / clip state に依存するため、結果値には固定期待を置かず、valid call boundary を確認する。
- `skia/test/test_shader_invalid_input_smoke.cpp`
  - `SkGradientShader_MakeRadial` の representative valid returned handle path を追加した。
  - `SkGradientShader_MakeTwoPointConical` の representative valid returned handle path を追加した。
  - `SkGradientShader_MakeSweep` の representative valid returned handle path を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `image_async_rescale` を `omitted-with-reason` から `representative-valid-path` に更新した。
  - `canvas_surface_context_getters`、`canvas_raster_factories`、`canvas_state_getters`、`gradient_shader_factories` を `covered` valid path に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke test_shader_invalid_input_smoke test_phase_d_async_read_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|shader)_invalid_input_smoke|c_skia_phase_d_async_read_smoke' --output-on-failure`
  - 実行済み。成功。3/3 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkImage` texture/context getters の CPU-raster representative valid path と nullable context behavior を再確認し、`image_texture_context_getters` を fully covered に近づける。
- `SkImage` ref / unique / asLegacyBitmap valid output path を追加し、`image_ref_legacy_bitmap` を fully covered に進める。
- `SkCanvas` pixel read/write family の writePixels valid round-trip と rowBytes lifetime を追加し、`canvas_read_write_pixels` を fully covered に進める。
- `SkCanvas` atlas / patch / vertices / mesh draw family の representative valid path を追加し、`canvas_atlas_patch_vertices_mesh` を fully covered に進める。
- `SkCapabilities` refcount / RasterBackend borrowed const handle behavior を再確認し、`capabilities_null_raster_backend` を fully covered に進める。
