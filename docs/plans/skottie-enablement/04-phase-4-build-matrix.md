# 04 Phase 4: ビルド行列と skottie スモーク

更新日時: 2026-02-17 07:36:26 JST

## 実施内容

1. `test_skottie_smoke.cpp` を追加し、最小 Lottie JSON の load/seek/render を検証。
2. `cmake/reskia/tests.cmake` に `RESKIA_ENABLE_SKOTTIE` 条件でテストターゲット/ctest 登録を追加。
3. `RESKIA_ENABLE_SKOTTIE=ON` + `RESKIA_BUILD_TESTS=ON` で configure/build 実行後、`ctest` でスモークを実行。

## 変更ファイル

- `skia/test/test_skottie_smoke.cpp`（新規）
- `cmake/reskia/tests.cmake`

## スモークテスト仕様（最小）

`test_skottie_smoke.cpp` では以下を確認する。

1. `Skottie_Animation_Make()` が最小 JSON から `Animation` を生成できる。
2. `duration/fps/size` が正値として取得できる。
3. `seek` と `seekFrameTime` が成功する。
4. `SkCanvas_newWithSizeProps` で作成したキャンバスへ `render` / `renderWithFlags` を呼び出せる。
5. 参照解放（`Skottie_Animation_release`）とキャンバス解放で終了する。

## 実行コマンド

```bash
cmake -S skia -B skia/cmake-build-skottie-phase4 \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKOTTIE=ON \
  -DRESKIA_BUILD_TESTS=ON

cmake --build skia/cmake-build-skottie-phase4 --target test_skottie_smoke -j 8

ctest --test-dir skia/cmake-build-skottie-phase4 \
  -R c_skia_skottie_smoke \
  --output-on-failure
```

## 結果

- `test_skottie_smoke` ビルド: 成功
- `ctest` (`c_skia_skottie_smoke`): PASS

出力要約:

- `1/1 Test #4: c_skia_skottie_smoke ... Passed`
- `100% tests passed, 0 tests failed out of 1`

## 補足

- 既知の `test_c_skia` 互換課題の影響を避けるため、Phase 4 の検証は `test_skottie_smoke` ターゲットを明示ビルドし、`ctest -R` で対象テストを絞って実施した。

## Phase 5 への引き継ぎ

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.3 skottie` 状態を更新。
2. `RESKIA_ENABLE_SKOTTIE` の有効化手順・制約（Apple 限定、依存条件）を文書化。
