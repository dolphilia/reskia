# 05 Phase 4: Rollout and Deprecation

## ゴール

新構成へ移行し、旧運用（曖昧なグローバル設定・肥大化エントリ）を段階的に整理する。

## 作業ステップ

1. 移行ガイド公開
- 旧手順と新手順の差分を README/docs に反映。
- `RESKIA_DEPS_MODE` ごとの推奨手順を一本化。

2. 旧構成の整理
- 使われない変数/コメントアウトを削除。
- 互換目的で残す要素には期限（いつ削除するか）を記載。

3. 最終整合確認

```bash
cmake -S skia -B skia/cmake-build-final -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-final -j 8
```

4. 進捗クローズ
- `checklists/cmake-status.csv` を全件 `done` or `na` にする。
- `na` は `note` に理由を残す。

## 完了条件

- CMake構成改善後の標準手順が docs で一意
- 主要 CMake ファイルの責務が分離
- 継続運用での変更ルール（PR粒度・レビュー観点）が定義済み
