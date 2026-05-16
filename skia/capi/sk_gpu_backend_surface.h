//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H
#define RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H

#include <stdbool.h>
#include <stdint.h>

#include "sk_i_size.h"
#include "sk_string.h"
#include "sk_surface_gpu.h"

typedef struct reskia_gr_backend_format_t reskia_gr_backend_format_t;
typedef struct reskia_gr_backend_texture_t reskia_gr_backend_texture_t;
typedef struct reskia_gr_backend_render_target_t reskia_gr_backend_render_target_t;
typedef struct reskia_gr_backend_semaphore_t reskia_gr_backend_semaphore_t;
typedef struct reskia_skgpu_mutable_texture_state_t reskia_skgpu_mutable_texture_state_t;

typedef int32_t reskia_gr_backend_api_t;
typedef int32_t reskia_gr_texture_type_t;
typedef int32_t reskia_gr_color_type_t;
typedef int32_t reskia_sk_texture_compression_type_t;
typedef int32_t reskia_skgpu_mipmapped_t;
typedef int32_t reskia_skgpu_protected_t;

typedef struct reskia_gr_color_format_desc_t {
    int r_bits;
    int g_bits;
    int b_bits;
    int a_bits;
    int gray_bits;
    int encoding;
} reskia_gr_color_format_desc_t;

typedef struct reskia_gr_mock_texture_info_t {
    reskia_gr_color_type_t color_type;
    reskia_sk_texture_compression_type_t compression_type;
    int id;
    reskia_skgpu_protected_t is_protected;
} reskia_gr_mock_texture_info_t;

typedef struct reskia_gr_mock_render_target_info_t {
    reskia_gr_color_type_t color_type;
    int id;
    reskia_skgpu_protected_t is_protected;
} reskia_gr_mock_render_target_info_t;

typedef struct reskia_gr_mtl_texture_info_t {
    void *texture; // borrowed GrMTLHandle/id<MTLTexture>; NULL when unavailable or not Metal-backed
} reskia_gr_mtl_texture_info_t;

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
bool GrBackendFormat_desc(const reskia_gr_backend_format_t *format, reskia_gr_color_format_desc_t *out_desc); // NULL/invalid input returns false
int GrBackendFormat_asMtlFormat(const reskia_gr_backend_format_t *format); // NULL/non-Metal input returns 0
reskia_gr_color_type_t GrBackendFormat_asMockColorType(const reskia_gr_backend_format_t *format); // NULL/non-mock input returns Skia default
reskia_sk_texture_compression_type_t GrBackendFormat_asMockCompressionType(const reskia_gr_backend_format_t *format); // NULL/non-mock input returns Skia default
bool GrBackendFormat_isMockStencilFormat(const reskia_gr_backend_format_t *format); // NULL input returns false
reskia_gr_backend_format_t *GrBackendFormat_makeTexture2D(const reskia_gr_backend_format_t *format); // owned; NULL returns NULL
bool GrBackendFormat_isValid(const reskia_gr_backend_format_t *format); // NULL input returns false
reskia_string_t *GrBackendFormat_toStr(const reskia_gr_backend_format_t *format); // owned; NULL/unavailable returns NULL

