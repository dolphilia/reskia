# 01 Phase 1: SVG / テキストシェーピング依存・リンク要件の固定

更新日時: 2026-02-16 20:44:15 JST

## 実施内容

1. `svg/CMakeLists.txt` の条件付き実装追加（HarfBuzz/ICU/ICU4X/libgrapheme）を棚卸し。
2. `source/system/prebuilt` の依存供給経路を `cmake/deps/ReskiaDeps.cmake` と `scripts/build_third_party.sh` から整理。
3. 実ビルド成果物（`link.txt`, `flags.make`, `CMakeCache.txt`, `nm -u`）からリンクグラフを確認。
4. ICU4X の方針を「Phase 2 までは暫定OFF」に固定。

## 成果物（マニフェスト）

- `/Users/dolphilia/github/reskia/docs/plans/svg-text-shaping-enablement/manifests/svg-conditional-implementations.csv`
- `/Users/dolphilia/github/reskia/docs/plans/svg-text-shaping-enablement/manifests/svg-deps-mode-matrix.csv`
- `/Users/dolphilia/github/reskia/docs/plans/svg-text-shaping-enablement/manifests/svg-link-observations.md`

## 棚卸し結果

1. `svg` は `SkSVGText.cpp` を常時ビルド対象に含むが、`SkShaper::Make` 解決を `libsvg.a` 単体では満たせない（`nm -u libsvg.a` で未解決記号確認）。
2. `skshaper` / `skunicode` は個別 static library として生成されるが、`svg/CMakeLists.txt` 上で相互 `target_link_libraries` が未定義。
3. `skia` 側の最終リンクでは `_deps/svg/libsvg.a` のみが直接指定され、`_deps/svg/libskshaper.a` / `_deps/svg/libskunicode.a` は含まれない。
4. 現環境の configure 結果では `HARFBUZZ_INCLUDE_DIR` / `ICU_UBIDI_INCLUDE_DIR` / `ICU4X_INCLUDE_DIR` / `LIBGRAPHEME_INCLUDE_DIR` はすべて `NOTFOUND`。
5. そのため実際の有効実装は `SkShaper_primitive.cpp` + `SkUnicode_hardcoded.cpp`（Apple では CoreText 追加）に縮退している。

## Phase 1 判断

1. **リンクグラフ方針**: Phase 2 で `svg -> skshaper -> skunicode` を `target_link_libraries` で明示化する。
2. **依存方針**: 依存あり/なしの双方を維持し、依存不足時は現行どおり縮退継続。
3. **ICU4X方針**: 既知 API 差異が解消されるまで `暫定OFF`（検出のみ、既定有効化しない）。

## Phase 2 への引き継ぎ

1. `svg/CMakeLists.txt` にターゲット間リンク定義を追加する。
2. ICU/HarfBuzz 有効時の include/link をターゲット単位で明示し、`source/system/prebuilt` で挙動差をなくす。
3. `reskia` へリンクされる内部ライブラリの閉包を検証し、`SkSVGText` 経路の未解決記号を排除する。
