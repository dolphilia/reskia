# vendor Skia 管理実装メモ（2026-02-14）

対象リポジトリ: `/Users/dolphilia/github/reskia`  
確認時刻: 2026-02-14 11:07 JST

## 1. 実装内容

- 追加: `/Users/dolphilia/github/reskia/vendor/skia-source.lock`
  - 比較・参照用 Skia の取得元と固定 ref を管理
- 追加: `/Users/dolphilia/github/reskia/scripts/fetch_skia_upstream.sh`
  - lock を読み込んで `vendor/skia-upstream` を clone/fetch
  - `--remote upstream|fork` で取得元切替
  - `--ref` で一時検証用の commit/tag/branch を指定可能
- 追加: `/Users/dolphilia/github/reskia/vendor/README.md`
  - `vendor/` 配下の管理方針を明文化

## 2. 採用理由

- `vendor/skia-upstream` をサブモジュール化すると、比較用 clone の更新が本体履歴に過剰に干渉しやすい。
- lock + fetch 方式なら、比較 clone を追跡外に保ちつつ、固定 ref は履歴化できる。
- 段階的アップグレード時に lock の差分だけで比較対象の変更を明確に管理できる。

## 3. 運用ルール

- 正本取得元は `google/skia`（upstream）
- `dolphilia/skia` は補助（互換確認や一時回避）
- 比較対象を上げるときは `vendor/skia-source.lock` の `SKIA_REF` を更新し、関連ドキュメントに結果を追記する。
