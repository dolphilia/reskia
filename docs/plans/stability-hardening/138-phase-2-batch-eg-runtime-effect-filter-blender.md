# 138 Phase 2 Batch EG: runtime effect filter and blender ownership

開始時刻: 2026-05-13 04:31:11 JST

## 目的

`137-phase-2-batch-ef-runtime-effect-make-shader.md` の「次バッチ候補」から、`SkRuntimeEffect` makeColorFilter / makeBlender returned handle ownership と data / children optional 規約を再確認する。data handle 0 と child pointer handle 0 は空入力として許容し、成功時の color filter / blender handle は呼び出し側が delete できることを固定する。

## 変更内容

- `skia/capi/sk_runtime_effect.h`
  - `SkRuntimeEffect_makeColorFilter` / `SkRuntimeEffect_makeColorFilterWithChildren` / `SkRuntimeEffect_makeColorFilterWithChildPtr` の returned color filter handle ownership を明記した。
  - `SkRuntimeEffect_makeBlender` の returned blender handle ownership を明記した。
- `skia/test/test_runtime_effect_invalid_input_smoke.cpp`
  - `SkRuntimeEffect_makeColorFilterWithChildren(effect, 0, nullptr, 0)` が有効 color filter handle を返し delete できることを確認した。
  - `SkRuntimeEffect_makeColorFilterWithChildPtr(effect, 0, 0)` が有効 color filter handle を返し delete できることを確認した。
  - 既存の makeColorFilter / makeBlender ownership smoke と invalid data / child pointer smoke と合わせて optional input 規約を固定した。
- `docs/plans/c-binding-remediation/checklists/capi-status.csv`
  - `sk_runtime_effect.cpp` / `sk_runtime_effect.h` の P2 記録を Batch EG に更新した。

## 検証

- `cmake -S skia -B skia/cmake-build-stability-tests -DCMAKE_BUILD_TYPE=Debug -DRESKIA_BUILD_TESTS=ON`
  - 成功。
- `cmake --build skia/cmake-build-stability-tests --target test_runtime_effect_invalid_input_smoke -j 8`
  - 成功。
- `ctest --test-dir skia/cmake-build-stability-tests -R 'c_skia_runtime_effect_invalid_input_smoke' --output-on-failure`
  - 成功。1/1 passed。
- `cmake --build skia/cmake-build-stability-prebuilt -j 8`
  - 成功。`Built target reskia`。
- `git diff --check`
  - 終了コード 0。既知の `docs/plans/c-binding-remediation/checklists/capi-status.csv` CRLF 警告のみ。

## 次バッチ候補

- `SkCanvas` drawPicture / drawTextBlob handle and pointer overload の borrowed / owned handle 規約を再確認する。
- `SkImage` encode / refEncodedData returned data handle ownership と failure 0 規約を再確認する。
- `SkCanvas` drawVertices / drawVerticesPtr の handle / borrowed pointer と paint required 規約を再確認する。
