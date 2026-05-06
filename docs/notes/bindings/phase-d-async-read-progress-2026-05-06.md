# Phase D: async read API binding progress

作業日時: 2026-05-06

## 対象

Phase D では `SkImage` / `SkSurface` の async read 系 API を C ABI として公開した。

- `SkImage::asyncRescaleAndReadPixels`
- `SkImage::asyncRescaleAndReadPixelsYUV420`
- `SkImage::asyncRescaleAndReadPixelsYUVA420`
- `SkSurface::asyncRescaleAndReadPixels`
- `SkSurface::asyncRescaleAndReadPixelsYUV420`
- `SkSurface::asyncRescaleAndReadPixelsYUVA420`

## 実装方針

- C++ の `SkImage::ReadPixelsCallback` / `SkSurface::ReadPixelsCallback` を直接 ABI に出さず、`reskia_async_read_pixels_callback_t` を追加した。
- `AsyncReadResult` は `reskia_async_read_result_t` として opaque 化した。
- result は callback 中だけ有効な borrowed object とした。呼び出し側が callback 後も保持したい場合は、callback 内で pixel data をコピーする必要がある。
- accessor は `Reskia_AsyncReadResult_count` / `Reskia_AsyncReadResult_data` / `Reskia_AsyncReadResult_rowBytes` の 3 つに絞った。
- invalid input では callback があれば即時に `result == nullptr` で通知する。

## 変更点

- `skia/capi/sk_async_read_result.h`
- `skia/capi/sk_async_read_result-internal.h`
- `skia/capi/sk_async_read_result.cpp`
- `skia/capi/sk_image.h`
- `skia/capi/sk_image.cpp`
- `skia/capi/sk_surface.h`
- `skia/capi/sk_surface.cpp`
- `cmake/reskia/sources-capi.cmake`
- `skia/test/test_phase_d_async_read_smoke.cpp`
- `cmake/reskia/tests.cmake`

## coverage

`scripts/generate_public_api_coverage.py` の再生成後、`public-api-coverage-matrix.csv` では `include/core/SkImage.h` と `include/core/SkSurface.h` の対象 6 件が `covered` になった。

`public-api-core-effects-missing-triage.csv` でも該当行を `covered` / `P0` に更新した。

## 検証

成功:

- `python3 -m py_compile scripts/generate_public_api_coverage.py`
- `python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia`
- `cmake -S skia -B skia/cmake-build-codex-project-survey-prebuilt -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build skia/cmake-build-codex-project-survey-prebuilt -j 8`
- `c++ -std=c++17 -I skia -I skia/include skia/test/test_phase_d_async_read_smoke.cpp skia/cmake-build-codex-project-survey-prebuilt/libreskia.dylib -Wl,-rpath,/Users/dolphilia/github/reskia/skia/cmake-build-codex-project-survey-prebuilt -o /private/tmp/reskia_phase_d_async_read_smoke`
- `/private/tmp/reskia_phase_d_async_read_smoke`

制約:

- `cmake -S skia -B skia/cmake-build-codex-phase-d-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON` は configure 成功。
- `cmake --build skia/cmake-build-codex-phase-d-tests --target test_phase_d_async_read_smoke -j 8` は、既存 test 構成が `SkTestCanvas.cpp` 関連の未解決シンボルで `reskia` link に失敗するため完走しない。
