# Phase 7+ Post-Phase 6 Residual Plan

- 作成日: 2026-05-16
- 作業開始時刻: 2026-05-16 01:01:05 JST
- 前提: Phase 6 は完了扱い
- coverage 入力: `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`

## Snapshot

Phase 6 完了時点の method-level coverage は次の状態である。

| status | count |
| --- | ---: |
| `covered` | 2302 |
| `missing` | 998 |
| `partial` | 17 |
| `no_public_methods_found` | 104 |

`missing` / `partial` の多い領域は以下である。

| area | remaining | 主な内容 |
| --- | ---: | --- |
| `modules/svg` | 357 | SVG value types、node/attribute mutation、filter/render context、resource provider |
| `include/gpu` | 314 | Ganesh residual、Graphite context/recorder/backend values、backend-specific structs |
| `modules/sksg` | 123 | graph node ownership、render/effect/geometry nodes、invalidation |
| `modules/skparagraph` | 46 | `ParagraphPainter`、custom paint、remaining `TextStyle` / value helpers |
| `include/core` | 32 | legacy/guarded APIs、operator heuristic、callback/global registration residual |
| `modules/skplaintexteditor` | 26 | editor/string slice API; paragraph integration dependent |
| `modules/bentleyottmann` | 24 | algorithm/internal-public module; public value to confirm |
| `modules/skottie` | 23 | property observer, expression manager, text shaper residual |
| `modules/skshaper` | 23 | `SkShaper` shaping APIs and run handler integration |
| `include/android` | 18 | `SkAnimatedImage`, Android framework helpers |
| `include/ports` | 7 | `SkFontConfigInterface` guarded provider/global registration |

## Phase 7: Residual Triage Refresh

目的: Phase 0 で作った triage 台帳を、Phase 1-6 の実装済み状態に同期し、次の実装対象を誤検出や既実装 partial から分離する。

対象:

- `public-api-gpu-missing-triage.csv`
- `public-api-svg-missing-triage.csv`
- `public-api-paragraph-unicode-shaper-missing-triage.csv`
- `public-api-skottie-sksg-resources-missing-triage.csv`
- `public-api-core-effects-missing-triage.csv`
- `public-api-phase-6-remaining-triage.csv`

作業:

1. `scripts/generate_public_api_coverage.py` を再実行する。
2. 各 triage CSV から covered 済み行を落とす。
3. `partial` 行を次に分ける。
   - overload disambiguation 済みの false positive / heuristic limitation
   - まだ同名 overload の C API がない real gap
4. `real_gap` を次の実装フェーズへ再分類する。
   - Phase 8: platform/import-source guarded
   - Phase 9: optional module expansion
   - Phase 10: polish/generator
5. P0/P1/P2/P3 の priority を現在の実装価値で付け直す。

受け入れ条件:

- 各 triage CSV の `untriaged` が 0。
- Phase 8 / 9 / 10 の対象行が CSV note から追える。
- `SkCustomTypefaceBuilder::setGlyph` のような実装済み partial は、coverage generator 改善候補として明示される。

### Progress 2026-05-16

`public-api-phase-7-residual-index.csv` を追加し、現行 matrix の `missing` / `partial` 1015 行を 1 つの Phase 7 index に集約した。

集計:

| key | count |
| --- | ---: |
| rows | 1015 |
| `missing` | 998 |
| `partial` | 17 |
| `real_gap` | 505 |
| `na` | 283 |
| `false_positive` | 227 |

Phase 割当:

| next phase | count | 内容 |
| --- | ---: | --- |
| Phase 8 | 29 | Android / FontConfig / Android-framework guarded API |
| Phase 9 GPU | 297 | Ganesh / Graphite / backend object residual |
| Phase 9 optional | 445 | SVG、SKSG、paragraph、skottie、skshaper、editor、bentleyottmann など |
| Phase 9 callback/provider | 7 | codec/core callback / registration residual |
| Phase 10 | 237 | generator polish、false positive、guarded/legacy polish |

同期内容:

