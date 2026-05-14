//
// Created by dolphilia on 2026/02/17.
//

#include "sk_gpu_context.h"

#include "include/gpu/GrDirectContext.h"
#include "include/gpu/GrTypes.h"
#include "include/core/SkTextureCompressionType.h"

#include <chrono>

#if defined(SK_VULKAN)
#include "include/gpu/vk/GrVkBackendContext.h"
#endif

#if defined(SK_GRAPHITE)
#include "include/gpu/graphite/Context.h"
#include "include/gpu/graphite/GraphiteTypes.h"
#include "include/gpu/graphite/Recorder.h"
#include "include/gpu/graphite/Recording.h"
#endif

#if defined(SK_GRAPHITE) && defined(SK_VULKAN)
#include "include/gpu/graphite/vk/VulkanGraphiteUtils.h"
#include "include/gpu/vk/VulkanBackendContext.h"
#endif

#if defined(SK_GRAPHITE) && defined(SK_METAL) && defined(__APPLE__)
#include "include/gpu/graphite/mtl/MtlBackendContext.h"
#include "include/gpu/graphite/mtl/MtlGraphiteUtils.h"
#include "include/ports/SkCFObject.h"
#endif

#if defined(SK_GANESH)
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContextThreadSafeProxy.h"
#include "include/gpu/GrRecordingContext.h"
#include "include/gpu/GpuTypes.h"
#endif

namespace {

#if defined(SK_GANESH)
GrDirectContext *as_direct_context(reskia_direct_context_t *ctx) {
    return reinterpret_cast<GrDirectContext *>(ctx);
}

const GrDirectContext *as_direct_context(const reskia_direct_context_t *ctx) {
    return reinterpret_cast<const GrDirectContext *>(ctx);
}

GrRecordingContext *as_recording_context(reskia_direct_context_t *ctx) {
    return reinterpret_cast<GrRecordingContext *>(ctx);
}

GrContextThreadSafeProxy *as_thread_safe_proxy(reskia_gr_context_thread_safe_proxy_t *proxy) {
    return reinterpret_cast<GrContextThreadSafeProxy *>(proxy);
}

bool is_valid_purge_resource_options(reskia_gr_purge_resource_options_t options) {
    return options >= static_cast<reskia_gr_purge_resource_options_t>(GrPurgeResourceOptions::kAllResources) &&
           options <= static_cast<reskia_gr_purge_resource_options_t>(GrPurgeResourceOptions::kScratchResourcesOnly);
}

GrPurgeResourceOptions to_purge_resource_options(reskia_gr_purge_resource_options_t options) {
    return static_cast<GrPurgeResourceOptions>(options);
}

GrSyncCpu to_sync_cpu(bool sync_cpu) {
    return sync_cpu ? GrSyncCpu::kYes : GrSyncCpu::kNo;
}
#endif

}  // namespace

extern "C" {

reskia_direct_context_t *Reskia_GaneshContext_MakeMetal(void *device, void *queue) {
#if defined(SK_GANESH) && defined(SK_METAL)
    if (device == nullptr || queue == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_direct_context_t *>(GrDirectContext::MakeMetal(device, queue).release());
#else
    (void) device;
    (void) queue;
    return nullptr;
#endif
}

reskia_direct_context_t *Reskia_GaneshContext_MakeVulkan(const void *backend_context) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    if (backend_context == nullptr) {
        return nullptr;
    }

    auto *vk_backend_context = reinterpret_cast<const GrVkBackendContext *>(backend_context);
    return reinterpret_cast<reskia_direct_context_t *>(GrDirectContext::MakeVulkan(*vk_backend_context).release());
#else
    (void) backend_context;
    return nullptr;
#endif
}

void Reskia_DirectContext_FlushAndSubmit(reskia_direct_context_t *ctx, bool sync_cpu) {
#if defined(SK_GANESH)
    GrDirectContext_flushAndSubmit(ctx, sync_cpu);
#else
    (void) ctx;
    (void) sync_cpu;
#endif
}

void Reskia_DirectContext_Abandon(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    GrDirectContext_abandonContext(ctx);
#else
    (void) ctx;
#endif
}

void Reskia_DirectContext_Release(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    reinterpret_cast<GrDirectContext *>(ctx)->unref();
#else
    (void) ctx;
#endif
}

void GrDirectContext_resetContext(reskia_direct_context_t *ctx, uint32_t state) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->resetContext(state);
#else
    (void) ctx;
    (void) state;
#endif
}

