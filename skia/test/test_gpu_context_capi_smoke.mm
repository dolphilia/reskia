#include <cstdio>

#import <Metal/Metal.h>

#include "capi/sk_gpu_backend_surface.h"
#include "capi/sk_gpu_context.h"
#include "capi/sk_graphics.h"
#include "capi/sk_string.h"

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
    reskia_gr_backend_format_t *texture_format = GrBackendTexture_getBackendFormat(mock_texture);
    if (!check(texture_format != nullptr && GrBackendFormat_isValid(texture_format), "GrBackendTexture_getBackendFormat")) {
        GrBackendFormat_delete(texture_format);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    GrBackendFormat_delete(texture_format);
    if (!check(GrBackendTexture_asHandle(mock_texture, &texture_handle) &&
               texture_handle.backend_texture != nullptr,
               "GrBackendTexture_asHandle")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
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
    reskia_gr_backend_format_t *render_target_format = GrBackendRenderTarget_getBackendFormat(mock_render_target);
    if (!check(render_target_format != nullptr && GrBackendFormat_isValid(render_target_format), "GrBackendRenderTarget_getBackendFormat")) {
        GrBackendFormat_delete(render_target_format);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendFormat_delete(render_target_format);
    if (!check(GrBackendRenderTarget_asHandle(mock_render_target, &render_target_handle) &&
               render_target_handle.backend_render_target != nullptr,
               "GrBackendRenderTarget_asHandle")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendRenderTarget_delete(mock_render_target);
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
               GrContextThreadSafeProxy_createCharacterization(nullptr, 0, nullptr, nullptr, 0, 0, nullptr, false, false, false, false, false, false) == nullptr,
               "GrDirectContext null input helpers")) {
        return false;
    }

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

        reskia_graphite_recorder_t* recorder =
                Reskia_GraphiteContext_MakeRecorder(graphite_context);
        if (!check(recorder != nullptr, "Reskia_GraphiteContext_MakeRecorder")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

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
