#include <array>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "include/codec/SkCodec.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPixmap.h"
#include "include/encode/SkJpegEncoder.h"
#include "include/encode/SkWebpEncoder.h"

#include "capi/sk_codec.h"
#include "capi/sk_data.h"
#include "capi/sk_dynamic_memory_w_stream.h"
#include "capi/sk_gif_decoder.h"
#include "capi/sk_graphics.h"
#include "capi/sk_jpeg_encoder.h"
#include "capi/sk_raw_decoder.h"
#include "capi/sk_webp_encoder.h"

#if RESKIA_TEST_ENABLE_AVIF
#include "capi/sk_avif_decoder.h"
#endif

#if RESKIA_TEST_ENABLE_JPEGXL
#include "capi/sk_jpegxl_decoder.h"
#endif

#include "handles/static_sk_codec.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_image_info.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[codec-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

std::vector<uint8_t> make_valid_gif_1x1() {
    return {
        0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x01, 0x00,
        0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0x21, 0xF9, 0x04, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x01, 0x00, 0x00, 0x02, 0x02, 0x44,
        0x01, 0x00, 0x3B
    };
}

std::vector<uint8_t> make_avif_ftyp_header() {
    return {
        0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70,
        0x61, 0x76, 0x69, 0x66, 0x00, 0x00, 0x00, 0x00,
        0x6D, 0x69, 0x66, 0x31, 0x61, 0x76, 0x69, 0x66
    };
}

std::vector<uint8_t> make_jpegxl_codestream_header() {
    return {0xFF, 0x0A, 0x00, 0x00};
}

