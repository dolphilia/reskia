# skia Cバインディング設計レビュー（2026-02-14）

対象: `/Users/dolphilia/github/reskia/skia/static`, `/Users/dolphilia/github/reskia/skia/binding`  
確認時刻: 2026-02-14 11:21:24 JST

## 1. 現状構成の要約

- `binding/`: C公開API。`void*` と `int`（`sk_*_t`）で C++ 型を橋渡し。
- `static/`: `int` キーを `std::map<int, T>` に紐付けるグローバルレジストリ群。
- 規模:
  - `static/*.cpp`: 108
  - `binding/*.cpp`: 155
  - `static` の公開ハンドル typedef（`typedef int sk_*_t`）: 92

## 2. 主要な問題点（優先度順）

### P0: `get_entity()` が所有権を破壊する実装

`sk_sp` / `std::unique_ptr` の `get_entity()` が `std::move(map[key])` を返しており、取得時にストアから値が抜ける。

- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_image.cpp:31`
- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_data.cpp:34`
- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_data.cpp:71`

影響:

- 「参照だけしたい」呼び出しでも実体が消える。
- 同じハンドルの再利用時に `null` 化し、後続で不定挙動。
- `binding` 側で `get_entity()` を多用しており、連鎖的に再現しうる。
  - 例: `/Users/dolphilia/github/reskia/skia/binding/sk_image_filters.cpp:33`
  - 例: `/Users/dolphilia/github/reskia/skia/binding/sk_runtime_effect.cpp:45`

### P0: `map[key]` 乱用による無効キーの黙殺

`get_ptr`, `get_entity`, `delete` で `operator[]` を多用しているため、無効キーでも新規エントリが暗黙生成される。

- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_surface.cpp:43`
- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_color_4f.cpp:40`
- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_stream_asset.cpp:41`

影響:

- バグが即時検出されず、状態破壊が遅延顕在化。
- `delete(-1)` のような異常値でもキー空間を汚染可能。

### P0: ハンドル再利用（ABA問題）と世代管理なし

キー再利用は `available_keys` の再配布のみで、世代カウンタがない。

- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_surface.cpp:10`

影響:

- 古いハンドル値が新しいオブジェクトを誤参照する可能性。
- FFI層で stale handle を安全に検出できない。

### P1: スレッド安全性がない

`static` グローバル `map/set` をロック無しで更新している。  
`mutex/atomic/thread_local` は `static/`・`binding/` で未使用。

影響:

- 複数スレッドから同時呼び出し時にデータ競合。
- 将来、描画処理やデコード処理を並列化した際に不安定化。

### P1: 所有権モデルの混在（`delete` と `ref/unref` が並立）

同じ型に `delete` と `ref/unref` が共存しており、呼び出し側で責務を誤りやすい。

- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_image.h:12`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_image.h:66`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_surface.h:12`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_surface.h:46`

影響:

- 二重解放・解放漏れ・未定義動作の誘発。

### P1: C APIとしての型情報不足

`void*` / `int` 主体で、シグネチャだけでは型意味が分かりづらい。  
コメント依存で補っているが、IDE補完・静的解析・誤用検知に弱い。

- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_path.h:13`

### P2: C APIに C++ 寄り要素が残る

`std::string_view` / `std::initializer_list` 相当の概念をハンドル化して持ち込んでいる。

