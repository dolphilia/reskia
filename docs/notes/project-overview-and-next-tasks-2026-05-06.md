# Reskia プロジェクト全体調査メモ

調査日時: 2026-05-06 15:20:50 JST  
対象リポジトリ: `/Users/dolphilia/github/reskia`  
調査方法: 既存 `README.md`、`docs/guides`、`docs/notes`、`docs/plans`、`skia/CMakeLists.txt`、`cmake/reskia/*.cmake`、`cmake/deps/ReskiaDeps.cmake`、`skia/capi`、`skia/handles`、`bindings/rust`、`third_party`、`vendor` を確認。

## 1. このプロジェクトが目指していること

Reskia は、Google Skia を CMake ベースで再構成し、C API と Rust などの他言語バインディングから利用しやすい共有ライブラリ `reskia` として提供することを目指している。

中心目的は次の 3 つに整理できる。

1. Skia の大規模な C++ ソース群を CMake で再現可能にビルドする。
2. `skia/capi` と `skia/handles` を通じて、C ABI 境界から Skia の描画、画像、テキスト、PDF、コーデック、GPU などへアクセスできるようにする。
3. 依存ライブラリと upstream Skia 追従を管理し、機能ごとに段階的に有効化できる構造へ移行する。

つまり、単なる Skia のコピーではなく、「Skia を CMake と C ABI で扱いやすくする移植・再構成プロジェクト」である。

## 2. 実現方法

### 2.1 CMake 入口を `skia/` に置く

リポジトリルートには `CMakeLists.txt` がなく、現在の主入口は `skia/CMakeLists.txt` である。

`skia/CMakeLists.txt` は以下を行う。

- `reskia` 共有ライブラリを定義する。
- `cmake/deps/ReskiaDeps.cmake` を読み込み、依存解決モードを決める。
- `cmake/reskia/sources-core.cmake`、`sources-capi.cmake`、`sources-handles.cmake` からソース一覧を読み込む。
- OS 別ソース、内部モジュール、機能フラグ、compile definition、リンクライブラリを結線する。
- `cmake/reskia/tests.cmake` を読み込み、必要なスモークテストを登録する。

以前は `skia/CMakeLists.txt` に source list やテスト定義が集中していたが、現在は `cmake/reskia/` へかなり分割されている。

### 2.2 依存解決をモード化する

依存解決は `RESKIA_DEPS_MODE` で切り替える。

- `prebuilt`: 既定。`third_party/install` などにあるビルド済み依存を `find_library` で解決する。
- `source`: `third_party/src` のサブモジュールを `scripts/build_third_party.sh` で install した成果物を使う。Apple では `skia/modules/skcms`、`skresources`、`svg` も `add_subdirectory` で接続する。
- `system`: OS やパッケージ管理側のライブラリを `find_package` / `find_library` で利用する。

この構造により、手元の最短ビルド、再現性重視ビルド、システム依存ビルドを切り分けられる。

### 2.3 機能フラグで Skia 機能を段階導入する

`cmake/deps/ReskiaDeps.cmake` には多数の機能フラグが定義されている。

主なフラグ:

- コーデック/エンコーダ: `RESKIA_ENABLE_AVIF`、`RESKIA_ENABLE_JPEGXL`、`RESKIA_ENABLE_RAW`、`RESKIA_ENABLE_GIF`、`RESKIA_ENABLE_JPEG_ENCODER`、`RESKIA_ENABLE_WEBP_ENCODER`
- 文書/テキスト/アニメーション: `RESKIA_ENABLE_PDF`、`RESKIA_ENABLE_SKSG`、`RESKIA_ENABLE_SKOTTIE`、`RESKIA_ENABLE_SKPARAGRAPH`
- GPU: `RESKIA_ENABLE_GPU_GANESH`、`RESKIA_ENABLE_GPU_GRAPHITE`、`RESKIA_ENABLE_GPU_VULKAN`、`RESKIA_ENABLE_GPU_METAL`、`RESKIA_ENABLE_GPU_DAWN`
- フォント: `RESKIA_ENABLE_FONTCONFIG_CAPI`

既定は多くが `OFF` で、機能有効時だけ追加 source、追加 include、追加 link、追加 compile definition が入る。これにより、CPU ラスタ中心の安定ビルドを維持しながら、PDF、Skottie、SkParagraph、GPU などの重い機能を段階的に導入している。

