//
// Created by dolphilia on 2026/02/17.
//

#include "sk_gpu_context.h"

#include "include/gpu/GrDirectContext.h"

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
    if (ctx == nullptr) {
        return;
    }
    reinterpret_cast<GrDirectContext *>(ctx)->flushAndSubmit(sync_cpu ? GrSyncCpu::kYes : GrSyncCpu::kNo);
#else
    (void) ctx;
    (void) sync_cpu;
#endif
}

void Reskia_DirectContext_Abandon(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    reinterpret_cast<GrDirectContext *>(ctx)->abandonContext();
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
