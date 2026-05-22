#include <cstdio>

#import <Metal/Metal.h>

#include "capi/sk_gpu_backend_surface.h"
#include "capi/sk_gpu_context.h"
#include "capi/sk_graphics.h"
#include "capi/sk_i_size.h"
#include "capi/sk_image_info.h"
#include "capi/sk_string.h"
#include "capi/sk_yuva_info.h"
#include "handles/static_sk_capabilities.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_image_info.h"
#include "include/private/gpu/ganesh/GrTypesPriv.h"

namespace {

constexpr reskia_gr_color_type_t kRGBA8888GrColorType =
        static_cast<reskia_gr_color_type_t>(GrColorType::kRGBA_8888);

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[gpu-context-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

struct FinishCallbackState {
    int calls;
    int result;
    int releases;
};

struct AsyncFailState {
    int calls;
};

struct ShaderErrorState {
    int calls;
    int releases;
    const char *shader;
    const char *errors;
};

struct ImageProviderState {
    int calls;
    int releases;
};

struct ExternalTextureState {
    int generates;
    int disposes;
    int releases;
    int generator_releases;
};

void finish_callback(void *user_data, int32_t result) {
    auto *state = static_cast<FinishCallbackState *>(user_data);
    state->calls += 1;
    state->result = result;
}

void finish_release(void *user_data) {
    auto *state = static_cast<FinishCallbackState *>(user_data);
    state->releases += 1;
}

void async_fail_callback(void *context, const reskia_async_read_result_t *result) {
    auto *state = static_cast<AsyncFailState *>(context);
    state->calls += 1;
    if (result != nullptr) {
        state->calls += 1000;
    }
}

void shader_error_callback(void *user_data, const char *shader, const char *errors) {
    auto *state = static_cast<ShaderErrorState *>(user_data);
    state->calls += 1;
    state->shader = shader;
    state->errors = errors;
}

void shader_error_release(void *user_data) {
    auto *state = static_cast<ShaderErrorState *>(user_data);
    state->releases += 1;
}

sk_image_t image_provider_find_or_create(
        reskia_graphite_recorder_t *,
        const reskia_image_t *,
        sk_image_required_properties_t,
        void *user_data) {
    auto *state = static_cast<ImageProviderState *>(user_data);
    state->calls += 1;
    return 0;
}

void image_provider_release(void *user_data) {
    auto *state = static_cast<ImageProviderState *>(user_data);
    state->releases += 1;
}

void external_texture_dispose(void *user_data, const reskia_gr_backend_texture_t *texture) {
    auto *state = static_cast<ExternalTextureState *>(user_data);
    state->disposes += 1;
    if (texture == nullptr || !GrBackendTexture_isValid(texture)) {
        state->disposes += 1000;
    }
}

void external_texture_release(void *user_data) {
    auto *state = static_cast<ExternalTextureState *>(user_data);
    state->releases += 1;
}

void external_texture_generator_release(void *user_data) {
    auto *state = static_cast<ExternalTextureState *>(user_data);
    state->generator_releases += 1;
}

reskia_gr_external_texture_t *external_texture_generate(
        reskia_direct_context_t *,
        bool mipmapped,
        void *user_data) {
    auto *state = static_cast<ExternalTextureState *>(user_data);
    state->generates += 1;
    reskia_gr_backend_texture_t *backend_texture =
            GrBackendTexture_newMock(1, 1, mipmapped ? 1 : 0, kRGBA8888GrColorType, 0, 321 + state->generates, 0);
    reskia_gr_external_texture_t *external_texture =
            GrExternalTexture_new(backend_texture, external_texture_dispose, user_data, external_texture_release);
    GrBackendTexture_delete(backend_texture);
    return external_texture;
}

bool smoke_context_create_destroy() {
    reskia_gpu_backend_texture_handle_t texture_handle = {};
    reskia_gpu_backend_render_target_handle_t render_target_handle = {};
    if (!check(!GrBackendFormat_isValid(nullptr) &&
               !GrBackendTexture_isValid(nullptr) &&
               !GrBackendRenderTarget_isValid(nullptr) &&
               GrBackendFormat_toStr(nullptr) == nullptr &&
               GrBackendTexture_dimensions(nullptr) == 0 &&
               GrBackendTexture_getLabel(nullptr) == nullptr &&
               GrBackendRenderTarget_dimensions(nullptr) == 0 &&
               !GrBackendFormat_desc(nullptr, nullptr) &&
               !GrBackendTexture_getMtlTextureInfo(nullptr, nullptr) &&
               !GrBackendTexture_getMockTextureInfo(nullptr, nullptr) &&
               !GrBackendRenderTarget_getMtlTextureInfo(nullptr, nullptr) &&
               !GrBackendRenderTarget_getMockRenderTargetInfo(nullptr, nullptr) &&
               GrBackendSemaphore_newCopy(nullptr) == nullptr &&
               !GrBackendSemaphore_isInitialized(nullptr) &&
               GrBackendSemaphore_backend(nullptr) == 0 &&
               GrBackendSemaphore_vkSemaphore(nullptr) == 0 &&
               GrBackendSemaphore_mtlSemaphore(nullptr) == nullptr &&
               GrBackendSemaphore_mtlValue(nullptr) == 0 &&
               GrDriverBugWorkarounds_newWithTypes(nullptr, 0) == nullptr &&
               GrDriverBugWorkarounds_newCopy(nullptr) == nullptr &&
               !GrDriverBugWorkarounds_isEnabled(nullptr, 0) &&
               GrYUVABackendTextureInfo_newCopy(nullptr) == nullptr &&
               !GrYUVABackendTextureInfo_isValid(nullptr) &&
               GrYUVABackendTextureInfo_yuvaInfo(nullptr) == nullptr &&
               GrYUVABackendTextureInfo_yuvColorSpace(nullptr) == -1 &&
               GrYUVABackendTextureInfo_numPlanes(nullptr) == 0 &&
               GrYUVABackendTextureInfo_planeFormat(nullptr, 0) == nullptr &&
               !GrYUVABackendTextureInfo_toYUVALocations(nullptr, nullptr) &&
               GrYUVABackendTextures_textures(nullptr, nullptr, 0) == 0 &&
               GrYUVABackendTextures_texture(nullptr, 0) == nullptr &&
               GrYUVABackendTextures_yuvaInfo(nullptr) == nullptr &&
               GrYUVABackendTextures_numPlanes(nullptr) == 0 &&
               !GrYUVABackendTextures_isValid(nullptr) &&
               !GrYUVABackendTextures_toYUVALocations(nullptr, nullptr) &&
               MutableTextureState_newCopy(nullptr) == nullptr &&
               !MutableTextureState_isValid(nullptr) &&
               MutableTextureState_backend(nullptr) == 0 &&
               MutableTextureState_getVkImageLayout(nullptr) == 0 &&
               MutableTextureState_getQueueFamilyIndex(nullptr) == 0 &&
               !GrBackendTexture_asHandle(nullptr, &texture_handle) &&
               texture_handle.backend_texture == nullptr &&
               !GrBackendRenderTarget_asHandle(nullptr, &render_target_handle) &&
               render_target_handle.backend_render_target == nullptr &&
               !GrMockTextureInfo_new(nullptr) &&
               !GrMockTextureInfo_newWithValues(4, 0, 0, 0, nullptr) &&
               !GrMockTextureInfo_equals(nullptr, nullptr) &&
               GrMockTextureInfo_getBackendFormat(nullptr) == nullptr &&
               GrMockTextureInfo_compressionType(nullptr) == 0 &&
               GrMockTextureInfo_colorType(nullptr) == 0 &&
               GrMockTextureInfo_id(nullptr) == 0 &&
               GrMockTextureInfo_getProtected(nullptr) == 0 &&
               !GrMockTextureInfo_isProtected(nullptr) &&
               !GrMockRenderTargetInfo_new(nullptr) &&
               !GrMockRenderTargetInfo_newWithValues(4, 0, 0, nullptr) &&
               !GrMockRenderTargetInfo_equals(nullptr, nullptr) &&
               GrMockRenderTargetInfo_getBackendFormat(nullptr) == nullptr &&
               GrMockRenderTargetInfo_colorType(nullptr) == 0 &&
               GrMockRenderTargetInfo_getProtected(nullptr) == 0 &&
               !GrMockRenderTargetInfo_isProtected(nullptr) &&
               !GrGLTextureInfo_equals(nullptr, nullptr) &&
               !GrGLTextureInfo_isProtected(nullptr) &&
               !GrGLFramebufferInfo_equals(nullptr, nullptr) &&
               !GrGLFramebufferInfo_isProtected(nullptr) &&
               !GrGLExtensions_isInitialized(nullptr) &&
               !GrMtlTextureInfo_new(nullptr) &&
               !GrMtlTextureInfo_equals(nullptr, nullptr) &&
               GrBackendDrawableInfo_newVk(nullptr) == nullptr &&
               !GrBackendDrawableInfo_isValid(nullptr) &&
               GrBackendDrawableInfo_backend(nullptr) == 0 &&
               !GrBackendDrawableInfo_getVkDrawableInfo(nullptr, nullptr),
               "GPU backend wrappers null input")) {
        return false;
    }

#if RESKIA_TEST_GPU_GANESH
    reskia_gr_backend_format_t *mock_format = GrBackendFormat_MakeMock(kRGBA8888GrColorType, 0, false);
    if (!check(mock_format != nullptr && GrBackendFormat_isValid(mock_format), "GrBackendFormat_MakeMock")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_color_format_desc_t format_desc = {};
    if (!check(GrBackendFormat_desc(mock_format, &format_desc) &&
               format_desc.r_bits == 8 &&
               format_desc.g_bits == 8 &&
               format_desc.b_bits == 8 &&
               format_desc.a_bits == 8,
               "GrBackendFormat_desc")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_string_t *format_description = GrBackendFormat_toStr(mock_format);
    if (format_description != nullptr && !check(SkString_c_str(format_description) != nullptr, "GrBackendFormat_toStr")) {
        SkString_delete(format_description);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    SkString_delete(format_description);

    reskia_gr_mock_texture_info_t default_mock_texture_info = {};
    reskia_gr_mock_texture_info_t explicit_mock_texture_info = {};
    reskia_gr_mock_texture_info_t explicit_mock_texture_info_copy = {};
    if (!check(GrMockTextureInfo_new(&default_mock_texture_info) &&
               default_mock_texture_info.color_type == 0 &&
               default_mock_texture_info.compression_type == 0 &&
               default_mock_texture_info.id == 0 &&
               GrMockTextureInfo_newWithValues(kRGBA8888GrColorType, 0, 303, 1, &explicit_mock_texture_info) &&
               GrMockTextureInfo_newWithValues(kRGBA8888GrColorType, 0, 303, 1, &explicit_mock_texture_info_copy) &&
               GrMockTextureInfo_equals(&explicit_mock_texture_info, &explicit_mock_texture_info_copy) &&
               GrMockTextureInfo_colorType(&explicit_mock_texture_info) == kRGBA8888GrColorType &&
               GrMockTextureInfo_compressionType(&explicit_mock_texture_info) == 0 &&
               GrMockTextureInfo_id(&explicit_mock_texture_info) == 303 &&
               GrMockTextureInfo_getProtected(&explicit_mock_texture_info) == 1 &&
               GrMockTextureInfo_isProtected(&explicit_mock_texture_info),
               "GrMockTextureInfo value helpers")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_backend_format_t *mock_texture_info_format = GrMockTextureInfo_getBackendFormat(&explicit_mock_texture_info);
    if (!check(mock_texture_info_format != nullptr && GrBackendFormat_isValid(mock_texture_info_format),
               "GrMockTextureInfo_getBackendFormat")) {
        GrBackendFormat_delete(mock_texture_info_format);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    GrBackendFormat_delete(mock_texture_info_format);

    reskia_gr_mock_render_target_info_t default_mock_render_target_info = {};
    reskia_gr_mock_render_target_info_t explicit_mock_render_target_info = {};
    reskia_gr_mock_render_target_info_t explicit_mock_render_target_info_copy = {};
    if (!check(GrMockRenderTargetInfo_new(&default_mock_render_target_info) &&
               default_mock_render_target_info.color_type == 0 &&
               default_mock_render_target_info.id == 0 &&
               GrMockRenderTargetInfo_newWithValues(kRGBA8888GrColorType, 404, 1, &explicit_mock_render_target_info) &&
               GrMockRenderTargetInfo_newWithValues(kRGBA8888GrColorType, 404, 1, &explicit_mock_render_target_info_copy) &&
               GrMockRenderTargetInfo_equals(&explicit_mock_render_target_info, &explicit_mock_render_target_info_copy) &&
               GrMockRenderTargetInfo_colorType(&explicit_mock_render_target_info) == kRGBA8888GrColorType &&
               GrMockRenderTargetInfo_getProtected(&explicit_mock_render_target_info) == 1 &&
               GrMockRenderTargetInfo_isProtected(&explicit_mock_render_target_info),
               "GrMockRenderTargetInfo value helpers")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_backend_format_t *mock_render_target_info_format = GrMockRenderTargetInfo_getBackendFormat(&explicit_mock_render_target_info);
    if (!check(mock_render_target_info_format != nullptr && GrBackendFormat_isValid(mock_render_target_info_format),
               "GrMockRenderTargetInfo_getBackendFormat")) {
        GrBackendFormat_delete(mock_render_target_info_format);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    GrBackendFormat_delete(mock_render_target_info_format);

    reskia_gr_gl_texture_info_t gl_texture_info_a = {3553, 11, 32856, 1};
    reskia_gr_gl_texture_info_t gl_texture_info_b = {3553, 11, 32856, 1};
    reskia_gr_gl_framebuffer_info_t gl_framebuffer_info_a = {7, 32856, 1};
    reskia_gr_gl_framebuffer_info_t gl_framebuffer_info_b = {7, 32856, 1};
    reskia_gr_mtl_texture_info_t mtl_texture_info_a = {};
    reskia_gr_mtl_texture_info_t mtl_texture_info_b = {};
    if (!check(GrMockOptions_new() &&
               GrGLTextureInfo_equals(&gl_texture_info_a, &gl_texture_info_b) &&
               GrGLTextureInfo_isProtected(&gl_texture_info_a) &&
               GrGLFramebufferInfo_equals(&gl_framebuffer_info_a, &gl_framebuffer_info_b) &&
               GrGLFramebufferInfo_isProtected(&gl_framebuffer_info_a) &&
               GrMtlTextureInfo_new(&mtl_texture_info_a) &&
               GrMtlTextureInfo_new(&mtl_texture_info_b) &&
               GrMtlTextureInfo_equals(&mtl_texture_info_a, &mtl_texture_info_b),
               "GL/Metal/mock value helpers")) {
        GrBackendFormat_delete(mock_format);
        return false;
    }

    reskia_gr_gl_extensions_t *gl_extensions = GrGLExtensions_new();
    if (!check(gl_extensions != nullptr &&
               !GrGLExtensions_isInitialized(gl_extensions),
               "GrGLExtensions default")) {
        GrGLExtensions_delete(gl_extensions);
        GrBackendFormat_delete(mock_format);
        return false;
    }
    reskia_gr_gl_extensions_t *gl_extensions_other = GrGLExtensions_new();
    GrGLExtensions_swap(gl_extensions, gl_extensions_other);
    GrGLExtensions_reset(gl_extensions_other);
    GrGLExtensions_delete(gl_extensions_other);
    GrGLExtensions_delete(gl_extensions);

    reskia_gr_backend_drawable_info_t *drawable_info = GrBackendDrawableInfo_new();
    if (drawable_info != nullptr) {
        if (!check(!GrBackendDrawableInfo_isValid(drawable_info) &&
                   GrBackendDrawableInfo_backend(drawable_info) == 0,
                   "GrBackendDrawableInfo default")) {
            GrBackendDrawableInfo_delete(drawable_info);
            GrBackendFormat_delete(mock_format);
            return false;
        }
        reskia_gr_vk_drawable_info_t vk_drawable_info = {};
        if (!check(!GrBackendDrawableInfo_getVkDrawableInfo(drawable_info, &vk_drawable_info) &&
                   vk_drawable_info.secondary_command_buffer == 0,
                   "GrBackendDrawableInfo_getVkDrawableInfo invalid default")) {
            GrBackendDrawableInfo_delete(drawable_info);
            GrBackendFormat_delete(mock_format);
            return false;
        }
    }
    GrBackendDrawableInfo_delete(drawable_info);

    if (!check(GrBackendFormat_asMtlFormat(mock_format) == 0, "GrBackendFormat_asMtlFormat(mock)")) {
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

    reskia_gr_backend_texture_t *mock_texture = GrBackendTexture_newMock(8, 4, 1, kRGBA8888GrColorType, 0, 101, 0);
    if (!check(mock_texture != nullptr &&
               GrBackendTexture_isValid(mock_texture) &&
               GrBackendTexture_width(mock_texture) == 8 &&
               GrBackendTexture_height(mock_texture) == 4 &&
               GrBackendTexture_hasMipmaps(mock_texture),
               "GrBackendTexture_newMock")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    const sk_i_size_t texture_dimensions = GrBackendTexture_dimensions(mock_texture);
    auto *texture_size = reinterpret_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(texture_dimensions));
    if (!check(texture_size != nullptr &&
               SkISize_width(texture_size) == 8 &&
               SkISize_height(texture_size) == 4,
               "GrBackendTexture_dimensions")) {
        static_sk_i_size_delete(texture_dimensions);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    static_sk_i_size_delete(texture_dimensions);
    reskia_string_t *texture_label = GrBackendTexture_getLabel(mock_texture);
    if (!check(texture_label != nullptr && SkString_c_str(texture_label) != nullptr, "GrBackendTexture_getLabel")) {
        SkString_delete(texture_label);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    SkString_delete(texture_label);
    reskia_gr_backend_format_t *texture_format = GrBackendTexture_getBackendFormat(mock_texture);
    if (!check(texture_format != nullptr && GrBackendFormat_isValid(texture_format), "GrBackendTexture_getBackendFormat")) {
        GrBackendFormat_delete(texture_format);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    GrBackendFormat_delete(texture_format);
    reskia_gr_mtl_texture_info_t mtl_texture_info = {reinterpret_cast<void *>(0x1)};
    if (!check(!GrBackendTexture_getMtlTextureInfo(mock_texture, &mtl_texture_info) &&
               mtl_texture_info.texture == nullptr,
               "GrBackendTexture_getMtlTextureInfo(mock)")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    reskia_gr_mock_texture_info_t texture_info = {};
    if (!check(GrBackendTexture_getMockTextureInfo(mock_texture, &texture_info) &&
               texture_info.color_type == kRGBA8888GrColorType &&
               texture_info.compression_type == 0 &&
               texture_info.id == 101 &&
               texture_info.is_protected == 0,
               "GrBackendTexture_getMockTextureInfo")) {
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *mutable_state = MutableTextureState_new();
    if (!check(mutable_state != nullptr &&
               !MutableTextureState_isValid(mutable_state) &&
               MutableTextureState_backend(mutable_state) == 0,
               "MutableTextureState default")) {
        MutableTextureState_delete(mutable_state);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    GrBackendTexture_setMutableState(mock_texture, mutable_state);
    if (!check(GrBackendTexture_asHandle(mock_texture, &texture_handle) &&
               texture_handle.backend_texture != nullptr,
               "GrBackendTexture_asHandle")) {
        MutableTextureState_delete(mutable_state);
        GrBackendTexture_delete(mock_texture);
        return false;
    }
    MutableTextureState_delete(mutable_state);
    GrBackendTexture_delete(mock_texture);

    reskia_gr_backend_render_target_t *mock_render_target = GrBackendRenderTarget_newMock(16, 12, 1, 8, kRGBA8888GrColorType, 202, 0);
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
    const sk_i_size_t render_target_dimensions = GrBackendRenderTarget_dimensions(mock_render_target);
    auto *render_target_size = reinterpret_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(render_target_dimensions));
    if (!check(render_target_size != nullptr &&
               SkISize_width(render_target_size) == 16 &&
               SkISize_height(render_target_size) == 12,
               "GrBackendRenderTarget_dimensions")) {
        static_sk_i_size_delete(render_target_dimensions);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    static_sk_i_size_delete(render_target_dimensions);
    reskia_gr_backend_format_t *render_target_format = GrBackendRenderTarget_getBackendFormat(mock_render_target);
    if (!check(render_target_format != nullptr && GrBackendFormat_isValid(render_target_format), "GrBackendRenderTarget_getBackendFormat")) {
        GrBackendFormat_delete(render_target_format);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendFormat_delete(render_target_format);
    reskia_gr_mtl_texture_info_t mtl_render_target_info = {reinterpret_cast<void *>(0x1)};
    if (!check(!GrBackendRenderTarget_getMtlTextureInfo(mock_render_target, &mtl_render_target_info) &&
               mtl_render_target_info.texture == nullptr,
               "GrBackendRenderTarget_getMtlTextureInfo(mock)")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_gr_mock_render_target_info_t render_target_info = {};
    if (!check(GrBackendRenderTarget_getMockRenderTargetInfo(mock_render_target, &render_target_info) &&
               render_target_info.color_type == kRGBA8888GrColorType &&
               render_target_info.id == 0 &&
               render_target_info.is_protected == 0,
               "GrBackendRenderTarget_getMockRenderTargetInfo")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *render_target_state = MutableTextureState_newVulkan(0, 0);
    if (!check(render_target_state != nullptr, "MutableTextureState_newVulkan")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    reskia_skgpu_mutable_texture_state_t *render_target_state_copy = MutableTextureState_newCopy(render_target_state);
    if (!check(render_target_state_copy != nullptr &&
               MutableTextureState_isValid(render_target_state_copy) == MutableTextureState_isValid(render_target_state),
               "MutableTextureState copy")) {
        MutableTextureState_delete(render_target_state_copy);
        MutableTextureState_delete(render_target_state);
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendRenderTarget_setMutableState(mock_render_target, render_target_state_copy);
    MutableTextureState_delete(render_target_state_copy);
    MutableTextureState_delete(render_target_state);
    if (!check(GrBackendRenderTarget_asHandle(mock_render_target, &render_target_handle) &&
               render_target_handle.backend_render_target != nullptr,
               "GrBackendRenderTarget_asHandle")) {
        GrBackendRenderTarget_delete(mock_render_target);
        return false;
    }
    GrBackendRenderTarget_delete(mock_render_target);

    reskia_gr_backend_semaphore_t *semaphore = GrBackendSemaphore_new();
    if (!check(semaphore != nullptr &&
               !GrBackendSemaphore_isInitialized(semaphore),
               "GrBackendSemaphore default")) {
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    GrBackendSemaphore_initMetal(semaphore, nullptr, 77);
    if (!check(GrBackendSemaphore_isInitialized(semaphore) &&
               GrBackendSemaphore_mtlSemaphore(semaphore) == nullptr &&
               GrBackendSemaphore_mtlValue(semaphore) == 77,
               "GrBackendSemaphore Metal init/query")) {
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    reskia_gr_backend_semaphore_t *semaphore_copy = GrBackendSemaphore_newCopy(semaphore);
    if (!check(semaphore_copy != nullptr &&
               GrBackendSemaphore_isInitialized(semaphore_copy) &&
               GrBackendSemaphore_mtlValue(semaphore_copy) == 77,
               "GrBackendSemaphore copy")) {
        GrBackendSemaphore_delete(semaphore_copy);
        GrBackendSemaphore_delete(semaphore);
        return false;
    }
    GrBackendSemaphore_delete(semaphore_copy);
    GrBackendSemaphore_delete(semaphore);

    reskia_gr_driver_bug_workarounds_t *default_workarounds = GrDriverBugWorkarounds_new();
    const int32_t workaround_type = 0;
    reskia_gr_driver_bug_workarounds_t *enabled_workarounds =
            GrDriverBugWorkarounds_newWithTypes(&workaround_type, 1);
    if (!check(default_workarounds != nullptr &&
               enabled_workarounds != nullptr &&
               !GrDriverBugWorkarounds_isEnabled(default_workarounds, workaround_type) &&
               GrDriverBugWorkarounds_isEnabled(enabled_workarounds, workaround_type),
               "GrDriverBugWorkarounds constructors/query")) {
        GrDriverBugWorkarounds_delete(enabled_workarounds);
        GrDriverBugWorkarounds_delete(default_workarounds);
        return false;
    }
    reskia_gr_driver_bug_workarounds_t *enabled_workarounds_copy =
            GrDriverBugWorkarounds_newCopy(enabled_workarounds);
    GrDriverBugWorkarounds_applyOverrides(default_workarounds, enabled_workarounds_copy);
    if (!check(enabled_workarounds_copy != nullptr &&
               GrDriverBugWorkarounds_isEnabled(default_workarounds, workaround_type) &&
               GrDriverBugWorkarounds_isEnabled(enabled_workarounds_copy, workaround_type),
               "GrDriverBugWorkarounds copy/apply")) {
        GrDriverBugWorkarounds_delete(enabled_workarounds_copy);
        GrDriverBugWorkarounds_delete(enabled_workarounds);
        GrDriverBugWorkarounds_delete(default_workarounds);
        return false;
    }
    GrDriverBugWorkarounds_delete(enabled_workarounds_copy);
    GrDriverBugWorkarounds_delete(enabled_workarounds);
    GrDriverBugWorkarounds_delete(default_workarounds);

    reskia_gr_yuva_backend_texture_info_t *default_yuva_texture_info = GrYUVABackendTextureInfo_new();
    if (!check(default_yuva_texture_info != nullptr &&
               !GrYUVABackendTextureInfo_isValid(default_yuva_texture_info) &&
               GrYUVABackendTextureInfo_numPlanes(default_yuva_texture_info) == 0,
               "GrYUVABackendTextureInfo default")) {
        GrYUVABackendTextureInfo_delete(default_yuva_texture_info);
        return false;
    }
    reskia_gr_yuva_backend_texture_info_t *default_yuva_texture_info_copy =
            GrYUVABackendTextureInfo_newCopy(default_yuva_texture_info);
    if (!check(default_yuva_texture_info_copy != nullptr &&
               GrYUVABackendTextureInfo_equals(default_yuva_texture_info, default_yuva_texture_info_copy) &&
               !GrYUVABackendTextureInfo_notEquals(default_yuva_texture_info, default_yuva_texture_info_copy),
               "GrYUVABackendTextureInfo copy")) {
        GrYUVABackendTextureInfo_delete(default_yuva_texture_info_copy);
        GrYUVABackendTextureInfo_delete(default_yuva_texture_info);
        return false;
    }
    GrYUVABackendTextureInfo_delete(default_yuva_texture_info_copy);
    GrYUVABackendTextureInfo_delete(default_yuva_texture_info);

    reskia_gr_yuva_backend_textures_t *default_yuva_textures = GrYUVABackendTextures_new();
    if (!check(default_yuva_textures != nullptr &&
               !GrYUVABackendTextures_isValid(default_yuva_textures) &&
               GrYUVABackendTextures_numPlanes(default_yuva_textures) == 0 &&
               GrYUVABackendTextures_texture(default_yuva_textures, 0) == nullptr,
               "GrYUVABackendTextures default")) {
        GrYUVABackendTextures_delete(default_yuva_textures);
        return false;
    }
    GrYUVABackendTextures_delete(default_yuva_textures);

    const sk_i_size_t yuva_size = SkISize_Make(4, 2);
    reskia_yuva_info_t *yuva_info = SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(
            yuva_size,
            1,
            1,
            0,
            1,
            0,
            0);
    if (!check(yuva_info != nullptr && SkYUVAInfo_isValid(yuva_info), "SkYUVAInfo for backend texture wrappers")) {
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    reskia_gr_backend_format_t *plane_formats[4] = {
            GrBackendFormat_MakeMock(1, 0, false),
            GrBackendFormat_MakeMock(1, 0, false),
            GrBackendFormat_MakeMock(1, 0, false),
            nullptr,
    };
    reskia_gr_yuva_backend_texture_info_t *yuva_texture_info =
            GrYUVABackendTextureInfo_newWithYUVAInfoFormats(yuva_info, plane_formats, 0, 0);
    if (!check(yuva_texture_info != nullptr &&
               GrYUVABackendTextureInfo_isValid(yuva_texture_info) &&
               GrYUVABackendTextureInfo_numPlanes(yuva_texture_info) == 3 &&
               GrYUVABackendTextureInfo_yuvColorSpace(yuva_texture_info) == 0 &&
               GrYUVABackendTextureInfo_textureOrigin(yuva_texture_info) == 0,
               "GrYUVABackendTextureInfo valid")) {
        GrYUVABackendTextureInfo_delete(yuva_texture_info);
        for (auto *format : plane_formats) {
            GrBackendFormat_delete(format);
        }
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    reskia_gr_backend_format_t *plane_format_copy = GrYUVABackendTextureInfo_planeFormat(yuva_texture_info, 0);
    reskia_yuva_info_t *yuva_info_copy = GrYUVABackendTextureInfo_yuvaInfo(yuva_texture_info);
    if (!check(plane_format_copy != nullptr &&
               GrBackendFormat_isValid(plane_format_copy) &&
               yuva_info_copy != nullptr &&
               SkYUVAInfo_numPlanes(yuva_info_copy) == 3,
               "GrYUVABackendTextureInfo owned queries")) {
        GrBackendFormat_delete(plane_format_copy);
        SkYUVAInfo_delete(yuva_info_copy);
        GrYUVABackendTextureInfo_delete(yuva_texture_info);
        for (auto *format : plane_formats) {
            GrBackendFormat_delete(format);
        }
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    GrBackendFormat_delete(plane_format_copy);
    SkYUVAInfo_delete(yuva_info_copy);
    reskia_yuva_location_t yuva_locations[4] = {};
    if (!check(GrYUVABackendTextureInfo_toYUVALocations(yuva_texture_info, yuva_locations),
               "GrYUVABackendTextureInfo locations")) {
        GrYUVABackendTextureInfo_delete(yuva_texture_info);
        for (auto *format : plane_formats) {
            GrBackendFormat_delete(format);
        }
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    GrYUVABackendTextureInfo_delete(yuva_texture_info);
    for (auto *format : plane_formats) {
        GrBackendFormat_delete(format);
    }

    reskia_gr_backend_texture_t *plane_textures[4] = {
            GrBackendTexture_newMock(4, 2, 0, 1, 0, 301, 0),
            GrBackendTexture_newMock(4, 2, 0, 1, 0, 302, 0),
            GrBackendTexture_newMock(4, 2, 0, 1, 0, 303, 0),
            nullptr,
    };
    reskia_gr_yuva_backend_textures_t *yuva_textures =
            GrYUVABackendTextures_newWithYUVAInfoTextures(yuva_info, plane_textures, 0);
    if (!check(yuva_textures != nullptr &&
               GrYUVABackendTextures_isValid(yuva_textures) &&
               GrYUVABackendTextures_numPlanes(yuva_textures) == 3 &&
               GrYUVABackendTextures_textureOrigin(yuva_textures) == 0,
               "GrYUVABackendTextures valid")) {
        GrYUVABackendTextures_delete(yuva_textures);
        for (auto *texture : plane_textures) {
            GrBackendTexture_delete(texture);
        }
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    reskia_gr_backend_texture_t *plane_texture_copy = GrYUVABackendTextures_texture(yuva_textures, 0);
    reskia_gr_backend_texture_t *plane_texture_copies[3] = {};
    reskia_yuva_info_t *textures_yuva_info_copy = GrYUVABackendTextures_yuvaInfo(yuva_textures);
    if (!check(plane_texture_copy != nullptr &&
               GrBackendTexture_isValid(plane_texture_copy) &&
               GrYUVABackendTextures_textures(yuva_textures, plane_texture_copies, 3) == 3 &&
               plane_texture_copies[0] != nullptr &&
               plane_texture_copies[1] != nullptr &&
               plane_texture_copies[2] != nullptr &&
               GrBackendTexture_isValid(plane_texture_copies[0]) &&
               textures_yuva_info_copy != nullptr &&
               SkYUVAInfo_numPlanes(textures_yuva_info_copy) == 3 &&
               GrYUVABackendTextures_toYUVALocations(yuva_textures, yuva_locations),
               "GrYUVABackendTextures owned queries")) {
        for (auto *texture : plane_texture_copies) {
            GrBackendTexture_delete(texture);
        }
        GrBackendTexture_delete(plane_texture_copy);
        SkYUVAInfo_delete(textures_yuva_info_copy);
        GrYUVABackendTextures_delete(yuva_textures);
        for (auto *texture : plane_textures) {
            GrBackendTexture_delete(texture);
        }
        SkYUVAInfo_delete(yuva_info);
        static_sk_i_size_delete(yuva_size);
        return false;
    }
    for (auto *texture : plane_texture_copies) {
        GrBackendTexture_delete(texture);
    }
    GrBackendTexture_delete(plane_texture_copy);
    SkYUVAInfo_delete(textures_yuva_info_copy);
    GrYUVABackendTextures_delete(yuva_textures);
    for (auto *texture : plane_textures) {
        GrBackendTexture_delete(texture);
    }
    SkYUVAInfo_delete(yuva_info);
    static_sk_i_size_delete(yuva_size);
#endif

    int null_resource_count = 1;
    size_t null_resource_bytes = 1;
#if RESKIA_TEST_GPU_GANESH
    reskia_gr_surface_characterization_t *default_characterization = GrSurfaceCharacterization_new();
    if (!check(default_characterization != nullptr &&
               !GrSurfaceCharacterization_isValid(default_characterization) &&
               GrSurfaceCharacterization_width(default_characterization) == 0 &&
               GrSurfaceCharacterization_height(default_characterization) == 0 &&
               GrSurfaceCharacterization_newCopy(nullptr) == nullptr,
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
    GrDirectContext_resetGLTextureBindings(nullptr);
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
    AsyncFailState graphite_async_fail_state = {};
    Graphite_Context_asyncRescaleAndReadPixelsFromImage(nullptr, nullptr, nullptr, nullptr, 0, 0, async_fail_callback, &graphite_async_fail_state);
    Graphite_Context_asyncRescaleAndReadPixelsFromSurface(nullptr, nullptr, nullptr, nullptr, 0, 0, async_fail_callback, &graphite_async_fail_state);
    Graphite_Context_asyncRescaleAndReadPixelsYUV420FromImage(nullptr, nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &graphite_async_fail_state);
    Graphite_Context_asyncRescaleAndReadPixelsYUV420FromSurface(nullptr, nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &graphite_async_fail_state);
    Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromImage(nullptr, nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &graphite_async_fail_state);
    Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromSurface(nullptr, nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &graphite_async_fail_state);
    if (!check(graphite_async_fail_state.calls == 6, "Graphite_Context async invalid fail callbacks")) {
        return false;
    }
    if (GrDirectContext_MakeMetal(nullptr, nullptr) != nullptr) {
        return false;
    }
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
               !GrDirectContext_wait(nullptr, 0, nullptr, false) &&
               GrDirectContext_dump(nullptr) == nullptr &&
               !GrDirectContext_supportsDistanceFieldText(nullptr) &&
               GrDirectContext_createBackendTexture(nullptr, 1, 1, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColorType(nullptr, 1, 1, kRGBA8888GrColorType, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColor(nullptr, 1, 1, nullptr, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureWithColorTypeColor(nullptr, 1, 1, kRGBA8888GrColorType, nullptr, false, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmaps(nullptr, nullptr, 1, 0, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmap(nullptr, nullptr, 0, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmapsTopLeft(nullptr, nullptr, 1, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createBackendTextureFromPixmapTopLeft(nullptr, nullptr, false, false, nullptr, 0) == nullptr &&
               GrDirectContext_createCompressedBackendTexture(nullptr, 1, 1, nullptr, nullptr, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithCompressionType(nullptr, 1, 1, 0, nullptr, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithData(nullptr, 1, 1, nullptr, nullptr, 0, false, false) == nullptr &&
               GrDirectContext_createCompressedBackendTextureWithCompressionTypeData(nullptr, 1, 1, 0, nullptr, 0, false, false) == nullptr &&
               !GrDirectContext_updateBackendTexture(nullptr, nullptr, nullptr) &&
               !GrDirectContext_updateBackendTextureWithColorType(nullptr, nullptr, 0, nullptr) &&
               !GrDirectContext_updateBackendTextureFromPixmaps(nullptr, nullptr, nullptr, 0, 0) &&
               !GrDirectContext_updateBackendTextureFromPixmap(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_updateBackendTextureFromPixmapsTopLeft(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_updateCompressedBackendTexture(nullptr, nullptr, nullptr) &&
               !GrDirectContext_updateCompressedBackendTextureWithData(nullptr, nullptr, nullptr, 0) &&
               !GrDirectContext_setBackendTextureState(nullptr, nullptr, nullptr, nullptr) &&
               !GrDirectContext_setBackendRenderTargetState(nullptr, nullptr, nullptr, nullptr) &&
               !GrDirectContext_precompileShader(nullptr, nullptr, nullptr) &&
               GrRecordingContext_skCapabilities(nullptr) == 0 &&
               Graphite_Context_backend(nullptr) == 0 &&
               Graphite_Context_makeRecorder(nullptr) == nullptr &&
               Graphite_Context_makeRecorderWithOptions(nullptr, nullptr) == nullptr &&
               !Graphite_Context_submit(nullptr, false) &&
               !Graphite_Context_insertRecording(nullptr, nullptr) &&
               Graphite_Context_currentBudgetedBytes(nullptr) == 0 &&
               !Graphite_Context_supportsProtectedContent(nullptr) &&
               !Graphite_Context_isDeviceLost(nullptr) &&
               Graphite_Context_contextID(nullptr) == nullptr &&
               !Graphite_ContextID_isValid(nullptr) &&
               !Graphite_ContextID_equals(nullptr, nullptr) &&
               GrContextOptions_newCopy(nullptr) == nullptr &&
               !GrContextOptions_suppressPrints(nullptr) &&
               ShaderErrorHandler_new(nullptr, nullptr, nullptr) == nullptr &&
               GrExternalTexture_new(nullptr, nullptr, nullptr, nullptr) == nullptr &&
               GrExternalTexture_getBackendTexture(nullptr) == nullptr &&
               GrExternalTextureGenerator_new(nullptr, nullptr, nullptr, nullptr) == nullptr &&
               GrExternalTextureGenerator_generateExternalTexture(nullptr, nullptr, false) == nullptr &&
               SkImages_DeferredFromTextureGenerator(nullptr) == 0 &&
               Graphite_ContextOptions_gpuBudgetInBytes(nullptr) == 0 &&
               Graphite_RecorderOptions_newCopy(nullptr) == nullptr &&
               Graphite_RecorderOptions_gpuBudgetInBytes(nullptr) == 0 &&
               Graphite_ImageProvider_new(nullptr, nullptr, nullptr) == nullptr &&
               Graphite_ImageProvider_findOrCreate(nullptr, nullptr, nullptr, 0) == 0 &&
               !Graphite_Recorder_addFinishInfo(nullptr, nullptr, nullptr, nullptr) &&
               Graphite_Recorder_clientImageProvider(nullptr) == nullptr &&
               Graphite_Recorder_makeDeferredCanvas(nullptr, nullptr, nullptr) == nullptr &&
               Graphite_Recorder_snap(nullptr) == nullptr &&
               Graphite_Recorder_currentBudgetedBytes(nullptr) == 0 &&
               Graphite_Recorder_createBackendTexture(nullptr, 0, nullptr) == nullptr &&
               !Graphite_Recorder_updateBackendTexture(nullptr, nullptr, nullptr, 0) &&
               Graphite_TextureInfo_newCopy(nullptr) == nullptr &&
               !Graphite_TextureInfo_equals(nullptr, nullptr) &&
               !Graphite_TextureInfo_isValid(nullptr) &&
               Graphite_TextureInfo_backend(nullptr) == 0 &&
               Graphite_TextureInfo_numSamples(nullptr) == 0 &&
               !Graphite_TextureInfo_mipmapped(nullptr) &&
               !Graphite_TextureInfo_isProtected(nullptr) &&
               !Graphite_TextureInfo_getMtlTextureInfo(nullptr, nullptr) &&
               !Graphite_TextureInfo_isCompatible(nullptr, nullptr) &&
               Graphite_TextureInfo_toString(nullptr) == nullptr &&
               !Graphite_MtlTextureInfo_new(nullptr) &&
               !Graphite_MtlTextureInfo_newTexture(nullptr, nullptr) &&
               !Graphite_MtlTextureInfo_newWithValues(1, false, 0, 0, 0, false, nullptr) &&
               Graphite_BackendSemaphore_newCopy(nullptr) == nullptr &&
               !Graphite_BackendSemaphore_isValid(nullptr) &&
               Graphite_BackendSemaphore_backend(nullptr) == 0 &&
               Graphite_BackendSemaphore_getMtlEvent(nullptr) == nullptr &&
               Graphite_BackendSemaphore_getMtlValue(nullptr) == 0 &&
               Graphite_YUVABackendTextureInfo_newCopy(nullptr) == nullptr &&
               !Graphite_YUVABackendTextureInfo_isValid(nullptr) &&
               Graphite_YUVABackendTextureInfo_planeTextureInfo(nullptr, 0) == nullptr &&
               Graphite_YUVABackendTextureInfo_yuvaInfo(nullptr) == nullptr &&
               Graphite_YUVABackendTextureInfo_yuvColorSpace(nullptr) == -1 &&
               Graphite_YUVABackendTextureInfo_numPlanes(nullptr) == 0 &&
               !Graphite_YUVABackendTextureInfo_toYUVALocations(nullptr, nullptr) &&
               Graphite_YUVABackendTextures_planeTextures(nullptr, nullptr, 0) == 0 &&
               Graphite_YUVABackendTextures_planeTexture(nullptr, 0) == nullptr &&
               Graphite_YUVABackendTextures_yuvaInfo(nullptr) == nullptr &&
               Graphite_YUVABackendTextures_yuvColorSpace(nullptr) == -1 &&
               Graphite_YUVABackendTextures_numPlanes(nullptr) == 0 &&
               !Graphite_YUVABackendTextures_isValid(nullptr) &&
               !Graphite_YUVABackendTextures_toYUVALocations(nullptr, nullptr) &&
               Graphite_BackendTexture_newCopy(nullptr) == nullptr &&
               !Graphite_BackendTexture_equals(nullptr, nullptr) &&
               !Graphite_BackendTexture_isValid(nullptr) &&
               Graphite_BackendTexture_backend(nullptr) == 0 &&
               Graphite_BackendTexture_dimensions(nullptr) == 0 &&
               Graphite_BackendTexture_info(nullptr) == nullptr &&
               Graphite_BackendTexture_getMtlTexture(nullptr) == nullptr &&
               GrContextThreadSafeProxy_createCharacterization(nullptr, 0, nullptr, nullptr, 0, 0, nullptr, false, false, false, false, false, false) == nullptr,
               "GrDirectContext null input helpers")) {
        return false;
    }

#if RESKIA_TEST_GPU_GANESH
    reskia_direct_context_t *mock_context = GrDirectContext_MakeMock();
    if (mock_context != nullptr) {
        GrDirectContext_resetGLTextureBindings(mock_context);
        Reskia_DirectContext_Release(mock_context);
    }

    reskia_gr_context_options_t *context_options = GrContextOptions_new();
    if (!check(context_options != nullptr &&
               !GrContextOptions_suppressPrints(context_options),
               "GrContextOptions default")) {
        GrContextOptions_delete(context_options);
        return false;
    }
    GrContextOptions_setSuppressPrints(context_options, true);
    reskia_gr_context_options_t *context_options_copy = GrContextOptions_newCopy(context_options);
    if (!check(context_options_copy != nullptr &&
               GrContextOptions_suppressPrints(context_options_copy),
               "GrContextOptions copy")) {
        GrContextOptions_delete(context_options_copy);
        GrContextOptions_delete(context_options);
        return false;
    }
    ShaderErrorState shader_error_state = {};
    reskia_shader_error_handler_t *shader_error_handler =
            ShaderErrorHandler_new(shader_error_callback, &shader_error_state, shader_error_release);
    if (!check(shader_error_handler != nullptr, "ShaderErrorHandler_new")) {
        GrContextOptions_delete(context_options_copy);
        GrContextOptions_delete(context_options);
        return false;
    }
    GrContextOptions_setShaderErrorHandler(context_options, shader_error_handler);
    ShaderErrorHandler_compileError(shader_error_handler, "shader", "errors");
    if (!check(shader_error_state.calls == 1 &&
               shader_error_state.shader != nullptr &&
               shader_error_state.errors != nullptr,
               "ShaderErrorHandler_compileError")) {
        ShaderErrorHandler_delete(shader_error_handler);
        GrContextOptions_delete(context_options_copy);
        GrContextOptions_delete(context_options);
        return false;
    }
    GrContextOptions_setShaderErrorHandler(context_options, nullptr);
    ShaderErrorHandler_delete(shader_error_handler);
    if (!check(shader_error_state.releases == 1, "ShaderErrorHandler release")) {
        GrContextOptions_delete(context_options_copy);
        GrContextOptions_delete(context_options);
        return false;
    }
    GrContextOptions_delete(context_options_copy);
    GrContextOptions_delete(context_options);

    ExternalTextureState external_state = {};
    reskia_gr_backend_texture_t *backend_texture =
            GrBackendTexture_newMock(1, 1, 0, kRGBA8888GrColorType, 0, 123, 0);
    reskia_gr_external_texture_t *external_texture =
            GrExternalTexture_new(backend_texture, external_texture_dispose, &external_state, external_texture_release);
    reskia_gr_backend_texture_t *external_backend_copy =
            GrExternalTexture_getBackendTexture(external_texture);
    if (!check(backend_texture != nullptr &&
               external_texture != nullptr &&
               external_backend_copy != nullptr &&
               GrBackendTexture_isValid(external_backend_copy),
               "GrExternalTexture_new/getBackendTexture")) {
        GrBackendTexture_delete(external_backend_copy);
        GrExternalTexture_delete(external_texture);
        GrBackendTexture_delete(backend_texture);
        return false;
    }
    GrBackendTexture_delete(external_backend_copy);
    GrExternalTexture_dispose(external_texture);
    GrExternalTexture_dispose(external_texture);
    GrExternalTexture_delete(external_texture);
    GrBackendTexture_delete(backend_texture);
    if (!check(external_state.disposes == 1 && external_state.releases == 1,
               "GrExternalTexture dispose/release")) {
        return false;
    }

    const sk_image_info_t generator_info_handle = SkImageInfo_MakeN32Premul(1, 1);
    auto *generator_info = reinterpret_cast<reskia_image_info_t *>(
            static_sk_image_info_get_ptr(generator_info_handle));
    reskia_gr_external_texture_generator_t *generator =
            GrExternalTextureGenerator_new(generator_info, external_texture_generate, &external_state, external_texture_generator_release);
    reskia_gr_external_texture_t *generated_texture =
            GrExternalTextureGenerator_generateExternalTexture(generator, nullptr, false);
    if (!check(generator != nullptr &&
               generated_texture != nullptr &&
               external_state.generates == 1,
               "GrExternalTextureGenerator_generateExternalTexture")) {
        GrExternalTexture_delete(generated_texture);
        GrExternalTextureGenerator_delete(generator);
        static_sk_image_info_delete(generator_info_handle);
        return false;
    }
    GrExternalTexture_delete(generated_texture);
    sk_image_t deferred_image = SkImages_DeferredFromTextureGenerator(generator);
    static_sk_image_info_delete(generator_info_handle);
    if (!check(deferred_image != 0, "SkImages_DeferredFromTextureGenerator")) {
        return false;
    }
    static_sk_image_delete(deferred_image);
    if (!check(external_state.generator_releases == 1, "GrExternalTextureGenerator release")) {
        return false;
    }
#endif

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
        const_sk_capabilities_t capabilities = GrRecordingContext_skCapabilities(direct_context);
        if (!check(capabilities != 0 && static_const_sk_capabilities_get_ptr(capabilities) != nullptr,
                   "GrRecordingContext_skCapabilities")) {
            static_const_sk_capabilities_delete(capabilities);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        static_const_sk_capabilities_delete(capabilities);
        reskia_gr_context_thread_safe_proxy_t *proxy = GrDirectContext_threadSafeProxy(direct_context);
        if (!check(proxy != nullptr && GrContextThreadSafeProxy_isValid(proxy), "GrDirectContext_threadSafeProxy(valid)")) {
            GrContextThreadSafeProxy_release(proxy);
            Reskia_DirectContext_Release(direct_context);
            return false;
        }
        reskia_gr_backend_format_t *proxy_format = GrContextThreadSafeProxy_defaultBackendFormat(proxy, kRGBA8888GrColorType, true);
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
        if (!check(Graphite_Context_backend(graphite_context) == RESKIA_GPU_BACKEND_API_METAL,
                   "Graphite_Context_backend")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        if (!check(!Graphite_Context_isDeviceLost(graphite_context),
                   "Graphite_Context_isDeviceLost")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        reskia_graphite_context_id_t *graphite_context_id = Graphite_Context_contextID(graphite_context);
        if (!check(graphite_context_id != nullptr &&
                   Graphite_ContextID_isValid(graphite_context_id) &&
                   Graphite_ContextID_equals(graphite_context_id, graphite_context_id),
                   "Graphite_Context_contextID")) {
            Graphite_ContextID_delete(graphite_context_id);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_ContextID_delete(graphite_context_id);
        Graphite_Context_checkAsyncWorkCompletion(graphite_context);
        Graphite_Context_performDeferredCleanup(graphite_context, 0);
        Graphite_Context_freeGpuResources(graphite_context);

        reskia_graphite_context_options_t* context_options = Graphite_ContextOptions_new();
        if (!check(context_options != nullptr &&
                   Graphite_ContextOptions_gpuBudgetInBytes(context_options) > 0,
                   "Graphite_ContextOptions default")) {
            Graphite_ContextOptions_delete(context_options);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_ContextOptions_setGpuBudgetInBytes(context_options, 4096);
        if (!check(Graphite_ContextOptions_gpuBudgetInBytes(context_options) == 4096,
                   "Graphite_ContextOptions budget roundtrip")) {
            Graphite_ContextOptions_delete(context_options);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_ContextOptions_delete(context_options);

        reskia_graphite_recorder_t* recorder =
                Graphite_Context_makeRecorder(graphite_context);
        if (!check(recorder != nullptr, "Graphite_Context_makeRecorder")) {
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_Recorder_performDeferredCleanup(recorder, 0);
        Graphite_Recorder_freeGpuResources(recorder);
        if (!check(Graphite_Recorder_clientImageProvider(recorder) != nullptr,
                   "Graphite_Recorder_clientImageProvider")) {
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

        reskia_graphite_recorder_t *finish_recorder = Graphite_Context_makeRecorder(graphite_context);
        FinishCallbackState finish_state = {};
        if (!check(finish_recorder != nullptr &&
                   Graphite_Recorder_addFinishInfo(finish_recorder, finish_callback, &finish_state, finish_release),
                   "Graphite_Recorder_addFinishInfo")) {
            Reskia_GraphiteRecorder_Release(finish_recorder);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Reskia_GraphiteRecorder_Release(finish_recorder);
        if (!check(finish_state.calls == 1 &&
                   finish_state.result == 0 &&
                   finish_state.releases == 1,
                   "Graphite_Recorder_addFinishInfo failure callback on recorder release")) {
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

        reskia_graphite_recorder_options_t* recorder_options = Graphite_RecorderOptions_new();
        reskia_graphite_recorder_options_t* recorder_options_copy =
                Graphite_RecorderOptions_newCopy(recorder_options);
        if (!check(recorder_options != nullptr &&
                   recorder_options_copy != nullptr &&
                   Graphite_RecorderOptions_gpuBudgetInBytes(recorder_options) > 0 &&
                   Graphite_RecorderOptions_gpuBudgetInBytes(recorder_options_copy) ==
                           Graphite_RecorderOptions_gpuBudgetInBytes(recorder_options),
                   "Graphite_RecorderOptions default/copy")) {
            Graphite_RecorderOptions_delete(recorder_options_copy);
            Graphite_RecorderOptions_delete(recorder_options);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_RecorderOptions_setGpuBudgetInBytes(recorder_options, 8192);
        if (!check(Graphite_RecorderOptions_gpuBudgetInBytes(recorder_options) == 8192,
                   "Graphite_RecorderOptions budget roundtrip")) {
            Graphite_RecorderOptions_delete(recorder_options_copy);
            Graphite_RecorderOptions_delete(recorder_options);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

        ImageProviderState image_provider_state = {};
        reskia_graphite_image_provider_t *image_provider =
                Graphite_ImageProvider_new(image_provider_find_or_create, &image_provider_state, image_provider_release);
        Graphite_RecorderOptions_setImageProvider(recorder_options, image_provider);
        reskia_graphite_recorder_t *provider_recorder =
                Graphite_Context_makeRecorderWithOptions(graphite_context, recorder_options);
        if (!check(image_provider != nullptr &&
                   provider_recorder != nullptr &&
                   Graphite_Recorder_clientImageProvider(provider_recorder) == image_provider &&
                   Graphite_ImageProvider_findOrCreate(image_provider, provider_recorder, nullptr, 0) == 0,
                   "Graphite_ImageProvider bridge")) {
            Reskia_GraphiteRecorder_Release(provider_recorder);
            Graphite_ImageProvider_unref(image_provider);
            Graphite_RecorderOptions_delete(recorder_options_copy);
            Graphite_RecorderOptions_delete(recorder_options);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Reskia_GraphiteRecorder_Release(provider_recorder);
        Graphite_RecorderOptions_setImageProvider(recorder_options, nullptr);
        Graphite_ImageProvider_unref(image_provider);
        if (!check(image_provider_state.calls == 0 && image_provider_state.releases == 1,
                   "Graphite_ImageProvider release")) {
            Graphite_RecorderOptions_delete(recorder_options_copy);
            Graphite_RecorderOptions_delete(recorder_options);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }

        Graphite_RecorderOptions_delete(recorder_options_copy);
        Graphite_RecorderOptions_delete(recorder_options);

        reskia_graphite_recording_t *recording = Graphite_Recorder_snap(recorder);
        if (!check(recording != nullptr &&
                   Graphite_Context_insertRecording(graphite_context, recording),
                   "Graphite_Recorder_snap/Context_insertRecording")) {
            Graphite_Recording_delete(recording);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_Recording_delete(recording);

        reskia_graphite_texture_info_t* default_texture_info = Graphite_TextureInfo_new();
        reskia_string_t* texture_info_string = Graphite_TextureInfo_toString(default_texture_info);
        if (!check(default_texture_info != nullptr &&
                   !Graphite_TextureInfo_isValid(default_texture_info) &&
                   Graphite_TextureInfo_backend(default_texture_info) == 0 &&
                   Graphite_TextureInfo_numSamples(default_texture_info) == 0 &&
                   !Graphite_TextureInfo_mipmapped(default_texture_info) &&
                   !Graphite_TextureInfo_isProtected(default_texture_info) &&
                   texture_info_string != nullptr,
                   "Graphite_TextureInfo default")) {
            SkString_delete(texture_info_string);
            Graphite_TextureInfo_delete(default_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        SkString_delete(texture_info_string);

        reskia_graphite_texture_info_t* copied_texture_info =
                Graphite_TextureInfo_newCopy(default_texture_info);
        if (!check(copied_texture_info != nullptr &&
                   Graphite_TextureInfo_equals(default_texture_info, copied_texture_info) &&
                   !Graphite_TextureInfo_notEquals(default_texture_info, copied_texture_info) &&
                   Graphite_TextureInfo_isCompatible(default_texture_info, copied_texture_info),
                   "Graphite_TextureInfo copy")) {
            Graphite_TextureInfo_delete(copied_texture_info);
            Graphite_TextureInfo_delete(default_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_TextureInfo_delete(copied_texture_info);
        Graphite_TextureInfo_delete(default_texture_info);

        reskia_graphite_mtl_texture_info_t default_mtl_info = {};
        reskia_graphite_mtl_texture_info_t explicit_mtl_info = {};
        if (!check(Graphite_MtlTextureInfo_new(&default_mtl_info) &&
                   default_mtl_info.sample_count == 1 &&
                   !default_mtl_info.mipmapped &&
                   Graphite_MtlTextureInfo_newWithValues(4, true, 80, 17, 2, true, &explicit_mtl_info) &&
                   explicit_mtl_info.sample_count == 4 &&
                   explicit_mtl_info.mipmapped &&
                   explicit_mtl_info.format == 80 &&
                   explicit_mtl_info.usage == 17 &&
                   explicit_mtl_info.storage_mode == 2 &&
                   explicit_mtl_info.framebuffer_only,
                   "Graphite_MtlTextureInfo values")) {
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        reskia_graphite_texture_info_t *mtl_texture_info = Graphite_TextureInfo_newMtl(&explicit_mtl_info);
        if (!check(mtl_texture_info != nullptr &&
                   Graphite_TextureInfo_isValid(mtl_texture_info) &&
                   Graphite_TextureInfo_backend(mtl_texture_info) == RESKIA_GPU_BACKEND_API_METAL,
                   "Graphite_TextureInfo_newMtl")) {
            Graphite_TextureInfo_delete(mtl_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        sk_image_info_t deferred_image_info = SkImageInfo_MakeN32Premul(4, 4);
        auto *deferred_image_info_ptr = static_cast<reskia_image_info_t *>(
                static_sk_image_info_get_ptr(deferred_image_info));
        if (!check(deferred_image_info_ptr != nullptr &&
                   Graphite_Recorder_makeDeferredCanvas(recorder, deferred_image_info_ptr, mtl_texture_info) != nullptr,
                   "Graphite_Recorder_makeDeferredCanvas")) {
            static_sk_image_info_delete(deferred_image_info);
            Graphite_TextureInfo_delete(mtl_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        static_sk_image_info_delete(deferred_image_info);
        Graphite_TextureInfo_delete(mtl_texture_info);

        reskia_graphite_backend_semaphore_t* default_semaphore = Graphite_BackendSemaphore_new();
        reskia_graphite_backend_semaphore_t* copied_semaphore =
                Graphite_BackendSemaphore_newCopy(default_semaphore);
        if (!check(default_semaphore != nullptr &&
                   copied_semaphore != nullptr &&
                   !Graphite_BackendSemaphore_isValid(default_semaphore) &&
                   Graphite_BackendSemaphore_backend(default_semaphore) == 0 &&
                   Graphite_BackendSemaphore_getMtlEvent(default_semaphore) == nullptr &&
                   Graphite_BackendSemaphore_getMtlValue(default_semaphore) == 0,
                   "Graphite_BackendSemaphore default/copy")) {
            Graphite_BackendSemaphore_delete(copied_semaphore);
            Graphite_BackendSemaphore_delete(default_semaphore);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_BackendSemaphore_delete(copied_semaphore);
        Graphite_BackendSemaphore_delete(default_semaphore);

        reskia_graphite_yuva_backend_texture_info_t* default_yuva_texture_info =
                Graphite_YUVABackendTextureInfo_new();
        reskia_graphite_yuva_backend_texture_info_t* copied_yuva_texture_info =
                Graphite_YUVABackendTextureInfo_newCopy(default_yuva_texture_info);
        if (!check(default_yuva_texture_info != nullptr &&
                   copied_yuva_texture_info != nullptr &&
                   !Graphite_YUVABackendTextureInfo_isValid(default_yuva_texture_info) &&
                   Graphite_YUVABackendTextureInfo_numPlanes(default_yuva_texture_info) == 0 &&
                   Graphite_YUVABackendTextureInfo_equals(default_yuva_texture_info, copied_yuva_texture_info) &&
                   !Graphite_YUVABackendTextureInfo_notEquals(default_yuva_texture_info, copied_yuva_texture_info),
                   "Graphite_YUVABackendTextureInfo default/copy")) {
            Graphite_YUVABackendTextureInfo_delete(copied_yuva_texture_info);
            Graphite_YUVABackendTextureInfo_delete(default_yuva_texture_info);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_YUVABackendTextureInfo_delete(copied_yuva_texture_info);
        Graphite_YUVABackendTextureInfo_delete(default_yuva_texture_info);

        reskia_graphite_yuva_backend_textures_t* default_yuva_textures =
                Graphite_YUVABackendTextures_new();
        if (!check(default_yuva_textures != nullptr &&
                   !Graphite_YUVABackendTextures_isValid(default_yuva_textures) &&
                   Graphite_YUVABackendTextures_numPlanes(default_yuva_textures) == 0 &&
                   Graphite_YUVABackendTextures_planeTexture(default_yuva_textures, 0) == nullptr,
                   "Graphite_YUVABackendTextures default")) {
            Graphite_YUVABackendTextures_delete(default_yuva_textures);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_YUVABackendTextures_delete(default_yuva_textures);

        reskia_graphite_backend_texture_t* default_backend_texture = Graphite_BackendTexture_new();
        reskia_graphite_backend_texture_t* copied_backend_texture =
                Graphite_BackendTexture_newCopy(default_backend_texture);
        sk_i_size_t default_backend_dimensions =
                Graphite_BackendTexture_dimensions(default_backend_texture);
        reskia_graphite_texture_info_t* backend_texture_info =
                Graphite_BackendTexture_info(default_backend_texture);
        if (!check(default_backend_texture != nullptr &&
                   copied_backend_texture != nullptr &&
                   !Graphite_BackendTexture_isValid(default_backend_texture) &&
                   Graphite_BackendTexture_backend(default_backend_texture) == 0 &&
                   Graphite_BackendTexture_equals(default_backend_texture, copied_backend_texture) &&
                   !Graphite_BackendTexture_notEquals(default_backend_texture, copied_backend_texture) &&
                   default_backend_dimensions != 0 &&
                   backend_texture_info != nullptr,
                   "Graphite_BackendTexture default")) {
            Graphite_TextureInfo_delete(backend_texture_info);
            static_sk_i_size_delete(default_backend_dimensions);
            Graphite_BackendTexture_delete(copied_backend_texture);
            Graphite_BackendTexture_delete(default_backend_texture);
            Reskia_GraphiteRecorder_Release(recorder);
            Reskia_GraphiteContext_Release(graphite_context);
            return false;
        }
        Graphite_TextureInfo_delete(backend_texture_info);
        static_sk_i_size_delete(default_backend_dimensions);
        Graphite_BackendTexture_delete(copied_backend_texture);
        Graphite_BackendTexture_delete(default_backend_texture);

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
