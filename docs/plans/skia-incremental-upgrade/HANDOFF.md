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
- `SKIA_REF`: `cd75e467271917846f2b53277028168255e4f485`
- next probe candidate: choose a fixed commit after `cd75e467271917846f2b53277028168255e4f485`
- `vendor/skia-source.lock` は probe が通るまで更新しない。

## 作業の現在地

完了済み:

- C API coverage は `missing 0` / `deferred 0` まで閉じている。
- Phase 30-33 の verification matrix がある。
- 段階的アップグレードの readiness 調査済み。
- 約2週間幅が初回 probe の妥当な目安として選定済み。
- cycle 001 accepted: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`。
- cycle 002 accepted: `f0987bd082ac9bc3d5ed6257c9ecfad18d9b0467`。
- cycle 003 accepted: `596053dde5f0db44e435fb802823524dc01a7637`。
- cycle 004 accepted: `38e85e85079f4140158a8f83c7bbceb7a1ac5ca5`。
- cycle 005 accepted: `126f1add48c34f47b7e1e9fd21ca8c0724748c30`。
- cycle 006 accepted: `ab1e11ab1d10aa598c294b2b1f56ed7c4dd4f823`。
- cycle 007 accepted: `1986c687065ff91583a9f26de66aec2882b59c46`。
- cycle 008 accepted: `dc528310c09aef0e167cac1d456f4a78bf5b53ec`。
- cycle 009 accepted: `c464143dfaab463d553b6f48e73ba6889d1e187f`。
- cycle 010 accepted: `a4ff02094bbd98084cdcf79f7fdc3c1edb150433`。
- cycle 011 accepted: `4346b8f4a1e03ba08e3d80c66084a35a8ccde4d2`。
- cycle 012 accepted: `dfd933f9930cab2e492b5bb99cbd31e431b32ba0`。
- cycle 013 accepted: `76154622bf46eb7b107b437a5d1a032ae6d30344`。
- cycle 014 accepted: `2f07d8e1829ba5bcd0868e3d27e644b87b110598`。
- cycle 015 accepted: `7ffd936a66df500b2275695f6a58208163f31518`。
- cycle 016 accepted: `cd75e467271917846f2b53277028168255e4f485`。

未実施:

- 次サイクル candidate の選定。
- 次サイクル candidate checkout を使った coverage regression。
- 次サイクルの source/header sync と C API 追従実装。

## 次にやること

次の作業は、cycle 017 の candidate selection から始める。

推奨順:

1. baseline `cd75e467271917846f2b53277028168255e4f485` から1-2週間後の固定 commit を第一候補にする。
2. 1週間候補と3週間候補も比較し、commit 数、`include` / `modules` diff、dependency/source-list drift を見る。
3. candidate checkout を用意して coverage regression と stale C API report を取る。
4. 新規 `missing` / `partial` / `overcovered` / `stale_capi` / `signature_changed_review` を area ごとに routing する。
5. low-risk source/header sync と C API catch-up へ進む。

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

## 直近 accepted candidate のメモ

候補:

- `cd75e467271917846f2b53277028168255e4f485`
- committer date: 2024-04-01T21:33:54Z
- subject: `[paragraph] TypefaceFontProvider impl more FontMgr`

cycle 016 結果:

- baseline から 108 commits。
- `include` / `modules` 差分は 31 files, +455/-274。broad surface は 136 files, +4438/-1464。
- 2-week 候補は `missing 12`、3-week 候補は `missing 13` になり、Graphite/Ganesh GPU drift と text-module drift が広がるため、1-week date-end 候補を採用した。
- initial candidate coverage は `missing 3` / `stale_capi 5` / `signature_changed_review 5`。
- final coverage は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- stale C API report は `stale_capi 0`。
- C API catch-up として `Graphite_Recorder_updateCompressedBackendTexture`、`Graphite_TextureInfo_compressionType`、`SkImage_readPixelsGraphite` を追加した。
- Metal backend surface helpers を upstream の namespace-style API に合わせて rename し、旧 stale aliases を削除した。
- `SkImage_readPixelsGraphite` は upstream member が `GRAPHITE_TEST_UTILS` 限定のため、通常 build では false を返す guarded wrapper とした。
- `SkBidiFactory_icu_full/subset` source を `skunicode` target に追加し、ローカル ICU の versioned symbols に合わせて subset wrapper の固定 `_skia` suffix 前提を外した。
- upstream header に残る `SkICCFloatXYZD50ToGrid16Lab` / `SkICCFloatToTable16` の public declarations に対し、Reskia link 互換のため定義を復元した。
- `TypefaceFontProvider` の FontMgr 実装拡張に伴い、paragraph provider smoke は CoreText FontMgr から登録用 typeface を作るよう更新した。
- Metal backend header migration、SkUnicode Bidi factory split、Graphite/Ganesh/Metal source drift を含む 125 files を source/header sync し、2 files を upstream 削除に追従して削除した。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke、Skottie/SKSG optional smoke は pass。
- 次サイクルでは、2-week 候補 `8567db100d685f017915d30996905363fae2658d` で見えていた `missing 12` と stale/signature review 14 rows に注意して、1週間/2週間/3週間候補を再比較する。

cycle records:

- `docs/plans/skia-incremental-upgrade/records/cycle-001-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-002-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-003-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-004-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-005-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-006-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-007-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-008-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-009-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-010-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-011-2026-05-22.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-012-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-013-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-014-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-015-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-016-2026-05-23.md`

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
