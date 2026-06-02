# Public API Coverage Workflow

この文書は、Skia public API と Reskia C API の対応状況を確認する workflow をまとめます。

## 目的

Reskia は Skia public API を可能な範囲で C ABI に公開します。その進捗は coverage matrix で管理します。

coverage workflow で確認すること:

- upstream Skia public header にある class / method。
- Reskia C API として対応済みか。
- 対応しない場合の理由。
- Skia 更新で stale になった C API がないか。

## 主要ファイル

| パス | 役割 |
| --- | --- |
| `scripts/generate_public_api_coverage.py` | coverage matrix generator。 |
| `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` | 現在の coverage matrix。 |
| `docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv` | upstream から消えた API に対応する stale C API report。 |
| `vendor/skia-upstream` | baseline Skia public header の参照先。 |
| `vendor/skia-upstream-candidate` | upgrade candidate の参照先。 |

## Matrix の読み方

matrix は Skia public API の行ごとに、Reskia 側の対応状態を記録します。

重要な status:

| status | 意味 |
| --- | --- |
| `covered` | 対応する C API が存在する。 |
| `split_covered` | 1つの Skia API を複数の C API に分けて対応している。 |
| `false_positive` | generator が拾ったが、実際には公開対象として扱わない。 |
| `na` | C ABI として公開しない理由がある。 |
| `missing` | 対応が必要。 |
| `deferred` | 後続作業に回す。現在は原則 0 を維持する。 |
| `partial` | 部分対応。現在は原則 0 を維持する。 |
| `overcovered` | Reskia 側が upstream public API を超えている可能性。現在は原則 0 を維持する。 |

`missing` / `deferred` / `partial` / `overcovered` は 0 を維持することを基本にします。

## 通常の再生成

baseline に対して matrix を再生成する例:

```bash
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

stale report が header のみであれば、upstream 側で消えた public API に対応する C API は検出されていません。

## Candidate Probe

Skia upgrade candidate を試すときは、lock を更新する前に candidate checkout に対して generator を実行します。

```bash
mkdir -p .tmp/skia-upgrade-cycle-XXX
python3 scripts/generate_public_api_coverage.py \
  --skia-root vendor/skia-upstream-candidate \
  --output .tmp/skia-upgrade-cycle-XXX/candidate-public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output .tmp/skia-upgrade-cycle-XXX/candidate-stale-capi.csv
```

candidate matrix で見ること:

- `missing` が増えていないか。
- `deferred` / `partial` / `overcovered` が出ていないか。
- stale C API が出ていないか。
- optional module や platform 依存の理由が妥当か。

## Overrides

generator が自動判定できないものは override CSV で理由を管理します。

override は、単に debt を隠すために使いません。次のような場合に使います。

- C ABI として安全に公開できない。
- optional module / platform dependency が必要。
- Skia API が template、private helper、callback-heavy などで直接公開に向かない。
- 既に別名または分割 API で対応済み。
- generator の false positive。

override を追加した場合は、理由を短く具体的に書きます。

## Stale C API Report

Skia 側で public API が削除・変更された場合、Reskia C API が古いまま残ることがあります。`--stale-output` はその候補を検出します。

stale row が出た場合:

1. upstream で本当に削除・変更されたか確認する。
2. Reskia C API が互換目的で残すべきものか判断する。
3. 残すなら理由を記録する。
4. 不要なら C API、header、source list、tests、docs を削除する。

## 変更時の checklist

C API を追加・削除・rename したら、次を確認します。

1. public header と実装が一致している。
2. source list に追加・削除が反映されている。
3. ownership / lifetime comment がある。
4. smoke test が必要な範囲で追加されている。
5. coverage matrix が再生成できる。
6. stale report が想定どおり。
7. build が通る。

## 関連文書

- `docs/ja/guides/c-api-bindings-overview.md`
- `docs/ja/guides/c-api-safety-guidelines.md`
- `docs/ja/guides/skia-upgrade-workflow.md`
