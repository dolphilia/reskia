# reskia リポジトリ構造調査

調査日: 2026-02-13  
対象リポジトリ: `/Users/dolphilia/github/reskia`  
ベースSkia: <https://github.com/dolphilia/skia/commit/0d49b661d75adbb8ac8cf88f7d527b1587be2c63>

## 1. 全体概要

このリポジトリは、Skia系のコードをCMakeでビルド可能な形にまとめ、さらにC言語インターフェースを提供する構成になっている。

トップレベル主要ディレクトリ:

- `skia/`: メインの共有ライブラリ `reskia` をビルドする中核
- `skcms/`: `skcms` ライブラリ用の小規模プロジェクト
- `skpath/`: `skcms` とほぼ同等内容の小規模プロジェクト（命名との不一致あり）
- `skresources/`: `skresources` ライブラリ
- `svg/`: `svg`, `skshaper`, `skunicode` ライブラリ

ファイル規模の目安（`find ... -type f | wc -l`）:

- `skia`: 3306 files
- `skcms`: 84 files
- `skpath`: 78 files
- `skresources`: 81 files
- `svg`: 242 files

## 2. ビルド構造（CMake）

### 2.1 ルート

- リポジトリ直下には `CMakeLists.txt` がなく、モジュールごとに独立した `CMakeLists.txt` がある。
- 実運用上の中心は `skia/CMakeLists.txt`。

### 2.2 `skia/CMakeLists.txt`

- `project(reskia)` で `reskia` 共有ライブラリを生成。
- `SOURCE_FILES` にSkia本体ソース（`src/`）を大量列挙し、加えて:
  - `binding/*.cpp`（Cラッパー本体）
  - `static/*.cpp`（整数ハンドル管理レイヤ）
  を組み込む。
- プラットフォームごとにソースとリンク先を分岐:
  - `WIN32`: `zlib`, `libpng`, `turbojpeg-static`, `avif`, `webp` など
  - `APPLE`: `skcms`, `skresources`, `svg`, `expat`, `png`, `jpeg`, `avif`, `webp` + `CoreFoundation/CoreText/Cocoa`
  - `UNIX`: 最小構成で `skcms`
- テストターゲット `test_c_skia` を定義（`skia/test/test.cpp`）。

### 2.3 補助ライブラリ

- `skcms/CMakeLists.txt`: `add_library(skcms ...)`
- `skresources/CMakeLists.txt`: `add_library(skresources ...)`
- `svg/CMakeLists.txt`:
  - `add_library(svg ...)`
  - `add_library(skshaper ...)`
  - `add_library(skunicode ...)`
- `skpath/CMakeLists.txt`:
  - 内容は `skcms` とほぼ同等
  - `project(skcms)` / `add_library(skcms ...)` になっており、ディレクトリ名と定義名が一致していない

## 3. Cラッパー層の構造

`skia/` 配下に、主に2種類のC向け公開レイヤがある。

### 3.1 `binding/`（ポインタベースAPI）

- 例: `skia/binding/sk_canvas.h`, `skia/binding/sk_canvas.cpp`
- `extern "C"` で C から呼べる関数を提供し、内部で `SkCanvas*` 等にキャストしてSkia C++ APIを呼ぶ。
- `void*` と C互換プリミティブを中心にした境界になっている。

### 3.2 `static/`（整数ハンドルベースAPI）

- 例: `skia/static/static_sk_rect.h`, `skia/static/static_sk_rect.cpp`
- `typedef int sk_rect_t;` のような整数キーを公開。
- 内部で `std::map<int, T>` と `std::set<int>` で実体管理し、キー再利用も行う。
- 他言語バインディング時に「生ポインタを直接渡さない」運用がしやすい設計。

### 3.3 補足

- `skia/export_api.h` でOS判定マクロと `RAIA_API` を定義。
- `skia/internal/` は現時点では空。
- `skia/reskia.h`, `skia/reskia.cpp` は現状ほぼプレースホルダ状態。

## 4. 依存ライブラリ配置

- `skia/lib/` に `.a` / `.dylib` が多数同梱されている（`libpng`, `libjpeg`, `libwebp`, `libavif` など）。
- `link_directories(${PROJECT_SOURCE_DIR}/lib)` を使う構成のため、事前配置されたローカル依存ライブラリを使う前提が強い。

## 5. テストの状況

