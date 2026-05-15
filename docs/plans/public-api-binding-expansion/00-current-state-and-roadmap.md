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

開始: 2026-05-15 09:28:34 JST

実行順:

1. callback / provider を伴わない `Skottie_Animation` の残 accessor を先に追加する。
2. `Phase 5A: Callback / Resource Provider Foundation` で callback context、release proc、global registration、provider bridge の共通規約を確定する。
3. Phase 5A の規約に沿って、`SlotManager`、skresources provider、skottie property observer / resource provider をまとめて追加する。
4. sksg は SceneGraph node ownership と invalidation model を決めてから、単純 node factory と render/revalidate helper を小さく追加する。

### Phase 5 progress 2026-05-15

callback / provider 設計を待たずに安全に追加できる `skottie::Animation` の simple accessor から着手した。

追加済み:

- `Skottie_Animation_inPoint`
- `Skottie_Animation_outPoint`
- `Skottie_Animation_version`
- `Skottie_Animation_size`

設計メモ:

- `version()` は `SkString` の owned copy を返し、caller は既存 `SkString_delete` で破棄する。
- `size()` は `SkSize` の owned handle を返し、caller は `static_sk_size_delete` で破棄する。
- `NULL` 入力は既存 `Skottie_Animation_duration` / `fps` と同じく、scalar は `0`、owned object は `NULL` を返す。
- `SlotManager`、resource provider、property observer、expression evaluator、text shaper は callback / provider ownership と resource lifetime に触れるため Phase 5A 後に扱う。

検証:

- `cmake -S skia -B skia/cmake-build-stability-skottie-tests -DRESKIA_DEPS_MODE=source -DRESKIA_ENABLE_SKOTTIE=ON -DRESKIA_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build skia/cmake-build-stability-skottie-tests --target test_skottie_smoke -j 8`
- `ctest --test-dir skia/cmake-build-stability-skottie-tests -R c_skia_skottie_smoke --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1131`、`covered=2171`、`partial=15`、`no_public_methods_found=104`
- `modules/skottie`: `covered 13`、`partial 1`、`missing 35`、`no_public_methods_found 1`
- `modules/skresources`: `missing 17`、`no_public_methods_found 2`
- `modules/sksg`: `covered 2`、`partial 1`、`missing 122`、`no_public_methods_found 4`
- `public-api-skottie-sksg-resources-missing-triage.csv`: covered 行を削除し、残 `174` 行。内訳は `real_gap 95`、`na 53`、`false_positive 26`

## Phase 5A: Callback / Resource Provider Foundation

目的: Phase 1 で残した callback/global registration と、optional module の provider / observer callback を同じ C ABI 規約で実装する。

実行位置: Phase 3 の SVG DOM 最小公開後、Phase 5 の simple accessor batch の次に行う。Phase 4 の paragraph/unicode/shaper は依存が重いため、Phase 5A と並行または前後してよいが、callback/provider API を追加する場合は Phase 5A の規約を先に適用する。

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

### Phase 5A progress 2026-05-15

callback / global registration foundation の最初の concrete API として、`SkGraphics::SetImageGeneratorFromEncodedDataFactory` を C ABI に公開した。

追加済み:

- `reskia_callback_release_proc_t`
- `reskia_image_generator_from_encoded_data_factory_t`
- `SkGraphics_SetImageGeneratorFromEncodedDataFactory`

設計メモ:

- callback context は Reskia 側で retained として保持し、登録置換時に旧 context の `release_proc` を一度だけ呼ぶ。
- callback 実行中の context は `shared_ptr` で保持し、置換が同時に起きても callback 終了まで生存する。
- encoded data は callback 中だけ有効な borrowed `const_sk_data_t` として渡す。
- callback が返す `sk_image_generator_t` は transferred handle として consume する。
- callback が `0` を返した場合は Skia default decoder への fallback として扱う。
- Skia 側に完全 deregistration API がないため、custom generator を止める場合は `0` を返す callback で置換する。

検証:

- `cmake --build skia/cmake-build-codex-phase1-tests --target test_enum_capabilities_graphics_invalid_input_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase1-tests -R c_skia_enum_capabilities_graphics_invalid_input_smoke --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1130`、`covered=2172`、`partial=15`、`no_public_methods_found=104`
- `public-api-core-effects-missing-triage.csv`: covered 行を削除し、残 `35` 行。内訳は `real_gap 1`、`na 14`、`false_positive 20`
- core/effects の残 `real_gap` は `SkTypeface::Register` のみ。

### Phase 5 skresources progress 2026-05-15

skottie の `SlotManager::setImageSlot` と skottie / SVG resource provider bridge の前提として、skresources の concrete provider / asset API を先に追加した。

追加済み:

