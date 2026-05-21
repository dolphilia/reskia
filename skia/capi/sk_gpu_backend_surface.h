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
#include "sk_yuva_info.h"

typedef struct reskia_gr_backend_format_t reskia_gr_backend_format_t;
typedef struct reskia_gr_backend_drawable_info_t reskia_gr_backend_drawable_info_t;
typedef struct reskia_gr_backend_texture_t reskia_gr_backend_texture_t;
typedef struct reskia_gr_backend_render_target_t reskia_gr_backend_render_target_t;
typedef struct reskia_gr_backend_semaphore_t reskia_gr_backend_semaphore_t;
typedef struct reskia_gr_driver_bug_workarounds_t reskia_gr_driver_bug_workarounds_t;
typedef struct reskia_gr_yuva_backend_texture_info_t reskia_gr_yuva_backend_texture_info_t;
typedef struct reskia_gr_yuva_backend_textures_t reskia_gr_yuva_backend_textures_t;
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

typedef struct reskia_gr_gl_texture_info_t {
    uint32_t target;
    uint32_t id;
    uint32_t format;
    reskia_skgpu_protected_t is_protected;
} reskia_gr_gl_texture_info_t;

typedef struct reskia_gr_gl_framebuffer_info_t {
    uint32_t fbo_id;
    uint32_t format;
    reskia_skgpu_protected_t is_protected;
} reskia_gr_gl_framebuffer_info_t;

typedef struct reskia_gr_mtl_texture_info_t {
    void *texture; // borrowed GrMTLHandle/id<MTLTexture>; NULL when unavailable or not Metal-backed
} reskia_gr_mtl_texture_info_t;

typedef struct reskia_gr_vk_drawable_info_t {
    uintptr_t secondary_command_buffer;
    uint32_t color_attachment_index;
    uintptr_t compatible_render_pass;
    uint32_t format;
    void *draw_bounds; // borrowed VkRect2D*; NULL allowed
} reskia_gr_vk_drawable_info_t;

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

reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_new(); // owned
reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_newWithTypes(const int32_t *workarounds, int count); // owned; invalid input returns NULL
reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_newCopy(const reskia_gr_driver_bug_workarounds_t *workarounds); // owned; NULL returns NULL
void GrDriverBugWorkarounds_delete(reskia_gr_driver_bug_workarounds_t *workarounds); // NULL input is no-op
void GrDriverBugWorkarounds_applyOverrides(reskia_gr_driver_bug_workarounds_t *workarounds, const reskia_gr_driver_bug_workarounds_t *overrides); // NULL input is no-op
bool GrDriverBugWorkarounds_isEnabled(const reskia_gr_driver_bug_workarounds_t *workarounds, int32_t type); // NULL/invalid input returns false

bool GrMockTextureInfo_new(reskia_gr_mock_texture_info_t *out_info); // out_info required
bool GrMockTextureInfo_newWithValues(reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression_type, int id, reskia_skgpu_protected_t is_protected, reskia_gr_mock_texture_info_t *out_info); // invalid id/out returns false
bool GrMockTextureInfo_equals(const reskia_gr_mock_texture_info_t *info, const reskia_gr_mock_texture_info_t *other); // NULL input returns false
reskia_gr_backend_format_t *GrMockTextureInfo_getBackendFormat(const reskia_gr_mock_texture_info_t *info); // owned; invalid input returns NULL
reskia_sk_texture_compression_type_t GrMockTextureInfo_compressionType(const reskia_gr_mock_texture_info_t *info); // NULL input returns 0
reskia_gr_color_type_t GrMockTextureInfo_colorType(const reskia_gr_mock_texture_info_t *info); // NULL/compressed input returns 0
int GrMockTextureInfo_id(const reskia_gr_mock_texture_info_t *info); // NULL input returns 0
reskia_skgpu_protected_t GrMockTextureInfo_getProtected(const reskia_gr_mock_texture_info_t *info); // NULL input returns 0
bool GrMockTextureInfo_isProtected(const reskia_gr_mock_texture_info_t *info); // NULL input returns false

bool GrMockRenderTargetInfo_new(reskia_gr_mock_render_target_info_t *out_info); // out_info required
bool GrMockRenderTargetInfo_newWithValues(reskia_gr_color_type_t color_type, int id, reskia_skgpu_protected_t is_protected, reskia_gr_mock_render_target_info_t *out_info); // invalid id/out returns false
bool GrMockRenderTargetInfo_equals(const reskia_gr_mock_render_target_info_t *info, const reskia_gr_mock_render_target_info_t *other); // NULL input returns false
reskia_gr_backend_format_t *GrMockRenderTargetInfo_getBackendFormat(const reskia_gr_mock_render_target_info_t *info); // owned; invalid input returns NULL
reskia_gr_color_type_t GrMockRenderTargetInfo_colorType(const reskia_gr_mock_render_target_info_t *info); // NULL input returns 0
reskia_skgpu_protected_t GrMockRenderTargetInfo_getProtected(const reskia_gr_mock_render_target_info_t *info); // NULL input returns 0
bool GrMockRenderTargetInfo_isProtected(const reskia_gr_mock_render_target_info_t *info); // NULL input returns false

bool GrMockOptions_new(); // true when Ganesh mock options are available

