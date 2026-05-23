//
// Created by Codex on 2026/05/14.
//

#include "sk_gpu_backend_surface.h"

#include <vector>

#if defined(SK_GANESH)
#include "include/core/SkString.h"
#include "include/core/SkYUVAInfo.h"
#include "include/gpu/GrBackendSemaphore.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDriverBugWorkarounds.h"
#include "include/gpu/GrYUVABackendTextures.h"
#include "include/gpu/MutableTextureState.h"
#include "include/gpu/gl/GrGLExtensions.h"
#include "include/gpu/gl/GrGLTypes.h"
#include "include/gpu/mock/GrMockTypes.h"
#if defined(SK_METAL)
#include "include/gpu/ganesh/mtl/GrMtlBackendSurface.h"
#include "include/gpu/ganesh/mtl/GrMtlBackendSemaphore.h"
#endif
#if defined(SK_VULKAN)
#include "include/gpu/vk/VulkanMutableTextureState.h"
#endif
#include "include/core/SkTextureCompressionType.h"
#include "src/core/SkYUVAInfoLocation.h"

#include "../handles/static_sk_i_size-internal.h"
#endif

#if defined(SK_GANESH) && __has_include("include/third_party/vulkan/vulkan/vulkan_core.h")
#define RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO 1
#include "include/gpu/GrBackendDrawableInfo.h"
#endif

#if defined(SK_METAL)
#include "include/gpu/ganesh/mtl/GrMtlTypes.h"
#endif

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
const GrBackendFormat *as_format(const reskia_gr_backend_format_t *format) {
    return reinterpret_cast<const GrBackendFormat *>(format);
}

const SkYUVAInfo *as_yuva_info(const reskia_yuva_info_t *info) {
    return reinterpret_cast<const SkYUVAInfo *>(info);
}

GrBackendTexture *as_texture(reskia_gr_backend_texture_t *texture) {
    return reinterpret_cast<GrBackendTexture *>(texture);
}

const GrBackendTexture *as_texture(const reskia_gr_backend_texture_t *texture) {
    return reinterpret_cast<const GrBackendTexture *>(texture);
}

const GrBackendRenderTarget *as_render_target(const reskia_gr_backend_render_target_t *render_target) {
    return reinterpret_cast<const GrBackendRenderTarget *>(render_target);
}

GrBackendSemaphore *as_semaphore(reskia_gr_backend_semaphore_t *semaphore) {
    return reinterpret_cast<GrBackendSemaphore *>(semaphore);
}

const GrBackendSemaphore *as_semaphore(const reskia_gr_backend_semaphore_t *semaphore) {
    return reinterpret_cast<const GrBackendSemaphore *>(semaphore);
}

GrDriverBugWorkarounds *as_driver_bug_workarounds(reskia_gr_driver_bug_workarounds_t *workarounds) {
    return reinterpret_cast<GrDriverBugWorkarounds *>(workarounds);
}

const GrDriverBugWorkarounds *as_driver_bug_workarounds(const reskia_gr_driver_bug_workarounds_t *workarounds) {
    return reinterpret_cast<const GrDriverBugWorkarounds *>(workarounds);
}

GrGLExtensions *as_gl_extensions(reskia_gr_gl_extensions_t *extensions) {
    return reinterpret_cast<GrGLExtensions *>(extensions);
}

const GrGLExtensions *as_gl_extensions(const reskia_gr_gl_extensions_t *extensions) {
    return reinterpret_cast<const GrGLExtensions *>(extensions);
}

const GrYUVABackendTextureInfo *as_yuva_backend_texture_info(const reskia_gr_yuva_backend_texture_info_t *info) {
    return reinterpret_cast<const GrYUVABackendTextureInfo *>(info);
}

const GrYUVABackendTextures *as_yuva_backend_textures(const reskia_gr_yuva_backend_textures_t *textures) {
    return reinterpret_cast<const GrYUVABackendTextures *>(textures);
}

skgpu::MutableTextureState *as_mutable_texture_state(reskia_skgpu_mutable_texture_state_t *state) {
    return reinterpret_cast<skgpu::MutableTextureState *>(state);
}

const skgpu::MutableTextureState *as_mutable_texture_state(const reskia_skgpu_mutable_texture_state_t *state) {
    return reinterpret_cast<const skgpu::MutableTextureState *>(state);
}

skgpu::Mipmapped to_mipmapped(reskia_skgpu_mipmapped_t mipmapped) {
    return mipmapped ? skgpu::Mipmapped::kYes : skgpu::Mipmapped::kNo;
}

skgpu::Protected to_protected(reskia_skgpu_protected_t is_protected) {
    return is_protected ? skgpu::Protected::kYes : skgpu::Protected::kNo;
}

reskia_gpu_backend_api_t to_reskia_backend_api(GrBackendApi backend) {
    switch (backend) {
        case GrBackendApi::kMetal:
            return RESKIA_GPU_BACKEND_API_METAL;
        case GrBackendApi::kVulkan:
            return RESKIA_GPU_BACKEND_API_VULKAN;
        default:
            return RESKIA_GPU_BACKEND_API_UNKNOWN;
    }
}

reskia_gpu_backend_api_t to_reskia_backend_api(skgpu::BackendApi backend) {
    switch (backend) {
        case skgpu::BackendApi::kMetal:
            return RESKIA_GPU_BACKEND_API_METAL;
        case skgpu::BackendApi::kVulkan:
            return RESKIA_GPU_BACKEND_API_VULKAN;
        default:
            return RESKIA_GPU_BACKEND_API_UNKNOWN;
    }
}

