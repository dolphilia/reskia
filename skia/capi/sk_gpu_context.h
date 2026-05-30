//
// Created by dolphilia on 2026/02/17.
//

#ifndef RAIA_SKIA_SK_GPU_CONTEXT_H
#define RAIA_SKIA_SK_GPU_CONTEXT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sk_async_read_result.h"
#include "sk_i_size.h"
#include "sk_yuva_info.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_capabilities.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_required_properties.h"

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_gr_backend_format_t reskia_gr_backend_format_t;
typedef struct reskia_gr_backend_render_target_t reskia_gr_backend_render_target_t;
typedef struct reskia_gr_backend_semaphore_t reskia_gr_backend_semaphore_t;
typedef struct reskia_gr_backend_texture_t reskia_gr_backend_texture_t;
typedef struct reskia_gr_context_options_t reskia_gr_context_options_t;
typedef struct reskia_shader_error_handler_t reskia_shader_error_handler_t;
typedef struct reskia_gr_external_texture_t reskia_gr_external_texture_t;
typedef struct reskia_gr_external_texture_generator_t reskia_gr_external_texture_generator_t;
typedef struct reskia_gr_context_thread_safe_proxy_t reskia_gr_context_thread_safe_proxy_t;
typedef struct reskia_gr_direct_context_id_t reskia_gr_direct_context_id_t;
typedef struct reskia_gr_surface_characterization_t reskia_gr_surface_characterization_t;
typedef struct reskia_graphite_backend_semaphore_t reskia_graphite_backend_semaphore_t;
typedef struct reskia_graphite_backend_texture_t reskia_graphite_backend_texture_t;
typedef struct reskia_graphite_context_id_t reskia_graphite_context_id_t;
typedef struct reskia_graphite_context_t reskia_graphite_context_t;
typedef struct reskia_graphite_context_options_t reskia_graphite_context_options_t;
typedef struct reskia_graphite_image_provider_t reskia_graphite_image_provider_t;
typedef struct reskia_graphite_recording_t reskia_graphite_recording_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_graphite_recorder_options_t reskia_graphite_recorder_options_t;
typedef struct reskia_graphite_texture_info_t reskia_graphite_texture_info_t;
typedef struct reskia_graphite_yuva_backend_texture_info_t reskia_graphite_yuva_backend_texture_info_t;
typedef struct reskia_graphite_yuva_backend_textures_t reskia_graphite_yuva_backend_textures_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_skgpu_mutable_texture_state_t reskia_skgpu_mutable_texture_state_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_surface_t reskia_surface_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;
typedef int32_t reskia_gr_purge_resource_options_t;
typedef int32_t reskia_gr_semaphores_submitted_t;
typedef int32_t reskia_sk_texture_compression_type_t;
typedef int32_t reskia_graphite_rescale_gamma_t;
typedef int32_t reskia_graphite_rescale_mode_t;
typedef int32_t reskia_graphite_yuv_color_space_t;
typedef uint32_t reskia_gpu_stats_flags_t;
typedef void (*reskia_shader_error_proc_t)(void *user_data, const char *shader, const char *errors);
typedef void (*reskia_graphite_finished_proc_t)(void *user_data, int32_t result);
typedef void (*reskia_graphite_release_proc_t)(void *user_data);
typedef sk_image_t (*reskia_graphite_image_provider_find_or_create_proc_t)(reskia_graphite_recorder_t *recorder, const reskia_image_t *image, sk_image_required_properties_t properties, void *user_data);
typedef void (*reskia_gr_external_texture_dispose_proc_t)(void *user_data, const reskia_gr_backend_texture_t *texture);
typedef reskia_gr_external_texture_t *(*reskia_gr_external_texture_generate_proc_t)(reskia_direct_context_t *recording_context, bool mipmapped, void *user_data);

typedef struct reskia_graphite_mtl_texture_info_t {
    uint32_t sample_count;
    bool mipmapped;
    uint32_t format;
    uint32_t usage;
    uint32_t storage_mode;
    bool framebuffer_only;
} reskia_graphite_mtl_texture_info_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * owned: 呼び出し側が Reskia_DirectContext_Release で解放する (void *device, void *queue) -> GrDirectContext *
 */
