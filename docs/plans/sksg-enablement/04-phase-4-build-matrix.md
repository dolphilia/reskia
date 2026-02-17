# 04 Phase 4: 検証マトリクス整理

更新日時: 2026-02-17 10:06:43 JST

## 目的

`RESKIA_ENABLE_SKSG` 導入後の以下 3 経路で configure/build/test の再現性を確認する。

1. 既定経路: `RESKIA_ENABLE_SKSG=OFF`, `RESKIA_ENABLE_SKOTTIE=OFF`
2. sksg 経路: `RESKIA_ENABLE_SKSG=ON`, `RESKIA_ENABLE_SKOTTIE=OFF`
3. 併用経路: `RESKIA_ENABLE_SKSG=ON`, `RESKIA_ENABLE_SKOTTIE=ON`

## 実行結果

### 1. 既定経路（OFF/OFF）

```bash
cmake -S skia -B skia/cmake-build-sksg-matrix-off \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=OFF \
  -DRESKIA_ENABLE_SKSG=OFF \
  -DRESKIA_ENABLE_SKOTTIE=OFF
cmake --build skia/cmake-build-sksg-matrix-off -j 8 --target reskia
```

- 結果: 成功（`libreskia.dylib` 生成）

### 2. sksg 経路（ON/OFF）

```bash
cmake -S skia -B skia/cmake-build-sksg-matrix-on \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON \
  -DRESKIA_ENABLE_SKSG=ON \
  -DRESKIA_ENABLE_SKOTTIE=OFF
cmake --build skia/cmake-build-sksg-matrix-on -j 8 \
  --target test_sksg_smoke test_sksg_capi_smoke
ctest --test-dir skia/cmake-build-sksg-matrix-on \
  -R c_skia_sksg_ --output-on-failure
```

- 結果: 成功
- テスト:
  - `c_skia_sksg_smoke` PASS
  - `c_skia_sksg_capi_smoke` PASS

### 3. 併用経路（ON/ON）

```bash
cmake -S skia -B skia/cmake-build-sksg-matrix-both \
  -DRESKIA_DEPS_MODE=source \
  -DRESKIA_BUILD_TESTS=ON \
  -DRESKIA_ENABLE_SKSG=ON \
  -DRESKIA_ENABLE_SKOTTIE=ON
cmake --build skia/cmake-build-sksg-matrix-both -j 8 \
  --target test_sksg_smoke test_sksg_capi_smoke test_skottie_smoke
ctest --test-dir skia/cmake-build-sksg-matrix-both \
  -R 'c_skia_(sksg|skottie)' --output-on-failure
```

- 結果: 成功
- テスト:
  - `c_skia_skottie_smoke` PASS
  - `c_skia_sksg_smoke` PASS
  - `c_skia_sksg_capi_smoke` PASS

## まとめ

1. `RESKIA_ENABLE_SKSG` の OFF/ON/併用の 3 経路で configure/build/test が再現可能。
2. `sksg` 単独有効化時と `skottie` 併用時の両方でスモークテストが通る。
3. Phase 4 の完了条件（OFF/ON/併用 3 経路の検証）は充足。
