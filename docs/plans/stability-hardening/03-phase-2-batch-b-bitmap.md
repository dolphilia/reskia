# 03 Phase 2 Batch B: bitmap C API safety

作業開始日時: 2026-05-08 15:22:08 JST

## 目的

`02-phase-2-batch-a-capi-safety.md` の次バッチとして、`SkBitmap` の C API 境界を fail-safe に寄せる。`SkBitmap` は caller-owned pixel buffer を扱うため、NULL 入力だけでなく raw buffer の lifetime / mutability コメントも明示する。

対象:

- `skia/capi/sk_bitmap.h`
- `skia/capi/sk_bitmap.cpp`

## 実装変更

`sk_bitmap.cpp` に NULL ガードを追加した。

戻り規約:

| 戻り値種別 | NULL 入力時 |
| --- | --- |
| `void` | no-op |
| `bool` | `false` |
| pointer | `NULL` |
| handle (`sk_*_t`) | `0` |
| numeric | `0` |
| empty/null query | `true` |

対象例:

- allocation: `allocPixels*`, `tryAllocPixels*`
- getter: `width`, `height`, `rowBytes`, `info`, `bounds`, `getPixels`, `getAddr*`
- pixel IO: `installPixels*`, `readPixels*`, `writePixels*`, `peekPixels`
- mutation: `erase*`, `reset`, `setInfo`, `setPixels`, `setImmutable`, `swap`
- factory/helper: `new_copy`, `asImage`, `makeShader*`, `ComputeIsOpaque`

## raw buffer 規約

`sk_bitmap.h` に raw pixel buffer の lifetime / mutability コメントを追加した。

- `SkBitmap_getPixels` / `SkBitmap_getAddr*`: borrowed mutable pixel pointer。bitmap の pixel storage が変わるまで有効で、caller は解放しない。
- `SkBitmap_installPixels`: caller-owned mutable backing store。bitmap storage が変わるか reset/delete されるまで有効である必要がある。
- `SkBitmap_installPixels_withReleaseProc`: backing store を bitmap に渡し、必要なら `releaseProc` で解放する。`releaseProc == NULL` の場合は caller 側で lifetime を維持する。
- `SkBitmap_readPixels`: caller-owned mutable output buffer。`dstInfo` / `dstRowBytes` に対して十分なサイズが必要で、bitmap は保持しない。
- `SkBitmap_setPixels`: caller-owned mutable backing store。bitmap storage が変わるか reset/delete されるまで有効である必要がある。

## smoke test

`test_bitmap_invalid_input_smoke` を追加し、`ctest` に `c_skia_bitmap_invalid_input_smoke` として登録した。

確認内容:

- `SkBitmap_new_copy(nullptr) == nullptr`
- `SkBitmap_width(nullptr) == 0`
- `SkBitmap_height(nullptr) == 0`
- `SkBitmap_getPixels(nullptr) == nullptr`
- `SkBitmap_empty(nullptr) == true`
- `SkBitmap_isNull(nullptr) == true`
- `SkBitmap_peekPixels(nullptr, nullptr) == false`
- `SkBitmap_readPixels(nullptr, nullptr, nullptr, 0, 0, 0) == false`
- `SkBitmap_writePixels(nullptr, nullptr) == false`
- `SkBitmap_ComputeIsOpaque(nullptr) == false`
- mutation API の NULL bitmap no-op

## 検証

実施コマンド:

```bash
cmake --build skia/cmake-build-stability-prebuilt -j 8
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target test_bitmap_invalid_input_smoke -j 8
ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_(canvas|image_surface|bitmap)_invalid_input_smoke' --output-on-failure
```

結果:

- prebuilt Debug build 成功。
- `c_skia_canvas_invalid_input_smoke` 成功。
- `c_skia_image_surface_invalid_input_smoke` 成功。
- `c_skia_bitmap_invalid_input_smoke` 成功。

## チェックリスト更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` を更新した。

`done` に変更:

- `skia/capi/sk_bitmap.h`
- `skia/capi/sk_bitmap.cpp`

## 次バッチ候補

Phase 2 の次候補:

- `SkPath`
- `SkPaint`
- `SkData` / stream 系
- `SkFont` / `SkTypeface`
