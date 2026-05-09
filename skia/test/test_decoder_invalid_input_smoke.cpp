#include "capi/sk_bmp_decoder.h"
#include "capi/sk_ico_decoder.h"
#include "capi/sk_jpeg_decoder.h"
#include "capi/sk_png_decoder.h"
#include "capi/sk_wbmp_decoder.h"
#include "capi/sk_webp_decoder.h"

#if RESKIA_TEST_ENABLE_AVIF
#include "capi/sk_avif_decoder.h"
#endif

#if RESKIA_TEST_ENABLE_GIF
#include "capi/sk_gif_decoder.h"
#endif

#if RESKIA_TEST_ENABLE_JPEGXL
#include "capi/sk_jpegxl_decoder.h"
#endif

#if RESKIA_TEST_ENABLE_RAW
#include "capi/sk_raw_decoder.h"
#endif

#include <cstdint>
#include <cstdio>

namespace {

constexpr int32_t kInvalidInput = 6;

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[decoder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool check_result(int32_t value, const char *message) {
    return check(value == kInvalidInput, message);
}

}  // namespace

int main() {
    bool ok = true;
    int32_t result = -1;

    ok &= check(!SkBmpDecoder_IsBmp(nullptr, 1), "bmp Is rejects null");
    ok &= check(SkBmpDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "bmp Decode rejects invalid stream");
    ok &= check_result(result, "bmp Decode invalid result");
    result = -1;
    ok &= check(SkBmpDecoder_DecodeFromDataHandle(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "bmp DecodeFromData rejects invalid data");
    ok &= check_result(result, "bmp DecodeFromData invalid result");

    result = -1;
    ok &= check(!SkIcoDecoder_IsIco(nullptr, 1), "ico Is rejects null");
    ok &= check(SkIcoDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "ico Decode rejects invalid stream");
    ok &= check_result(result, "ico Decode invalid result");
    result = -1;
    ok &= check(SkIcoDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "ico DecodeFromData rejects invalid data");
    ok &= check_result(result, "ico DecodeFromData invalid result");

    result = -1;
    ok &= check(!SkJpegDecoder_IsJpeg(nullptr, 1), "jpeg Is rejects null");
    ok &= check(SkJpegDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "jpeg Decode rejects invalid stream");
    ok &= check_result(result, "jpeg Decode invalid result");
    result = -1;
    ok &= check(SkJpegDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "jpeg DecodeFromData rejects invalid data");
    ok &= check_result(result, "jpeg DecodeFromData invalid result");

    result = -1;
    ok &= check(!SkPngDecoder_IsPng(nullptr, 1), "png Is rejects null");
    ok &= check(SkPngDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "png Decode rejects invalid stream");
    ok &= check_result(result, "png Decode invalid result");
    result = -1;
    ok &= check(SkPngDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "png DecodeFromData rejects invalid data");
    ok &= check_result(result, "png DecodeFromData invalid result");

    result = -1;
    ok &= check(!SkWbmpDecoder_IsWbmp(nullptr, 1), "wbmp Is rejects null");
    ok &= check(SkWbmpDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "wbmp Decode rejects invalid stream");
    ok &= check_result(result, "wbmp Decode invalid result");
    result = -1;
    ok &= check(SkWbmpDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "wbmp DecodeFromData rejects invalid data");
    ok &= check_result(result, "wbmp DecodeFromData invalid result");

    result = -1;
    ok &= check(!SkWebpDecoder_IsWbmp(nullptr, 1), "webp Is rejects null");
    ok &= check(SkWebpDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "webp Decode rejects invalid stream");
    ok &= check_result(result, "webp Decode invalid result");
    result = -1;
    ok &= check(SkWebpDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "webp DecodeFromData rejects invalid data");
    ok &= check_result(result, "webp DecodeFromData invalid result");

#if RESKIA_TEST_ENABLE_AVIF
    result = -1;
    ok &= check(!SkAvifDecoder_IsAvif(nullptr, 1), "avif Is rejects null");
    ok &= check(SkAvifDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "avif Decode rejects invalid stream");
    ok &= check_result(result, "avif Decode invalid result");
    result = -1;
    ok &= check(SkAvifDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "avif DecodeFromData rejects invalid data");
    ok &= check_result(result, "avif DecodeFromData invalid result");
#endif

#if RESKIA_TEST_ENABLE_GIF
    result = -1;
    ok &= check(!SkGifDecoder_IsGif(nullptr, 1), "gif Is rejects null");
    ok &= check(SkGifDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "gif Decode rejects invalid stream");
    ok &= check_result(result, "gif Decode invalid result");
    result = -1;
    ok &= check(SkGifDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "gif DecodeFromData rejects invalid data");
    ok &= check_result(result, "gif DecodeFromData invalid result");
#endif

#if RESKIA_TEST_ENABLE_JPEGXL
    result = -1;
    ok &= check(!SkJpegxlDecoder_IsJpegxl(nullptr, 1), "jpegxl Is rejects null");
    ok &= check(SkJpegxlDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "jpegxl Decode rejects invalid stream");
    ok &= check_result(result, "jpegxl Decode invalid result");
    result = -1;
    ok &= check(SkJpegxlDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "jpegxl DecodeFromData rejects invalid data");
    ok &= check_result(result, "jpegxl DecodeFromData invalid result");
#endif

#if RESKIA_TEST_ENABLE_RAW
    result = -1;
    ok &= check(!SkRawDecoder_IsRaw(nullptr, 1), "raw Is rejects null");
    ok &= check(SkRawDecoder_Decode(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "raw Decode rejects invalid stream");
    ok &= check_result(result, "raw Decode invalid result");
    result = -1;
    ok &= check(SkRawDecoder_DecodeFromData(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr) == 0, "raw DecodeFromData rejects invalid data");
    ok &= check_result(result, "raw DecodeFromData invalid result");
#endif

    return ok ? 0 : 1;
}
