# Skia 段階的アップグレード準備状況

作成時刻: 2026-05-22 07:29:54 JST

## 概要

`vendor/skia-upstream` を徐々に新しい Skia commit へ進め、Reskia の C API binding と CMake source sync を段階的に追従する作業に入れるかを調査した。

結論:

- 段階的アップグレードの探索を始める土台は整っている。
- ただし、`vendor/skia-source.lock` を即座に最新 main へ更新する段階ではない。
- まずは候補 commit を一時 checkout し、public API 差分、source/header sync 差分、coverage regression、build smoke を記録する「upgrade probe」フェーズを挟むべき。
- 現在の coverage freeze (`missing 0` / `deferred 0`) と Phase 30-33 の verification matrix は、upgrade probe の合否判定として使える。

## 現在のベースライン

Skia baseline:

- `vendor/skia-source.lock`
- `SKIA_REF=0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- `SKIA_BASELINE_DATE=2026-02-14`

ローカルの `vendor/skia-upstream`:

- HEAD: `0d49b661d7`
- status: clean
- 調査時に観測した現在の remote: `https://github.com/dolphilia/skia.git`
- lock file 上の upstream URL: `https://github.com/google/skia.git`

この remote の不一致は致命的ではない。`scripts/fetch_skia_upstream.sh` は lock file の内容から remote を再設定する。ただし、アップグレード作業では現在の clone 設定に依存せず、必ず fetch script から開始すべきである。

Coverage freeze:

| status | count |
| --- | ---: |
| `covered` | 2811 |
| `split_covered` | 33 |
| `false_positive` | 275 |
| `na` | 198 |
| `no_public_methods_found` | 104 |
| `missing` | 0 |
| `deferred` | 0 |
| `partial` | 0 |
| `overcovered` | 0 |
| total | 3421 |

直近の検証ベースライン:

- prebuilt `reskia` build: pass
- source `reskia` build: pass
- GPU prebuilt smoke: pass。Metal device unavailable は `SKIP` 後 `PASS`
- source SVG/provider smoke: pass
- coverage generator: pass

## Upstream の現状

Skia 公式ドキュメントでは、`skia.googlesource.com/skia` が canonical source tree とされている。公式の download documentation でも、`https://skia.googlesource.com/skia.git` から clone し、Skia の dependency sync tools を実行する手順が説明されている。Gitiles の main branch は活発に進んでおり、今回の調査時点でも public main page には数時間前の commit が表示されていた。

Reskia への含意:

- 「latest」は floating branch ではなく、固定された commit を意味するべき。
- すべての upgrade step で候補 Skia commit hash を記録する。
- lock file は、候補 commit が coverage gate と build gate を通過した後にのみ更新する。

参照:

- https://skia.org/docs/
- https://docs.skia.org/docs/user/download/
- https://skia.googlesource.com/skia.git/

## 既存のアップグレード資産

### Lock + fetch workflow

`docs/ja/notes/vendor-skia-management-2026-02-14.md` では、すでに lock + untracked clone model が採用されている。

- `vendor/skia-source.lock` が source URL と固定 ref を管理する。
- `scripts/fetch_skia_upstream.sh` は `vendor/skia-upstream` を clone/fetch できる。
- `--ref` は一時的な候補 checkout をサポートする。
- `--dest` は候補を別ディレクトリに checkout する用途に使える。

各候補を `vendor/skia-upstream` の submodule 化なしで検証できるため、この方式は段階的アップグレードに向いている。

### Public API coverage generator

`scripts/generate_public_api_coverage.py` は `vendor/skia-upstream` から public header を抽出し、method-level の public API coverage を `skia/capi` と比較する。

Phase 29-33 で steady-state matrix を閉じたため、この generator は upgrade gate として使える段階にある。

- accepted upgrade 後も `missing` は 0 のままにする。
- upstream 由来の新しい public API は probe 中に `missing` として出る。その後、実装または分類する。
- `false_positive` / `na` / `split_covered` は、理由が明確であれば generator noise や platform noise を吸収できる。

### Verification matrix

Phase 30 と Phase 33 で実用的な build gate が確立された。

- coverage generator
- prebuilt `reskia`
- source `reskia`
- GPU prebuilt smoke
- source SVG/provider smoke

小さな候補 bump を判定するには十分である。

## 準備状況の評価