- `ImageAsset_ref` / `unref` / `release`
- `ImageAsset_isMultiFrame`
- `ImageAsset_getFrame`
- `ImageAsset_getFrameData`
- `MultiFrameImageAsset_Make`
- `MultiFrameImageAsset_isMultiFrame`
- `MultiFrameImageAsset_getFrame`
- `ResourceProvider_ref` / `unref` / `release`
- `ResourceProvider_load`
- `ResourceProvider_loadImageAsset`
- `ResourceProvider_loadFont`
- `ResourceProvider_loadTypeface`
- `FileResourceProvider_Make`
- `FileResourceProvider_load`
- `FileResourceProvider_loadImageAsset`
- `CachingResourceProvider_Make`
- `DataURIResourceProviderProxy_Make`

設計メモ:

- `ImageAsset` / `ResourceProvider` は SkRefCnt 派生の opaque pointer として扱い、caller の owned ref は `*_release` で破棄する。
- `MultiFrameImageAsset_Make` は `sk_data_t` を borrow し、生成された asset は caller-owned ref として返す。
- `ResourceProvider` / `FileResourceProvider` から返る `SkData`、`SkImage`、`SkTypeface` は既存 handle に載せ、caller が handle delete で破棄する。
- `ImageAsset_getFrameData` は `image` / `sampling` / `matrix` を caller-owned handle として返す。caller は各 handle を delete する。
- source-mode の現在の codec 構成では `MultiFrameImageAsset::Make` が fixture PNG から codec を生成できない場合があるため、smoke は asset 生成成功時だけ frame helper を追加検証する。`FileResourceProvider_load` など provider 本体の動作は必須検証にしている。

検証:

- `cmake -S skia -B skia/cmake-build-stability-skresources-tests -DRESKIA_DEPS_MODE=source -DRESKIA_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build skia/cmake-build-stability-skresources-tests --target test_skresources_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-stability-skresources-tests -R c_skia_skresources_capi_smoke --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1115`、`covered=2187`、`partial=15`、`no_public_methods_found=104`
- `modules/skresources`: `covered 15`、`missing 2`、`no_public_methods_found 2`
- `public-api-skottie-sksg-resources-missing-triage.csv`: covered 行を削除し、残 `159` 行。内訳は `real_gap 80`、`na 53`、`false_positive 26`
- skresources の残件は `ExternalTrackAsset::seek` と `ResourceProvider::loadAudioAsset`。どちらも audio track callback/subclass surface なので、後続 callback provider batch まで残す。

### Phase 5 skottie builder / SlotManager progress 2026-05-15

`SlotManager` は直接 construct しても実用にならず、`Animation::Builder::make()` 後の `Builder::getSlotManager()` が公開経路であるため、builder wrapper と slot manager value subset を同じ batch で追加した。

追加済み:

- `Skottie_AnimationBuilder_new`
- `Skottie_AnimationBuilder_delete`
- `Skottie_AnimationBuilder_setResourceProvider`
- `Skottie_AnimationBuilder_make`
- `Skottie_AnimationBuilder_makeFromFile`
- `Skottie_AnimationBuilder_getSlotManager`
- `SlotManager_ref` / `unref` / `release`
- `SlotManager_setColorSlot` / `getColorSlot`
- `SlotManager_setScalarSlot` / `getScalarSlot`
- `SlotManager_setVec2Slot` / `getVec2Slot`
- `SlotManager_setImageSlot` / `getImageSlot`
- `SlotManager_getSlotInfo`
- `SlotInfo_*` count / id copy helpers

設計メモ:

- `AnimationBuilder` は heap-owned value wrapper とし、`Skottie_AnimationBuilder_delete` で破棄する。
- `AnimationBuilder_setResourceProvider` は skresources provider を borrow して `sk_ref_sp` で保持する。
- `AnimationBuilder_getSlotManager` は `sk_sp` を copy して release し、caller-owned ref を返す。
- `SlotManager` は SkRefCnt 派生の opaque pointer とし、caller-owned ref は `SlotManager_release` で破棄する。
- `SlotManager_getVec2Slot` は caller-owned `sk_v2_t` handle を返す。
- `SlotManager_getImageSlot` は caller-owned `ImageAsset` ref を返し、`ImageAsset_release` で破棄する。
- `SlotInfo_*Id` は owned `SkString` copy を返し、`SkString_delete` で破棄する。
- `SlotManager` の直接 constructor は internal `SceneGraphRevalidator` を必要とするため C ABI では直接公開せず、`AnimationBuilder_getSlotManager` を取得経路にする。
- `setTextSlot` / `getTextSlot` は `TextPropertyValue` の C ABI wrapper 設計が必要なため、次の focused batch で扱う。

検証:

- `cmake --build skia/cmake-build-stability-skottie-tests --target test_skottie_smoke -j 8`
- `ctest --test-dir skia/cmake-build-stability-skottie-tests -R c_skia_skottie_smoke --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1106`、`covered=2196`、`partial=15`、`no_public_methods_found=104`
- `modules/skottie`: `covered 22`、`partial 1`、`missing 26`、`no_public_methods_found 1`
- `public-api-skottie-sksg-resources-missing-triage.csv`: covered 行を削除し、残 `150` 行。内訳は `real_gap 70`、`na 54`、`false_positive 26`
- skottie の残 `real_gap` は `setTextSlot` / `getTextSlot`、TextShaper `Shape` overload、template expression evaluator、skresources audio provider である。次に進める場合は `TextPropertyValue` の value struct 設計または sksg の graph ownership 設計を先に行う。

