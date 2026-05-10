# 62 Phase 2 Batch BI: canvas C API safety recheck

作業開始日時: 2026-05-10 10:06:16 JST

## 目的

Phase 2 の次バッチとして、`SkCanvas` draw picture / drawable / surface-related API を再確認する。大半は既存 Batch A 系で guard 済みだったため、残っていた invalid picture handle と `makeSurface` 生成結果の扱いを補強した。

対象:

- `skia/capi/sk_canvas.{h,cpp}`
- `skia/test/test_canvas_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| void | no-op |

`SkCanvas_drawPicture` / `SkCanvas_drawPictureHandleWithMatrixPaint` は picture handle `0` だけでなく、存在しない handle も no-op にした。

`SkCanvas_makeSurface` は NULL canvas / NULL info で handle `0` を返す既存規約を維持しつつ、Skia から NULL `sk_sp<SkSurface>` が返った場合も handle `0` を返すようにした。

`drawDrawable` / `drawDrawableAt` / pointer picture 系は既存 guard のまま、smoke で明示確認した。

## smoke test

`test_canvas_invalid_input_smoke` を拡張した。

確認内容:

- NULL canvas の draw drawable / draw picture / makeSurface が no-op / handle `0` になる。
- valid canvas でも NULL drawable / pointer picture が no-op になる。
- invalid picture handle が no-op になる。
- NULL info の `makeSurface` が handle `0` になる。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_canvas_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_canvas_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 58 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` を更新:

- `skia/capi/sk_canvas.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` callback / glyph path 周辺の borrowed pointer 規約
- `SkMeshSpecification` の runtime child / uniform pointer 規約
- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約