- 既存 triage 台帳の分類を引き継いだ。
- 既存台帳に未収録だった 67 行を Phase 7 index で分類した。
- `public-api-paragraph-unicode-shaper-missing-triage.csv` から、現行 matrix では covered になった stale 10 行を削除した。
- `partial` 17 行を Phase 10 の generator polish と、真に後続設計が必要な overload review に分けた。
- `SkCustomTypefaceBuilder::setGlyph` は両 overload が `SkCustomTypefaceBuilder_setGlyphPath` / `SkCustomTypefaceBuilder_setGlyphDrawable` として実装済みなので、Phase 10 generator polish に分類した。

### Routing Artifacts 2026-05-16

Phase 7 の後続作業として、次フェーズへ直接渡すための補助台帳を追加した。

| file | rows | purpose |
| --- | ---: | --- |
| `public-api-phase-7-triage-routing-index.csv` | 930 | 既存 triage CSV の各行に Phase 7 の `next_phase` / `residual_kind` を合流した routing view |
| `public-api-phase-8-guarded-platform-index.csv` | 11 | Android framework guarded API の Phase 8 残件 index |
| `public-api-phase-9-shortlist.csv` | 80 | Phase 9 の初期実装候補 shortlist |
| `public-api-phase-10-generator-polish-backlog.csv` | 237 | generator polish / false positive / guard-aware coverage backlog |

Phase 8 index 内訳:

- `android_framework_only`: 11

Phase 9 shortlist 内訳:

- `svg_value_helpers`: 20
- `gpu_no_callback_value_query`: 20
- `sksg_graph_ownership_design`: 15
- `paragraph_value_and_painter_residual`: 15
- `shaper_run_handler_design`: 10

Phase 10 backlog 内訳:

- false positive suppression / mapping: 209
- overload / split-helper matching: 18
- guard-aware NA classification: 10

## Phase 8: Guarded Platform / Import-Source APIs

目的: Phase 6 で後回しにした platform source import、global/provider ownership、feature guard が必要な API を、既定 build に混ぜずに扱う。

優先順:

1. `SkAnimatedImage`。Phase 8 で実装済み。
   - `vendor/skia-upstream/src/android/SkAnimatedImage.cpp` を source import した。
   - C API は `SkAndroidCodec` handle を consume し、返却 object は ref-counted `SkDrawable` 派生として unref 解放する。
   - `getCurrentFrame` は retained `sk_image_t` を返す。
2. `SkFontConfigInterface`。Phase 8 で実装済み。
   - implementation source (`SkFontConfigInterface.cpp`, direct FontConfig sources) を `RESKIA_ENABLE_FONTCONFIG_CAPI=ON` 配下で import した。
   - `SetGlobal` は pointer を retain して global に保持する C ABI とし、`RefGlobal` は retained pointer を返す。
   - `FontIdentity` は `SkString` と `SkFontStyle` を含むため、opaque value wrapper と memory serialization helper を追加した。
3. Android framework helpers
   - `SkAndroidFrameworkUtils` と `Sk3DView` camera location methods は `SK_BUILD_FOR_ANDROID_FRAMEWORK` only。
   - Android build target を明示できるまで `na` のまま維持する。

受け入れ条件:

- feature option が OFF のとき未解決 symbol を出さない。
- source import する場合は upstream ref と差分理由を文書化する。
- smoke test は platform guard と同じ条件でのみ登録する。

### Phase 8 Progress 2026-05-16

`SkAnimatedImage` 11 行は Phase 8 の source-import subset として実装済み。

実施内容:

- `vendor/skia-upstream/src/android/SkAnimatedImage.cpp` を `skia/src/android/SkAnimatedImage.cpp` に import し、core source set に追加した。
- `skia/capi/sk_animated_image.h` / `.cpp` を追加し、`Make` 2 overload、lifetime (`delete`)、`reset`、`isFinished`、`decodeNextFrame`、`getCurrentFrame`、frame duration、repetition count、frame count を C ABI に公開した。
- `SkAnimatedImage_Make*` は `sk_android_codec_t` を consume する。`postProcess` は既存 `sk_picture_t` を borrow し、`getCurrentFrame` は retained `sk_image_t` を返す。
- `test_animated_image_utils_smoke` を追加し、PNG fixture から `SkCodec`、`SkAndroidCodec`、`SkAnimatedImage` へ進む基本経路と handle ownership を検証した。

