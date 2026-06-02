# Public API Coverage Matrix Progress

- 作成日時: 2026-05-06
- 作業開始時刻: 2026-05-06 20:01:41 JST
- 参照 Skia ref: `0d49b661d75adbb8ac8cf88f7d527b1587be2c63`
- 生成スクリプト: `scripts/generate_public_api_coverage.py`
- 生成マトリクス: `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`

## 目的

Skia の公開クラス全体を「可能な限り C ABI に露出する」方針を進めるため、class 単位ではなく public method 単位で進捗を確認できるマトリクスを導入した。

既存の `capi-status.csv` は `skia/capi` のファイル単位で有効だが、次の問いには粒度が足りない。

- upstream Skia の公開 class/struct が Reskia C API に存在するか。
- その class の public method/static method/factory が C API 関数として見つかるか。
- どの class のどの method が未対応候補か。
- optional module や GPU まで含めた残量が領域別にどの程度あるか。

今回追加した `public-api-coverage-matrix.csv` は、この問いに対する作業用チェックリストである。

## 生成方法

```bash
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
```

生成対象:

- `vendor/skia-upstream/include/**`
- `vendor/skia-upstream/modules/*/include/**`

除外対象:

- `vendor/skia-upstream/include/private/**`
- `vendor/skia-upstream/include/third_party/**`
- `vendor/skia-upstream/src/**`

判定方法:

- upstream 公開ヘッダから top-level class/struct と public method 宣言を抽出する。
- `skia/capi/*.h` の C API 関数名を抽出する。
- `ClassName_methodName` 形式、または module bridge 用の prefix を使って照合する。
- `covered`, `partial`, `missing`, `no_public_methods_found` の status を付ける。

この生成は C++ AST ではなく静的なテキスト走査である。したがって、誤検出や過検出はあり得る。特に inline method が複数同一 statement に並ぶ箇所、macro 展開、operator、protected/private が同一行に混ざる箇所は、作業前に upstream header を確認する必要がある。

## マトリクス列

| 列 | 意味 |
| --- | --- |
| `area` | `include/core`, `modules/svg` などの領域 |
| `header` | upstream 側の公開ヘッダ |
| `class` | class/struct 名 |
| `class_kind` | `class` または `struct` |
| `class_line` | class/struct 定義の概算行 |
| `class_status` | class prefix に対応する C API 関数があるか |
| `method` | public method/static method/factory 名 |
| `method_line` | method 宣言の概算行 |
| `method_static` | static method か |
| `method_status` | method 対応状況 |
| `matched_capi` | 見つかった C API 関数名 |
| `signature` | upstream 側の method 宣言抜粋 |
| `note` | 補足 |

## status の意味

| status | 意味 | 作業上の扱い |
| --- | --- | --- |
| `covered` | 対応する C API 関数名が見つかった | 実装内容、所有権、overload 完全性をレビューする |
| `partial` | prefix は見つかるが完全一致ではない | 意味名 API や overload 対応を確認する |
| `missing` | 対応する C API 関数名が見つからない | 未対応候補として優先度付けする |
| `no_public_methods_found` | public method 抽出が 0 件 | value struct、macro、抽出漏れ、対象外のいずれかを確認する |

## 全体集計

今回の生成結果は次の通り。

| 指標 | 件数 |
| --- | ---: |
| matrix 行数 | 2446 |
| class/struct 候補 | 488 |
| method 候補 | 2334 |
| `covered` method | 1082 |
| `partial` method | 1 |
| `missing` method | 1235 |
| `no_public_methods_found` 行 | 128 |
| method coverage 概算 | 46.7% |

coverage は `(covered + 0.5 * partial) / (covered + partial + missing)` で計算した。これは実装品質や overload 完全性ではなく、関数名照合による入口の有無を示す概算である。

## 領域別集計

| area | classes | methods | covered | partial | missing | no methods | coverage |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| `include/android` | 2 | 17 | 0 | 0 | 17 | 0 | 0.0% |
| `include/codec` | 7 | 34 | 33 | 0 | 1 | 4 | 97.1% |
| `include/core` | 117 | 1058 | 939 | 0 | 119 | 33 | 88.8% |
| `include/docs` | 5 | 8 | 0 | 0 | 8 | 3 | 0.0% |
| `include/effects` | 25 | 99 | 90 | 0 | 9 | 3 | 90.9% |
| `include/encode` | 8 | 3 | 2 | 0 | 1 | 7 | 66.7% |
| `include/gpu` | 85 | 302 | 0 | 0 | 302 | 36 | 0.0% |
| `include/pathops` | 1 | 2 | 2 | 0 | 0 | 0 | 100.0% |
| `include/ports` | 7 | 27 | 0 | 0 | 27 | 2 | 0.0% |
| `include/sksl` | 2 | 2 | 0 | 0 | 2 | 1 | 0.0% |
| `include/svg` | 1 | 1 | 0 | 0 | 1 | 0 | 0.0% |
| `include/utils` | 15 | 104 | 0 | 0 | 104 | 0 | 0.0% |
| `modules/bentleyottmann` | 13 | 26 | 0 | 0 | 26 | 6 | 0.0% |
| `modules/skottie` | 15 | 47 | 7 | 0 | 40 | 1 | 14.9% |
| `modules/skparagraph` | 30 | 101 | 0 | 0 | 101 | 11 | 0.0% |
| `modules/skplaintexteditor` | 3 | 18 | 0 | 0 | 18 | 1 | 0.0% |
| `modules/skresources` | 9 | 13 | 0 | 0 | 13 | 3 | 0.0% |
| `modules/sksg` | 48 | 138 | 2 | 1 | 135 | 4 | 1.8% |
| `modules/skshaper` | 2 | 30 | 7 | 0 | 23 | 0 | 23.3% |
| `modules/skunicode` | 4 | 48 | 0 | 0 | 48 | 1 | 0.0% |
| `modules/svg` | 89 | 256 | 0 | 0 | 256 | 12 | 0.0% |

