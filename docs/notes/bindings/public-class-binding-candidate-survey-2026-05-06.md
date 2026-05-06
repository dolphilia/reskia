# Public Class Binding Candidate Survey

- 作成日時: 2026-05-06
- 作業開始時刻: 2026-05-06 19:49:15 JST
- 対象リポジトリ: `/Users/dolphilia/github/reskia`
- 参照 Skia: `vendor/skia-source.lock`
  - upstream: `https://github.com/google/skia.git`
  - ref: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
  - baseline date: `2026-02-14`

## 前提

前回調査の結論どおり、Reskia の C API バインディングは、Skia の公開クラスについて「公開メソッドと static factory/helper を可能な限り C ABI に露出する」方針で進められていると見る。

この前提に立つと、今後の残作業は「Skia の公開ヘッダにある class/struct のうち、まだ `skia/capi` に対応する API がないものをどれだけ拾うか」という問題になる。

## 調査方法

母集団は次の公開ヘッダに限定した。

- `vendor/skia-upstream/include/**`
- `vendor/skia-upstream/modules/*/include/**`

以下は残量見積もりから外した。

- `vendor/skia-upstream/src/**`
- `vendor/skia-upstream/include/private/**`
- generated/internal 実装ヘッダ

判定は静的なテキスト走査で行った。

- `class` / `struct` 定義候補を抽出する。
- `skia/capi/*.h`, `skia/capi/*.cpp`, `skia/handles/static_*` に対応するファイル名または `ClassName_` 形式の関数があれば「実体バインディング済みらしい」と判定する。
- 型名だけが C API 側に出るものは「参照のみ/部分対応」と判定する。
- どちらもないものを「未対応候補」と判定する。

注意点:

- C++ AST ではなくテキスト走査のため、nested struct、namespace 内 class、同名 `Options` などは過不足があり得る。
- `skia/capi` が helper namespace だけをまとめている場合、対応ファイル名だけでは網羅性を完全には判断できない。
- `skia/capi` に型名が出るだけでは、公開メソッドを C ABI に露出しているとは限らない。
- したがって、本メモの数値は「残量の上限に近い概算」として扱う。

## 全体集計

公開ヘッダの top-level class/struct 候補を重複排除した結果は次の通り。

| 区分 | 件数 | 意味 |
| --- | ---: | --- |
| 公開ヘッダ | 357 | `include/**` と `modules/*/include/**` |
| top-level class/struct 候補 | 420 | 公開バインディング対象になり得る型 |
| 実体バインディング済みらしい | 127 | C API ファイル/関数または handle がある |
| 参照のみ/部分対応 | 33 | C API 内に型名は出るが、対応 API は薄い可能性がある |
| 未対応候補 | 260 | C API 側で対応が見つからない |

厳しめに見るなら、今後の候補は `260 + 33 = 293` 件ある。型名参照だけでも partial support とみなすなら、未対応候補は 260 件である。

ただし、この 260 件の大半は optional module、GPU backend、SVG DOM 内部型、utility/port 型であり、`include/core` の主要型はかなり埋まっている。

## 領域別集計

| 領域 | 候補 | 実体あり | 参照のみ | 未対応候補 |
| --- | ---: | ---: | ---: | ---: |
| `include/core` | 98 | 88 | 5 | 5 |
| `include/effects` | 25 | 23 | 0 | 2 |
| `include/codec` | 4 | 2 | 2 | 0 |
| `include/encode` | 4 | 1 | 3 | 0 |
| `include/pathops` | 1 | 1 | 0 | 0 |
| `include/gpu` | 67 | 0 | 14 | 53 |
| `include/utils` | 15 | 0 | 0 | 15 |
| `include/ports` | 6 | 0 | 0 | 6 |
| `include/docs` | 5 | 0 | 2 | 3 |
| `include/android` | 2 | 0 | 0 | 2 |
| `include/svg` | 1 | 0 | 0 | 1 |
| `include/sksl` | 1 | 0 | 0 | 1 |
| `modules/svg` | 79 | 0 | 0 | 79 |
| `modules/sksg` | 48 | 9 | 4 | 35 |
| `modules/skparagraph` | 21 | 1 | 0 | 20 |
| `modules/skottie` | 14 | 0 | 1 | 13 |
| `modules/skresources` | 8 | 0 | 0 | 8 |
| `modules/skshaper` | 2 | 1 | 1 | 0 |
| `modules/skunicode` | 3 | 0 | 0 | 3 |
| `modules/bentleyottmann` | 13 | 1 | 1 | 11 |
| `modules/skplaintexteditor` | 3 | 0 | 0 | 3 |

