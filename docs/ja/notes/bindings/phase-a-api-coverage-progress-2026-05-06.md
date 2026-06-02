# Phase A API Coverage Progress

- 作成日: 2026-05-06
- 作業開始時刻: 2026-05-06 20:36:51 JST
- 対象計画: `docs/ja/plans/c-binding-remediation/06-public-api-coverage-roadmap.md`

## 実施内容

Phase A の低リスク core gap から、callback/async/GPU を含まないものを先に処理した。

実装した API:

| Skia API | Reskia C API | 変更先 |
| --- | --- | --- |
| `SkImage::imageInfo` | `SkImage_imageInfo` | `skia/capi/sk_image.h`, `skia/capi/sk_image.cpp` |
| `SkYUVAInfo::GetYUVALocations` | `SkYUVAInfo_GetYUVALocations` | `skia/capi/sk_yuva_info.h`, `skia/capi/sk_yuva_info.cpp` |
| `SkNullWStream::SkNullWStream` | `SkNullWStream_new` | `skia/capi/sk_w_stream.h`, `skia/capi/sk_w_stream.cpp` |
| `SkOverdrawCanvas::SkOverdrawCanvas` | `SkOverdrawCanvas_new` | `skia/capi/sk_overdraw_canvas.h`, `skia/capi/sk_overdraw_canvas.cpp` |
| `SkRasterHandleAllocator::MakeCanvas` | `SkRasterHandleAllocator_MakeCanvas` | `skia/capi/sk_raster_handle_allocator.h`, `skia/capi/sk_raster_handle_allocator.cpp` |

再分類した API:

| Skia API | 判定 | 理由 |
| --- | --- | --- |
| `SkPathBuilder::countVerbs` | `false_positive` | `vendor/skia-upstream/include/core/SkPathBuilder.h` では `private:` 節にあり、公開 API ではない。 |

## 生成器の修正

`scripts/generate_public_api_coverage.py` の `split_top_level_statements` は、inline method body の閉じ `}` で statement を切っていなかった。そのため、inline method の直後にある `private:` 節が同一 statement に混ざり、private method を public method として誤検出することがあった。

今回、トップレベルの `}` でも statement を区切るように修正し、`SkPathBuilder::countVerbs` が matrix から消えることを確認した。

## Matrix 結果

再生成後の `public-api-coverage-matrix.csv` 集計:

| method_status | 件数 |
| --- | ---: |
| `covered` | 1757 |
| `missing` | 1747 |
| `partial` | 2 |
| `no_public_methods_found` | 107 |

Phase A 対象の確認結果:

| API | matrix status |
| --- | --- |
| `SkImage::imageInfo` | `covered` |
| `SkYUVAInfo::GetYUVALocations` | `covered` |
| `SkNullWStream::SkNullWStream` | `covered` |
| `SkOverdrawCanvas::SkOverdrawCanvas` | `covered` |
| `SkRasterHandleAllocator::MakeCanvas` | `covered` |
| `SkPathBuilder::countVerbs` | 行なし。private method のため対象外。 |

## 検証

成功:

```bash
python3 -m py_compile scripts/generate_public_api_coverage.py
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8
```

## 所有権メモ

`SkRasterHandleAllocator_MakeCanvas` は upstream API と同じく allocator の所有権を消費する。C ABI の `reskia_raster_handle_allocator_t*` は呼び出し後に caller 側で delete してはいけない。戻り値は `sk_canvas_t` で、失敗時は `0`、成功時は `static_sk_canvas_delete` で解放する。

## 次にやること

Phase A は完了。次は Phase B の named comparison API、または callback/registration 設計が必要な Phase C に進む。
