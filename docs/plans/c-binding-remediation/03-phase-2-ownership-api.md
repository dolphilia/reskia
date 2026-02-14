# 03 Phase 2: Ownership API Rework (`skia/binding`)

## ゴール

- 解放ルールを明文化し、`delete` と `ref/unref` の混在を解消する。
- Rust/LuaJIT両対応できる API 形に揃える。

## 方針

- RefCounted型:
  - `retain/release` を正規APIにする。
  - `*_delete(void*)` は非推奨化し内部で `release` に委譲。
- 非RefCounted型:
  - `create/destroy` を維持。
  - `borrow` 系 API は解放不要であることを命名で明示。

## 作業ステップ

1. 型分類表を作成
- RefCounted / NonRefCounted / Borrowed の3分類を定義。
- `checklists/binding-status.csv` に `phase=P2` を設定して管理。

2. 解放APIの統一
- `*_delete` 実装を順次修正:
  - RefCounted: `delete` 直呼びを廃止し `unref/release` 経由へ変更。
  - NonRefCounted: `delete` を維持。
- ヘッダコメントに所有権を明示:
  - `owned`, `borrowed`, `retained`.

3. `void*` APIの型情報補強
- 互換維持のため ABI は維持しつつ、型付き typedef を追加。
- 連番関数名（`_2`, `_3`）には `note` で置換予定名を記録。

4. IN/OUT引数規約の統一
- `out*` は必ず `reskia_status_t` 戻り値へ段階移行。
- NULL許容/非許容をコメントで統一記載。

5. フェーズ2検証

```bash
rg -n "delete static_cast<Sk.*>" skia/binding/*.cpp
rg -n "\\bref\\(|\\bunref\\(" skia/binding/*.cpp
cmake --build skia/cmake-build-local -j 8
```

## 完了条件

- RefCounted型で `delete static_cast<...>` がゼロ。
- 解放規約コメントが全公開ヘッダに記載済み。
- `checklists/binding-status.csv` の Phase 2 対象が `done`。
