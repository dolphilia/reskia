# 221 Phase 2 Batch HL: sampling unpremul string stroke trace rules

開始時刻: 2026-05-13 12:47:19 JST

## 目的

`220-phase-2-batch-hk-value-transform-buffer-stroke-trace.md` の「次バッチ候補」から、`SkSamplingOptions`、`SkUnPreMultiply`、`SkString` string_view / format family、`SkStrokeRec` paint / path integration、`SkTraceMemoryDump` concrete forwarding の 5 件を順に確認する。未完了 P2 の `SkSamplingOptions` / `SkUnPreMultiply` を完了させつつ、前回代表 coverage に残した string_view handle、valid paint/path、concrete dump forwarding を補強する。

## 変更内容

- `skia/capi/sk_sampling_options.cpp` / `skia/capi/sk_sampling_options.h`
  - `newCopy(nullptr)`、`new_5(nullptr)` を `NULL` にした。
  - filter / mipmap enum を範囲検証し、invalid enum は `NULL` を返すようにした。
  - `isAniso(nullptr)` を `false` にした。
  - `Aniso` は Skia upstream の clamp 挙動を維持し、caller-owned handle 規約をヘッダに明記した。
- `skia/capi/sk_un_pre_multiply.cpp` / `skia/capi/sk_un_pre_multiply.h`
  - `GetScale(alpha)` は `alpha > 255` で `0` を返すようにした。
  - `ApplyScale(scale, component)` は `component > 255` で `0` を返すようにした。
  - `GetScaleTable` の返却値が borrowed static 256-entry table であることをヘッダに明記した。
- `skia/capi/sk_string.cpp` / `skia/capi/sk_string.h`
  - `new_7`、`setStringView`、`insertStringView`、`appendStringView`、`prependStringView` で static string_view handle validity を確認するようにした。
  - invalid string_view handle は constructor では `NULL`、mutation では no-op にした。
- `skia/test/test_sampling_unpremul_string_stroke_trace_invalid_input_smoke.cpp`
  - `SkSamplingOptions` invalid enum / null pointer / representative valid path、`SkUnPreMultiply` borrowed table / U8 sentinel、`SkString` invalid and valid string_view、`SkStrokeRec` valid paint/path integration、`SkTraceMemoryDump` concrete subclass forwarding をまとめて確認する smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `test_sampling_unpremul_string_stroke_trace_invalid_input_smoke` を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - `sampling_options_constructor_rules`
  - `unpremultiply_static_helpers`
  - `string_view_format_mutation_helpers`
  - `stroke_rec_paint_path_valid_integration`
  - `trace_memory_dump_concrete_forwarding`
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_sampling_options.cpp/h`、`sk_un_pre_multiply.cpp/h` を完了にした。
  - 追加補強として `sk_string.cpp/h`、`sk_stroke_rec.cpp/h`、`sk_trace_memory_dump.cpp/h` の batch を HL に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-tests --target test_sampling_unpremul_string_stroke_trace_invalid_input_smoke -j 8`
  - 実行済み。成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R c_skia_sampling_unpremul_string_stroke_trace_invalid_input_smoke --output-on-failure`
  - 実行済み。成功。1/1 passed。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(sampling_unpremul_string_stroke_trace|value_transform_string_stroke_trace|image_surface|canvas)_invalid_input_smoke' --output-on-failure`
  - 実行済み。成功。4/4 passed。
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 実行済み。成功。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 実行済み。成功。`Built target reskia`。
- `git diff --check`
  - 実行済み。成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- P2 `todo` が空になったため、`docs/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv` の `representative-valid-path` / `partial` 行を優先して、代表 coverage から fully covered へ進める候補を抽出する。
- `SkCanvas` image draw family の lattice / nine / src-dst overload valid path を、既存 image rect smoke から追加拡張する。
- `SkImage` raster / texture conversion factory の context optional / factory failure / representative valid path を追加拡張する。
- `SkPDF` document factory の feature-gated 範囲を再調査し、現在の build feature で smoke 可能な最小 valid path があるか確認する。
- `SkICC` valid ICC construction path または output buffer helpers の代表 valid path を追加し、`omitted-with-reason` を減らせるか確認する。
