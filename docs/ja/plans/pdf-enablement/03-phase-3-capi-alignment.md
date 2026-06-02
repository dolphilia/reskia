# 03 Phase 3: C API 公開面と型整合

更新日時: 2026-02-16 20:21:58 JST

## 実施内容

1. `reskia_ffi.h` に `sk_pdf.h` を追加し、統合ヘッダ経由で PDF API を参照可能にした。
2. `sk_pdf.h` の `reskia_pdf_metadata_t` を opaque 前提から C 互換の明示 struct へ変更した。
3. `sk_pdf.cpp` で `reskia_pdf_metadata_t` -> `SkPDF::Metadata` の変換レイヤを追加し、`reinterpret_cast` 依存を除去した。
4. `SkPDF_MakeDocument` の `metadata == nullptr` を許容し、`SkPDF_MakeDocumentWithoutMetadata` と同等動作へ統一した。

## 変更ファイル

- `skia/capi/reskia_ffi.h`
- `skia/capi/sk_pdf.h`
- `skia/capi/sk_pdf.cpp`

## 型整合ポリシー

- 文字列: `const char *` を `SkString` フィールドへコピー。
- 日時: `reskia_pdf_date_time_t` を `SkPDF::DateTime` へ明示マッピング。
- enum 相当値（outline/compression/subsetter）: `switch` で対応する Skia enum へ変換。未知値は安全側の既定値へフォールバック。
- `raster_dpi`: 0 以下は不正値とみなし Skia 既定値を維持（0除算リスク回避）。

## 現時点の制約

- `SkPDF::Metadata` のうち、構造木 (`fStructureElementTreeRoot`) と executor (`fExecutor`) は C API では未公開。
- 必要になった時点で、別フェーズで専用ハンドル API を追加する。

## ビルド検証

実行コマンド:
```bash
cmake --build skia/cmake-build-pdf-prebuilt -j 8
```

結果:
- 成功（`[100%] Built target reskia`）

## Phase 4 への引き継ぎ

1. `prebuilt/source/system` で `RESKIA_ENABLE_PDF=ON` の configure/build 行列を実施する。
2. mode 別の `zlib` 解決可否とエラー表現を確認する。