### 2.4 Skia C++ API を C ABI へ橋渡しする

公開層は大きく 2 系統ある。

- `skia/capi`: ポインタまたは型付き opaque pointer を受け渡す C API 層。
- `skia/handles`: `int` ハンドルで C++ オブジェクトを静的レジストリ管理する層。

Rust バインディングでは、`bindings/rust/reskia-sys` が C ABI を宣言し、`bindings/rust/reskia` が `Image`、`Surface`、`Paint`、`Path` などの RAII ラッパを提供している。

この方向性は明確だが、既存レビューでは `handles` 側の所有権、無効キー処理、世代管理、スレッド安全性に課題が残ると整理されている。

### 2.5 upstream Skia と依存を分離管理する

- `vendor/skia-source.lock`: upstream URL、fork URL、固定コミットを管理する。
- `vendor/skia-upstream`: 比較・同期用の upstream 作業ツリー。追跡対象外。
- `third_party/src`: 依存ライブラリ本体。git submodule 管理。
- `third_party/build`: 依存ビルド生成物。
- `third_party/install`: Reskia が参照する install 成果物。

`scripts/fetch_skia_upstream.sh`、`scripts/bootstrap_third_party.sh`、`scripts/build_third_party.sh` により、upstream 参照取得と依存ビルドを手順化している。

## 3. 現在の構造

トップレベル構造:

- `skia/`: `reskia` 本体。Skia ソース、C API、handles、modules、tests を持つ。
- `cmake/`: Reskia 用 CMake モジュール。依存解決と source list 分割の中心。
- `third_party/`: 外部依存の submodule、build、install 領域。
- `vendor/`: upstream Skia 参照と固定コミット管理。
- `bindings/rust/`: Rust FFI crate と safe wrapper crate。
- `scripts/`: upstream 取得、third_party 初期化、依存ビルド補助。
- `docs/`: ガイド、調査ノート、機能有効化計画。

`skia/` 内の主な構造:

- `skia/include`: Skia 公開ヘッダ群。
- `skia/src`: Skia 本体実装。`core`、`codec`、`encode`、`gpu`、`pdf`、`sksl` など。
- `skia/capi`: C ABI ラッパ。
- `skia/handles`: 整数ハンドルレジストリ。
- `skia/modules/skcms`: `skcms` 静的ライブラリ。
- `skia/modules/skresources`: resource provider 系。
- `skia/modules/svg`: `svg`、`skshaper`、`skunicode`。
- `skia/modules/skottie`、`sksg`、`skparagraph`: 条件付きで利用されるモジュール。
- `skia/test`: 機能ごとのスモークテスト。

`cmake/` 内の主な構造:

- `cmake/deps/ReskiaDeps.cmake`: 依存解決モード、機能フラグ、依存ライブラリ探索。
- `cmake/reskia/sources-core.cmake`: Skia 本体 source list と機能別追加 source。
- `cmake/reskia/sources-capi.cmake`: C API source list。
- `cmake/reskia/sources-handles.cmake`: handles source list。
- `cmake/reskia/tests.cmake`: `RESKIA_BUILD_TESTS=ON` 時のテスト登録。

## 4. 現在の到達点

既存ドキュメントと CMake 実装から見ると、2026-02 中旬以降に以下がかなり進んでいる。

- `prebuilt` / `source` モードで `reskia` 本体ビルドが確認済み。
- `source` モード向けに third_party submodule と install 自動化が整備済み。
- `skia/CMakeLists.txt` の source list と tests は `cmake/reskia/` へ分割済み。
- PDF は `RESKIA_ENABLE_PDF=ON` で条件付き対応済み。
- AVIF/JPEGXL/GIF/RAW/OpenType SVG decode と JPEG/WebP encode は、条件付き有効化とスモーク整備が進んでいる。
- SVG/text shaping は `svg -> skshaper -> skunicode` のリンク関係と縮退条件が整理済み。
- `skottie` は Apple 条件付きで最小 C API とスモークあり。
- `sksg` は `skottie` 非依存の単独トグル、C++ スモーク、C API スモークが整備済み。
- `skparagraph` は Apple + source + HarfBuzz 条件で C++ モジュール有効化とスモークが整備済み。ただし C API は未実装。
- GPU は Ganesh/Graphite/Vulkan/Metal/Dawn のフラグと C API 方針が入り、少なくとも Ganesh + Metal の最小スモークが確認済み。
- Rust 側は `reskia-sys` と `reskia` crate があり、画像、サーフェス、ペイント、パス中心の薄い safe wrapper が存在する。