void GrDirectContext_abandonContext(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->abandonContext();
#else
    (void) ctx;
#endif
}

bool GrDirectContext_abandoned(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx == nullptr || as_direct_context(ctx)->abandoned();
#else
    (void) ctx;
    return true;
#endif
}

bool GrDirectContext_isDeviceLost(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->isDeviceLost();
#else
    (void) ctx;
    return false;
#endif
}

bool GrDirectContext_oomed(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->oomed();
#else
    (void) ctx;
    return false;
#endif
}

void GrDirectContext_releaseResourcesAndAbandonContext(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->releaseResourcesAndAbandonContext();
#else
    (void) ctx;
#endif
}

bool GrDirectContext_getResourceCacheLimits(reskia_direct_context_t *ctx, int *maxResources, size_t *maxResourceBytes) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return false;
    }
    as_direct_context(ctx)->getResourceCacheLimits(maxResources, maxResourceBytes);
    return true;
#else
    (void) ctx;
    (void) maxResources;
    (void) maxResourceBytes;
    return false;
#endif
}

size_t GrDirectContext_getResourceCacheLimit(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? as_direct_context(ctx)->getResourceCacheLimit() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

bool GrDirectContext_getResourceCacheUsage(reskia_direct_context_t *ctx, int *resourceCount, size_t *resourceBytes) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return false;
    }
    as_direct_context(ctx)->getResourceCacheUsage(resourceCount, resourceBytes);
    return true;
#else
    (void) ctx;
    (void) resourceCount;
    (void) resourceBytes;
    return false;
#endif
}

size_t GrDirectContext_getResourceCachePurgeableBytes(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? as_direct_context(ctx)->getResourceCachePurgeableBytes() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

void GrDirectContext_setResourceCacheLimits(reskia_direct_context_t *ctx, int maxResources, size_t maxResourceBytes) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->setResourceCacheLimits(maxResources, maxResourceBytes);
#else
    (void) ctx;
    (void) maxResources;
    (void) maxResourceBytes;
#endif
}

void GrDirectContext_setResourceCacheLimit(reskia_direct_context_t *ctx, size_t maxResourceBytes) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->setResourceCacheLimit(maxResourceBytes);
#else
    (void) ctx;
    (void) maxResourceBytes;
#endif
}

void GrDirectContext_freeGpuResources(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->freeGpuResources();
#else
    (void) ctx;
#endif
}

void GrDirectContext_performDeferredCleanup(reskia_direct_context_t *ctx, int64_t msNotUsed, reskia_gr_purge_resource_options_t options) {
#if defined(SK_GANESH)
    if (ctx == nullptr || msNotUsed < 0 || !is_valid_purge_resource_options(options)) {
        return;
    }
    as_direct_context(ctx)->performDeferredCleanup(std::chrono::milliseconds(msNotUsed), to_purge_resource_options(options));
#else
    (void) ctx;
    (void) msNotUsed;
    (void) options;
#endif
}

void GrDirectContext_purgeResourcesNotUsedInMs(reskia_direct_context_t *ctx, int64_t msNotUsed) {
#if defined(SK_GANESH)
    if (ctx == nullptr || msNotUsed < 0) {
        return;
    }
    as_direct_context(ctx)->purgeResourcesNotUsedInMs(std::chrono::milliseconds(msNotUsed));
#else
    (void) ctx;
    (void) msNotUsed;
#endif
}

