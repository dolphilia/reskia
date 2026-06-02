# 21 Phase 2 Batch T: mask filter C API safety

作業開始日時: 2026-05-09 10:51:28 JST

## 目的

Phase 2 の次バッチとして、`SkMaskFilter` 基底と mask filter factory/helper 周辺を fail-safe に寄せる。`SkTableMaskFilter` は 256 要素の raw table を扱い、`SkShaderMaskFilter` / `SkMaskFilter::MakeBlur` は null `sk_sp<SkMaskFilter>` を返す可能性があるため、NULL 入力・生成不能時 handle・owned ref の規約を明文化する。

対象:

- `skia/capi/sk_mask_filter.h`
- `skia/capi/sk_mask_filter.cpp`
- `skia/capi/sk_shader_mask_filter.h`
- `skia/capi/sk_shader_mask_filter.cpp`
- `skia/capi/sk_table_mask_filter.h`
- `skia/capi/sk_table_mask_filter.cpp`

## 実装変更

各 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / 生成不能入力時 |
| --- | --- |
| pointer / borrowed string | `NULL` |
| handle (`sk_mask_filter_t`, `sk_data_t`, `sk_flattenable_factory_t`) | `0` |
| `size_t` | `0` |
| `bool` query | `false` |
| flattenable type | `-1` |
| ref-count mutation / register / table helper | no-op |
| bounds query | empty rect handle |

static factory では null `sk_sp<SkMaskFilter>` を handle table に登録せず、C ABI では handle `0` として返す helper を追加した。

## raw buffer / owned pointer 規約

ヘッダコメントを補強した。

- `SkMaskFilter_serializeToMemory`: `memory_size > 0` のとき `memory` は非 NULL。NULL 入力では `0`。
- `SkMaskFilter_Deserialize`: `data` は `size > 0` で非 NULL。NULL/空/生成不能では `0`。
- `SkMaskFilter_NameToFactory`: `name` は NUL 終端、非 NULL。未登録/NULL 入力では `0`。
- `SkTableMaskFilter_MakeGammaTable` / `MakeClipTable`: `table` は 256 要素以上、非 NULL。NULL 入力では no-op。
- `SkTableMaskFilter_Create`: `table` は 256 要素以上、非 NULL。NULL 入力や生成不能では `NULL`。戻り pointer は owned ref。
- `SkShaderMaskFilter_Make`: shader handle `0` や生成不能では `0`。

## smoke test

`test_mask_filter_invalid_input_smoke` を追加し、`ctest` に `c_skia_mask_filter_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkMaskFilter` query/refcount/flatten/register がクラッシュせず fail-safe 値または no-op になる。
- invalid deserialize / factory name / factory handle が `0` / `NULL` を返す。
- `SkShaderMaskFilter_Make(0)` が `0` を返す。
- `SkTableMaskFilter` の raw table helper が NULL no-op になり、valid 256 要素 table を更新できる。
- `SkTableMaskFilter_Create(valid)` が owned `SkMaskFilter*` を返し、`SkMaskFilter_release` で解放できる。
- `SkMaskFilter_MakeBlur(valid)` が non-zero handle を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_mask_filter_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_mask_filter_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_mask_filter_invalid_input_smoke` build 成功。
- `c_skia_mask_filter_invalid_input_smoke` 成功。
- C API invalid-input smoke 21 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_mask_filter.h`
- `skia/capi/sk_mask_filter.cpp`
- `skia/capi/sk_shader_mask_filter.h`
- `skia/capi/sk_shader_mask_filter.cpp`
- `skia/capi/sk_table_mask_filter.h`
- `skia/capi/sk_table_mask_filter.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkMask` / `SkMaskBuilder`
- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
