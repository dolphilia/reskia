# 227 Phase 2 Batch HR: mesh geometry pixel text ledger

開始時刻: 2026-05-14 00:05:43 JST

## 目的

`226-phase-2-batch-hq-image-codecs-stroke-trace-cleanup.md` の「次バッチ候補」から、重複を避けて次の 5 件を順に確認する。対象は `SkCanvas` drawMesh 制約、geometry broad row の分割、`SkMesh` / `SkMeshSpecification` 詳細台帳登録、pixel storage 系 smoke の詳細台帳登録、text blob / vertices 系 smoke の詳細台帳登録。

## 概算進捗

詳細台帳 `capi-safety-detail-status.csv` は今回の新規 row 追加後で 41 行。`valid_path_status` が `covered` または `omitted-with-reason` の行は 38/41 で、概算 92.7%。

残る `representative-valid-path` は 3 行:

- `image_async_rescale`
- `canvas_atlas_patch_vertices_mesh`
- `mesh_specification_factory_guards`

`canvas_atlas_patch_vertices_mesh` と `mesh_specification_factory_guards` はどちらも `SkMesh::Result` から `reskia_mesh_t *` を得る C API がないことが制約として残る。

## 変更内容

- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `canvas_atlas_patch_vertices_mesh` を HR evidence に更新し、`drawMesh` がまだ representative に残る理由を再確認して記録した。
  - `value_handle_geometry_helpers` を broad row から具体 row へ分割し、covered に更新した。
  - `geometry_irect_helpers`、`geometry_size_helpers`、`geometry_point_helpers` を追加した。
  - `mesh_specification_factory_guards` を追加した。NULL guard と vertex/index buffer factory valid path は coverage 済みだが、successful mesh/spec result unwrapping は C API 制約として representative に残した。
  - `pixel_storage_mask_pixmap_helpers` を追加し、`SkPixelRef` / `SkPixmap` / `SkMask` / `SkMaskBuilder` の rowBytes / borrowed storage evidence を記録した。
  - `text_blob_vertices_buffer_helpers` を追加し、`SkTextBlob` / builder / run handler / `SkVertices` の count-array / returned handle evidence を記録した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke test_value_icc_high_contrast_invalid_input_smoke test_mesh_invalid_input_smoke test_mesh_specification_invalid_input_smoke test_pixel_ref_invalid_input_smoke test_pixmap_invalid_input_smoke test_mask_invalid_input_smoke test_text_blob_invalid_input_smoke test_vertices_invalid_input_smoke -j 8`
  - 実行済み。成功。
  - `test_text_blob_run_handler_invalid_input_smoke` は `RESKIA_ENABLE_SKPARAGRAPH` gated のため、この prebuilt test build では target 未生成。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|value_icc_high_contrast|mesh|mesh_specification|pixel_ref|pixmap|mask|text_blob|vertices)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。9/9 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。

## 次バッチ候補

次候補は今回の mesh、geometry、pixel storage、text blob / vertices 登録作業と重複しないように選ぶ。着手時は必ず `rg '<対象API名|detail id>' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` で既存行を確認し、既存 row がない場合は detail row を先に追加する。

- `SkReadBuffer` / `SkWriteBuffer` smoke を詳細台帳に登録し、serialization buffer の borrowed / consumed / bounds 規約を整理する。
- `SkRegion` / `SkPath` / `SkPathBuilder` smoke を詳細台帳に登録し、path geometry mutation と returned handle ownership を整理する。
- `SkPictureRecorder` / `SkDrawable` / `SkOverdrawCanvas` smoke を詳細台帳に登録し、recording canvas と borrowed pointer lifetime を整理する。
- `SkTypeface` / `SkFont` / `SkFontMgr` 周辺 smoke を詳細台帳に登録し、font object ownership と platform-gated behavior を整理する。
- `SkRuntimeEffect` / runtime shader builder smoke を詳細台帳に登録し、data handle 0 と child array count の規約を整理する。
