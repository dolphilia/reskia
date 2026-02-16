# Reskia 機能ギャップ調査（2026-02-14）

対象:
- `/Users/dolphilia/github/reskia/skia`
- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`
- `/Users/dolphilia/github/reskia/skia/capi`
- `/Users/dolphilia/github/reskia/vendor/skia-upstream`

確認時刻: 2026-02-14 11:47:19 JST

## 1. 調査方法

1. `vendor/skia-upstream/modules` と `skia/modules` のディレクトリ比較  
2. `skia/CMakeLists.txt` の source/link 対象確認  
3. `binding` 実装と CMake での有効/無効差分確認  

## 2. upstream modules 比較

Reskia 側 `skia/modules`:

- `skcms`
- `skresources`
- `svg`

upstream 側 `vendor/skia-upstream/modules` で存在し、Reskia 側に未配置:

- `skottie`
- `skparagraph`
- `sksg`
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

### 3.3 skottie（Lottie アニメーション）

- 状態: 未対応
- 根拠:
  - `skia/modules/skottie` が存在しない
  - `skia/CMakeLists.txt` に `modules/skottie` 系の source/link なし

### 3.4 skparagraph（高機能テキストレイアウト）

- 状態: 未対応
- 根拠:
  - `skia/modules/skparagraph` が存在しない
  - `binding` に paragraph API 群なし

### 3.5 sksg（Scene Graph）

- 状態: 未対応
- 根拠:
  - `skia/modules/sksg` が存在しない
  - `binding` で `SkSG*` の公開なし

### 3.6 GPU（Ganesh/Graphite、Vulkan/Metal/Dawn）

- 状態: 弱い（実質未網羅）
- 根拠:
  - upstream には `vendor/skia-upstream/src/gpu/ganesh`, `graphite`, `vk`, `mtl`, `dawn` がある
  - Reskia `skia/CMakeLists.txt` には `src/gpu/*` が列挙されていない
  - `binding` には `GrDirectContext*` / `Recorder*` を受ける関数はあるが、コンテキスト生成系 API がほぼない

### 3.7 PDF ✅ 完了

- 状態: 実装ファイルはあるが未有効
- 根拠:
  - `skia/capi/sk_pdf.cpp` は存在
  - `skia/CMakeLists.txt` では `#        capi/sk_pdf.cpp` として無効

### 3.8 コーデック拡張（AVIF/JPEGXL/GIF/RAW/OpenType SVG） ✅ 完了

- 状態: 部分対応・未有効混在
- 根拠:
  - `SkAvifCodec.cpp`, `SkJpegxlCodec.cpp` などが `skia/CMakeLists.txt` でコメントアウト
  - `sk_avif_decoder.cpp`, `sk_jpegxl_decoder.cpp` は関数実装自体がコメントアウト
  - `sk_gif_decoder.cpp`, `sk_open_type_svg_decoder.cpp` は実装あるが CMake 側で無効

### 3.9 エンコーダ（JPEG/WebP） ✅ 完了

- 状態: 実装ありだが未有効
- 根拠:
  - `capi/sk_jpeg_encoder.cpp`, `capi/sk_webp_encoder.cpp` 存在
  - `skia/CMakeLists.txt` で両方コメントアウト

## 4. C binding の有効化状況（件数）

- `skia/capi/*.cpp` 実ファイル数: 155
- `skia/CMakeLists.txt` で有効化: 146
- `skia/CMakeLists.txt` でコメントアウト: 9

コメントアウト対象:

- `capi/sk_font_mgr_fontconfig.cpp`
- `capi/sk_gif_decoder.cpp`
- `capi/sk_jpeg_encoder.cpp`
- `capi/sk_open_type_svg_decoder.cpp`
- `capi/sk_pdf.cpp`
- `capi/sk_raster_handle_allocator.cpp`
- `capi/sk_raw_decoder.cpp`
- `capi/sk_text_blob_builder_run_handler.cpp`
- `capi/sk_webp_encoder.cpp`

## 5. 代表的な未網羅機能（優先候補）

優先度A（機能価値が高い）:

1. `skottie`（Lottie）
2. `skparagraph`（高度テキスト組版）
3. GPU実行パス（少なくとも1 backend: Metal/Vulkan のどちらか）

優先度B（周辺機能の実用性向上）:

4. PDF binding 有効化
5. JPEG/WebP encoder binding 有効化
6. GIF/OpenType SVG decoder binding 有効化

優先度C（将来拡張）:

7. `sksg`
8. `skplaintexteditor`
9. Web系モジュール（PathKit/CanvasKit/Jetski）

## 6. 補足

- 「ヘッダ上で型が見える」ことと「CMake で機能が有効」なことは別。  
  Reskia では後者が不足している機能が複数ある。
- GPU系は API 断片はあるが、`src/gpu` 非ビルドのため機能としては不十分。
