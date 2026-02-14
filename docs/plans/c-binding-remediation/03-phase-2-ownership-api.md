# 03 Phase 2: Ownership API Rework (`skia/binding`)

## ゴール

- 解放ルールを明文化し、`delete` と `ref/unref` の混在を解消する。
- Rust/LuaJIT両対応できる API 形に揃える。

## 方針

- RefCounted型:
  - `retain/release` を正規APIにする。
  - `*_delete(void*)` は非推奨化し内部で `release` に委譲。
- 非RefCounted型:
  - `create/destroy` を維持。
  - `borrow` 系 API は解放不要であることを命名で明示。

## 作業ステップ

1. 型分類表を作成
- RefCounted / NonRefCounted / Borrowed の3分類を定義。
- `checklists/binding-status.csv` に `phase=P2` を設定して管理。

2. 解放APIの統一
- `*_delete` 実装を順次修正:
  - RefCounted: `delete` 直呼びを廃止し `unref/release` 経由へ変更。
  - NonRefCounted: `delete` を維持。
- ヘッダコメントに所有権を明示:
  - `owned`, `borrowed`, `retained`.

1. `void*` APIの型情報補強
- 連番関数名（`_2`, `_3`）には `note` で置換予定名を記録。
- Cプリミティブ型の正規化方針を追加:
  - `unsigned long`（`size_t` 代用）や `unsigned int`（`uint32_t` 代用）を段階的に型エイリアスへ統一。
  - 例: `reskia_size_t`, `reskia_u32_t`, `reskia_u64_t`（内部は `<stddef.h>/<stdint.h>` 由来）。
  - Skia独自意味型を C 側で明示する typedef を追加し、素の `unsigned int`/`int` 露出を削減。
  - 例: `reskia_color_t` (`SkColor`), `reskia_pmcolor_t` (`SkPMColor`), `reskia_typeface_id_t` (`SkTypefaceID`), `reskia_font_table_tag_t` (`SkFontTableTag`)
  - enum 戻り値/引数（例: `SkAlphaType`, `SkColorType`, `SkBlendMode`）の正規化方針:
    - 互換期間は ABI 互換を優先し、既存 `int` シグネチャは維持。
    - 併設する新シグネチャでは enum 意味型 typedef（例: `reskia_alpha_type_t`, `reskia_color_type_t`, `reskia_blend_mode_t`）を使用。
    - 旧関数は新関数への thin wrapper 化し、`note` に旧名/新名/削除予定を記録。
    - 実装側では `static_cast<Sk...>` を一箇所に閉じ込め、呼び出し側の生 `int` 依存を段階的に解消。
  - 対象マニフェスト:
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-voidptr-headers.txt`（111件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-suffix-headers.txt`（87件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-priority-headers.txt`（66件）
    - `docs/plans/c-binding-remediation/manifests/phase2-step3-primitive-headers.txt`（75件）

1. IN/OUT引数規約の統一
- `out*` は必ず `reskia_status_t` 戻り値へ段階移行。
- NULL許容/非許容をコメントで統一記載。
- `*_in` / `*_out` 変数名依存を廃止し、シグネチャで方向性を表現:
  - `in`: 値渡しまたは `const` ポインタ引数
  - `out`: 末尾の `*_t* out_...` 引数
  - 関数戻り値: `reskia_status_t`（`RESKIA_STATUS_OK` / エラーコード）
- ハンドル引数の型情報を強化:
  - 例: `int function_void_void_key_in` -> `reskia_function_void_void_t function_key`
  - 例: `int sk_font_style_set_out` -> `sk_font_style_set_t* out_style_set`
- 互換維持の段階移行:
  1. 既存関数を維持したまま `...2`（または `..._with_status`）を追加
  2. 旧関数は新関数へ委譲する thin wrapper 化
  3. `note` に旧名/新名/削除予定を記録し、Phase 4で `deprecated` 化
- 優先対象（現時点で `_in/_out` を持つ関数）:
  - `SkFontMgr_createStyleSet(int sk_font_style_set_out, void *font_mgr, int index)`
  - `SkFontMgr_matchFamily(int sk_font_style_set_out, void *font_mgr, const char familyName[])`
  - `SkExecutor_add(int function_void_void_key_in, void *executor)`

1. フェーズ2検証

```bash
rg -n "delete static_cast<Sk.*>" skia/binding/*.cpp
rg -n "\\bref\\(|\\bunref\\(" skia/binding/*.cpp
cmake --build skia/cmake-build-local -j 8
```

## 進捗（2026-02-14）

- [x] 1. 型分類表を作成
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-type-classification.md`
  - 集計結果:
    - RefCounted: 28
    - NonRefCounted: 93
    - Borrowed API: 17
  - `checklists/binding-status.csv` 更新:
    - `status in {todo,doing,blocked}` の行に `phase=P2` を設定（299件）
    - `phase1` で `done` 済みの11件は履歴維持のため据え置き
- [x] 2. 解放APIの統一
  - 準備完了: `docs/plans/c-binding-remediation/checklists/phase2-release-api-status.csv` を追加（RefCounted 28型の header/cpp を追跡）
  - 進捗: 28/28 完了（`phase2-release-api-status.csv` 全件 `done`）
- [ ] 3. `void*` APIの型情報補強
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-type-hardening-status.csv`（Step3 専用）
  - 追加: `docs/plans/c-binding-remediation/checklists/phase2-enum-int-status.csv`（enum/int 露出改善専用）
  - 実施済みセット:
    - `skia/binding/sk_annotation.h` + `skia/binding/sk_annotation.cpp`（3/3 関数 `done`）
    - 変更内容: `void*` 引数を `reskia_canvas_t` / `reskia_rect_t` / `reskia_point_t` / `reskia_data_t` の不透明型ポインタへ置換
    - `skia/binding/sk_android_codec.h` + `skia/binding/sk_android_codec.cpp`（18/18 関数 `done`）
    - 変更内容: `SkAndroidCodec` 系シグネチャの `void*` を不透明型ポインタへ置換し、`rowBytes` を `size_t` へ正規化
    - `skia/binding/sk_b_box_hierarchy.h` + `skia/binding/sk_b_box_hierarchy.cpp`（8/8 関数 `done`）
    - 変更内容: `SkBBoxHierarchy` 系シグネチャの `void*` を不透明型ポインタへ置換し、`bytesUsed` 戻り値を `size_t` へ正規化
    - `skia/binding/sk_bitmap.h` + `skia/binding/sk_bitmap.cpp`（84/84 関数 `done`）
    - 変更内容: `SkBitmap` 系シグネチャの `void*` を不透明型ポインタへ置換し、`unsigned long/unsigned int` を `size_t/uint32_t` へ正規化
    - `skia/binding/sk_blender.h` + `skia/binding/sk_blender.cpp`（11/11 関数 `done`）
    - 変更内容: `SkBlender` 系シグネチャの `void*` を不透明型ポインタへ置換し、`serialize/deserialize` で `size_t` 正規化を実施
    - `skia/binding/sk_bmp_decoder.h` + `skia/binding/sk_bmp_decoder.cpp`（3/3 関数 `done`）
    - 変更内容: `SkBmpDecoder` 系シグネチャで入力バッファを `const uint8_t* + size_t` に正規化し、`result/decodeContext` を不透明型ポインタ化
    - `skia/binding/sk_canvas.h` + `skia/binding/sk_canvas.cpp`（126/126 関数 `done`）
    - 変更内容: 全APIで `canvas` 受け口を `reskia_canvas_t*` に型強化し、`unsigned long/unsigned int` を `size_t/uint32_t` へ正規化
    - `skia/binding/sk_codec.h` + `skia/binding/sk_codec.cpp`（33/33 関数 `done`）
    - 変更内容: `SkCodec` 系シグネチャの `void*` を不透明型ポインタへ置換し、`rowBytes/length` を `size_t` に正規化
    - `skia/binding/sk_color.h` + `skia/binding/sk_color.cpp`（8/8 関数 `done`）
    - 変更内容: `SkColor` / `SkPMColor` / `U8CPU` を `reskia_color_t` / `reskia_pmcolor_t` / `reskia_u32_t` の意味型へ正規化
    - `skia/binding/sk_color_4f.h` + `skia/binding/sk_color_4f.cpp`（15/15 関数 `done`）
    - 変更内容: `SkColor4f` API を `reskia_color_4f_t*` 不透明型へ移行し、`SkColor`/`SkPMColor` を意味型 typedef（`reskia_color_t`/`reskia_pmcolor_t`）へ正規化
    - `skia/binding/sk_color_filter.h` + `skia/binding/sk_color_filter.cpp`（18/18 関数 `done`）
    - 変更内容: `SkColorFilter` API の `void*` を不透明型ポインタへ置換し、`size_t` と `reskia_color_t` でプリミティブ型を正規化
    - `skia/binding/sk_color_filters.h` + `skia/binding/sk_color_filters.cpp`（7/7 関数 `done`）
    - 変更内容: `SkColorFilters` API の `void*` と `unsigned int/unsigned char` を不透明型/意味型（`reskia_color_4f_t`, `reskia_color_t`, `uint8_t`）へ正規化
  - チェックリスト規模:
    - 対象ヘッダ: 134
    - 対象関数: 2431
  - 進捗:
    - `phase2-type-hardening-status.csv`: 334 / 2431 `done`
  - enum/int 露出チェックリスト規模:
    - 対象関数: 263
    - `enum_int_return`: 71
    - `enum_int_param`: 196
  - カテゴリ内訳（関数宣言ベース）:
    - `void_ptr`: 2365
    - `suffix`: 341
    - `primitive`: 366
    - `semantic` (`SkColor` / `SkPMColor` / `SkTypefaceID` / `SkFontTableTag`): 64
  - 検討結果: `unsigned long` / `unsigned int` はクロスプラットフォーム ABI 差分リスクがあるため、Step3に含めて正規化する。
  - 集計（宣言ベース）:
    - `unsigned long`: 250行
    - `unsigned int`: 120行
  - 集計（ファイルベース）:
    - `unsigned long` を含むヘッダ: 64件
    - `unsigned int` を含むヘッダ: 36件
    - いずれかを含むヘッダ: 75件
- [ ] 4. IN/OUT引数規約の統一
  - 設計方針を追加（`*_in/*_out` 廃止、`reskia_status_t + typed out pointer` へ移行）
  - 優先対象3関数（`SkFontMgr_createStyleSet`, `SkFontMgr_matchFamily`, `SkExecutor_add`）から着手
- [ ] 5. フェーズ2検証

## 完了条件

- RefCounted型で `delete static_cast<...>` がゼロ。
- 解放規約コメントが全公開ヘッダに記載済み。
- `checklists/binding-status.csv` の Phase 2 対象が `done`。
