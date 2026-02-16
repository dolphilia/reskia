# Phase 2 型分類表（Ownership API）

更新日: 2026-02-14
作成根拠: `skia/capi/*.h` の `*_delete` / `*_ref` / `*_unref` / 借用系API（`borrow` / `peek` / `getCanvas` / `props` / `pixels`）

## 分類ルール

| 分類 | 判定条件 | Phase 2 の規約 |
|---|---|---|
| RefCounted | 同一型に `*_ref` と `*_unref` がある | 公開解放は `release` 系へ統一（`*_delete` は互換ラッパ化） |
| NonRefCounted | `*_delete` はあるが `*_ref` / `*_unref` がない | `create/destroy` 維持 |
| Borrowed | 借用取得API（`borrow` / `peek` / `getCanvas` / `props` / `pixels`）のみで解放責務を移さない | `borrow_*` 命名とコメントで解放不要を明示 |

## 集計

| 分類 | 件数 | 備考 |
|---|---:|---|
| RefCounted | 28 | `delete` と `ref/unref` が併存 |
| NonRefCounted | 93 | `delete` 中心の所有 |
| Borrowed API | 17 | 返却値や out 引数は借用参照 |

## RefCounted 一覧（28）

`SkBBoxHierarchy`, `SkBlender`, `SkCapabilities`, `SkColorFilter`, `SkColorMatrixFilter`, `SkColorSpace`, `SkColorTable`, `SkContourMeasure`, `SkData`, `SkDataTable`, `SkDocument`, `SkDrawable`, `SkFlattenable`, `SkFontMgr`, `SkFontStyleSet`, `SkImage`, `SkImageFilter`, `SkMaskFilter`, `SkPathEffect`, `SkPicture`, `SkPixelRef`, `SkRuntimeEffect`, `SkShader`, `SkSurface`, `SkTextBlob`, `SkRefCnt`, `SkRefCntBase`, `SkVertices`

注記: `SkRefCnt`/`SkRefCntBase` は抽象基盤のため、実移行では派生公開型を優先する。

## NonRefCounted 一覧（93）

`SkAndroidCodec`, `SkAutoCanvasRestore`, `SkBitmap`, `SkCanvas`, `SkCodec`, `SkColor4f`, `SkColorFilters`, `SkColorInfo`, `SkColorMatrix`, `SkColorSpacePrimaries`, `SkContourMeasureIter`, `SkCornerPathEffect`, `SkCubicMap`, `SkCubicResampler`, `SkDashPathEffect`, `SkDiscretePathEffect`, `SkDynamicMemoryWStream`, `SkEncoder`, `SkExecutor`, `SkFILEStream`, `SkFILEWStream`, `SkFont`, `SkFontArguments`, `SkFontMetrics`, `SkFontStyle`, `SkGradientShader`, `SkGraphics`, `SkHighContrastConfig`, `SkHighContrastFilter`, `SkIPoint`, `SkIRect`, `SkISize`, `SkImageFilters`, `SkImageGenerator`, `SkImageInfo`, `SkLine2DPathEffect`, `SkLumaColorFilter`, `SkM44`, `SkMask`, `SkMaskBuilder`, `SkMatrix`, `SkMemoryStream`, `SkMesh`, `SkOpBuilder`, `SkOpenTypeSVGDecoder`, `SkOverdrawCanvas`, `SkOverdrawColorFilter`, `SkPaint`, `SkPath`, `SkPath1DPathEffect`, `SkPath2DPathEffect`, `SkPathBuilder`, `SkPathMeasure`, `SkPictureRecorder`, `SkPixmap`, `SkPoint`, `SkPoint3`, `SkRRect`, `SkRSXform`, `SkRasterHandleAllocator`, `SkReadBuffer`, `SkRect`, `SkRegion`, `SkRuntimeBlendBuilder`, `SkRuntimeColorFilterBuilder`, `SkRuntimeEffectBuilder`, `SkRuntimeShaderBuilder`, `SkSamplingOptions`, `SkShaderMaskFilter`, `SkSize`, `SkStream`, `SkStreamAsset`, `SkStreamMemory`, `SkStreamRewindable`, `SkStreamSeekable`, `SkString`, `SkStrokeRec`, `SkSurfaceProps`, `SkTableMaskFilter`, `SkTextBlobBuilder`, `SkTextBlobBuilderRunHandler`, `SkTraceMemoryDump`, `SkTrimPathEffect`, `SkTypeface`, `SkUnPreMultiply`, `SkV2`, `SkV3`, `SkV4`, `SkWStream`, `SkWriteBuffer`, `SkYUVAInfo`, `SkYUVAPixmapInfo`, `SkYUVAPixmaps`

## Borrowed API 一覧（17）

| API | 借用対象 | 根拠 |
|---|---|---|
| `SkExecutor_borrow` | `SkExecutor*` | API名に `borrow` を含む |
| `SkSurface_getCanvas` | `SkCanvas*` | Surface 所有の Canvas を返す |
| `SkSurface_props` | `const SkSurfaceProps*` | `const` 返却で借用 |
| `SkSurface_peekPixels` | `SkPixmap*` | `peek` は非所有参照 |
| `SkCanvas_peekPixels` | `SkPixmap*` | `peek` は非所有参照 |
| `SkImage_peekPixels` | `SkPixmap*` | `peek` は非所有参照 |
| `SkBitmap_peekPixels` | `SkPixmap*` | `peek` は非所有参照 |
| `SkPixelRef_pixels` | `void*` pixel buffer | 生ポインタ借用 |
| `SkStream_peek` | stream buffer | `peek` は読み取りのみ |
| `SkFILEStream_peek` | stream buffer | `peek` は読み取りのみ |
| `SkStreamAsset_peek` | stream buffer | `peek` は読み取りのみ |
| `SkMemoryStream_peek` | stream buffer | `peek` は読み取りのみ |
| `SkStreamMemory_peek` | stream buffer | `peek` は読み取りのみ |
| `SkStreamRewindable_peek` | stream buffer | `peek` は読み取りのみ |
| `SkStreamSeekable_peek` | stream buffer | `peek` は読み取りのみ |
| `SkReadBuffer_peekByte` | read cursor | 読み取りのみ |
| `SkCodec_Register` (commented) | codec factory callback | 所有権は caller 管理前提 |

## 実装メモ

- 本表は Step1 のベースラインであり、Step2 以降で API 名の `retain/release/borrow` へ移行する。
- 連番関数（`_2`, `_3`）の置換候補は Step3 で `note` 管理する。
