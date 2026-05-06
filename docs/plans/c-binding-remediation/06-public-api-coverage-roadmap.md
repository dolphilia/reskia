# 06 Public API Coverage Roadmap

- 作成日時: 2026-05-06
- 作業開始時刻: 2026-05-06 20:30:29 JST
- 入力:
  - `scripts/generate_public_api_coverage.py`
  - `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
  - `docs/plans/c-binding-remediation/checklists/public-api-core-effects-missing-triage.csv`
  - `docs/notes/bindings/public-api-coverage-matrix-progress-2026-05-06.md`
  - `docs/notes/bindings/core-effects-missing-triage-2026-05-06.md`

## 目的

Skia の公開クラスについて、公開メソッドと static factory/helper を可能な限り C ABI に露出する方針を、実装順序に落とし込む。

この計画では、単に missing 数が多い領域から着手するのではなく、以下を優先する。

1. 既存 C API に TODO やコメントアウトがあるもの。
2. 実装が局所的で ABI/所有権設計のリスクが低いもの。
3. core/effects のように coverage が高く、残りを減らす効果が読みやすいもの。
4. callback、async、GPU、optional module など設計が重いものは専用フェーズへ分離する。

## 現状

`public-api-coverage-matrix.csv` の機械照合結果:

| 指標 | 件数 |
| --- | ---: |
| matrix rows | 2446 |
| `covered` | 1082 |
| `partial` | 1 |
| `missing` | 1235 |
| `no_public_methods_found` | 128 |

`include/core` / `include/effects` の missing triage:

| area | missing rows | real_gap | na | false_positive |
| --- | ---: | ---: | ---: | ---: |
| `include/core` | 118 | 36 | 25 | 57 |
| `include/effects` | 9 | 0 | 2 | 7 |
| total | 127 | 36 | 27 | 64 |

`real_gap` 優先度:

| priority | 件数 |
| --- | ---: |
| `P1` | 1 |
| `P2` | 16 |
| `P3` | 19 |

## 作業原則

- `public-api-coverage-matrix.csv` は生成物として扱い、手編集しない。
- 実装対象の確定は triage CSV または個別調査メモで行う。
- C API 追加時は、所有権を名前と型で表す。
  - borrowed pointer
  - retained/refcounted handle
  - owned/release
  - value handle
  - out parameter + `reskia_status_t`
- callback を含む API は、同期/非同期、context lifetime、callback thread、payload ownership を設計してから実装する。
- platform/feature macro guarded API は、CMake option と source registration まで含めて扱う。
- 1 PR/1作業単位は小さくし、configure/build を必ず通す。

## Phase A: 低リスク core gap の解消

目的: `include/core` の `real_gap` のうち、callback/async/GPU を含まない局所 API を先に埋める。

対象候補:

| priority | API | 作業内容 |
| --- | --- | --- |
| P1 | `SkImage::imageInfo` | `SkImage_imageInfo` を実装し、戻り値を `sk_image_info_t` または既存 `reskia_image_info_t` 規約へ合わせる。 |
| P0 | `SkPathBuilder::countVerbs` | Phase A 再確認で private method と判明。バインディング対象外として generator を修正する。 |
| P2 | `SkYUVAInfo::GetYUVALocations` | コメントアウト済み API を再設計し、C ABI で返せる型にする。 |
| P2 | `SkNullWStream` constructor | `SkNullWStream_new` / `delete` または stream handle 化を追加する。 |
| P2 | `SkOverdrawCanvas` constructor | 既存 `onDraw*` / `delete` と整合する `SkOverdrawCanvas_new` を追加する。 |
| P2 | `SkRasterHandleAllocator::MakeCanvas` | `SkRasterHandleAllocator_MakeCanvas` を追加し、戻り値 canvas の所有権を明確化する。 |

受け入れ条件:

- 対象 API が `skia/capi` に追加される。
- 対応 header/cpp が `cmake/reskia/sources-capi.cmake` の現行登録と整合する。
- `public-api-core-effects-missing-triage.csv` の対象行を実装済みとして再評価できる。
- `cmake -S skia ...` / `cmake --build ...` が成功する。

推奨順:

1. `SkImage::imageInfo`
2. `SkPathBuilder::countVerbs`
3. `SkYUVAInfo::GetYUVALocations`
4. `SkNullWStream`
5. `SkOverdrawCanvas`
6. `SkRasterHandleAllocator::MakeCanvas`

### Phase A progress 2026-05-06

実装済み:

- `SkImage::imageInfo` -> `SkImage_imageInfo`
- `SkYUVAInfo::GetYUVALocations` -> `SkYUVAInfo_GetYUVALocations`
- `SkNullWStream` constructor -> `SkNullWStream_new`
- `SkOverdrawCanvas` constructor -> `SkOverdrawCanvas_new`
- `SkRasterHandleAllocator::MakeCanvas` -> `SkRasterHandleAllocator_MakeCanvas`

再分類:

- `SkPathBuilder::countVerbs` は `vendor/skia-upstream/include/core/SkPathBuilder.h` で `private:` 節にあるため、公開 API ではない。`scripts/generate_public_api_coverage.py` は inline method body の後ろに続く `private:` 節を同一 statement に混ぜていたため、`}` で文を区切るように修正した。

検証:

- `python3 -m py_compile scripts/generate_public_api_coverage.py`
- `python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`

所有権メモ:

- `SkRasterHandleAllocator_MakeCanvas` は C ABI に渡された `reskia_raster_handle_allocator_t*` の所有権を引き取る。これは upstream API が `std::unique_ptr<SkRasterHandleAllocator>` を消費するため。呼び出し後、成功/失敗にかかわらず caller は allocator を delete してはいけない。
- 戻り値は `sk_canvas_t`。`0` は失敗、非 0 は `static_sk_canvas_delete` で解放する static canvas handle。

Phase A は完了。

## Phase B: named comparison API のまとめ実装

目的: C++ operator として検出された P3 real gap を、C ABI 向け named API としてまとめて処理する。

対象候補:

- `SkFont::operator==` / `operator!=`
- `SkColorInfo::operator==` / `operator!=`
- `SkImageInfo::operator==`
- `SkM44::operator==` / `operator!=`
- `SkRegion::operator==` / `operator!=`
- `SkYUVAInfo::operator==` / `operator!=`
- `SkYUVAPixmapInfo::operator==` / `operator!=`

命名案:

- `*_equals`
- `*_notEquals`

実装方針:

- `notEquals` は C++ `operator!=` を直接呼ぶか、`!equals` で実装する。
- 既存 API に `equals` 相当がある型は重複を避ける。
- 値型 handle と pointer 型が混在するため、型ごとの既存 C API 規約に合わせる。

受け入れ条件:

- operator missing が named API として解消される。
- generator 側は operator を named API 候補として扱えるよう改善する。
- `public-api-coverage-matrix.csv` 再生成後、対象 API が `covered` または `partial` へ移る。

### Phase B progress 2026-05-06

実装済み:

- `SkFont::operator==` / `operator!=` -> `SkFont_equals` / `SkFont_notEquals`
- `SkColorInfo::operator==` / `operator!=` -> `SkColorInfo_equals` / `SkColorInfo_notEquals`
- `SkImageInfo::operator==` / `operator!=` -> `SkImageInfo_equals` / `SkImageInfo_notEquals`
- `SkM44::operator==` / `operator!=` -> `SkM44_equals` / `SkM44_notEquals`
- `SkRegion::operator==` / `operator!=` -> `SkRegion_equals` / `SkRegion_notEquals`
- `SkYUVAInfo::operator==` / `operator!=` -> `SkYUVAInfo_equals` / `SkYUVAInfo_notEquals`
- `SkYUVAPixmapInfo::operator==` / `operator!=` -> `SkYUVAPixmapInfo_equals` / `SkYUVAPixmapInfo_notEquals`

生成器:

- `scripts/generate_public_api_coverage.py` の `method_token` で `operator==` を `equals`、`operator!=` を `notEquals`、`operator=` を `assign` として扱うようにした。これにより named comparison API が matrix 上で `covered` として追跡できる。

検証:

- `python3 -m py_compile scripts/generate_public_api_coverage.py`
- `python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`

Phase B は完了。

## Phase C: callback/registration API の設計

目的: callback または registration を含む public API を、所有権と lifetime を明確にした上で C ABI 化する。

対象候補:

- `SkFont::getPaths`
- `SkGraphics::SetImageGeneratorFromEncodedDataFactory`
- `SkTypeface::Register`
- `SkRegion::toString`

注意:

- `SkFont::getPaths` は callback に `SkPath*` と `SkMatrix&` が渡る。
- `SkGraphics::SetImageGeneratorFromEncodedDataFactory` と `SkTypeface::Register` は global registration であり、callback の lifetime と置換時の挙動が重要。
- `SkRegion::toString` は返却文字列の解放方法を C ABI として決める必要がある。

成果物:

- callback ABI 設計メモ
- `reskia_status_t` / out parameter / borrowed pointer の使い分け
- 必要なら `reskia_ffi` 側の safe wrapper 方針

受け入れ条件:

- callback context の所有権が文書化される。
- 少なくとも 1 つの callback API に smoke test を追加する。
- 既存 LuaJIT/Rust 利用を壊さない。

## Phase D: async read API の専用フェーズ

目的: `SkImage` / `SkSurface` の async read 系 TODO をまとめて設計・実装する。

対象:

- `SkImage::asyncRescaleAndReadPixels`
- `SkImage::asyncRescaleAndReadPixelsYUV420`
- `SkImage::asyncRescaleAndReadPixelsYUVA420`
- `SkSurface::asyncRescaleAndReadPixels`
- `SkSurface::asyncRescaleAndReadPixelsYUV420`
- `SkSurface::asyncRescaleAndReadPixelsYUVA420`

設計論点:

- callback function pointer と context の lifetime
- `AsyncReadResult` の C API 表現
- result data の borrowed/owned 境界
- callback 実行 thread と reentrancy
- GPU context/recorder 依存
- cancellation 不可でよいか

推奨方針:

1. sync read 系と同じ入力型を使えるところは合わせる。
2. callback result は opaque wrapper にし、callback 内でだけ有効な borrowed object とするか、retain/take 可能にするかを明確化する。
3. まず raster/simple path の smoke を作る。

## Phase E: generator 精度改善

目的: `public-api-coverage-matrix.csv` の false positive を減らし、coverage 指標を実作業により近づける。

改善候補:

- `= delete` / `= default` / destructor / assignment operator を初期分類で分ける。
- protected/private の同一行混在をより正確に扱う。
- `#ifdef` guarded API を `conditional` として出力する。
- C API 側のコメントアウト TODO を `known_todo` として拾う。
- operator `==` / `!=` を `*_equals` / `*_notEquals` 候補へ map する。
- class fullname と namespace を保持する。
- 将来的に libclang など AST ベース抽出へ移行する。

