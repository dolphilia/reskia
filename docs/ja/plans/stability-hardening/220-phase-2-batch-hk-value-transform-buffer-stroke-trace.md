# 220 Phase 2 Batch HK: value transform buffer stroke trace rules

開始時刻: 2026-05-13 12:25:21 JST

## 目的

`219-phase-2-batch-hj-value-icc-pdf-perlin.md` の「次バッチ候補」から、`SkPoint3` / `SkIPoint`、`SkRSXform`、`SkString`、`SkStrokeRec`、`SkTraceMemoryDump` の 5 件を順に確認する。NULL pointer、required output array、borrowed string lifetime、invalid enum、callback/dump no-op の規約を `docs/ja/guides/c-api-safety-guidelines.md` に合わせて固定する。

## 変更内容

- `skia/capi/sk_i_point.cpp` / `skia/capi/sk_i_point.h`
  - getter は NULL receiver で `0`、`isZero` は `true`、`equals` は `false`、setter は no-op にした。
  - static `Make` の caller-owned handle 規約をヘッダに明記した。
- `skia/capi/sk_point_3.cpp` / `skia/capi/sk_point_3.h`
  - getter / length / dot は NULL input で `0`、predicate は `false`、mutation は no-op にした。
  - `makeScale` / `cross` / `CrossProduct` は NULL input で handle `0` を返すようにした。
  - returned handle ownership と invalid handle `0` 規約をヘッダに明記した。
- `skia/capi/sk_rsx_form.cpp` / `skia/capi/sk_rsx_form.h`
  - receiver と output array を required とし、`toQuad` / `toQuadWithSize` / `toTriStrip` は invalid input no-op にした。
  - static factory の caller-owned handle 規約をヘッダに明記した。
- `skia/capi/sk_string.cpp` / `skia/capi/sk_string.h`
  - text / source pointer を required とする constructor、comparison、mutation に NULL guard を追加した。
  - borrowed pointer getter は NULL receiver で `NULL`、search は `-1`、size は `0`、mutation / format helper は no-op にした。
  - `data` / `dataMutable` / `c_str` が borrowed storage であることをヘッダに明記した。
- `skia/capi/sk_stroke_rec.cpp` / `skia/capi/sk_stroke_rec.h`
  - `InitStyle`、`SkPaint::Style`、cap、join を範囲検証し、invalid enum は handle `0` / no-op / `0` にした。
  - NULL receiver / paint / path を guard し、getter は `0` / `false`、mutation は no-op、`applyToPath` は `false` にした。
  - `setResScale` は non-positive / non-finite input を no-op にした。
- `skia/capi/sk_trace_memory_dump.cpp` / `skia/capi/sk_trace_memory_dump.h`
  - dump pointer と required string / discardable object を guard し、invalid input no-op にした。
  - getter は NULL receiver で `0` / `false` にした。
  - dump pointer は borrowed / non-owned で、delete が no-op であることをヘッダに明記した。
- `skia/test/test_value_transform_string_stroke_trace_invalid_input_smoke.cpp`
  - 5候補をまとめて確認する invalid input smoke と代表 valid path を追加した。
- `cmake/reskia/tests.cmake`
  - `test_value_transform_string_stroke_trace_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `point3_ipoint_vector_helpers`
  - `rsxform_matrix_m44_transform_helpers`
  - `string_data_buffer_ownership`
  - `stroke_rec_path_paint_helpers`
  - `trace_memory_dump_noop_helpers`
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_i_point.cpp/h`、`sk_point_3.cpp/h`、`sk_rsx_form.cpp/h`、`sk_string.cpp/h`、`sk_stroke_rec.cpp/h`、`sk_trace_memory_dump.cpp/h` を batch HK の進捗として更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-tests --target test_value_transform_string_stroke_trace_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R c_skia_value_transform_string_stroke_trace_invalid_input_smoke --output-on-failure`
  - 実行済み。成功。1/1 passed。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(value_transform_string_stroke_trace|matrix|m44|data|data_table)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。5/5 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkSamplingOptions` filter / mipmap enum、cubic pointer、constructor helper 系の invalid enum と handle `0` 規約を確認する。
- `SkUnPreMultiply` table / PMColor helper 系の NULL table、color sentinel、output buffer 規約を確認する。
- `SkString` string_view / format / insert family の残りについて、static string_view handle validity と NULL format no-op を追加確認する。
- `SkStrokeRec` の paint / path valid integration を、`SkPaint` / `SkPath` 側の既存 guard と合わせて追加確認する。
- `SkTraceMemoryDump` の concrete implementation 非公開範囲を再調査し、callback / subclass helper が追加されていないか確認する。
