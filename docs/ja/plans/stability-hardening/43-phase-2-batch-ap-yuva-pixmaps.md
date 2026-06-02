# 43 Phase 2 Batch AP: YUVA pixmap C API safety

作業開始日時: 2026-05-10 07:56:52 JST

## 目的

Phase 2 の次バッチとして、`SkYUVAPixmapInfo` / `SkYUVAPixmaps` 周辺を fail-safe に寄せる。YUVA pixmap は plane 配列、外部メモリ、`SkData` backing store を扱うため、NULL 入力、plane index、invalid handle を C ABI 境界で止める。

対象:

- `skia/capi/sk_yuva_pixmap_info.h`
- `skia/capi/sk_yuva_pixmap_info.cpp`
- `skia/capi/sk_yuva_pixmaps.h`
- `skia/capi/sk_yuva_pixmaps.cpp`

## 実装変更

`SkYUVAPixmapInfo` に NULL ガード、plane index チェック、DataType / ColorType の範囲チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed pointer | `NULL` |
| handle (`sk_yuva_pixmaps_t`, `sk_yuva_pixmap_info_t`, tuple handle) | `0` |
| integer / size | `0` |
| enum | `-1` |
| `bool` | `false` |
| delete | no-op |

`SkYUVAPixmapInfo_computeTotalBytes(NULL, planeSizes)` は `0` を返し、`planeSizes` が非 NULL なら 4 plane 分を 0 で埋める。

## plane / memory 規約

- `rowBytes(i)` / `planeInfo(i)` / `plane(i)` は `i < 0` または `i >= numPlanes()` で失敗値を返す。
- `SkYUVAPixmapInfo_initPixmapsFromSingleAllocation` は `info` / `memory` / `pixmaps` を必須にする。
- `SkYUVAPixmaps_FromData` は valid `SkData` handle を必須にする。upstream は `data->size()` を呼ぶため、invalid handle は handle `0` で拒否する。
- `SkYUVAPixmaps_FromExternalMemory` は `memory != NULL` を必須にする。
- `SkYUVAPixmaps_*` factory は生成結果が invalid の場合、invalid object handle ではなく handle `0` を返す。

## smoke test

`test_yuva_pixmaps_invalid_input_smoke` を追加し、`ctest` に `c_skia_yuva_pixmaps_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkYUVAPixmapInfo` / `SkYUVAPixmaps` query / factory が fail-safe 値になる。
- invalid DataType / ColorType / plane index が失敗値になる。
- valid `SkYUVAInfo` から `SkYUVAPixmapInfo` を作成し、plane count / rowBytes / planeInfo / total bytes / pixmap 初期化を確認する。
- `SkYUVAPixmaps_Allocate` / `MakeCopy` / `FromExternalMemory` / `FromExternalPixmaps` の valid 経路を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_yuva_pixmaps_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_yuva_pixmaps_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_yuva_pixmaps_invalid_input_smoke` build 成功。
- `c_skia_yuva_pixmaps_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 43 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_yuva_pixmap_info.h`
- `skia/capi/sk_yuva_pixmap_info.cpp`
- `skia/capi/sk_yuva_pixmaps.h`
- `skia/capi/sk_yuva_pixmaps.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkYUVAInfo` の NULL / enum / handle 規約補強
- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
