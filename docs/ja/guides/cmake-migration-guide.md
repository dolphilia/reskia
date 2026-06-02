# CMake ビルドガイド

この文書は、Reskia を CMake で configure / build するための標準手順をまとめます。

Reskia はリポジトリルートではなく、`skia/CMakeLists.txt` を CMake の入口にします。

## 要件

- CMake 3.26.4 以上
- C++17 対応コンパイラ
- `source` モードを使う場合は、依存ライブラリを `third_party/install` に用意できる環境

macOS / AppleClang が主要な検証環境です。Windows と Linux では、機能フラグや依存解決の対応状況に差があります。

## 依存解決モード

`RESKIA_DEPS_MODE` で依存ライブラリの解決方法を選びます。

| mode | 既定 | 用途 |
| --- | --- | --- |
| `prebuilt` | yes | 事前に用意された依存を使って短時間でビルドする。 |
| `source` | no | `third_party` 管理の依存を使い、再現性を高める。 |
| `system` | no | OS や package manager で導入済みの依存を使う。 |

mode は configure 時に明示できます。

```bash
cmake -S skia -B skia/cmake-build-local -DRESKIA_DEPS_MODE=prebuilt
```

## `prebuilt` モード

最短で `reskia` を確認する標準手順です。

```bash
cmake -S skia -B skia/cmake-build-prebuilt \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=prebuilt
cmake --build skia/cmake-build-prebuilt -j 8
```

`RESKIA_DEPS_MODE` を省略した場合も、既定では `prebuilt` として扱われます。

## `source` モード

依存ライブラリの準備を含めて再現したい場合に使います。

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source -j 8
```

追加依存が必要な機能を使う場合は、依存ビルド時のオプションと CMake の機能フラグを揃えます。

例:

```bash
scripts/build_third_party.sh --build-type Release --clean --with-avif
cmake -S skia -B skia/cmake-build-avif \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_AVIF=ON
```

## `system` モード

システム側に導入済みの依存を使います。

```bash
cmake -S skia -B skia/cmake-build-system \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=system
cmake --build skia/cmake-build-system -j 8
```

必要に応じて `CMAKE_PREFIX_PATH`、`PKG_CONFIG_PATH`、個別の `*_DIR` を指定します。

## テスト

テストは既定では無効です。C API smoke を含めて確認する場合は `RESKIA_BUILD_TESTS=ON` を指定します。

```bash
cmake -S skia -B skia/cmake-build-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-tests -j 8
ctest --test-dir skia/cmake-build-tests --output-on-failure
```

optional feature の smoke は、対応する機能フラグと依存が揃った場合だけ登録されます。

## よく使う機能フラグ

| 領域 | 主なフラグ |
| --- | --- |
| Codec / encoder | `RESKIA_ENABLE_AVIF`, `RESKIA_ENABLE_JPEGXL`, `RESKIA_ENABLE_RAW`, `RESKIA_ENABLE_GIF`, `RESKIA_ENABLE_PDF`, `RESKIA_ENABLE_JPEG_ENCODER`, `RESKIA_ENABLE_WEBP_ENCODER` |
| Text / animation | `RESKIA_ENABLE_SKSG`, `RESKIA_ENABLE_SKOTTIE`, `RESKIA_ENABLE_SKPARAGRAPH`, `RESKIA_ENABLE_FONTCONFIG_CAPI` |
| GPU | `RESKIA_ENABLE_GPU_GANESH`, `RESKIA_ENABLE_GPU_GRAPHITE`, `RESKIA_ENABLE_GPU_VULKAN`, `RESKIA_ENABLE_GPU_METAL`, `RESKIA_ENABLE_GPU_DAWN` |

代表的な制約:

- `RESKIA_DEPS_MODE=source` on Windows は未実装です。
- `RESKIA_ENABLE_GPU_METAL=ON` は Apple 環境が必要です。
- `RESKIA_ENABLE_GPU_DAWN=ON` は `RESKIA_ENABLE_GPU_GRAPHITE=ON` が必要です。
- text stack 関連機能は HarfBuzz、ICU、ICU4X、libgrapheme などの有無で縮退します。

## 失敗時の確認項目

ビルドや configure に失敗した場合は、少なくとも次を確認します。

1. 実行した configure コマンド。
2. `RESKIA_DEPS_MODE` の値。
3. 有効にした `RESKIA_ENABLE_*` フラグ。
4. `third_party/install` または system dependency の有無。
5. platform 固有機能を有効にしていないか。

関連文書:

- `docs/ja/README.md`
- `third_party/README.md`
- `docs/ja/guides/repository-structure.md`
