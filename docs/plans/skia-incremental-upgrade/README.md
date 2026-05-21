# Skia Incremental Upgrade

このディレクトリは、`vendor/skia-upstream` を段階的に新しい Skia commit へ進め、Reskia の source/header mirror、C API binding、coverage matrix、build verification を継続的に追従するための計画と作業記録を置く場所である。

段階的アップグレードは一回きりのタスクではなく、固定された Skia commit を小さく選び、probe、routing、実装、verification、lock update を繰り返す運用として扱う。

## 文書

- [00-continuous-upgrade-cycle.md](00-continuous-upgrade-cycle.md): 継続的に回す作業サイクルの計画書。
- [HANDOFF.md](HANDOFF.md): 次の作業者がすぐ作業に入るための引き継ぎ文書。
- [templates/cycle-record-template.md](templates/cycle-record-template.md): 各サイクルの記録テンプレート。

## 現在の初回候補

- branch: `incremental-upgrade`
- baseline: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- first probe candidate: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- candidate date: 2023-12-05T19:49:10Z
- 位置づけ: 約2週間幅の妥当性を検証する最初の upgrade probe。

## 原則

- `vendor/skia-source.lock` は、probe と追従実装が gate を通過するまで更新しない。
- accepted baseline にする条件は、coverage が `missing 0` / `deferred 0` に戻り、代表 build/smoke が通っていること。
- すべての候補 commit、判断、未実装理由、停止理由は記録に残す。
