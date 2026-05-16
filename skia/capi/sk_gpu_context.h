//
// Created by dolphilia on 2026/02/17.
//

#ifndef RAIA_SKIA_SK_GPU_CONTEXT_H
#define RAIA_SKIA_SK_GPU_CONTEXT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_gr_backend_format_t reskia_gr_backend_format_t;
typedef struct reskia_gr_backend_texture_t reskia_gr_backend_texture_t;
typedef struct reskia_gr_context_thread_safe_proxy_t reskia_gr_context_thread_safe_proxy_t;
typedef struct reskia_gr_direct_context_id_t reskia_gr_direct_context_id_t;
typedef struct reskia_gr_surface_characterization_t reskia_gr_surface_characterization_t;
typedef struct reskia_graphite_context_t reskia_graphite_context_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;
typedef int32_t reskia_gr_purge_resource_options_t;
typedef int32_t reskia_gr_semaphores_submitted_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * owned: 呼び出し側が Reskia_DirectContext_Release で解放する (void *device, void *queue) -> GrDirectContext *
 */
reskia_direct_context_t *Reskia_GaneshContext_MakeMetal(void *device, void *queue);
/**
 * owned: 呼び出し側が Reskia_DirectContext_Release で解放する (const GrVkBackendContext *backend_context) -> GrDirectContext *
 */
reskia_direct_context_t *Reskia_GaneshContext_MakeVulkan(const void *backend_context);
void Reskia_DirectContext_FlushAndSubmit(reskia_direct_context_t *ctx, bool sync_cpu); // (GrDirectContext *ctx, bool sync_cpu)
void Reskia_DirectContext_Abandon(reskia_direct_context_t *ctx); // (GrDirectContext *ctx)
void Reskia_DirectContext_Release(reskia_direct_context_t *ctx); // owned: 呼び出し側が保持する参照を release する (GrDirectContext *ctx)

