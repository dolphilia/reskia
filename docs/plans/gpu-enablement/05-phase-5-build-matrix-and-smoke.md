# 05 Phase 5: Build 行列と GPU スモーク

更新日時: 2026-02-17 12:24:18 JST

## 目的

GPU 有効化を再現可能にするため、構成行列を固定し、最小スモークテストを通す。

## 検証行列（最小）

1. macOS: `GANESH=ON` + `METAL=ON`
2. 非Apple（可能環境）: `GANESH=ON` + `VULKAN=ON`
3. 任意: `GRAPHITE=ON`（Metal または Vulkan どちらか）
4. 任意: `DAWN=ON`

## スモーク項目

1. context/recorder の生成と破棄
2. surface 作成と最小描画（clear + 1 draw）
3. flush/submit の成功
4. 可能なら readback または encode までの 1 経路

## テスト配置案

- `skia/test/test_gpu_context_smoke.cpp`
- `skia/test/test_gpu_surface_smoke.cpp`
- `cmake/reskia/tests.cmake` への登録

## 前倒し実装（Phase 4.5）

1. C API のみで `surface 作成 -> clear/draw -> flush` を検証するスモークを追加。
- 追加ファイル: `skia/test/test_gpu_surface_capi_smoke.mm`
- 登録: `cmake/reskia/tests.cmake`（`APPLE && RESKIA_ENABLE_GPU_GANESH && RESKIA_ENABLE_GPU_METAL` 条件）
2. 実行不可環境の分類を追加。
- `MTLCreateSystemDefaultDevice` が取得できない場合は `SKIP` を出力して成功終了し、環境制約として扱う。

## 判定基準

1. 主要 1 構成以上でスモークが 0 exit。
2. 失敗構成は原因分類（依存不足/未実装/環境制約）が記録される。
3. 既定 OFF 構成の回帰がない。

## 代表コマンド

```bash
cmake -S skia -B skia/cmake-build-gpu-smoke-metal \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON \
  -DRESKIA_ENABLE_GPU_GANESH=ON \
  -DRESKIA_ENABLE_GPU_METAL=ON
cmake --build skia/cmake-build-gpu-smoke-metal -j 8
ctest --test-dir skia/cmake-build-gpu-smoke-metal --output-on-failure
```

## 実施結果（前倒し）

1. `test_gpu_surface_capi_smoke` ターゲットはビルド成功。
2. `ctest -R c_skia_gpu_surface_capi_smoke` は成功（環境により `PASS` または `SKIP` 分類）。

## 次フェーズへの引き継ぎ

1. Phase 6 で結果を docs へ反映し、公開ポリシーを確定する。
