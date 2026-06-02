# 09 Phase 2 Batch H: stream / memory stream C API safety

作業開始日時: 2026-05-08 16:35:09 JST

## 目的

Phase 2 の次バッチとして、`SkData` に続く stream 系のうち、基底 `SkStream` と `SkMemoryStream` の C API 境界を fail-safe に寄せる。raw byte buffer の read/peek と borrowed memory base の NULL 規約を明確にする。

対象:

- `skia/capi/sk_stream.h`
- `skia/capi/sk_stream.cpp`
- `skia/capi/sk_memory_stream.h`
- `skia/capi/sk_memory_stream.cpp`

## 実装変更

`sk_stream.cpp` / `sk_memory_stream.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| `bool` query | 原則 `false` |
| end-of-stream query | `true` |

主な対象:

- `SkStream`: read/skip/peek、typed read、rewind/seek/move、duplicate/fork、position/length、memory base、file factory
- `SkMemoryStream`: construction、setMemory/setData、asData、read/peek、typed read、position/length、duplicate/fork、memory base、MakeCopy/MakeDirect

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `read(buffer, size)`: `buffer == NULL` は Skia の規約通り skip として扱う。
- `peek(buffer, size)`: `buffer == NULL` は `size == 0` の場合だけ許可する。
- typed read の output pointer は非 NULL。
- `getMemoryBase` / `getAtPos`: borrowed pointer。caller は解放しない。
- `SkMemoryStream_newWithDataAndCopyFlag` / `setMemory` / `MakeCopy` / `MakeDirect`: `data == NULL` は `length == 0` の場合だけ許可する。
- `copyData == false` / `MakeDirect`: caller が storage lifetime を維持する。
- `setMemoryOwned`: stream が sk_malloc-compatible storage を所有する。

## smoke test

`test_stream_invalid_input_smoke` を追加し、`ctest` に `c_skia_stream_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkStream *` / `SkMemoryStream *` の query/read/seek/duplicate がクラッシュせず fail-safe 値を返す。
- NULL output pointer の typed read が `false` を返す。
- `SkMemoryStream` valid instance で `read(NULL, size)` が skip として機能する。
- `peek` が stream position を変えずに byte を返す。
- `SkMemoryStream_MakeCopy` の handle 経路が有効。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_stream_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_stream_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。
- `c_skia_rect_rrect_invalid_input_smoke` 成功。
- `c_skia_image_info_invalid_input_smoke` 成功。
- `c_skia_data_invalid_input_smoke` 成功。
- `c_skia_stream_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_stream.h`
- `skia/capi/sk_stream.cpp`
- `skia/capi/sk_memory_stream.h`
- `skia/capi/sk_memory_stream.cpp`

## 次バッチ候補

Phase 2 の次候補:

- remaining stream 系: `SkWStream` / `SkDynamicMemoryWStream` / stream asset/seekable/rewindable
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorInfo` / `SkColorSpace` 周辺
