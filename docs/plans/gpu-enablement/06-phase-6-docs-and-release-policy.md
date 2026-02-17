# 06 Phase 6: ドキュメント更新と公開ポリシー

更新日時: 2026-02-17 14:08:26 JST

## 目的

GPU 対応状況を第三者が追跡可能な状態にし、C API の公開レベルを明文化する。

## 作業項目

1. `docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.6` を進捗に合わせて更新する。
2. `docs/plans/gpu-enablement/` に backend 別制約・依存条件・既知課題を追記する。
3. API 公開レベルを定義する。
- `experimental`: 互換性保証なし
- `preview`: 破壊変更の可能性あり
- `stable`: 互換性維持対象
4. リリースノート向けに「有効化フラグ」「サポートバックエンド」「既知制約」を整理する。

## 更新対象ファイル

- `docs/notes/reskia-feature-gap-survey-2026-02-14.md`
- `docs/plans/gpu-enablement/*.md`
- 必要に応じて `docs/` 配下のガイド

## 判定基準

1. GPU 有効化手順がコマンド付きで再現可能。
2. backend ごとのサポート範囲と未対応事項が明記されている。
3. C API の安定性レベルが利用者に伝わる。

## 引き継ぎメモ

1. CI へ GPU 構成を追加する場合は、まず 1 backend を常設し段階拡張する。
2. Dawn は experimental 扱いで運用し、安定後に preview/stable へ昇格判定する。

## Phase 6 具体化（実装反映済み）

### 1. Graphite 生成物同期手順（`sksl_graphite_*`）

`RESKIA_ENABLE_GPU_GRAPHITE=ON` 時に以下 2 ファイルを必須とする。

- `skia/src/sksl/generated/sksl_graphite_frag.minified.sksl`
- `skia/src/sksl/generated/sksl_graphite_vert.minified.sksl`

同期手順（ベースコミット `0d49b661d75adbb8ac8cf88f7d527b1587be2c63` 相当）:

```bash
cp /Users/dolphilia/github/reskia/vendor/skia-upstream/src/sksl/generated/sksl_graphite_frag.minified.sksl \
   /Users/dolphilia/github/reskia/skia/src/sksl/generated/
cp /Users/dolphilia/github/reskia/vendor/skia-upstream/src/sksl/generated/sksl_graphite_vert.minified.sksl \
   /Users/dolphilia/github/reskia/skia/src/sksl/generated/
```

反映ポリシー:

1. `skia/CMakeLists.txt` で `RESKIA_ENABLE_GPU_GRAPHITE=ON` 時に存在チェックし、不足時は configure で `FATAL_ERROR`。
2. エラー文言に不足ファイル名を列挙し、同期元（`vendor/skia-upstream/src/sksl/generated`）を明示する。

### 2. Vulkan VMA 依存（`vk_mem_alloc.h`）の CMake 手順

Vulkan 有効時 (`RESKIA_ENABLE_GPU_VULKAN=ON`) は VMA ヘッダを必須にする。

追加した CMake 仕様:

1. `RESKIA_VMA_INCLUDE_DIR`（cache PATH）を導入。
2. 未指定時は次の候補で `find_path(vk_mem_alloc.h)` を実施。
- `${RESKIA_ROOT_DIR}/third_party/src/vulkanmemoryallocator/include`
- `${RESKIA_ROOT_DIR}/third_party/install/include`
- `${RESKIA_THIRD_PARTY_PREFIX}/include`
3. 未検出なら configure を `FATAL_ERROR`。
4. 検出後は `target_include_directories(reskia PRIVATE "${RESKIA_VMA_INCLUDE_DIR}")` を追加。
5. Vulkan 有効時 compile definition に `SK_USE_VMA` を追加。

利用例:

```bash
cmake -S skia -B skia/cmake-build-vulkan \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_GPU_GANESH=ON \
  -DRESKIA_ENABLE_GPU_VULKAN=ON \
  -DRESKIA_VMA_INCLUDE_DIR=/absolute/path/to/VulkanMemoryAllocator/include
```

### 3. Dawn 導入テンプレート（include/lib 指定）

Dawn は `RESKIA_ENABLE_GPU_DAWN=ON` かつ `RESKIA_ENABLE_GPU_GRAPHITE=ON` を前提とし、以下 2 変数を必須で扱う。

- `RESKIA_DAWN_INCLUDE_DIR`
- `RESKIA_DAWN_LIBRARY`

テンプレート:

```bash
cmake -S skia -B skia/cmake-build-graphite-dawn \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_ENABLE_GPU_GRAPHITE=ON \
  -DRESKIA_ENABLE_GPU_DAWN=ON \
  -DRESKIA_DAWN_INCLUDE_DIR=/absolute/path/to/dawn/include \
  -DRESKIA_DAWN_LIBRARY=/absolute/path/to/libdawn_native.dylib
```

補足:

1. `RESKIA_DAWN_LIBRARY` は環境により `libdawn.dylib`, `libwebgpu_dawn.so`, `dawn_native.lib` など実ファイル名が異なる。
2. 現段階の公開レベルは `experimental` とし、CI 常設は `GANESH+METAL` から開始する。
