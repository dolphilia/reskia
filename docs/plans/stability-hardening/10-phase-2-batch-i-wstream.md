# 10 Phase 2 Batch I: write stream C API safety

作業開始日時: 2026-05-08 16:43:54 JST

## 目的

Phase 2 の次バッチとして、stream 系のうち write 側の `SkWStream` / `SkDynamicMemoryWStream` の C API 境界を fail-safe に寄せる。write/copy/read の raw buffer と stream 間転送の NULL 規約を明確にする。

対象:

- `skia/capi/sk_w_stream.h`
- `skia/capi/sk_w_stream.cpp`
- `skia/capi/sk_dynamic_memory_w_stream.h`
- `skia/capi/sk_dynamic_memory_w_stream.cpp`

## 実装変更

`sk_w_stream.cpp` / `sk_dynamic_memory_w_stream.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| `bool` | `false` |

主な対象:

- `SkWStream`: write/flush/bytesWritten、typed write、text write、writeStream
- `SkDynamicMemoryWStream`: write/bytesWritten/read/copyTo/writeToStream/copyToAndReset/writeToAndReset/detach/reset/flush、typed write、text write、writeStream

## raw buffer / stream transfer 規約

ヘッダコメントを補強した。

- `write(buffer, size)`: `buffer == NULL` は `size == 0` の場合だけ許可。
- `read(buffer, offset, size)`: `buffer == NULL` は `size == 0` の場合だけ許可。
- `writeText(text)`: `text` は非 NULL。
- `writeStream(input, length)`: `input == NULL` は `length == 0` の場合だけ許可。
- `copyTo` / `copyToAndReset`: `dst` は `bytesWritten()` 分の容量を持つ caller-owned buffer。

## smoke test

`test_wstream_invalid_input_smoke` を追加し、`ctest` に `c_skia_wstream_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkWStream *` / `SkDynamicMemoryWStream *` の write/query/transfer がクラッシュせず fail-safe 値を返す。
- `SkNullWStream` で `write(NULL, 0)` は成功、`write(NULL, 1)` は失敗する。
- `writeStream(NULL, 0)` は空転送として成功する。
- valid dynamic stream で write/read/bytesWritten が機能する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_wstream_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|stream|wstream)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_wstream_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。
- `c_skia_rect_rrect_invalid_input_smoke` 成功。
- `c_skia_image_info_invalid_input_smoke` 成功。
- `c_skia_data_invalid_input_smoke` 成功。
- `c_skia_stream_invalid_input_smoke` 成功。
- `c_skia_wstream_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_w_stream.h`
- `skia/capi/sk_w_stream.cpp`
- `skia/capi/sk_dynamic_memory_w_stream.h`
- `skia/capi/sk_dynamic_memory_w_stream.cpp`

## 次バッチ候補

Phase 2 の次候補:

- remaining stream 系: stream asset/seekable/rewindable
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
- `SkColorInfo` / `SkColorSpace` 周辺
