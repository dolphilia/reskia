# 06 Phase 2 Batch E: rect / rrect C API safety

作業開始日時: 2026-05-08 16:17:44 JST

## 目的

Phase 2 の次バッチとして、draw 系 API の基本入力である `SkRect` / `SkRRect` の C API 境界を fail-safe に寄せる。`SkCanvas` / `SkPath` / `SkPaint` の NULL 規約に続き、形状入力側の NULL dereference を減らす。

対象:

- `skia/capi/sk_rect.h`
- `skia/capi/sk_rect.cpp`
- `skia/capi/sk_r_rect.h`
- `skia/capi/sk_r_rect.cpp`

## 実装変更

`sk_rect.cpp` / `sk_r_rect.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric / enum | `0` |
| `bool` query | 原則 `false` |
| empty query | `true` |

主な対象:

- `SkRect`: scalar accessor、center/bounds、set/offset/inset/outset/intersect/join/contains/round/sort/dump/static factory
- `SkRRect`: copy/type/query、set rect/oval/radii、borrowed bounds、inset/outset/offset/contains/validity/transform/dump/static factory

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkRect_toQuad`: `quad` は caller-owned `SkPoint[4]` output。
- `SkRect_setBounds*`: `pts == NULL` は `count == 0` の場合だけ許可。
- `SkRect_round*`: `dst` は caller-owned output。
- `SkRect_asScalars`: borrowed scalar storage。rect が生存し変更されない間だけ有効。
- `SkRRect_setRectRadii`: `radii` は caller-owned `SkVector[4]` input。
- `SkRRect_rect` / `SkRRect_getBounds`: borrowed pointer。rrect が生存し変更されない間だけ有効。
- `SkRRect_writeToMemory`: `buffer == NULL` は `SkRRect::kSizeInMemory` の問い合わせとして C API 側で吸収する。
- `SkRRect_readFromMemory`: `buffer == NULL` は `length == 0` の場合だけ許可。

## smoke test

`test_rect_rrect_invalid_input_smoke` を追加し、`ctest` に `c_skia_rect_rrect_invalid_input_smoke` として登録した。

確認内容:

- NULL rect / rrect の query/mutation/static factory がクラッシュせず fail-safe 値を返す。
- valid rect に対する NULL point/bounds 入力が no-op / `false` になる。
- valid rrect に対する `writeToMemory(rrect, NULL)` が byte 数問い合わせとして機能する。
- valid rect から `SkRRect_MakeRect` が作成できる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_rect_rrect_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `test_rect_rrect_invalid_input_smoke` build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。
- `c_skia_path_invalid_input_smoke` 成功。
- `c_skia_paint_invalid_input_smoke` 成功。
- `c_skia_rect_rrect_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_rect.h`
- `skia/capi/sk_rect.cpp`
- `skia/capi/sk_r_rect.h`
- `skia/capi/sk_r_rect.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkImageInfo`
- `SkData` / stream 系
- `SkFont` / `SkTypeface`
- `SkPathEffect` / path effect factory 系
