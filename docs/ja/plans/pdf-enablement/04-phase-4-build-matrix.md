# 04 Phase 4: ビルド行列検証

更新日時: 2026-02-16 20:26:19 JST

## 検証条件

- 共通オプション: `-DRESKIA_ENABLE_PDF=ON`
- 対象モード: `prebuilt`, `source`, `system`
- 対象ターゲット: `reskia`（`cmake --build ...`）

## 実行コマンドと結果

1. prebuilt
```bash
cmake -S skia -B skia/cmake-build-pdf-prebuilt \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_PDF=ON
cmake --build skia/cmake-build-pdf-prebuilt -j 8
```
- 結果: configure/build とも成功

2. source
```bash
cmake -S skia -B skia/cmake-build-pdf-source \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_PDF=ON
cmake --build skia/cmake-build-pdf-source -j 8
```
- 初回結果: link 失敗
- エラー: `SkDeflate.cpp` 由来の `deflate`, `deflateEnd`, `deflateInit2_` 未解決
- 原因: `source + APPLE + RESKIA_ENABLE_PDF=ON` で `zlib` が依存リストに追加されていなかった
- 対応: `cmake/deps/ReskiaDeps.cmake` の source/APPLE 分岐で `RESKIA_ENABLE_RAW OR RESKIA_ENABLE_PDF` 条件へ修正
- 再実行結果: configure/build 成功

3. system
```bash
cmake -S skia -B skia/cmake-build-pdf-system \
  -DRESKIA_DEPS_MODE=system \
  -DRESKIA_ENABLE_PDF=ON
cmake --build skia/cmake-build-pdf-system -j 8
```
- 結果: configure/build とも成功
- configure で `ZLIB` 検出を確認（`find_package(ZLIB REQUIRED)`）

## 判定

- 3モードすべてで `RESKIA_ENABLE_PDF=ON` の build 成功を確認。
- Phase 4 完了。

## Phase 5 への引き継ぎ

1. PDF C API の最小スモーク（ドキュメント作成→1ページ描画→close→バイト非空確認）を追加する。
2. `SkPDF_MakeDocument`（メタデータあり/なし）の両経路を実行確認する。
