# Phase 2 Batch HS - Buffer Path Recording Font Runtime Ledger

開始時刻: 2026-05-14 00:12:06 JST

## 目的

`227-phase-2-batch-hr-mesh-geometry-pixel-text-ledger.md` の「次バッチ候補」5 件を順に処理し、既存 smoke の根拠を詳細進捗台帳へ登録する。今回は実装拡張ではなく、過去バッチで分散していた安全規約を API 群単位の安定 ID として固定し、次回以降の重複作業を避けられる状態にする。

## 変更内容

- `read_write_buffer_serialization`
  - `SkReadBuffer` / `SkWriteBuffer` の receiver 必須、入力 memory / output storage 必須、returned byte/span の呼び出し中借用規約を台帳化した。
  - `test_read_write_buffer_invalid_input_smoke.cpp` を根拠に、invalid path と代表的 serialization valid path を `covered` とした。
- `path_region_builder_geometry`
  - `SkRegion` / `SkPath` / `SkPathBuilder` の geometry pointer、enum、mutation、returned handle ownership を台帳化した。
  - `test_region_invalid_input_smoke.cpp`、`test_path_invalid_input_smoke.cpp`、`test_path_builder_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `picture_drawable_recording_helpers`
  - `SkPictureRecorder` / `SkDrawable` / `SkOverdrawCanvas` の recording canvas 借用 lifetime と returned picture / drawable handle ownership を台帳化した。
  - `test_picture_recorder_invalid_input_smoke.cpp`、`test_drawable_flattenable_invalid_input_smoke.cpp`、`test_overdraw_canvas_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `font_typeface_mgr_helpers`
  - `SkFont` / `SkTypeface` / `SkFontMgr` / `SkFontStyleSet` / `SkFontArguments` の receiver、family/text/glyph 入力、returned font object ownership、platform-gated Mac typeface の扱いを台帳化した。
  - `test_font_invalid_input_smoke.cpp`、`test_typeface_invalid_input_smoke.cpp`、`test_font_mgr_invalid_input_smoke.cpp`、`test_font_style_set_invalid_input_smoke.cpp`、`test_font_arguments_metrics_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `runtime_effect_builder_helpers`
  - `SkRuntimeEffect` と runtime builder の source string 必須、data handle `0` empty data 許可、child array count 規約、returned shader/filter/blender handle ownership を台帳化した。
  - `test_runtime_effect_invalid_input_smoke.cpp` を根拠に `covered` とした。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target ... -j 8`
  - 成功
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(read_write_buffer|region|path|path_builder|picture_recorder|drawable_flattenable|overdraw_canvas|font|typeface|font_mgr|font_style_set|font_arguments_metrics|runtime_effect|typeface_mac)_invalid_input_smoke' --output-on-failure`
  - 14/14 passed
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 成功
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 成功
- `cmake --build skia/cmake-build-codex-docrefresh-prebuilt -j 8`
  - 成功
- `git diff --check`
  - 成功

## 進捗概算

詳細台帳は 46 行中、`covered` / `omitted-with-reason` 相当が 43 行になった。`valid_path_status` 基準の概算進捗は約 93.5%。

残る代表扱いは `image_async_rescale`、`canvas_atlas_patch_vertices_mesh`、`mesh_specification_factory_guards` の 3 件。これらは環境依存、C accessor 不足、result unwrapping 不足が理由で、単純な smoke 追加だけでは完了扱いにしない。

## 次のバッチ候補

過去バッチと今回の HS 登録分に重複しないよう、詳細台帳未登録の領域から候補を選ぶ。

- `SkColorInfo` / `SkColorSpace` / `SkColorMatrixFilter` / color value helpers smoke を詳細台帳に登録し、borrowed color space と returned filter/data handle ownership を整理する。
- `SkStream` / `SkWStream` / file stream / memory stream smoke を詳細台帳に登録し、borrowed buffer、owned stream handle、read/write count 規約を整理する。
- `SkPaint` / `SkPathEffect` / `SkMaskFilter` / shader / blender helper smoke を詳細台帳に登録し、nullable effect handle と returned handle ownership を整理する。
- `SkBitmap` / `SkImageInfo` / `SkSurfaceProps` / `SkSurfaces` smoke を詳細台帳に登録し、caller-owned pixel storage と returned surface handle ownership を整理する。
- `SkYUVAInfo` / `SkYUVAPixmaps` / `SkTiledImageUtils` smoke を詳細台帳に登録し、plane count、storage lifetime、factory failure 規約を整理する。
