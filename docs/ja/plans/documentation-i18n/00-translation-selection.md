# 00 Translation Selection

作成日時: 2026-06-02 16:51:31 JST

## 目的

`docs/ja/` 配下の日本語ドキュメントから、将来 `docs/en/` へ英訳する価値がある文書を選定する。

今回の作業では、日本語ドキュメント本文の古さや構成は直さない。古い情報の整理、統合、削除は次タスクで扱う。

## 選定基準

英訳候補は、次の条件を満たすものを優先する。

1. 新規利用者が Reskia を理解・ビルド・利用するために読む。
2. contributor が C API / CMake / dependency / upstream sync の方針を理解するために読む。
3. 履歴ログではなく、今後も運用規約または参照ガイドとして使える。
4. 翻訳前の更新量が少ない、または更新すれば長期的な入口文書になる。

次の文書は原則として英訳しない。

1. 古い実装計画の詳細フェーズ記録。
2. 一回限りの調査メモ、build log、handoff。
3. `skia-incremental-upgrade/records/` の cycle record。
4. `stability-hardening/NNN-phase-2-batch-*.md` の batch record。
5. coverage matrix / checklist / manifest など、機械処理または内部進捗管理が主目的のファイル。

## P0: 英訳する価値が高い文書

以下は、英語圏の利用者・contributor に直接必要になる可能性が高い。

| 日本語文書 | 推奨英訳先 | 判断 | 備考 |
| --- | --- | --- | --- |
| `docs/ja/README.md` | `docs/en/README.md` | translate after refresh | リポジトリ説明、ビルド手順、機能フラグの入口。現状値と「主要ドキュメント」欄は次タスクで整理してから翻訳する。 |
| `docs/ja/guides/cmake-migration-guide.md` | `docs/en/guides/cmake-migration-guide.md` | translate after light refresh | `RESKIA_DEPS_MODE` と標準ビルド手順は外部利用者にも有用。絶対パスと Phase 4 表記は整理してから翻訳する。 |
| `docs/ja/guides/c-api-safety-guidelines.md` | `docs/en/guides/c-api-safety-guidelines.md` | translate after refresh | C ABI の所有権、invalid input、lifetime の規約は binding 利用者に重要。長いが、履歴ではなく規約文書なので英訳価値が高い。 |
| `docs/ja/guides/repository-structure.md` | `docs/en/guides/repository-structure.md` | rewrite then translate | 新規 contributor 向けに価値がある。ただし現状は調査メモと履歴が混在しているため、英訳前に構造ガイドとして短く再編する。 |

## P1: 直接翻訳ではなく、英語ガイドへ再編する候補

以下は情報価値があるが、そのまま翻訳すると古い計画や調査ログを英語化するだけになりやすい。英語版では要約・統合した新規ガイドにする方がよい。

| 参照元 | 推奨英語文書 | 判断 | 備考 |
| --- | --- | --- | --- |
| `docs/ja/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md` | `docs/en/guides/c-api-bindings-overview.md` | distill | C API / handles の全体像と代表例は有用。古い coverage 状態は削り、現行方針だけ抽出する。 |
| `docs/ja/notes/bindings/public-api-coverage-matrix-progress-2026-05-06.md` | `docs/en/guides/public-api-coverage-workflow.md` | distill | coverage generator の使い方、status の意味は contributor に有用。数値 snapshot は最新化または削除する。 |
| `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md` | `docs/en/guides/skia-upgrade-workflow.md` | distill | maintainer 向けには重要。ただし運用細部と履歴文脈が多いため、英語版では短い workflow guide にする。 |
| `docs/ja/notes/vendor-skia-management-2026-02-14.md` | `docs/en/guides/skia-upstream-management.md` | distill | lock + untracked checkout model の説明は有用。単独翻訳ではなく upgrade workflow と統合する。 |
| `docs/ja/plans/stability-hardening/00-plan.md` | `docs/en/guides/c-api-safety-guidelines.md` or `docs/en/guides/testing-and-stability.md` | distill | 安定化方針は有用だが、進捗計画としては古くなる。規約・検証方針だけ抽出する。 |
| `docs/ja/notes/project-overview-and-next-tasks-2026-05-06.md` | `docs/en/guides/architecture-overview.md` | distill | 全体像の材料として使えるが、next tasks は古くなりやすい。直接翻訳しない。 |

## P2: 条件付きで英訳する候補

以下は機能別 contributor には有用だが、現時点では古い計画の性格が強い。対応機能を外部向けに説明する段階で、計画書ではなく user/contributor guide として作り直す。

| 参照元 | 将来の英語文書候補 | 判断 |
| --- | --- | --- |
| `docs/ja/plans/gpu-enablement/00-plan.md` | `docs/en/guides/gpu-support.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/pdf-enablement/00-plan.md` | `docs/en/guides/pdf-support.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/codec-encoder-enablement/00-plan.md` | `docs/en/guides/codec-and-encoder-support.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/skottie-enablement/00-plan.md` | `docs/en/guides/skottie-support.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/skparagraph-enablement/00-plan.md` | `docs/en/guides/skparagraph-support.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/svg-text-shaping-enablement/00-plan.md` | `docs/en/guides/svg-and-text-shaping.md` | feature guide が必要になったら再編 |
| `docs/ja/plans/sksg-enablement/00-plan.md` | `docs/en/guides/sksg-support.md` | feature guide が必要になったら再編 |
| `docs/ja/notes/reskia-feature-gap-survey-2026-02-14.md` | feature support guides | 現状説明の材料としてのみ使う |

## 英訳対象外

以下は現時点では英訳しない。

- `docs/ja/plans/stability-hardening/03-phase-2-batch-*.md` 以降の batch record。
- `docs/ja/plans/stability-hardening/handoff-*.md`。
- `docs/ja/plans/skia-incremental-upgrade/records/*.md`。
- `docs/ja/plans/skia-incremental-upgrade/HANDOFF.md`。
- `docs/ja/plans/*/01-phase-*.md` 以降の個別フェーズ計画。
- `docs/ja/notes/skia-cmakelists-build-report-2026-02-13.md` など日付付き build report。
- `docs/ja/notes/bindings/phase-*.md` と `docs/ja/notes/bindings/public-api-phase*.md` の phase log。
- `docs/ja/plans/**/checklists/*`。
- `docs/ja/plans/**/manifests/*`。

これらは履歴・監査証跡として日本語のまま残し、英語版では必要に応じて現在の方針だけを上位ガイドへ取り込む。

## 推奨する英語ドキュメント初期セット

最初に `docs/en/` を作る場合は、次の小さな構成から始める。

```text
docs/en/
  README.md
  guides/
    cmake-migration-guide.md
    c-api-safety-guidelines.md
    repository-structure.md
    c-api-bindings-overview.md
    public-api-coverage-workflow.md
    skia-upgrade-workflow.md
```

ただし、英訳前に `docs/ja/README.md` と `docs/ja/guides/` を現行状態に合わせて整理する。特に `repository-structure.md` は、調査ログではなく短い構造ガイドに作り直してから翻訳する。

## 作業順

1. 日本語の入口文書を整理する。
   - `docs/ja/README.md`
   - `docs/ja/guides/repository-structure.md`
   - `docs/ja/guides/cmake-migration-guide.md`
   - `docs/ja/guides/c-api-safety-guidelines.md`
2. P1 文書から、現行情報だけを `docs/ja/guides/` の新規ガイドへ抽出する。
3. `docs/en/` を作成し、P0 から翻訳する。
4. P1 の再編済みガイドを翻訳する。
5. feature guide は、外部利用者向けに必要になった時点で個別に追加する。
