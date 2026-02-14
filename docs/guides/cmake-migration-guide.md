# CMake 移行ガイド（Phase 4）

更新日: 2026-02-14

## 目的

`RESKIA_DEPS_MODE` 導入前の運用から、新運用へ移行するための標準手順を一本化する。

## 旧手順と新手順の差分

| 観点 | 旧手順 | 新手順 |
|------|--------|--------|
| 依存解決 | `skia/lib` 前提（実質固定） | `RESKIA_DEPS_MODE=prebuilt/source/system` を明示選択 |
| 初期化 | 個別に手作業 | `source` は `scripts/bootstrap_third_party.sh` を先に実行 |
| 依存ビルド | 手動・環境依存 | `source` は `scripts/build_third_party.sh` で統一 |
| configure 失敗時の切り分け | 原因が分散 | mode 単位で原因を切り分け可能 |

## 標準手順（モード別）

以下はリポジトリルート（`/Users/dolphilia/github/reskia`）で実行する。

### 1. `prebuilt`（既定・最短）

```bash
cmake -S skia -B skia/cmake-build-prebuilt -DRESKIA_DEPS_MODE=prebuilt -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-prebuilt -j 8
```

- 想定用途: 既存 `skia/lib` 前提で素早くビルド確認したい場合。

### 2. `source`（再現性重視）

```bash
scripts/bootstrap_third_party.sh
scripts/build_third_party.sh --build-type Release --clean
cmake -S skia -B skia/cmake-build-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-source -j 8
```

- 想定用途: 依存の構築手順を含めて再現したい場合。
- 追加オプション:
  - AVIF: `scripts/build_third_party.sh --with-avif` + `-DRESKIA_ENABLE_AVIF=ON`
  - ICU/ICU4X: `scripts/build_third_party.sh --with-icu --with-icu4x`

### 3. `system`（OS導入済み依存を利用）

```bash
cmake -S skia -B skia/cmake-build-system -DRESKIA_DEPS_MODE=system -DCMAKE_BUILD_TYPE=Release
cmake --build skia/cmake-build-system -j 8
```

- 想定用途: システム側パッケージ管理と連携したい場合。
- 必要に応じて `CMAKE_PREFIX_PATH` 等を指定する。

## 移行チェックリスト

1. CI/ローカルで使う mode（`prebuilt/source/system`）を明示した。
2. `source` 利用時は `bootstrap/build_third_party` を手順化した。
3. README や運用メモから「mode 未指定」の configure 例を削減した。
4. 障害報告時に `RESKIA_DEPS_MODE` と configure コマンドを必ず添付する。

## 関連ドキュメント

- `/Users/dolphilia/github/reskia/README.md`
- `/Users/dolphilia/github/reskia/third_party/README.md`
- `/Users/dolphilia/github/reskia/docs/plans/cmake-remediation/05-phase-4-rollout-and-deprecation.md`
