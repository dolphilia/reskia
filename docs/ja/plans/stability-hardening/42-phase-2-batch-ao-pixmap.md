# 42 Phase 2 Batch AO: pixmap C API safety

作業開始日時: 2026-05-10 07:46:44 JST

## 目的

Phase 2 の次バッチとして、`SkPixmap` / `SkPixmapUtils` 周辺を fail-safe に寄せる。`SkPixmap` は pixel buffer を所有しない低レベル view であり、typed pointer 取得や x/y 指定 API が upstream 側では入力検証を行わないため、C ABI 境界で NULL と範囲外入力を止める。

対象:

- `skia/capi/sk_pixmap.h`
- `skia/capi/sk_pixmap.cpp`
- `skia/capi/sk_pixmap_utils.h`
- `skia/capi/sk_pixmap_utils.cpp`

## 実装変更

`SkPixmap` constructor / reset / query / read / erase / typed pointer API に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed pointer | `NULL` |
| handle (`sk_i_size_t`, `sk_i_rect_t`, `sk_color_4f_t`, `sk_color_space_t`) | `0` |
| integer / size | `0` |
| enum (`colorType`, `alphaType`) | `-1` |
| `float` | `0.0f` |
| `bool` | `false` |
| mutation / reset / setColorSpace | no-op |

`SkPixmap_newWithImageInfoAddressAndRowBytes` は `info == NULL` を拒否して `NULL` を返す。`addr == NULL` は upstream と同じく許可する。

## typed pointer 規約

`addr(x, y)` / `writable_addr(x, y)` / typed pointer 系は以下を C API 側で確認する。

- pixmap が非 NULL。
- pixmap が pixel address を持つ。
- x/y 指定 API は `0 <= x < width` かつ `0 <= y < height`。
- `addr8/16/32/64` は `bytesPerPixel()` と一致する typed accessor のみ呼ぶ。
- `addrF16` / `writable_addrF16` は `kRGBA_F16_SkColorType` または `kRGBA_F16Norm_SkColorType` の場合のみ呼ぶ。

条件を満たさない場合は `NULL` を返し、upstream の debug assert や範囲外 address 計算に入らない。

## SkPixmapUtils

`SkPixmapUtils_Orient` は `dst` / `src` の NULL と `SkEncodedOrigin` の範囲外値を拒否して `false` を返す。

`SkPixmapUtils_SwapWidthHeight` は `info == NULL` で handle `0` を返す。

## smoke test

`test_pixmap_invalid_input_smoke` を追加し、`ctest` に `c_skia_pixmap_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkPixmap` query / mutation / read / erase が fail-safe 値または no-op になる。
- `SkPixmapUtils` の NULL 入力と invalid origin が失敗値になる。
- valid `SkImageInfo` と borrowed pixel buffer から `SkPixmap` を作成し、width / height / addr / typed addr / out-of-bounds / dimensions / bounds / getColor4f / readPixels / eraseColor / SwapWidthHeight を確認する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_pixmap_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_pixmap_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_pixmap_invalid_input_smoke` build 成功。
- `c_skia_pixmap_invalid_input_smoke` 成功。
- Phase 2 invalid-input smoke 42 件成功。
- `git diff --check` は新規 whitespace error なし。既存の `capi-status.csv` CRLF 変換警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_pixmap.h`
- `skia/capi/sk_pixmap.cpp`
- `skia/capi/sk_pixmap_utils.h`
- `skia/capi/sk_pixmap_utils.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の primitive read/write と geometry/object reference 系の残り
- `SkTextBlobBuilderRunHandler` / shaper run buffer 周辺（feature enabled 構成で別途検証）
- `SkYUVAPixmapInfo` / `SkYUVAPixmaps` 周辺
