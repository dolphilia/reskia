#include "capi/sk_image_generator.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[image-generator-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkImageGenerator_delete(nullptr);

    ok &= check(SkImageGenerator_uniqueID(nullptr) == 0, "uniqueID null");
    ok &= check(SkImageGenerator_refEncodedData(nullptr) == 0, "refEncodedData null");
    ok &= check(SkImageGenerator_getInfo(nullptr) == 0, "getInfo null");
    ok &= check(!SkImageGenerator_isValid(nullptr, nullptr), "isValid null");
    ok &= check(!SkImageGenerator_isProtected(nullptr), "isProtected null");
    ok &= check(!SkImageGenerator_getPixels(nullptr, nullptr, nullptr, 0), "getPixels null");
    ok &= check(!SkImageGenerator_getPixelsWithPixmap(nullptr, nullptr), "getPixelsWithPixmap null");
    ok &= check(!SkImageGenerator_queryYUVAInfo(nullptr, nullptr, nullptr), "queryYUVAInfo null");
    ok &= check(!SkImageGenerator_getYUVAPlanes(nullptr, nullptr), "getYUVAPlanes null");
    ok &= check(!SkImageGenerator_isTextureGenerator(nullptr), "isTextureGenerator null");

    return ok ? 0 : 1;
}
