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
- `SKIA_REF`: `70f9d90bc8e6a56101d036153cfef28088e57f5b`
- next probe candidate: start from `70f9d90bc8e6a56101d036153cfef28088e57f5b`; cycle 091 consumed the currently available local refs through `70f9d90bc8e6a56101d036153cfef28088e57f5b` (committer date 2026-06-01). Begin cycle 092 by rechecking local refs for fixed commits after this baseline. If no newer fixed commit exists, record candidate absence without treating floating `main` as baseline.
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
- cycle 066 split-required: local refs did not contain a fixed commit after `844288bf88af93e6ee50ebf1b4f473c79d2ee176`; lock unchanged.
- cycle 067 accepted: `7a8e9f5d35d8d08c10da95ea8e0d872b995c43f3`。
- cycle 068 accepted: `1c10d9bb7d5846f08c474538b400f61a10a507fb`。
- cycle 069 accepted: `ec032dbe0e04e305b06bfc7a01dd6d2e1d5f3dc8`。
- cycle 070 accepted: `9a43169d5cadb5c3a56e78c6d19ca71b51097e5e`。
- cycle 071 accepted: `0682b51e060f4f82b757f0872cf5d8e380540213`。
- cycle 072 accepted: `5e03cbcadaf57b0d6a16029a08627f924d3c7352`。
- cycle 073 accepted: `d13c1deb15577be689ef622de3c9bc7299cd0579`。
- cycle 074 accepted: `e3c2686662294e45d56923b21c991c32a6c0863d`。
- cycle 075 accepted: `b1569739f431d0b0f974f639c9356b06400682e9`。
- cycle 076 accepted: `1a5fb55a686feacb0103d15fcac869fac279a06d`。
- cycle 077 accepted: `a1f0df04bd133ec1594cd7fd463ed57845464b47`。
- cycle 078 accepted: `bef2a0fe6b96f0a067e26abfdac4ae4f8f588f20`。
- cycle 079 accepted: `dcbb6588a6c54754b1bf6251531fed974e80ce18`。
- cycle 080 accepted: `ed220c490eea2ab10fcefe1a5786262724499b88`。
- cycle 081 accepted: `38761e1803d05e0eca689a296a4ed6ab20e0323f`。
- cycle 082 accepted: `3f328b35d929c70d2ef57599c8e3872e4db867a8`。
- cycle 083 accepted: `e4d0350f477005ae71691642ec0db96cce7e3266`。
- cycle 084 accepted: `812822ad5caa8f39ff4cf5ab96f48fe942562252`。
- cycle 085 accepted: `f04d09d1075926a5e5ef0a52171c9c12043fab03`。
- cycle 086 accepted: `aba405ee605f2578f3054bc4d997e2f32f57f291`。
- cycle 087 accepted: `f37239a7a689d64268b73fc7eb45b5c40a7f7013`。
- cycle 088 accepted: `bda7232e6772bcc585435ae760983d6d43aa1155`。
- cycle 089 accepted: `7b88c5c281e587c267457dba51f53e0b962c1748`。
- cycle 090 accepted: `3b718ddc8ae51dbfb311afe02c35a83dd7999172`。
- cycle 091 accepted: `70f9d90bc8e6a56101d036153cfef28088e57f5b`。

未実施:

- cycle 092 candidate selection from `70f9d90bc8e6a56101d036153cfef28088e57f5b`.
- cycle 092 candidate checkout を使った coverage regression。
- cycle 092 の source/header sync と C API 追従実装。

## 次にやること

次の作業は、cycle 092 の candidate selection から始める。

推奨順:

1. baseline `70f9d90bc8e6a56101d036153cfef28088e57f5b` より後の固定 mainline commit を local refs から選ぶ。
2. `vendor/skia-upstream-candidate` の refs を優先する。cycle 091 終了時点で local refs は accepted candidate `70f9d90bc8e6a56101d036153cfef28088e57f5b` まで確認済み。1週間/2週間/3週間候補を再比較する。候補がない場合は無理に floating `main` へ進まず cycle record / HANDOFF に記録する。
3. 1週間候補と必要に応じて2-3週間候補も比較し、commit 数、`include` / `modules` diff、dependency/source-list drift を見る。
4. candidate checkout を用意して coverage regression と stale C API report を取る。
5. 新規 `missing` / `partial` / `overcovered` / `stale_capi` / `signature_changed_review` を area ごとに routing する。
6. low-risk source/header sync と C API catch-up へ進む。

