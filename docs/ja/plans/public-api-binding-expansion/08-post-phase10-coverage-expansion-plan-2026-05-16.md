# Post-Phase10 Coverage Expansion Plan

作成時刻: 2026-05-16 19:43:52 JST

Phase 10 では coverage quality / overload polish / deferred small-gap cleanup を完了し、`partial` / `overcovered` / `deferred` は 0 になった。ここから先は generator polish ではなく、Phase 11 開始時点で残っていた `missing` 719 行を、実装価値・依存設計・platform guard の観点で再編して進める。

## Current Snapshot

`docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` の現状:

| status | count |
| --- | ---: |
| `covered` | 2811 |
| `missing` | 0 |
| `false_positive` | 275 |
| `split_covered` | 33 |
| `na` | 198 |
| `no_public_methods_found` | 104 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 0 |

Phase 29 で `missing` / `deferred` / `partial` / `overcovered` はすべて 0 として freeze した。以降の phase は coverage 数字を増やす実装追加ではなく、freeze 状態を壊さないための検証・命名・所有権・optional backend roadmap の整備を主目的にする。

## Missing Distribution

| area | missing | 主な内容 |
| --- | ---: | --- |
| `include/gpu` | 0 | 通常 missing なし。`GrExternalTexture*` dedicated bridge も Phase 28 で covered |
| `modules/svg` | 0 | `SkSVGImage::LoadImage` resource/provider loading 済み |

Phase 16 audit residual index view (reference; Phase 17/18 covered moves are reflected in the matrix counts above):

| bucket | count |
| --- | ---: |
| `real_gap` | 324 |
| `na` | 160 |
| `false_positive` | 282 |
| `P1` | 8 |
| `P2` | 184 |
| `P3` | 286 |
| `P0` | 288 |

Phase 17A で Graphite `BackendSemaphore` / `TextureInfo::isCompatible` / YUV(A) / options、Ganesh `GrYUVABackendTextureInfo` / `GrYUVABackendTextures`、`GrDriverBugWorkarounds` を covered に移した。Phase 18A では SVG type value accessor、node factory、filter-effect query、`SkSVGLengthContext` helper、node mutation helper、OpenType SVG decoder を covered に移したため、Phase 16 audit snapshot から `missing` は 126 行減少した。

## Planning Principles

- 先に `P1/P2 real_gap` を減らす。特に GPU と text stack は coverage 上の大きな塊で、実装後の smoke も作りやすい。
- `na` は放置せず、Phase 15 で platform/internal/abstract callback として明示分類を増やす。matrix 上の `missing` を減らすには、実装だけでなく適切な対象外理由の反映も必要。
- callback/provider/global registration は Phase 5A の方針に従い、所有権・lifetime・threading を先に固定してから実装する。
- SVG/SkSG はすでに最小 API があるため、次は graph/value object を incremental に増やし、抽象 render context を直接公開しすぎない。

## Phase 11: GPU Backend And Context Expansion

目的: `include/gpu` の残行を、実装可能な backend value API と platform/priv NA に分ける。

対象:

- `GrBackendSemaphore`
- `GrBackendFormat` の remaining query / string helpers
- `GrBackendTexture` / `GrBackendRenderTarget` の dimensions、label、mock/metal info、mutable state
- `GrDirectContext` の `MakeMock`、options overload、wait/update/state/precompile helpers
- Graphite `Context` / `Recorder` / `BackendTexture` / `TextureInfo` / `MutableTextureState`
- YUV(A) backend info/textures
- D3D/Vulkan-only / priv / testing-only rows の `na` 整理

Subphases:

| subphase | work |
| --- | --- |
| 11A | backend value wrappers: semaphore、format desc/toStr、texture/render-target dimensions/label/mock info |
| 11B | direct context operations: MakeMock/options、wait/update/state/precompile with callback omitted/defaulted where Skia permits |
| 11C | Graphite wrappers: Context/Recorder/TextureInfo/BackendTexture/MutableTextureState |
| 11D | GPU platform guard cleanup: D3D-only、priv、testing-only、unsupported Vulkan rowsを `na` へ反映 |

Expected outcome:

- GPU `real_gap` の大半を covered または documented `na` に移す。
- `public-api-gpu-missing-triage.csv` を Phase 11 用に再同期する。
- Metal/Ganesh smoke、Graphite smoke、Mock backend smoke を分ける。

Progress:

- 2026-05-16: Phase 11A first pass として `GrBackendFormat_asMtlFormat` / `GrBackendFormat_toStr`、`GrBackendTexture_dimensions` / `GrBackendTexture_getLabel`、`GrBackendRenderTarget_dimensions`、`GrBackendSemaphore` default/copy/Metal/Vulkan query を追加した。`c_skia_gpu_context_capi_smoke` で mock backend の size/string wrapper と semaphore wrapper を検証済み。matrix は `covered 2427`、`missing 705`。
- 2026-05-16: `GrBackendFormat_desc`、`GrBackendTexture_getMockTextureInfo`、`GrBackendRenderTarget_getMockRenderTargetInfo` を追加した。mock render target の `id` は upstream に public accessor がないため C struct では 0 固定として明記した。matrix は `covered 2430`、`missing 702`。
- 2026-05-16: `MutableTextureState` wrapper、`GrBackendTexture_getMtlTextureInfo` / `GrBackendRenderTarget_getMtlTextureInfo`、`GrBackendTexture_setMutableState` / `GrBackendRenderTarget_setMutableState` を追加した。invalid mutable state は upstream assert を避けるため no-op とする。matrix は `covered 2441`、`missing 691`。
- 2026-05-17: Phase 11D として GPU D3D-only 17 行を `na`、`TestingOnly_Equals` 2 行を `false_positive` に分類する `public-api-phase-11-gpu-platform-overrides.csv` を追加し、generator が Phase 11 override も読むようにした。matrix は `covered 2441`、`missing 672`、`na 27`、`false_positive 164`。
- 2026-05-17: Phase 11B として `GrDirectContext_MakeMetal` / `MakeVulkan` / `MakeMock`、`resetGLTextureBindings`、`wait`、backend texture update、compressed texture update、backend state setter、`precompileShader` を callback なし wrapper として追加した。`priv()` 2 行は internal control surface として Phase 11D override で `na` にした。matrix は `covered 2461`、`missing 650`、`na 29`。
- 2026-05-17: Phase 11C として Graphite `Context` / `Recorder` / `TextureInfo` / `BackendTexture` の C wrapper を追加した。`Graphite_*` prefix を coverage generator の Graphite class alias に追加し、`c_skia_gpu_context_capi_smoke` で null/default object/Metal context 経路を検証済み。matrix は `covered 2506`、`missing 605`、`include/gpu missing 169`。
- 2026-05-17: Phase 11D cleanup として Graphite/GPU の platform-only / priv / callback-design-required 行を `public-api-phase-11-gpu-platform-overrides.csv` に追加分類した。Dawn/Vulkan-only、Graphite/Ganesh `priv()`、D3D-only は `na`、`ShaderErrorHandler` / allocator / external texture / Graphite async readback / `insertRecording` / `snap` / provider/canvas transfer は `design_required` として Phase 14 に routing した。matrix は `covered 2506`、`missing 587`、`na 47`、`include/gpu missing 151`。
- 2026-05-17: Phase 11 は完了扱いとし、残る Graphite `BackendSemaphore` Metal/default value wrapper、`ContextID`、`RecorderOptions` / `ContextOptions`、`TextureInfo::isCompatible` の 12 行は `Phase 16 GPU small-gap batch` に routing した。YUV(A) backend texture value objects も後続の GPU small-gap / coverage polish でまとめる。

