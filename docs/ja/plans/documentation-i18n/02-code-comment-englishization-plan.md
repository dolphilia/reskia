# 02 Code Comment Englishization Plan

作成日時: 2026-06-02 17:29:13 JST

## 目的

`docs/` 以外に残る日本語のうち、次の3領域を段階的に英語化する。

- CMake message / comment
- C API header comments
- Test / sample source

対象は、外部利用者や contributor が読む可能性のある説明・警告・エラー・public header comment である。
描画テストや Unicode 処理のための日本語テキストデータは、英語化の対象外とする。

## 現状

### CMake message / comment

初回検出対象:

- `skia/CMakeLists.txt`
- `skia/modules/svg/CMakeLists.txt`
- `cmake/deps/ReskiaDeps.cmake`
- `cmake/reskia/sources-capi.cmake`
- `cmake/reskia/sources-core.cmake`

状態:

- 2026-06-02 に user-facing message と主要コメントの英語化を完了した。
- `rg -n '[ぁ-んァ-ン一-龯]' cmake skia/CMakeLists.txt skia/modules/*/CMakeLists.txt third_party/CMakeLists.txt` で検出なし。

### C API header comments

初回検出では、`skia/capi/*.h` の多数の public header に日本語コメントが残っている。

主な内容:

- ownership / borrowed pointer
- nullable input
- factory failure
- return value lifetime
- caller-owned output buffer

方針:

1. API 群単位で分割する。
2. 一括変換ではなく、意味を確認しながら短い英語コメントにする。
3. `docs/en/guides/c-api-safety-guidelines.md` の表現に寄せる。
4. 生成・整形スクリプトの辞書は、移行が完了するまで残す。

推奨順:

1. Core value / math headers: `sk_color*`, `sk_matrix.h`, `sk_m_44.h`, `sk_v*.h`
2. Ownership-heavy base headers: `sk_ref_cnt*`, `sk_data*`, `sk_flattenable.h`
3. Drawing resource headers: `sk_shader*`, `sk_color_filter*`, `sk_path*`
4. Font / text headers: `sk_font*`, `sk_typeface*`, `sk_text_blob.h`
5. Optional platform / feature headers: GPU, FontConfig, Android, Mac

### Test / sample source

初回検出対象:

- `skia/test/test.cpp`
- `skia/src/ports/SkFontConfigInterface_direct.cpp`
- `skia/modules/skparagraph/tests/SkParagraphTest.cpp`
- `skia/modules/skparagraph/slides/ParagraphSlide.cpp`
- `skia/modules/skparagraph/test.html`
- `skia/modules/skottie/tests/Shaper.cpp`

方針:

1. 日本語文字列が text rendering の入力データなら維持する。
2. テスト意図を説明するコメントやログだけを英語化する。
3. HTML sample は表示確認用の多言語文面を含む可能性があるため、削除・翻訳前に用途を確認する。

## 作業単位

各サイクルで次を守る。

1. 対象ファイルを `rg` で限定する。
2. コメントや message の意味を確認する。
3. 英語化後、同じ対象範囲で日本語検出が残っていないか確認する。
4. `git diff --check` を実行する。
5. CMake または C/C++ に触れた場合は prebuilt configure/build を実行する。

## 完了条件

- CMake message / comment: 検出なし。
- C API header comments: public header comment の日本語検出なし。ただし API 名や外部仕様由来の非英語語句は個別判断。
- Test / sample source: 説明コメント・ログの日本語検出なし。テスト入力として必要な日本語文字列は残してよい。
