# 35 Phase 2 Batch AH: overdraw canvas C API safety

作業開始日時: 2026-05-10 00:36:39 JST

## 目的

Phase 2 の次バッチとして、`SkOverdrawCanvas` / draw callback wrapper 周辺を fail-safe に寄せる。overdraw canvas は `SkCanvas` callback surface を C ABI へ露出しており、ほぼ全 API が raw object pointer / raw array / optional pointer を受けるため、NULL 入力・必須 pointer 欠落を C ABI 境界で明示する。

対象:

- `skia/capi/sk_overdraw_canvas.h`
- `skia/capi/sk_overdraw_canvas.cpp`

## 実装変更

各 callback wrapper に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| `SkOverdrawCanvas*` | `NULL` |
| draw callback / delete | no-op |

`SkOverdrawCanvas_new` は backing `SkCanvas` が NULL の場合に `NULL` を返す。各 `onDraw*` wrapper は overdraw canvas 本体または必須入力がない場合に upstream を呼ばず no-op にする。

## pointer / raw array 規約

ヘッダコメントを補強した。

- scalar draw callbacks: 対象 geometry / paint は非 NULL。invalid 入力では no-op。
- `onDrawPatch`: `point1[12]` / paint は非 NULL。colors / tex coords は NULL 許可。
- `onDrawPoints`: `size > 0` では point array は非 NULL。
- image callbacks: image と sampling options など参照型引数は非 NULL。paint は pointer 型のまま NULL 許可。
- `onDrawAtlas2`: `v > 0` では transform / source rect arrays は非 NULL。color / cull rect / paint は NULL 許可。
- `onDrawDrawable`: drawable は非 NULL、matrix は NULL 許可。
- `onDrawPicture`: picture は非 NULL、matrix / paint は NULL 許可。
- `onDrawAnnotation`: rect / key は非 NULL、value は NULL 許可。
- `onDrawEdgeAAImageSet2`: `count > 0` では entry array は非 NULL。point / matrix / paint は NULL 許可。sampling options は非 NULL。

## smoke test

`test_overdraw_canvas_invalid_input_smoke` を追加し、`ctest` に `c_skia_overdraw_canvas_invalid_input_smoke` として登録した。

確認内容:

- NULL backing canvas で constructor が `NULL` を返す。
- NULL overdraw canvas と NULL callback inputs がクラッシュせず no-op になる。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_overdraw_canvas_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_overdraw_canvas_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_overdraw_canvas_invalid_input_smoke` build 成功。
- `c_skia_overdraw_canvas_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_overdraw_canvas.h`
- `skia/capi/sk_overdraw_canvas.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkReadBuffer` / `SkWriteBuffer` の flattenable factory 周辺
- `SkTextBlob` / glyph-buffer 周辺
- `SkRegion` / clipping helper 周辺
