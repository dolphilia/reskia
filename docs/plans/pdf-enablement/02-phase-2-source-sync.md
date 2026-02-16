# 02 Phase 2: src/pdf 同期と CMake 組み込み

更新日時: 2026-02-16 16:13:32 JST

## 実施内容

1. Phase 1 で確定した `phase1-selected-src-pdf-files.txt` に基づき、`vendor/skia-upstream/src/pdf` から `skia/src/pdf` へ 48 ファイルを同期。
2. `cmake/reskia/sources-core.cmake` に PDF 実装 `.cpp` 群を `RESKIA_ENABLE_PDF` 条件で追加。
3. `cmake/reskia/sources-capi.cmake` に `capi/sk_pdf.cpp` を `RESKIA_ENABLE_PDF` 条件で追加。
4. `cmake/deps/ReskiaDeps.cmake` に `RESKIA_ENABLE_PDF` オプションを追加し、PDF ON 時の `zlib` 連携を mode/OS 別に追加。
5. `skia/CMakeLists.txt` で `RESKIA_ENABLE_PDF` かつ `src/pdf/SkPDFDocument.cpp` 登録時に `SK_SUPPORT_PDF` を定義。
6. `skia/capi/sk_pdf.cpp` に `../handles/static_sk_document-internal.h` を追加し、`static_sk_document_make()` 解決を修正。

## 同期ファイル

- 同期元: `vendor/skia-upstream/src/pdf/*`
- 同期先: `skia/src/pdf/*`
- 同期件数: 48（Phase 1 選定セット）

## ビルド検証

実行コマンド:
```bash
cmake -S skia -B skia/cmake-build-pdf-prebuilt \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_PDF=ON
cmake --build skia/cmake-build-pdf-prebuilt -j 8
```

結果:
- configure: 成功
- build: 成功（`[100%] Built target reskia`）

## 発生した問題と対応

1. `capi/sk_pdf.cpp` で `static_sk_document_make` 未宣言によりビルド失敗。
- 原因: `sk_pdf.h` 経由では C 公開ヘッダ (`static_sk_document.h`) しか参照せず、内部 API 宣言を持たない。
- 対応: `skia/capi/sk_pdf.cpp` に `../handles/static_sk_document-internal.h` を追加。

## Phase 3 への引き継ぎ

1. `reskia_ffi.h` への `sk_pdf.h` 公開要否を確定する。
2. `reskia_pdf_metadata_t` と `SkPDF::Metadata` の ABI 前提を確認し、必要なら変換レイヤを導入する。