void GrDirectContext_purgeUnlockedResources(reskia_direct_context_t *ctx, reskia_gr_purge_resource_options_t options) {
#if defined(SK_GANESH)
    if (ctx == nullptr || !is_valid_purge_resource_options(options)) {
        return;
    }
    as_direct_context(ctx)->purgeUnlockedResources(to_purge_resource_options(options));
#else
    (void) ctx;
    (void) options;
#endif
}

void GrDirectContext_purgeUnlockedResourcesWithBytes(reskia_direct_context_t *ctx, size_t bytesToPurge, bool preferScratchResources) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->purgeUnlockedResources(bytesToPurge, preferScratchResources);
#else
    (void) ctx;
    (void) bytesToPurge;
    (void) preferScratchResources;
#endif
}

void GrDirectContext_flushAndSubmit(reskia_direct_context_t *ctx, bool sync_cpu) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->flushAndSubmit(to_sync_cpu(sync_cpu));
#else
    (void) ctx;
    (void) sync_cpu;
#endif
}

reskia_gr_semaphores_submitted_t GrDirectContext_flush(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return -1;
    }
    return static_cast<reskia_gr_semaphores_submitted_t>(as_direct_context(ctx)->flush(GrFlushInfo()));
#else
    (void) ctx;
    return -1;
#endif
}

bool GrDirectContext_submit(reskia_direct_context_t *ctx, bool sync_cpu) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->submit(to_sync_cpu(sync_cpu));
#else
    (void) ctx;
    (void) sync_cpu;
    return false;
#endif
}

void GrDirectContext_checkAsyncWorkCompletion(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->checkAsyncWorkCompletion();
#else
    (void) ctx;
#endif
}

void GrDirectContext_dumpMemoryStatistics(reskia_direct_context_t *ctx, reskia_trace_memory_dump_t *traceMemoryDump) {
#if defined(SK_GANESH)
    if (ctx == nullptr || traceMemoryDump == nullptr) {
        return;
    }
    as_direct_context(ctx)->dumpMemoryStatistics(reinterpret_cast<SkTraceMemoryDump *>(traceMemoryDump));
#else
    (void) ctx;
    (void) traceMemoryDump;
#endif
}

bool GrDirectContext_supportsDistanceFieldText(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->supportsDistanceFieldText();
#else
    (void) ctx;
    return false;
#endif
}

void GrDirectContext_storeVkPipelineCacheData(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->storeVkPipelineCacheData();
#else
    (void) ctx;
#endif
}

reskia_gr_direct_context_id_t *GrDirectContext_directContextID(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? reinterpret_cast<reskia_gr_direct_context_id_t *>(new GrDirectContext::DirectContextID(as_direct_context(ctx)->directContextID())) : nullptr;
#else
    (void) ctx;
    return nullptr;
#endif
}

void GrDirectContextID_delete(reskia_gr_direct_context_id_t *context_id) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrDirectContext::DirectContextID *>(context_id);
#else
    (void) context_id;
#endif
}

bool GrDirectContextID_isValid(reskia_gr_direct_context_id_t *context_id) {
#if defined(SK_GANESH)
    return context_id != nullptr && reinterpret_cast<GrDirectContext::DirectContextID *>(context_id)->isValid();
#else
    (void) context_id;
    return false;
#endif
}

bool GrDirectContextID_equals(reskia_gr_direct_context_id_t *context_id, reskia_gr_direct_context_id_t *other) {
#if defined(SK_GANESH)
    return context_id != nullptr && other != nullptr &&
           *reinterpret_cast<GrDirectContext::DirectContextID *>(context_id) == *reinterpret_cast<GrDirectContext::DirectContextID *>(other);
#else
    (void) context_id;
    (void) other;
    return false;
#endif
}

