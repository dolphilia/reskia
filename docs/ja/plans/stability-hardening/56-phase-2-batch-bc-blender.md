# 56 Phase 2 Batch BC: blender C API safety

作業開始日時: 2026-05-10 09:34:58 JST

## 目的

Phase 2 の次バッチとして、`SkBlender` instance API の refcount / flattenable 規約を整理する。

対象:

- `skia/capi/sk_blender.{h,cpp}`
- `skia/test/test_blender_invalid_input_smoke.cpp`

## 実装変更

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle | `0` |
| pointer | `NULL` |
| bool | `false` |
| size_t | `0` |
| void | no-op |

`SkBlender_release` / `ref` / `unref` は NULL blender で no-op にした。

`getFactory` / `getTypeName` / `getFlattenableType` / `serialize` / `serializeToMemory` / `unique` は NULL receiver を guard し、戻り値を上記規約へ統一した。

`flatten` は blender と `write_buffer` を必須にし、NULL 入力では no-op にした。

`serialize` / `serializeToMemory` の `serial_procs` は NULL 許可を維持した。`serializeToMemory` は NULL memory かつ nonzero size を `0` にして、Skia 側へ不正な出力バッファを渡さない。

static API では、`Mode` の NULL 結果を handle `0` に変換する。`NameToFactory` / `FactoryToName` / `Register` は NULL name、invalid factory、missing factory を guard する。`Deserialize` は NULL data または length `0` を handle `0` にし、復元不能な結果も handle `0` にする。

## smoke test

`test_blender_invalid_input_smoke` を追加し、`ctest` に `c_skia_blender_invalid_input_smoke` として登録した。

確認内容:

- NULL receiver の API が no-op / `0` / `NULL` / `false` になる。
- invalid factory handle と NULL name が `0` / `NULL` / no-op になる。
- NULL data / zero length の deserialize が handle `0` になる。
- `SkBlender_Mode` の正常系が handle を返し、serialize 可能である。

## 検証

実施コマンド:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_blender_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_blender_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|open_type_svg_decoder|image_filter|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt test configure 成功。
- `test_blender_invalid_input_smoke` build 成功。
- `c_skia_blender_invalid_input_smoke` 成功。
- prebuilt Debug build 成功。
- prebuilt Phase 2 invalid-input smoke 53 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_blender.{h,cpp}`

## 次バッチ候補

Phase 2 の次候補:

- `SkPathBuilder` の builder pointer / output path 規約
- `SkTiledImageUtils` の required image / rect / sampling pointer 規約
- `SkRuntimeEffect` / runtime builders の factory handle 0 / child pointer 規約