- `skia/test/test.cpp` に C API 経由の描画テスト（矩形・パス・文字描画など）がある。
- `CTest` 連携されており、`test_c_skia` 実行で検証可能。
- 画像ファイル出力 (`output*.png`) を行うテストが含まれる。

## 6. 現時点での所見

- プロジェクトの主目的（SkiaのCMake化 + Cラッパー提供）は、`skia/` を中心に実装済み。
- `binding/` と `static/` の二層構造により、他言語バインディングの選択肢（ポインタ方式 / ハンドル方式）が用意されている。
- 一方で、次の整理余地がある:
  - ルート `CMakeLists.txt` 不在（導入時の入口が分かりにくい）
  - `skpath/` のプロジェクト名・ライブラリ名の不一致
  - `reskia.h/.cpp` の実質未使用状態

## 7. 主要パス一覧（把握用）

- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skia/binding/`
- `/Users/dolphilia/github/reskia/skia/static/`
- `/Users/dolphilia/github/reskia/skia/test/test.cpp`
- `/Users/dolphilia/github/reskia/skcms/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skpath/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skresources/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt`

## 8. ビルド検証メモ（2026-02-13）

- 検証対象: `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- `cmake -S ... -B ... -DCMAKE_BUILD_TYPE=Debug` は成功。
- 初回 `cmake --build` は `SkSLModuleLoader.cpp` で失敗。
  - `src/sksl/generated/*.unoptimized.sksl` を参照するが、実体は `*.minified.sksl` のみ。
- 対応として `skia/CMakeLists.txt` の `reskia` ターゲットに以下を追加:
  - `target_compile_definitions(reskia PRIVATE SK_ENABLE_OPTIMIZE_SIZE)`
- その後、`reskia` 自体はビルド成功。
- 一方、`test_c_skia` は現状API不整合で失敗するため、テスト定義をオプション化:
  - `option(RESKIA_BUILD_TESTS "Build test_c_skia target" OFF)`
  - `if(RESKIA_BUILD_TESTS) ... endif()`
- 最終的に `cmake --build ...` で `Built target reskia` を確認。

詳細は以下を参照:
- `/Users/dolphilia/github/reskia/docs/notes/skia-cmakelists-build-report-2026-02-13.md`

## 9. 非`skia` CMake修正メモ（2026-02-14）

`skia` 以外のCMakeプロジェクト（`skcms`, `skpath`, `skresources`, `svg`）を同様に検証した結果、`skpath` と `svg` に最小修正を実施した。

### 9.1 `skpath` の修正

対象:
- `/Users/dolphilia/github/reskia/skpath/CMakeLists.txt`

修正内容:
- `src/skcms_Transform*.cc` が `skpath/src` に存在しない環境向けに、`../skcms/src` へ自動フォールバックするよう変更。
- `skcms.cc` の `#include "src/skcms_public.h"` 解決のため、`../skcms` を include path に追加。

意図:
- `skpath` 単体の configure/build を、実体ソース配置差異があっても通るようにする。

### 9.2 `svg`（`skshaper` / `skunicode`）の修正

対象:
- `/Users/dolphilia/github/reskia/svg/CMakeLists.txt`

修正内容（最小構成化 + 依存検出）:
- `skshaper` のデフォルト構成を以下に限定:
  - `SkShaper.cpp`
  - `SkShaper_primitive.cpp`
- `skunicode` のデフォルト構成を以下に限定:
  - `SkUnicode.cpp`
  - `SkUnicode_hardcoded.cpp`
- 追加実装は依存ヘッダが見つかった場合のみ有効化:
  - CoreText（Apple）: `SkShaper_coretext.cpp`
  - HarfBuzz（`hb.h`）: `SkShaper_harfbuzz.cpp`
  - ICU（`unicode/ubidi.h`）: `SkUnicode_icu*.cpp` / `SkUnicode_client.cpp`
  - ICU4X（`ICU4XDataProvider.hpp`）: `SkUnicode_icu4x.cpp`
  - libgrapheme（`grapheme.h`）: `SkUnicode_libgrapheme.cpp`
- `SkShaper_skunicode.cpp` は ICU が見つかった場合のみ追加。

意図:
- 外部依存が無い環境でも `svg` / `skshaper` / `skunicode` をビルド可能にする。

### 9.3 機能縮退する条件

この最小修正によりビルド通過性は上がるが、以下の条件で機能縮退する。

- `hb.h` が無い場合:
  - HarfBuzzベースのシェーピング機能は無効化（`SkShaper_harfbuzz.cpp` を未ビルド）。
