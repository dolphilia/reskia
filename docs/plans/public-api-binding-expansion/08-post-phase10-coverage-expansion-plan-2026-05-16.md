# Post-Phase10 Coverage Expansion Plan

作成時刻: 2026-05-16 19:43:52 JST

Phase 10 では coverage quality / overload polish / deferred small-gap cleanup を完了し、`partial` / `overcovered` / `deferred` は 0 になった。ここから先は generator polish ではなく、Phase 11 開始時点で残っていた `missing` 719 行を、実装価値・依存設計・platform guard の観点で再編して進める。

## Current Snapshot

`docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` の現状:

| status | count |
| --- | ---: |
| `covered` | 2506 |
| `missing` | 605 |
| `false_positive` | 164 |
| `split_covered` | 13 |
| `na` | 29 |
| `no_public_methods_found` | 104 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 0 |

Phase 10 backlog は 185 行で、内訳は `false_positive 162`、`split_covered 13`、`na 10` のみ。実装待ちとしての Phase 10 行は残っていない。

## Missing Distribution

| area | missing | 主な内容 |
| --- | ---: | --- |
| `include/gpu` | 169 | Ganesh / Graphite backend value、context/recorder、semaphore、YUV(A)、platform backend |
| `modules/svg` | 191 | SVG nodes、filter/render context、shape-specific setters/helpers |
| `modules/sksg` | 102 | RenderNode graph primitives/effects、invalidation、nodeAt |
| `modules/skparagraph` | 33 | TextStyle paint ID、Paragraph update paint、Block/Placeholder/FontArguments |
| `modules/bentleyottmann` | 24 | low-priority internal geometry helpers |
| `modules/skplaintexteditor` | 23 | editor helper API |
| `modules/skshaper` | 22 | shaping factory/result paths |
| `modules/skottie` | 18 | observers/interceptors/expression callbacks |
| `include/android` | 7 | Android-only framework helpers |
| `include/core` | 5 | registration/subclass hooks |
| `include/utils` | 4 | Sk3DView camera location guarded methods |
| `include/codec` | 2 | codec registration / chunk callback |
| `include/sksl` | 2 | debug trace sink |
| `modules/skresources` | 2 | ResourceProvider / ExternalTrackAsset |
| `modules/skunicode` | 1 | remaining utility helper |

Residual index view:

| bucket | count |
| --- | ---: |
| `real_gap` | 357 |
| `na` | 277 |
| `false_positive` | 177 |
| `P1` | 8 |
| `P2` | 172 |
| `P3` | 459 |
| `P0` | 172 |

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
- Phase 11C の value/query wrapper first pass は完了。残る Phase 11 は Graphite async callback / `insertRecording` / `snap` / `clientImageProvider` / `addFinishInfo` / `makeDeferredCanvas` など所有権設計が必要な行と、Dawn/Vulkan/platform/priv cleanup が中心。

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

## Recommended Order

1. Phase 11A: GPU backend value wrappers。coverage impact が大きく、既存 GPU smoke に足しやすい。
2. Phase 11D: GPU platform/priv NA sweep。283 行の見かけの missing を早めに正規化する。
3. Phase 13A: Paragraph `P1` rows。user-facing で実装価値が高い。
4. Phase 12 SkSG graph expansion。Phase 10 の render node holder を活かせる。
5. Phase 14 callback/provider batch。設計リスクが高いため、上記の value/object API を進めた後にまとめて扱う。