整っているもの:

- baseline Skia ref は固定されている。
- ローカル比較ツリーは存在し、clean である。
- C API coverage は `missing 0` / `deferred 0` で freeze されている。
- callback/provider ownership policy は文書化されている。
- optional backend の `na` policy は文書化されている。
- 代表 build/smoke matrix は存在し、通過している。
- fetch script は一時 ref をサポートしている。

まだ不足しているもの:

- 2 つの Skia ref を比較して public API delta を出す first-class script がない。
- `generate_public_api_coverage.py` は `vendor/skia-upstream` を source tree と仮定している。別の候補 Skia checkout path を直接受け取れない。
- upstream から `skia/` への source/header sync は、まだ area-specific かつ手動である。
- `DEPS`、`gn/*.gni`、generated files、optional third_party roll 由来の Skia dependency 変更は自動分類されない。
- 現在のローカル `vendor/skia-upstream` remote は、fetch script が再設定するまでは fork を指している。
- ローカル clone は checked-out baseline から見て grafted/shallow に見えるため、local history だけでは commit range planning に不十分である。

総合判断:

- 範囲を絞った upgrade probe へ進んでよい。
- ただし、最初の probe で再現可能な diff/build report ができるまでは、`vendor/skia-source.lock` を新しい baseline へ更新しない。

## 推奨アップグレード戦略

3 つの段階に分ける。

1. Probe commit
2. Accepted bump
3. Baseline lock update

### Level 1: Probe commit

目的: baseline へ採用する前に drift を測定する。

推奨手順:

1. 候補 commit を選ぶ。
   - `main` そのものではなく、小さな日付単位の checkpoint を優先する。
   - 2026-02-14 baseline から current main へ直接飛ばない。
2. 候補を fetch する。
   - `scripts/fetch_skia_upstream.sh --ref <candidate>` を使う。
   - baseline checkout を触らずに残したい場合は、`--dest vendor/skia-upstream-candidate` を使う。
3. public API coverage を実行する。
   - `python3 scripts/generate_public_api_coverage.py`
   - 新しい `missing` / `partial` / `overcovered` / `deferred` を記録する。
4. public header を area ごとに diff する。
   - `include/core`
   - `include/effects`
   - `include/utils`
   - `modules/*/include`
   - `include/gpu`
5. source list dependency を diff する。
   - `gn/*.gni`
   - `DEPS`
   - すでに `skia/` に mirror されている module source directories
6. source/header sync を試した後にだけ、代表 build/smoke matrix を実行する。

Probe output は `docs/ja/notes/` 配下の note として残す。

- candidate commit
- public API delta summary
- expected coverage debt
- source sync risk
- dependency risk
- build result
- accept/reject recommendation

### Level 2: Accepted bump

目的: 候補 Skia snapshot に対して Reskia が compile できる状態にする。

推奨順:

1. public headers と low-risk source sync から始める。
2. coverage を再生成し、新規行を分類する。
3. low-risk な新規 public method に C ABI wrapper を実装する。
4. `na` / `false_positive` override は、理由を明示できる場合だけ追加する。
5. Phase 30/33 verification matrix を実行する。
6. CMake/source-list の変更をすべて記録する。

Accepted bump でも、広い latest jump ではなく、1 つの小さな Skia candidate に留める。

### Level 3: Baseline lock update

目的: 候補を Reskia の新しい公式 baseline にする。

これを行う条件:

- coverage が `missing 0` / `deferred 0` に戻っている。
- representative builds が通っている。
- source sync note が書かれている。
- optional backend changes が分類されている。
- `vendor/skia-source.lock` が accepted commit と日付で更新されている。

## 候補 commit の選び方

floating `main` を直接使わない。

推奨する候補:

1. 公式 `main` の特定 commit。
2. Skia Gitiles から選んだ日付単位の checkpoint commit。
3. dependency change を調査対象にする場合は、dependency roll boundary に対応する commit。

最初の bump size:

- `0d49b661...` の 1-2 週間後から始める。
- diff が小さく build が安定していれば、月単位の checkpoint へ広げる。
- diff が大きい場合は、時間単位ではなく feature area ごとに分割する。

理由:

- 現在の baseline は 2026-02-14 の commit である。
- 現在の upstream main は数か月先に進んでおり、dependency repository roll も頻繁に入っている。
- 直接 jump すると、public API drift、source-list drift、dependency drift、optional backend drift が 1 つの review に混ざる。

