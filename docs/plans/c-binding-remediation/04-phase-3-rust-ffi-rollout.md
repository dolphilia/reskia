# 04 Phase 3: Rust FFI Rollout

## ゴール

- Rust側で安全に扱える最小ラッパを提供する。
- C APIの所有権ルールが Rust `Drop` と一致することを実証する。

## 作業ステップ

1. Rust PoCクレート追加
- 例: `bindings/rust/reskia-sys`（生FFI）
- 例: `bindings/rust/reskia`（safe wrapper）

2. FFI境界の設計
- `reskia_*_retain` -> `Clone`
- `reskia_*_release` -> `Drop`
- `borrow_*` は lifetime 付き unsafe wrapper へ限定

3. 最小対象型で実装開始
- `SkImage`
- `SkSurface`
- `SkPaint`
- `SkPath`

4. 動作検証
- 二重解放しないこと
- clone/dropでリークしないこと
- 無効ハンドル時に失敗を返すこと

5. CI検証追加

```bash
cargo test -p reskia-sys
cargo test -p reskia
ctest --test-dir skia/cmake-build-local --output-on-failure
```

## 完了条件

- Rust wrapper で basic draw の往復が成功。
- ASan/UBSan（可能なら）でクラッシュ/リーク重大項目がゼロ。
- C APIとRust APIの所有権表が一致している。
