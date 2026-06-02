//
// Created by dolphilia on 2026/02/17.
//

#include "sk_gpu_context.h"

#include "sk_async_read_result-internal.h"
#include "sk_surface_gpu.h"

#include "include/core/SkColor.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkString.h"
#include "include/core/SkSurface.h"
#include "include/core/SkSurfaceProps.h"
#include "include/core/SkYUVAInfo.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/GrTypes.h"
#include "include/core/SkTextureCompressionType.h"

#include <chrono>
#include <memory>
#include <string_view>
#include <vector>

#if defined(SK_VULKAN)
#include "include/gpu/vk/GrVkBackendContext.h"
#endif

#if defined(SK_GRAPHITE)
#include "include/gpu/graphite/Context.h"
#include "include/gpu/graphite/ContextOptions.h"
#include "include/gpu/graphite/BackendSemaphore.h"
#include "include/gpu/graphite/BackendTexture.h"
#include "include/gpu/graphite/GraphiteTypes.h"
#include "include/gpu/graphite/ImageProvider.h"
#include "src/capture/SkCapture.h"
#include "include/gpu/graphite/Recorder.h"
#include "include/gpu/graphite/Recording.h"
#include "include/gpu/graphite/TextureInfo.h"
#include "include/gpu/graphite/YUVABackendTextures.h"
#include "src/core/SkYUVAInfoLocation.h"
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
#include "include/gpu/ganesh/GrBackendSemaphore.h"
#include "include/gpu/ganesh/GrBackendSurface.h"
#include "include/gpu/ganesh/GrContextOptions.h"
#include "include/gpu/ganesh/GrContextThreadSafeProxy.h"
#include "include/gpu/ganesh/GrRecordingContext.h"
#include "include/gpu/GpuTypes.h"
#include "include/gpu/MutableTextureState.h"
#include "include/gpu/ShaderErrorHandler.h"
#include "include/gpu/ganesh/GrExternalTextureGenerator.h"
#include "include/gpu/ganesh/mock/GrMockTypes.h"
#include "include/private/chromium/GrSurfaceCharacterization.h"
#endif

#if defined(SK_GANESH) && defined(SK_METAL) && defined(__APPLE__)
#include "include/gpu/ganesh/mtl/GrMtlBackendContext.h"
#include "include/gpu/ganesh/mtl/GrMtlDirectContext.h"
#include "include/ports/SkCFObject.h"
#endif

#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_capabilities-internal.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_image_required_properties-internal.h"
#include "../handles/static_sk_i_size.h"

