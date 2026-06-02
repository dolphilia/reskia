# 04 Phase 4: ビルド行列検証

作成日時: 2026-02-17 04:50:00 JST

## 実施内容

### 1. 縮退構成（依存なし）

実行コマンド:

```bash
cmake -S skia -B skia/cmake-build-shaping-min \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-shaping-min -j 8
```

結果:

- `Built target reskia` で成功。
- `CMakeCache.txt` は依存未検出（縮退）:
  - `HARFBUZZ_INCLUDE_DIR-NOTFOUND`
  - `ICU_UBIDI_INCLUDE_DIR-NOTFOUND`
  - `ICU4X_INCLUDE_DIR-NOTFOUND`
  - `LIBGRAPHEME_INCLUDE_DIR-NOTFOUND`

### 2. 拡張構成（ICU 導入）

実行コマンド:

```bash
scripts/build_third_party.sh --with-harfbuzz --with-icu --clean
cmake -S skia -B skia/cmake-build-shaping-full \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH=/Users/dolphilia/github/reskia/third_party/install
cmake --build skia/cmake-build-shaping-full -j 8
```

初回結果:

- `libreskia.dylib` のリンク時に ICU 記号未解決で失敗。
- 例: `_ubidi_setPara_79`, `_ubrk_open_79`, `_u_getIntPropertyValue_79`

原因:

- `svg/CMakeLists.txt` で `ICU_UBIDI_INCLUDE_DIR` 検出時に `skunicode` の ICU ソースは有効化していたが、`icui18n/icuuc/icudata` をリンクしていなかった。

修正:

- `svg/CMakeLists.txt` に `find_library(ICU_I18N_LIBRARY ...)`, `find_library(ICU_UC_LIBRARY ...)`, `find_library(ICU_DATA_LIBRARY ...)` を追加。
- `skunicode` に対して上記 3 ライブラリを `PUBLIC` でリンク。

再実行結果:

- `cmake --build skia/cmake-build-shaping-full -j 8` で `Built target reskia` を確認。
- `CMakeCache.txt` で以下を確認:
  - `ICU_UBIDI_INCLUDE_DIR=/Users/dolphilia/github/reskia/third_party/install/include`
  - `ICU_I18N_LIBRARY=/Users/dolphilia/github/reskia/third_party/install/lib/libicui18n.a`
  - `ICU_UC_LIBRARY=/Users/dolphilia/github/reskia/third_party/install/lib/libicuuc.a`
  - `ICU_DATA_LIBRARY=/Users/dolphilia/github/reskia/third_party/install/lib/libicudata.a`

## 判定

- Phase 4 の最小完了条件（`reskia` 本体ビルド成功）は満たした。
- 拡張構成で ICU 経路が最終リンクまで到達することを確認した。
- HarfBuzz は今回の環境では `HARFBUZZ_INCLUDE_DIR-NOTFOUND` のため、次フェーズで導入経路を追加検証する。
