# 01 Non-docs Japanese Survey

調査日時: 2026-06-02 17:20:52 JST

## 目的

`docs/` 以外に残っている日本語文書・日本語コメント・日本語メッセージを把握し、今後の国際化作業でどのように扱うかを整理する。

この調査文書は、初回調査時点では変更方針の整理のみを目的としていた。
2026-06-02 に、優先対象3件の英語化を完了した。

## 調査範囲

主に Git 管理下のファイルを対象にした。

除外:

- `docs/**`
- `third_party/src/**` の外部依存 source
- `vendor/skia-upstream/**` と `vendor/skia-upstream-candidate/**`
- `third_party/build/**` と `third_party/install/**` の生成物
- `skia/cmake-build-*` の生成物

補足として、除外領域に README や日本語/中国語/韓国語データが存在することは確認したが、Reskia の国際化対象からは外す。

## 日本語を含む文書候補

| ファイル | 日本語行数 | 種別 | 状態 | 推奨対応 |
| --- | ---: | --- | --- | --- |
| `README.md` | 1 | ルート入口 | 言語名として `日本語` があるのみ。本文は英語。 | 現状維持でよい。 |
| `vendor/README.md` | 7 | 運用 README | Skia lock / upstream checkout / incremental upgrade の日本語説明。 | 完了: 英語化し、詳細を `docs/en/guides/skia-upgrade-workflow.md` へ誘導した。 |
| `third_party/README.md` | 14 | 運用 README | dependency source/build/install と bootstrap/build 手順の日本語説明。 | 完了: 英語化し、`docs/en/guides/cmake-migration-guide.md` と整合させた。 |
| `bindings/rust/reskia/examples/README.md` | 5 | サンプル README | `window_shapes` example の日本語説明。絶対パス例を含む。 | 完了: 英語化し、`RESKIA_LIB_DIR` を repo-relative な例にした。 |

## 文書ではないが日本語が残る主要領域

### CMake message / comment

対象例:

- `skia/CMakeLists.txt`
- `skia/modules/svg/CMakeLists.txt`
- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/sources-core.cmake`

内容:

- configure error / warning の日本語メッセージ。
- dependency mode や互換維持に関する日本語コメント。
- source sync が不足している場合の日本語案内。

影響:

- `cmake` 実行時に英語利用者へ日本語メッセージが表示される。
- docs ではないが、国際化の観点では user-facing。

推奨対応:

1. error / warning message は英語化する。
2. 内部コメントも、今後の contributor を想定して英語化する。
3. `docs/ja/...` への参照は必要に応じて `docs/en/...` または language-neutral な docs root へ寄せる。

### C API header comments

対象例:

- `skia/capi/*.h`

内容:

- ownership、NULL input、borrowed pointer、factory failure などの安全性コメントが日本語混在で残っている。

影響:

- public C API header として外部利用者が直接読む可能性が高い。
- すでに `docs/en/guides/c-api-safety-guidelines.md` では、今後追加する安全性コメントを短い英語文に寄せる方針にしている。

推奨対応:

1. 既存の日本語 safety comment を API 群単位で英語化する。
2. 一括巨大 diff は避け、触る header から段階的に進める。
3. `scripts/refine_capi_header_comments.py` の置換辞書は、既存日本語コメントの移行が終わるまで保持してよい。

### Test / sample source

対象例:

- `skia/test/test.cpp`
- `skia/src/ports/SkFontConfigInterface_direct.cpp`
- `skia/modules/skparagraph/tests/SkParagraphTest.cpp`
- `skia/modules/skparagraph/slides/ParagraphSlide.cpp`
- `skia/modules/skottie/tests/Shaper.cpp`

内容:

- テスト名、サンプル文字列、コメント、フォント/日本語テキスト関連の fixture。

影響:

- 多くはテストデータや text rendering 用サンプル文字列であり、国際化対象ではない。
- コメントやエラーメッセージとして残っているものは、必要に応じて英語化できる。

推奨対応:

- text rendering の test data として必要な日本語文字列は維持する。
- 説明コメントだけを英語化対象にする。

## 対象外

以下は Reskia の文書国際化対象から外す。

- `third_party/src/**` の外部依存 source に含まれる日本語・中国語・韓国語・Unicode data。
- `third_party/build/**` と `third_party/install/**` の生成物 README / docs。
- `vendor/skia-upstream/**` と `vendor/skia-upstream-candidate/**`。
- binary / image / fixture 内の文字列検出結果。

## 推奨作業順

1. `third_party/README.md` を英語化する。
2. `vendor/README.md` を英語化し、詳細は `docs/en/guides/skia-upgrade-workflow.md` へ誘導する。
3. `bindings/rust/reskia/examples/README.md` を英語化し、絶対パス例を避ける。
4. CMake の user-facing error / warning を英語化する。
5. C API header の日本語 safety comment を、API 群単位で英語化する。
6. test/sample source の日本語コメントを必要に応じて整理する。テストデータとしての日本語文字列は維持する。

## まとめ

docs 外の「文書」として優先対応すべきものは少ない。

最優先だった次の3件は、2026-06-02 に英語化済み:

- `third_party/README.md`
- `vendor/README.md`
- `bindings/rust/reskia/examples/README.md`

次点は、実行時に利用者へ出る CMake message と、public header として読まれる `skia/capi/*.h` の日本語 safety comment である。
