# 00 Plan: Reskia 安全化・安定化

作成日時: 2026-05-08 12:13:52 JST

## 背景

`docs/ja/notes/project-overview-and-next-tasks-2026-05-06.md` の「重要な制約とリスク」では、Reskia の今後のボトルネックは機能不足だけでなく、C API / handles の所有権、無効 handle、stale handle、スレッド安全性、テスト導線、platform 差分に移っていると整理されている。

再調査時点では、当初の `handles` 基盤リスクはかなり改善されている。

- `skia/handles/handle_table.hpp` に `std::mutex` と世代付き handle が導入済み。
- `docs/ja/plans/c-binding-remediation/checklists/static-handle-table-status.csv` は `done=105`, `na=2`。
- RefCounted release API は `docs/ja/plans/c-binding-remediation/checklists/phase2-release-api-status.csv` 上で 28/28 完了。
- `SkImage::imageInfo`、async read、`SkFont::getPaths` など一部の coverage gap は実装済み。

一方で、安定化の残課題はまだ大きい。

- `docs/ja/plans/c-binding-remediation/checklists/capi-status.csv` は `done=34`, `todo=276` で、C ABI 全体の品質レビューが未完了。
- `docs/ja/plans/c-binding-remediation/checklists/handles-status.csv` は `.cpp` / `*-internal.h` の Phase 1 は進んでいるが、公開 `.h` の進捗記録が未整理。
- borrowed pointer の寿命規約は実装に現れ始めているが、全 C API で一貫した文書化には至っていない。
- `RESKIA_BUILD_TESTS=ON` の CMake target build は、既存 test 構成の link issue により一部 smoke が `ctest` へ完全統合されていない。
- sanitizer 用の標準 configure/build/test 手順が未整備。
- GPU / optional codec / SkParagraph などは platform と依存条件が重く、失敗理由を分類しないと安定性評価が難しい。

## ゴール

1. C ABI 境界の所有権と lifetime を、型・関数単位で説明できる状態にする。
2. invalid input / invalid handle / stale handle が crash ではなく規約どおり失敗する状態を増やす。
3. `RESKIA_BUILD_TESTS=ON` + `ctest` を、最低限の CPU raster / C API smoke で常用できる状態にする。
4. ASan/UBSan を使った標準 smoke を追加し、メモリ破壊や未定義動作を早期検出する。
5. platform / dependency / feature flag の非対応条件を、明示的な configure error または documented unsupported に寄せる。
6. 新機能追加の前に、安定化タスクの優先順位と完了条件を共有できる状態にする。

## 非ゴール

- Skia 公開 API の完全網羅をこの計画だけで完了すること。
- GPU Graphite / Vulkan / Dawn / SkParagraph C API などの大きな機能追加を本計画の主タスクにすること。
- 既存 C API の ABI 互換を一括破壊すること。
- 言語別 wrapper を本リポジトリ内で実装・拡張すること。外部言語向けには C ABI と規約を提供する。

## 対象

