#include <cstdint>
#include <cstdio>
#include <vector>

#include "capi/sk_animated_image.h"
#include "capi/sk_android_codec.h"
#include "capi/sk_codec.h"
#include "capi/sk_data.h"
#include "capi/sk_png_decoder.h"
#include "handles/static_sk_android_codec.h"
#include "handles/static_sk_codec.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_image.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[animated-image-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

std::vector<uint8_t> make_valid_png_1x1() {
    return {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4,
        0x89, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x44, 0x41,
        0x54, 0x78, 0x9C, 0x63, 0xF8, 0xCF, 0xC0, 0xF0,
        0x1F, 0x00, 0x05, 0x00, 0x01, 0xFF, 0x89, 0x99,
        0x3D, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
        0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
    };
}

}  // namespace

int main() {
    if (!check(SkAnimatedImage_Make(0) == nullptr, "SkAnimatedImage_Make invalid codec")) {
        return 1;
    }
    if (!check(SkAnimatedImage_getCurrentFrame(nullptr) == 0, "SkAnimatedImage_getCurrentFrame null")) {
        return 1;
    }
    if (!check(SkAnimatedImage_decodeNextFrame(nullptr) == -1, "SkAnimatedImage_decodeNextFrame null")) {
        return 1;
    }
    if (!check(SkAnimatedImage_currentFrameDuration(nullptr) == -1, "SkAnimatedImage_currentFrameDuration null")) {
        return 1;
    }

    const auto png = make_valid_png_1x1();
    sk_data_t data = SkData_MakeWithCopy(png.data(), png.size());
    if (!check(data != 0, "SkData_MakeWithCopy png")) {
        return 1;
    }
    sk_codec_t codec = SkPngDecoder_DecodeFromData(data, nullptr, nullptr);
    if (!check(codec != 0, "SkPngDecoder_DecodeFromData png")) {
        static_sk_data_delete(data);
        return 1;
    }
    sk_android_codec_t android_codec = SkAndroidCodec_MakeFromCodec(codec);
    if (!check(android_codec != 0, "SkAndroidCodec_MakeFromCodec png")) {
        static_sk_codec_delete(codec);
        static_sk_data_delete(data);
        return 1;
    }

    reskia_animated_image_t *animated = SkAnimatedImage_Make(android_codec);
    if (!check(animated != nullptr, "SkAnimatedImage_Make")) {
        static_sk_android_codec_delete(android_codec);
        static_sk_data_delete(data);
        return 1;
    }
    if (!check(static_sk_android_codec_get_ptr(android_codec) == nullptr, "SkAnimatedImage_Make consumes codec handle")) {
        SkAnimatedImage_delete(animated);
        static_sk_data_delete(data);
        return 1;
    }

    if (!check(SkAnimatedImage_getFrameCount(animated) == 1, "SkAnimatedImage_getFrameCount")) {
        SkAnimatedImage_delete(animated);
        static_sk_data_delete(data);
        return 1;
    }
    SkAnimatedImage_setRepetitionCount(animated, 0);
    if (!check(SkAnimatedImage_getRepetitionCount(animated) == 0, "SkAnimatedImage_getRepetitionCount")) {
        SkAnimatedImage_delete(animated);
        static_sk_data_delete(data);
        return 1;
    }
    sk_image_t frame = SkAnimatedImage_getCurrentFrame(animated);
    if (!check(frame != 0, "SkAnimatedImage_getCurrentFrame")) {
        SkAnimatedImage_delete(animated);
        static_sk_data_delete(data);
        return 1;
    }
    static_sk_image_delete(frame);
    (void)SkAnimatedImage_currentFrameDuration(animated);
    (void)SkAnimatedImage_decodeNextFrame(animated);
    SkAnimatedImage_reset(animated);

    SkAnimatedImage_delete(animated);
    static_sk_data_delete(data);
    std::fprintf(stdout, "[animated-image-utils-smoke] PASS\n");
    return 0;
}
