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

1. 命名の一貫化 ✅ 完了（2026-02-14）
- `skpath` の `project(skcms)` を意図に合う名称へ変更。
- ライブラリ名の衝突リスクを解消（必要なら `ALIAS` で互換維持）。
  - 実施内容:
    - `project(skpath LANGUAGES CXX)` へ修正
    - 実ターゲットを `skpath_skcms` に変更
    - 互換用 `ALIAS` として `skpath::skcms` を追加
    - `skcms` は未定義時のみ `ALIAS` 提供（同時取り込み時の衝突回避）

2. `svg` の `project()` 再定義を解消 ✅ 完了（2026-02-14）
- `project()` は1回のみ。
- `svg/skshaper/skunicode` は `add_library()` で管理。
  - 実施内容:
    - `project(svg LANGUAGES CXX)` に明示化
    - `project(skshaper)` / `project(skunicode)` を削除
    - `skshaper` / `skunicode` は `add_library()` のみで管理

3. グローバル設定の最小化 ✅ 完了（2026-02-14）
- `include_directories/link_directories` を可能な範囲で `target_*` に置換。
- 未使用コメント資産（OpenMP など）を整理。
  - 実施内容:
    - `skcms/skpath/skresources/svg` の `include_directories/link_directories` を削減し、各ターゲットへ `target_include_directories` を適用
    - `set(CMAKE_CXX_STANDARD 17)` をターゲット単位の `target_compile_features(... cxx_std_17)` へ移行
    - `skcms/skpath/skresources` の未使用 OpenMP/CUDA コメント資産を削除

4. configure回帰確認 ✅ 完了（2026-02-14）

```bash
cmake -S skcms -B skcms/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S skpath -B skpath/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S skresources -B skresources/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake -S svg -B svg/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
```

- 実施結果:
  - `skcms`: configure/build 成功（`Built target skcms`）
  - `skpath`: configure/build 成功（`Built target skpath_skcms`）
  - `skresources`: configure/build 成功（`Built target skresources`）
  - `svg`: configure/build 成功（`Built target skunicode`, `Built target skshaper`, `Built target svg`）

## 完了条件

- `project()` の多重定義なし
- `skpath` 命名不一致を解消
- フェーズ対象を `cmake-status.csv` で `done`