reskia_gr_context_thread_safe_proxy_t *GrDirectContext_threadSafeProxy(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return nullptr;
    }
    auto proxy = as_direct_context(ctx)->threadSafeProxy();
    return reinterpret_cast<reskia_gr_context_thread_safe_proxy_t *>(proxy.release());
#else
    (void) ctx;
    return nullptr;
#endif
}

bool GrRecordingContext_abandoned(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx == nullptr || as_recording_context(ctx)->abandoned();
#else
    (void) ctx;
    return true;
#endif
}

bool GrRecordingContext_colorTypeSupportedAsSurface(reskia_direct_context_t *ctx, int color_type) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_recording_context(ctx)->colorTypeSupportedAsSurface(static_cast<SkColorType>(color_type));
#else
    (void) ctx;
    (void) color_type;
    return false;
#endif
}

int GrRecordingContext_maxTextureSize(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? as_recording_context(ctx)->maxTextureSize() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

int GrRecordingContext_maxRenderTargetSize(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? as_recording_context(ctx)->maxRenderTargetSize() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

bool GrRecordingContext_colorTypeSupportedAsImage(reskia_direct_context_t *ctx, int color_type) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_recording_context(ctx)->colorTypeSupportedAsImage(static_cast<SkColorType>(color_type));
#else
    (void) ctx;
    (void) color_type;
    return false;
#endif
}

bool GrRecordingContext_supportsProtectedContent(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_recording_context(ctx)->supportsProtectedContent();
#else
    (void) ctx;
    return false;
#endif
}

int GrRecordingContext_maxSurfaceSampleCountForColorType(reskia_direct_context_t *ctx, int color_type) {
#if defined(SK_GANESH)
    return ctx != nullptr ? as_recording_context(ctx)->maxSurfaceSampleCountForColorType(static_cast<SkColorType>(color_type)) : 0;
#else
    (void) ctx;
    (void) color_type;
    return 0;
#endif
}

void GrContextThreadSafeProxy_release(reskia_gr_context_thread_safe_proxy_t *proxy) {
#if defined(SK_GANESH)
    if (proxy == nullptr) {
        return;
    }
    as_thread_safe_proxy(proxy)->unref();
#else
    (void) proxy;
#endif
}

reskia_gr_backend_format_t *GrContextThreadSafeProxy_defaultBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type, bool renderable) {
#if defined(SK_GANESH)
    if (proxy == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_thread_safe_proxy(proxy)->defaultBackendFormat(static_cast<SkColorType>(color_type), renderable ? GrRenderable::kYes : GrRenderable::kNo)));
#else
    (void) proxy;
    (void) color_type;
    (void) renderable;
    return nullptr;
#endif
}

reskia_gr_backend_format_t *GrContextThreadSafeProxy_compressedBackendFormat(reskia_gr_context_thread_safe_proxy_t *proxy, int compression_type) {
#if defined(SK_GANESH)
    if (proxy == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_thread_safe_proxy(proxy)->compressedBackendFormat(static_cast<SkTextureCompressionType>(compression_type))));
#else
    (void) proxy;
    (void) compression_type;
    return nullptr;
#endif
}

int GrContextThreadSafeProxy_maxSurfaceSampleCountForColorType(reskia_gr_context_thread_safe_proxy_t *proxy, int color_type) {
#if defined(SK_GANESH)
    return proxy != nullptr ? as_thread_safe_proxy(proxy)->maxSurfaceSampleCountForColorType(static_cast<SkColorType>(color_type)) : 0;
#else
    (void) proxy;
    (void) color_type;
    return 0;
#endif
}

bool GrContextThreadSafeProxy_isValid(reskia_gr_context_thread_safe_proxy_t *proxy) {
#if defined(SK_GANESH)
    return proxy != nullptr && as_thread_safe_proxy(proxy)->isValid();
#else
    (void) proxy;
    return false;
#endif
}

