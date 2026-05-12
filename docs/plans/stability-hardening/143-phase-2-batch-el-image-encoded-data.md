# 143 Phase 2 Batch EL: image encoded data ownership

開始時刻: 2026-05-13 07:56:07 JST

## 目的

`142-phase-2-batch-ek-canvas-picture-text-blob.md` の「次バッチ候補」から、`SkImage_refEncodedData` の returned data handle ownership と failure 0 規約を再確認する。NULL image と encoded data を持たない image は 0 を返し、encoded data を持つ image では呼び出し側所有の retained data handle を返すことを明文化する。

## 変更内容

- `skia/capi/sk_image.h`
  - `SkImage_refEncodedData` のコメントを、caller-owned retained data handle、`static_sk_data_delete` による削除、NULL / encoded data 不在時の 0 戻りが明確になるよう整えた。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - 既存の NULL image と raster snapshot image without encoded data の 0 戻り確認を維持した。
  - valid encoded image 経路は、現行 prebuilt 構成では GIF / PNG fixture とも `SkImages_DeferredFromEncodedData` が 0 になったため、構成非依存の smoke には入れなかった。ownership は `SkImage_refEncodedData` が `sk_sp<SkData>` を handle 化する実装とヘッダーコメントで明確化する。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` の P2 記録を Batch EL に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_image_surface_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` draw glyph array 系の count / array required と origin handle 規約をまとめて再確認する。
- `SkCanvas` draw string / simple text 系の text buffer / font / paint required 規約をまとめて再確認する。
- `SkCanvas` saveLayer 系の bounds / paint optional と returned save count 規約をまとめて再確認する。
- `SkCanvas` state transform / clip helper 系の required geometry pointer と no-op 規約をまとめて再確認する。
- `SkImage` makeShader / makeRawShader 系の sampling required と localMatrix optional 規約をまとめて再確認する。
