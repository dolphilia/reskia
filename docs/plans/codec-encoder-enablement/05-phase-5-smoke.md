# 05 Phase 5: 実行スモーク（最小）

更新日時: 2026-02-16 16:03:40 JST

## 目的

`00-plan.md` の Phase 5 要件に従い、3.8/3.9 対象の C API について最小スモークを追加し、`ctest` で実行可能な状態にする。

## 実装内容

### 1. スモーク実行ファイルを追加

追加ファイル:
- `/Users/dolphilia/github/reskia/skia/test/test_codec_smoke.cpp`

内容:
- Decode（最小）
  - `SkGifDecoder_IsGif` / `SkGifDecoder_DecodeFromData`（1x1 GIF で成功パス）
  - `SkAvifDecoder_IsAvif` / `SkAvifDecoder_DecodeFromData`（entrypoint 呼び出し）
  - `SkJpegxlDecoder_IsJpegxl` / `SkJpegxlDecoder_DecodeFromData`（entrypoint 呼び出し）
  - `SkRawDecoder_IsRaw` / `SkRawDecoder_DecodeFromData`（entrypoint 呼び出し）
- Encode（最小）
  - `SkJpegEncoder_Encode`（2x2 RGBA pixmap を in-memory encode）
  - `SkWebpEncoder_Encode`（2x2 RGBA pixmap を in-memory encode）
  - いずれも `SkDynamicMemoryWStream_bytesWritten` と `SkData_size` が非0であることを確認
- OpenType SVG factory（最小）
  - `SkGraphics_SetOpenTypeSVGDecoderFactory`
  - `SkGraphics_GetOpenTypeSVGDecoderFactory`
  - null を返すダミー factory を登録し、`get` が非 null を返すことを確認

### 2. CMake テスト定義を追加

変更ファイル:
- `/Users/dolphilia/github/reskia/cmake/reskia/tests.cmake`

内容:
- `test_codec_smoke` ターゲット追加
- `c_skia_codec_smoke` を `add_test` 登録
- `RESKIA_ENABLE_*` と連動したコンパイル定義を `test_codec_smoke` へ付与
  - `RESKIA_TEST_ENABLE_AVIF`
  - `RESKIA_TEST_ENABLE_JPEGXL`
  - `RESKIA_TEST_ENABLE_GIF`
  - `RESKIA_TEST_ENABLE_RAW`
  - `RESKIA_TEST_ENABLE_JPEG_ENCODER`
  - `RESKIA_TEST_ENABLE_WEBP_ENCODER`
  - `RESKIA_TEST_ENABLE_OPEN_TYPE_SVG`（Apple のみ）
- テスト実行ファイル向け include path を設定（`test_c_skia` / `test_codec_smoke`）

## 実行コマンド

```bash
cmake -S skia -B skia/cmake-build-phase5-smoke \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_AVIF=ON \
  -DRESKIA_ENABLE_JPEGXL=ON \
  -DRESKIA_ENABLE_RAW=ON \
  -DRESKIA_ENABLE_GIF=ON \
  -DRESKIA_ENABLE_JPEG_ENCODER=ON \
  -DRESKIA_ENABLE_WEBP_ENCODER=ON \
  -DRESKIA_BUILD_TESTS=ON \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build skia/cmake-build-phase5-smoke -j 8 --target test_codec_smoke

ctest --test-dir skia/cmake-build-phase5-smoke -R c_skia_codec_smoke --output-on-failure
```

## 結果

- `test_codec_smoke` ビルド: 成功
- `c_skia_codec_smoke`: 成功（`100% tests passed, 0 tests failed out of 1`）

## 補足

- OpenType SVG factory API は `sk_graphics.h` 側で C++ 宣言として公開した（`SkGraphics::OpenTypeSVGDecoderFactory`）。