bool GrGLTextureInfo_equals(const reskia_gr_gl_texture_info_t *info, const reskia_gr_gl_texture_info_t *other); // NULL input returns false
bool GrGLTextureInfo_isProtected(const reskia_gr_gl_texture_info_t *info); // NULL input returns false
bool GrGLFramebufferInfo_equals(const reskia_gr_gl_framebuffer_info_t *info, const reskia_gr_gl_framebuffer_info_t *other); // NULL input returns false
bool GrGLFramebufferInfo_isProtected(const reskia_gr_gl_framebuffer_info_t *info); // NULL input returns false

bool GrMtlTextureInfo_new(reskia_gr_mtl_texture_info_t *out_info); // out_info required
bool GrMtlTextureInfo_equals(const reskia_gr_mtl_texture_info_t *info, const reskia_gr_mtl_texture_info_t *other); // NULL input returns false

reskia_gr_backend_drawable_info_t *GrBackendDrawableInfo_new(); // owned; invalid default drawable info
reskia_gr_backend_drawable_info_t *GrBackendDrawableInfo_newVk(const reskia_gr_vk_drawable_info_t *info); // owned; NULL/unavailable Vulkan returns NULL
void GrBackendDrawableInfo_delete(reskia_gr_backend_drawable_info_t *info); // NULL input is no-op
bool GrBackendDrawableInfo_isValid(const reskia_gr_backend_drawable_info_t *info); // NULL input returns false
reskia_gr_backend_api_t GrBackendDrawableInfo_backend(const reskia_gr_backend_drawable_info_t *info); // NULL input returns 0
bool GrBackendDrawableInfo_getVkDrawableInfo(const reskia_gr_backend_drawable_info_t *info, reskia_gr_vk_drawable_info_t *out_info); // NULL/non-Vulkan returns false

reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_new(); // owned; invalid default info
reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_newWithYUVAInfoFormats(const reskia_yuva_info_t *info, const reskia_gr_backend_format_t *const *formats, reskia_skgpu_mipmapped_t mipmapped, int texture_origin); // owned; invalid input returns NULL
reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_newCopy(const reskia_gr_yuva_backend_texture_info_t *info); // owned; NULL returns NULL
void GrYUVABackendTextureInfo_delete(reskia_gr_yuva_backend_texture_info_t *info); // NULL input is no-op
bool GrYUVABackendTextureInfo_equals(const reskia_gr_yuva_backend_texture_info_t *info, const reskia_gr_yuva_backend_texture_info_t *other); // NULL input returns false
bool GrYUVABackendTextureInfo_notEquals(const reskia_gr_yuva_backend_texture_info_t *info, const reskia_gr_yuva_backend_texture_info_t *other); // NULL input returns false
reskia_yuva_info_t *GrYUVABackendTextureInfo_yuvaInfo(const reskia_gr_yuva_backend_texture_info_t *info); // owned; NULL input returns NULL
int GrYUVABackendTextureInfo_yuvColorSpace(const reskia_gr_yuva_backend_texture_info_t *info); // NULL input returns -1
reskia_skgpu_mipmapped_t GrYUVABackendTextureInfo_mipmapped(const reskia_gr_yuva_backend_texture_info_t *info); // NULL input returns 0
int GrYUVABackendTextureInfo_textureOrigin(const reskia_gr_yuva_backend_texture_info_t *info); // NULL input returns 0
int GrYUVABackendTextureInfo_numPlanes(const reskia_gr_yuva_backend_texture_info_t *info); // NULL input returns 0
reskia_gr_backend_format_t *GrYUVABackendTextureInfo_planeFormat(const reskia_gr_yuva_backend_texture_info_t *info, int index); // owned; invalid input returns NULL
bool GrYUVABackendTextureInfo_isValid(const reskia_gr_yuva_backend_texture_info_t *info); // NULL input returns false
bool GrYUVABackendTextureInfo_toYUVALocations(const reskia_gr_yuva_backend_texture_info_t *info, reskia_yuva_location_t *locations); // locations[4]; invalid input clears locations and returns false

reskia_gr_yuva_backend_textures_t *GrYUVABackendTextures_new(); // owned; invalid default textures
reskia_gr_yuva_backend_textures_t *GrYUVABackendTextures_newWithYUVAInfoTextures(const reskia_yuva_info_t *info, const reskia_gr_backend_texture_t *const *textures, int texture_origin); // owned; invalid input returns NULL
void GrYUVABackendTextures_delete(reskia_gr_yuva_backend_textures_t *textures); // NULL input is no-op
int GrYUVABackendTextures_textures(const reskia_gr_yuva_backend_textures_t *textures, reskia_gr_backend_texture_t **out_textures, int capacity); // fills owned texture copies; returns plane count, invalid input returns 0
reskia_gr_backend_texture_t *GrYUVABackendTextures_texture(const reskia_gr_yuva_backend_textures_t *textures, int index); // owned; invalid input returns NULL
reskia_yuva_info_t *GrYUVABackendTextures_yuvaInfo(const reskia_gr_yuva_backend_textures_t *textures); // owned; NULL input returns NULL
int GrYUVABackendTextures_numPlanes(const reskia_gr_yuva_backend_textures_t *textures); // NULL input returns 0
int GrYUVABackendTextures_textureOrigin(const reskia_gr_yuva_backend_textures_t *textures); // NULL input returns 0
bool GrYUVABackendTextures_isValid(const reskia_gr_yuva_backend_textures_t *textures); // NULL input returns false
bool GrYUVABackendTextures_toYUVALocations(const reskia_gr_yuva_backend_textures_t *textures, reskia_yuva_location_t *locations); // locations[4]; invalid input clears locations and returns false

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
