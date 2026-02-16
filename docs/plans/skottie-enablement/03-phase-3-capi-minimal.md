# 03 Phase 3: sk_skottie 最小 C API

更新日時: 2026-02-17 07:32:34 JST

## 実施内容

1. `skia/capi/sk_skottie.h` / `skia/capi/sk_skottie.cpp` を新規追加。
2. `cmake/reskia/sources-capi.cmake` に `RESKIA_ENABLE_SKOTTIE=ON` 時のみ `capi/sk_skottie.cpp` を追加。
3. `skia/capi/reskia_ffi.h` に `#include "sk_skottie.h"` を追加。

## 追加 API（最小ライフサイクル）

- 生成:
  - `Skottie_Animation_Make(const char *data, size_t length)`
  - `Skottie_Animation_MakeFromFile(const char path[])`
- 参照管理:
  - `Skottie_Animation_release(...)`
  - `Skottie_Animation_ref(...)`
  - `Skottie_Animation_unref(...)`
- 再生制御:
  - `Skottie_Animation_seek(...)`
  - `Skottie_Animation_seekFrameTime(...)`
- 描画:
  - `Skottie_Animation_render(...)`
  - `Skottie_Animation_renderWithFlags(...)`
- 情報取得:
  - `Skottie_Animation_duration(...)`
  - `Skottie_Animation_fps(...)`
  - `Skottie_Animation_width(...)`
  - `Skottie_Animation_height(...)`

## 実装ポリシー

1. C 側ハンドルは `reskia_skottie_animation_t*`（opaque pointer）として扱う。
2. 内部は `skottie::Animation*` を保持し、`Make*` は `sk_sp` を `release()` して所有権を C 側へ移譲。
3. 解放は `unref()` ベース（Skia の参照カウント規約に合わせる）。
4. `null` 入力は安全に no-op / `false` / `0` を返す。

## 変更ファイル

- `skia/capi/sk_skottie.h`（新規）
- `skia/capi/sk_skottie.cpp`（新規）
- `cmake/reskia/sources-capi.cmake`
- `skia/capi/reskia_ffi.h`

## 検証結果

1. `RESKIA_ENABLE_SKOTTIE=OFF` で configure/build 成功。
```bash
cmake -S skia -B skia/cmake-build-skottie-phase3-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF
cmake --build skia/cmake-build-skottie-phase3-off -j 8
```

2. `RESKIA_ENABLE_SKOTTIE=ON` で configure/build 成功。
```bash
cmake -S skia -B skia/cmake-build-skottie-phase3-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DRESKIA_ENABLE_SKOTTIE=ON
cmake --build skia/cmake-build-skottie-phase3-on -j 8
```

3. `ON` ビルドで `sk_skottie.cpp` のオブジェクト生成を確認。
- `skia/cmake-build-skottie-phase3-on/CMakeFiles/reskia.dir/capi/sk_skottie.cpp.o`

## Phase 4 への引き継ぎ

1. `test_skottie_smoke.cpp` を追加し、最小 Lottie JSON の load/seek/render を実行確認。
2. `RESKIA_ENABLE_SKOTTIE=ON` + `RESKIA_BUILD_TESTS=ON` で `ctest` 行列を確認。
