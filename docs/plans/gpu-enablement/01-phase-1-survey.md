# 01 Phase 1: GPU 実装差分の棚卸しと導入順序確定

更新日時: 2026-02-17 11:44:28 JST

## 目的

Reskia の現行ツリーと upstream Skia の GPU 実装差分を整理し、最小リスクで導入可能な順序を確定する。

## 実施内容

1. `vendor/skia-upstream/src/gpu` を起点に、以下の差分マニフェストを作成する。
- `ganesh`
- `graphite`
- `vk`
- `mtl`
- `dawn`
2. 依存を「共通基盤」「Ganesh 固有」「Graphite 固有」「Backend 固有」に分類する。
3. プラットフォーム別に実行可能な初期導入経路を確定する。
- macOS: `Ganesh + Metal`
- 非Apple: `Ganesh + Vulkan`
- Graphite: Phase 3/4 で最小経路
- Dawn: 後段の任意対応

## 成果物（作成済み）

- `docs/plans/gpu-enablement/manifests/phase1-upstream-gpu-files.txt`
- `docs/plans/gpu-enablement/manifests/phase1-reskia-gpu-files.txt`
- `docs/plans/gpu-enablement/manifests/phase1-gpu-diff.txt`
- `docs/plans/gpu-enablement/manifests/phase1-backend-prerequisites.md`

## 調査結果サマリ

1. `src/gpu` の実ファイル件数
- upstream: `1058`
- Reskia 現行: `0`（空ディレクトリのみ）
2. upstream 側内訳
- `ganesh`: `706`
- `graphite`: `283`
- `common`: `34`
- `vk`: `14`
- `tessellate`: `13`
- `mtl`: `5`
- `dawn`: `3`
3. 差分
- `phase1-gpu-diff.txt` は `1058` 行（全件未同期）
4. 周辺状態
- `skia/src/gpu` はディレクトリ階層のみ存在し、`find skia/src/gpu -type f` は 0 件
- `skia/include/gpu` も同様に 0 件
- CMake 側に `RESKIA_ENABLE_GPU_*` や Vulkan/Metal/Dawn 検出ロジックは未実装

## 導入順序（Phase 1 判定）

1. Step A: Ganesh + Metal（macOS）を先行
- 理由: 現在の開発環境が macOS で、最短で実機検証できる。
2. Step B: Ganesh + Vulkan（非Apple）
- 理由: backend 抽象の共通化を確認しやすく、Graphite 導入前の土台検証になる。
3. Step C: Graphite（Context/Recorder 最小）
- 理由: API 面の追加範囲が広いため、Ganesh の最小経路確立後に分離導入する。
4. Step D: Dawn（experimental）
- 理由: 依存導入負荷が高く、既定 ON にしない運用が妥当。

## 実行コマンド

```bash
mkdir -p docs/plans/gpu-enablement/manifests
find vendor/skia-upstream/src/gpu -type f | sed 's#^vendor/skia-upstream/src/gpu/##' | sort > docs/plans/gpu-enablement/manifests/phase1-upstream-gpu-files.txt
find skia/src/gpu -type f | sed 's#^skia/src/gpu/##' | sort > docs/plans/gpu-enablement/manifests/phase1-reskia-gpu-files.txt
comm -23 docs/plans/gpu-enablement/manifests/phase1-upstream-gpu-files.txt \
  docs/plans/gpu-enablement/manifests/phase1-reskia-gpu-files.txt \
  > docs/plans/gpu-enablement/manifests/phase1-gpu-diff.txt
```

## 判定

Phase 1 は完了。Phase 2 へ進める。

## 次フェーズへの引き継ぎ

1. Phase 2 で `RESKIA_ENABLE_GPU_GANESH/GRAPHITE/VULKAN/METAL/DAWN` のトグルを追加する。
2. `sources-core.cmake` へ追加する際、`phase1-gpu-diff.txt` を一次投入候補集合として使う。
3. backend 依存条件は `phase1-backend-prerequisites.md` を根拠に configure エラー条件へ落とし込む。
