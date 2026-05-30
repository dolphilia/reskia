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
- `SKIA_REF`: `ae41c09f89ef33e9f6197455d4d4b939d843687c`
- next probe candidate: choose a fixed commit after `ae41c09f89ef33e9f6197455d4d4b939d843687c`
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
- cycle 017 accepted: `8567db100d685f017915d30996905363fae2658d`。
- cycle 018 accepted: `b159229f2174800f6655f7b7dbba01d7bd3d5d48`。
- cycle 019 accepted: `22d1130a2ba22beb7156d5578f1a9942d1e88bcb`。
- cycle 020 accepted: `a6bc04f984d25bbce342d33ee469b15e93e37698`。
- cycle 021 accepted: `423b224869102f5462a6f15b6a1a558f07f72739`。
- cycle 022 accepted: `78069713e02aae7f03d20114a8bebe8c6a89259a`。
- cycle 023 accepted: `73e53abdf54f56fe30d60dba6e62e19597fa2618`。
- cycle 024 accepted: `51eabd0d1e4466eb427394912eddb6f7a9d0cafb`。
- cycle 025 accepted: `24a4123fc949aad0c98d251b05c8ba2b21a9b931`。
- cycle 026 accepted: `a8c2acc3903806ff36800a67f5e60dba84265fd3`。
- cycle 027 accepted: `7c69f39fa85b3cca07c7d433a396011e01c88f34`。
- cycle 028 accepted: `c73cff97952aa15e01985a35e5c6575b4eb50454`。
- cycle 029 accepted: `84d893159af295c4dc61f408f227cf37916b5b55`。
- cycle 030 accepted: `746d444f3efdc41216d94ae53b07bac3c949f887`。
- cycle 031 accepted: `0a7c7b0b96fc897040e71ea3304d9d6a042cda8b`。
- cycle 032 accepted: `d50960eac8398fd1ad360198944be1376c805486`。
- cycle 033 accepted: `ca108745b1de1ce366393013c441abc8012794f5`。
- cycle 034 accepted: `f60608d53b08f8bf592092941ed2102faa1429bc`。
- cycle 035 accepted: `45bccf339342dfca11887af2c569b5153455d1f1`。
- cycle 036 accepted: `e732cdf455c88501f22154e4a97569f020ffe41d`。
- cycle 037 accepted: `7b0947eb2a6f56c8c7959faa6a5acc5a7b49084e`。
- cycle 038 accepted: `2905e15411bb6d956f58e9b6f0b3fd351731b8fe`。
- cycle 039 accepted: `554b798423c371d187c505b405232c974b266ebc`。
- cycle 040 accepted: `8054b098b5cd313951983effa41f7ae9efa9d9c9`。
- cycle 041 accepted: `a38c4ae0287a1d6d4a57db85b8b52c0d43965deb`。
- cycle 042 accepted: `b4613bade556fa6e5e8264712b2ee8ccf303a959`。
- cycle 043 accepted: `dac808134f758c75b52cd53a4c93f84dea22803a`。
- cycle 044 accepted: `ae41c09f89ef33e9f6197455d4d4b939d843687c`。

未実施:

- cycle 045 candidate の選定。
- cycle 045 candidate checkout を使った coverage regression。
- cycle 045 の source/header sync と C API 追従実装。

## 次にやること

次の作業は、cycle 045 の candidate selection から始める。

推奨順:

1. baseline `ae41c09f89ef33e9f6197455d4d4b939d843687c` から1-2週間後の固定 commit を第一候補にする。
2. 1週間候補と3週間候補も比較し、commit 数、`include` / `modules` diff、dependency/source-list drift を見る。
3. candidate checkout を用意して coverage regression と stale C API report を取る。
4. 新規 `missing` / `partial` / `overcovered` / `stale_capi` / `signature_changed_review` を area ごとに routing する。
5. low-risk source/header sync と C API catch-up へ進む。

cycle 045 の比較候補メモ:

- cycle 044 では `vendor/skia-upstream-candidate` の 2週間候補 `ae41c09f89ef33e9f6197455d4d4b939d843687c` を採用した。baseline `dac808134f...` から 147 commits、`include` / `modules` は 32 files changed, +442/-478、total source-list/dependency drift は 183 files changed, +4177/-2885。
- 1週間候補 `dd163f163584e64a812083e715a1729fd40aeead` は 84 commits、14 `include` / `modules` files、123 total files で軽かったが、Skottie/Graphite drift を次回へ残すため見送った。3週間候補 `5b56d9a916333f5dc594d333293d6ba9f11e914a` は 210 commits、38 `include` / `modules` files、256 total files まで広がったため見送った。
- cycle 044 の新規 gap は `SkSurface::makeTemporaryImage()` と SkSG protected hook signature drift 4件。`SkSurface_makeTemporaryImage` を追加し、SkSG hook は既存の protected/internal policy に沿って `false_positive` 分類した。
- 既知リスクは Graphite precompile ABI design、font scanner variation output の C ABI design、Graphite/Metal deprecation warning、prebuilt static archive の macOS deployment-target warning。

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

- `ae41c09f89ef33e9f6197455d4d4b939d843687c`
- committer date: 2025-02-03T21:41:01-08:00
- subject: `Roll Skia Infra from f69f215a2ce4 to 16948351755e (9 revisions)`

cycle 044 結果:

- `vendor/skia-upstream-candidate` の 2週間候補 `ae41c09f...` を採用した。baseline `dac808134f...` から 147 commits、`include` / `modules` は 32 files changed, +442/-478、total source-list/dependency drift は 183 files changed, +4177/-2885。
- final coverage は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final synced stale C API report と final lock stale report は空。
- 初期 probe の新規 `missing` は `SkSurface::makeTemporaryImage()` と SkSG protected hook signature drift 4件。`SkSurface_makeTemporaryImage` を追加し、SkSG hook は `false_positive` override に分類して閉じた。
- source/header sync では Core/Codec、skcms、Skottie/SKSG、Graphite/Ganesh/Metal/Vulkan/Dawn drift を取り込んだ。新規 `src/core/SkMaskFilterBase.cpp` を `cmake/reskia/sources-core.cmake` に追加し、`SkDrawTypes.h`、`NonMSAAClip.h`、Graphite precompile `SerializationUtils.*` を追加した。削除された `MotionBlurEffect.*` と `AnalyticClip.h` も mirror から削除した。
- upstream `DEPS`、Bazel/GN metadata、CanvasKit は同期対象外として残した。
- GPU build で Metal `fastMathEnabled` deprecation warning、prebuilt/GPU build で既知の macOS deployment-target warning、C API build で `SkPathOps::TightBounds` deprecation warning、test `sprintf` warning が出たが、いずれも non-fatal。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `ae41c09f89ef33e9f6197455d4d4b939d843687c` から再比較する。cycle 044 は 2週間幅が通ったが Graphite source drift は引き続き広めだったため、cycle 045 でも 1/2/3週間候補を比較してから選ぶ。

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
- `docs/plans/skia-incremental-upgrade/records/cycle-017-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-018-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-019-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-020-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-021-2026-05-23.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-022-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-023-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-024-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-025-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-026-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-027-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-028-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-029-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-030-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-031-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-032-2026-05-24.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-033-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-034-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-035-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-036-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-037-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-038-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-039-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-040-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-041-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-042-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-043-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-044-2026-05-30.md`

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
