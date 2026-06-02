# 07 Phase 2 Batch F: image info C API safety

作業開始日時: 2026-05-08 16:24:18 JST

## 目的

Phase 2 の次バッチとして、pixel buffer のサイズ計算と read/write pixel 系 API の土台になる `SkImageInfo` の C API 境界を fail-safe に寄せる。`SkBitmap` / `SkCanvas` / `SkSurface` が参照する rowBytes・byte size 計算の入力を安定させる。

対象:

- `skia/capi/sk_image_info.h`
- `skia/capi/sk_image_info.cpp`

## 実装変更

`sk_image_info.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric / enum | `0` |
| `bool` query | 原則 `false` |
| empty query | `true` |

主な対象:

- equality: `equals` / `notEquals`
- scalar query: width、height、color type、alpha type、bytes per pixel、row bytes、byte size
- ownership query: `colorSpace` / `refColorSpace` / `colorInfo`
- derived value: dimensions、bounds、makeWH、makeDimensions、makeAlphaType、makeColorType、makeColorSpace
- mutation: `reset`
- static helper: `SkImageInfo_Make_5`

## pointer / byte size 規約

`sk_image_info.h` のコメントを補強した。

- `SkImageInfo_colorSpace`: borrowed pointer。caller は delete しない。
- `SkImageInfo_refColorSpace`: retained handle を返す。`image_info == NULL` の場合は `0`。
- `SkImageInfo_computeOffset`: caller は pixel buffer layout に十分な `rowBytes` を渡す。
- `SkImageInfo_computeByteSize`: `image_info == NULL` では `0`。overflow sentinel は `SkImageInfo_ByteSizeOverflowed` で判定する。
- `SkImageInfo_Make_5`: `colorInfo` は非 NULL。
- color space handle `0` は null color space として扱う。

## smoke test

`test_image_info_invalid_input_smoke` を追加し、`ctest` に `c_skia_image_info_invalid_input_smoke` として登録した。

確認内容:

- NULL image info の query/mutation/derived factory がクラッシュせず fail-safe 値を返す。
- NULL image info の borrowed/ref color space が `NULL` / `0` を返す。
- `SkImageInfo_Make_5` の NULL `colorInfo` が `0` を返す。
- valid `SkImageInfo_MakeN32Premul` handle で width と rowBytes validation が機能する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_image_info_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_image_info_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。
- `c_skia_rect_rrect_invalid_input_smoke` 成功。
- `c_skia_image_info_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_image_info.h`
- `skia/capi/sk_image_info.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkData` / stream 系
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorInfo` / `SkColorSpace` 周辺