## 主要領域の評価

### include/core

`include/core` は 98 件中 88 件が実体ありと判定され、Reskia の主戦場としてかなり進んでいる。残りは 5 件だけである。

未対応候補:

- `SkNullWStream`
- `SkCanvasVirtualEnforcer`
- `SkDrawLooper`
- `SkNVRefCnt`
- `SkRTreeFactory`

参照のみ/部分対応:

- `SkFontParameters`
- `SkRGBA4f`
- `SkBBHFactory`
- `SkSerialProcs`
- `SkDeserialProcs`

`SkCanvasVirtualEnforcer` や `SkNVRefCnt` は直接バインディング価値が低い。`SkNullWStream`, `SkRTreeFactory`, `SkBBHFactory`, `SkSerialProcs` / `SkDeserialProcs` は、既存の stream/document/picture serialization API を厚くする場合に候補になる。

### include/effects

`include/effects` は 25 件中 23 件が実体ありで、かなり埋まっている。

未対応候補:

- `SkBlurMaskFilter`
- `SkLayerDrawLooper`

`SkBlurMaskFilter` は C API 化の価値が高い。既存の `sk_mask_filter`, `sk_table_mask_filter`, `sk_shader_mask_filter` と同じ系統で扱える可能性がある。`SkLayerDrawLooper` は古い/特殊な API なので、優先度は要確認。

### codec / encode

codec/encode は未対応候補が 0 で、主要な decoder/encoder API はすでに C API 側に取り込まれている。

参照のみ/部分対応:

- `SkPngChunkReader`
- `SkCodec::Decoder`
- `SkJpegEncoder::Options`
- `SkWebpEncoder::Options`
- `SkPngEncoder::Options`

この領域の残作業は、新規 class バインディングよりも options struct の完全性、callback、所有権、条件付き source 登録の整理が中心になる。

### include/gpu

`include/gpu` は 67 件中、実体バインディング済み判定が 0 件、参照のみが 14 件、未対応候補が 53 件である。ここが公開ヘッダ側の最大の未対応領域である。

参照のみ/部分対応の代表:

- `GrDirectContext`
- `GrRecordingContext`
- `GrBackendTexture`
- `GrBackendRenderTarget`
- `GrBackendSemaphore`
- Graphite の `Context`, `Recorder`, `Recording`, `BackendTexture`, `ContextOptions`
- Vulkan/Metal backend context 系

未対応候補の代表:

- `GrContextThreadSafeProxy`
- `GrContextOptions`
- `GrBackendFormat`
- `GrFlushInfo`
- `MutableTextureState`
- `ShaderErrorHandler`
- GL/Vulkan/Metal/D3D backend info struct 群
- Graphite の `BackendSemaphore`, `TextureInfo`, `ImageProvider`, `RecorderOptions`, `YUVABackendTextures`

Reskia 側には `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN` があり、GPU ビルド取り込みの足場はある。ただし C API としては、`sk_surface_gpu.cpp` や `sk_gpu_context.cpp` で部分的に触れている段階で、公開 GPU class の全面バインディングはまだこれからである。

優先するなら、まず次の順が自然である。

1. `GrDirectContext`
2. `GrRecordingContext`
3. `GrBackendTexture`
4. `GrBackendRenderTarget`
5. `GrBackendSemaphore`
6. backend context/info structs
7. Graphite `Context` / `Recorder` / `Recording`

ただし GPU は platform/backend 依存が強いため、C API 化だけでなく CMake option、依存検出、テスト行列も同時に必要になる。

### modules/svg

`modules/svg` は 79 件すべてが未対応候補である。ここには `SkSVGDOM` だけでなく、SVG DOM node、attribute、filter、paint、text、gradient、render context など多数の型が含まれる。

代表候補:

- `SkSVGDOM`
- `SkSVGNode`
- `SkSVGRenderContext`
- `SkSVGLengthContext`
- `SkSVGRect`
- `SkSVGCircle`
- `SkSVGPath`
- `SkSVGText`
- `SkSVGImage`
- `SkSVGGradient`
- `SkSVGFilter`
- `SkSVGOpenTypeSVGDecoder`

Reskia には `sk_open_type_svg_decoder.cpp` はあるが、SVG DOM module 全体を公開 C API として扱う層はまだない。現実的には全 79 型を一気に対象にするより、まず `SkSVGDOM` の load/render と、必要最小限の resource/stream integration を公開する方がよい。

### modules/sksg

`modules/sksg` は 48 件中、実体あり 9 件、参照のみ 4 件、未対応候補 35 件である。

既存の `skia/capi/sk_sksg.cpp` は、`SkSG_Scene_MakeSimpleRect`, `SkSG_Scene_render`, `SkSG_Scene_revalidate` などの最小 API を提供している。これは sksg 全体の class を広く C API 化するというより、Scene を扱う smoke/minimal bridge である。

未対応候補の代表:

- `sksg::Node`
- `sksg::RenderNode`
- `sksg::GeometryNode`
- `sksg::PaintNode`
- `sksg::Text`
- `sksg::Transform`
- `sksg::ClipEffect`
- `sksg::OpacityEffect`
- `sksg::ShaderEffect`
- `sksg::ImageFilterEffect`
- `sksg::LinearGradient`
- `sksg::RadialGradient`

`RESKIA_ENABLE_SKSG` は既定 OFF で、C API も条件付き登録である。全面バインディングを目指すなら、Scene Graph の所有権モデルを先に設計する必要がある。

### modules/skparagraph

`modules/skparagraph` は 21 件中、実体あり 1 件、未対応候補 20 件である。

未対応候補:

- `Paragraph`
- `ParagraphBuilder`
- `ParagraphPainter`
- `ParagraphStyle`
- `TextStyle`
- `FontCollection`
- `TypefaceFontProvider`
- `TextShadow`
- `StrutStyle`
- `LineMetrics`
- `TextBox`
- `PositionWithAffinity`
- `PlaceholderStyle`
- `FontFeature`

`cmake/reskia/sources-capi.cmake` では `RESKIA_ENABLE_SKPARAGRAPH` 時に `sk_text_blob_builder_run_handler.cpp` だけが追加される。つまり paragraph module の実 API はまだほぼ未バインディングである。

ただし `RESKIA_ENABLE_SKPARAGRAPH=ON` は現在 Apple + source mode + HarfBuzz 前提で、CMake 制約が重い。バインディングを増やす場合も、先に依存条件と smoke test を固めるべきである。

### modules/skottie

`modules/skottie` は 14 件中、参照のみ 1 件、未対応候補 13 件である。

既存の `skia/capi/sk_skottie.cpp` は `Skottie_Animation_Make`, `render`, `seek`, `duration`, `fps`, `width`, `height` などを提供しており、`skottie::Animation` の利用 API はある。しかし静的判定上はファイル名/関数名が `Skottie_Animation_` 形式なので、class 全体の実体バインディングとしては限定的である。

未対応候補の代表:

- `ExternalLayer`
- `PrecompInterceptor`
- `PropertyHandle`
- `PropertyObserver`
- `SlotManager`
- `Logger`
- `ExpressionEvaluator`
- `ExpressionManager`
- `MarkerObserver`
- `TextPropertyValue`
- `TransformPropertyValue`
- `Shaper`

skottie はまず animation の基本操作があり、次の拡張候補は property observer、slot manager、resource provider、text shaper になる。

### modules/skresources

`modules/skresources` は 8 件すべてが未対応候補である。

候補:

- `ImageAsset`
- `MultiFrameImageAsset`
- `ExternalTrackAsset`
- `ResourceProvider`
- `FileResourceProvider`
- `ResourceProviderProxyBase`
- `CachingResourceProvider`
- `DataURIResourceProviderProxy`

skottie/svg を実用化するなら、resource provider 系は優先候補になる。単独で C API 化するより、skottie/svg の入力解決 API とセットで設計するのがよい。

### modules/skshaper / skunicode