cycle 072 の比較候補メモ:

- cycle 065 では baseline `46ec77ae39545acb1d6734028d9e2fbfef55f1c3` から `844288bf88af93e6ee50ebf1b4f473c79d2ee176` を採用した。189 commits、`include` / `modules` は 34 files changed, +919/-170、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 202 files changed, +4736/-2781。
- cycle 065 の主変更は `SkPath` / `SkPathBuilder` iterator API、new `SkPathIter` / `SkPathContourIter`、SkParagraph style accessors、Graphite precompile WCS overload、SkColorFilters signature drift、skcms/prebuilt compatibility drift。
- cycle 065 の初期 missing は 15 rows、初期 stale/signature report は 2 rows。Path iterator API と Paragraph/TextStyle accessor を追加し、`PrecompileShader::makeWithWorkingColorSpace(inputCS, outputCS)` は Graphite precompile ABI 設計待ちとして `na` に分類した。
- cycle 065 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final lock stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text/path smoke は pass。
- 次 cycle では accepted baseline `844288bf88af93e6ee50ebf1b4f473c79d2ee176` から再比較する。path iterator/raw churn、Graphite precompile/render churn、skcms/prebuilt compatibility drift、Android font/GPU helper drift、ANGLE/Dawn/Vulkan rolls が継続リスク。
- cycle 066 では通常の1週/2週/3週候補ウィンドウを local refs から探索したが、baseline 後の固定 commit が存在しなかった。baseline coverage は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`、stale report は空。`vendor/skia-source.lock` は更新していない。
- cycle 067 では `vendor/skia-upstream-candidate` を local ref source として使い、2週間候補 `7a8e9f5d35d8d08c10da95ea8e0d872b995c43f3` を採用した。137 commits、`include` / `modules` は 47 files changed, +271/-214、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 186 files changed, +2311/-1916。
- cycle 067 の初期 stale/signature report は `SkParsePath::FromSVGString` 1件。upstream が旧 bool/out-param overload を deprecated inline helper として保持しているため、既存 C ABI `SkParsePath_FromSVGString(const char[], reskia_path_t*)` は互換として維持した。
- cycle 067 では HEIF decoder public/source/stub removal、Graphite `PipelineManager` related internals、SVG/core/codec/GPU/XML drift を同期した。prebuilt `libsvg.a` の旧 `SkDOM::build(SkStream&)` 参照には forwarding overload を追加した。
- cycle 067 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final lock stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text/path smoke は pass。
- cycle 068 では `vendor/skia-upstream-candidate` を local ref source として使い、2週間候補 `1c10d9bb7d5846f08c474538b400f61a10a507fb` を採用した。149 commits、`include` / `modules` は 37 files changed, +454/-192、`DEPS` / `include` / `modules` / `src` drift は 199 files changed, +4530/-1531。
- cycle 068 の初期 missing は 8 rows: `SkCodec::getHdrMetadata`、`SkExecutor` work-list/multi-list helpers、`SkPathBuilder::addLine`、`graphite::SubmitInfo` constructors。C API 追従で全て closed。
- cycle 068 の `signature_changed_review` は 5 rows: `SkPath::getLastPt`、`SkPathBuilder::snapshot`、`SkPathBuilder::detach`、`Graphite_Context_submit`、`SkOpBuilder::resolve`。既存 C ABI 維持または compatibility shim で処理済み。
- cycle 068 では HDR metadata、PNG encode/decode、path/pathops、SkExecutor、Graphite submit/task/resource flow、Ganesh atlas/path rendering、SVG geometry transform、Vulkan/Dawn/Metal backend drift を同期した。Rust PNG optional backend と GN/Bazel-only metadata は同期対象外。
- prebuilt static libraries が旧 symbol を参照するため、`SkPathBuilder::snapshot()` / `detach()` と `Op` / `Simplify` / `AsWinding` の out-param compatibility symbols を Reskia 側で維持した。
- cycle 068 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final stale C API report は 5 `signature_changed_review` rows で、cycle record に互換理由を記録済み。
- prebuilt/source build、GPU smoke、source SVG/provider/text/path smoke は pass。
- cycle 069 では `vendor/skia-upstream-candidate` を local ref source として使い、2週間候補 `ec032dbe0e04e305b06bfc7a01dd6d2e1d5f3dc8` を採用した。184 commits、`include` / `modules` は 50 files changed, +598/-281、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 221 files changed, +4684/-3187。
- cycle 069 の初期 missing は 12 rows: `SkPathBuilder` comparison/bounds/data/dump helpers、`Graphite_Context::syncPipelineData`、`PersistentPipelineStorage`。C API 追従と分類で全て closed。
- cycle 069 では PathData/PathRef migration、Graphite resource/pipeline churn、encode API、Skottie/SkParagraph/SVG drift を同期した。Rust PNG optional backend、Android NDK encoder、GN/Bazel-only metadata は同期対象外。
- prebuilt static library compatibility のため、旧 `SkApplyPerspectiveClip` overload symbols と no-arg `SkPathBuilder::snapshot()` / `detach()` symbols を Reskia 側で維持した。
- cycle 069 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final stale C API report は 2 `stale_capi` rows と 19 `signature_changed_review` rows で、cycle record に互換理由を記録済み。
- prebuilt/source build は pass。GPU smoke と source smoke は未実施。
- cycle 070 では `vendor/skia-upstream-candidate` を local ref source として使い、1週間候補の直前 `9a43169d5cadb5c3a56e78c6d19ca71b51097e5e` を採用した。128 commits、`include` / `modules` は 59 files changed, +2596/-1889、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 230 files changed, +7130/-5843。
- cycle 070 では通常の1週間先 `0682b51e060f4f82b757f0872cf5d8e380540213` が `Delete PathKit` を含み、`include` / `modules` は 101 files changed, +2598/-37742 まで膨らむため、その直前で split した。
- cycle 070 の初期 missing は 13 rows: `SkPath::points` / `verbs` / `conicWeights`、`SkPathBuilder::computeTightBounds` / `setPoint` / `contains`、`SkDynamicMemoryWStream::detachAsVector`、および constructor/classification rows。C API 追従と分類で全て closed。
- cycle 070 では PathData/PathRef split、SkPath direct span accessors、SkPathBuilder helper、Graphite capture/resource churn、Ganesh/Vulkan/Dawn/Metal drift、SVG/SkParagraph/Skottie drift を同期した。Android NDK encoder、XPS document source、GN/Bazel-only metadata は同期対象外。
- prebuilt static library compatibility のため、旧 `SkApplyPerspectiveClip` overload symbols と no-arg `SkPathBuilder::snapshot()` / `detach()` symbols を維持した。
- cycle 070 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final stale C API report は 49 `signature_changed_review` rows で、cycle record に互換理由を記録済み。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- cycle 071 では `vendor/skia-upstream-candidate` を local ref source として使い、PathKit deletion commit `0682b51e060f4f82b757f0872cf5d8e380540213` を単独で採用した。1 commit、`include` / `modules` は 42 files changed, +2/-35853、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift も 42 files changed, +2/-35853。
- cycle 071 では通常の1週/2週/3週候補が全て `Delete PathKit` を含むため、削除 commit を先に split した。Reskia は `modules/pathkit` と CanvasKit を追跡・build していないため、tracked source/header sync と C API 追従は不要だった。
- cycle 071 の初期 coverage は、generator の exact previous-matrix classification carry-forward 修正後に `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。stale C API report は空。
- cycle 071 では `scripts/generate_public_api_coverage.py` が `--previous-matrix` 指定時に exact signature の既存分類を引き継ぐよう修正した。これにより、レビュー済みの constructor/classification 行が no-op regeneration で `missing` に戻らない。
- cycle 071 の final matrix は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- cycle 072 では `vendor/skia-upstream-candidate` を local ref source として使い、2週間候補 `5e03cbcadaf57b0d6a16029a08627f924d3c7352` を採用した。187 commits、`include` / `modules` は 52 files changed, +1389/-1090、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 202 files changed, +4994/-3380。
- cycle 072 の初期 missing は 23 rows: `SkPath` tryMake helpers、`SkRRect::MakeRectRadii`、`SkString::operator+=(char)`、`SkYUVAInfo::inverseOriginMatrix`、`VulkanYcbcrConversionInfo` constructor/accessor/conversion rows。C API 追従と optional-backend `na` 分類で全て closed。
- cycle 072 の初期 stale C API report は 2 `stale_capi` rows と 26 `signature_changed_review` rows。upstream で削除された `SkPath::dumpArrays` C API は削除し、value/const signature drift は既存 C ABI 互換として記録した。
- cycle 072 では PathData/PathRef migration、HDR AGTM codec source、Graphite resource/provider/precompile churn、Vulkan YCbcr conversion、XPS helper cleanup、SVG/SkParagraph drift を同期した。Bazel-only metadata と Rust PNG optional backend implementation files は同期対象外。
- prebuilt static library compatibility のため、旧 no-arg `SkPathBuilder::detach()` と旧 `SkPath::transform(..., SkApplyPerspectiveClip)` symbols を `SkPrebuiltCompat.cpp` で維持した。
- cycle 072 の final matrix は `covered 3026` / `split_covered 42` / `false_positive 296` / `na 276` / `no_public_methods_found 120`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。final stale C API report は 26 `signature_changed_review` rows で、cycle record に互換理由を記録済み。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。

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

