# Reskia リポジトリ構造

この文書は、Reskia の主要ディレクトリと、それぞれの責務を説明します。

## 全体像

Reskia は、Skia の C++ 実装を CMake でビルドし、C ABI を通じて他言語から利用できるようにするプロジェクトです。

主要な責務は次の3つです。

1. Skia 本体と周辺 modules を CMake でビルドする。
2. Skia の公開 API を `skia/capi` と `skia/handles` から C ABI として公開する。
3. upstream Skia の固定 commit に継続的に追従する。

## トップレベル

| パス | 役割 |
| --- | --- |
| `skia/` | `reskia` 共有ライブラリのビルド入口。Skia source、C API、handles、tests を含む。 |
| `cmake/` | 依存解決、source list、feature flag、test registration などの CMake 補助。 |
| `scripts/` | upstream 取得、依存ビルド、coverage 生成、補助チェックのスクリプト。 |
| `third_party/` | 依存ライブラリの source / build / install 管理。 |
| `vendor/` | Skia upstream 参照 checkout と lock file。 |
| `docs/` | 言語別ドキュメント。日本語は `docs/ja/`。 |

リポジトリルートには `CMakeLists.txt` を置きません。CMake の入口は `skia/CMakeLists.txt` です。

## `skia/`

`skia/` は Reskia の中心です。

| パス | 役割 |
| --- | --- |
| `skia/CMakeLists.txt` | CMake project `reskia` の入口。 |
| `skia/include/` | Skia public headers。 |
| `skia/src/` | Skia implementation source。 |
| `skia/capi/` | pointer-oriented C API。 |
| `skia/handles/` | integer-handle API と handle table。 |
| `skia/modules/` | `skcms`, `skresources`, `svg`, `skpath` などの module CMake integration。 |
| `skia/test/` | C API smoke / regression tests。 |
| `skia/lib/` | prebuilt mode で使う事前配置ライブラリ。 |

`reskia` target は、Skia 本体 source、必要な module source、`skia/capi/*.cpp`、`skia/handles/*.cpp` をまとめて共有ライブラリにします。

## C API 層

Reskia の C API は2層です。

### `skia/capi`

`skia/capi` は、C から Skia object を直接扱うための pointer-oriented API です。

特徴:

- `extern "C"` の関数を公開する。
- `reskia_*_t` の不透明 pointer 型を使う。
- 内部で `SkCanvas*` などの Skia C++ 型へ変換する。
- 所有権、NULL 入力、borrowed pointer、callback lifetime をヘッダコメントで明示する。

### `skia/handles`

`skia/handles` は、raw pointer を言語境界へ出したくない FFI 利用者向けの integer-handle API です。

特徴:

- `sk_image_t` のような整数 handle を公開する。
- 内部の `HandleTable` が object を保持する。
- stale handle や invalid handle を検出する。
- raw pointer を言語境界へ出したくない場合に使いやすい。

## C API 方針

C API は、Skia の公開クラスについて、公開メソッドと static factory / helper を可能な範囲で公開します。

新規 API や変更では、次を確認します。

- upstream Skia の公開 header に対応する API か。
- pointer API と handle API のどちらで公開するべきか。
- caller-owned / borrowed / retained / consumed のどれか。
- invalid input 時に crash せず規約どおり失敗するか。
- optional module や platform dependency が必要か。
- coverage matrix に状態を反映できるか。

詳細な安全性規約は `docs/ja/guides/c-api-safety-guidelines.md` にあります。

## CMake 構成

CMake の基本入口は `skia/CMakeLists.txt` です。補助的な定義は `cmake/` に分割されています。

主なファイル:

- `cmake/deps/ReskiaDeps.cmake`: `RESKIA_DEPS_MODE` と依存解決。
- `cmake/reskia/sources-*.cmake`: source list と feature-specific source registration。
- `cmake/reskia/tests.cmake`: test target registration。

依存解決 mode:

- `prebuilt`: 事前配置依存を使う既定 mode。
- `source`: `third_party/install` を使う再現性重視 mode。
- `system`: system dependency を使う mode。

詳細な手順は `docs/ja/guides/cmake-migration-guide.md` にあります。

## `third_party/`

`third_party/` は、依存ライブラリを分離して管理するための領域です。

| パス | 役割 |
| --- | --- |
| `third_party/src/` | 依存ライブラリの source checkout / submodule。 |
| `third_party/build/` | 依存ライブラリの build directory。 |
| `third_party/install/` | Reskia が参照する install prefix。 |

初期化とビルド:

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
```

## `vendor/`

`vendor/` は、Skia upstream の参照状態を管理します。

| パス | 役割 |
| --- | --- |
| `vendor/skia-source.lock` | Reskia が基準にする Skia commit。 |
| `vendor/skia-upstream/` | 比較・参照用の Skia checkout。Git 追跡対象外。 |
| `vendor/skia-upstream-candidate/` | upgrade probe 用 checkout。必要時に使う。 |

Skia の更新では、候補 commit を hash で固定し、probe と検証が通るまで `vendor/skia-source.lock` を更新しません。

## `docs/`

ドキュメントは言語別に配置します。

| パス | 役割 |
| --- | --- |
| `docs/ja/README.md` | 日本語ドキュメントの入口。 |
| `docs/ja/guides/` | 利用者・contributor 向けの継続的なガイド。 |
| `docs/ja/notes/` | 調査メモ、設計メモ、検証メモ。 |
| `docs/ja/plans/` | 実装計画、運用計画、履歴記録。 |

将来、翻訳版は `docs/en/`、`docs/de/` のように追加します。

## よく見るファイル

- `docs/ja/README.md`: 入口と基本ビルド。
- `docs/ja/guides/architecture-overview.md`: 全体アーキテクチャ。
- `docs/ja/guides/cmake-migration-guide.md`: CMake / dependency mode。
- `docs/ja/guides/c-api-bindings-overview.md`: C API / handle API overview。
- `docs/ja/guides/c-api-safety-guidelines.md`: C API safety rule。
- `docs/ja/guides/public-api-coverage-workflow.md`: public API coverage workflow。
- `docs/ja/guides/skia-upgrade-workflow.md`: Skia upgrade workflow。
- `docs/ja/guides/testing-and-stability.md`: build / smoke / stability 確認。
- `scripts/generate_public_api_coverage.py`: public API coverage matrix generator。
- `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`: coverage matrix。
- `docs/ja/plans/skia-incremental-upgrade/00-continuous-upgrade-cycle.md`: Skia upgrade cycle。
