# Post-Phase10 Coverage Expansion Plan

作成時刻: 2026-05-16 19:43:52 JST

Phase 10 では coverage quality / overload polish / deferred small-gap cleanup を完了し、`partial` / `overcovered` / `deferred` は 0 になった。ここから先は generator polish ではなく、Phase 11 開始時点で残っていた `missing` 719 行を、実装価値・依存設計・platform guard の観点で再編して進める。

## Current Snapshot

`docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` の現状:

| status | count |
| --- | ---: |
| `covered` | 2713 |
| `missing` | 143 |
| `false_positive` | 274 |
| `split_covered` | 33 |
| `na` | 154 |
| `no_public_methods_found` | 104 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 0 |

Phase 10 backlog は 185 行で、内訳は `false_positive 162`、`split_covered 13`、`na 10` のみ。実装待ちとしての Phase 10 行は残っていない。

## Missing Distribution

| area | missing | 主な内容 |
| --- | ---: | --- |
| `include/gpu` | 98 | Ganesh / Graphite backend value、context/recorder、platform backend |
| `modules/svg` | 18 | SVG node render helpers、resource/provider loading、OpenType SVG decoder |
| `modules/sksg` | 25 | RenderNode graph primitives/effects、invalidation、nodeAt |
| `include/core` | 1 | global registration |
| `include/codec` | 1 | codec registration |

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

Phase 17A で Graphite `BackendSemaphore` / `TextureInfo::isCompatible` / YUV(A) / options、Ganesh `GrYUVABackendTextureInfo` / `GrYUVABackendTextures`、`GrDriverBugWorkarounds` を covered に移した。Phase 18A では SVG type value accessor、node factory、filter-effect query、`SkSVGLengthContext` helper を covered に移したため、Phase 16 audit snapshot から `missing` は 109 行減少した。

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

## Phase 19: SkSG Graph Polish

目的: `modules/sksg` 25 行の graph/effect factories と getter/iterator surface を整理する。

Priority:

1. Color filter、gradient、image、merge、render effect factories。
2. `GeometryTransform::getTransform`、shader/filter getters の revalidate-safe wrapper。
3. `InvalidationController` begin/end は C iterator API を設計してから実装する。

Expected outcome:

- SkSG graph factory rows を covered に寄せ、iterator-only rows は明示設計済みにする。

## Phase 20: Global Registration Design

目的: `SkCodec::Register` と `SkTypeface::Register` の process-global callback registration を安全に扱う。

Design requirements:

- upstream に unregister がないため、callback owner は process lifetime または disabled callback policy を持つ。
- repeated registration と replacement behavior を明記する。
- `std::unique_ptr<SkStream>` / `SkStreamAsset` transfer と returned `SkCodec` / `SkTypeface` ownership を C ABI に落とす。
- callback release timing を library teardown に依存させない。

Expected outcome:

- まず設計メモと API skeleton を作り、通常の borrowed callback bridge と混同しない。

## Recommended Order

1. Phase 17A: GPU low-risk value wrappers。残数が最大で、既存 GPU smoke に足しやすい。
2. Phase 18A: SVG value accessors / node factories。DOM/render smoke と接続しやすい。
3. Phase 19A: SkSG remaining factories。既存 SkSG holder と smoke を活かせる。
4. Phase 17B/20: callback/provider/global registration design。設計リスクが高いため、value/object rows の後にまとめる。
