//
// Created by dolphilia on 2026/02/17.
//

#include "sk_gpu_context.h"

#include "sk_surface_gpu.h"

#include "include/core/SkColor.h"
#include "include/core/SkData.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkString.h"
#include "include/core/SkSurfaceProps.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/GrTypes.h"
#include "include/core/SkTextureCompressionType.h"

#include <chrono>
#include <string_view>
#include <vector>

#if defined(SK_VULKAN)
#include "include/gpu/vk/GrVkBackendContext.h"
#endif

#if defined(SK_GRAPHITE)
#include "include/gpu/graphite/Context.h"
#include "include/gpu/graphite/BackendTexture.h"
#include "include/gpu/graphite/GraphiteTypes.h"
#include "include/gpu/graphite/Recorder.h"
#include "include/gpu/graphite/Recording.h"
#include "include/gpu/graphite/TextureInfo.h"
#endif

#if defined(SK_GRAPHITE) && defined(SK_VULKAN)
#include "include/gpu/graphite/vk/VulkanGraphiteUtils.h"
#include "include/gpu/vk/VulkanBackendContext.h"
#endif

#if defined(SK_GRAPHITE) && defined(SK_METAL) && defined(__APPLE__)
#include "include/gpu/graphite/mtl/MtlBackendContext.h"
#include "include/gpu/graphite/mtl/MtlGraphiteUtils.h"
#include "include/gpu/graphite/mtl/MtlGraphiteTypes.h"
#include "include/ports/SkCFObject.h"
#endif

#if defined(SK_GANESH)
#include "include/gpu/GrBackendSemaphore.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContextThreadSafeProxy.h"
#include "include/gpu/GrRecordingContext.h"
#include "include/gpu/GpuTypes.h"
#include "include/gpu/MutableTextureState.h"
#include "include/gpu/mock/GrMockTypes.h"
#include "include/private/chromium/GrSurfaceCharacterization.h"
#endif

#include "../handles/static_sk_i_size-internal.h"

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

const GrBackendFormat *as_backend_format(const reskia_gr_backend_format_t *format) {
    return reinterpret_cast<const GrBackendFormat *>(format);
}

const GrBackendTexture *as_backend_texture(const reskia_gr_backend_texture_t *texture) {
    return reinterpret_cast<const GrBackendTexture *>(texture);
}

const GrBackendRenderTarget *as_backend_render_target(const reskia_gr_backend_render_target_t *render_target) {
    return reinterpret_cast<const GrBackendRenderTarget *>(render_target);
}

const GrBackendSemaphore *as_backend_semaphore(const reskia_gr_backend_semaphore_t *semaphore) {
    return reinterpret_cast<const GrBackendSemaphore *>(semaphore);
}

const skgpu::MutableTextureState *as_mutable_texture_state(const reskia_skgpu_mutable_texture_state_t *state) {
    return reinterpret_cast<const skgpu::MutableTextureState *>(state);
}

skgpu::MutableTextureState *as_mutable_texture_state(reskia_skgpu_mutable_texture_state_t *state) {
    return reinterpret_cast<skgpu::MutableTextureState *>(state);
}

const SkPixmap *as_pixmap(const reskia_pixmap_t *pixmap) {
    return reinterpret_cast<const SkPixmap *>(pixmap);
}

const SkData *as_data(const reskia_data_t *data) {
    return reinterpret_cast<const SkData *>(data);
}

const SkImageInfo *as_image_info(const reskia_image_info_t *image_info) {
    return reinterpret_cast<const SkImageInfo *>(image_info);
}

const SkSurfaceProps *as_surface_props(const reskia_surface_props_t *surface_props) {
    return reinterpret_cast<const SkSurfaceProps *>(surface_props);
}

GrSurfaceCharacterization *as_surface_characterization(reskia_gr_surface_characterization_t *characterization) {
    return reinterpret_cast<GrSurfaceCharacterization *>(characterization);
}

