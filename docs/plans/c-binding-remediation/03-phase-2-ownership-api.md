# 03 Phase 2: Ownership API Rework (`skia/binding`)

## ゴール

- 解放ルールを明文化し、`delete` と `ref/unref` の混在を解消する。
- Rust/LuaJIT両対応できる API 形に揃える。

## 方針

- RefCounted型:
  - `retain/release` を正規APIにする。
  - `*_delete(void*)` は非推奨化し内部で `release` に委譲。
- 非RefCounted型:
  - `create/destroy` を維持。
  - `borrow` 系 API は解放不要であることを命名で明示。

## 作業ステップ

1. 型分類表を作成
- RefCounted / NonRefCounted / Borrowed の3分類を定義。
- `checklists/binding-status.csv` に `phase=P2` を設定して管理。

2. 解放APIの統一
- `*_delete` 実装を順次修正:
  - RefCounted: `delete` 直呼びを廃止し `unref/release` 経由へ変更。
  - NonRefCounted: `delete` を維持。
- ヘッダコメントに所有権を明示:
  - `owned`, `borrowed`, `retained`.

1. `void*` APIの型情報補強
- 連番関数名（`_2`, `_3`）には `note` で置換予定名を記録。
- Cプリミティブ型の正規化方針を追加:
  - `unsigned long`（`size_t` 代用）や `unsigned int`（`uint32_t` 代用）を段階的に型エイリアスへ統一。
  - 例: `reskia_size_t`, `reskia_u32_t`, `reskia_u64_t`（内部は `<stddef.h>/<stdint.h>` 由来）。
  - Skia独自意味型を C 側で明示する typedef を追加し、素の `unsigned int`/`int` 露出を削減。
  - 例: `reskia_color_t` (`SkColor`), `reskia_pmcolor_t` (`SkPMColor`), `reskia_typeface_id_t` (`SkTypefaceID`), `reskia_font_table_tag_t` (`SkFontTableTag`)
  - enum 戻り値/引数（例: `SkAlphaType`, `SkColorType`, `SkBlendMode`）の正規化方針:
    - 互換期間は ABI 互換を優先し、既存 `int` シグネチャは維持。
    - 併設する新シグネチャでは enum 意味型 typedef（例: `reskia_alpha_type_t`, `reskia_color_type_t`, `reskia_blend_mode_t`）を使用。
    - 旧関数は新関数への thin wrapper 化し、`note` に旧名/新名/削除予定を記録。
    - 実装側では `static_cast<Sk...>` を一箇所に閉じ込め、呼び出し側の生 `int` 依存を段階的に解消。
  - 対象マニフェスト:
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-voidptr-headers.txt`（111件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-suffix-headers.txt`（87件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-priority-headers.txt`（66件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-primitive-headers.txt`（75件）

1. IN/OUT引数規約の統一
- `out*` は必ず `reskia_status_t` 戻り値へ段階移行。
- NULL許容/非許容をコメントで統一記載。
- `*_in` / `*_out` 変数名依存を廃止し、シグネチャで方向性を表現:
  - `in`: 値渡しまたは `const` ポインタ引数
  - `out`: 末尾の `*_t* out_...` 引数
  - 関数戻り値: `reskia_status_t`（`RESKIA_STATUS_OK` / エラーコード）
- ハンドル引数の型情報を強化:
  - 例: `int function_void_void_key_in` -> `reskia_function_void_void_t function_key`
  - 例: `int sk_font_style_set_out` -> `sk_font_style_set_t* out_style_set`
- 互換維持の段階移行:
  1. 既存関数を維持したまま `...2`（または `..._with_status`）を追加
  2. 旧関数は新関数へ委譲する thin wrapper 化
  3. `note` に旧名/新名/削除予定を記録し、Phase 4で `deprecated` 化
- 優先対象（現時点で `_in/_out` を持つ関数）:
  - `SkFontMgr_createStyleSet(int sk_font_style_set_out, void *font_mgr, int index)`
  - `SkFontMgr_matchFamily(int sk_font_style_set_out, void *font_mgr, const char familyName[])`
  - `SkExecutor_add(int function_void_void_key_in, void *executor)`

1. フェーズ2検証

