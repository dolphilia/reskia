# 65 Phase 2 Batch BL: mesh C API safety

開始時刻: 2026-05-10 13:18:59 JST

## 目的

`64-phase-2-batch-bk-mesh-specification.md` の「次バッチ候補」から、`SkMesh` / `SkMeshes` の buffer / bounds / handle `0` 規約を確認する。`SkMesh` は NULL mesh getter と NULL bounds factory input を直接 dereference し、`SkMeshes` は raw data / copy pointer の NULL 入力を受け得るため、既存 ABI の範囲で sentinel を固定する。

## 変更内容

- `skia/capi/sk_mesh.cpp`
  - NULL `mesh` getter を `0` / `NULL` / `false` / `-1` sentinel にした。
  - borrowed pointer を返す `spec` / `vertexBuffer` / `indexBuffer` / `uniforms` は NULL `mesh` で `NULL` を返すようにした。
  - `SkMesh_Make` / `SkMesh_MakeIndexed` は NULL `bounds` で result handle `0` を返すようにした。
- `skia/capi/sk_mesh.h`
  - NULL 入力時の sentinel、borrowed pointer、`bounds` 必須規約を明記した。
- `skia/capi/sk_meshes.cpp`
  - `size > 0` で NULL `data` の buffer factory は handle `0` を返すようにした。
  - `CopyIndexBuffer` / `CopyVertexBuffer` は NULL pointer で handle `0` を返すようにした。
- `skia/capi/sk_meshes.h`
  - raw data と copy pointer の invalid input 規約を明記した。
- `skia/test/test_mesh_invalid_input_smoke.cpp`
  - NULL mesh getter、NULL bounds factory、NULL raw data / copy pointer の sentinel smoke を追加した。
- `cmake/reskia/tests.cmake`
  - `c_skia_mesh_invalid_input_smoke` を追加した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_mesh.*` / `sk_meshes.*` の P2 記録を Batch BL に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_mesh_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_mesh_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|mesh|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_mesh_invalid_input_smoke`: build 成功。
- `c_skia_mesh_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 60/60 passed。
- `git diff --check`: exit 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkFileStream` / `SkFileWStream` の path / stream 状態規約を確認する。
