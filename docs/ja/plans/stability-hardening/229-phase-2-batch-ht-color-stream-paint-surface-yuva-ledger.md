# Phase 2 Batch HT - Color Stream Paint Surface YUVA Ledger

開始時刻: 2026-05-14 00:16:58 JST

## 目的

`228-phase-2-batch-hs-buffer-path-recording-font-runtime-ledger.md` の「次バッチ候補」5 件を順に処理し、詳細進捗台帳へ安定 ID として登録する。今回も実装拡張ではなく、既存 smoke で確認できる安全規約を API 群単位に集約し、未確認の valid path は過大に `covered` としない。

## 変更内容

- `color_space_filter_value_helpers`
  - `SkColorInfo` / `SkColorSpace` / `SkColor4f` / `SkColorMatrix` / `SkColorMatrixFilter` / `SkColor` の borrowed color space、retained handle、output buffer、static conversion helper 規約を台帳化した。
  - `test_color_info_space_invalid_input_smoke.cpp`、`test_color_values_invalid_input_smoke.cpp`、`test_color_matrix_filter_invalid_input_smoke.cpp`、`test_color_core_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `stream_wstream_file_helpers`
  - `SkStream` / `SkMemoryStream` / `SkWStream` / `SkDynamicMemoryWStream` / `SkFILEStream` / `SkFILEWStream` の count と buffer、file path / file handle、borrowed memory base、detached handle ownership を台帳化した。
  - `test_stream_invalid_input_smoke.cpp`、`test_wstream_invalid_input_smoke.cpp`、`test_file_stream_invalid_input_smoke.cpp`、`test_stream_derived_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `paint_effect_shader_blender_helpers`
  - `SkPaint` と base effect / shader / color filter / blender 群の nullable setter、factory failure、serialization、returned handle ownership を台帳化した。
  - `test_paint_invalid_input_smoke.cpp`、`test_path_effect_invalid_input_smoke.cpp`、`test_mask_filter_invalid_input_smoke.cpp`、`test_shader_invalid_input_smoke.cpp`、`test_color_filter_invalid_input_smoke.cpp`、`test_blender_invalid_input_smoke.cpp`、`test_blenders_invalid_input_smoke.cpp` を根拠に `covered` とした。
- `bitmap_imageinfo_surface_helpers`
  - `SkBitmap` / `SkImageInfo` / `SkSurfaceProps` / `SkSurfaces` の image info rowBytes、surface props clone、surface factory failure、wrapped pixel storage lifetime を台帳化した。
  - `ImageInfo` / `SurfaceProps` / `Null surface` の valid path は確認済みだが、bitmap pixel allocation と `WrapPixels` valid caller-owned storage は現行 smoke では代表確認に留まるため `representative-valid-path` とした。
- `yuva_tiled_image_helpers`
  - `SkYUVAInfo` / `SkYUVAPixmapInfo` / `SkYUVAPixmaps` / `SkTiledImageUtils` の plane count、external memory lifetime、factory failure、key output zero-fill 規約を台帳化した。
  - YUVA pixmap の valid allocation / external memory / plane path は確認済みだが、`SkTiledImageUtils` の valid image drawing は現行 smoke では未確認のため `representative-valid-path` とした。

## 検証

- `cmake --build skia/cmake-build-stability-tests --target ... -j 8`
  - 成功
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(color_info_space|color_values|color_matrix_filter|color_core|stream|wstream|file_stream|stream_derived|paint|path_effect|mask_filter|shader|color_filter|blender|blenders|bitmap|image_info|surface_props_surfaces|yuva_info|yuva_pixmaps|tiled_image_utils)_invalid_input_smoke' --output-on-failure`
  - 21/21 passed
- `python3 scripts/validate_capi_safety_detail_status.py`
  - 成功
- `awk -F, 'NR==1{n=NF} NF!=n{print NR; bad=1} END{exit bad}' docs/ja/plans/c-binding-remediation/checklists/capi-safety-detail-status.csv`
  - 成功
- `cmake --build skia/cmake-build-codex-docrefresh-prebuilt -j 8`
  - 成功
- `git diff --check`
  - 成功

## 進捗概算

詳細台帳は 51 行中、`covered` / `omitted-with-reason` 相当が 46 行になった。`valid_path_status` 基準の概算進捗は約 90.2%。

今回、`bitmap_imageinfo_surface_helpers` と `yuva_tiled_image_helpers` は重複防止のために台帳化したが、valid path は代表扱いに留めた。未確認の valid storage / draw path を無理に完了扱いにしないことで、今後の追加 smoke の対象を明確にする。

## 次のバッチ候補

過去バッチ、HS、HT の登録分と重複しないよう、詳細台帳未登録の領域から候補を選ぶ。

- `SkContourMeasure` / `SkPathMeasure` smoke を詳細台帳に登録し、path measurement iterator、returned segment path、borrowed contour lifetime を整理する。
- `SkImageFilter` / image filter factory smoke を詳細台帳に登録し、optional crop rect、required child filter handle、returned filter ownership を整理する。
- `SkCodec` / decoder / encoder / image generator smoke を詳細台帳に登録し、encoded data ownership、result enum、output pixel storage 規約を整理する。
- `SkAutoCanvasRestore` / `SkBBoxHierarchy` / `SkRasterHandleAllocator` / `SkRefCnt` smoke を詳細台帳に登録し、RAII helper、borrowed callback object、refcount no-op 規約を整理する。
- `SkRect` / `SkRRect` / `SkCubicMap` / `SkEncodedCubic` / `SkOpBuilder` smoke を詳細台帳に登録し、value helper output、path operation result、returned handle ownership を整理する。
