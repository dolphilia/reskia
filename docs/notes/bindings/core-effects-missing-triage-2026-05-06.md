# Core / Effects Missing API Triage

- 作成日時: 2026-05-06
- 作業開始時刻: 2026-05-06 20:13:09 JST
- 元マトリクス: `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- 仕分け結果: `docs/plans/c-binding-remediation/checklists/public-api-core-effects-missing-triage.csv`
- 対象: `area=include/core` / `area=include/effects` かつ `method_status=missing`

## 目的

`public-api-coverage-matrix.csv` の `missing` は機械照合の結果であり、そのまま実装漏れとは限らない。今回、まず `include/core` と `include/effects` について、各 missing method を次の 3 種類に仕分けた。

| triage | 意味 |
| --- | --- |
| `real_gap` | 実際に C API 追加候補として扱うべき公開 API |
| `na` | 公開ヘッダには出るが、抽象基底、subclass hook、internal/private helper、条件付き legacy API などの理由で通常の C ABI 対象外 |
| `false_positive` | 抽出器の粗さ、operator/特殊メンバ、既存 named API で代替済み、private/protected の取り違えなど |

## 集計

| area | missing rows | real_gap | na | false_positive |
| --- | ---: | ---: | ---: | ---: |
| `include/core` | 118 | 36 | 25 | 57 |
| `include/effects` | 9 | 0 | 2 | 7 |
| total | 127 | 36 | 27 | 64 |

`real_gap` の優先度内訳:

| priority | 件数 |
| --- | ---: |
| `P1` | 1 |
| `P2` | 16 |
| `P3` | 19 |

## P1 real gap

| class | method | 理由 |
| --- | --- | --- |
| `SkImage` | `imageInfo` | `skia/capi/sk_image.h` に明示 TODO が残っている。戻り値は `SkImageInfo` なので既存 handle/値型 API と整合させやすい。 |

## P2 real gaps

| class | method | 理由 |
| --- | --- | --- |
| `SkRTreeFactory` | `operator()` | `SkPictureRecorder_beginRecording*WithFactory` が `SkBBHFactory*` を受ける一方、具体 factory の作成 API がない。 |
| `SkFont` | `getPaths` | glyph path callback API が未露出。callback ABI の設計が必要。 |
| `SkGraphics` | `SetImageGeneratorFromEncodedDataFactory` | global callback registration API。callback/所有権設計が必要。 |
| `SkImage` | `asyncRescaleAndReadPixels` | C API 側にも TODO コメントあり。callback/lifetime ABI が必要。 |
| `SkImage` | `asyncRescaleAndReadPixelsYUV420` | 同上。 |
| `SkImage` | `asyncRescaleAndReadPixelsYUVA420` | 同上。 |
| `SkMeshSpecification` | `MakeFromSourceWithStructs` | public static factory overload が未露出。 |
| `SkOverdrawCanvas` | constructor | `onDraw*` と delete はあるが、作成 API がない。 |
| `SkPathBuilder` | `countVerbs` | `countPoints` 系と並ぶ public getter。 |
| `SkRasterHandleAllocator` | `MakeCanvas` | public static factory が未露出。 |
| `SkRegion` | `toString` | string ownership 設計が必要。 |
| `SkNullWStream` | constructor | public no-op stream sink が作成できない。 |
| `SkSurface` | `asyncRescaleAndReadPixels` | C API 側にも TODO コメントあり。callback/lifetime ABI が必要。 |
| `SkSurface` | `asyncRescaleAndReadPixelsYUV420` | 同上。 |
| `SkSurface` | `asyncRescaleAndReadPixelsYUVA420` | 同上。 |
| `SkYUVAInfo` | `GetYUVALocations` | `skia/capi/sk_yuva_info.h` でコメントアウトされている public static helper。 |

## P3 real gaps

P3 は低優先の公開 API 漏れである。多くは比較 operator、古い/特殊な class、debug/helper API、callback 登録 API である。

- `SkDrawLooper`: `canComputeFastBounds`, `computeFastBounds`, `asABlurShadow`, `GetFlattenableType`
- `SkFont`: `operator==`, `operator!=`
- `SkColorInfo`: `operator==`, `operator!=`
- `SkImageInfo`: `operator==`
- `SkM44`: `operator==`, `operator!=`
- `SkPathMeasure`: `dump`
- `SkRegion`: `operator==`, `operator!=`
- `SkTypeface`: `Register`
- `SkYUVAInfo`: `operator==`, `operator!=`
- `SkYUVAPixmapInfo`: `operator==`, `operator!=`

比較 operator は C ABI では `*_equals` / `*_notEquals` のような named API として扱うのが自然である。

## NA の主な理由

`na` は 27 件。主な理由は次の通り。

- 抽象基底の hook:
  - `SkBBHFactory::operator()`
  - `SkDrawLooper::makeContext`
  - `SkDrawable::on*`
  - `SkFlattenable` constructor
  - `SkImageGenerator::on*`
  - `SkTraceMemoryDump` constructor
- private/protected/internal helper:
  - `SkCapabilities::initSkCaps`
  - `SkPicture::MakeFromStreamPriv`
  - `SkPicture::StreamIsSKP`
  - `SkPicture::BufferIsSKP`
  - `SkPicture::asSkBigPicture`
  - `SkPicture::Forwardport`
  - `SkPathBuilder::privateReverseAddPath`
  - `SkRRect::computeType`
  - `SkRRect::checkCornerContainment`
  - `SkRRect::scaleRadii`
- 条件付き legacy API:
  - `SkBlurMaskFilter::MakeEmboss` は `SK_SUPPORT_LEGACY_EMBOSSMASKFILTER` guarded。既定ビルドでは対象外として扱う。
- base builder の直接構築:
  - `SkRuntimeEffectBuilder` constructor/assignment は specialized builder (`Shader`, `ColorFilter`, `Blend`) 側の C API を優先する。

## false_positive の主な理由

`false_positive` は 64 件。主な理由は次の通り。

- deleted/defaulted special member:
  - copy/move assignment
  - deleted copy constructor
  - protected/default constructor
- destructor:
  - `release` / `delete` / `unref` 規約で扱うため、直接 destructor API は不要。
- operator convenience:
  - `SkMatrix::operator[]` は `SkMatrix_get` / `SkMatrix_set` で代替済み。
  - `SkM44::operator*` は `SkM44_map` で代替済み。
  - `SkString::operator=`, `operator+=`, `operator[]` は `set` / `append` / `dataMutable` で代替済み。
- template convenience:
  - `SkDataTable::atT` は `SkDataTable_at` / `SkDataTable_atStr` で代替済み。
- 既存 factory-style API で代替済み:
  - `SkStrokeRec` constructors は `SkStrokeRec_static*` で代替済み。

## 次の実装候補

優先順は次が妥当。

1. `SkImage::imageInfo`
   - P1。既存 TODO で、戻り値の扱いも比較的局所的。

2. `SkYUVAInfo::GetYUVALocations`
   - P2。既存 C API にコメントアウトがあり、実装方針を決めやすい。

3. `SkPathBuilder::countVerbs`
   - P2。単純 getter でリスクが低い。

4. `SkNullWStream` constructor
   - P2。stream 系 C API の補完として扱いやすい。

5. `SkOverdrawCanvas` constructor
   - P2。既に `onDraw*` と delete があるため、作成 API の欠落が目立つ。

6. async read 系 (`SkImage` / `SkSurface`)
   - P2 だが callback/lifetime ABI 設計が必要なので専用フェーズに分ける。

7. equality operator 群
   - P3。`*_equals` / `*_notEquals` としてまとめて処理できる。

## 生成器へのフィードバック

今回の triage で、`generate_public_api_coverage.py` の改善点も明確になった。

- access specifier の同一行混在や `private:` 以降の抽出精度を上げる。
- `= delete`, `= default`, destructor、assignment operator を初期状態で `false_positive` または別 status に分ける。
- `#ifdef` guarded API を保持し、`conditional` として出力する。
- C API のコメントアウト済み TODO を `known_todo` として拾う。
- operator のうち `==` / `!=` は `*_equals` 候補として別扱いにする。