受け入れ条件:

- `include/core` / `include/effects` の false positive が明確に減る。
- triage CSV の手動補正量が減る。
- generator の出力列に `generated_classification` または `reason` を追加できる。

## Phase F: GPU public API の最小 coverage

目的: `include/gpu` の missing 302 件を一気に埋めようとせず、Ganesh/Graphite の実用最小単位を切り出す。

初期候補:

- `GrDirectContext`
- `GrRecordingContext`
- `GrBackendTexture`
- `GrBackendRenderTarget`
- `GrBackendSemaphore`
- `GrBackendFormat`
- backend context/info structs
- Graphite `Context` / `Recorder` / `Recording`

方針:

- CMake option と backend dependency を前提にする。
- Metal/Vulkan/Dawn/D3D/GL を同時に扱わない。
- まず Apple + Metal または既存で最も通しやすい backend を基準にする。
- smoke test は backend availability を検出して conditional にする。

受け入れ条件:

- GPU backend surface/context の最小 creation/query path が C API から使える。
- `RESKIA_ENABLE_GPU_*` の制約と文書が一致する。

## Phase G: text / paragraph / unicode

目的: `modules/skparagraph`, `modules/skshaper`, `modules/skunicode` の coverage を、実用 API 単位で上げる。

初期候補:

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

