# 22 Phase 2 Batch U: mask C API safety

作業開始日時: 2026-05-09 13:58:43 JST

## 目的

Phase 2 の次バッチとして、`SkMask` / `SkMaskBuilder` 周辺を fail-safe に寄せる。mask API は caller-owned image buffer、borrowed bounds、format-specific address accessor を扱い、debug build では format・bounds・image の不一致が assert になるため、C ABI 境界で NULL と不整合入力を先に落とす。

対象:

- `skia/capi/sk_mask.h`
- `skia/capi/sk_mask.cpp`
- `skia/capi/sk_mask_builder.h`
- `skia/capi/sk_mask_builder.cpp`

## 実装変更

各 C API に NULL ガードと format/bounds/image チェックを追加した。

戻り規約:

| 戻り値種別 | NULL / invalid 入力時 |
| --- | --- |
| pointer / borrowed image / address | `NULL` |
| handle (`sk_mask_t`, `sk_mask_builder_t`) | `0` |
| bounds handle | empty rect handle |
| `size_t` / rowBytes | `0` |
| format | `-1` |
| `isEmpty(NULL)` | `true` |
| delete / free | no-op |

`getAddr*` 系は Skia 側の assert に入る前に以下を検査する。

- `mask` / `maskBuilder` が非 NULL。
- `fImage` が非 NULL。
- `(x, y)` が `fBounds` 内。
- accessor が要求する `fFormat` と一致する。
- generic `getAddr` は `kBW_Format` を受け付けない。

## raw buffer / borrowed pointer 規約

ヘッダコメントを補強した。

- `SkMask_new`: `img` は borrowed。`bounds` は非 NULL、`format` は valid。invalid 入力では `0`。
- `SkMask_fImage`: borrowed pointer。caller は解放しない。NULL 入力では `NULL`。
- `SkMask_getAddr*`: borrowed address。format/bounds/image 不一致や NULL 入力では `NULL`。
- `SkMaskBuilder_newWithImageBoundsRowBytesFormat`: `img` は borrowed mutable。`bounds` は非 NULL、`format` は valid。invalid 入力では `NULL`。
- `SkMaskBuilder_image` / `bounds`: borrowed mutable。NULL 入力では `NULL`。
- `SkMaskBuilder_AllocImage`: `bytes > 0`。`0` や割当不能では `NULL`。
- `SkMaskBuilder_FreeImage`: NULL 入力では no-op。
- `SkMaskBuilder_PrepareDestination`: `src` は非 NULL。NULL 入力では `0`。

## smoke test

`test_mask_invalid_input_smoke` を追加し、`ctest` に `c_skia_mask_invalid_input_smoke` として登録した。

確認内容:

- NULL `SkMask` query/address がクラッシュせず fail-safe 値を返す。
- invalid constructor 入力が handle `0` / `NULL` を返す。
- valid A8 mask / builder で address を取得できる。
- format mismatch と範囲外 address が `NULL` を返す。
- LCD16 / ARGB32 / BW の format-specific accessor が valid 入力で動く。
- `SkMaskBuilder_AllocImage(0)` と `PrepareDestination(NULL)` が `NULL` / `0` を返す。
- valid `PrepareDestination` が builder handle を返す。

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_mask_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_mask_invalid_input_smoke' --output-on-failure
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap|path|paint|rect_rrect|image_info|data|data_table|color_table|mask_filter|mask|stream|wstream|stream_derived|color_info_space|path_effect|color_filter|color_values|color_matrix_filter|color_core|contour_path_measure)_invalid_input_smoke' --output-on-failure
git diff --check
```

結果:

- prebuilt Debug build 成功。
- test configure 成功。
- `test_mask_invalid_input_smoke` build 成功。
- `c_skia_mask_invalid_input_smoke` 成功。
- C API invalid-input smoke 22 本成功。
- `git diff --check` は whitespace error なし。既存どおり `capi-status.csv` の CRLF が次回 Git touch で LF になる警告のみ。

## チェックリスト更新

`docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_mask.h`
- `skia/capi/sk_mask.cpp`
- `skia/capi/sk_mask_builder.h`
- `skia/capi/sk_mask_builder.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkFont` / `SkTypeface`
- `SkDrawable` / flattenable 周辺
- `SkMatrix` / geometry value helpers