bool GrContextThreadSafeProxy_equals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other) {
#if defined(SK_GANESH)
    return proxy != nullptr && other != nullptr && *as_thread_safe_proxy(proxy) == *as_thread_safe_proxy(other);
#else
    (void) proxy;
    (void) other;
    return false;
#endif
}

bool GrContextThreadSafeProxy_notEquals(reskia_gr_context_thread_safe_proxy_t *proxy, reskia_gr_context_thread_safe_proxy_t *other) {
#if defined(SK_GANESH)
    return proxy != nullptr && other != nullptr && *as_thread_safe_proxy(proxy) != *as_thread_safe_proxy(other);
#else
    (void) proxy;
    (void) other;
    return false;
#endif
}

reskia_graphite_context_t *Reskia_GraphiteContext_MakeMetal(void *device, void *queue) {
#if defined(SK_GRAPHITE) && defined(SK_METAL) && defined(__APPLE__)
    if (device == nullptr || queue == nullptr) {
        return nullptr;
    }

    skgpu::graphite::MtlBackendContext backend_context;
    backend_context.fDevice = sk_ret_cfp(reinterpret_cast<CFTypeRef>(device));
    backend_context.fQueue = sk_ret_cfp(reinterpret_cast<CFTypeRef>(queue));

    auto context = skgpu::graphite::ContextFactory::MakeMetal(backend_context, skgpu::graphite::ContextOptions{});
    return reinterpret_cast<reskia_graphite_context_t *>(context.release());
#else
    (void) device;
    (void) queue;
    return nullptr;
#endif
}

reskia_graphite_context_t *Reskia_GraphiteContext_MakeVulkan(const void *backend_context) {
#if defined(SK_GRAPHITE) && defined(SK_VULKAN)
    if (backend_context == nullptr) {
        return nullptr;
    }

    auto *vk_backend_context = reinterpret_cast<const skgpu::VulkanBackendContext *>(backend_context);
    auto context = skgpu::graphite::ContextFactory::MakeVulkan(*vk_backend_context, skgpu::graphite::ContextOptions{});
    return reinterpret_cast<reskia_graphite_context_t *>(context.release());
#else
    (void) backend_context;
    return nullptr;
#endif
}

reskia_graphite_recorder_t *Reskia_GraphiteContext_MakeRecorder(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr) {
        return nullptr;
    }

    auto recorder = reinterpret_cast<skgpu::graphite::Context *>(ctx)->makeRecorder();
    return reinterpret_cast<reskia_graphite_recorder_t *>(recorder.release());
#else
    (void) ctx;
    return nullptr;
#endif
}

bool Reskia_GraphiteContext_InsertRecordingAndSubmit(reskia_graphite_context_t *ctx, reskia_graphite_recorder_t *recorder, bool sync_cpu) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || recorder == nullptr) {
        return false;
    }

    auto *graphite_context = reinterpret_cast<skgpu::graphite::Context *>(ctx);
    auto *graphite_recorder = reinterpret_cast<skgpu::graphite::Recorder *>(recorder);

    std::unique_ptr<skgpu::graphite::Recording> recording = graphite_recorder->snap();
    if (!recording) {
        return false;
    }

    skgpu::graphite::InsertRecordingInfo info;
    info.fRecording = recording.get();

    if (!graphite_context->insertRecording(info)) {
        return false;
    }

    return graphite_context->submit(sync_cpu ? skgpu::graphite::SyncToCpu::kYes
                                             : skgpu::graphite::SyncToCpu::kNo);
#else
    (void) ctx;
    (void) recorder;
    (void) sync_cpu;
    return false;
#endif
}

void Reskia_GraphiteRecorder_Release(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    delete reinterpret_cast<skgpu::graphite::Recorder *>(recorder);
#else
    (void) recorder;
#endif
}

void Reskia_GraphiteContext_Release(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    delete reinterpret_cast<skgpu::graphite::Context *>(ctx);
#else
    (void) ctx;
#endif
}

}
