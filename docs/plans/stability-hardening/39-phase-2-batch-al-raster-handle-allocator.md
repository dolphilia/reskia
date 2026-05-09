# 39 Phase 2 Batch AL: raster handle allocator C API safety

作業開始日時: 2026-05-10 07:33:36 JST

## 目的

Phase 2 の次バッチとして、`SkRasterHandleAllocator` / allocator callback 周辺を fail-safe に寄せる。`SkRasterHandleAllocator` は抽象 allocator を C ABI に露出し、`MakeCanvas` では allocator ownership を `std::unique_ptr` に移すため、NULL 入力と consumed ownership の境界を明示する。

対象:

- `skia/capi/sk_raster_handle_allocator.h`
- `skia/capi/sk_raster_handle_allocator.cpp`

## 実装変更

`SkRasterHandleAllocator` wrapper に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `bool` | `false` |
| `sk_canvas_t` | `0` |
| delete / update | no-op |

`SkRasterHandleAllocator_MakeCanvas` は allocator / info が非 NULL の場合だけ allocator ownership を `std::unique_ptr` に移す。`rec` / `props` は upstream 規約どおり NULL 許可とした。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `delete`: NULL allocator は no-op。
- `allocHandle`: allocator / image info / output rec は非 NULL。
- `updateHandle`: allocator / handle / matrix / clip rect は非 NULL。
- `MakeCanvas`: non-NULL allocator は callee が ownership を引き取る。`rec` / `props` は NULL 許可。失敗時は `0`。

## smoke test

`test_raster_handle_allocator_invalid_input_smoke` を追加し、`ctest` に `c_skia_raster_handle_allocator_invalid_input_smoke` として登録した。

確認内容:

- NULL allocator delete / update が no-op になる。
- NULL `allocHandle` が `false` を返す。
- NULL `MakeCanvas` が `0` を返す。

`SkRasterHandleAllocator` は abstract base であり、この C API だけでは valid concrete allocator を作れないため、今回の smoke は invalid-input boundary に限定した。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_raster_handle_allocator_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_raster_handle_allocator_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_raster_handle_allocator_invalid_input_smoke` build 成功。
- `c_skia_raster_handle_allocator_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 39 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_raster_handle_allocator.h`
- `skia/capi/sk_raster_handle_allocator.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
- `SkRefCnt` / `SkNVRefCnt` / raw ref-count helper 周辺
