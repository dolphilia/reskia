# 59 Phase 2 Batch BF: runtime effect C API safety

作業開始日時: 2026-05-10 09:49:04 JST

## 目的

Phase 2 の次バッチとして、`SkRuntimeEffect` / runtime builders の factory handle `0` と child pointer 規約を整理する。

対象:

- `skia/capi/sk_runtime_effect.{h,cpp}`
- `skia/capi/sk_runtime_effect_builder.{h,cpp}`
- `skia/capi/sk_runtime_shader_builder.{h,cpp}`
- `skia/capi/sk_runtime_color_filter_builder.{h,cpp}`
- `skia/capi/sk_runtime_blend_builder.{h,cpp}`
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| pointer | `NULL` |
| bool | `false` |
| size_t | `0` |
| void | no-op |

`SkRuntimeEffect` instance API は NULL receiver を guard し、生成 API は Skia から NULL `sk_sp` が返った場合に handle `0` を返す。

`makeShader` / `makeColorFilterWithChildren` は `childCount > 0` かつ children NULL を handle `0` にした。`localMatrix` と child pointer handle `0` は NULL / empty child list として許可する。

`MakeFor*` の options 付き overload は options を必須にし、NULL options では result handle `0` を返す。default overload は従来通り options なしで呼ぶ。

`MakeTraced` は `traceCoord` を必須にし、NULL では traced shader handle `0` を返す。

runtime shader / color filter / blend builder は invalid runtime effect handle `0` から builder を作らず `NULL` を返す。NULL builder receiver は `NULL` / handle `0` / no-op に統一した。

`SkRuntimeEffectBuilder` 共通 accessor も NULL builder receiver を guard し、handle `0` または `NULL` を返す。

## smoke test

`test_runtime_effect_invalid_input_smoke` を追加し、`ctest` に `c_skia_runtime_effect_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkRuntimeEffect` receiver の API が no-op / `0` / `NULL` / `false` になる。
- options 付き static factory の NULL options が result handle `0` になる。
- `MakeTraced` の NULL trace coord が handle `0` になる。
- runtime shader / color filter / blend builder が invalid effect handle `0` から `NULL` を返す。
- 各 builder の NULL receiver accessor / maker が handle `0` または `NULL` になる。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_runtime_effect_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_runtime_effect_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_runtime_effect_invalid_input_smoke` build 成功。
- `c_skia_runtime_effect_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 56 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_runtime_effect.{h,cpp}`
- `skia/capi/sk_runtime_effect_builder.{h,cpp}`
- `skia/capi/sk_runtime_shader_builder.{h,cpp}`
- `skia/capi/sk_runtime_color_filter_builder.{h,cpp}`
- `skia/capi/sk_runtime_blend_builder.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkSurfaceProps` / `SkSurface` 周辺の pointer / handle 規約
- `SkTextUtils` の canvas / font / text pointer 規約
- `SkDrawable` / picture callback 周辺の borrowed pointer 規約
