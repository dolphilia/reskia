# Skia Incremental Upgrade

このディレクトリは、`vendor/skia-upstream` を段階的に新しい Skia commit へ進め、Reskia の source/header mirror、C API binding、coverage matrix、build verification を継続的に追従するための計画と作業記録を置く場所である。

段階的アップグレードは一回きりのタスクではなく、固定された Skia commit を小さく選び、probe、routing、実装、verification、lock update を繰り返す運用として扱う。

## 文書

- [00-continuous-upgrade-cycle.md](00-continuous-upgrade-cycle.md): 継続的に回す作業サイクルの計画書。
- [HANDOFF.md](HANDOFF.md): 次の作業者がすぐ作業に入るための引き継ぎ文書。
- [templates/cycle-record-template.md](templates/cycle-record-template.md): 各サイクルの記録テンプレート。

## 現在地

- branch: `incremental-upgrade`
- accepted baseline: `73e53abdf54f56fe30d60dba6e62e19597fa2618`
- baseline date: 2024-06-04T20:41:40Z
- latest completed cycle: `docs/plans/skia-incremental-upgrade/records/cycle-023-2026-05-24.md`
- next probe: cycle 024 で baseline から 1週間/2週間/3週間候補を比較する。2-week 候補 `24a4123fc949aad0c98d251b05c8ba2b21a9b931` は標準幅だが `include`/`modules` insertions が大きいため、1-week 候補 `51eabd0d1e4466eb427394912eddb6f7a9d0cafb` と差分内容を比較して選ぶ。

## 原則

- `vendor/skia-source.lock` は、probe と追従実装が gate を通過するまで更新しない。
- accepted baseline にする条件は、coverage が `missing 0` / `deferred 0` に戻り、代表 build/smoke が通っていること。
- すべての候補 commit、判断、未実装理由、停止理由は記録に残す。
