# 02 Phase 2: 不足ソース補完と source list 有効化

更新日時: 2026-02-16 14:53:23 JST

## 実施内容

### 1. upstream から不足ソースを同期

追加ファイル:

- `/Users/dolphilia/github/reskia/skia/include/encode/SkWebpEncoder.h`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkJPEGWriteUtility.cpp`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkJPEGWriteUtility.h`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkJpegEncoderImpl.cpp`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkJpegEncoderImpl.h`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkJpegEncoder_none.cpp`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkWebpEncoderImpl.cpp`
- `/Users/dolphilia/github/reskia/skia/src/encode/SkWebpEncoder_none.cpp`

### 2. `sources-core.cmake` を option 連動で有効化

変更ファイル:

- `/Users/dolphilia/github/reskia/cmake/reskia/sources-core.cmake`

追加した条件付き source:

- `RESKIA_ENABLE_AVIF=ON` で `src/codec/SkAvifCodec.cpp`
- `RESKIA_ENABLE_JPEGXL=ON` で `src/codec/SkJpegxlCodec.cpp`
- `RESKIA_ENABLE_JPEG_ENCODER=ON` で `src/encode/SkJPEGWriteUtility.cpp`, `src/encode/SkJpegEncoderImpl.cpp`
- `RESKIA_ENABLE_WEBP_ENCODER=ON` で `src/encode/SkWebpEncoderImpl.cpp`

フォールバック:

- `RESKIA_ENABLE_JPEG_ENCODER=OFF` で `SkJpegEncoder_none.cpp`
- `RESKIA_ENABLE_WEBP_ENCODER=OFF` で `SkWebpEncoder_none.cpp`

### 3. RAW / GIF 依存の解消（Phase 2 継続）

追加サブモジュール:

- `/Users/dolphilia/github/reskia/third_party/src/dng_sdk`
- `/Users/dolphilia/github/reskia/third_party/src/piex`
- `/Users/dolphilia/github/reskia/third_party/src/wuffs`

関連更新:

- `/Users/dolphilia/github/reskia/.gitmodules`
- `/Users/dolphilia/github/reskia/scripts/bootstrap_third_party.sh`

実装方針:

- RAW:
  - `SkRawCodec.cpp` に加えて `dng_sdk/source/*.cpp`（`dng_xmp*.cpp`, `dng_validate.cpp` 除外）と `piex` 必須 `.cc` を source list へ追加
  - include path/define を `skia/CMakeLists.txt` で付与
  - `zlib` 依存を `ReskiaDeps.cmake` へ追加
- GIF:
  - `third_party/src/wuffs/release/c/wuffs-v0.3.c` を source list に追加
  - `wuffs-v0.3.c` にのみ `WUFFS_IMPLEMENTATION` などの定義を適用
  - `SkWuffsCodec.cpp` は include path で `wuffs-v0.3.c` を解決

## ビルド確認

実行コマンド:

```bash
cmake -S skia -B skia/cmake-build-phase2-deps \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_AVIF=ON \
  -DRESKIA_ENABLE_JPEGXL=ON \
  -DRESKIA_ENABLE_JPEG_ENCODER=ON \
  -DRESKIA_ENABLE_WEBP_ENCODER=ON \
  -DRESKIA_ENABLE_RAW=ON \
  -DRESKIA_ENABLE_GIF=ON \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-phase2-deps -j 8
```

結果: configure/build 成功（`Built target reskia`）

## Phase 3 への引き継ぎ

1. `cmake/reskia/sources-capi.cmake` の対象コメントアウト解除。
2. `sk_avif_decoder` / `sk_jpegxl_decoder` のコメントアウト実装を復帰し、現行ハンドル型に整合。
3. `sk_jpeg_encoder` / `sk_webp_encoder` の C API 有効化とリンク確認。
4. RAW/GIF 追加分を含む C API（`sources-capi.cmake` 側）の有効化へ進む。