const GrSurfaceCharacterization *as_surface_characterization(const reskia_gr_surface_characterization_t *characterization) {
    return reinterpret_cast<const GrSurfaceCharacterization *>(characterization);
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

skgpu::Mipmapped to_mipmapped(bool mipmapped) {
    return mipmapped ? skgpu::Mipmapped::kYes : skgpu::Mipmapped::kNo;
}

GrRenderable to_renderable(bool renderable) {
    return renderable ? GrRenderable::kYes : GrRenderable::kNo;
}

GrProtected to_protected(bool is_protected) {
    return is_protected ? GrProtected::kYes : GrProtected::kNo;
}

bool is_valid_surface_origin(int surface_origin) {
    return surface_origin == static_cast<int>(kTopLeft_GrSurfaceOrigin) ||
           surface_origin == static_cast<int>(kBottomLeft_GrSurfaceOrigin);
}

GrSurfaceOrigin to_surface_origin(int surface_origin) {
    return static_cast<GrSurfaceOrigin>(surface_origin);
}

SkColor4f to_color4f(const float color[4]) {
    if (color == nullptr) {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }
    return {color[0], color[1], color[2], color[3]};
}

std::string_view to_label(const char *label, size_t label_len) {
    return label != nullptr ? std::string_view(label, label_len) : std::string_view();
}
#endif

#if defined(SK_GRAPHITE)
skgpu::graphite::Context *as_graphite_context(reskia_graphite_context_t *ctx) {
    return reinterpret_cast<skgpu::graphite::Context *>(ctx);
}

const skgpu::graphite::Context *as_graphite_context(const reskia_graphite_context_t *ctx) {
    return reinterpret_cast<const skgpu::graphite::Context *>(ctx);
}

skgpu::graphite::Recorder *as_graphite_recorder(reskia_graphite_recorder_t *recorder) {
    return reinterpret_cast<skgpu::graphite::Recorder *>(recorder);
}

const skgpu::graphite::BackendTexture *as_graphite_backend_texture(const reskia_graphite_backend_texture_t *texture) {
    return reinterpret_cast<const skgpu::graphite::BackendTexture *>(texture);
}

skgpu::graphite::BackendTexture *as_graphite_backend_texture(reskia_graphite_backend_texture_t *texture) {
    return reinterpret_cast<skgpu::graphite::BackendTexture *>(texture);
}

const skgpu::graphite::TextureInfo *as_graphite_texture_info(const reskia_graphite_texture_info_t *info) {
    return reinterpret_cast<const skgpu::graphite::TextureInfo *>(info);
}

skgpu::graphite::TextureInfo *as_graphite_texture_info(reskia_graphite_texture_info_t *info) {
    return reinterpret_cast<skgpu::graphite::TextureInfo *>(info);
}

int to_reskia_graphite_backend_api(skgpu::BackendApi backend) {
    switch (backend) {
        case skgpu::BackendApi::kMetal:
            return RESKIA_GPU_BACKEND_API_METAL;
        case skgpu::BackendApi::kVulkan:
            return RESKIA_GPU_BACKEND_API_VULKAN;
        default:
            return RESKIA_GPU_BACKEND_API_UNKNOWN;
    }
}

skgpu::Mipmapped to_graphite_mipmapped(bool mipmapped) {
    return mipmapped ? skgpu::Mipmapped::kYes : skgpu::Mipmapped::kNo;
}

bool from_graphite_mipmapped(skgpu::Mipmapped mipmapped) {
    return mipmapped == skgpu::Mipmapped::kYes;
}

bool from_graphite_protected(skgpu::Protected is_protected) {
    return is_protected == skgpu::Protected::kYes;
}

skgpu::graphite::SyncToCpu to_graphite_sync_cpu(bool sync_cpu) {
    return sync_cpu ? skgpu::graphite::SyncToCpu::kYes : skgpu::graphite::SyncToCpu::kNo;
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

reskia_direct_context_t *GrDirectContext_MakeMetal(void *device, void *queue) {
    return Reskia_GaneshContext_MakeMetal(device, queue);
}

reskia_direct_context_t *GrDirectContext_MakeVulkan(const void *backend_context) {
    return Reskia_GaneshContext_MakeVulkan(backend_context);
}

reskia_direct_context_t *GrDirectContext_MakeMock() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_direct_context_t *>(GrDirectContext::MakeMock(nullptr).release());
#else
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

reskia_string_t *GrDirectContext_dump(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH) && defined(SK_ENABLE_DUMP_GPU)
    if (ctx == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_direct_context(ctx)->dump()));
#else
    (void) ctx;
    return nullptr;
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

void GrDirectContext_resetGLTextureBindings(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->resetGLTextureBindings();
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

reskia_gr_backend_texture_t *GrDirectContext_createBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || format == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(width, height, *as_backend_format(format), to_mipmapped(mipmapped), to_renderable(renderable), to_protected(is_protected), to_label(label, label_len))));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) format;
    (void) mipmapped;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorType(reskia_direct_context_t *ctx, int width, int height, int color_type, bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(width, height, static_cast<SkColorType>(color_type), to_mipmapped(mipmapped), to_renderable(renderable), to_protected(is_protected), to_label(label, label_len))));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) color_type;
    (void) mipmapped;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColor(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || format == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(width, height, *as_backend_format(format), to_color4f(color), to_mipmapped(mipmapped), to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) format;
    (void) color;
    (void) mipmapped;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureWithColorTypeColor(reskia_direct_context_t *ctx, int width, int height, int color_type, const float color[4], bool mipmapped, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(width, height, static_cast<SkColorType>(color_type), to_color4f(color), to_mipmapped(mipmapped), to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) color_type;
    (void) color;
    (void) mipmapped;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmaps(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int num_levels, int surface_origin, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || src_data == nullptr || num_levels <= 0 || !is_valid_surface_origin(surface_origin)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(as_pixmap(src_data), num_levels, to_surface_origin(surface_origin), to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) src_data;
    (void) num_levels;
    (void) surface_origin;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmap(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int surface_origin, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || src_data == nullptr || !is_valid_surface_origin(surface_origin)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(*as_pixmap(src_data), to_surface_origin(surface_origin), to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) src_data;
    (void) surface_origin;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmapsTopLeft(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, int num_levels, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || src_data == nullptr || num_levels <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(as_pixmap(src_data), num_levels, to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) src_data;
    (void) num_levels;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createBackendTextureFromPixmapTopLeft(reskia_direct_context_t *ctx, const reskia_pixmap_t *src_data, bool renderable, bool is_protected, const char *label, size_t label_len) {
#if defined(SK_GANESH)
    if (ctx == nullptr || src_data == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createBackendTexture(*as_pixmap(src_data), to_renderable(renderable), to_protected(is_protected), nullptr, nullptr, to_label(label, label_len))));
#else
    (void) ctx;
    (void) src_data;
    (void) renderable;
    (void) is_protected;
    (void) label;
    (void) label_len;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTexture(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const float color[4], bool mipmapped, bool is_protected) {
#if defined(SK_GANESH)
    if (ctx == nullptr || format == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createCompressedBackendTexture(width, height, *as_backend_format(format), to_color4f(color), to_mipmapped(mipmapped), to_protected(is_protected), nullptr, nullptr)));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) format;
    (void) color;
    (void) mipmapped;
    (void) is_protected;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithCompressionType(reskia_direct_context_t *ctx, int width, int height, int compression_type, const float color[4], bool mipmapped, bool is_protected) {
#if defined(SK_GANESH)
    if (ctx == nullptr || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createCompressedBackendTexture(width, height, static_cast<SkTextureCompressionType>(compression_type), to_color4f(color), to_mipmapped(mipmapped), to_protected(is_protected), nullptr, nullptr)));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) compression_type;
    (void) color;
    (void) mipmapped;
    (void) is_protected;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithData(reskia_direct_context_t *ctx, int width, int height, const reskia_gr_backend_format_t *format, const void *data, size_t data_size, bool mipmapped, bool is_protected) {
#if defined(SK_GANESH)
    if (ctx == nullptr || format == nullptr || data == nullptr || data_size == 0 || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createCompressedBackendTexture(width, height, *as_backend_format(format), data, data_size, to_mipmapped(mipmapped), to_protected(is_protected), nullptr, nullptr)));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) format;
    (void) data;
    (void) data_size;
    (void) mipmapped;
    (void) is_protected;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrDirectContext_createCompressedBackendTextureWithCompressionTypeData(reskia_direct_context_t *ctx, int width, int height, int compression_type, const void *data, size_t data_size, bool mipmapped, bool is_protected) {
#if defined(SK_GANESH)
    if (ctx == nullptr || data == nullptr || data_size == 0 || width <= 0 || height <= 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_direct_context(ctx)->createCompressedBackendTexture(width, height, static_cast<SkTextureCompressionType>(compression_type), data, data_size, to_mipmapped(mipmapped), to_protected(is_protected), nullptr, nullptr)));
#else
    (void) ctx;
    (void) width;
    (void) height;
    (void) compression_type;
    (void) data;
    (void) data_size;
    (void) mipmapped;
    (void) is_protected;
    return nullptr;
#endif
}

bool GrDirectContext_wait(reskia_direct_context_t *ctx, int num_semaphores, const reskia_gr_backend_semaphore_t * const *wait_semaphores, bool delete_semaphores_after_wait) {
#if defined(SK_GANESH)
    if (ctx == nullptr || num_semaphores < 0 || (num_semaphores > 0 && wait_semaphores == nullptr)) {
        return false;
    }
    std::vector<GrBackendSemaphore> semaphores;
    semaphores.reserve(static_cast<size_t>(num_semaphores));
    for (int i = 0; i < num_semaphores; ++i) {
        if (wait_semaphores[i] == nullptr) {
            return false;
        }
        semaphores.push_back(*as_backend_semaphore(wait_semaphores[i]));
    }
    return as_direct_context(ctx)->wait(num_semaphores, semaphores.data(), delete_semaphores_after_wait);
#else
    (void) ctx;
    (void) num_semaphores;
    (void) wait_semaphores;
    (void) delete_semaphores_after_wait;
    return false;
#endif
}

bool GrDirectContext_updateBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const float color[4]) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && color != nullptr &&
           as_direct_context(ctx)->updateBackendTexture(*as_backend_texture(texture), to_color4f(color), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) color;
    return false;
