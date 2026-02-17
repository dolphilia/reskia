# 00 Plan: sksg（Scene Graph）有効化

作成日時: 2026-02-17 09:46:26 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.5 sksg（Scene Graph）` を「skottie 依存の同梱」から前進させ、少なくとも以下を満たす。

1. `sksg` を `skottie` 非依存でも明示的にビルド対象へ組み込める。
2. `sksg` の最小実行経路（Scene 構築 + render 呼び出し）を再現可能にする。
3. configure/build/test の検証手順を文書化し、回帰確認可能にする。

## 再調査サマリ（2026-02-17）

1. `skia/modules/sksg` はローカルに同期済みで、`src/` / `include/` 一式が存在する。
2. 現行の `cmake/reskia/sources-core.cmake` は `RESKIA_ENABLE_SKOTTIE=ON` 時のみ `modules/sksg/sksg.gni` を読み込み、`SOURCE_FILES` に `sksg` を追加する。
3. `sksg` 単独トグル（例: `RESKIA_ENABLE_SKSG`）は未実装で、`skottie` を有効化しないと `sksg` はビルドに入らない。
4. C API には `SkSG*` 公開がなく、`sksg` 直接利用経路は未提供。
5. 実行確認は `skottie` 経由のみ可能。実測として `test_skottie_smoke` 単体ビルドと `ctest -R c_skia_skottie_smoke` は成功。

## 現状ギャップ（sksg観点）

1. `sksg` 単体有効化スイッチがないため、機能検証が `skottie` の成否に従属している。
2. `sksg` 専用スモークがなく、`sksg` 回帰の検知粒度が粗い。
3. 直接 C API がないため、外部利用者が `Scene Graph` を明示的に扱えない。

## 対象ファイル（予定）

- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-core.cmake`
- `skia/CMakeLists.txt`
- `cmake/reskia/tests.cmake`
- `skia/capi/sk_sksg.{h,cpp}`（新規、最小公開を行う場合）
- `skia/capi/reskia_ffi.h`（必要時）
- `skia/test/test_sksg_smoke.cpp`（新規）
- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`

## 実施フェーズ

### Phase 1: CMake 経路分離（sksg 単独トグル）

ステータス: 完了（2026-02-17 09:52 JST）

1. `RESKIA_ENABLE_SKSG`（既定 `OFF`）を追加する。
2. `sources-core.cmake` の `sksg` 取り込みを `RESKIA_ENABLE_SKSG OR RESKIA_ENABLE_SKOTTIE` で有効化する。
3. `skottie` 由来ソースは `RESKIA_ENABLE_SKOTTIE` のまま維持し、`sksg` と `skottie` の追加条件を分離する。

完了条件:
- `RESKIA_ENABLE_SKSG=ON, RESKIA_ENABLE_SKOTTIE=OFF` で `modules/sksg/src/*.cpp` がコンパイルされる。

### Phase 2: 最小実行スモーク（C++）

ステータス: 完了（2026-02-17 09:55 JST）

1. `test_sksg_smoke.cpp` を追加し、`sksg::Scene` と最小ノード（例: `Group` + `Rect`）を構築して `SkCanvas` に描画する。
2. `tests.cmake` に `RESKIA_ENABLE_SKSG` 条件でテスト登録を追加する。
3. `ctest -R c_skia_sksg_smoke` を CI/ローカルの回帰軸として定義する。

完了条件:
- `c_skia_sksg_smoke` が 0 exit で通る。

### Phase 3: C API 最小公開（必要性を評価して実施）

ステータス: 完了（2026-02-17 10:00 JST）

1. `sk_sksg.h/.cpp` を追加し、最小の作成/描画/破棄 API を公開する。
2. 初期スコープは「Scene 所有・1種類の図形ノード・render」に限定する。
3. ハンドル所有権を既存 C API（new/delete または ref/unref）と整合させる。

完了条件:
- C 側から `sksg` 最小ライフサイクルを 1 経路で実行可能。

### Phase 4: 検証マトリクス整理

ステータス: 完了（2026-02-17 10:06 JST）

1. 既定経路: `RESKIA_ENABLE_SKSG=OFF` の回帰ビルドを確認する。
2. 有効化経路: `RESKIA_ENABLE_SKSG=ON` で configure/build/test を実施する。
3. 併用経路: `RESKIA_ENABLE_SKSG=ON` + `RESKIA_ENABLE_SKOTTIE=ON` で二重取り込みや定義衝突がないことを確認する。

完了条件:
- OFF/ON/併用の3経路で configure/build が再現可能。

### Phase 5: ドキュメント更新

ステータス: 完了（2026-02-17 10:07:56 JST）

1. `reskia-feature-gap-survey` の `3.5 sksg` を最新状態へ更新する。
2. 有効化手順・制約・既知課題（Apple限定条件の有無、依存モジュール）を記載する。

完了条件:
- 第三者が手順を追って `sksg` ビルド・実行確認を再現できる。

## 検証コマンド（案）

```bash
cmake -S skia -B skia/cmake-build-sksg-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON \
  -DRESKIA_ENABLE_SKSG=ON
cmake --build skia/cmake-build-sksg-on -j 8 --target test_sksg_smoke
ctest --test-dir skia/cmake-build-sksg-on -R c_skia_sksg_smoke --output-on-failure
```

## Definition of Done

1. `sksg` が `skottie` 非依存で有効化可能。
2. `sksg` 専用スモークで実行確認ができる。
3. 必要なら最小 C API が公開される（スコープ明示つき）。
4. 調査メモと有効化手順が更新され、運用可能な状態になる。
