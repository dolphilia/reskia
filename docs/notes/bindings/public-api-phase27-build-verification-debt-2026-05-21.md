# Public API Coverage Phase 27 Build Verification Debt

Date: 2026-05-21

## Problem

The GPU C API smoke target in the prebuilt build directory failed at link time:

```text
Undefined symbols for architecture arm64:
  "SkShaper::Make(sk_sp<SkFontMgr>)", referenced from:
      SkSVGTextContext::SkSVGTextContext(...) in libsvg.a[40](SkSVGText.cpp.o)
```

This blocked verification for recent GPU C API work even though the failure was not caused by those C API changes.

## Cause

The source-mode `modules/svg/CMakeLists.txt` already defines the dependency chain:

```text
svg -> skshaper -> skunicode
```

The prebuilt-mode artifact directory contained:

```text
skia/lib/libskcms.a
skia/lib/libskresources.a
skia/lib/libsvg.a
```

but did not contain:

```text
libskshaper.a
libskunicode.a
```

`libsvg.a` still contains `SkSVGText.cpp.o`, which references `SkShaper::Make(sk_sp<SkFontMgr>)`. Therefore the prebuilt internal library closure was incomplete for any final link that pulls the SVG text object into `libreskia.dylib`.

## Fix

For Apple non-source dependency modes, `skia/CMakeLists.txt` now creates local fallback static targets:

- `skunicode` from `SkUnicode.cpp` and `SkUnicode_hardcoded.cpp`
- `skshaper` from `SkShaper.cpp`, `SkShaper_primitive.cpp`, and `SkShaper_coretext.cpp`

These targets are appended to `RESKIA_INTERNAL_LIBS` when present. The prebuilt `libsvg.a` remains in use; the fallback targets only provide the missing text shaping symbols.

Source mode is unchanged because it already gets `svg`, `skshaper`, and `skunicode` from `modules/svg/CMakeLists.txt`.

## Verification

Commands run:

```sh
cmake -S skia -B skia/cmake-build-codex-phase9-gpu -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codex-phase9-gpu --target test_gpu_context_capi_smoke -j 8
skia/cmake-build-codex-phase9-gpu/test_gpu_context_capi_smoke
cmake -S skia -B skia/cmake-build-codex-phase3-svg-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codex-phase3-svg-source --target test_svg_image_capi_smoke -j 8
skia/cmake-build-codex-phase3-svg-source/test_svg_image_capi_smoke
skia/cmake-build-codex-phase3-svg-source/test_svg_types_capi_smoke
```

Results:

- `test_gpu_context_capi_smoke` built and linked successfully in prebuilt mode.
- Runtime reported `SKIP: Metal device is unavailable in this environment` and then `PASS`, which is expected for a machine/session without a Metal device.
- source-mode SVG image and SVG types smoke tests passed.

## Remaining Risk

The fallback targets are intentionally minimal and match the current dependency-reduced environment. If the prebuilt SVG artifact is later built with HarfBuzz/ICU-specific shaping assumptions, the prebuilt distribution should ship matching `libskshaper.a` / `libskunicode.a` artifacts instead of relying on the fallback.
