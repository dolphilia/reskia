//
// Created by dolphilia on 2026/02/17.
//

#ifndef RAIA_SKIA_SK_GPU_CONTEXT_H
#define RAIA_SKIA_SK_GPU_CONTEXT_H

#include <stdbool.h>

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_graphite_context_t reskia_graphite_context_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_direct_context_t *Reskia_GaneshContext_MakeMetal(void *device, void *queue); // owned: 呼び出し側が Reskia_DirectContext_Release で解放する (void *device, void *queue) -> GrDirectContext *
reskia_direct_context_t *Reskia_GaneshContext_MakeVulkan(const void *backend_context); // owned: 呼び出し側が Reskia_DirectContext_Release で解放する (const GrVkBackendContext *backend_context) -> GrDirectContext *
void Reskia_DirectContext_FlushAndSubmit(reskia_direct_context_t *ctx, bool sync_cpu); // (GrDirectContext *ctx, bool sync_cpu)
void Reskia_DirectContext_Abandon(reskia_direct_context_t *ctx); // (GrDirectContext *ctx)
void Reskia_DirectContext_Release(reskia_direct_context_t *ctx); // owned: 呼び出し側が保持する参照を release する (GrDirectContext *ctx)

reskia_graphite_context_t *Reskia_GraphiteContext_MakeMetal(void *device, void *queue); // owned: 呼び出し側が Reskia_GraphiteContext_Release で解放する (void *device, void *queue) -> skgpu::graphite::Context *
reskia_graphite_context_t *Reskia_GraphiteContext_MakeVulkan(const void *backend_context); // owned: 呼び出し側が Reskia_GraphiteContext_Release で解放する (const skgpu::VulkanBackendContext *backend_context) -> skgpu::graphite::Context *
reskia_graphite_recorder_t *Reskia_GraphiteContext_MakeRecorder(reskia_graphite_context_t *ctx); // owned: 呼び出し側が Reskia_GraphiteRecorder_Release で解放する (skgpu::graphite::Context *ctx) -> skgpu::graphite::Recorder *
bool Reskia_GraphiteContext_InsertRecordingAndSubmit(reskia_graphite_context_t *ctx, reskia_graphite_recorder_t *recorder, bool sync_cpu); // (skgpu::graphite::Context *ctx, skgpu::graphite::Recorder *recorder, bool sync_cpu) -> bool
void Reskia_GraphiteRecorder_Release(reskia_graphite_recorder_t *recorder); // owned: 呼び出し側が保持する recorder を解放する (skgpu::graphite::Recorder *recorder)
void Reskia_GraphiteContext_Release(reskia_graphite_context_t *ctx); // owned: 呼び出し側が保持する context を解放する (skgpu::graphite::Context *ctx)

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_GPU_CONTEXT_H
