# 01 Phase 1: PDF 実装差分の棚卸し

更新日時: 2026-02-16 16:08:43 JST

## 実施内容

1. `vendor/skia-upstream/src/pdf` と現ツリー `skia/src/pdf` の差分をマニフェスト化。
2. `SkPDFDocument.cpp` と `src/pdf/*.cpp` の include を収集し、依存閉包を確認。
3. `RESKIA_DEPS_MODE`（prebuilt/source/system）ごとに、PDF 有効化時の追加依存要件を判定。

## 成果物（マニフェスト）

- `docs/plans/pdf-enablement/manifests/upstream-src-pdf-files.txt`
- `docs/plans/pdf-enablement/manifests/reskia-src-pdf-files.txt`
- `docs/plans/pdf-enablement/manifests/missing-src-pdf-files.txt`
- `docs/plans/pdf-enablement/manifests/skpdfdocument-direct-includes.txt`
- `docs/plans/pdf-enablement/manifests/pdf-cpp-include-closure.txt`
- `docs/plans/pdf-enablement/manifests/pdf-conditional-external-deps.txt`
- `docs/plans/pdf-enablement/manifests/phase1-selected-src-pdf-files.txt`

## 棚卸し結果

- 現在 `skia/src/pdf` は未配置（`reskia-src-pdf-files.txt` は空）。
- upstream 側の `src/pdf` 実ファイルは 51 件で、現ツリー不足は 51 件。
- `SkPDFDocument.cpp` 単体ではなく、`SkPDFDevice`/`SkPDFFont`/`SkPDFTypes` など多数ユニットへ依存するため、部分取り込みではなく `gn/pdf.gni` の `skia_pdf_sources` 相当を基準に同期するのが妥当。

## Phase 1 判定（取り込みポリシー）

1. PDF 有効化の初期取り込みセットは `phase1-selected-src-pdf-files.txt` を採用する。
- 除外: `src/pdf/BUILD.bazel`（ビルド設定ファイル）、`src/pdf/SkDocument_PDF_None.cpp`（PDF無効時の代替実装）、`src/pdf/SkJpegInfo_libjpegturbo.cpp`（初期段階では未採用）。

2. `SkJpegInfo` は初期段階で `src/pdf/SkJpegInfo_none.cpp` を採用する。
- 理由: PDF 有効化の最小化を優先し、`libjpeg` 系依存差異を Phase 2 で増やさない。
- 補足: 将来、高品質 JPEG 情報抽出が必要なら `SkJpegInfo_libjpegturbo.cpp` 切替を別途検討。

3. `SkPDFSubsetFont.cpp` は取り込むが、`SK_PDF_USE_HARFBUZZ_SUBSET` / `SK_PDF_USE_SFNTLY` は初期段階で有効化しない。
- `hb.h`/`hb-subset.h`/`font_subsetter.h` は `#if` 配下でのみ必要なため、マクロ未定義ならビルド可能。
- AGENTS.md の機能縮退方針（HarfBuzz/ICU 不在時に無効化）とも整合する。

## 依存判定（RESKIA_DEPS_MODE 別）

| モード | PDF 有効化時の追加要件 | 判定 |
|---|---|---|
| `prebuilt` | `zlib` リンクを明示追加（特に APPLE） | 必須 |
| `source` | `z`/`zlib` を `find_library` で解決しリンク追加 | 必須 |
| `system` | `find_package(ZLIB REQUIRED)` を PDF ON 時に追加 | 必須 |

補足:
- `src/pdf/SkDeflate.cpp` が `zlib.h` と deflate API を直接利用するため、PDF ON では `zlib` 連携が必須。
- `harfbuzz`/`sfntly`/`icu` は subsetter 機能を有効化する場合のみ必要（初期段階は任意）。

## Phase 2 への引き継ぎ

1. `phase1-selected-src-pdf-files.txt` を基準に `skia/src/pdf` を同期する。
2. `cmake/reskia/sources-core.cmake` に PDF ソース群を追加する。
3. `cmake/deps/ReskiaDeps.cmake` と `skia/CMakeLists.txt` に PDF ON 時の `zlib` リンク条件を追加する。
4. `cmake/reskia/sources-capi.cmake` で `capi/sk_pdf.cpp` を有効化する。
