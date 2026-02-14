# third_party

Reskia の依存ライブラリを、ソース分離かつ再現可能に管理するための領域です。

## 構成

- `third_party/src/*`: 依存ライブラリ本体（git submodule）
- `third_party/build/*`: 各依存のビルドディレクトリ（生成物）
- `third_party/install/*`: 各依存の install 先（生成物）

## サブモジュール

現在 `src` 配下は以下をサブモジュール管理しています。

- `zlib`
- `libpng`
- `libjpeg-turbo`
- `libwebp`
- `libavif`
- `expat`
- `harfbuzz`
- `icu`
- `icu4x`
- `libgrapheme`

初期化:

```bash
scripts/bootstrap_third_party.sh
```

## 依存ビルド自動化

core 依存（zlib/libpng/libjpeg-turbo/expat/libwebp）:

```bash
scripts/build_third_party.sh --build-type Release --clean
```

オプション依存:

```bash
scripts/build_third_party.sh --with-avif --with-harfbuzz --with-libgrapheme --with-icu --with-icu4x
```

## 注意

- `--with-avif` はコーデック依存を外部取得するため、ネットワーク環境に依存します。
- `--with-icu4x` は Rust ツールチェーン（`cargo`）が必要です。
