# C API / Handle Binding Overview

この文書は、Reskia の C API binding と handle binding の全体像を説明します。個別 API の安全性規約は `docs/ja/guides/c-api-safety-guidelines.md` を参照してください。

## 方針

Reskia は、Skia の公開クラスについて、公開メソッドと static factory / helper を可能な範囲で C ABI に公開します。

公開時に確認すること:

- upstream Skia の public header に存在する API か。
- C ABI として表現できる型か。
- pointer API と handle API のどちらが適しているか。
- ownership と lifetime を説明できるか。
- optional module や platform dependency を持つか。
- coverage matrix に状態を記録できるか。

## 2つの API 層

### `skia/capi`

`skia/capi` は pointer-oriented API です。

特徴:

- `extern "C"` の関数を公開する。
- 不透明 pointer 型を通じて Skia object を扱う。
- Skia C++ API に近い形で呼び出せる。
- ownership、NULL 入力、borrowed lifetime、callback lifetime をヘッダコメントで補う。

例:

```c
reskia_image_t *SkImage_newRaster(...);
void SkImage_delete(reskia_image_t *image);
bool SkImage_readPixels(...);
```

### `skia/handles`

`skia/handles` は integer-handle API です。

特徴:

- `sk_image_t` のような整数 handle を公開する。
- 内部の handle table が object を保持する。
- invalid handle と stale handle を検出できる。
- 他言語 binding で raw pointer を避けやすい。

例:

```c
sk_image_t static_sk_image_make(...);
void static_sk_image_delete(sk_image_t image);
```

## 使い分け

| 観点 | `skia/capi` | `skia/handles` |
| --- | --- | --- |
| 境界 | raw pointer に近い | integer handle |
| 表現力 | Skia C++ API に近い | binding 側で扱いやすい |
| lifetime | caller とコメントで管理 | handle table が管理 |
| 主な用途 | C / FFI の薄い wrapper | raw pointer を避けたい言語 binding |

同じ概念を両方で公開する場合は、所有権と失敗値を揃えます。

## 命名

API 名は、Skia の型名と method / factory の意味が分かる名前にします。

推奨:

- overload は連番ではなく意味名にする。
- factory failure があり得る API は戻り値で `0` / `NULL` を表す。
- handle API は `static_sk_*` の既存規則に合わせる。

避けるもの:

- `_2`, `_3` のような一時的な連番名。
- 所有権が分からない `get` / `new` の混用。
- Skia 側で削除された API を残すこと。

## Ownership

返却値は次のいずれかに分類します。

| 分類 | 意味 |
| --- | --- |
| `caller-owned` | caller が delete / release する。 |
| `borrowed` | caller は解放しない。親 object や storage の寿命に依存する。 |
| `retained` | refcount を増やして caller-owned にしたもの。 |
| `consumed` | callee が引数の所有権を引き取る。 |
| `callback-only` | callback 実行中だけ有効。 |

ヘッダコメントには、少なくとも required / optional input、返却 ownership、failure value を書きます。

## Coverage Matrix

公開 API の対応状況は `docs/ja/plans/c-binding-remediation/checklists/public-api-coverage-matrix.csv` で管理します。

主な status:

- `covered`: C API として対応済み。
- `split_covered`: 複数関数に分けて対応済み。
- `false_positive`: generator 上の検出だが実 API としては対象外。
- `na`: C ABI として公開しない理由がある。
- `missing`: 対応が必要。

matrix の生成方法は `docs/ja/guides/public-api-coverage-workflow.md` にあります。

## CMake への組み込み

C API / handles の source は `reskia` target に組み込みます。

関連箇所:

- `skia/capi/*.h`, `skia/capi/*.cpp`
- `skia/handles/*.h`, `skia/handles/*.cpp`
- `cmake/reskia/sources-*.cmake`
- `skia/CMakeLists.txt`

新しい source を追加したら、CMake source list と build を確認します。

## 追加・変更時の流れ

1. upstream Skia の public header を確認する。
2. C ABI として公開する価値と制約を判断する。
3. API 名、引数、返却 ownership、failure value を決める。
4. `skia/capi` または `skia/handles` に実装する。
5. safety comment と smoke test を追加する。
6. coverage matrix と stale C API report を更新する。
7. configure / build / test を実行する。

安全性の詳細は `docs/ja/guides/c-api-safety-guidelines.md` に従います。
