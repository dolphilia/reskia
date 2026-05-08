# 05 Phase 2 Batch D: paint C API safety

作業開始日時: 2026-05-08 15:45:24 JST

## 目的

Phase 2 の次バッチとして、draw 系 API の主要入力である `SkPaint` の C API 境界を fail-safe に寄せる。`SkCanvas` / `SkPath` の安全化後、paint まわりの NULL dereference と borrowed/ref handle 規約を先に固め、draw 入力の安定性を上げる。

対象:

- `skia/capi/sk_paint.h`
- `skia/capi/sk_paint.cpp`

## 実装変更

`sk_paint.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric / enum | `0` |
| `bool` query | 原則 `false` |
| `nothingToDraw` | `true` |
| default 指定 query | caller-provided default |

主な対象:

- construction / copy: `SkPaint_newWithColor4fAndColorSpace`, `SkPaint_newCopy`
- scalar/color query and mutation: anti alias、dither、style、color、alpha、stroke
- effect ownership: shader、color filter、blend mode、blender、path effect、mask filter、image filter
- bounds helpers: `computeFastBounds` / `computeFastStrokeBounds` / `doComputeFastBounds`

## pointer / handle 規約

`sk_paint.h` に borrowed pointer と retained handle のコメントを補強した。

- `get*` 系の pointer は paint が所有する borrowed pointer。caller は delete しない。
- `ref*` 系は retained handle を返す。`paint == NULL` の場合は `0`。
- `set*` 系の handle に `0` を渡すと Skia 側の `sk_sp` は null になり、effect を clear する。
- `SkColor4f *color` は非 NULL。`SkColorSpace *colorSpace` は NULL 許可。
- fast bounds helper の `orig` / `storage` は非 NULL。

## smoke test

`test_paint_invalid_input_smoke` を追加し、`ctest` に `c_skia_paint_invalid_input_smoke` として登録した。

確認内容:

- NULL paint の copy/query/mutation がクラッシュせず fail-safe 値を返す。
- NULL paint の effect ref/get/set が `0` / `NULL` / no-op になる。
- `SkPaint_getBlendMode_or(NULL, default)` が caller default を返す。
- `SkPaint_nothingToDraw(NULL)` が true を返す。
- valid paint に対する NULL color/bounds 入力が no-op / `NULL` になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_paint_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_paint_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_paint.h`
- `skia/capi/sk_paint.cpp`

## 次バッチ候補

Phase 2 の次候補:

- draw 系で参照頻度が高い `SkRect` / `SkRRect` / `SkImageInfo`
- `SkData` / stream 系
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