reskia_skgpu_protected_t to_reskia_protected(skgpu::Protected is_protected) {
    return is_protected == skgpu::Protected::kYes ? 1 : 0;
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

bool driver_bug_workaround_is_enabled(const GrDriverBugWorkarounds &workarounds, int32_t type) {
    switch (type) {
#define GPU_OP(enum_type, name) \
        case GrDriverBugWorkaroundType::enum_type: return workarounds.name;
        GPU_DRIVER_BUG_WORKAROUNDS(GPU_OP)
#undef GPU_OP
        default:
            return false;
    }
}

GrMockTextureInfo to_mock_texture_info(const reskia_gr_mock_texture_info_t &info) {
    return GrMockTextureInfo(
            static_cast<GrColorType>(info.color_type),
            static_cast<SkTextureCompressionType>(info.compression_type),
            info.id,
            to_protected(info.is_protected));
}

GrMockRenderTargetInfo to_mock_render_target_info(const reskia_gr_mock_render_target_info_t &info) {
    return GrMockRenderTargetInfo(
            static_cast<GrColorType>(info.color_type),
            info.id,
            to_protected(info.is_protected));
}

GrGLTextureInfo to_gl_texture_info(const reskia_gr_gl_texture_info_t &info) {
    return GrGLTextureInfo{
            static_cast<GrGLenum>(info.target),
            static_cast<GrGLuint>(info.id),
            static_cast<GrGLenum>(info.format),
            to_protected(info.is_protected)};
}

GrGLFramebufferInfo to_gl_framebuffer_info(const reskia_gr_gl_framebuffer_info_t &info) {
    return GrGLFramebufferInfo{
            static_cast<GrGLuint>(info.fbo_id),
            static_cast<GrGLenum>(info.format),
            to_protected(info.is_protected)};
}

#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
GrVkDrawableInfo to_vk_drawable_info(const reskia_gr_vk_drawable_info_t &info) {
    return GrVkDrawableInfo{
            reinterpret_cast<VkCommandBuffer>(info.secondary_command_buffer),
            info.color_attachment_index,
            reinterpret_cast<VkRenderPass>(info.compatible_render_pass),
            static_cast<VkFormat>(info.format),
            static_cast<VkRect2D *>(info.draw_bounds)};
}

reskia_gr_vk_drawable_info_t to_reskia_vk_drawable_info(const GrVkDrawableInfo &info) {
    return reskia_gr_vk_drawable_info_t{
            reinterpret_cast<uintptr_t>(info.fSecondaryCommandBuffer),
            info.fColorAttachmentIndex,
            reinterpret_cast<uintptr_t>(info.fCompatibleRenderPass),
            static_cast<uint32_t>(info.fFormat),
            info.fDrawBounds};
}
#endif
#endif

#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
const GrBackendDrawableInfo *as_drawable_info(const reskia_gr_backend_drawable_info_t *info) {
    return reinterpret_cast<const GrBackendDrawableInfo *>(info);
}
#endif

}  // namespace

extern "C" {

reskia_gr_backend_format_t *GrBackendFormat_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat());
#else
    return nullptr;
#endif
}

reskia_gr_backend_format_t *GrBackendFormat_newCopy(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(*as_format(format))) : nullptr;
#else
    (void) format;
    return nullptr;
#endif
}

reskia_gr_backend_format_t *GrBackendFormat_MakeMock(reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression, bool is_stencil_format) {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(GrBackendFormat::MakeMock(static_cast<GrColorType>(color_type), static_cast<SkTextureCompressionType>(compression), is_stencil_format)));
#else
    (void) color_type;
    (void) compression;
    (void) is_stencil_format;
    return nullptr;
#endif
}

reskia_gr_backend_format_t *GrBackendFormats_MakeMtl(int format) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(GrBackendFormats::MakeMtl(static_cast<GrMTLPixelFormat>(format))));
#elif defined(SK_GANESH)
    (void) format;
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat());
#else
    (void) format;
    return nullptr;
#endif
}

void GrBackendFormat_delete(reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrBackendFormat *>(format);
#else
    (void) format;
#endif
}

bool GrBackendFormat_equals(const reskia_gr_backend_format_t *format, const reskia_gr_backend_format_t *other) {
#if defined(SK_GANESH)
    return format != nullptr && other != nullptr && *as_format(format) == *as_format(other);
#else
    (void) format;
    (void) other;
    return false;
#endif
}

bool GrBackendFormat_notEquals(const reskia_gr_backend_format_t *format, const reskia_gr_backend_format_t *other) {
#if defined(SK_GANESH)
    return format != nullptr && other != nullptr && *as_format(format) != *as_format(other);
#else
    (void) format;
    (void) other;
    return false;
#endif
}

reskia_gr_backend_api_t GrBackendFormat_backend(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? static_cast<reskia_gr_backend_api_t>(as_format(format)->backend()) : 0;
#else
    (void) format;
    return 0;
#endif
}

reskia_gr_texture_type_t GrBackendFormat_textureType(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? static_cast<reskia_gr_texture_type_t>(as_format(format)->textureType()) : 0;
#else
    (void) format;
    return 0;
#endif
}

uint32_t GrBackendFormat_channelMask(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? as_format(format)->channelMask() : 0;
#else
    (void) format;
    return 0;
#endif
}

bool GrBackendFormat_desc(const reskia_gr_backend_format_t *format, reskia_gr_color_format_desc_t *out_desc) {
    if (out_desc != nullptr) {
        *out_desc = {};
    }
#if defined(SK_GANESH)
    if (format == nullptr || out_desc == nullptr || !as_format(format)->isValid()) {
        return false;
    }
    GrColorFormatDesc desc = as_format(format)->desc();
    out_desc->r_bits = desc.r();
    out_desc->g_bits = desc.g();
    out_desc->b_bits = desc.b();
    out_desc->a_bits = desc.a();
    out_desc->gray_bits = desc.gray();
    out_desc->encoding = static_cast<int>(desc.encoding());
    return true;
#else
    (void) format;
    return false;
#endif
}

int GrBackendFormats_AsMtlFormat(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return format != nullptr ? static_cast<int>(GrBackendFormats::AsMtlFormat(*as_format(format))) : 0;
#else
    (void) format;
    return 0;
#endif
}

reskia_gr_color_type_t GrBackendFormat_asMockColorType(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? static_cast<reskia_gr_color_type_t>(as_format(format)->asMockColorType()) : 0;
#else
    (void) format;
    return 0;
#endif
}

reskia_sk_texture_compression_type_t GrBackendFormat_asMockCompressionType(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? static_cast<reskia_sk_texture_compression_type_t>(as_format(format)->asMockCompressionType()) : 0;
#else
    (void) format;
    return 0;
#endif
}

