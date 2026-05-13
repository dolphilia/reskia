# 201 Phase 2 Batch GR: canvas image draw rules

開始時刻: 2026-05-13 10:18:40 JST

## 目的

`200-phase-2-batch-gq-image-encoded-data.md` の「次バッチ候補」から、`SkCanvas` draw image / image rect / image nine / image lattice 系の image handle、sampling、paint optional 規約を再確認する。void draw API は invalid input で no-op、image handle は valid handle、raw image pointer は borrowed non-null、paint は Skia が NULL を許容する overload では optional とする。

## 変更内容

- `skia/capi/sk_canvas.cpp`
  - `SkCanvas_drawImage` / handle image rect 系が static image handle を `has_image_handle` で検証することを確認した。
  - raw image pointer overload は image pointer NULL を no-op にすることを確認した。
  - sampling required overload は sampling NULL を no-op にし、paint は optional として渡すことを確認した。
  - lattice / nine patch 系は image / lattice or center / dst を required にし、filter enum を検証することを確認した。
  - src/dst rect overload は `SkCanvas::SrcRectConstraint` を検証することを確認した。
- `skia/capi/sk_canvas.h`
  - raw image pointer overload のコメントを borrowed non-null pointer と sampling required に揃えた。
  - image handle、sampling required、paint optional、filter / constraint enum validation のコメントが揃っていることを確認した。
- `skia/test/test_canvas_invalid_input_smoke.cpp`
  - invalid image handle、NULL required pointer、NULL optional paint、invalid filter / constraint、有効 handle/pointer draw の smoke が揃っていることを確認した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_canvas.cpp/h` を batch GR、`sk_image.cpp/h` を batch GQ の進捗として更新した。

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

- `SkCanvas` draw text blob / string / glyphs 系の text buffer、encoding、font/paint required 規約をまとめて再確認する。
- `SkImage` shader factory 系の tile mode、sampling、localMatrix optional 規約をまとめて再確認する。
- `SkCanvas` draw picture / drawable 系の handle/pointer ownership と optional matrix/paint 規約をまとめて再確認する。
- `SkImage` subset / color type / color space factory 系の recorder/context optional と properties validation 規約をまとめて再確認する。
- `SkCanvas` annotation / data 系の borrowed key/value、data handle optional、NULL no-op 規約をまとめて再確認する。
