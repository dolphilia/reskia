# 01 Phase 1: チェックリスト整合化

作業開始日時: 2026-05-08 12:18:05 JST

## 目的

`docs/ja/plans/stability-hardening/00-plan.md` の Phase 1 に従い、実装状態と進捗チェックリストのずれをなくす。

対象は主に次の 3 系統。

- `docs/ja/plans/c-binding-remediation/checklists/handles-status.csv`
- `docs/ja/plans/c-binding-remediation/checklists/static-handle-table-status.csv`
- `docs/ja/plans/c-binding-remediation/checklists/public-api-core-effects-missing-triage.csv`

## 実施内容

### 1. `handles-status.csv` の役割整理

`handles-status.csv` は `.cpp`、`*-internal.h`、公開 `.h` をまとめて持つため、Phase 1 の実装安全化対象と宣言ファイルが混在していた。

今回、次の方針で整合化した。

| ファイル種別 | Phase 1 での扱い |
| --- | --- |
| `.cpp` | handle table / get_entity / 無効キー処理の実装対象 |
| `*-internal.h` | 内部宣言の整合対象 |
| 公開 `.h` | 宣言のみ。Phase 1 の実装安全化対象外として `na` |

更新後の集計:

| ファイル種別 | done | na | todo |
| --- | ---: | ---: | ---: |
| `.cpp` | 107 | 1 | 0 |
| `*-internal.h` | 106 | 2 | 0 |
| 公開 `.h` | 0 | 108 | 0 |
| 合計 | 213 | 111 | 0 |

`na` の主な理由:

- 公開 `.h`: 宣言のみで、Phase 1 の `handle_table` / `get_entity` / 無効キー処理の実装対象外。
- `static_sk_color-internal.h`: 実装本体がコメントアウトのみ。
- `static_sk_image_read_pixels_callback-internal.h`: 実装/API 未定義。

### 2. `static-handle-table-status.csv` との整合確認

`static-handle-table-status.csv` は `.cpp` の `HandleTable` 移行を追う専用チェックリストであり、既に次の状態だった。

| status | count |
| --- | ---: |
| `done` | 105 |
| `na` | 2 |

この結果と `handles-status.csv` の `.cpp done/na` は意味上整合している。

補足:

- `handles-status.csv` 側の `.cpp done=107` は、`static-handle-table-status.csv` の `HandleTable` 移行対象以外の安全化済み `.cpp` を含む。
- `static-handle-table-status.csv` は今後も `HandleTable` 移行専用として維持する。
- `handles-status.csv` は `handles` ディレクトリ全体の棚卸し表として維持する。

### 3. 危険パターンの再確認

確認コマンド:

```bash
rg -n "return std::move\\(static_.*\\[key\\]\\)|static_.*\\[key\\]" skia/handles/*.cpp
```

結果:

- 実コード上の危険な `map[key]` 使用は検出されなかった。
- 検出されたのは `static_sk_image_read_pixels_callback.cpp` のコメントアウト済み行のみ。

### 4. public API core/effects triage の更新

`public-api-core-effects-missing-triage.csv` には、2026-05-06 の Phase A/C/D で実装済みになった API が `real_gap` のまま残っていた。

今回、次を `covered,P0` に更新した。

| Skia API | Reskia C API |
| --- | --- |
| `SkFont::getPaths` | `SkFont_getPaths` |
| `SkImage::imageInfo` | `SkImage_imageInfo` |
| `SkOverdrawCanvas::SkOverdrawCanvas` | `SkOverdrawCanvas_new` |
| `SkRasterHandleAllocator::MakeCanvas` | `SkRasterHandleAllocator_MakeCanvas` |
| `SkNullWStream::SkNullWStream` | `SkNullWStream_new` |
| `SkYUVAInfo::GetYUVALocations` | `SkYUVAInfo_GetYUVALocations` |

更新後の集計:

| triage | count |
| --- | ---: |
| `covered` | 12 |
| `real_gap` | 22 |
| `na` | 28 |
| `false_positive` | 65 |

