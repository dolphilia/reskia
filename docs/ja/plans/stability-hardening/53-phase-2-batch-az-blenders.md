# 53 Phase 2 Batch AZ: blenders C API safety

作業開始日時: 2026-05-10 09:22:56 JST

## 目的

Phase 2 の次バッチとして、`SkBlenders` C API を fail-safe に寄せる。前バッチの次候補には `SkBlenders` / `SkColorFilters` を挙げていたが、`SkColorFilters` は Batch M で raw array / handle `0` 規約が既に入っているため、今回の実変更は未処理の `SkBlenders` に絞った。

対象:

- `skia/capi/sk_blenders.{h,cpp}`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |

`SkBlenders_Arithmetic` は upstream factory が NULL `sk_sp<SkBlender>` を返した場合、`static_sk_blender_make(nullptr)` に進まず handle `0` を返すようにした。

`SkColorFilters` は再確認のみ。現状は必須 raw pointer に NULL guard があり、optional table pointer は upstream 規約どおり NULL 許可になっている。

## smoke test

`test_blenders_invalid_input_smoke` を追加し、`ctest` に `c_skia_blenders_invalid_input_smoke` として登録した。

確認内容:

- `SkBlenders_Arithmetic` が通常入力で blender handle を返す。
- 返した handle を `static_sk_blender_delete` で解放できる。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_blenders_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_blenders_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_blenders_invalid_input_smoke` build 成功。
- `c_skia_blenders_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 52 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_blenders.{h,cpp}`

再確認のみ:

- `skia/capi/sk_color_filters.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkPathEffect` 周辺の factory handle `0` と optional pointer 規約の再確認
- `SkTextBlob` / builder 周辺の span / output pointer 規約の再確認
- `SkBlender` instance API の refcount / flattenable 規約