void GrDirectContext_resetContext(reskia_direct_context_t *ctx, uint32_t state); // NULL input is no-op
void GrDirectContext_abandonContext(reskia_direct_context_t *ctx); // NULL input is no-op
bool GrDirectContext_abandoned(reskia_direct_context_t *ctx); // NULL input returns true
bool GrDirectContext_isDeviceLost(reskia_direct_context_t *ctx); // NULL input returns false
bool GrDirectContext_oomed(reskia_direct_context_t *ctx); // NULL input returns false
void GrDirectContext_releaseResourcesAndAbandonContext(reskia_direct_context_t *ctx); // NULL input is no-op
bool GrDirectContext_getResourceCacheLimits(reskia_direct_context_t *ctx, int *maxResources, size_t *maxResourceBytes); // NULL ctx returns false
size_t GrDirectContext_getResourceCacheLimit(reskia_direct_context_t *ctx); // NULL input returns 0
bool GrDirectContext_getResourceCacheUsage(reskia_direct_context_t *ctx, int *resourceCount, size_t *resourceBytes); // NULL ctx returns false
size_t GrDirectContext_getResourceCachePurgeableBytes(reskia_direct_context_t *ctx); // NULL input returns 0
void GrDirectContext_setResourceCacheLimits(reskia_direct_context_t *ctx, int maxResources, size_t maxResourceBytes); // NULL input is no-op
void GrDirectContext_setResourceCacheLimit(reskia_direct_context_t *ctx, size_t maxResourceBytes); // NULL input is no-op
void GrDirectContext_freeGpuResources(reskia_direct_context_t *ctx); // NULL input is no-op
void GrDirectContext_performDeferredCleanup(reskia_direct_context_t *ctx, int64_t msNotUsed, reskia_gr_purge_resource_options_t options); // invalid input is no-op
void GrDirectContext_purgeResourcesNotUsedInMs(reskia_direct_context_t *ctx, int64_t msNotUsed); // invalid input is no-op
void GrDirectContext_purgeUnlockedResources(reskia_direct_context_t *ctx, reskia_gr_purge_resource_options_t options); // invalid input is no-op
void GrDirectContext_purgeUnlockedResourcesWithBytes(reskia_direct_context_t *ctx, size_t bytesToPurge, bool preferScratchResources); // NULL input is no-op
void GrDirectContext_flushAndSubmit(reskia_direct_context_t *ctx, bool sync_cpu); // NULL input is no-op
reskia_gr_semaphores_submitted_t GrDirectContext_flush(reskia_direct_context_t *ctx); // NULL input returns -1
bool GrDirectContext_submit(reskia_direct_context_t *ctx, bool sync_cpu); // NULL input returns false
void GrDirectContext_checkAsyncWorkCompletion(reskia_direct_context_t *ctx); // NULL input is no-op
void GrDirectContext_dumpMemoryStatistics(reskia_direct_context_t *ctx, reskia_trace_memory_dump_t *traceMemoryDump); // NULL input is no-op
reskia_string_t *GrDirectContext_dump(reskia_direct_context_t *ctx); // owned; NULL input or SK_ENABLE_DUMP_GPU-disabled build returns NULL
bool GrDirectContext_supportsDistanceFieldText(reskia_direct_context_t *ctx); // NULL input returns false
void GrDirectContext_storeVkPipelineCacheData(reskia_direct_context_t *ctx); // NULL input is no-op
reskia_gr_direct_context_id_t *GrDirectContext_directContextID(reskia_direct_context_t *ctx); // owned; NULL input returns NULL
void GrDirectContextID_delete(reskia_gr_direct_context_id_t *context_id); // NULL input is no-op
bool GrDirectContextID_isValid(reskia_gr_direct_context_id_t *context_id); // NULL input returns false
bool GrDirectContextID_equals(reskia_gr_direct_context_id_t *context_id, reskia_gr_direct_context_id_t *other); // NULL input returns false
reskia_gr_context_thread_safe_proxy_t *GrDirectContext_threadSafeProxy(reskia_direct_context_t *ctx); // owned; NULL input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorType(reskia_direct_context_t *ctx, int width, int height, int color_type, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColor(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorTypeColor(reskia_direct_context_t *ctx, int width, int height, int color_type, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool is_protected); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithCompressionType(reskia_direct_context_t *ctx, int width, int height, int compression_type, const float color[4], bool mipmapped, bool is_protected); // owned; invalid input returns NULL
void GrDirectContext_deleteBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture); // NULL input is no-op

bool GrRecordingContext_abandoned(reskia_direct_context_t *ctx); // NULL input returns true
bool GrRecordingContext_colorTypeSupportedAsSurface(reskia_direct_context_t *ctx, int color_type); // NULL input returns false
int GrRecordingContext_maxTextureSize(reskia_direct_context_t *ctx); // NULL input returns 0
int GrRecordingContext_maxRenderTargetSize(reskia_direct_context_t *ctx); // NULL input returns 0
bool GrRecordingContext_colorTypeSupportedAsImage(reskia_direct_context_t *ctx, int color_type); // NULL input returns false
bool GrRecordingContext_supportsProtectedContent(reskia_direct_context_t *ctx); // NULL input returns false
int GrRecordingContext_maxSurfaceSampleCountForColorType(reskia_direct_context_t *ctx, int color_type); // NULL input returns 0

void GrContextThreadSafeProxy_release(reskia_gr_context_thread_safe_proxy_t *proxy); // owned; NULL input is no-op
reskia_gr_backend_format_t *GrContextThreadSafeProxy_defaultBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type, bool renderable); // owned; NULL input returns NULL
reskia_gr_backend_format_t *GrContextThreadSafeProxy_compressedBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int compression_type); // owned; NULL input returns NULL
int GrContextThreadSafeProxy_maxSurfaceSampleCountForColorType(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type); // NULL input returns 0
bool GrContextThreadSafeProxy_isValid(reskia_gr_context_thread_safe_proxy_t *proxy); // NULL input returns false
bool GrContextThreadSafeProxy_equals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other); // NULL input returns false
bool GrContextThreadSafeProxy_notEquals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other); // NULL input returns false
reskia_gr_surface_characterization_t *GrContextThreadSafeProxy_createCharacterization(reskia_gr_context_thread_safe_proxy_t *proxy, size_t cache_max_resource_bytes, const reskia_image_info_t *image_info, const reskia_gr_backend_format_t *backend_format, int sample_count, int origin, const reskia_surface_props_t *surface_props, bool is_mipmapped, bool will_use_gl_fbo0, bool is_textureable, bool is_protected, bool vk_rt_supports_input_attachment, bool for_vulkan_secondary_command_buffer); // owned; invalid input returns NULL

