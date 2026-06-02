# 12 Phase 2 Batch K: color info / color space C API safety

作業開始日時: 2026-05-09 06:24:30 JST

## 目的

Phase 2 の次バッチとして、`SkImageInfo` 周辺から未処理の `SkColorInfo` / `SkColorSpace` / `SkColorSpacePrimaries` を fail-safe に寄せる。色空間 API は borrowed pointer、ref-counted handle、raw serialized buffer、skcms output struct が混在するため、NULL 入力と所有権規約を小さく明文化する。

対象:

- `skia/capi/sk_color_info.h`
- `skia/capi/sk_color_info.cpp`
- `skia/capi/sk_color_space.h`
- `skia/capi/sk_color_space.cpp`
- `skia/capi/sk_color_space_primaries.h`
- `skia/capi/sk_color_space_primaries.cpp`

## 実装変更

各 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric/hash/size | `0` |
| `bool` query | 原則 `false` |
| ref-count mutation | no-op |
| output write | no-op / `false` |

例外:

- `SkColorSpace_Equals(NULL, NULL)` は upstream の static helper と同じく `true` を返す。
- `SkColorSpace_writeToMemory(valid, NULL)` は upstream と同じく必要サイズを返す。

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkColorInfo_colorSpace`: borrowed pointer。caller は `release` / `unref` しない。
- `SkColorInfo_refColorSpace`: retained handle。caller は `static_sk_color_space_delete` する。
- `SkColorSpace_serialize`: retained data handle。caller は `static_sk_data_delete` する。
- `SkColorSpace_writeToMemory`: `memory == NULL` は必要サイズ問い合わせ。`color_space == NULL` では `0`。
- `SkColorSpace_transferFn` / `transferFnToStruct` / `invTransferFn` / `toXYZD50`: output pointer は非 NULL。
- `SkColorSpace_Deserialize`: `data` は `length` バイト以上、非 NULL。
- `SkColorSpace_MakeRGB` / `Make`: skcms 入力構造体は非 NULL。
- `SkColorSpacePrimaries_toXYZD50`: output matrix は非 NULL。

## smoke test

`test_color_info_space_invalid_input_smoke` を追加し、`ctest` に `c_skia_color_info_space_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkColorInfo` query/factory がクラッシュせず fail-safe 値を返す。
- NULL `SkColorSpace` query/ref-count/output/write がクラッシュせず fail-safe 値または no-op になる。
- raw buffer factory が NULL 入力で `0` を返す。
- `SkColorSpace_MakeSRGB` / `MakeRGB` の正常系ハンドルを最小確認する。
- `SkColorSpace_writeToMemory(valid, NULL)` が必要サイズを返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_color_info_space_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_color_info_space_invalid_input_smoke` build 成功。
- `c_skia_color_info_space_invalid_input_smoke` 成功。
- C API invalid-input smoke 12 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_color_info.h`
- `skia/capi/sk_color_info.cpp`
- `skia/capi/sk_color_space.h`
- `skia/capi/sk_color_space.cpp`
- `skia/capi/sk_color_space_primaries.h`
- `skia/capi/sk_color_space_primaries.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorFilter` / color filter factory 系
