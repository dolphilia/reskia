# Phase C Callback Registration Progress

- 作成日: 2026-05-06
- 作業開始時刻: 2026-05-06 20:54:04 JST
- 対象計画: `docs/plans/c-binding-remediation/06-public-api-coverage-roadmap.md`

## 実施内容

`SkFont::getPaths` を C ABI に公開した。

```c
typedef void (*reskia_font_glyph_path_proc_t)(
    const reskia_path_t *path_or_null,
    const reskia_matrix_t *matrix,
    void *ctx);

void SkFont_getPaths(
    reskia_font_t *font,
    const uint16_t *glyphIDs,
    int count,
    reskia_font_glyph_path_proc_t glyphPathProc,
    void *ctx);
```

## Callback Lifetime

- `path_or_null` は callback 中だけ有効な borrowed pointer。
- `matrix` は callback 中だけ有効な borrowed pointer。
- caller は `path_or_null` と `matrix` を保持・delete してはいけない。
- `path_or_null` は glyph が path を持たない場合に `NULL` になり得る。
- `ctx` は caller 所有。Reskia は保持・解放しない。
- `font == NULL`、`glyphIDs == NULL`、`count <= 0`、`glyphPathProc == NULL` の場合は no-op。

## Smoke

追加:

- `skia/test/test_phase_c_callback_smoke.cpp`
- `cmake/reskia/tests.cmake` の `test_phase_c_callback_smoke`

検証:

```bash
c++ -std=c++17 -I skia -I skia/include skia/test/test_phase_c_callback_smoke.cpp skia/cmake-build-codex-project-survey-prebuilt/libreskia.dylib -Wl,-rpath,/Users/dolphilia/github/reskia/skia/cmake-build-codex-project-survey-prebuilt -o /private/tmp/reskia_phase_c_callback_smoke
/private/tmp/reskia_phase_c_callback_smoke
```

`RESKIA_BUILD_TESTS=ON` の CMake target としても登録した。ただし現状の test 構成は `SkTestCanvas.cpp` 関連の未解決シンボルで `reskia` link に失敗するため、target build では完走確認できていない。

## Deferred APIs

`SkGraphics::SetImageGeneratorFromEncodedDataFactory`:

- global process-wide registration。
- callback は `sk_sp<SkData>` を受け取り、`std::unique_ptr<SkImageGenerator>` を返す。
- C ABI 化には `SkImageGenerator` の owned wrapper と、登録 callback の lifetime policy が必要。
- 既存の `sk_graphics.cpp` には C++ 型を直接受ける未公開関数があるが、C ABI としては不十分。

`SkTypeface::Register`:

- global process-wide registration。
- callback は `std::unique_ptr<SkStreamAsset>` を消費し、`sk_sp<SkTypeface>` を返す。
- C ABI 化には stream asset ownership transfer、returned typeface ownership、registration id の衝突/上書き方針が必要。

`SkRegion::toString`:

- upstream header では `SK_BUILD_FOR_ANDROID_FRAMEWORK` guarded。
- current default Reskia build では利用できないため `na` に再分類した。

## Matrix 結果

再生成後:

| API | method_status |
| --- | --- |
| `SkFont::getPaths` | `covered` |
| `SkGraphics::SetImageGeneratorFromEncodedDataFactory` | `missing` |
| `SkTypeface::Register` | `missing` |
| `SkRegion::toString` | `missing` in generated matrix, `na` in triage |

## 検証

成功:

```bash
python3 -m py_compile scripts/generate_public_api_coverage.py
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8
```

制約:

```bash
cmake -S skia -B skia/cmake-build-codex-phase-c-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-codex-phase-c-tests --target test_phase_c_callback_smoke -j 8
```

前者は成功。後者は既存 test 構成の `SkTestCanvas.cpp` link issue で失敗。