### Phase 5 skottie TextPropertyValue / text slot progress 2026-05-15

`TextPropertyValue` は `SkString`、`sk_sp<SkTypeface>`、`GlyphDecorator` を含むため、C ABI では raw struct ではなく opaque な heap-owned wrapper として追加した。`GlyphDecorator` の新規 callback 注入は callback/observer batch へ残し、今回の wrapper は既存値のコピーと C 側から扱いやすい scalar/string/color/typeface fields の set/get に限定する。

追加済み:

- `TextPropertyValue_new`
- `TextPropertyValue_newCopy`
- `TextPropertyValue_delete`
- `TextPropertyValue_equals` / `notEquals`
- `TextPropertyValue_setTypeface` / `getTypeface`
- `TextPropertyValue_setText` / `getText`
- `TextPropertyValue_setTextSize` / `getTextSize`
- `TextPropertyValue_setMinTextSize` / `getMinTextSize`
- `TextPropertyValue_setMaxTextSize` / `getMaxTextSize`
- `TextPropertyValue_setStrokeWidth` / `getStrokeWidth`
- `TextPropertyValue_setLineHeight` / `getLineHeight`
- `TextPropertyValue_setLineShift` / `getLineShift`
- `TextPropertyValue_setAscent` / `getAscent`
- `TextPropertyValue_setMaxLines` / `getMaxLines`
- `TextPropertyValue_setHAlign` / `getHAlign`
- `TextPropertyValue_setVAlign` / `getVAlign`
- `TextPropertyValue_setResizePolicy` / `getResizePolicy`
- `TextPropertyValue_setLinebreakPolicy` / `getLinebreakPolicy`
- `TextPropertyValue_setDirection` / `getDirection`
- `TextPropertyValue_setCapitalization` / `getCapitalization`
- `TextPropertyValue_setBox` / `getBox`
- `TextPropertyValue_setFillColor` / `getFillColor`
- `TextPropertyValue_setStrokeColor` / `getStrokeColor`
- `TextPropertyValue_setPaintOrder` / `getPaintOrder`
- `TextPropertyValue_setStrokeJoin` / `getStrokeJoin`
- `TextPropertyValue_setHasFill` / `hasFill`
- `TextPropertyValue_setHasStroke` / `hasStroke`
- `TextPropertyValue_setLocale` / `getLocale`
- `SlotManager_setTextSlot`
- `SlotManager_getTextSlot`

設計メモ:

- `TextPropertyValue_newCopy` と `SlotManager_getTextSlot` は caller-owned wrapper を返し、`TextPropertyValue_delete` で破棄する。
- `TextPropertyValue_getText` / `getLocale` は owned `SkString` copy を返し、`SkString_delete` で破棄する。
- `TextPropertyValue_setTypeface` は `sk_typeface_t` handle を borrow して `sk_sp` copy を保持する。
- `TextPropertyValue_getTypeface` は owned `sk_typeface_t` handle を返し、`static_sk_typeface_delete` で破棄する。
- enum fields は Skia の enum ordinal を `int32_t` として受け渡す。定数名の C enum 化は別 batch で追加可能だが、slot set/get の実用には必須ではない。
- `GlyphDecorator` は callback lifetime と draw-time canvas/thread の設計が必要なため、この batch では C 側 setter を追加しない。

検証:

- `cmake --build skia/cmake-build-stability-skottie-tests --target test_skottie_smoke -j 8`
- `ctest --test-dir skia/cmake-build-stability-skottie-tests -R c_skia_skottie_smoke --output-on-failure`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1102`、`covered=2200`、`partial=15`、`no_public_methods_found=104`
- `modules/skottie`: `covered 26`、`partial 1`、`missing 22`、`no_public_methods_found 1`
- `public-api-skottie-sksg-resources-missing-triage.csv`: covered 行を削除し、残 `146` 行。内訳は `real_gap 68`、`na 54`、`false_positive 24`
- skottie の残 `real_gap` は TextShaper `Shape` overload と template expression evaluator に絞られた。skresources 側の audio provider は callback provider batch、sksg 側は graph ownership 設計後に扱う。

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

### Phase 6 parse utilities progress 2026-05-15

Phase 6 の初手として、既定 build に既に入っており callback / platform handle を伴わない `SkParse` と `SkParsePath` を C API に追加した。どちらも static utility surface で、所有権は output buffer または owned `SkString` copy に閉じる。

追加済み:

- `SkParse_Count`
- `SkParse_CountWithSeparator`
- `SkParse_FindColor`
- `SkParse_FindHex`
- `SkParse_FindMSec`
- `SkParse_FindNamedColor`
- `SkParse_FindS32`
- `SkParse_FindScalar`
- `SkParse_FindScalars`
- `SkParse_FindBool`
- `SkParse_FindList`
- `SkParsePath_FromSVGString`
- `SkParsePath_ToSVGString`

設計メモ:

- `SkParse_Find*` は upstream と同じく入力文字列内の終端位置を borrowed `const char*` として返す。invalid input は `nullptr` / `false` / `-1` に正規化する。
- `SkParse_FindScalars` は `count > 0` の場合のみ output 配列を必須にする。
- `SkParsePath_FromSVGString` は caller-owned `SkPath` に書き込む。
- `SkParsePath_ToSVGString` は owned `SkString` copy を返し、`SkString_delete` で破棄する。
- `SkParsePath::PathEncoding` は upstream enum ordinal を `int32_t` として受け渡す。C enum 定数化は後続の polish batch で追加可能。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_parse_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_parse_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1089`、`covered=2213`、`partial=15`、`no_public_methods_found=104`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `123` から `110` に減少した。
- 次候補は `SkTextUtils` / `SkShadowUtils` の pure static helpers、または `SkNWayCanvas` / `SkNoDrawCanvas` の canvas wrapper。platform 固有の Android / ports font manager は guard と smoke 方針を先に固める。

