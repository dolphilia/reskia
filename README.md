# Reskia

Reskia は、Google Skia を CMake ベースで再構成し、C API を提供するリポジトリです。

主目的:

- Skia を CMake で段階的にビルドできる構成へ整理する
- C API（`skia/capi` と `skia/handles`）を通じて他言語連携しやすくする

## 現在の基準（2026-02-18）

- ベースSkiaロック: `vendor/skia-source.lock`
- fixed ref: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- upstream 参照作業ツリー: `vendor/skia-upstream`（`.gitignore` で追跡対象外）

upstream 同期:

```bash
scripts/fetch_skia_upstream.sh
```

fork 参照:

```bash
scripts/fetch_skia_upstream.sh --remote fork
```

## ディレクトリ構成

- `skia/`: メイン共有ライブラリ `reskia` のビルド入口
- `skia/capi/`: ポインタ境界の C API
- `skia/handles/`: 整数ハンドル境界の C API
- `skia/modules/skcms/`: `skcms` 静的ライブラリ
- `skia/modules/skresources/`: `skresources` 静的ライブラリ
- `skia/modules/svg/`: `svg`, `skshaper`, `skunicode` 静的ライブラリ
- `skia/modules/skpath/`: `skpath_skcms`（`skcms` 互換エイリアス）
- `cmake/deps/ReskiaDeps.cmake`: 依存解決モードと機能フラグ
- `third_party/`: 依存サブモジュール（`src`）と生成物（`build`, `install`）
- `docs/`: `guides`（運用ガイド）, `notes`（検証メモ）, `plans`（実装計画）

注記:

- ルート直下には `CMakeLists.txt` がありません。`skia/CMakeLists.txt` を入口として利用します。

## ビルド要件

- CMake `>= 3.26.4`
- C++17
- 現行の検証環境: macOS + AppleClang

## 依存解決モード

`skia/CMakeLists.txt` は `RESKIA_DEPS_MODE` で依存解決を切り替えます。

- `prebuilt`（既定）
  - `third_party/install` を優先参照して依存ライブラリを解決
- `source`
  - `third_party/install` 前提で解決
  - APPLE では `skcms/skresources/svg` を `add_subdirectory` で連携
  - WIN32 は現状未実装（`FATAL_ERROR`）
- `system`
  - `find_package` / `find_library` によるシステム解決

関連スクリプト:

- サブモジュール初期化: `scripts/bootstrap_third_party.sh`
- 依存ビルド: `scripts/build_third_party.sh`

## ビルド手順（基本）

以下はリポジトリルートで実行します。

### Debug / prebuilt

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

### Debug / source

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source-local -DCMAKE_BUILD_TYPE=Debug -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source-local -j 8
```

### テストを有効にする場合

```bash
cmake -S skia -B skia/cmake-build-tests-local -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests-local -j 8
ctest --test-dir skia/cmake-build-tests-local --output-on-failure
```

注記:

- 既定は `RESKIA_BUILD_TESTS=OFF`。
- `reskia` 本体は `SK_ENABLE_OPTIMIZE_SIZE` を有効化してビルドします。

## 代表的な機能フラグ

`cmake/deps/ReskiaDeps.cmake` で以下の機能を切り替えできます（既定 OFF）。

- codec/format: `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_GIF`, `RESKIA_ENABLE_PDF`, `RESKIA_ENABLE_JPEG_GAINMAP`
- encoder: `RESKIA_ENABLE_JPEG_ENCODER`, `RESKIA_ENABLE_WEBP_ENCODER`
- text/layout: `RESKIA_ENABLE_SKSG`, `RESKIA_ENABLE_SKOTTIE`, `RESKIA_ENABLE_SKPARAGRAPH`, `RESKIA_ENABLE_FONTCONFIG_CAPI`
- GPU: `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN`

主な制約:

- `RESKIA_ENABLE_SKOTTIE=ON`: 現在 APPLE 前提
- `RESKIA_ENABLE_SKPARAGRAPH=ON`: 現在 APPLE + `RESKIA_DEPS_MODE=source` + HarfBuzz 必須
- `RESKIA_ENABLE_GPU_METAL=ON`: APPLE 限定
- `RESKIA_ENABLE_GPU_DAWN=ON`: `RESKIA_ENABLE_GPU_GRAPHITE=ON` 必須

## `svg/skshaper/skunicode` の縮退動作

依存検出により実装を段階的に有効化します。依存不足時は最小実装へ縮退します。

- `hb.h` 不在: HarfBuzz shaping 無効
- `unicode/ubidi.h` 不在: ICU Unicode 処理と `SkShaper_skunicode` 無効
- `ICU4XDataProvider.hpp` 不在: ICU4X 無効
- `grapheme.h` 不在: libgrapheme 無効
- 非Apple環境: CoreText 実装無効

## 2026-02-18 のビルド確認

以下を確認済みです。

- `cmake -S skia -B skia/cmake-build-codex-docrefresh-prebuilt -DCMAKE_BUILD_TYPE=Debug` 成功
- `cmake --build skia/cmake-build-codex-docrefresh-prebuilt -j 8` 成功（`Built target reskia`）
- `cmake -S skia -B skia/cmake-build-codex-docrefresh-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Debug` 成功
- `cmake --build skia/cmake-build-codex-docrefresh-source -j 8` 成功（`Built target reskia`）

## 主要ドキュメント

- 構造ガイド: `docs/guides/repository-structure.md`
- CMake移行ガイド: `docs/guides/cmake-migration-guide.md`
- `skia` ビルド検証: `docs/notes/skia-cmakelists-build-report-2026-02-13.md`
- 依存管理レポート: `docs/notes/dependency-management-report-2026-02-14.md`
- C binding 設計レビュー: `docs/notes/c-binding-static-binding-review-2026-02-14.md`
- CMake 構成レビュー: `docs/notes/cmake-architecture-review-2026-02-14.md`
