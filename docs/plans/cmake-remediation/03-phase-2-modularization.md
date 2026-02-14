# 03 Phase 2: Modularization (`skia/CMakeLists.txt`)

## ゴール

`skia/CMakeLists.txt` の責務分離を行い、差分レビューと追従作業を容易化する。

## 方針

- `skia/CMakeLists.txt` は「エントリ」に限定
- ソース群・プラットフォーム分岐・テスト定義を別モジュール化

## 想定分割

- `cmake/reskia/sources-core.cmake`
- `cmake/reskia/sources-binding.cmake`
- `cmake/reskia/sources-static.cmake`
- `cmake/reskia/platform-win32.cmake`
- `cmake/reskia/platform-apple.cmake`
- `cmake/reskia/platform-unix.cmake`
- `cmake/reskia/tests.cmake`

## 作業ステップ

1. ソース列挙の移設 ✅ 完了（2026-02-14）
- `SOURCE_FILES` を用途別ファイルへ移す。
- 機能差分を起こさないよう、まずは単純移設を優先。
  - 実施内容:
    - `cmake/reskia/sources-core.cmake` を追加し、Skia本体の `SOURCE_FILES` 列挙を移設
    - `cmake/reskia/sources-binding.cmake` を追加し、`binding/*.cpp` の列挙を移設
    - `cmake/reskia/sources-static.cmake` を追加し、`static/*.cpp` の列挙を移設
    - `skia/CMakeLists.txt` は `set(SOURCE_FILES reskia.cpp)` 後に上記3ファイルを `include()` する構成へ変更
  - 検証結果:
    - `cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug`: 成功
    - `cmake --build skia/cmake-build-cmake-review -j 8`: 成功（`Built target reskia`）
    - `cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功

2. ターゲット定義の明確化
- `add_library(reskia ...)` 後に `target_include_directories` / `target_compile_definitions` / `target_link_libraries` を集約。

3. テストを分離
- `RESKIA_BUILD_TESTS` ブロックを `tests.cmake` へ移動。

4. 回帰検証

```bash
cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-cmake-review -j 8
cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
```

## 完了条件

- `skia/CMakeLists.txt` の行数を大幅に削減（エントリ中心）
- `prebuilt/source` で configure 成功
- `cmake-status.csv` の `skia/CMakeLists.txt` を `done`
