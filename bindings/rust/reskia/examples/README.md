# window_shapes

`window_shapes.rs` は、Reskia で CPU ラスタ描画した図形を `winit + softbuffer` のウィンドウへ表示する最小サンプルです。

## 事前準備

`libreskia` をビルドしておきます（例: prebuilt Debug）。

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

## 実行

```bash
RESKIA_LIB_DIR=/Users/dolphilia/github/reskia/skia/cmake-build-local \
  cargo run -p reskia --example window_shapes
```

`RESKIA_LIB_DIR` は `libreskia.dylib` があるディレクトリに合わせて変更してください。
