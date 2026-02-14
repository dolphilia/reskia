# 00 Objectives and Constraints

## スコープ

- 対象ディレクトリ:
  - `skia/static`
  - `skia/binding`
- 非対象:
  - Skia本体アルゴリズム変更
  - レンダリング結果変更（API安全化に伴う副作用を除く）

## 主要課題（再掲）

1. `static_*_get_entity()` が move を返し所有権を破壊する。
2. `map[key]` による無効キー黙殺がある。
3. キー再利用に世代管理がなく stale handle を検出できない。
4. `delete` と `ref/unref` の混在で解放責務が曖昧。
5. Rust向け安全ラッパを作るには C ABI の所有権規約が不足。

## 受け入れ基準（最終）

- `SkRefCnt` 系の公開解放は `release` 統一（`delete` は非推奨または内部化）。
- `static` レジストリで `operator[]` を排除し、無効ハンドルが失敗として返る。
- ハンドルは世代付きで stale handle を検出できる。
- `binding/static` の全対象ファイルが `checklists/*.csv` で `done`。
- Rust PoC が `Drop` / `Clone` / エラーハンドリングでクラッシュ無し。

## 制約

- 既存LuaJIT利用を即時破壊しない（段階移行）。
- API変更はフェーズ分割し、互換レイヤを一定期間維持。
- 一度に全置換しない。必ず「ビルド可能状態」を維持して進める。
