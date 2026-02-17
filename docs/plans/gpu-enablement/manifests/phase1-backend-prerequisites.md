# Phase 1 Backend Prerequisites

更新日時: 2026-02-17 11:44:28 JST

## 現状観測（Reskia ツリー）

1. `skia/src/gpu` は空ディレクトリのみで、実ファイルは未同期。
2. `skia/include/gpu` も空ディレクトリのみで、公開ヘッダは未同期。
3. `cmake/` と `skia/CMakeLists.txt` に GPU トグルや backend 検出ロジックは未定義。
4. `skia/include/core/SkTypes.h` では `SK_GANESH` / `SK_GRAPHITE` 未定義時に `SK_VULKAN` / `SK_METAL` / `SK_DAWN` が `#undef` される。

## backend 別前提条件（Phase 2 設計入力）

## Ganesh + Metal（macOS）

- OS: Apple プラットフォーム必須
- 必要物:
  - Metal フレームワーク
  - CoreFoundation/QuartzCore など関連フレームワーク（実装参照で確定）
- CMake 条件:
  - `RESKIA_ENABLE_GPU_GANESH=ON`
  - `RESKIA_ENABLE_GPU_METAL=ON`
  - 非Apple なら `FATAL_ERROR`

## Ganesh + Vulkan（非Apple優先）

- OS: クロスプラットフォーム（環境依存）
- 必要物:
  - Vulkan headers
  - Vulkan loader library
- CMake 条件:
  - `RESKIA_ENABLE_GPU_GANESH=ON`
  - `RESKIA_ENABLE_GPU_VULKAN=ON`
  - 依存未検出時は `FATAL_ERROR`

## Graphite（Metal/Vulkan backend）

- 必要物:
  - Graphite 本体ソース
  - 選択 backend（Metal または Vulkan）の SDK/ライブラリ
- CMake 条件:
  - `RESKIA_ENABLE_GPU_GRAPHITE=ON`
  - backend 未選択時は configure エラー

## Dawn（任意・experimental）

- 必要物:
  - Dawn headers/libraries
- CMake 条件:
  - `RESKIA_ENABLE_GPU_DAWN=ON` を明示要求時のみ有効
  - 既定 OFF を維持

## 導入順序（推奨）

1. Ganesh + Metal（macOS）
2. Ganesh + Vulkan
3. Graphite（最小経路）
4. Dawn（experimental）
