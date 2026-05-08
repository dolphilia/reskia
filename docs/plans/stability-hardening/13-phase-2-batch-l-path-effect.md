# 13 Phase 2 Batch L: path effect C API safety

作業開始日時: 2026-05-09 06:57:20 JST

## 目的

Phase 2 の次バッチとして、`SkPathEffect` 本体と path effect factory 群を fail-safe に寄せる。path effect は `SkPaint` から参照される ref-counted object であり、factory が `nullptr` の `sk_sp<SkPathEffect>` を返すケースがあるため、C ABI では「生成不能なら handle 0」を徹底する。

対象:

- `skia/capi/sk_path_effect.h`
- `skia/capi/sk_path_effect.cpp`
- `skia/capi/sk_dash_path_effect.h`
- `skia/capi/sk_dash_path_effect.cpp`
- `skia/capi/sk_corner_path_effect.h`
- `skia/capi/sk_corner_path_effect.cpp`
- `skia/capi/sk_discrete_path_effect.h`
- `skia/capi/sk_discrete_path_effect.cpp`
- `skia/capi/sk_line_2d_path_effect.h`
- `skia/capi/sk_line_2d_path_effect.cpp`
- `skia/capi/sk_path_1d_path_effect.h`
- `skia/capi/sk_path_1d_path_effect.cpp`
- `skia/capi/sk_path_2d_path_effect.h`
- `skia/capi/sk_path_2d_path_effect.cpp`
- `skia/capi/sk_trim_path_effect.h`
- `skia/capi/sk_trim_path_effect.cpp`

## 実装変更

各 C API に NULL ガードを追加し、factory 戻り値を `make_path_effect_handle()` 経由に統一した。

戻り規約:

| 戻り値種別 | NULL / 無効入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric/size | `0` |
| `bool` query / operation | `false` |
| ref-count mutation / register | no-op |

主な対象:

- `SkPathEffect` query / serialize / flatten / filterPath
- `MakeSum` / `MakeCompose`
- `Deserialize`
- flattenable factory name lookup / registration
- dash/corner/discrete/trim/line2D/path1D/path2D factory

## raw buffer / typed pointer 規約

ヘッダコメントを補強した。

- `SkPathEffect_filterPath`: `dst` / `src` / `rec` は非 NULL。`cullR` は NULL 許可。
- `SkPathEffect_filterPathWithCTM`: `dst` / `src` / `rec` / `ctm` は非 NULL。`cullR` は NULL 許可。
- `SkPathEffect_serialize`: retained data handle。`procs` は NULL 許可。
- `SkPathEffect_serializeToMemory`: `memory` は `memory_size` バイト以上。サイズ取得は `serialize()` を使う。
- `SkPathEffect_Deserialize`: `data` は `size` バイト以上、非 NULL。`procs` は NULL 許可。
- `SkDashPathEffect_Make`: `intervals` は `count` 要素以上、非 NULL。
- `SkLine2DPathEffect_Make`: `matrix` は非 NULL。
- `SkPath1DPathEffect_Make`: `path` は非 NULL。
- `SkPath2DPathEffect_Make`: `matrix` / `path` は非 NULL。

## smoke test

`test_path_effect_invalid_input_smoke` を追加し、`ctest` に `c_skia_path_effect_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkPathEffect` query/filter/serialize/ref-count がクラッシュせず fail-safe 値または no-op になる。
- NULL raw input / typed pointer factory が `0` を返す。
- dash/corner factory の正常系 handle を最小確認する。
- valid path effect の `serialize()` が data handle を返す。
- valid dash/corner handle から `MakeSum` / `MakeCompose` が生成できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_path_effect_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_path_effect_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_path_effect_invalid_input_smoke` build 成功。
- `c_skia_path_effect_invalid_input_smoke` 成功。
- C API invalid-input smoke 13 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更または Batch L の補足に更新:

- `skia/capi/sk_path_effect.h`
- `skia/capi/sk_path_effect.cpp`
- `skia/capi/sk_dash_path_effect.h`
- `skia/capi/sk_dash_path_effect.cpp`
- `skia/capi/sk_corner_path_effect.h`
- `skia/capi/sk_corner_path_effect.cpp`
- `skia/capi/sk_discrete_path_effect.h`
- `skia/capi/sk_discrete_path_effect.cpp`
- `skia/capi/sk_line_2d_path_effect.h`
- `skia/capi/sk_line_2d_path_effect.cpp`
- `skia/capi/sk_path_1d_path_effect.h`
- `skia/capi/sk_path_1d_path_effect.cpp`
- `skia/capi/sk_path_2d_path_effect.h`
- `skia/capi/sk_path_2d_path_effect.cpp`
- `skia/capi/sk_trim_path_effect.h`
- `skia/capi/sk_trim_path_effect.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkColorFilter` / color filter factory 系
- `SkFont` / `SkTypeface`
- `SkContourMeasure` / path measure 周辺
