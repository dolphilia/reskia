# 08 Phase 2 Batch G: data C API safety

作業開始日時: 2026-05-08 16:29:14 JST

## 目的

Phase 2 の次バッチとして、raw byte buffer と所有権規約に関わる `SkData` の C API 境界を fail-safe に寄せる。`SkData` は codec / image / stream 系 API の受け渡しに使われるため、NULL data と raw pointer lifetime の扱いを明確にする。

対象:

- `skia/capi/sk_data.h`
- `skia/capi/sk_data.cpp`

## 実装変更

`sk_data.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| `bool` query | 原則 `false` |
| empty query | `true` |

主な対象:

- refcount 操作: `release` / `ref` / `unref` / `deref`
- query: `size` / `isEmpty` / `data` / `bytes` / `writable_data` / `unique` / `refCntGreaterThan`
- copy: `copyRange`
- equality: `equals`
- static factory: `MakeWithCopy` / `MakeWithProc` / `MakeWithoutCopy` / `MakeFromMalloc` / `MakeFromFileName` / `MakeFromFILE` / `MakeFromStream` / `MakeSubset`

## raw buffer / ownership 規約

`sk_data.h` のコメントを補強した。

- `SkData_data` / `SkData_bytes`: borrowed pointer。caller は解放しない。
- `SkData_writable_data`: borrowed mutable pointer。`SkData` が unique の間だけ mutation する。
- `SkData_copyRange`: `buffer == NULL` は clamped copy size の問い合わせとして許可。
- `SkData_MakeWithCopy`: `data == NULL` は `length == 0` の場合だけ許可。内容はコピーされる。
- `SkData_MakeWithProc`: `ptr == NULL` は `length == 0` の場合だけ許可。`proc == NULL` は Skia と同じく許可。
- `SkData_MakeWithoutCopy`: `data == NULL` は `length == 0` の場合だけ許可。caller が storage lifetime を維持する。
- `SkData_MakeFromMalloc`: `data == NULL` は `length == 0` の場合だけ許可。SkData が malloc storage を所有する。
- `SkData_MakeFromStream`: `stream == NULL` は `size == 0` の場合だけ許可。

`length == 0` / `size == 0` の NULL pointer factory は C API 側で `SkData::MakeEmpty()` に寄せる。

## smoke test

`test_data_invalid_input_smoke` を追加し、`ctest` に `c_skia_data_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkData *` の query/refcount/copy がクラッシュせず fail-safe 値を返す。
- raw pointer factory は `length > 0` かつ pointer NULL の場合に `0` を返す。
- `length == 0` の NULL pointer factory は empty data handle を返す。
- valid data で `copyRange(NULL buffer)` が clamped size を返し、実 buffer copy も期待値になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_data_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_data_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。
- `c_skia_rect_rrect_invalid_input_smoke` 成功。
- `c_skia_image_info_invalid_input_smoke` 成功。
- `c_skia_data_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_data.h`
- `skia/capi/sk_data.cpp`

## 次バッチ候補

Phase 2 の次候補:

- stream 系: `SkStream` / `SkWStream` / memory stream
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorInfo` / `SkColorSpace` 周辺
