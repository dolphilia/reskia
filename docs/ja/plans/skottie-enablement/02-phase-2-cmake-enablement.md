# 02 Phase 2: RESKIA_ENABLE_SKOTTIE と CMake 取り込み

更新日時: 2026-02-17 07:26:19 JST

## 実施内容

1. CMake オプション `RESKIA_ENABLE_SKOTTIE`（既定 OFF）を追加。
2. `cmake/reskia/sources-core.cmake` で `sksg.gni` / `skottie.gni` を参照し、`sksg` + `skottie` のソース群を条件付きで `SOURCE_FILES` に追加。
3. `skia/CMakeLists.txt` で以下を `RESKIA_ENABLE_SKOTTIE=ON` 時のみ有効化。
- `SK_ENABLE_SKOTTIE`
- `SK_ENABLE_SKOTTIE_SKSLEFFECT`
- `target_include_directories(reskia PRIVATE "${RESKIA_ROOT_DIR}/svg")`

4. 依存条件の明示チェックを追加。
- `RESKIA_ENABLE_SKOTTIE=ON` かつ非 Apple: `FATAL_ERROR`
- `RESKIA_DEPS_MODE=source` で `skresources` / `svg` 未解決: `FATAL_ERROR`
- `modules/sksg/sksg.gni` または `modules/skottie/skottie.gni` 不在: `FATAL_ERROR`

## 変更ファイル

- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-core.cmake`
- `skia/CMakeLists.txt`

## 検証結果

1. 回帰確認（OFF）
```bash
cmake -S skia -B skia/cmake-build-skottie-phase2-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF
cmake --build skia/cmake-build-skottie-phase2-off -j 8
```
- 結果: 成功（`libreskia.dylib` 生成）

2. 有効化確認（ON）
```bash
cmake -S skia -B skia/cmake-build-skottie-phase2-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DRESKIA_ENABLE_SKOTTIE=ON
cmake --build skia/cmake-build-skottie-phase2-on -j 8
```
- 結果: 成功（`modules/sksg` / `modules/skottie` を含めて `libreskia.dylib` 生成）

## 補足

- `sources-core.cmake` は `*.gni` から `$_modules/...` エントリを抽出して `modules/...` に変換するため、Phase 1 同期済みファイル集合との整合が取りやすい。
- 取り込み対象は `*.gni` が列挙する公開ヘッダ/本体ソースのみで、`tests` / `gm` / `fuzz` / `utils` / `SkottieTool.cpp` / `SkottieTest.cpp` は含まない。

## Phase 3 への引き継ぎ

1. `skia/capi/sk_skottie.{h,cpp}` の新規追加。
2. C API 最小ライフサイクル（load/seek/render/destroy）の実装。
3. 必要に応じて `reskia_ffi.h` と handle レイヤの公開面調整。
