# 依存管理方針 実施レポート（2026-02-14）

対象リポジトリ: `/Users/dolphilia/github/reskia`  
確認時刻: 2026-02-14 10:26:42 JST

## 1. 背景

従来は `skia/lib` に配置済みの静的/動的ライブラリを前提としていたため、別環境での再現性が低かった。  
この問題に対して、依存解決方式を選択可能にし、`third_party` を分離管理する最小実装を導入した。

## 2. 実施内容

### 2.1 依存解決モジュール追加

- 追加: `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake`
- 追加したモード:
  - `RESKIA_DEPS_MODE=prebuilt`（既定）
  - `RESKIA_DEPS_MODE=source`
  - `RESKIA_DEPS_MODE=system`

### 2.2 `skia/CMakeLists.txt` 統合

- 変更: `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- 変更点:
  - 依存解決を `ReskiaDeps.cmake` に委譲。
  - `prebuilt` 互換を維持しつつ、`source/system` を選択可能化。

### 2.3 `third_party` 分離管理

- 追加: `/Users/dolphilia/github/reskia/third_party/README.md`
- 追加: `/Users/dolphilia/github/reskia/third_party/CMakeLists.txt`
- 追加: `/Users/dolphilia/github/reskia/scripts/bootstrap_third_party.sh`
  - `third_party/src`, `third_party/build`, `third_party/install` を初期化。
- 変更: `/Users/dolphilia/github/reskia/.gitignore`
  - `third_party` 配下の管理ファイルのみ追跡し、生成物は追跡外。

## 3. 検証結果

### 3.1 `prebuilt`（既定）

実行:

```bash
cmake -S skia -B skia/cmake-build-codex -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-codex -j 8
```

結果:

- configure 成功
- build 成功（`Built target reskia`）

### 3.2 `source`

実行:

```bash
cmake -S skia -B skia/cmake-build-source-mode -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
```

結果:

- configure 失敗（想定内）
- 直接原因: `EXPATConfig.cmake` / `expat-config.cmake` が見つからない
- 意味: `third_party/install` への依存インストールが未完了のため

## 4. 制約と運用条件

- `source` は依存未配置時に configure 失敗する（フェイルファスト）。
- `source` の `WIN32` 分岐は未実装（明示 `FATAL_ERROR`）。
- `UNIX`（Apple 以外）は現状最小リンク（`skcms`）運用のまま。
- したがって、当面の安定運用は `prebuilt`、再現性強化は `source` へ段階移行する方針。

## 5. 次の実装候補

1. `third_party/src/*` を実体サブモジュール化し、コミット固定する。  
2. 依存ビルド（configure/build/install）を統合スクリプト化する。  
3. `source` で必要な `find_package` 設定（`CMAKE_PREFIX_PATH` 含む）を CI でも検証する。  
