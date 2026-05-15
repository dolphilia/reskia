# Phase 6 Design Memos 2026-05-15

Phase 6 の残件は、小さな static utility から ownership や platform 条件を持つ API に移っている。このメモでは、実装前に必要な線引きと推奨順を整理する。

## 現在の前提

- 既定 build で小さく追加できる `SkParse`、`SkParsePath`、`SkTextUtils`、`SkShadowUtils`、`SkNoDrawCanvas`、`SkNWayCanvas`、`SkCanvasStateUtils` は実装済み。
- `public-api-coverage-matrix.csv` の現状は `covered=2267`、`missing=1033`、`partial=17`、`no_public_methods_found=104`。
- Phase 6 の default build utility 実装はほぼ一段落。残る実装候補は callback/global/subclass design batch と platform/feature guard batch に寄っている。

## Candidate Summary

| 対象 | missing | 推奨分類 | 方針 |
| --- | ---: | --- | --- |
| `SkCustomTypefaceBuilder` | 0 missing / 2 partial | split | path glyph、drawable glyph、stream deserialize は実装済み。overload 別 C 名のため generator は `setGlyph` を partial として残す。 |
| `SkAnimCodecPlayer` | 0 | covered | `SkCodec` ownership transfer を consume API として実装済み。 |
| `SkCamera.h` | 4 | split / low priority | deprecated。非 Android public methods は実装済み。残り 4 件は Android framework 条件付き methods で `na`。 |
| `SkOrderedFontMgr` | 0 | covered | minimal wrapper 実装済み。 |
| `SkPaintFilterCanvas` | 3 | design-wait | subclass/protected paint filtering hook が本体。単純 constructor だけでは実用価値が薄い。 |
| `SkEventTracer` | 3 | design-wait | global callback registration。Phase 5A callback foundation の延長でまとめる。 |
| Android headers | 18 | platform-guard | Android / hardware buffer availability と build guard を先に確定する。 |
| ports font managers | 18 | platform-guard | fontconfig / remotable font manager の依存と ownership を分ける。 |
| docs/PDF | 8 | feature-guard | `RESKIA_ENABLE_PDF` guard の既存 `sk_pdf` と重複確認後に扱う。 |

## SkCustomTypefaceBuilder

### Public Surface

- `SkCustomTypefaceBuilder()`
- `setGlyph(SkGlyphID, float, const SkPath&)`
- `setGlyph(SkGlyphID, float, sk_sp<SkDrawable>, const SkRect&)`
- `setMetrics(const SkFontMetrics&, float)`
- `setFontStyle(SkFontStyle)`
- `detach()`
- `MakeFromStream(std::unique_ptr<SkStreamAsset>, const SkFontArguments&)`

### C ABI Design

追加済み subset:

- `SkCustomTypefaceBuilder_new`
- `SkCustomTypefaceBuilder_delete`
- `SkCustomTypefaceBuilder_setGlyphPath`
- `SkCustomTypefaceBuilder_setGlyphDrawable`
- `SkCustomTypefaceBuilder_setMetrics`
- `SkCustomTypefaceBuilder_setFontStyle`
- `SkCustomTypefaceBuilder_detach`
- `SkCustomTypefaceBuilder_MakeFromStream`

所有権:

- builder は heap-owned value。`delete` で破棄する。
- `setGlyphPath` は caller-owned `SkPath` を借用し、Skia 側で path をコピーする。
- `setMetrics` は caller-owned `SkFontMetrics` を借用し、Skia 側で値をコピーする。
- `setFontStyle` は caller-owned `SkFontStyle` を借用し、Skia 側で値をコピーする。
- `detach` は caller-owned `sk_typeface_t` handle を返す。builder は detach 後も C++ object として存在するが、再利用 semantics は upstream に委ねるため、C API 利用側には detach 後に builder を破棄する運用を推奨する。
- `setGlyphDrawable` は `sk_drawable_t` から retained `sk_sp<SkDrawable>` を渡す。input drawable handle は消費しない。
- `MakeFromStream` は `sk_stream_asset_t` を消費する。成功時も失敗時も入力 stream handle は無効になる。

coverage 上の残件:

- `setGlyph` は C++ overload 2 件を `SkCustomTypefaceBuilder_setGlyphPath` と `SkCustomTypefaceBuilder_setGlyphDrawable` に分けているため、method-level heuristic では `partial` のまま残る。

## SkAnimCodecPlayer

### Public Surface

- constructor consumes `std::unique_ptr<SkCodec>`
- `getFrame()`
- `dimensions()`
- `duration()`
- `seek(uint32_t)`

### C ABI Design

実装済み API:

- `SkAnimCodecPlayer_new(sk_codec_t codec)` where codec handle is consumed.
- `SkAnimCodecPlayer_delete`
- `SkAnimCodecPlayer_getFrame` returns retained `sk_image_t`.
- `SkAnimCodecPlayer_dimensions` returns `sk_i_size_t`.
- `SkAnimCodecPlayer_duration`
- `SkAnimCodecPlayer_seek`