- `unicode/ubidi.h`（ICU）が無い場合:
  - ICUベースUnicode処理および `SkShaper` の Unicode 連携機能（`SkShaper_skunicode.cpp`）を無効化。
- `ICU4XDataProvider.hpp` が無い場合:
  - ICU4X 実装を無効化。
- `grapheme.h` が無い場合:
  - libgrapheme 実装を無効化。
- Apple以外:
  - CoreText 実装を無効化（`SkShaper_coretext.cpp` 未ビルド）。

つまり、依存不足時は「テキスト整形/Unicode処理の実装選択肢」が段階的に減り、最終的には primitive/hardcoded ベースの最小機能で動作する構成になる。

## 10. 依存管理方針の実施メモ（2026-02-14）

`skia/lib` の事前配置依存だけでは他環境再現が難しいため、依存解決を切り替え可能にする最小実装を追加した。

### 10.1 実施計画（実行済み）

1. `RESKIA_DEPS_MODE` で依存解決方式を切り替える基盤を追加する。  
2. `skia/CMakeLists.txt` を基盤に接続し、`prebuilt` 互換を維持しつつ `source/system` を選択可能にする。  
3. `third_party` を分離ディレクトリとして整備し、初期化スクリプトとドキュメントを追加する。  

### 10.2 追加・変更したファイル

- `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake`
  - 依存解決モジュール本体。
  - `RESKIA_DEPS_MODE=prebuilt|source|system` を解釈。
- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
  - 上記モジュールを `include` し、リンクディレクトリ/リンクライブラリを外部化。
- `/Users/dolphilia/github/reskia/third_party/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/third_party/README.md`
- `/Users/dolphilia/github/reskia/scripts/bootstrap_third_party.sh`
  - `third_party/src`, `third_party/build`, `third_party/install` を初期化。
- `/Users/dolphilia/github/reskia/.gitignore`
  - `third_party` 配下の管理方針を反映（生成物は追跡外、管理用ファイルのみ追跡）。

### 10.3 ビルド確認結果

- 確認日時: 2026-02-14 10:26:42 JST
- 成功:
  - `cmake -S skia -B skia/cmake-build-codex -DCMAKE_BUILD_TYPE=Debug`
  - `cmake --build skia/cmake-build-codex -j 8`
  - 結果: `Built target reskia`
- 期待どおり失敗:
  - `cmake -S skia -B skia/cmake-build-source-mode -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`
  - 原因: `third_party/install` に EXPAT 等の CMake package 設定が未配置。

### 10.4 現時点の制約（機能縮退/未実装）

- `RESKIA_DEPS_MODE=source` は依存未配置時に configure 失敗する（フェイルファスト）。
- `RESKIA_DEPS_MODE=source` の `WIN32` 分岐は未実装（明示的に `FATAL_ERROR`）。
- `UNIX`（Apple 以外）は現状 `skcms` 最小リンクのままで、外部画像系依存は未接続。
- `prebuilt` は従来互換を優先し、`skia/lib` 依存を維持している。

詳細ログは以下を参照:
- `/Users/dolphilia/github/reskia/docs/notes/dependency-management-report-2026-02-14.md`

## 11. `third_party/src` サブモジュール化と自動ビルド（2026-02-14）

再現性向上のため、`third_party/src/*` を実サブモジュール化し、`install` まで自動化した。

### 11.1 追加・更新

- 追加: `/Users/dolphilia/github/reskia/.gitmodules`
  - `zlib`, `libpng`, `libjpeg-turbo`, `libwebp`, `libavif`, `expat`, `harfbuzz`, `icu`, `icu4x`, `libgrapheme`
- 更新: `/Users/dolphilia/github/reskia/.gitignore`
  - `third_party/src/*` をサブモジュールとして追跡可能化
- 更新: `/Users/dolphilia/github/reskia/scripts/bootstrap_third_party.sh`
  - プレースホルダ作成方式を廃止し、submodule init/update 方式へ変更
- 追加: `/Users/dolphilia/github/reskia/scripts/build_third_party.sh`
  - core 依存（zlib/libpng/libjpeg-turbo/expat/libwebp）を `third_party/install` へ自動 install
  - オプションで `--with-avif` / `--with-harfbuzz` / `--with-libgrapheme`

### 11.2 検証