#endif
}

bool GrDirectContext_updateBackendTextureWithColorType(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, int color_type, const float color[4]) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && color != nullptr &&
           as_direct_context(ctx)->updateBackendTexture(*as_backend_texture(texture), static_cast<SkColorType>(color_type), to_color4f(color), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) color_type;
    (void) color;
    return false;
#endif
}

bool GrDirectContext_updateBackendTextureFromPixmaps(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels, int surface_origin) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && src_data != nullptr && num_levels > 0 && is_valid_surface_origin(surface_origin) &&
           as_direct_context(ctx)->updateBackendTexture(*as_backend_texture(texture), as_pixmap(src_data), num_levels, to_surface_origin(surface_origin), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) src_data;
    (void) num_levels;
    (void) surface_origin;
    return false;
#endif
}

bool GrDirectContext_updateBackendTextureFromPixmap(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int surface_origin) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && src_data != nullptr && is_valid_surface_origin(surface_origin) &&
           as_direct_context(ctx)->updateBackendTexture(*as_backend_texture(texture), *as_pixmap(src_data), to_surface_origin(surface_origin), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) src_data;
    (void) surface_origin;
    return false;
#endif
}

bool GrDirectContext_updateBackendTextureFromPixmapsTopLeft(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && src_data != nullptr && num_levels > 0 &&
           as_direct_context(ctx)->updateBackendTexture(*as_backend_texture(texture), as_pixmap(src_data), num_levels, nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) src_data;
    (void) num_levels;
    return false;
#endif
}

