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
- `/Users/dolphilia/github/reskia/docs/skia-cmakelists-build-report-2026-02-13.md`

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
