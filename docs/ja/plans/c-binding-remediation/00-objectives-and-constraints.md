# 00 Objectives and Constraints

## スコープ

- 対象ディレクトリ:
  - `skia/handles`
  - `skia/capi`
- バインディング対象:
  - `vendor/skia-upstream` の公開ヘッダにある Skia 公開 class/struct
  - 公開メソッド、static factory、static helper は可能な限り C ABI に露出する
  - 対象外にする場合は、platform dependency、optional module、ABI 安全性、所有権設計などの理由を checklist または文書に残す
- 非対象:
  - Skia本体アルゴリズム変更
  - レンダリング結果変更（API安全化に伴う副作用を除く）

## 主要課題（再掲）

1. `static_*_get_entity()` が move を返し所有権を破壊する。
2. `map[key]` による無効キー黙殺がある。
3. キー再利用に世代管理がなく stale handle を検出できない。
4. `delete` と `ref/unref` の混在で解放責務が曖昧。
5. Rust向け安全ラッパを作るには C ABI の所有権規約が不足。
6. Skia 公開 API 全体に対する C API coverage を method-level で追跡する必要がある。

## 受け入れ基準（最終）

- `SkRefCnt` 系の公開解放は `release` 統一（`delete` は非推奨または内部化）。
- `static` レジストリで `operator[]` を排除し、無効ハンドルが失敗として返る。
- ハンドルは世代付きで stale handle を検出できる。
- `capi/handles` の全対象ファイルが `checklists/*.csv` で `done`。
- Skia 公開 API の coverage は `checklists/public-api-coverage-matrix.csv` で把握し、未対応候補を `todo` / `done` / `na` / false positive として段階的に triage できる。
- Rust PoC が `Drop` / `Clone` / エラーハンドリングでクラッシュ無し。

## 制約

- 既存LuaJIT利用を即時破壊しない（段階移行）。
- API変更はフェーズ分割し、互換レイヤを一定期間維持。
- 一度に全置換しない。必ず「ビルド可能状態」を維持して進める。
