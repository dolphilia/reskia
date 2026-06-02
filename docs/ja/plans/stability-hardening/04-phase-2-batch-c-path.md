# 04 Phase 2 Batch C: path C API safety

作業開始日時: 2026-05-08 15:30:52 JST

## 目的

Phase 2 の次バッチとして、`SkPath` の C API 境界を fail-safe に寄せる。`SkPath` は draw 系 API の入力として広く使われるため、path 自体と補助入力ポインタの NULL dereference を先に潰し、次の `SkPaint` / draw 入力整理へ進みやすくする。

対象:

- `skia/capi/sk_path.h`
- `skia/capi/sk_path.cpp`

## 実装変更

`sk_path.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| `bool` query | 原則 `false` |
| empty query | `true` |
| degenerate helper | `true` |

主な対象:

- construction / copy: `SkPath_newCopy`
- query: fill type、convex/oval/rrect/line/rect、point/verb count、bounds、generation ID、validity
- mutation: fill type、reset/rewind、reserve、move/line/quad/conic/cubic/arc/close、add rect/oval/rrect/poly/path、offset/transform
- serialization: `writeToMemory` / `serialize` / `readFromMemory`
- static factory/helper: `Make`、`Rect`、`Oval`、`RRect`、`Polygon`、degenerate 判定、`ConvertConicToQuads`

## raw buffer / C++ ABI helper 規約

`sk_path.h` に raw buffer と `std::initializer_list` helper のコメントを補強した。

- `SkPath_writeToMemory`: `buffer == NULL` は必要 byte 数の問い合わせとして許可する。非 NULL の場合、caller-owned writable buffer が十分な容量を持つ必要がある。
- `SkPath_readFromMemory`: `buffer == NULL` は `length == 0` の場合だけ許可する。
- `SkPath_addPoly` / `SkPath_Polygon`: `pts == NULL` は `count == 0` の場合だけ許可する。
- `SkPath_Make`: `point` / `i` / `v` は対応する count が 0 の場合だけ NULL を許可する。
- `SkPath_addPolyFromList` / `SkPath_PolygonFromList`: `void *` は raw point buffer ではなく `std::initializer_list<SkPoint>` への非 NULL ポインタとして扱う。

## smoke test

`test_path_invalid_input_smoke` を追加し、`ctest` に `c_skia_path_invalid_input_smoke` として登録した。

確認内容:

- NULL path の copy/query/mutation/serialization がクラッシュせず fail-safe 値を返す。
- `SkPath_interpolate` の NULL 入力が `RESKIA_STATUS_INVALID_ARGUMENT` を返す。
- NULL rect/point/poly 入力を伴う path mutation/static factory が `NULL` / `0` を返す。
- 有効 path に対する `writeToMemory(path, NULL)` は byte 数問い合わせとして機能する。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_path_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_path_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

更新:

- `skia/capi/sk_path.h`
- `skia/capi/sk_path.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkPaint`
- draw 系で参照頻度が高い `SkRect` / `SkRRect` / `SkImageInfo`
- `SkData` / stream 系
- `SkFont` / `SkTypeface`
