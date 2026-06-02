# 31 Phase 2 Batch AD: drawable / flattenable C API safety

作業開始日時: 2026-05-09 22:38:22 JST

## 目的

Phase 2 の次バッチとして、`SkDrawable` / `SkFlattenable` 周辺を fail-safe に寄せる。両者は ref-counted base object、factory callback handle、serialize/deserialize、nullable `sk_sp` / `unique_ptr` を扱うため、NULL 入力・生成不能・必須 pointer 欠落を C ABI 境界で明示する。

対象:

- `skia/capi/sk_drawable.h`
- `skia/capi/sk_drawable.cpp`
- `skia/capi/sk_flattenable.h`
- `skia/capi/sk_flattenable.cpp`

## 実装変更

各 C API に NULL ガードと nullable handle helper を追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| handle (`sk_drawable_t`, `sk_flattenable_t`, `sk_data_t`, `sk_picture_t`, factory handle など) | `0` |
| raw pointer / name pointer | `NULL` |
| id / size | `0` |
| flattenable type query | `-1` |
| `bool` query | `false` |
| draw / flatten / register / ref-count mutation | no-op |

nullable `sk_sp` / `unique_ptr` / factory pointer は handle table に登録せず、C ABI では handle `0` として返す。

## pointer / buffer 規約

ヘッダコメントを補強した。

- `draw` / `drawAt`: `drawable` と `canvas` は非 NULL。invalid 入力では no-op。
- `snapGpuDrawHandler`: `drawable` / `matrix` / `clipBounds` / `bufferInfo` は非 NULL。invalid 入力や生成不能では `0`。
- `flatten`: `write_buffer` は非 NULL。invalid 入力では no-op。
- `serialize`: serial procs は NULL 許可。NULL object や生成不能では `0`。
- `serializeToMemory`: `memory_size > 0` では `memory` は非 NULL。invalid 入力では `0`。
- `NameToFactory`: `name` は非 NULL。未登録や invalid 入力では `0`。
- `FactoryToName`: invalid factory では `NULL`。
- `Deserialize`: data は非 NULL、length/size は `> 0`。invalid 入力や生成不能では `0`。
- `SkFlattenable_Deserialize`: type は `SkFlattenable::Type` の既知範囲内。

## smoke test

`test_drawable_flattenable_invalid_input_smoke` を追加し、`ctest` に `c_skia_drawable_flattenable_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkFlattenable` / `SkDrawable` query/refcount/serialize APIs が fail-safe 値または no-op になる。
- NULL name、未登録 name、invalid factory が handle `0` / `NULL` になる。
- deserialize の invalid type、NULL data、empty data が handle `0` になる。
- `SkDrawable_GetFlattenableType()` が drawable type を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_drawable_flattenable_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_drawable_flattenable_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_drawable_flattenable_invalid_input_smoke` build 成功。
- `c_skia_drawable_flattenable_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_drawable.h`
- `skia/capi/sk_drawable.cpp`
- `skia/capi/sk_flattenable.h`
- `skia/capi/sk_flattenable.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFontMgr` / font family enumeration 周辺
- `SkTypeface_Mac` の Apple 限定 C API
- `SkPicture` / `SkPictureRecorder`
