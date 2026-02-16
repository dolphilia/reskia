# SVG Text Shaping Link Observations (2026-02-16)

## 1. configure/build 観測

- `cmake -S svg -B svg/cmake-build-survey -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build svg/cmake-build-survey -j 8`
- `cmake -S skia -B skia/cmake-build-svg-shaping-survey -DRESKIA_DEPS_MODE=source -DRESKIA_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build skia/cmake-build-svg-shaping-survey -j 8`

結果:
- `libsvg.a`, `libskshaper.a`, `libskunicode.a`, `libreskia.dylib` は生成成功。
- `test_c_skia` は既知 API 不整合で失敗。
- `test_codec_smoke` は成功し `ctest -R c_skia_codec_smoke` も pass。

## 2. 依存検出キャッシュ（現環境）

`skia/cmake-build-svg-shaping-survey/CMakeCache.txt`

- `HARFBUZZ_INCLUDE_DIR=HARFBUZZ_INCLUDE_DIR-NOTFOUND`
- `ICU_UBIDI_INCLUDE_DIR=ICU_UBIDI_INCLUDE_DIR-NOTFOUND`
- `ICU4X_INCLUDE_DIR=ICU4X_INCLUDE_DIR-NOTFOUND`
- `LIBGRAPHEME_INCLUDE_DIR=LIBGRAPHEME_INCLUDE_DIR-NOTFOUND`

## 3. ターゲット別フラグ観測

`skia/cmake-build-svg-shaping-survey/_deps/svg/CMakeFiles/skshaper.dir/flags.make`

- `CXX_DEFINES = -DSK_BUILD_FOR_MAC -DSK_SHAPER_CORETEXT_AVAILABLE`

`skia/cmake-build-svg-shaping-survey/_deps/svg/CMakeFiles/skunicode.dir/flags.make`

- `CXX_DEFINES =`（追加 define なし）

## 4. リンク観測

`skia/cmake-build-svg-shaping-survey/_deps/svg/CMakeFiles/svg.dir/link.txt`

- `libsvg.a` 生成のみ（`ar`/`ranlib`）。`skshaper`/`skunicode` へのリンク指定はなし。

`skia/cmake-build-svg-shaping-survey/CMakeFiles/reskia.dir/link.txt`

- 最終リンクの内部ライブラリは `_deps/skcms/libskcms.a`, `_deps/skresources/libskresources.a`, `_deps/svg/libsvg.a`。
- `_deps/svg/libskshaper.a` / `_deps/svg/libskunicode.a` は含まれない。

## 5. 未解決記号観測

`nm -u skia/cmake-build-svg-shaping-survey/_deps/svg/libsvg.a | rg "SkShaper|SkUnicode"`

- `__ZN8SkShaper4MakeE5sk_spI9SkFontMgrE`（`SkShaper::Make`）が未解決として残る。

解釈:
- 現状は `libsvg.a` 内の `SkSVGText` 由来オブジェクトが最終リンクで要求されない限り顕在化しない。
- テキスト経路を確実に有効化するには、Phase 2 でターゲットリンク関係の明示化が必要。
