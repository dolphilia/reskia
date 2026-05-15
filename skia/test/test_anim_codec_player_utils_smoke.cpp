#include <cstdint>
#include <cstdio>
#include <vector>

#include "capi/sk_anim_codec_player.h"
#include "capi/sk_codec.h"
#include "capi/sk_data.h"
#include "capi/sk_i_size.h"
#include "capi/sk_png_decoder.h"
#include "handles/static_sk_codec.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_image.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[anim-codec-player-utils-smoke] FAIL: %s\n", message);
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
    if (!check(SkAnimCodecPlayer_new(0) == nullptr, "SkAnimCodecPlayer_new invalid codec")) {
        return 1;
    }
    if (!check(SkAnimCodecPlayer_getFrame(nullptr) == 0, "SkAnimCodecPlayer_getFrame null")) {
        return 1;
    }
    if (!check(SkAnimCodecPlayer_dimensions(nullptr) == 0, "SkAnimCodecPlayer_dimensions null")) {
        return 1;
    }
    if (!check(SkAnimCodecPlayer_duration(nullptr) == 0, "SkAnimCodecPlayer_duration null")) {
        return 1;
    }
    if (!check(!SkAnimCodecPlayer_seek(nullptr, 0), "SkAnimCodecPlayer_seek null")) {
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
    reskia_anim_codec_player_t *player = SkAnimCodecPlayer_new(codec);
    if (!check(player != nullptr, "SkAnimCodecPlayer_new")) {
        static_sk_codec_delete(codec);
        static_sk_data_delete(data);
        return 1;
    }
    if (!check(static_sk_codec_get_ptr(codec) == nullptr, "SkAnimCodecPlayer_new consumes codec handle")) {
        SkAnimCodecPlayer_delete(player);
        static_sk_data_delete(data);
        return 1;
    }

    sk_i_size_t dimensions = SkAnimCodecPlayer_dimensions(player);
    auto *dimensions_ptr = reinterpret_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(dimensions));
    if (!check(dimensions_ptr != nullptr &&
               SkISize_width(dimensions_ptr) == 1 &&
               SkISize_height(dimensions_ptr) == 1,
               "SkAnimCodecPlayer_dimensions")) {
        static_sk_i_size_delete(dimensions);
        SkAnimCodecPlayer_delete(player);
        static_sk_data_delete(data);
        return 1;
    }
    static_sk_i_size_delete(dimensions);

    sk_image_t frame = SkAnimCodecPlayer_getFrame(player);
    if (!check(frame != 0, "SkAnimCodecPlayer_getFrame")) {
        SkAnimCodecPlayer_delete(player);
        static_sk_data_delete(data);
        return 1;
    }
    static_sk_image_delete(frame);
    (void)SkAnimCodecPlayer_duration(player);
    (void)SkAnimCodecPlayer_seek(player, 0);

    SkAnimCodecPlayer_delete(player);
    static_sk_data_delete(data);
    std::fprintf(stdout, "[anim-codec-player-utils-smoke] PASS\n");
    return 0;
}