## 読み取れること

`include/core` と `include/effects` は既にかなり進んでいる。method-level の機械照合では、`include/core` が 88.8%、`include/effects` が 90.9% である。これは前回の class-level 調査と整合する。

一方で、全体 coverage は 46.7% に落ちる。理由は明確で、GPU、SVG、paragraph、sksg、skunicode、utils/ports が大きく残っているためである。

特に大きい未対応領域:

- `include/gpu`: 302 missing methods
- `modules/svg`: 256 missing methods
- `modules/sksg`: 135 missing methods
- `include/core`: 119 missing methods
- `include/utils`: 104 missing methods
- `modules/skparagraph`: 101 missing methods
- `modules/skunicode`: 48 missing methods
- `modules/skottie`: 40 missing methods

`include/core` は coverage が高いが、母数が大きいため missing method 数としてはまだ 119 件ある。ただしこの中には operator、macro、copy assignment、対象外に近い protected/internal 系の誤検出も含まれるため、実作業では class ごとに triage する。

## 代表的な未対応候補

### Core

`include/core` の missing は 50 class に分散している。代表例:

- `SkBBHFactory`: destructor, assignment/operator 周辺
- `SkRTreeFactory`: operator 周辺
- `SkBitmap`: assignment/operator 周辺
- `SkCapabilities`: constructor/init 系
- `SkContourMeasure`: constructor/destructor
- `SkDataTable`: `atT`

Core の次作業は、まず missing を `real gap`, `intentional na`, `false positive` に分類することが重要である。

### Effects

代表例:

- `SkBlurMaskFilter::MakeEmboss`
- `SkLayerDrawLooper` destructor 周辺
- `SkRuntimeEffectBuilder` constructor/operator 周辺
- `SkRuntimeColorFilterBuilder` operator 周辺
- `SkRuntimeBlendBuilder` operator 周辺

`SkBlurMaskFilter::MakeEmboss` は実装候補として具体性が高い。

### GPU

代表例:

- `GrDirectContext::MakeVulkan`
- `GrDirectContext::MakeMetal`
- `GrDirectContext::MakeDirect3D`
- `GrBackendTexture` constructor/getter/setter 群
- `GrBackendRenderTarget` constructor/getter/setter 群
- `GrBackendSemaphore` constructor/init 群
- `GrBackendFormat` factory/getter 群
- `GrContextThreadSafeProxy` query/characterization 群

GPU は C API 関数名としてほぼ未照合であり、今後の最大領域である。ただし backend ごとの CMake option と依存検出も必要なので、単純に method を上から埋めるより、backend surface/context の最小セットを先に決めるべきである。

### Paragraph / Shaper / Unicode

代表例:

- `FontCollection`
- `ParagraphStyle`
- `TextStyle`
- `ParagraphBuilder`
- `Paragraph`
- `LineMetrics`
- `TextBox`
- `SkShaper`
- `SkUnicode`
- `SkBidiIterator`
- `SkBreakIterator`

paragraph は公開 API として価値が高いが、HarfBuzz/ICU/skunicode 依存が強い。`RESKIA_ENABLE_SKPARAGRAPH` の制約とセットで進める。

### SVG / sksg / skottie

SVG は `SkSVGDOM` から始めるのが現実的である。全 DOM node を method-level に一気にバインディングするより、まず load/render/resource 解決を C API 化する。

sksg は現在 `SkSG_Scene_*` の最小 bridge があり、matrix 上も coverage は 1.8% に留まる。全面化するなら node/effect/paint/geometry の所有権設計が先に必要である。

skottie は `Skottie_Animation_*` の基本 API はあるが、property observer、slot manager、resource provider、text shaper が未対応候補として残る。

## 運用案

1. `public-api-coverage-matrix.csv` は生成物として扱う
   - 手編集しない。
   - upstream 同期後や C API 追加後に再生成する。

2. 作業対象は matrix から抽出する
   - `method_status=missing` を対象にする。
   - まず `area` と `class` で絞る。
   - upstream header と `skia/capi` 実装を確認して、`real gap`, `na`, `false positive` に分ける。

3. 実作業の進捗管理は既存 checklist に反映する
   - ファイル単位の `capi-status.csv` は維持する。
   - method-level の漏れ確認には matrix を使う。
   - 必要なら将来 `public-api-coverage-triage.csv` を別途作り、`missing` ごとの `todo/done/na/false_positive` を人手で管理する。

4. 生成器を段階的に改善する
   - AST ベース抽出へ移行する。
   - namespace と class fullname を保持する。
   - protected/private の同一行混在をより正確に扱う。
   - overload と意味名 API の対応ルールを明示する。
   - `static factory/helper` の C API 命名候補を増やす。

## 次にやるべきこと

最初の実務タスクは、`include/core` と `include/effects` の missing を triage すること。

理由:

- coverage が高く、残量が比較的局所的。
- optional dependency や platform dependency が少ない。
- false positive と real gap の分類が短時間で進めやすい。
- `SkBlurMaskFilter::MakeEmboss` のように具体的な実装候補が見えている。

次に GPU の最小 API セットを設計する。GPU は missing 数が最大だが、依存と backend 差分が大きいため、matrix の上から機械的に埋めるより、`GrDirectContext`、`GrBackendTexture`、`GrBackendRenderTarget`、`GrBackendSemaphore` を初期フェーズとして切るのがよい。
