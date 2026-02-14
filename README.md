# Reskia

Reskia は、Google Skia を CMake ベースで扱いやすく再構成し、C 言語ラッパーを提供するためのリポジトリです。  
主に以下を目的としています。

- Skia をモジュール単位の CMake プロジェクトとしてビルド可能にする
- C API（`skia/binding` と `skia/static`）を通じて他言語連携しやすくする

## ベースSkia

Reskia が基準としている Skia コミットは `vendor/skia-source.lock` で固定管理します。

- lock: `vendor/skia-source.lock`
- fixed ref: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`

比較・参照用の実クローンは以下に隔離配置します。

- working clone: `vendor/skia-upstream`（`.gitignore` で追跡対象外）

取得・同期:

```bash
scripts/fetch_skia_upstream.sh
```

デフォルトは `google/skia`（upstream）を取得元にし、必要時のみ fork を選択します。

```bash
scripts/fetch_skia_upstream.sh --remote fork
```

履歴比較・追従の基準:

- upstream: <https://github.com/google/skia>
- fork: <https://github.com/dolphilia/skia>

運用上は「upstream を正本、fork は補助（比較・一時回避）」とします。

## ディレクトリ構成

- `skia/`: メイン共有ライブラリ `reskia`（Skia本体 + Cラッパー）
- `skcms/`: `skcms` 静的ライブラリ
- `skpath/`: `skcms` 相当の補助プロジェクト（`../skcms/src` フォールバックあり）
- `skresources/`: `skresources` 静的ライブラリ
- `svg/`: `svg`, `skshaper`, `skunicode`
- `vendor/`: 比較・参照用Skia管理（lock は追跡、実クローンは追跡外）
- `docs/`: ドキュメントルート
  - `docs/notes/`: 調査結果・検証メモ
  - `docs/guides/`: ガイド文書
  - `docs/plans/`: 計画書

## ビルド要件

- CMake `>= 3.26.4`
- C++17
- macOS では AppleClang 環境を前提（現行検証環境）

## 依存管理モード（新規）

`skia/CMakeLists.txt` は `RESKIA_DEPS_MODE` で依存解決方法を切り替えできます。

- `prebuilt`（既定）:
  - 従来どおり `skia/lib` の事前ビルド済みライブラリを使用
- `source`:
  - `third_party/install` を参照して依存を解決
  - 依存が未インストールなら configure で失敗
- `system`:
  - システム環境（`find_package` / `find_library`）から依存を解決

補足:

- `source` モード用の初期ディレクトリ作成:
  - `scripts/bootstrap_third_party.sh`
- 依存ビルド自動化:
  - `scripts/build_third_party.sh`
- 依存解決ロジック:
  - `cmake/deps/ReskiaDeps.cmake`

## ビルド手順（例）

以下はリポジトリルートで実行します。

### skia（reskia）

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

補足:

- `reskia` は `SK_ENABLE_OPTIMIZE_SIZE` を付与してビルドする構成です。
- `test_c_skia` は既定 `OFF`（`RESKIA_BUILD_TESTS`）です。

### skia（reskia）Release ビルド例

```bash
cmake -S skia -B skia/cmake-build-release-local -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-release-local -j 8
```

### skia（reskia）`source` モード例

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source-local -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-source-local -j 8
```

注意:

- 上記を成功させるには、事前に `third_party/install` へ各依存ライブラリをインストールしておく必要があります。
- AVIF を有効にする場合:
  - 依存ビルド: `scripts/build_third_party.sh --with-avif`
  - Reskia 側: `-DRESKIA_ENABLE_AVIF=ON`
- ICU / ICU4X を導入する場合:
  - `scripts/build_third_party.sh --with-icu --with-icu4x`
  - `--with-icu4x` には Rust ツールチェーン（`cargo`）が必要です。
- `source` モードでは `skia/CMakeLists.txt` から `skcms`（および Apple では `skresources/svg`）を `add_subdirectory` 連携してビルドします。

### skia（reskia）`RESKIA_BUILD_TESTS=ON` 検証手順

```bash
cmake -S skia -B skia/cmake-build-tests-local -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests-local -j 8
ctest --test-dir skia/cmake-build-tests-local --output-on-failure
```

注意:

- 2026-02-14 時点では `test_c_skia` は API 不整合が残っており、`RESKIA_BUILD_TESTS=ON` では失敗する可能性があります。
- 現行の安定運用は `RESKIA_BUILD_TESTS=OFF`（既定値）で `reskia` 本体をビルドする方法です。

### skcms / skpath / skresources / svg

```bash
cmake -S skcms -B skcms/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skcms/cmake-build-local -j 8

cmake -S skpath -B skpath/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skpath/cmake-build-local -j 8

cmake -S skresources -B skresources/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skresources/cmake-build-local -j 8

cmake -S svg -B svg/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build svg/cmake-build-local -j 8
```

## 非`skia`プロジェクトの現状（2026-02-14時点）

- `skcms`: build 成功
- `skpath`: build 成功（`skcms` 変換ソースのフォールバック導入後）
- `skresources`: build 成功
- `svg`: `svg` / `skshaper` / `skunicode` すべて build 成功

## `svg` の依存検出と機能縮退

`svg/CMakeLists.txt` は依存ヘッダ検出ベースで `skshaper` / `skunicode` の実装を段階的に有効化します。  
依存が無い場合は最小構成（primitive/hardcoded）でビルドします。

- `hb.h` が無い: HarfBuzz shaping 無効
- `unicode/ubidi.h` が無い: ICU ベース Unicode 処理と `SkShaper_skunicode` 無効
- `ICU4XDataProvider.hpp` が無い: ICU4X 無効
- `grapheme.h` が無い: libgrapheme 無効
- Apple 以外: CoreText 実装無効

## ドキュメント

- 構造調査ガイド: `docs/guides/repository-structure.md`
- `skia/CMakeLists.txt` ビルド検証: `docs/notes/skia-cmakelists-build-report-2026-02-13.md`
- 依存管理方針の実施結果: `docs/notes/dependency-management-report-2026-02-14.md`
- `third_party` サブモジュール化と自動ビルド: `docs/notes/third-party-submodule-automation-2026-02-14.md`
- `vendor` 比較Skia管理の実装: `docs/notes/vendor-skia-management-2026-02-14.md`