## Phase 12: SVG And SkSG Graph Expansion

目的: `modules/svg` 191 行と `modules/sksg` 102 行を、graph/value object と internal render plumbing に分ける。

SVG work:

- shape/filter node の attribute helper を増やす。
- `SkSVGLengthContext` / `SkSVGRenderContext` / `SkSVGFilterContext` は direct public ABI にするか、`na` として render-internal に固定するかを決める。
- `SkSVGFe*` filter nodes は lightweight setter/query helper を優先する。
- `SkSVGImage` / `SkSVGUse` など resource/provider に絡むものは Phase 14 と接続する。

SkSG work:

- `RenderNode` / `Node` の invalidate/revalidate/nodeAt wrapper を検討する。
- `Group` add/remove child、basic geometry nodes、transform/effect nodes を追加する。
- `InvalidationController` は callback/observer ではなく value collector として公開できるか確認する。

Expected outcome:

- SVG/SkSG の `P3 real_gap` を、small helper 実装と `na` に二分する。
- `SkSG_RenderNode` holder を Phase 10 で導入済みなので、Graph node factory を安全に増やせる。

Progress:

- 2026-05-17: Phase 12 first pass として SkSG `Group::Make` / `addChild` / `removeChild` / `size` / `empty` / `clear`、`RenderNode::render` / `nodeAt` / `isVisible` / `setVisible`、`Node::invalidate` wrapper を追加した。`c_skia_sksg_capi_smoke` で null path、group child operation、visibility、scene construction を検証済み。matrix は `covered 2518`、`missing 575`、`modules/sksg missing 90`。
- 2026-05-17: SkSG second pass として `Rect::Make`、`Color::Make` / `getColor` / `setColor`、`Draw::Make`、`GeometryNode::contains`、`PaintNode::makePaint` wrapper を追加した。`contains` / `makePaint` は SkSG 内部 assert を避けるため wrapper 内で revalidate する。さらに SkSG protected virtual hook 32 行を `public-api-phase-12-svg-sksg-overrides.csv` で `false_positive` に分類した。matrix は `covered 2524`、`missing 537`、`false_positive 196`、`modules/sksg missing 52`。
- 2026-05-17: SkSG third pass として `Path::Make` / `setFillType`、`Plane::Make`、`OpacityEffect::Make` / `getOpacity` / `setOpacity`、`ClipEffect::Make`、`TransformEffect::Make`、`InvalidationController` の `new` / `inval` / `bounds` / `reset` wrapper を追加した。`TransformEffect_MakeWithMatrix` は互換 alias とし、generator の `partial` を避けるため正規名 `SkSG_TransformEffect_Make` も公開した。matrix は `covered 2536`、`missing 525`、`modules/sksg missing 40`。
- 2026-05-17: SkSG fourth pass として `RRect::Make`、`GeometryNode::clip` / `draw` / `asPath`、`Scene::nodeAt`、`TrimEffect` / `DashEffect` / `RoundEffect` / `OffsetEffect`、`ShaderEffect` / `MaskShaderEffect` / `BlenderEffect` / `LayerEffect` / `MaskEffect` factory wrapper を追加した。SVG cleanup として render/filter/parser internal hook、subclass `parseAndSetAttribute` の generic coverage、provider/image loading design-required を `public-api-phase-12-svg-sksg-overrides.csv` に分類した。matrix は `covered 2551`、`missing 393`、`false_positive 269`、`na 71`、`split_covered 33`、`modules/svg missing 74`、`modules/sksg missing 25`。

## Phase 13: Text Stack Expansion

目的: paragraph / shaper / unicode / plaintext editor の 79 行を整理し、実用 text API を広げる。

対象:

- `TextStyle` foreground/background `PaintOrID`
- `Paragraph::updateForegroundPaint` / `updateBackgroundPaint`
- `FontArguments` / `Block` / `Placeholder` / `StyleMetrics`
- `SkShaper` factory/result overloads
- `SkUnicode` remaining helper
- `skplaintexteditor::Editor` / `StringSlice`

Priority:

1. Paragraph `P1` rows: TextStyle paint ID and Paragraph update paint.
2. Shaper `P2` rows: existing shaping smoke と接続できる factory/result helpers.
3. Paragraph value objects `P2`: FontArguments、Block、Placeholder、StyleMetrics.
4. Plaintext editor `P3`: editor moduleを CMake/test と一緒に扱う。

Expected outcome:

- text stack の user-facing API を優先し、internal painter/cache rows は `na` へ整理する。

Progress:

- 2026-05-17: Phase 13 first pass として `TextStyle` foreground/background の `PaintOrID` query と `PaintID` setter wrapper を追加した。C ABI では `reskia_paragraph_paint_or_id_t` により PaintID variant を返し、paint 本体は既存の `getForeground` / `getBackground` で扱う分担にした。`c_skia_paragraph_text_style_capi_smoke` で null path と foreground/background PaintID roundtrip を検証済み。matrix は `covered 2555`、`missing 389`、`modules/skparagraph missing 29`。
- 2026-05-17: `SkUnicode_extractBidi` を追加した。upstream の static 宣言はこの build ではリンク実体がないため、C wrapper 内では `SkUnicode::Make()` で取得した backend の `getBidiRegions` に委譲する。`c_skia_unicode_capi_smoke` で static helper と null path を検証済み。matrix は `covered 2557`、`missing 388`、`modules/skunicode missing 0`。
- 2026-05-17: `Paragraph::updateForegroundPaint` / `updateBackgroundPaint` wrapper を追加した。upstream 実装は full text range 以外を debug assert するため、C wrapper では `ParagraphImpl::text().size()` を確認し、partial range は `false` で返して trap を避ける。`c_skia_paragraph_builder_capi_smoke` で partial range rejection と full range update を検証済み。matrix は `covered 2559`、`missing 386`、`modules/skparagraph missing 27`。
- 2026-05-17: `SkShaper` factory / cache purge / run iterator / simple, iterator, feature shape wrapper を追加した。shape output は既存 `SkTextBlobBuilderRunHandler` に接続し、font fallback handle 0 は `SkFontMgr::RefDefault()` に補完して upstream null dereference を避ける。`c_skia_shaper_capi_smoke` で factory、simple shape、iterator shape、feature shape を検証済み。matrix は `covered 2581`、`missing 364`、`modules/skshaper missing 0`。
- 2026-05-17: `skia::textlayout::FontArguments` wrapper を追加し、core `SkFontArguments` からの construction/copy と `CloneTypeface` を C ABI に露出した。`c_skia_paragraph_text_style_capi_smoke` で null path、copy、default typeface clone path を検証済み。さらに `public-api-phase-13-text-stack-overrides.csv` を追加し、`ParagraphPainter` / `ParagraphCache` callback/internal rows、`Block` / `Placeholder` / `StyleMetrics` internal layout records、未移植 optional module `skplaintexteditor` を理由付きで `na` / `false_positive` に分類した。matrix は `covered 2585`、`missing 314`、`na 116`、`modules/skparagraph missing 0`、`modules/skplaintexteditor missing 0`。
- 2026-05-17: Phase 13 は完了扱いとした。`skottie::Shaper::Shape` は text helper だが `modules/skottie` 側の After Effects shaping API であり、Phase 13 の paragraph/shaper/unicode/plaintext editor 範囲から外して後続 skottie helper batch に回す。

