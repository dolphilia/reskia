# Reskia C API Safety Guidelines

作成日時: 2026-05-12 23:58:17 JST

## 目的

この文書は、`skia/capi`、`skia/handles`、`skia/test` を編集するときの安全化基準を一本化する。特に、C ABI 境界での NULL 入力、invalid handle、stale handle、所有権、borrowed lifetime、callback、ヘッダコメント、smoke test、バッチ記録の書き方を揃える。

`docs/plans/stability-hardening/` の各バッチ記録は実施ログであり、この文書は今後の編集時に参照する作業標準である。

## 基本原則

1. C ABI 境界では、利用者の誤入力で crash させない。
2. Skia C++ API の意味を勝手に変えない。C API 側では入力検証、所有権明示、失敗値の正規化を行う。
3. 既存 ABI を一括破壊しない。型や戻り値を変える必要がある場合は、互換 wrapper、別名 API、または移行フェーズを用意する。
4. 返却値の所有権と寿命は、ヘッダコメントまたはガイドから判断できる状態にする。
5. invalid input 対応を入れたら、原則として invalid path と最小 valid path の smoke を追加する。
6. 関係ないリファクタを混ぜない。1 バッチは、対象 API とその規約確認に閉じる。
7. 実装、ヘッダコメント、smoke、`capi-status.csv`、バッチ記録を同じ意味に揃える。

## 用語

| 用語 | 意味 | 呼び出し側の責務 |
| --- | --- | --- |
| caller-owned | 返された handle / object を呼び出し側が delete / release する | 対応する `static_*_delete`、`*_delete`、`*_release` を呼ぶ |
| retained | refcount を増やして caller-owned にしたもの | `release` する |
| borrowed | 親 object、handle table、または Skia 内部 storage に借用依存する | 解放しない。寿命を越えて保持しない |
| optional | NULL が意味を持ち、許容される | NULL を渡してよい |
| required | NULL 不可 | NULL なら fail-safe 値または no-op |
| consumed | callee が所有権を引き取る | 渡した後に呼び出し側が解放しない |
| callback-only | callback 実行中だけ有効 | callback の外へ保存しない |
| not retained | callee が pointer を保持しない | 呼び出し後の寿命管理は caller 側 |

## Invalid Input の戻り規約

原則として、NULL receiver、required pointer NULL、invalid handle、stale handle、範囲外 enum、無効 rowBytes、count と array の不整合は次の規約に寄せる。

| API 種別 | invalid input 時の戻り値 |
| --- | --- |
| `void` mutation / draw / setter | no-op |
| `bool` | `false` |
| static handle return (`sk_image_t` など) | `0` |
| raw borrowed pointer return | `NULL` |
| refcounted pointer return | `NULL` |
| numeric getter | 原則 `0` |
| enum getter | 既存互換がなければ `0` 相当 |
| size getter | `0` |
| `delete` / `release` / `unref` | no-op |
| callback API | callback が非 NULL なら失敗 result で呼ぶ。callback NULL なら no-op |

例外を置く場合は、ヘッダコメントとバッチ記録に理由を残す。Skia upstream が NULL payload を意味のある入力として許容する場合は、receiver だけを required にし、payload 側は optional として扱う。

## 入力検証の基準

### Receiver

メソッド風 API の第一引数 receiver は required とする。

```cpp
if (canvas == nullptr) {
    return;
}
```

戻り値がある場合は戻り規約に従う。

```cpp
if (image == nullptr) {
    return 0;
}
```

### Pointer Input

`const T*` の入力 pointer は、Skia API が NULL を許容する場合だけ optional とする。許容しない場合は required として guard する。

```cpp
if (image == nullptr || sampling == nullptr) {
    return 0;
}
```

### Output Pointer

出力 pointer は原則 required とする。NULL なら `false` / `0` / no-op にする。

```cpp
if (font == nullptr || widths == nullptr) {
    return false;
}
```

複数の out param が optional の場合は、ヘッダコメントで `info/rowBytes/origin are optional out params` のように明記する。

### Count と Array

`count <= 0` を no-op または空入力として扱える API では、array NULL を許容してよい。`count > 0` なら array は required とする。

```cpp
if (count < 0) {
    return;
}
if (count > 0 && values == nullptr) {
    return;
}
```

`size_t childCount` のような unsigned count では、`childCount > 0 && children == nullptr` を invalid とする。

### Handle

static handle は `has_*_handle` または registry の valid check を使う。存在しない key や stale handle を `operator[]` 的に生成しない。