注意:

- `RESKIA_ENABLE_SKPARAGRAPH=ON` は Apple + source mode + HarfBuzz 前提。
- Unicode/shaping は依存縮退条件が多い。
- API coverage とビルド可能性を同時に追う必要がある。

## Phase H: skottie / skresources / sksg / svg

目的: optional module の coverage を、全面バインディングではなく実用 workflow ごとに増やす。

skottie:

- property observer
- slot manager
- resource provider
- text shaper

skresources:

- `ResourceProvider`
- `FileResourceProvider`
- `CachingResourceProvider`
- `DataURIResourceProviderProxy`

sksg:

- Scene 以外の node/effect/paint/geometry の所有権モデルを設計する。
- 既存 `SkSG_Scene_*` は minimal bridge なので、全面化は別フェーズ扱いにする。

svg:

- まず `SkSVGDOM` の load/render/resource 解決を対象にする。
- DOM node 全面露出は後続フェーズにする。

## Coverage 更新手順

各実装フェーズ後に次を実施する。

```bash
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
python3 - <<'PY'
import csv, collections
rows=list(csv.DictReader(open('docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv')))
c=collections.Counter(r['method_status'] for r in rows)
denom=c['covered']+c['partial']+c['missing']
print(c)
print(round((c['covered']+0.5*c['partial'])/denom*100, 1))
PY
```

必要に応じて、該当 area の triage CSV も更新する。

## 最初の実装バッチ案

最初の 1 バッチは、callback/async を避けて次の 3 件に絞る。

1. `SkImage::imageInfo`
2. `SkPathBuilder::countVerbs`
3. `SkYUVAInfo::GetYUVALocations`

理由:

- すべて `include/core` の real gap。
- 既存 C API ファイルがある。
- 既存コメント/TODO があるものを含む。
- 所有権設計が比較的局所的。

このバッチ完了後、coverage matrix を再生成し、`public-api-core-effects-missing-triage.csv` を更新する。
