# 02 Phase 1: Registry Safety (`skia/static`)

## ゴール

- `static` レジストリを「壊れない状態」にする。
- 所有権破壊・無効キー黙殺・データ競合を先に止血する。

## 対象

- `skia/static/*.cpp`
- `skia/static/*-internal.h`（必要に応じてAPI分割）

## 作業ステップ

1. レジストリ共通ユーティリティ導入
- 追加: `skia/static/handle_table.hpp`（仮）
- 機能:
  - `find` ベース取得（`operator[]` 禁止）
  - `create/get_ptr/erase/contains`
  - `std::mutex` で排他
  - エラー時の戻り規約（`nullptr` or `false`）

2. `get_entity` の分離
- 既存 `get_entity` を以下に再編:
  - `borrow_entity`（非破壊）
  - `take_entity`（移譲が必要な型のみ）
- `sk_sp` / `unique_ptr` 型は既定で `borrow_entity` を使うよう移行。

3. 無効キー処理の統一
- `get_ptr/delete/set` すべて `find` で存在確認。
- 無効キー時:
  - 何もしない/`false` を返す/ログを返す方針を統一。

4. 世代付きハンドル導入（第一段）
- 既存 `int` を維持しつつ内部で generation を保持。
- stale handle 検出時の失敗経路を整備。

5. フェーズ1検証

```bash
rg -n "return std::move\\(static_.*\\[key\\]\\)" skia/static
rg -n "static_.*\\[key\\]" skia/static/*.cpp
rg -n "mutex|shared_mutex" skia/static
cmake --build skia/cmake-build-local -j 8
```

## 進捗（2026-02-14）

- [x] 1. レジストリ共通ユーティリティ導入
  - 追加: `skia/static/handle_table.hpp`
  - 実装済み機能: `create` / `get_ptr` / `erase` / `contains` / `set`（strict） / `set_or_insert`（移行用）
  - 実装詳細:
    - `std::mutex` による排他を導入
    - 内部実装を `find` ベースに統一（`operator[]` 不使用）
    - エラー時は `get_ptr -> nullptr`, `erase/set -> false` を返却
  - 適用開始: `skia/static/static_sk_surface.cpp`
  - `handle_table` ロールアウト管理:
    - 進捗チェックリスト: `docs/plans/c-binding-remediation/checklists/static-handle-table-status.csv`
    - 第1バッチ（10件）完了: `static_sk_android_codec`, `static_sk_b_box_hierarchy`, `static_sk_blender`, `static_sk_canvas`, `static_sk_capabilities`, `static_sk_codec`, `static_sk_color_filter`, `static_sk_color_space`, `static_sk_color_table`, `static_sk_contour_measure`
    - 第2バッチ（10件）完了: `static_sk_blend_mode`, `static_sk_codecs_decoder`, `static_sk_color_4f`, `static_sk_color_info`, `static_sk_color_matrix`, `static_sk_cubic_resampler`, `static_sk_data`, `static_sk_data_table`, `static_sk_document`, `static_sk_drawable`
    - 第3バッチ（10件）完了: `static_sk_drawable_gpu_draw_handler`, `static_sk_encoder`, `static_sk_encoder_frame`, `static_sk_executor`, `static_sk_file_stream`, `static_sk_flattenable`, `static_sk_flattenable_factory`, `static_sk_font`, `static_sk_font_arguments`, `static_sk_font_arguments_palette`
    - 第4バッチ（10件）完了: `static_sk_font_arguments_variation_position`, `static_sk_font_mgr`, `static_sk_font_style`, `static_sk_font_style_set`, `static_sk_i_point`, `static_sk_i_rect`, `static_sk_i_size`, `static_sk_id_change_listener`, `static_sk_image`, `static_sk_image_filter`
    - 第5バッチ（10件）反映: `static_sk_image_generator`, `static_sk_image_info`, `static_sk_image_required_properties`, `static_sk_m_44`, `static_sk_mask`, `static_sk_mask_builder`, `static_sk_mask_filter`, `static_sk_matrix`, `static_sk_memory_stream` を `handle_table` 化。`static_sk_image_read_pixels_callback` は実装/API 未定義（コメントアウトのみ）のため `na`。
    - 第6バッチ（10件）完了: `static_sk_mesh_child_ptr`, `static_sk_mesh_index_buffer`, `static_sk_mesh_result`, `static_sk_mesh_specification`, `static_sk_mesh_specification_attribute`, `static_sk_mesh_specification_result`, `static_sk_mesh_vertex_buffer`, `static_sk_paint`, `static_sk_path`, `static_sk_path_effect`
    - 第7バッチ（10件）完了: `static_sk_picture`, `static_sk_pixel_ref`, `static_sk_pixmap`, `static_sk_point`, `static_sk_point_3`, `static_sk_point_two`, `static_sk_r_rect`, `static_sk_rect`, `static_sk_rsx_form`, `static_sk_runtime_effect`
    - 第8バッチ（10件）完了: `static_sk_runtime_effect_builder_builder_child`, `static_sk_runtime_effect_builder_builder_uniform`, `static_sk_runtime_effect_child`, `static_sk_runtime_effect_child_ptr`, `static_sk_runtime_effect_result`, `static_sk_runtime_effect_traced_shader`, `static_sk_runtime_effect_uniform`, `static_sk_sampling_options`, `static_sk_shader`, `static_sk_size_t`
    - 第9バッチ（10件）完了: `static_sk_stream`, `static_sk_stream_asset`, `static_sk_stream_memory`, `static_sk_stream_rewindable`, `static_sk_stream_seekable`, `static_sk_string`, `static_sk_stroke_rec`, `static_sk_surface_props`, `static_sk_text_blob`, `static_sk_typeface`
    - 第10バッチ（10件）完了: `static_sk_v2`, `static_sk_v3`, `static_sk_v4`, `static_sk_vertices`, `static_sk_yuva_info`, `static_sk_yuva_pixmap_info`, `static_sk_yuva_pixmaps`, `static_std_chrono_milliseconds`, `static_std_function_void_void`, `static_std_string_view`
    - 第11バッチ（6件）完了: `static_std_tuple_int_int`, `static_std_tuple_int_sk_yuva_pixmap_info_data_type`, `static_std_tuple_sk_image_sk_codec_result`, `static_std_vector_int_ptr`, `static_std_vector_sk_codec_frame_info`, `static_std_vector_sk_scalar`
    - 補足: `static_sk_color.cpp` は実装本体がコメントアウトのみのため `na` 扱い。