- `70f9d90bc8e6a56101d036153cfef28088e57f5b`
- committer date: 2026-06-01
- subject: Roll recipe dependencies (trivial).

cycle 091 結果:

- baseline `3b718ddc8ae51dbfb311afe02c35a83dd7999172` から `70f9d90bc8e6a56101d036153cfef28088e57f5b` を採用した。181 commits、`include` / `modules` は 17 files changed, +80/-38、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 193 files changed, +3374/-3419。
- 1週間候補 `f71b040b55a3023cfb8d71d160fb1dc821e93a42`、2週間候補 `3f20d9676d08ab11d7e2f3690176d531b8d8b492`、local-ref endpoint `70f9d90bc8e6a56101d036153cfef28088e57f5b` を比較し、public churn が小さく local refs 内で固定 hash の endpoint を採用した。3週間相当の target は local refs に存在しなかった。
- 新規 missing はなく、C API 追加は不要だった。`SkRegion::setRects` は canonical signature が `SkSpan<const SkIRect>` へ移ったが、legacy array/count helper が upstream に残るため既存 `SkRegion_setRects` C ABI を維持した。`SkFILEStream::Make` は実装 drift のみで public signature は互換だった。
- tracked `skia/DEPS`、public/private headers、skcms、skottie、core/codec/pathops/pdf/ports/shaders/utils、Ganesh/Graphite/Dawn/Metal/Vulkan backend、SkSL generated drift を同期した。`src/gpu/graphite/Log.h` と `src/partition_alloc` raw_ptr compatibility shim は upstream 削除に合わせて削除した。
- Reskia の optimize-size build で `SK_DISABLE_SDF_TEXT` が定義される場合に `SDFTextLCDRenderStep.cpp` が `SK_DistanceFieldInset` を参照できないため、SDF disabled 用の local inset fallback を追加した。
- final coverage は `covered 2952` / `split_covered 42` / `false_positive 299` / `na 266` / `no_public_methods_found 121`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `70f9d90bc8e6a56101d036153cfef28088e57f5b` から再比較する。cycle 091 で local refs はこの commit まで消費済みなので、cycle 092 開始時に local refs を再確認し、候補がなければ floating `main` に進まず記録する。Graphite sparse_strips/Vello/compute churn、Dawn/Vulkan/Metal backend churn、`SK_ENABLE_OPTIMIZE_SIZE` + SDF text guard、Graphite precompile ABI 設計 debt を既知リスクとして扱う。

