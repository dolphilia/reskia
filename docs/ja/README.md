# Reskia

Reskia は、Google Skia を CMake ベースで再構成し、C API を提供するリポジトリです。

主目的:

- Skia を CMake で段階的にビルドできる構成へ整理する
- C API（`skia/capi` と `skia/handles`）を通じて他言語連携しやすくする

## C API バインディング方針

Reskia の C API バインディングは、Skia の公開クラスについて、公開メソッドと static factory/helper を可能な限り C ABI に露出する方針で進めます。`skia/capi` はポインタ境界の直接的な C API、`skia/handles` は整数ハンドル境界の API を担います。

今後の C API 追加・レビュー・計画では、この方針を前提にします。実装対象の優先順位は、`vendor/skia-upstream` の公開ヘッダ、既存 `skia/capi` の coverage、optional module / platform dependency、所有権と ABI 安全性を見て決めます。進捗確認には `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` と `scripts/generate_public_api_coverage.py` を使用します。

## 現在の基準（2026-06-02）

- ベースSkiaロック: `vendor/skia-source.lock`
- fixed ref: `70f9d90bc8e6a56101d036153cfef28088e57f5b`
- baseline date: `2026-06-01`
- upstream 参照作業ツリー: `vendor/skia-upstream`（`.gitignore` で追跡対象外）
- C API coverage:
  - `covered`: 2954
  - `split_covered`: 42
  - `false_positive`: 297
  - `na`: 266
  - `no_public_methods_found`: 121
  - `missing` / `deferred` / `partial` / `overcovered`: 0

upstream 同期:

```bash
scripts/fetch_skia_upstream.sh
```

fork 参照:

```bash
scripts/fetch_skia_upstream.sh --remote fork
```

段階的アップグレード:

- 継続運用計画: `docs/ja/plans/skia-incremental-upgrade/`
- 現在の運用: `main` 上で lock 済み baseline から次の固定 Skia commit を選び、probe / routing / C API 追従 / verification / lock update を繰り返す。
- 直近完了サイクル: cycle 091（`70f9d90bc8e6a56101d036153cfef28088e57f5b`）
- 次サイクル: cycle 092 は、baseline 後の固定 local ref を再確認する。floating `main` は baseline として扱わない。

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
- `docs/ja/`: 日本語ドキュメントのルート
- `docs/ja/guides/`: 運用ガイド
- `docs/ja/notes/`: 検証メモ
- `docs/ja/plans/`: 実装計画

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

## 2026-06-02 の検証基準

cycle 091 完了後、main への統合後の binding audit と追加修正で以下を確認済みです。

- public API coverage generator 成功
- coverage matrix: `missing 0`, `deferred 0`, `partial 0`, `overcovered 0`
- prebuilt `reskia` build 成功
- source smoke build 成功
- targeted C API smoke tests 成功
- stale C API report は header のみ

過去の詳細なビルド確認は `docs/ja/notes/` と `docs/ja/plans/skia-incremental-upgrade/records/` に記録しています。

## 主要ドキュメント

- 構造ガイド: `docs/ja/guides/repository-structure.md`
- CMake移行ガイド: `docs/ja/guides/cmake-migration-guide.md`
- `skia` ビルド検証: `docs/ja/notes/skia-cmakelists-build-report-2026-02-13.md`
- 依存管理レポート: `docs/ja/notes/dependency-management-report-2026-02-14.md`
- C binding 設計レビュー: `docs/ja/notes/c-binding-static-binding-review-2026-02-14.md`
- C API / handle coverage 調査: `docs/ja/notes/bindings/capi-and-handle-binding-coverage-survey-2026-05-06.md`
- 公開 API coverage matrix: `docs/ja/notes/bindings/public-api-coverage-matrix-progress-2026-05-06.md`
- 公開 API binding 拡張計画: `docs/ja/plans/public-api-binding-expansion/`
- Skia 段階的アップグレード継続計画: `docs/ja/plans/skia-incremental-upgrade/`
- Skia 段階的アップグレード準備調査: `docs/ja/notes/skia-incremental-upgrade-readiness-2026-05-22.md`
- CMake 構成レビュー: `docs/ja/notes/cmake-architecture-review-2026-02-14.md`
