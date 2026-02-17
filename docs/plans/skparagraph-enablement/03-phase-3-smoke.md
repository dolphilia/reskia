# 03 Phase 3: 最小実行スモーク整備

更新日時: 2026-02-17 09:33:05 JST

## 実施内容

1. `skia/test/test_skparagraph_smoke.cpp` を追加。
2. `cmake/reskia/tests.cmake` に `c_skia_skparagraph_smoke` を追加。
3. `RESKIA_ENABLE_SKPARAGRAPH=ON` + `RESKIA_BUILD_TESTS=ON` 構成で configure/build/ctest を実行。

## 追加テスト概要

`test_skparagraph_smoke.cpp` は以下を検証する。

1. `FontCollection` + `ParagraphBuilder::make` で paragraph を生成できる。
2. UTF-8（`Hello 日本語\nمرحبا 123`）を追加して `layout(280)` が成立する。
3. `paragraph->getHeight() > 0` と `lineNumber() >= 2` を満たす。
4. `paint` 後の bitmap に非白色ピクセルが存在する。

## 変更ファイル

- `skia/test/test_skparagraph_smoke.cpp`
- `cmake/reskia/tests.cmake`

## 検証コマンドと結果

1. configure
```bash
cmake -S skia -B skia/cmake-build-skparagraph-phase3 \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKPARAGRAPH=ON \
  -DRESKIA_BUILD_TESTS=ON
```
- 成功

2. build（対象テストのみ）
```bash
cmake --build skia/cmake-build-skparagraph-phase3 -j 8 --target test_skparagraph_smoke
```
- 成功

3. 実行
```bash
ctest --test-dir skia/cmake-build-skparagraph-phase3 \
  -R c_skia_skparagraph_smoke --output-on-failure
```
- 成功（`1/1 Test #4: c_skia_skparagraph_smoke ......... Passed`）

## 引き継ぎ

1. Phase 4 で `OFF/ON` のビルド行列に本スモークを組み込み、再現性を確認する。
2. 既存 `test_c_skia` 系の既知課題とは分離して、`c_skia_skparagraph_smoke` を継続監視対象にする。
