# 03 Phase 3: GPU C API（Context/Recorder）最小公開設計

更新日時: 2026-02-17 12:13:57 JST

## 目的

既存 C API と整合する形で、GPU コンテキスト生成・破棄と最小同期経路を公開する。

## 設計スコープ

1. Ganesh（`GrDirectContext`）
- backend 別作成エントリ（Metal / Vulkan）
- flush / submit / abandon / release
2. Graphite（`Context` / `Recorder`）
- context 作成・破棄
- recorder 作成・破棄
- submit（最小）
3. 既存 API との連携
- `SkImage_*`、`Sk*Encoder_*` が受ける `reskia_direct_context_t*` へ接続
- `SkSurface_recorder` 系と所有権注記を統一

## 作業項目

1. `skia/capi` に GPU 用ヘッダ/実装を追加する。
2. `skia/capi/reskia_ffi.h` へ include を追加する。
3. `borrowed` / `owned` を API コメントで明記する。
4. `null` 入力時の挙動（no-op / false / nullptr）を統一する。

## 変更対象ファイル

- `skia/capi/reskia_ffi.h`
- `skia/capi/sk_gpu_context.h`（新規）
- `skia/capi/sk_gpu_context.cpp`（新規）
- `cmake/reskia/sources-capi.cmake`

## 実装進捗（着手）

1. `Ganesh/Metal`
- `Reskia_GaneshContext_MakeMetal(void* device, void* queue)` を実装。
- `Reskia_DirectContext_FlushAndSubmit` / `Reskia_DirectContext_Abandon` / `Reskia_DirectContext_Release` を実装。
 - `Reskia_GaneshContext_MakeVulkan(const void* backend_context)` を実装。
2. `Graphite/Metal`
- `Reskia_GraphiteContext_MakeMetal` / `Reskia_GraphiteContext_MakeRecorder` を実装。
- `Reskia_GraphiteContext_InsertRecordingAndSubmit` / `Reskia_GraphiteRecorder_Release` / `Reskia_GraphiteContext_Release` を実装。
 - `Reskia_GraphiteContext_MakeVulkan(const void* backend_context)` を実装。
3. 公開結線
- `reskia_ffi.h` へ `sk_gpu_context.h` include を追加。
- `sources-capi.cmake` へ `capi/sk_gpu_context.cpp` を追加。
4. 互換性ガード
- `SK_GANESH=OFF` でもリンク破綻しないよう、DirectContext 操作 API を no-op / `nullptr` スタブ化。

## 判定基準

1. C から context/recorder の生成・破棄が実行可能。
2. 既存 API に context を渡してクラッシュしない。
3. 所有権規約がヘッダコメントと実装で一致している。

## API 草案（最小）

```c
reskia_direct_context_t* Reskia_GaneshContext_MakeMetal(...);
reskia_direct_context_t* Reskia_GaneshContext_MakeVulkan(...);
void Reskia_DirectContext_FlushAndSubmit(reskia_direct_context_t* ctx);
void Reskia_DirectContext_Release(reskia_direct_context_t* ctx);

reskia_graphite_context_t* Reskia_GraphiteContext_Make(...);
reskia_graphite_recorder_t* Reskia_GraphiteRecorder_Make(reskia_graphite_context_t* ctx);
bool Reskia_GraphiteRecorder_Submit(reskia_graphite_recorder_t* recorder);
void Reskia_GraphiteRecorder_Release(reskia_graphite_recorder_t* recorder);
```

## 次フェーズへの引き継ぎ

1. Phase 4 で GPU surface 作成 API と backend handle ラップを追加する。
2. 実機依存の backend handle 受け渡し構造体を C ABI で固定する。
