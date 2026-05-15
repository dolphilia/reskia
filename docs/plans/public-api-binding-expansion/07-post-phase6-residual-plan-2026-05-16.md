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

## Phase 8: Guarded Platform / Import-Source APIs

目的: Phase 6 で後回しにした platform source import、global/provider ownership、feature guard が必要な API を、既定 build に混ぜずに扱う。

優先順:

1. `SkAnimatedImage`
   - `skia/include/android/SkAnimatedImage.h` は存在するが、`skia/src/android/SkAnimatedImage.cpp` が未 import。
   - `vendor/skia-upstream/src/android/SkAnimatedImage.cpp` を source import するか、Android source set として feature guard するかを先に決める。
   - C API は `SkAndroidCodec` handle を consume し、返却 object は ref-counted `SkDrawable` 派生として unref 解放する。
   - `getCurrentFrame` は retained `sk_image_t` を返す。
2. `SkFontConfigInterface`
   - implementation source (`SkFontConfigInterface.cpp`, direct FontConfig sources) の import/guard が必要。
   - `SetGlobal` は registration replacement と release policy を `01-callback-global-registration-design.md` に合わせる。
   - `FontIdentity` は `SkString` と `SkFontStyle` を含むため、raw struct ではなく opaque value wrapper を優先する。
3. Android framework helpers
   - `SkAndroidFrameworkUtils` と `Sk3DView` camera location methods は `SK_BUILD_FOR_ANDROID_FRAMEWORK` only。
   - Android build target を明示できるまで `na` のまま維持する。

受け入れ条件:

- feature option が OFF のとき未解決 symbol を出さない。
- source import する場合は upstream ref と差分理由を文書化する。
- smoke test は platform guard と同じ条件でのみ登録する。

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
