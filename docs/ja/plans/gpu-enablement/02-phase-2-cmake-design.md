# 02 Phase 2: CMake トグル設計とソース結線

更新日時: 2026-02-17 12:12:08 JST

## 目的

CPU 既定挙動を維持したまま、GPU 機能を段階有効化できる CMake 構成を導入する。

## 実施内容

1. 機能トグルを追加する。
- `RESKIA_ENABLE_GPU_GANESH`（既定 OFF）
- `RESKIA_ENABLE_GPU_GRAPHITE`（既定 OFF）
- `RESKIA_ENABLE_GPU_VULKAN`（既定 OFF）
- `RESKIA_ENABLE_GPU_METAL`（既定 OFF）
- `RESKIA_ENABLE_GPU_DAWN`（既定 OFF）
2. トグル連動で compile definition を制御する。
- `SK_GANESH`
- `SK_GRAPHITE`
- `SK_VULKAN`
- `SK_METAL`
- `SK_DAWN`
3. `cmake/reskia/sources-core.cmake` を GPU セクション分割し、ON 時のみ `SOURCE_FILES` に追加する。
4. プラットフォーム非対応時の `FATAL_ERROR` 条件を定義する（例: 非Appleで `METAL=ON`）。

## 実装結果

1. `cmake/deps/ReskiaDeps.cmake`
- GPU トグル 5 種（Ganesh/Graphite/Vulkan/Metal/Dawn）を追加。
2. `skia/CMakeLists.txt`
- backend と core トグルの整合チェックを追加。
- `RESKIA_ENABLE_GPU_METAL=ON` の Apple 制約を追加。
- `RESKIA_ENABLE_GPU_VULKAN=ON` 時に `find_package(Vulkan REQUIRED)` を追加。
- `RESKIA_ENABLE_GPU_DAWN=ON` 時に Dawn include/lib 検出と必須チェックを追加。
- compile definition 連動（`SK_GANESH`/`SK_GRAPHITE`/`SK_VULKAN`/`SK_METAL`/`SK_DAWN`）を追加。
- `METAL=ON` 時の framework link（`Metal`, `QuartzCore`）を追加。
3. `cmake/reskia/sources-core.cmake`
- GPU セクションを追加し、トグルに応じて `src/gpu` 下のソースを段階収集して `SOURCE_FILES` に追加する実装を追加。
- GPU 有効時に `src/gpu` 実ファイル未同期なら `FATAL_ERROR` で停止するガードを追加。
- `GANESH+METAL` 完走に必要な追加結線として、`src/gpu/tessellate/*.cpp` と `src/text/gpu/*.cpp` を GPU 有効時に段階追加するよう更新。

## 変更対象ファイル

- `cmake/deps/ReskiaDeps.cmake`
- `skia/CMakeLists.txt`
- `cmake/reskia/sources-core.cmake`

## 判定基準

1. 既定（全 OFF）で既存 build と同等動作を維持する。
2. 少なくとも 1 構成（macOS で `GANESH=ON, METAL=ON`）でリンクまで通る。
3. 不正組み合わせ時に、原因が明確な configure エラーになる。

## 検証結果

1. 既定 OFF 経路
```bash
cmake -S skia -B skia/cmake-build-gpu-phase2-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF
cmake --build skia/cmake-build-gpu-phase2-off -j 8
```
- 結果: 成功（`[100%] Built target reskia`）。

2. `GANESH=ON, METAL=ON` 経路（最終再検証）
```bash
cmake -S skia -B skia/cmake-build-gpu-phase2-ganesh-metal \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DRESKIA_ENABLE_GPU_GANESH=ON \
  -DRESKIA_ENABLE_GPU_METAL=ON
cmake --build skia/cmake-build-gpu-phase2-ganesh-metal -j 8
```
- 結果: 成功（`[100%] Built target reskia`）。
- 補足: 再検証途中で発生した link エラー（`skgpu::tess::*`, `sktext::gpu::*` 未解決）は `sources-core.cmake` の追加結線で解消済み。

## 判定

Phase 2 は「トグル設計と段階結線」に加えて、`GANESH+METAL` フルビルド完走まで確認できたため完了。

## 代表コマンド

```bash
cmake -S skia -B skia/cmake-build-gpu-phase2-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF

cmake -S skia -B skia/cmake-build-gpu-phase2-ganesh-metal \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DRESKIA_ENABLE_GPU_GANESH=ON \
  -DRESKIA_ENABLE_GPU_METAL=ON
```

## 次フェーズへの引き継ぎ

1. Phase 3 で必要な C API 実装ファイルを `sources-capi.cmake` に接続する。
2. Ganesh/Graphite の最小公開 API 範囲をヘッダ設計に反映する。
3. backend handle（Metal/Vulkan）の C ABI 固定と、Phase 4 surface API 追加へ接続する。