```cpp
if (!has_image_handle(image)) {
    return;
}
```

handle `0` は原則 invalid だが、API ごとに「0 は空入力として許容」と決めた場合は明記する。例: `SkRuntimeEffect_makeShader` の data handle `0`。

### Row Bytes と Storage

pixel buffer は、info、pixels、rowBytes をまとめて検証する。`rowBytes` は `SkImageInfo::validRowBytes` 相当を満たすことを条件にする。

```cpp
if (info == nullptr || pixels == nullptr || !info->validRowBytes(rowBytes)) {
    return false;
}
```

caller-owned buffer を callee が保持しない場合は `not retained` と書く。bitmap / pixmap / canvas が storage を借用する場合は lifetime を書く。

### Enum / Flags

既存 ABI の enum は `int32_t` typedef を維持することが多い。実装では `static_cast<Sk...>` を一箇所に閉じ込める。明らかな範囲外値を検出できる API では no-op / `0` / `false` にする。

## 所有権と Lifetime の基準

### Handle を返す API

返却 handle は、成功時に caller-owned とする。factory が NULL `sk_sp` を返した場合や入力が invalid の場合は `0` を返す。

ヘッダコメントには、少なくとも次を書く。

- required input
- optional input
- returned handle ownership
- failure value
- delete 方法が自明でない場合の delete 関数

例:

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

borrowed pointer は caller が解放しない。親 object、handle table、または callback の寿命に依存することを明記する。

例:

```c
/**
 * Returns borrowed raw pixels owned by the canvas top layer.
 * info, rowBytes, and origin are optional out params.
 * Returns NULL when canvas is NULL or top-layer storage is unavailable.
 * The returned pointer is valid only while the canvas storage remains unchanged.
 */
void *SkCanvas_accessTopLayerPixels(...);
```

### RefCounted

RefCounted 型は `retain/release` を正規規約に寄せる。互換のため `delete` が残る場合も、内部では `release` 相当に委譲する方針を優先する。ヘッダでは `caller-owned reference`、`release with ...` のように書く。

### Callback

callback に渡る result / pointer は、原則 callback-only とする。callback の外へ保存してはいけない。context は caller-owned であり、C API は解放しない。

invalid input で callback を呼ぶ API は、次の規約にする。

- callback 非 NULL: `NULL result` で callback を呼ぶ。
- callback NULL: no-op。
- context は NULL 許可。

## ヘッダコメント規約

### いつ複数行コメントにするか

次のいずれかを含む場合は、宣言の直前に `/** ... */` の複数行コメントを置く。

- returned handle ownership
- borrowed pointer lifetime
- callback result / context lifetime
- consumed ownership
- required と optional が混在する
- failure value が複数条件に依存する
- rowBytes / storage lifetime
- count と array の関係
- delete / release 方法

単純な NULL no-op だけなら行末コメントを維持してよい。

```c
void SkCanvas_delete(reskia_canvas_t *canvas); // NULL canvas is no-op.
```

### 複数行コメントの標準形

```c
/**
 * canvas, image, dst, and sampling are required.
 * paint may be NULL.
 * Invalid input is no-op.
 */
void SkCanvas_drawImageRect(...);
```

```c
/**
 * image, info, srcRect, and callback are required.
 * context may be NULL and is not owned by Reskia.
 * Invalid input calls callback with NULL result when callback is provided.
 * NULL callback is no-op.
 */
void SkImage_asyncRescaleAndReadPixels(...);
```

```c
/**
 * data handle 0 is allowed as empty data.
 * Non-zero data must be a valid handle.
 * children must be non-NULL when childCount > 0.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * Returns 0 on invalid input or factory failure.
 */
sk_shader_t SkRuntimeEffect_makeShader(...);
```

### 行末コメントを使ってよい場合

短い API では行末コメントを残してよい。

```c
bool SkImage_isTextureBacked(reskia_image_t *image); // NULL image returns false.
```

ただし、行が長くなりすぎる場合、または安全性規約が 2 文以上になる場合は複数行へ昇格する。

### 既存コメントの機械整形

既存ヘッダーの長い行末コメントを複数行へ移す場合は、`scripts/format_capi_header_comments.py` を使える。このスクリプトは宣言の意味を書き換えず、` ; // ...` の行末コメントを宣言直前の `/** ... */` block comment に移すだけに限定している。

高頻度ヘッダーをやや広めに整形する例:

```bash
python3 scripts/format_capi_header_comments.py --dry-run --mode moderate --min-length 120 \
  skia/capi/sk_canvas.h \
  skia/capi/sk_image.h \
  skia/capi/sk_runtime_effect.h \
  skia/capi/sk_runtime_shader_builder.h \
  skia/capi/sk_runtime_color_filter_builder.h \
  skia/capi/sk_runtime_blend_builder.h \
  skia/capi/sk_runtime_effect_builder.h
```

全 `skia/capi/*.h` に対して安全性 keyword を含む長いコメントだけを保守的に整形する例:

```bash
python3 scripts/format_capi_header_comments.py --dry-run --mode strict --min-length 160 --all-capi
```

`--apply` は dry-run の候補数と内容を確認してから使う。整形後は、少なくとも次を確認する。

```bash
git diff --check
python3 scripts/format_capi_header_comments.py --dry-run --mode strict --min-length 160 --all-capi
cmake --build skia/cmake-build-stability-prebuilt -j 8
```

既に複数行化した高頻度ヘッダーについて、行末に残った Skia signature 断片、長すぎる Skia signature 行、定型的な日英混在句を追加で整える場合は、`scripts/refine_capi_header_comments.py` を使う。この pass は既存の `/** ... */` 内だけを編集し、宣言本体には触れない。対象はまず `--default-set` の高頻度ヘッダーに限定し、dry-run と diff review を挟む。

```bash
python3 scripts/refine_capi_header_comments.py --dry-run --default-set
python3 scripts/refine_capi_header_comments.py --apply --default-set
```

### コメントの語彙

コメントでは次の語彙を優先する。

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

- `safe`
- `valid` だけで条件を書かない説明
- `owned` だけで誰が所有するか不明な説明
- 日本語と英語が混在しすぎる長文
- 実装と一致しない理想論

既存ヘッダには日本語コメントもあるが、今後追加する安全性規約コメントは、短い英語文に寄せる。既存コメントを一括翻訳する必要はない。

## 実装パターン

### Void API

```cpp
void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top) {
    if (canvas == nullptr || !has_image_handle(image)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), left, top);
}
```

### Bool API

```cpp
bool SkImage_readPixelsWithImageInfo(
        reskia_image_t *image,
        const reskia_image_info_t *dstInfo,
        void *dstPixels,
        size_t dstRowBytes,
        int srcX,
        int srcY,
        reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || !has_valid_pixels(dstInfo, dstPixels, dstRowBytes)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(
            *reinterpret_cast<const SkImageInfo *>(dstInfo),
            dstPixels,
            dstRowBytes,
            srcX,
            srcY,
            static_cast<SkImage::CachingHint>(cachingHint));
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

`static_*_make` 側が NULL `sk_sp` を 0 に正規化しない場合は、C API 側で明示的に 0 へ正規化する。

### Borrowed Return API

```cpp
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface) {
    if (surface == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkSurface *>(surface)->getCanvas());
}
```

この場合、返却 pointer は surface-owned であり caller は delete しない。

### Callback API

```cpp
void SkImage_asyncRescaleAndReadPixels(
        reskia_image_t *image,
        const reskia_image_info_t *info,
        const reskia_i_rect_t *srcRect,
        reskia_image_rescale_gamma_t rescaleGamma,
        reskia_image_rescale_mode_t rescaleMode,
        reskia_async_read_pixels_callback_t callback,
        void *context) {
    if (!image || !info || !srcRect || !callback) {
        reskia_async_read_pixels_fail(callback, context);
        return;
    }
    reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixels(
            *reinterpret_cast<const SkImageInfo *>(info),
            *reinterpret_cast<const SkIRect *>(srcRect),
            static_cast<SkImage::RescaleGamma>(rescaleGamma),
            static_cast<SkImage::RescaleMode>(rescaleMode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, context));
}
```

`reskia_async_read_pixels_fail` は callback NULL を no-op にする前提で使う。

## Smoke Test 基準

### 最低限入れるケース

安全化対象 API では、可能な範囲で次を入れる。

1. NULL receiver。
2. required pointer NULL。
3. invalid handle。
4. optional pointer NULL が許容されること。
5. count > 0 かつ array NULL。
6. invalid rowBytes / storage。
7. factory failure が `0` になること。
8. valid minimal path。
9. returned handle が registry 上で有効で delete できること。
10. borrowed pointer / pixmap が返るが caller が delete しないこと。
11. callback NULL no-op。
12. callback context NULL でも callback が呼べること。

全ケースを毎回入れる必要はない。対象 API のリスクに対応するケースを選ぶ。

### Valid Path を入れる基準

次のどれかに該当する場合は valid path を入れる。

- returned handle ownership をコメントに書く。
- borrowed pointer lifetime をコメントに書く。
- optional pointer NULL を許容する。
- callback context を扱う。
- factory failure と成功時の両方があり得る。
- rowBytes / storage の valid 条件を明記する。

valid path では、返却 handle を `static_*_get_ptr` などで確認し、必ず delete / release する。

```cpp
const sk_shader_t shader = SkImage_makeShader(image, 0, 0, sampling, nullptr);
ok &= check(shader != 0 && static_sk_shader_get_ptr(shader) != nullptr, "SkImage_makeShader returned handle ownership");
if (shader != 0) {
    static_sk_shader_delete(shader);
}
```

### Invalid Path の書き方

`void` API は no-op なので、戻り値を assert できない。クラッシュしないことを smoke として扱う。

```cpp
SkCanvas_drawImage(canvas, 999999, 0.0f, 0.0f);
SkCanvas_drawImageHandleWithSampling(canvas, image, 0.0f, 0.0f, nullptr, nullptr);
```

戻り値がある API は明示的に check する。

```cpp
if (!check(SkImage_makeSubset(image, nullptr, invalid_subset) == 0, "SkImage_makeSubset factory failure returns 0")) {
    return 40;
}
```

### Callback の確認

invalid input の callback は、呼び出し回数と result NULL を確認する。

```cpp
struct AsyncFailState {
    int calls = 0;
};

