# 166 Phase 2 Batch FI: canvas annotation data rules

開始時刻: 2026-05-13 09:29:33 JST

## 目的

`165-phase-2-batch-fh-image-async-rescale.md` の「次バッチ候補」から、`SkCanvas` draw annotation / data handle 系の optional data handle と key/rect required 規約をまとめて再確認する。annotation は `rect` / `key` を required、data handle `0` を optional null、非 0 data handle を valid required とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawAnnotation` が `has_optional_data_handle` で optional data handle を検証していることを確認した。
  - `SkCanvas_drawAnnotationWithDataPtr` は `value` NULL を Skia に渡せる optional pointer として維持した。
- `skia/capi/sk_canvas.h`
  - 既存の annotation コメントが `rect` / `key` required、data handle `0` optional、非 0 valid を明記していることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - NULL canvas に対する annotation 系 no-op smoke を追加した。
  - 既存の valid canvas 上の NULL rect / NULL key / invalid data handle / optional data NULL smoke を維持した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp` / `sk_canvas.h` を Batch FI に更新した。
  - `sk_image.cpp` / `sk_image.h` を Batch FH に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` experimental edge AA quad / image set 系の array pointer、blend/filter enum、constraint 規約をまとめて再確認する。
- `SkImage` makeColorTypeAndColorSpace 系の targetColorType enum と returned handle 規約をまとめて再確認する。
- `SkCanvas` draw vertices 系の vertices handle / pointer と blend mode enum 規約をまとめて再確認する。
- `SkImage` makeSubset / withDefaultMipmaps / makeNonTextureImage 系の returned handle ownership と factory failure 0 規約をまとめて再確認する。
- `SkCanvas` draw text blob / string 系の text/blob handle、borrowed pointer、font/paint required 規約をまとめて再確認する。
