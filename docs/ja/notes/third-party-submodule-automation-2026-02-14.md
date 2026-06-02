# third_party サブモジュール化と依存ビルド自動化（2026-02-14）

対象: `/Users/dolphilia/github/reskia`  
記録時刻: 2026-02-14 10:37:57 JST

## 1. 実施内容

### 1.1 `third_party/src/*` の実サブモジュール化

以下をサブモジュールとして登録:

- `third_party/src/zlib`
- `third_party/src/libpng`
- `third_party/src/libjpeg-turbo`
- `third_party/src/libwebp`
- `third_party/src/libavif`
- `third_party/src/expat`
- `third_party/src/harfbuzz`
- `third_party/src/icu`
- `third_party/src/icu4x`
- `third_party/src/libgrapheme`

反映ファイル:

- `/Users/dolphilia/github/reskia/.gitmodules`
- `/Users/dolphilia/github/reskia/.gitignore`（`third_party/src/*` を追跡可能化）

### 1.2 自動化スクリプト

- `/Users/dolphilia/github/reskia/scripts/bootstrap_third_party.sh`
  - `third_party/src/build/install` を準備
  - サブモジュールを `update --init --recursive` で初期化
- `/Users/dolphilia/github/reskia/scripts/build_third_party.sh`
  - core 依存を `install` まで自動化:
    - zlib
    - libpng
    - libjpeg-turbo
    - expat
    - libwebp
  - オプション:
    - `--with-avif`
    - `--with-harfbuzz`
    - `--with-libgrapheme`
    - `--with-icu`
    - `--with-icu4x`
  - `--clean`, `--jobs`, `--build-type` をサポート

### 1.3 `source` モード依存解決の修正

- `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake`
  - `source` で `expat/png/jpeg` を `find_library` ベース解決に変更
  - `RESKIA_ENABLE_AVIF`（既定 `OFF`）を追加

## 2. 検証結果

### 2.1 自動化スクリプト

実行:

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
```

結果:

- 成功（`third_party/install` に core 依存を導入）

### 2.2 `skia` の `source` モード

実行:

```bash
cmake -S skia -B skia/cmake-build-source-local -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-source-local -j 8
```

結果（2026-02-14 更新）:

- configure: 成功
- build: 成功（`Built target reskia`）
- 対応:
  - `skia/CMakeLists.txt` で `RESKIA_DEPS_MODE=source` 時に
    - `skcms`
    - （Apple）`skresources`, `svg`
    を `add_subdirectory` 連携するよう修正。

## 3. 制約

- third-party 自動化と `skcms/skresources/svg` の `source` 連携は実施済み。
- `--with-avif` は codec 依存取得が必要で、ネットワーク・外部取得に依存。
- `--with-icu4x` は Rust ツールチェーン（`cargo`）に依存。
- `svg/modules/skunicode/src/SkUnicode_icu4x.cpp` が期待する `ICU4X*.hpp` と、
  最新 ICU4X C++ binding の型名には差異があるため、ICU4X 連携を有効化するには追加の互換調整が必要。