残る `real_gap` は次の通り。

| class | method | priority |
| --- | --- | --- |
| `SkRTreeFactory` | `operator` | P2 |
| `SkGraphics` | `SetImageGeneratorFromEncodedDataFactory` | P2 |
| `SkMeshSpecification` | `MakeFromSourceWithStructs` | P2 |
| `SkDrawLooper` | `canComputeFastBounds`, `computeFastBounds`, `asABlurShadow`, `GetFlattenableType` | P3 |
| `SkFont` | `operator==`, `operator!=` | P3 |
| `SkColorInfo` | `operator==`, `operator!=` | P3 |
| `SkImageInfo` | `operator==` | P3 |
| `SkM44` | `operator==`, `operator!=` | P3 |
| `SkPathMeasure` | `dump` | P3 |
| `SkRegion` | `operator==`, `operator!=` | P3 |
| `SkTypeface` | `Register` | P3 |
| `SkYUVAInfo` | `operator==`, `operator!=` | P3 |
| `SkYUVAPixmapInfo` | `operator==`, `operator!=` | P3 |

### 5. coverage matrix 再生成

実行コマンド:

```bash
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
```

再生成後の `public-api-coverage-matrix.csv` 集計:

| method_status | count |
| --- | ---: |
| `covered` | 1894 |
| `missing` | 1579 |
| `referenced` | 140 |

`public-api-coverage-matrix.csv` は生成物であり、今回の再生成では内容差分は発生しなかった。

## C API Phase 2 次バッチ候補

`capi-status.csv` は引き続き次の状態。

| status | count |
| --- | ---: |
| `done` | 34 |
| `todo` | 276 |

`stability-hardening` Phase 2 の最初のバッチ候補は、利用頻度とリスクから次が妥当。

### Batch A: image / surface / canvas

- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/capi/sk_surface.h`
- `skia/capi/sk_surface.cpp`
- `skia/capi/sk_canvas.h`
- `skia/capi/sk_canvas.cpp`

理由:

- C/Rust 利用者が最初に触る中心型。
- borrowed parent pointer、RefCounted、async callback、GPU context 引数が混在する。
- ownership/lifetime guide の実例にしやすい。

### Batch B: bitmap / data / stream

- `skia/capi/sk_bitmap.h`
- `skia/capi/sk_bitmap.cpp`
- `skia/capi/sk_data.h`
- `skia/capi/sk_data.cpp`
- `skia/capi/sk_stream.h`
- `skia/capi/sk_stream.cpp`

理由:

- pixel buffer、borrowed memory、external storage、stream ownership が絡む。
- ASan/UBSan smoke の初期対象にしやすい。

### Batch C: paint / path / font

- `skia/capi/sk_paint.h`
- `skia/capi/sk_paint.cpp`
- `skia/capi/sk_font.h`
- `skia/capi/sk_font.cpp`

補足:

- `skia/capi/sk_path.h` / `skia/capi/sk_path.cpp` は既に `done`。
- `skia/capi/sk_typeface.cpp` は `done` だが、`skia/capi/sk_typeface.h` は `todo` のためヘッダ規約の確認対象。

## 完了条件に対する現在地

| Phase 1 完了条件 | 状態 |
| --- | --- |
| `handles` の Phase 1 完了状況が、実装とチェックリストで矛盾しない | 完了 |
| `capi-status.csv` の次バッチ候補が 5-10 ファイル単位で選べる | 完了 |
| 機械生成 matrix と人手 triage の読み方が明文化されている | 一部完了。`checklists/README.md` と本メモに記載済み |

## 次アクション

1. Phase 2 Batch A に入り、`sk_image` / `sk_surface` / `sk_canvas` の ownership/lifetime/NULL 規約を確認する。
2. Batch A の前に、`docs/ja/guides/` に C ABI ownership/lifetime guide の雛形を作るか判断する。
3. `RESKIA_BUILD_TESTS=ON` の smoke 修復は Phase 4 で扱うが、Batch A の変更時に影響が出る場合は先行して最小修正する。

