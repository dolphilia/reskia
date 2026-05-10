# 58 Phase 2 Batch BE: tiled image utils C API safety

作業開始日時: 2026-05-10 09:45:43 JST

## 目的

Phase 2 の次バッチとして、`SkTiledImageUtils` の required image / rect / sampling pointer 規約を整理する。

対象:

- `skia/capi/sk_tiled_image_utils.{h,cpp}`
- `skia/test/test_tiled_image_utils_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| void | no-op |

`DrawImageRect` 系は `canvas` / `image` / `src` / `dst` / `sampling` を必須にし、NULL 入力では no-op にした。`paint` は upstream と同じく NULL 許可を維持した。

`DrawImageRectWithDst` 系は `canvas` / `image` / `dst` / `sampling` を必須にし、NULL 入力では no-op にした。

`DrawImage` 系は `canvas` / `image` / `sampling` を必須にし、NULL 入力では no-op にした。

`sk_sp<SkImage>` 版は C API 側の `image` pointer を必須にした。`sk_sp` の中身が NULL の場合は upstream inline の image NULL no-op に任せる。

`GetImageKeyValues` は upstream が NULL image / NULL keyValues を guard しているため、そのまま委譲する。NULL image かつ non-NULL keyValues では 6 要素が 0 で埋まる。

## smoke test

`test_tiled_image_utils_invalid_input_smoke` を追加し、`ctest` に `c_skia_tiled_image_utils_invalid_input_smoke` として登録した。

確認内容:

- Draw 系 API の NULL 入力が no-op になる。
- `GetImageKeyValues(nullptr, nullptr)` が no-op になる。
- `GetImageKeyValues(nullptr, keyValues)` が 6 要素を 0 で埋める。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_tiled_image_utils_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_tiled_image_utils_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|tiled_image_utils|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_tiled_image_utils_invalid_input_smoke` build 成功。
- `c_skia_tiled_image_utils_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 55 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_tiled_image_utils.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkRuntimeEffect` / runtime builders の factory handle 0 / child pointer 規約
- `SkSurfaceProps` / `SkSurface` 周辺の pointer / handle 規約
- `SkTextUtils` の canvas / font / text pointer 規約
