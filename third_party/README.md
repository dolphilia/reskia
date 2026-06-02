# third_party

This directory stores third-party dependencies used by Reskia when dependencies
are built from source.

Reskia can also use prebuilt or system dependencies. See
`docs/en/guides/cmake-migration-guide.md` for the CMake-level dependency modes.

## Layout

- `third_party/src/*`: dependency source trees, managed as git submodules
- `third_party/build/*`: local dependency build directories, generated
- `third_party/install/*`: local dependency install prefixes, generated

Generated build and install directories are local artifacts and are not part of
the source-of-truth repository state.

## Submodules

The following dependency sources are managed under `third_party/src`:

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

Initialize or update them with:

```bash
scripts/bootstrap_third_party.sh
```

## Building Dependencies

Build the core dependencies (`zlib`, `libpng`, `libjpeg-turbo`, `expat`, and
`libwebp`) with:

```bash
scripts/build_third_party.sh --build-type Release --clean
```

Enable optional dependency groups as needed:

```bash
scripts/build_third_party.sh --with-avif --with-harfbuzz --with-libgrapheme --with-icu --with-icu4x
```

After the dependencies are installed under `third_party/install`, configure
Reskia with `RESKIA_DEPS_MODE=source`.

```bash
cmake -S skia -B skia/cmake-build-source \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_DEPS_MODE=source
cmake --build skia/cmake-build-source -j 8
```

## Notes

- `--with-avif` may download codec dependencies, so it depends on network
  access.
- `--with-icu4x` requires a Rust toolchain with `cargo`.
- `RESKIA_DEPS_MODE=source` on Windows is currently not implemented.
