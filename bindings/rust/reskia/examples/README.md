# window_shapes

`window_shapes.rs` is a minimal example that draws CPU-rasterized shapes with
Reskia and presents them in a `winit` + `softbuffer` window.

## Build Reskia

Build `libreskia` first. The default dependency mode is `prebuilt`.

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-local -j 8
```

## Run the Example

Run the example from the repository root and point `RESKIA_LIB_DIR` at the
directory that contains `libreskia.dylib` or the platform equivalent.

```bash
RESKIA_LIB_DIR="$PWD/skia/cmake-build-local" \
  cargo run -p reskia --example window_shapes
```

On macOS, the built library is normally
`skia/cmake-build-local/libreskia.dylib`.