namespace {

void clear_yuva_locations(reskia_yuva_location_t *locations) {
    if (locations == nullptr) {
        return;
    }
    for (int i = 0; i < 4; ++i) {
        locations[i].plane = -1;
        locations[i].channel = -1;
    }
}

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

GrContextOptions *as_context_options(reskia_gr_context_options_t *options) {
    return reinterpret_cast<GrContextOptions *>(options);
}

const GrContextOptions *as_context_options(const reskia_gr_context_options_t *options) {
    return reinterpret_cast<const GrContextOptions *>(options);
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

class ReskiaShaderErrorHandler final : public skgpu::ShaderErrorHandler {
public:
    ReskiaShaderErrorHandler(reskia_shader_error_proc_t proc,
                             void *user_data,
                             reskia_graphite_release_proc_t release_proc)
            : fProc(proc), fUserData(user_data), fReleaseProc(release_proc) {}

    ~ReskiaShaderErrorHandler() override {
        if (fReleaseProc != nullptr) {
            fReleaseProc(fUserData);
        }
    }

    void compileError(const char *shader, const char *errors) override {
        if (fProc != nullptr) {
            fProc(fUserData, shader != nullptr ? shader : "", errors != nullptr ? errors : "");
        }
    }

private:
    reskia_shader_error_proc_t fProc;
    void *fUserData;
    reskia_graphite_release_proc_t fReleaseProc;
};

class ReskiaGrExternalTexture final : public GrExternalTexture {
public:
    ReskiaGrExternalTexture(const GrBackendTexture& texture,
                            reskia_gr_external_texture_dispose_proc_t dispose_proc,
                            void *user_data,
                            reskia_graphite_release_proc_t release_proc)
            : fTexture(texture),
              fDisposeProc(dispose_proc),
              fUserData(user_data),
              fReleaseProc(release_proc) {}

    ~ReskiaGrExternalTexture() override {
        this->dispose();
        if (fReleaseProc != nullptr) {
            fReleaseProc(fUserData);
        }
    }

    GrBackendTexture getBackendTexture() override {
        return fTexture;
    }

    void dispose() override {
        if (fDisposed) {
            return;
        }
        fDisposed = true;
        if (fDisposeProc != nullptr) {
            fDisposeProc(fUserData, reinterpret_cast<const reskia_gr_backend_texture_t *>(&fTexture));
        }
    }

private:
    GrBackendTexture fTexture;
    reskia_gr_external_texture_dispose_proc_t fDisposeProc;
    void *fUserData;
    reskia_graphite_release_proc_t fReleaseProc;
    bool fDisposed = false;
};

class ReskiaGrExternalTextureGenerator final : public GrExternalTextureGenerator {
public:
    ReskiaGrExternalTextureGenerator(const SkImageInfo& info,
                                     reskia_gr_external_texture_generate_proc_t generate_proc,
                                     void *user_data,
                                     reskia_graphite_release_proc_t release_proc)
            : GrExternalTextureGenerator(info),
              fGenerateProc(generate_proc),
              fUserData(user_data),
              fReleaseProc(release_proc) {}

    ~ReskiaGrExternalTextureGenerator() override {
        if (fReleaseProc != nullptr) {
            fReleaseProc(fUserData);
        }
    }

    std::unique_ptr<GrExternalTexture> generateExternalTexture(GrRecordingContext *ctx,
                                                               skgpu::Mipmapped mipmapped) override {
        if (fGenerateProc == nullptr) {
            return std::make_unique<ReskiaGrExternalTexture>(GrBackendTexture(), nullptr, nullptr, nullptr);
        }
        auto *texture = fGenerateProc(
                reinterpret_cast<reskia_direct_context_t *>(ctx),
                mipmapped == skgpu::Mipmapped::kYes,
                fUserData);
        return texture != nullptr
                ? std::unique_ptr<GrExternalTexture>(reinterpret_cast<ReskiaGrExternalTexture *>(texture))
                : std::make_unique<ReskiaGrExternalTexture>(GrBackendTexture(), nullptr, nullptr, nullptr);
    }

private:
    reskia_gr_external_texture_generate_proc_t fGenerateProc;
    void *fUserData;
    reskia_graphite_release_proc_t fReleaseProc;
};

ReskiaShaderErrorHandler *as_shader_error_handler(reskia_shader_error_handler_t *handler) {
    return reinterpret_cast<ReskiaShaderErrorHandler *>(handler);
}

ReskiaGrExternalTexture *as_external_texture(reskia_gr_external_texture_t *texture) {
    return reinterpret_cast<ReskiaGrExternalTexture *>(texture);
}

ReskiaGrExternalTextureGenerator *as_external_texture_generator(reskia_gr_external_texture_generator_t *generator) {
    return reinterpret_cast<ReskiaGrExternalTextureGenerator *>(generator);
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
const SkYUVAInfo *as_yuva_info(const reskia_yuva_info_t *info) {
    return reinterpret_cast<const SkYUVAInfo *>(info);
}

struct GraphiteFinishedCallbackContext {
    reskia_graphite_finished_proc_t proc;
    void *user_data;
    reskia_graphite_release_proc_t release_proc;
};

void graphite_finished_callback(skgpu::graphite::GpuFinishedContext context, skgpu::CallbackResult result) {
    auto *callback_context = static_cast<GraphiteFinishedCallbackContext *>(context);
    if (callback_context == nullptr) {
        return;
    }
    if (callback_context->proc != nullptr) {
        callback_context->proc(callback_context->user_data, result == skgpu::CallbackResult::kSuccess ? 1 : 0);
    }
    if (callback_context->release_proc != nullptr) {
        callback_context->release_proc(callback_context->user_data);
    }
    delete callback_context;
}

skgpu::graphite::Context *as_graphite_context(reskia_graphite_context_t *ctx) {
    return reinterpret_cast<skgpu::graphite::Context *>(ctx);
}

const skgpu::graphite::ContextOptions *as_graphite_context_options(const reskia_graphite_context_options_t *options) {
    return reinterpret_cast<const skgpu::graphite::ContextOptions *>(options);
}

skgpu::graphite::ContextOptions *as_graphite_context_options(reskia_graphite_context_options_t *options) {
    return reinterpret_cast<skgpu::graphite::ContextOptions *>(options);
}

const skgpu::graphite::Context *as_graphite_context(const reskia_graphite_context_t *ctx) {
    return reinterpret_cast<const skgpu::graphite::Context *>(ctx);
}

const skgpu::graphite::Context::ContextID *as_graphite_context_id(const reskia_graphite_context_id_t *context_id) {
    return reinterpret_cast<const skgpu::graphite::Context::ContextID *>(context_id);
}

skgpu::graphite::Recorder *as_graphite_recorder(reskia_graphite_recorder_t *recorder) {
    return reinterpret_cast<skgpu::graphite::Recorder *>(recorder);
}

const skgpu::graphite::Recorder *as_graphite_recorder(const reskia_graphite_recorder_t *recorder) {
    return reinterpret_cast<const skgpu::graphite::Recorder *>(recorder);
}

skgpu::graphite::Recording *as_graphite_recording(reskia_graphite_recording_t *recording) {
    return reinterpret_cast<skgpu::graphite::Recording *>(recording);
}

const skgpu::graphite::BackendTexture *as_graphite_backend_texture(const reskia_graphite_backend_texture_t *texture) {
    return reinterpret_cast<const skgpu::graphite::BackendTexture *>(texture);
}

const skgpu::graphite::RecorderOptions *as_graphite_recorder_options(const reskia_graphite_recorder_options_t *options) {
    return reinterpret_cast<const skgpu::graphite::RecorderOptions *>(options);
}

skgpu::graphite::RecorderOptions *as_graphite_recorder_options(reskia_graphite_recorder_options_t *options) {
    return reinterpret_cast<skgpu::graphite::RecorderOptions *>(options);
}

skgpu::graphite::ImageProvider *as_graphite_image_provider(reskia_graphite_image_provider_t *provider) {
    return reinterpret_cast<skgpu::graphite::ImageProvider *>(provider);
}

const skgpu::graphite::ImageProvider *as_graphite_image_provider(const reskia_graphite_image_provider_t *provider) {
    return reinterpret_cast<const skgpu::graphite::ImageProvider *>(provider);
}

const skgpu::graphite::BackendSemaphore *as_graphite_backend_semaphore(const reskia_graphite_backend_semaphore_t *semaphore) {
    return reinterpret_cast<const skgpu::graphite::BackendSemaphore *>(semaphore);
}

skgpu::graphite::BackendSemaphore *as_graphite_backend_semaphore(reskia_graphite_backend_semaphore_t *semaphore) {
    return reinterpret_cast<skgpu::graphite::BackendSemaphore *>(semaphore);
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

const skgpu::graphite::YUVABackendTextureInfo *as_graphite_yuva_backend_texture_info(const reskia_graphite_yuva_backend_texture_info_t *info) {
    return reinterpret_cast<const skgpu::graphite::YUVABackendTextureInfo *>(info);
}

const skgpu::graphite::YUVABackendTextures *as_graphite_yuva_backend_textures(const reskia_graphite_yuva_backend_textures_t *textures) {
    return reinterpret_cast<const skgpu::graphite::YUVABackendTextures *>(textures);
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

bool is_valid_graphite_rescale_gamma(reskia_graphite_rescale_gamma_t gamma) {
    return gamma == static_cast<reskia_graphite_rescale_gamma_t>(SkImage::RescaleGamma::kSrc) ||
           gamma == static_cast<reskia_graphite_rescale_gamma_t>(SkImage::RescaleGamma::kLinear);
}

class ReskiaGraphiteImageProvider final : public skgpu::graphite::ImageProvider {
public:
    ReskiaGraphiteImageProvider(reskia_graphite_image_provider_find_or_create_proc_t proc,
                                void *user_data,
                                reskia_graphite_release_proc_t release_proc)
            : fProc(proc), fUserData(user_data), fReleaseProc(release_proc) {}

    ~ReskiaGraphiteImageProvider() override {
        if (fReleaseProc != nullptr) {
            fReleaseProc(fUserData);
        }
    }

    sk_sp<SkImage> findOrCreate(skgpu::graphite::Recorder *recorder,
                                const SkImage *image,
                                SkImage::RequiredProperties properties) override {
        if (fProc == nullptr || recorder == nullptr || image == nullptr) {
            return nullptr;
        }
        const sk_image_required_properties_t properties_handle =
                static_sk_image_required_properties_make(properties);
        const sk_image_t image_handle = fProc(
                reinterpret_cast<reskia_graphite_recorder_t *>(recorder),
                reinterpret_cast<const reskia_image_t *>(image),
                properties_handle,
                fUserData);
        static_sk_image_required_properties_delete(properties_handle);
        return image_handle != 0 ? static_sk_image_take_entity(image_handle) : nullptr;
    }

private:
    reskia_graphite_image_provider_find_or_create_proc_t fProc;
    void *fUserData;
    reskia_graphite_release_proc_t fReleaseProc;
};

bool is_valid_graphite_rescale_mode(reskia_graphite_rescale_mode_t mode) {
    return mode >= static_cast<reskia_graphite_rescale_mode_t>(SkImage::RescaleMode::kNearest) &&
           mode <= static_cast<reskia_graphite_rescale_mode_t>(SkImage::RescaleMode::kRepeatedCubic);
}

bool is_valid_graphite_yuv_color_space(reskia_graphite_yuv_color_space_t yuv_color_space) {
    return yuv_color_space >= 0 &&
           yuv_color_space <= static_cast<reskia_graphite_yuv_color_space_t>(kLastEnum_SkYUVColorSpace);
}

bool has_i_size_handle(sk_i_size_t size) {
    return size != 0 && static_sk_i_size_get_ptr(size) != nullptr;
}

bool has_optional_color_space_handle(sk_color_space_t color_space) {
    return color_space == 0 || static_sk_color_space_get_ptr(color_space) != nullptr;
}

bool copy_yuva_locations(const SkYUVAInfo::YUVALocations &native_locations, reskia_yuva_location_t *locations) {
    if (locations == nullptr) {
        return false;
    }
    for (int i = 0; i < SkYUVAInfo::kYUVAChannelCount; ++i) {
        locations[i].plane = native_locations[i].fPlane;
        locations[i].channel = static_cast<int32_t>(native_locations[i].fChannel);
    }
    return SkYUVAInfo::YUVALocation::AreValidLocations(native_locations);
}
#endif

}  // namespace

extern "C" {

reskia_direct_context_t *Reskia_GaneshContext_MakeMetal(void *device, void *queue) {
#if defined(SK_GANESH) && defined(SK_METAL) && defined(__APPLE__)
    if (device == nullptr || queue == nullptr) {
        return nullptr;
    }

    GrMtlBackendContext backend_context;
    backend_context.fDevice = sk_ret_cfp(reinterpret_cast<CFTypeRef>(device));
    backend_context.fQueue = sk_ret_cfp(reinterpret_cast<CFTypeRef>(queue));

    return reinterpret_cast<reskia_direct_context_t *>(GrDirectContexts::MakeMetal(backend_context).release());
#else
    (void) device;
    (void) queue;
    return nullptr;
#endif
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

bool GrDirectContext_canDetectNewVkPipelineCacheData(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->canDetectNewVkPipelineCacheData();
#else
    (void) ctx;
    return false;
#endif
}

bool GrDirectContext_hasNewVkPipelineCacheData(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr && as_direct_context(ctx)->hasNewVkPipelineCacheData();
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

void GrDirectContext_storeVkPipelineCacheDataWithMaxSize(reskia_direct_context_t *ctx, size_t max_size) {
#if defined(SK_GANESH)
    if (ctx == nullptr) {
        return;
    }
    as_direct_context(ctx)->storeVkPipelineCacheData(max_size);
#else
    (void) ctx;
    (void) max_size;
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

reskia_gpu_stats_flags_t GrDirectContext_supportedGpuStats(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr
            ? static_cast<reskia_gpu_stats_flags_t>(as_direct_context(ctx)->supportedGpuStats())
            : 0;
#else
    (void) ctx;
    return 0;
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

const_sk_capabilities_t GrRecordingContext_skCapabilities(reskia_direct_context_t *ctx) {
#if defined(SK_GANESH)
    return ctx != nullptr ? static_const_sk_capabilities_make(as_recording_context(ctx)->skCapabilities()) : 0;
#else
    (void) ctx;
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
    return reinterpret_cast<reskia_gr_surface_characterization_t *>(new GrSurfaceCharacterization(as_thread_safe_proxy(proxy)->createCharacterization(cache_max_resource_bytes, *as_image_info(image_info), *as_backend_format(backend_format), sample_count, static_cast<GrSurfaceOrigin>(origin), *as_surface_props(surface_props), static_cast<skgpu::Mipmapped>(is_mipmapped), will_use_gl_fbo0, is_textureable, to_protected(is_protected), vk_rt_supports_input_attachment, for_vulkan_secondary_command_buffer)));
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

reskia_gr_context_options_t *GrContextOptions_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_context_options_t *>(new GrContextOptions());
#else
    return nullptr;
#endif
}

reskia_gr_context_options_t *GrContextOptions_newCopy(const reskia_gr_context_options_t *options) {
#if defined(SK_GANESH)
    return options != nullptr ? reinterpret_cast<reskia_gr_context_options_t *>(new GrContextOptions(*as_context_options(options))) : nullptr;
#else
    (void) options;
    return nullptr;
#endif
}

void GrContextOptions_delete(reskia_gr_context_options_t *options) {
#if defined(SK_GANESH)
    delete as_context_options(options);
#else
    (void) options;
#endif
}

bool GrContextOptions_suppressPrints(const reskia_gr_context_options_t *options) {
#if defined(SK_GANESH)
    return options != nullptr && as_context_options(options)->fSuppressPrints;
#else
    (void) options;
    return false;
#endif
}

void GrContextOptions_setSuppressPrints(reskia_gr_context_options_t *options, bool suppress) {
#if defined(SK_GANESH)
    if (options != nullptr) {
        as_context_options(options)->fSuppressPrints = suppress;
    }
#else
    (void) options;
    (void) suppress;
#endif
}

void GrContextOptions_setShaderErrorHandler(reskia_gr_context_options_t *options, reskia_shader_error_handler_t *handler) {
#if defined(SK_GANESH)
    if (options != nullptr) {
        as_context_options(options)->fShaderErrorHandler = handler != nullptr ? as_shader_error_handler(handler) : nullptr;
    }
#else
    (void) options;
    (void) handler;
#endif
}

reskia_shader_error_handler_t *ShaderErrorHandler_new(reskia_shader_error_proc_t proc, void *user_data, reskia_graphite_release_proc_t release_proc) {
#if defined(SK_GANESH)
    return proc != nullptr ? reinterpret_cast<reskia_shader_error_handler_t *>(new ReskiaShaderErrorHandler(proc, user_data, release_proc)) : nullptr;
#else
    (void) proc;
    (void) user_data;
    (void) release_proc;
    return nullptr;
#endif
}

void ShaderErrorHandler_delete(reskia_shader_error_handler_t *handler) {
#if defined(SK_GANESH)
    delete as_shader_error_handler(handler);
#else
    (void) handler;
#endif
}

void ShaderErrorHandler_compileError(reskia_shader_error_handler_t *handler, const char *shader, const char *errors) {
#if defined(SK_GANESH)
    if (handler != nullptr) {
        as_shader_error_handler(handler)->compileError(shader, errors);
    }
#else
    (void) handler;
    (void) shader;
    (void) errors;
#endif
}

reskia_gr_external_texture_t *GrExternalTexture_new(
        const reskia_gr_backend_texture_t *texture,
        reskia_gr_external_texture_dispose_proc_t dispose_proc,
        void *user_data,
        reskia_graphite_release_proc_t release_proc) {
#if defined(SK_GANESH)
    return texture != nullptr
            ? reinterpret_cast<reskia_gr_external_texture_t *>(
                    new ReskiaGrExternalTexture(*as_backend_texture(texture), dispose_proc, user_data, release_proc))
            : nullptr;
#else
    (void) texture;
    (void) dispose_proc;
    (void) user_data;
    (void) release_proc;
    return nullptr;
#endif
}

void GrExternalTexture_delete(reskia_gr_external_texture_t *texture) {
#if defined(SK_GANESH)
    delete as_external_texture(texture);
#else
    (void) texture;
#endif
}

reskia_gr_backend_texture_t *GrExternalTexture_getBackendTexture(reskia_gr_external_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr
            ? reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_external_texture(texture)->getBackendTexture()))
            : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

void GrExternalTexture_dispose(reskia_gr_external_texture_t *texture) {
#if defined(SK_GANESH)
    if (texture != nullptr) {
        as_external_texture(texture)->dispose();
    }
#else
    (void) texture;
#endif
}

reskia_gr_external_texture_generator_t *GrExternalTextureGenerator_new(
        const reskia_image_info_t *image_info,
        reskia_gr_external_texture_generate_proc_t generate_proc,
        void *user_data,
        reskia_graphite_release_proc_t release_proc) {
#if defined(SK_GANESH)
    return image_info != nullptr && generate_proc != nullptr
            ? reinterpret_cast<reskia_gr_external_texture_generator_t *>(
                    new ReskiaGrExternalTextureGenerator(*as_image_info(image_info), generate_proc, user_data, release_proc))
            : nullptr;
#else
    (void) image_info;
    (void) generate_proc;
    (void) user_data;
    (void) release_proc;
    return nullptr;
#endif
}

void GrExternalTextureGenerator_delete(reskia_gr_external_texture_generator_t *generator) {
#if defined(SK_GANESH)
    delete as_external_texture_generator(generator);
#else
    (void) generator;
#endif
}

reskia_gr_external_texture_t *GrExternalTextureGenerator_generateExternalTexture(
        reskia_gr_external_texture_generator_t *generator,
        reskia_direct_context_t *recording_context,
        bool mipmapped) {
#if defined(SK_GANESH)
    if (generator == nullptr) {
        return nullptr;
    }
    std::unique_ptr<GrExternalTexture> texture = as_external_texture_generator(generator)->generateExternalTexture(
            as_recording_context(recording_context),
            to_mipmapped(mipmapped));
    return reinterpret_cast<reskia_gr_external_texture_t *>(texture.release());
#else
    (void) generator;
    (void) recording_context;
    (void) mipmapped;
    return nullptr;
#endif
}

sk_image_t SkImages_DeferredFromTextureGenerator(reskia_gr_external_texture_generator_t *generator) {
#if defined(SK_GANESH)
    if (generator == nullptr) {
        return 0;
    }
    std::unique_ptr<GrTextureGenerator> native_generator(as_external_texture_generator(generator));
    sk_sp<SkImage> image = SkImages::DeferredFromTextureGenerator(std::move(native_generator));
    return image ? static_sk_image_make(std::move(image)) : 0;
#else
    (void) generator;
    return 0;
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

reskia_graphite_context_options_t *Graphite_ContextOptions_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_context_options_t *>(new skgpu::graphite::ContextOptions());
#else
    return nullptr;
#endif
}

void Graphite_ContextOptions_delete(reskia_graphite_context_options_t *options) {
#if defined(SK_GRAPHITE)
    delete as_graphite_context_options(options);
#else
    (void) options;
#endif
}

size_t Graphite_ContextOptions_gpuBudgetInBytes(const reskia_graphite_context_options_t *options) {
#if defined(SK_GRAPHITE)
    return options != nullptr ? as_graphite_context_options(options)->fGpuBudgetInBytes : 0;
#else
    (void) options;
    return 0;
#endif
}

void Graphite_ContextOptions_setGpuBudgetInBytes(reskia_graphite_context_options_t *options, size_t budget) {
#if defined(SK_GRAPHITE)
    if (options != nullptr) {
        as_graphite_context_options(options)->fGpuBudgetInBytes = budget;
    }
#else
    (void) options;
    (void) budget;
#endif
}

reskia_graphite_recorder_options_t *Graphite_RecorderOptions_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_recorder_options_t *>(new skgpu::graphite::RecorderOptions());
#else
    return nullptr;
#endif
}

reskia_graphite_recorder_options_t *Graphite_RecorderOptions_newCopy(const reskia_graphite_recorder_options_t *options) {
#if defined(SK_GRAPHITE)
    return options != nullptr
            ? reinterpret_cast<reskia_graphite_recorder_options_t *>(new skgpu::graphite::RecorderOptions(*as_graphite_recorder_options(options)))
            : nullptr;
#else
    (void) options;
    return nullptr;
#endif
}

void Graphite_RecorderOptions_delete(reskia_graphite_recorder_options_t *options) {
#if defined(SK_GRAPHITE)
    delete as_graphite_recorder_options(options);
#else
    (void) options;
#endif
}

size_t Graphite_RecorderOptions_gpuBudgetInBytes(const reskia_graphite_recorder_options_t *options) {
#if defined(SK_GRAPHITE)
    return options != nullptr ? as_graphite_recorder_options(options)->fGpuBudgetInBytes : 0;
#else
    (void) options;
    return 0;
#endif
}

void Graphite_RecorderOptions_setGpuBudgetInBytes(reskia_graphite_recorder_options_t *options, size_t budget) {
#if defined(SK_GRAPHITE)
    if (options != nullptr) {
        as_graphite_recorder_options(options)->fGpuBudgetInBytes = budget;
    }
#else
    (void) options;
    (void) budget;
#endif
}

void Graphite_RecorderOptions_setImageProvider(reskia_graphite_recorder_options_t *options, reskia_graphite_image_provider_t *provider) {
#if defined(SK_GRAPHITE)
    if (options != nullptr) {
        as_graphite_recorder_options(options)->fImageProvider = provider != nullptr
                ? sk_ref_sp(as_graphite_image_provider(provider))
                : nullptr;
    }
#else
    (void) options;
    (void) provider;
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

reskia_graphite_recorder_t *Graphite_Context_makeRecorderWithOptions(reskia_graphite_context_t *ctx, const reskia_graphite_recorder_options_t *options) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || options == nullptr) {
        return nullptr;
    }

    auto recorder = as_graphite_context(ctx)->makeRecorder(*as_graphite_recorder_options(options));
    return reinterpret_cast<reskia_graphite_recorder_t *>(recorder.release());
#else
    (void) ctx;
    (void) options;
    return nullptr;
#endif
}

void Graphite_Recorder_delete(reskia_graphite_recorder_t *recorder) {
    Reskia_GraphiteRecorder_Release(recorder);
}

bool Graphite_Context_submit(reskia_graphite_context_t *ctx, bool sync_cpu) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->submit(skgpu::graphite::SubmitInfo(to_graphite_sync_cpu(sync_cpu)));
#else
    (void) ctx;
    (void) sync_cpu;
    return false;
#endif
}

reskia_graphite_submit_info_t Graphite_SubmitInfo_new() {
    return {false, false, 0};
}

reskia_graphite_submit_info_t Graphite_SubmitInfo_newWithSync(bool sync_cpu) {
    return {sync_cpu, false, 0};
}

reskia_graphite_submit_info_t Graphite_SubmitInfo_newWithSyncAndFrameID(bool sync_cpu, uint64_t frame_id) {
    return {sync_cpu, true, frame_id};
}

bool Graphite_Context_submitWithInfo(reskia_graphite_context_t *ctx, const reskia_graphite_submit_info_t *submit_info) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || submit_info == nullptr) {
        return false;
    }
    skgpu::graphite::SubmitInfo native(to_graphite_sync_cpu(submit_info->sync_cpu));
    if (submit_info->mark_frame_boundary) {
        native = skgpu::graphite::SubmitInfo(to_graphite_sync_cpu(submit_info->sync_cpu), submit_info->frame_id);
    }
    return as_graphite_context(ctx)->submit(native);
#else
    (void) ctx;
    (void) submit_info;
    return false;
#endif
}

bool Graphite_Context_hasUnfinishedGpuWork(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->hasUnfinishedGpuWork();
#else
    (void) ctx;
    return false;
#endif
}

bool Graphite_Context_hasPendingGPUWork(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->hasPendingGPUWork();
#else
    (void) ctx;
    return false;
#endif
}

reskia_graphite_insert_status_t Graphite_InsertStatus_new() {
    return 0;
}

reskia_graphite_insert_status_t Graphite_InsertStatus_newWithValue(int32_t value) {
    return value >= 0 && value <= 5 ? value : 0;
}

int32_t Graphite_InsertStatus_operator_InsertStatus_V(reskia_graphite_insert_status_t status) {
    return Graphite_InsertStatus_newWithValue(status);
}

reskia_string_t *Graphite_InsertStatus_message(reskia_graphite_insert_status_t status) {
    (void) status;
    return reinterpret_cast<reskia_string_t *>(new SkString());
}

bool Graphite_InsertStatus_operator_bool(reskia_graphite_insert_status_t status) {
    return Graphite_InsertStatus_newWithValue(status) == 0;
}

bool Graphite_Context_insertRecording(reskia_graphite_context_t *ctx, reskia_graphite_recording_t *recording) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || recording == nullptr) {
        return false;
    }
    skgpu::graphite::InsertRecordingInfo info;
    info.fRecording = as_graphite_recording(recording);
    return static_cast<bool>(as_graphite_context(ctx)->insertRecording(info));
#else
    (void) ctx;
    (void) recording;
    return false;
#endif
}

void Graphite_Context_startCapture(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr) {
        as_graphite_context(ctx)->startCapture();
    }
#else
    (void) ctx;
#endif
}

