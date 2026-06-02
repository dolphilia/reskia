# 175 Phase 2 Batch FR: image readPixels and scalePixels pixmap rules

開始時刻: 2026-05-13 09:50:09 JST

## 目的

`174-phase-2-batch-fq-canvas-glyphs.md` の「次バッチ候補」から、`SkImage` readPixels / scalePixels pixmap 系の pixmap required と cachingHint enum 規約をまとめて再確認する。pixmap / sampling / storage は required、`cachingHint` は valid enum、invalid input は false とする。

## 変更内容

- `skia/capi/sk_image.cpp`
  - readPixels pixmap 系と scalePixels が NULL image / NULL pixmap / NULL sampling / invalid cachingHint を false にしていることを確認した。
- `skia/capi/sk_image.h`
  - 既存コメントが pixmap required、sampling required、cachingHint valid enum、invalid false を明記していることを確認した。
- `skia/test/test_image_surface_invalid_input_smoke.cpp`
  - NULL image に対する `readPixelsWithContextPixmap` / `readPixelsWithPixmap` / `scalePixels` smoke を追加した。
  - 既存の NULL pixmap、invalid cachingHint、valid pixmap storage smoke を維持した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_image.cpp` / `sk_image.h` を Batch FR に更新した。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target test_image_surface_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface)_invalid_input_smoke' --output-on-failure`
  - 成功。2/2 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。

## 次バッチ候補

- `SkCanvas` draw picture 系の picture handle / borrowed pointer と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` shader factory 系の sampling/localMatrix と returned shader ownership 規約をまとめて再確認する。
- `SkCanvas` draw image rect / lattice / nine 系の sampling/filter/constraint と required geometry pointer 規約をまとめて再確認する。
- `SkImage` encoded data / texture validity getter 系の retained data handle と bool/numeric failure 規約をまとめて再確認する。
- `SkCanvas` clip shader / clip geometry 系の shader handle、clip op enum、required geometry pointer 規約をまとめて再確認する。
