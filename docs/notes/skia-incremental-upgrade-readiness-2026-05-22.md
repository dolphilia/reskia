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

`docs/notes/vendor-skia-management-2026-02-14.md` では、すでに lock + untracked clone model が採用されている。

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

Probe output は `docs/notes/` 配下の note として残す。

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
