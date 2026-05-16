#include <cstdio>

#import <Metal/Metal.h>

#include "capi/sk_gpu_backend_surface.h"
#include "capi/sk_gpu_context.h"
#include "capi/sk_graphics.h"
#include "capi/sk_i_size.h"
#include "capi/sk_string.h"
#include "handles/static_sk_i_size.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[gpu-context-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_context_create_destroy() {
    reskia_gpu_backend_texture_handle_t texture_handle = {};
    reskia_gpu_backend_render_target_handle_t render_target_handle = {};
    if (!check(!GrBackendFormat_isValid(nullptr) &&
               !GrBackendTexture_isValid(nullptr) &&
               !GrBackendRenderTarget_isValid(nullptr) &&
               GrBackendFormat_toStr(nullptr) == nullptr &&
               GrBackendTexture_dimensions(nullptr) == 0 &&
               GrBackendTexture_getLabel(nullptr) == nullptr &&
               GrBackendRenderTarget_dimensions(nullptr) == 0 &&
               !GrBackendFormat_desc(nullptr, nullptr) &&
               !GrBackendTexture_getMtlTextureInfo(nullptr, nullptr) &&
               !GrBackendTexture_getMockTextureInfo(nullptr, nullptr) &&
               !GrBackendRenderTarget_getMtlTextureInfo(nullptr, nullptr) &&
               !GrBackendRenderTarget_getMockRenderTargetInfo(nullptr, nullptr) &&
               GrBackendSemaphore_newCopy(nullptr) == nullptr &&
               !GrBackendSemaphore_isInitialized(nullptr) &&
               GrBackendSemaphore_backend(nullptr) == 0 &&
               GrBackendSemaphore_vkSemaphore(nullptr) == 0 &&
               GrBackendSemaphore_mtlSemaphore(nullptr) == nullptr &&
               GrBackendSemaphore_mtlValue(nullptr) == 0 &&
               MutableTextureState_newCopy(nullptr) == nullptr &&
               !MutableTextureState_isValid(nullptr) &&
               MutableTextureState_backend(nullptr) == 0 &&
               MutableTextureState_getVkImageLayout(nullptr) == 0 &&
               MutableTextureState_getQueueFamilyIndex(nullptr) == 0 &&
               !GrBackendTexture_asHandle(nullptr, &texture_handle) &&
               texture_handle.backend_texture == nullptr &&
               !GrBackendRenderTarget_asHandle(nullptr, &render_target_handle) &&
               render_target_handle.backend_render_target == nullptr,
               "GPU backend wrappers null input")) {
        return false;
    }

