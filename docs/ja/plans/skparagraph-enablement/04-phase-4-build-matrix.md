# Phase 4: ビルド行列確認（実績）

実施日時: 2026-02-17 09:38:55 JST - 2026-02-17 09:40:08 JST

## 目的

- `RESKIA_ENABLE_SKPARAGRAPH=OFF/ON` の 2 構成で、configure/build/ctest の行列を確認する。
- `skparagraph` 有効化で `shaping` / `codec` / `skparagraph` の最小スモークが成立することを確認する。

## 実行コマンド

### 1. configure（OFF/ON）

```bash
cmake -S skia -B skia/cmake-build-skparagraph-phase4-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON

cmake -S skia -B skia/cmake-build-skparagraph-phase4-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKPARAGRAPH=ON \
  -DRESKIA_BUILD_TESTS=ON
```

### 2. build（最小スモーク対象）

```bash
cmake --build skia/cmake-build-skparagraph-phase4-off -j 8 \
  --target test_codec_smoke test_shaping_smoke

cmake --build skia/cmake-build-skparagraph-phase4-on -j 8 \
  --target test_codec_smoke test_shaping_smoke test_skparagraph_smoke
```

### 3. ctest（行列確認）

```bash
ctest --test-dir skia/cmake-build-skparagraph-phase4-off --output-on-failure \
  -R 'c_skia_codec_smoke|c_skia_shaping_smoke'

ctest --test-dir skia/cmake-build-skparagraph-phase4-on --output-on-failure \
  -R 'c_skia_codec_smoke|c_skia_shaping_smoke|c_skia_skparagraph_smoke'
```

## 結果

1. `OFF` 構成
- `c_skia_codec_smoke`: PASS
- `c_skia_shaping_smoke`: PASS

2. `ON` 構成
- `c_skia_codec_smoke`: PASS
- `c_skia_shaping_smoke`: PASS
- `c_skia_skparagraph_smoke`: PASS

## 補足（既知制約）

- `test_c_skia` は既存の型不整合（`skia/test/test.cpp`）によりビルド失敗するため、本 Phase の行列は `skparagraph` 有効化可否に直結する最小スモークで評価した。
- 本 Phase の完了条件（`reskia` 本体 build 成功 + paragraph スモーク実行結果記録）は満たしている。