void async_fail_callback(void *context, const reskia_async_read_result_t *result) {
    auto *state = static_cast<AsyncFailState *>(context);
    if (state != nullptr && result == nullptr) {
        ++state->calls;
    }
}
```

NULL callback no-op も count が増えないことで確認する。

### Test の粒度

既存の `test_*_invalid_input_smoke.cpp` に追加できる場合は、対象型の既存 smoke を拡張する。新しい型や横断性が高い API では専用 smoke を追加する。

テスト名は `c_skia_<type>_invalid_input_smoke` の既存規則に従う。

### Cleanup

test は早期 return が多いため、追加した handle / pointer は全 exit path で解放する。失敗時の cleanup を省かない。

小さい追加では既存スタイルに合わせる。大きくなる場合は、局所 RAII helper を検討してよいが、既存 test の読みやすさを優先する。

## ヘッダ編集の進め方

1. まず実装の guard と実際の戻り値を確認する。
2. コメントは実装と smoke で保証できる内容だけを書く。
3. 複雑な規約は複数行コメントにする。
4. 同じ overload 群では語彙と順序を揃える。
5. 既存の長い行末コメントは、触る関数から段階的に複数行へ移す。
6. 一括整形だけの巨大 diff は作らない。

コメントの推奨順序:

1. required input
2. optional input / optional out param
3. ownership / lifetime
4. failure value / no-op
5. delete / release 方法

## 実装編集の進め方

1. Skia upstream の公開ヘッダで対象 API の NULL 許容、ownership、factory failure を確認する。
2. 既存 C API の呼び出しパターンと helper を確認する。
3. receiver guard を追加する。
4. required pointer / handle guard を追加する。
5. optional pointer は Skia API にそのまま渡す。
6. factory result は handle `0` に正規化する。
7. callback context allocation がある API は、invalid path で leak しないようにする。
8. 実装変更後に smoke を追加する。

## 効率的なバッチ設計

安全化バッチは、関数 1 つずつではなく、同じ安全性規約を共有する API 群単位で進める。目的は、確実性を落とさずに、1 バッチあたりの進捗量を増やすことである。

### バッチ単位の基本

1 バッチでは、原則として 1-3 ファイル、10-30 関数程度までを扱ってよい。ただし、callback、borrowed lifetime、consumed ownership、async、threading が絡む場合は小さくする。

バッチは「型」だけで切らず、次のような規約パターンで切る。

| パターン | 例 | 推奨規模 |
| --- | --- | --- |
| `void` no-op 系 | `SkCanvas_draw*`, setter, mutation | 20-30 関数 |
| `bool` false 系 | pixel read/write, query with output | 10-20 関数 |
| returned handle 系 | `make*`, `ref*`, `serialize`, factory | 8-15 関数 |
| borrowed pointer 系 | `peekPixels`, `getCanvas`, `access*` | 3-8 関数 |
| callback / async 系 | async read, path callbacks | 3-8 関数 |
| pixel storage 系 | bitmap / pixmap / raw buffer / rowBytes | 5-12 関数 |
| count / array 系 | glyph arrays, vertices, colors, children | 8-20 関数 |

この規模は上限であり、実装差分が複雑になった場合は途中で分割する。

### バッチ前の棚卸し

作業前に `rg` で候補 API を広めに抽出する。

```bash
rg -n "SkCanvas_drawImage|SkCanvas_drawImageRect" skia/capi skia/test
rg -n "SkImage_.*Encoded|SkImage_encode|SkImage_refEncodedData" skia/capi skia/test
rg -n "SkRuntimeEffect_makeColorFilter|SkRuntimeEffect_makeBlender" skia/capi skia/test
```

抽出した API を次の観点で分類する。

- 戻り値: `void` / `bool` / handle / borrowed pointer / numeric。
- receiver: required か、static helper か。
- handle: `0` が invalid か、empty input として許容されるか。
- pointer: required / optional / optional out param のどれか。
- storage: caller-owned / borrowed / consumed / not retained のどれか。
- callback: callback NULL no-op か、callback required か。
- valid path: 軽く作れるか、依存が重いか。

### スコープ宣言

編集前に、バッチ記録または進捗共有で今回のスコープを短く宣言する。

例:

```md
今回のスコープ:

- `SkCanvas` draw image 系 handle/pointer overload。
- 共通規約は invalid input no-op、sampling required、paint optional。
- valid path は handle 版 `drawImage` / `drawImageRect` を代表として確認する。
- pointer 版は NULL pointer no-op を中心に確認し、valid path は handle 版で代表する。
```

### 代表 Valid Path

同じ implementation helper、同じ ownership、同じ overload 群に属する API は、全関数で valid path を重複確認しなくてよい。代表 1-3 件で確認し、残りは invalid path / no-op / failure value を確認する。

代表 valid path を選ぶ優先順位:

1. returned handle ownership を持つ API。
2. borrowed pointer / storage lifetime を持つ API。
3. optional pointer NULL を許容する API。
4. callback context を持つ API。
5. overload 群の中で最も引数が多い API。

ただし、コメントで `Returns a caller-owned ... handle` と書いた API は、可能な限り success handle の registry check と delete / release を smoke に入れる。重い依存のため省略する場合は、バッチ記録に理由を書く。

### Invalid Path の広げ方

`void` no-op 系は比較的広く進めてよい。戻り値がないため、smoke は「クラッシュしないこと」を確認する形になる。

```cpp
SkCanvas_drawImage(canvas, 999999, 0.0f, 0.0f);
SkCanvas_drawImageHandleWithSampling(canvas, image_handle, 0.0f, 0.0f, nullptr, nullptr);
```

`bool` / handle return 系は、各 overload で少なくとも主要 required input の NULL / invalid handle を 1 つ以上確認する。

```cpp
ok &= check(SkImage_makeSubset(image, nullptr, nullptr) == 0, "SkImage_makeSubset null subset");
ok &= check(!SkCanvas_readPixelsWithImageInfo(canvas, info, pixels, 1, 0, 0), "invalid rowBytes");
```

callback 系は広げすぎない。callback NULL no-op、context NULL、invalid input result NULL の 3 点を優先する。

### 省略してよい確認

同じバッチ内で次の条件を満たす場合、全 API の full valid path は省略してよい。

- 同じ C API helper または同じ guard pattern を通る。
- 同じ Skia overload family に属する。
- valid path の作成に重い object graph が必要。
- 代表 valid path で returned handle / borrowed lifetime / callback context を確認済み。

省略した場合は、バッチ記録に「代表 valid path」と「省略理由」を短く書く。

例:

```md
valid path は `SkCanvas_drawImageHandleWithSampling` と `SkCanvas_drawImageRect` で代表確認した。
pointer overload は同じ guard/no-op 規約であり、追加の描画結果検証は行っていない。
```

### 分割すべき兆候

次の兆候が出たら、同じ候補内でもバッチを分ける。

- cleanup path が複雑になり、test の早期 return が読みにくくなる。
- callback と returned handle と borrowed pointer が同じバッチに混在する。
- smoke のために新しい fixture を大きく作る必要がある。
- 実装 guard の意味が API ごとに異なる。
- 1 つの失敗で、多数の unrelated API の検証が止まる。

### 次バッチ候補の書き方

次バッチ候補は、単一関数ではなく、まとまった規約単位で書く。

悪い例:

```md
- `SkImage_refEncodedData` を確認する。
- `SkImage_encodeToData` を確認する。
- `SkImage_encodeToDataWithContext` を確認する。
```

良い例:

```md
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
```

候補は 3 件程度にし、それぞれが 1 バッチとして実行できる粒度にする。

### 効率化しても維持する条件

バッチを大きくしても、次は省略しない。

- ヘッダコメントと実装 guard の一致確認。
- 代表 valid path。
- returned handle の delete / release。
- borrowed pointer を delete しないこと。
- callback NULL no-op と context NULL の扱い。
- 対象 smoke の build / ctest。
- `capi-status.csv` とバッチ記録。
- `git diff --check`。

## Checklist 更新

`docs/plans/c-binding-remediation/checklists/capi-status.csv` は、対象ファイル単位で更新する。

更新する内容:

- `status`: 完了したら `done`
- `phase`: 原則 `P2`
- `date`: 作業日
- `note`: batch 名と要約

例:

```csv
skia/capi/sk_image.h,done,P2,2026-05-12,Phase 2 batch EB: documented image shader rawShader ownership rules
```

実装 `.cpp` を直接変えていない場合でも、smoke でその API の実装規約を固定したなら `.cpp` 行を更新してよい。ただし、コメントだけで behavior を確認していない場合は `.h` のみ更新する。

## バッチ記録

`docs/plans/stability-hardening/NNN-phase-2-batch-xx-*.md` は次の形にする。

```md
# NNN Phase 2 Batch XX: short title