## 提案フェーズ

### Phase U0: Upgrade Probe Tooling

範囲:

- 再現可能な probe checklist を追加または文書化する。
- 現 baseline と candidate の public header extraction を比較できる script を追加するのが望ましい。
- 候補 checkout で `vendor/skia-upstream` を置き換えずに済むよう、`scripts/generate_public_api_coverage.py` に `--skia-root` を追加することを検討する。

終了条件:

- `vendor/skia-source.lock` を変更せずに public API delta report を生成できる。

### Phase U1: First Small Skia Bump Probe

範囲:

- `0d49b661...` より少し後の小さな候補を選ぶ。
- 候補を `vendor/skia-upstream` または temporary candidate checkout に fetch する。
- coverage generator を実行する。
- public API delta と build risk を記録する。

終了条件:

- probe note に、候補を accept できるかどうかが記録されている。

### Phase U2: Low-Risk Core/Effects/Utils Sync

範囲:

- low-risk area の public headers と source files だけを同期する。
- GPU、text shaping、Skottie、Graphite、Dawn/Vulkan/D3D changes は避ける。
- coverage を freeze 状態へ戻す。

終了条件:

- prebuilt/source `reskia` builds が通る。
- coverage が `missing 0` に戻る。

### Phase U3: Module Sync

範囲:

- SVG / skresources / skunicode / skshaper / skparagraph changes。
- optional dependency gates を尊重する。

終了条件:

- source SVG/provider smoke が通る。
- 有効化されている場合は text stack smoke が通る。

### Phase U4: GPU/Graphite Sync

範囲:

- Ganesh/Graphite public header と source drift。
- Optional backend rows は、backend-specific bridge を計画する場合を除き Phase 32 roadmap の背後に残す。

終了条件:

- GPU prebuilt smoke が build され、`PASS` または expected `SKIP`/`PASS` で終了する。
- 新しい GPU public APIs が実装または分類されている。

### Phase U5: Lock Update

範囲:

- `vendor/skia-source.lock` を更新する。
- accepted commit と日付を記録する。
- final coverage matrix を再生成する。
- Phase 33 build sweep を実行する。

終了条件:

- 候補 commit が新しい baseline になる。

## 直近の推奨

進めてよい。ただし、lock 変更ではなく Phase U0 から始める。

次の具体的なタスク:

1. candidate comparison tooling を追加する、または manual checklist を文書化する。
2. 最初の小さな candidate commit を選ぶ。
3. `vendor/skia-source.lock` を意図的に更新しない probe を実行する。

これにより、現在の安定した freeze を維持したまま、アップグレードリスクを可視化できる。

## 追記: 仮候補 commit 選定調査

調査時刻: 2026-05-22 07:44:32 JST

この追記では、計画をまだ実施せず、`vendor/skia-upstream` の現行 commit からどの程度先の Skia commit を最初の probe 候補にするのがよいかを調べた。

### 調査条件

現在の Reskia baseline:

- commit: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- local `vendor/skia-upstream` HEAD: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- upstream 上の commit date: 2023-11-19
- lock file 上の `SKIA_BASELINE_DATE`: 2026-02-14

注意点:

- ローカル `origin/main` は調査時点で lock commit と同じだった。
- 候補選定のため、公式 `https://github.com/google/skia.git` の `main` と GitHub API を参照した。
- `vendor/skia-source.lock` は変更していない。
- この調査は候補選定までであり、candidate checkout、source sync、coverage regeneration、build verification はまだ実施していない。

### 比較した候補

| 候補 | commit | committer date | baseline からの commit 数 | `include`/`modules` 差分 | public header 変更の性格 | 評価 |
| --- | --- | ---: | ---: | ---: | --- | --- |
| 1週間後 | `600986ba305dcb2c61f02749d992e46d5996a1e7` | 2023-11-27 | 88 | 49 files, +529/-400 | ほぼ GPU / Graphite / skcms / skshaper 寄り | 小さすぎるわけではないが、初回 probe としては API 領域が GPU に偏る |
| 2週間強 | `5f54e9f84cff8c42fd645ec53c1727857bdb12ab` | 2023-12-05 | 181 | 83 files, +1147/-565 | Codec/Core/GPU/Graphite/SkUnicode/SkParagraph/Skottie に広がる | 最初の probe 候補として最もよい |
| 3週間強 | `927f20598b11040c3265369e6da1ee3732cbb9e3` | 2023-12-12 | 267 | 103 files, +1422/-615 | 12/05 の範囲に加えて Android/Dawn/SkFont/SkCGUtils が増える | 初回にはやや広い。2回目以降の候補向き |

