# Skia Incremental Upgrade

このディレクトリは、`vendor/skia-upstream` を段階的に新しい Skia commit へ進め、Reskia の source/header mirror、C API binding、coverage matrix、build verification を継続的に追従するための計画と作業記録を置く場所である。

段階的アップグレードは一回きりのタスクではなく、固定された Skia commit を小さく選び、probe、routing、実装、verification、lock update を繰り返す運用として扱う。

## 文書

- [00-continuous-upgrade-cycle.md](00-continuous-upgrade-cycle.md): 継続的に回す作業サイクルの計画書。
- [HANDOFF.md](HANDOFF.md): 次の作業者がすぐ作業に入るための引き継ぎ文書。
- [templates/cycle-record-template.md](templates/cycle-record-template.md): 各サイクルの記録テンプレート。

## 現在地

- branch: `main`
- accepted baseline: `688ca258abd6030f7377a7fa2d22d4e548b8f369`
- baseline date: `2026-06-08`
- latest completed cycle: `docs/ja/plans/skia-incremental-upgrade/records/cycle-092-2026-06-25.md`
- next probe: cycle 093 で baseline 後の固定 local ref を再確認する。次の 1週間候補は `include/private/base` to `include/private` relocation を含む大きな節目なので、split 方針を先に判断する。

## 原則

- `vendor/skia-source.lock` は、probe と追従実装が gate を通過するまで更新しない。
- accepted baseline にする条件は、coverage が `missing 0` / `deferred 0` に戻り、代表 build/smoke が通っていること。
- すべての候補 commit、判断、未実装理由、停止理由は記録に残す。
