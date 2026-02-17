//
// Created by dolphilia on 2026/02/17.
//

#include "sk_surface_gpu.h"

#include "include/core/SkSurface.h"
#include "include/gpu/GpuTypes.h"

#if defined(SK_GANESH)
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#endif

#if defined(SK_GRAPHITE)
#include "include/gpu/graphite/BackendTexture.h"
#include "include/gpu/graphite/Surface.h"
#endif

#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_surface-internal.h"

namespace {

void reskia_gpu_surface_init_out(sk_surface_t *out_surface) {
    if (out_surface != nullptr) {
        *out_surface = static_sk_surface_make(nullptr);
    }
}

bool reskia_gpu_backend_enabled(reskia_gpu_backend_api_t backend_api) {
    switch (backend_api) {
        case RESKIA_GPU_BACKEND_API_METAL:
#if defined(SK_METAL)
            return true;
#else
            return false;
#endif
        case RESKIA_GPU_BACKEND_API_VULKAN:
#if defined(SK_VULKAN)
            return true;
#else
            return false;
#endif
        default:
            return false;
    }
}

} // namespace

extern "C" {

reskia_gpu_surface_status_t Reskia_GaneshSurface_MakeRenderTarget(reskia_direct_context_t *ctx, const reskia_image_info_t *image_info, bool budgeted, int sample_count, reskia_gpu_surface_origin_t origin, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface) {
    reskia_gpu_surface_init_out(out_surface);

    if (ctx == nullptr || image_info == nullptr || out_surface == nullptr) {
        return RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT;
    }

#if defined(SK_GANESH)
    auto surface = SkSurfaces::RenderTarget(
            reinterpret_cast<GrRecordingContext *>(ctx),
            budgeted ? skgpu::Budgeted::kYes : skgpu::Budgeted::kNo,
            *reinterpret_cast<const SkImageInfo *>(image_info),
            sample_count,
            static_cast<GrSurfaceOrigin>(origin),
            reinterpret_cast<const SkSurfaceProps *>(surface_props));
    if (!surface) {
        return RESKIA_GPU_SURFACE_STATUS_FAILED;
    }

    *out_surface = static_sk_surface_make(surface);
    return RESKIA_GPU_SURFACE_STATUS_OK;
#else
    (void) sample_count;
    (void) origin;
    (void) budgeted;
    (void) surface_props;
    return RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED;
#endif
}

reskia_gpu_surface_status_t Reskia_GaneshSurface_WrapBackendTexture(reskia_direct_context_t *ctx, const reskia_gpu_backend_texture_handle_t *backend_texture, reskia_gpu_surface_origin_t origin, int sample_count, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface) {
    reskia_gpu_surface_init_out(out_surface);

    if (ctx == nullptr || backend_texture == nullptr || backend_texture->backend_texture == nullptr || out_surface == nullptr) {
        return RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT;
    }
    if (!reskia_gpu_backend_enabled(backend_texture->backend_api)) {
        return RESKIA_GPU_SURFACE_STATUS_BACKEND_MISMATCH;
    }

#if defined(SK_GANESH)
    auto surface = SkSurfaces::WrapBackendTexture(
            reinterpret_cast<GrRecordingContext *>(ctx),
            *reinterpret_cast<const GrBackendTexture *>(backend_texture->backend_texture),
            static_cast<GrSurfaceOrigin>(origin),
            sample_count,
            static_cast<SkColorType>(color_type),
            static_sk_color_space_get_entity(color_space),
            reinterpret_cast<const SkSurfaceProps *>(surface_props));
    if (!surface) {
        return RESKIA_GPU_SURFACE_STATUS_FAILED;
    }

    *out_surface = static_sk_surface_make(surface);
    return RESKIA_GPU_SURFACE_STATUS_OK;
#else
    (void) origin;
    (void) sample_count;
    (void) color_type;
    (void) color_space;
    (void) surface_props;
    return RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED;
#endif
}

reskia_gpu_surface_status_t Reskia_GaneshSurface_WrapBackendRenderTarget(reskia_direct_context_t *ctx, const reskia_gpu_backend_render_target_handle_t *backend_render_target, reskia_gpu_surface_origin_t origin, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface) {
    reskia_gpu_surface_init_out(out_surface);

    if (ctx == nullptr || backend_render_target == nullptr || backend_render_target->backend_render_target == nullptr || out_surface == nullptr) {
        return RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT;
    }
    if (!reskia_gpu_backend_enabled(backend_render_target->backend_api)) {
        return RESKIA_GPU_SURFACE_STATUS_BACKEND_MISMATCH;
    }

#if defined(SK_GANESH)
    auto surface = SkSurfaces::WrapBackendRenderTarget(
            reinterpret_cast<GrRecordingContext *>(ctx),
            *reinterpret_cast<const GrBackendRenderTarget *>(backend_render_target->backend_render_target),
            static_cast<GrSurfaceOrigin>(origin),
            static_cast<SkColorType>(color_type),
            static_sk_color_space_get_entity(color_space),
            reinterpret_cast<const SkSurfaceProps *>(surface_props));
    if (!surface) {
        return RESKIA_GPU_SURFACE_STATUS_FAILED;
    }

    *out_surface = static_sk_surface_make(surface);
    return RESKIA_GPU_SURFACE_STATUS_OK;
#else
    (void) origin;
    (void) color_type;
    (void) color_space;
    (void) surface_props;
    return RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED;
#endif
}

reskia_gpu_surface_status_t Reskia_GraphiteSurface_MakeRenderTarget(reskia_graphite_recorder_t *recorder, const reskia_image_info_t *image_info, bool mipmapped, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface) {
    reskia_gpu_surface_init_out(out_surface);

    if (recorder == nullptr || image_info == nullptr || out_surface == nullptr) {
        return RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT;
    }

#if defined(SK_GRAPHITE)
    auto surface = SkSurfaces::RenderTarget(
            reinterpret_cast<skgpu::graphite::Recorder *>(recorder),
            *reinterpret_cast<const SkImageInfo *>(image_info),
            mipmapped ? skgpu::Mipmapped::kYes : skgpu::Mipmapped::kNo,
            reinterpret_cast<const SkSurfaceProps *>(surface_props));
    if (!surface) {
        return RESKIA_GPU_SURFACE_STATUS_FAILED;
    }

    *out_surface = static_sk_surface_make(surface);
    return RESKIA_GPU_SURFACE_STATUS_OK;
#else
    (void) mipmapped;
    (void) surface_props;
    return RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED;
#endif
}

reskia_gpu_surface_status_t Reskia_GraphiteSurface_WrapBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_gpu_backend_texture_handle_t *backend_texture, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface) {
    reskia_gpu_surface_init_out(out_surface);

    if (recorder == nullptr || backend_texture == nullptr || backend_texture->backend_texture == nullptr || out_surface == nullptr) {
        return RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT;
    }
    if (!reskia_gpu_backend_enabled(backend_texture->backend_api)) {
        return RESKIA_GPU_SURFACE_STATUS_BACKEND_MISMATCH;
    }

#if defined(SK_GRAPHITE)
    auto surface = SkSurfaces::WrapBackendTexture(
            reinterpret_cast<skgpu::graphite::Recorder *>(recorder),
            *reinterpret_cast<const skgpu::graphite::BackendTexture *>(backend_texture->backend_texture),
            static_cast<SkColorType>(color_type),
            static_sk_color_space_get_entity(color_space),
            reinterpret_cast<const SkSurfaceProps *>(surface_props));
    if (!surface) {
        return RESKIA_GPU_SURFACE_STATUS_FAILED;
    }

    *out_surface = static_sk_surface_make(surface);
    return RESKIA_GPU_SURFACE_STATUS_OK;
#else
    (void) color_type;
    (void) color_space;
    (void) surface_props;
    return RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED;
#endif
}

}
