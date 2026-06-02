# 04 Phase 4: ビルド行列確認

更新日時: 2026-02-16 15:43:19 JST

## 実施結果（最終）

| Case | Configure | Build | 結果要約 |
|---|---|---|---|
| `prebuilt` / 全機能ON | 既存ディレクトリ利用 | `cmake --build skia/cmake-build-phase2-deps -j 8` | 成功 (`Built target reskia`) |
| `source` / 全機能ON | `cmake -S skia -B skia/cmake-build-phase4-source-on ...` | `cmake --build skia/cmake-build-phase4-source-on -j 8` | 成功 (`Built target reskia`) |
| `source` / AVIF+JPEGXL=OFF, RAW=ON | `cmake -S skia -B skia/cmake-build-phase4-source-compatible ...` | `cmake --build skia/cmake-build-phase4-source-compatible -j 8` | 成功 (`Built target reskia`) |
| `system` / 全機能ON | `cmake -S skia -B skia/cmake-build-phase4-system-on ...` | `cmake --build skia/cmake-build-phase4-system-on -j 8` | 成功 (`Built target reskia`) |

## `source` 全機能ONの AVIF/JPEGXL 導入手順（サブモジュール前提）

前提:

1. `.gitmodules` に以下が登録済みであること:
   - `third_party/src/aom`
   - `third_party/src/libjxl`
   - `third_party/src/highway`
   - `third_party/src/brotli`
   - `third_party/src/lcms2`

手順:

1. サブモジュールを同期・取得する。

```bash
git submodule sync --recursive
git submodule update --init --recursive
scripts/bootstrap_third_party.sh
```

2. `third_party/install` へ AVIF/JPEGXL 依存をソースビルドで導入する。

```bash
scripts/build_third_party.sh --with-avif --with-jpegxl --build-type Release
```

3. `source` 全機能ONで configure/build を実行する。

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

導入対象（必須）:

- `third_party/install/lib/libavif.a`
- `third_party/install/lib/libjxl.a`
- `third_party/install/lib/libjxl_threads.a`
- `third_party/install/lib/libjxl_cms.a`
- `third_party/install/include/avif`
- `third_party/install/include/jxl`

注意:

- 以前に `scripts/sync_codec_deps_from_homebrew.sh` を実行している場合、`third_party/install/include/{avif,jxl,hwy,lcms2.h,lcms2_plugin.h}` の symlink が残っていると install 時に失敗するため、事前に削除してから再実行する。

## 判定

- `prebuilt` / `source` / `system` すべてで全機能ONビルド成功。
- `source` 全機能ONの阻害要因だった `avif` 欠如は解消済み。