`modules/skshaper` は 2 件中、`SkShaper` が参照のみ、もう 1 件は実体あり判定になった。`modules/skunicode` は 3 件すべて未対応候補である。

候補:

- `SkShaper`
- `SkUnicode`
- `SkBidiIterator`
- `SkBreakIterator`

`SkShaper` / `SkUnicode` は paragraph/text shaping の中核なので、`RESKIA_ENABLE_SKPARAGRAPH` の拡張と同時に扱うのが自然である。

### include/utils / include/ports / include/android / docs

この領域は合計で 26 件程度の未対応候補がある。

代表候補:

- `SkTextUtils`
- `SkParsePath`
- `SkShadowUtils`
- `SkNWayCanvas`
- `SkNoDrawCanvas`
- `SkPaintFilterCanvas`
- `SkEventTracer`
- `SkFontConfigInterface`
- `SkRemotableFontMgr`
- `SkAnimatedImage`
- `SkAndroidFrameworkUtils`
- PDF document metadata/structure 関連

これらは core API より優先度を下げてよい。必要なユースケースが明確なものから個別に拾う方がよい。

## 残量の見方

単純な総数では、今後の公開 class/struct 候補は最大で 293 件ある。

- 未対応候補: 260
- 参照のみ/部分対応: 33

ただし、実務上の優先度で分けると次のようになる。

| 優先層 | 件数目安 | 内容 |
| --- | ---: | --- |
| Core/effects の穴埋め | 10 前後 | `SkBlurMaskFilter`, `SkNullWStream`, serialization/BBH 周辺 |
| GPU/Ganesh/Graphite | 60-70 | context, backend texture/render target/semaphore, backend info |
| text/shaping/paragraph | 25 前後 | `Paragraph`, `TextStyle`, `FontCollection`, `SkShaper`, `SkUnicode` |
| skottie/resources 実用拡張 | 20 前後 | property/resource/slot/text shaper |
| sksg 全面化 | 35-40 | scene graph node/effect/paint/geometry |
| SVG DOM 全面化 | 80 前後 | `SkSVGDOM` と DOM node/attribute/filter 群 |
| utils/ports/android/docs | 25 前後 | utility/port/platform/document 補助 API |

つまり、主要描画 core の残量は小さいが、Skia の公開面全体を対象にすると、optional subsystem と GPU を中心にまだ大きな残りがある。

## 次の作業候補

1. Core/effects の小さい穴を先に埋める
   - `SkBlurMaskFilter`
   - `SkNullWStream`
   - `SkBBHFactory` / `SkRTreeFactory`
   - `SkSerialProcs` / `SkDeserialProcs`

2. GPU C API の対象範囲を決める
   - `GrDirectContext` と `GrBackendTexture` / `GrBackendRenderTarget` / `GrBackendSemaphore` を最初の単位にする。
   - Graphite は `Context` / `Recorder` / `Recording` を別フェーズに分ける。

3. Paragraph の最小 API を設計する
   - `FontCollection`
   - `ParagraphStyle`
   - `TextStyle`
   - `ParagraphBuilder`
   - `Paragraph`

4. skottie の実用 API を拡張する
   - property observer
   - slot manager
   - resource provider
   - text shaper

5. SVG は `SkSVGDOM` から始める
   - DOM node 全面バインディングではなく、まず load/render API と resource 解決を優先する。

6. 機械的な coverage 生成を導入する
   - `vendor/skia-upstream` の公開ヘッダから class/method を抽出し、`skia/capi` 関数と対応表を出すスクリプトを作る。
   - 現状のテキスト走査を AST ベースへ寄せると、残量管理の精度が上がる。

## 結論

Reskia は core/effects/codec/encode 周辺ではかなり広く C API バインディングを持っている。一方、Skia の公開クラス全体を「可能な限り露出する」方針で見ると、未対応候補はまだ 260 件程度、参照のみ/部分対応を含めると 293 件程度残っている。

残りの中心は `include/gpu`、`modules/svg`、`modules/sksg`、`modules/skparagraph`、`modules/skottie`、`modules/skresources` である。したがって今後は、core の細かな穴埋めと並行して、GPU・paragraph・skottie/resources・SVG DOM のどこまでを Reskia の公開 API として本気で対象にするかをフェーズ分けして決める必要がある。
