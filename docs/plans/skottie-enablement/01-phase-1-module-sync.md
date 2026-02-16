# 01 Phase 1: modules/sksg・modules/skottie 同期

更新日時: 2026-02-17 07:19:32 JST

## 実施内容

1. `vendor/skia-upstream/modules/sksg` を `skia/modules/sksg` へ同期。
2. `vendor/skia-upstream/modules/skottie` を `skia/modules/skottie` へ同期。
3. `BUILD.gn` / `*.gni` を根拠に、Phase 2 で CMake へ移植する初期対象ファイルのマニフェストを作成。

実行コマンド:

```bash
rsync -a vendor/skia-upstream/modules/sksg/ skia/modules/sksg/
rsync -a vendor/skia-upstream/modules/skottie/ skia/modules/skottie/
```

## 成果物（マニフェスト）

- `docs/plans/skottie-enablement/manifests/upstream-sksg-files.txt`
- `docs/plans/skottie-enablement/manifests/local-sksg-files.txt`
- `docs/plans/skottie-enablement/manifests/upstream-skottie-files.txt`
- `docs/plans/skottie-enablement/manifests/local-skottie-files.txt`
- `docs/plans/skottie-enablement/manifests/phase1-selected-module-files.txt`

## 同期結果

1. ファイル件数一致:
- `sksg`: upstream 57 / local 57
- `skottie`: upstream 127 / local 127

2. `rsync -ain --delete` に差分なし:
- `vendor/skia-upstream/modules/sksg` -> `skia/modules/sksg`
- `vendor/skia-upstream/modules/skottie` -> `skia/modules/skottie`

## Phase 1 判定（初期取り込みポリシー）

1. 初期移植対象は `modules/sksg/sksg.gni` と `modules/skottie/skottie.gni` の公開ヘッダ/本体ソースに合わせる。
2. 初期段階では以下を CMake 対象から除外する。
- `tests/`（単体テスト専用）
- `gm/`（GM 専用）
- `fuzz/`（fuzz 専用）
- `utils/`（補助ツール系）
- `src/SkottieTool.cpp`（スタンドアロンツール）
- `src/SkottieTest.cpp`（テスト専用）

3. `phase1-selected-module-files.txt` は上記方針で `*.gni` から抽出した 122 ファイルを保持する。

## Phase 2 への引き継ぎ

1. `RESKIA_ENABLE_SKOTTIE` トグルを追加する。
2. `sources-core.cmake` へ `phase1-selected-module-files.txt` ベースで `sksg` / `skottie` ソースを条件付き追加する。
3. `skia/CMakeLists.txt` で `SK_ENABLE_SKOTTIE` をトグル有効時のみ定義する。
4. `skresources` / `svg(skshaper+skunicode)` 依存が未解決の場合は configure で明示的に停止する。
