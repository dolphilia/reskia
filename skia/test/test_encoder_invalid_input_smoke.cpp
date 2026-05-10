#include "capi/sk_encoder.h"
#include "capi/sk_png_encoder.h"

#if RESKIA_TEST_ENABLE_JPEG_ENCODER
#include "capi/sk_jpeg_encoder.h"
#endif

#if RESKIA_TEST_ENABLE_WEBP_ENCODER
#include "capi/sk_webp_encoder.h"
#endif

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[encoder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkEncoder_delete(nullptr);
    ok &= check(!SkEncoder_encodeRows(nullptr, 1), "SkEncoder_encodeRows rejects null");
    ok &= check(!SkEncoder_encodeRows(nullptr, 0), "SkEncoder_encodeRows rejects non-positive rows");

#if RESKIA_TEST_ENABLE_JPEG_ENCODER
    ok &= check(!SkJpegEncoder_Encode(nullptr, nullptr, nullptr), "jpeg Encode rejects null");
    ok &= check(!SkJpegEncoder_EncodeYuvaPixmaps(nullptr, nullptr, nullptr, nullptr), "jpeg EncodeYuvaPixmaps rejects null");
    ok &= check(SkJpegEncoder_EncodeImage(nullptr, nullptr, nullptr) == 0, "jpeg EncodeImage rejects null");
    ok &= check(SkJpegEncoder_Make(nullptr, nullptr, nullptr) == 0, "jpeg Make rejects null");
    ok &= check(SkJpegEncoder_MakeYuvaPixmaps(nullptr, nullptr, nullptr, nullptr) == 0, "jpeg MakeYuvaPixmaps rejects null");
#endif

    ok &= check(!SkPngEncoder_Encode(nullptr, nullptr, nullptr), "png Encode rejects null");
    ok &= check(SkPngEncoder_EncodeFromImage(nullptr, nullptr, nullptr) == 0, "png EncodeFromImage rejects null");
    ok &= check(SkPngEncoder_Make(nullptr, nullptr, nullptr) == 0, "png Make rejects null");

#if RESKIA_TEST_ENABLE_WEBP_ENCODER
    ok &= check(!SkWebpEncoder_Encode(nullptr, nullptr, nullptr), "webp Encode rejects null");
    ok &= check(SkWebpEncoder_EncodeFromImage(nullptr, nullptr, nullptr) == 0, "webp EncodeFromImage rejects null");
    ok &= check(!SkWebpEncoder_EncodeAnimated(nullptr, 0, nullptr), "webp EncodeAnimated rejects null");
#endif

    return ok ? 0 : 1;
}