bool GrDirectContext_updateCompressedBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const float color[4]) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && color != nullptr &&
           as_direct_context(ctx)->updateCompressedBackendTexture(*as_backend_texture(texture), to_color4f(color), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) color;
    return false;
#endif
}

bool GrDirectContext_updateCompressedBackendTextureWithData(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const void *data, size_t data_size) {
#if defined(SK_GANESH)
    return ctx != nullptr && texture != nullptr && data != nullptr && data_size > 0 &&
           as_direct_context(ctx)->updateCompressedBackendTexture(*as_backend_texture(texture), data, data_size, nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) data;
    (void) data_size;
    return false;
#endif
}

bool GrDirectContext_setBackendTextureState(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture, const reskia_skgpu_mutable_texture_state_t *state, reskia_skgpu_mutable_texture_state_t *previous_state) {
#if defined(SK_GANESH)
    if (ctx == nullptr || texture == nullptr || state == nullptr || !as_mutable_texture_state(state)->isValid()) {
        return false;
    }
    return as_direct_context(ctx)->setBackendTextureState(*as_backend_texture(texture), *as_mutable_texture_state(state), as_mutable_texture_state(previous_state), nullptr, nullptr);
#else
    (void) ctx;
    (void) texture;
    (void) state;
    (void) previous_state;
    return false;
#endif
}

