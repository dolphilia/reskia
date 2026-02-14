# Checklists

進捗トラッキング用CSVです。

- `binding-status.csv`
- `static-status.csv`
- `phase2-type-classification.md`（Phase 2 Step1 の型分類表）
- `phase2-release-api-status.csv`（Phase 2 Step2 の解放API統一専用チェックリスト）
- `phase2-type-hardening-status.csv`（Phase 2 Step3 の型情報補強専用チェックリスト）

更新ルール:

1. ファイル修正に着手したら `status=doing`
2. 実装 + ビルド + レビュー完了で `status=done`
3. 対象外は `status=na` とし `note` に理由を書く

必須:

- フェーズ終了時に未完了件数を集計し、0件を確認する
- 集計コマンドは `01-file-coverage-governance.md` を参照
