# CMake構成レビュー（2026-02-14）

対象: `/Users/dolphilia/github/reskia`  
確認時刻: 2026-02-14 11:37:43 JST

## 1. 調査対象と現状

主要CMakeエントリ:

- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skcms/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skpath/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skresources/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake`
- `/Users/dolphilia/github/reskia/third_party/CMakeLists.txt`

configure確認（2026-02-14）:

- `skia`, `skcms`, `skpath`, `skresources`, `svg` は configure 成功
- `skia` は `prebuilt/source` 両モードで configure 成功（この環境）

## 2. 問題点（優先度順）

### P0: `skia/CMakeLists.txt` への責務集中（単一巨大ファイル）

`skia/CMakeLists.txt` が以下を1ファイルで抱えている:

- 依存解決モード切替
- プラットフォーム分岐
- 膨大な `SOURCE_FILES` 列挙
- C binding/static 追加
- テスト定義

影響:

- レビュー負荷が高く、変更時の差分把握が難しい
- source list の更新漏れが起きやすい

### P0: グローバル指向コマンドの多用

`include_directories()` / `link_directories()` が多く、ターゲット境界が曖昧。

- 例: `/Users/dolphilia/github/reskia/skia/CMakeLists.txt:4`
- 例: `/Users/dolphilia/github/reskia/svg/CMakeLists.txt:4`
- 例: `/Users/dolphilia/github/reskia/skcms/CMakeLists.txt:10`

影響:

- 他ターゲットへの副作用・将来の衝突要因
- IDE統合や再利用時の予測可能性低下

### P1: `svg/CMakeLists.txt` の `project()` 再定義

1ファイル内で `project(svg)` の後に `project(skshaper)` / `project(skunicode)` を再定義。

- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt:2`
- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt:60`
- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt:66`

影響:

- 変数/メタ情報が上書きされ、読み手の認知負荷が高い
- 将来のツール連携で不整合が起きやすい

### P1: `skpath` の命名/実体不一致

`skpath/CMakeLists.txt` が `project(skcms)` + `add_library(skcms ...)` となっている。

- `/Users/dolphilia/github/reskia/skpath/CMakeLists.txt:7`

影響:

- 目的が分かりにくく、ビルドログ上も識別しづらい
- `skcms` と混同しやすい

### P1: 依存解決モードのプラットフォーム差異が大きい

`ReskiaDeps.cmake` では:

- `APPLE` は `source/system` 整備あり
- `WIN32` は `source` 未実装（`FATAL_ERROR`）
- `UNIX` は最小リンク（実質未整備）

- `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake:105`

影響:

- クロスプラットフォーム再現性が低い
- CI設計が複雑化

### P2: テスト定義の分離不足

テスト定義が `skia/CMakeLists.txt` 本体末尾に直接埋め込まれている。

- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt:872`

影響:

- 本体変更とテスト変更が同時に混ざりやすい

### P2: コメントアウト資産の蓄積

OpenMPや未使用ソースのコメントアウトが複数箇所に散在。

- 例: `/Users/dolphilia/github/reskia/skcms/CMakeLists.txt`
- 例: `/Users/dolphilia/github/reskia/skresources/CMakeLists.txt`

影響:

- 現在有効な設計意図が読み取りづらい

## 3. 改善案（短期）

1. ターゲット指向へ置換

- `include_directories` -> `target_include_directories`
- `link_directories` -> 可能な限り廃止し、`target_link_libraries` にフルパス/IMPORTEDを渡す

2. `skia/CMakeLists.txt` 分割

- `cmake/reskia/sources_core.cmake`
- `cmake/reskia/sources_binding.cmake`
- `cmake/reskia/sources_static.cmake`
- `cmake/reskia/platform_apple.cmake` 等
- `cmake/reskia/tests.cmake`

3. `svg` の `project()` 一つ化

- `project(svg_modules)` 等に統一
- `svg/skshaper/skunicode` は `add_library` のみで管理

4. `skpath` 命名整理

- 最低限 `project(skpath)` に変更
- ライブラリ名も `skpath` へ寄せるか、`skcms_compat` など意図名へ変更

5. source list 検証の自動化

- `cmake --build` 前に list 健全性を検査する簡易スクリプト導入

## 4. 改善案（中期）

1. ルート `CMakeLists.txt` 追加（Superbuild）

- `option(RESKIA_BUILD_SKIA ...)`
- `option(RESKIA_BUILD_SKCMS ...)`
- `option(RESKIA_BUILD_SVG ...)`
- 依存関係をトップで一元制御

2. `ReskiaDeps.cmake` のAPI整理

- モード別に関数分割:
  - `reskia_deps_prebuilt()`
  - `reskia_deps_source()`
  - `reskia_deps_system()`
- platform matrix を明示表化

3. CIでモード/OS行列を固定

- macOS: `prebuilt`, `source`
- Linux: `source`（将来）
- Windows: `prebuilt`（`source`実装後に追加）

## 5. 推奨する実施順

1. `skpath` 命名整理 + `svg project()` 整理（低リスク）
2. `target_*` 化（`skcms/skresources/svg` から先行）
3. `skia/CMakeLists.txt` の source list と test 分割
4. ルート superbuild 導入
5. `ReskiaDeps.cmake` の platform matrix 整備

## 6. 管理しやすくするための具体策（運用）

- CMake変更は「1PR=1責務」に限定（依存/ソース列挙/テストを混ぜない）
- CMakeレビュー時に以下を必須チェック:
  - グローバルコマンド追加の有無
  - 新規ファイルが source list へ反映済みか
  - mode/platform で非対称が増えていないか
- docs には「モード別サポート表」を常に最新化して保持する