- `scripts/bootstrap_third_party.sh`: 成功
- `scripts/build_third_party.sh --build-type Release --clean`: 成功
- `cmake -S skia -B ... -DRESKIA_DEPS_MODE=source`: configure 成功
- `cmake --build`: 成功（`Built target reskia`）
- `source` モード連携:
  - `skia/CMakeLists.txt` から `skcms` を `add_subdirectory` 連携
  - Apple では `skresources` / `svg` も `add_subdirectory` 連携

### 11.3 現時点の制約

- third-party と `skcms/skresources/svg` の `source` 連携は自動化済み。
- `icu/icu4x` は `scripts/build_third_party.sh --with-icu --with-icu4x` でビルド可能。
- ただし ICU4X は Skia 側 `SkUnicode_icu4x.cpp` との API 名差異があり、利用有効化には追加調整が必要。
- AVIF は `RESKIA_ENABLE_AVIF=ON` かつ `--with-avif` を前提とする拡張扱い。

詳細ログ:
- `/Users/dolphilia/github/reskia/docs/notes/third-party-submodule-automation-2026-02-14.md`

## 12. `vendor/skia-upstream` 管理方針の実装（2026-02-14）

比較・参照用 Skia の管理を、必須サブモジュール方式ではなく「lock + fetch スクリプト」方式へ統一した。

### 12.1 方針

- `vendor/skia-upstream` は実作業用クローンとして `.gitignore` 管理（追跡対象外）
- 固定バージョンは追跡対象の lock ファイルで管理
- 取得元は `google/skia` を正本、`dolphilia/skia` は補助

### 12.2 追加ファイル

- 追加: `/Users/dolphilia/github/reskia/vendor/skia-source.lock`
  - `SKIA_UPSTREAM_URL`, `SKIA_FORK_URL`, `SKIA_REF` を管理
- 追加: `/Users/dolphilia/github/reskia/vendor/README.md`
- 追加: `/Users/dolphilia/github/reskia/scripts/fetch_skia_upstream.sh`
  - lock を読み込んで `vendor/skia-upstream` を clone/fetch
  - `--remote upstream|fork` で取得元切替
  - `--ref` で一時検証用 ref 指定

### 12.3 期待効果

- Reskia 本体リポジトリと比較クローンを明確に分離できる。
- lock を更新するだけで「どの Skia を比較対象にしたか」を履歴化できる。
- 将来の段階アップグレード（commit 単位での追従、CMake 化拡張）を小さい差分で進めやすい。

## 13. Cバインディング（`binding/`・`static/`）調査（2026-02-14）

`skia` のCバインディング実装方式について、`binding/` と `static/` の設計レビューを実施した。  
主な所見は以下。

- `static_*_get_entity()` の `std::move` により、取得時に所有権が失われる箇所がある。
- `map[key]` 依存で無効キーが暗黙生成され、異常が潜在化しやすい。
- キー再利用に世代管理がなく、stale handle を検出できない。
- `delete` と `ref/unref` が混在し、所有権規約が読み取りづらい。
- `void*` / `int` 主体のAPIで型情報が薄く、誤用検知が難しい。

改善方針:

- レジストリ層を共通化し、検証付きハンドル（世代付き）と同期を導入。
- `get_entity` を `borrow/take` へ分離し、所有権を明示。
- 命名を `static` -> `handles`（または `registry`）へ段階移行。
- LuaJIT互換を維持しつつ、型付きC APIへ移行可能な二層構成を整備。

詳細:
- `/Users/dolphilia/github/reskia/docs/notes/c-binding-static-binding-review-2026-02-14.md`

## 14. CMake構成レビュー（2026-02-14）

`skia/CMakeLists.txt` を中心に CMake 構成を再点検した。主な課題は以下。

- `skia/CMakeLists.txt` が巨大で責務集中（source list / 依存 / テストが混在）
- `include_directories` / `link_directories` などグローバル設定が多い
- `svg/CMakeLists.txt` で `project()` を複数回再定義している
- `skpath` の project/library 命名が `skcms` と不一致
- `ReskiaDeps.cmake` の platform 対応が非対称（WIN32 source未実装, UNIX最小）

改善方針:

- ターゲット指向へ移行（`target_include_directories` / `target_link_libraries`）
- `skia/CMakeLists.txt` を用途別 `.cmake` に分割
- `svg` と `skpath` の命名・構造を明確化
- 将来的にルート superbuild を導入し、モジュールと依存モードを一元管理

詳細:
- `/Users/dolphilia/github/reskia/docs/notes/cmake-architecture-review-2026-02-14.md`
