# Reskia

Reskia は、Google Skia を CMake でビルドできる形に再構成し、他言語から利用しやすい C API を提供するリポジトリです。

主な提供物:

- `skia/`: 共有ライブラリ `reskia` のビルド入口
- `skia/capi/`: ポインタ境界の C API
- `skia/handles/`: 整数ハンドル境界の C API
- `cmake/`: 依存解決、機能フラグ、ターゲット分割の補助 CMake
- `third_party/`: 依存ライブラリの source / build / install 管理
- `vendor/`: 参照用 Skia checkout と lock file

## 現在の基準

- Skia lock file: `vendor/skia-source.lock`
- Upstream 参照 checkout: `vendor/skia-upstream`
- C API coverage: `missing 0`, `deferred 0`, `partial 0`, `overcovered 0`
- ルート直下には `CMakeLists.txt` を置かず、`skia/CMakeLists.txt` を CMake の入口にします。

Skia の更新は、固定 commit を選び、coverage / build / smoke を確認してから lock を更新する段階的な運用です。floating な `main` を baseline として扱いません。

## ビルド要件

- CMake 3.26.4 以上
- C++17 対応コンパイラ
- macOS / AppleClang が主要な検証環境

一部機能は OS や依存ライブラリにより有効化条件があります。依存が不足する場合は、可能な範囲で最小実装へ縮退します。

## 基本ビルド

既定の依存解決モードは `prebuilt` です。

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

`source` モードでは、`third_party/install` に依存ライブラリを用意してから configure します。

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source-local -j 8
```

テストを有効にする場合:

```bash
cmake -S skia -B skia/cmake-build-tests-local \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests-local -j 8
ctest --test-dir skia/cmake-build-tests-local --output-on-failure
```

## 依存解決モード

`RESKIA_DEPS_MODE` で依存解決方法を選びます。

| mode | 用途 |
| --- | --- |
| `prebuilt` | 既定。事前に用意された依存を使って短時間で確認する。 |
| `source` | `third_party` 管理の依存を使い、再現性を高める。 |
| `system` | OS や package manager による依存解決を使う。 |

詳細は `docs/ja/guides/cmake-migration-guide.md` を参照してください。

## 主な機能フラグ

機能フラグは主に `cmake/deps/ReskiaDeps.cmake` で定義します。

- Codec / encoder: `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_GIF`, `RESKIA_ENABLE_PDF`, `RESKIA_ENABLE_JPEG_ENCODER`, `RESKIA_ENABLE_WEBP_ENCODER`
- Text / animation: `RESKIA_ENABLE_SKSG`, `RESKIA_ENABLE_SKOTTIE`, `RESKIA_ENABLE_SKPARAGRAPH`, `RESKIA_ENABLE_FONTCONFIG_CAPI`
- GPU: `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN`

代表的な制約:

- `RESKIA_ENABLE_GPU_METAL=ON` は Apple 環境が必要です。
- `RESKIA_ENABLE_GPU_DAWN=ON` は `RESKIA_ENABLE_GPU_GRAPHITE=ON` を必要とします。
- `RESKIA_ENABLE_SKPARAGRAPH=ON` は HarfBuzz などの text stack 依存が必要です。

## C API 方針

Reskia の C API は、Skia の公開クラスについて、公開メソッドと static factory / helper を可能な範囲で C ABI に露出する方針です。

2つの境界を使い分けます。

- `skia/capi`: C から直接扱う pointer-oriented API
- `skia/handles`: 他言語 binding で扱いやすい integer-handle API

C API を追加・変更する場合は、所有権、NULL 入力、invalid handle、borrowed lifetime、callback lifetime を明示します。詳細は `docs/ja/guides/c-api-safety-guidelines.md` を参照してください。

## Skia 追従

Skia upstream への追従は、`vendor/skia-source.lock` の fixed commit を基準に進めます。

基本方針:

- `vendor/skia-upstream` は参照用 checkout として扱う。
- 候補 commit は hash で固定する。
- probe が通るまで `vendor/skia-source.lock` を更新しない。
- coverage matrix と stale C API report を確認する。
- build / smoke の通過後に lock を更新する。

運用手順は `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md` にあります。

## 主要ドキュメント

- `docs/ja/guides/repository-structure.md`: リポジトリ構造
- `docs/ja/guides/cmake-migration-guide.md`: CMake と依存解決モード
- `docs/ja/guides/c-api-safety-guidelines.md`: C API 安全性規約
- `docs/ja/plans/documentation-i18n/00-translation-selection.md`: 英訳対象の選定メモ
