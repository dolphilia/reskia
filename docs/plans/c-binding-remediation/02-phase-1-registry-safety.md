# 02 Phase 1: Registry Safety (`skia/static`)

## ゴール

- `static` レジストリを「壊れない状態」にする。
- 所有権破壊・無効キー黙殺・データ競合を先に止血する。

## 対象

- `skia/static/*.cpp`
- `skia/static/*-internal.h`（必要に応じてAPI分割）

## 作業ステップ

1. レジストリ共通ユーティリティ導入
- 追加: `skia/static/handle_table.hpp`（仮）
- 機能:
  - `find` ベース取得（`operator[]` 禁止）
  - `create/get_ptr/erase/contains`
  - `std::mutex` で排他
  - エラー時の戻り規約（`nullptr` or `false`）

2. `get_entity` の分離
- 既存 `get_entity` を以下に再編:
  - `borrow_entity`（非破壊）
  - `take_entity`（移譲が必要な型のみ）
- `sk_sp` / `unique_ptr` 型は既定で `borrow_entity` を使うよう移行。

3. 無効キー処理の統一
- `get_ptr/delete/set` すべて `find` で存在確認。
- 無効キー時:
  - 何もしない/`false` を返す/ログを返す方針を統一。

4. 世代付きハンドル導入（第一段）
- 既存 `int` を維持しつつ内部で generation を保持。
- stale handle 検出時の失敗経路を整備。

5. フェーズ1検証

```bash
rg -n "return std::move\\(static_.*\\[key\\]\\)" skia/static
rg -n "static_.*\\[key\\]" skia/static/*.cpp
rg -n "mutex|shared_mutex" skia/static
cmake --build skia/cmake-build-local -j 8
```

## 完了条件

- `skia/static` から `return std::move(static_*[key])` がゼロ。
- `skia/static/*.cpp` から `map[key]` パターンがゼロ。
- `checklists/static-status.csv` が Phase 1 対象で `done`。

## リスクと対策

- リスク: API互換破壊
- 対策: 旧関数名を thin wrapper として一時残す（内部は新実装）