候補:

- `3b718ddc8ae51dbfb311afe02c35a83dd7999172`
- committer date: 2026-05-13
- subject: Roll vulkan-deps from 1b6c53ba0f23 to df04fe18c28e (6 revisions)

cycle 090 結果:

- baseline `7b88c5c281e587c267457dba51f53e0b962c1748` から `3b718ddc8ae51dbfb311afe02c35a83dd7999172` を採用した。128 commits、`include` / `modules` は 18 files changed, +323/-20、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 143 files changed, +3705/-1717。
- 1週間候補 `8a3d4001f093702aaaa80eb55a8cf36dd3c694b4` と 3週間候補 `f71b040b55a3023cfb8d71d160fb1dc821e93a42` を比較し、標準幅内で public header churn が小さい2週間候補を採用した。
- `SkFont::makeStrikeRef()` と新規 `SkStrikeRef` value wrapper を C API / handle に追加した。`SkStrikeRef_operator_bool` は generator の exact token に合わせ、利用しやすい alias として `SkStrikeRef_isValid` も追加した。
- SkSL `raw_ptr` 互換のため `src/partition_alloc` no-op headers を同期した。Bazel/GN metadata、未参照の sparse_strips `Flatten.*` / `Tiler.h` は CMake tracked source では不要なため同期対象外にした。
- final coverage は `covered 2951` / `split_covered 42` / `false_positive 299` / `na 266` / `no_public_methods_found 121`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `3b718ddc8ae51dbfb311afe02c35a83dd7999172` から再比較する。`vendor/skia-upstream-candidate` は cycle 090 終了時点で accepted candidate checkout、local refs の `upstream/main` は `70f9d90bc8e6a56101d036153cfef28088e57f5b`（committer date 2026-06-01）まである。raw_ptr/`partition_alloc` 互換、Graphite sparse_strips/Vello/compute churn、Dawn/Vulkan/Metal backend churn、Graphite precompile ABI 設計 debt を既知リスクとして扱う。

