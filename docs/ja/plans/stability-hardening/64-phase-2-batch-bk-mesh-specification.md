# 64 Phase 2 Batch BK: mesh specification C API safety

開始時刻: 2026-05-10 13:02:56 JST

## 目的

`63-phase-2-batch-bj-font-callback-recheck.md` の「次バッチ候補」から、`SkMeshSpecification` の runtime child / uniform pointer 規約を確認する。`SkMeshSpecification` は P2 checklist 上で未着手で、NULL `spec` / `name` / factory input を直接 dereference する箇所があるため、既存 ABI の範囲で invalid input を sentinel に寄せる。

## 変更内容

- `skia/capi/sk_mesh_specification.cpp`
  - `SkMeshSpecification_delete` を NULL no-op として明示した。
  - `attributes` / `uniforms` / `children` は NULL `spec` で handle `0` を返すようにした。
  - `uniformSize` / `stride` は NULL `spec` で `0` を返すようにした。
  - `findChild` / `findUniform` / `findAttribute` / `findVarying` は NULL `spec` または NULL `name` で `NULL` を返すようにした。
  - `Make*` 系は必須 input の NULL で result handle `0` を返すようにした。
  - `MakeWithColorSpace*` の `cs` pointer は NULL 許可にし、NULL の場合は空の `sk_sp<SkColorSpace>` として渡すようにした。
- `skia/capi/sk_mesh_specification.h`
  - runtime child / uniform / attribute / varying の戻り pointer が `spec` に借用依存することを明記した。
  - NULL 入力時の sentinel と factory input 規約を明記した。
- `skia/test/test_mesh_specification_invalid_input_smoke.cpp`
  - NULL `spec` / NULL `name` / NULL factory input の no-crash sentinel を追加した。
- `cmake/reskia/tests.cmake`
  - `c_skia_mesh_specification_invalid_input_smoke` を追加した。
- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_mesh_specification.cpp` / `sk_mesh_specification.h` の P2 記録を Batch BK に更新した。

## 検証

すべて成功:

```sh
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_mesh_specification_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_mesh_specification_invalid_input_smoke' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|surface_props_surfaces|bitmap|path_builder|path|paint|rect_rrect|region|text_blob|raster_handle_allocator|ref_cnt|pixel_ref|pixmap|codec|decoder|encoder|image_generator|images|open_type_svg_decoder|image_filter|tiled_image_utils|runtime_effect|mesh_specification|shader|blender|blenders|yuva_info|yuva_pixmaps|image_info|data|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure|data_table|color_table|mask_filter|mask|matrix|m44|vector|vertices|font_style_set|font|typeface|typeface_mac|font_arguments_metrics|drawable_flattenable|picture_recorder|font_mgr|overdraw_canvas|read_write_buffer)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- configure: 成功。
- `test_mesh_specification_invalid_input_smoke`: build 成功。
- `c_skia_mesh_specification_invalid_input_smoke`: 1/1 passed。
- `skia/cmake-build-stability-prebuilt`: build 成功、`Built target reskia`。
- Phase 2 invalid-input smoke: 59/59 passed。
- `git diff --check`: exit 0。既知の `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 変換 warning のみ。

## 次バッチ候補

- `SkCanvas` raw text / glyph array 周辺の count / pointer 規約を追加で確認する。
- `SkFont` glyph bounds / widths optional output pointer の挙動を再確認する。
- `SkMesh` / `SkMeshes` の buffer / bounds / handle `0` 規約を確認する。
