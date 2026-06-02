# 04 Phase 3: Dependency Matrix and Local Verification

## ゴール

`ReskiaDeps.cmake` の mode/platform 挙動を明文化し、ローカルで再現できる検証手順として維持する。

## 対象

- `cmake/deps/ReskiaDeps.cmake`

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

2. サポート表の明文化 ✅ 完了（2026-02-14）
- docsに mode/platform サポートマトリクスを追加:
  - macOS: prebuilt/source/system
  - Linux: prebuilt/source/system（実装差分明示）
  - Windows: prebuilt/system（source未実装なら明記）
  - 実施内容:
    - 本書に mode/platform サポートマトリクスを追加
    - Linux/Windows の実装差分を注記として明文化

## mode/platform サポートマトリクス（現状）

| Platform | prebuilt | source | system | 注記 |
|----------|----------|--------|--------|------|
| macOS (`APPLE`) | ✅ | ✅ | ✅ | `source`: `third_party/install` から `find_library` で解決。`system`: `EXPAT/PNG/JPEG` は `find_package`、`webp*` は `find_library`。 |
| Linux (`UNIX` かつ非 `APPLE`) | ✅ | ✅ | ✅ | 現状は3 mode とも外部画像系依存は未接続で、`skia/CMakeLists.txt` 側の `skcms` 最小リンク運用。 |
| Windows (`WIN32`) | ✅ | ❌ | ✅ | `source` は未実装で `FATAL_ERROR`。`system` は prebuilt 互換名で `skia/lib` を参照。 |

3. 依存モード検証最小行列 ✅ 完了（2026-02-14、2026-06-02 更新）
- `prebuilt` + `source` の configure をローカルで再現できるようにする。
- 失敗時に mode/platform を即特定できるコマンドを維持する。
  - 実施内容:
    - 当初は GitHub Actions workflow `.github/workflows/cmake-deps-matrix.yml` を追加していた。
    - 2026-06-02 に、Reskia の検証はローカル重視とし、`.github/` を削除した。
    - 今後は下記のローカル configure/build コマンドを標準検証として扱う。
  - ローカル検証結果:
    - `cmake -S skia -B skia/cmake-build-ci-prebuilt -DRESKIA_DEPS_MODE=prebuilt -DCMAKE_BUILD_TYPE=Release`: 成功
    - `cmake -S skia -B skia/cmake-build-ci-source -DRESKIA_DEPS_MODE=source -DCMAKE_BUILD_TYPE=Release`: 成功
    - `cmake --build skia/cmake-build-ci-prebuilt -j 8`: 成功（`Built target reskia`）

4. 回帰検証コマンド ✅ 完了（2026-02-14）

```bash
cmake -S skia -B skia/cmake-build-ci-prebuilt -DRESKIA_DEPS_MODE=prebuilt
cmake -S skia -B skia/cmake-build-ci-source -DRESKIA_DEPS_MODE=source
```

- 実行結果:
  - `cmake -S skia -B skia/cmake-build-ci-prebuilt -DRESKIA_DEPS_MODE=prebuilt`: 成功
  - `cmake -S skia -B skia/cmake-build-ci-source -DRESKIA_DEPS_MODE=source`: 成功

## 完了条件

- `ReskiaDeps.cmake` が mode別に追える構造
- サポート行列が docs に存在
- mode別 configure/build をローカルで再現できる

## 完了状況（2026-02-14、2026-06-02 更新）

- 作業ステップ 1: 完了
- 作業ステップ 2: 完了
- 作業ステップ 3: 完了。GitHub Actions workflow は 2026-06-02 に削除し、ローカル検証運用へ移行。
- 作業ステップ 4: 完了
