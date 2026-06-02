# 211 Phase 2 Batch HB: canvas state getter rules

開始時刻: 2026-05-13 11:21:28 JST

## 目的

`210-phase-2-batch-ha-image-async-rescale.md` の「次バッチ候補」から、`SkCanvas` save/restore/state getter 系の NULL receiver、numeric/bool getter、state mutation no-op 規約を再確認する。numeric getter は NULL receiver `0`、bool getter は false、void state mutation は no-op とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_getSaveCount` / `SkCanvas_save` が NULL canvas `0` を返すことを確認した。
  - `SkCanvas_restore` / `SkCanvas_restoreToCount` が NULL canvas no-op であることを確認した。
  - `SkCanvas_isClipRect` が NULL canvas false を返すことを確認した。
  - `SkCanvas_isClipEmpty` をガイドの bool getter 規約に合わせ、NULL canvas false に変更した。
  - `SkCanvas_quickReject` / `SkCanvas_quickRejectRect` が invalid input false を返すことを確認した。
- `skia/capi/sk_canvas.h`
  - `getSaveCount` / `isClipEmpty` / `isClipRect` / `quickReject*` の NULL / invalid return コメントを更新した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - `SkCanvas_isClipEmpty(nullptr)` / `SkCanvas_isClipRect(nullptr)` false smoke を追加した。
  - 既存の save / restore / quickReject / handle getter smoke が揃っていることを確認した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch HB、`sk_image.cpp/h` を batch HA の進捗として更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_canvas_invalid_input_smoke -j 8`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 成功。既存の `capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` makeSurface / recorder / recordingContext / getSurface 系の returned handle / borrowed pointer 規約をまとめて再確認する。
- `SkImage` texture / backend / Graphite / Ganesh context 系の optional context と feature-gated no-op 規約をまとめて再確認する。
- `SkCanvas` getLocalToDevice / matrix getter 系の caller-owned handle と NULL receiver 0 規約をまとめて再確認する。
- `SkImage` ref/unref/release/unique/asLegacyBitmap 系の refcount no-op と output pointer validation 規約をまとめて再確認する。
- `SkCanvas` MakeRasterDirect / newFromBitmap 系の borrowed pixel storage、rowBytes、props optional 規約をまとめて再確認する。
