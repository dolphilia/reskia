# Reskia C API Safety Guidelines

この文書は、`skia/capi`、`skia/handles`、`skia/test` を編集するときの C ABI 安全性規約をまとめます。

目的は、C API 利用者の誤入力で crash させず、所有権と lifetime を読み取れる API にすることです。

## 基本原則

1. C ABI 境界では、NULL、invalid handle、stale handle、範囲外値で crash させない。
2. Skia C++ API の意味を変えず、C API 側で入力検証と失敗値の正規化を行う。
3. 既存 ABI を一括破壊しない。必要な場合は互換 wrapper、新しい名前の API、移行フェーズを用意する。
4. 返却値の所有権と寿命は、ヘッダコメントから判断できるようにする。
5. 安全化した API には、可能な範囲で invalid path と最小 valid path の smoke を追加する。
6. 実装、ヘッダコメント、テスト、coverage / checklist の意味を揃える。

## 用語

| 用語 | 意味 | 呼び出し側の責務 |
| --- | --- | --- |
| `caller-owned` | 呼び出し側が所有する object / handle / reference | 対応する `delete` / `release` / `unref` を呼ぶ |
| `retained` | refcount を増やして caller-owned にしたもの | `release` する |
| `borrowed` | 親 object、handle table、Skia 内部 storage に寿命が依存する | 解放しない。寿命を越えて保持しない |
| `consumed` | callee が所有権を引き取る | 渡した後に caller 側で解放しない |
| `required` | NULL 不可 | NULL を渡すと fail-safe 値または no-op |
| `optional` | NULL が意味を持ち許容される | NULL を渡してよい |
| `callback-only` | callback 実行中だけ有効 | callback の外へ保存しない |
| `not retained` | callee が pointer を保持しない | 呼び出し後の寿命管理は caller 側 |

## Invalid Input の戻り規約

NULL receiver、required pointer NULL、invalid handle、stale handle、範囲外 enum、無効な buffer / rowBytes、count と array の不整合は、次の規約に寄せます。

| API 種別 | invalid input 時の戻り値 |
| --- | --- |
| `void` mutation / draw / setter | no-op |
| `bool` | `false` |
| integer handle return | `0` |
| raw borrowed pointer return | `NULL` |
| refcounted pointer return | `NULL` |
| numeric getter | 原則 `0` |
| enum getter | 既存互換がなければ `0` 相当 |
| `delete` / `release` / `unref` | no-op |
| callback API | callback が非 NULL なら失敗 result で呼ぶ。callback NULL なら no-op |

例外を置く場合は、ヘッダコメントと作業記録に理由を残します。Skia upstream が NULL payload を意味のある入力として許容する場合は、receiver だけを required にし、payload 側は optional とします。

## 入力検証

### Receiver

メソッド風 API の第一引数 receiver は required です。

```cpp
if (canvas == nullptr) {
    return;
}
```

戻り値がある場合は、戻り規約に従います。

```cpp
if (image == nullptr) {
    return 0;
}
```

### Pointer Input

`const T*` の入力 pointer は、Skia API が NULL を許容する場合だけ optional とします。許容しない場合は required として guard します。

```cpp
if (image == nullptr || sampling == nullptr) {
    return 0;
}
```

### Output Pointer

出力 pointer は原則 required です。NULL の場合は `false` / `0` / no-op にします。

```cpp
if (font == nullptr || widths == nullptr) {
    return false;
}
```

複数の out parameter が optional の場合は、ヘッダコメントで明記します。

### Count と Array

`count <= 0` を空入力として扱える API では、array NULL を許容できます。`count > 0` の場合、array は required です。

```cpp
if (count < 0) {
    return;
}
if (count > 0 && values == nullptr) {
    return;
}
```

`size_t` のような unsigned count では、`count > 0 && array == nullptr` を invalid とします。

### Handle

integer handle は、registry または `has_*_handle` 相当で検証します。存在しない key や stale handle を `operator[]` 的に生成してはいけません。

```cpp
if (!has_image_handle(image)) {
    return;
}
```

handle `0` は原則 invalid です。API ごとに「0 は空入力として許容」とする場合は、ヘッダコメントで明記します。

### Buffer と Row Bytes

pixel buffer は、info、pixels、rowBytes をまとめて検証します。

```cpp
if (info == nullptr || pixels == nullptr || !info->validRowBytes(rowBytes)) {
    return false;
}
```

caller-owned buffer を callee が保持しない場合は `not retained` と書きます。bitmap、pixmap、canvas が storage を借用する場合は、どの object の寿命に依存するかを書きます。

## 所有権と Lifetime

### Handle を返す API

成功時に返す handle は `caller-owned` とします。factory failure や invalid input では `0` を返します。

```c
/**
 * image and sampling are required.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * Returns 0 on invalid input or factory failure.
 */
sk_shader_t SkImage_makeShader(...);
```

### Borrowed Pointer を返す API

borrowed pointer は caller が解放しません。どの object の寿命に依存するかを必ず書きます。

```c
/**
 * Returns a borrowed canvas owned by surface.
 * The returned pointer must not be deleted by the caller.
 * Returns NULL when surface is NULL.
 */
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface);
```

### RefCounted

RefCounted object は `retain` / `release` を基本規約にします。互換のため `delete` が残る場合でも、内部では `release` 相当に寄せます。

