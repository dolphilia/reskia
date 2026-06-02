# 01 Phase 1: 依存マトリクスと有効化ポリシー

更新日時: 2026-02-16 14:43:33 JST

## 目的

3.8/3.9 対象機能を CMake オプションで段階的に有効化できるようにし、依存不足を configure 時に検出できる状態を作る。

## 追加したオプション

- `RESKIA_ENABLE_AVIF`
- `RESKIA_ENABLE_JPEGXL`
- `RESKIA_ENABLE_RAW`
- `RESKIA_ENABLE_GIF`
- `RESKIA_ENABLE_JPEG_ENCODER`
- `RESKIA_ENABLE_WEBP_ENCODER`

定義場所:
- `/Users/dolphilia/github/reskia/cmake/deps/ReskiaDeps.cmake`

## 依存マトリクス（Phase 1 時点）

| 機能 | CMake option | prebuilt (APPLE/WIN32) | source/system (APPLE) | compile definition |
|---|---|---|---|---|
| AVIF decode | `RESKIA_ENABLE_AVIF` | `avif` | `avif` | `SK_CODEC_DECODES_AVIF` |
| JPEGXL decode | `RESKIA_ENABLE_JPEGXL` | `jxl`, `jxl_threads`, `jxl_cms` | `jxl`, `jxl_threads`, `jxl_cms` | `SK_CODEC_DECODES_JPEGXL` |
| RAW decode | `RESKIA_ENABLE_RAW` | (追加リンクなし) | (追加リンクなし) | `SK_CODEC_DECODES_RAW` |
| GIF decode | `RESKIA_ENABLE_GIF` | (追加リンクなし) | (追加リンクなし) | `SK_HAS_WUFFS_LIBRARY` |
| JPEG encode | `RESKIA_ENABLE_JPEG_ENCODER` | 既存 `jpeg` 系依存を利用 | 既存 `JPEG::JPEG` / `libjpeg` 利用 | なし |
| WebP encode | `RESKIA_ENABLE_WEBP_ENCODER` | 既存 `webp*` 依存を利用 | 既存 `webp*` 依存を利用 | なし |

## 実装ポリシー（重要）

- compile definition は、対応 core source が `SOURCE_FILES` に入っている場合のみ付与する。
- option を ON にしても source 未登録なら WARNING を出し、マクロは付与しない。
- これにより、Phase 2（ソース補完）前に誤ってマクロだけ有効化される事故を防ぐ。

対象ファイル:
- `/Users/dolphilia/github/reskia/skia/CMakeLists.txt`

## Phase 2 への引き継ぎ

1. `sources-core.cmake` へ codec/encoder 実装を追加する。
2. `sources-capi.cmake` の対象 API コメントアウトを解除する。
3. source 登録後、同オプション ON で compile definition が有効化されることを確認する。
