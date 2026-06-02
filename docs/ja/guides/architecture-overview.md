# Reskia アーキテクチャ概要

この文書は、Reskia が何を実現し、どのような境界で構成されているかを説明します。ディレクトリ単位の詳細は `docs/ja/guides/repository-structure.md` を参照してください。

## 目的

Reskia は、Skia を CMake で扱える形に整理し、C ABI を通じて他言語から利用しやすくするプロジェクトです。

中心となる考え方:

1. Skia source を `skia/` に集約し、`reskia` 共有ライブラリとしてビルドする。
2. Skia C++ API を `skia/capi` と `skia/handles` から C ABI に橋渡しする。
3. 依存解決と optional feature を CMake flag で制御する。
4. upstream Skia には固定 commit 単位で段階的に追従する。

## 主要な境界

| 境界 | 役割 |
| --- | --- |
| CMake boundary | `skia/CMakeLists.txt` と `cmake/` が source、依存、feature flag、tests を束ねる。 |
| C ABI boundary | `skia/capi` が pointer-oriented API、`skia/handles` が integer-handle API を公開する。 |
| Dependency boundary | `third_party` と `RESKIA_DEPS_MODE` が依存の取り込み方を分ける。 |
| Upstream boundary | `vendor/skia-source.lock` と `vendor/skia-upstream` が基準 commit と比較対象を分ける。 |
| Documentation boundary | `docs/ja/guides` は継続的なガイド、`notes` と `plans` は調査・計画・履歴を扱う。 |

## ビルドの流れ

基本のビルド入口は `skia/CMakeLists.txt` です。

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

configure 時に `RESKIA_DEPS_MODE` と `RESKIA_ENABLE_*` flag を決めます。

- `RESKIA_DEPS_MODE=prebuilt`: 事前配置依存を使う既定 mode。
- `RESKIA_DEPS_MODE=source`: `third_party/install` の依存を使う。
- `RESKIA_DEPS_MODE=system`: system dependency を使う。

詳細は `docs/ja/guides/cmake-migration-guide.md` にあります。

## C API の流れ

Reskia の C API は、Skia C++ object を C ABI で扱える形に変換します。

```text
caller
  -> skia/capi/*.h
  -> skia/capi/*.cpp
  -> Skia C++ API
```

handle API を使う場合は、C API と Skia object の間に handle table が入ります。

```text
caller
  -> skia/handles/static_*.h
  -> HandleTable
  -> Skia C++ object
```

pointer API は直接性が高く、handle API は他言語 binding で raw pointer を避けたい場合に向いています。

## 依存と feature flag

Reskia は Skia の全機能を常に有効にするのではなく、依存や platform に応じて段階的に有効化します。

例:

- PDF、codec、encoder は関連 dependency と CMake flag に依存する。
- GPU backend は platform と backend ごとの前提に依存する。
- text stack は HarfBuzz、ICU、ICU4X、libgrapheme、CoreText の有無で縮退する。

依存が不足する場合は、可能な範囲で最小実装に縮退します。縮退できない機能は configure error または未登録の test として扱います。

## Upstream 追従

Skia 追従では、`vendor/skia-source.lock` の fixed commit を現在の baseline とします。

基本ルール:

- candidate は commit hash で固定する。
- probe が通るまで lock を更新しない。
- public API coverage と stale C API report を確認する。
- source sync、C API 追従、build / smoke を通してから cycle を閉じる。

詳細は `docs/ja/guides/skia-upgrade-workflow.md` にあります。

## Contributor が最初に読む文書

- `docs/ja/README.md`: 全体の入口。
- `docs/ja/guides/repository-structure.md`: ディレクトリ構造。
- `docs/ja/guides/cmake-migration-guide.md`: CMake build。
- `docs/ja/guides/c-api-bindings-overview.md`: C API / handle API の概要。
- `docs/ja/guides/c-api-safety-guidelines.md`: C ABI safety rule。
- `docs/ja/guides/public-api-coverage-workflow.md`: coverage matrix の使い方。