bool GrBackendFormat_isMockStencilFormat(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr && as_format(format)->isMockStencilFormat();
#else
    (void) format;
    return false;
#endif
}

reskia_gr_backend_format_t *GrBackendFormat_makeTexture2D(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_format(format)->makeTexture2D())) : nullptr;
#else
    (void) format;
    return nullptr;
#endif
}

bool GrBackendFormat_isValid(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH)
    return format != nullptr && as_format(format)->isValid();
#else
    (void) format;
    return false;
#endif
}

reskia_string_t *GrBackendFormat_toStr(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH) && (defined(SK_DEBUG) || defined(GR_TEST_UTILS))
    return format != nullptr ? reinterpret_cast<reskia_string_t *>(new SkString(as_format(format)->toStr())) : nullptr;
#else
    (void) format;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrBackendTexture_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture());
#else
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrBackendTexture_newCopy(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(*as_texture(texture))) : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

reskia_gr_backend_texture_t *GrBackendTexture_newMock(int width, int height, reskia_skgpu_mipmapped_t mipmapped, reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression, int id, reskia_skgpu_protected_t is_protected) {
#if defined(SK_GANESH)
    if (width <= 0 || height <= 0 || id == 0) {
        return nullptr;
    }
    GrMockTextureInfo info(static_cast<GrColorType>(color_type), static_cast<SkTextureCompressionType>(compression), id, to_protected(is_protected));
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(width, height, to_mipmapped(mipmapped), info));
#else
    (void) width;
    (void) height;
    (void) mipmapped;
    (void) color_type;
    (void) compression;
    (void) id;
    (void) is_protected;
    return nullptr;
#endif
}

void GrBackendTexture_delete(reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrBackendTexture *>(texture);
#else
    (void) texture;
#endif
}

sk_i_size_t GrBackendTexture_dimensions(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? static_sk_i_size_make(as_texture(texture)->dimensions()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

int GrBackendTexture_width(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? as_texture(texture)->width() : 0;
#else
    (void) texture;
    return 0;
#endif
}

int GrBackendTexture_height(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? as_texture(texture)->height() : 0;
#else
    (void) texture;
    return 0;
#endif
}

reskia_skgpu_mipmapped_t GrBackendTexture_mipmapped(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? static_cast<reskia_skgpu_mipmapped_t>(as_texture(texture)->mipmapped()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

bool GrBackendTexture_hasMipmaps(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr && as_texture(texture)->hasMipmaps();
#else
    (void) texture;
    return false;
#endif
}

reskia_gr_backend_api_t GrBackendTexture_backend(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? static_cast<reskia_gr_backend_api_t>(as_texture(texture)->backend()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

reskia_gr_texture_type_t GrBackendTexture_textureType(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? static_cast<reskia_gr_texture_type_t>(as_texture(texture)->textureType()) : 0;
#else
    (void) texture;
    return 0;
#endif
}

bool GrBackendTextures_GetMtlTextureInfo(const reskia_gr_backend_texture_t *texture, reskia_gr_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH) && defined(SK_METAL)
    if (texture == nullptr || out_info == nullptr) {
        return false;
    }
    GrMtlTextureInfo info;
    if (!GrBackendTextures::GetMtlTextureInfo(*as_texture(texture), &info)) {
        return false;
    }
    out_info->texture = const_cast<void *>(info.fTexture.get());
    return true;
#else
    (void) texture;
    return false;
#endif
}

reskia_gr_backend_format_t *GrBackendTexture_getBackendFormat(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_texture(texture)->getBackendFormat())) : nullptr;
#else
    (void) texture;
    return nullptr;
#endif
}

bool GrBackendTexture_getMockTextureInfo(const reskia_gr_backend_texture_t *texture, reskia_gr_mock_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH)
    if (texture == nullptr || out_info == nullptr) {
        return false;
    }
    GrMockTextureInfo info;
    if (!as_texture(texture)->getMockTextureInfo(&info)) {
        return false;
    }
    out_info->color_type = static_cast<reskia_gr_color_type_t>(info.colorType());
    out_info->compression_type = static_cast<reskia_sk_texture_compression_type_t>(info.compressionType());
    out_info->id = info.id();
    out_info->is_protected = to_reskia_protected(info.getProtected());
    return true;
#else
    (void) texture;
    return false;
#endif
}

reskia_string_t *GrBackendTexture_getLabel(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    if (texture == nullptr) {
        return nullptr;
    }
    std::string_view label = as_texture(texture)->getLabel();
    return reinterpret_cast<reskia_string_t *>(new SkString(label.data(), label.size()));
#else
    (void) texture;
    return nullptr;
#endif
}

void GrBackendTexture_setMutableState(reskia_gr_backend_texture_t *texture, const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    if (texture != nullptr && state != nullptr && as_mutable_texture_state(state)->isValid()) {
        as_texture(texture)->setMutableState(*as_mutable_texture_state(state));
    }
#else
    (void) texture;
    (void) state;
#endif
}

bool GrBackendTexture_isProtected(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr && as_texture(texture)->isProtected();
#else
    (void) texture;
    return false;
#endif
}

bool GrBackendTexture_isValid(const reskia_gr_backend_texture_t *texture) {
#if defined(SK_GANESH)
    return texture != nullptr && as_texture(texture)->isValid();
#else
    (void) texture;
    return false;
#endif
}

bool GrBackendTexture_isSameTexture(reskia_gr_backend_texture_t *texture, reskia_gr_backend_texture_t *other) {
#if defined(SK_GANESH)
    return texture != nullptr && other != nullptr && as_texture(texture)->isSameTexture(*as_texture(other));
#else
    (void) texture;
    (void) other;
    return false;
#endif
}

bool GrBackendTexture_asHandle(const reskia_gr_backend_texture_t *texture, reskia_gpu_backend_texture_handle_t *out_handle) {
    if (out_handle != nullptr) {
        out_handle->backend_api = RESKIA_GPU_BACKEND_API_UNKNOWN;
        out_handle->backend_texture = nullptr;
    }
#if defined(SK_GANESH)
    if (texture == nullptr || out_handle == nullptr || !as_texture(texture)->isValid()) {
        return false;
    }
    out_handle->backend_api = to_reskia_backend_api(as_texture(texture)->backend());
    out_handle->backend_texture = as_texture(texture);
    return true;
#else
    (void) texture;
    return false;
#endif
}

reskia_gr_backend_render_target_t *GrBackendRenderTarget_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_backend_render_target_t *>(new GrBackendRenderTarget());
#else
    return nullptr;
#endif
}

reskia_gr_backend_render_target_t *GrBackendRenderTarget_newCopy(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? reinterpret_cast<reskia_gr_backend_render_target_t *>(new GrBackendRenderTarget(*as_render_target(render_target))) : nullptr;
#else
    (void) render_target;
    return nullptr;
#endif
}

reskia_gr_backend_render_target_t *GrBackendRenderTarget_newMock(int width, int height, int sample_count, int stencil_bits, reskia_gr_color_type_t color_type, int id, reskia_skgpu_protected_t is_protected) {
#if defined(SK_GANESH)
    if (width <= 0 || height <= 0 || id == 0) {
        return nullptr;
    }
    GrMockRenderTargetInfo info(static_cast<GrColorType>(color_type), id, to_protected(is_protected));
    return reinterpret_cast<reskia_gr_backend_render_target_t *>(new GrBackendRenderTarget(width, height, sample_count, stencil_bits, info));
#else
    (void) width;
    (void) height;
    (void) sample_count;
    (void) stencil_bits;
    (void) color_type;
    (void) id;
    (void) is_protected;
    return nullptr;
#endif
}

void GrBackendRenderTarget_delete(reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrBackendRenderTarget *>(render_target);
#else
    (void) render_target;
#endif
}

sk_i_size_t GrBackendRenderTarget_dimensions(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? static_sk_i_size_make(as_render_target(render_target)->dimensions()) : 0;
#else
    (void) render_target;
    return 0;
#endif
}

int GrBackendRenderTarget_width(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? as_render_target(render_target)->width() : 0;
#else
    (void) render_target;
    return 0;
#endif
}

int GrBackendRenderTarget_height(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? as_render_target(render_target)->height() : 0;
#else
    (void) render_target;
    return 0;
#endif
}

int GrBackendRenderTarget_sampleCnt(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? as_render_target(render_target)->sampleCnt() : 0;
#else
    (void) render_target;
    return 0;
#endif
}

int GrBackendRenderTarget_stencilBits(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? as_render_target(render_target)->stencilBits() : 0;
#else
    (void) render_target;
    return 0;
#endif
}

reskia_gr_backend_api_t GrBackendRenderTarget_backend(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? static_cast<reskia_gr_backend_api_t>(as_render_target(render_target)->backend()) : 0;
#else
    (void) render_target;
    return 0;
#endif
}

bool GrBackendRenderTarget_isFramebufferOnly(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr && as_render_target(render_target)->isFramebufferOnly();
#else
    (void) render_target;
    return false;
#endif
}

bool GrBackendRenderTargets_GetMtlTextureInfo(const reskia_gr_backend_render_target_t *render_target, reskia_gr_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH) && defined(SK_METAL)
    if (render_target == nullptr || out_info == nullptr) {
        return false;
    }
    GrMtlTextureInfo info;
    if (!GrBackendRenderTargets::GetMtlTextureInfo(*as_render_target(render_target), &info)) {
        return false;
    }
    out_info->texture = const_cast<void *>(info.fTexture.get());
    return true;
#else
    (void) render_target;
    return false;
#endif
}

