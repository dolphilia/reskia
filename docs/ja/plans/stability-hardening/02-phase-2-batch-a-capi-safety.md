# 02 Phase 2 Batch A: image / surface / canvas C API safety

作業開始日時: 2026-05-08 12:22:39 JST

## 目的

`docs/ja/plans/stability-hardening/00-plan.md` の Phase 2 に従い、利用頻度が高い `SkImage` / `SkSurface` / `SkCanvas` 周辺から C ABI の安全性を上げる。

Batch A の対象:

- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/capi/sk_surface.h`
- `skia/capi/sk_surface.cpp`
- `skia/capi/sk_canvas.h`
- `skia/capi/sk_canvas.cpp`

## 今回の実施範囲

今回完了したもの:

- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/capi/sk_surface.h`
- `skia/capi/sk_surface.cpp`

着手済み・継続中:

- `skia/capi/sk_canvas.h`
- `skia/capi/sk_canvas.cpp`

`SkCanvas` は API 数が多く、`void*` 引数がまだ広く残っている。単純な NULL ガードだけで `done` にすると型安全性レビューが浅くなるため、query / read / state / draw / static factory に分類し、typed pointer 化と NULL 規約を小さく進める。

## `SkImage` C API

### 確認結果

`sk_image.h` は既に次の整理が進んでいた。

- `reskia_image_t` opaque pointer を主入力に使う。
- 戻り値の多くは `sk_*_t` typed handle。
- `SkImage_release` / `SkImage_ref` / `SkImage_unref` は所有権操作としてコメント済み。
- `SkImage_colorSpace` は borrowed pointer としてコメント済み。
- async read 系は `reskia_async_read_pixels_callback_t` と borrowed result wrapper を使う。

一方、`sk_image.cpp` は多くの関数で `image` や out/input pointer をそのまま dereference しており、NULL 入力時に crash する余地があった。

### 実装変更

`sk_image.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| `bool` | `false` |
| pointer | `nullptr` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |

対象例:

- basic getter: `SkImage_width`, `SkImage_height`, `SkImage_uniqueID`
- handle-return getter: `SkImage_imageInfo`, `SkImage_dimensions`, `SkImage_bounds`
- borrowed pointer: `SkImage_colorSpace`
- pixel read: `SkImage_readPixels*`
- shader/image factory: `SkImage_makeShader*`, `SkImage_makeSubset*`, `SkImage_makeColorSpace*`
- ownership: `SkImage_release`, `SkImage_ref`, `SkImage_unref`

async read 系は既存実装で invalid input を callback に `result == nullptr` として通知していたため、その方針を維持した。

## `SkSurface` C API

### 確認結果

`sk_surface.h` は既に次の整理が進んでいた。

- `reskia_surface_t` opaque pointer を主入力に使う。
- `SkSurface_getCanvas`, `SkSurface_props`, `SkSurface_recordingContext`, `SkSurface_recorder` は borrowed pointer としてコメント済み。
- `SkSurface_release` / `SkSurface_ref` / `SkSurface_unref` は所有権操作としてコメント済み。
- async read 系は `SkImage` と同じ callback/result 規約。

一方、`sk_surface.cpp` は `surface`、`imageInfo`、`pixmap`、`characterization` などを直接 dereference していた。

### 実装変更

`sk_surface.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| `bool` | `false` |
| pointer | `nullptr` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |

対象例:

- basic getter: `SkSurface_width`, `SkSurface_height`, `SkSurface_generationID`
- handle-return getter/factory: `SkSurface_imageInfo`, `SkSurface_makeSurface*`, `SkSurface_makeImageSnapshot*`
- borrowed parent pointer: `SkSurface_getCanvas`, `SkSurface_props`, `SkSurface_recordingContext`, `SkSurface_recorder`
- pixel read/write: `SkSurface_readPixels*`, `SkSurface_writePixels*`, `SkSurface_peekPixels`
- GPU/sync related: `SkSurface_replaceBackendTexture`, `SkSurface_wait`, `SkSurface_characterize`
- ownership: `SkSurface_release`, `SkSurface_ref`, `SkSurface_unref`

