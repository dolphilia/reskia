# 04 Phase 3: Dependency Matrix and CI

## ゴール

`ReskiaDeps.cmake` の mode/platform 挙動を明文化し、CIで継続検証する。

## 対象

- `cmake/deps/ReskiaDeps.cmake`
- （必要に応じて）CI設定ファイル

## 作業ステップ

1. 依存解決関数の整理 ✅ 完了（2026-02-14）
- `prebuilt/source/system` を関数分離し、読みやすくする。
- OS分岐を表形式コメントで明示。
  - 実施内容:
    - `cmake/deps/ReskiaDeps.cmake` に mode別関数を追加:
      - `_reskia_resolve_mode_prebuilt(...)`
      - `_reskia_resolve_mode_source(...)`
      - `_reskia_resolve_mode_system(...)`
    - 既存エントリ `reskia_resolve_third_party(...)` は mode検証とディスパッチを担当する構成に変更
    - modeごとに `WIN32/APPLE/UNIX` の挙動を表形式コメントで明示
  - 検証結果:
    - `cmake -S skia -B skia/cmake-build-phase3-prebuilt -DRESKIA_DEPS_MODE=prebuilt -DCMAKE_BUILD_TYPE=Debug`: 成功
    - `cmake -S skia -B skia/cmake-build-phase3-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功
    - `cmake --build skia/cmake-build-phase3-prebuilt -j 8`: 成功（`Built target reskia`）

2. サポート表の明文化
- docsに mode/platform サポートマトリクスを追加:
  - macOS: prebuilt/source/system
  - Linux: prebuilt/source/system（実装差分明示）
  - Windows: prebuilt/system（source未実装なら明記）

3. CI検証最小行列
- `prebuilt` + `source` の configure を自動実行。
- 失敗時に mode/platform を即特定できるログ出力にする。

4. 回帰検証コマンド

```bash
cmake -S skia -B skia/cmake-build-ci-prebuilt -DRESKIA_DEPS_MODE=prebuilt
cmake -S skia -B skia/cmake-build-ci-source -DRESKIA_DEPS_MODE=source
```

## 完了条件

- `ReskiaDeps.cmake` が mode別に追える構造
- サポート行列が docs に存在
- CIで mode別 configure が常時走る