### Phase 6 text / shadow utilities progress 2026-05-15

`SkParse` / `SkParsePath` に続く pure static helper batch として、既定 build の `SkTextUtils` と `SkShadowUtils` を追加した。どちらも既存の `SkCanvas`、`SkFont`、`SkPaint`、`SkPath`、`SkMatrix`、`SkPoint3`、`SkRect` C API 型だけで表現できるため、platform guard や callback lifetime を増やさずに公開できる。

追加済み:

- `SkTextUtils_Draw`
- `SkTextUtils_DrawString`
- `SkTextUtils_GetPath`
- `SkShadowUtils_DrawShadow`
- `SkShadowUtils_GetLocalBounds`
- `SkShadowUtils_ComputeTonalColors`

設計メモ:

- `SkTextUtils_Draw` / `GetPath` の `SkTextEncoding` と `SkTextUtils::Align` は upstream enum ordinal を `int32_t` で受け渡す。範囲外入力は no-op。
- `SkTextUtils_Draw` は `size == 0` の場合だけ `text == nullptr` を許容する。
- `SkTextUtils_GetPath` は caller-owned `SkPath` に書き込む。
- `SkShadowUtils_GetLocalBounds` は caller-owned `SkRect` に書き込み、invalid input は `false`。
- `SkShadowUtils_ComputeTonalColors` は output color pointer を必須にし、invalid input は no-op。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_text_shadow_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_text_shadow_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1083`、`covered=2219`、`partial=15`、`no_public_methods_found=104`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `110` から `104` に減少した。
- 次候補は `SkNWayCanvas` / `SkNoDrawCanvas` の canvas wrapper。`SkCamera` は値型と matrix interaction の API surface が広く、`SkCustomTypefaceBuilder` と `SkAnimCodecPlayer` は stream/codec/font ownership を含むため、必要なら小さな設計メモを先に置く。

### Phase 6 canvas utilities progress 2026-05-15

Phase 6 の canvas wrapper batch として、`SkNoDrawCanvas` と `SkNWayCanvas` を追加した。どちらも `SkCanvas` 派生だが、既存の `SkCanvas_delete` へ混ぜると派生型の intent が曖昧になるため、型ごとの owned wrapper と borrowed `asCanvas` view を用意した。

追加済み:

- `SkNoDrawCanvas_new`
- `SkNoDrawCanvas_newWithIRect`
- `SkNoDrawCanvas_delete`
- `SkNoDrawCanvas_asCanvas`
- `SkNoDrawCanvas_resetCanvas`
- `SkNoDrawCanvas_resetCanvasWithIRect`
- `SkNWayCanvas_new`
- `SkNWayCanvas_delete`
- `SkNWayCanvas_asCanvas`
- `SkNWayCanvas_addCanvas`
- `SkNWayCanvas_removeCanvas`
- `SkNWayCanvas_removeAll`

設計メモ:

- `SkNoDrawCanvas_asCanvas` / `SkNWayCanvas_asCanvas` は borrowed view を返す。caller は返された `reskia_canvas_t*` を削除しない。
- `SkNWayCanvas_addCanvas` は child canvas を borrow する。caller は登録中の child canvas を生存させ、削除前に `removeCanvas` または `removeAll` で解除する。
- `SkNoDrawCanvas_newWithIRect` / `resetCanvasWithIRect` は caller-owned `SkIRect` をコピーして使う。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_canvas_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_canvas_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1074`、`covered=2228`、`partial=15`、`no_public_methods_found=104`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `104` から `95` に減少した。
- 次候補は `SkCanvasStateUtils`。`SkPaintFilterCanvas` は subclass/protected override 寄り、`SkEventTracer` は global tracer/callback 登録、`SkCamera` は値型 API が広いため、どれも小さな設計メモを先に置くのがよい。

### Phase 6 canvas state utilities progress 2026-05-15