検証:

- `cmake -S skia -B skia/cmake-build-codex-phase8-animated -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase8-animated --target test_animated_image_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase8-animated -R 'c_skia_animated_image_utils_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2320 |
| `missing` | 980 |
| `partial` | 17 |
| `no_public_methods_found` | 104 |

更新後の Phase 8 index:

| group | rows |
| --- | ---: |
| `android_framework_only` | 11 |

残りの Phase 8 方針:

1. Android framework helpers
   - `SkAndroidFrameworkUtils` と `Sk3DView` camera location methods は `SK_BUILD_FOR_ANDROID_FRAMEWORK` only。
   - Android build target を明示できるまで `na` のまま維持する。

### Phase 8 FontConfig Progress 2026-05-16

`SkFontConfigInterface` 7 行は `RESKIA_ENABLE_FONTCONFIG_CAPI=ON` 配下の guarded provider subset として実装済み。

実施内容:

- `include/ports/SkFontConfigInterface.h`、`src/ports/SkFontConfigInterface.cpp`、`src/ports/SkFontConfigInterface_direct.cpp`、`src/ports/SkFontConfigInterface_direct.h`、`src/ports/SkFontConfigInterface_direct_factory.cpp` を upstream から import した。
- `skia/capi/sk_font_config_interface.h` / `.cpp` を追加し、global registration、provider call wrapper、typeface/stream return handle、`FontIdentity` opaque wrapper を公開した。
- CMake は既存の `RESKIA_ENABLE_FONTCONFIG_CAPI` に閉じ込め、default build には FontConfig direct source と C API を追加しない。
- `test_font_config_interface_utils_smoke` を FontConfig C API 有効時のみ登録した。

検証:

- `cmake -S skia -B skia/cmake-build-codex-phase8-fontconfig -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON -DRESKIA_ENABLE_FONTCONFIG_CAPI=ON`
- `cmake --build skia/cmake-build-codex-phase8-fontconfig --target test_font_config_interface_utils_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase8-fontconfig -R 'c_skia_font_config_interface_utils_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

## Phase 9: High-Volume Optional Modules

目的: 残件数の大きい optional module を、全面公開ではなく実用 entry point と value/helper wrapper に分解して進める。

推奨順:

1. SVG residual
   - まず `SkSVGTypes.h` の value/helper と attribute mutation を整理する。
   - `SkSVGNode` の mutation/query は owned DOM lifetime と borrowed node pointer の関係を明記する。
   - filter/render context と resource provider は skresources/skottie provider 方針と合わせる。
2. GPU residual
   - `02-phase2-gpu-residual-design.md` を更新し、Ganesh residual と Graphite residual を分ける。
   - callback finished proc、backend native state、Vulkan/Dawn/D3D は platform-specific batch に分ける。
   - no-callback value wrappers と simple query から進める。
3. SKSG residual
   - graph ownership、invalidation、node reference cycle を設計してから node factory を広げる。
   - 最初は simple geometry/effect/value helper に限定する。
4. skparagraph / skunicode / skshaper residual
   - `ParagraphPainter` custom painter と `SkShaper` run handler は callback foundation を適用する。
   - `TextStyle` / metrics / placeholder の remaining value helper は低リスク batch として先に進められる。
5. skottie / skresources residual
   - property observer、expression evaluator、text shaper は callback/provider batch。
   - resource provider は SVG と共通語彙に揃える。
6. skplaintexteditor / bentleyottmann
   - editor は paragraph integration の需要確認後。
   - bentleyottmann は public header だが内部 algorithm 色が強いため、実用 entry point が定まるまで低優先。

受け入れ条件:

- optional module ごとに CMake option、source registration、smoke test が対応している。
- provider/callback API は release proc と failure path を smoke で検証する。
- value/helper wrapper は null/invalid input 規約を既存 C API と揃える。

### Phase 9 SVG Value Progress 2026-05-16

Phase 9 の最初の batch として、`SkSVGTypes.h` の value/helper shortlist を実装した。

実施内容:

- `skia/capi/sk_svg_types.h` / `.cpp` を追加した。
- `SkSVGColor`、`SkSVGDashArray`、`SkSVGFeInputType`、`SkSVGFeTurbulenceBaseFrequency`、`SkSVGFillRule`、`SkSVGFontFamily`、`SkSVGFontSize`、`SkSVGFontStyle`、`SkSVGFontWeight`、`SkSVGFuncIRI` の getter / equality helper を C ABI に公開した。
- `sk_svg_types.cpp` は DOM / parser source へ依存しない header-only value subset のため、`svg` target guard ではなく通常 C API source として登録した。
- `test_svg_types_capi_smoke` を追加し、value getter、string return、equality helper、null-safe delete を検証した。

検証:

- `cmake -S skia -B skia/cmake-build-codex-phase8-animated -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
- `cmake --build skia/cmake-build-codex-phase8-animated --target test_svg_types_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase8-animated -R 'c_skia_svg_types_capi_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py`

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2392 |
| `missing` | 908 |
| `partial` | 17 |
| `no_public_methods_found` | 104 |

台帳更新:

- `public-api-svg-missing-triage.csv`: 356 行から 284 行へ縮小。
- `public-api-phase-7-residual-index.csv`: 925 行。
- `public-api-phase-7-triage-routing-index.csv`: 858 行。
- `public-api-phase-9-shortlist.csv`: 60 行。`svg_value_helpers` は完了し、残りは GPU 20、SKSG 15、paragraph 15、SkShaper 10。

### Phase 9 GPU Value/Query Progress 2026-05-16

GPU residual の推奨順 2 件目として、callback / native backend state を必要としない value/query subset を実装した。

実施内容:

- `GrDirectContext::createBackendTexture` の uninitialized overload と color initialization overload を C ABI に公開した。
- `GrDirectContext::createCompressedBackendTexture` の color initialization overload を C ABI に公開した。
- `GrDirectContext::deleteBackendTexture` を C ABI に公開した。
- `GrContextThreadSafeProxy::createCharacterization` の返却値を扱うため、`GrSurfaceCharacterization` owned wrapper と query helper を追加した。
- `test_gpu_context_capi_smoke` を更新し、null-safe path、`GrSurfaceCharacterization` default/copy path、Metal Ganesh context 上の backend texture allocation / delete path を検証した。
- pixmap/data upload overload は exact method-name matching で matrix 上は `covered` になるため、Phase 10 generator polish backlog に overcovered row として残した。

検証:

