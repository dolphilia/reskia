# 03 Phase 2: Modularization (`skia/CMakeLists.txt`)

## ゴール

`skia/CMakeLists.txt` の責務分離を行い、差分レビューと追従作業を容易化する。

## 方針

- `skia/CMakeLists.txt` は「エントリ」に限定
- ソース群・プラットフォーム分岐・テスト定義を別モジュール化

## 想定分割

- `cmake/reskia/sources-core.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/sources-handles.cmake`
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
    - `cmake/reskia/sources-capi.cmake` を追加し、`capi/*.cpp` の列挙を移設
    - `cmake/reskia/sources-handles.cmake` を追加し、`handles/*.cpp` の列挙を移設
    - `skia/CMakeLists.txt` は `set(SOURCE_FILES reskia.cpp)` 後に上記3ファイルを `include()` する構成へ変更
  - 検証結果:
    - `cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug`: 成功
    - `cmake --build skia/cmake-build-cmake-review -j 8`: 成功（`Built target reskia`）
    - `cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功

2. ターゲット定義の明確化 ✅ 完了（2026-02-14）
- `add_library(reskia ...)` 後に `target_include_directories` / `target_compile_definitions` / `target_link_libraries` を集約。
  - 実施内容:
    - グローバル `include_directories(${PROJECT_SOURCE_DIR}/)` と `include_directories(${PROJECT_SOURCE_DIR}/_include)` を削除
    - `set(CMAKE_CXX_STANDARD 17)` を削除し、`target_compile_features(reskia PRIVATE cxx_std_17)` を追加
    - グローバル `link_directories(${RESKIA_DEP_LINK_DIRS})` を削除し、`target_link_directories(reskia PRIVATE ${RESKIA_DEP_LINK_DIRS})` へ移行
    - `target_include_directories(reskia PRIVATE ...)` を追加し、include path を `reskia` ターゲットに集約
  - 検証結果:
    - `cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug`: 成功
    - `cmake --build skia/cmake-build-cmake-review -j 8`: 成功（`Built target reskia`）
    - `cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功

3. テストを分離 ✅ 完了（2026-02-14）
- `RESKIA_BUILD_TESTS` ブロックを `tests.cmake` へ移動。
  - 実施内容:
    - `cmake/reskia/tests.cmake` を追加し、`option(RESKIA_BUILD_TESTS ...)` と `test_c_skia` 定義を移設
    - `skia/CMakeLists.txt` のテストブロックを削除し、`include("${RESKIA_ROOT_DIR}/cmake/reskia/tests.cmake")` へ置換
  - 検証結果:
    - `cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug`: 成功
    - `cmake --build skia/cmake-build-cmake-review -j 8`: 成功（`Built target reskia`）
    - `cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功

4. 回帰検証 ✅ 完了（2026-02-14）

```bash
cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-cmake-review -j 8
cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
```

- 実行結果:
  - `cmake -S skia -B skia/cmake-build-cmake-review -DCMAKE_BUILD_TYPE=Debug`: 成功
  - `cmake --build skia/cmake-build-cmake-review -j 8`: 成功（`Built target reskia`）
  - `cmake -S skia -B skia/cmake-build-cmake-review-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功
- 完了判定:
  - `skia/CMakeLists.txt` は 94 行（モジュール分割前 884 行から削減）
  - `prebuilt/source` で configure 成功
  - `cmake-status.csv` の `skia/CMakeLists.txt` を `done` へ更新

## 完了条件

- `skia/CMakeLists.txt` の行数を大幅に削減（エントリ中心）
- `prebuilt/source` で configure 成功
- `cmake-status.csv` の `skia/CMakeLists.txt` を `done`