## Phase 14: Callback / Provider / Registration Batch

目的: Phase 5A の callback/provider foundation を使い、global registration と provider callback をまとめて扱う。

対象:

- `SkCodec::Register`
- `SkPngChunkReader::readChunk`
- `SkTypeface::Register`
- `skresources::ResourceProvider`
- skottie `PropertyObserver` / `MarkerObserver` / `PrecompInterceptor` / `Logger` / expression evaluator
- SVG image/resource loading hooks

Design requirements:

- callback の owner handle と destruction order を固定する。
- Skia が unregister API を持たない global registration は replacement / disabled callback policy を明記する。
- callback が返す Skia object の ownership は transferred / retained / borrowed を API 名または header comment に残す。

Expected outcome:

- callback/provider rows を実装可能なものと permanently-deferred/na に分ける。
- Phase 1 の設計メモを現行 API 実装に反映する。

Progress:

- 2026-05-17: Phase 14 first pass として `SkPngChunkReader` の C callback bridge を追加した。`SkPngChunkReader_new` は callback と `user_data` を保持する concrete subclass を作り、`SkPngChunkReader_retain` / `release` で `SkRefCnt` lifetime を管理する。`readChunk` の `tag` / `data` は callback 中だけ有効な borrowed pointer とし、reader 破棄時に `release_proc` を呼ぶ。`c_skia_codec_invalid_input_smoke` で null reader、null callback、callback dispatch、retain/release destruction を検証済み。matrix は `covered 2586`、`missing 313`、`include/codec missing 1`。
- 2026-05-17: skresources provider callback batch として `ExternalTrackAsset_new` / `seek` / refcount wrapper と `ResourceProvider_loadAudioAsset` を追加した。`ExternalTrackAsset` は seek callback と `user_data` を持つ concrete subclass とし、asset 破棄時に `release_proc` を呼ぶ。`c_skia_skresources_capi_smoke` で null path、seek callback、retain/release destruction、default `ResourceProvider_loadAudioAsset` null result を検証済み。matrix は `covered 2588`、`missing 311`、`modules/skresources missing 0`。
- 2026-05-17: skottie observer batch として `Logger` / `MarkerObserver` / `ExternalLayer` / `PrecompInterceptor` / `PropertyObserver` node traversal の C callback bridge と `AnimationBuilder` setter を追加した。`ExternalLayer` と `PrecompInterceptor` は callback が返した external layer を C++ 側で retain して `sk_sp` に変換する。`PropertyObserver` は property handle lazy materialization をまだ公開せず、`onEnterNode` / `onLeavingNode` のみを先行公開した。`c_skia_skottie_smoke` で direct callback、builder retained lifetime、release callback を検証済み。matrix は `covered 2594`、`missing 305`、`modules/skottie missing 12`。
- 2026-05-17: skottie expression/glyph batch として typed `ExpressionEvaluator` (`number` / `string` / `array`)、`ExpressionManager`、`AnimationBuilder_setExpressionManager`、`GlyphDecorator`、`TextPropertyValue_setDecorator` を追加した。array evaluator は C callback に `out_values == NULL` / `capacity == 0` で必要要素数を問い合わせ、2 回目の callback で値をコピーする規約にした。`c_skia_skottie_smoke` で evaluator callback、manager create callback、builder retained lifetime、glyph decorator dispatch、TextPropertyValue decorator retention を検証済み。matrix は `covered 2598`、`missing 301`、`modules/skottie missing 8`。
- 2026-05-17: Phase 14 callback/provider override 台帳 `public-api-phase-14-callback-provider-overrides.csv` を追加し、typed `ExpressionEvaluator<T>` の template marker 行を `split_covered`、内部 `SceneGraphRevalidator` を必要とする `SlotManager` constructor を `na` に分類した。matrix は `covered 2598`、`missing 299`、`split_covered 33`、`na 117`、`modules/skottie missing 6`。
- 2026-05-17: `PropertyObserver` property callback batch として lazy handle 設計メモ `skottie-property-observer-lazy-handle-design-2026-05-17.md` を追加し、`onColorProperty` / `onOpacityProperty` / `onTextProperty` / `onTransformProperty` の C callback bridge、callback-scoped lazy handle、owned property handle materialization、color/opacity/text/transform get/set wrapper を追加した。`c_skia_skottie_smoke` で direct property callback dispatch、null lazy materialization、transform null guard、builder retained lifetime を検証済み。matrix は `covered 2602`、`missing 295`、`modules/skottie missing 2`。
- 2026-05-17: Skottie shaper batch として設計メモ `skottie-shaper-result-capi-design-2026-05-17.md` を追加し、`Skottie_Shaper_Shape` / `ShapeAtPoint` / `ShapeInBox`、owned `Shaper::Result` wrapper、fragment count / missing glyph count / scale / visual bounds query を追加した。`TextPropertyValue` を `Shaper::TextDesc` source として再利用する。`c_skia_skottie_smoke` で point/box shape、result metadata、visual bounds、null path を検証済み。matrix は `covered 2604`、`missing 293`、`modules/skottie missing 0`。
- 2026-05-17: Phase 14 routing closeout として `phase14-registration-provider-routing-2026-05-17.md` を追加した。`SkCodec::Register` / `SkTypeface::Register` は process-global registration policy が必要な follow-up として missing に残し、`SkSVGImage::LoadImage` は SVG resource polish、GPU/Graphite async/provider/allocator は GPU 専用 phase に送る。

## Phase 15: Platform/Internal NA Sweep

目的: 残る `missing` のうち、Reskia の C ABI 方針で対象外にするものを明示する。

対象:

- Android-only `SkAndroidFrameworkUtils`
- D3D-only GPU rows
- `priv()` / testing-only / debug-only interfaces
- `bentleyottmann` low-priority internal geometry helpers
- abstract C++ base destructors / pure virtual callback surfaces
- `Sk3DView` platform/legacy camera helpers
- SkSL debug trace sinks

Expected outcome:

- `triage=na` / `false_positive` を Phase 10 override または新しい post-Phase10 override に反映し、matrix の `missing` を実態に近づける。
- `real_gap` は「実装すべき API」だけに近づける。

Progress:

- 2026-05-17: Phase 15 first pass として `public-api-phase-15-platform-internal-overrides.csv` を追加し、Android framework-only API、`SK_BUILD_FOR_ANDROID_FRAMEWORK` guarded `Sk3DView` camera helpers、SkSL debug trace sinks、`bentleyottmann` internal geometry helpers、core abstract/destructor/subclass hooks を `na` / `false_positive` に分類した。`SkCodec::Register` / `SkTypeface::Register` は global registration follow-up として missing に残した。matrix は `covered 2604`、`missing 252`、`na 154`、`false_positive 274`。

## Phase 16: Coverage Audit And Generator Refresh

目的: Phase 11-15 の結果を generator と台帳に反映し、次の長期サイクルへつなぐ。

Work:

- Phase 7 residual / routing index を再生成または同期する。
- `missing` の stale row、既に covered になった row、古い `next_phase` を削除する。
- overload-aware matching の追加が必要な領域を抽出する。
- smoke test matrix を docs にまとめる。
- `public-api-coverage-matrix.csv` の status vocabulary を整理する。

Exit criteria:

- `partial` / `overcovered` / `deferred` は 0 のまま維持する。
- `missing` は `real_gap` 実装候補と明示 `na` 候補に整理済み。
- 次に着手する phase が、coverage impact と design risk の両方から説明できる。

Progress:

- 2026-05-20: Phase 16 first pass として `public-api-phase16-coverage-audit-2026-05-20.md` と `public-api-phase-16-current-missing-routing.csv` を追加した。最新 matrix では `covered 2604`、`missing 252`、`false_positive 274`、`na 154`、`split_covered 33`、`partial/overcovered/deferred 0`。古い Phase 7 routing index は stale とし、残 `missing` を `include/gpu 151`、`modules/svg 74`、`modules/sksg 25`、global registration 2 行へ再 routing した。Phase 16 は runtime C ABI を追加せず、status vocabulary、smoke coverage map、次 phase 境界を固定する audit phase とした。

## Phase 17: GPU Small-Gap And Provider Split

目的: 残る `include/gpu` 151 行を、low-risk value wrappers と design-heavy provider/async/platform allocator に分割して進める。

Priority:

1. YUV(A) backend texture value wrappers: `GrYUVABackendTextureInfo` / `GrYUVABackendTextures` / Graphite equivalents.
2. Backend value/options wrappers: `GrBackendDrawableInfo`、mock texture/render target info、`GrDriverBugWorkarounds`、Graphite `BackendSemaphore` / options / compatibility queries.
3. GL/Vulkan/Dawn/platform-only rows の build guard / `na` 再確認。
4. Graphite async readback、`ImageProvider`、`Recorder::snap`、`Context::insertRecording`、allocator provider は専用 ownership design を置いてから実装可否を判断する。

Expected outcome:

- GPU value rows を covered/na に寄せ、callback/provider rows だけを明示 follow-up として残す。
- `c_skia_gpu_context_capi_smoke` / `c_skia_gpu_surface_capi_smoke` を拡張して value wrappers を検証する。

Progress:

- 2026-05-20: Phase 17A first pass として Graphite `TextureInfo::isCompatible` と `BackendSemaphore` default / Metal / copy constructor、`isValid` / `backend` / Metal event/value query wrapper を追加した。Phase 11 で実装候補として `missing` 固定していた行は `public-api-phase-17-gpu-small-gap-overrides.csv` で covered に昇格し、generator は post-phase override の `covered` を扱うようにした。`c_skia_gpu_context_capi_smoke` は既存 Ganesh+Metal 構成で通過。Graphite+Metal 専用構成は既存の Objective-C ARC 互換エラーでビルド不可のため、Phase 17B の GPU verification risk として残す。matrix は `covered 2612`、`missing 244`、`include/gpu missing 143`。
- 2026-05-20: Phase 17A continuation として Ganesh `GrYUVABackendTextureInfo` / `GrYUVABackendTextures` の default / constructor / copy / equality / plane query / YUVA location wrapper と、`GrDriverBugWorkarounds` の constructor / copy / apply wrapper を追加した。YUV(A) wrapper は `SkYUVAInfo` と mock alpha texture/format で smoke 検証し、集合 accessor は owned copy の配列出力にした。matrix は `covered 2633`、`missing 223`、`include/gpu missing 122`。
- 2026-05-20: Graphite YUV(A) continuation として `YUVABackendTextureInfo` / `YUVABackendTextures` の default / recorder constructor / copy / query wrapper を追加した。constructor は有効オブジェクト作成に `Recorder` を要求し、query 結果は owned copy として返す。さらに Graphite `ContextOptions` / `RecorderOptions` の default/copy と GPU budget field wrapper を追加した。matrix は `covered 2657`、`missing 199`、`include/gpu missing 98`。

## Phase 18: SVG Resource And Value Polish

目的: `modules/svg` の残行を、value accessors、node factories、resource/provider design に分ける。Phase 18A first pass 後の残行は 62 行。

Priority:

1. `SkSVGTypes.h` の lightweight `type()` / value accessors。
2. SVG node/filter `Make` factories の追加と existing DOM/render smoke への接続。
3. `appendChild` は standalone node ownership / child transfer model を設計してから扱う。
4. `SkSVGImage::LoadImage` は `SkSVGIRI`、`SkSVGPreserveAspectRatio`、`ImageInfo` wrapper と skresources provider owner model をまとめて設計する。

Expected outcome:

- SVG value/factory rows を coverage polish し、resource loading は設計済み follow-up にする。

Progress:

- 2026-05-20: Phase 18A first pass として `SkSVGTypes.h` の lightweight value wrapper を追加した。`SkSVGIRI` / `SkSVGPaint` は owned copy の `SkString` / value object を返し、`SkSVGPaint::color` / `iri` と `SkSVGStopColor::color` は upstream assert 条件を C wrapper 側で型確認してから呼ぶ。`SkSVGLineJoin` / `SkSVGSpreadMethod` / `SkSVGVisibility` / `SkSVGStopColor` / `SkSVGObjectBoundingBoxUnits` / `SkSVGTextAnchor` は enum type accessor を追加し、`c_skia_svg_types_capi_smoke` で roundtrip と null-safe cleanup を検証済み。matrix は `covered 2669`、`missing 187`、`modules/svg missing 62`。
- 2026-05-20: Phase 18A continuation として SVG node `Make` factory 群、`SkSVGNode_ref` / `unref` / `release`、`SkSVGFe::IsFilterEffect` wrapper を追加した。factory は `sk_sp<T>::release()` で owned node を C ABI に渡し、DOM 由来 borrowed node は既存どおり解放対象外とする。`SkSVGLengthContext` は render context 本体から切り離せる lightweight helper として `viewPort` / `setViewPort` / `resolve` / `resolveRect` を追加した。`c_skia_svg_dom_capi_smoke` と `c_skia_svg_types_capi_smoke` で検証済み。matrix は `covered 2713`、`missing 143`、`modules/svg missing 18`。
- 2026-05-20: Phase 18A closeout として `SkSVGNode_appendChild`、`SkSVGTransformableNode_setTransform`、`SkSVGPresentationAttributes_MakeInitial`、`SkSVGOpenTypeSVGDecoder_Make` / `approximateSize` / `render` wrapper を追加した。`appendChild` は child を retain して渡し、caller-owned node を消費しない。render-context 直結の `SkSVGNode::render` / `asPaint` / `asPath` / `objectBoundingBox` は `SkSVGDOM_render` / `renderNode` と今後の higher-level extraction API に任せるため Phase 18 override で `na`、macro 抽出された `SVG_PRES_ATTR` は `false_positive` に分類した。matrix は `covered 2725`、`missing 126`、`modules/svg missing 1`。残る SVG 行は `SkSVGImage::LoadImage` のみで、skresources provider と image asset ownership を伴うため resource/provider follow-up に残す。

## Phase 19: SkSG Graph Polish

目的: `modules/sksg` 25 行の graph/effect factories と getter/iterator surface を整理する。

Priority:

1. Color filter、gradient、image、merge、render effect factories。
2. `GeometryTransform::getTransform`、shader/filter getters の revalidate-safe wrapper。
3. `InvalidationController` begin/end は C iterator API を設計してから実装する。

Expected outcome:

- SkSG graph factory rows を covered に寄せ、iterator-only rows は明示設計済みにする。

Progress:

- 2026-05-20: Phase 19A として SkSG `ColorFilter` / `Gradient` / `Image` / `Merge` / `Text` / `ShaderPaint` / `ImageFilter` / `Transform` / `GeometryTransform` / `ShaderEffect::setShader` / `Node::revalidate` / `InvalidationController` begin/end wrapper を追加した。`InvalidationController` は C iterator object ではなく、現時点の invalidation rect 数を返す count-style helper として exposed し、既存 `bounds` と併用する。`Transform::MakeConcat` は同一 transform を左右に渡すと upstream debug assert になるため C wrapper 側で invalid 入力として `NULL` を返す。`c_skia_sksg_capi_smoke` で graph/effect factory、getter、ref/unref、null path を検証済み。matrix は `covered 2750`、`missing 101`、`modules/sksg missing 0`。

## Phase 20: Global Registration Design

目的: `SkCodec::Register` と `SkTypeface::Register` の process-global callback registration を安全に扱う。

Design requirements:

- upstream に unregister がないため、callback owner は process lifetime または disabled callback policy を持つ。
- repeated registration と replacement behavior を明記する。
- `std::unique_ptr<SkStream>` / `SkStreamAsset` transfer と returned `SkCodec` / `SkTypeface` ownership を C ABI に落とす。
- callback release timing を library teardown に依存させない。

Expected outcome:

- まず設計メモと API skeleton を作り、通常の borrowed callback bridge と混同しない。

Progress:

- 2026-05-21: Phase 20A として設計メモ `docs/ja/notes/bindings/phase20-global-registration-capi-design-2026-05-21.md` を追加し、`SkCodec_Register` と `SkTypeface_Register` を実装した。`SkCodec_Register` は現行 upstream の `SkCodecs::Register` に固定 decoder id `reskia` で接続し、peek/make callback と context replacement を提供する。`SkTypeface_Register` は upstream factory callback が matched `FactoryId` を受け取れないため、初回登録 id を process 内で固定し、同一 id の context replacement のみ許可する。`c_skia_codec_smoke` で null rejection、callback dispatch、replacement release、different-id rejection を検証済み。matrix は `covered 2752`、`missing 99`、global registration missing 0。

## Phase 21: GPU Residual Triage Refresh

目的: 残る `include/gpu` 98 行を、実装可能な value wrapper、platform guard / optional backend、abstract provider / callback design に再分類する。

Residual buckets:

1. Low-risk value wrappers: `GrMockTypes`、`GrGLTypes`、`GrVkTypes`、`VulkanTypes`、`GrBackendDrawableInfo`、一部 `GrContextOptions`。
2. Platform backend value wrappers: `GrGLExtensions` / `GrGLInterface`、`VulkanExtensions`、Graphite `DawnTextureInfo` / `MtlTextureInfo` / `VulkanTextureInfo`、Metal / Vulkan allocator 周辺。
3. Graphite ownership/API design: `Context::insertRecording`、async readback、`Recorder::snap`、`addFinishInfo`、`makeDeferredCanvas`、`ImageProvider`。
4. Abstract callback/provider rows: `ShaderErrorHandler`、`GrExternalTextureGenerator` / `GrExternalTexture`、`VulkanMemoryAllocator`、`MtlMemoryAllocator`。

Tasks:

1. `public-api-phase-21-gpu-residual-routing.csv` を追加し、98 行を `value_wrapper` / `platform_guard` / `provider_design` / `callback_design` / `abstract_virtual` に分類する。
2. platform guard が明確な row は Phase 15/17 override 方針と同じ語彙で `na` 候補にする。
3. 実装候補は Phase 22 の small value batch に移し、provider/callback は Phase 23 の設計 batch に移す。

Expected outcome:

- `include/gpu` 98 行の next action が row-level で明示される。
- Phase 22 の実装対象を、既存 GPU smoke で検証できる value wrapper に絞る。

Progress:

- 2026-05-21: `public-api-phase-21-gpu-residual-routing.csv` を追加し、GPU missing 98 行を row-level に routing した。内訳は next phase 別に `Phase 22` 57 行、`Phase 23` 38 行、`Phase 21` platform guard 判定 3 行。bucket 別では `value_wrapper` 33、`platform_value_wrapper` 24、`provider_design` 20、`allocator_design` 14、`callback_design` 4、`platform_guard` 3。Phase 22 は mock/GL/Vulkan/Metal/DrawableInfo/ContextID の small value wrapper、Phase 23 は Graphite async/provider、external texture、allocator、GL/Vulkan loader callback 設計に分けた。
- 2026-05-21: Phase 21 platform guard closeout として Dawn-only `DawnTextureInfo` constructor 3 行を `public-api-phase-21-gpu-platform-overrides.csv` で `na` に分類した。Dawn backend は `RESKIA_ENABLE_GPU_DAWN=ON` と Dawn/WebGPU C++ headers が必要な optional backend で、現行 portable C ABI coverage からは外す。matrix は `covered 2752`、`missing 96`、`na 161`、`include/gpu missing 95`。

## Phase 22: GPU Value Wrapper Final Batch

目的: Phase 21 で `value_wrapper` とした GPU row を実装し、coverage を安全に上げる。

Priority:

1. Mock / GL / Vulkan lightweight structs: equality、protected query、constructor、basic accessor。
2. `GrBackendDrawableInfo` と `GrContextOptions` の default/copy/accessor。
3. Graphite backend texture info value constructors は backend guard と dependency availability を確認してから追加する。

Acceptance:

- `c_skia_gpu_context_capi_smoke` または `c_skia_gpu_surface_capi_smoke` に null path と roundtrip を追加する。
- optional backend guarded row は、ビルド不能な backend で無理に public C API を出さず、guarded implementation または documented `na` にする。
- Phase 22 後、GPU `missing` は provider/callback/platform allocator 設計行だけに残す。

Progress:

- 2026-05-21: Phase 22 first batch として Ganesh mock value wrapper (`GrMockTextureInfo` / `GrMockRenderTargetInfo` / `GrMockOptions`) と GL value wrapper (`GrGLTextureInfo` / `GrGLFramebufferInfo`) を追加した。さらに `GrMtlTextureInfo` default/equality、`GrContextOptions` default/copy/suppressPrints、`GrBackendDrawableInfo` guarded wrapper を追加した。`GrBackendDrawableInfo` は upstream header が Vulkan third_party header を直接要求するため、現行 portable GPU build では stub fallback、Vulkan header がある構成のみ native `GrBackendDrawableInfo` に接続する。matrix は `covered 2781`、`missing 67`、`include/gpu missing 66`。`test_gpu_context_capi_smoke` target は `sk_gpu_backend_surface.cpp` / `sk_gpu_context.cpp` の compile まで到達したが、既存の `libsvg.a` 由来 `SkShaper::Make(sk_sp<SkFontMgr>)` 未解決で link に失敗した。
- 2026-05-21: Phase 22 continuation として Graphite `MtlTextureInfo` default / texture / value constructor helper と `Context::contextID` opaque value wrapper (`Graphite_Context_contextID` / `Graphite_ContextID_*`) を追加した。`ContextID` は private raw id を公開せず、owned opaque copy の validity/equality だけを C ABI に出す。`public-api-phase-22-gpu-value-overrides.csv` を追加し、Phase 11D で missing 固定していた `contextID` 行を covered に更新した。matrix は `covered 2785`、`missing 63`、`include/gpu missing 62`。`test_gpu_context_capi_smoke` target は引き続き compile 後に既存 `libsvg.a` 由来 `SkShaper::Make(sk_sp<SkFontMgr>)` 未解決で link 失敗する。
- 2026-05-21: Phase 22 GL extension inline subset として `GrGLExtensions` default / swap / isInitialized / reset wrapper を追加した。copy / has / remove / add / init / dumpJSON は、この build の linked objects に `GrGLExtensions.cpp` 実装が入っておらず未解決 symbol になるため Phase 23 の GL interface/loader design に残した。matrix は `covered 2790`、`missing 58`、`include/gpu missing 57`。

