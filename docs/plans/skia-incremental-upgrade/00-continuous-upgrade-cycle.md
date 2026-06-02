# Skia 段階的アップグレード継続計画

作成時刻: 2026-05-22 08:05:52 JST

## 目的

`vendor/skia-upstream` を一度に最新へ近づけるのではなく、固定された Skia commit を小さく選び、Reskia の CMake source sync、C API binding、coverage matrix、verification matrix を段階的に追従する。

この計画は一回きりの upgrade plan ではない。`incremental-upgrade` ブランチ上で、同じ作業サイクルを何度も繰り返し、各サイクルの結果に応じて次の commit 幅を調整するための運用計画である。

## 前提

- 作業ブランチ: `incremental-upgrade`
- 現在の baseline: `vendor/skia-source.lock`
- 現在の `SKIA_REF`: `vendor/skia-source.lock` の値を正とする。計画書中の古い例や初回候補より、常に lock と `HANDOFF.md` を優先する。
- 現在の coverage freeze: `missing 0` / `deferred 0`
- 直近の build/smoke baseline は Phase 30-33 の verification matrix を基準にする。

関連メモ:

- `docs/notes/skia-incremental-upgrade-readiness-2026-05-22.md`
- `docs/notes/vendor-skia-management-2026-02-14.md`
- `docs/plans/public-api-binding-expansion/08-post-phase10-coverage-expansion-plan-2026-05-16.md`

## サイクル幅の基準

標準幅は、現在の baseline から Skia upstream main 上で約2週間後の固定 commit とする。

ここでいう `main` は「floating な最新 main」ではない。必ず `vendor/skia-upstream` または `vendor/skia-upstream-candidate` の local refs に存在する固定 commit hash を選ぶ。候補選定のために、毎回 upstream main 全体を fetch しようとしない。local refs で候補が見つからない場合は、まずその事実を cycle record / HANDOFF に記録し、必要なら次サイクルの作業として refs 更新可否を確認する。

目安:

- commit 数: 150-220 commits 程度。
- public header 差分: `include` / `modules` で 50-100 files 程度。
- 変更の広がり: Core / Codec / Text / GPU / Module にある程度分散していること。
- 避けるもの: large dependency roll、revert storm、backend migration、generated file の大量更新が同時に入る checkpoint。

2週間幅を標準にする理由:

- 1週間幅は扱いやすいが、GPU / Graphite など特定領域に偏る場合があり、upgrade probe として得られる知見が狭い。
- 3週間以上は Android / Dawn / platform-specific helper など optional backend policy に触れやすく、初回から判断が混ざりすぎる。
- 初回候補 `5f54e9f84cff8c42fd645ec53c1727857bdb12ab` は 181 commits、`include` / `modules` で 83 files, +1147/-565 であり、実作業量の観測にちょうどよい。

実運用では、2週間幅が重すぎる場合や local refs に候補がない場合がある。その場合は、1週間候補を採用してよい。特に HANDOFF に deferred candidate が残っている場合は、それを最初に再評価する。deferred candidate は前サイクルで一度見送られた固定 commit であり、再検索や広範囲 fetch よりも再現性が高い。

## 1サイクルの流れ

### Step 0: Baseline Check

目的:

- `incremental-upgrade` ブランチで作業していることを確認する。
- lock、upstream checkout、coverage、build baseline を確認する。

確認項目:

- `git branch --show-current`
- `git status --short --branch`
- `vendor/skia-source.lock`
- `git -C vendor/skia-upstream rev-parse HEAD`
- `git -C vendor/skia-upstream status --short --branch`
- `scripts/generate_public_api_coverage.py` の現状結果

この step では `vendor/skia-source.lock` を変更しない。

### Step 1: Candidate Selection

目的:

- 次に probe する固定 Skia commit を1つ選ぶ。

基本方針:

- `HANDOFF.md` の「次にやること」と「比較候補メモ」を最初に見る。
- deferred candidate が書かれていれば、まずそれを第一候補として再評価する。
- 候補は必ず commit hash で固定する。日付や `main` という名前だけを candidate にしない。
- local refs にある commit だけで選定する。候補選定のためだけに `git fetch` や外部検索へ進まない。
- local refs の先が不足している場合は、無理に探さず「local refs に候補なし」と記録する。

推奨手順:

1. 現 baseline から約2週間後の `main` commit を第一候補にする。
2. 比較用に1週間候補と3週間候補も見る。
3. 各候補について commit 数、`include` / `modules` shortstat、主要 public header list、dependency/source-list drift を確認する。
4. large dependency roll、platform-specific backend、generated file 大量更新が強い候補は少し前後へずらす。

ただし、HANDOFF に deferred candidate がある場合は、上記 1 の前に deferred candidate を確認する。deferred candidate が現在 baseline から見て 1週間程度の固定 commit で、coverage/build gate を通せそうなら、それを採用してよい。

候補探索の具体例:

```sh
baseline=$(sed -n 's/^SKIA_REF="//p' vendor/skia-source.lock | sed 's/"$//')

# HANDOFF の deferred candidate がある場合は、その commit が local にあるか確認する。
git -C vendor/skia-upstream cat-file -e <candidate>^{commit}
git -C vendor/skia-upstream show -s --format='%H%n%cI%n%s' <candidate>
git -C vendor/skia-upstream rev-list --count "$baseline"..<candidate>

# 1週間/2週間/3週間の候補を local refs から探す。出なければ「候補なし」と記録する。
git -C vendor/skia-upstream log --all \
  --since='<baseline date + 7 days>' \
  --until='<baseline date + 8 days>' \
  --format='%H %cI %s' \
  --reverse | head -20
```

候補比較の具体例:

```sh
git -C vendor/skia-upstream diff --shortstat "$baseline"..<candidate> -- include modules
git -C vendor/skia-upstream diff --name-status "$baseline"..<candidate> -- include modules
git -C vendor/skia-upstream diff --shortstat "$baseline"..<candidate> -- DEPS gn bazel include modules src
git -C vendor/skia-upstream diff --name-status "$baseline"..<candidate> -- DEPS gn bazel include modules src
```

選定時の判断基準:

- `include` / `modules` が小さく、source drift が主に Core/SkSL/GPU helper なら probe へ進みやすい。
- Graphite/Dawn/Vulkan/Metal の backend migration が広い場合は、1週間幅へ縮めるか、その candidate を deferred として次回に回す。
- `DEPS` や third_party roll が Reskia の dependency model に影響しそうなら、その cycle で lock update しない前提で probe する。
- generated file churn だけで候補を見送らない。ただし generated churn と backend migration と dependency roll が同時に大きい場合は候補を前倒しする。
- local refs に 2週間/3週間候補が存在しない場合は、1週間候補または deferred candidate を採用する。候補なしを理由に floating latest main へ飛ばない。

記録項目:

- baseline commit
- candidate commit
- candidate committer date
- candidate subject
- baseline からの commit 数
- `include` / `modules` diff shortstat
- 主要 public header 差分
- 採用理由または見送り理由
- local refs の範囲不足があった場合は、その旨

やってはいけないこと:

- 候補選定のたびに upstream main 全体を fetch しようとする。
- local に存在しない commit を前提に probe 手順へ進む。
- `origin/main` や `main` という ref 名をそのまま baseline/candidate として扱う。
- 候補が見つからないまま web 検索や広範囲の試行錯誤に進む。
- commit 数だけで選ぶ。必ず `include` / `modules` と `DEPS` / source drift も見る。

### Step 2: Probe Without Lock Update

目的:

- candidate を official baseline にする前に、差分の性格と想定負債を測る。

手順:

1. candidate を一時 checkout または別 checkout で用意する。
2. baseline と candidate の public header delta を出す。
3. `DEPS`、`gn/*.gni`、Bazel metadata、mirror 済み source directory の drift を見る。
4. coverage generator が candidate root を扱える状態なら、candidate coverage regression を取得する。
5. 前回 coverage matrix と candidate coverage matrix を比較し、vendor 側で削除された public method に対応する C API が残っていないか stale C API report を取得する。
6. generator が candidate root または stale C API report を扱えない場合は、先に tooling を整える。

成果物:

- `docs/plans/skia-incremental-upgrade/records/` に cycle record を作る。
- probe 段階では `vendor/skia-source.lock` を更新しない。
- probe 段階では原則 C API 実装を入れない。ただし probe tooling の小修正は許容する。

推奨コマンド:

```sh
git -C vendor/skia-upstream-candidate checkout <candidate>
mkdir -p .tmp/skia-upgrade-cycle-XXX
cp docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  .tmp/skia-upgrade-cycle-XXX/previous-public-api-coverage-matrix.csv

python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream-candidate \
  --output .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv \
  --previous-matrix docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv

awk -F, 'NR>1{c[$10]++} END{for (k in c) print k,c[k]}' \
  .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv
awk -F, 'NR>1{c[$6]++} END{for (k in c) print k,c[k]}' \
  .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv
```

probe で `stale_capi` が出た場合:

- まず upstream header で該当 method/class が本当に削除されたか確認する。
- 削除済みなら、対応する C API 宣言・実装も削除するのが原則。
- 互換維持のために残す場合は、cycle record に理由と削除期限または明示分類を書く。
- stale を放置したまま lock update しない。

### Step 3: Routing

目的:

- candidate 由来の新規差分を実装順に分解する。

分類:

- `core-codec-low-risk`: Core / Codec / simple value object / helper。
- `text-module`: SkUnicode / SkShaper / SkParagraph / Skottie text。
- `gpu-ganesh-graphite`: Ganesh / Graphite common。
- `optional-backend`: Dawn / Vulkan / Metal / Android / platform-specific helper。
- `generator-noise`: public API ではない、または parser 誤検出。
- `design-required`: callback/provider/global registration/ownership 設計が必要なもの。
- `removed-upstream`: vendor public API から削除された method/class/header に対応する C API が残っているもの。