reskia_gr_backend_format_t *GrBackendRenderTarget_getBackendFormat(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_render_target(render_target)->getBackendFormat())) : nullptr;
#else
    (void) render_target;
    return nullptr;
#endif
}

bool GrBackendRenderTarget_getMockRenderTargetInfo(const reskia_gr_backend_render_target_t *render_target, reskia_gr_mock_render_target_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH)
    if (render_target == nullptr || out_info == nullptr) {
        return false;
    }
    GrMockRenderTargetInfo info;
    if (!as_render_target(render_target)->getMockRenderTargetInfo(&info)) {
        return false;
    }
    out_info->color_type = static_cast<reskia_gr_color_type_t>(info.colorType());
    out_info->id = 0;
    out_info->is_protected = to_reskia_protected(info.getProtected());
    return true;
#else
    (void) render_target;
    return false;
#endif
}

void GrBackendRenderTarget_setMutableState(reskia_gr_backend_render_target_t *render_target, const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    if (render_target != nullptr && state != nullptr && as_mutable_texture_state(state)->isValid()) {
        reinterpret_cast<GrBackendRenderTarget *>(render_target)->setMutableState(*as_mutable_texture_state(state));
    }
#else
    (void) render_target;
    (void) state;
#endif
}

bool GrBackendRenderTarget_isProtected(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr && as_render_target(render_target)->isProtected();
#else
    (void) render_target;
    return false;
#endif
}

bool GrBackendRenderTarget_isValid(const reskia_gr_backend_render_target_t *render_target) {
#if defined(SK_GANESH)
    return render_target != nullptr && as_render_target(render_target)->isValid();
#else
    (void) render_target;
    return false;
#endif
}

bool GrBackendRenderTarget_asHandle(const reskia_gr_backend_render_target_t *render_target, reskia_gpu_backend_render_target_handle_t *out_handle) {
    if (out_handle != nullptr) {
        out_handle->backend_api = RESKIA_GPU_BACKEND_API_UNKNOWN;
        out_handle->backend_render_target = nullptr;
    }
#if defined(SK_GANESH)
    if (render_target == nullptr || out_handle == nullptr || !as_render_target(render_target)->isValid()) {
        return false;
    }
    out_handle->backend_api = to_reskia_backend_api(as_render_target(render_target)->backend());
    out_handle->backend_render_target = as_render_target(render_target);
    return true;
#else
    (void) render_target;
    return false;
#endif
}