reskia_direct_context_t *Reskia_GaneshContext_MakeMetal(void *device, void *queue);
reskia_direct_context_t *GrDirectContext_MakeMock(); // owned; unavailable Ganesh returns NULL
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
bool GrDirectContext_canDetectNewVkPipelineCacheData(reskia_direct_context_t *ctx); // NULL input returns false
bool GrDirectContext_hasNewVkPipelineCacheData(reskia_direct_context_t *ctx); // NULL input returns false
void GrDirectContext_storeVkPipelineCacheData(reskia_direct_context_t *ctx); // NULL input is no-op
void GrDirectContext_storeVkPipelineCacheDataWithMaxSize(reskia_direct_context_t *ctx, size_t max_size); // NULL input is no-op
void GrDirectContext_resetGLTextureBindings(reskia_direct_context_t *ctx); // NULL input is no-op
reskia_gpu_stats_flags_t GrDirectContext_supportedGpuStats(reskia_direct_context_t *ctx); // NULL input returns 0
reskia_gr_direct_context_id_t *GrDirectContext_directContextID(reskia_direct_context_t *ctx); // owned; NULL input returns NULL
void GrDirectContextID_delete(reskia_gr_direct_context_id_t *context_id); // NULL input is no-op
bool GrDirectContextID_isValid(reskia_gr_direct_context_id_t *context_id); // NULL input returns false
bool GrDirectContextID_equals(reskia_gr_direct_context_id_t *context_id, reskia_gr_direct_context_id_t *other); // NULL input returns false
reskia_gr_context_thread_safe_proxy_t *GrDirectContext_threadSafeProxy(reskia_direct_context_t *ctx); // owned; NULL input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorType(reskia_direct_context_t *ctx, int width, int height, int color_type, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColor(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorTypeColor(reskia_direct_context_t *ctx, int width, int height, int color_type, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmaps(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int num_levels, int surface_origin, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmap(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int surface_origin, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmapsTopLeft(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int num_levels, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmapTopLeft(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, bool renderable, bool is_protected, const char *label, size_t label_len); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool is_protected); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithCompressionType(reskia_direct_context_t *ctx, int width, int height, int compression_type, const float color[4], bool mipmapped, bool is_protected); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithData(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const void *data, size_t data_size, bool mipmapped, bool is_protected); // owned; invalid input returns NULL
reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithCompressionTypeData(reskia_direct_context_t *ctx, int width, int height, int compression_type, const void *data, size_t data_size, bool mipmapped, bool is_protected); // owned; invalid input returns NULL
bool GrDirectContext_wait(reskia_direct_context_t *ctx, int num_semaphores, const reskia_gr_backend_semaphore_t * const *wait_semaphores, bool delete_semaphores_after_wait); // invalid input returns false
bool GrDirectContext_updateBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const float color[4]); // invalid input returns false; no callback
bool GrDirectContext_updateBackendTextureWithColorType(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, int color_type, const float color[4]); // invalid input returns false; no callback
bool GrDirectContext_updateBackendTextureFromPixmaps(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels, int surface_origin); // invalid input returns false; no callback
bool GrDirectContext_updateBackendTextureFromPixmap(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int surface_origin); // invalid input returns false; no callback
bool GrDirectContext_updateBackendTextureFromPixmapsTopLeft(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels); // invalid input returns false; no callback
bool GrDirectContext_updateCompressedBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const float color[4]); // invalid input returns false; no callback
bool GrDirectContext_updateCompressedBackendTextureWithData(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const void *data, size_t data_size); // invalid input returns false; no callback
bool GrDirectContext_setBackendTextureState(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_skgpu_mutable_texture_state_t *state, reskia_skgpu_mutable_texture_state_t *previous_state); // invalid input returns false; no callback
bool GrDirectContext_setBackendRenderTargetState(reskia_direct_context_t *ctx, const reskia_gr_backend_render_target_t *render_target, const reskia_skgpu_mutable_texture_state_t *state, reskia_skgpu_mutable_texture_state_t *previous_state); // invalid input returns false; no callback
bool GrDirectContext_precompileShader(reskia_direct_context_t *ctx, const reskia_data_t *key, const reskia_data_t *data); // invalid input returns false
void GrDirectContext_deleteBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture); // NULL input is no-op