- `skia/capi/`
- `skia/handles/`
- `skia/test/`
- `cmake/reskia/tests.cmake`
- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/*.cmake`
- `docs/ja/plans/c-binding-remediation/checklists/`
- `docs/ja/guides/`

## 実施フェーズ

### Phase 1: 現状チェックリストの整合化

目的: 進捗ファイルと実装状態のずれをなくし、安定化作業の入口を明確にする。

作業:

1. `static-handle-table-status.csv` と `handles-status.csv` の役割を再定義する。
2. `handles-status.csv` の公開 `.h` が `todo` のまま残っている理由を確認し、Phase 1 対象外なら `na` または別 phase へ移す。
3. `capi-status.csv` の `todo,P2` を、型別・リスク別に並べ替える。
4. `public-api-core-effects-missing-triage.csv` の `covered` / `na` / `real_gap` を最新実装に合わせて再確認する。
5. `scripts/generate_public_api_coverage.py` の再生成結果と人手 triage の関係を文書化する。

完了条件:

- `handles` の Phase 1 完了状況が、実装とチェックリストで矛盾しない。
- `capi-status.csv` の次バッチ候補が 5-10 ファイル単位で選べる。
- 機械生成 matrix と人手 triage の読み方が明文化されている。

検証候補:

```bash
rg -n "return std::move\\(static_.*\\[key\\]\\)" skia/handles
rg -n "static_.*\\[key\\]" skia/handles/*.cpp
python3 scripts/generate_public_api_coverage.py --repo /Users/dolphilia/github/reskia
```

### Phase 2: C API 高リスク型の安全化バッチ

目的: 利用頻度が高く、誤用時の影響が大きい型から C ABI 品質を上げる。

優先型:

1. `SkImage`
2. `SkSurface`
3. `SkCanvas`
4. `SkBitmap`
5. `SkPath`
6. `SkPaint`
7. `SkData` / stream 系
8. `SkFont` / `SkTypeface`

作業観点:

1. `void*` を不透明型 pointer または typed handle へ置換する。
2. borrowed / owned / retained / consumed のコメントをヘッダに追加する。
3. NULL 許容・非許容を関数ごとに明示する。
4. 失敗可能 API は、可能な範囲で `reskia_status_t + out parameter` へ寄せる。
5. callback API は callback 中だけ有効な pointer と、context 所有権を明記する。
6. `delete` / `release` / `unref` の混在箇所を `phase2-release-api-status.csv` の方針へ寄せる。
7. 互換維持が必要な旧 API は thin wrapper 化し、Phase 4 で deprecate する。

完了条件:

- 1 バッチごとに `capi-status.csv` の該当行が `done` または理由付き `na` になる。
- 各バッチで configure/build が成功する。
- invalid input の smoke が少なくとも 1 つ追加される。

検証候補:

```bash
cmake -S skia -B skia/cmake-build-stability-prebuilt -DCMAKE_BUILD_TYPE=Debug
cmake --build skia/cmake-build-stability-prebuilt -j 8
```

### Phase 3: borrowed pointer / handle lifetime 規約の固定

目的: `HandleTable::get_ptr()` や callback borrowed pointer の寿命を、C ABI 利用者が誤解しない形にする。

分類:

| 分類 | 意味 | 例 |
| --- | --- | --- |
| owned | caller が release/delete する | `*_new`, `*_retain` が返す pointer |
| retained | refcount を増やして caller 所有にする | `reskia_image_retain` |
| borrowed-handle | handle table 内 storage 生存中だけ有効 | `reskia_*_borrow_from_handle` |
| borrowed-parent | parent object 生存中だけ有効 | `SkSurface_getCanvas` |
| borrowed-callback | callback 実行中だけ有効 | `SkFont_getPaths` の path/matrix, async read result |
| consumed | callee が所有権を引き取る | `SkRasterHandleAllocator_MakeCanvas` の allocator |

作業:

1. `docs/ja/guides/` に C ABI ownership/lifetime guide を追加する。
2. `reskia_ffi.h` の borrowed bridge API に lifetime コメントを追加する。
3. callback 系 API の result / context / thread / reentrancy を個別に記録する。
4. handle delete 後の stale handle が `nullptr` / `false` / no-op になる smoke を追加する。

完了条件:

- C API 利用者が、返却 pointer を解放すべきか保持してよいかをヘッダまたは guide から判断できる。
- stale handle の最小回帰テストが存在する。

### Phase 4: `RESKIA_BUILD_TESTS=ON` の標準化

目的: smoke test を局所検証ではなく `ctest` で再現できる状態にする。

作業:

1. `test_c_skia` の役割を見直す。
   - 現行 API に追従して修正する。
   - 追従コストが高い場合は legacy target として分離する。
2. Phase C/D smoke が `cmake --build --target ...` で link 失敗しないように依存を修正する。
3. CPU raster の基本 smoke セットを定義する。
4. optional feature smoke は `ctest -R` で個別実行できるように維持する。
5. docs に標準検証コマンドを追加する。

標準 smoke 候補:

- `c_skia_codec_smoke`
- `c_skia_phase_c_callback_smoke`
- `c_skia_phase_d_async_read_smoke`
- `c_skia_pdf_smoke`（`RESKIA_ENABLE_PDF=ON`）
- `c_skia_sksg_smoke` / `c_skia_sksg_capi_smoke`（`RESKIA_ENABLE_SKSG=ON`）
- `c_skia_gpu_*`（GPU 有効時のみ）

完了条件:

- 既定機能の `RESKIA_BUILD_TESTS=ON` configure/build が成功する。
- CPU raster の smoke が `ctest --output-on-failure` で成功する。
- optional smoke は依存不足時に未登録または明確な skip/unsupported として扱われる。

検証候補:

```bash
cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-stability-tests -j 8
ctest --test-dir skia/cmake-build-stability-tests --output-on-failure
```

### Phase 5: sanitizer smoke の導入

目的: C ABI 境界のメモリ破壊、use-after-free、未定義動作を早期に検出する。

作業:

1. ASan/UBSan 用 configure コマンドを docs に定義する。
2. 必要なら CMake option として `RESKIA_ENABLE_SANITIZERS` または preset 相当を追加する。
3. まず CPU raster + C API smoke のみに適用する。
4. TSan は handle table 周辺の小さい smoke から試す。
5. sanitizer で既知 false positive が出る場合は、Skia 側由来か Reskia 側由来かを分類する。

初期対象:

- handle create/delete/stale handle smoke
- `Paint` / `Path` clone/drop stress
- raster `Surface` snapshot + `Image` retain/release
- async read callback result の callback 外保持禁止を破らない smoke

完了条件:

- ASan/UBSan の configure/build/test 手順が再現可能。
- 少なくとも CPU raster smoke が sanitizer 構成で成功する。
- sanitizer 失敗は issue 化または docs に既知制約として残る。

### Phase 6: platform / dependency / feature flag の失敗条件整理

目的: platform 差と optional dependency による不安定さを、暗黙失敗から明示的な運用ルールへ変える。

作業:

1. `prebuilt` / `source` / `system` と `APPLE` / `UNIX` / `WIN32` の実サポート表を更新する。
2. `RESKIA_ENABLE_*` feature flag の依存条件を一覧化する。
3. 未対応構成は `FATAL_ERROR`、未登録、または documented unsupported のどれにするか決める。
4. GPU は `GANESH+METAL` を安定候補、Graphite/Vulkan/Dawn を experimental として分ける。
5. SkParagraph は C++ smoke 済みと C API 未実装の境界を明記する。

完了条件:

- configure 失敗時に「依存不足」「platform 未対応」「実装未完了」の区別がつく。
- README または guide から、安定サポート対象と experimental 対象が読める。

### Phase 7: 外部 FFI 利用を想定した C API 回帰強化

目的: C ABI 安全化の成果を、外部の言語別 wrapper から利用しても破綻しにくい形で固定する。

作業:

1. invalid handle / stale handle / null return の C API smoke を増やす。
2. retain / release / borrowed pointer の lifetime comment を C guide と揃える。
3. retain 成功後に元 handle を削除しても caller-owned pointer が安全に使えることを確認する。
4. borrowed pointer は owner / handle storage 生存前提であることを header と guide に明示し続ける。
5. 外部 wrapper が参照できる C API smoke と最小 C example を維持する。

完了条件:

- C API smoke が所有権規約をカバーする。
- C 側の lifetime guide と header comment が矛盾しない。

## 優先順位

### P0

- `RESKIA_BUILD_TESTS=ON` の smoke 経路修復。
- `capi-status.csv` の高リスク型バッチ開始。
- borrowed / owned / retained / consumed 規約の guide 化。

### P1

- ASan/UBSan smoke の標準化。
- stale handle / invalid handle の C++ smoke 追加。
- platform / feature flag matrix の更新。

### P2

- 外部 FFI 利用を想定した C API 回帰テスト拡張。
- `system` / 非 Apple Unix / Windows の unsupported 条件整理。
- public API coverage の追加 triage。

## 判定ゲート

1. C ABI 変更が ABI 互換を壊す場合:
   - 旧関数を thin wrapper として残し、新関数を typed/status API として追加する。
2. smoke 修復が `test_c_skia` の大改修を必要とする場合:
   - 先に `test_c_skia` を legacy 分離し、新 smoke を独立 target として通す。
3. sanitizer が Skia 内部由来の大量 failure を出す場合:
   - Reskia C API smoke に対象を絞り、known issue として分類する。
4. optional dependency の検証が再現しにくい場合:
   - stable matrix から外し、experimental matrix として別管理する。

## Definition of Done

1. 既定構成で `reskia` が configure/build 成功する。
2. 既定構成 + `RESKIA_BUILD_TESTS=ON` で CPU raster / C API smoke が `ctest` 成功する。
3. ASan/UBSan 構成で最小 smoke が成功する。
4. C API の主要型について、所有権・NULL・borrowed lifetime がヘッダまたは guide に明記される。
5. `capi-status.csv` の高リスク型バッチが `done` または理由付き `na` で閉じる。
6. platform / dependency / feature flag の安定サポート範囲と experimental 範囲が文書化される。