commit 数は `git rev-list --count <baseline>..<candidate>` で確認した。

### 12/05 候補の public header 差分

`5f54e9f84cff8c42fd645ec53c1727857bdb12ab` まで進めた場合、主に次の公開ヘッダに差分が出る。

- `include/codec/*Decoder.h`
- `include/codec/SkCodec.h`
- `include/core/SkCanvas.h`
- `include/core/SkMilestone.h`
- `include/gpu/GrBackendSemaphore.h`
- `include/gpu/GrBackendSurface.h`
- `include/gpu/GrContextThreadSafeProxy.h`
- `include/gpu/GrDirectContext.h`
- `include/gpu/GrTypes.h`
- `include/gpu/MutableTextureState.h`
- `include/gpu/ganesh/vk/GrVkBackendSemaphore.h`
- `include/gpu/gl/GrGLFunctions.h`
- `include/gpu/graphite/BackendTexture.h`
- `include/gpu/graphite/Context.h`
- `include/gpu/graphite/ContextOptions.h`
- `include/gpu/graphite/Recorder.h`
- `include/gpu/graphite/Surface.h`
- `include/gpu/vk/VulkanMutableTextureState.h`
- `include/ports/SkFontConfigInterface.h`
- `include/private/base/SkDeque.h`
- `include/private/base/SkThreadAnnotations.h`
- `include/private/chromium/GrSurfaceCharacterization.h`
- `modules/skottie/include/SkottieProperty.h`
- `modules/skottie/include/TextShaper.h`
- `modules/skparagraph/include/FontCollection.h`
- `modules/skshaper/include/SkShaper.h`
- `modules/skunicode/include/SkUnicode.h`

公開 API 追従として目につく変更:

- `SkCodec::MakeFromStream` / `MakeFromData` 周辺に decoder span を受け取る overload が増える。
- codec decoder headers に小さな interface 変更が入る。
- `SkCanvas` 内部の predraw flag 型が整理される。ただし C ABI 対象としては private/internal 寄りの可能性が高い。
- `GrContextThreadSafeProxy::createCharacterization` の引数型が `bool` から `skgpu::Mipmapped` / `skgpu::Protected` へ寄る。legacy overload も残る。
- `SkUnicode` に emoji component / modifier / regional indicator 判定系が増える。
- `FontCollection` に fallback 用 font family の保持が増える。
- Graphite/Ganesh header は引き続き optional backend / GPU policy の分類対象になる。

### 12/12 候補を初回にしない理由

`927f20598b11040c3265369e6da1ee3732cbb9e3` は、12/05 候補との差分に加えて以下が増える。

- Android hardware buffer helpers
- Graphite Dawn backend context
- `include/core/SkFont.h`
- `include/gpu/ShaderErrorHandler.h`
- `include/utils/mac/SkCGUtils.h`
- `modules/skparagraph/include/TypefaceFontProvider.h`

これらは Reskia の optional backend roadmap や platform-specific policy に触れやすい。初回 probe でここまで入れると、C API binding 追従、CMake/source sync、optional backend 判定、platform gating が同時に混ざる。最初の候補としては少し広い。

### 仮選定

仮の最初の candidate commit は次を推奨する。

