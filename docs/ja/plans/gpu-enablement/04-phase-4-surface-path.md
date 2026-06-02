# 04 Phase 4: GPU Surface/Texture 最小経路

更新日時: 2026-02-17 12:24:18 JST

## 目的

GPU コンテキストだけでなく、実際に描画できる surface/texture 経路を C API で成立させる。

## 作業項目

1. Ganesh で backend texture / render target から `SkSurface` 生成 API を追加する。
2. Graphite で recorder 経由 surface 作成 API を追加する。
3. backend handle の C 構造体を定義し、Metal/Vulkan 差分を吸収する。
4. flush/sync の最小 API を surface 描画シーケンスに組み込む。

## 変更対象ファイル

- `skia/capi/sk_surface_gpu.h`（新規）
- `skia/capi/sk_surface_gpu.cpp`（新規）
- `skia/capi/reskia_ffi.h`
- `cmake/reskia/sources-capi.cmake`

## 実装進捗（着手）

1. Ganesh surface 生成
- `Reskia_GaneshSurface_MakeRenderTarget` を追加。
- `Reskia_GaneshSurface_WrapBackendTexture` / `Reskia_GaneshSurface_WrapBackendRenderTarget` を追加。
2. Graphite surface 生成
- `Reskia_GraphiteSurface_MakeRenderTarget` を追加。
- `Reskia_GraphiteSurface_WrapBackendTexture` を追加。
3. backend handle C ABI
- `reskia_gpu_backend_texture_handle_t` / `reskia_gpu_backend_render_target_handle_t` を定義。
- backend API を `METAL` / `VULKAN` enum で明示し、ミスマッチ時は `RESKIA_GPU_SURFACE_STATUS_BACKEND_MISMATCH` を返す仕様を追加。
4. 結線
- `reskia_ffi.h` へ `sk_surface_gpu.h` を追加。
- `sources-capi.cmake` へ `capi/sk_surface_gpu.cpp` を追加。
5. 判定基準 1 向け前倒しスモーク
- `test_gpu_surface_capi_smoke.mm` を追加し、C API のみで `surface 作成 -> clear/draw -> flush` 経路を検証。

## 判定基準

1. `surface 作成 -> clear/draw -> flush` が C API で完結する。
2. backend handle の ABI が macOS/非Apple で分離管理され、誤用時に明示エラーとなる。
3. 既存 `SkSurface_*` API と重複/衝突しない命名になっている。

## 実装方針メモ

1. 汎用 API を優先し、backend 固有 API は拡張ヘッダへ隔離する。
2. 初期段階では readback を必須にせず、draw + submit 成功を第一ゲートにする。
3. Graphite は recorder 中心で開始し、texture import は後段拡張に回す。

## 次フェーズへの引き継ぎ

1. Phase 5 で backend 別スモークテスト（context/surface/flush）を追加する。
2. 実行不可構成は依存不足・未実装で分類して記録する。
