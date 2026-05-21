# Skia Incremental Upgrade Handoff

作成時刻: 2026-05-22 08:05:52 JST

## 最初に確認すること

この作業は `incremental-upgrade` ブランチで行う。

開始時に確認するコマンド:

```sh
date '+%Y-%m-%d %H:%M:%S %Z'
git branch --show-current
git status --short --branch
sed -n '1,40p' vendor/skia-source.lock
git -C vendor/skia-upstream rev-parse HEAD
git -C vendor/skia-upstream status --short --branch
```

期待する現在値:

- branch: `incremental-upgrade`
- `SKIA_REF`: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- first probe candidate: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- `vendor/skia-source.lock` は probe が通るまで更新しない。

## 作業の現在地

完了済み:

- C API coverage は `missing 0` / `deferred 0` まで閉じている。
- Phase 30-33 の verification matrix がある。
- 段階的アップグレードの readiness 調査済み。
- 約2週間幅が初回 probe の妥当な目安として選定済み。
- 初回 candidate は `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`。

未実施:

- candidate checkout を使った coverage regression。
- candidate root を直接扱う tooling 整備。
- source/header sync。
- C API 追従実装。
- `vendor/skia-source.lock` 更新。

## 次にやること

最初の作業は、実装ではなく probe tooling と記録の整備から始める。

推奨順:

1. `scripts/generate_public_api_coverage.py` が candidate Skia root と stale C API report を受け取れるようにするか、同等の再現可能な probe 手順を用意する。
2. `docs/plans/skia-incremental-upgrade/records/` に初回 cycle record を作る。
3. baseline `0d49b661...` と candidate `5f54e9f...` の public header delta を記録する。
4. coverage regression と stale C API report を取り、新規 `missing` / `partial` / `overcovered` / `stale_capi` / `signature_changed_review` を area ごとに routing する。
5. Core / Codec など低リスク領域の追従可否を確認する。

## やってはいけないこと

- probe 前に `vendor/skia-source.lock` を更新しない。
- floating `main` を baseline として扱わない。
- candidate の差分を1つの大きな implementation batch にしない。
- optional backend や ownership 設計が必要な API を、設計メモなしに C ABI へ露出しない。
- coverage が `missing 0` / `deferred 0` に戻る前に cycle close しない。
- vendor 側で削除された public API に対応する C API を、理由や削除期限なしに残したまま cycle close しない。

## 記録先

サイクル記録:

- `docs/plans/skia-incremental-upgrade/records/`

テンプレート:

- `docs/plans/skia-incremental-upgrade/templates/cycle-record-template.md`

関連調査メモ:

- `docs/notes/skia-incremental-upgrade-readiness-2026-05-22.md`

## 初回 candidate のメモ

候補:

- `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- committer date: 2023-12-05T19:49:10Z
- subject: `Allow undefined format from Android format properties and ability to fallback to importing as external`

選定理由:

- baseline から 181 commits。
- `include` / `modules` 差分は 83 files, +1147/-565。
- Core / Codec / Text / GPU / Module に適度に広がる。
- 12/12 候補ほど Android / Dawn / platform-specific surface が膨らまない。

fallback:

- `600986ba305dcb2c61f02749d992e46d5996a1e7`
- baseline から 88 commits。
- 12/05 候補が重すぎた場合の1週間幅候補。

## Cycle close の条件

次を満たすまで、candidate を accepted baseline にしない。

- coverage matrix が `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- stale C API report が `stale_capi 0`、または残す理由が cycle record に記録されている。
- `signature_changed_review` が出た場合は ABI 互換性の確認結果が記録されている。
- prebuilt `reskia` configure/build が通る。
- source `reskia` configure/build が通る。
- GPU smoke が `PASS` または expected `SKIP`/`PASS`。
- source SVG/provider smoke が通る。
- optional backend / design-required / false_positive / na の理由が記録されている。
- `vendor/skia-source.lock` の更新内容と日付が cycle record に記録されている。
