# 00 Plan: GPU（Ganesh/Graphite）有効化と C API 公開

作成日時: 2026-02-17 10:10:21 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.6 GPU（Ganesh/Graphite、Vulkan/Metal/Dawn）` を再調査し、Reskia で GPU バックエンドを段階的に有効化しつつ、C API から利用できる状態にする。

- `RESKIA_ENABLE_GPU_GANESH` / `RESKIA_ENABLE_GPU_GRAPHITE` の機能トグルを定義する
- プラットフォーム別バックエンド（Vulkan/Metal/Dawn）の有効化条件を CMake へ反映する
- C API で `GrDirectContext`（Ganesh）と Graphite の最小利用経路を提供する
- configure/build と最小スモークを通し、依存不足時の挙動を明文化する

## 再調査サマリ（2026-02-17）

1. `vendor/skia-upstream/src/gpu` には `ganesh` / `graphite` / `vk` / `mtl` / `dawn` 実装が存在する。
2. 現行 `cmake/reskia/sources-core.cmake` には `src/gpu/*` の組み込み定義がなく、GPU 実装は実質未結線。
3. C API は `reskia_direct_context_t` / `reskia_graphite_recorder_t` を引数に取る API があるが、コンテキスト生成 API が不足している。
4. 既存機能（`SkImage_*`, `Sk*Encoder_*` など）に GPU 文脈引数があるため、生成 API を追加すれば既存公開面の実利用が進む余地が大きい。

## 対象ファイル（主）

- `cmake/deps/ReskiaDeps.cmake`
- `skia/CMakeLists.txt`
- `cmake/reskia/sources-core.cmake`
- `cmake/reskia/sources-capi.cmake`
- `skia/capi/reskia_ffi.h`
- `skia/capi/sk_*.{h,cpp}`（GPU 用新規ラッパ）
- `skia/test/test_gpu_*.cpp`（新規スモーク）
- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`

## 実施フェーズ

### Phase 1: GPU 実装差分の棚卸しと導入順序確定

1. upstream の `src/gpu/ganesh`, `src/gpu/graphite`, `src/gpu/{vk,mtl,dawn}` を参照し、Reskia 側未導入分をマニフェスト化する。
2. 依存を「共通 GPU 基盤」「Ganesh 固有」「Graphite 固有」「Backend 固有」に分割する。
3. 導入順序を以下で確定する。
- Step A: Ganesh + Metal(macOS) / Vulkan(非Apple)
- Step B: Graphite（まず recorder/surface 最小）
- Step C: Dawn（任意依存として後段）

完了条件:
- 導入対象ソース一覧と除外理由が文書化されている。
- 各バックエンドの前提依存（SDK/loader/ヘッダ）が確定している。

### Phase 2: CMake トグルとソース結線（CPU 既定維持）

1. `RESKIA_ENABLE_GPU_GANESH` / `RESKIA_ENABLE_GPU_GRAPHITE`（既定 `OFF`）を追加する。
2. `RESKIA_ENABLE_GPU_VULKAN` / `RESKIA_ENABLE_GPU_METAL` / `RESKIA_ENABLE_GPU_DAWN` を追加し、プラットフォーム条件を持たせる。
3. `sources-core.cmake` を GPU ソース群で分割管理し、ON 時のみ `SOURCE_FILES` へ追加する。
4. `SK_GANESH` / `SK_GRAPHITE` / `SK_VULKAN` / `SK_METAL` / `SK_DAWN` の compile definition をトグルと連動させる。

完了条件:
- 既定（すべて OFF）で従来ビルドが維持される。
- 少なくとも 1 経路（例: macOS + Ganesh + Metal）でリンクまで通る。

### Phase 3: C API 最小公開（コンテキスト生成・破棄）

1. Ganesh 用 C API を追加する。
- `GrDirectContext` 作成（Metal/Vulkan 別エントリ）
- flush/submit/abandon/解放
2. Graphite 用 C API を追加する。
- `Context` / `Recorder` の生成と破棄
- 必要最小の submit/同期 API
3. 既存 `reskia_direct_context_t` / `reskia_graphite_recorder_t` と所有権規約（borrowed/owned）をヘッダコメントで明確化する。

完了条件:
- C 側から GPU コンテキストを生成し、既存 `SkImage_*` 系 API に受け渡せる。

### Phase 4: Surface/Texture 最小経路の公開

1. Ganesh で RenderTarget/BackendTexture から `SkSurface` を作る最小 API を追加する。
2. Graphite で Recorder ベースの描画ターゲット作成 API を追加する（可能なら backend texture 経路も検証）。
3. Vulkan/Metal の backend handle 受け渡し型を C ABI でラップし、プラットフォーム分岐を隠蔽する。

完了条件:
- GPU Surface を生成し、draw + flush までの最小経路が C API で成立する。

### Phase 5: 検証行列（configure/build/smoke）

1. 最低限の build 行列を定義し、各構成で configure/build を実施する。
- macOS: `GANESH+METAL=ON`
- 非Apple（可能環境）: `GANESH+VULKAN=ON`
- 任意: `GRAPHITE=ON`（backend は Metal/Vulkan いずれか）
- 任意: `DAWN=ON`
2. スモークテストを追加する。
- context 生成/破棄
- surface 作成 + clear/draw + flush
- encode/readback の 1 経路
3. 失敗時は「依存不足」か「実装欠落」かを分類して記録する。

完了条件:
- 主要 1 構成以上で GPU スモーク成功。
- 他構成は失敗理由が再現可能な形で記録される。

### Phase 6: ドキュメント更新と公開方針確定

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.6` を進捗に合わせて更新する。
2. `docs/plans/gpu-enablement/` に backend 別の詳細メモ（依存、制約、未対応）を追記する。
3. C API の安定化ポリシー（experimental/preview/stable）を定義する。

完了条件:
- GPU 有効化手順、依存条件、C API のサポート範囲が第三者に再現可能な形で残る。

## 判定ゲート（途中判断）

1. Graphite の導入コストが大きい場合:
- まず Ganesh + Metal/Vulkan を先行完了し、Graphite は別マイルストーンへ分離する。
2. Dawn 依存が重く CI 再現性が低い場合:
- `RESKIA_ENABLE_GPU_DAWN` は experimental のまま既定 OFF を維持する。
3. C API が backend 詳細に引きずられる場合:
- 共通抽象（context/surface/sync）を優先し、backend 固有 API は拡張ヘッダへ隔離する。

## Definition of Done

1. GPU 有効化トグル（Ganesh/Graphite/Vulkan/Metal/Dawn）が CMake で機能する。
2. 少なくとも 1 backend で `reskia` が GPU 有効ビルド成功する。
3. C API で GPU コンテキスト生成と最小描画経路（surface + flush）が利用可能。
4. 3.6 の調査結果と制約、再現手順がドキュメント化される。