`SkCanvasStateUtils` は raster-backed canvas の state を library boundary 越しに渡すための opaque state API である。C ABI では `SkCanvasState` を opaque owned pointer とし、state から復元した `SkCanvas` は caller-owned raw canvas として返す。

追加済み:

- `SkCanvasStateUtils_CaptureCanvasState`
- `SkCanvasStateUtils_MakeFromCanvasState`
- `SkCanvasStateUtils_ReleaseCanvasState`

設計メモ:

- `SkCanvasStateUtils_CaptureCanvasState` は owned state を返す。失敗時は `nullptr`。
- `SkCanvasStateUtils_MakeFromCanvasState` は owned `reskia_canvas_t*` を返し、`SkCanvas_delete` で破棄する。
- state は、state から作成した canvas を破棄した後に `SkCanvasStateUtils_ReleaseCanvasState` で解放する。
- upstream 実装は raster-backed device などの条件を満たす canvas だけ capture できるため、smoke では bitmap-backed canvas を使う。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_canvas_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_canvas_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1071`、`covered=2231`、`partial=15`、`no_public_methods_found=104`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `95` から `92` に減少した。
- 既定 build で小さく進めやすい Phase 6 utility はここまでで一段落。残る大きな塊は `SkCamera`、`SkCustomTypefaceBuilder`、`SkAnimCodecPlayer`、Android/ports font manager、global callback/subclass 系であり、次は分類・設計メモを先に進めるのがよい。

### Phase 6 design memo / custom typeface progress 2026-05-15

大きめの残件に入る前に、`phase-6-design-memos-2026-05-15.md` を追加し、`SkCamera`、`SkCustomTypefaceBuilder`、`SkAnimCodecPlayer`、`SkOrderedFontMgr`、`SkPaintFilterCanvas`、`SkEventTracer`、Android / ports 系の所有権と推奨順を整理した。

この設計メモに従い、まず `SkCustomTypefaceBuilder` の path glyph subset を追加した。drawable glyph と stream deserialize は、それぞれ `SkDrawable` ref ownership と `SkStreamAsset` consume semantics を API 名で明示してから後続で扱う。

追加済み:

- `SkCustomTypefaceBuilder_new`
- `SkCustomTypefaceBuilder_delete`
- `SkCustomTypefaceBuilder_setGlyphPath`
- `SkCustomTypefaceBuilder_setMetrics`
- `SkCustomTypefaceBuilder_setFontStyle`
- `SkCustomTypefaceBuilder_detach`

設計メモ:

- builder は heap-owned value とし、`SkCustomTypefaceBuilder_delete` で破棄する。
- `setGlyphPath` は caller-owned `SkPath` を借用し、Skia 側で path をコピーする。
- `setMetrics` / `setFontStyle` は caller-owned value object を借用し、Skia 側で値をコピーする。
- `detach` は caller-owned `sk_typeface_t` handle を返し、`static_sk_typeface_delete` で破棄する。
- `setGlyph` drawable overload は未実装のため coverage 上は `partial`。`MakeFromStream` は stream handle consume policy の確定まで残す。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_custom_typeface_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_custom_typeface_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1065`、`covered=2235`、`partial=17`、`no_public_methods_found=104`
- `SkCustomTypefaceBuilder`: `covered 4`、`partial 2`、`missing 1`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `92` から `86` に減少した。

### Phase 6 ordered font manager / anim codec player progress 2026-05-15

設計メモの推奨順に従い、`SkOrderedFontMgr` minimal wrapper と `SkAnimCodecPlayer` codec-consuming wrapper を追加した。

追加済み:

- `SkOrderedFontMgr_new`
- `SkOrderedFontMgr_delete`
- `SkOrderedFontMgr_asFontMgr`
- `SkOrderedFontMgr_refAsFontMgr`
- `SkOrderedFontMgr_append`
- `SkAnimCodecPlayer_new`
- `SkAnimCodecPlayer_delete`
- `SkAnimCodecPlayer_getFrame`
- `SkAnimCodecPlayer_dimensions`
- `SkAnimCodecPlayer_duration`
- `SkAnimCodecPlayer_seek`

設計メモ:

- `SkOrderedFontMgr_asFontMgr` は borrowed view を返す。caller は削除しない。
- `SkOrderedFontMgr_refAsFontMgr` は retained `sk_font_mgr_t` handle を返し、`static_sk_font_mgr_delete` で破棄する。
- `SkOrderedFontMgr_append` は child font manager handle を borrow して `sk_sp` copy を保持する。
- `SkAnimCodecPlayer_new` は valid `sk_codec_t` handle を consume する。生成後、元 codec handle は無効になる。
- `SkAnimCodecPlayer_getFrame` は retained `sk_image_t` handle を返し、`static_sk_image_delete` で破棄する。
- `SkAnimCodecPlayer_dimensions` は owned `sk_i_size_t` handle を返し、`static_sk_i_size_delete` で破棄する。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_anim_codec_player_utils_smoke test_ordered_font_mgr_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R 'c_skia_(ordered_font_mgr|anim_codec_player)_utils_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1056`、`covered=2244`、`partial=17`、`no_public_methods_found=104`
- `SkOrderedFontMgr`: `covered 3`
- `SkAnimCodecPlayer`: `covered 6`
- Phase 6 候補として抽出される `include/utils` / `include/ports` / `include/android` / `include/docs` の missing は `86` から `77` に減少した。
- 次候補は `SkCamera` non-Android deprecated subset、または `SkCustomTypefaceBuilder` の drawable / stream 残件。ただし callback/global/subclass 系と platform guard 系は引き続き設計待ちとする。