候補:

- `7b88c5c281e587c267457dba51f53e0b962c1748`
- committer date: 2026-04-29
- subject: Roll vulkan-deps from a5c5df5b99ef to 68b1d78abfc4 (10 revisions)

cycle 089 結果:

- baseline `bda7232e6772bcc585435ae760983d6d43aa1155` から `7b88c5c281e587c267457dba51f53e0b962c1748` を採用した。196 commits、`include` / `modules` は 20 files changed, +445/-56、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 125 files changed, +4121/-1550。
- 1週間候補 `3150bddf3edd9ff7e9c3171a196cea2fb4d53a1f` と 3週間候補 `2447c273d06c205e98063329a31c0cbc999d2366` を比較し、標準幅内で public header churn が小さい2週間候補を採用した。
- `ParagraphStyle::getRenderSoftHyphens` / `setRenderSoftHyphens` を C API に追加した。
- `PrecompileColorFilter::priv()` / const `priv()` は `PrecompileColorFilterPriv` を返す internal implementation accessor であり、公開 C ABI surface ではないため `false_positive` に分類した。
- `PrecompileColorFilters::Matrix(bool clamp=true)` を含む Graphite precompile object-family は、opaque ownership と span marshalling 設計待ちの既存 `na` 方針を維持した。
- final coverage は `covered 2942` / `split_covered 42` / `false_positive 299` / `na 266` / `no_public_methods_found 121`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `7b88c5c281e587c267457dba51f53e0b962c1748` から再比較する。cycle 089 close 後に `vendor/skia-upstream-candidate` は `upstream` から fetch 済みで、`upstream/main` checkout は `70f9d90bc8e6a56101d036153cfef28088e57f5b`（committer date 2026-06-01）。Graphite precompile ABI 設計 debt、Dawn/Vulkan/Metal churn、SkRP/CPU opts flag churn、skcms roll compatibility、private Graphite accessor false-positive rows を既知リスクとして扱う。

