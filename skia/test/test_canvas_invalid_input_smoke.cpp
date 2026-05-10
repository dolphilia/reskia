#include "capi/sk_canvas.h"
#include "capi/sk_image_info.h"
#include "handles/static_sk_image_info.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[canvas-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkCanvas_getSaveCount(nullptr) == 0, "SkCanvas_getSaveCount(nullptr)")) {
        return 1;
    }
    if (!check(!SkCanvas_readPixels(nullptr, nullptr, 0, 0), "SkCanvas_readPixels(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_quickReject(nullptr, nullptr), "SkCanvas_quickReject(nullptr)")) {
        return 3;
    }
    if (!check(!SkCanvas_quickRejectRect(nullptr, nullptr), "SkCanvas_quickRejectRect(nullptr)")) {
        return 4;
    }

    SkCanvas_translate(nullptr, 1.0f, 1.0f);
    SkCanvas_drawPath(nullptr, nullptr, nullptr);
    SkCanvas_drawPoints(nullptr, 0, 1, nullptr, nullptr);
    SkCanvas_drawSimpleText(nullptr, nullptr, 1, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawGlyphs(nullptr, 1, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawDrawable(nullptr, nullptr, nullptr);
    SkCanvas_drawDrawableAt(nullptr, nullptr, 0.0f, 0.0f);
    SkCanvas_drawPicture(nullptr, 0);
    SkCanvas_drawPictureHandleWithMatrixPaint(nullptr, 0, nullptr, nullptr);
    SkCanvas_drawPicturePtr(nullptr, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(nullptr, nullptr, nullptr, nullptr);
    if (!check(SkCanvas_saveLayer(nullptr, nullptr) == 0, "SkCanvas_saveLayer(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintRef(nullptr, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintRef(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintPtr(nullptr, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintPtr(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerAlpha(nullptr, nullptr, 255) == 0, "SkCanvas_saveLayerAlpha(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerAlphaf(nullptr, nullptr, 1.0f) == 0, "SkCanvas_saveLayerAlphaf(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirect(nullptr, nullptr, 0, nullptr) == 0, "SkCanvas_MakeRasterDirect(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(-1, 1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(negative width)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(1, -1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(negative height)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(1, 1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(null pixels)")) {
        return 5;
    }
    if (!check(SkCanvas_makeSurface(nullptr, nullptr, nullptr) == 0, "SkCanvas_makeSurface(nullptr)")) {
        return 5;
    }

    reskia_canvas_t *canvas = SkCanvas_new();
    if (!check(canvas != nullptr, "SkCanvas_new")) {
        return 6;
    }

    SkCanvas_translate(canvas, 1.0f, 1.0f);
    SkCanvas_drawPath(canvas, nullptr, nullptr);
    SkCanvas_drawPoints(canvas, 0, 1, nullptr, nullptr);
    SkCanvas_drawSimpleText(canvas, nullptr, 0, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawSimpleText(canvas, nullptr, 1, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 0, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), reinterpret_cast<const uint32_t *>(1), -1, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), reinterpret_cast<const uint32_t *>(1), 1, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(canvas, 0, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(canvas, 0, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, -1, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, -1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawDrawable(canvas, nullptr, nullptr);
    SkCanvas_drawDrawableAt(canvas, nullptr, 0.0f, 0.0f);
    SkCanvas_drawPicture(canvas, 0);
    SkCanvas_drawPicture(canvas, 999999);
    SkCanvas_drawImage(canvas, 0, 0.0f, 0.0f);
    SkCanvas_drawImage(canvas, 999999, 0.0f, 0.0f);
    SkCanvas_drawImageHandleWithSampling(canvas, 999999, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawImageRect(canvas, 999999, nullptr, nullptr, nullptr);
    SkCanvas_drawImageRectHandleWithSrcDst(canvas, 999999, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, 0, nullptr, nullptr);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, 999999, nullptr, nullptr);
    SkCanvas_drawPicturePtr(canvas, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, nullptr, nullptr, nullptr);
    if (!check(SkCanvas_saveLayer(canvas, nullptr) == 0, "SkCanvas_saveLayer(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintRef(canvas, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintRef(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintPtr(canvas, nullptr, nullptr) > 0, "SkCanvas_saveLayerWithBoundsPaintPtr optional bounds/paint")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_saveLayerAlpha(canvas, nullptr, 255) > 0, "SkCanvas_saveLayerAlpha optional bounds")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_saveLayerAlphaf(canvas, nullptr, 1.0f) > 0, "SkCanvas_saveLayerAlphaf optional bounds")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_makeSurface(canvas, nullptr, nullptr) == 0, "SkCanvas_makeSurface(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }

    if (!check(!SkCanvas_readPixels(canvas, nullptr, 0, 0), "SkCanvas_readPixels(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, nullptr, nullptr, 0, 0, 0), "SkCanvas_readPixelsWithImageInfo(null info)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, nullptr, nullptr, 0, 0, 0), "SkCanvas_writePixelsWithImageInfo(null info)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    const sk_image_info_t image_info_handle = SkImageInfo_MakeN32Premul(2, 2);
    auto *image_info = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(image_info_handle));
    if (!check(image_info != nullptr, "SkImageInfo_MakeN32Premul for canvas pixels")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    uint32_t pixels[4] = {};
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, image_info, nullptr, SkImageInfo_minRowBytes(image_info), 0, 0), "SkCanvas_readPixelsWithImageInfo(null pixels)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, image_info, pixels, 1, 0, 0), "SkCanvas_readPixelsWithImageInfo(invalid rowBytes)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, image_info, nullptr, SkImageInfo_minRowBytes(image_info), 0, 0), "SkCanvas_writePixelsWithImageInfo(null pixels)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, image_info, pixels, 1, 0, 0), "SkCanvas_writePixelsWithImageInfo(invalid rowBytes)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    static_sk_image_info_delete(image_info_handle);
    if (!check(!SkCanvas_quickReject(canvas, nullptr), "SkCanvas_quickReject(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 9;
    }
    if (!check(!SkCanvas_quickRejectRect(canvas, nullptr), "SkCanvas_quickRejectRect(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 10;
    }

    SkCanvas_delete(canvas);
    return 0;
}
