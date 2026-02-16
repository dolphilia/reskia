# 00 Plan: SVG / テキストシェーピング実装強化

作成日時: 2026-02-16 20:42:18 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.2 SVG / テキストシェーピング` を「部分網羅（最小縮退中心）」から改善し、以下を満たす。

- `svg` / `skshaper` / `skunicode` の有効化条件とリンク関係を明確化する
- 依存あり環境では HarfBuzz + ICU 系の経路を優先有効化できる
- 依存なし環境では従来どおり縮退ビルドを維持する
- `reskia` の configure/build と最小実行確認（スモーク）を通す

## 再調査サマリ（2026-02-16）

1. `svg/CMakeLists.txt` は `hb.h` / `unicode/ubidi.h` / `ICU4XDataProvider.hpp` / `grapheme.h` のヘッダ検出ベースで機能縮退する構成。
2. 現環境では上記 4 依存がすべて未検出（`*-NOTFOUND`）で、`SkShaper_primitive` + `SkUnicode_hardcoded` を中心にビルドされる。
3. `cmake -S svg -B svg/cmake-build-survey && cmake --build ...` は成功（`libsvg.a`, `libskshaper.a`, `libskunicode.a`）。
4. `cmake -S skia -B skia/cmake-build-svg-shaping-survey -DRESKIA_DEPS_MODE=source -DRESKIA_BUILD_TESTS=ON` の build は `libreskia.dylib` まで成功。
5. 同 build では既知の `test_c_skia` API 不整合で失敗する一方、`test_codec_smoke` はビルド・実行成功（`c_skia_codec_smoke: Passed`）。
6. `cmake/reskia/sources-capi.cmake` で `capi/sk_text_blob_builder_run_handler.cpp` が未有効で、C API のテキストシェーピング公開面が不十分。

## 現状ギャップ（着手前の事実）

1. `skia/CMakeLists.txt` では `svg` を内部ライブラリとしてリンクするが、`skshaper` / `skunicode` を直接解決する設計が明示されていない。
2. `svg/CMakeLists.txt` 内で `svg` -> `skshaper` -> `skunicode` のターゲットリンク関係が明示されていない。
3. 依存検出は include path ベースで、`source/system/prebuilt` 各モードの依存供給元と整合確認が不足している。
4. ICU4X は既知の API 差異があり、検出できてもそのまま有効化できない可能性が高い。
5. テキストシェーピング用 C API（例: `SkTextBlobBuilderRunHandler`）はソース存在に対して CMake 無効化状態。

## 対象ファイル（主）

- `svg/CMakeLists.txt`
- `skia/CMakeLists.txt`
- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-capi.cmake`
- `skia/capi/sk_text_blob_builder_run_handler.{h,cpp}`
- `cmake/reskia/tests.cmake`
- `skia/test/*`（シェーピング/Unicode スモーク追加時）
- `third_party/README.md`（依存導入手順の追記が必要な場合）

## 実施フェーズ

### Phase 1: 依存・リンク要件の固定

ステータス: 完了（2026-02-16 20:44:15 JST）

1. `svg` / `skshaper` / `skunicode` 間の最小リンクグラフを確定する。
2. `source/system/prebuilt` モードごとに HarfBuzz / ICU / ICU4X / libgrapheme の解決元を表にする。
3. ICU4X は「暫定OFF（検出しても使わない）」か「互換レイヤ追加でON」の方針を先に決める。

完了条件:
- どの依存があればどの実装ファイルが有効化されるかを、モード別に説明可能。

### Phase 2: CMake 結線の調整

1. `svg/CMakeLists.txt` でターゲット間依存（`svg` -> `skshaper`, `skshaper` -> `skunicode`）を明示化する。
2. 外部依存を使う実装（HarfBuzz/ICU など）で必要な include/link 設定をターゲット単位で整理する。
3. `skia/CMakeLists.txt` の内部ライブラリ解決を再確認し、`source` 以外での欠落時挙動を明文化する。

完了条件:
- 依存有無どちらでも configure 時の挙動が一貫し、リンクエラーが再現しない。

### Phase 3: C API 公開面の有効化（最小）

ステータス: 完了（2026-02-17 04:40:42 JST）

1. `capi/sk_text_blob_builder_run_handler.cpp` の有効化を検討し、必要な型/ABI 整合を確認する。
2. 既存 C API 命名（`reskia_*_t`）との不整合があれば薄い互換ラッパーで吸収する。
3. 依存なし環境でもビルド可能なよう、該当 API を条件付き有効化する。

完了条件:
- テキストシェーピング関連 C API が少なくとも 1 経路でリンク可能。

### Phase 4: ビルド行列検証

ステータス: 完了（2026-02-17 04:50:00 JST）

1. 基本系（依存なし縮退）を確認する。
```bash
cmake -S skia -B skia/cmake-build-shaping-min \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF
cmake --build skia/cmake-build-shaping-min -j 8
```
2. 拡張系（HarfBuzz + ICU）を確認する。
```bash
scripts/build_third_party.sh --with-harfbuzz --with-icu --clean
cmake -S skia -B skia/cmake-build-shaping-full \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-shaping-full -j 8
```
3. `test_c_skia` 既知不整合に引きずられないよう、シェーピング対象の検証ターゲットを分離する。

完了条件:
- `reskia` 本体ビルド成功。
- シェーピング関連スモークが 0 exit。

### Phase 5: 実行スモークと文書化

ステータス: 完了（2026-02-17 04:53:55 JST）

1. 最小スモーク（UTF-8 + BiDi + line break を含む短文 shaping）を追加する。
2. SVG text 描画経路の到達確認（クラッシュしない、blob 生成成功）を追加する。
3. 依存縮退条件と有効化手順を `docs/notes` または `docs/guides` に反映する。

完了条件:
- 実行確認結果と依存条件が再現可能な形で文書化される。

## 判定ゲート（途中判断）

1. ICU4X 互換対応の工数が大きい場合:
- 今回は ICU4X を明示 OFF（検出しても無効）とし、HarfBuzz + ICU を先行完了にする。
2. `test_c_skia` の既知崩れが継続する場合:
- 既存テストは触らず、シェーピング専用スモークを別ターゲット化して前進する。
3. `prebuilt/system` で依存供給が不安定な場合:
- 先に `source` モードを完了条件とし、他モードは追補フェーズへ分離する。

## Definition of Done

1. `3.2 SVG / テキストシェーピング` の実装状態を、依存あり/なし双方で説明できる。
2. `svg` / `skshaper` / `skunicode` のターゲット結線が明示され、リンク不整合がない。
3. シェーピング関連 C API の最小経路が有効化され、ビルド可能。
4. 最小スモークで実行確認が取れ、結果がドキュメント化されている。
