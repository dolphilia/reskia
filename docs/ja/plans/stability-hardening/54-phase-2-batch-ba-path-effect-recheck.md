# 54 Phase 2 Batch BA: path effect C API recheck

作業開始日時: 2026-05-10 09:25:21 JST

## 目的

Phase 2 の次バッチとして、`SkPathEffect` 周辺の factory handle `0` と optional pointer 規約を再確認する。PathEffect 系 factory は Batch L で処理済みだが、base `SkPathEffect` の serialize / factory helper に残る境界条件を補強する。

対象:

- `skia/capi/sk_path_effect.{h,cpp}`
- `skia/test/test_path_effect_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| pointer | `NULL` |
| handle | `0` |
| `size_t` | `0` |

`SkPathEffect_serialize` は upstream が NULL `SkData` を返した場合、`static_sk_data_make(nullptr)` に進まず handle `0` を返すようにした。

`SkPathEffect_serializeToMemory` は `memory == NULL && memory_size != 0` を `0` で拒否する。`procs` は upstream 規約どおり NULL 許可を維持した。

`SkPathEffect_Deserialize` は NULL data に加えて zero size も handle `0` にした。

`SkPathEffect_FactoryToName` / `SkPathEffect_Register` は handle `0` だけでなく invalid factory handle から得られる NULL factory も upstream に渡さない。

## smoke test

既存の `test_path_effect_invalid_input_smoke` を拡張した。

追加確認:

- NULL path effect かつ nonzero size の `serializeToMemory` が `0` になる。
- invalid factory handle の `FactoryToName` が `NULL` になる。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_path_effect_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_path_effect_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- test configure 成功。
- `test_path_effect_invalid_input_smoke` build 成功。
- `c_skia_path_effect_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- Phase 2 invalid-input smoke 52 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

更新:

- `skia/capi/sk_path_effect.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkTextBlob` / builder 周辺の span / output pointer 規約の再確認
- `SkBlender` instance API の refcount / flattenable 規約
- `SkPathBuilder` の builder pointer / output path 規約