### Phase 6 camera / custom typeface remainder progress 2026-05-16

`SkCamera.h` の deprecated 3D utility subset と、`SkCustomTypefaceBuilder` の残っていた stream / drawable entry point を追加した。`Sk3DView` の Android framework-only camera location methods は default build では member 自体が存在しないため、`public-api-phase-6-remaining-triage.csv` で `na` に分類した。

追加済み:

- `SkPatch3D_new`
- `SkPatch3D_delete`
- `SkPatch3D_reset`
- `SkPatch3D_transform`
- `SkPatch3D_dotWith`
- `SkPatch3D_dotWithV3`
- `SkPatch3D_rotate`
- `SkPatch3D_rotateDegrees`
- `SkPatch3D_getU` / `SkPatch3D_getV` / `SkPatch3D_getOrigin`
- `SkPatch3D_setU` / `SkPatch3D_setV` / `SkPatch3D_setOrigin`
- `SkCamera3D_new`
- `SkCamera3D_delete`
- `SkCamera3D_reset`
- `SkCamera3D_update`
- `SkCamera3D_patchToMatrix`
- `SkCamera3D_getLocation` / `SkCamera3D_getAxis` / `SkCamera3D_getZenith` / `SkCamera3D_getObserver`
- `SkCamera3D_setLocation` / `SkCamera3D_setAxis` / `SkCamera3D_setZenith` / `SkCamera3D_setObserver`
- `Sk3DView_new`
- `Sk3DView_delete`
- `Sk3DView_save`
- `Sk3DView_restore`
- `Sk3DView_translate`
- `Sk3DView_rotateX`
- `Sk3DView_rotateY`
- `Sk3DView_rotateZ`
- `Sk3DView_getMatrix`
- `Sk3DView_applyToCanvas`
- `Sk3DView_dotWithNormal`
- `SkCustomTypefaceBuilder_setGlyphDrawable`
- `SkCustomTypefaceBuilder_MakeFromStream`

設計メモ:

- `SkPatch3D` / `SkCamera3D` / `Sk3DView` は heap-owned wrapper とし、対応する delete API で破棄する。
- `SkPatch3D_transform` は `SkM44` を借用し、`dst` が非 NULL の場合は caller-owned destination に書き込む。`dst == NULL` では upstream と同じく self transform として扱う。
- `SkCamera3D_patchToMatrix` と `Sk3DView_getMatrix` は caller-owned `SkMatrix` に書き込む。
- `Sk3DView_applyToCanvas` は canvas を借用し、保持しない。
- `SkCustomTypefaceBuilder_setGlyphDrawable` は `sk_drawable_t` から retained `sk_sp<SkDrawable>` を渡す。caller の drawable handle は消費しない。
- `SkCustomTypefaceBuilder_MakeFromStream` は `sk_stream_asset_t` を消費し、成功時も失敗時も入力 stream handle は無効になる。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_custom_typeface_utils_smoke test_camera_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R 'c_skia_(custom_typeface_utils|camera_utils)_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1033`、`covered=2267`、`partial=17`、`no_public_methods_found=104`
- `SkPatch3D`: `covered 7`
- `SkCamera3D`: `covered 4`
- `Sk3DView`: `covered 11`、`missing 4`
- `SkCustomTypefaceBuilder`: `covered 5`、`partial 2`
- `public-api-phase-6-remaining-triage.csv` を追加し、`Sk3DView` Android-only methods、`SkEventTracer`、`SkPaintFilterCanvas`、`SkCustomTypefaceBuilder` overload partial を分類した。
- Phase 6 の default build utility 実装はほぼ一段落。残る `SkEventTracer` と `SkPaintFilterCanvas` は callback/global/subclass design batch に回す。

### Phase 6 callback / subclass remainder progress 2026-05-16

Phase 5A の callback foundation 方針を使い、Phase 6 に残っていた `SkEventTracer` と `SkPaintFilterCanvas` を追加した。

追加済み:

- `SkEventTracer_new`
- `SkEventTracer_delete`
- `SkEventTracer_SetInstance`
- `SkEventTracer_GetInstance`
- `SkEventTracer_getCategoryGroupEnabled`
- `SkEventTracer_getCategoryGroupName`
- `SkEventTracer_addTraceEvent`
- `SkEventTracer_updateTraceEventDuration`
- `SkEventTracer_newTracingSection`
- `SkPaintFilterCanvas_new`
- `SkPaintFilterCanvas_delete`
- `SkPaintFilterCanvas_asCanvas`
- `SkPaintFilterCanvas_getBaseLayerSize`
- `SkPaintFilterCanvas_recordingContext`