bool GrDirectContext_setBackendRenderTargetState(reskia_direct_context_t *ctx, const reskia_gr_backend_render_target_t *render_target, const reskia_skgpu_mutable_texture_state_t *state, reskia_skgpu_mutable_texture_state_t *previous_state) {
#if defined(SK_GANESH)
    if (ctx == nullptr || render_target == nullptr || state == nullptr || !as_mutable_texture_state(state)->isValid()) {
        return false;
    }
    return as_direct_context(ctx)->setBackendRenderTargetState(*as_backend_render_target(render_target), *as_mutable_texture_state(state), as_mutable_texture_state(previous_state), nullptr, nullptr);
#else
    (void) ctx;
    (void) render_target;
    (void) state;
    (void) previous_state;
    return false;
#endif
}

bool GrDirectContext_precompileShader(reskia_direct_context_t *ctx, const reskia_data_t *key, const reskia_data_t *data) {
#if defined(SK_GANESH)
    return ctx != nullptr && key != nullptr && data != nullptr && as_direct_context(ctx)->precompileShader(*as_data(key), *as_data(data));
#else
    (void) ctx;
    (void) key;
    (void) data;
    return false;
#endif
}

void GrDirectContext_deleteBackendTexture(reskia_direct_context_t *ctx, const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    if (ctx == nullptr || texture == nullptr) {
        return;
    }
    as_direct_context(ctx)->deleteBackendTexture(*as_backend_texture(texture));
#else
    (void) ctx;
    (void) texture;
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

reskia_gr_surface_characterization_t *GrContextThreadSafeProxy_createCharacterization(reskia_gr_context_thread_safe_proxy_t *proxy, size_t cache_max_resource_bytes, const reskia_image_info_t *image_info, const reskia_gr_backend_format_t *backend_format, int sample_count, int origin, const reskia_surface_props_t *surface_props, bool is_mipmapped, bool will_use_gl_fbo0, bool is_textureable, bool is_protected, bool vk_rt_supports_input_attachment, bool for_vulkan_secondary_command_buffer) {
#if defined(SK_GANESH)
    if (proxy == nullptr || image_info == nullptr || backend_format == nullptr || surface_props == nullptr || sample_count < 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_surface_characterization_t *>(new GrSurfaceCharacterization(as_thread_safe_proxy(proxy)->createCharacterization(cache_max_resource_bytes, *as_image_info(image_info), *as_backend_format(backend_format), sample_count, static_cast<GrSurfaceOrigin>(origin), *as_surface_props(surface_props), is_mipmapped, will_use_gl_fbo0, is_textureable, to_protected(is_protected), vk_rt_supports_input_attachment, for_vulkan_secondary_command_buffer)));
#else
    (void) proxy;
    (void) cache_max_resource_bytes;
    (void) image_info;
    (void) backend_format;
    (void) sample_count;
    (void) origin;
    (void) surface_props;
    (void) is_mipmapped;
    (void) will_use_gl_fbo0;
    (void) is_textureable;
    (void) is_protected;
    (void) vk_rt_supports_input_attachment;
    (void) for_vulkan_secondary_command_buffer;
    return nullptr;
#endif
}

reskia_gr_surface_characterization_t *GrSurfaceCharacterization_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_surface_characterization_t *>(new GrSurfaceCharacterization());
#else
    return nullptr;
#endif
}

reskia_gr_surface_characterization_t *GrSurfaceCharacterization_newCopy(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? reinterpret_cast<reskia_gr_surface_characterization_t *>(new GrSurfaceCharacterization(*as_surface_characterization(characterization))) : nullptr;
#else
    (void) characterization;
    return nullptr;
#endif
}

void GrSurfaceCharacterization_delete(reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    delete as_surface_characterization(characterization);
#else
    (void) characterization;
#endif
}

bool GrSurfaceCharacterization_equals(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_surface_characterization_t *other) {
#if defined(SK_GANESH)
    return characterization != nullptr && other != nullptr && *as_surface_characterization(characterization) == *as_surface_characterization(other);
#else
    (void) characterization;
    (void) other;
    return false;
#endif
}

bool GrSurfaceCharacterization_notEquals(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_surface_characterization_t *other) {
#if defined(SK_GANESH)
    return characterization != nullptr && other != nullptr && *as_surface_characterization(characterization) != *as_surface_characterization(other);
#else
    (void) characterization;
    (void) other;
    return false;
#endif
}

bool GrSurfaceCharacterization_isValid(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr && as_surface_characterization(characterization)->isValid();
#else
    (void) characterization;
    return false;
#endif
}

int GrSurfaceCharacterization_width(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? as_surface_characterization(characterization)->width() : 0;
#else
    (void) characterization;
    return 0;
#endif
}

int GrSurfaceCharacterization_height(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? as_surface_characterization(characterization)->height() : 0;
#else
    (void) characterization;
    return 0;
#endif
}

int GrSurfaceCharacterization_colorType(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? static_cast<int>(as_surface_characterization(characterization)->colorType()) : 0;
#else
    (void) characterization;
    return 0;
#endif
}

int GrSurfaceCharacterization_sampleCount(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? as_surface_characterization(characterization)->sampleCount() : 0;
#else
    (void) characterization;
    return 0;
#endif
}

int GrSurfaceCharacterization_origin(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? static_cast<int>(as_surface_characterization(characterization)->origin()) : 0;
#else
    (void) characterization;
    return 0;
#endif
}

bool GrSurfaceCharacterization_isTextureable(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr && as_surface_characterization(characterization)->isTextureable();
#else
    (void) characterization;
    return false;
#endif
}

bool GrSurfaceCharacterization_isMipMapped(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr && as_surface_characterization(characterization)->isMipMapped();
#else
    (void) characterization;
    return false;
#endif
}

bool GrSurfaceCharacterization_isCompatible(const reskia_gr_surface_characterization_t *characterization, const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return characterization != nullptr && texture != nullptr && as_surface_characterization(characterization)->isCompatible(*as_backend_texture(texture));
#else
    (void) characterization;
    (void) texture;
    return false;
#endif
}

reskia_gr_backend_format_t *GrSurfaceCharacterization_backendFormat(const reskia_gr_surface_characterization_t *characterization) {
#if defined(SK_GANESH)
    return characterization != nullptr ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_surface_characterization(characterization)->backendFormat())) : nullptr;
