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
