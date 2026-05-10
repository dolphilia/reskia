#include "capi/sk_images.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[images-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    ok &= check(SkImages_RasterFromBitmap(nullptr) == 0, "RasterFromBitmap null");
    ok &= check(SkImages_RasterFromCompressedTextureData(0, 1, 1, 0) == 0, "RasterFromCompressedTextureData invalid data");
    ok &= check(SkImages_DeferredFromEncodedData(0) == 0, "DeferredFromEncodedData invalid data");
    ok &= check(SkImages_DeferredFromGenerator(0) == 0, "DeferredFromGenerator invalid generator");
    ok &= check(SkImages_DeferredFromPicture(0, nullptr, nullptr, nullptr, 0, 0, 0) == 0, "DeferredFromPicture null dimensions");
    ok &= check(SkImages_DeferredFromPictureWithoutProps(0, nullptr, nullptr, nullptr, 0, 0) == 0, "DeferredFromPictureWithoutProps null dimensions");
    ok &= check(SkImages_RasterFromPixmapCopy(nullptr) == 0, "RasterFromPixmapCopy null");
    ok &= check(SkImages_RasterFromPixmap(nullptr, nullptr, nullptr) == 0, "RasterFromPixmap null");
    ok &= check(SkImages_RasterFromData(nullptr, 0, 0) == 0, "RasterFromData null info");

    sk_image_t out_image = 123;
    reskia_status_t status = SkImages_MakeWithFilter(0, nullptr, nullptr, nullptr, nullptr, nullptr, &out_image);
    ok &= check(status == RESKIA_STATUS_INVALID_ARGUMENT, "MakeWithFilter invalid args status");
    ok &= check(out_image == 0, "MakeWithFilter invalid args clears out image");

    status = SkImages_MakeWithFilter(0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    ok &= check(status == RESKIA_STATUS_INVALID_ARGUMENT, "MakeWithFilter null out image status");

    return ok ? 0 : 1;
}