reskia_gr_surface_characterization_t *GrSurfaceCharacterization_new(); // owned; invalid default characterization
reskia_gr_surface_characterization_t *GrSurfaceCharacterization_newCopy(const reskia_gr_surface_characterization_t *characterization); // owned; NULL returns NULL
void GrSurfaceCharacterization_delete(reskia_gr_surface_characterization_t *characterization); // NULL input is no-op
bool GrSurfaceCharacterization_equals(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_surface_characterization_t *other); // NULL input returns false
bool GrSurfaceCharacterization_notEquals(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_surface_characterization_t *other); // NULL input returns false
bool GrSurfaceCharacterization_isValid(const reskia_gr_surface_characterization_t *characterization); // NULL input returns false
int GrSurfaceCharacterization_width(const reskia_gr_surface_characterization_t *characterization); // NULL input returns 0
int GrSurfaceCharacterization_height(const reskia_gr_surface_characterization_t *characterization); // NULL input returns 0
int GrSurfaceCharacterization_colorType(const reskia_gr_surface_characterization_t *characterization); // NULL input returns 0
int GrSurfaceCharacterization_sampleCount(const reskia_gr_surface_characterization_t *characterization); // NULL input returns 0
int GrSurfaceCharacterization_origin(const reskia_gr_surface_characterization_t *characterization); // NULL input returns 0
bool GrSurfaceCharacterization_isTextureable(const reskia_gr_surface_characterization_t *characterization); // NULL input returns false
bool GrSurfaceCharacterization_isMipMapped(const reskia_gr_surface_characterization_t *characterization); // NULL input returns false
bool GrSurfaceCharacterization_isCompatible(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_backend_texture_t *texture); // NULL input returns false
reskia_gr_backend_format_t *GrSurfaceCharacterization_backendFormat(const reskia_gr_surface_characterization_t *characterization); // owned; NULL input returns NULL

/**
 * owned: 呼び出し側が Reskia_GraphiteContext_Release で解放する (void *device, void *queue) -> skgpu::graphite::Context *
 */
reskia_graphite_context_t *Reskia_GraphiteContext_MakeMetal(void *device, void *queue);
/**
 * owned: 呼び出し側が Reskia_GraphiteContext_Release で解放する (const skgpu::VulkanBackendContext *backend_context) -> skgpu::graphite::Context *
 */
reskia_graphite_context_t *Reskia_GraphiteContext_MakeVulkan(const void *backend_context);
/**
 * owned: 呼び出し側が Reskia_GraphiteRecorder_Release で解放する (skgpu::graphite::Context *ctx) -> skgpu::graphite::Recorder *
 */
reskia_graphite_recorder_t *Reskia_GraphiteContext_MakeRecorder(reskia_graphite_context_t *ctx);
bool Reskia_GraphiteContext_InsertRecordingAndSubmit(reskia_graphite_context_t *ctx, reskia_graphite_recorder_t *recorder, bool sync_cpu); // (skgpu::graphite::Context *ctx, skgpu::graphite::Recorder *recorder, bool sync_cpu) -> bool
void Reskia_GraphiteRecorder_Release(reskia_graphite_recorder_t *recorder); // owned: 呼び出し側が保持する recorder を解放する (skgpu::graphite::Recorder *recorder)
void Reskia_GraphiteContext_Release(reskia_graphite_context_t *ctx); // owned: 呼び出し側が保持する context を解放する (skgpu::graphite::Context *ctx)

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_GPU_CONTEXT_H