bool GrRecordingContext_abandoned(reskia_direct_context_t *ctx); // NULL input returns true
bool GrRecordingContext_colorTypeSupportedAsSurface(reskia_direct_context_t *ctx, int color_type); // NULL input returns false
int GrRecordingContext_maxTextureSize(reskia_direct_context_t *ctx); // NULL input returns 0
int GrRecordingContext_maxRenderTargetSize(reskia_direct_context_t *ctx); // NULL input returns 0
bool GrRecordingContext_colorTypeSupportedAsImage(reskia_direct_context_t *ctx, int color_type); // NULL input returns false
bool GrRecordingContext_supportsProtectedContent(reskia_direct_context_t *ctx); // NULL input returns false
int GrRecordingContext_maxSurfaceSampleCountForColorType(reskia_direct_context_t *ctx, int color_type); // NULL input returns 0
const_sk_capabilities_t GrRecordingContext_skCapabilities(reskia_direct_context_t *ctx); // owned handle; NULL input returns 0

void GrContextThreadSafeProxy_release(reskia_gr_context_thread_safe_proxy_t *proxy); // owned; NULL input is no-op
reskia_gr_backend_format_t *GrContextThreadSafeProxy_defaultBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type, bool renderable); // owned; NULL input returns NULL
reskia_gr_backend_format_t *GrContextThreadSafeProxy_compressedBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int compression_type); // owned; NULL input returns NULL
int GrContextThreadSafeProxy_maxSurfaceSampleCountForColorType(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type); // NULL input returns 0
bool GrContextThreadSafeProxy_isValid(reskia_gr_context_thread_safe_proxy_t *proxy); // NULL input returns false
bool GrContextThreadSafeProxy_equals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other); // NULL input returns false
bool GrContextThreadSafeProxy_notEquals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other); // NULL input returns false
reskia_gr_surface_characterization_t *GrContextThreadSafeProxy_createCharacterization(reskia_gr_context_thread_safe_proxy_t *proxy, size_t cache_max_resource_bytes, const reskia_image_info_t *image_info, const reskia_gr_backend_format_t *backend_format, int sample_count, int origin, const reskia_surface_props_t *surface_props, bool is_mipmapped, bool will_use_gl_fbo0, bool is_textureable, bool is_protected, bool vk_rt_supports_input_attachment, bool for_vulkan_secondary_command_buffer); // owned; invalid input returns NULL

reskia_gr_context_options_t *GrContextOptions_new(); // owned
reskia_gr_context_options_t *GrContextOptions_newCopy(const reskia_gr_context_options_t *options); // owned; NULL returns NULL
void GrContextOptions_delete(reskia_gr_context_options_t *options); // NULL input is no-op
bool GrContextOptions_suppressPrints(const reskia_gr_context_options_t *options); // NULL input returns false
void GrContextOptions_setSuppressPrints(reskia_gr_context_options_t *options, bool suppress); // NULL input is no-op
void GrContextOptions_setShaderErrorHandler(reskia_gr_context_options_t *options, reskia_shader_error_handler_t *handler); // borrowed handler; NULL clears

reskia_shader_error_handler_t *ShaderErrorHandler_new(reskia_shader_error_proc_t proc, void *user_data, reskia_graphite_release_proc_t release_proc); // owned; NULL proc returns NULL
void ShaderErrorHandler_delete(reskia_shader_error_handler_t *handler); // owned; NULL input is no-op
void ShaderErrorHandler_compileError(reskia_shader_error_handler_t *handler, const char *shader, const char *errors); // NULL handler/proc is no-op

reskia_gr_external_texture_t *GrExternalTexture_new(const reskia_gr_backend_texture_t *texture, reskia_gr_external_texture_dispose_proc_t dispose_proc, void *user_data, reskia_graphite_release_proc_t release_proc); // owned; texture required
void GrExternalTexture_delete(reskia_gr_external_texture_t *texture); // NULL input is no-op; disposes once
reskia_gr_backend_texture_t *GrExternalTexture_getBackendTexture(reskia_gr_external_texture_t *texture); // owned copy; invalid input returns NULL
void GrExternalTexture_dispose(reskia_gr_external_texture_t *texture); // idempotent; NULL input is no-op
reskia_gr_external_texture_generator_t *GrExternalTextureGenerator_new(const reskia_image_info_t *image_info, reskia_gr_external_texture_generate_proc_t generate_proc, void *user_data, reskia_graphite_release_proc_t release_proc); // owned; image_info/proc required
void GrExternalTextureGenerator_delete(reskia_gr_external_texture_generator_t *generator); // NULL input is no-op; do not call after SkImages_DeferredFromTextureGenerator consumes it
reskia_gr_external_texture_t *GrExternalTextureGenerator_generateExternalTexture(reskia_gr_external_texture_generator_t *generator, reskia_direct_context_t *recording_context, bool mipmapped); // owned; invalid input returns NULL
sk_image_t SkImages_DeferredFromTextureGenerator(reskia_gr_external_texture_generator_t *generator); // consumes generator; invalid input returns 0

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

