# 025 Phase 2.5: GPU ソース/ヘッダ同期

更新日時: 2026-02-17 11:52:14 JST

## 目的

Phase 2 で追加した GPU トグルを実際に機能させる前提として、upstream Skia の GPU 関連ソース/ヘッダを Reskia ツリーへ同期する。

## 同期対象と結果

1. `vendor/skia-upstream/src/gpu` -> `skia/src/gpu`
2. `vendor/skia-upstream/include/gpu` -> `skia/include/gpu`
3. `vendor/skia-upstream/include/private/gpu` -> `skia/include/private/gpu`
4. 追加依存として以下も同期
- `vendor/skia-upstream/src/text/gpu` -> `skia/src/text/gpu`
- `vendor/skia-upstream/include/android` -> `skia/include/android`
- `vendor/skia-upstream/include/private/chromium` -> `skia/include/private/chromium`
- `vendor/skia-upstream/include/ports/SkCFObject.h` -> `skia/include/ports/SkCFObject.h`

同期後件数:

- `skia/src/gpu`: `1058` files
- `skia/include/gpu`: `80` files
- `skia/include/private/gpu`: `14` files

## 実施コマンド（主要）

```bash
rsync -a --delete vendor/skia-upstream/src/gpu/ skia/src/gpu/
rsync -a --delete vendor/skia-upstream/include/gpu/ skia/include/gpu/
rsync -a --delete vendor/skia-upstream/include/private/gpu/ skia/include/private/gpu/

rsync -a --delete vendor/skia-upstream/src/text/gpu/ skia/src/text/gpu/
rsync -a --delete vendor/skia-upstream/include/android/ skia/include/android/
rsync -a --delete vendor/skia-upstream/include/private/chromium/ skia/include/private/chromium/
rsync -a vendor/skia-upstream/include/ports/SkCFObject.h skia/include/ports/SkCFObject.h
```

## 途中で判明した問題と対処

1. `GANESH+METAL` ビルドで `dawn`/`graphite` ソースが混入
- 原因: `sources-core.cmake` の GPU 収集が広すぎた。
- 対処: backend トグルに応じた収集/除外へ修正。

2. Metal `.mm` で ARC 必須エラー
- 原因: `-fobjc-arc` 未設定。
- 対処: `skia/CMakeLists.txt` で `src/gpu/**/*.mm` に ARC を適用。

3. `GRAPHITE=OFF` なのに `graphite/mtl` がビルド対象
- 原因: `RESKIA_ENABLE_GPU_METAL=ON` 時に graphite mtl を無条件追加。
- 対処: `RESKIA_ENABLE_GPU_GRAPHITE=ON` 時のみ graphite backend を追加する条件へ修正。

## 検証結果（現時点）

1. configure（`GANESH=ON`, `METAL=ON`）は成功。
2. 直近修正後、ビルドルール上は `graphite/mtl`/`graphite/vk`/`graphite/dawn` が含まれないことを確認。
3. `GANESH+METAL` のフルビルド完走確認は継続タスク。

## 次アクション

1. `GANESH+METAL` のフルビルド完走を確認。
2. 完走後に `02-phase-2-cmake-design.md` を最終ステータスへ更新。
