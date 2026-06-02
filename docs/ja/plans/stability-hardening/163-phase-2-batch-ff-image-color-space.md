# 163 Phase 2 Batch FF: image color space conversion rules

開始時刻: 2026-05-13 09:29:33 JST

## 目的

`162-phase-2-batch-fe-canvas-rect-rrect-oval-arc.md` の「次バッチ候補」から、`SkImage` makeColorSpace / reinterpretColorSpace 系の color_space handle optional/valid 規約をまとめて再確認する。`color_space` handle `0` は null color space として許容し、非 0 の stale / invalid handle は `0` 戻りにする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - `SkImage_makeColorSpace` / `SkImage_makeColorSpaceWithRecorder` / `SkImage_reinterpretColorSpace` が `has_optional_color_space_handle` で handle を検証していることを確認した。
- `skia/capi/sk_image.h`
  - color space 変換系の returned image handle が caller-owned であることを明記した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image、invalid color space handle、valid SRGB handle smoke を確認し、今回のコメント方針と整合させた。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` drawable / mesh 系の borrowed pointer と handle validation 規約をまとめて再確認する。
- `SkImage` async rescale read 系の enum range と callback failure 規約をまとめて再確認する。
- `SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。
- `SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。
- `SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。
