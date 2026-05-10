#include "capi/sk_tiled_image_utils.h"

#include <cstdio>
#include <cstdint>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[tiled-image-utils-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    SkTiledImageUtils_DrawImageRect(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    SkTiledImageUtils_DrawImageRectWithImageSp(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    SkTiledImageUtils_DrawImageRectWithDst(nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    SkTiledImageUtils_DrawImageRectWithImageSpAndDst(nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    SkTiledImageUtils_DrawImage(nullptr, nullptr, 0.0f, 0.0f, nullptr, nullptr, 0);
    SkTiledImageUtils_DrawImageWithImageSp(nullptr, nullptr, 0.0f, 0.0f, nullptr, nullptr, 0);
    SkTiledImageUtils_GetImageKeyValues(nullptr, nullptr);

    uint32_t key_values[6] = {1, 2, 3, 4, 5, 6};
    SkTiledImageUtils_GetImageKeyValues(nullptr, key_values);
    for (uint32_t value : key_values) {
        ok &= check(value == 0, "GetImageKeyValues null image zero fills output");
    }

    return ok ? 0 : 1;
}