reskia_graphite_context_options_t *Graphite_ContextOptions_new(); // owned
void Graphite_ContextOptions_delete(reskia_graphite_context_options_t *options); // NULL input is no-op
size_t Graphite_ContextOptions_gpuBudgetInBytes(const reskia_graphite_context_options_t *options); // NULL input returns 0
void Graphite_ContextOptions_setGpuBudgetInBytes(reskia_graphite_context_options_t *options, size_t budget); // NULL input is no-op

reskia_graphite_recorder_options_t *Graphite_RecorderOptions_new(); // owned
reskia_graphite_recorder_options_t *Graphite_RecorderOptions_newCopy(const reskia_graphite_recorder_options_t *options); // owned; NULL returns NULL
void Graphite_RecorderOptions_delete(reskia_graphite_recorder_options_t *options); // NULL input is no-op
size_t Graphite_RecorderOptions_gpuBudgetInBytes(const reskia_graphite_recorder_options_t *options); // NULL input returns 0
void Graphite_RecorderOptions_setGpuBudgetInBytes(reskia_graphite_recorder_options_t *options, size_t budget); // NULL input is no-op
void Graphite_RecorderOptions_setImageProvider(reskia_graphite_recorder_options_t *options, reskia_graphite_image_provider_t *provider); // retains provider; NULL provider clears

int Graphite_Context_backend(reskia_graphite_context_t *ctx); // NULL input returns 0
reskia_graphite_recorder_t *Graphite_Context_makeRecorder(reskia_graphite_context_t *ctx); // owned; NULL input returns NULL
reskia_graphite_recorder_t *Graphite_Context_makeRecorderWithOptions(reskia_graphite_context_t *ctx, const reskia_graphite_recorder_options_t *options); // owned; invalid input returns NULL
bool Graphite_Context_submit(reskia_graphite_context_t *ctx, bool sync_cpu); // NULL input returns false
bool Graphite_Context_hasUnfinishedGpuWork(reskia_graphite_context_t *ctx); // NULL input returns false
bool Graphite_Context_insertRecording(reskia_graphite_context_t *ctx, reskia_graphite_recording_t *recording); // borrowed recording; NULL input returns false
void Graphite_Context_asyncRescaleAndReadPixelsFromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, const reskia_image_info_t *dst_info, const reskia_i_rect_t *src_rect, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_asyncRescaleAndReadPixelsFromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, const reskia_image_info_t *dst_info, const reskia_i_rect_t *src_rect, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_asyncRescaleAndReadPixelsYUV420FromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_asyncRescaleAndReadPixelsYUV420FromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context); // invalid input invokes callback with NULL result
void Graphite_Context_checkAsyncWorkCompletion(reskia_graphite_context_t *ctx); // NULL input is no-op
void Graphite_Context_deleteBackendTexture(reskia_graphite_context_t *ctx, const reskia_graphite_backend_texture_t *texture); // NULL input is no-op
void Graphite_Context_freeGpuResources(reskia_graphite_context_t *ctx); // NULL input is no-op
void Graphite_Context_performDeferredCleanup(reskia_graphite_context_t *ctx, int64_t ms_not_used); // invalid input is no-op
size_t Graphite_Context_currentBudgetedBytes(reskia_graphite_context_t *ctx); // NULL input returns 0
size_t Graphite_Context_currentPurgeableBytes(reskia_graphite_context_t *ctx); // NULL input returns 0
size_t Graphite_Context_maxBudgetedBytes(reskia_graphite_context_t *ctx); // NULL input returns 0
void Graphite_Context_setMaxBudgetedBytes(reskia_graphite_context_t *ctx, size_t bytes); // NULL input is no-op
void Graphite_Context_dumpMemoryStatistics(reskia_graphite_context_t *ctx, reskia_trace_memory_dump_t *trace_memory_dump); // NULL input is no-op
bool Graphite_Context_supportsProtectedContent(reskia_graphite_context_t *ctx); // NULL input returns false
bool Graphite_Context_isDeviceLost(reskia_graphite_context_t *ctx); // NULL input returns false
int Graphite_Context_maxTextureSize(reskia_graphite_context_t *ctx); // NULL input returns 0
reskia_gpu_stats_flags_t Graphite_Context_supportedGpuStats(reskia_graphite_context_t *ctx); // NULL input returns 0
reskia_graphite_context_id_t *Graphite_Context_contextID(reskia_graphite_context_t *ctx); // owned; NULL input returns NULL
void Graphite_ContextID_delete(reskia_graphite_context_id_t *context_id); // NULL input is no-op
bool Graphite_ContextID_isValid(const reskia_graphite_context_id_t *context_id); // NULL input returns false
bool Graphite_ContextID_equals(const reskia_graphite_context_id_t *context_id, const reskia_graphite_context_id_t *other); // NULL input returns false