reskia_gr_backend_texture_t *GrBackendTexture_new(); // owned; invalid default texture
reskia_gr_backend_texture_t *GrBackendTexture_newCopy(const reskia_gr_backend_texture_t *texture); // owned; NULL returns NULL
reskia_gr_backend_texture_t *GrBackendTexture_newMock(int width, int height, reskia_skgpu_mipmapped_t mipmapped, reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression, int id, reskia_skgpu_protected_t is_protected); // owned; invalid dimensions/id return NULL
void GrBackendTexture_delete(reskia_gr_backend_texture_t *texture); // NULL input is no-op
sk_i_size_t GrBackendTexture_dimensions(const reskia_gr_backend_texture_t *texture); // returns handle; NULL input returns 0
int GrBackendTexture_width(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
int GrBackendTexture_height(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
reskia_skgpu_mipmapped_t GrBackendTexture_mipmapped(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
bool GrBackendTexture_hasMipmaps(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_hasMipMaps(const reskia_gr_backend_texture_t *texture); // NULL input returns false
reskia_gr_backend_api_t GrBackendTexture_backend(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
reskia_gr_texture_type_t GrBackendTexture_textureType(const reskia_gr_backend_texture_t *texture); // NULL input returns 0
bool GrBackendTexture_getMtlTextureInfo(const reskia_gr_backend_texture_t *texture, reskia_gr_mtl_texture_info_t *out_info); // NULL/non-Metal input returns false
reskia_gr_backend_format_t *GrBackendTexture_getBackendFormat(const reskia_gr_backend_texture_t *texture); // owned; NULL returns NULL
bool GrBackendTexture_getMockTextureInfo(const reskia_gr_backend_texture_t *texture, reskia_gr_mock_texture_info_t *out_info); // NULL/non-mock input returns false
reskia_string_t *GrBackendTexture_getLabel(const reskia_gr_backend_texture_t *texture); // owned; NULL input returns NULL
void GrBackendTexture_setMutableState(reskia_gr_backend_texture_t *texture, const reskia_skgpu_mutable_texture_state_t *state); // NULL input is no-op
bool GrBackendTexture_isProtected(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_isValid(const reskia_gr_backend_texture_t *texture); // NULL input returns false
bool GrBackendTexture_isSameTexture(reskia_gr_backend_texture_t *texture, reskia_gr_backend_texture_t *other); // NULL input returns false
bool GrBackendTexture_asHandle(const reskia_gr_backend_texture_t *texture, reskia_gpu_backend_texture_handle_t *out_handle); // borrowed handle; NULL/invalid returns false

reskia_gr_backend_render_target_t *GrBackendRenderTarget_new(); // owned; invalid default render target
reskia_gr_backend_render_target_t *GrBackendRenderTarget_newCopy(const reskia_gr_backend_render_target_t *render_target); // owned; NULL returns NULL
reskia_gr_backend_render_target_t *GrBackendRenderTarget_newMock(int width, int height, int sample_count, int stencil_bits, reskia_gr_color_type_t color_type, int id, reskia_skgpu_protected_t is_protected); // owned; invalid dimensions/id return NULL
void GrBackendRenderTarget_delete(reskia_gr_backend_render_target_t *render_target); // NULL input is no-op
sk_i_size_t GrBackendRenderTarget_dimensions(const reskia_gr_backend_render_target_t *render_target); // returns handle; NULL input returns 0
int GrBackendRenderTarget_width(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_height(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_sampleCnt(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
int GrBackendRenderTarget_stencilBits(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
reskia_gr_backend_api_t GrBackendRenderTarget_backend(const reskia_gr_backend_render_target_t *render_target); // NULL input returns 0
bool GrBackendRenderTarget_isFramebufferOnly(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
bool GrBackendRenderTarget_getMtlTextureInfo(const reskia_gr_backend_render_target_t *render_target, reskia_gr_mtl_texture_info_t *out_info); // NULL/non-Metal input returns false
reskia_gr_backend_format_t *GrBackendRenderTarget_getBackendFormat(const reskia_gr_backend_render_target_t *render_target); // owned; NULL returns NULL
bool GrBackendRenderTarget_getMockRenderTargetInfo(const reskia_gr_backend_render_target_t *render_target, reskia_gr_mock_render_target_info_t *out_info); // NULL/non-mock input returns false; id is 0 because Skia exposes no accessor
void GrBackendRenderTarget_setMutableState(reskia_gr_backend_render_target_t *render_target, const reskia_skgpu_mutable_texture_state_t *state); // NULL input is no-op
bool GrBackendRenderTarget_isProtected(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
bool GrBackendRenderTarget_isValid(const reskia_gr_backend_render_target_t *render_target); // NULL input returns false
bool GrBackendRenderTarget_asHandle(const reskia_gr_backend_render_target_t *render_target, reskia_gpu_backend_render_target_handle_t *out_handle); // borrowed handle; NULL/invalid returns false

reskia_gr_backend_semaphore_t *GrBackendSemaphore_new(); // owned; uninitialized default semaphore
reskia_gr_backend_semaphore_t *GrBackendSemaphore_newCopy(const reskia_gr_backend_semaphore_t *semaphore); // owned; NULL returns NULL
void GrBackendSemaphore_delete(reskia_gr_backend_semaphore_t *semaphore); // NULL input is no-op
void GrBackendSemaphore_initVulkan(reskia_gr_backend_semaphore_t *semaphore, uintptr_t vk_semaphore); // NULL input or unavailable Vulkan is no-op
uintptr_t GrBackendSemaphore_vkSemaphore(const reskia_gr_backend_semaphore_t *semaphore); // NULL/non-Vulkan input returns 0
void GrBackendSemaphore_initMetal(reskia_gr_backend_semaphore_t *semaphore, void *event, uint64_t value); // NULL input or unavailable Metal is no-op
void *GrBackendSemaphore_mtlSemaphore(const reskia_gr_backend_semaphore_t *semaphore); // NULL/non-Metal input returns NULL
uint64_t GrBackendSemaphore_mtlValue(const reskia_gr_backend_semaphore_t *semaphore); // NULL/non-Metal input returns 0
bool GrBackendSemaphore_isInitialized(const reskia_gr_backend_semaphore_t *semaphore); // NULL input returns false
reskia_gr_backend_api_t GrBackendSemaphore_backend(const reskia_gr_backend_semaphore_t *semaphore); // NULL input returns 0

reskia_skgpu_mutable_texture_state_t *MutableTextureState_new(); // owned; invalid default state
reskia_skgpu_mutable_texture_state_t *MutableTextureState_newVulkan(int vk_image_layout, uint32_t queue_family_index); // owned; returns invalid default state when Vulkan is unavailable
reskia_skgpu_mutable_texture_state_t *MutableTextureState_newCopy(const reskia_skgpu_mutable_texture_state_t *state); // owned; NULL returns NULL
void MutableTextureState_delete(reskia_skgpu_mutable_texture_state_t *state); // NULL input is no-op
int MutableTextureState_getVkImageLayout(const reskia_skgpu_mutable_texture_state_t *state); // NULL/non-Vulkan input returns 0
uint32_t MutableTextureState_getQueueFamilyIndex(const reskia_skgpu_mutable_texture_state_t *state); // NULL/non-Vulkan input returns 0
reskia_gr_backend_api_t MutableTextureState_backend(const reskia_skgpu_mutable_texture_state_t *state); // NULL input returns 0
bool MutableTextureState_isValid(const reskia_skgpu_mutable_texture_state_t *state); // NULL input returns false

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_GPU_BACKEND_SURFACE_H