## Phase 23: GPU Provider / Async / Allocator Design

目的: GPU の abstract provider / callback / allocator 行を、実装するものと対象外にするものへ分ける。

Design targets:

- Graphite `Context` async readback and `insertRecording`
- Graphite `Recorder::snap` / `addFinishInfo` / `makeDeferredCanvas`
- Graphite `ImageProvider`
- Ganesh `GrExternalTextureGenerator` / `GrExternalTexture`
- `ShaderErrorHandler`
- Vulkan / Metal memory allocator interfaces

Design requirements:

- callback context lifetime、release timing、threading、GPU queue / recorder ownership を Phase 5A/20 と同じ語彙で書く。
- returned GPU resource handle の ownership と backend-specific guard を明示する。
- abstract virtual hooks を C ABI に出す場合は concrete C++ bridge class を作る。そうでない場合は `na` 理由を matrix override に残す。

Expected outcome:

- `docs/ja/notes/bindings/phase23-gpu-provider-async-allocator-design-YYYY-MM-DD.md` を追加する。
- 実装しない row は `na` / `false_positive` に分類し、実装する row は Phase 24+ に移す。

Progress:

- 2026-05-21: Phase 23 design note `docs/ja/notes/bindings/phase23-gpu-provider-async-allocator-design-2026-05-21.md` を追加した。残る GPU 行を Graphite recording/async/image provider、Ganesh external texture/shader error callback、GL interface/extension loader、Vulkan/Metal allocator、optional Vulkan value に分け、callback owner、async result、recording transfer、borrowed deferred canvas、allocator provider の ownership 方針を固定した。
- 2026-05-21: Phase 23A optional Vulkan guard として `public-api-phase-23-gpu-provider-overrides.csv` を追加し、Graphite Vulkan texture info、`GrVkImageInfo`、`VulkanExtensions`、`VulkanAlloc`、`VulkanYcbcrConversionInfo` の 10 行を `na` に分類した。現行 portable build は `include/third_party/vulkan/vulkan/vulkan_core.h` が無く native Vulkan type を compile できないため、Vulkan build target が整うまで C ABI coverage から外す。matrix は `covered 2790`、`missing 48`、`na 171`、`include/gpu missing 47`。
- 2026-05-21: Phase 23B first implementation として `Graphite_Recording` owned handle、`Graphite_Recorder_snap`、`Graphite_Context_insertRecording`、`Graphite_Recording_delete` を追加した。`insertRecording` は recording を borrowed とし、callback/semaphore/target surface/target texture state は指定しない最小 `InsertRecordingInfo` に限定する。advanced fields は finish callback / deferred canvas continuation に残す。matrix は `covered 2792`、`missing 46`、`include/gpu missing 45`。`test_gpu_context_capi_smoke` target は compile 後に既存 `libsvg.a` 由来 `SkShaper::Make(sk_sp<SkFontMgr>)` 未解決で link 失敗する。
- 2026-05-21: Phase 23B finish callback continuation として `Graphite_Recorder_addFinishInfo` を追加した。C callback と `user_data` は C++ bridge context が保持し、Skia の finished callback 発火時に result を `0/1` で渡して `release_proc` を一度だけ呼ぶ。smoke では snap 前に recorder を release した failure callback path を追加した。matrix は `covered 2793`、`missing 45`、`include/gpu missing 44`。build は同じ既存 `SkShaper::Make` link issue で停止する。
- 2026-05-21: Phase 23B recorder provider/deferred canvas continuation として `Graphite_Recorder_clientImageProvider` と `Graphite_Recorder_makeDeferredCanvas` を追加した。`clientImageProvider` は recorder-owned borrowed opaque pointer、`makeDeferredCanvas` は次回 `snap` または recorder release まで有効な borrowed `reskia_canvas_t*` として C ABI に出す。smoke には null path、default provider non-null、Metal `TextureInfo` + `SkImageInfo` の deferred canvas path を追加した。matrix は `covered 2796`、`missing 42`、`include/gpu missing 41`。build は compile 後に既存 `libsvg.a` 由来 `SkShaper::Make(sk_sp<SkFontMgr>)` 未解決で停止する。
- 2026-05-21: Phase 23E Vulkan allocator guard として `VulkanMemoryAllocator` 12 行を `na` に分類した。これらは `VkImage` / `VkBuffer` / `VkDeviceSize` / `VulkanBackendMemory` と concrete allocator callback bridge に依存し、現行 portable build では Vulkan header / allocator target がないため、optional Vulkan allocator bridge まで C ABI coverage から外す。matrix は `covered 2796`、`missing 30`、`na 183`、`include/gpu missing 29`。
- 2026-05-21: Phase 23E Metal allocator guard として `MtlMemoryAllocator` 2 行を `na` に分類した。`id<MTLBuffer>` / `id<MTLTexture>` / `MTLTextureDescriptor` と `MtlAlloc` refcount の Objective-C lifetime を伴うため、optional Metal allocator bridge まで portable C ABI coverage から外す。matrix は `covered 2796`、`missing 28`、`na 185`、`include/gpu missing 27`。
- 2026-05-21: Phase 23B Graphite async readback continuation として `Graphite_Context_asyncRescaleAndReadPixels*` 6 wrapper を追加した。image/surface overload は C 名で分け、callback ABI は既存 `reskia_async_read_pixels_callback_t` / `reskia_async_read_result_t` を再利用する。invalid input は既存 `SkImage` / `SkSurface` wrapper と同じく callback に `NULL` result を返す。あわせて `GrRecordingContext_skCapabilities` を owned `const_sk_capabilities_t` handle として追加した。matrix は `covered 2803`、`missing 21`、`include/gpu missing 20`。build は compile 後に既存 `libsvg.a` 由来 `SkShaper::Make(sk_sp<SkFontMgr>)` 未解決で停止する。
- 2026-05-21: Phase 23C/D closeout として `ShaderErrorHandler` の C callback bridge (`ShaderErrorHandler_new` / `compileError` / `delete`) と `GrContextOptions_setShaderErrorHandler` を追加した。handler は caller-owned、options は borrowed pointer を保持し、handler delete 時に release callback を一度だけ呼ぶ。さらに `GrGLExtensions` 残 5 行と `GrGLInterface` 8 行を GL loader / linked implementation follow-up として `na` に分類した。matrix は `covered 2804`、`missing 7`、`na 198`、`include/gpu missing 6`。build は同じ既存 `SkShaper::Make` link issue で停止する。

## Phase 24: SVG Image Resource Loading

目的: 最後の `modules/svg` 1 行、`SkSVGImage::LoadImage` を resource/provider ownership とともに処理する。

Tasks:

1. `SkSVGIRI`、`SkSVGPreserveAspectRatio`、`SkSVGImage::ImageInfo` の C ABI 表現を確認する。
2. 既存 `skresources::ResourceProvider` wrapper から `SkSVGImage::LoadImage` に渡せる provider ownership を設計する。
3. `ImageInfo` の返却を owned result struct にするか、image / destination rect / intrinsic size などの accessor に分割するか決める。
4. `c_skia_svg_dom_capi_smoke` または skresources smoke に null/failure path と minimal provider path を追加する。

