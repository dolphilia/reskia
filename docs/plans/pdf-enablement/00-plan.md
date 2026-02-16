# 00 Plan: PDF 有効化

作成日時: 2026-02-16 16:05:25 JST

## ゴール

`docs/notes/reskia-feature-gap-survey-2026-02-14.md` の `3.7 PDF` を「未有効」から解消し、`reskia` で PDF 作成 API を C バインディング経由で利用可能にする。

- configure/build が通る
- 最小実行スモークで PDF 出力呼び出しが完了する
- 依存不足時の挙動（OFF にする条件）が明文化される

## 現状ギャップ（着手前の事実）

1. `cmake/reskia/sources-capi.cmake` で `capi/sk_pdf.cpp` がコメントアウトされている。
2. `skia/capi/sk_pdf.cpp` / `skia/capi/sk_pdf.h` は存在するが、現 CMake では未ビルド。
3. `skia/include/docs/SkPDFDocument.h` は存在する一方、`skia/src/pdf/` が現ツリーに存在しないため、API 有効化だけではリンク成立しない可能性が高い。
4. upstream 参照 (`vendor/skia-upstream/src/pdf`) には `SkPDFDocument.cpp` を含む PDF 実装群がある。

## 対象ファイル（主）

- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/sources-core.cmake`
- `cmake/deps/ReskiaDeps.cmake`（必要なら PDF トグル追加）
- `skia/capi/sk_pdf.{h,cpp}`
- `skia/capi/reskia_ffi.h`（必要なら公開ヘッダ統合）
- `skia/src/pdf/*`（upstream から同期する場合）
- `skia/test/*` または既存スモーク

## 実施フェーズ

### Phase 1: PDF 実装差分の棚卸し

ステータス: 完了（2026-02-16 16:08:43 JST）

1. `vendor/skia-upstream/src/pdf` と現ツリー差分をマニフェスト化する。
2. `SkPDFDocument.cpp` から逆引きし、最低限必要な `src/pdf/*` と関連 `src/core`/`src/utils` 依存を洗い出す。
3. 既存 `RESKIA_DEPS_MODE`（prebuilt/source/system）で追加依存が必要か判定する。

完了条件:
- 取り込む PDF ソースの最小セットと除外理由が確定している。

### Phase 2: ソース同期と CMake 組み込み

ステータス: 完了（2026-02-16 16:13:32 JST）

1. Phase 1 で確定した `src/pdf/*` を `vendor/skia-upstream` から同期する。
2. `cmake/reskia/sources-core.cmake` に PDF 実装ソース群を追加する。
3. 機能トグルで段階導入する場合は `RESKIA_ENABLE_PDF` を追加し、既定値と警告文を整備する。
4. `cmake/reskia/sources-capi.cmake` の `capi/sk_pdf.cpp` コメントアウトを解除する。

完了条件:
- PDF 有効時に `reskia` のリンクまで通る（未解決シンボルなし）。

### Phase 3: C API 公開面と型整合

ステータス: 完了（2026-02-16 20:21:58 JST）

1. `skia/capi/sk_pdf.h` の型前方宣言と実装シグネチャを現行スタイルで確認する。
2. 利用側の入口として `reskia_ffi.h` への include 追加要否を判断し、必要なら追加する。
3. `SkPDF::Metadata` との ABI 前提（`reskia_pdf_metadata_t`）を確認し、ずれがあればラッパー構造体に切り替える。

完了条件:
- C ヘッダ利用者が PDF API を警告/未定義なしで参照できる。

### Phase 4: ビルド行列検証

ステータス: 完了（2026-02-16 20:26:19 JST）

1. まず既定モード（`RESKIA_DEPS_MODE=prebuilt`）で configure/build。
2. `source` / `system` でも configure/build を行い、失敗時は依存不足として明示的に落ちることを確認する。
3. `RESKIA_BUILD_TESTS=ON` を使う場合は既存テストとの共存を確認する（既定 OFF は維持）。

実行例:
```bash
cmake -S skia -B skia/cmake-build-pdf-prebuilt \
  -DRESKIA_DEPS_MODE=prebuilt \
  -DRESKIA_ENABLE_PDF=ON
cmake --build skia/cmake-build-pdf-prebuilt -j 8
```

完了条件:
- 少なくとも 1 モードで PDF ON ビルド成功。
- 他モード失敗時も原因が依存不足として追跡可能。

### Phase 5: 実行スモーク（最小）

ステータス: 完了（2026-02-16 20:32:19 JST）

1. メモリストリームまたはファイルストリームを使って `SkPDF_MakeDocument*` を呼び出す最小テストを追加する。
2. `SkDocument_beginPage` -> 描画 -> `SkDocument_endPage` -> `SkDocument_close` を実行する。
3. 生成データが非空であることを確認する。

完了条件:
- PDF 作成経路の最小スモークが 0 exit で完了する。

## リスクと回避策

1. PDF 実装同期の規模が大きい。
- 回避: `SkPDFDocument.cpp` の依存閉包を先に固定し、段階的に取り込む。
2. `SkPDF::Metadata` の ABI 前提が C 側で壊れる。
- 回避: `reinterpret_cast` 依存をやめ、C 用メタデータ変換関数を用意する。
3. モード別リンク差異で `source/system` が壊れる。
- 回避: 各モードの configure を CI かローカル行列で早期実行する。

## Definition of Done

1. `3.7 PDF` が「実装ファイルはあるが未有効」状態から脱却している。
2. PDF API (`SkPDF_MakeDocument*`) が CMake 上で有効かつリンク可能。
3. 最小スモークで PDF 出力経路の実行確認が取れている。
4. 機能トグル・依存条件・既定値がドキュメント化されている。