void Graphite_Context_endCapture(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr) {
        as_graphite_context(ctx)->endCapture();
    }
#else
    (void) ctx;
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsFromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, const reskia_image_info_t *dst_info, const reskia_i_rect_t *src_rect, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || image == nullptr || dst_info == nullptr || src_rect == nullptr || callback == nullptr ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixels(
            reinterpret_cast<const SkImage *>(image),
            *reinterpret_cast<const SkImageInfo *>(dst_info),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) image;
    (void) dst_info;
    (void) src_rect;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsFromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, const reskia_image_info_t *dst_info, const reskia_i_rect_t *src_rect, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || surface == nullptr || dst_info == nullptr || src_rect == nullptr || callback == nullptr ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixels(
            reinterpret_cast<const SkSurface *>(surface),
            *reinterpret_cast<const SkImageInfo *>(dst_info),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) surface;
    (void) dst_info;
    (void) src_rect;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsYUV420FromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || image == nullptr || src_rect == nullptr || callback == nullptr || !has_i_size_handle(dst_size) ||
        !has_optional_color_space_handle(dst_color_space) || !is_valid_graphite_yuv_color_space(yuv_color_space) ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixelsYUV420(
            reinterpret_cast<const SkImage *>(image),
            static_cast<SkYUVColorSpace>(yuv_color_space),
            static_sk_color_space_get_entity(dst_color_space),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_sk_i_size_get_entity(dst_size),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) image;
    (void) yuv_color_space;
    (void) dst_color_space;
    (void) src_rect;
    (void) dst_size;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsYUV420FromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || surface == nullptr || src_rect == nullptr || callback == nullptr || !has_i_size_handle(dst_size) ||
        !has_optional_color_space_handle(dst_color_space) || !is_valid_graphite_yuv_color_space(yuv_color_space) ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixelsYUV420(
            reinterpret_cast<const SkSurface *>(surface),
            static_cast<SkYUVColorSpace>(yuv_color_space),
            static_sk_color_space_get_entity(dst_color_space),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_sk_i_size_get_entity(dst_size),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) surface;
    (void) yuv_color_space;
    (void) dst_color_space;
    (void) src_rect;
    (void) dst_size;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromImage(reskia_graphite_context_t *ctx, const reskia_image_t *image, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || image == nullptr || src_rect == nullptr || callback == nullptr || !has_i_size_handle(dst_size) ||
        !has_optional_color_space_handle(dst_color_space) || !is_valid_graphite_yuv_color_space(yuv_color_space) ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixelsYUVA420(
            reinterpret_cast<const SkImage *>(image),
            static_cast<SkYUVColorSpace>(yuv_color_space),
            static_sk_color_space_get_entity(dst_color_space),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_sk_i_size_get_entity(dst_size),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) image;
    (void) yuv_color_space;
    (void) dst_color_space;
    (void) src_rect;
    (void) dst_size;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
#endif
}

void Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromSurface(reskia_graphite_context_t *ctx, const reskia_surface_t *surface, reskia_graphite_yuv_color_space_t yuv_color_space, sk_color_space_t dst_color_space, const reskia_i_rect_t *src_rect, sk_i_size_t dst_size, reskia_graphite_rescale_gamma_t rescale_gamma, reskia_graphite_rescale_mode_t rescale_mode, reskia_async_read_pixels_callback_t callback, void *callback_context) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr || surface == nullptr || src_rect == nullptr || callback == nullptr || !has_i_size_handle(dst_size) ||
        !has_optional_color_space_handle(dst_color_space) || !is_valid_graphite_yuv_color_space(yuv_color_space) ||
        !is_valid_graphite_rescale_gamma(rescale_gamma) || !is_valid_graphite_rescale_mode(rescale_mode)) {
        reskia_async_read_pixels_fail(callback, callback_context);
        return;
    }
    as_graphite_context(ctx)->asyncRescaleAndReadPixelsYUVA420(
            reinterpret_cast<const SkSurface *>(surface),
            static_cast<SkYUVColorSpace>(yuv_color_space),
            static_sk_color_space_get_entity(dst_color_space),
            *reinterpret_cast<const SkIRect *>(src_rect),
            static_sk_i_size_get_entity(dst_size),
            static_cast<SkImage::RescaleGamma>(rescale_gamma),
            static_cast<SkImage::RescaleMode>(rescale_mode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, callback_context));