設計メモ:

- `SkEventTracer_new` は concrete C callback bridge を作る。各 callback は `void *user_data` を最後に受け取る。
- `SkEventTracer_delete` は `SkEventTracer_new` で作った未登録 tracer を破棄する。
- `SkEventTracer_SetInstance` は tracer を消費する。Skia 側の仕様に従い、登録失敗時も渡した tracer は Skia 側で破棄される。
- `SkEventTracer_GetInstance` は borrowed singleton を返す。caller は削除しない。
- `SkPaintFilterCanvas_new` は wrapped canvas を借用し、`onFilter(SkPaint&)` を C callback に渡す concrete subclass を作る。
- `SkPaintFilterCanvas_asCanvas` は borrowed `SkCanvas` view を返す。多重継承の pointer adjustment を避けるため、実装では `static_cast<SkCanvas*>` を使う。
- `SkPaintFilterCanvas_recordingContext` は borrowed pointer を返す。raster/no-draw target では `nullptr`。

検証:

- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt --target test_event_paint_filter_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-project-survey-prebuilt -R c_skia_event_paint_filter_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=1027`、`covered=2273`、`partial=17`、`no_public_methods_found=104`
- `SkEventTracer`: `covered 3`
- `SkPaintFilterCanvas`: `covered 3`
- `public-api-phase-6-remaining-triage.csv` は、残る `Sk3DView` Android-only methods と `SkCustomTypefaceBuilder` overload heuristic partial だけに整理した。
- Phase 6 の default build `include/utils` 実装候補は、Android framework-only 条件付き API を除いて一段落。

### Phase 6 PDF / ports guarded value progress 2026-05-16

PDF と ports のうち、既定 build または既存 source import で無理なく進められるものを追加した。

追加済み:

- `AttributeList_new`
- `AttributeList_delete`
- `AttributeList_appendInt`
- `AttributeList_appendFloat`
- `AttributeList_appendName`
- `AttributeList_appendFloatArray`
- `AttributeList_appendNodeIdArray`
- `DateTime_toISO8601`
- `SkFontIdentity_InvalidDataId`
- `SkRemotableFontIdentitySet_new`
- `SkRemotableFontIdentitySet_unref`
- `SkRemotableFontIdentitySet_count`
- `SkRemotableFontIdentitySet_at`
- `SkRemotableFontIdentitySet_NewEmpty`
- `SkRemotableFontMgr_ref`
- `SkRemotableFontMgr_unref`
- `SkRemotableFontMgr_getIndex`
- `SkRemotableFontMgr_matchIndexStyle`
- `SkRemotableFontMgr_matchName`
- `SkRemotableFontMgr_matchNameStyle`
- `SkRemotableFontMgr_matchNameStyleCharacter`
- `SkRemotableFontMgr_getData`
- `SkFontMgr_Indirect_new`

設計メモ:

- `SkPDF::AttributeList` は standalone value helper として raw owned pointer にした。PDF document tagging への接続 API は別 batch で扱う。
- `SkPDF::DateTime::toISO8601` は caller-owned `SkString` に書き込む。
- `SkRemotableFontIdentitySet` は ref-counted object なので `*_unref` で解放する。
- `SkRemotableFontMgr` は抽象 provider pointer に対する薄い call wrapper に留めた。C callback provider 実装は callback/provider batch に残す。
- `SkFontMgr_Indirect_new` は `sk_font_mgr_t` の impl を retain し、raw `SkRemotableFontMgr*` proxy も retain して `sk_font_mgr_t` として返す。
- coverage generator は underscore を含む class 名の constructor 判定が壊れていたため、prefix 長で suffix を取るよう修正した。

検証:

- `cmake -S skia -B skia/cmake-build-codex-phase6-pdf -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON -DRESKIA_ENABLE_PDF=ON`
- `cmake --build skia/cmake-build-codex-phase6-pdf --target test_pdf_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase6-pdf -R c_skia_pdf_smoke --output-on-failure`
- `cmake -S skia -B skia/cmake-build-codex-phase6-ports -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase6-ports --target test_remotable_font_mgr_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase6-ports -R c_skia_remotable_font_mgr_utils_smoke --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

台帳更新:

- `public-api-coverage-matrix.csv`: `missing=998`、`covered=2302`、`partial=17`、`no_public_methods_found=104`
- `include/docs` の Phase 6 対象は covered。
- `SkRemotableFontIdentitySet`: `covered 4`
- `SkRemotableFontMgr`: `covered 6`
- `SkFontMgr_Indirect`: `covered 1`
- 残る Android 18 行と `SkFontConfigInterface` 7 行は、platform/import-source/provider-ownership 待ちとして `public-api-phase-6-remaining-triage.csv` に分類した。

### Phase 6 completion 2026-05-16

Phase 6 は完了扱いとする。

完了判断:

- 既定 build で実装可能な utils / docs / ports thin wrapper は実装済み。
- callback/subclass 系の `SkEventTracer` / `SkPaintFilterCanvas` は Phase 5A 方針に沿って実装済み。
- `Sk3DView` Android framework-only methods は default build では member が存在しないため `na`。
- `SkCustomTypefaceBuilder::setGlyph` overload は C API 実装済みで、coverage generator の overload-disambiguation heuristic により `partial` として残る。
- `SkAnimatedImage`、`SkAndroidFrameworkUtils`、`SkFontConfigInterface` は platform/import-source/provider-ownership が必要なため、Phase 8 以降に分離する。

Phase 6 完了時点の残件 snapshot:

| area | missing/partial | 次の扱い |
| --- | ---: | --- |
| `modules/svg` | 357 | Phase 9 optional module expansion |
| `include/gpu` | 314 | Phase 9 GPU residual / `02-phase2-gpu-residual-design.md` 更新 |
| `modules/sksg` | 123 | Phase 9 graph ownership batch |
| `modules/skparagraph` | 46 | Phase 9 paragraph painter / value helper batch |
| `include/core` | 32 | Phase 7 triage refresh / Phase 10 generator polish |
| `modules/skplaintexteditor` | 26 | Phase 9 low-priority editor batch |
| `modules/bentleyottmann` | 24 | Phase 9 value-confirmation batch |
| `modules/skottie` | 23 | Phase 9 callback/provider residual |
| `modules/skshaper` | 23 | Phase 9 shaper run-handler batch |
| `include/android` | 18 | Phase 8 guarded Android/import-source batch |
| `include/ports` | 7 | Phase 8 FontConfig guarded provider batch |

## Phase 7: Post-Phase 6 residual triage refresh

目的: Phase 1-6 で実装済みになった行を triage 台帳から落とし、残った `missing` / `partial` を Phase 8 以降の実装単位へ再分類する。

詳細計画: `07-post-phase6-residual-plan-2026-05-16.md`

作業:

- `scripts/generate_public_api_coverage.py` を再実行し、coverage snapshot を固定する。
- optional module triage CSV を現行 matrix に同期する。
- `partial` を「実装済みだが generator limitation」と「未実装 overload」に分ける。
- `real_gap` を Phase 8 / Phase 9 / Phase 10 に再分類する。
- priority を現状の実装価値で付け直す。

受け入れ条件:

- 各 triage CSV の `untriaged` が 0。
- Phase 8 / Phase 9 / Phase 10 の対象が triage note から追える。
- Phase 6 の残件が platform/provider/generator polish として説明できる。

## Phase 8: Guarded platform / import-source APIs

目的: 既定 build に混ぜられない Android / FontConfig / platform source import 系 API を feature guard 付きで扱う。

対象:

- `SkAnimatedImage`
- `SkAndroidFrameworkUtils`
- `SkFontConfigInterface`
- `Sk3DView` Android framework-only camera location methods

方針:

- source import が必要な API は、upstream ref と import 差分を文書化してから C API を追加する。
- `SK_BUILD_FOR_ANDROID_FRAMEWORK` や platform library 依存を default build へ混ぜない。
- global registration と provider ownership は `01-callback-global-registration-design.md` の語彙に合わせる。
- smoke test は feature guard と同じ条件でのみ登録する。

受け入れ条件:

- feature option OFF で configure/build が通る。
- feature option ON の環境では smoke が実行される。
- source import / platform dependency / ownership が計画書に残る。

## Phase 9: High-volume optional module expansion

目的: 残件の大きい optional module を、実用 entry point、value/helper、callback/provider に分けて継続実装する。

推奨順:

1. SVG residual: `SkSVGTypes` value/helper、node attribute mutation、filter/render context、resource provider。
2. GPU residual: Ganesh residual と Graphite residual を分け、no-callback value/query から進める。
3. SKSG residual: graph ownership と invalidation model を設計してから node factory を広げる。
4. paragraph/unicode/shaper residual: value helper と custom painter/run-handler callback を分ける。
5. skottie/skresources residual: property observer、expression evaluator、resource provider。
6. skplaintexteditor/bentleyottmann: 実用 entry point が明確になってから低優先で進める。

受け入れ条件:

- optional module ごとに CMake option、source registration、依存検出、smoke test が揃う。
- callback/provider API は release proc と failure path を smoke で検証する。
- SVG、skottie、skresources の provider 設計が矛盾しない。

## Phase 10: Coverage quality / ABI polish

目的: 実装済みなのに `partial` / `missing` に残る行を減らし、C ABI の命名・所有権コメント・enum 定数を整える。

対象:

- overload-disambiguated C API の generator matching
- platform guard の `na` 表現
- named operator API と coverage token の対応
- C enum 定数化
- ownership comment の語彙統一

受け入れ条件:

- `partial` が真の未実装 overload だけを表す。
- platform guard 由来の未実装が triage CSV と note で説明できる。
- 新規 C API の header comment が `owned` / `borrowed` / `consumed` / `retained` の語彙で揃う。

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
