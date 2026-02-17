# 05 Phase 5: 調査ノート更新と skparagraph 有効化条件の明文化

更新日時: 2026-02-17 09:41:06 JST

## 実施内容

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.4 skparagraph` を未対応から実装反映状態へ更新。
2. 同ノートの関連箇所（`2. upstream modules 比較`, `5. 優先候補`）を整合更新。
3. skparagraph の有効化条件と既知制約（`APPLE` 限定、`source` モード限定、HarfBuzz 必須、C API 未実装）を明文化。
4. `ctest -R c_skia_skparagraph_smoke` を再実行し、PASS を再確認。

## 変更ファイル

- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`
- `docs/plans/skparagraph-enablement/05-phase-5-smoke-and-docs.md`（本ファイル）

## skparagraph 有効化条件（再現用）

前提:

1. プラットフォームは `APPLE`（現状 `RESKIA_ENABLE_SKPARAGRAPH=ON` は Apple 限定）。
2. `RESKIA_DEPS_MODE=source`（現状 `source` モード限定）。
3. `skshaper` / `skunicode` が source モードで解決されること。
4. HarfBuzz（`hb.h` と `libharfbuzz`）が `third_party/install` などの探索パスにあること。

configure/build:

```bash
cmake -S skia -B skia/cmake-build-skparagraph-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKPARAGRAPH=ON \
  -DRESKIA_BUILD_TESTS=ON

cmake --build skia/cmake-build-skparagraph-on -j 8 --target test_skparagraph_smoke
```

スモークテスト:

```bash
ctest --test-dir skia/cmake-build-skparagraph-phase4-on \
  -R c_skia_skparagraph_smoke \
  --output-on-failure
```

期待結果:

1. `test_skparagraph_smoke` がビルドされる。
2. `c_skia_skparagraph_smoke` が `Passed`。

## 検証結果

実行コマンド:

```bash
ctest --test-dir skia/cmake-build-skparagraph-phase4-on -R c_skia_skparagraph_smoke --output-on-failure
```

結果要約:

- `1/1 Test #4: c_skia_skparagraph_smoke ......... Passed`
- `100% tests passed, 0 tests failed out of 1`

## 完了判定

1. 機能ギャップ調査 `3.4` が実装後状態に更新された。
2. skparagraph の有効化条件・縮退条件・既知制約が再現可能な粒度で文書化された。
