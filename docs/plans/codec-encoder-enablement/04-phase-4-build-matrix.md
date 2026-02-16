# 04 Phase 4: ビルド行列確認

更新日時: 2026-02-16 15:28:35 JST

## 実施結果（最終）

| Case | Configure | Build | 結果要約 |
|---|---|---|---|
| `prebuilt` / 全機能ON | 既存ディレクトリ利用 | `cmake --build skia/cmake-build-phase2-deps -j 8` | 成功 (`Built target reskia`) |
| `source` / 全機能ON | `cmake -S skia -B skia/cmake-build-phase4-source-on ...` | `cmake --build skia/cmake-build-phase4-source-on -j 8` | 成功 (`Built target reskia`) |
| `source` / AVIF+JPEGXL=OFF, RAW=ON | `cmake -S skia -B skia/cmake-build-phase4-source-compatible ...` | `cmake --build skia/cmake-build-phase4-source-compatible -j 8` | 成功 (`Built target reskia`) |
| `system` / 全機能ON | `cmake -S skia -B skia/cmake-build-phase4-system-on ...` | `cmake --build skia/cmake-build-phase4-system-on -j 8` | 成功 (`Built target reskia`) |

## `source` 全機能ONの AVIF/JPEGXL 導入手順

前提:

1. `libavif` と `jpeg-xl` を Homebrew で導入済み。
2. Homebrew prefix は既定 `/opt/homebrew`（必要なら `HOMEBREW_PREFIX` で上書き）。

手順:

1. Homebrew の codec 依存を `third_party/install` へ同期する。

```bash
scripts/sync_codec_deps_from_homebrew.sh
```

2. `source` 全機能ONで configure/build を実行する。

```bash
cmake -S skia -B skia/cmake-build-phase4-source-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_AVIF=ON \
  -DRESKIA_ENABLE_JPEGXL=ON \
  -DRESKIA_ENABLE_RAW=ON \
  -DRESKIA_ENABLE_GIF=ON \
  -DRESKIA_ENABLE_JPEG_ENCODER=ON \
  -DRESKIA_ENABLE_WEBP_ENCODER=ON \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-phase4-source-on -j 8
```

同期対象（必須）:

- `third_party/install/lib/libavif.dylib`
- `third_party/install/lib/libjxl.dylib`
- `third_party/install/lib/libjxl_threads.dylib`
- `third_party/install/lib/libjxl_cms.dylib`
- `third_party/install/include/avif`
- `third_party/install/include/jxl`

## 判定

- `prebuilt` / `source` / `system` すべてで全機能ONビルド成功。
- `source` 全機能ONの阻害要因だった `avif` 欠如は解消済み。
