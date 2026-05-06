# Phase B Named Comparison Progress

- 作成日: 2026-05-06
- 作業開始時刻: 2026-05-06 20:48:19 JST
- 対象計画: `docs/plans/c-binding-remediation/06-public-api-coverage-roadmap.md`

## 実施内容

Phase B の対象だった C++ 比較 operator を、C ABI 向けの named API として追加した。

| Skia API | Reskia C API |
| --- | --- |
| `SkFont::operator==` | `SkFont_equals` |
| `SkFont::operator!=` | `SkFont_notEquals` |
| `SkColorInfo::operator==` | `SkColorInfo_equals` |
| `SkColorInfo::operator!=` | `SkColorInfo_notEquals` |
| `SkImageInfo::operator==` | `SkImageInfo_equals` |
| `SkImageInfo::operator!=` | `SkImageInfo_notEquals` |
| `SkM44::operator==` | `SkM44_equals` |
| `SkM44::operator!=` | `SkM44_notEquals` |
| `SkRegion::operator==` | `SkRegion_equals` |
| `SkRegion::operator!=` | `SkRegion_notEquals` |
| `SkYUVAInfo::operator==` | `SkYUVAInfo_equals` |
| `SkYUVAInfo::operator!=` | `SkYUVAInfo_notEquals` |
| `SkYUVAPixmapInfo::operator==` | `SkYUVAPixmapInfo_equals` |
| `SkYUVAPixmapInfo::operator!=` | `SkYUVAPixmapInfo_notEquals` |

## 生成器の修正

`scripts/generate_public_api_coverage.py` の `method_token` を更新し、C++ operator を C ABI の named API に対応付けた。

| C++ method | C API token |
| --- | --- |
| `operator==` | `equals` |
| `operator!=` | `notEquals` |
| `operator=` | `assign` |

これにより、`public-api-coverage-matrix.csv` で比較 API が `covered` として追跡できる。

## Matrix 結果

再生成後の `public-api-coverage-matrix.csv` 集計:

| method_status | 件数 |
| --- | ---: |
| `covered` | 1772 |
| `missing` | 1732 |
| `partial` | 2 |
| `no_public_methods_found` | 107 |

Phase B 対象 14 件はすべて `covered`。

## 検証

成功:

```bash
python3 -m py_compile scripts/generate_public_api_coverage.py
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8
```

## 次にやること

Phase B は完了。次は Phase C の callback/registration API 設計に進む。
