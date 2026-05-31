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
- `SKIA_REF`: `844288bf88af93e6ee50ebf1b4f473c79d2ee176`
- next probe candidate: choose a fixed commit after `844288bf88af93e6ee50ebf1b4f473c79d2ee176`
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
- cycle 045 accepted: `1f2c4409ef78c158586a058acb5fcf8bdfd13e4c`。
- cycle 046 accepted: `0c3880f949701a44ad4ebd86f4843c2eeebbb41d`。
- cycle 047 accepted: `de4799f97cd0b4bd971d016ed179f8c854ef4c29`。
- cycle 048 accepted: `bc81df52bfa0d842b73d20d9f309b4e1540905a3`。
- cycle 049 accepted: `3dc3ffeb45f0d3decf40f876c9d7600f163e053c`。
- cycle 050 accepted: `fd69db63210f06f024f65a2b9981a6a76b363f46`。
- cycle 051 accepted: `cb1646ca59dbaa37c07a8697c2cb9a0451853932`。
- cycle 052 accepted: `e56aa7634d2667c25f360c0c4073e996d54d459b`。
- cycle 053 accepted: `91dc88dc70e5c7e8debbe21d4d5566d5e9f121e1`。
- cycle 054 accepted: `6366bcd2e0c185b433b51245483dec2b29fb2675`。
- cycle 055 accepted: `9100700840668a8a3276c05f114463f9b8c7a264`。
- cycle 056 accepted: `80bffd1ae51733a54cbfbf777a38060e2f8e5c30`。
- cycle 057 accepted: `f8cd9fe75f21d3be759cbf9491ddc582efcf1e2a`。
- cycle 058 accepted: `203469ef4672898f1190088a8a13a1538db59485`。
- cycle 059 accepted: `2dc747ddcc4ef84284de56e69382b00bcefaa06d`。
- cycle 060 accepted: `e84f5ed7d152063a4efd1399eb379305ebe5d3d6`。
- cycle 061 accepted: `92354f64e37f96bec944fb20256e85a8925f9fe5`。
- cycle 062 accepted: `df39eefbeef3d86d8237d24692208b9ba78d1c5d`。
- cycle 063 accepted: `fb7334edc4de5833a67324e6bca1a9143dd4d607`。
- cycle 064 accepted: `46ec77ae39545acb1d6734028d9e2fbfef55f1c3`。
- cycle 065 accepted: `844288bf88af93e6ee50ebf1b4f473c79d2ee176`。

未実施:

- cycle 066 candidate の選定。
- cycle 066 candidate checkout を使った coverage regression。
- cycle 066 の source/header sync と C API 追従実装。

## 次にやること

次の作業は、cycle 066 の candidate selection から始める。

推奨順:

1. baseline `844288bf88af93e6ee50ebf1b4f473c79d2ee176` から1週間程度の固定 commit を第一候補にする。
2. 1週間候補と必要に応じて2-3週間候補も比較し、commit 数、`include` / `modules` diff、dependency/source-list drift を見る。
3. candidate checkout を用意して coverage regression と stale C API report を取る。
4. 新規 `missing` / `partial` / `overcovered` / `stale_capi` / `signature_changed_review` を area ごとに routing する。
5. low-risk source/header sync と C API catch-up へ進む。

cycle 066 の比較候補メモ:

- cycle 065 では baseline `46ec77ae39545acb1d6734028d9e2fbfef55f1c3` から `844288bf88af93e6ee50ebf1b4f473c79d2ee176` を採用した。189 commits、`include` / `modules` は 34 files changed, +919/-170、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 202 files changed, +4736/-2781。
- cycle 065 の主変更は `SkPath` / `SkPathBuilder` iterator API、new `SkPathIter` / `SkPathContourIter`、SkParagraph style accessors、Graphite precompile WCS overload、SkColorFilters signature drift、skcms/prebuilt compatibility drift。
- cycle 065 の初期 missing は 15 rows、初期 stale/signature report は 2 rows。Path iterator API と Paragraph/TextStyle accessor を追加し、`PrecompileShader::makeWithWorkingColorSpace(inputCS, outputCS)` は Graphite precompile ABI 設計待ちとして `na` に分類した。
- cycle 065 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final lock stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text/path smoke は pass。
- 次 cycle では accepted baseline `844288bf88af93e6ee50ebf1b4f473c79d2ee176` から再比較する。path iterator/raw churn、Graphite precompile/render churn、skcms/prebuilt compatibility drift、Android font/GPU helper drift、ANGLE/Dawn/Vulkan rolls が継続リスク。

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

- `844288bf88af93e6ee50ebf1b4f473c79d2ee176`
- committer date: 2025-08-30T18:35:39-07:00
- subject: Roll vulkan-deps from f2cd9d27d5a9 to e1c9d5968038 (2 revisions)

cycle 065 結果:

- baseline `46ec77ae...` から `844288bf...` を採用した。189 commits、`include` / `modules` は 34 files changed, +919/-170、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 202 files changed, +4736/-2781。
- `SkPath_iter`、`SkPathBuilder_iter`、`SkPathIter_*`、`SkPathContourIter_*`、ParagraphStyle fake-missing-font accessors、TextStyle edging/subpixel/hinting accessors を追加した。
- `PrecompileShader::makeWithWorkingColorSpace(inputCS, outputCS)` は Graphite precompile ABI 設計待ちとして `na` に分類した。
- tracked mirror surface の core path/raw/iterator、Graphite precompile/render/Vulkan、skcms、skparagraph/skunicode/skshaper、ports/shaders/sksl drift を同期した。prebuilt `libsvg.a` の旧 `SkColorFilters::Matrix(const SkColorMatrix&)` 参照には Apple private ABI shim を追加した。
- final coverage は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final lock stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text/path smoke は pass。
- 次サイクルでは、accepted baseline `844288bf88af93e6ee50ebf1b4f473c79d2ee176` から再比較する。既知リスクは path iterator/raw churn、Graphite precompile/render churn、skcms/prebuilt compatibility drift、Android font/GPU helper drift、ANGLE/Dawn/Vulkan rolls。

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
- `docs/plans/skia-incremental-upgrade/records/cycle-045-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-046-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-047-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-048-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-049-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-050-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-051-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-052-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-053-2026-05-30.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-054-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-055-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-056-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-057-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-058-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-059-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-060-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-061-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-062-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-063-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-064-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-065-2026-05-31.md`

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
