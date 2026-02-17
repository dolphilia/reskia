//
// Created by dolphilia on 2026/02/17.
//

#ifndef RAIA_SKIA_SK_SURFACE_GPU_H
#define RAIA_SKIA_SK_SURFACE_GPU_H

#include <stdbool.h>
#include <stdint.h>

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_surface.h"

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef int32_t reskia_image_info_color_type_t;

typedef int32_t reskia_gpu_backend_api_t;
typedef int32_t reskia_gpu_surface_status_t;
typedef int32_t reskia_gpu_surface_origin_t;

enum {
    RESKIA_GPU_BACKEND_API_UNKNOWN = 0,
    RESKIA_GPU_BACKEND_API_METAL = 1,
    RESKIA_GPU_BACKEND_API_VULKAN = 2,
};

enum {
    RESKIA_GPU_SURFACE_STATUS_OK = 0,
    RESKIA_GPU_SURFACE_STATUS_INVALID_ARGUMENT = 1,
    RESKIA_GPU_SURFACE_STATUS_BACKEND_MISMATCH = 2,
    RESKIA_GPU_SURFACE_STATUS_UNSUPPORTED = 3,
    RESKIA_GPU_SURFACE_STATUS_FAILED = 4,
};

typedef struct reskia_gpu_backend_texture_handle_t {
    reskia_gpu_backend_api_t backend_api;
    const void *backend_texture; // Ganesh: const GrBackendTexture*, Graphite: const skgpu::graphite::BackendTexture*
} reskia_gpu_backend_texture_handle_t;

typedef struct reskia_gpu_backend_render_target_handle_t {
    reskia_gpu_backend_api_t backend_api;
    const void *backend_render_target; // Ganesh: const GrBackendRenderTarget*
} reskia_gpu_backend_render_target_handle_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_gpu_surface_status_t Reskia_GaneshSurface_MakeRenderTarget(reskia_direct_context_t *ctx, const reskia_image_info_t *image_info, bool budgeted, int sample_count, reskia_gpu_surface_origin_t origin, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface); // (GrDirectContext *ctx, const SkImageInfo *image_info, bool budgeted, int sample_count, GrSurfaceOrigin origin, const SkSurfaceProps *surface_props, sk_surface_t *out_surface) -> status
reskia_gpu_surface_status_t Reskia_GaneshSurface_WrapBackendTexture(reskia_direct_context_t *ctx, const reskia_gpu_backend_texture_handle_t *backend_texture, reskia_gpu_surface_origin_t origin, int sample_count, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface); // (GrDirectContext *ctx, const GrBackendTexture *backend_texture, GrSurfaceOrigin origin, int sample_count, SkColorType color_type, sk_color_space_t color_space, const SkSurfaceProps *surface_props, sk_surface_t *out_surface) -> status
reskia_gpu_surface_status_t Reskia_GaneshSurface_WrapBackendRenderTarget(reskia_direct_context_t *ctx, const reskia_gpu_backend_render_target_handle_t *backend_render_target, reskia_gpu_surface_origin_t origin, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface); // (GrDirectContext *ctx, const GrBackendRenderTarget *backend_render_target, GrSurfaceOrigin origin, SkColorType color_type, sk_color_space_t color_space, const SkSurfaceProps *surface_props, sk_surface_t *out_surface) -> status

reskia_gpu_surface_status_t Reskia_GraphiteSurface_MakeRenderTarget(reskia_graphite_recorder_t *recorder, const reskia_image_info_t *image_info, bool mipmapped, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface); // (skgpu::graphite::Recorder *recorder, const SkImageInfo *image_info, bool mipmapped, const SkSurfaceProps *surface_props, sk_surface_t *out_surface) -> status
reskia_gpu_surface_status_t Reskia_GraphiteSurface_WrapBackendTexture(reskia_graphite_recorder_t *recorder, const reskia_gpu_backend_texture_handle_t *backend_texture, reskia_image_info_color_type_t color_type, sk_color_space_t color_space, const reskia_surface_props_t *surface_props, sk_surface_t *out_surface); // (skgpu::graphite::Recorder *recorder, const skgpu::graphite::BackendTexture *backend_texture, SkColorType color_type, sk_color_space_t color_space, const SkSurfaceProps *surface_props, sk_surface_t *out_surface) -> status

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SURFACE_GPU_H
