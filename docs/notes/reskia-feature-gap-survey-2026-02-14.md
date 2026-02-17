# Reskia 機能ギャップ調査（2026-02-14）

対象:
- `/Users/dolphilia/github/reskia/skia`
- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skia/capi`
- `/Users/dolphilia/github/reskia/vendor/skia-upstream`

確認時刻: 2026-02-14 11:47:19 JST
追補更新: 2026-02-17 07:38:20 JST（3.3 skottie 対応反映）
追補更新: 2026-02-17 09:41:06 JST（3.4 skparagraph 対応反映）

## 1. 調査方法

1. `vendor/skia-upstream/modules` と `skia/modules` のディレクトリ比較  
2. `skia/CMakeLists.txt` の source/link 対象確認  
3. `binding` 実装と CMake での有効/無効差分確認  

## 2. upstream modules 比較

Reskia 側 `skia/modules`:

- `skcms`
- `skottie`
- `skresources`
- `sksg`
- `svg`

upstream 側 `vendor/skia-upstream/modules` で存在し、Reskia 側に未配置:

- `skplaintexteditor`
- `skshaper`（Reskia では `svg/modules/skshaper` として同梱）
- `skunicode`（Reskia では `svg/modules/skunicode` として同梱）
- `pathkit`, `canvaskit`, `jetski`, `audioplayer`, `bentleyottmann`

## 3. 代表機能の網羅状況

### 3.1 2Dラスタ描画（core/pathops/sksl）

- 状態: 概ね網羅
- 根拠: `skia/CMakeLists.txt` で `src/core`, `src/pathops`, `src/sksl` を大量にビルド対象化

### 3.2 SVG / テキストシェーピング ✅ 完了

- 状態: 部分網羅
- `svg`, `skshaper`, `skunicode` は別プロジェクトでビルド可能
- ただし依存（ICU/HarfBuzz/ICU4X/libgrapheme）不足時は最小実装へ縮退
- 根拠: `/Users/dolphilia/github/reskia/svg/CMakeLists.txt`
- 追補（2026-02-17）:
  - `svg -> skshaper -> skunicode` のリンクを明示化済み
  - ICU 利用時の `skunicode` への `icui18n/icuuc/icudata` リンクを明示化済み
  - `test_shaping_smoke` を追加し、UTF-8 + BiDi + 改行 shaping と SVG text 描画スモークを `PASS` 確認済み
  - 詳細: `/Users/dolphilia/github/reskia/docs/plans/svg-text-shaping-enablement/04-phase-4-build-matrix.md`, `/Users/dolphilia/github/reskia/docs/plans/svg-text-shaping-enablement/05-phase-5-smoke-and-docs.md`

### 3.3 skottie（Lottie アニメーション） ✅ 完了

- 状態: 部分網羅（最小 C API + CMake トグル対応）
- 根拠:
  - `skia/modules/skottie` と `skia/modules/sksg` を同期済み
  - `RESKIA_ENABLE_SKOTTIE`（既定 `OFF`）を追加し、`ON` 時のみ `modules/sksg` / `modules/skottie` の source を取り込み
  - `SK_ENABLE_SKOTTIE` / `SK_ENABLE_SKOTTIE_SKSLEFFECT` を `ON` 時に付与
  - C API `skia/capi/sk_skottie.{h,cpp}` を追加（load/seek/render/release）
  - `test_skottie_smoke` を追加し、`ctest -R c_skia_skottie_smoke` で `PASS` 確認
- 制約:
  - 現状 `RESKIA_ENABLE_SKOTTIE=ON` は `APPLE` のみ対応
  - `RESKIA_DEPS_MODE=source` では `skresources` / `svg` の解決が必要
- 詳細:
  - `/Users/dolphilia/github/reskia/docs/plans/skottie-enablement/02-phase-2-cmake-enablement.md`
  - `/Users/dolphilia/github/reskia/docs/plans/skottie-enablement/03-phase-3-capi-minimal.md`
  - `/Users/dolphilia/github/reskia/docs/plans/skottie-enablement/04-phase-4-build-matrix.md`
  - `/Users/dolphilia/github/reskia/docs/plans/skottie-enablement/05-phase-5-smoke-and-docs.md`

### 3.4 skparagraph（高機能テキストレイアウト） ✅ 完了

- 状態: 部分網羅（C++ モジュール有効化 + 最小スモーク）
- 根拠:
  - `skia/modules/skparagraph` を同期済み
  - `RESKIA_ENABLE_SKPARAGRAPH`（既定 `OFF`）を追加し、`ON` 時のみ `skparagraph` source を取り込み
  - `RESKIA_ENABLE_SKPARAGRAPH=ON` 時に HarfBuzz（`hb.h` / `libharfbuzz`）を検出し、未導入時は configure で `FATAL_ERROR`
  - `test_skparagraph_smoke` を追加し、`ctest -R c_skia_skparagraph_smoke` で `PASS` 確認
- 制約:
  - 現状 `RESKIA_ENABLE_SKPARAGRAPH=ON` は `APPLE` のみ対応
  - 現状 `RESKIA_DEPS_MODE=source` のみ対応
  - C API の paragraph 公開は未実装
- 詳細:
  - `/Users/dolphilia/github/reskia/docs/plans/skparagraph-enablement/02-phase-2-cmake-enablement.md`
  - `/Users/dolphilia/github/reskia/docs/plans/skparagraph-enablement/03-phase-3-smoke.md`
  - `/Users/dolphilia/github/reskia/docs/plans/skparagraph-enablement/04-phase-4-build-matrix.md`

### 3.5 sksg（Scene Graph） ✅ 完了

- 状態: 条件付き対応（既定 OFF）
- 根拠:
  - `skia/modules/sksg` は同期済み
  - `RESKIA_ENABLE_SKSG=ON` で `modules/sksg/sksg.gni` 由来ソースをビルドへ取り込み可能
  - `RESKIA_ENABLE_SKSG=ON` + `RESKIA_ENABLE_SKOTTIE=OFF` で `sksg` 単独ビルド経路を確認済み
  - `capi/sk_sksg.h`, `capi/sk_sksg.cpp` を追加し、最小 C API（Scene 作成/再検証/描画/解放）を公開済み
  - `c_skia_sksg_smoke`（C++）と `c_skia_sksg_capi_smoke`（C API）の実行成功を確認
- 制約:
  - 既定では `RESKIA_ENABLE_SKSG=OFF`
  - 検証済み構成は `RESKIA_DEPS_MODE=source`（macOS）での OFF/ON/併用（`SKOTTIE`）3 経路
  - `RESKIA_ENABLE_SKOTTIE=ON` 併用時は `skottie` 側制約（現在 APPLE のみ対応）を受ける
- 詳細:
  - `/Users/dolphilia/github/reskia/docs/plans/sksg-enablement/00-plan.md`
  - `/Users/dolphilia/github/reskia/docs/plans/sksg-enablement/04-phase-4-build-matrix.md`

### 3.6 GPU（Ganesh/Graphite、Vulkan/Metal/Dawn）

- 状態: 弱い（実質未網羅）
- 根拠:
  - upstream には `vendor/skia-upstream/src/gpu/ganesh`, `graphite`, `vk`, `mtl`, `dawn` がある
  - Reskia `skia/CMakeLists.txt` には `src/gpu/*` が列挙されていない
  - `binding` には `GrDirectContext*` / `Recorder*` を受ける関数はあるが、コンテキスト生成系 API がほぼない

### 3.7 PDF ✅ 完了

- 状態: 条件付き対応（既定 OFF）
- 根拠:
  - `skia/capi/sk_pdf.cpp` は存在
  - `RESKIA_ENABLE_PDF=ON` で `sources-capi.cmake` から有効化可能

### 3.8 コーデック拡張（AVIF/JPEGXL/GIF/RAW/OpenType SVG） ✅ 完了

- 状態: 部分対応・条件付き有効化
- 根拠:
  - `SkAvifCodec.cpp`, `SkJpegxlCodec.cpp` などが `skia/CMakeLists.txt` でコメントアウト
  - `sk_avif_decoder.cpp`, `sk_jpegxl_decoder.cpp` は関数実装自体がコメントアウト
  - `sk_gif_decoder.cpp`, `sk_raw_decoder.cpp` はトグル（`RESKIA_ENABLE_GIF` / `RESKIA_ENABLE_RAW`）で有効化
  - `sk_open_type_svg_decoder.cpp` は既定でビルド対象に組み込み済み

### 3.9 エンコーダ（JPEG/WebP） ✅ 完了

- 状態: 実装あり・条件付き有効化
- 根拠:
  - `capi/sk_jpeg_encoder.cpp`, `capi/sk_webp_encoder.cpp` 存在
  - `RESKIA_ENABLE_JPEG_ENCODER` / `RESKIA_ENABLE_WEBP_ENCODER` で有効化可能

## 4. C binding の有効化状況（件数）

- `skia/capi/*.cpp` 実ファイル数: 157
- 既定（主要トグル `OFF`）で有効: 147（`APPLE` の `capi/sk_typeface_mac.cpp` を含む）
- `sources-capi.cmake` でコメントアウト: 2
- トグル有効化で追加される C API: 8（AVIF/JPEGXL/GIF/RAW/JPEG encoder/WebP encoder/PDF/skottie）

コメントアウト対象（常時無効）:

- `capi/sk_font_mgr_fontconfig.cpp`
- `capi/sk_raster_handle_allocator.cpp`

## 5. 代表的な未網羅機能（優先候補）

優先度A（機能価値が高い）:

1. GPU実行パス（少なくとも1 backend: Metal/Vulkan のどちらか）
2. `skparagraph` C API 公開（現状は C++ モジュールのみ）

優先度B（周辺機能の実用性向上）:

3. PDF binding 有効化
4. JPEG/WebP encoder binding 有効化
5. GIF/OpenType SVG decoder binding 有効化

優先度C（将来拡張）:

6. `sksg` 直接 C API 公開
7. `skplaintexteditor`
8. Web系モジュール（PathKit/CanvasKit/Jetski）

## 6. 補足

- 「ヘッダ上で型が見える」ことと「CMake で機能が有効」なことは別。  
  Reskia では後者が不足している機能が複数ある。
- GPU系は API 断片はあるが、`src/gpu` 非ビルドのため機能としては不十分。