void Graphite_Recorder_freeGpuResources(reskia_graphite_recorder_t *recorder); // NULL input is no-op
void Graphite_Recorder_performDeferredCleanup(reskia_graphite_recorder_t *recorder, int64_t ms_not_used); // invalid input is no-op
size_t Graphite_Recorder_currentBudgetedBytes(reskia_graphite_recorder_t *recorder); // NULL input returns 0
size_t Graphite_Recorder_currentPurgeableBytes(reskia_graphite_recorder_t *recorder); // NULL input returns 0
size_t Graphite_Recorder_maxBudgetedBytes(reskia_graphite_recorder_t *recorder); // NULL input returns 0
void Graphite_Recorder_setMaxBudgetedBytes(reskia_graphite_recorder_t *recorder, size_t bytes); // NULL input is no-op
void Graphite_Recorder_dumpMemoryStatistics(reskia_graphite_recorder_t *recorder, reskia_trace_memory_dump_t *trace_memory_dump); // NULL input is no-op
bool Graphite_Recorder_addFinishInfo(reskia_graphite_recorder_t *recorder, reskia_graphite_finished_proc_t proc, void *user_data, reskia_graphite_release_proc_t release_proc); // owns user_data until callback if true; invalid input returns false
reskia_graphite_image_provider_t *Graphite_Recorder_clientImageProvider(reskia_graphite_recorder_t *recorder); // borrowed; NULL input returns NULL
int Graphite_Recorder_backend(reskia_graphite_recorder_t *recorder); // NULL input returns 0
int Graphite_Recorder_maxTextureSize(reskia_graphite_recorder_t *recorder); // NULL input returns 0
reskia_canvas_t *Graphite_Recorder_makeDeferredCanvas(reskia_graphite_recorder_t *recorder, const reskia_image_info_t *image_info, const reskia_graphite_texture_info_t *info); // borrowed until next snap/release; invalid input returns NULL
reskia_graphite_recording_t *Graphite_Recorder_snap(reskia_graphite_recorder_t *recorder); // owned; NULL/no recording returns NULL
reskia_graphite_backend_texture_t *Graphite_Recorder_createBackendTexture(reskia_graphite_recorder_t *recorder, sk_i_size_t dimensions, const reskia_graphite_texture_info_t *info); // owned; invalid input returns NULL
bool Graphite_Recorder_updateBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels); // invalid input returns false
bool Graphite_Recorder_updateCompressedBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture, const void *data, size_t data_size); // invalid input returns false
void Graphite_Recorder_deleteBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture); // NULL input is no-op
void Graphite_Recording_delete(reskia_graphite_recording_t *recording); // NULL input is no-op

reskia_graphite_image_provider_t *Graphite_ImageProvider_new(reskia_graphite_image_provider_find_or_create_proc_t proc, void *user_data, reskia_graphite_release_proc_t release_proc); // owned; proc required
void Graphite_ImageProvider_ref(reskia_graphite_image_provider_t *provider); // NULL input is no-op
void Graphite_ImageProvider_unref(reskia_graphite_image_provider_t *provider); // NULL input is no-op
sk_image_t Graphite_ImageProvider_findOrCreate(reskia_graphite_image_provider_t *provider, reskia_graphite_recorder_t *recorder, const reskia_image_t *image, sk_image_required_properties_t properties); // caller-owned image; invalid input returns 0

