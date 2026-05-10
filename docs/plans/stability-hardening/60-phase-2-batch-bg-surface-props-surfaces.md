# 60 Phase 2 Batch BG: surface props and surfaces C API safety

作業開始日時: 2026-05-10 09:56:22 JST

## 目的

Phase 2 の次バッチとして、`SkSurfaceProps` / `SkSurfaces` 周辺の pointer / handle 規約を整理する。`SkSurface` 本体は Batch A で処理済みのため、未処理の props と factory API を対象にした。

対象:

- `skia/capi/sk_surface_props.{h,cpp}`
- `skia/capi/sk_surfaces.{h,cpp}`
- `skia/test/test_surface_props_surfaces_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| pointer | `NULL` |
| bool | `false` |
| integer / enum | `0` |
| void | no-op |

`SkSurfaceProps_newCopy` は NULL props で `NULL` を返す。`delete` は NULL で no-op にした。

`cloneWithPixelGeometry` / `flags` / `pixelGeometry` / `isUseDeviceIndependentFonts` / `isAlwaysDither` は NULL receiver を guard し、上記規約の戻り値にした。

`SkSurfaces` factory は `SkSurfaceProps *` を Skia と同じく NULL 許可にしたまま、required pointer を明示した。

required pointer:

- `Raster` / `RasterWithoutRowBytes`: `imageInfo`
- `WrapPixels`: `imageInfo` / `pixels`
- `WrapPixelsWithPixmap`: `pm`
- `WrapPixelsWithReleaseProcAndContext`: `imageInfo` / `pixels`

factory の `sk_sp<SkSurface>` 結果が NULL の場合は handle `0` を返す。

## smoke test

`test_surface_props_surfaces_invalid_input_smoke` を追加し、`ctest` に `c_skia_surface_props_surfaces_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkSurfaceProps` receiver が no-op / `NULL` / handle `0` / `false` / `0` になる。
- `SkSurfaceProps_new` / `newCopy` / `cloneWithPixelGeometry` の正常系が動作する。
- `SkSurfaces` factory の required pointer NULL が handle `0` になる。
- `SkSurfaces_Null(1, 1)` が valid handle を返す。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_surface_props_surfaces_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_surface_props_surfaces_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_surface_props_surfaces_invalid_input_smoke` build 成功。
- `c_skia_surface_props_surfaces_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 57 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_surface_props.{h,cpp}`
- `skia/capi/sk_surfaces.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkTextUtils` の canvas / font / text pointer 規約
- `SkDrawable` / picture callback 周辺の borrowed pointer 規約
- `SkImages` の picture / dimensions / props handle 規約