async read 系は既存実装で invalid input を callback に `result == nullptr` として通知していたため、その方針を維持した。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/capi/sk_surface.h`
- `skia/capi/sk_surface.cpp`

Batch A 初回では未完了維持:

- `skia/capi/sk_canvas.h`
- `skia/capi/sk_canvas.cpp`

その後 `SkCanvas` の部分対応を開始したため、`sk_canvas.h` / `sk_canvas.cpp` は `doing` に変更した。

## `SkCanvas` C API

### 分類

| 分類 | 対象の例 | 方針 |
| --- | --- | --- |
| query | `getBaseLayerSize`, `getDeviceClipBounds*`, `getLocalClipBounds*`, `getProps`, `getSaveCount`, `getSurface`, `imageInfo`, `isClipEmpty`, `isClipRect`, `recorder`, `recordingContext` | `canvas == NULL` は fail-safe 値を返す。out param は非 NULL 必須に寄せる。borrowed pointer はコメントで明示する。 |
| read | `accessTopLayerPixels`, `accessTopRasterHandle`, `peekPixels`, `readPixels*` | `canvas` と必須入力が NULL の場合は `NULL` / `false`。borrowed pixels は所有権を渡さない。 |
| state | `save*`, `restore*`, `concat*`, `clip*`, `translate`, `scale`, `rotate`, `skew`, `resetMatrix`, `discard` | 次バッチで `canvas == NULL` の no-op 化と、図形・行列 pointer の typed 化を進める。 |
| draw | `draw*`, `clear*`, `experimental_DrawEdgeAA*`, `private_draw_shadow_rec` | `paint` を NULL 許容にするか必須にするかを関数ごとに決めてから typed pointer 化する。 |
| static factory | `SkCanvas_new*`, `SkCanvas_MakeRasterDirect*` | 必須 pointer が NULL の場合は `NULL` / `0`。`props` など Skia が NULL を受ける optional pointer は NULL 許容を維持する。 |

### 実装変更

今回の小さい差分では、query / read / static factory の一部を typed pointer と NULL 規約へ寄せた。

typed pointer 化:

- `SkCanvas_newWithSizeProps`: `const reskia_surface_props_t *`
- `SkCanvas_newFromBitmap*`: `reskia_bitmap_t *` / `const reskia_bitmap_t *`
- `SkCanvas_accessTopLayerPixels`: `reskia_image_info_t *`, `reskia_i_point_t *`
- `SkCanvas_getDeviceClipBoundsInto`: `reskia_i_rect_t *`
- `SkCanvas_getLocalClipBoundsInto`: `reskia_rect_t *`
- `SkCanvas_getProps`: `reskia_surface_props_t *`
- `SkCanvas_getSurface`: `reskia_surface_t *` borrowed
- `SkCanvas_makeSurface`: `const reskia_image_info_t *`, `const reskia_surface_props_t *`
- `SkCanvas_peekPixels`: `reskia_pixmap_t *`
- `SkCanvas_readPixels*`: `reskia_bitmap_t`, `reskia_image_info_t`, `reskia_pixmap_t`
- `SkCanvas_writePixels*`: `reskia_bitmap_t`, `reskia_image_info_t`
- `SkCanvas_recorder` / `SkCanvas_recordingContext`: typed borrowed pointer
- `SkCanvas_MakeRasterDirect`: `const reskia_image_info_t *`, `const reskia_surface_props_t *`

NULL 規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `bool` | `false` |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| clip empty query | `true` |

`props` は Skia 側が optional pointer として扱える箇所では NULL 許容を維持した。`info` / `bitmap` / `pixmap` / `pixels` など dereference が必要な入力は非 NULL 必須にした。

### 追加実装変更: state / draw

2026-05-08 の継続作業で、state mutation 系と draw 系にも NULL 規約を広げた。

state mutation:

- `clearColor`, `discard`, `resetMatrix`, `restore*`, `rotate*`, `scale`, `skew`, `translate` は `canvas == NULL` で no-op。
- `save*` は `canvas == NULL` で `0`。
- `clip*`, `concat*`, `setMatrix*` は参照渡しになる入力 pointer を非 NULL 必須にし、NULL なら no-op。
- `saveLayerWithBoundsPaintPtr`, `saveLayerAlpha`, `saveLayerAlphaf` は Skia 側が `bounds == NULL` を扱えるため NULL 許容を維持。
- `saveLayerWithBoundsPaintRef` は `SkRect&` 経由のため `bounds` を非 NULL 必須にした。

draw:

- `SkPaint&`, `SkPath&`, `SkRect&`, `SkRRect&`, `SkIRect&`, `SkRegion&` のように dereference が必要な入力は非 NULL 必須。NULL なら no-op。
- `SkImage*`, `SkDrawable*`, `SkPicture*`, `SkTextBlob*`, `SkVertices*` は描画対象として非 NULL 必須。NULL なら no-op。
- `SkCanvas` が pointer として受ける optional `paint` / `matrix` / `cullRect` は NULL 許容を維持。
- handle 入力の `sk_image_t`, `sk_picture_t`, `sk_text_blob_t`, `sk_vertices_t`, `sk_blender_t`, `sk_point_t`, `sk_rect_t` は `0` を invalid とし、必要な箇所では no-op。

typed pointer 化を追加した主な関数:

- state: `clipIRect`, `clipPath*`, `clipRect*`, `clipRegion`, `clipRRect*`, `concat*`, `setMatrix*`
- draw: `drawAnnotation*`, `drawArc`, `drawAtlas`, `drawCircle*`, `drawColor`, `drawDrawable*`, `drawDRRect`, `drawGlyphs*`, `drawImage*`, `drawImageLattice*`, `drawImageNine`, `drawImageRect*`, `drawIRect`, `drawLine*`, `drawMesh`, `drawOval`, `drawPaint`, `drawPatch`, `drawPath`, `drawPicture*`, `drawPoint*`, `drawPoints`, `drawRect`, `drawRegion`, `drawRoundRect`, `drawRRect`, `drawSimpleText`, `drawString*`, `drawTextBlob*`, `drawVertices*`, `experimental_DrawEdgeAA*`, `private_draw_shadow_rec`, `quickReject*`

最終的に `void*` を維持している範囲:

- `SkCanvas_accessTopLayerPixels` / `SkCanvas_accessTopRasterHandle`: raw borrowed pointer を返す API。
- `SkCanvas_drawSimpleText`: raw text buffer を受ける API。
- `SkCanvas_readPixelsWithImageInfo` / `SkCanvas_writePixelsWithImageInfo` / `SkCanvas_MakeRasterDirect*`: caller-owned pixel buffer を受ける API。

`SkCanvas::SaveLayerRec` は `reskia_canvas_save_layer_rec_t` opaque pointer として typed pointer 化した。`SkGlyphID` 配列は upstream が `uint16_t` typedef として定義しているため、C ABI では `const uint16_t *` として公開する。

## 残課題

### `SkCanvas`

`SkCanvas` の typed pointer 化と NULL 規約整理は Batch A として完了扱いにする。

完了条件:

- query / read / state / draw / static factory の主要 API が typed pointer または意図的な raw buffer に分類済み。
- `canvas == NULL` は no-op / `false` / `0` / `NULL` の fail-safe に統一済み。
- dereference が必要な入力 pointer は非 NULL 必須として、NULL 入力時に no-op / `false` / `0` を返す。
- Skia が optional pointer として扱える入力は NULL 許容を維持。

継続方針:

1. raw buffer API は wrapper 化せず、buffer lifetime / mutability のコメントを必要に応じて補強する。
2. Phase 2 の次バッチとして `SkBitmap` / `SkPath` / `SkPaint` を進める。

### smoke test

今回の変更は既存 API の NULL 入力挙動を crash から fail-safe に寄せたもの。invalid input smoke を追加し、`ctest` に登録した。

追加 target:

- `test_canvas_invalid_input_smoke` / `c_skia_canvas_invalid_input_smoke`
- `test_image_surface_invalid_input_smoke` / `c_skia_image_surface_invalid_input_smoke`

追加済み:

- `SkImage_width(nullptr) == 0`
- `SkImage_height(nullptr) == 0`
- `SkImage_peekPixels(nullptr, nullptr) == false`
- `SkImage_colorSpace(nullptr) == nullptr`
- `SkImage_refEncodedData(nullptr) == 0`
- `SkImage_ref(nullptr)` / `SkImage_unref(nullptr)` / `SkImage_release(nullptr)` が no-op
- `SkSurface_width(nullptr) == 0`
- `SkSurface_height(nullptr) == 0`
- `SkSurface_getCanvas(nullptr) == nullptr`
- `SkSurface_makeImageSnapshot(nullptr) == 0`
- `SkSurface_peekPixels(nullptr, nullptr) == false`
- `SkSurface_notifyContentWillChange(nullptr, ...)` / `SkSurface_writePixels*(nullptr, ...)` / `SkSurface_ref(nullptr)` / `SkSurface_unref(nullptr)` / `SkSurface_release(nullptr)` が no-op
- `SkCanvas_getSaveCount(nullptr) == 0`
- `SkCanvas_readPixels(nullptr, nullptr, 0, 0) == false`
- `SkCanvas_translate(nullptr, 1, 1)` が no-op
- `SkCanvas_drawPath(nullptr, nullptr, nullptr)` が no-op
- 配列 pointer 系 draw API の `count > 0` / pointer NULL no-op

今後追加候補:

- stale handle smoke
- raw buffer API の lifetime / mutability コメント確認

### test target link fix

`RESKIA_BUILD_TESTS=ON` で `src/utils/SkTestCanvas.cpp` を有効化すると、text GPU の slug / strike helper 実装が未登録のため `SkStrikeClient` / `SkStrikeServer` / `sktext::gpu::Slug` 系で link error になっていた。`RESKIA_BUILD_TESTS` 時だけ次の source を追加し、既存 smoke target の link 前提を修正した。

- `src/text/gpu/DistanceFieldAdjustTable.cpp`
- `src/text/gpu/GlyphVector.cpp`
- `src/text/gpu/SDFTControl.cpp`
- `src/text/gpu/SkChromeRemoteGlyphCache.cpp`
- `src/text/gpu/Slug.cpp`
- `src/text/gpu/SlugImpl.cpp`
- `src/text/gpu/StrikeCache.cpp`
- `src/text/gpu/SubRunAllocator.cpp`
- `src/text/gpu/SubRunContainer.cpp`
- `src/text/gpu/TextBlob.cpp`
- `src/text/gpu/VertexFiller.cpp`
