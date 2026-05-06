# Checklists

進捗トラッキング用CSVです。

- `capi-status.csv`
- `handles-status.csv`
- `phase2-type-classification.md`（Phase 2 Step1 の型分類表）
- `phase2-release-api-status.csv`（Phase 2 Step2 の解放API統一専用チェックリスト）
- `phase2-type-hardening-status.csv`（Phase 2 Step3 の型情報補強専用チェックリスト）
- `phase2-enum-int-status.csv`（Phase 2 Step3 の enum/int 露出改善専用チェックリスト）
- `phase2-handle-key-typing-status.csv`（Phase 2 Step3 の static handle key の int 露出改善専用チェックリスト）
- `public-api-coverage-matrix.csv`（vendored Skia 公開 class/struct method と Reskia C API 関数名の機械照合マトリクス）
- `public-api-core-effects-missing-triage.csv`（`include/core` / `include/effects` の missing method を `real_gap` / `na` / `false_positive` に仕分けたもの）

更新ルール:

1. ファイル修正に着手したら `status=doing`
2. 実装 + ビルド + レビュー完了で `status=done`
3. 対象外は `status=na` とし `note` に理由を書く

必須:

- フェーズ終了時に未完了件数を集計し、0件を確認する
- 集計コマンドは `01-file-coverage-governance.md` を参照

## Public API coverage matrix

`public-api-coverage-matrix.csv` は生成物です。手編集せず、次のコマンドで再生成してください。

```bash
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
```

判定は C++ AST ではなく公開ヘッダと C API 関数名の静的照合です。`method_status=missing` は実装漏れ候補、`partial` は overload や意味名 API の追加確認候補、`covered` は対応関数が見つかった候補として扱います。誤検出があり得るため、作業着手時には該当 upstream header と `skia/capi` 実装を確認してください。