Expected outcome:

- 実装可能なら `SkSVGImage_LoadImage` と `ImageInfo` wrapper を追加して `modules/svg missing 0` にする。
- 依存が過大な場合でも、row-level `na` ではなく provider follow-up として設計メモに明確な blocker を残す。

Progress:

- 2026-05-21: Phase 24 implementation として `SkSVGPreserveAspectRatio` value wrapper と `SkSVGImage_LoadImage` を追加した。`LoadImage` は borrowed `reskia_skresources_resource_provider_t*`、borrowed `SkSVGIRI` / viewport / preserveAspectRatio input を受け、成功時は caller-owned `sk_image_t` と `sk_rect_t` を `reskia_svg_image_info_t` で返す。`public-api-phase-24-svg-provider-overrides.csv` で古い Phase 12 design-required override を covered に上書きし、matrix は `covered 2805`、`missing 6`、`modules/svg missing 0`。source SVG build の `test_svg_image_capi_smoke` は通過。PNG decode が有効な環境では success path も検証し、現行 source build のように fixture decode が無効な場合は failure/clear path を検証する。

## Recommended Order

1. Phase 21: GPU residual triage refresh。98 行を実装候補と設計候補に分ける。
2. Phase 22: GPU value wrapper final batch。既存 smoke で検証できる small value row を先に減らす。
3. Phase 23: GPU provider / async / allocator design。callback/resource ownership を文書化してから実装可否を決める。
4. Phase 24: SVG image resource loading。残り 1 行を skresources provider と `ImageInfo` ownership と一緒に処理する。

## Phase 25: GPU Provider Bridge Closeout

目的: Phase 24 後に残った GPU 6 行を、実装可能な Graphite provider bridge と専用設計が必要な Ganesh external texture bridge に分けて処理する。

Tasks:

1. Graphite `ImageProvider::findOrCreate` を direct wrapper と C callback provider で公開する。
2. `RecorderOptions` に provider を retain して渡せる setter と、options 付き recorder factory を追加する。
3. callback が返す `sk_image_t` の transfer semantics を文書化する。
4. `GrExternalTexture` / `GrExternalTextureGenerator` は `SkImages::DeferredFromTextureGenerator` と external backend resource lifecycle を含む dedicated bridge として設計に残す。

Expected outcome:

- `ImageProvider::findOrCreate` は `covered` にする。
- `GrExternalTexture*` 5 行は `deferred` とし、`na` にはしない。
- 通常の `missing` は 0 にし、残りは dedicated external texture bridge の follow-up として明確化する。

Progress:

- 2026-05-21: `Graphite_ImageProvider_findOrCreate`、`Graphite_ImageProvider_new` / `ref` / `unref`、`Graphite_RecorderOptions_setImageProvider`、`Graphite_Context_makeRecorderWithOptions` を追加した。C callback provider が返す `sk_image_t` は bridge が消費し、Skia へ `sk_sp<SkImage>` として渡す。`phase25-gpu-provider-bridge-design-2026-05-21.md` と `public-api-phase-25-gpu-provider-bridge-overrides.csv` を追加し、`GrExternalTexture` / `GrExternalTextureGenerator` 5 行は dedicated external texture bridge まで `deferred` とした。

## Phase 26: Coverage Freeze / Audit

目的: Phase 25 後の `missing 0` を正式な到達点として固定し、残る `deferred 5` を通常の未実装ではなく dedicated Ganesh external texture bridge backlog として扱う。

Tasks:

1. 最新 matrix の status count と area 分布を audit note に記録する。
2. status vocabulary を Phase 26 時点の意味に更新する。`deferred` は一時的な generator warning ではなく、明示設計済み dedicated bridge backlog として扱う。
3. 古い Phase 16 audit の前提と Phase 26 後の前提を区別する。
4. 次 work order を build verification debt と Ganesh external texture bridge に分ける。

Expected outcome:

- `missing 0` を維持する。
- `partial 0` / `overcovered 0` を維持する。
- `deferred 5` は `GrExternalTexture` / `GrExternalTextureGenerator` のみであることを固定する。
- 次に進む場合は Phase 27 build verification debt、または Phase 28 Ganesh external texture dedicated bridge から選べる。

Progress:

- 2026-05-21: `public-api-phase26-coverage-freeze-audit-2026-05-21.md` を追加し、Phase 25 後の snapshot (`covered 2806`、`missing 0`、`deferred 5`) と `deferred` の扱いを固定した。

## Phase 27: Build Verification Debt

目的: Phase 22-25 の GPU C API 変更を継続的に検証できるよう、prebuilt GPU build で止まっていた `libsvg.a` / `SkShaper::Make(sk_sp<SkFontMgr>)` link debt を解消する。

Tasks:

1. `test_gpu_context_capi_smoke` の link failure を再現し、source mode と prebuilt mode の差を確認する。
2. prebuilt mode の内部ライブラリ閉包に `skshaper` / `skunicode` が欠けていることを記録する。
3. Apple prebuilt mode では local fallback `skshaper` / `skunicode` targets を構成し、prebuilt `libsvg.a` の text shaping symbol を満たす。
4. GPU smoke target が link できることを確認する。

Expected outcome:

- `cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8` が link まで成功する。
- Metal device がない環境では runtime smoke が SKIP/PASS になることを許容する。
- source mode の SVG smoke build に回帰がないことを確認する。

Progress:

- 2026-05-21: prebuilt mode で `skia/lib/libsvg.a` は存在するが `libskshaper.a` / `libskunicode.a` が無いことを確認した。`libsvg.a` は `SkSVGText.cpp.o` から `SkShaper::Make(sk_sp<SkFontMgr>)` を未解決参照していた。
- 2026-05-21: Apple non-source mode で fallback `skunicode` / `skshaper` static targets を local source から作り、`RESKIA_INTERNAL_LIBS` に追加する CMake 修正を入れた。prebuilt `libsvg.a` はそのまま使い、欠けていた shaping symbol だけを補う。
- 2026-05-21: `test_gpu_context_capi_smoke` は build/link 成功。実行は現在環境に Metal device が無いため `SKIP: Metal device is unavailable in this environment` のうえ `PASS`。source mode の `test_svg_image_capi_smoke` / `test_svg_types_capi_smoke` も通過。

## Phase 28: Ganesh External Texture Dedicated Bridge

目的: Phase 26 で意図的に残した `deferred 5`、つまり `GrExternalTexture` / `GrExternalTextureGenerator` を safe concrete C callback bridge として実装する。

Tasks:

1. caller-owned `reskia_gr_external_texture_t` を追加し、backend texture copy accessor と idempotent dispose を公開する。
2. C callback backed `GrExternalTextureGenerator` concrete subclass を追加する。
3. `SkImages::DeferredFromTextureGenerator` を C ABI に公開し、generator ownership transfer を明確にする。
4. `test_gpu_context_capi_smoke` に null path、direct external texture path、generator callback path、deferred image factory path を追加する。
5. Phase 25 の `deferred` override を Phase 28 override で `covered` に更新する。

Expected outcome:

- `deferred` は 0 に戻る。
- `missing` は 0 を維持する。
- `test_gpu_context_capi_smoke` が build/link し、Metal device がない環境でも Ganesh external texture bridge の non-device smoke を通す。

Progress:

- 2026-05-21: `GrExternalTexture_new` / `delete` / `getBackendTexture` / `dispose`、`GrExternalTextureGenerator_new` / `delete` / `generateExternalTexture`、`SkImages_DeferredFromTextureGenerator` を追加した。external texture は `GrBackendTexture` を copy して保持し、dispose は一度だけ、delete 時にも未 dispose なら dispose する。generator callback が返した external texture object は bridge が consume して `std::unique_ptr<GrExternalTexture>` に移す。
- 2026-05-21: `public-api-phase28-ganesh-external-texture-bridge-2026-05-21.md` と `public-api-phase-28-ganesh-external-texture-overrides.csv` を追加し、5 行を `covered` に更新した。`test_gpu_context_capi_smoke` は build/link 成功し、Metal device unavailable により Graphite/Metal path は skip されたが Ganesh external texture bridge smoke は `PASS`。

## Phase 29: Final Coverage Freeze / Documentation Closeout

目的: Phase 28 後の `missing 0` / `deferred 0` を最終 coverage freeze として固定し、以降の作業を coverage expansion ではなく freeze maintenance として再定義する。

Tasks:

1. 最新 matrix を generator で再生成し、status count を記録する。
2. `missing` / `deferred` / `partial` / `overcovered` がすべて 0 であることを final freeze note に残す。
3. `false_positive` / `na` / `no_public_methods_found` / `split_covered` の意味を freeze invariant として明文化する。
4. Phase 26 の freeze は `deferred 5` 時点の中間 freeze、Phase 29 は `deferred 0` の final freeze として位置づける。
5. 次 phase を verification hardening / API surface audit / optional backend roadmap / full build sweep に分ける。

Expected outcome:

- `docs/ja/notes/bindings/public-api-phase29-final-coverage-freeze-2026-05-21.md` に final snapshot を残す。
- 以降、coverage matrix の steady state は `missing 0` / `deferred 0` / `partial 0` / `overcovered 0` とする。
- 新しい missing が出た場合は、同じ変更内で implementation / classification / design-required follow-up のどれかに routing する。

Progress:

- 2026-05-21: generator を再実行し、`covered 2811`、`split_covered 33`、`false_positive 275`、`na 198`、`no_public_methods_found 104`、`missing 0`、`deferred 0`、`partial 0`、`overcovered 0` を Phase 29 final freeze snapshot として記録した。

## Phase 30: Verification Matrix Hardening

目的: coverage freeze を build/test matrix で守れるよう、現在手元で確認している smoke を CI/ローカル検証観点で整理する。

Tasks:

1. C API smoke targets を module/feature flag ごとに一覧化する。
2. prebuilt / source / system mode のうち、現実的に継続検証できる組み合わせを明示する。
3. GPU/Graphite/Metal unavailable 環境の `SKIP/PASS` 条件を記録し、失敗と区別できるようにする。
4. `scripts/generate_public_api_coverage.py` の実行を coverage freeze check として扱う運用を文書化する。

Expected outcome:

- coverage regression を generator count と smoke target の両方で検出できる。
- optional backend が使えない環境でも、skip 条件が明示されているため false failure を避けられる。

Progress:

- 2026-05-21: `public-api-phase30-verification-matrix-hardening-2026-05-21.md` を追加し、freeze check を `python3 scripts/generate_public_api_coverage.py` と代表 smoke matrix に分けた。prebuilt GPU tree では `test_gpu_context_capi_smoke` / `test_gpu_surface_capi_smoke` を build/run し、Metal device unavailable は `SKIP` のうえ `PASS` として扱う条件を固定した。source SVG tree では `test_svg_image_capi_smoke`、`test_svg_types_capi_smoke`、`test_svg_canvas_capi_smoke`、`test_skresources_capi_smoke` を build/run した。

## Phase 31: Header / Naming / Ownership Audit

目的: 大量追加した C ABI の naming、ownership、null handling、callback lifetime を横断監査し、API surface の保守性を上げる。

Tasks:

1. `skia/capi` の newly added symbols を header ごとに棚卸しする。
2. `new` / `delete` / `ref` / `unref` / ownership transfer naming が既存規約と一致するか確認する。
3. callback/provider bridge の release callback、consume semantics、threading assumptions を note に集約する。
4. null input policy と output parameter policy のばらつきを小さくする。

Expected outcome:

- Phase 5A 以降に追加した callback/provider foundation の所有権ルールが、個別 note だけでなく横断ドキュメントから参照できる。
- ABI 名前・lifetime 表現の drift を早期に検出できる。

Progress:

- 2026-05-21: `public-api-phase31-header-naming-ownership-audit-2026-05-21.md` を追加し、`new/delete`、`ref/unref/release`、`borrowed and retained`、`consumes`、callback-scoped pointer、global registration replacement policy、null/output parameter policy を横断ルールとして固定した。Phase 31 時点では即時修正が必要な ABI 不整合は見つからず、`reskia_graphite_release_proc_t` と共有 `reskia_callback_release_proc_t` の使い分けは今後の callback API で注意する cleanup observation として残した。

## Phase 32: Optional Backend Roadmap

目的: coverage 上は `na` として閉じた optional/platform backend 行について、将来実装する場合の入口と条件を分けておく。

Tasks:

1. D3D/Vulkan/Dawn/Metal/platform-private の `na` 行を backend family ごとに再分類する。
2. Reskia の現在の feature flags と dependency modes で実装可能なもの、将来 dependency が必要なものを分ける。
3. C ABI へ出す場合に必要な ownership/design guard を短く記録する。

Expected outcome:

- `na` は放置ではなく、現時点の platform/dependency 境界として説明できる。
- optional backend を将来有効化するときに、coverage matrix を再利用して作業順を立てられる。

Progress:

- 2026-05-21: `public-api-phase32-optional-backend-roadmap-2026-05-21.md` を追加し、GPU/platform backend 系 `na` 77 行を D3D 17、Vulkan 29、Dawn 5、GL loader 13、Metal allocator 2、GPU private/internal 11 に分けた。現時点では coverage status を変更せず、将来実装する場合は backend family ごとに optional bridge、native dependency、smoke target、ownership policy を揃えてから `na` から `covered` へ移す方針にした。

## Phase 33: Full Build Sweep

目的: Phase 29 final freeze 後の代表 build をまとめて確認し、coverage freeze と build health の closeout を行う。

Tasks:

1. prebuilt mode の主要 smoke target を build/run する。
2. source mode の SVG/text/provider 系 smoke target を build/run する。
3. 可能なら `reskia` main target の clean-ish configure/build を再確認する。
4. build unavailable な optional path は、理由と再現条件を closeout note に記録する。

Expected outcome:

- Phase 29 final freeze 後に、少なくとも代表構成で build/link regression がないことを確認できる。
- 残る作業が coverage implementation ではなく、環境依存の full verification debt であることを明確にできる。

Progress:

- 2026-05-21: `public-api-phase33-full-build-sweep-2026-05-21.md` を追加した。`docrefresh-prebuilt` と `docrefresh-source` の `reskia` main target は build 成功。prebuilt GPU tree の `test_gpu_context_capi_smoke` / `test_gpu_surface_capi_smoke` は build/run 成功し、Metal device unavailable は `SKIP` のうえ `PASS`。source SVG tree の `test_svg_image_capi_smoke`、`test_svg_types_capi_smoke`、`test_svg_canvas_capi_smoke`、`test_skresources_capi_smoke` は build/run 成功。coverage generator も `missing 0` / `deferred 0` / `partial 0` / `overcovered 0` を維持した。