#else
    (void) characterization;
    return nullptr;
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

int Graphite_Context_backend(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr ? to_reskia_graphite_backend_api(as_graphite_context(ctx)->backend()) : 0;
#else
    (void) ctx;
    return 0;
#endif
}

reskia_graphite_recorder_t *Graphite_Context_makeRecorder(reskia_graphite_context_t *ctx) {
    return Reskia_GraphiteContext_MakeRecorder(ctx);
}

bool Graphite_Context_submit(reskia_graphite_context_t *ctx, bool sync_cpu) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->submit(to_graphite_sync_cpu(sync_cpu));
#else
    (void) ctx;
    (void) sync_cpu;
    return false;
#endif
}

void Graphite_Context_checkAsyncWorkCompletion(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr) {
        as_graphite_context(ctx)->checkAsyncWorkCompletion();
    }
#else
    (void) ctx;
#endif
}

void Graphite_Context_deleteBackendTexture(reskia_graphite_context_t *ctx, const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr && texture != nullptr) {
        as_graphite_context(ctx)->deleteBackendTexture(*as_graphite_backend_texture(texture));
    }
#else
    (void) ctx;
    (void) texture;
#endif
}

void Graphite_Context_freeGpuResources(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr) {
        as_graphite_context(ctx)->freeGpuResources();
    }
#else
    (void) ctx;
#endif
}

void Graphite_Context_performDeferredCleanup(reskia_graphite_context_t *ctx, int64_t ms_not_used) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr && ms_not_used >= 0) {
        as_graphite_context(ctx)->performDeferredCleanup(std::chrono::milliseconds(ms_not_used));
    }
#else
    (void) ctx;
    (void) ms_not_used;
#endif
}

size_t Graphite_Context_currentBudgetedBytes(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr ? as_graphite_context(ctx)->currentBudgetedBytes() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

void Graphite_Context_dumpMemoryStatistics(reskia_graphite_context_t *ctx, reskia_trace_memory_dump_t *trace_memory_dump) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr && trace_memory_dump != nullptr) {
        as_graphite_context(ctx)->dumpMemoryStatistics(reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump));
    }
#else
    (void) ctx;
    (void) trace_memory_dump;
#endif
}

bool Graphite_Context_supportsProtectedContent(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->supportsProtectedContent();
#else
    (void) ctx;
    return false;
#endif
}

void Graphite_Recorder_freeGpuResources(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    if (recorder != nullptr) {
        as_graphite_recorder(recorder)->freeGpuResources();
    }
#else
    (void) recorder;
#endif
}

