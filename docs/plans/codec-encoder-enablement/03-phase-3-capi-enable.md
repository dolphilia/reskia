# 03 Phase 3: sources-capi と C API 実装の有効化

更新日時: 2026-02-16 15:09:30 JST

## 実施内容

### 1. `sources-capi.cmake` を機能トグル連動で有効化

変更ファイル:
- `/Users/dolphilia/github/reskia/cmake/reskia/sources-capi.cmake`

対応:
- `RESKIA_ENABLE_AVIF` -> `capi/sk_avif_decoder.cpp`
- `RESKIA_ENABLE_JPEGXL` -> `capi/sk_jpegxl_decoder.cpp`
- `RESKIA_ENABLE_GIF` -> `capi/sk_gif_decoder.cpp`
- `RESKIA_ENABLE_RAW` -> `capi/sk_raw_decoder.cpp`
- `RESKIA_ENABLE_JPEG_ENCODER` -> `capi/sk_jpeg_encoder.cpp`
- `RESKIA_ENABLE_WEBP_ENCODER` -> `capi/sk_webp_encoder.cpp`
- `capi/sk_open_type_svg_decoder.cpp` は常時追加

### 2. AVIF/JPEGXL/RAW C API 実装を現行ハンドル型に統一

変更ファイル:
- `/Users/dolphilia/github/reskia/skia/capi/sk_avif_decoder.h`
- `/Users/dolphilia/github/reskia/skia/capi/sk_avif_decoder.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_jpegxl_decoder.h`
- `/Users/dolphilia/github/reskia/skia/capi/sk_jpegxl_decoder.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_raw_decoder.h`
- `/Users/dolphilia/github/reskia/skia/capi/sk_raw_decoder.cpp`

対応:
- コメントアウトされていた宣言/実装を復帰
- `int static_stream/static_data` から `sk_stream_t/sk_data_t` へ統一
- `static_sk_stream_take_entity` / `static_sk_data_get_entity` を使用

### 3. Phase 3 有効化で露出した C API 側不整合を修正

変更ファイル:
- `/Users/dolphilia/github/reskia/skia/capi/sk_gif_decoder.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_jpeg_encoder.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_webp_encoder.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_open_type_svg_decoder.h`
- `/Users/dolphilia/github/reskia/skia/capi/sk_open_type_svg_decoder.cpp`

対応:
- `static_*_make` / `static_const_*_get_entity` の内部ヘッダ不足を解消
- WebP animated encoder の取得関数を `static_const_sk_encoder_frame_get_entity` に修正
- OpenType SVG の `render` ラッパーを `SkSpan<SkColor>` へ適合（単色 palette 1 要素）

## ビルド確認

### ON 構成（Phase 2 で使用したディレクトリ）

```bash
cmake --build skia/cmake-build-phase2-deps -j 8
```

結果: 成功（`Built target reskia`）

### デフォルト構成（オプション無指定）

```bash
cmake -S skia -B skia/cmake-build-phase3-default \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-phase3-default -j 8
```

結果: 成功（`Built target reskia`）

## Phase 4 への引き継ぎ

1. `prebuilt/source/system` のビルド行列で 3.8/3.9 対象オプション ON/OFF を確認。
2. 必要であれば C API の feature OFF 時の挙動（未提供/0返却）を仕様化。
