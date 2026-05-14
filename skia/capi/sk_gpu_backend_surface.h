//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H
#define RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H

#include <stdbool.h>
#include <stdint.h>

#include "sk_surface_gpu.h"

typedef struct reskia_gr_backend_format_t reskia_gr_backend_format_t;
typedef struct reskia_gr_backend_texture_t reskia_gr_backend_texture_t;
typedef struct reskia_gr_backend_render_target_t reskia_gr_backend_render_target_t;

typedef int32_t reskia_gr_backend_api_t;
typedef int32_t reskia_gr_texture_type_t;
typedef int32_t reskia_gr_color_type_t;
typedef int32_t reskia_sk_texture_compression_type_t;
typedef int32_t reskia_skgpu_mipmapped_t;
typedef int32_t reskia_skgpu_protected_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_gr_backend_format_t *GrBackendFormat_new(); // owned; invalid default format
reskia_gr_backend_format_t *GrBackendFormat_newCopy(const reskia_gr_backend_format_t *format); // owned; NULL returns NULL
reskia_gr_backend_format_t *GrBackendFormat_MakeMock(reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression, bool is_stencil_format); // owned
reskia_gr_backend_format_t *GrBackendFormat_MakeMtl(int format); // owned; returns invalid format when Metal is unavailable
void GrBackendFormat_delete(reskia_gr_backend_format_t *format); // NULL input is no-op
bool GrBackendFormat_equals(const reskia_gr_backend_format_t *format, const reskia_gr_backend_format_t *other); // NULL input returns false
bool GrBackendFormat_notEquals(const reskia_gr_backend_format_t *format, const reskia_gr_backend_format_t *other); // NULL input returns false
reskia_gr_backend_api_t GrBackendFormat_backend(const reskia_gr_backend_format_t *format); // NULL input returns 0
reskia_gr_texture_type_t GrBackendFormat_textureType(const reskia_gr_backend_format_t *format); // NULL input returns 0
uint32_t GrBackendFormat_channelMask(const reskia_gr_backend_format_t *format); // NULL input returns 0
reskia_gr_color_type_t GrBackendFormat_asMockColorType(const reskia_gr_backend_format_t *format); // NULL/non-mock input returns Skia default
reskia_sk_texture_compression_type_t GrBackendFormat_asMockCompressionType(const reskia_gr_backend_format_t *format); // NULL/non-mock input returns Skia default
bool GrBackendFormat_isMockStencilFormat(const reskia_gr_backend_format_t *format); // NULL input returns false
reskia_gr_backend_format_t *GrBackendFormat_makeTexture2D(const reskia_gr_backend_format_t *format); // owned; NULL returns NULL
bool GrBackendFormat_isValid(const reskia_gr_backend_format_t *format); // NULL input returns false

reskia_gr_backend_texture_t *GrBackendTexture_new(); // owned; invalid default texture
reskia_gr_backend_texture_t *GrBackendTexture_newCopy(const reskia_gr_backend_texture_t *texture); // owned; NULL returns NULL
reskia_gr_backend_texture_t *GrBackendTexture_newMock(int width, int height, reskia_skgpu_mipmapped_t mipmapped, reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression, int id, reskia_skgpu_protected_t is_protected); // owned; invalid dimensions/id return NULL
void GrBackendTexture_delete(reskia_gr_backend_texture_t *texture); // NULL input is no-op
int GrBackendTexture_width(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
int GrBackendTexture_height(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
reskia_skgpu_mipmapped_t GrBackendTexture_mipmapped(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
bool GrBackendTexture_hasMipmaps(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_hasMipMaps(const reskia_gr_backend_texture_t *texture); // NULL input returns false
reskia_gr_backend_api_t GrBackendTexture_backend(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
reskia_gr_texture_type_t GrBackendTexture_textureType(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
reskia_gr_backend_format_t *GrBackendTexture_getBackendFormat(const reskia_gr_backend_texture_t *texture); // owned; NULL returns NULL
bool GrBackendTexture_isProtected(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_isValid(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_isSameTexture(reskia_gr_backend_texture_t *texture, reskia_gr_backend_texture_t *other); // NULL input returns false
bool GrBackendTexture_asHandle(const reskia_gr_backend_texture_t *texture, reskia_gpu_backend_texture_handle_t *out_handle); // borrowed handle; NULL/invalid returns false

reskia_gr_backend_render_target_t *GrBackendRenderTarget_new(); // owned; invalid default render target
reskia_gr_backend_render_target_t *GrBackendRenderTarget_newCopy(const reskia_gr_backend_render_target_t *render_target); // owned; NULL returns NULL
reskia_gr_backend_render_target_t *GrBackendRenderTarget_newMock(int width, int height, int sample_count, int stencil_bits, reskia_gr_color_type_t color_type, int id, reskia_skgpu_protected_t is_protected); // owned; invalid dimensions/id return NULL
void GrBackendRenderTarget_delete(reskia_gr_backend_render_target_t *render_target); // NULL input is no-op
int GrBackendRenderTarget_width(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_height(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_sampleCnt(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_stencilBits(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
reskia_gr_backend_api_t GrBackendRenderTarget_backend(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
bool GrBackendRenderTarget_isFramebufferOnly(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
reskia_gr_backend_format_t *GrBackendRenderTarget_getBackendFormat(const reskia_gr_backend_render_target_t *render_target); // owned; NULL returns NULL
bool GrBackendRenderTarget_isProtected(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
bool GrBackendRenderTarget_isValid(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
bool GrBackendRenderTarget_asHandle(const reskia_gr_backend_render_target_t *render_target, reskia_gpu_backend_render_target_handle_t *out_handle); // borrowed handle; NULL/invalid returns false

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H