- 例: `/Users/dolphilia/github/reskia/skia/static/static_std_string_view.cpp:9`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_path.h:80`

影響:

- C側利用者にはライフタイム規約が読み取りづらい。
- `string_view` は参照先寿命切れの危険が高い。

### P2: 命名の意図が伝わりにくい

- `static/` は「静的ストレージ実装」であって公開意図を示しにくい。
- `*_2`, `*_3` 連番はオーバーロード代替としては機械的で可読性が低い。

## 3. 改善方針（推奨）

### 方針A: API面の整理（互換を保ちつつ段階移行）

- `binding` を「公開C API」、`static` を「内部ハンドルレジストリ」と明確化。
- ディレクトリ名を段階的に以下へ移行:
  - `static/` -> `handles/` または `registry/`
  - `binding/` -> `capi/`

### 方針B: ハンドルレジストリ共通化

個別 `map/set/index` をやめ、共通テンプレート化した `HandleTable<T>` を導入する。

要件:

- `create/get/erase/retain/release` を共通実装
- `std::shared_mutex` などで同期
- 64bit ハンドル（`index + generation`）で stale handle 検出
- `operator[]` 禁止、`find` ベースで厳密チェック

### 方針C: 所有権 API を明示分離

- Borrow: `*_get_ptr` 相当（所有権移動なし）
- Clone/Retain: `*_retain`（参照カウント増加またはコピー）
- Take: `*_take`（明示的所有権移動）
- Release: `*_release`

現状の `get_entity()` は用途が曖昧なため、`borrow_entity` / `take_entity` に分割する。

### 方針D: C公開型の見直し（LuaJIT互換を維持）

- FFI都合で `void*` を残す場合も、型付き typedef を併設:
  - `typedef struct reskia_image* reskia_image_t;`
- 少なくとも API 名で型を明確化し、`void*` 生値を跨いで使う場面を削減。
- `out` パラメータには `reskia_status_t` を導入し失敗理由を返す。

### 方針E: 自動生成の導入

現状の関数数では手作業同期コストが高い。  
型定義（YAML/JSON）から `*.h/*.cpp` を生成し、コメントと実装乖離を減らす。

## 4. まず着手すべき最小修正（高効果）

1. `static_*_get_entity()` から `std::move` を除去（非破壊取得に統一）
2. `operator[]` を `find` に置換し、無効キーを即エラー化
3. レジストリ層にロック導入（最低限 `std::mutex`）
4. `delete`/`ref`/`unref` が混在する型に所有権規約コメントを追加
5. `string_view` 系ハンドルの寿命ルールを明文化し、危険 API を限定

## 5. 命名に関する提案

- `static/` は `handles/` が最も意図に一致
  - 理由: 「静的変数」ではなく「ハンドル管理」が本質
- `binding/` は `capi/` または `api/c/`
  - 理由: 利用者視点で公開面が明確

## 6. 提案する移行ステップ

1. 安全化フェーズ  
`get_entity` / `operator[]` / 同期の修正を最優先（挙動バグ抑止）。

2. API整備フェーズ  
所有権APIを `borrow/retain/release/take` に分離し、`delete` 依存を縮小。

3. 構造改善フェーズ  
`static` -> `handles` へ名称移行、コード生成導入、連番関数名の整理。

4. 互換整理フェーズ  
LuaJIT向け互換ヘッダを残しつつ、新API（型付き）を既定へ移行。

## 7. Rust利用を前提にした追加検討

### 7.1 LuaJIT前提から Rust前提への設計転換

LuaJIT時代は GC finalizer で解放フックを差し込めるため、C側 API が多少曖昧でも運用で吸収できた。  
Rustでは `Drop` による RAII が基本で、所有権規約が API で明示されていないと unsafe 境界が肥大化する。

結論:

- Rust向けには「何を所有し、何を借用し、何を解放するか」をC API側で固定する必要がある。
- `void*`/`int` だけのAPIをそのまま包むより、最小限でも ownership-aware な C ABI を定義した方が安全。

### 7.2 現状APIで特に危険な点（解放まわり）

`SkRefCnt` 系オブジェクトで `delete` と `ref/unref` が同時公開されている。

- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_image.cpp:27`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_image.cpp:232`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_surface.cpp:25`
- 例: `/Users/dolphilia/github/reskia/skia/binding/sk_surface.cpp:150`

`static` 側は `sk_sp` 保持だが、`get_entity()` が move 取得になっているため、所有権の一貫性が壊れやすい。

- 例: `/Users/dolphilia/github/reskia/skia/static/static_sk_image.cpp:31`

### 7.3 Rust向け推奨所有権モデル（C ABI）

型カテゴリを3つに分ける。

1. RefCounted型（`SkImage`, `SkSurface`, `SkShader` など）
- C ABIは `retain/release` のみ公開（`delete` は禁止）
- Rust側: `Clone` で retain、`Drop` で release

2. Value型（`SkRect`, `SkMatrix`, `SkColor4f` など）
- POD近いものは値渡し構造体化を優先
- どうしてもハンドル化する場合は `create/destroy` 明示

3. Borrowed型（内部バッファ・一時ビュー）
- `borrow_*` APIを別名で分離
- 所有権を持たないことを関数名で明示

### 7.4 GC連携（LuaJIT）とRust RAIIの両立

両言語対応のため、C APIを以下に統一する。

- 生成: `reskia_*_new` / `reskia_*_from_*`
- 共有参照: `reskia_*_retain`
- 解放: `reskia_*_release`
- 借用: `reskia_*_borrow_*`（release不要）

これにより:

- LuaJIT: `ffi.gc(handle, reskia_*_release)` を設定
- Rust: `Drop` で `reskia_*_release` を呼ぶ
- 双方とも同じ所有権規約を使える

### 7.5 Rust実装戦略

選択肢A（推奨）: C ABIを薄く再設計し、Rustは `bindgen` + 手書き safe wrapper  
選択肢B: `cxx/autocxx` でC++直接連携（開発速度は高いが ABI 依存が強い）

Reskiaの目的（他言語展開と長期保守）を考えると、Aの方が将来の互換維持に有利。

### 7.6 直近で実施すべき解放ルールの是正

1. `SkRefCnt` 系の `*_delete(void*)` を非推奨化し、内部実装を `unref` 経由へ統一  
2. `static_*_get_entity()` を非破壊化（move撤廃）  
3. `reskia_status_t` を導入し、無効ハンドル時は失敗を明示返却  
4. Rust側PoCで `Drop` / `Clone` / `Send`/`Sync` 条件を検証してAPIを固定
