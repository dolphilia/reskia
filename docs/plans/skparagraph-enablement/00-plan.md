# 00 Plan: skparagraph（高機能テキストレイアウト）有効化

作成日時: 2026-02-17 07:41:25 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.4 skparagraph` を未対応から改善し、以下を満たす。

- `skia/modules/skparagraph` を Reskia 側へ取り込み、CMake で条件付きビルド可能にする
- 依存条件（`skshaper` / `skunicode` / HarfBuzz / ICU 系）を明示し、縮退条件を整理する
- `reskia` 本体の configure/build を通し、最小の実行スモークを追加して実行可能性を確認する
- C API は段階導入とし、まずは C++ モジュール有効化を安定化させる

## 再調査サマリ（2026-02-17）

1. Reskia 側 `skia/modules` には `skparagraph` が存在しない（`skcms`, `skottie`, `skresources`, `sksg`, `svg` のみ）。
2. upstream 側 `vendor/skia-upstream/modules/skparagraph` には `include/` と `src/` が一式存在する。
3. upstream `modules/skparagraph/BUILD.gn` では `skparagraph` 有効条件が `skia_enable_skparagraph && skia_enable_skshaper && skia_enable_skunicode && skia_use_harfbuzz` となっている。
4. 既存 Reskia では `svg/CMakeLists.txt` に `svg -> skshaper -> skunicode` のリンクはあるが、`skparagraph` を組み込む CMake ターゲットは未定義。
5. `skia/CMakeLists.txt` と `cmake/deps/ReskiaDeps.cmake` に `RESKIA_ENABLE_SKPARAGRAPH` 相当のトグルは未実装。
6. `skia/capi` 側には paragraph API 群が未実装で、現時点の最短経路は「C++ モジュールの安定有効化 + 実行スモーク」である。

## 主要リスクと前提

- `skparagraph` は実質的に HarfBuzz + Unicode 実装（ICU / ICU4X / libgrapheme のいずれか）前提で、依存欠落時の扱いを先に決める必要がある。
- 既存の `RESKIA_DEPS_MODE`（`prebuilt`/`source`/`system`）ごとに依存供給が異なるため、最初は `source` モードを完了条件にする。
- C API まで同時実装すると工数と不確実性が増えるため、フェーズを分離する。

## 対象ファイル（予定）

- `skia/modules/skparagraph/**`（upstream から同期）
- `skia/CMakeLists.txt`
- `cmake/deps/ReskiaDeps.cmake`
- `svg/CMakeLists.txt`（`skparagraph` 連携用ターゲット整理時）
- `cmake/reskia/tests.cmake`
- `skia/test/*`（paragraph スモーク追加時）
- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`（反映時）

## 実施フェーズ

### Phase 1: モジュール同期と依存棚卸し

ステータス: 完了（2026-02-17 07:44:18 JST）

1. `vendor/skia-upstream/modules/skparagraph` から `skia/modules/skparagraph` へ最小差分で同期する。
2. `skparagraph.gni` を参照し、必要 source/header の一覧を CMake 向けに固定する。
3. `skparagraph` が参照する `skshaper` / `skunicode` / HarfBuzz / ICU 系の依存マップを整理する。

完了条件:
- `skia/modules/skparagraph` が配置され、ビルド対象候補ファイル一覧を説明できる。

### Phase 2: CMake 有効化（C++ モジュール）

ステータス: 完了（2026-02-17 07:50:21 JST）

1. `RESKIA_ENABLE_SKPARAGRAPH`（既定 `OFF`）を追加する。
2. `RESKIA_ENABLE_SKPARAGRAPH=ON` 時のみ `skparagraph` source を `reskia` に組み込む。
3. 必須依存が解決できない場合は configure 時に明確なエラーを出す。
4. `RESKIA_ENABLE_SKOTTIE` との共存時に include/link が破綻しないことを確認する。

完了条件:
- `ON/OFF` の切り替えで configure 挙動が一貫し、リンクエラーが再現しない。

### Phase 3: 最小実行スモーク整備

ステータス: 完了（2026-02-17 09:33:05 JST）

1. 段落生成（`ParagraphBuilder` -> `layout` -> `paint`）の最小テストを追加する。
2. UTF-8（ASCII + 日本語 + 改行）を含む入力でクラッシュしないことを確認する。
3. 依存がない環境ではテストを skip 可能にして CI 安定性を維持する。

完了条件:
- `ctest` で paragraph スモークが 0 exit（または依存不足時に明示 skip）になる。

### Phase 4: ビルド行列確認

ステータス: 完了（2026-02-17 09:40:08 JST）

1. 基本確認（既定 OFF）
```bash
cmake -S skia -B skia/cmake-build-skparagraph-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-skparagraph-off -j 8
ctest --test-dir skia/cmake-build-skparagraph-off --output-on-failure
```
2. 有効化確認（ON）
```bash
cmake -S skia -B skia/cmake-build-skparagraph-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKPARAGRAPH=ON \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-skparagraph-on -j 8
ctest --test-dir skia/cmake-build-skparagraph-on --output-on-failure
```
3. 必要に応じて `system` / `prebuilt` を追試し、未対応モードは制約として明文化する。

完了条件:
- `reskia` 本体のビルド成功と paragraph スモークの実行結果を記録できる。

### Phase 5: ドキュメント反映

ステータス: 完了（2026-02-17 09:41:06 JST）

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.4` を実装実態に更新する。
2. 有効化条件と縮退条件を `docs/plans/skparagraph-enablement/` に追記する。
3. 既知制約（例: 非 Apple / 依存未導入時）を明示する。

完了条件:
- 調査報告と実装状態が一致し、再現手順が文書化される。

## 判定ゲート

1. HarfBuzz 依存が満たせない場合:
- `RESKIA_ENABLE_SKPARAGRAPH` は `APPLE && source` のみ先行対応とし、他条件は `FATAL_ERROR` で早期停止する。
2. Unicode 実装（ICU/ICU4X/libgrapheme）が未整備の場合:
- 既存 `skunicode` 縮退実装で成立する範囲を限定し、テストを分岐する。
3. C API 導入工数が大きい場合:
- 本計画では見送り、別計画（Phase 2）として切り出す。

## Definition of Done

1. `skparagraph` が `RESKIA_ENABLE_SKPARAGRAPH` で条件付きビルド可能。
2. 依存不足時の失敗理由が configure ログで明確。
3. paragraph の最小実行スモークが追加され、実行結果が記録済み。
4. `docs/notes` の `3.4` 記述が実装実態に更新済み。
