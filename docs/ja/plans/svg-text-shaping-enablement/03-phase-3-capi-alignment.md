# 03 Phase 3: C API 公開面の最小有効化

更新日時: 2026-02-17 04:40:42 JST

## 実施内容

1. `cmake/reskia/sources-capi.cmake` で `capi/sk_text_blob_builder_run_handler.cpp` を有効化。
2. `SkShaper::RunHandler::Buffer` 用の static handle 実装を追加。
3. `sk_text_blob_builder_run_handler.cpp` を internal handle API に接続。
4. include 解決失敗を避けるため、`SkShaper.h` の参照先を実ツリーに合わせて修正。

## 変更ファイル

- `/Users/dolphilia/github/reskia/cmake/reskia/sources-capi.cmake`
- `/Users/dolphilia/github/reskia/cmake/reskia/sources-handles.cmake`
- `/Users/dolphilia/github/reskia/skia/capi/sk_text_blob_builder_run_handler.cpp`
- `/Users/dolphilia/github/reskia/skia/capi/sk_text_blob_builder_run_handler.h`
- `/Users/dolphilia/github/reskia/skia/handles/static_sk_shaper_run_handler_buffer.h`
- `/Users/dolphilia/github/reskia/skia/handles/static_sk_shaper_run_handler_buffer-internal.h`
- `/Users/dolphilia/github/reskia/skia/handles/static_sk_shaper_run_handler_buffer.cpp`

## ビルド検証

実行コマンド:

```bash
cmake -S skia -B skia/cmake-build-phase3-capi \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-phase3-capi -j 8
```

結果:

- `Built target reskia` を確認。
- `sk_text_blob_builder_run_handler.cpp` と `static_sk_shaper_run_handler_buffer.cpp` を含む構成でリンク成功。

## 補足

- `reskia_ffi.h` への `sk_text_blob_builder_run_handler.h` 統合は、ヘッダ解決条件を広げる副作用があるため今回は採用しない。
- 公開面は「対象 C API 実装をビルド可能化する最小変更」に限定した。