- [x] 2. `get_entity` の分離
  - `sk_sp` / `unique_ptr` 管理の `static_*_get_entity` を `borrow_entity` / `take_entity` に分離。
  - `sk_sp` 系は `get_entity -> borrow_entity`（非破壊）を既定化。
  - `unique_ptr` 系は `get_entity -> take_entity` を薄い互換ラッパとして維持し、`binding` 側の所有権移譲呼び出しを `take_entity` へ明示置換。
  - 実装反映: `skia/static/*-internal.h` と `skia/static/*.cpp`（Step2対象88ファイル）、`skia/binding/*.cpp`（`unique_ptr` 移譲呼び出し）。
- [x] 3. 無効キー処理の統一
  - `skia/static/*.cpp` の値型レジストリを含む実装で `set/get_ptr/delete` を `find` ベースへ統一。
  - 無効キー時の規約を統一:
    - `set`: 何もしない（`void` API のため no-op）
    - `get_ptr`: `nullptr` を返す
    - `delete`: 何もしない（no-op）
  - `static_sk_stream_ptr_*` も同方針で無効キー処理を追加。
  - `static_sk_surface_set` は `set_or_insert` から strict `set` へ変更し、無効キーで no-op 化。
- [x] 4. 世代付きハンドル導入（第一段）
  - `skia/static/handle_table.hpp` を世代付きハンドル方式へ更新（`int` API 互換維持）。
  - ハンドル形式:
    - 下位20bit: slot
    - 上位bit: generation（`0` は無効）
  - 実装内容:
    - `create`: free slot を再利用しつつ generation を付与した handle を返却
    - `set/get_ptr/erase/contains/take_or_default`: handle の slot/generation を検証して stale handle を reject
    - `erase`: entry 削除時に generation を進めて stale handle を無効化
  - 検証:
    - `cmake --build skia/cmake-build-local -j 8` 成功（`Built target reskia`）
- [x] 5. フェーズ1検証
  - 実施コマンド:
    - `rg -n "return std::move\\(static_.*\\[key\\]\\)" skia/static` -> 0件
    - `rg -n "static_.*\\[key\\]" skia/static/*.cpp` -> コメントアウト実装のみ（`static_sk_color.cpp`, `static_sk_image_read_pixels_callback.cpp`）
    - `rg -n "mutex|shared_mutex" skia/static` -> `handle_table.hpp` で排他実装を確認
    - `cmake --build skia/cmake-build-local -j 8` -> 成功（`Built target reskia`）
  - チェックリスト整合:
    - `checklists/static-handle-table-status.csv` は全対象が `done` または `na`
    - `checklists/static-status.csv` の `static_sk_image_read_pixels_callback.cpp` を `na` へ更新（実装/API未定義）

## 完了条件

- `skia/static` から `return std::move(static_*[key])` がゼロ。
- `skia/static/*.cpp` から `map[key]` パターンがゼロ。
- `checklists/static-status.csv` が Phase 1 対象で `done`。

## リスクと対策

- リスク: API互換破壊
- 対策: 旧関数名を thin wrapper として一時残す（内部は新実装）