#else
    (void) ctx;
    (void) surface;
    (void) yuv_color_space;
    (void) dst_color_space;
    (void) src_rect;
    (void) dst_size;
    (void) rescale_gamma;
    (void) rescale_mode;
    reskia_async_read_pixels_fail(callback, callback_context);
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

size_t Graphite_Context_currentPurgeableBytes(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr ? as_graphite_context(ctx)->currentPurgeableBytes() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

size_t Graphite_Context_maxBudgetedBytes(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr ? as_graphite_context(ctx)->maxBudgetedBytes() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

void Graphite_Context_setMaxBudgetedBytes(reskia_graphite_context_t *ctx, size_t bytes) {
#if defined(SK_GRAPHITE)
    if (ctx != nullptr) {
        as_graphite_context(ctx)->setMaxBudgetedBytes(bytes);
    }
#else
    (void) ctx;
    (void) bytes;
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

bool Graphite_Context_isDeviceLost(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr && as_graphite_context(ctx)->isDeviceLost();
#else
    (void) ctx;
    return false;
#endif
}

int Graphite_Context_maxTextureSize(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr ? as_graphite_context(ctx)->maxTextureSize() : 0;
#else
    (void) ctx;
    return 0;
#endif
}

reskia_gpu_stats_flags_t Graphite_Context_supportedGpuStats(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr
            ? static_cast<reskia_gpu_stats_flags_t>(as_graphite_context(ctx)->supportedGpuStats())
            : 0;
#else
    (void) ctx;
    return 0;
#endif
}

void Graphite_Context_syncPipelineData(reskia_graphite_context_t *ctx, size_t max_size) {
#if defined(SK_GRAPHITE)
    if (ctx == nullptr) {
        return;
    }
    as_graphite_context(ctx)->syncPipelineData(max_size);
#else
    (void) ctx;
    (void) max_size;
#endif
}

reskia_graphite_context_id_t *Graphite_Context_contextID(reskia_graphite_context_t *ctx) {
#if defined(SK_GRAPHITE)
    return ctx != nullptr
                   ? reinterpret_cast<reskia_graphite_context_id_t *>(new skgpu::graphite::Context::ContextID(as_graphite_context(ctx)->contextID()))
                   : nullptr;
#else
    (void) ctx;
    return nullptr;
#endif
}

void Graphite_ContextID_delete(reskia_graphite_context_id_t *context_id) {
#if defined(SK_GRAPHITE)
    delete reinterpret_cast<skgpu::graphite::Context::ContextID *>(context_id);
#else
    (void) context_id;
#endif
}

bool Graphite_ContextID_isValid(const reskia_graphite_context_id_t *context_id) {
#if defined(SK_GRAPHITE)
    return context_id != nullptr && as_graphite_context_id(context_id)->isValid();
#else
    (void) context_id;
    return false;
#endif
}

bool Graphite_ContextID_equals(const reskia_graphite_context_id_t *context_id, const reskia_graphite_context_id_t *other) {
#if defined(SK_GRAPHITE)
    return context_id != nullptr && other != nullptr && *as_graphite_context_id(context_id) == *as_graphite_context_id(other);
#else
    (void) context_id;
    (void) other;
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

size_t Graphite_Recorder_currentPurgeableBytes(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? as_graphite_recorder(recorder)->currentPurgeableBytes() : 0;
#else
    (void) recorder;
    return 0;
#endif
}

size_t Graphite_Recorder_maxBudgetedBytes(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? as_graphite_recorder(recorder)->maxBudgetedBytes() : 0;
#else
    (void) recorder;
    return 0;
#endif
}

void Graphite_Recorder_setMaxBudgetedBytes(reskia_graphite_recorder_t *recorder, size_t bytes) {
#if defined(SK_GRAPHITE)
    if (recorder != nullptr) {
        as_graphite_recorder(recorder)->setMaxBudgetedBytes(bytes);
    }
#else
    (void) recorder;
    (void) bytes;
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

bool Graphite_Recorder_addFinishInfo(reskia_graphite_recorder_t *recorder, reskia_graphite_finished_proc_t proc, void *user_data, reskia_graphite_release_proc_t release_proc) {
#if defined(SK_GRAPHITE)
    if (recorder == nullptr || proc == nullptr) {
        return false;
    }
    auto *callback_context = new GraphiteFinishedCallbackContext{proc, user_data, release_proc};
    skgpu::graphite::InsertFinishInfo info;
    info.fFinishedContext = callback_context;
    info.fFinishedProc = graphite_finished_callback;
    as_graphite_recorder(recorder)->addFinishInfo(info);
    return true;
#else
    (void) recorder;
    (void) proc;
    (void) user_data;
    (void) release_proc;
    return false;
#endif
}

reskia_graphite_image_provider_t *Graphite_Recorder_clientImageProvider(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? reinterpret_cast<reskia_graphite_image_provider_t *>(as_graphite_recorder(recorder)->clientImageProvider()) : nullptr;
#else
    (void) recorder;
    return nullptr;
#endif
}

int Graphite_Recorder_backend(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? to_reskia_graphite_backend_api(as_graphite_recorder(recorder)->backend()) : 0;
#else
    (void) recorder;
    return 0;
#endif
}

int Graphite_Recorder_type(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? static_cast<int>(as_graphite_recorder(recorder)->type()) : 0;
#else
    (void) recorder;
    return 0;
#endif
}

int Graphite_Recorder_maxTextureSize(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr ? as_graphite_recorder(recorder)->maxTextureSize() : 0;
#else
    (void) recorder;
    return 0;
#endif
}

reskia_canvas_t *Graphite_Recorder_makeDeferredCanvas(reskia_graphite_recorder_t *recorder, const reskia_image_info_t *image_info, const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    if (recorder == nullptr || image_info == nullptr || info == nullptr || !as_graphite_texture_info(info)->isValid()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(as_graphite_recorder(recorder)->makeDeferredCanvas(*reinterpret_cast<const SkImageInfo *>(image_info), *as_graphite_texture_info(info)));
#else
    (void) recorder;
    (void) image_info;
    (void) info;
    return nullptr;
#endif
}

reskia_graphite_recording_t *Graphite_Recorder_snap(reskia_graphite_recorder_t *recorder) {
#if defined(SK_GRAPHITE)
    if (recorder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_graphite_recording_t *>(as_graphite_recorder(recorder)->snap().release());
#else
    (void) recorder;
    return nullptr;
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

bool Graphite_Recorder_updateCompressedBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_graphite_backend_texture_t *texture, const void *data, size_t data_size) {
#if defined(SK_GRAPHITE)
    return recorder != nullptr && texture != nullptr && data != nullptr && data_size > 0 &&
           as_graphite_recorder(recorder)->updateCompressedBackendTexture(*as_graphite_backend_texture(texture), data, data_size);
#else
    (void) recorder;
    (void) texture;
    (void) data;
    (void) data_size;
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

void Graphite_Recording_delete(reskia_graphite_recording_t *recording) {
#if defined(SK_GRAPHITE)
    delete as_graphite_recording(recording);
#else
    (void) recording;
#endif
}

reskia_graphite_image_provider_t *Graphite_ImageProvider_new(
        reskia_graphite_image_provider_find_or_create_proc_t proc,
        void *user_data,
        reskia_graphite_release_proc_t release_proc) {
#if defined(SK_GRAPHITE)
    return proc != nullptr
            ? reinterpret_cast<reskia_graphite_image_provider_t *>(new ReskiaGraphiteImageProvider(proc, user_data, release_proc))
            : nullptr;
#else
    (void) proc;
    (void) user_data;
    (void) release_proc;
    return nullptr;
#endif
}

void Graphite_ImageProvider_ref(reskia_graphite_image_provider_t *provider) {
#if defined(SK_GRAPHITE)
    if (provider != nullptr) {
        as_graphite_image_provider(provider)->ref();
    }
#else
    (void) provider;
#endif
}

void Graphite_ImageProvider_unref(reskia_graphite_image_provider_t *provider) {
#if defined(SK_GRAPHITE)
    if (provider != nullptr) {
        as_graphite_image_provider(provider)->unref();
    }
#else
    (void) provider;
#endif
}

sk_image_t Graphite_ImageProvider_findOrCreate(
        reskia_graphite_image_provider_t *provider,
        reskia_graphite_recorder_t *recorder,
        const reskia_image_t *image,
        sk_image_required_properties_t properties) {
#if defined(SK_GRAPHITE)
    if (provider == nullptr || recorder == nullptr || image == nullptr ||
        static_sk_image_required_properties_get_ptr(properties) == nullptr) {
        return 0;
    }
    sk_sp<SkImage> result = as_graphite_image_provider(provider)->findOrCreate(
            as_graphite_recorder(recorder),
            reinterpret_cast<const SkImage *>(image),
            static_sk_image_required_properties_get_entity(properties));
    return result ? static_sk_image_make(std::move(result)) : 0;
#else
    (void) provider;
    (void) recorder;
    (void) image;
    (void) properties;
    return 0;
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
            skgpu::graphite::ToSampleCount(info->sample_count),
            to_graphite_mipmapped(info->mipmapped),
            static_cast<MTLPixelFormat>(info->format),
            static_cast<MTLTextureUsage>(info->usage),
            static_cast<MTLStorageMode>(info->storage_mode),
            info->framebuffer_only);
    return reinterpret_cast<reskia_graphite_texture_info_t *>(
            new skgpu::graphite::TextureInfo(skgpu::graphite::TextureInfos::MakeMetal(mtl_info)));
#else
    (void) info;
    return nullptr;
#endif
}

bool Graphite_MtlTextureInfo_new(reskia_graphite_mtl_texture_info_t *out_info) {
    if (out_info == nullptr) {
        return false;
    }
    *out_info = {};
    out_info->sample_count = 1;
    return true;
}

bool Graphite_MtlTextureInfo_newTexture(void *texture, reskia_graphite_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GRAPHITE) && defined(SK_METAL) && defined(__APPLE__)
    if (texture == nullptr || out_info == nullptr) {
        return false;
    }
    skgpu::graphite::MtlTextureInfo mtl_info(reinterpret_cast<CFTypeRef>(texture));
    out_info->sample_count = static_cast<uint8_t>(mtl_info.fSampleCount);
    out_info->mipmapped = from_graphite_mipmapped(mtl_info.fMipmapped);
    out_info->format = mtl_info.fFormat;
    out_info->usage = mtl_info.fUsage;
    out_info->storage_mode = mtl_info.fStorageMode;
    out_info->framebuffer_only = mtl_info.fFramebufferOnly;
    return true;
#else
    (void) texture;
    return false;
#endif
}

bool Graphite_MtlTextureInfo_newWithValues(uint32_t sample_count, bool mipmapped, uint32_t format, uint32_t usage, uint32_t storage_mode, bool framebuffer_only, reskia_graphite_mtl_texture_info_t *out_info) {
    if (out_info == nullptr) {
        return false;
    }
    *out_info = {
            sample_count,
            mipmapped,
            format,
            usage,
            storage_mode,
            framebuffer_only};
    return true;
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

uint32_t Graphite_TextureInfo_sampleCount(const reskia_graphite_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? static_cast<uint8_t>(as_graphite_texture_info(info)->sampleCount()) : 0;
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
    if (!skgpu::graphite::TextureInfos::GetMtlTextureInfo(*as_graphite_texture_info(info), &mtl_info)) {
        return false;
    }
    out_info->sample_count = static_cast<uint8_t>(mtl_info.fSampleCount);
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

bool Graphite_TextureInfo_canBeFulfilledBy(const reskia_graphite_texture_info_t *info, const reskia_graphite_texture_info_t *other) {
#if defined(SK_GRAPHITE)
    return info != nullptr && other != nullptr && as_graphite_texture_info(info)->canBeFulfilledBy(*as_graphite_texture_info(other));
#else
    (void) info;
    (void) other;
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

reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_backend_semaphore_t *>(new skgpu::graphite::BackendSemaphore());
#else
    return nullptr;
#endif
}

reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_newMtl(void *event, uint64_t value) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    return reinterpret_cast<reskia_graphite_backend_semaphore_t *>(
            new skgpu::graphite::BackendSemaphore(
                    skgpu::graphite::BackendSemaphores::MakeMetal(event, value)));
#else
    (void) event;
    (void) value;
    return nullptr;
#endif
}

reskia_graphite_backend_semaphore_t *Graphite_BackendSemaphore_newCopy(const reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE)
    return semaphore != nullptr
            ? reinterpret_cast<reskia_graphite_backend_semaphore_t *>(
                    new skgpu::graphite::BackendSemaphore(*as_graphite_backend_semaphore(semaphore)))
            : nullptr;
#else
    (void) semaphore;
    return nullptr;
#endif
}

void Graphite_BackendSemaphore_delete(reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE)
    delete as_graphite_backend_semaphore(semaphore);
#else
    (void) semaphore;
#endif
}

bool Graphite_BackendSemaphore_isValid(const reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE)
    return semaphore != nullptr && as_graphite_backend_semaphore(semaphore)->isValid();
#else
    (void) semaphore;
    return false;
#endif
}

int Graphite_BackendSemaphore_backend(const reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE)
    return semaphore != nullptr ? to_reskia_graphite_backend_api(as_graphite_backend_semaphore(semaphore)->backend()) : 0;
#else
    (void) semaphore;
    return 0;
#endif
}

void *Graphite_BackendSemaphore_getMtlEvent(const reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    return semaphore != nullptr
            ? const_cast<void *>(skgpu::graphite::BackendSemaphores::GetMtlEvent(*as_graphite_backend_semaphore(semaphore)))
            : nullptr;
#else
    (void) semaphore;
    return nullptr;
#endif
}

uint64_t Graphite_BackendSemaphore_getMtlValue(const reskia_graphite_backend_semaphore_t *semaphore) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    return semaphore != nullptr
            ? skgpu::graphite::BackendSemaphores::GetMtlValue(*as_graphite_backend_semaphore(semaphore))
            : 0;
#else
    (void) semaphore;
    return 0;
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
    return reinterpret_cast<reskia_graphite_backend_texture_t *>(
            new skgpu::graphite::BackendTexture(skgpu::graphite::BackendTextures::MakeMetal(
                    static_sk_i_size_get_entity(dimensions),
                    reinterpret_cast<CFTypeRef>(mtl_texture))));
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

void *Graphite_BackendTexture_getMtlTexture(const reskia_graphite_backend_texture_t *texture) {
#if defined(SK_GRAPHITE) && defined(SK_METAL)
    return texture != nullptr
            ? const_cast<void *>(skgpu::graphite::BackendTextures::GetMtlTexture(*as_graphite_backend_texture(texture)))
            : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_yuva_backend_texture_info_t *>(new skgpu::graphite::YUVABackendTextureInfo());
#else
    return nullptr;
#endif
}

reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_newWithRecorderYUVAInfoTextureInfos(const reskia_graphite_recorder_t *recorder, const reskia_yuva_info_t *info, const reskia_graphite_texture_info_t *const *texture_infos, int texture_info_count, bool mipmapped) {
#if defined(SK_GRAPHITE)
    const SkYUVAInfo *native_info = as_yuva_info(info);
    if (recorder == nullptr || native_info == nullptr || texture_infos == nullptr || texture_info_count < 0 || !native_info->isValid()) {
        return nullptr;
    }
    std::vector<skgpu::graphite::TextureInfo> native_texture_infos;
    native_texture_infos.reserve(static_cast<size_t>(texture_info_count));
    for (int i = 0; i < texture_info_count; ++i) {
        if (texture_infos[i] == nullptr) {
            return nullptr;
        }
        native_texture_infos.push_back(*as_graphite_texture_info(texture_infos[i]));
    }
    return reinterpret_cast<reskia_graphite_yuva_backend_texture_info_t *>(new skgpu::graphite::YUVABackendTextureInfo(
            as_graphite_recorder(const_cast<reskia_graphite_recorder_t *>(recorder)),
            *native_info,
            SkSpan<const skgpu::graphite::TextureInfo>(native_texture_infos.data(), native_texture_infos.size()),
            to_graphite_mipmapped(mipmapped)));
#else
    (void) recorder;
    (void) info;
    (void) texture_infos;
    (void) texture_info_count;
    (void) mipmapped;
    return nullptr;
#endif
}

reskia_graphite_yuva_backend_texture_info_t *Graphite_YUVABackendTextureInfo_newCopy(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr
            ? reinterpret_cast<reskia_graphite_yuva_backend_texture_info_t *>(new skgpu::graphite::YUVABackendTextureInfo(*as_graphite_yuva_backend_texture_info(info)))
            : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

void Graphite_YUVABackendTextureInfo_delete(reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    delete reinterpret_cast<skgpu::graphite::YUVABackendTextureInfo *>(info);
#else
    (void) info;
#endif
}

bool Graphite_YUVABackendTextureInfo_equals(const reskia_graphite_yuva_backend_texture_info_t *info, const reskia_graphite_yuva_backend_texture_info_t *other) {
#if defined(SK_GRAPHITE)
    return info != nullptr && other != nullptr && *as_graphite_yuva_backend_texture_info(info) == *as_graphite_yuva_backend_texture_info(other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

bool Graphite_YUVABackendTextureInfo_notEquals(const reskia_graphite_yuva_backend_texture_info_t *info, const reskia_graphite_yuva_backend_texture_info_t *other) {
    return info != nullptr && other != nullptr && !Graphite_YUVABackendTextureInfo_equals(info, other);
}

reskia_graphite_texture_info_t *Graphite_YUVABackendTextureInfo_planeTextureInfo(const reskia_graphite_yuva_backend_texture_info_t *info, int index) {
#if defined(SK_GRAPHITE)
    if (info == nullptr || index < 0 || index >= as_graphite_yuva_backend_texture_info(info)->numPlanes()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_graphite_texture_info_t *>(new skgpu::graphite::TextureInfo(as_graphite_yuva_backend_texture_info(info)->planeTextureInfo(index)));
#else
    (void) info;
    (void) index;
    return nullptr;
#endif
}

reskia_yuva_info_t *Graphite_YUVABackendTextureInfo_yuvaInfo(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(as_graphite_yuva_backend_texture_info(info)->yuvaInfo())) : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

int Graphite_YUVABackendTextureInfo_yuvColorSpace(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? static_cast<int>(as_graphite_yuva_backend_texture_info(info)->yuvColorSpace()) : -1;
#else
    (void) info;
    return -1;
#endif
}

bool Graphite_YUVABackendTextureInfo_mipmapped(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr && from_graphite_mipmapped(as_graphite_yuva_backend_texture_info(info)->mipmapped());
#else
    (void) info;
    return false;
#endif
}

int Graphite_YUVABackendTextureInfo_numPlanes(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr ? as_graphite_yuva_backend_texture_info(info)->numPlanes() : 0;
#else
    (void) info;
    return 0;
#endif
}

bool Graphite_YUVABackendTextureInfo_isValid(const reskia_graphite_yuva_backend_texture_info_t *info) {
#if defined(SK_GRAPHITE)
    return info != nullptr && as_graphite_yuva_backend_texture_info(info)->isValid();
#else
    (void) info;
    return false;
#endif
}

bool Graphite_YUVABackendTextureInfo_toYUVALocations(const reskia_graphite_yuva_backend_texture_info_t *info, reskia_yuva_location_t *locations) {
    clear_yuva_locations(locations);
#if defined(SK_GRAPHITE)
    if (info == nullptr || locations == nullptr || !as_graphite_yuva_backend_texture_info(info)->isValid()) {
        return false;
    }
    return copy_yuva_locations(as_graphite_yuva_backend_texture_info(info)->toYUVALocations(), locations);
#else
    (void) info;
    return false;
#endif
}

reskia_graphite_yuva_backend_textures_t *Graphite_YUVABackendTextures_new() {
#if defined(SK_GRAPHITE)
    return reinterpret_cast<reskia_graphite_yuva_backend_textures_t *>(new skgpu::graphite::YUVABackendTextures());
#else
    return nullptr;
#endif
}

reskia_graphite_yuva_backend_textures_t *Graphite_YUVABackendTextures_newWithRecorderYUVAInfoTextures(const reskia_graphite_recorder_t *recorder, const reskia_yuva_info_t *info, const reskia_graphite_backend_texture_t *const *textures, int texture_count) {
#if defined(SK_GRAPHITE)
    const SkYUVAInfo *native_info = as_yuva_info(info);
    if (recorder == nullptr || native_info == nullptr || textures == nullptr || texture_count < 0 || !native_info->isValid()) {
        return nullptr;
    }
    std::vector<skgpu::graphite::BackendTexture> native_textures;
    native_textures.reserve(static_cast<size_t>(texture_count));
    for (int i = 0; i < texture_count; ++i) {
        if (textures[i] == nullptr) {
            return nullptr;
        }
        native_textures.push_back(*as_graphite_backend_texture(textures[i]));
    }
    return reinterpret_cast<reskia_graphite_yuva_backend_textures_t *>(new skgpu::graphite::YUVABackendTextures(
            as_graphite_recorder(const_cast<reskia_graphite_recorder_t *>(recorder)),
            *native_info,
            SkSpan<const skgpu::graphite::BackendTexture>(native_textures.data(), native_textures.size())));
#else
    (void) recorder;
    (void) info;
    (void) textures;
    (void) texture_count;
    return nullptr;
#endif
}

void Graphite_YUVABackendTextures_delete(reskia_graphite_yuva_backend_textures_t *textures) {
#if defined(SK_GRAPHITE)
    delete reinterpret_cast<skgpu::graphite::YUVABackendTextures *>(textures);
#else
    (void) textures;
#endif
}

int Graphite_YUVABackendTextures_planeTextures(const reskia_graphite_yuva_backend_textures_t *textures, reskia_graphite_backend_texture_t **out_textures, int capacity) {
#if defined(SK_GRAPHITE)
    if (textures == nullptr) {
        return 0;
    }
    const skgpu::graphite::YUVABackendTextures *native = as_graphite_yuva_backend_textures(textures);
    const int num_planes = native->numPlanes();
    if (out_textures != nullptr && capacity > 0) {
        const int count = capacity < num_planes ? capacity : num_planes;
        for (int i = 0; i < count; ++i) {
            out_textures[i] = reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture(native->planeTexture(i)));
        }
    }
    return num_planes;
#else
    (void) textures;
    (void) out_textures;
    (void) capacity;
    return 0;
#endif
}

reskia_graphite_backend_texture_t *Graphite_YUVABackendTextures_planeTexture(const reskia_graphite_yuva_backend_textures_t *textures, int index) {
#if defined(SK_GRAPHITE)
    if (textures == nullptr || index < 0 || index >= as_graphite_yuva_backend_textures(textures)->numPlanes()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_graphite_backend_texture_t *>(new skgpu::graphite::BackendTexture(as_graphite_yuva_backend_textures(textures)->planeTexture(index)));
#else
    (void) textures;
    (void) index;
    return nullptr;
#endif
}

reskia_yuva_info_t *Graphite_YUVABackendTextures_yuvaInfo(const reskia_graphite_yuva_backend_textures_t *textures) {
#if defined(SK_GRAPHITE)
    return textures != nullptr ? reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(as_graphite_yuva_backend_textures(textures)->yuvaInfo())) : nullptr;
#else
    (void) textures;
    return nullptr;
#endif
}

int Graphite_YUVABackendTextures_yuvColorSpace(const reskia_graphite_yuva_backend_textures_t *textures) {
#if defined(SK_GRAPHITE)
    return textures != nullptr ? static_cast<int>(as_graphite_yuva_backend_textures(textures)->yuvColorSpace()) : -1;
#else
    (void) textures;
    return -1;
#endif
}

int Graphite_YUVABackendTextures_numPlanes(const reskia_graphite_yuva_backend_textures_t *textures) {
#if defined(SK_GRAPHITE)
    return textures != nullptr ? as_graphite_yuva_backend_textures(textures)->numPlanes() : 0;
#else
    (void) textures;
    return 0;
#endif
}

bool Graphite_YUVABackendTextures_isValid(const reskia_graphite_yuva_backend_textures_t *textures) {
#if defined(SK_GRAPHITE)
    return textures != nullptr && as_graphite_yuva_backend_textures(textures)->isValid();
#else
    (void) textures;
    return false;
#endif
}

bool Graphite_YUVABackendTextures_toYUVALocations(const reskia_graphite_yuva_backend_textures_t *textures, reskia_yuva_location_t *locations) {
    clear_yuva_locations(locations);
#if defined(SK_GRAPHITE)
    if (textures == nullptr || locations == nullptr || !as_graphite_yuva_backend_textures(textures)->isValid()) {
        return false;
    }
    return copy_yuva_locations(as_graphite_yuva_backend_textures(textures)->toYUVALocations(), locations);
#else
    (void) textures;
    return false;
#endif
}

}