void Graphite_Recorder_performDeferredCleanup(reskia_graphite_recorder_t *recorder, int64_t ms_not_used) {
#if defined(SK_GRAPHITE)
    if (recorder != nullptr && ms_not_used >= 0) {
        as_graphite_recorder(recorder)->performDeferredCleanup(std::chrono::milliseconds(ms_not_used));
    }
#else
    (void) recorder;
    (void) ms_not_used;
#endif
}

size_t Graphite_Recorder_currentBudgetedBytes(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? as_graphite_recorder(recorder)->currentBudgetedBytes() : 0;
#else
    (void) recorder;
    return 0;
#endif
}

void Graphite_Recorder_dumpMemoryStatistics(reskia_graphite_recorder_t *recorder, reskia_trace_memory_dump_t *trace_memory_dump) {
#if defined(SK_GRAPHITE)
    if (recorder != nullptr && trace_memory_dump != nullptr) {
        as_graphite_recorder(recorder)->dumpMemoryStatistics(reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump));
    }
#else
    (void) recorder;
    (void) trace_memory_dump;
#endif
}

reskia_graphite_backend_texture_t *Graphite_Recorder_createBackendTexture(reskia_graphite_recorder_t *recorder, sk_i_size_t dimensions, const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    if (recorder == nullptr || dimensions == 0 || info == nullptr || !as_graphite_texture_info(info)->isValid()) {
        return nullptr;
    }
    auto texture = as_graphite_recorder(recorder)->createBackendTexture(static_sk_i_size_get_entity(dimensions), *as_graphite_texture_info(info));
    return reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture(texture));
#else
    (void) recorder;
    (void) dimensions;
    (void) info;
    return nullptr;
#endif
}

bool Graphite_Recorder_updateBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture, const reskia_pixmap_t *src_data, int num_levels) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr && texture != nullptr && src_data != nullptr && num_levels > 0 &&
           as_graphite_recorder(recorder)->updateBackendTexture(*as_graphite_backend_texture(texture), reinterpret_cast<const SkPixmap *>(src_data), num_levels);
#else
    (void) recorder;
    (void) texture;
    (void) src_data;
    (void) num_levels;
    return false;
#endif
}

void Graphite_Recorder_deleteBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    if (recorder != nullptr && texture != nullptr) {
        as_graphite_recorder(recorder)->deleteBackendTexture(*as_graphite_backend_texture(texture));
    }
#else
    (void) recorder;
    (void) texture;
#endif
}

reskia_graphite_texture_info_t *Graphite_TextureInfo_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_texture_info_t *>(new skgpu::graphite::TextureInfo());
#else
    return nullptr;
#endif
}

reskia_graphite_texture_info_t *Graphite_TextureInfo_newMtl(const reskia_graphite_mtl_texture_info_t *info) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    if (info == nullptr) {
        return nullptr;
    }
    skgpu::graphite::MtlTextureInfo mtl_info(
            info->sample_count,
            to_graphite_mipmapped(info->mipmapped),
            info->format,
            info->usage,
            info->storage_mode,
            info->framebuffer_only);
    return reinterpret_cast<reskia_graphite_texture_info_t *>(new skgpu::graphite::TextureInfo(mtl_info));
#else
    (void) info;
    return nullptr;
#endif
}

