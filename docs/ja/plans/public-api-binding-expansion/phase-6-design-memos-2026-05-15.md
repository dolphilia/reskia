# Phase 6 Design Memos 2026-05-15

Phase 6 の残件は、小さな static utility から ownership や platform 条件を持つ API に移っている。このメモでは、実装前に必要な線引きと推奨順を整理する。

## 現在の前提

- 既定 build で小さく追加できる `SkParse`、`SkParsePath`、`SkTextUtils`、`SkShadowUtils`、`SkNoDrawCanvas`、`SkNWayCanvas`、`SkCanvasStateUtils` は実装済み。
- `public-api-coverage-matrix.csv` の現状は `covered=2273`、`missing=1027`、`partial=17`、`no_public_methods_found=104`。
- Phase 6 の default build utility 実装はほぼ一段落。残る実装候補は platform/feature guard batch に寄っている。

## Candidate Summary

| 対象 | missing | 推奨分類 | 方針 |
| --- | ---: | --- | --- |
| `SkCustomTypefaceBuilder` | 0 missing / 2 partial | split | path glyph、drawable glyph、stream deserialize は実装済み。overload 別 C 名のため generator は `setGlyph` を partial として残す。 |
| `SkAnimCodecPlayer` | 0 | covered | `SkCodec` ownership transfer を consume API として実装済み。 |
| `SkCamera.h` | 4 | split / low priority | deprecated。非 Android public methods は実装済み。残り 4 件は Android framework 条件付き methods で `na`。 |
| `SkOrderedFontMgr` | 0 | covered | minimal wrapper 実装済み。 |
| `SkPaintFilterCanvas` | 0 | covered | C callback `onFilter` bridge と borrowed canvas view を実装済み。 |
| `SkEventTracer` | 0 | covered | concrete C callback bridge と global Set/Get wrapper を実装済み。 |
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

実装済み:

- `SkPaintFilterCanvas_new`
- `SkPaintFilterCanvas_delete`
- `SkPaintFilterCanvas_asCanvas`
- `SkPaintFilterCanvas_getBaseLayerSize`
- `SkPaintFilterCanvas_recordingContext`

設計:

- `SkPaintFilterCanvas_new` は wrapped canvas を借用し、`onFilter(SkPaint&)` を C callback に渡す concrete subclass を作る。
- callback は mutable borrowed `reskia_paint_t*` を受け取り、`false` で draw op を skip する。
- `SkPaintFilterCanvas_asCanvas` は borrowed `SkCanvas` view を返す。継承階層の pointer adjustment が必要なため、実装では `static_cast<SkCanvas*>` を使う。
- `release_proc` は filter canvas delete 時に一度だけ呼ぶ。

### SkEventTracer

実装済み:

- `SkEventTracer_new`
- `SkEventTracer_delete`
- `SkEventTracer_SetInstance`
- `SkEventTracer_GetInstance`
- `SkEventTracer_getCategoryGroupEnabled`
- `SkEventTracer_getCategoryGroupName`
- `SkEventTracer_addTraceEvent`
- `SkEventTracer_updateTraceEventDuration`
- `SkEventTracer_newTracingSection`

設計:

- `SkEventTracer_new` は C callback set を持つ concrete tracer を作る。
- `SkEventTracer_SetInstance` は tracer を消費する。Skia の仕様上、登録失敗時も渡した tracer は Skia 側で破棄される。
- `SkEventTracer_GetInstance` は borrowed singleton を返す。caller は削除しない。
- `release_proc` は tracer destructor で一度だけ呼ぶ。ただし `leakTracer=true` で process lifetime に残す場合は process exit で解放されない。

### Android / Ports

Android hardware buffer helpers と ports font manager は platform availability と CMake guard を先に確定する。既定 build に混ぜない。

2026-05-16 追記:

- `SkRemotableFontIdentitySet` は ref-counted owned pointer wrapper を追加済み。
- 抽象 `SkRemotableFontMgr` は concrete provider を作らず、既存または将来 provider pointer に対する call wrapper だけ追加済み。
- `SkFontMgr_Indirect` constructor は `sk_font_mgr_t` impl と `SkRemotableFontMgr*` proxy を retain して `sk_font_mgr_t` を返す形で追加済み。
- `SkFontConfigInterface` は Phase 8 で implementation source (`SkFontConfigInterface.cpp` / direct FontConfig sources) を import し、`RESKIA_ENABLE_FONTCONFIG_CAPI=ON` 配下の C API と smoke test を追加済み。
- `SkAndroidFrameworkUtils` は `SK_BUILD_FOR_ANDROID_FRAMEWORK` と Android platform API 依存のため `na`。
- `SkAnimatedImage` は Phase 8 で `src/android/SkAnimatedImage.cpp` を import し、`SkAndroidCodec` consumed ownership の C API と smoke test を追加済み。

## Recommended Order

1. `SkCustomTypefaceBuilder` path / drawable / stream subset。実装済み。
2. `SkOrderedFontMgr` minimal wrapper。実装済み。
3. `SkAnimCodecPlayer` codec-consuming wrapper。実装済み。
4. `SkCamera` non-Android deprecated subset。実装済み。
5. callback/global/subclass 系 (`SkEventTracer`, `SkPaintFilterCanvas`)。実装済み。
6. PDF value helpers と ports remotable thin wrappers。実装済み。
7. Android / FontConfig guarded provider/import-source APIs。
