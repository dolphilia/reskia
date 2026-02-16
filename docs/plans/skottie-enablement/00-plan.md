# 00 Plan: skottie（Lottie）有効化

作成日時: 2026-02-17 07:16:48 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.3 skottie（Lottie アニメーション）` を「未対応」から改善し、少なくとも以下を満たす。

- `skottie` 実装が `reskia` ビルドに組み込まれる
- 依存モジュール（`sksg`, `skresources`, `skshaper`, `skunicode`）とのリンクが再現可能な形で定義される
- 最小 C API から `skottie::Animation` の生成と描画呼び出しを実行できる
- configure/build と最小スモーク実行が成功する

## 再調査サマリ（2026-02-17）

1. 現在の `skia/modules` には `skottie` と `sksg` が存在しない（`skcms`, `skresources`, `svg` のみ）。
2. `vendor/skia-upstream/modules/skottie` と `vendor/skia-upstream/modules/sksg` には必要ソース一式が存在する。
3. upstream `modules/skottie/BUILD.gn` では `skottie` は `skresources`, `sksg`, `skshaper`, `skunicode` に依存する。
4. 現行 `skia/CMakeLists.txt` / `cmake/reskia/sources-*.cmake` に `skottie` / `sksg` 取り込み定義はない。
5. ベースライン確認として `cmake -S skia -B skia/cmake-build-skottie-survey -DRESKIA_DEPS_MODE=source -DRESKIA_BUILD_TESTS=OFF` と `cmake --build ... -j 8` は成功（`libreskia.dylib` 生成）。

## 現状ギャップ（着手前の事実）

1. `skottie` 本体と前提モジュール `sksg` がツリー未配置。
2. `reskia` には `skottie` を切り替える機能トグル（例: `RESKIA_ENABLE_SKOTTIE`）が未定義。
3. `SOURCE_FILES` / include path / compile definition に `SK_ENABLE_SKOTTIE` 相当の設定がない。
4. C binding 側に `skottie` 用 API（Animation 作成、seek、render、破棄）が未実装。
5. 実行確認用の Lottie スモークテストが未整備。

## 対象ファイル（主）

- `skia/modules/skottie/*`（upstream 同期）
- `skia/modules/sksg/*`（upstream 同期）
- `cmake/deps/ReskiaDeps.cmake`
- `skia/CMakeLists.txt`
- `cmake/reskia/sources-core.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/tests.cmake`
- `skia/capi/sk_skottie.{h,cpp}`（新規）
- `skia/capi/reskia_ffi.h`（必要に応じて公開面追加）
- `skia/test/test_skottie_smoke.cpp`（新規）

## 実施フェーズ

### Phase 1: モジュール同期と依存閉包固定

ステータス: 完了（2026-02-17 07:19:32 JST）

1. `vendor/skia-upstream/modules/sksg` と `vendor/skia-upstream/modules/skottie` を `skia/modules/` に同期する。
2. `BUILD.gn` / `*.gni` を参照し、CMake へ移植する最小ソース集合（公開ヘッダ含む）を確定する。
3. まずは CPU ラスタ経路の最小構成に限定し、tool/gm/fuzz/test 専用ソースは除外方針を明記する。

完了条件:
- `skia/modules/skottie` と `skia/modules/sksg` が再現可能な手順で同期されている。
- 取り込む/除外するソースの基準が文書化されている。

### Phase 2: CMake への段階導入

ステータス: 完了（2026-02-17 07:26:19 JST）

1. `RESKIA_ENABLE_SKOTTIE`（既定 `OFF`）を追加する。
2. `sources-core.cmake` に `sksg` と `skottie` ソースを条件付き追加する。
3. `skia/CMakeLists.txt` で `SK_ENABLE_SKOTTIE` をトグル有効時のみ定義する。
4. `skresources` / `svg(skshaper+skunicode)` 依存の解決条件を整理し、条件未充足時の configure エラーを明確化する。

完了条件:
- `RESKIA_ENABLE_SKOTTIE=OFF` では従来ビルドを維持。
- `RESKIA_ENABLE_SKOTTIE=ON` の configure が依存不足を明示し、依存充足時にリンクまで通る。

### Phase 3: C API 最小公開

ステータス: 完了（2026-02-17 07:32:34 JST）

1. `skia/capi/sk_skottie.h/.cpp` を追加し、最低限以下の API を提供する。
   - JSON から `Animation` 生成
   - 再生位置設定（seek）
   - `SkCanvas` への render
   - オブジェクト解放
2. 既存ハンドル設計と同じ所有権ルール（作成/破棄責務）を適用する。
3. 必要に応じて `reskia_ffi.h` にエントリを追加する。

完了条件:
- C 側から `skottie` の最小ライフサイクルを 1 経路で実行できる。

### Phase 4: ビルド行列と実行スモーク

ステータス: 完了（2026-02-17 07:36:26 JST）

1. 既定経路（`RESKIA_ENABLE_SKOTTIE=OFF`）で回帰確認。
2. 有効化経路（`RESKIA_ENABLE_SKOTTIE=ON`）で configure/build。
3. `test_skottie_smoke` を追加し、最小 Lottie JSON を読み込んで seek + render まで実行確認する。

実行例:
```bash
cmake -S skia -B skia/cmake-build-skottie-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_SKOTTIE=ON \
  -DRESKIA_BUILD_TESTS=ON
cmake --build skia/cmake-build-skottie-on -j 8
ctest --test-dir skia/cmake-build-skottie-on --output-on-failure
```

完了条件:
- `reskia` 本体ビルド成功。
- `test_skottie_smoke` が 0 exit。

### Phase 5: ドキュメント更新

ステータス: 完了（2026-02-17 07:38:20 JST）

1. 機能ギャップ調査 `3.3` の状態を更新する。
2. 依存条件、既定値、ON/OFF 時挙動、既知制約（GPU 非対象など）を `docs/notes` または `docs/guides` に反映する。

完了条件:
- `skottie` の有効化手順と制約が第三者に再現可能な形で記録される。

## 判定ゲート（途中判断）

1. `skottie` 導入で `sksg` 依存が大きく膨らむ場合:
- まず `sksg` 最小サブセットでリンクを通し、追加ノードは段階導入する。
2. C API 設計が肥大化する場合:
- 1st step は「再生・描画・破棄」の最小 API に限定する。
3. `RESKIA_DEPS_MODE=system/prebuilt` が不安定な場合:
- まず `source` モードを DoD にし、他モードは追補フェーズへ分離する。

## Definition of Done

1. `skottie` が `RESKIA_ENABLE_SKOTTIE=ON` でビルド可能。
2. `skottie` 依存（`sksg`, `skresources`, `skshaper`, `skunicode`）の結線が明示されている。
3. C API から最小 Lottie 再生経路（load/seek/render/destroy）が実行可能。
4. スモークテスト結果と有効化手順がドキュメント化されている。