- `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- committer date: 2023-12-05T19:49:10Z
- subject: `Allow undefined format from Android format properties and ability to fallback to importing as external`

理由:

- baseline から 181 commits で、1週間候補より十分に変化がある。
- public header 差分は 40件台で、調査・分類・coverage 追従が現実的な範囲に収まる。
- Core/Codec/Text/GPU/Module にある程度広がりがあり、upgrade probe の手順を検証する材料として偏りすぎない。
- 12/12 候補ほど Android/Dawn/platform-specific surface が増えていない。
- `missing 0` freeze 後の初回 probe として、coverage regression の量を観測するにはちょうどよい。

### 次点候補

より保守的に始めるなら、`600986ba305dcb2c61f02749d992e46d5996a1e7` を使う。

- baseline から 88 commits。
- public header 差分は比較的小さい。
- ただし変更の中心が GPU / Graphite に寄るため、Reskia 全体の upgrade probe としては観測できる範囲が狭い。

12/05 候補で public API delta や build drift が想定より大きかった場合の fallback として扱うのがよい。

### 今後の probe で確認すべきこと

次に実施する場合は、まだ lock を更新せず、次だけを確認する。

1. 候補 commit を別 checkout または一時 checkout で用意する。
2. baseline と candidate の public header delta を機械的に出す。
3. `scripts/generate_public_api_coverage.py` が candidate root を扱えるようにするか、作業ツリーを一時的に candidate に切り替えて coverage regression を取る。
4. 新規 `missing` を area ごとに `real_gap` / `na` / `false_positive` / `design-required` へ仮分類する。
5. CMake source list、`DEPS`、`gn/*.gni` の drift を記録する。
6. 実装・lock 更新は、probe note の accept/reject 判定後に行う。

## 追記: incremental-upgrade ブランチでの作業サイクル

調査時刻: 2026-05-22 08:00:43 JST

`incremental-upgrade` ブランチが作成されたため、今後の段階的アップグレードはこのブランチで進める。これまでの C API coverage freeze を崩さず、Skia の固定 commit を少しずつ受け入れるため、1回の作業を「約2週間分の候補 commit を選び、probe し、追従し、freeze へ戻し、lock を更新する」サイクルとして扱う。

### サイクルの基本単位

1サイクルの推奨幅:

- 原則: baseline commit から Skia upstream main 上で約2週間後の固定 commit。
- 目安: 150-220 commits 程度。
- public header 差分目安: `include` / `modules` でおおむね 50-100 files 程度。
- 初回候補の実測値: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`、181 commits、`include` / `modules` で 83 files, +1147/-565。

2週間を基本単位にする理由:

- 1週間程度では、変更量は扱いやすいが GPU / Graphite など特定領域に偏る場合があり、upgrade probe として得られる知見が狭い。
- 3週間以上では、Android / Dawn / platform-specific helper など optional backend policy に触れやすくなり、初回から source sync と policy 判断が混ざりすぎる。
- 2週間前後なら、Core / Codec / Text / GPU / Module に適度な広がりがあり、C API coverage regression の観測にも使いやすい。

### 1サイクルの流れ

#### Step 0: Branch baseline check

目的:

- `incremental-upgrade` ブランチで作業していることを確認する。
- 現在の Reskia baseline と coverage freeze を記録する。

確認するもの:

- `git branch --show-current`
- `vendor/skia-source.lock`
- `vendor/skia-upstream` の HEAD と clean status
- coverage matrix の `missing 0` / `deferred 0`
- 直近の build/smoke baseline

この step では lock を変更しない。

#### Step 1: Candidate selection

目的:

- 次に進める固定 Skia commit を1つ選ぶ。

選び方:

- 現 baseline から約2週間後の `main` commit を第一候補にする。
- 候補の前後に revert storm、large dependency roll、backend migration、generated file 大量更新がある場合は、少し前後にずらす。
- 1週間候補と3週間候補も併記し、採用候補が大きすぎるか小さすぎるかを判断する。

記録するもの:

- candidate commit hash
- committer date
- commit subject
- baseline からの commit 数
- `include` / `modules` の diff shortstat
- 主要 public header list
- 初回 probe としての accept/reject 予想

#### Step 2: Probe without lock update

目的:

- 候補 commit を baseline として採用する前に、差分の性格を測る。

実施内容:

- 候補を一時 checkout または別 checkout で用意する。
- baseline と candidate の public header delta を出す。
- `DEPS`、`gn/*.gni`、Bazel metadata、mirror 済み source directory の drift を見る。
- coverage generator が candidate root を扱える場合は candidate coverage を取り、新規 `missing` / `partial` / `overcovered` を記録する。
- generator がまだ candidate root を扱えない場合は、先に tooling を整える。

成果物:

- `docs/ja/notes/` に probe note を作る。
- この段階では `vendor/skia-source.lock` を更新しない。
- この段階では C API 実装も原則入れない。ただし probe tooling の小修正は許容する。

#### Step 3: Routing and implementation plan

目的:

- candidate 由来の新規差分を、実装順に分解する。

分類:

- `core-codec-low-risk`: Core / Codec / simple value object / helper。
- `text-module`: SkUnicode / SkShaper / SkParagraph / Skottie text。
- `gpu-ganesh-graphite`: Ganesh / Graphite common。
- `optional-backend`: Dawn / Vulkan / Metal / Android / platform-specific helper。
- `generator-noise`: public API ではない、または parser 誤検出。
- `design-required`: callback/provider/global registration/ownership 設計が必要なもの。

判断基準:

- すぐ実装できる public method は `real_gap` として実装へ回す。
- platform 依存や backend 未有効領域は既存 policy に沿って `na` または roadmap 行へ回す。
- internal/private surface は `false_positive` として理由を残す。
- ownership 設計が必要なものは、この段階では実装せず設計メモ化する。

#### Step 4: Source/header sync and C API catch-up

目的:

- candidate snapshot に Reskia の source/header mirror と C API を追従させる。

推奨順:

1. Low-risk Core / Codec。
2. Text / module helper。
3. GPU common。
4. Optional backend routing。
5. 設計必須領域のメモ化。

作業ルール:

- 1サイクル中でも area ごとに小さく分ける。
- 各 area の終了ごとに coverage を再生成する。
- `missing` は一時的に許容しても、cycle close 前に必ず 0 に戻す。
- 既存の safety policy、ownership policy、optional backend policy を変更する場合は、必ず docs に理由を残す。

#### Step 5: Verification gate

目的:

- candidate bump を accepted baseline にしてよいか判定する。

最低限の gate:

- `scripts/generate_public_api_coverage.py`
- coverage matrix: `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`
- prebuilt `reskia` configure/build
- source `reskia` configure/build
- GPU smoke: `PASS` または expected `SKIP`/`PASS`
- source SVG/provider smoke

サイクル中の変更が text stack、optional backend、callback/provider foundation に触れた場合は、その領域の追加 smoke を実行する。

#### Step 6: Lock update and cycle close

目的:

- accepted candidate を新しい Reskia Skia baseline にする。

実施条件:

- coverage が freeze 状態に戻っている。
- build/smoke gate が通っている。
- probe note と source sync note が残っている。
- optional backend / design-required の未実装理由が明確である。

実施内容:

- `vendor/skia-source.lock` の `SKIA_REF` と `SKIA_BASELINE_DATE` を更新する。
- cycle close note を `docs/ja/notes/` に残す。
- 次サイクルの候補選定基準を更新する。

### サイクルの停止条件

次のいずれかが出たら、そのサイクルでは lock update へ進まない。

- public header delta が想定より大きく、1サイクルで `missing 0` に戻せない。
- `DEPS` / third_party roll が Reskia の dependency model に大きな変更を要求する。
- CMake source sync が広範囲に壊れ、Reskia 側の build system 整備が先に必要になる。
- callback/provider/global registration など、ABI ownership 設計なしに実装すると危険な API が中心になる。
- optional backend の有効化方針が未決のまま build surface に入ってくる。

停止した場合は、候補 commit を前倒しして小さくするか、feature area ごとに分割する。

### 初回サイクルの推奨形

初回は次の固定 commit を probe する。

- candidate: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- date: 2023-12-05T19:49:10Z
- baseline からの commit 数: 181
- 位置づけ: 2週間幅の妥当性を検証する最初の probe。

初回サイクルでは、lock update まで一気に進むより、まず次を完了条件にするのがよい。

1. candidate root を使った public API delta / coverage regression の再現可能な取得。
2. 新規差分の row-level routing。
3. Core / Codec など低リスク領域だけの追従可否確認。
4. GPU / optional backend / design-required の残量見積もり。

この結果が小さければ、そのまま accepted bump へ進む。大きければ `600986ba305dcb2c61f02749d992e46d5996a1e7` へ戻して、1週間幅を初回にする。

### 長期運用の目安

当面は「2週間幅」を標準とし、各サイクルの結果で幅を調整する。

- 連続して build/coverage gate が軽く通る場合: 3-4週間幅を試す。
- 毎回 optional backend / dependency drift が重い場合: 1週間幅へ戻す。
- 特定領域が大きい場合: 日付幅ではなく area-specific cycle に切る。
- latest main への直接追従は、複数サイクルで source sync と coverage regression の傾向が見えてから検討する。