reskia_graphite_texture_info_t *Graphite_TextureInfo_new(); // owned; invalid default info
reskia_graphite_texture_info_t *Graphite_TextureInfo_newMtl(const reskia_graphite_mtl_texture_info_t *info); // owned; NULL/unavailable Metal returns NULL
bool Graphite_MtlTextureInfo_new(reskia_graphite_mtl_texture_info_t *out_info); // out_info required
bool Graphite_MtlTextureInfo_newTexture(void *texture, reskia_graphite_mtl_texture_info_t *out_info); // borrowed texture; NULL/unavailable Metal returns false
bool Graphite_MtlTextureInfo_newWithValues(uint32_t sample_count, bool mipmapped, uint32_t format, uint32_t usage, uint32_t storage_mode, bool framebuffer_only, reskia_graphite_mtl_texture_info_t *out_info); // out_info required
reskia_graphite_texture_info_t *Graphite_TextureInfo_newCopy(const reskia_graphite_texture_info_t *info); // owned; NULL returns NULL
void Graphite_TextureInfo_delete(reskia_graphite_texture_info_t *info); // NULL input is no-op
bool Graphite_TextureInfo_equals(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other); // NULL input returns false
bool Graphite_TextureInfo_notEquals(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other); // NULL input returns false
bool Graphite_TextureInfo_isValid(const reskia_graphite_texture_info_t *info); // NULL input returns false
int Graphite_TextureInfo_backend(const reskia_graphite_texture_info_t *info); // NULL input returns 0
uint32_t Graphite_TextureInfo_numSamples(const reskia_graphite_texture_info_t *info); // NULL input returns 0
bool Graphite_TextureInfo_mipmapped(const reskia_graphite_texture_info_t *info); // NULL input returns false
bool Graphite_TextureInfo_isProtected(const reskia_graphite_texture_info_t *info); // NULL input returns false
bool Graphite_TextureInfo_getMtlTextureInfo(const reskia_graphite_texture_info_t *info, reskia_graphite_mtl_texture_info_t *out_info); // NULL/non-Metal returns false
bool Graphite_TextureInfo_canBeFulfilledBy(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other); // NULL input returns false
reskia_string_t *Graphite_TextureInfo_toString(const reskia_graphite_texture_info_t *info); // owned; NULL input returns NULL

reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_new(); // owned; invalid default semaphore
reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_newMtl(void *event, uint64_t value); // owned; unavailable Metal returns NULL
reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_newCopy(const reskia_graphite_backend_semaphore_t *semaphore); // owned; NULL returns NULL
void Graphite_BackendSemaphore_delete(reskia_graphite_backend_semaphore_t *semaphore); // NULL input is no-op
bool Graphite_BackendSemaphore_isValid(const reskia_graphite_backend_semaphore_t *semaphore); // NULL input returns false
int Graphite_BackendSemaphore_backend(const reskia_graphite_backend_semaphore_t *semaphore); // NULL input returns 0
void *Graphite_BackendSemaphore_getMtlEvent(const reskia_graphite_backend_semaphore_t *semaphore); // NULL/non-Metal returns NULL
uint64_t Graphite_BackendSemaphore_getMtlValue(const reskia_graphite_backend_semaphore_t *semaphore); // NULL/non-Metal returns 0

reskia_graphite_backend_texture_t *Graphite_BackendTexture_new(); // owned; invalid default texture
reskia_graphite_backend_texture_t *Graphite_BackendTexture_newMtl(sk_i_size_t dimensions, void *mtl_texture); // owned; invalid input/unavailable Metal returns NULL
reskia_graphite_backend_texture_t *Graphite_BackendTexture_newCopy(const reskia_graphite_backend_texture_t *texture); // owned; NULL returns NULL
void Graphite_BackendTexture_delete(reskia_graphite_backend_texture_t *texture); // NULL input is no-op
bool Graphite_BackendTexture_equals(const reskia_graphite_backend_texture_t *texture, const reskia_graphite_backend_texture_t *other); // NULL input returns false
bool Graphite_BackendTexture_notEquals(const reskia_graphite_backend_texture_t *texture, const reskia_graphite_backend_texture_t *other); // NULL input returns false
bool Graphite_BackendTexture_isValid(const reskia_graphite_backend_texture_t *texture); // NULL input returns false
int Graphite_BackendTexture_backend(const reskia_graphite_backend_texture_t *texture); // NULL input returns 0
sk_i_size_t Graphite_BackendTexture_dimensions(const reskia_graphite_backend_texture_t *texture); // returns handle; NULL input returns 0
reskia_graphite_texture_info_t *Graphite_BackendTexture_info(const reskia_graphite_backend_texture_t *texture); // owned; NULL input returns NULL
void *Graphite_BackendTexture_getMtlTexture(const reskia_graphite_backend_texture_t *texture); // NULL/non-Metal returns NULL

reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_new(); // owned; invalid default info
reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_newWithRecorderYUVAInfoTextureInfos(const reskia_graphite_recorder_t *recorder, const reskia_yuva_info_t *info, const reskia_graphite_texture_info_t *const *texture_infos, int texture_info_count, bool mipmapped); // owned; invalid input returns NULL
reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_newCopy(const reskia_graphite_yuva_backend_texture_info_t *info); // owned; NULL returns NULL
void Graphite_YUVABackendTextureInfo_delete(reskia_graphite_yuva_backend_texture_info_t *info); // NULL input is no-op
bool Graphite_YUVABackendTextureInfo_equals(const reskia_graphite_yuva_backend_texture_info_t *info, const reskia_graphite_yuva_backend_texture_info_t *other); // NULL input returns false
bool Graphite_YUVABackendTextureInfo_notEquals(const reskia_graphite_yuva_backend_texture_info_t *info, const reskia_graphite_yuva_backend_texture_info_t *other); // NULL input returns false
reskia_graphite_texture_info_t *Graphite_YUVABackendTextureInfo_planeTextureInfo(const reskia_graphite_yuva_backend_texture_info_t *info, int index); // owned; invalid input returns NULL
reskia_yuva_info_t *Graphite_YUVABackendTextureInfo_yuvaInfo(const reskia_graphite_yuva_backend_texture_info_t *info); // owned; NULL input returns NULL
int Graphite_YUVABackendTextureInfo_yuvColorSpace(const reskia_graphite_yuva_backend_texture_info_t *info); // NULL input returns -1
bool Graphite_YUVABackendTextureInfo_mipmapped(const reskia_graphite_yuva_backend_texture_info_t *info); // NULL input returns false
int Graphite_YUVABackendTextureInfo_numPlanes(const reskia_graphite_yuva_backend_texture_info_t *info); // NULL input returns 0
bool Graphite_YUVABackendTextureInfo_isValid(const reskia_graphite_yuva_backend_texture_info_t *info); // NULL input returns false
bool Graphite_YUVABackendTextureInfo_toYUVALocations(const reskia_graphite_yuva_backend_texture_info_t *info, reskia_yuva_location_t *locations); // locations[4]; invalid input clears locations and returns false

reskia_graphite_yuva_backend_textures_t *Graphite_YUVABackendTextures_new(); // owned; invalid default textures
reskia_graphite_yuva_backend_textures_t *Graphite_YUVABackendTextures_newWithRecorderYUVAInfoTextures(const reskia_graphite_recorder_t *recorder, const reskia_yuva_info_t *info, const reskia_graphite_backend_texture_t *const *textures, int texture_count); // owned; invalid input returns NULL
void Graphite_YUVABackendTextures_delete(reskia_graphite_yuva_backend_textures_t *textures); // NULL input is no-op
int Graphite_YUVABackendTextures_planeTextures(const reskia_graphite_yuva_backend_textures_t *textures, reskia_graphite_backend_texture_t **out_textures, int capacity); // fills owned texture copies; returns plane count, invalid input returns 0
reskia_graphite_backend_texture_t *Graphite_YUVABackendTextures_planeTexture(const reskia_graphite_yuva_backend_textures_t *textures, int index); // owned; invalid input returns NULL
reskia_yuva_info_t *Graphite_YUVABackendTextures_yuvaInfo(const reskia_graphite_yuva_backend_textures_t *textures); // owned; NULL input returns NULL
int Graphite_YUVABackendTextures_yuvColorSpace(const reskia_graphite_yuva_backend_textures_t *textures); // NULL input returns -1
int Graphite_YUVABackendTextures_numPlanes(const reskia_graphite_yuva_backend_textures_t *textures); // NULL input returns 0
bool Graphite_YUVABackendTextures_isValid(const reskia_graphite_yuva_backend_textures_t *textures); // NULL input returns false
bool Graphite_YUVABackendTextures_toYUVALocations(const reskia_graphite_yuva_backend_textures_t *textures, reskia_yuva_location_t *locations); // locations[4]; invalid input clears locations and returns false

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_GPU_CONTEXT_H