## 5. 重要な制約とリスク

### 5.1 CMake / プラットフォーム

- ルート `CMakeLists.txt` はまだない。利用者は `cmake -S skia ...` を入口にする必要がある。
- `RESKIA_DEPS_MODE=source` の Windows 対応は未実装。
- Apple 以外の `source` / `system` モードは Apple と比べて依存接続が薄い。
- `system` の Windows は互換目的で `skia/lib` 参照を残しており、完全な imported target 化には至っていない。

### 5.2 機能別

- `RESKIA_ENABLE_SKOTTIE=ON` は現在 Apple 前提。
- `RESKIA_ENABLE_SKPARAGRAPH=ON` は現在 Apple + `RESKIA_DEPS_MODE=source` + HarfBuzz 前提。C API は未実装。
- `RESKIA_ENABLE_GPU_METAL=ON` は Apple 限定。
- `RESKIA_ENABLE_GPU_DAWN=ON` は Graphite 前提で、Dawn include/library の指定が必要。
- Graphite は `src/sksl/generated/sksl_graphite_{frag,vert}.minified.sksl` の同期が必要。
- Vulkan は `vk_mem_alloc.h` が必要。
- GIF/RAW/AVIF/JPEGXL などは third_party の配置とビルド状態に強く依存する。

### 5.3 C API / handles

既存レビューでは、`skia/handles` と `skia/capi` に以下の設計リスクが指摘されている。

- `get_entity()` が所有権を破壊する可能性。
- `map[key]` による無効キーの黙殺。
- ハンドル再利用に世代管理がなく、stale handle を検出できない。
- レジストリのスレッド安全性が不足。
- `delete`、`retain`、`release`、`ref/unref` の責務が一部混在。
- Rust safe wrapper を広げるには、C ABI 側の所有権規約がまだ足りない。

この領域は「機能追加」より先に安定化すべき基盤リスクである。

### 5.4 テスト

- `RESKIA_BUILD_TESTS` は既定 `OFF`。
- 機能別スモークは整備されているが、古い `test/test.cpp` は API 不整合が残る既知課題として複数文書で触れられている。
- 既存計画では、対象機能ごとのスモークを `ctest -R ...` で分離して前進する方針が取られている。

## 6. 今後のタスク候補

優先度順に見ると、次にするべきことは以下である。

### A. C API / handles の安全化を進める

最優先候補。

理由:

- Rust ラッパを広げる前提として所有権規約が必要。
- stale handle、無効キー、所有権移動の問題は、機能追加後ほど修正コストが上がる。
- `docs/plans/c-binding-remediation/` に計画とチェックリストが既にある。

次アクション:

1. `docs/plans/c-binding-remediation/checklists` の現状を再確認する。
2. `handles` の `operator[]` 排除、非破壊 borrow、mutex 導入の未完了箇所を洗い出す。
3. `SkRefCnt` 系を `retain/release` 規約へ寄せる。
4. Rust 側で `Drop` / `Clone` / invalid handle の最小回帰テストを増やす。

### B. `skparagraph` の C API 公開

高優先候補。

理由:

- `skparagraph` 本体の C++ 有効化とスモークは済んでいる。
- 既存機能ギャップ調査でも C API 未実装が残課題として明記されている。
- テキストレイアウトは C/Rust 利用者にとって価値が高い。

次アクション:

1. 公開する最小 API を `ParagraphStyle`、`TextStyle`、`ParagraphBuilder`、`Paragraph`、`layout`、`paint` に限定して設計する。
2. `RESKIA_ENABLE_SKPARAGRAPH` 条件で `sources-capi.cmake` へ追加する。
3. `test_skparagraph_capi_smoke.cpp` を追加する。
4. Rust には直接広げず、まず C ABI と C++ スモークを安定させる。

### C. GPU 経路の残課題を分割して潰す

