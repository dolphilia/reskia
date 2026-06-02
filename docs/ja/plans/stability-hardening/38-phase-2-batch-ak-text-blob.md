# 38 Phase 2 Batch AK: text blob C API safety

作業開始日時: 2026-05-10 07:18:59 JST

## 目的

Phase 2 の次バッチとして、`SkTextBlob` / glyph-buffer 周辺を fail-safe に寄せる。`SkTextBlob` は text buffer、position / transform array、serialization procs、handle 化された `sk_sp`、builder run buffer を横断するため、C ABI 境界で NULL 入力と生成不能時の戻り値を明示する。

対象:

- `skia/capi/sk_text_blob.h`
- `skia/capi/sk_text_blob.cpp`
- `skia/capi/sk_text_blob_builder.h`
- `skia/capi/sk_text_blob_builder.cpp`

`SkTextBlobBuilderRunHandler` はこの prebuilt test 構成の `reskia` にリンクされていないため、今回の verified scope から外した。

## 実装変更

`SkTextBlob` の ref/query/serialize/static factory API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| borrowed pointer | `NULL` |
| handle (`sk_text_blob_t`, `sk_data_t`) | `0` |
| `uint32_t` / size / count | `0` |
| `bool` | `false` |
| ref/unref/deref | no-op |

serialization / deserialization procs は Skia 側の「NULL なら default procs」相当として扱い、C ABI では `procs == NULL` を許可する。

`SkTextBlobBuilder` は builder / font / count / textByteCount を C ABI 境界で検証し、invalid 入力では run buffer を返さず `NULL` にする。empty builder の `make` は handle `0` を返す。

## pointer / raw array 規約

ヘッダコメントを補強した。

- `SkTextBlob_getIntercepts`: `bounds[2]` は非 NULL。`intervals` / `paint` は NULL 許可。
- `SkTextBlob_serialize`: `memory_size > 0` では `memory` は非 NULL。`procs` は NULL 許可。
- `SkTextBlob_serializeToData`: NULL / missing data は handle `0`。
- text factory: `byteLength > 0` では `text` は非 NULL。`font` と valid encoding は必須。
- positional text factory: `byteLength > 0` では text と position / xform array は非 NULL。
- `Deserialize`: `size > 0` では data は非 NULL。`procs` は NULL 許可。
- builder run allocation: builder / font は必須。`count > 0`、text run は `textByteCount >= 0`。

## smoke test

`test_text_blob_invalid_input_smoke` を追加し、`ctest` に `c_skia_text_blob_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkTextBlob` ref/query/serialize/static factory が fail-safe 値または no-op になる。
- NULL / invalid builder allocation が `NULL` / `0` になる。
- valid default `SkFont` から `SkTextBlob` を生成し、bounds / uniqueID / intercept count / serializeToData を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_text_blob_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_text_blob_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_text_blob_invalid_input_smoke` build 成功。
- `c_skia_text_blob_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 38 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_text_blob.h`
- `skia/capi/sk_text_blob.cpp`
- `skia/capi/sk_text_blob_builder.h`
- `skia/capi/sk_text_blob_builder.cpp`

未変更:

- `skia/capi/sk_text_blob_builder_run_handler.h`
- `skia/capi/sk_text_blob_builder_run_handler.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkRasterHandleAllocator` / allocator callback 周辺
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
