# 01 Phase 1: modules/skparagraph 同期と依存棚卸し

更新日時: 2026-02-17 07:44:18 JST

## 実施内容

1. `vendor/skia-upstream/modules/skparagraph` を `skia/modules/skparagraph` へ同期。
2. 同期差分確認（`rsync -ain --delete`）で差分ゼロを確認。
3. `skparagraph.gni` を根拠に、Phase 2 で CMake へ移植する初期対象ファイルをマニフェスト化。

実行コマンド:

```bash
rsync -a vendor/skia-upstream/modules/skparagraph/ skia/modules/skparagraph/
```

## 成果物（マニフェスト）

- `docs/plans/skparagraph-enablement/manifests/upstream-skparagraph-files.txt`
- `docs/plans/skparagraph-enablement/manifests/local-skparagraph-files.txt`
- `docs/plans/skparagraph-enablement/manifests/phase1-selected-module-files.txt`

## 同期結果

1. ファイル件数一致:
- `skparagraph`: upstream 56 / local 56

2. `rsync -ain --delete` に差分なし:
- `vendor/skia-upstream/modules/skparagraph` -> `skia/modules/skparagraph`

## Phase 1 判定（初期取り込みポリシー）

1. 初期移植対象は `modules/skparagraph/skparagraph.gni` の `skparagraph_public` と `skparagraph_sources` を基準にする。
2. 初期段階では以下を CMake 対象から除外する。
- `bench/`（ベンチ）
- `gm/`（GM）
- `slides/`（スライド）
- `tests/`（テスト専用）
- `BUILD.gn` / `BUILD.bazel` / `test.html`（ビルド定義・補助）
3. `phase1-selected-module-files.txt` には上記方針で 38 ファイルを保持する（`include/`, `src/`, `utils/TestFontCollection.*`）。

## Phase 2 への引き継ぎ

1. `RESKIA_ENABLE_SKPARAGRAPH` トグルを追加する。
2. `skia/CMakeLists.txt` で `RESKIA_ENABLE_SKPARAGRAPH=ON` 時のみ `skparagraph` source を条件付き取り込みする。
3. 有効条件（`skshaper`, `skunicode`, HarfBuzz）を configure 時に検証し、未解決時は明示エラーで停止する。

## configure/build 検証（Phase 1 時点）

実行コマンド:

```bash
cmake -S skia -B skia/cmake-build-skparagraph-phase1 -DRESKIA_BUILD_TESTS=OFF
cmake --build skia/cmake-build-skparagraph-phase1 -j 8
```

結果:

1. configure: 成功
2. build: 失敗（`libreskia.dylib` リンク時）
- `sk_text_blob_builder_run_handler.cpp` 由来の `SkTextBlobBuilderRunHandler::*` 未解決シンボルで停止
- 本失敗は `skparagraph` 同期前から存在するテキストシェーピング経路のリンク課題で、Phase 2 で依存条件を明示しながら併せて解消確認する