```bash
rg -n "delete static_cast<Sk.*>" skia/binding/*.cpp
rg -n "\\bref\\(|\\bunref\\(" skia/binding/*.cpp
cmake --build skia/cmake-build-local -j 8
```

## 進捗（2026-02-14）

- [x] 1. 型分類表を作成
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-type-classification.md`
  - 集計結果:
    - RefCounted: 28
    - NonRefCounted: 93
    - Borrowed API: 17
  - `checklists/binding-status.csv` 更新:
    - `status in {todo,doing,blocked}` の行に `phase=P2` を設定（299件）
    - `phase1` で `done` 済みの11件は履歴維持のため据え置き
- [x] 2. 解放APIの統一
  - 準備完了: `docs/plans/c-binding-remediation/checklists/phase2-release-api-status.csv` を追加（RefCounted 28型の header/cpp を追跡）
  - 進捗: 28/28 完了（`phase2-release-api-status.csv` 全件 `done`）
- [ ] 3. `void*` APIの型情報補強
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-type-hardening-status.csv`（Step3 専用）
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-enum-int-status.csv`（enum/int 露出改善専用）
  - 実施済みセット:
    - `skia/binding/sk_annotation.h` + `skia/binding/sk_annotation.cpp`（3/3 関数 `done`）
    - 変更内容: `void*` 引数を `reskia_canvas_t` / `reskia_rect_t` / `reskia_point_t` / `reskia_data_t` の不透明型ポインタへ置換
    - `skia/binding/sk_android_codec.h` + `skia/binding/sk_android_codec.cpp`（18/18 関数 `done`）
    - 変更内容: `SkAndroidCodec` 系シグネチャの `void*` を不透明型ポインタへ置換し、`rowBytes` を `size_t` へ正規化
    - `skia/binding/sk_b_box_hierarchy.h` + `skia/binding/sk_b_box_hierarchy.cpp`（8/8 関数 `done`）
    - 変更内容: `SkBBoxHierarchy` 系シグネチャの `void*` を不透明型ポインタへ置換し、`bytesUsed` 戻り値を `size_t` へ正規化
    - `skia/binding/sk_bitmap.h` + `skia/binding/sk_bitmap.cpp`（84/84 関数 `done`）
    - 変更内容: `SkBitmap` 系シグネチャの `void*` を不透明型ポインタへ置換し、`unsigned long/unsigned int` を `size_t/uint32_t` へ正規化
    - `skia/binding/sk_blender.h` + `skia/binding/sk_blender.cpp`（11/11 関数 `done`）
    - 変更内容: `SkBlender` 系シグネチャの `void*` を不透明型ポインタへ置換し、`serialize/deserialize` で `size_t` 正規化を実施
    - `skia/binding/sk_bmp_decoder.h` + `skia/binding/sk_bmp_decoder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkBmpDecoder` 系シグネチャで入力バッファを `const uint8_t* + size_t` に正規化し、`result/decodeContext` を不透明型ポインタ化
    - `skia/binding/sk_canvas.h` + `skia/binding/sk_canvas.cpp`（126/126 関数 `done`）
    - 変更内容: 全APIで `canvas` 受け口を `reskia_canvas_t*` に型強化し、`unsigned long/unsigned int` を `size_t/uint32_t` へ正規化
    - `skia/binding/sk_codec.h` + `skia/binding/sk_codec.cpp`（33/33 関数 `done`）
    - 変更内容: `SkCodec` 系シグネチャの `void*` を不透明型ポインタへ置換し、`rowBytes/length` を `size_t` に正規化
    - `skia/binding/sk_color.h` + `skia/binding/sk_color.cpp`（8/8 関数 `done`）
    - 変更内容: `SkColor` / `SkPMColor` / `U8CPU` を `reskia_color_t` / `reskia_pmcolor_t` / `reskia_u32_t` の意味型へ正規化
    - `skia/binding/sk_color_4f.h` + `skia/binding/sk_color_4f.cpp`（15/15 関数 `done`）
    - 変更内容: `SkColor4f` API を `reskia_color_4f_t*` 不透明型へ移行し、`SkColor`/`SkPMColor` を意味型 typedef（`reskia_color_t`/`reskia_pmcolor_t`）へ正規化
    - `skia/binding/sk_color_filter.h` + `skia/binding/sk_color_filter.cpp`（18/18 関数 `done`）
    - 変更内容: `SkColorFilter` API の `void*` を不透明型ポインタへ置換し、`size_t` と `reskia_color_t` でプリミティブ型を正規化
    - `skia/binding/sk_color_filters.h` + `skia/binding/sk_color_filters.cpp`（7/7 関数 `done`）
    - 変更内容: `SkColorFilters` API の `void*` と `unsigned int/unsigned char` を不透明型/意味型（`reskia_color_4f_t`, `reskia_color_t`, `uint8_t`）へ正規化
    - `skia/binding/sk_color_info.h` + `skia/binding/sk_color_info.cpp`（15/15 関数 `done`）
    - 変更内容: `SkColorInfo` API の `void*` を `reskia_color_info_t*` 不透明型へ置換し、戻り値ポインタを `reskia_color_space_t*` へ型強化
    - `skia/binding/sk_color_matrix.h` + `skia/binding/sk_color_matrix.cpp`（12/12 関数 `done`）
    - 変更内容: `SkColorMatrix` API の `void*` を `reskia_color_matrix_t*` 不透明型へ置換し、`set/getRowMajor` を `float[20]` へ型正規化
    - `skia/binding/sk_color_matrix_filter.h` + `skia/binding/sk_color_matrix_filter.cpp`（19/19 関数 `done`）
    - 変更内容: `SkColorMatrixFilter` API の `void*` を不透明型ポインタへ置換し、色プリミティブを `reskia_color_t`、サイズを `size_t` へ正規化
    - `skia/binding/sk_color_priv.h` + `skia/binding/sk_color_priv.cpp`（7/7 関数 `done`）
    - 変更内容: `SkColorPriv` API の整数引数/戻り値を `reskia_u32_t` / `reskia_pmcolor_t` へ意味型正規化
    - `skia/binding/sk_color_space.h` + `skia/binding/sk_color_space.cpp`（28/28 関数 `done`）
    - 変更内容: `SkColorSpace` API の `void*` を不透明型ポインタへ置換し、`size_t`/`uint32_t`/`uint64_t` と skcms 関連型を正規化
    - `skia/binding/sk_color_space_primaries.h` + `skia/binding/sk_color_space_primaries.cpp`（2/2 関数 `done`）
    - 変更内容: `SkColorSpacePrimaries` API の `void*` を不透明型ポインタへ置換し、`toXYZD50` の matrix 出力を型強化
    - `skia/binding/sk_color_table.h` + `skia/binding/sk_color_table.cpp`（12/12 関数 `done`）
    - 変更内容: `SkColorTable` API の `void*` を不透明型ポインタへ置換し、テーブル入力/出力を `uint8_t[256]` / `const uint8_t*` に正規化
    - `skia/binding/sk_contour_measure.h` + `skia/binding/sk_contour_measure.cpp`（9/9 関数 `done`）
    - 変更内容: `SkContourMeasure` API の `void*` を不透明型ポインタへ置換し、`SkPoint` / `SkVector` / `SkMatrix` / `SkPath` 引数を型強化
    - `skia/binding/sk_contour_measure_iter.h` + `skia/binding/sk_contour_measure_iter.cpp`（5/5 関数 `done`）
    - 変更内容: `SkContourMeasureIter` API の `void*` を不透明型ポインタへ置換し、`SkPath` 入力引数を型強化
    - `skia/binding/sk_cubic_map.h` + `skia/binding/sk_cubic_map.cpp`（4/4 関数 `done`）
    - 変更内容: `SkCubicMap` API の `void*` を `reskia_cubic_map_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_cubic_resampler.h` + `skia/binding/sk_cubic_resampler.cpp`（1/1 関数 `done`）
    - 変更内容: `SkCubicResampler` API の `delete` 受け口を `reskia_cubic_resampler_t*` へ型強化
    - `skia/binding/sk_data.h` + `skia/binding/sk_data.cpp`（22/22 関数 `done`）
    - 変更内容: `SkData` API の `void*` を不透明型/バイト列型へ置換し、`unsigned long/unsigned int` を `size_t/int32_t` へ正規化
    - `skia/binding/sk_data_table.h` + `skia/binding/sk_data_table.cpp`（12/12 関数 `done`）
    - 変更内容: `SkDataTable` API の `void*` を不透明型/バイト列型へ置換し、`unsigned long` を `size_t` へ正規化
    - `skia/binding/sk_discrete_path_effect.h` + `skia/binding/sk_discrete_path_effect.cpp`（2/2 関数 `done`）
    - 変更内容: `SkDiscretePathEffect` API の `delete` 受け口を不透明型ポインタへ置換し、`seedAssist` を `uint32_t` へ正規化
    - `skia/binding/sk_document.h` + `skia/binding/sk_document.cpp`（8/8 関数 `done`）
    - 変更内容: `SkDocument` API の `void*` を不透明型ポインタへ置換し、`beginPage` の `SkCanvas`/`SkRect` ポインタを型強化
    - `skia/binding/sk_drawable.h` + `skia/binding/sk_drawable.cpp`（19/19 関数 `done`）
    - 変更内容: `SkDrawable` API の `void*` を不透明型ポインタへ置換し、`unsigned int/unsigned long` を `uint32_t/size_t` へ正規化
    - `skia/binding/sk_dynamic_memory_w_stream.h` + `skia/binding/sk_dynamic_memory_w_stream.cpp`（30/30 関数 `done`）
    - 変更内容: `SkDynamicMemoryWStream` API の `void*` を不透明型ポインタへ置換し、`unsigned int/unsigned long` を `uint8_t/uint16_t/uint32_t/size_t` へ正規化
    - `skia/binding/sk_encoder.h` + `skia/binding/sk_encoder.cpp`（2/2 関数 `done`）
    - 変更内容: `SkEncoder` API の `void*` を `reskia_encoder_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_executor.h` + `skia/binding/sk_executor.cpp`（5/5 関数 `done`）
    - 変更内容: `SkExecutor` API の `void*` を `reskia_executor_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_file_stream.h` + `skia/binding/sk_file_stream.cpp`（29/29 関数 `done`）
    - 変更内容: `SkFILEStream` API の `void*` を不透明型ポインタへ置換し、`unsigned long` を `size_t` と型付きスカラポインタへ正規化
    - `skia/binding/sk_file_w_stream.h` + `skia/binding/sk_file_w_stream.cpp`（21/21 関数 `done`）
    - 変更内容: `SkFILEWStream` API の `void*` を不透明型ポインタへ置換し、`unsigned long/unsigned int` を `size_t/uint8_t/uint16_t/uint32_t` へ正規化
    - `skia/binding/sk_flattenable.h` + `skia/binding/sk_flattenable.cpp`（11/11 関数 `done`）
    - 変更内容: `SkFlattenable` API の `void*` を不透明型ポインタへ置換し、`serialize/deserialize` の `size_t/uint8_t` シグネチャを正規化
    - `skia/binding/sk_font.h` + `skia/binding/sk_font.cpp`（47/47 関数 `done`）
    - 変更内容: `SkFont` API の `void*` を不透明型ポインタへ置換し、`unsigned long/void*` を `size_t/uint8_t/uint16_t` と型付き幾何ポインタへ正規化
    - `skia/binding/sk_font_arguments.h` + `skia/binding/sk_font_arguments.cpp`（8/8 関数 `done`）
    - 変更内容: `SkFontArguments` API の `void*` を `reskia_font_arguments_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_font_metrics.h` + `skia/binding/sk_font_metrics.cpp`（6/6 関数 `done`）
    - 変更内容: `SkFontMetrics` API の `void*` を `reskia_font_metrics_t*` 不透明型ポインタへ置換し、`SkScalar*` out 引数を `float*` へ正規化
    - `skia/binding/sk_font_mgr.h` + `skia/binding/sk_font_mgr.cpp`（15/15 関数 `done`）
    - 変更内容: `SkFontMgr` API の `void*` を不透明型ポインタへ置換し、`SkString` / `SkFontStyle` / `SkFontArguments` 引数ポインタを型強化
    - `skia/binding/sk_font_style.h` + `skia/binding/sk_font_style.cpp`（4/4 関数 `done`）
    - 変更内容: `SkFontStyle` API の `void*` を `reskia_font_style_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_font_style_set.h` + `skia/binding/sk_font_style_set.cpp`（8/8 関数 `done`）
    - 変更内容: `SkFontStyleSet` API の `void*` を不透明型ポインタへ置換し、`SkFontStyle` / `SkString` 引数ポインタを型強化
    - `skia/binding/sk_gif_decoder.h` + `skia/binding/sk_gif_decoder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkGifDecoder` API の `void*` を `uint8_t*` / 不透明型ポインタへ置換し、`SkCodec::Result` / `SkCodecs::DecodeContext` 引数を型強化
    - `skia/binding/sk_gradient_shader.h` + `skia/binding/sk_gradient_shader.cpp`（15/15 関数 `done`）
    - 変更内容: `SkGradientShader` API の `void*` を `reskia_*` 不透明型と `float*`/`uint32_t` に正規化し、点列・行列・色配列・補間引数を型強化
    - `skia/binding/sk_graphics.h` + `skia/binding/sk_graphics.cpp`（10/10 関数 `done`）
    - 変更内容: `SkGraphics` API の `void*` を不透明型ポインタへ置換し、キャッシュサイズ関連の `unsigned long` を `size_t` に正規化
    - `skia/binding/sk_high_contrast_config.h` + `skia/binding/sk_high_contrast_config.cpp`（4/4 関数 `done`）
    - 変更内容: `SkHighContrastConfig` API の `void*` を `reskia_high_contrast_config_t*` 不透明型ポインタへ置換
    - `skia/binding/sk_i_rect.h` + `skia/binding/sk_i_rect.cpp`（41/41 関数 `done`）
    - 変更内容: `SkIRect` API の `void*` を `reskia_i_rect_t*` 不透明型ポインタへ置換し、`SkIPoint` / `SkISize` / `SkRect` 引数ポインタを型強化
    - `skia/binding/sk_i_size.h` + `skia/binding/sk_i_size.cpp`（9/9 関数 `done`）
    - 変更内容: `SkISize` API の `void*` を `reskia_i_size_t*` 不透明型ポインタへ置換し、`int64_t` 戻り値を明示化
    - `skia/binding/sk_icc.h` + `skia/binding/sk_icc.cpp`（4/4 関数 `done`）
    - 変更内容: `SkICC` API の `void*` を `reskia_transfer_function_t*` / `reskia_matrix3x3_t*` / `reskia_icc_profile_t*` と `uint8_t*` バッファへ置換
    - `skia/binding/sk_ico_decoder.h` + `skia/binding/sk_ico_decoder.cpp`（3/3 関数 `done`）
    - 変更内容: ファイル名 typo（`sk_ico_cecoder`）を `sk_ico_decoder` に修正し、`SkIcoDecoder` API の `void*` を `uint8_t*` / 不透明型ポインタへ置換
    - `skia/binding/sk_image.h` + `skia/binding/sk_image.cpp`（48/48 関数 `done`）
    - 変更内容: `SkImage` API の `void*` を不透明型ポインタへ置換し、`unsigned long` を `size_t`、`sampling/matrix/pixmap/context` 引数を型強化
    - `skia/binding/sk_image_filter.h` + `skia/binding/sk_image_filter.cpp`（20/20 関数 `done`）
    - 変更内容: `SkImageFilter` API の `void*` を不透明型ポインタへ置換し、`matrix/rect/color-filter/procs` 引数と `size_t` シグネチャを正規化
    - `skia/binding/sk_image_filters.h` + `skia/binding/sk_image_filters.cpp`（37/37 関数 `done`）
    - 変更内容: `SkImageFilters` API の `void*` を不透明型ポインタへ置換し、`crop/rect/sampling/runtime-shader` 引数を型強化
    - `skia/binding/sk_image_generator.h` + `skia/binding/sk_image_generator.cpp`（11/11 関数 `done`）
    - 変更内容: `SkImageGenerator` API の `void*` を不透明型ポインタへ置換し、`image/pixmap/YUVA/context` 引数と `uint32_t/size_t` シグネチャを正規化
    - `skia/binding/sk_image_info.h` + `skia/binding/sk_image_info.cpp`（37/37 関数 `done`）
    - 変更内容: `SkImageInfo` API の `void*` を不透明型ポインタへ置換し、`SkColorInfo`/`SkColorSpace` 引数と `size_t/uint64_t` シグネチャを正規化
    - `skia/binding/sk_images.h` + `skia/binding/sk_images.cpp`（7/7 関数 `done`）
    - 変更内容: `SkImages` API の `void*` を不透明型ポインタへ置換し、`SkBitmap`/`SkPixmap`/`SkImageInfo`/`SkIRect`/`SkMatrix`/`SkPaint` 引数と `size_t` シグネチャを正規化
    - `skia/binding/sk_jpeg_decoder.h` + `skia/binding/sk_jpeg_decoder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkJpegDecoder` API の `void*` を `uint8_t*` / `reskia_codec_result_t*` / `reskia_codecs_decode_context_t*` へ置換し、入力サイズを `size_t` へ正規化
    - `skia/binding/sk_jpeg_encoder.h` + `skia/binding/sk_jpeg_encoder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkJpegEncoder` API の suffix 関数で `SkYUVAPixmaps`/`SkColorSpace`/`GrDirectContext`/`SkImage`/`SkJpegEncoder::Options` 引数を不透明型ポインタへ正規化
    - `skia/binding/sk_line_2d_path_effect.h` + `skia/binding/sk_line_2d_path_effect.cpp`（2/2 関数 `done`）
    - 変更内容: `SkLine2DPathEffect` API の `void*` を `reskia_line_2d_path_effect_t*` / `reskia_matrix_t*` へ置換
    - `skia/binding/sk_m_44.h` + `skia/binding/sk_m_44.cpp`（41/41 関数 `done`）
    - 変更内容: `SkM44` API の `void*` を `reskia_m_44_t*`/`reskia_matrix_t*`/`reskia_v3_t*`/`reskia_v4_t*`/`reskia_rect_t*` へ置換し、列・行メジャ配列を `float*` へ正規化
    - `skia/binding/sk_malloc_pixel_ref.h` + `skia/binding/sk_malloc_pixel_ref.cpp`（2/2 関数 `done`）
    - 変更内容: `SkMallocPixelRef` API の `void*` を `reskia_image_info_t*` へ置換し、`rowBytes` を `size_t` へ正規化
    - `skia/binding/sk_mask.h` + `skia/binding/sk_mask.cpp`（15/15 関数 `done`）
    - 変更内容: `SkMask` API の `void*` を `reskia_mask_t*`/`reskia_i_rect_t*` と型付き画素ポインタ（`uint8_t*`/`uint16_t*`/`uint32_t*`）へ置換し、`size_t`/`uint8_t` シグネチャを正規化
    - `skia/binding/sk_mask_builder.h` + `skia/binding/sk_mask_builder.cpp`（15/15 関数 `done`）
    - 変更内容: `SkMaskBuilder` API の `void*` を `reskia_mask_builder_t*`/`reskia_mask_t*`/`reskia_i_rect_t*` と型付き画素ポインタへ置換し、`AllocImage` を `size_t` + `uint8_t*` へ正規化
    - `skia/binding/sk_mask_filter.h` + `skia/binding/sk_mask_filter.cpp`（12/12 関数 `done`）
    - 変更内容: `SkMaskFilter` API の `void*` を `reskia_mask_filter_t*`/`reskia_rect_t*`/`reskia_write_buffer_t*`/`reskia_(de)serial_procs_t*` へ置換し、`serialize` の `size_t` シグネチャを正規化
    - `skia/binding/sk_matrix.h` + `skia/binding/sk_matrix.cpp`（102/102 関数 `done`）
    - 変更内容: `SkMatrix` API の `void*` を `reskia_matrix_t*`/`reskia_point_t*`/`reskia_point3_t*`/`reskia_rect_t*`/`reskia_vector_t*`/`reskia_size_t*`/`reskia_rsxform_t*` へ置換し、`SkScalar[]` 入出力を `float*`/`const float*` へ正規化
    - `skia/binding/sk_memory_stream.h` + `skia/binding/sk_memory_stream.cpp`（36/36 関数 `done`）
    - 変更内容: `SkMemoryStream` API の `void*` を `reskia_memory_stream_t*`/`reskia_data_t*` へ置換し、バッファ入出力を `uint8_t*`、スカラ out 引数を `float*`/`size_t*` へ正規化
    - `skia/binding/sk_mesh.h` + `skia/binding/sk_mesh.cpp`（19/19 関数 `done`）
    - 変更内容: `SkMesh` API の `void*` を `reskia_mesh_t*`/`reskia_mesh_specification_t*`/`reskia_mesh_(vertex|index)_buffer_t*`/`reskia_data_t*`/`reskia_rect_t*` へ置換し、`size_t` シグネチャを正規化
    - `skia/binding/sk_mesh_specification.h` + `skia/binding/sk_mesh_specification.cpp`（12/12 関数 `done`）
    - 変更内容: `SkMeshSpecification` API の `void*` を `reskia_mesh_specification_t*`/`reskia_string_view_t*`/`reskia_runtime_effect_(uniform|child)_t*`/`reskia_color_space_sp_t*` へ置換し、`size_t` シグネチャを正規化
    - `skia/binding/sk_meshes.h` + `skia/binding/sk_meshes.cpp`（4/4 関数 `done`）
    - 変更内容: `SkMeshes` API の `void*` を `reskia_mesh_(index|vertex)_buffer_sp_t*` へ置換し、バイト列入力を `const uint8_t* + size_t` へ正規化
    - `skia/binding/sk_op_builder.h` + `skia/binding/sk_op_builder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkOpBuilder` API の `void*` を `reskia_op_builder_t*`/`reskia_path_t*` へ置換し、path 入出力シグネチャを型強化
    - `skia/binding/sk_overdraw_canvas.h` + `skia/binding/sk_overdraw_canvas.cpp`（25/25 関数 `done`）
    - 変更内容: `SkOverdrawCanvas` API の `void*` を `reskia_overdraw_canvas_t*` と描画関連不透明型（paint/path/image/rect/matrix など）へ置換し、`onDrawPoints` 件数を `size_t` へ正規化
    - `skia/binding/sk_paint.h` + `skia/binding/sk_paint.cpp`（57/57 関数 `done`）
    - 変更内容: `SkPaint` API の `void*` を `reskia_paint_t*` と shader/filter/blender/path-effect 系不透明型へ置換し、色・アルファ・bounds rect シグネチャを正規化
  - チェックリスト規模:
    - 対象ヘッダ: 134
    - 対象関数: 2431
  - 進捗:
    - `phase2-type-hardening-status.csv`: 1297 / 2431 `done`
  - enum/int 露出チェックリスト規模:
    - 対象関数: 263
    - `enum_int_return`: 71
    - `enum_int_param`: 196
  - カテゴリ内訳（関数宣言ベース）:
    - `void_ptr`: 2365
    - `suffix`: 341
    - `primitive`: 366
    - `semantic` (`SkColor` / `SkPMColor` / `SkTypefaceID` / `SkFontTableTag`): 64
  - 検討結果: `unsigned long` / `unsigned int` はクロスプラットフォーム ABI 差分リスクがあるため、Step3に含めて正規化する。
  - 集計（宣言ベース）:
    - `unsigned long`: 250行
    - `unsigned int`: 120行
  - 集計（ファイルベース）:
    - `unsigned long` を含むヘッダ: 64件
    - `unsigned int` を含むヘッダ: 36件
    - いずれかを含むヘッダ: 75件
- [ ] 4. IN/OUT引数規約の統一
  - 設計方針を追加（`*_in/*_out` 廃止、`reskia_status_t + typed out pointer` へ移行）
  - 優先対象3関数（`SkFontMgr_createStyleSet`, `SkFontMgr_matchFamily`, `SkExecutor_add`）から着手
- [ ] 5. フェーズ2検証

## 完了条件

- RefCounted型で `delete static_cast<...>` がゼロ。
- 解放規約コメントが全公開ヘッダに記載済み。
- `checklists/binding-status.csv` の Phase 2 対象が `done`。
