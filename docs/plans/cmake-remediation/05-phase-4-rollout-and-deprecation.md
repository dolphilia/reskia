# 05 Phase 4: Rollout and Deprecation

## ゴール

新構成へ移行し、旧運用（曖昧なグローバル設定・肥大化エントリ）を段階的に整理する。

## 作業ステップ

1. 移行ガイド公開 ✅ 完了（2026-02-14）
- 旧手順と新手順の差分を README/docs に反映。
- `RESKIA_DEPS_MODE` ごとの推奨手順を一本化。
  - 実施内容:
    - 追加: `docs/guides/cmake-migration-guide.md`
      - 旧手順（`skia/lib` 前提）と新手順（mode 明示）の差分を表形式で明記
      - `prebuilt/source/system` の推奨コマンドを一本化
    - 更新: `README.md`
      - `CMake 移行ガイド（Phase 4）` セクションを追加
      - 旧運用と新運用の差分要点を明記し、標準参照先を統一

2. 旧構成の整理 ✅ 完了（2026-02-14）
- 使われない変数/コメントアウトを削除。
- 互換目的で残す要素には期限（いつ削除するか）を記載。
  - 実施内容:
    - 更新: `skia/CMakeLists.txt`
      - 未使用のコメントアウト source 行（`SkWGL_win.cpp`, `SkFontMgr_empty_factory.cpp`）を削除
    - 更新: `cmake/deps/ReskiaDeps.cmake`
      - `WIN32 + RESKIA_DEPS_MODE=system` の prebuilt 互換リンク名維持について、削除期限 `2026-06-30` を明記
  - 検証:
    - `cmake -S skia -B skia/cmake-build-phase4-step2 -DCMAKE_BUILD_TYPE=Release`: 成功
    - `cmake --build skia/cmake-build-phase4-step2 -j 8`: 成功（`Built target reskia`）

3. 最終整合確認 ✅ 完了（2026-02-14）

```bash
cmake -S skia -B skia/cmake-build-final -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-final -j 8
```

- 実行結果:
  - `cmake -S skia -B skia/cmake-build-final -DCMAKE_BUILD_TYPE=Release`: 成功
  - `cmake --build skia/cmake-build-final -j 8`: 成功（`Built target reskia`）

4. 進捗クローズ ✅ 完了（2026-02-14）
- `checklists/cmake-status.csv` を全件 `done` or `na` にする。
- `na` は `note` に理由を残す。
  - 実施内容:
    - 更新: `docs/plans/cmake-remediation/checklists/cmake-status.csv`
      - 未完了 6 件（`cmake/deps/ReskiaDeps.cmake`, `skcms/skpath/skresources/svg/third_party`）を実績に基づき `done` 化
      - 各行に `phase` と `note` を補完
  - 集計結果:
    - `done`: 11 件
    - `na`: 0 件
    - 未完了件数（`done`/`na` 以外）: 0

## 完了条件

- CMake構成改善後の標準手順が docs で一意
- 主要 CMake ファイルの責務が分離
- 継続運用での変更ルール（PR粒度・レビュー観点）が定義済み

## 完了状況（2026-02-14）

- 作業ステップ 1: 完了
- 作業ステップ 2: 完了
- 作業ステップ 3: 完了
- 作業ステップ 4: 完了