注意:

- constructor が `unique_ptr<SkCodec>` を消費するため、borrow ではなく take semantics を API 名またはコメントに明示する。
- static codec handle の `take_entity` を使う場合、失敗時に handle が失われないよう、事前に handle validity を確認する。
- smoke は animated codec fixture がなければ single-frame PNG で `duration == 0` / `getFrame != 0` を確認する。

## SkCamera / SkPatch3D / SkCamera3D / Sk3DView

### Public Surface

- `SkPatch3D`: constructor、`reset`、`transform`、`dotWith` overload、deprecated no-op rotate methods。
- `SkCamera3D`: constructor、`reset`、`update`、`patchToMatrix`、public vector fields。
- `Sk3DView`: constructor/destructor、matrix stack、translate/rotate、matrix extraction、canvas application、normal dot。
- Android framework build only: `setCameraLocation` / `getCameraLocationX/Y/Z`。

### C ABI Design

実装可能な subset:

- owned wrappers for `SkPatch3D`, `SkCamera3D`, `Sk3DView`
- `SkPatch3D_transform` using borrowed `SkM44`, optional caller-owned dst。
- `SkCamera3D_patchToMatrix` writes into caller-owned `SkMatrix`。
- `Sk3DView_getMatrix` writes into caller-owned `SkMatrix`。
- `Sk3DView_applyToCanvas` borrows canvas。

実装済み:

- `SkPatch3D_new` / `SkPatch3D_delete`
- `SkPatch3D_reset`
- `SkPatch3D_transform`
- `SkPatch3D_dotWith` / `SkPatch3D_dotWithV3`
- `SkPatch3D_rotate` / `SkPatch3D_rotateDegrees`
- `SkPatch3D_getU` / `SkPatch3D_getV` / `SkPatch3D_getOrigin`
- `SkPatch3D_setU` / `SkPatch3D_setV` / `SkPatch3D_setOrigin`
- `SkCamera3D_new` / `SkCamera3D_delete`
- `SkCamera3D_reset`
- `SkCamera3D_update`
- `SkCamera3D_patchToMatrix`
- `SkCamera3D_getLocation` / `SkCamera3D_getAxis` / `SkCamera3D_getZenith` / `SkCamera3D_getObserver`
- `SkCamera3D_setLocation` / `SkCamera3D_setAxis` / `SkCamera3D_setZenith` / `SkCamera3D_setObserver`
- `Sk3DView_new` / `Sk3DView_delete`
- `Sk3DView_save` / `Sk3DView_restore`
- `Sk3DView_translate`
- `Sk3DView_rotateX` / `Sk3DView_rotateY` / `Sk3DView_rotateZ`
- `Sk3DView_getMatrix`
- `Sk3DView_applyToCanvas`
- `Sk3DView_dotWithNormal`

注意:

- header 自体が deprecated で、Skia は `SkM44` を推奨している。coverage 改善目的以外の実用価値は限定的。
- `SkCamera3D` の public fields は method-level generator の対象外。必要なら explicit field getter/setter を追加できるが、coverage 上は不要。
- Android framework conditional methods は通常 build では member が存在しないため、既定 build C ABI では `na` として扱う。Android framework build をサポートする場合のみ guarded implementation を追加する。

## SkOrderedFontMgr

### C ABI Design

- owned `SkOrderedFontMgr` pointer と retained `sk_font_mgr_t` view の両方を用意済み。
- `append(sk_sp<SkFontMgr>)` は input font manager handleを borrow して retain。
- `SkOrderedFontMgr` は `SkFontMgr` 派生として返せるため、`asFontMgr` borrowed view か `detach/ref` style が必要。

実装済み:

- `SkOrderedFontMgr_new`
- `SkOrderedFontMgr_delete`
- `SkOrderedFontMgr_asFontMgr` borrowed
- `SkOrderedFontMgr_refAsFontMgr`
- `SkOrderedFontMgr_append`

## Design-Wait / Platform-Guard Items

### SkPaintFilterCanvas

constructor と proxy forwarding だけを C ABI にしても paint filtering の callback を設定できない。実装するなら subclass callback API として設計する。Phase 5A callback foundation の後続 batch にまとめる。

### SkEventTracer

global singleton registration であり、callback lifetime、leakTracer、replacement 時の release が問題になる。`SkGraphics_SetImageGeneratorFromEncodedDataFactory` と同じ callback/global registration policy に従って後続 batch にまとめる。

### Android / Ports

Android hardware buffer helpers と ports font manager は platform availability と CMake guard を先に確定する。既定 build に混ぜない。

## Recommended Order

1. `SkCustomTypefaceBuilder` path / drawable / stream subset。実装済み。
2. `SkOrderedFontMgr` minimal wrapper。実装済み。
3. `SkAnimCodecPlayer` codec-consuming wrapper。実装済み。
4. `SkCamera` non-Android deprecated subset。実装済み。
5. callback/global/subclass 系 (`SkEventTracer`, `SkPaintFilterCanvas`)。
6. Android / ports guarded APIs。