判断:

- すぐ実装できる public method は `real_gap` として実装へ回す。
- platform 依存や backend 未有効領域は既存 policy に沿って `na` または roadmap 行へ回す。
- internal/private surface は `false_positive` として理由を残す。
- ownership 設計が必要なものは、この段階では実装せず設計メモ化する。
- `removed-upstream` は原則として C API も削除する。互換維持などで残す場合は、cycle record に理由、削除期限、または明示的な分類を残す。

### Step 4: Source/Header Sync and C API Catch-up

目的:

- candidate snapshot に Reskia の mirror source/header と C API binding を追従させる。

推奨順:

1. Low-risk Core / Codec。
2. Text / module helper。
3. GPU common。
4. Optional backend routing。
5. 設計必須領域のメモ化。

作業ルール:

- area ごとに小さく分ける。
- 各 area の終了ごとに coverage を再生成する。
- `missing` は一時的に許容しても、cycle close 前に必ず 0 に戻す。
- safety policy、ownership policy、optional backend policy を変える場合は理由を文書化する。
- upstream の `bazel/`、`gn/*.gni`、CanvasKit metadata など、Reskia の tracked mirror surface ではないファイルを機械同期で混ぜない。混ざった場合は cycle record に「意図的に同期しない」と書き、最終差分から除外する。
- rename は CMake 明示リストに残りやすい。`git diff --name-status` の `R*` 行を確認し、削除元が CMake に残っていないか `rg` で確認する。

### Step 5: Verification Gate

目的:

- candidate bump を accepted baseline にしてよいか判定する。

最低 gate:

- public API coverage regeneration。
- coverage matrix: `missing 0` / `deferred 0` / `partial 0` / `overcovered 0`。
- stale C API report: `stale_capi 0`。`signature_changed_review` が出た場合は ABI 互換性を確認し、実装修正または cycle record の分類で解消する。
- prebuilt `reskia` configure/build。
- source `reskia` configure/build。
- GPU smoke: `PASS` または expected `SKIP`/`PASS`。
- source SVG/provider smoke。

追加 gate:

- text stack に触れた場合は text/skparagraph/skshaper smoke。
- optional backend に触れた場合は backend-specific configure/build または expected skip note。
- callback/provider foundation に触れた場合は ownership/design note と focused ABI smoke。

### Step 6: Lock Update and Cycle Close

目的:

- accepted candidate を新しい Reskia Skia baseline にする。

lock update 条件:

- coverage が freeze 状態に戻っている。
- stale C API report が解消済み、または残す理由が明確である。
- build/smoke gate が通っている。
- cycle record が残っている。
- source sync note が残っている。
- optional backend / design-required の未実装理由が明確である。

実施内容:

- `vendor/skia-source.lock` の `SKIA_REF` と `SKIA_BASELINE_DATE` を更新する。
- cycle record に final result を追記する。
- 次サイクルの候補選定基準を更新する。

## 停止条件

次のいずれかが出たら、そのサイクルでは lock update へ進まない。

- public header delta が想定より大きく、1サイクルで `missing 0` に戻せない。
- `DEPS` / third_party roll が Reskia の dependency model に大きな変更を要求する。
- CMake source sync が広範囲に壊れ、Reskia 側の build system 整備が先に必要になる。
- callback/provider/global registration など、ABI ownership 設計なしに実装すると危険な API が中心になる。
- optional backend の有効化方針が未決のまま build surface に入ってくる。

停止した場合:

- 候補 commit を前倒しして小さくする。
- または日付単位ではなく feature area ごとの cycle に分割する。
- 停止理由は cycle record に残す。

## 初回サイクル

初回は次の commit を probe 候補にする。

- candidate: `5f54e9f84cff8c42fd645ec53c1727857bdb12ab`
- date: 2023-12-05T19:49:10Z
- baseline からの commit 数: 181
- diff: `include` / `modules` で 83 files, +1147/-565
- 位置づけ: 2週間幅の妥当性を検証する最初の probe。

初回の最低完了条件:

1. candidate root を使った public API delta / coverage regression の再現可能な取得。
2. 新規差分の row-level routing。
3. Core / Codec など低リスク領域の追従可否確認。
4. GPU / optional backend / design-required の残量見積もり。

結果が軽ければ accepted bump へ進む。重ければ `600986ba305dcb2c61f02749d992e46d5996a1e7` を fallback candidate として1週間幅に戻す。

## 長期運用

当面は2週間幅を標準とし、各サイクルの結果で調整する。

- 連続して build/coverage gate が軽く通る場合: 3-4週間幅を試す。
- 毎回 optional backend / dependency drift が重い場合: 1週間幅へ戻す。
- 特定領域が大きい場合: 日付幅ではなく area-specific cycle に切る。
- latest main への直接追従は、複数サイクルで source sync と coverage regression の傾向が見えてから検討する。