ヘッダでは `caller-owned reference` と、解放関数を明示します。

### Callback

callback に渡す result / pointer は、原則 `callback-only` です。callback の外へ保存できません。

context は caller-owned です。Reskia は解放しません。

invalid input で callback を呼ぶ API は、次の規約にします。

- callback 非 NULL: 失敗 result、または `NULL result` で callback を呼ぶ。
- callback NULL: no-op。
- context NULL: 許容。

## ヘッダコメント

安全性規約がある API は、宣言直前に短い `/** ... */` コメントを置きます。

コメントに含めるべき情報:

- required input
- optional input
- returned ownership
- borrowed lifetime
- consumed ownership
- callback result / context lifetime
- failure value
- count と array の関係
- buffer / rowBytes / storage lifetime
- delete / release 方法

単純な NULL no-op だけなら行末コメントでもよいです。

```c
void SkCanvas_delete(reskia_canvas_t *canvas); // NULL canvas is no-op.
```

推奨語彙:

- `required`
- `may be NULL`
- `optional out param`
- `caller-owned`
- `borrowed`
- `not retained`
- `valid only while ... remains unchanged`
- `callback-only`
- `invalid input is no-op`
- `returns 0 on invalid input or factory failure`
- `returns false on invalid input`

避ける表現:

- `safe` のように条件が不明な語。
- `owned` だけで所有者が不明な説明。
- 実装や smoke で保証していない理想論。
- 長すぎる日本語説明。

今後追加する安全性コメントは、短い英語文に寄せます。既存コメントを一括翻訳する必要はありません。

## 実装パターン

### `void` API

```cpp
void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top) {
    if (canvas == nullptr || !has_image_handle(image)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), left, top);
}
```

### `bool` API

```cpp
bool SkImage_readPixelsWithImageInfo(
        reskia_image_t *image,
        const reskia_image_info_t *dstInfo,
        void *dstPixels,
        size_t dstRowBytes) {
    if (image == nullptr || dstInfo == nullptr || dstPixels == nullptr ||
        !reinterpret_cast<const SkImageInfo *>(dstInfo)->validRowBytes(dstRowBytes)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(
            *reinterpret_cast<const SkImageInfo *>(dstInfo),
            dstPixels,
            dstRowBytes,
            0,
            0);
}
```

### Handle Return API

```cpp
sk_shader_t SkImage_makeShader(
        reskia_image_t *image,
        reskia_image_tile_mode_t tmx,
        reskia_image_tile_mode_t tmy,
        const reskia_sampling_options_t *sampling,
        const reskia_matrix_t *localMatrix) {
    if (image == nullptr || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(
            static_cast<SkTileMode>(tmx),
            static_cast<SkTileMode>(tmy),
            *reinterpret_cast<const SkSamplingOptions *>(sampling),
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}
```

`static_*_make` が NULL `sk_sp` を `0` に正規化しない場合は、C API 側で明示的に `0` へ正規化します。

### Borrowed Return API

```cpp
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface) {
    if (surface == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkSurface *>(surface)->getCanvas());
}
```

返却 pointer は surface-owned であり、caller は delete しません。

## Smoke Test

安全化対象 API では、対象リスクに応じて次を確認します。

- NULL receiver。
- required pointer NULL。
- invalid handle。
- stale handle。
- optional pointer NULL が許容されること。
- `count > 0` かつ array NULL。
- invalid rowBytes / storage。
- factory failure が `0` になること。
- 最小 valid path。
- 返却 handle が delete / release できること。
- borrowed pointer を caller が delete しないこと。
- callback NULL no-op。
- callback context NULL でも動くこと。

すべてのケースを毎回追加する必要はありません。対象 API の規約に対応するケースを選びます。

`void` API は戻り値を assert できないため、no crash を smoke として扱います。戻り値がある API は、invalid input の戻り値を明示的に check します。

test は早期 return が多いため、追加した handle / pointer は全 exit path で解放します。

## 編集手順

1. upstream Skia の public header と実装を確認する。
2. 既存 C API の形と ABI 互換を確認する。
3. receiver、required pointer、handle、buffer、callback の guard を入れる。
4. 戻り値を invalid input 規約に揃える。
5. ヘッダコメントに所有権と lifetime を書く。
6. 対象リスクに対応する smoke を追加する。
7. coverage / checklist / 作業記録を更新する。

変更は対象 API に閉じます。関係ないリファクタや広すぎる整形を混ぜないでください。

## 検証

基本確認:

```bash
git diff --check
cmake -S skia -B skia/cmake-build-capi-safety -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-capi-safety -j 8
```

テストを追加した場合:

```bash
cmake -S skia -B skia/cmake-build-capi-safety-tests \
  -DCMAKE_BUILD_TYPE=Debug \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-capi-safety-tests -j 8
ctest --test-dir skia/cmake-build-capi-safety-tests --output-on-failure
```

coverage に関わる変更では、必要に応じて generator を再実行します。

```bash
python3 scripts/generate_public_api_coverage.py \
  --output docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --previous-matrix docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv \
  --stale-output docs/ja/plans/c-binding-remediation/checklists/public-api-stale-capi.csv
```

## 関連文書

- `docs/ja/README.md`
- `docs/ja/guides/repository-structure.md`
- `docs/ja/plans/c-binding-remediation/README.md`
- `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- `docs/ja/plans/stability-hardening/00-plan.md`
