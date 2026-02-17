# 06 Phase 6: ドキュメント更新と公開ポリシー

更新日時: 2026-02-17 11:40:23 JST

## 目的

GPU 対応状況を第三者が追跡可能な状態にし、C API の公開レベルを明文化する。

## 作業項目

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.6` を進捗に合わせて更新する。
2. `docs/plans/gpu-enablement/` に backend 別制約・依存条件・既知課題を追記する。
3. API 公開レベルを定義する。
- `experimental`: 互換性保証なし
- `preview`: 破壊変更の可能性あり
- `stable`: 互換性維持対象
4. リリースノート向けに「有効化フラグ」「サポートバックエンド」「既知制約」を整理する。

## 更新対象ファイル

- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`
- `docs/plans/gpu-enablement/*.md`
- 必要に応じて `docs/` 配下のガイド

## 判定基準

1. GPU 有効化手順がコマンド付きで再現可能。
2. backend ごとのサポート範囲と未対応事項が明記されている。
3. C API の安定性レベルが利用者に伝わる。

## 引き継ぎメモ

1. CI へ GPU 構成を追加する場合は、まず 1 backend を常設し段階拡張する。
2. Dawn は experimental 扱いで運用し、安定後に preview/stable へ昇格判定する。