開始時刻: YYYY-MM-DD HH:MM:SS JST

## 目的

前バッチの「次バッチ候補」から何を確認するかを書く。

## 変更内容

- 変更ファイル
  - 何を固定したか。

## 検証

- 実行したコマンド
  - 結果。

## 次バッチ候補

- 次に着手できる候補を3件程度。
```

次バッチ候補は、単に未完了 API を並べるのではなく、同じ smoke / 同じ所有権観点でまとめて処理できる粒度にする。

## 検証コマンド

通常バッチでは、最低限次を実行する。

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests --target <changed_smoke_targets> -j 8
ctest --test-dir skia/cmake-build-stability-tests -R '<changed_ctest_regex>' --output-on-failure
cmake --build skia/cmake-build-stability-prebuilt -j 8
git diff --check
```

C API invalid-input smoke を広く確認する場合は、現在の全体 regex を使う。全体 regex はバッチ記録に残し、対象が増えたら更新する。

docs-only 変更では build は不要だが、少なくとも `git diff --check` を実行する。

## レビュー観点

変更後は次を確認する。

- 実装 guard とヘッダコメントが一致している。
- smoke がコメントで約束した挙動を確認している。
- returned handle を delete / release している。
- borrowed pointer を delete していない。
- callback context を C API 側で解放すると書いていない。
- `0` を invalid とする API と empty input とする API が混ざっていない。
- NULL callback の扱いが no-op か fail callback か、ヘッダと実装で一致している。
- rowBytes / storage の valid 条件が実装と一致している。
- `capi-status.csv` の note が今回の batch と一致している。
- バッチ記録の検証結果が実際に実行したコマンドと一致している。

## よくある判断

### 既存行末コメントをすべて複数行に直すべきか

一括では直さない。触る API のうち、安全性規約が複雑なものから複数行へ移す。単純な delete / getter は行末コメントのままでよい。

### Valid path が重い場合はどうするか

重い依存が必要な場合は invalid path だけにし、valid path は別バッチまたは feature-specific smoke に分ける。記録には valid path を省いた理由を書く。

### Skia が NULL を許容しているか不明な場合

Skia upstream header と実装を確認する。分からない場合は C API 側では required として guard し、後で緩和できる形にする。

### Factory が NULL を返す可能性がある場合

必ず `0` に正規化し、コメントに `factory failure returns 0` を書く。

### Pointer API と Handle API の両方がある場合

handle API は handle validity を確認する。pointer API は pointer non-null を確認する。どちらも同じ Skia API を呼ぶ場合でも、コメントにはそれぞれの入力規約を書く。

### Callback result を保存するテストを書くべきか

原則書かない。callback-only lifetime を破るテストは sanitizer 専用または負例ドキュメントに分ける。

## 関連文書

- `docs/plans/stability-hardening/00-plan.md`
- `docs/plans/c-binding-remediation/00-objectives-and-constraints.md`
- `docs/plans/c-binding-remediation/03-phase-2-ownership-api.md`
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
- `docs/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv`
- `docs/guides/repository-structure.md`
