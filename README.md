# Reskia

Reskia は、Google Skia を CMake ベースで扱いやすく再構成し、C 言語ラッパーを提供するためのリポジトリです。  
主に以下を目的としています。

- Skia をモジュール単位の CMake プロジェクトとしてビルド可能にする
- C API（`skia/binding` と `skia/static`）を通じて他言語連携しやすくする

## ベースSkia

Reskia が基準としている upstream Skia のコミット:

- `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- URL: <https://github.com/dolphilia/skia/commit/0d49b661d75adbb8ac8cf88f7d527b1587be2c63>

比較・参照用の upstream クローンは以下に隔離配置されます。

- `vendor/skia-upstream`（`.gitignore` で追跡対象外）

## ディレクトリ構成

- `skia/`: メイン共有ライブラリ `reskia`（Skia本体 + Cラッパー）
- `skcms/`: `skcms` 静的ライブラリ
- `skpath/`: `skcms` 相当の補助プロジェクト（`../skcms/src` フォールバックあり）
- `skresources/`: `skresources` 静的ライブラリ
- `svg/`: `svg`, `skshaper`, `skunicode`
- `docs/`: 調査・ビルド検証メモ

## ビルド要件

- CMake `>= 3.26.4`
- C++17
- macOS では AppleClang 環境を前提（現行検証環境）

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

- 構造調査: `docs/repository-structure.md`
- `skia/CMakeLists.txt` ビルド検証: `docs/skia-cmakelists-build-report-2026-02-13.md`