reskia_gr_backend_semaphore_t *GrBackendSemaphore_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_backend_semaphore_t *>(new GrBackendSemaphore());
#else
    return nullptr;
#endif
}

reskia_gr_backend_semaphore_t *GrBackendSemaphore_newCopy(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH)
    return semaphore != nullptr ? reinterpret_cast<reskia_gr_backend_semaphore_t *>(new GrBackendSemaphore(*as_semaphore(semaphore))) : nullptr;
#else
    (void) semaphore;
    return nullptr;
#endif
}

void GrBackendSemaphore_delete(reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH)
    delete as_semaphore(semaphore);
#else
    (void) semaphore;
#endif
}

reskia_gr_backend_semaphore_t *GrBackendSemaphores_MakeMtl(void *event, uint64_t value) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return reinterpret_cast<reskia_gr_backend_semaphore_t *>(new GrBackendSemaphore(GrBackendSemaphores::MakeMtl(event, value)));
#else
    (void) event;
    (void) value;
    return nullptr;
#endif
}

void *GrBackendSemaphores_GetMtlHandle(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return semaphore != nullptr ? const_cast<void *>(GrBackendSemaphores::GetMtlHandle(*as_semaphore(semaphore))) : nullptr;
#else
    (void) semaphore;
    return nullptr;
#endif
}

uint64_t GrBackendSemaphores_GetMtlValue(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return semaphore != nullptr ? GrBackendSemaphores::GetMtlValue(*as_semaphore(semaphore)) : 0;
#else
    (void) semaphore;
    return 0;
#endif
}

bool GrBackendSemaphore_isInitialized(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH)
    return semaphore != nullptr && as_semaphore(semaphore)->isInitialized();
#else
    (void) semaphore;
    return false;
#endif
}

reskia_gr_backend_api_t GrBackendSemaphore_backend(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH)
    return semaphore != nullptr ? static_cast<reskia_gr_backend_api_t>(as_semaphore(semaphore)->backend()) : 0;
#else
    (void) semaphore;
    return 0;
#endif
}

reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_driver_bug_workarounds_t *>(new GrDriverBugWorkarounds());
#else
    return nullptr;
#endif
}

reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_newWithTypes(const int32_t *workarounds, int count) {
#if defined(SK_GANESH)
    if (workarounds == nullptr || count < 0) {
        return nullptr;
    }
    std::vector<int32_t> native_workarounds;
    native_workarounds.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        if (workarounds[i] < 0 || workarounds[i] >= NUMBER_OF_GPU_DRIVER_BUG_WORKAROUND_TYPES) {
            return nullptr;
        }
        native_workarounds.push_back(workarounds[i]);
    }
    return reinterpret_cast<reskia_gr_driver_bug_workarounds_t *>(new GrDriverBugWorkarounds(native_workarounds));
#else
    (void) workarounds;
    (void) count;
    return nullptr;
#endif
}

reskia_gr_driver_bug_workarounds_t *GrDriverBugWorkarounds_newCopy(const reskia_gr_driver_bug_workarounds_t *workarounds) {
#if defined(SK_GANESH)
    return workarounds != nullptr
            ? reinterpret_cast<reskia_gr_driver_bug_workarounds_t *>(new GrDriverBugWorkarounds(*as_driver_bug_workarounds(workarounds)))
            : nullptr;
#else
    (void) workarounds;
    return nullptr;
#endif
}

void GrDriverBugWorkarounds_delete(reskia_gr_driver_bug_workarounds_t *workarounds) {
#if defined(SK_GANESH)
    delete as_driver_bug_workarounds(workarounds);
#else
    (void) workarounds;
#endif
}

void GrDriverBugWorkarounds_applyOverrides(reskia_gr_driver_bug_workarounds_t *workarounds, const reskia_gr_driver_bug_workarounds_t *overrides) {
#if defined(SK_GANESH)
    if (workarounds != nullptr && overrides != nullptr) {
        as_driver_bug_workarounds(workarounds)->applyOverrides(*as_driver_bug_workarounds(overrides));
    }
#else
    (void) workarounds;
    (void) overrides;
#endif
}

bool GrDriverBugWorkarounds_isEnabled(const reskia_gr_driver_bug_workarounds_t *workarounds, int32_t type) {
#if defined(SK_GANESH)
    return workarounds != nullptr && driver_bug_workaround_is_enabled(*as_driver_bug_workarounds(workarounds), type);
#else
    (void) workarounds;
    (void) type;
    return false;
#endif
}

bool GrMockTextureInfo_new(reskia_gr_mock_texture_info_t *out_info) {
    if (out_info == nullptr) {
        return false;
    }
    *out_info = {};
    return true;
}

bool GrMockTextureInfo_newWithValues(reskia_gr_color_type_t color_type, reskia_sk_texture_compression_type_t compression_type, int id, reskia_skgpu_protected_t is_protected, reskia_gr_mock_texture_info_t *out_info) {
    if (out_info == nullptr || id == 0) {
        return false;
    }
    *out_info = {color_type, compression_type, id, is_protected};
    return true;
}

