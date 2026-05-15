# 00 Current State and Roadmap

- 作成日: 2026-05-14
- 作業開始時刻: 2026-05-14 13:33:02 JST
- 参照 Skia ref: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- coverage 入力: `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- 生成スクリプト: `scripts/generate_public_api_coverage.py`

## 目的

Skia の公開クラスについて、公開メソッドと static factory/helper を可能な限り C ABI に露出するための長期計画を定義する。

前回までの安全性改善により、NULL 規約、所有権、callback lifetime、borrowed pointer の扱いは大きく改善された。この計画では、その安全性を維持したまま未バインディング領域を段階的に拡張する。

## 現行 coverage

2026-05-14 Phase 0 更新後の `public-api-coverage-matrix.csv` の集計:

| 指標 | 件数 |
| --- | ---: |
| matrix rows | 3421 |
| class/struct 候補 | 469 |
| method rows | 3317 |
| `covered` | 1779 |
| `partial` | 2 |
| `missing` | 1538 |
| `no_public_methods_found` | 104 |
| coverage 概算 | 53.6% |

coverage は機械的な関数名照合であり、実装品質や overload 完全性を保証しない。作業前には必ず upstream header、既存 `skia/capi`、必要なら `skia/handles` を確認する。

Phase 0 で `scripts/generate_public_api_coverage.py` を再実行し、`SkAutoCanvasRestore::restore` は `covered` に更新された。あわせて deleted special member、template method、template class、copy/move assignment operator、`SK_TRIVIAL_ABI` 由来の誤検出を generator 側で減らした。

## 未対応領域

| area | missing | 見方 |
| --- | ---: | --- |
| `include/gpu` | 408 | 最大領域。backend/platform 依存が強く、CMake option と smoke test が必須。 |
| `modules/svg` | 364 | DOM node 全面公開ではなく、まず `SkSVGDOM` の load/render を入口にする。 |
| `modules/skparagraph` | 256 | 依存条件が重い。`SkUnicode`、`FontCollection`、style、builder、paragraph の順で進める。 |
| `modules/sksg` | 122 | 既存は Scene の最小 bridge。全面化には所有権モデル設計が必要。 |
| `include/core` | 80 | coverage は高いが、operator、subclass hook、legacy API が混ざる。triage 台帳から次候補を選ぶ。 |
| `include/utils` | 79 | `Sk3DView`、parse、font builder、canvas helper など。個別価値で選別する。 |
| `modules/skunicode` | 48 | paragraph/shaper の基盤。factory と query API から始める。 |
| `modules/skottie` | 39 | `Animation` 基本 API はある。slot/property/resource provider が次候補。 |
| `modules/skplaintexteditor` | 26 | optional/editor 向け。paragraph 後の候補。 |
| `modules/bentleyottmann` | 24 | 内部寄り。公開価値を要確認。 |
| `modules/skshaper` | 23 | HarfBuzz/CoreText/skunicode 条件と合わせて進める。 |
| `include/ports` | 18 | platform 依存が強い。既定 build で使える対象を分離する。 |

## 優先順位の原則

1. 既存 C API の設計と ownership 規約に自然に乗るものを優先する。
2. `include/core` / `include/effects` の残件は、coverage を上げやすいが誤検出が多いため、実装前に triage を更新する。
3. optional module は、C API 関数だけを追加しない。CMake option、source registration、feature guard、smoke test を同じ単位で扱う。
4. GPU は surface/context の実用経路を先に固め、backend object の全面公開は段階化する。
5. callback、global registration、subclass hook は設計フェーズを挟む。
6. C++ operator、copy/move assignment、protected/private hook、template convenience は原則として C ABI 対象外または named API 化を検討する。

## Phase 0: matrix と triage の更新

目的: 実装対象を誤検出から切り離し、作業単位を安定させる。

作業:

- `python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia` を実行し、matrix を最新化する。
- `include/core` / `include/effects` の triage を現行 142 + 5 missing に追従する。
- optional module 用の triage を追加する。候補:
  - `public-api-gpu-missing-triage.csv`
  - `public-api-svg-missing-triage.csv`
  - `public-api-paragraph-unicode-shaper-missing-triage.csv`
  - `public-api-skottie-sksg-resources-missing-triage.csv`
- generator の誤検出を減らす。
  - inline method body の後続 access specifier
  - deleted/defaulted special member
  - operator の named API 対応
  - template convenience
  - macro 由来の疑似 class 名

受け入れ条件:

- matrix 再生成後に差分理由が説明できる。
- `real_gap`、`na`、`false_positive` が作業対象ごとに分離される。
- 以後の実装 batch が triage から選べる。

### Phase 0 progress 2026-05-14

実施済み:

- `scripts/generate_public_api_coverage.py` を更新し、以下の明確な誤検出を抑制した。
  - `SK_TRIVIAL_ABI` を API macro として扱う。
  - template class/struct 定義を coverage 対象から除外する。
  - template method を coverage 対象から除外する。
  - `= delete` の special member を coverage 対象から除外する。
  - `operator=` を coverage 対象から除外する。
- `public-api-coverage-matrix.csv` を再生成した。
- `public-api-core-effects-missing-triage.csv` を現行 matrix の `include/core` / `include/effects` missing 83 行に同期した。既存分類は可能な限り引き継ぎ、未分類行は `untriaged` とした。
- optional module 用 triage 台帳を追加した。
  - `public-api-gpu-missing-triage.csv`: 408 行
  - `public-api-svg-missing-triage.csv`: 365 行
  - `public-api-paragraph-unicode-shaper-missing-triage.csv`: 327 行
  - `public-api-skottie-sksg-resources-missing-triage.csv`: 178 行

残作業:

- optional module の `untriaged` 行を、実装フェーズごとに `real_gap`、`na`、`false_positive` へ分類する。
- core/effects の `untriaged` 52 行を Phase 1 着手前に分類する。

### Phase 0 triage completion 2026-05-14

残っていた `untriaged` 行を分類した。

| triage file | rows | real_gap | na | false_positive | untriaged |
| --- | ---: | ---: | ---: | ---: | ---: |
| `public-api-core-effects-missing-triage.csv` | 83 | 55 | 8 | 20 | 0 |
| `public-api-gpu-missing-triage.csv` | 408 | 322 | 67 | 19 | 0 |
| `public-api-svg-missing-triage.csv` | 365 | 122 | 107 | 136 | 0 |
| `public-api-paragraph-unicode-shaper-missing-triage.csv` | 327 | 285 | 27 | 15 | 0 |
| `public-api-skottie-sksg-resources-missing-triage.csv` | 178 | 99 | 53 | 26 | 0 |

分類基準:

- `real_gap`: 該当フェーズで C ABI として公開する価値がある public method / static factory / helper。
- `na`: public header 上には出るが、現在の platform/backend 条件、subclass/callback 設計、内部 hook、または初期実用経路から外れるため当面対象外。
- `false_positive`: destructor、C++ operator convenience、macro 展開、既存 release/delete/ref/unref で表現済みの lifetime など、直接の C ABI 関数として追うべきではないもの。

これにより Phase 1 以降の実装候補は、各 triage CSV の `real_gap` と `priority` から選べる状態になった。

## Phase 1: Core / Effects の低リスク残件

目的: 既存 coverage が高い領域の実 gap を小さくする。

候補:

- `SkRTreeFactory` / `SkBBHFactory` 周辺
  - `SkPictureRecorder` や serialization 経路で使える concrete factory として価値がある。
  - abstract base の destructor/operator は対象外に近い。
- `SkNullWStream`
  - constructor は `SkNullWStream_new` がある。
  - `write`、`flush`、`bytesWritten` が matrix 上では残るため、既存 `SkWStream_*` との対応を確認する。
- `SkDrawLooper`
  - 古い API で優先度は低い。
  - `canComputeFastBounds`、`computeFastBounds`、`asABlurShadow`、flattenable helper は実 gap だが、需要確認後に扱う。
- `SkBlurMaskFilter::MakeEmboss`
  - `SK_SUPPORT_LEGACY_EMBOSSMASKFILTER` guard があるため、既定 build では `na` 扱いが妥当。

受け入れ条件:

- 対象 API の所有権が header コメントか型で明確である。
- invalid input smoke を追加または既存 smoke に追記する。
- prebuilt 既定 build で configure/build が通る。

### Phase 1 progress 2026-05-14

低リスクで既存 C API 型に自然に載せられる core 残件から、次を実装した。

- `SkFontStyle::Normal` / `Bold` / `Italic` / `BoldItalic`
- `SkFont::setTypeface`
- `SkString::endsWith(const char[])` / `endsWith(char)`
- `SkNullWStream::write` / `flush` / `bytesWritten`
- `SkYUVAInfo::toYUVALocations`
- `SkYUVAPixmaps::toYUVALocations`

`public-api-coverage-matrix.csv` を再生成し、全体 missing は `1538` から `1526` へ減った。`include/core` / `include/effects` の triage 台帳は現行 matrix の missing 行に同期し、`83` 行から `71` 行へ更新した。内訳は `real_gap 43`、`na 8`、`false_positive 20`、`untriaged 0`。

検証:

- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `cmake -S skia -B skia/cmake-build-codex-phase1-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase1-tests --target test_wstream_invalid_input_smoke test_sampling_unpremul_string_stroke_trace_invalid_input_smoke test_font_style_set_invalid_input_smoke test_font_invalid_input_smoke test_yuva_pixmaps_invalid_input_smoke test_yuva_info_invalid_input_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase1-tests -R 'c_skia_(wstream|sampling_unpremul_string_stroke_trace|font_style_set|font|yuva_pixmaps|yuva_info)_invalid_input_smoke' --output-on-failure`

次の Phase 1 batch は、P2 の callback/global registration を避け、P3 の value comparison/operator helper または legacy flattenable helper から選ぶ。`SkGraphics::SetImageGeneratorFromEncodedDataFactory` と `SkTypeface::Register` は callback ownership 設計が必要なため、Phase 1 の即時実装対象からは外す。

### Phase 1 continuation 2026-05-14

網羅率を先に上げるため、既存の value wrapper と smoke に載せられる operator/helper を追加で実装した。

- `SkV2` / `SkV3` / `SkV4` の comparison、unary/binary arithmetic、assign arithmetic
- `SkPoint3::operator-` / `operator+=` / `operator-=`
- `SkSamplingOptions::operator==` / `operator!=`
- `SkFontMetrics::operator==`
- `SkRTreeFactory::operator()`
- `SkPathMeasure::dump`

operator 系の C API 名は `equals`、`notEquals`、`negate`、`add`、`subtract`、`multiply`、`addAssign`、`subtractAssign`、`multiplyAssign` のように C ABI で明確な名前へ正規化した。これに合わせて `generate_public_api_coverage.py` の operator token 正規化も更新した。

`public-api-coverage-matrix.csv` を再生成し、全体 missing は `1491` まで減った。`include/core` / `include/effects` の missing は `36` 行、triage 内訳は `real_gap 2`、`na 14`、`false_positive 20`、`untriaged 0`。残る `real_gap` は callback/global registration 設計が必要な `SkGraphics::SetImageGeneratorFromEncodedDataFactory` と `SkTypeface::Register` のみ。`SkDrawLooper` は `SK_SUPPORT_LEGACY_DRAWLOOPER` guard の unsupported legacy API として `na` に更新した。

callback/global registration は Phase 1 では実装しない。設計メモは `01-callback-global-registration-design.md` に固定し、実装は Phase 3 の SVG DOM 最小公開後、Phase 5 の skottie/skresources provider 実装前に `Phase 5A: Callback / Resource Provider Foundation` としてまとめる。

追加検証:

- `ctest --test-dir skia/cmake-build-codex-phase1-tests -R 'c_skia_(wstream|sampling_unpremul_string_stroke_trace|font_style_set|font|yuva_pixmaps|yuva_info|vector|value_transform_string_stroke_trace|font_arguments_metrics|auto_canvas_restore_bbox|contour_path_measure)_invalid_input_smoke' --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`

## Phase 2: GPU C API の実用入口

目的: `include/gpu` の全面公開ではなく、Ganesh/Graphite の context、surface、backend object の最小実用経路を安定させる。

現状:

- `skia/capi/sk_gpu_context.*` は Ganesh/Graphite context 作成と release を提供している。
- `skia/capi/sk_surface_gpu.*` は Ganesh/Graphite surface 作成と backend texture/render target wrap を提供している。
- 2026-05-14 に Phase 2 着手。`GrDirectContext` lifecycle/query/cache/flush の低リスク subset は C API に追加済み。
- matrix 上は `GrDirectContext` の backend texture/state/callback 系、`GrBackendTexture`、`GrBackendRenderTarget`、`GrBackendSemaphore`、`GrBackendFormat` が主な残作業として残る。

優先順:

1. `GrDirectContext` lifecycle/query/cache/flush
   - 完了: `resetContext`, `abandonContext`, `abandoned`, `isDeviceLost`, `oomed`
   - 完了: `releaseResourcesAndAbandonContext`, cache limit/usage query/set, GPU resource purge/cleanup
   - 完了: simple `flush`, `flushAndSubmit`, `submit`, `checkAsyncWorkCompletion`, `dumpMemoryStatistics`, `supportsDistanceFieldText`, `storeVkPipelineCacheData`
   - 残: `wait`, `threadSafeProxy`, `directContextID`, backend texture create/update/delete/state, callback 付き finished proc 系、image/surface 指定 flush の ABI 設計
2. `GrBackendTexture` / `GrBackendRenderTarget` value wrapper
   - opaque wrapper を用意し、backend tag と validity を C ABI 側で表す。
   - 既存の `const void *backend_texture` pass-through は互換維持しつつ、新 API へ誘導する。
3. `GrBackendFormat` / `GrBackendSemaphore`
   - backend 固有 struct を C ABI に直接晒しすぎない。
   - Metal/Vulkan/Mock ごとに feature guard を切る。
4. Graphite `Context` / `Recorder` / `Recording`
   - 既存 `Reskia_GraphiteContext_MakeRecorder` と `InsertRecordingAndSubmit` を起点にする。

除外または後回し:

- Direct3D は現行 platform/build 条件と優先度から後回し。
- Vulkan backend object は VMA/Vulkan dependency とセットで扱う。
- Graphite Dawn は `RESKIA_ENABLE_GPU_DAWN` と dependency discovery が安定してから扱う。

受け入れ条件:

- Apple + Metal + Ganesh の smoke が通る。
- Graphite を触る場合は Graphite smoke も通る。
- backend object の lifetime と mutability が C API コメントで明示される。
- CMake option 無効時に C API source が未解決 symbol を出さない。

Phase 2 着手時の検証:

- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`
- `cmake -S skia -B skia/cmake-build-codex-phase2-gpu-metal -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON -DRESKIA_ENABLE_GPU_GANESH=ON -DRESKIA_ENABLE_GPU_METAL=ON`
- `cmake --build skia/cmake-build-codex-phase2-gpu-metal --target test_gpu_context_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase2-gpu-metal -R c_skia_gpu_context_capi_smoke --output-on-failure`

