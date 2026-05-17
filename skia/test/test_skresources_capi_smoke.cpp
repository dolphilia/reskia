#include "capi/sk_data.h"
#include "capi/sk_image.h"
#include "capi/sk_resources.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_sampling_options.h"

#include <cstdio>
#include <fstream>
#include <iterator>
#include <vector>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[skresources-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

std::vector<uint8_t> read_png_fixture() {
    std::ifstream file(RESKIA_TEST_PNG_PATH, std::ios::binary);
    return std::vector<uint8_t>(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());
}

bool write_png_fixture(const char *path, const std::vector<uint8_t> &png) {
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char *>(png.data()), static_cast<std::streamsize>(png.size()));
    return file.good();
}

bool check_image_handle(sk_image_t image, const char *message) {
    auto *image_ptr = reinterpret_cast<reskia_image_t *>(static_sk_image_get_ptr(image));
    const bool ok = image_ptr != nullptr && SkImage_width(image_ptr) == 1 && SkImage_height(image_ptr) == 1;
    static_sk_image_delete(image);
    return check(ok, message);
}

struct ExternalTrackState {
    int seeks = 0;
    int releases = 0;
    float last_t = 0.0f;
};

void external_track_seek(float t, void *user_data) {
    auto *state = static_cast<ExternalTrackState *>(user_data);
    if (state != nullptr) {
        state->seeks += 1;
        state->last_t = t;
    }
}

void external_track_release(void *user_data) {
    auto *state = static_cast<ExternalTrackState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(!ImageAsset_isMultiFrame(nullptr), "ImageAsset_isMultiFrame null");
    ok &= check(ImageAsset_getFrame(nullptr, 0.0f) == 0, "ImageAsset_getFrame null");
    reskia_skresources_frame_data_t frame_data{};
    ok &= check(!ImageAsset_getFrameData(nullptr, 0.0f, &frame_data), "ImageAsset_getFrameData null asset");
    ok &= check(!ImageAsset_getFrameData(nullptr, 0.0f, nullptr), "ImageAsset_getFrameData null output");
    ok &= check(MultiFrameImageAsset_Make(0, RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE) == nullptr, "MultiFrameImageAsset_Make invalid data");
    ok &= check(FileResourceProvider_Make(nullptr, RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE) == nullptr, "FileResourceProvider_Make null");
    ok &= check(CachingResourceProvider_Make(nullptr) == nullptr, "CachingResourceProvider_Make null");
    ok &= check(ResourceProvider_load(nullptr, nullptr, nullptr) == 0, "ResourceProvider_load null");
    ok &= check(ResourceProvider_loadImageAsset(nullptr, nullptr, nullptr, nullptr) == nullptr, "ResourceProvider_loadImageAsset null");
    ok &= check(ResourceProvider_loadFont(nullptr, nullptr, nullptr) == 0, "ResourceProvider_loadFont null");
    ok &= check(ResourceProvider_loadTypeface(nullptr, nullptr, nullptr) == 0, "ResourceProvider_loadTypeface null");
    ok &= check(ResourceProvider_loadAudioAsset(nullptr, nullptr, nullptr, nullptr) == nullptr, "ResourceProvider_loadAudioAsset null");
    ExternalTrackAsset_seek(nullptr, 1.0f);

    ExternalTrackState track_state;
    reskia_skresources_external_track_asset_t *track =
            ExternalTrackAsset_new(external_track_seek, &track_state, external_track_release);
    ok &= check(track != nullptr, "ExternalTrackAsset_new");
    ExternalTrackAsset_seek(track, 2.5f);
    ok &= check(track_state.seeks == 1 && track_state.last_t == 2.5f, "ExternalTrackAsset_seek callback");
    ExternalTrackAsset_ref(track);
    ExternalTrackAsset_release(track);
    ok &= check(track_state.releases == 0, "ExternalTrackAsset retained release keeps alive");
    ExternalTrackAsset_release(track);
    ok &= check(track_state.releases == 1, "ExternalTrackAsset final release callback");

    const std::vector<uint8_t> png = read_png_fixture();
    ok &= check(!png.empty(), "read png fixture");
    const sk_data_t png_data = png.empty() ? 0 : SkData_MakeWithCopy(png.data(), png.size());
    ok &= check(png_data != 0, "SkData_MakeWithCopy png");
    reskia_skresources_image_asset_t *asset =
            MultiFrameImageAsset_Make(png_data, RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE);
    if (asset != nullptr) {
        ok &= check(!MultiFrameImageAsset_isMultiFrame(asset), "MultiFrameImageAsset_isMultiFrame static png");
        ok &= check_image_handle(MultiFrameImageAsset_getFrame(asset, 0.0f), "MultiFrameImageAsset_getFrame png");
        ok &= check(!ImageAsset_isMultiFrame(asset), "ImageAsset_isMultiFrame static png");
        ok &= check_image_handle(ImageAsset_getFrame(asset, 0.0f), "ImageAsset_getFrame png");
        ok &= check(ImageAsset_getFrameData(asset, 0.0f, &frame_data), "ImageAsset_getFrameData png");
        ok &= check(frame_data.image != 0 && frame_data.sampling != 0 && frame_data.matrix != 0, "ImageAsset_getFrameData handles");
        static_sk_image_delete(frame_data.image);
        static_sk_sampling_options_delete(frame_data.sampling);
        static_sk_matrix_delete(frame_data.matrix);
        ImageAsset_release(asset);
    }
    static_sk_data_delete(png_data);

    const char *fixture_name = "reskia_skresources_fixture.png";
    ok &= check(write_png_fixture(fixture_name, png), "write png fixture");
    reskia_skresources_resource_provider_t *file_provider =
            FileResourceProvider_Make(".", RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE);
    ok &= check(file_provider != nullptr, "FileResourceProvider_Make cwd");
    if (file_provider != nullptr) {
        sk_data_t loaded = FileResourceProvider_load(file_provider, "", fixture_name);
        ok &= check(loaded != 0, "FileResourceProvider_load fixture");
        static_sk_data_delete(loaded);
        ok &= check(ResourceProvider_loadAudioAsset(file_provider, "", fixture_name, "fixture") == nullptr,
                    "ResourceProvider_loadAudioAsset default null");

        reskia_skresources_image_asset_t *file_asset =
                FileResourceProvider_loadImageAsset(file_provider, "", fixture_name, "fixture");
        if (file_asset != nullptr) {
            ImageAsset_release(file_asset);
        }

        reskia_skresources_resource_provider_t *cached = CachingResourceProvider_Make(file_provider);
        ok &= check(cached != nullptr, "CachingResourceProvider_Make");
        if (cached != nullptr) {
            reskia_skresources_image_asset_t *cached_asset =
                    ResourceProvider_loadImageAsset(cached, "", fixture_name, "fixture");
            if (cached_asset != nullptr) {
                ImageAsset_release(cached_asset);
            }
            ResourceProvider_release(cached);
        }

        reskia_skresources_resource_provider_t *data_uri = DataURIResourceProviderProxy_Make(
                file_provider,
                RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE,
                0);
        ok &= check(data_uri != nullptr, "DataURIResourceProviderProxy_Make");
        if (data_uri != nullptr) {
            ok &= check(ResourceProvider_loadImageAsset(data_uri, "", "data:image/png;base64,AAAA", "bad-data-uri") == nullptr,
                        "DataURIResourceProviderProxy bad data uri returns null");
            ResourceProvider_release(data_uri);
        }

        ResourceProvider_release(file_provider);
    }

    return ok ? 0 : 1;
}
