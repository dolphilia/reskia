# 11 Phase 2 Batch J: stream derived C API safety

作業開始日時: 2026-05-08 16:51:50 JST

## 目的

Phase 2 の次バッチとして、remaining stream 系の `SkStreamAsset` / `SkStreamSeekable` / `SkStreamRewindable` / `SkStreamMemory` の C API 境界を fail-safe に寄せる。Batch H/I で整理した read/peek/typed read 規約を派生 stream に横展開する。

対象:

- `skia/capi/sk_stream_asset.h`
- `skia/capi/sk_stream_asset.cpp`
- `skia/capi/sk_stream_seekable.h`
- `skia/capi/sk_stream_seekable.cpp`
- `skia/capi/sk_stream_rewindable.h`
- `skia/capi/sk_stream_rewindable.cpp`
- `skia/capi/sk_stream_memory.h`
- `skia/capi/sk_stream_memory.cpp`

## 実装変更

各 stream 派生 C API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| `bool` query | 原則 `false` |
| end-of-stream query | `true` |

主な対象:

- duplicate/fork
- position/length query
- seek/move/rewind
- read/skip/peek
- typed read
- memory base
- file factory

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `read(buffer, size)`: `buffer == NULL` は skip として扱う。
- `peek(buffer, size)`: `buffer == NULL` は `size == 0` の場合だけ許可する。
- typed read の output pointer は非 NULL。
- `getMemoryBase`: borrowed pointer。caller は解放しない。
- `MakeFromFile`: `path` は非 NULL。

## smoke test

`test_stream_derived_invalid_input_smoke` を追加し、`ctest` に `c_skia_stream_derived_invalid_input_smoke` として登録した。

確認内容:

- NULL stream 派生 pointer の query/read/seek/duplicate/fork がクラッシュせず fail-safe 値を返す。
- NULL output pointer の typed read が `false` を返す。
- NULL path の file factory が `0` を返す。
- delete(NULL) が no-op であることを確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_stream_derived_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(stream|stream_derived|wstream)_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream|stream_derived)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_stream_derived_invalid_input_smoke` build 成功。
- stream 系 invalid-input smoke 3 本成功。
- C API invalid-input smoke 11 本成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_stream_asset.h`
- `skia/capi/sk_stream_asset.cpp`
- `skia/capi/sk_stream_seekable.h`
- `skia/capi/sk_stream_seekable.cpp`
- `skia/capi/sk_stream_rewindable.h`
- `skia/capi/sk_stream_rewindable.cpp`
- `skia/capi/sk_stream_memory.h`
- `skia/capi/sk_stream_memory.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorInfo` / `SkColorSpace` 周辺
