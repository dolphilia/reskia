# 61 Phase 2 Batch BH: images C API safety recheck

作業開始日時: 2026-05-10 10:02:23 JST

## 目的

Phase 2 の次バッチ候補を確認した。`SkTextUtils` は現状 `skia/capi` に C API ラッパーがなく、`SkDrawable` / `SkPicture` / `SkPictureRecorder` は Batch AD / AE で処理済みだったため、候補に残っていた `SkImages` の picture / dimensions / props handle 規約を再確認して補強した。

対象:

- `skia/capi/sk_images.{h,cpp}`
- `skia/test/test_images_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| status | `RESKIA_STATUS_INVALID_ARGUMENT` / `RESKIA_STATUS_NOT_FOUND` |

`SkImages_RasterFromBitmap` / `RasterFromPixmapCopy` / `RasterFromPixmap` / `RasterFromData` は required pointer を guard し、NULL 入力では image handle `0` を返す。

`RasterFromCompressedTextureData` / `DeferredFromEncodedData` / `DeferredFromGenerator` は Skia から NULL `sk_sp<SkImage>` が返った場合に handle `0` を返す。

`DeferredFromPicture` / `DeferredFromPictureWithoutProps` は `dimensions` を必須にし、NULL では handle `0` を返す。`matrix` / `paint` は NULL 許可を維持した。`picture` handle `0` と `props` handle `0` は既存どおり empty / default 扱いで Skia に渡し、生成不能なら handle `0` を返す。

`SkImages_MakeWithFilter` は `out_image` が非 NULL の場合、invalid argument / not found の失敗時にも `*out_image = 0` にする。

## smoke test

`test_images_invalid_input_smoke` を追加し、`ctest` に `c_skia_images_invalid_input_smoke` として登録した。

確認内容:

- required pointer NULL と invalid handle が image handle `0` になる。
- `DeferredFromPicture*` の NULL dimensions が handle `0` になる。
- `MakeWithFilter` の invalid argument が status を返し、non-NULL `out_image` を `0` に戻す。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_images_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_images_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_images_invalid_input_smoke` build 成功。
- `c_skia_images_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 58 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` を更新:

- `skia/capi/sk_images.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkCanvas` draw picture / drawable / surface-related 再確認
- `SkFont` callback / glyph path 周辺の borrowed pointer 規約
- `SkMeshSpecification` の runtime child / uniform pointer 規約
