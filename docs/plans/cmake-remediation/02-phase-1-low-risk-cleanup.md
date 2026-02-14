# 02 Phase 1: Low-risk Cleanup

## ゴール

ビルド挙動を大きく変えずに、可読性と管理性を先に上げる。

## 対象

- `skpath/CMakeLists.txt`
- `svg/CMakeLists.txt`
- `skcms/CMakeLists.txt`
- `skresources/CMakeLists.txt`
- `third_party/CMakeLists.txt`

## 作業ステップ

1. 命名の一貫化
- `skpath` の `project(skcms)` を意図に合う名称へ変更。
- ライブラリ名の衝突リスクを解消（必要なら `ALIAS` で互換維持）。

2. `svg` の `project()` 再定義を解消
- `project()` は1回のみ。
- `svg/skshaper/skunicode` は `add_library()` で管理。

3. グローバル設定の最小化
- `include_directories/link_directories` を可能な範囲で `target_*` に置換。
- 未使用コメント資産（OpenMP など）を整理。

4. configure回帰確認

```bash
cmake -S skcms -B skcms/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S skpath -B skpath/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S skresources -B skresources/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S svg -B svg/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
```

## 完了条件

- `project()` の多重定義なし
- `skpath` 命名不一致を解消
- フェーズ対象を `cmake-status.csv` で `done`
