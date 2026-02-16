# 05 Phase 5: 調査ノート更新と skottie 有効化手順

更新日時: 2026-02-17 07:38:20 JST

## 実施内容

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.3 skottie` を未対応から実装反映状態へ更新。
2. 同ノートの関連箇所（`2. upstream modules 比較`, `3.5 sksg`, `4. C binding 件数`, `5. 優先候補`）を整合更新。
3. 有効化手順（トグル、前提条件、build/test コマンド、既知制約）を本書に明文化。
4. `ctest -R c_skia_skottie_smoke` を再実行し、PASS を再確認。

## 変更ファイル

- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`
- `docs/plans/skottie-enablement/05-phase-5-smoke-and-docs.md`（本ファイル）

## skottie 有効化手順（再現用）

前提:

1. プラットフォームは `APPLE`（現状 `RESKIA_ENABLE_SKOTTIE=ON` は Apple 限定）。
2. `skia/modules/sksg` と `skia/modules/skottie` が同期済み。
3. `RESKIA_DEPS_MODE=source` を使う場合、`skresources` と `svg` を解決できること。

configure/build:

```bash
cmake -S skia -B skia/cmake-build-skottie-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKOTTIE=ON \
  -DRESKIA_BUILD_TESTS=ON

cmake --build skia/cmake-build-skottie-on -j 8
```

スモークテスト:

```bash
ctest --test-dir skia/cmake-build-skottie-on \
  -R c_skia_skottie_smoke \
  --output-on-failure
```

期待結果:

1. `test_skottie_smoke` がビルドされる。
2. `c_skia_skottie_smoke` が `Passed`。

## 既知制約

1. `RESKIA_ENABLE_SKOTTIE=ON` は非 Apple 環境で `FATAL_ERROR`。
2. C API は最小ライフサイクル（load/seek/render/release）に限定。
3. GPU 経路（Ganesh/Graphite）の追加は本フェーズ対象外。

## 検証結果

実行コマンド:

```bash
ctest --test-dir skia/cmake-build-skottie-phase4 -R c_skia_skottie_smoke --output-on-failure
```

結果要約:

- `1/1 Test #4: c_skia_skottie_smoke ... Passed`
- `100% tests passed, 0 tests failed out of 1`

## 完了判定

1. 機能ギャップ調査 `3.3` が実装後状態に更新された。
2. skottie の有効化条件と実行手順が第三者再現可能な粒度で文書化された。
