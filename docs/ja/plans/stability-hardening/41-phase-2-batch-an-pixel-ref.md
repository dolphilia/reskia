# 41 Phase 2 Batch AN: pixel ref C API safety

作業開始日時: 2026-05-10 07:40:26 JST

## 目的

Phase 2 の次バッチとして、`SkPixelRef` / `SkMallocPixelRef` 周辺を fail-safe に寄せる。pixel ref は raw pixel pointer を借用し、bitmap や handle table と参照カウントで共有されるため、NULL 入力、borrowed pointer、生成不能時の handle 規約を明示する。

対象:

- `skia/capi/sk_pixel_ref.h`
- `skia/capi/sk_pixel_ref.cpp`
- `skia/capi/sk_malloc_pixel_ref.h`
- `skia/capi/sk_malloc_pixel_ref.cpp`

## 実装変更

`SkPixelRef` query / mutation / refcount API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed pointer | `NULL` |
| handle (`sk_i_size_t`, `sk_pixel_ref_t`) | `0` |
| integer / size / generation id | `0` |
| `bool` | `false` |
| mutation / ref / unref | no-op |

`SkPixelRef_new` は負の width / height を拒否して `NULL` を返す。`addr == NULL` は upstream と同じく、呼び出し側が意図して空または外部管理 pixel ref を作る場合を許可する。

`SkMallocPixelRef` factory は NULL `SkImageInfo` と invalid data handle を拒否し、生成不能時は handle `0` を返す。null `SkData` で upstream assert に入らないようにした。

## pointer / ownership 規約

ヘッダコメントを補強した。

- `SkPixelRef_pixels`: borrowed pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkPixelRef_dimensions`: NULL 入力では handle `0`。
- `SkPixelRef_addGenIDChangeListener`: pixel ref と listener handle は必須。invalid 入力では no-op。
- `SkPixelRef_ref` / `unref` / `release`: NULL 入力では no-op。
- `SkMallocPixelRef_MakeAllocate`: image info は非 NULL。失敗時は `0`。
- `SkMallocPixelRef_MakeWithData`: image info と valid data handle は必須。失敗時は `0`。

## smoke test

`test_pixel_ref_invalid_input_smoke` を追加し、`ctest` に `c_skia_pixel_ref_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkPixelRef` query / mutation / refcount が fail-safe 値または no-op になる。
- 負サイズ factory が `NULL` になる。
- NULL `SkMallocPixelRef` factory が `0` になる。
- valid borrowed pixel buffer から `SkPixelRef` を作成し、width / height / pixels / rowBytes / generation id / dimensions / immutable / refcount を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_pixel_ref_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_pixel_ref_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|image_info|data|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_pixel_ref_invalid_input_smoke` build 成功。
- `c_skia_pixel_ref_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 41 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_pixel_ref.h`
- `skia/capi/sk_pixel_ref.cpp`
- `skia/capi/sk_malloc_pixel_ref.h`
- `skia/capi/sk_malloc_pixel_ref.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
- `SkPixmap` / `SkPixmapUtils` 周辺
