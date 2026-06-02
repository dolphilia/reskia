# 02 Code Comment Englishization Plan

作成日時: 2026-06-02 17:29:13 JST

## 目的

`docs/` 以外に残る日本語のうち、次の3領域を段階的に英語化する。

- CMake message / comment
- C API header comments
- Test / sample source

対象は、外部利用者や contributor が読む可能性のある説明・警告・エラー・public header comment である。
描画テストや Unicode 処理のための日本語テキストデータは、英語化の対象外とする。

## 現状

### CMake message / comment

初回検出対象:

- `skia/CMakeLists.txt`
- `skia/modules/svg/CMakeLists.txt`
- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/sources-core.cmake`

状態:

- 2026-06-02 に user-facing message と主要コメントの英語化を完了した。
- `rg -n '[ぁ-んァ-ン一-龯]' cmake skia/CMakeLists.txt skia/modules/*/CMakeLists.txt third_party/CMakeLists.txt` で検出なし。

### C API header comments

初回検出では、`skia/capi/*.h` の多数の public header に日本語コメントが残っている。

主な内容:

- ownership / borrowed pointer
- nullable input
- factory failure
- return value lifetime
- caller-owned output buffer

方針:

1. API 群単位で分割する。
2. 一括変換ではなく、意味を確認しながら短い英語コメントにする。
3. `docs/en/guides/c-api-safety-guidelines.md` の表現に寄せる。
4. 生成・整形スクリプトの辞書は、移行が完了するまで残す。

推奨順:

1. Core value / math headers: `sk_color*`, `sk_matrix.h`, `sk_m_44.h`, `sk_v*.h`
2. Ownership-heavy base headers: `sk_ref_cnt*`, `sk_data*`, `sk_flattenable.h`
3. Drawing resource headers: `sk_shader*`, `sk_color_filter*`, `sk_path*`
4. Font / text headers: `sk_font*`, `sk_typeface*`, `sk_text_blob.h`
5. Optional platform / feature headers: GPU, FontConfig, Android, Mac

完了済み:

| 日時 | 範囲 | ファイル | 備考 |
| --- | --- | --- | --- |
| 2026-06-02 17:29 JST | CMake message / comment | `skia/CMakeLists.txt`, `skia/modules/svg/CMakeLists.txt`, `cmake/deps/ReskiaDeps.cmake`, `cmake/reskia/sources-capi.cmake`, `cmake/reskia/sources-core.cmake` | user-facing message と主要コメントを英語化済み。 |
| 2026-06-02 17:29 JST | C API core color value headers | `skia/capi/sk_color.h`, `skia/capi/sk_color_4f.h`, `skia/capi/sk_color_info.h`, `skia/capi/sk_color_priv.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:35 JST | C API color filter / matrix headers | `skia/capi/sk_color_filter.h`, `skia/capi/sk_color_filters.h`, `skia/capi/sk_color_matrix.h`, `skia/capi/sk_color_matrix_filter.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:38 JST | C API color space / table headers | `skia/capi/sk_color_space.h`, `skia/capi/sk_color_space_primaries.h`, `skia/capi/sk_color_table.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:41 JST | C API matrix / vector headers | `skia/capi/sk_matrix.h`, `skia/capi/sk_m_44.h`, `skia/capi/sk_v2.h`, `skia/capi/sk_v3.h`, `skia/capi/sk_v4.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:45 JST | C API ownership-heavy base headers | `skia/capi/sk_data.h`, `skia/capi/sk_data_table.h`, `skia/capi/sk_ref_cnt.h`, `skia/capi/sk_ref_cnt_base.h`, `skia/capi/sk_flattenable.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:48 JST | C API path effect headers | `skia/capi/sk_path_effect.h`, `skia/capi/sk_dash_path_effect.h`, `skia/capi/sk_corner_path_effect.h`, `skia/capi/sk_discrete_path_effect.h`, `skia/capi/sk_line_2d_path_effect.h`, `skia/capi/sk_path_1d_path_effect.h`, `skia/capi/sk_path_2d_path_effect.h`, `skia/capi/sk_trim_path_effect.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:51 JST | C API path / path builder / measure headers | `skia/capi/sk_path.h`, `skia/capi/sk_path_builder.h`, `skia/capi/sk_path_measure.h`, `skia/capi/sk_op_builder.h`, `skia/capi/sk_contour_measure.h`, `skia/capi/sk_contour_measure_iter.h` | 日本語コメント検出なし。 |
| 2026-06-02 17:55 JST | C API mask / mask filter headers | `skia/capi/sk_mask.h`, `skia/capi/sk_mask_builder.h`, `skia/capi/sk_mask_filter.h`, `skia/capi/sk_shader_mask_filter.h`, `skia/capi/sk_table_mask_filter.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:00 JST | C API font argument/style and platform helper headers | `skia/capi/sk_font_arguments.h`, `skia/capi/sk_font_style.h`, `skia/capi/sk_font_mgr_fontconfig.h`, `skia/capi/sk_typeface_mac.h`, `skia/capi/sk_custom_typeface.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:02 JST | C API font manager/style set/metrics headers | `skia/capi/sk_font_mgr.h`, `skia/capi/sk_font_style_set.h`, `skia/capi/sk_font_metrics.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:05 JST | C API font header | `skia/capi/sk_font.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:08 JST | C API typeface header | `skia/capi/sk_typeface.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:13 JST | C API text blob / strike ref headers | `skia/capi/sk_text_blob.h`, `skia/capi/sk_strike_ref.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:15 JST | C API file stream headers | `skia/capi/sk_file_stream.h`, `skia/capi/sk_file_w_stream.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:18 JST | C API ownership/ref-count drawing support headers | `skia/capi/sk_pixel_ref.h`, `skia/capi/sk_b_box_hierarchy.h`, `skia/capi/sk_document.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:20 JST | C API mesh / vertices headers | `skia/capi/sk_mesh.h`, `skia/capi/sk_mesh_specification.h`, `skia/capi/sk_meshes.h`, `skia/capi/sk_vertices.h` | 日本語コメント検出なし。 |
| 2026-06-02 18:26 JST | C API surface headers | `skia/capi/sk_surface.h`, `skia/capi/sk_surface_props.h`, `skia/capi/sk_surfaces.h` | 日本語コメント検出なし。 |
| 2026-06-02 19:37 JST | C API picture / drawable headers | `skia/capi/sk_picture.h`, `skia/capi/sk_picture_recorder.h`, `skia/capi/sk_drawable.h` | 日本語コメント検出なし。 |
| 2026-06-02 19:40 JST | C API utility image/math headers | `skia/capi/sk_cubic_resampler.h`, `skia/capi/sk_cubic_map.h`, `skia/capi/sk_encoded_origin.h`, `skia/capi/sk_tiled_image_utils.h` | 日本語コメント検出なし。 |
| 2026-06-02 19:43 JST | C API platform / tracing / executor / blender headers | `skia/capi/sk_android_codec.h`, `skia/capi/sk_event_tracer.h`, `skia/capi/sk_executor.h`, `skia/capi/sk_blender.h` | 日本語コメント検出なし。 |
| 2026-06-02 19:46 JST | C API remaining image / GPU / overdraw headers | `skia/capi/sk_images.h`, `skia/capi/sk_gpu_context.h`, `skia/capi/sk_overdraw_canvas.h` | `skia/capi/*.h` の日本語コメント検出なし。 |
| 2026-06-02 19:46 JST | Test / platform source explanatory comments | `skia/test/test.cpp`, `skia/src/ports/SkFontConfigInterface_direct.cpp` | 説明コメントの日本語検出なし。fontconfig の CJK フォント名データは維持し、コメントのみ英語化。 |
| 2026-06-02 19:46 JST | Paragraph / Skottie multilingual test data | `skia/modules/skparagraph/tests/SkParagraphTest.cpp`, `skia/modules/skparagraph/slides/ParagraphSlide.cpp`, `skia/modules/skparagraph/test.html`, `skia/modules/skottie/tests/Shaper.cpp` | 検出箇所は shaping / layout / glyph resolution 用の多言語入力データとして維持。 |

### Test / sample source

初回検出対象:

- `skia/test/test.cpp`
- `skia/src/ports/SkFontConfigInterface_direct.cpp`
- `skia/modules/skparagraph/tests/SkParagraphTest.cpp`
- `skia/modules/skparagraph/slides/ParagraphSlide.cpp`
- `skia/modules/skparagraph/test.html`
- `skia/modules/skottie/tests/Shaper.cpp`

方針:

1. 日本語文字列が text rendering の入力データなら維持する。
2. テスト意図を説明するコメントやログだけを英語化する。
3. HTML sample は表示確認用の多言語文面を含む可能性があるため、削除・翻訳前に用途を確認する。

状態:

- `skia/test/test.cpp` と `skia/src/ports/SkFontConfigInterface_direct.cpp` の説明コメントは英語化済み。
- `skia/modules/skparagraph/*` と `skia/modules/skottie/tests/Shaper.cpp` に残る日本語・CJK 文字は、text rendering / shaping / glyph resolution の入力データとして維持する。

## 作業単位

各サイクルで次を守る。

1. 対象ファイルを `rg` で限定する。
2. コメントや message の意味を確認する。
3. 英語化後、同じ対象範囲で日本語検出が残っていないか確認する。
4. `git diff --check` を実行する。
5. CMake または C/C++ に触れた場合は prebuilt configure/build を実行する。

## 完了条件

- CMake message / comment: 検出なし。
- C API header comments: public header comment の日本語検出なし。ただし API 名や外部仕様由来の非英語語句は個別判断。
- Test / sample source: 説明コメント・ログの日本語検出なし。テスト入力として必要な日本語文字列は残してよい。