Phase 2 着手時の台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1458`, `covered=1856`, `partial=3`, `no_public_methods_found=104`
- `public-api-gpu-missing-triage.csv`: `GrDirectContext` の covered 33 行を削除し、残 `375` 行
- Metal `.mm` source の ARC 設定が既存 GPU 計画メモと逆向きだったため、`RESKIA_ENABLE_GPU_METAL=ON` 時は `-fobjc-arc` でコンパイルする設定に修正した。

### Phase 2 continuation 2026-05-14

backend object の C ABI 足場として、`GrBackendFormat` / `GrBackendTexture` / `GrBackendRenderTarget` の owned value wrapper を追加した。既存 `Reskia_GaneshSurface_WrapBackendTexture` / `WrapBackendRenderTarget` の `reskia_gpu_backend_*_handle_t` は維持し、新 wrapper から borrowed handle を生成する API を追加して互換性を保つ。

追加済み:

- `GrBackendFormat`: default/copy/mock/Metal factory、equality、backend、textureType、channelMask、mock query、`makeTexture2D`、`isValid`
- `GrBackendTexture`: default/copy/mock factory、width/height、mipmapped、hasMipmaps/hasMipMaps、backend、textureType、backend format、protected/valid query、same-texture query、borrowed handle 化
- `GrBackendRenderTarget`: default/copy/mock factory、width/height、sample/stencil、backend、framebuffer-only、backend format、protected/valid query、borrowed handle 化
- `GrRecordingContext`: abandoned、surface/image color type support、texture/render-target size、protected content、sample count query
- `GrContextThreadSafeProxy`: release、default/compressed backend format、sample count、valid/equality query
- `GrDirectContext`: `threadSafeProxy` と opaque `DirectContextID` wrapper

残すもの:

- `GrDirectContext::createBackendTexture` / `updateBackendTexture` / `deleteBackendTexture` は callback finished proc と backend resource lifetime の設計が必要なため、Phase 5A の callback 規約に寄せる。
- `GrContextThreadSafeProxy::createCharacterization` は `GrSurfaceCharacterization` wrapper とセットで扱う。
- Vulkan / Metal の native texture info accessor と mutable texture state は backend-specific ABI を切ってから追加する。
- Phase 2 の残件分類と `GrSurfaceCharacterization` / backend-specific ABI 方針は `02-phase2-gpu-residual-design.md` を正とする。

検証:

- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `cmake --build skia/cmake-build-codex-phase2-gpu-metal --target test_gpu_context_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase2-gpu-metal -R c_skia_gpu_context_capi_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1396`, `covered=1918`, `partial=3`, `no_public_methods_found=104`
- `public-api-gpu-missing-triage.csv`: covered 62 行を削除し、残 `313` 行

### Phase 2 residual planning 2026-05-14

Phase 2 の残 P1 は、実装単位ごとに triage CSV の note を更新した。

- Phase 2B: no-callback allocation、`GrMockOptions`、`GrSurfaceCharacterization`、`precompileShader` など次 batch 候補
- Phase 2C: `GrContextOptions`、`SkCapabilities` など wrapper 方針待ち
- Phase 2D: semaphore、mutable texture state、Metal/Vulkan native info など backend-specific ABI 待ち
- Phase 5A: finished proc / upload callback / semaphore delete policy など callback foundation 待ち

詳細は `02-phase2-gpu-residual-design.md` に切り出した。現時点で追加実装へ進むなら、`GrMockOptions` と `GrSurfaceCharacterization` wrapper を先に入れ、その後 `createBackendTexture` の no-callback allocation overload と `precompileShader` を追加する順がよい。

## Phase 3: SVG DOM の最小公開

目的: `modules/svg` / `include/svg` の missing に対して、まず実用入口である `SkSVGDOM` を C API 化する。

優先 API:

- `SkSVGDOM::MakeFromStream`
- `SkSVGDOM::setContainerSize`
- `SkSVGDOM::containerSize`
- `SkSVGDOM::render`
- `SkSVGDOM::findNodeById`

設計方針:

- 全 DOM node を一気に公開しない。
- `SkSVGNode` は初期段階では borrowed opaque pointer として扱い、node mutation API は後続フェーズへ分離する。
- stream 入力は既存 `SkStream` / `SkMemoryStream` C API と合わせる。
- resource provider は `skresources` と skottie の入力解決にも関係するため、単独で設計する。

受け入れ条件:

- `RESKIA_ENABLE_SKSG` / `RESKIA_ENABLE_SKOTTIE` と独立して SVG DOM の source registration 条件が説明できる。
- 最小 SVG 文字列または stream から render する smoke がある。
- `SkSVGDOM` の ref/unref/release 規約が既存 `sk_sp` wrapper と整合する。

### Phase 3 progress 2026-05-14

`SkSVGDOM` の最小 load/render/query API を C ABI に追加した。

追加済み:

- `SkSVGDOM_MakeFromStream`
- `SkSVGDOM_ref` / `SkSVGDOM_unref` / `SkSVGDOM_release`
- `SkSVGDOM_getRoot`
- `SkSVGDOM_setContainerSize`
- `SkSVGDOM_containerSize`
- `SkSVGDOM_findNodeById`
- `SkSVGDOM_render`
- `SkSVGCanvas_Make`
- `SkSVGNode_tag`
- `SkSVGDOM_renderNodeById`
- `SkSVGNode_setAttributeString`

`SkSVGNode` / `SkSVGSVG` は、DOM が所有する borrowed opaque pointer として扱う。`findNodeById` の戻り値を識別するため `SkSVGNode::tag` を read-only query として公開した。既存 DOM node の軽い mutation として `SkSVGNode::setAttribute(const char*, const char*)` だけを `SkSVGNode_setAttributeString` で公開した。node factory、appendChild、`SkSVGValue` overload はまだ公開しない。

`SkSVGDOM::renderNode` は full `SkSVGPresentationContext` ABI を公開せず、Phase 3 では default context helper の `SkSVGDOM_renderNodeById` として公開した。custom presentation context は後続の render context / resource provider 設計へ残す。

CMake registration は `APPLE AND TARGET svg` に限定した。これは `RESKIA_ENABLE_SKSG` / `RESKIA_ENABLE_SKOTTIE` とは独立しているが、既定 `prebuilt` mode の `libsvg.a` は `SkShaper` / `SkUnicode` の静的リンク解決が揃っていないため、現時点では source mode の `svg` target が存在する場合だけ `sk_svg_dom.cpp` を `reskia` に組み込む。`prebuilt` 既定 build はこの条件により未解決 symbol を出さずに通る。

検証:

- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `cmake -S skia -B skia/cmake-build-codex-phase3-svg-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_dom_capi_smoke -j 8`
- `cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_canvas_capi_smoke -j 8`
- `cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_dom_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase3-svg-source -R c_skia_svg_dom_capi_smoke --output-on-failure`
- `ctest --test-dir skia/cmake-build-codex-phase3-svg-source -R 'c_skia_svg_(dom|canvas)_capi_smoke' --output-on-failure`
- `ctest --test-dir skia/cmake-build-codex-phase3-svg-source -R c_skia_svg_dom_capi_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1385`, `covered=1926`, `partial=6`, `no_public_methods_found=104`
- `include/svg`: `SkSVGCanvas::Make` の 1 行が `covered`
- `modules/svg`: `SkSVGDOM` の 6 行と `SkSVGNode::tag` の 1 行が `covered`。`SkSVGDOM::renderNode` と `SkSVGNode::setAttribute` overload は helper により `partial`
- `public-api-svg-missing-triage.csv`: covered / helper 実装済み行を削除し、残 `356` 行。内訳は `real_gap 106`、`na 112`、`false_positive 138`

注意点:

- coverage generator の機械的な近似により、`SkSVGDOM_findNodeById` が `modules/sksg::Node` の reference としても記録される。`sksg` 側の `Node::revalidate` / `invalidate` は未実装のままであり、今回の SVG DOM API で covered になったわけではない。
- `SkSVGNode::hasChildren` と `SkSVGNode::ComputeViewboxMatrix` は実ヘッダ上 protected なので、台帳では `false_positive` として扱う。

## Phase 4: Paragraph / Unicode / Shaper

目的: text layout の実用 API を C ABI として使える状態にする。

前提:

- `RESKIA_ENABLE_SKPARAGRAPH=ON` は現在 Apple + `RESKIA_DEPS_MODE=source` + HarfBuzz 前提で制約が重い。
- HarfBuzz、ICU、ICU4X、libgrapheme の有無により機能縮退がある。
- `sk_text_blob_builder_run_handler.cpp` はあるが、paragraph module の実 API はほぼ未公開である。

優先順:

1. `SkUnicode`
   - `Make`
   - `MakeIcuBasedUnicode`
   - `MakeLibgraphemeBasedUnicode`
   - `MakeIcu4xBasedUnicode`
   - flag helper
   - UTF-8/UTF-16 conversion helper
2. `FontCollection`
   - font manager 設定
   - fallback query
3. `ParagraphStyle` / `StrutStyle`
   - scalar/enum/bool getter/setter
   - string/UTF-16 setter は別設計で扱う
4. `TextStyle`
   - scalar/enum/bool/color/font family getter/setter
   - foreground/background paint ownership を先に決める
5. `ParagraphBuilder`
   - `make`
   - `pushStyle`
   - `pop`
   - `addText`
   - `addPlaceholder`
   - `Build`
6. `Paragraph`
   - `layout`
   - `paint`
   - metrics getter
   - hit test / line metrics は配列出力設計後に追加

受け入れ条件:

- source mode + paragraph 有効 build が configure/build できる。
- 文字列入力の encoding と lifetime が明示される。
- paragraph smoke が C API 経由で作成、layout、paint まで到達する。

### Phase 4 progress 2026-05-15

`SkUnicode` の土台 API から着手した。個別 backend factory は `skunicode` target の実装ソース追加条件に依存するため、この batch では `SkUnicode::Make()` 経由と instance helper に限定し、`TARGET skunicode` が存在する source-mode build だけで C API source を組み込む。

追加済み:

- `SkUnicode_Make`
- `SkUnicode_MakeIcuBasedUnicode`
- `SkUnicode_MakeClientBasedUnicode`
- `SkUnicode_MakeLibgraphemeBasedUnicode`
- `SkUnicode_MakeIcu4xBasedUnicode`
- `SkUnicode_delete`
- `SkUnicode_copy`
- `SkUnicode_toUpper`
- `SkUnicode_isControl`
- `SkUnicode_isWhitespace`
- `SkUnicode_isSpace`
- `SkUnicode_isTabulation`
- `SkUnicode_isHardBreak`
- `SkUnicode_isEmoji`
- `SkUnicode_isIdeographic`
- `SkUnicode_hasTabulationFlag`
- `SkUnicode_hasHardLineBreakFlag`
- `SkUnicode_hasSoftLineBreakFlag`
- `SkUnicode_hasGraphemeStartFlag`
- `SkUnicode_hasControlFlag`
- `SkUnicode_hasPartOfWhiteSpaceBreakFlag`
- `SkUnicode_convertUtf16ToUtf8`
- `SkUnicode_convertUtf8ToUtf16`
- `SkUnicode_makeBidiIteratorUtf8`
- `SkUnicode_makeBidiIteratorUtf16`
- `SkBidiIterator_delete`
- `SkBidiIterator_getLength`
- `SkBidiIterator_getLevelAt`
- `SkUnicode_makeBreakIterator`
- `SkUnicode_makeBreakIteratorWithLocale`
- `SkBreakIterator_delete`
- `SkBreakIterator_first`
- `SkBreakIterator_current`
- `SkBreakIterator_next`
- `SkBreakIterator_status`
- `SkBreakIterator_isDone`
- `SkBreakIterator_setTextUtf8`
- `SkBreakIterator_setTextUtf16`
- `SkUnicode_getBidiRegions`
- `SkUnicode_getWords`
- `SkUnicode_getUtf8Words`
- `SkUnicode_getSentences`
- `SkUnicode_computeCodeUnitFlagsUtf8`
- `SkUnicode_computeCodeUnitFlagsUtf16`
- `SkUnicode_reorderVisual`
- `SkParagraph_FontCollection_*`
  - create/ref/unref/release
  - font manager setters
  - fallback manager/typeface helpers
  - `findTypefaces`
  - fallback enable/disable and cache access/clear
- `SkParagraph_ParagraphCache_*`
  - create/delete
  - abandon/reset/printStatistics/turnOn/count
- `SkParagraph_StrutStyle_*`
  - create/copy/delete/equals
  - font families count/index/set
  - font style, font size, height, leading, strut flags
- `SkParagraph_ParagraphStyle_*`
  - create/copy/delete/equals
  - strut/text style get/set
  - text direction/align, max lines, ellipsis, height, text height behavior
  - hinting, replace-tab, rounding-hack helpers
- `SkParagraph_TextStyle_*`
  - create/copy/delete/cloneForPlaceholder
  - color, foreground/background paint copy getter/setter and presence clear
  - decoration scalar/enum/color helpers
  - font style, font size, font families, typeface ref/set, locale
  - baseline shift, height, half leading, spacing, font metrics, placeholder
  - shadow value struct helper、shadow count/index/array/add/reset
  - font-feature count/array/add/reset
  - font arguments optional set/presence/clear
- `SkParagraph_ParagraphBuilder_*`
  - `make`
  - `pushStyle` / `pop` / `peekStyle`
  - UTF-8 / UTF-16 `addText`
  - primitive placeholder helper
  - `Build`
  - `getText` / `getParagraphStyle`
  - word/grapheme/line-break array setters
  - `SetUnicode` consuming helper and `Reset`
- paragraph value helper
  - `PositionWithAffinity` make helper
  - `TextBox` make helper
  - `PlaceholderStyle` make/equals helper
  - `LineMetrics` make helper
- `SkParagraph_Paragraph_*`
  - owned paragraph delete
  - layout / SkCanvas paint
  - width/height/intrinsic/baseline/line/unresolved glyph getter
  - line metrics array helper
  - text box array helpers for range/placeholders
  - glyph coordinate, word boundary, unresolved codepoint array helper
  - text align and font size update helpers
- `SkParagraph_TypefaceFontProvider_*`
  - create/ref/unref/release
  - `SkFontMgr` handle ref bridge for `FontCollection`
  - typeface registration with optional alias
  - family/style query wrappers and null-returning SkFontMgr override wrappers
- `SkParagraph_TypefaceFontStyleSet_*`
  - family name / alias query
  - append typeface helper

設計メモ:

- `reskia_unicode_t` は `std::unique_ptr<SkUnicode>` から release した owned pointer として扱い、`SkUnicode_delete` で破棄する。
- `reskia_bidi_iterator_t` / `reskia_break_iterator_t` も `std::unique_ptr` から release した owned pointer として扱い、それぞれ `SkBidiIterator_delete` / `SkBreakIterator_delete` で破棄する。
- UTF-16 C ABI は `uint16_t*` / unit count で表す。`convertUtf8ToUtf16` は必要 unit 数を返し、出力 buffer は任意とする。
- vector 出力系 API は caller-owned array にコピーし、戻り値で必要要素数を返す。`dst == NULL` は count query として扱う。
- `SkBreakIterator::setText`、`SkUnicode::makeBidiIterator`、`SkUnicode::computeCodeUnitFlags` は UTF-8/UTF-16 別 C ABI 名で公開したため、coverage generator 上は overload-specific `partial` として残る。
- `SkUnicode::extractBidi` は public static 宣言があるが、この source 構成では実体 symbol がリンクされないため、backend factory と同じく feature/linkage 判定が必要な残件として残す。
- `SkUnicode_MakeIcuBasedUnicode` / `MakeClientBasedUnicode` / `MakeLibgraphemeBasedUnicode` / `MakeIcu4xBasedUnicode` は、`skunicode` target の compile definition を `reskia` 側にも伝播し、該当 backend が有効な場合だけ実体を呼ぶ。無効な backend は C ABI 関数自体は存在するが `NULL` を返す。
- `FontCollection` は `sk_font_mgr_t` handle から `sk_sp<SkFontMgr>` を borrow して設定する。caller の font manager handle 所有権は奪わない。
- `ParagraphStyle` / `StrutStyle` / `TextStyle` は heap-owned value wrapper とし、`*_delete` で破棄する。value getter が C++ reference を返すものは、C ABI では copy または count/index/array accessor で表す。
- `TextStyle` の foreground/background `SkPaint` getter は owned copy を返し、既存 `SkPaint_delete` で破棄する。setter は caller の `SkPaint` を copy し、所有権を奪わない。
- `TextStyle` の `TextShadow` と `FontFeature` vector は C value struct の caller-owned array にコピーし、戻り値で必要要素数を返す。
- `TextStyle::getFontArguments` は paragraph module 内部の `FontArguments` が private wrapper で `SkFontArguments` へ戻せないため、現段階では optional が設定済みかどうかの presence query として公開した。`setFontArguments` は core `SkFontArguments` から copy し、`clearFontArguments` は `std::nullopt` に戻す。
- `TextStyle` の `ParagraphPainter::PaintID` 系 API は custom painter callback 設計が必要なため、Phase 5A の callback/provider foundation 後にまとめる。
- `ParagraphBuilder` / `Paragraph` は `std::unique_ptr` から release した owned pointer とし、`*_delete` で破棄する。
- `ParagraphBuilder::make` は `FontCollection` の raw pointer から `sk_ref_sp` で追加参照を取る。caller の `FontCollection` 所有権は維持される。
- `Paragraph::paint` はまず `SkCanvas*` 版だけ公開した。`ParagraphPainter*` 版は custom painter callback 設計が必要なため後続に残す。
- `TypefaceFontProvider` は `SkFontMgr` 派生だが、C ABI では paragraph 専用 opaque pointer として保持する。`SkParagraph_TypefaceFontProvider_refFontMgr` は追加参照を持つ `sk_font_mgr_t` handle を返し、既存 `FontCollection` API へ渡せる。provider 本体の所有権は caller が `release` / `unref` で管理する。
- `TypefaceFontProvider` の `onMakeFrom*` / `onLegacyMakeTypeface` は upstream 実装が nullptr を返す override であり、C ABI でも invalid/unsupported 経路は 0 を返す。
- `TypefaceFontStyleSet` は standalone owner としては公開せず、`TypefaceFontProvider_onMatchFamily` が返す `sk_font_style_set_t` に対する paragraph-specific helper と、既存 `SkFontStyleSet_*` API の組み合わせで扱う。
- `ParagraphCache` は owned cache を `SkParagraph_ParagraphCache_new/delete` で扱えるようにし、`FontCollection_getParagraphCache` から得る borrowed cache に対しても同じ helper を使えるようにした。`updateParagraph` / `findParagraph` / `isPossiblyTextEditing` は `ParagraphImpl*` を要求する内部寄り API なので、現段階では対象外寄りとして残す。
- `PositionWithAffinity`、`TextBox`、`PlaceholderStyle`、`LineMetrics` は C value struct として表す。constructor 相当の helper は field validation と初期化だけを行い、heap allocation はしない。

検証:

- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `cmake -S skia -B skia/cmake-build-codex-phase4-unicode-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase4-unicode-source --target test_unicode_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase4-unicode-source -R c_skia_unicode_capi_smoke --output-on-failure`
- `cmake -S skia -B skia/cmake-build-stability-skparagraph-tests -DRESKIA_DEPS_MODE=source -DRESKIA_ENABLE_SKPARAGRAPH=ON -DRESKIA_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build skia/cmake-build-stability-skparagraph-tests --target test_paragraph_font_collection_capi_smoke test_paragraph_style_capi_smoke test_paragraph_text_style_capi_smoke test_paragraph_builder_capi_smoke test_paragraph_typeface_font_provider_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-stability-skparagraph-tests -R 'c_skia_paragraph_(font_collection|style|text_style|builder|typeface_font_provider)_capi_smoke' --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1135`, `covered=2167`, `partial=15`, `no_public_methods_found=104`
- `modules/skunicode`: 48 行中 `covered 41`、`partial 6`、`missing 1`
- `modules/skparagraph`: `covered 200`、`partial 3`、`missing 53`
- `public-api-paragraph-unicode-shaper-missing-triage.csv`: covered 行を削除し、constructor / inherited generic wrapper / value helper 実装済み行を分類し直した結果、残 `77` 行。内訳は `real_gap 41`、`na 15`、`false_positive 21`
- `modules/skunicode` の残件は 7 行。`partial` は UTF-8/UTF-16 別名で公開済みの overload 6 行、`missing` は `extractBidi` 1 行。
- `modules/skparagraph` の triage 上の real gap は 18 行。大きい塊は `TextStyle` の `ParagraphPainter::PaintID` 周辺 4 行、`Paragraph` の custom paint update 周辺 3 行、`FontArguments` の wrapper/clone 周辺、`Block` / `StyleMetrics` / `Placeholder` の内部 value helper 周辺である。これらは custom painter、private wrapper、または internal layout model に近く、Phase 5A の callback/provider foundation 後または明確な利用経路が出てから扱う。

## Phase 5: Skottie / skresources / sksg

目的: 既存 minimal bridge を実用 API に拡張する。

## Phase 5A: Callback / Resource Provider Foundation

目的: Phase 1 で残した callback/global registration と、optional module の provider / observer callback を同じ C ABI 規約で実装する。

実行位置: Phase 3 の SVG DOM 最小公開後、Phase 5 の skottie/skresources/sksg 拡張に入る前に行う。Phase 4 の paragraph/unicode/shaper は依存が重いため、Phase 5A と並行または前後してよいが、callback/provider API を追加する場合は Phase 5A の規約を先に適用する。

対象:

- `SkGraphics::SetImageGeneratorFromEncodedDataFactory`
- `SkTypeface::Register`
- skresources image/data/font resource provider
- skottie resource provider
- skottie property observer / text property callback
- SVG DOM resource provider hook が必要になった場合の provider bridge

方針:

- 詳細設計は `01-callback-global-registration-design.md` を正とする。
- callback は function pointer + `void *user_data` + optional release proc の形に統一する。
- global registration は初期化時 API とみなし、登録解除不能な Skia API は replacement のみ提供する。
- callback が返す object の ownership transfer は API ごとに header コメントで明示する。

受け入れ条件:

- callback context release が一度だけ走ることを smoke で検証する。
- callback failure path を smoke で検証する。
- registration replacement の旧 context release を smoke で検証する。
- SkGraphics、SkTypeface、skresources/skottie provider の説明文と failure mode が同じ語彙で揃っている。

Skottie:

- 既存 `Skottie_Animation_*` は基本 API を提供している。
- 次候補は `SlotManager`、`PropertyObserver`、`PropertyHandle`、resource provider、text shaper。
- callback observer は lifetime と thread を明示するまで実装しない。

skresources:

- SVG と skottie の resource 解決に関係する。
- 単独で class を広く公開するより、画像/フォント/data resource provider の C ABI を先に設計する。

sksg:

- 既存 `SkSG_Scene_*` は smoke/minimal bridge。
- `Node` / `RenderNode` / `GeometryNode` / `PaintNode` の全面公開には graph ownership と invalidation model が必要。
- 当面は Scene 作成、render、revalidate、単純 geometry の追加に絞る。

受け入れ条件:

- optional module ごとに feature guard と smoke がある。
- callback/observer API は context lifetime と deregistration を文書化する。
- skottie と SVG の resource provider 設計が矛盾しない。

## Phase 6: Utils / Ports / Android / Docs / Misc

目的: core optional 周辺の公開 class を実用価値で選別する。

候補:

- `Sk3DView` / `SkCamera3D`
- `SkParse`
- `SkCustomTypefaceBuilder`
- `SkNWayCanvas`
- `SkNoDrawCanvas`
- `SkCanvasStateUtils`
- `SkFontConfigInterface`
- `SkRemotableFontMgr`
- Android hardware buffer helpers

方針:

- platform 固有 API は既定 build へ混ぜない。
- utility API は C ABI での利用価値が明確なものから追加する。
- docs/android/ports は optional module と同じく CMake guard と smoke を必須にする。

## 実装 batch の標準手順

1. `date '+%Y-%m-%d %H:%M:%S %Z'` で作業開始時刻を記録する。
2. `public-api-coverage-matrix.csv` と対象 upstream header を確認する。
3. 対象行を `real_gap`、`na`、`false_positive` に分類する。
4. C API の型、所有権、failure mode、feature guard を決める。
5. `skia/capi` を実装する。
6. 必要なら `skia/handles` を実装する。
7. `cmake/reskia/sources-capi.cmake` と tests を更新する。
8. `scripts/generate_public_api_coverage.py` を再実行する。
9. configure/build と対象 smoke を実行する。
10. coverage 数値と残件を計画または triage に反映する。

## 完了条件

この計画全体の完了は、単純な 100% coverage ではなく、以下で判断する。

- `missing` の大半が `real_gap`、`na`、`false_positive` に分類済みである。
- `real_gap` のうち、既定 build で利用できる core/effects/codec/encode/utils API が実装済みである。
- GPU、SVG、paragraph、skottie、sksg、skresources は、それぞれ最小実用 C API と smoke を持つ。
- optional module の CMake option、依存検出、source registration、テスト条件が C API と一致している。
- callback、global registration、subclass hook は未実装でも、対象外理由または設計待ち理由が文書化されている。
