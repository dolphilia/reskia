# Skia Upgrade Workflow

この文書は、Reskia が upstream Skia に追従するときの標準 workflow をまとめます。

詳細な cycle 計画と履歴は `docs/ja/plans/skia-incremental-upgrade/` にあります。このガイドでは、継続的に使う判断基準だけを扱います。

## 基本方針

Skia 追従では、`vendor/skia-source.lock` の fixed commit を現在の baseline とします。

原則:

1. floating な `main` を baseline にしない。
2. candidate は commit hash で固定する。
3. probe が通るまで `vendor/skia-source.lock` を更新しない。
4. public API coverage、stale C API、source drift、build / smoke を確認する。
5. cycle の結果は record と HANDOFF に残す。

## 主要ファイル

| パス | 役割 |
| --- | --- |
| `vendor/skia-source.lock` | 現在の accepted Skia commit。 |
| `vendor/skia-upstream` | accepted baseline の参照 checkout。 |
| `vendor/skia-upstream-candidate` | candidate probe 用 checkout。 |
| `docs/ja/plans/skia-incremental-upgrade/HANDOFF.md` | 次 cycle への引き継ぎ。 |
| `docs/ja/plans/skia-incremental-upgrade/records/` | cycle record。 |
| `scripts/generate_public_api_coverage.py` | candidate coverage と stale C API の確認。 |

## 1 cycle の流れ

### 1. Baseline Check

現在の状態を確認します。

```bash
git branch --show-current
git status --short --branch
cat vendor/skia-source.lock
git -C vendor/skia-upstream rev-parse HEAD
git -C vendor/skia-upstream status --short --branch
```

この段階では lock を変更しません。

### 2. Candidate Selection

次に試す Skia commit を1つ選びます。

選定基準:

- commit hash で固定できる。
- local refs に存在する。
- baseline からの変更量が大きすぎない。
- public header 差分、source drift、dependency drift が説明できる。
- large dependency roll や backend migration が大きすぎる場合は幅を縮める。

候補確認例:

```bash
baseline=$(sed -n 's/^SKIA_REF="//p' vendor/skia-source.lock | sed 's/"$//')
git -C vendor/skia-upstream show -s --format='%H%n%cI%n%s' <candidate>
git -C vendor/skia-upstream rev-list --count "$baseline"..<candidate>
git -C vendor/skia-upstream diff --shortstat "$baseline"..<candidate> -- include modules
git -C vendor/skia-upstream diff --name-status "$baseline"..<candidate> -- include modules
```

### 3. Probe Without Lock Update

candidate checkout を用意し、lock を変えずに差分を測ります。

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream-candidate \
  --output .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv
```

確認すること:

- public API coverage regression。
- stale C API。
- `DEPS`、`gn`、Bazel metadata の drift。
- mirror 済み source directory の追加・削除。
- optional backend や platform dependency の影響。

### 4. Routing

probe 結果を分類します。

| 分類 | 対応 |
| --- | --- |
| source sync のみ | source list や missing file を同期する。 |
| C API catch-up | header / implementation / tests / matrix を更新する。 |
| optional backend drift | feature flag、guard、unsupported 理由を確認する。 |
| tooling gap | coverage generator や stale report を先に直す。 |
| candidate が大きすぎる | candidate を deferred として記録し、幅を縮める。 |

### 5. Verification Gate

少なくとも次を確認します。

```bash
git diff --check
cmake -S skia -B skia/cmake-build-upgrade-prebuilt -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-upgrade-prebuilt -j 8
```

変更内容に応じて、source mode、feature smoke、coverage regeneration、stale report も実行します。

### 6. Lock Update

probe、routing、verification が通った後でだけ、`vendor/skia-source.lock` を candidate commit に更新します。

lock update 後に行うこと:

- `vendor/skia-upstream` を accepted commit に合わせる。
- coverage matrix を accepted baseline で再生成する。
- stale C API report を確認する。
- cycle record と HANDOFF を更新する。

## 停止条件

次の場合は lock を更新しません。

- candidate が local refs に存在しない。
- coverage generator が candidate を処理できない。
- stale C API の判断が未完了。
- build / smoke が失敗して原因を説明できない。
- dependency roll や backend migration が大きく、cycle 内で扱いきれない。

停止した場合は、candidate、理由、次に確認することを HANDOFF に残します。

## 関連文書

- `docs/ja/guides/public-api-coverage-workflow.md`
- `docs/ja/guides/repository-structure.md`
- `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md`
- `docs/ja/plans/skia-incremental-upgrade/HANDOFF.md`
