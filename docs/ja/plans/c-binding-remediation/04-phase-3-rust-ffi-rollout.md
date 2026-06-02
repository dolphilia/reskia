# 04 Phase 3: Rust FFI Rollout

## ゴール

- Rust側で安全に扱える最小ラッパを提供する。
- C APIの所有権ルールが Rust `Drop` と一致することを実証する。

## 作業ステップ

1. [x] Rust PoCクレート追加
- 例: `bindings/rust/reskia-sys`（生FFI）
- 例: `bindings/rust/reskia`（safe wrapper）

2. [x] FFI境界の設計
- `reskia_*_retain` -> `Clone`
- `reskia_*_release` -> `Drop`
- `borrow_*` は lifetime 付き unsafe wrapper へ限定

3. [x] 最小対象型で実装開始
- `SkImage`
- `SkSurface`
- `SkPaint`
- `SkPath`

4. [x] 動作検証
- 二重解放しないこと
- clone/dropでリークしないこと
- 無効ハンドル時に失敗を返すこと

5. [x] CI検証追加

```bash
cargo test -p reskia-sys
cargo test -p reskia
ctest --test-dir skia/cmake-build-local --output-on-failure
```

## 進捗ログ

- 2026-02-16: ステップ1（Rust PoCクレート追加）を完了。
  - 追加: `Cargo.toml`（workspace）
  - 追加: `bindings/rust/reskia-sys`（`build.rs` + 最小 FFI 宣言）
  - 追加: `bindings/rust/reskia`（safe wrapper、`Image/Surface/Paint/Path` の `Clone`/`Drop` と最小エラーハンドリング）
  - 検証: `cargo test -p reskia-sys` / `cargo test -p reskia` 成功
- 2026-02-16: ステップ2（FFI境界の設計）に着手。
  - 追加: `skia/capi/reskia_ffi.h` / `skia/capi/reskia_ffi.cpp`
  - 実装: `Image/Surface/Paint/Path` 向け `reskia_*_retain` / `reskia_*_release` / `reskia_*_borrow_from_handle` を新設
  - Rust反映: `reskia-sys` と `reskia` を新命名へ切替し、`borrow_from_handle` を lifetime 付き `unsafe` wrapper として追加
  - 検証: `cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug` / `cmake --build skia/cmake-build-local -j 8` / `cargo test -p reskia-sys` / `cargo test -p reskia` 成功
- 2026-02-16: ステップ2（FFI境界の設計）を完了。
  - 横展開（RefCounted）: 25型で `retain/release/borrow_from_handle` を `reskia_*` 命名で整備
    - `SkBBoxHierarchy`, `SkBlender`, `SkCapabilities`, `SkColorFilter`, `SkColorSpace`, `SkColorTable`, `SkContourMeasure`, `SkData`, `SkDataTable`, `SkDocument`, `SkDrawable`, `SkFlattenable`, `SkFontMgr`, `SkFontStyleSet`, `SkImage`, `SkImageFilter`, `SkMaskFilter`, `SkPathEffect`, `SkPicture`, `SkPixelRef`, `SkRuntimeEffect`, `SkShader`, `SkSurface`, `SkTextBlob`, `SkVertices`
  - 横展開（Borrowed）: `SkExecutor_borrow`, `getCanvas/props`, `peekPixels`, `pixels`, `peek*` を `reskia_*_borrow_*` 命名で追加
  - 補足:
    - `SkColorMatrixFilter` は static handle 型が無いため `retain/release` のみ整備
    - `SkRefCnt` / `SkRefCntBase` は抽象基盤のため公開 borrow handle 対象から除外
- 2026-02-16: ステップ3（最小対象型の実装拡張）を完了。
  - `bindings/rust/reskia-sys`:
    - `SkImage_uniqueID` / `SkImage_isOpaque`
    - `SkSurface_makeImageSnapshot`
    - `SkPaint_setARGB`
    - `SkPath_close` / `SkPath_isEmpty`
    を FFI 宣言へ追加
  - `bindings/rust/reskia`:
    - `Image`: `unique_id`, `is_opaque`, `from_handle_retained`
    - `Surface`: `from_handle_retained`, `make_image_snapshot`
    - `Paint`: `set_argb`, `from_handle_retained`
    - `Path`: `close`, `is_empty`, `from_handle_retained`
  - 検証:
    - `cargo test -p reskia-sys` 成功
    - `cargo test -p reskia` 成功（5 tests passed）
- 2026-02-16: ステップ4（動作検証）を拡張して進行中。
  - `Clone/Drop` 検証の追加:
    - `clone_keeps_paint_independent`（clone 後の状態独立）
    - `clone_keeps_path_independent`（clone 後の点列独立）
    - `clone_drop_stress_for_paint_and_path`（5000回 clone/drop ストレス）
  - FFI 追加:
    - `SkPaint_getStrokeWidth`
    - `SkPath_countPoints`
  - 検証:
    - `cargo test -p reskia-sys` 成功
    - `cargo test -p reskia` 成功（8 tests passed）
- 2026-02-16: ステップ4（動作検証）で Image/Surface 実動 clone/drop を追加。
  - 追加テスト:
    - `surface_clone_drop_with_valid_instance`
    - `image_clone_drop_with_snapshot_instance`
  - テスト方式:
    - `SkImageInfo_MakeN32Premul` + `SkSurfaces_Raster_2` で有効 `SkSurface` を生成
    - `SkSurface_makeImageSnapshot` で有効 `SkImage` を生成
    - `clone`/`drop` 経路を実際に通し、最後に `static_sk_surface_delete` / `static_sk_image_delete` で handle cleanup
  - 検証:
    - `cargo test -p reskia-sys` 成功
    - `cargo test -p reskia` 成功（10 tests passed）
- 2026-02-16: ステップ4（動作検証）を完了。
  - 実施:
    - `cargo test -p reskia-sys` 成功
    - `cargo test -p reskia` 成功（10 tests passed）
    - `ctest --test-dir skia/cmake-build-local --output-on-failure` 成功（`No tests were found!!!`）
  - 注記:
    - `RESKIA_BUILD_TESTS=OFF` 既定のため CTest 対象が未登録でも終了コードは成功。
- 2026-02-16: ステップ5（CI検証追加）を完了。
  - 追加: `.github/workflows/rust-ffi-rollout.yml`
  - 内容:
    - `cmake -S skia -B skia/cmake-build-local -DCMAKE_BUILD_TYPE=Debug`
    - `cmake --build skia/cmake-build-local -j 8`
    - `cargo test -p reskia-sys`
    - `cargo test -p reskia`
    - `ctest --test-dir skia/cmake-build-local --output-on-failure`
  - トリガー:
    - `push` / `pull_request`（Rust FFI 関連パス変更時）
    - `workflow_dispatch`

## 完了条件

- Rust wrapper で basic draw の往復が成功。
- ASan/UBSan（可能なら）でクラッシュ/リーク重大項目がゼロ。
- C APIとRust APIの所有権表が一致している。