cycle 088 結果:

- baseline `f37239a7a689d64268b73fc7eb45b5c40a7f7013` から `bda7232e6772bcc585435ae760983d6d43aa1155` を採用した。184 commits、`include` / `modules` は 18 files changed, +214/-78、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 201 files changed, +3618/-3767。
- 1週間候補 `b8f966a30b264e8d897fc825910a25f777ed210b` と 3週間候補 `3150bddf3edd9ff7e9c3171a196cea2fb4d53a1f` を比較し、標準幅内で public header churn が小さい2週間候補を採用した。
- `SkFontMgr::match(const Request&)` / `fallback(const Request&)` を C API に追加し、request struct で CMap entries、BCP47、family name、variation model、optional synthetic style flags を渡せるようにした。
- `PrecompileContext::getPipelineLabel` は PrecompileContext ownership と SkData transfer を含む opaque precompile ABI 設計待ちとして `na` に分類した。
- `SkCodec_Register` は現在も公開されている `SkCodecs::Register` に backed された互換 C API として保持した。`SkShader_isOpaque` と Graphite cleanup wrappers の signature drift は C ABI 互換として記録した。
- final coverage は `covered 2940` / `split_covered 42` / `false_positive 297` / `na 266` / `no_public_methods_found 121`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final stale C API report は `stale_capi 1` / `signature_changed_review 3` で、残す理由は cycle record に記録済み。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `bda7232e6772bcc585435ae760983d6d43aa1155` から再比較する。Graphite precompile ABI 設計 debt、Dawn/Vulkan/Metal churn、CPU opts target rename churn、互換維持 stale/signature rows を既知リスクとして扱う。

cycle 087 結果:

- baseline `aba405ee605f2578f3054bc4d997e2f32f57f291` から `f37239a7a689d64268b73fc7eb45b5c40a7f7013` を採用した。15 commits、`include` / `modules` は 50 files changed, +415637/-11320、`DEPS` / `gn` / `bazel` / `include` / `modules` / `src` drift は 65 files changed, +415864/-11542。
- immediate next `bf15cfab3bc0242fa854483cf8a36571c3331858` は Vulkan header roll 1 commit で `include` / `modules` 50 files changed, +415637/-11320。`f37239a7a689d64268b73fc7eb45b5c40a7f7013` まで広げても header/module churn は同じだったため、deferred boundary を採用した。
- tracked `skia/DEPS`、`include/third_party/vulkan` の既存・新規 Vulkan headers、`src/gpu/BufferWriter.h`、Graphite source/header、`src/shaders/SkImageShader.cpp` を同期した。root `gn/`、root `bazel/`、root `BUILD.bazel` metadata、Graphite subtree Bazel metadata は同期対象外にした。
- 新規 C API gap はなく、C API 追加・削除は不要だった。新規 stale C API はなく、互換維持のみの残存 C API もなし。
- final coverage は `covered 2939` / `split_covered 42` / `false_positive 297` / `na 266` / `no_public_methods_found 121`、かつ `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- final stale C API report は空。
- prebuilt/source build、GPU smoke、source SVG/provider/text smoke は pass。
- 次サイクルでは、accepted baseline `f37239a7a689d64268b73fc7eb45b5c40a7f7013` から再比較する。cycle 087 終了時点では local refs に baseline 後の commit がなかったため、まず refs 範囲を再確認し、不足していれば候補なしとして記録する。Dawn/Vulkan/ANGLE rolls、Graphite transfer/readback churn、Bazel/GN metadata の混入リスクを既知リスクとして扱う。

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
- `docs/plans/skia-incremental-upgrade/records/cycle-066-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-067-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-068-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-069-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-070-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-071-2026-05-31.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-072-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-073-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-074-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-075-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-076-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-077-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-078-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-079-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-080-2026-06-01.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-081-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-082-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-083-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-084-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-085-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-086-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-087-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-088-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-089-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-090-2026-06-02.md`
- `docs/plans/skia-incremental-upgrade/records/cycle-091-2026-06-02.md`

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
