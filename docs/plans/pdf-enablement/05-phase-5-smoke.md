# 05 Phase 5: PDF C API 最小スモーク

更新日時: 2026-02-16 20:32:19 JST

## 実施内容

1. `skia/test/test_pdf_smoke.cpp` を追加。
2. `cmake/reskia/tests.cmake` に `test_pdf_smoke` を追加（`RESKIA_ENABLE_PDF=ON` 時のみ）。
3. スモーク内容:
- `SkPDF_MakeDocumentWithoutMetadata`
- `SkPDF_MakeDocument`（`reskia_pdf_metadata_t` 指定）
- `SkDocument_beginPage` -> `SkPDF_SetNodeId` -> `SkCanvas_drawColorU32` -> `SkDocument_endPage` -> `SkDocument_close`
- `SkDynamicMemoryWStream_detachAsData` でデータ取得
- 出力の非空チェックと `%PDF-` シグネチャ検証

## CMake 追補

- `test_pdf_smoke` と `test_codec_smoke` に `RESKIA_DEP_LINK_DIRS` / `RESKIA_DEP_LIBS` を明示リンク。
- 理由: `prebuilt` 環境で `test_pdf_smoke` リンク時に `png` など依存ライブラリが見つからないケースを回避するため。

## 実行コマンド

```bash
cmake -S skia -B skia/cmake-build-pdf-phase5 \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_PDF=ON \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-pdf-phase5 --target test_pdf_smoke -j 8
ctest --test-dir skia/cmake-build-pdf-phase5 -R c_skia_pdf_smoke --output-on-failure
```

## 実行結果

- `test_pdf_smoke` ビルド: 成功
- `c_skia_pdf_smoke`: 成功（`100% tests passed, 0 tests failed out of 1`）

## 生成/更新ファイル

- `skia/test/test_pdf_smoke.cpp`（新規）
- `cmake/reskia/tests.cmake`（更新）

## 判定

- Phase 5 完了。