reskia_graphite_texture_info_t *Graphite_TextureInfo_newCopy(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? reinterpret_cast<reskia_graphite_texture_info_t *>(new skgpu::graphite::TextureInfo(*as_graphite_texture_info(info))) : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

void Graphite_TextureInfo_delete(reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    delete as_graphite_texture_info(info);
#else
    (void) info;
#endif
}

bool Graphite_TextureInfo_equals(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other) {
#if defined(SK_GRAPHITE)
    return info != nullptr && other != nullptr && *as_graphite_texture_info(info) == *as_graphite_texture_info(other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

bool Graphite_TextureInfo_notEquals(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other) {
    return info != nullptr && other != nullptr && !Graphite_TextureInfo_equals(info, other);
}

bool Graphite_TextureInfo_isValid(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr && as_graphite_texture_info(info)->isValid();
#else
    (void) info;
    return false;
#endif
}

int Graphite_TextureInfo_backend(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? to_reskia_graphite_backend_api(as_graphite_texture_info(info)->backend()) : 0;
#else
    (void) info;
    return 0;
#endif
}

uint32_t Graphite_TextureInfo_numSamples(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? as_graphite_texture_info(info)->numSamples() : 0;
#else
    (void) info;
    return 0;
#endif
}

bool Graphite_TextureInfo_mipmapped(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr && from_graphite_mipmapped(as_graphite_texture_info(info)->mipmapped());
#else
    (void) info;
    return false;
#endif
}

bool Graphite_TextureInfo_isProtected(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr && from_graphite_protected(as_graphite_texture_info(info)->isProtected());
#else
    (void) info;
    return false;
#endif
}

bool Graphite_TextureInfo_getMtlTextureInfo(const reskia_graphite_texture_info_t *info, reskia_graphite_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    if (info == nullptr || out_info == nullptr) {
        return false;
    }
    skgpu::graphite::MtlTextureInfo mtl_info;
    if (!as_graphite_texture_info(info)->getMtlTextureInfo(&mtl_info)) {
        return false;
    }
    out_info->sample_count = mtl_info.fSampleCount;
    out_info->mipmapped = from_graphite_mipmapped(mtl_info.fMipmapped);
    out_info->format = mtl_info.fFormat;
    out_info->usage = mtl_info.fUsage;
    out_info->storage_mode = mtl_info.fStorageMode;
    out_info->framebuffer_only = mtl_info.fFramebufferOnly;
    return true;
#else
    (void) info;
    return false;
#endif
}

reskia_string_t *Graphite_TextureInfo_toString(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? reinterpret_cast<reskia_string_t *>(new SkString(as_graphite_texture_info(info)->toString())) : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

reskia_graphite_backend_texture_t *Graphite_BackendTexture_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture());
#else
    return nullptr;
#endif
}

reskia_graphite_backend_texture_t *Graphite_BackendTexture_newMtl(sk_i_size_t dimensions, void *mtl_texture) {
#if defined(SK_GRAPHITE) && defined(SK_METAL) && defined(__APPLE__)
    if (dimensions == 0 || mtl_texture == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture(static_sk_i_size_get_entity(dimensions), reinterpret_cast<CFTypeRef>(mtl_texture)));
#else
    (void) dimensions;
    (void) mtl_texture;
    return nullptr;
#endif
}

reskia_graphite_backend_texture_t *Graphite_BackendTexture_newCopy(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    return texture != nullptr ? reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture(*as_graphite_backend_texture(texture))) : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

void Graphite_BackendTexture_delete(reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    delete as_graphite_backend_texture(texture);
#else
    (void) texture;
#endif
}

bool Graphite_BackendTexture_equals(const reskia_graphite_backend_texture_t *texture, const reskia_graphite_backend_texture_t *other) {
#if defined(SK_GRAPHITE)
    return texture != nullptr && other != nullptr && *as_graphite_backend_texture(texture) == *as_graphite_backend_texture(other);
#else
    (void) texture;
    (void) other;
    return false;
#endif
}

bool Graphite_BackendTexture_notEquals(const reskia_graphite_backend_texture_t *texture, const reskia_graphite_backend_texture_t *other) {
    return texture != nullptr && other != nullptr && !Graphite_BackendTexture_equals(texture, other);
}

bool Graphite_BackendTexture_isValid(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    return texture != nullptr && as_graphite_backend_texture(texture)->isValid();
#else
    (void) texture;
    return false;
#endif
}

int Graphite_BackendTexture_backend(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    return texture != nullptr ? to_reskia_graphite_backend_api(as_graphite_backend_texture(texture)->backend()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

sk_i_size_t Graphite_BackendTexture_dimensions(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    return texture != nullptr ? static_sk_i_size_make(as_graphite_backend_texture(texture)->dimensions()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

reskia_graphite_texture_info_t *Graphite_BackendTexture_info(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE)
    return texture != nullptr ? reinterpret_cast<reskia_graphite_texture_info_t *>(new skgpu::graphite::TextureInfo(as_graphite_backend_texture(texture)->info())) : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

void Graphite_BackendTexture_setMutableState(reskia_graphite_backend_texture_t *texture, const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GRAPHITE)
    if (texture != nullptr && state != nullptr && reinterpret_cast<const skgpu::MutableTextureState *>(state)->isValid()) {
        as_graphite_backend_texture(texture)->setMutableState(*reinterpret_cast<const skgpu::MutableTextureState *>(state));
    }
#else
    (void) texture;
    (void) state;
#endif
}

void *Graphite_BackendTexture_getMtlTexture(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    return texture != nullptr ? const_cast<void *>(as_graphite_backend_texture(texture)->getMtlTexture()) : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

}
