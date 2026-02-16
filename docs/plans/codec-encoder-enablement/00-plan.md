# 00 Plan: Codec Extensions / Encoders 有効化

作成日時: 2026-02-16 14:36:48 JST

## ゴール

`reskia` で以下を C API から利用可能にし、`cmake --build` と最小スモーク実行まで通す。

- Decode: AVIF / JPEGXL / GIF / RAW / OpenType SVG
- Encode: JPEG / WebP

## 対象ファイル（主）

- `cmake/reskia/sources-core.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/deps/ReskiaDeps.cmake`
- `skia/capi/sk_avif_decoder.{h,cpp}`
- `skia/capi/sk_jpegxl_decoder.{h,cpp}`
- `skia/capi/sk_gif_decoder.{h,cpp}`
- `skia/capi/sk_raw_decoder.{h,cpp}`
- `skia/capi/sk_open_type_svg_decoder.{h,cpp}`
- `skia/capi/sk_jpeg_encoder.{h,cpp}`
- `skia/capi/sk_webp_encoder.{h,cpp}`
- `skia/test/*`（スモーク追加時）

## 現状ギャップ（着手前の事実）

1. `sources-capi.cmake` で `sk_gif_decoder` / `sk_raw_decoder` / `sk_open_type_svg_decoder` / `sk_jpeg_encoder` / `sk_webp_encoder` がコメントアウト。
2. `sk_avif_decoder` / `sk_jpegxl_decoder` は `.cpp/.h` とも関数宣言・実装がコメントアウト。
3. `sources-core.cmake` で `SkAvifCodec.cpp` / `SkJpegxlCodec.cpp` がコメントアウト。
4. `skia/include/encode/SkWebpEncoder.h` と `skia/src/encode/SkWebpEncoder*.cpp` が現ツリーに存在しない（`vendor/skia-upstream` には存在）。
5. `RAW` は `SkRawCodec.cpp` が必要で、`dng_sdk` / `piex` / include path の整備が必要。

## 実施フェーズ

### Phase 1: 依存マトリクス固定と有効化ポリシー決定

1. `prebuilt/source/system` 各モードで必要ライブラリを機能別に表化する。
2. `cmake/deps/ReskiaDeps.cmake` に機能トグルを追加する。
- 追加候補: `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_WEBP_ENCODER`
3. `JPEGXL` 用リンク定義を追加する（例: `jxl`, `jxl_threads`, 必要に応じて `jxl_cms`）。
4. compile definition を機能トグルと連動させる。
- 例: `SK_CODEC_DECODES_AVIF`, `SK_CODEC_DECODES_JPEGXL`, `SK_CODEC_DECODES_RAW`

完了条件:
- configure 時に「有効化した機能に必要な依存不足」が即時検出される。

### Phase 2: Skia本体ソース不足の補完

1. `vendor/skia-upstream` から不足実装を同期する。
- WebP encoder: `include/encode/SkWebpEncoder.h`, `src/encode/SkWebpEncoder*.cpp`
- JPEG encoder: `src/encode/SkJpegEncoder*.cpp`（現ツリー欠落分のみ）
2. `RAW` / `GIF` 用に必要な third_party 資産を補完する。
- `third_party/dng_sdk`（RAW）
- `third_party/piex`（RAW）
- `third_party/wuffs`（GIF）
3. `sources-core.cmake` に以下を機能トグル付きで追加する。
- `src/codec/SkAvifCodec.cpp`
- `src/codec/SkJpegxlCodec.cpp`（必要に応じて `SkJpegXmp.cpp`）
- `src/codec/SkRawCodec.cpp`
- `src/codec/SkWuffsCodec.cpp`
- `src/encode/SkJpegEncoder*.cpp`
- `src/encode/SkWebpEncoder*.cpp`

完了条件:
- 追加した core ソースが単体でコンパイル可能。

### Phase 3: C API の有効化と型整合

1. `sources-capi.cmake` で対象ファイルのコメントアウトを解除。
2. `sk_avif_decoder` / `sk_jpegxl_decoder` の宣言・実装コメントを解除し、現行 C API スタイルへ寄せる。
- `int static_stream/static_data` ではなく `sk_stream_t/sk_data_t` に統一。
3. `sk_raw_decoder` も同様に引数型を現行化。
4. `sk_webp_encoder` は upstream 同期済み `SkWebpEncoder.h` へ合わせてシグネチャ確認。
5. `sk_open_type_svg_decoder` は `svg` 連携条件（Apple依存）を明示し、非対応環境では API を no-op または未提供にする方針を固定。

完了条件:
- 対象 C API が全てリンク可能（未解決シンボルなし）。

### Phase 4: ビルド行列での回帰確認

1. まず `prebuilt` で確認。
```bash
cmake -S skia -B skia/cmake-build-codec-prebuilt \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_AVIF=ON \
  -DRESKIA_ENABLE_JPEGXL=ON \
  -DRESKIA_ENABLE_RAW=ON \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codec-prebuilt -j 8
```
2. `source/system` も同一オプションで configure/build し、欠落依存を洗い出す。
3. `RAW` は依存未充足時に `OFF` へフォールバック可能であることを確認する。

完了条件:
- 少なくとも 1 モードで全機能 ON ビルド成功。
- それ以外モードも「失敗理由が依存不足として明示」される。

### Phase 5: 実行スモーク（最小）

ステータス: 完了（2026-02-16 16:03:40 JST）

1. `skia/test` に codec/encoder スモークを追加（または既存 `test_c_skia` 拡張）。
2. 最小検証を実施する。
- Decode: AVIF/JPEGXL/GIF/RAW の `Is*` と `Decode*`
- Encode: JPEG/WebP の encode 実行と生成バイト非空チェック
3. OpenType SVG はフォント依存が大きいため、factory 登録/呼び出し到達を最小確認にする。

完了条件:
- `ctest` または専用テスト実行で 0 exit。

実績:
- 追加テスト: `/Users/dolphilia/github/reskia/skia/test/test_codec_smoke.cpp`
- CMake 登録: `/Users/dolphilia/github/reskia/cmake/reskia/tests.cmake`
- OpenType SVG factory の C API 露出: `/Users/dolphilia/github/reskia/skia/capi/sk_graphics.h`, `/Users/dolphilia/github/reskia/skia/capi/sk_graphics.cpp`
- 実行結果: `ctest --test-dir skia/cmake-build-phase5-smoke -R c_skia_codec_smoke --output-on-failure` で `100% tests passed, 0 tests failed out of 1`
- 詳細記録: `/Users/dolphilia/github/reskia/docs/plans/codec-encoder-enablement/05-phase-5-smoke.md`

## 判定ゲート（途中判断）

1. `RAW` 依存（`dng_sdk/piex`）を短期で取り込めない場合:
- 先行リリースでは `RESKIA_ENABLE_RAW=OFF` 既定にして、他機能を先に完了させる。
2. `WebP encoder` 実装同期が想定より大きい場合:
- 一時的に JPEG encoder を先行有効化し、WebP は別PRに分離。

## 成果物

- CMake: 依存トグルと source list 更新
- C API: 3.8 / 3.9 対象APIの有効化
- テスト: codec/encoder スモーク
- ドキュメント: 有効化オプションと制約（README または `docs/notes` 追記）

## 完了定義（Definition of Done）

1. 3.8/3.9 対象 API が CMake 上で有効（コメントアウトなし）。
2. `reskia` がビルド成功し、対象 API 呼び出しで実行確認が取れている。
3. 依存不足時の挙動（どのオプションを OFF にするか）が明文化されている。