#if RESKIA_TEST_GPU_GANESH
    reskia_gr_backend_format_t *mock_format = GrBackendFormat_MakeMock(4, 0, false);
    if (!check(mock_format != nullptr && GrBackendFormat_isValid(mock_format), "GrBackendFormat_MakeMock")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_color_format_desc_t format_desc = {};
    if (!check(GrBackendFormat_desc(mock_format, &format_desc) &&
               format_desc.r_bits == 8 &&
               format_desc.g_bits == 8 &&
               format_desc.b_bits == 8 &&
               format_desc.a_bits == 8,
               "GrBackendFormat_desc")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_string_t *format_description = GrBackendFormat_toStr(mock_format);
    if (format_description != nullptr && !check(SkString_c_str(format_description) != nullptr, "GrBackendFormat_toStr")) {
        SkString_delete(format_description);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    SkString_delete(format_description);
    if (!check(GrBackendFormat_asMtlFormat(mock_format) == 0, "GrBackendFormat_asMtlFormat(mock)")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_backend_format_t *texture2d_format = GrBackendFormat_makeTexture2D(mock_format);
    if (!check(texture2d_format != nullptr && GrBackendFormat_isValid(texture2d_format), "GrBackendFormat_makeTexture2D")) {
        GrBackendFormat_delete(texture2d_format);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    GrBackendFormat_delete(texture2d_format);
    GrBackendFormat_delete(mock_format);

    reskia_gr_backend_texture_t *mock_texture = GrBackendTexture_newMock(8, 4, 1, 4, 0, 101, 0);
    if (!check(mock_texture != nullptr &&
               GrBackendTexture_isValid(mock_texture) &&
               GrBackendTexture_width(mock_texture) == 8 &&
               GrBackendTexture_height(mock_texture) == 4 &&
               GrBackendTexture_hasMipmaps(mock_texture),
               "GrBackendTexture_newMock")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    const sk_i_size_t texture_dimensions = GrBackendTexture_dimensions(mock_texture);
    auto *texture_size = reinterpret_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(texture_dimensions));
    if (!check(texture_size != nullptr &&
               SkISize_width(texture_size) == 8 &&
               SkISize_height(texture_size) == 4,
               "GrBackendTexture_dimensions")) {
        static_sk_i_size_delete(texture_dimensions);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    static_sk_i_size_delete(texture_dimensions);
    reskia_string_t *texture_label = GrBackendTexture_getLabel(mock_texture);
    if (!check(texture_label != nullptr && SkString_c_str(texture_label) != nullptr, "GrBackendTexture_getLabel")) {
        SkString_delete(texture_label);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    SkString_delete(texture_label);
    reskia_gr_backend_format_t *texture_format = GrBackendTexture_getBackendFormat(mock_texture);
    if (!check(texture_format != nullptr && GrBackendFormat_isValid(texture_format), "GrBackendTexture_getBackendFormat")) {
        GrBackendFormat_delete(texture_format);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    GrBackendFormat_delete(texture_format);
    reskia_gr_mtl_texture_info_t mtl_texture_info = {reinterpret_cast<void *>(0x1)};
    if (!check(!GrBackendTexture_getMtlTextureInfo(mock_texture, &mtl_texture_info) &&
               mtl_texture_info.texture == nullptr,
               "GrBackendTexture_getMtlTextureInfo(mock)")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    reskia_gr_mock_texture_info_t texture_info = {};
    if (!check(GrBackendTexture_getMockTextureInfo(mock_texture, &texture_info) &&
               texture_info.color_type == 4 &&
               texture_info.compression_type == 0 &&
               texture_info.id == 101 &&
               texture_info.is_protected == 0,
               "GrBackendTexture_getMockTextureInfo")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *mutable_state = MutableTextureState_new();
    if (!check(mutable_state != nullptr &&
               !MutableTextureState_isValid(mutable_state) &&
               MutableTextureState_backend(mutable_state) == 0,
               "MutableTextureState default")) {
        MutableTextureState_delete(mutable_state);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    GrBackendTexture_setMutableState(mock_texture, mutable_state);
    if (!check(GrBackendTexture_asHandle(mock_texture, &texture_handle) &&
               texture_handle.backend_texture != nullptr,
               "GrBackendTexture_asHandle")) {
        MutableTextureState_delete(mutable_state);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    MutableTextureState_delete(mutable_state);
    GrBackendTexture_delete(mock_texture);

    reskia_gr_backend_render_target_t *mock_render_target = GrBackendRenderTarget_newMock(16, 12, 1, 8, 4, 202, 0);
    if (!check(mock_render_target != nullptr &&
               GrBackendRenderTarget_isValid(mock_render_target) &&
               GrBackendRenderTarget_width(mock_render_target) == 16 &&
               GrBackendRenderTarget_height(mock_render_target) == 12 &&
               GrBackendRenderTarget_sampleCnt(mock_render_target) == 1 &&
               GrBackendRenderTarget_stencilBits(mock_render_target) == 8,
               "GrBackendRenderTarget_newMock")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    const sk_i_size_t render_target_dimensions = GrBackendRenderTarget_dimensions(mock_render_target);
    auto *render_target_size = reinterpret_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(render_target_dimensions));
    if (!check(render_target_size != nullptr &&
               SkISize_width(render_target_size) == 16 &&
               SkISize_height(render_target_size) == 12,
               "GrBackendRenderTarget_dimensions")) {
        static_sk_i_size_delete(render_target_dimensions);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    static_sk_i_size_delete(render_target_dimensions);
    reskia_gr_backend_format_t *render_target_format = GrBackendRenderTarget_getBackendFormat(mock_render_target);
    if (!check(render_target_format != nullptr && GrBackendFormat_isValid(render_target_format), "GrBackendRenderTarget_getBackendFormat")) {
        GrBackendFormat_delete(render_target_format);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendFormat_delete(render_target_format);
    reskia_gr_mtl_texture_info_t mtl_render_target_info = {reinterpret_cast<void *>(0x1)};
    if (!check(!GrBackendRenderTarget_getMtlTextureInfo(mock_render_target, &mtl_render_target_info) &&
               mtl_render_target_info.texture == nullptr,
               "GrBackendRenderTarget_getMtlTextureInfo(mock)")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_gr_mock_render_target_info_t render_target_info = {};
    if (!check(GrBackendRenderTarget_getMockRenderTargetInfo(mock_render_target, &render_target_info) &&
               render_target_info.color_type == 4 &&
               render_target_info.id == 0 &&
               render_target_info.is_protected == 0,
               "GrBackendRenderTarget_getMockRenderTargetInfo")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *render_target_state = MutableTextureState_newVulkan(0, 0);
    if (!check(render_target_state != nullptr, "MutableTextureState_newVulkan")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *render_target_state_copy = MutableTextureState_newCopy(render_target_state);
    if (!check(render_target_state_copy != nullptr &&
               MutableTextureState_isValid(render_target_state_copy) == MutableTextureState_isValid(render_target_state),
               "MutableTextureState copy")) {
        MutableTextureState_delete(render_target_state_copy);
        MutableTextureState_delete(render_target_state);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendRenderTarget_setMutableState(mock_render_target, render_target_state_copy);
    MutableTextureState_delete(render_target_state_copy);
    MutableTextureState_delete(render_target_state);
    if (!check(GrBackendRenderTarget_asHandle(mock_render_target, &render_target_handle) &&
               render_target_handle.backend_render_target != nullptr,
               "GrBackendRenderTarget_asHandle")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendRenderTarget_delete(mock_render_target);

    reskia_gr_backend_semaphore_t *semaphore = GrBackendSemaphore_new();
    if (!check(semaphore != nullptr &&
               !GrBackendSemaphore_isInitialized(semaphore),
               "GrBackendSemaphore default")) {
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    GrBackendSemaphore_initMetal(semaphore, nullptr, 77);
    if (!check(GrBackendSemaphore_isInitialized(semaphore) &&
               GrBackendSemaphore_mtlSemaphore(semaphore) == nullptr &&
               GrBackendSemaphore_mtlValue(semaphore) == 77,
               "GrBackendSemaphore Metal init/query")) {
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    reskia_gr_backend_semaphore_t *semaphore_copy = GrBackendSemaphore_newCopy(semaphore);
    if (!check(semaphore_copy != nullptr &&
               GrBackendSemaphore_isInitialized(semaphore_copy) &&
               GrBackendSemaphore_mtlValue(semaphore_copy) == 77,
               "GrBackendSemaphore copy")) {
        GrBackendSemaphore_delete(semaphore_copy);
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    GrBackendSemaphore_delete(semaphore_copy);
    GrBackendSemaphore_delete(semaphore);
#endif

    int null_resource_count = 1;
    size_t null_resource_bytes = 1;
#if RESKIA_TEST_GPU_GANESH
    reskia_gr_surface_characterization_t *default_characterization = GrSurfaceCharacterization_new();
    if (!check(default_characterization != nullptr &&
               !GrSurfaceCharacterization_isValid(default_characterization) &&
               GrSurfaceCharacterization_width(default_characterization) == 0 &&
               GrSurfaceCharacterization_height(default_characterization) == 0 &&
               GrSurfaceCharacterization_newCopy(nullptr) == nullptr &&
               !GrSurfaceCharacterization_isCompatible(default_characterization, nullptr),
               "GrSurfaceCharacterization default/null helpers")) {
        GrSurfaceCharacterization_delete(default_characterization);
        return false;
    }
    reskia_gr_surface_characterization_t *default_characterization_copy =
            GrSurfaceCharacterization_newCopy(default_characterization);
    if (!check(default_characterization_copy != nullptr &&
               !GrSurfaceCharacterization_isValid(default_characterization_copy),
               "GrSurfaceCharacterization copy")) {
        GrSurfaceCharacterization_delete(default_characterization_copy);
        GrSurfaceCharacterization_delete(default_characterization);
        return false;
    }
    GrSurfaceCharacterization_delete(default_characterization_copy);
    GrSurfaceCharacterization_delete(default_characterization);
#endif
    GrDirectContext_resetContext(nullptr, 0);
    GrDirectContext_abandonContext(nullptr);
    GrDirectContext_releaseResourcesAndAbandonContext(nullptr);
    GrDirectContext_resetGLTextureBindings(nullptr);
    GrDirectContext_setResourceCacheLimits(nullptr, 0, 0);
    GrDirectContext_setResourceCacheLimit(nullptr, 0);
    GrDirectContext_freeGpuResources(nullptr);
    GrDirectContext_performDeferredCleanup(nullptr, 0, 0);
    GrDirectContext_purgeResourcesNotUsedInMs(nullptr, 0);
    GrDirectContext_purgeUnlockedResources(nullptr, 0);
    GrDirectContext_purgeUnlockedResourcesWithBytes(nullptr, 0, false);
    GrDirectContext_flushAndSubmit(nullptr, false);
    GrDirectContext_checkAsyncWorkCompletion(nullptr);
    GrDirectContext_dumpMemoryStatistics(nullptr, nullptr);
    GrDirectContext_storeVkPipelineCacheData(nullptr);
    if (GrDirectContext_MakeMetal(nullptr, nullptr) != nullptr ||
        GrDirectContext_MakeVulkan(nullptr) != nullptr) {
        return false;
    }
    GrDirectContext_deleteBackendTexture(nullptr, nullptr);
    if (!check(GrDirectContext_abandoned(nullptr), "GrDirectContext_abandoned(nullptr)")) {
        return false;
    }
    if (!check(!GrDirectContext_isDeviceLost(nullptr) &&
               !GrDirectContext_oomed(nullptr) &&
               !GrDirectContext_getResourceCacheLimits(nullptr, &null_resource_count, &null_resource_bytes) &&
               GrDirectContext_getResourceCacheLimit(nullptr) == 0 &&
               !GrDirectContext_getResourceCacheUsage(nullptr, &null_resource_count, &null_resource_bytes) &&
               GrDirectContext_getResourceCachePurgeableBytes(nullptr) == 0 &&
               GrDirectContext_flush(nullptr) == -1 &&
               !GrDirectContext_submit(nullptr, false) &&
               !GrDirectContext_wait(nullptr, 0, nullptr, false) &&
               GrDirectContext_dump(nullptr) == nullptr &&
               !GrDirectContext_supportsDistanceFieldText(nullptr) &&
               GrDirectContext_createBackendTexture(nullptr, 1, 1, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColorType(nullptr, 1, 1, 4, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColor(nullptr, 1, 1, nullptr, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColorTypeColor(nullptr, 1, 1, 4, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmaps(nullptr, nullptr, 1, 0, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmap(nullptr, nullptr, 0, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmapsTopLeft(nullptr, nullptr, 1, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmapTopLeft(nullptr, nullptr, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createCompressedBackendTexture(nullptr, 1, 1, nullptr, nullptr, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithCompressionType(nullptr, 1, 1, 0, nullptr, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithData(nullptr, 1, 1, nullptr, nullptr, 0, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithCompressionTypeData(nullptr, 1, 1, 0, nullptr, 0, false, false) == nullptr &&
               !GrDirectContext_updateBackendTexture(nullptr, nullptr, nullptr) &&
               !GrDirectContext_updateBackendTextureWithColorType(nullptr, nullptr, 0, nullptr) &&
               !GrDirectContext_updateBackendTextureFromPixmaps(nullptr, nullptr, nullptr, 0, 0) &&
               !GrDirectContext_updateBackendTextureFromPixmap(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_updateBackendTextureFromPixmapsTopLeft(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_updateCompressedBackendTexture(nullptr, nullptr, nullptr) &&
               !GrDirectContext_updateCompressedBackendTextureWithData(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_setBackendTextureState(nullptr, nullptr, nullptr, nullptr) &&
               !GrDirectContext_setBackendRenderTargetState(nullptr, nullptr, nullptr, nullptr) &&
               !GrDirectContext_precompileShader(nullptr, nullptr, nullptr) &&
               Graphite_Context_backend(nullptr) == 0 &&
               Graphite_Context_makeRecorder(nullptr) == nullptr &&
               !Graphite_Context_submit(nullptr, false) &&
               Graphite_Context_currentBudgetedBytes(nullptr) == 0 &&
               !Graphite_Context_supportsProtectedContent(nullptr) &&
               Graphite_Recorder_currentBudgetedBytes(nullptr) == 0 &&
               Graphite_Recorder_createBackendTexture(nullptr, 0, nullptr) == nullptr &&
               !Graphite_Recorder_updateBackendTexture(nullptr, nullptr, nullptr, 0) &&
               Graphite_TextureInfo_newCopy(nullptr) == nullptr &&
               !Graphite_TextureInfo_equals(nullptr, nullptr) &&
               !Graphite_TextureInfo_isValid(nullptr) &&
               Graphite_TextureInfo_backend(nullptr) == 0 &&
               Graphite_TextureInfo_numSamples(nullptr) == 0 &&
               !Graphite_TextureInfo_mipmapped(nullptr) &&
               !Graphite_TextureInfo_isProtected(nullptr) &&
               !Graphite_TextureInfo_getMtlTextureInfo(nullptr, nullptr) &&
               Graphite_TextureInfo_toString(nullptr) == nullptr &&
               Graphite_BackendTexture_newCopy(nullptr) == nullptr &&
               !Graphite_BackendTexture_equals(nullptr, nullptr) &&
               !Graphite_BackendTexture_isValid(nullptr) &&
               Graphite_BackendTexture_backend(nullptr) == 0 &&
               Graphite_BackendTexture_dimensions(nullptr) == 0 &&
               Graphite_BackendTexture_info(nullptr) == nullptr &&
               Graphite_BackendTexture_getMtlTexture(nullptr) == nullptr &&
               GrContextThreadSafeProxy_createCharacterization(nullptr, 0, nullptr, nullptr, 0, 0, nullptr, false, false, false, false, false, false) == nullptr,
               "GrDirectContext null input helpers")) {
        return false;
    }

#if RESKIA_TEST_GPU_GANESH
    reskia_direct_context_t *mock_context = GrDirectContext_MakeMock();
    if (mock_context != nullptr) {
        GrDirectContext_resetGLTextureBindings(mock_context);
        Reskia_DirectContext_Release(mock_context);
    }
#endif

    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if (device == nil) {
        std::fprintf(stdout, "[gpu-context-capi-smoke] SKIP: Metal device is unavailable in this environment\n");
        return true;
    }

    id<MTLCommandQueue> queue = [device newCommandQueue];
    if (queue == nil) {
        std::fprintf(stdout, "[gpu-context-capi-smoke] SKIP: Metal command queue could not be created\n");
        return true;
    }

    bool exercised = false;

#if RESKIA_TEST_GPU_GANESH
    {
        reskia_direct_context_t* direct_context =
                Reskia_GaneshContext_MakeMetal((void*)device, (void*)queue);
        if (!check(direct_context != nullptr, "Reskia_GaneshContext_MakeMetal")) {
            return false;
        }
        int max_resources = 0;
        size_t max_resource_bytes = 0;
        int resource_count = 0;
        size_t resource_bytes = 0;
        if (!check(!GrDirectContext_abandoned(direct_context), "GrDirectContext_abandoned(valid initial)") ||
            !check(!GrDirectContext_isDeviceLost(direct_context), "GrDirectContext_isDeviceLost(valid initial)") ||
            !check(GrDirectContext_getResourceCacheLimits(direct_context, &max_resources, &max_resource_bytes), "GrDirectContext_getResourceCacheLimits(valid)") ||
            !check(GrDirectContext_getResourceCacheUsage(direct_context, &resource_count, &resource_bytes), "GrDirectContext_getResourceCacheUsage(valid)")) {
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        reskia_gr_direct_context_id_t *context_id = GrDirectContext_directContextID(direct_context);
        if (!check(context_id != nullptr && GrDirectContextID_isValid(context_id), "GrDirectContext_directContextID(valid)")) {
            GrDirectContextID_delete(context_id);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        GrDirectContextID_delete(context_id);
        reskia_string_t *dump = GrDirectContext_dump(direct_context);
        if (dump != nullptr && !check(SkString_c_str(dump) != nullptr, "GrDirectContext_dump(valid)")) {
            SkString_delete(dump);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        SkString_delete(dump);
        if (!check(!GrRecordingContext_abandoned(direct_context) &&
                   GrRecordingContext_maxTextureSize(direct_context) > 0 &&
                   GrRecordingContext_maxRenderTargetSize(direct_context) > 0 &&
                   GrRecordingContext_maxSurfaceSampleCountForColorType(direct_context, 4) >= 0,
                   "GrRecordingContext query helpers")) {
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        reskia_gr_context_thread_safe_proxy_t *proxy = GrDirectContext_threadSafeProxy(direct_context);
        if (!check(proxy != nullptr && GrContextThreadSafeProxy_isValid(proxy), "GrDirectContext_threadSafeProxy(valid)")) {
            GrContextThreadSafeProxy_release(proxy);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        reskia_gr_backend_format_t *proxy_format = GrContextThreadSafeProxy_defaultBackendFormat(proxy, 4, true);
        if (!check(proxy_format != nullptr, "GrContextThreadSafeProxy_defaultBackendFormat(valid)")) {
            GrBackendFormat_delete(proxy_format);
            GrContextThreadSafeProxy_release(proxy);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        reskia_gr_backend_texture_t *backend_texture =
                GrDirectContext_createBackendTexture(direct_context, 4, 4, proxy_format, false, true, false, "reskia-smoke", 12);
        if (!check(backend_texture != nullptr, "GrDirectContext_createBackendTexture(valid)")) {
            GrBackendTexture_delete(backend_texture);
            GrBackendFormat_delete(proxy_format);
            GrContextThreadSafeProxy_release(proxy);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        GrDirectContext_deleteBackendTexture(direct_context, backend_texture);
        GrBackendTexture_delete(backend_texture);
        GrBackendFormat_delete(proxy_format);
        GrContextThreadSafeProxy_release(proxy);
        const size_t cache_limit = GrDirectContext_getResourceCacheLimit(direct_context);
        (void) GrDirectContext_getResourceCachePurgeableBytes(direct_context);
        GrDirectContext_setResourceCacheLimits(direct_context, max_resources, max_resource_bytes);
        GrDirectContext_setResourceCacheLimit(direct_context, cache_limit);
        GrDirectContext_resetContext(direct_context, 0);
        GrDirectContext_performDeferredCleanup(direct_context, 0, 0);
        GrDirectContext_purgeResourcesNotUsedInMs(direct_context, 0);
        GrDirectContext_purgeUnlockedResources(direct_context, 0);
        GrDirectContext_purgeUnlockedResourcesWithBytes(direct_context, 0, false);
        GrDirectContext_checkAsyncWorkCompletion(direct_context);
        (void) GrDirectContext_flush(direct_context);
        (void) GrDirectContext_submit(direct_context, false);
        Reskia_DirectContext_FlushAndSubmit(direct_context, true);
        GrDirectContext_freeGpuResources(direct_context);
        Reskia_DirectContext_Release(direct_context);
        exercised = true;
    }
#endif

#if RESKIA_TEST_GPU_GRAPHITE
    {
        reskia_graphite_context_t* graphite_context =
                Reskia_GraphiteContext_MakeMetal((void*)device, (void*)queue);
        if (!check(graphite_context != nullptr, "Reskia_GraphiteContext_MakeMetal")) {
            return false;
        }
        if (!check(Graphite_Context_backend(graphite_context) == RESKIA_GPU_BACKEND_API_METAL,
                   "Graphite_Context_backend")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_Context_checkAsyncWorkCompletion(graphite_context);
        Graphite_Context_performDeferredCleanup(graphite_context, 0);
        Graphite_Context_freeGpuResources(graphite_context);

        reskia_graphite_recorder_t* recorder =
                Graphite_Context_makeRecorder(graphite_context);
        if (!check(recorder != nullptr, "Graphite_Context_makeRecorder")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_Recorder_performDeferredCleanup(recorder, 0);
        Graphite_Recorder_freeGpuResources(recorder);

        reskia_graphite_texture_info_t* default_texture_info = Graphite_TextureInfo_new();
        reskia_string_t* texture_info_string = Graphite_TextureInfo_toString(default_texture_info);
        if (!check(default_texture_info != nullptr &&
                   !Graphite_TextureInfo_isValid(default_texture_info) &&
                   Graphite_TextureInfo_backend(default_texture_info) == 0 &&
                   Graphite_TextureInfo_numSamples(default_texture_info) == 0 &&
                   !Graphite_TextureInfo_mipmapped(default_texture_info) &&
                   !Graphite_TextureInfo_isProtected(default_texture_info) &&
                   texture_info_string != nullptr,
                   "Graphite_TextureInfo default")) {
            SkString_delete(texture_info_string);
            Graphite_TextureInfo_delete(default_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        SkString_delete(texture_info_string);

        reskia_graphite_texture_info_t* copied_texture_info =
                Graphite_TextureInfo_newCopy(default_texture_info);
        if (!check(copied_texture_info != nullptr &&
                   Graphite_TextureInfo_equals(default_texture_info, copied_texture_info) &&
                   !Graphite_TextureInfo_notEquals(default_texture_info, copied_texture_info),
                   "Graphite_TextureInfo copy")) {
            Graphite_TextureInfo_delete(copied_texture_info);
            Graphite_TextureInfo_delete(default_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_TextureInfo_delete(copied_texture_info);
        Graphite_TextureInfo_delete(default_texture_info);

        reskia_graphite_backend_texture_t* default_backend_texture = Graphite_BackendTexture_new();
        reskia_graphite_backend_texture_t* copied_backend_texture =
                Graphite_BackendTexture_newCopy(default_backend_texture);
        sk_i_size_t default_backend_dimensions =
                Graphite_BackendTexture_dimensions(default_backend_texture);
        reskia_graphite_texture_info_t* backend_texture_info =
                Graphite_BackendTexture_info(default_backend_texture);
        if (!check(default_backend_texture != nullptr &&
                   copied_backend_texture != nullptr &&
                   !Graphite_BackendTexture_isValid(default_backend_texture) &&
                   Graphite_BackendTexture_backend(default_backend_texture) == 0 &&
                   Graphite_BackendTexture_equals(default_backend_texture, copied_backend_texture) &&
                   !Graphite_BackendTexture_notEquals(default_backend_texture, copied_backend_texture) &&
                   default_backend_dimensions != 0 &&
                   backend_texture_info != nullptr,
                   "Graphite_BackendTexture default")) {
            Graphite_TextureInfo_delete(backend_texture_info);
            static_sk_i_size_delete(default_backend_dimensions);
            Graphite_BackendTexture_delete(copied_backend_texture);
            Graphite_BackendTexture_delete(default_backend_texture);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_TextureInfo_delete(backend_texture_info);
        static_sk_i_size_delete(default_backend_dimensions);
        Graphite_BackendTexture_delete(copied_backend_texture);
        Graphite_BackendTexture_delete(default_backend_texture);

        Reskia_GraphiteRecorder_Release(recorder);
        Reskia_GraphiteContext_Release(graphite_context);
        exercised = true;
    }
#endif

    return check(exercised, "no GPU context path exercised");
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_context_create_destroy()) {
        return 1;
    }

    std::fprintf(stdout, "[gpu-context-capi-smoke] PASS\n");
    return 0;
}
