# 02 Phase 2: RESKIA_ENABLE_SKPARAGRAPH と CMake 条件付き取り込み

更新日時: 2026-02-17 07:50:21 JST

## 実施内容

1. `RESKIA_ENABLE_SKPARAGRAPH` トグルを追加（既定 `OFF`）。
2. `skia/CMakeLists.txt` に `RESKIA_ENABLE_SKPARAGRAPH=ON` 時の有効条件チェックを追加。
3. `cmake/reskia/sources-core.cmake` で `modules/skparagraph/skparagraph.gni` から `include/` と `src/` を抽出し、`SOURCE_FILES` へ条件付き追加。
4. `RESKIA_ENABLE_SKPARAGRAPH=ON` 時に `reskia` へ `SK_ENABLE_PARAGRAPH` / `SK_SHAPER_HARFBUZZ_AVAILABLE` を付与。
5. `modules/skshaper` / `modules/skunicode` ヘッダ参照用に `svg` ルート include を有効化。

## 変更ファイル

- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-core.cmake`
- `skia/CMakeLists.txt`

## 有効条件（Phase 2 時点）

`RESKIA_ENABLE_SKPARAGRAPH=ON` は以下を満たす場合のみ configure を通す。

1. `APPLE` 環境
2. `RESKIA_DEPS_MODE=source`
3. `skshaper` / `skunicode` ターゲットが解決済み
4. `hb.h` が検出可能（HarfBuzz 導入済み）

未充足時は configure で `FATAL_ERROR` として停止。

## 検証結果

1. 既定 OFF configure:
```bash
cmake -S skia -B skia/cmake-build-skparagraph-phase2-off -DRESKIA_BUILD_TESTS=OFF
```
- 成功

2. ON configure（source モード）:
```bash
cmake -S skia -B skia/cmake-build-skparagraph-phase2-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKPARAGRAPH=ON \
  -DRESKIA_BUILD_TESTS=OFF
```
- 失敗（期待どおり）: `hb.h` 未検出で停止

3. 既定 OFF build:
```bash
cmake --build skia/cmake-build-skparagraph-phase2-off -j 8
```
- 失敗（既知）: `sk_text_blob_builder_run_handler.cpp` 由来の `SkTextBlobBuilderRunHandler::*` 未解決シンボル
- 今回追加した `skparagraph` トグル有無とは独立した既存リンク課題

## Phase 3 への引き継ぎ

1. HarfBuzz を導入した環境で `RESKIA_ENABLE_SKPARAGRAPH=ON` の configure/build を再検証する。
2. paragraph 最小スモーク（`ParagraphBuilder` -> `layout` -> `paint`）を追加する。
3. 既存の `SkTextBlobBuilderRunHandler` リンク課題が Phase 3 検証を阻害する場合、先に分離対応またはテスト分離を行う。
