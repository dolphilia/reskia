# Checklists

進捗トラッキング用CSVです。

- `binding-status.csv`
- `static-status.csv`

更新ルール:

1. ファイル修正に着手したら `status=doing`
2. 実装 + ビルド + レビュー完了で `status=done`
3. 対象外は `status=na` とし `note` に理由を書く

必須:

- フェーズ終了時に未完了件数を集計し、0件を確認する
- 集計コマンドは `01-file-coverage-governance.md` を参照