- `cmake -S skia -B skia/cmake-build-codex-phase9-gpu -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON -DRESKIA_ENABLE_GPU_GANESH=ON -DRESKIA_ENABLE_GPU_METAL=ON`
- `cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8`
- `ctest --test-dir skia/cmake-build-codex-phase9-gpu -R 'c_skia_gpu_context_capi_smoke' --output-on-failure`
- `python3 scripts/generate_public_api_coverage.py --repo . --output docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2406 |
| `missing` | 893 |
| `partial` | 18 |
| `no_public_methods_found` | 104 |

台帳更新:

- `public-api-gpu-missing-triage.csv`: 313 行から 300 行へ縮小。
- `public-api-phase-7-residual-index.csv`: 911 行。
- `public-api-phase-7-triage-routing-index.csv`: 857 行。
- `public-api-phase-9-shortlist.csv`: 48 行。`gpu_no_callback_value_query` は残り 8 行で、主に `MakeMetal` / `MakeVulkan` / `MakeMock` の factory options 設計側。
- `public-api-phase-10-generator-polish-backlog.csv`: 195 行。
- `public-api-phase-10-generator-polish-backlog.csv`: 187 行。SVG value の special-member / operator false positive は今回の equality helper で covered に移った。

次の推奨作業:

1. GPU residual の no-callback value/query 20 行を、既存 `02-phase2-gpu-residual-design.md` と照合する。
2. GPU が platform/native-state に寄りすぎる場合は、SKSG graph ownership design に先に進む。

## Phase 10: Coverage Quality / ABI Polish

目的: 機械 coverage の精度と C API の使いやすさを改善し、実装済みなのに `partial` / `missing` に残る行を減らす。

対象:

- overload-disambiguated C API の generator matching
- Android / platform guard の `na` 表現
- copied/moved/deleted special member と legacy macro の検出
- named operator API と existing generic base API の対応
- C enum 定数の追加
- docs comments の ownership wording 統一

受け入れ条件:

- `partial` が、本当に未実装 overload を意味する行だけになる。
- platform guard による未実装は triage CSV と note で説明できる。
- new API の ownership comment が `owned` / `borrowed` / `consumed` / `retained` の語彙で統一される。

### Phase 10 Generator Override Progress 2026-05-16

Phase 10 の初手として、`scripts/generate_public_api_coverage.py` が `public-api-phase-10-generator-polish-backlog.csv` を読み込むようにした。

目的:

- `false_positive` / `na` を通常の `missing` に混ぜない。
- exact method-name matching による upload overload の過剰 coverage を `overcovered` として見える化する。
- Phase 9 以降の実装判断で、見かけの `missing` / `covered` に引きずられないようにする。

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2400 |
| `missing` | 722 |
| `false_positive` | 161 |
| `na` | 10 |
| `overcovered` | 6 |
| `partial` | 18 |
| `no_public_methods_found` | 104 |

台帳更新:

- `public-api-phase-10-generator-polish-backlog.csv`: 195 行。
- `method_status` を Phase 10 override 後の `false_positive` / `na` / `overcovered` と同期した。
- `overcovered` 6 行は `GrDirectContext::createBackendTexture` / `createCompressedBackendTexture` の pixmap/data upload overload。実装は callback/provider batch 側へ残し、generator では exact method-name covered と区別する。

### Phase 10 Partial Resolution Progress 2026-05-16

Phase 10 backlog の `partial` 18 行を再分類し、coverage matrix の曖昧な `partial` を 0 行にした。

分類:

| status | count | 内容 |
| --- | ---: | --- |
| `split_covered` | 13 | overload / vector / value-object / UTF-8・UTF-16 split helper で実装済み |
| `deferred` | 4 | 設計待ちとして残す実装候補 |
| `false_positive` | 1 | C++ destructor row |

`split_covered` にしたもの:

- `SkCustomTypefaceBuilder::setGlyph` 2 overload
- `Skottie::Animation::seekFrame(double, InvalidationController*)` の default null controller path
- paragraph `getFontFamilies` / `getDecoration`
- skunicode `setText` / `makeBidiIterator` / `computeCodeUnitFlags` の UTF-8 / UTF-16 split helper
- `SkSVGNode::setAttribute(const char*, const char*)`

`deferred` にしたもの:

- `GrDirectContext::dump`
- generic `SkSG::Scene::Make(RenderNode)`
- `SkSVGDOM::renderNode` with custom `SkSVGPresentationContext`
- `SkSVGNode::setAttribute(SkSVGValue)`

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2400 |
| `missing` | 722 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `overcovered` | 6 |
| `deferred` | 4 |
| `partial` | 0 |
| `no_public_methods_found` | 104 |

### Phase 10 Residual Sync / GrDirectContext Dump Progress 2026-05-16

`GrDirectContext::dump` は `SK_ENABLE_DUMP_GPU` guarded API として C ABI に追加した。通常 build では `NULL` を返し、dump 有効 build では owned `reskia_string_t *` を返す。これにより debug-only な機能 guard を C ABI 上で安定させつつ、coverage 上は実装済みとして扱える。

実施内容:

- `GrDirectContext_dump` を追加。
- GPU context smoke test に `NULL` input と valid context path を追加。
- `GrDirectContext::dump` を Phase 10 backlog / Phase 7 residual index / Phase 7 routing index / GPU triage から削除。
- Phase 7 residual / routing index の status を現行 matrix に同期し、`partial` 残りを 0 行にした。

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2401 |
| `missing` | 722 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `overcovered` | 6 |
| `deferred` | 3 |
| `partial` | 0 |
| `no_public_methods_found` | 104 |

台帳:

| file | rows | note |
| --- | ---: | --- |
| `public-api-phase-10-generator-polish-backlog.csv` | 194 | `false_positive` / `split_covered` / `na` / `overcovered` / `deferred` |
| `public-api-phase-7-residual-index.csv` | 916 | matrix status 同期済み |
| `public-api-phase-7-triage-routing-index.csv` | 865 | matrix status 同期済み |
| `public-api-gpu-missing-triage.csv` | 299 | `GrDirectContext::dump` 削除済み |

残る Phase 10 実装・設計候補:

- `overcovered` 6 行: `GrDirectContext::createBackendTexture` / `createCompressedBackendTexture` の pixmap / raw data upload overload。
- `deferred` 3 行: generic `SkSG::Scene::Make(RenderNode)`、custom presentation context 付き `SkSVGDOM::renderNode`、`SkSVGNode::setAttribute(SkSVGValue)`。

### Phase 10 SVG Presentation Context Progress 2026-05-16

`SkSVGDOM::renderNode(SkCanvas*, SkSVGPresentationContext&, const char*)` は `SkSVGPresentationContext` の owned wrapper を最小公開し、custom context を渡せる `SkSVGDOM_renderNode` として C ABI に追加した。

実施内容:

- `SkSVGPresentationContext_new` / `SkSVGPresentationContext_copy` / `SkSVGPresentationContext_delete` を追加。
- `SkSVGDOM_renderNode` を追加。
- SVG DOM smoke test に presentation context lifecycle と custom-context render path を追加。
- `SkSVGDOM::renderNode` と `SkSVGPresentationContext` constructor / copy constructor 行を Phase 7 residual index / Phase 7 routing index / SVG triage から削除。
- `SkSVGDOM::renderNode` を Phase 10 backlog から削除。

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2404 |
| `missing` | 720 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `overcovered` | 6 |
| `deferred` | 2 |
| `partial` | 0 |
| `no_public_methods_found` | 104 |

台帳:

| file | rows | note |
| --- | ---: | --- |
| `public-api-phase-10-generator-polish-backlog.csv` | 193 | `false_positive` / `split_covered` / `na` / `overcovered` / `deferred` |
| `public-api-phase-7-residual-index.csv` | 913 | matrix status 同期済み |
| `public-api-phase-7-triage-routing-index.csv` | 862 | matrix status 同期済み |
| `public-api-svg-missing-triage.csv` | 281 | `SkSVGDOM::renderNode` / `SkSVGPresentationContext` covered rows 削除済み |

残る Phase 10 実装・設計候補:

- `overcovered` 6 行: `GrDirectContext::createBackendTexture` / `createCompressedBackendTexture` の pixmap / raw data upload overload。
- `deferred` 2 行: generic `SkSG::Scene::Make(RenderNode)`、`SkSVGNode::setAttribute(SkSVGValue)`。

### Phase 10 SVG Value Attribute Progress 2026-05-16

`SkSVGNode::setAttribute(SkSVGAttribute, const SkSVGValue&)` は、C ABI 用の owned `reskia_svg_value_t` holder を経由して公開した。`SkSVGWrapperValue` は stack-only なので、holder は color / length / number / string の基本値を保持し、呼び出し時に Skia の wrapper value へ変換する。

実施内容:

- `SkSVGValue_newColor` / `SkSVGValue_newLength` / `SkSVGValue_newNumber` / `SkSVGValue_newString` / `SkSVGValue_delete` / `SkSVGValue_type` を追加。
- `SkSVGNode_setAttribute` を追加。
- SVG DOM smoke test に value lifecycle と typed attribute set path を追加。
- `SkSVGNode::setAttribute(SkSVGValue)` と `SkSVGValue::type` を Phase 7 residual index / Phase 7 routing index / SVG triage から削除。
- `SkSVGNode::setAttribute(SkSVGValue)` を Phase 10 backlog から削除。

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2406 |
| `missing` | 719 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `overcovered` | 6 |
| `deferred` | 1 |
| `partial` | 0 |
| `no_public_methods_found` | 104 |

台帳:

| file | rows | note |
| --- | ---: | --- |
| `public-api-phase-10-generator-polish-backlog.csv` | 192 | `false_positive` / `split_covered` / `na` / `overcovered` / `deferred` |
| `public-api-phase-7-residual-index.csv` | 911 | matrix status 同期済み |
| `public-api-phase-7-triage-routing-index.csv` | 860 | matrix status 同期済み |
| `public-api-svg-missing-triage.csv` | 279 | `SkSVGNode::setAttribute(SkSVGValue)` / `SkSVGValue::type` covered rows 削除済み |

残る Phase 10 実装・設計候補:

- `overcovered` 6 行: `GrDirectContext::createBackendTexture` / `createCompressedBackendTexture` の pixmap / raw data upload overload。
- `deferred` 1 行: generic `SkSG::Scene::Make(RenderNode)`。

### Phase 10 GPU Upload / SkSG Scene Closeout 2026-05-16

Phase 10 backlog の `overcovered` と `deferred` をすべて解消した。

実施内容:

- `GrDirectContext_createBackendTextureFromPixmaps` / `FromPixmap` / `FromPixmapsTopLeft` / `FromPixmapTopLeft` を追加。
- `GrDirectContext_createCompressedBackendTextureWithData` / `WithCompressionTypeData` を追加。
- `SkSG_RenderNode_MakeSimpleRect` と render node ref/unref/release を追加。
- `SkSG_Scene_Make` を追加し、`SkSG::Scene::Make(sk_sp<RenderNode>)` に対応。
- GPU context smoke test に upload overload の null input path を追加。
- SkSG C API smoke test に generic Scene::Make path を追加。
- Phase 10 backlog から `overcovered` / `deferred` 行を削除。

更新後 snapshot:

| status | count |
| --- | ---: |
| `covered` | 2413 |
| `missing` | 719 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `overcovered` | 0 |
| `deferred` | 0 |
| `partial` | 0 |
| `no_public_methods_found` | 104 |

台帳:

| file | rows | note |
| --- | ---: | --- |
| `public-api-phase-10-generator-polish-backlog.csv` | 185 | `false_positive` / `split_covered` / `na` のみ |
| `public-api-phase-7-residual-index.csv` | 904 | matrix status 同期済み |
| `public-api-phase-7-triage-routing-index.csv` | 853 | matrix status 同期済み |

Phase 10 の coverage quality / overload polish / deferred small-gap cleanup は完了。残る `missing` 719 行は後続 phase の実装・分類対象として扱う。

## Phase 11+ Handoff

Phase 10 完了後の計画は `08-post-phase10-coverage-expansion-plan-2026-05-16.md` に引き継ぐ。

Phase 10 closeout 時点:

| status | count |
| --- | ---: |
| `covered` | 2413 |
| `missing` | 719 |
| `false_positive` | 162 |
| `split_covered` | 13 |
| `na` | 10 |
| `partial` | 0 |
| `overcovered` | 0 |
| `deferred` | 0 |
| `no_public_methods_found` | 104 |

Phase 11 以降の大枠:

| phase | theme |
| --- | --- |
| Phase 11 | GPU backend and context expansion |
| Phase 12 | SVG and SkSG graph expansion |
| Phase 13 | Text stack expansion |
| Phase 14 | Callback / provider / registration batch |
| Phase 15 | Platform/internal NA sweep |
| Phase 16 | Coverage audit and generator refresh |