bool GrMockTextureInfo_equals(const reskia_gr_mock_texture_info_t *info, const reskia_gr_mock_texture_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && to_mock_texture_info(*info) == to_mock_texture_info(*other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

reskia_gr_backend_format_t *GrMockTextureInfo_getBackendFormat(const reskia_gr_mock_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr && info->id != 0
                   ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(to_mock_texture_info(*info).getBackendFormat()))
                   : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

reskia_sk_texture_compression_type_t GrMockTextureInfo_compressionType(const reskia_gr_mock_texture_info_t *info) {
    return info != nullptr ? info->compression_type : 0;
}

reskia_gr_color_type_t GrMockTextureInfo_colorType(const reskia_gr_mock_texture_info_t *info) {
    return info != nullptr && info->compression_type == 0 ? info->color_type : 0;
}

int GrMockTextureInfo_id(const reskia_gr_mock_texture_info_t *info) {
    return info != nullptr ? info->id : 0;
}

reskia_skgpu_protected_t GrMockTextureInfo_getProtected(const reskia_gr_mock_texture_info_t *info) {
    return info != nullptr ? info->is_protected : 0;
}

bool GrMockTextureInfo_isProtected(const reskia_gr_mock_texture_info_t *info) {
    return info != nullptr && info->is_protected != 0;
}

bool GrMockRenderTargetInfo_new(reskia_gr_mock_render_target_info_t *out_info) {
    if (out_info == nullptr) {
        return false;
    }
    *out_info = {};
    return true;
}

bool GrMockRenderTargetInfo_newWithValues(reskia_gr_color_type_t color_type, int id, reskia_skgpu_protected_t is_protected, reskia_gr_mock_render_target_info_t *out_info) {
    if (out_info == nullptr || id == 0) {
        return false;
    }
    *out_info = {color_type, id, is_protected};
    return true;
}

bool GrMockRenderTargetInfo_equals(const reskia_gr_mock_render_target_info_t *info, const reskia_gr_mock_render_target_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && to_mock_render_target_info(*info) == to_mock_render_target_info(*other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

reskia_gr_backend_format_t *GrMockRenderTargetInfo_getBackendFormat(const reskia_gr_mock_render_target_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr && info->id != 0
                   ? reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(to_mock_render_target_info(*info).getBackendFormat()))
                   : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

reskia_gr_color_type_t GrMockRenderTargetInfo_colorType(const reskia_gr_mock_render_target_info_t *info) {
    return info != nullptr ? info->color_type : 0;
}

reskia_skgpu_protected_t GrMockRenderTargetInfo_getProtected(const reskia_gr_mock_render_target_info_t *info) {
    return info != nullptr ? info->is_protected : 0;
}

bool GrMockRenderTargetInfo_isProtected(const reskia_gr_mock_render_target_info_t *info) {
    return info != nullptr && info->is_protected != 0;
}

bool GrMockOptions_new() {
#if defined(SK_GANESH)
    GrMockOptions options;
    (void) options;
    return true;
#else
    return false;
#endif
}

bool GrGLTextureInfo_equals(const reskia_gr_gl_texture_info_t *info, const reskia_gr_gl_texture_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && to_gl_texture_info(*info) == to_gl_texture_info(*other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

bool GrGLTextureInfo_isProtected(const reskia_gr_gl_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr && to_gl_texture_info(*info).isProtected();
#else
    (void) info;
    return false;
#endif
}

bool GrGLFramebufferInfo_equals(const reskia_gr_gl_framebuffer_info_t *info, const reskia_gr_gl_framebuffer_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && to_gl_framebuffer_info(*info) == to_gl_framebuffer_info(*other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

bool GrGLFramebufferInfo_isProtected(const reskia_gr_gl_framebuffer_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr && to_gl_framebuffer_info(*info).isProtected();
#else
    (void) info;
    return false;
#endif
}

reskia_gr_gl_extensions_t *GrGLExtensions_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_gl_extensions_t *>(new GrGLExtensions());
#else
    return nullptr;
#endif
}

void GrGLExtensions_delete(reskia_gr_gl_extensions_t *extensions) {
#if defined(SK_GANESH)
    delete as_gl_extensions(extensions);
#else
    (void) extensions;
#endif
}

void GrGLExtensions_swap(reskia_gr_gl_extensions_t *extensions, reskia_gr_gl_extensions_t *other) {
#if defined(SK_GANESH)
    if (extensions != nullptr && other != nullptr) {
        as_gl_extensions(extensions)->swap(as_gl_extensions(other));
    }
#else
    (void) extensions;
    (void) other;
#endif
}

bool GrGLExtensions_isInitialized(const reskia_gr_gl_extensions_t *extensions) {
#if defined(SK_GANESH)
    return extensions != nullptr && as_gl_extensions(extensions)->isInitialized();
#else
    (void) extensions;
    return false;
#endif
}

void GrGLExtensions_reset(reskia_gr_gl_extensions_t *extensions) {
#if defined(SK_GANESH)
    if (extensions != nullptr) {
        as_gl_extensions(extensions)->reset();
    }
#else
    (void) extensions;
#endif
}

bool GrMtlTextureInfo_new(reskia_gr_mtl_texture_info_t *out_info) {
    if (out_info == nullptr) {
        return false;
    }
    *out_info = {};
    return true;
}

bool GrMtlTextureInfo_equals(const reskia_gr_mtl_texture_info_t *info, const reskia_gr_mtl_texture_info_t *other) {
    return info != nullptr && other != nullptr && info->texture == other->texture;
}

reskia_gr_backend_drawable_info_t *GrBackendDrawableInfo_new() {
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    return reinterpret_cast<reskia_gr_backend_drawable_info_t *>(new GrBackendDrawableInfo());
#else
    return nullptr;
#endif
}

reskia_gr_backend_drawable_info_t *GrBackendDrawableInfo_newVk(const reskia_gr_vk_drawable_info_t *info) {
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    return info != nullptr
                   ? reinterpret_cast<reskia_gr_backend_drawable_info_t *>(new GrBackendDrawableInfo(to_vk_drawable_info(*info)))
                   : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

void GrBackendDrawableInfo_delete(reskia_gr_backend_drawable_info_t *info) {
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    delete reinterpret_cast<GrBackendDrawableInfo *>(info);
#else
    (void) info;
#endif
}

bool GrBackendDrawableInfo_isValid(const reskia_gr_backend_drawable_info_t *info) {
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    return info != nullptr && as_drawable_info(info)->isValid();
#else
    (void) info;
    return false;
#endif
}

reskia_gr_backend_api_t GrBackendDrawableInfo_backend(const reskia_gr_backend_drawable_info_t *info) {
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    return info != nullptr ? static_cast<reskia_gr_backend_api_t>(as_drawable_info(info)->backend()) : 0;
#else
    (void) info;
    return 0;
#endif
}

bool GrBackendDrawableInfo_getVkDrawableInfo(const reskia_gr_backend_drawable_info_t *info, reskia_gr_vk_drawable_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(RESKIA_HAS_GR_BACKEND_DRAWABLE_INFO)
    if (info == nullptr || out_info == nullptr) {
        return false;
    }
    GrVkDrawableInfo native_info = {};
    if (!as_drawable_info(info)->getVkDrawableInfo(&native_info)) {
        return false;
    }
    *out_info = to_reskia_vk_drawable_info(native_info);
    return true;
#else
    (void) info;
    return false;
#endif
}

reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_yuva_backend_texture_info_t *>(new GrYUVABackendTextureInfo());
#else
    return nullptr;
#endif
}

reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_newWithYUVAInfoFormats(const reskia_yuva_info_t *info, const reskia_gr_backend_format_t *const *formats, reskia_skgpu_mipmapped_t mipmapped, int texture_origin) {
#if defined(SK_GANESH)
    const SkYUVAInfo *native_info = as_yuva_info(info);
    if (native_info == nullptr || formats == nullptr || !native_info->isValid()) {
        return nullptr;
    }
    GrBackendFormat native_formats[SkYUVAInfo::kMaxPlanes];
    const int num_planes = native_info->numPlanes();
    for (int i = 0; i < num_planes; ++i) {
        if (formats[i] == nullptr) {
            return nullptr;
        }
        native_formats[i] = *as_format(formats[i]);
    }
    return reinterpret_cast<reskia_gr_yuva_backend_texture_info_t *>(new GrYUVABackendTextureInfo(
            *native_info,
            native_formats,
            to_mipmapped(mipmapped),
            static_cast<GrSurfaceOrigin>(texture_origin)));
#else
    (void) info;
    (void) formats;
    (void) mipmapped;
    (void) texture_origin;
    return nullptr;
#endif
}

reskia_gr_yuva_backend_texture_info_t *GrYUVABackendTextureInfo_newCopy(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr
            ? reinterpret_cast<reskia_gr_yuva_backend_texture_info_t *>(new GrYUVABackendTextureInfo(*as_yuva_backend_texture_info(info)))
            : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

void GrYUVABackendTextureInfo_delete(reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrYUVABackendTextureInfo *>(info);
#else
    (void) info;
#endif
}

bool GrYUVABackendTextureInfo_equals(const reskia_gr_yuva_backend_texture_info_t *info, const reskia_gr_yuva_backend_texture_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && *as_yuva_backend_texture_info(info) == *as_yuva_backend_texture_info(other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

bool GrYUVABackendTextureInfo_notEquals(const reskia_gr_yuva_backend_texture_info_t *info, const reskia_gr_yuva_backend_texture_info_t *other) {
#if defined(SK_GANESH)
    return info != nullptr && other != nullptr && *as_yuva_backend_texture_info(info) != *as_yuva_backend_texture_info(other);
#else
    (void) info;
    (void) other;
    return false;
#endif
}

reskia_yuva_info_t *GrYUVABackendTextureInfo_yuvaInfo(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr ? reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(as_yuva_backend_texture_info(info)->yuvaInfo())) : nullptr;
#else
    (void) info;
    return nullptr;
#endif
}

int GrYUVABackendTextureInfo_yuvColorSpace(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr ? static_cast<int>(as_yuva_backend_texture_info(info)->yuvColorSpace()) : -1;
#else
    (void) info;
    return -1;
#endif
}

reskia_skgpu_mipmapped_t GrYUVABackendTextureInfo_mipmapped(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr ? static_cast<reskia_skgpu_mipmapped_t>(as_yuva_backend_texture_info(info)->mipmapped()) : 0;
#else
    (void) info;
    return 0;
#endif
}

int GrYUVABackendTextureInfo_textureOrigin(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr ? static_cast<int>(as_yuva_backend_texture_info(info)->textureOrigin()) : 0;
#else
    (void) info;
    return 0;
#endif
}

int GrYUVABackendTextureInfo_numPlanes(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr ? as_yuva_backend_texture_info(info)->numPlanes() : 0;
#else
    (void) info;
    return 0;
#endif
}

reskia_gr_backend_format_t *GrYUVABackendTextureInfo_planeFormat(const reskia_gr_yuva_backend_texture_info_t *info, int index) {
#if defined(SK_GANESH)
    if (info == nullptr || index < 0 || index >= as_yuva_backend_texture_info(info)->numPlanes()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(as_yuva_backend_texture_info(info)->planeFormat(index)));
#else
    (void) info;
    (void) index;
    return nullptr;
#endif
}

bool GrYUVABackendTextureInfo_isValid(const reskia_gr_yuva_backend_texture_info_t *info) {
#if defined(SK_GANESH)
    return info != nullptr && as_yuva_backend_texture_info(info)->isValid();
#else
    (void) info;
    return false;
#endif
}

bool GrYUVABackendTextureInfo_toYUVALocations(const reskia_gr_yuva_backend_texture_info_t *info, reskia_yuva_location_t *locations) {
    clear_yuva_locations(locations);
#if defined(SK_GANESH)
    if (info == nullptr || locations == nullptr || !as_yuva_backend_texture_info(info)->isValid()) {
        return false;
    }
    return copy_yuva_locations(as_yuva_backend_texture_info(info)->toYUVALocations(), locations);
#else
    (void) info;
    return false;
#endif
}

reskia_gr_yuva_backend_textures_t *GrYUVABackendTextures_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_gr_yuva_backend_textures_t *>(new GrYUVABackendTextures());
#else
    return nullptr;
#endif
}

reskia_gr_yuva_backend_textures_t *GrYUVABackendTextures_newWithYUVAInfoTextures(const reskia_yuva_info_t *info, const reskia_gr_backend_texture_t *const *textures, int texture_origin) {
#if defined(SK_GANESH)
    const SkYUVAInfo *native_info = as_yuva_info(info);
    if (native_info == nullptr || textures == nullptr || !native_info->isValid()) {
        return nullptr;
    }
    GrBackendTexture native_textures[SkYUVAInfo::kMaxPlanes];
    const int num_planes = native_info->numPlanes();
    for (int i = 0; i < num_planes; ++i) {
        if (textures[i] == nullptr) {
            return nullptr;
        }
        native_textures[i] = *as_texture(textures[i]);
    }
    return reinterpret_cast<reskia_gr_yuva_backend_textures_t *>(
            new GrYUVABackendTextures(*native_info, native_textures, static_cast<GrSurfaceOrigin>(texture_origin)));
#else
    (void) info;
    (void) textures;
    (void) texture_origin;
    return nullptr;
#endif
}

void GrYUVABackendTextures_delete(reskia_gr_yuva_backend_textures_t *textures) {
#if defined(SK_GANESH)
    delete reinterpret_cast<GrYUVABackendTextures *>(textures);
#else
    (void) textures;
#endif
}

int GrYUVABackendTextures_textures(const reskia_gr_yuva_backend_textures_t *textures, reskia_gr_backend_texture_t **out_textures, int capacity) {
#if defined(SK_GANESH)
    if (textures == nullptr) {
        return 0;
    }
    const GrYUVABackendTextures *native = as_yuva_backend_textures(textures);
    const int num_planes = native->numPlanes();
    if (out_textures != nullptr && capacity > 0) {
        const int count = capacity < num_planes ? capacity : num_planes;
        for (int i = 0; i < count; ++i) {
            out_textures[i] = reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(native->texture(i)));
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

reskia_gr_backend_texture_t *GrYUVABackendTextures_texture(const reskia_gr_yuva_backend_textures_t *textures, int index) {
#if defined(SK_GANESH)
    if (textures == nullptr || index < 0 || index >= as_yuva_backend_textures(textures)->numPlanes()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_gr_backend_texture_t *>(new GrBackendTexture(as_yuva_backend_textures(textures)->texture(index)));
#else
    (void) textures;
    (void) index;
    return nullptr;
#endif
}

reskia_yuva_info_t *GrYUVABackendTextures_yuvaInfo(const reskia_gr_yuva_backend_textures_t *textures) {
#if defined(SK_GANESH)
    return textures != nullptr ? reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(as_yuva_backend_textures(textures)->yuvaInfo())) : nullptr;
#else
    (void) textures;
    return nullptr;
#endif
}

int GrYUVABackendTextures_numPlanes(const reskia_gr_yuva_backend_textures_t *textures) {
#if defined(SK_GANESH)
    return textures != nullptr ? as_yuva_backend_textures(textures)->numPlanes() : 0;
#else
    (void) textures;
    return 0;
#endif
}

int GrYUVABackendTextures_textureOrigin(const reskia_gr_yuva_backend_textures_t *textures) {
#if defined(SK_GANESH)
    return textures != nullptr ? static_cast<int>(as_yuva_backend_textures(textures)->textureOrigin()) : 0;
#else
    (void) textures;
    return 0;
#endif
}

bool GrYUVABackendTextures_isValid(const reskia_gr_yuva_backend_textures_t *textures) {
#if defined(SK_GANESH)
    return textures != nullptr && as_yuva_backend_textures(textures)->isValid();
#else
    (void) textures;
    return false;
#endif
}

bool GrYUVABackendTextures_toYUVALocations(const reskia_gr_yuva_backend_textures_t *textures, reskia_yuva_location_t *locations) {
    clear_yuva_locations(locations);
#if defined(SK_GANESH)
    if (textures == nullptr || locations == nullptr || !as_yuva_backend_textures(textures)->isValid()) {
        return false;
    }
    return copy_yuva_locations(as_yuva_backend_textures(textures)->toYUVALocations(), locations);
#else
    (void) textures;
    return false;
#endif
}

reskia_skgpu_mutable_texture_state_t *MutableTextureState_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(new skgpu::MutableTextureState());
#else
    return nullptr;
#endif
}

reskia_skgpu_mutable_texture_state_t *MutableTextureState_newVulkan(int vk_image_layout, uint32_t queue_family_index) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    return reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(
            new skgpu::MutableTextureState(skgpu::MutableTextureStates::MakeVulkan(
                    static_cast<VkImageLayout>(vk_image_layout),
                    queue_family_index)));
#elif defined(SK_GANESH)
    (void) vk_image_layout;
    (void) queue_family_index;
    return reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(new skgpu::MutableTextureState());
#else
    (void) vk_image_layout;
    (void) queue_family_index;
    return nullptr;
#endif
}

reskia_skgpu_mutable_texture_state_t *MutableTextureState_newCopy(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    return state != nullptr ? reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(new skgpu::MutableTextureState(*as_mutable_texture_state(state))) : nullptr;
#else
    (void) state;
    return nullptr;
#endif
}

void MutableTextureState_delete(reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    delete as_mutable_texture_state(state);
#else
    (void) state;
#endif
}

void MutableTextureState_set(reskia_skgpu_mutable_texture_state_t *state, const reskia_skgpu_mutable_texture_state_t *other) {
#if defined(SK_GANESH)
    if (state != nullptr && other != nullptr) {
        as_mutable_texture_state(state)->set(*as_mutable_texture_state(other));
    }
#else
    (void) state;
    (void) other;
#endif
}

int MutableTextureState_getVkImageLayout(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    const skgpu::MutableTextureState *mutable_state = as_mutable_texture_state(state);
    return mutable_state != nullptr && mutable_state->backend() == skgpu::BackendApi::kVulkan
                   ? static_cast<int>(skgpu::MutableTextureStates::GetVkImageLayout(mutable_state))
                   : 0;
#else
    (void) state;
    return 0;
#endif
}

uint32_t MutableTextureState_getQueueFamilyIndex(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    const skgpu::MutableTextureState *mutable_state = as_mutable_texture_state(state);
    return mutable_state != nullptr && mutable_state->backend() == skgpu::BackendApi::kVulkan
                   ? skgpu::MutableTextureStates::GetVkQueueFamilyIndex(mutable_state)
                   : 0;
#else
    (void) state;
    return 0;
#endif
}

reskia_gr_backend_api_t MutableTextureState_backend(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    return state != nullptr ? to_reskia_backend_api(as_mutable_texture_state(state)->backend()) : 0;
#else
    (void) state;
    return 0;
#endif
}

bool MutableTextureState_isValid(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH)
    return state != nullptr && as_mutable_texture_state(state)->isValid();
#else
    (void) state;
    return false;
#endif
}

}
