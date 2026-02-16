# 05 Phase 5: 実行スモークと文書化

作成日時: 2026-02-17 04:53:55 JST

## 実装

### 1. シェーピング専用スモークを追加

追加ファイル:

- `skia/test/test_shaping_smoke.cpp`

検証項目:

1. UTF-8 + BiDi + 改行を含む短文を `SkShaper::Make()` で shaping。
2. `SkTextBlobBuilderRunHandler` で blob を生成し、`makeBlob()` が `null` でないことを確認。
3. `endPoint()` が有限値であることを確認。

### 2. SVG text 描画経路スモークを追加

同テスト内で以下を実施:

1. SVG 文字列（英語 + ヘブライ語 + アラビア語テキスト）を `SkSVGDOM::Builder` で構築。
2. `setFontManager(SkFontMgr::RefDefault())` を設定して `<text>` 描画可能な状態にする。
3. `SkBitmap` 上へ `render()` し、非透明ピクセルが 1 つ以上描画されることを確認。

## CMake 反映

更新ファイル:

- `cmake/reskia/tests.cmake`

変更内容:

1. `APPLE && TARGET svg && TARGET skshaper && TARGET skunicode` 条件下で `test_shaping_smoke` ターゲットを追加。
2. include path に `${RESKIA_ROOT_DIR}/svg` を追加し、`modules/skshaper/include/SkShaper.h` / `modules/svg/include/SkSVGDOM.h` を解決。
3. `add_test(NAME c_skia_shaping_smoke COMMAND test_shaping_smoke)` を追加。

## 実行結果

### configure

```bash
cmake -S skia -B skia/cmake-build-shaping-phase5 \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON \
  -DRESKIA_ENABLE_PDF=ON \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH=/Users/dolphilia/github/reskia/third_party/install
```

### build（対象限定）

```bash
cmake --build skia/cmake-build-shaping-phase5 --target test_shaping_smoke -j 8
```

結果:

- `Built target test_shaping_smoke`

### 実行

```bash
./skia/cmake-build-shaping-phase5/test_shaping_smoke
```

結果:

- `[shaping-smoke] PASS`

### ctest

```bash
ctest --test-dir skia/cmake-build-shaping-phase5 -R c_skia_shaping_smoke --output-on-failure
```

結果:

- `1/1 Test #3: c_skia_shaping_smoke ... Passed`

## 依存縮退条件の再掲（今回の確認範囲）

1. `HARFBUZZ_INCLUDE_DIR-NOTFOUND` でも本スモークは通過（CoreText + ICU + primitive 経路で成立）。
2. `ICU_UBIDI_INCLUDE_DIR` が解決される環境では、BiDi 処理を含む shaping 経路がビルド・実行可能。
3. `test_c_skia` 既知不整合とは分離した専用スモークとして実行可能。
