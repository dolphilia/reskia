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

## Phase 2: GPU C API の実用入口

目的: `include/gpu` の全面公開ではなく、Ganesh/Graphite の context、surface、backend object の最小実用経路を安定させる。

現状:

- `skia/capi/sk_gpu_context.*` は Ganesh/Graphite context 作成と release を提供している。
- `skia/capi/sk_surface_gpu.*` は Ganesh/Graphite surface 作成と backend texture/render target wrap を提供している。
- matrix 上は `GrDirectContext`、`GrBackendTexture`、`GrBackendRenderTarget`、`GrBackendSemaphore`、`GrBackendFormat` がほぼ未対応として残る。

優先順:

1. `GrDirectContext` lifecycle/query/cache/flush
   - `resetContext`
   - `abandonContext`
   - `abandoned`
   - `isDeviceLost`
   - `oomed`
   - `getResourceCacheLimits`
   - `getResourceCacheUsage`
   - `setResourceCacheLimits`
   - `freeGpuResources`
   - `performDeferredCleanup`
   - `flush`
   - `submit`
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

## Phase 3: SVG DOM の最小公開

目的: `modules/svg` の 398 missing に対して、まず実用入口である `SkSVGDOM` を C API 化する。

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

## Phase 5: Skottie / skresources / sksg

目的: 既存 minimal bridge を実用 API に拡張する。

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
