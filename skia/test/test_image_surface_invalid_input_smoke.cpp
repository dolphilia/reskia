#include "capi/sk_image.h"
#include "capi/sk_color_space.h"
#include "capi/sk_image_info.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_i_size.h"
#include "capi/sk_matrix.h"
#include "capi/sk_sampling_options.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_image_info.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_color_space.h"
#include "handles/static_sk_shader.h"
#include "handles/static_sk_surface.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[image-surface-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

struct AsyncFailState {
    int calls = 0;
};

void async_fail_callback(void *context, const reskia_async_read_result_t *result) {
    auto *state = static_cast<AsyncFailState *>(context);
    if (state != nullptr && result == nullptr) {
        ++state->calls;
    }
}

}  // namespace

int main() {
    if (!check(SkImage_width(nullptr) == 0, "SkImage_width(nullptr)")) {
        return 1;
    }
    if (!check(SkImage_height(nullptr) == 0, "SkImage_height(nullptr)")) {
        return 2;
    }
    if (!check(!SkImage_peekPixels(nullptr, nullptr), "SkImage_peekPixels(nullptr)")) {
        return 3;
    }
    if (!check(SkImage_colorSpace(nullptr) == nullptr, "SkImage_colorSpace(nullptr)")) {
        return 4;
    }
    if (!check(SkImage_refColorSpace(nullptr) == 0, "SkImage_refColorSpace(nullptr)")) {
        return 4;
    }
    if (!check(SkImage_refEncodedData(nullptr) == 0, "SkImage_refEncodedData(nullptr)")) {
        return 5;
    }

    SkImage_ref(nullptr);
    SkImage_unref(nullptr);
    SkImage_release(nullptr);

    if (!check(SkSurface_width(nullptr) == 0, "SkSurface_width(nullptr)")) {
        return 6;
    }
    if (!check(SkSurface_height(nullptr) == 0, "SkSurface_height(nullptr)")) {
        return 7;
    }
    if (!check(SkSurface_getCanvas(nullptr) == nullptr, "SkSurface_getCanvas(nullptr)")) {
        return 8;
    }
    if (!check(SkSurface_makeImageSnapshot(nullptr) == 0, "SkSurface_makeImageSnapshot(nullptr)")) {
        return 9;
    }
    if (!check(!SkSurface_peekPixels(nullptr, nullptr), "SkSurface_peekPixels(nullptr)")) {
        return 10;
    }
    if (!check(!SkSurface_readPixels(nullptr, nullptr, 0, 0), "SkSurface_readPixels(nullptr)")) {
        return 10;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(nullptr, nullptr, nullptr, 0, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels(nullptr)")) {
        return 10;
    }
    AsyncFailState async_fail_state;
    SkSurface_asyncRescaleAndReadPixels(nullptr, nullptr, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 1, "SkSurface_asyncRescaleAndReadPixels invalid fail callback")) {
        return 10;
    }
    SkSurface_asyncRescaleAndReadPixelsYUV420(nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 2, "SkSurface_asyncRescaleAndReadPixelsYUV420 invalid fail callback")) {
        return 10;
    }
    SkSurface_asyncRescaleAndReadPixelsYUVA420(nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 3, "SkSurface_asyncRescaleAndReadPixelsYUVA420 invalid fail callback")) {
        return 10;
    }

    SkSurface_notifyContentWillChange(nullptr, 0);
    SkSurface_writePixels(nullptr, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(nullptr, nullptr, 0, 0);
    SkSurface_ref(nullptr);
    SkSurface_unref(nullptr);
    SkSurface_release(nullptr);

    const sk_image_info_t info_handle = SkImageInfo_MakeN32Premul(2, 2);
    auto *info = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(info_handle));
    if (!check(info != nullptr, "SkImageInfo_MakeN32Premul")) {
        return 11;
    }
    const sk_surface_t surface_handle = SkSurfaces_RasterWithoutRowBytes(info, nullptr);
    auto *surface = static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(surface_handle));
    if (!check(surface != nullptr, "SkSurfaces_RasterWithoutRowBytes")) {
        static_sk_image_info_delete(info_handle);
        return 12;
    }
    uint32_t pixels[4] = {};
    if (!check(!SkSurface_readPixels(surface, nullptr, 0, 0), "SkSurface_readPixels null pixmap")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 13;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, nullptr, pixels, 8, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels null info")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 14;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, info, nullptr, SkImageInfo_minRowBytes(info), 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels null pixels")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 15;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, info, pixels, 1, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels invalid rowBytes")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 16;
    }
    const sk_i_rect_t src_rect_handle = SkIRect_MakeXYWH(0, 0, 1, 1);
    auto *src_rect = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(src_rect_handle));
    if (!check(src_rect != nullptr, "SkIRect_MakeXYWH for surface async")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 17;
    }
    SkSurface_asyncRescaleAndReadPixels(surface, nullptr, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 4, "SkSurface_asyncRescaleAndReadPixels null info fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 18;
    }
    SkSurface_asyncRescaleAndReadPixels(surface, info, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 5, "SkSurface_asyncRescaleAndReadPixels null srcRect fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 19;
    }
    SkSurface_asyncRescaleAndReadPixelsYUV420(surface, 0, 0, src_rect, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 6, "SkSurface_asyncRescaleAndReadPixelsYUV420 invalid dstSize fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 20;
    }
    SkSurface_asyncRescaleAndReadPixelsYUVA420(surface, 0, 0, src_rect, 999999, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 7, "SkSurface_asyncRescaleAndReadPixelsYUVA420 invalid dstSize fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 21;
    }
    const sk_image_t image_handle = SkSurface_makeImageSnapshot(surface);
    auto *image = static_cast<reskia_image_t *>(static_sk_image_get_ptr(image_handle));
    if (!check(image != nullptr, "SkSurface_makeImageSnapshot for image async")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 22;
    }
    if (!check(SkImage_colorSpace(image) == nullptr, "SkImage_colorSpace image without color space")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 23;
    }
    if (!check(SkImage_refColorSpace(image) == 0, "SkImage_refColorSpace image without color space")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 23;
    }
    SkImage_asyncRescaleAndReadPixels(nullptr, info, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 8, "SkImage_asyncRescaleAndReadPixels null image fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 23;
    }
    SkImage_asyncRescaleAndReadPixels(image, nullptr, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 9, "SkImage_asyncRescaleAndReadPixels null info fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 24;
    }
    SkImage_asyncRescaleAndReadPixels(image, info, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 10, "SkImage_asyncRescaleAndReadPixels null srcRect fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 25;
    }
    SkImage_asyncRescaleAndReadPixelsYUV420(image, 0, 0, src_rect, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 11, "SkImage_asyncRescaleAndReadPixelsYUV420 invalid dstSize fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 26;
    }
    SkImage_asyncRescaleAndReadPixelsYUVA420(image, 0, 0, src_rect, 999999, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 12, "SkImage_asyncRescaleAndReadPixelsYUVA420 invalid dstSize fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 27;
    }
    const sk_i_size_t valid_dst_size = SkISize_Make(1, 1);
    if (!check(static_sk_i_size_get_ptr(valid_dst_size) != nullptr, "SkISize_Make for image async")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 28;
    }
    static_sk_i_size_delete(valid_dst_size);
    if (!check(!SkImage_readPixels(image, nullptr, nullptr, pixels, 8, 0, 0, 0), "SkImage_readPixels null info")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 29;
    }
    if (!check(!SkImage_readPixels(image, nullptr, info, nullptr, SkImageInfo_minRowBytes(info), 0, 0, 0), "SkImage_readPixels null pixels")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 30;
    }
    if (!check(!SkImage_readPixels(image, nullptr, info, pixels, 1, 0, 0, 0), "SkImage_readPixels invalid rowBytes")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 31;
    }
    if (!check(!SkImage_readPixelsWithImageInfo(image, nullptr, pixels, 8, 0, 0, 0), "SkImage_readPixelsWithImageInfo null info")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 32;
    }
    if (!check(!SkImage_readPixelsWithImageInfo(image, info, nullptr, SkImageInfo_minRowBytes(info), 0, 0, 0), "SkImage_readPixelsWithImageInfo null pixels")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 33;
    }
    if (!check(!SkImage_readPixelsWithImageInfo(image, info, pixels, 1, 0, 0, 0), "SkImage_readPixelsWithImageInfo invalid rowBytes")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 34;
    }
    if (!check(!SkImage_readPixelsWithContextPixmap(image, nullptr, nullptr, 0, 0, 0), "SkImage_readPixelsWithContextPixmap null pixmap")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 35;
    }
    if (!check(!SkImage_readPixelsWithPixmap(image, nullptr, 0, 0, 0), "SkImage_readPixelsWithPixmap null pixmap")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 36;
    }
    if (!check(SkImage_makeSubset(nullptr, nullptr, src_rect) == 0, "SkImage_makeSubset null image")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 37;
    }
    if (!check(SkImage_makeSubset(image, nullptr, nullptr) == 0, "SkImage_makeSubset null subset")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 38;
    }
    const sk_i_rect_t invalid_subset_handle = SkIRect_MakeXYWH(4, 4, 1, 1);
    auto *invalid_subset = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(invalid_subset_handle));
    if (!check(invalid_subset != nullptr, "SkIRect_MakeXYWH invalid image subset")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 39;
    }
    if (!check(SkImage_makeSubset(image, nullptr, invalid_subset) == 0, "SkImage_makeSubset factory failure returns 0")) {
        static_sk_i_rect_delete(invalid_subset_handle);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 40;
    }
    static_sk_i_rect_delete(invalid_subset_handle);
    if (!check(SkImage_withDefaultMipmaps(nullptr) == 0, "SkImage_withDefaultMipmaps null image")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 41;
    }
    if (!check(SkImage_makeNonTextureImage(nullptr, nullptr) == 0, "SkImage_makeNonTextureImage null image")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 42;
    }
    if (!check(SkImage_makeRasterImage(nullptr, nullptr, 0) == 0, "SkImage_makeRasterImage null image")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 43;
    }
    if (!check(SkImage_makeRasterImageWithoutContext(nullptr, 0) == 0, "SkImage_makeRasterImageWithoutContext null image")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 44;
    }
    const sk_image_t raster_image_handle = SkImage_makeRasterImageWithoutContext(image, 0);
    if (raster_image_handle != 0) {
        if (!check(static_sk_image_get_ptr(raster_image_handle) != nullptr, "SkImage_makeRasterImageWithoutContext valid handle")) {
            static_sk_image_delete(raster_image_handle);
            static_sk_image_delete(image_handle);
            static_sk_i_rect_delete(src_rect_handle);
            static_sk_surface_delete(surface_handle);
            static_sk_image_info_delete(info_handle);
            return 45;
        }
        static_sk_image_delete(raster_image_handle);
    }
    reskia_sampling_options_t *sampling = SkSamplingOptions_new();
    if (!check(sampling != nullptr, "SkSamplingOptions_new for image shaders")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 46;
    }
    const sk_matrix_t matrix_handle = SkMatrix_I();
    auto *matrix = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(matrix_handle));
    if (!check(matrix != nullptr, "SkMatrix_I for image shaders")) {
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 47;
    }
    if (!check(SkImage_makeShader(nullptr, 0, 0, sampling, nullptr) == 0, "SkImage_makeShader null image")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 48;
    }
    if (!check(SkImage_makeShader(image, 0, 0, nullptr, nullptr) == 0, "SkImage_makeShader null sampling")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 49;
    }
    if (!check(SkImage_makeShaderWithTileModesAndLocalMatrix(image, 0, 0, sampling, nullptr) == 0, "SkImage_makeShaderWithTileModesAndLocalMatrix null matrix")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 50;
    }
    if (!check(SkImage_makeShaderWithSamplingAndLocalMatrix(nullptr, sampling, matrix) == 0, "SkImage_makeShaderWithSamplingAndLocalMatrix null image")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 51;
    }
    if (!check(SkImage_makeShaderWithSampling(image, nullptr, matrix) == 0, "SkImage_makeShaderWithSampling null sampling")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 52;
    }
    if (!check(SkImage_makeRawShader(nullptr, 0, 0, sampling, nullptr) == 0, "SkImage_makeRawShader null image")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 53;
    }
    if (!check(SkImage_makeRawShader(image, 0, 0, nullptr, nullptr) == 0, "SkImage_makeRawShader null sampling")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 54;
    }
    if (!check(SkImage_makeRawShaderWithTileModesAndLocalMatrix(image, 0, 0, sampling, nullptr) == 0, "SkImage_makeRawShaderWithTileModesAndLocalMatrix null matrix")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 55;
    }
    if (!check(SkImage_makeRawShaderWithSamplingAndLocalMatrix(nullptr, sampling, matrix) == 0, "SkImage_makeRawShaderWithSamplingAndLocalMatrix null image")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 56;
    }
    if (!check(SkImage_makeRawShaderWithSampling(image, nullptr, matrix) == 0, "SkImage_makeRawShaderWithSampling null sampling")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 57;
    }
    const sk_shader_t shader_handle = SkImage_makeShader(image, 0, 0, sampling, nullptr);
    if (shader_handle != 0) {
        static_sk_shader_delete(shader_handle);
    }
    if (!check(SkImage_makeColorSpace(nullptr, nullptr, 0) == 0, "SkImage_makeColorSpace null image")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 58;
    }
    if (!check(SkImage_makeColorSpace(image, nullptr, 999999) == 0, "SkImage_makeColorSpace invalid color space")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 59;
    }
    if (!check(SkImage_makeColorTypeAndColorSpace(image, nullptr, 4, 999999) == 0, "SkImage_makeColorTypeAndColorSpace invalid color space")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 60;
    }
    if (!check(SkImage_reinterpretColorSpace(image, 999999) == 0, "SkImage_reinterpretColorSpace invalid color space")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 61;
    }
    const sk_color_space_t srgb = SkColorSpace_MakeSRGB();
    if (!check(srgb != 0 && static_sk_color_space_get_ptr(srgb) != nullptr, "SkColorSpace_MakeSRGB for image color space")) {
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 62;
    }
    const sk_image_t reinterpreted = SkImage_reinterpretColorSpace(image, srgb);
    if (reinterpreted != 0) {
        if (!check(static_sk_image_get_ptr(reinterpreted) != nullptr, "SkImage_reinterpretColorSpace valid handle")) {
            static_sk_image_delete(reinterpreted);
            static_sk_color_space_delete(srgb);
            static_sk_matrix_delete(matrix_handle);
            SkSamplingOptions_delete(sampling);
            static_sk_image_delete(image_handle);
            static_sk_i_rect_delete(src_rect_handle);
            static_sk_surface_delete(surface_handle);
            static_sk_image_info_delete(info_handle);
            return 63;
        }
        static_sk_image_delete(reinterpreted);
    }
    const sk_image_info_t srgb_info_handle = SkImageInfo_MakeN32PremulWithColorSpace(2, 2, srgb);
    auto *srgb_info = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(srgb_info_handle));
    if (!check(srgb_info != nullptr, "SkImageInfo_MakeN32PremulWithColorSpace for image color space")) {
        static_sk_color_space_delete(srgb);
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 64;
    }
    const sk_surface_t srgb_surface_handle = SkSurfaces_RasterWithoutRowBytes(srgb_info, nullptr);
    auto *srgb_surface = static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(srgb_surface_handle));
    if (!check(srgb_surface != nullptr, "SkSurfaces_RasterWithoutRowBytes for image color space")) {
        static_sk_image_info_delete(srgb_info_handle);
        static_sk_color_space_delete(srgb);
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 65;
    }
    const sk_image_t srgb_image_handle = SkSurface_makeImageSnapshot(srgb_surface);
    auto *srgb_image = static_cast<reskia_image_t *>(static_sk_image_get_ptr(srgb_image_handle));
    if (!check(srgb_image != nullptr, "SkSurface_makeImageSnapshot for image color space")) {
        static_sk_surface_delete(srgb_surface_handle);
        static_sk_image_info_delete(srgb_info_handle);
        static_sk_color_space_delete(srgb);
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 66;
    }
    if (!check(SkImage_colorSpace(srgb_image) != nullptr, "SkImage_colorSpace borrowed valid color space")) {
        static_sk_image_delete(srgb_image_handle);
        static_sk_surface_delete(srgb_surface_handle);
        static_sk_image_info_delete(srgb_info_handle);
        static_sk_color_space_delete(srgb);
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 67;
    }
    const sk_color_space_t retained_color_space = SkImage_refColorSpace(srgb_image);
    if (!check(retained_color_space != 0 && static_sk_color_space_get_ptr(retained_color_space) != nullptr, "SkImage_refColorSpace retained valid color space")) {
        if (retained_color_space != 0) {
            static_sk_color_space_delete(retained_color_space);
        }
        static_sk_image_delete(srgb_image_handle);
        static_sk_surface_delete(srgb_surface_handle);
        static_sk_image_info_delete(srgb_info_handle);
        static_sk_color_space_delete(srgb);
        static_sk_matrix_delete(matrix_handle);
        SkSamplingOptions_delete(sampling);
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 68;
    }
    static_sk_color_space_delete(retained_color_space);
    static_sk_image_delete(srgb_image_handle);
    static_sk_surface_delete(srgb_surface_handle);
    static_sk_image_info_delete(srgb_info_handle);
    static_sk_color_space_delete(srgb);
    static_sk_matrix_delete(matrix_handle);
    SkSamplingOptions_delete(sampling);
    static_sk_image_delete(image_handle);
    static_sk_i_rect_delete(src_rect_handle);
    SkSurface_writePixels(surface, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(surface, nullptr, 0, 0);

    static_sk_surface_delete(surface_handle);
    static_sk_image_info_delete(info_handle);

    return 0;
}
