# 05 Phase 4: Migration and Cleanup

## ゴール

- 新規約への移行完了後、命名/互換層/ドキュメントを整理する。

## 作業ステップ

1. [x] ディレクトリ命名の移行
- `skia/static` -> `skia/handles`
- `skia/binding` -> `skia/capi`
- 実施内容（2026-02-16）:
  - ディレクトリ本体を移動（`skia/capi`, `skia/handles`）。
  - `#include` / CMakeソース列挙 / テスト / ドキュメント参照を新パスへ更新。
  - 管理ファイル名を新命名へ統一:
    - `manifests/binding-files.txt` -> `manifests/capi-files.txt`
    - `manifests/static-files.txt` -> `manifests/handles-files.txt`
    - `checklists/binding-status.csv` -> `checklists/capi-status.csv`
    - `checklists/static-status.csv` -> `checklists/handles-status.csv`
  - `cmake/reskia/` のソース定義ファイル名も新命名へ統一:
    - `sources-binding.cmake` -> `sources-capi.cmake`
    - `sources-static.cmake` -> `sources-handles.cmake`

1. [ ] 旧API廃止計画
- `*_delete`（RefCounted対象）を `deprecated` マクロ化
- 2リリース後に削除予定としてマイルストーン化

1. [ ] 連番関数名の整理
- `_2/_3/_4` 形式を意味名へ置換
- 旧名は互換ラッパで段階削除

1. [ ] 自動生成の導入（任意だが推奨）
- 型定義から header/cpp を生成
- 手編集面積を縮小し、Skia追従の保守コストを下げる

1. [ ] 最終検証

```bash
cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-local -j 8
ctest --test-dir skia/cmake-build-local --output-on-failure
```

## 完了条件

- `checklists/capi-status.csv` / `checklists/handles-status.csv` が全件 `done` または `na`。
- `docs/guides/repository-structure.md` と `README.md` の名称・手順が新構成に一致。
- 既存利用者向け移行ガイドを公開済み。
