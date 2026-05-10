# 57 Phase 2 Batch BD: path builder C API safety

作業開始日時: 2026-05-10 09:40:12 JST

## 目的

Phase 2 の次バッチとして、`SkPathBuilder` の builder pointer / output path 規約を整理する。

対象:

- `skia/capi/sk_path_builder.{h,cpp}`
- `skia/test/test_path_builder_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| builder pointer | `NULL` |
| handle | `0` |
| fill type | `0` |
| void | no-op |

`newFromPath` / `newCopy` は入力 pointer を必須にし、NULL 入力では `NULL` を返す。

`delete` / `incReserve` / `incReservePoints` は NULL builder で no-op にした。

`fillType` / `computeBounds` / `snapshot` / `detach` は NULL builder を guard し、`0` を返す。

builder を変更して `SkPathBuilder *` を返す API は、NULL builder では `NULL` を返す。NULL `pts` / `list` / `rect` / `rrect` / `path` などの required pointer は no-op とし、既存 builder pointer を返す。

`polylineTo` / `addPolygon` は NULL `pts` または `count <= 0` を no-op にした。

## smoke test

`test_path_builder_invalid_input_smoke` を追加し、`ctest` に `c_skia_path_builder_invalid_input_smoke` として登録した。

確認内容:

- NULL builder の API が no-op / `NULL` / handle `0` になる。
- required pointer が NULL の mutator は no-op として同じ builder を返す。
- `moveToPoint` / `lineToPoint` / `computeBounds` / `snapshot` / `newFromPath` / `newCopy` / `detach` の正常系が動作する。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_path_builder_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_path_builder_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_path_builder_invalid_input_smoke` build 成功。
- `c_skia_path_builder_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 54 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_path_builder.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkTiledImageUtils` の required image / rect / sampling pointer 規約
- `SkRuntimeEffect` / runtime builders の factory handle 0 / child pointer 規約
- `SkSurfaceProps` / `SkSurface` 周辺の pointer / handle 規約
