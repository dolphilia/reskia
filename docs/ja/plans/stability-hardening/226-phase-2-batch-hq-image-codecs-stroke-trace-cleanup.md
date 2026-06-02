# 226 Phase 2 Batch HQ: image codecs stroke trace cleanup

開始時刻: 2026-05-13 18:15:09 JST

## 目的

`225-phase-2-batch-hp-graphics-value-icc-transform-string-valid-paths.md` の「次バッチ候補」から、重複を避けて次の 5 件を順に確認する。対象は `SkImage` async rescale YUV / YUVA、`SkImage` raster / texture conversion factories、`SkCodecs` empty header delegation、`SkStrokeRec` baseline helper row、`SkTraceMemoryDump` no-op row。

## 概算進捗

詳細台帳 `capi-safety-detail-status.csv` は 35 行。今回の更新後は、`valid_path_status` が `covered` または `omitted-with-reason` の行が 32/35 で、概算 91.4%。実装・ヘッダ・smoke・valid path の全条件で見ても 32/35 で、概算 91.4%。

残る `representative-valid-path` は 3 行:

- `image_async_rescale`
- `canvas_atlas_patch_vertices_mesh`
- `value_handle_geometry_helpers`

`codecs_empty_header_decoder_delegation` は direct C API がないため `omitted-with-reason` のまま維持する。

## 変更内容

- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - `SkImage_makeRasterImage` と `SkImage_makeRasterImageWithoutContext` の returned handle について、成功時に borrowed pointer lookup だけでなく画像 dimensions も確認する valid path を追加した。
  - `SkImage_asyncRescaleAndReadPixelsYUV420` / `YUVA420` の valid callback path は raster smoke 環境で fail result になるため、無理に covered 扱いにせず、環境依存の representative 残りとして台帳に明記した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `image_raster_texture_factories` を `covered` valid path に更新した。
  - `image_async_rescale` は recheck evidence を HQ に更新しつつ、YUV / YUVA valid callback の環境依存を notes に残して `representative-valid-path` を維持した。
  - `codecs_empty_header_decoder_delegation` は direct C API なしの意図を再確認し、decoder-specific smoke が実 coverage を持つことを notes に追記した。
  - `stroke_rec_path_paint_helpers` は HK invalid path と HL paint/path integration の evidence を統合し、`covered` valid path に更新した。
  - `trace_memory_dump_noop_helpers` は NULL no-op と test-only concrete forwarding の evidence を統合し、`covered` valid path に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke test_codec_invalid_input_smoke test_annotation_android_codec_invalid_input_smoke test_sampling_unpremul_string_stroke_trace_invalid_input_smoke test_value_transform_string_stroke_trace_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(image_surface|codec|annotation_android_codec|sampling_unpremul_string_stroke_trace|value_transform_string_stroke_trace)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。5/5 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。

## 次バッチ候補

次候補は今回の `SkImage` async/factory、`SkCodecs`、`SkStrokeRec`、`SkTraceMemoryDump` と重複しないように選ぶ。着手時は必ず `rg '<対象API名|detail id>' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` で既存行を確認し、既存 row がない場合は detail row を先に追加する。

- `SkCanvas` drawMesh の C API 制約を調査し、`canvas_atlas_patch_vertices_mesh` の remaining representative 範囲を解消できるか判断する。
- `SkIRect` / `SkISize` / `SkSize` / `SkPoint` の broad geometry row を API 群ごとに分割し、`value_handle_geometry_helpers` の残りを具体化する。
- `SkMesh` / `SkMeshSpecification` invalid input smoke を詳細台帳に登録し、mesh factory / result / spec ownership を重複なく記録する。
- `SkPixelRef` / `SkPixmap` / `SkMask` など pixel storage 系 smoke を詳細台帳に登録し、borrowed storage と rowBytes 規約を整理する。
- `SkTextBlob` / `SkTextBlobRunHandler` / `SkVertices` など buffer-count 系 smoke を詳細台帳に登録し、count と array の安全規約を整理する。
