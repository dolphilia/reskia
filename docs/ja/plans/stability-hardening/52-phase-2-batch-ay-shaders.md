# 52 Phase 2 Batch AY: shader C API safety

作業開始日時: 2026-05-10 09:17:57 JST

## 目的

Phase 2 の次バッチとして、`SkShader` / `SkShaders` C API を fail-safe に寄せる。shader API は raw receiver、flattenable factory、serialize 出力、factory の optional handle と必須 pointer を混在して扱うため、NULL pointer を upstream の dereference に渡さない。

対象:

- `skia/capi/sk_shader.{h,cpp}`
- `skia/capi/sk_shaders.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| enum / `size_t` | `0` |
| pointer | `NULL` |
| handle | `0` |
| release/ref/unref/flatten/register | no-op |

`SkShader` instance method は NULL receiver を no-op / `false` / `0` / `NULL` に統一した。`isAImage` の `localMatrix` / `xy`、serialize procs は upstream 規約どおり NULL 許可を維持した。

`makeWithLocalMatrix` の `matrix`、`flatten` の `buffer` は必須にした。`makeWithColorFilter` の `color_filter` と `makeWithWorkingColorSpace` の `color_space` は handle `0` を upstream の NULL `sk_sp` として渡す。

`NameToFactory` / `FactoryToName` / `Register` は NULL name や invalid factory を upstream に渡さない。`Deserialize` は NULL data または zero length で handle `0` を返す。

`SkShaders` factory は `static_sk_shader_make(nullptr)` に進まないようにし、factory が NULL `sk_sp` を返した場合は handle `0` を返す。`ColorWithColor4fAndColorSpace` の `color4f` と `CoordClamp` の `subset` は必須にした。`Blend` / `BlendWithBlender` の shader handle `0` は upstream に渡され、結果 NULL は handle `0` になる。

## smoke test

`test_shader_invalid_input_smoke` を追加し、`ctest` に `c_skia_shader_invalid_input_smoke` として登録した。

確認内容:

- NULL receiver の `SkShader` instance method が fail-safe な戻り値になる。
- NULL name / invalid factory / NULL deserialize data を static API が upstream に渡さない。
- `SkShaders_Empty` / `SkShaders_Color` が handle を返す。
- `SkShaders_ColorWithColor4fAndColorSpace` / `SkShaders_CoordClamp` の必須 pointer NULL が handle `0` になる。
- `SkShaders_Blend` / `SkShaders_BlendWithBlender` の NULL shader 結果が handle `0` になる。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_shader_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_shader_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_shader_invalid_input_smoke` build 成功。
- `c_skia_shader_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 51 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_shader.{h,cpp}`
- `skia/capi/sk_shaders.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkBlenders` / `SkColorFilters` の factory input pointer 規約
- `SkPathEffect` 周辺の factory handle `0` と optional pointer 規約の再確認
- `SkTextBlob` / builder 周辺の span / output pointer 規約の再確認