中から高優先。

理由:

- Ganesh + Metal は前進しているが、Graphite、Vulkan、Dawn は依存・同期・環境制約がまだ大きい。
- GPU は機能価値が高い一方、CMake と C API の複雑度も高い。

次アクション:

1. Graphite 用 `sksl_graphite_*` 生成物同期手順を固定する。
2. Vulkan の VMA 導入手順と `RESKIA_VMA_INCLUDE_DIR` 運用を文書化する。
3. `GPU_GANESH+METAL` をまず安定サポート軸として CI 候補にする。
4. Graphite / Dawn は experimental として、失敗理由を依存不足・未実装・環境制約に分類して継続管理する。

### D. CMake の仕上げ

中優先。

理由:

- source list 分割は進んだが、ルート入口、platform matrix、target 指向化、CI 行列はまだ改善余地がある。
- 新機能追加のたびに CMake 差分が増えるため、基盤整理の効果が大きい。

次アクション:

1. ルート `CMakeLists.txt` を追加するかどうかを判断する。追加するなら薄い superbuild に限定する。
2. `prebuilt/source/system` x `APPLE/UNIX/WIN32` の実サポート表を README または docs に最新化する。
3. `system` / 非 Apple Unix / Windows の未整備領域を明示的に `FATAL_ERROR` または documented unsupported に寄せる。
4. CMake 変更時の検証コマンドを固定する。

### E. 既存 smoke と CI 相当の標準コマンドを固める

中優先。

理由:

- 機能別スモークは増えているが、利用者が「何を通せばよいか」を判断しづらい。
- `test/test.cpp` の既知不整合が残るため、全体テストの入口を整理する必要がある。

次アクション:

1. `RESKIA_BUILD_TESTS=ON` で既定構成がどこまで通るかを再確認する。
2. `test_c_skia` を現行 API に合わせて修正するか、legacy test として分離する。
3. `ctest -R c_skia_codec_smoke`、`c_skia_pdf_smoke`、`c_skia_sksg_*`、`c_skia_gpu_*` などを機能別検証セットとして docs にまとめる。

### F. Rust バインディングの拡張

中優先。ただし C ABI 安全化の後が望ましい。

理由:

- 現在の Rust wrapper は `Image`、`Surface`、`Paint`、`Path` などの基本操作に限定されている。
- 安全ラッパを広げるには C 側の所有権規約が先に必要。

次アクション:

1. C ABI の `retain/release/borrow` 規約が固まった型から Rust wrapper を増やす。
2. `reskia-sys` の手書き extern 宣言を bindgen 導入するか、当面は手書き最小維持するか判断する。
3. `bindings/rust/reskia/examples/window_shapes.rs` を基準に、画像 decode、PDF、skparagraph などの例を段階追加する。

## 7. 推奨ロードマップ

短期:

1. C API / handles 安全化の現状棚卸しを再開する。
2. `test_c_skia` の扱いを決める。
3. 既定 `prebuilt` と `source` の configure/build を再確認し、現在日時の検証メモを追加する。

中期:

1. `skparagraph` C API を最小公開する。
2. GPU は Ganesh + Metal を安定軸にし、Graphite/Vulkan/Dawn は個別の依存導入タスクへ分離する。
3. CMake platform matrix と CI 相当コマンドを固定する。

長期:

1. ルート superbuild の導入を検討する。
2. Rust safe wrapper を主要機能へ広げる。
3. upstream Skia 追従手順と source list 差分検査を自動化する。
4. C API の自動生成または半自動生成を導入し、手作業同期コストを下げる。

## 8. まとめ

Reskia は現在、Skia の CMake 移植と C ABI 化を土台に、PDF、SVG/text shaping、Skottie、SkParagraph、Sksg、GPU、codec/encoder を機能フラグで段階的に有効化する段階まで進んでいる。

一方で、今後の拡張のボトルネックは「機能が足りないこと」よりも、「C API / handles の所有権と安全性をどこまで明確にできるか」「CMake と依存解決の platform 差をどこまで整理できるか」に移っている。

次に最も効果が高い作業は、`docs/plans/c-binding-remediation/` に沿って C ABI の所有権・ハンドル安全性を固め、その上で `skparagraph` C API と Rust wrapper 拡張へ進むことである。