std::vector<uint8_t> make_tiff_header() {
    return {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
}

bool smoke_decoder_is_functions() {
#if RESKIA_TEST_ENABLE_GIF
    const auto gif = make_valid_gif_1x1();
    if (!check(SkGifDecoder_IsGif(gif.data(), gif.size()), "SkGifDecoder_IsGif")) return false;
#endif

#if RESKIA_TEST_ENABLE_AVIF
    const auto avif = make_avif_ftyp_header();
    if (!check(SkAvifDecoder_IsAvif(avif.data(), avif.size()), "SkAvifDecoder_IsAvif")) return false;
#endif

#if RESKIA_TEST_ENABLE_JPEGXL
    const auto jxl = make_jpegxl_codestream_header();
    if (!check(SkJpegxlDecoder_IsJpegxl(jxl.data(), jxl.size()), "SkJpegxlDecoder_IsJpegxl")) return false;
#endif

#if RESKIA_TEST_ENABLE_RAW
    const auto raw = make_tiff_header();
    if (!check(SkRawDecoder_IsRaw(raw.data(), raw.size()), "SkRawDecoder_IsRaw")) return false;
#endif

    return true;
}

bool smoke_gif_decode() {
#if RESKIA_TEST_ENABLE_GIF
    const auto gif = make_valid_gif_1x1();
    const sk_data_t data = SkData_MakeWithCopy(gif.data(), gif.size());
    if (!check(data != 0, "SkData_MakeWithCopy(gif)")) return false;

    SkCodec::Result decode_result = SkCodec::kErrorInInput;
    const sk_codec_t codec = SkGifDecoder_DecodeFromData(
        data,
        reinterpret_cast<reskia_codec_result_t*>(&decode_result),
        nullptr
    );
    if (!check(codec != 0, "SkGifDecoder_DecodeFromData")) return false;

    auto* codec_ptr = reinterpret_cast<reskia_codec_t*>(static_sk_codec_get_ptr(codec));
    if (!check(codec_ptr != nullptr, "static_sk_codec_get_ptr(gif)")) return false;

    const sk_image_info_t info_handle = SkCodec_getInfo(codec_ptr);
    auto* info_ptr = reinterpret_cast<SkImageInfo*>(static_sk_image_info_get_ptr(info_handle));
    if (!check(info_ptr != nullptr, "SkCodec_getInfo")) return false;
    if (!check(info_ptr->width() == 1 && info_ptr->height() == 1, "decoded gif dimensions")) return false;

    const size_t row_bytes = info_ptr->minRowBytes();
    std::vector<uint8_t> pixels(row_bytes * static_cast<size_t>(info_ptr->height()));
    const auto result = SkCodec_getPixelsWithoutOptions(
        codec_ptr,
        reinterpret_cast<const reskia_image_info_t*>(info_ptr),
        pixels.data(),
        row_bytes
    );
    if (!check(result == static_cast<reskia_codec_result_code_t>(SkCodec::kSuccess), "SkCodec_getPixelsWithoutOptions(gif)")) return false;

    static_sk_image_info_delete(info_handle);
    static_sk_codec_delete(codec);
    static_sk_data_delete(data);
#endif
    return true;
}

bool smoke_optional_decode_entrypoints() {
#if RESKIA_TEST_ENABLE_AVIF
    const auto avif = make_avif_ftyp_header();
    const sk_data_t avif_data = SkData_MakeWithCopy(avif.data(), avif.size());
    if (!check(avif_data != 0, "SkData_MakeWithCopy(avif)")) return false;
    SkCodec::Result avif_result = SkCodec::kErrorInInput;
    const sk_codec_t avif_codec = SkAvifDecoder_DecodeFromData(
        avif_data, reinterpret_cast<reskia_codec_result_t*>(&avif_result), nullptr
    );
    if (avif_codec != 0) static_sk_codec_delete(avif_codec);
    static_sk_data_delete(avif_data);
#endif

#if RESKIA_TEST_ENABLE_JPEGXL
    const auto jxl = make_jpegxl_codestream_header();
    const sk_data_t jxl_data = SkData_MakeWithCopy(jxl.data(), jxl.size());
    if (!check(jxl_data != 0, "SkData_MakeWithCopy(jxl)")) return false;
    SkCodec::Result jxl_result = SkCodec::kErrorInInput;
    const sk_codec_t jxl_codec = SkJpegxlDecoder_DecodeFromData(
        jxl_data, reinterpret_cast<reskia_codec_result_t*>(&jxl_result), nullptr
    );
    if (jxl_codec != 0) static_sk_codec_delete(jxl_codec);
    static_sk_data_delete(jxl_data);
#endif

#if RESKIA_TEST_ENABLE_RAW
    const auto raw = make_tiff_header();
    const sk_data_t raw_data = SkData_MakeWithCopy(raw.data(), raw.size());
    if (!check(raw_data != 0, "SkData_MakeWithCopy(raw)")) return false;
    SkCodec::Result raw_result = SkCodec::kErrorInInput;
    const sk_codec_t raw_codec = SkRawDecoder_DecodeFromData(
        raw_data, reinterpret_cast<reskia_codec_result_t*>(&raw_result), nullptr
    );
    if (raw_codec != 0) static_sk_codec_delete(raw_codec);
    static_sk_data_delete(raw_data);
#endif

    return true;
}

bool smoke_encoders() {
    const int width = 2;
    const int height = 2;
    const std::array<uint32_t, 4> rgba = {
        0xFFFF0000u, 0xFF00FF00u,
        0xFF0000FFu, 0xFFFFFFFFu
    };

    const SkImageInfo image_info = SkImageInfo::Make(
        width, height, kRGBA_8888_SkColorType, kPremul_SkAlphaType
    );
    const size_t row_bytes = image_info.minRowBytes();
    const SkPixmap pixmap(image_info, rgba.data(), row_bytes);

#if RESKIA_TEST_ENABLE_JPEG_ENCODER
    {
        auto* stream = SkDynamicMemoryWStream_new();
        if (!check(stream != nullptr, "SkDynamicMemoryWStream_new(jpeg)")) return false;

        SkJpegEncoder::Options options;
        options.fQuality = 80;
        const bool ok = SkJpegEncoder_Encode(
            reinterpret_cast<reskia_w_stream_t*>(stream),
            reinterpret_cast<const reskia_pixmap_t*>(&pixmap),
            reinterpret_cast<const reskia_jpeg_encoder_options_t*>(&options)
        );
        if (!check(ok, "SkJpegEncoder_Encode")) return false;
        if (!check(SkDynamicMemoryWStream_bytesWritten(stream) > 0, "jpeg bytesWritten")) return false;

        const sk_data_t encoded = SkDynamicMemoryWStream_detachAsData(stream);
        if (!check(encoded != 0, "SkDynamicMemoryWStream_detachAsData(jpeg)")) return false;
        auto* encoded_ptr = reinterpret_cast<reskia_data_t*>(static_sk_data_get_ptr(encoded));
        if (!check(encoded_ptr != nullptr, "static_sk_data_get_ptr(jpeg)")) return false;
        if (!check(SkData_size(encoded_ptr) > 0, "jpeg encoded size")) return false;

        static_sk_data_delete(encoded);
        SkDynamicMemoryWStream_delete(stream);
    }
#endif

#if RESKIA_TEST_ENABLE_WEBP_ENCODER
    {
        auto* stream = SkDynamicMemoryWStream_new();
        if (!check(stream != nullptr, "SkDynamicMemoryWStream_new(webp)")) return false;

        SkWebpEncoder::Options options;
        options.fCompression = SkWebpEncoder::Compression::kLossy;
        options.fQuality = 75.0f;
        const bool ok = SkWebpEncoder_Encode(
            reinterpret_cast<reskia_w_stream_t*>(stream),
            reinterpret_cast<const reskia_pixmap_t*>(&pixmap),
            reinterpret_cast<const reskia_webp_encoder_options_t*>(&options)
        );
        if (!check(ok, "SkWebpEncoder_Encode")) return false;
        if (!check(SkDynamicMemoryWStream_bytesWritten(stream) > 0, "webp bytesWritten")) return false;

        const sk_data_t encoded = SkDynamicMemoryWStream_detachAsData(stream);
        if (!check(encoded != 0, "SkDynamicMemoryWStream_detachAsData(webp)")) return false;
        auto* encoded_ptr = reinterpret_cast<reskia_data_t*>(static_sk_data_get_ptr(encoded));
        if (!check(encoded_ptr != nullptr, "static_sk_data_get_ptr(webp)")) return false;
        if (!check(SkData_size(encoded_ptr) > 0, "webp encoded size")) return false;

        static_sk_data_delete(encoded);
        SkDynamicMemoryWStream_delete(stream);
    }
#endif

    return true;
}

#if RESKIA_TEST_ENABLE_OPEN_TYPE_SVG
std::unique_ptr<SkOpenTypeSVGDecoder> null_open_type_svg_decoder_factory(const uint8_t*, size_t) {
    return nullptr;
}

bool smoke_open_type_svg_factory() {
    const auto previous = SkGraphics_GetOpenTypeSVGDecoderFactory();
    (void)SkGraphics_SetOpenTypeSVGDecoderFactory(&null_open_type_svg_decoder_factory);
    const auto current = SkGraphics_GetOpenTypeSVGDecoderFactory();
    if (!check(current != nullptr, "SkGraphics_GetOpenTypeSVGDecoderFactory(after set)")) return false;
    (void)SkGraphics_SetOpenTypeSVGDecoderFactory(previous);
    return true;
}
#else
bool smoke_open_type_svg_factory() {
    return true;
}
#endif

}  // namespace

int main() {
    SkGraphics_Init();
    if (!smoke_decoder_is_functions()) return 1;
    if (!smoke_gif_decode()) return 1;
    if (!smoke_optional_decode_entrypoints()) return 1;
    if (!smoke_encoders()) return 1;
    if (!smoke_open_type_svg_factory()) return 1;
    std::fprintf(stdout, "[codec-smoke] PASS\n");
    return 0;
}
