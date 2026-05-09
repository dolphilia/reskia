# 44 Phase 2 Batch AQ: YUVA info C API safety

作業開始日時: 2026-05-10 08:09:02 JST

## 目的

Phase 2 の次バッチとして、`SkYUVAInfo` 周辺を fail-safe に寄せる。`SkYUVAInfo` は YUVA plane config / subsampling / origin / siting / dimensions handle / output 配列を C ABI 境界で受け取るため、NULL 入力、invalid handle、enum 範囲外、plane index 範囲外を upstream の `SkUNREACHABLE` や dereference に渡さない。

対象:

- `skia/capi/sk_yuva_info.h`
- `skia/capi/sk_yuva_info.cpp`

## 実装変更

`SkYUVAInfo` に NULL ガード、enum 範囲チェック、`sk_i_size_t` handle 検証、plane index チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_i_size_t`, `sk_matrix_t`, `sk_yuva_info_t`, `tuple_int_int_t`) | `0` |
| integer / size | `0` |
| enum | `-1` |
| `bool` | `false` |
| delete | no-op |

`planeDimensions` / `PlaneDimensions` は `planeDimensions == NULL` を拒否して `0` を返す。出力配列が非 NULL で入力が invalid の場合は 4 plane 分を empty size でクリアする。

`computeTotalBytes` は `yuva_info == NULL` または `rowBytes == NULL` で `0` を返す。`planeSizes` が非 NULL なら 4 plane 分を `0` でクリアする。

## enum / plane 規約

- `PlaneConfig` は `0..SkYUVAInfo::PlaneConfig::kLast` の範囲だけを upstream に渡す。
- `Subsampling` は `0..SkYUVAInfo::Subsampling::kLast` の範囲だけを upstream に渡す。
- `SkYUVColorSpace` は `0..kLastEnum_SkYUVColorSpace` の範囲だけを constructor に渡す。
- `SkEncodedOrigin` は `kTopLeft_SkEncodedOrigin..kLast_SkEncodedOrigin` の範囲だけを constructor / static `PlaneDimensions` に渡す。`0` は invalid。
- `Siting` は現行 upstream が提供する `kCentered` のみ許可する。
- `planeSubsamplingFactors` / static `PlaneSubsamplingFactors` は `0 <= planeIdx < NumPlanes(config)` の場合だけ tuple handle を返す。

## smoke test

`test_yuva_info_invalid_input_smoke` を追加し、`ctest` に `c_skia_yuva_info_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkYUVAInfo` query / comparison / factory が fail-safe 値になる。
- invalid dimensions handle / enum / origin / siting / plane index が upstream に渡らず失敗値になる。
- output 配列が invalid 入力時にクリアされる。
- valid `SkYUVAInfo` から dimensions / plane count / plane dimensions / byte size / tuple handle / `YUVALocations` / `makeSubsampling` / `makeDimensions` を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_yuva_info_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_yuva_info_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_yuva_info_invalid_input_smoke` build 成功。
- `c_skia_yuva_info_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 44 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。
- ビルド時に Skia header 由来の C++17 inline variable warning が出るが、ビルドは成功している。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_yuva_info.h`
- `skia/capi/sk_yuva_info.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
