//
// Created by Codex on 2026/05/14.
//

#include "sk_gpu_backend_surface.h"

#if defined(SK_GANESH)
#include "include/core/SkString.h"
#include "include/gpu/GrBackendSemaphore.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/MutableTextureState.h"
#include "include/gpu/mock/GrMockTypes.h"
#include "include/core/SkTextureCompressionType.h"

#include "../handles/static_sk_i_size-internal.h"
#endif

#if defined(SK_METAL)
#include "include/gpu/mtl/GrMtlTypes.h"
#endif

namespace {

#if defined(SK_GANESH)
const GrBackendFormat *as_format(const reskia_gr_backend_format_t *format) {
    return reinterpret_cast<const GrBackendFormat *>(format);
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

reskia_gr_backend_format_t *GrBackendFormat_MakeMtl(int format) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return reinterpret_cast<reskia_gr_backend_format_t *>(new GrBackendFormat(GrBackendFormat::MakeMtl(static_cast<GrMTLPixelFormat>(format))));
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

int GrBackendFormat_asMtlFormat(const reskia_gr_backend_format_t *format) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return format != nullptr ? static_cast<int>(as_format(format)->asMtlFormat()) : 0;
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

bool GrBackendTexture_hasMipMaps(const reskia_gr_backend_texture_t *texture) {
    return GrBackendTexture_hasMipmaps(texture);
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

bool GrBackendTexture_getMtlTextureInfo(const reskia_gr_backend_texture_t *texture, reskia_gr_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH) && defined(SK_METAL)
    if (texture == nullptr || out_info == nullptr) {
        return false;
    }
    GrMtlTextureInfo info;
    if (!as_texture(texture)->getMtlTextureInfo(&info)) {
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

bool GrBackendRenderTarget_getMtlTextureInfo(const reskia_gr_backend_render_target_t *render_target, reskia_gr_mtl_texture_info_t *out_info) {
    if (out_info != nullptr) {
        *out_info = {};
    }
#if defined(SK_GANESH) && defined(SK_METAL)
    if (render_target == nullptr || out_info == nullptr) {
        return false;
    }
    GrMtlTextureInfo info;
    if (!as_render_target(render_target)->getMtlTextureInfo(&info)) {
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

void GrBackendSemaphore_initVulkan(reskia_gr_backend_semaphore_t *semaphore, uintptr_t vk_semaphore) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    if (semaphore != nullptr) {
        as_semaphore(semaphore)->initVulkan((VkSemaphore) vk_semaphore);
    }
#else
    (void) semaphore;
    (void) vk_semaphore;
#endif
}

uintptr_t GrBackendSemaphore_vkSemaphore(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    return semaphore != nullptr ? (uintptr_t) as_semaphore(semaphore)->vkSemaphore() : 0;
#else
    (void) semaphore;
    return 0;
#endif
}

void GrBackendSemaphore_initMetal(reskia_gr_backend_semaphore_t *semaphore, void *event, uint64_t value) {
#if defined(SK_GANESH) && defined(SK_METAL)
    if (semaphore != nullptr) {
        as_semaphore(semaphore)->initMetal(event, value);
    }
#else
    (void) semaphore;
    (void) event;
    (void) value;
#endif
}

void *GrBackendSemaphore_mtlSemaphore(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return semaphore != nullptr ? const_cast<void *>(as_semaphore(semaphore)->mtlSemaphore()) : nullptr;
#else
    (void) semaphore;
    return nullptr;
#endif
}

uint64_t GrBackendSemaphore_mtlValue(const reskia_gr_backend_semaphore_t *semaphore) {
#if defined(SK_GANESH) && defined(SK_METAL)
    return semaphore != nullptr ? as_semaphore(semaphore)->mtlValue() : 0;
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

reskia_skgpu_mutable_texture_state_t *MutableTextureState_new() {
#if defined(SK_GANESH)
    return reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(new skgpu::MutableTextureState());
#else
    return nullptr;
#endif
}

reskia_skgpu_mutable_texture_state_t *MutableTextureState_newVulkan(int vk_image_layout, uint32_t queue_family_index) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    return reinterpret_cast<reskia_skgpu_mutable_texture_state_t *>(new skgpu::MutableTextureState(static_cast<VkImageLayout>(vk_image_layout), queue_family_index));
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

int MutableTextureState_getVkImageLayout(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    return state != nullptr ? static_cast<int>(as_mutable_texture_state(state)->getVkImageLayout()) : 0;
#else
    (void) state;
    return 0;
#endif
}

uint32_t MutableTextureState_getQueueFamilyIndex(const reskia_skgpu_mutable_texture_state_t *state) {
#if defined(SK_GANESH) && defined(SK_VULKAN)
    return state != nullptr ? as_mutable_texture_state(state)->getQueueFamilyIndex() : 0;
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
