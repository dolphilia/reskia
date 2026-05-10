# 51 Phase 2 Batch AX: image filter C API safety

作業開始日時: 2026-05-10 09:09:14 JST

## 目的

Phase 2 の次バッチとして、`SkImageFilter` / `SkImageFilters` C API を fail-safe に寄せる。image filter API は raw object pointer、handle table の `sk_sp`、factory の optional crop rect、必須参照引数を混在して扱うため、NULL pointer を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_image_filter.{h,cpp}`
- `skia/capi/sk_image_filters.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| `int` / `size_t` / enum | `0` |
| pointer | `NULL` |
| handle | `0` |
| release/ref/unref/flatten/register | no-op |

`SkImageFilter` instance method は NULL receiver を no-op / `false` / `0` / `NULL` に統一した。`filterBounds` の `src` / `ctm`、`computeFastBounds` の `bounds`、`makeWithLocalMatrix` の `matrix`、`flatten` の `buffer` は必須にした。`inputRect`、color filter output pointer、serial/deserial procs は upstream 規約どおり NULL 許可を維持した。

`SkImageFilter_Deserialize` は NULL data または zero size で handle `0` を返す。`NameToFactory` / `FactoryToName` / `Register` は NULL name や invalid factory を upstream に渡さない。

`SkImageFilters` factory は `cropRect` を optional として扱い、NULL の場合は empty `SkImageFilters::CropRect` を渡す。input image filter handle `0` は upstream 規約どおり implicit source image として維持した。factory が NULL `sk_sp` を返した場合は handle table に登録せず handle `0` を返す。

必須参照引数は NULL で handle `0` を返すようにした。対象は rect / sampling / kernel descriptors / matrix / runtime shader builder / runtime shader arrays / lighting point / tile rect など。

## smoke test

`test_image_filter_invalid_input_smoke` を追加し、`ctest` に `c_skia_image_filter_invalid_input_smoke` として登録した。

確認内容:

- NULL receiver の `SkImageFilter` instance method が fail-safe な戻り値になる。
- NULL data / name / factory を static API が upstream に渡さない。
- `SkImageFilters_Empty` が handle を返す。
- optional `cropRect == NULL` の Blur / DropShadow が handle を返す。
- 必須 pointer が NULL の factory は handle `0` を返す。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_image_filter_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_image_filter_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_image_filter_invalid_input_smoke` build 成功。
- `c_skia_image_filter_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 50 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_image_filter.{h,cpp}`
- `skia/capi/sk_image_filters.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkShader` / `SkShaders` の factory optional pointer 規約
- `SkBlenders` / `SkColorFilters` の factory input pointer 規約
- `SkPathEffect` 周辺の factory handle `0` と optional pointer 規約の再確認
