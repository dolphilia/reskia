#include "capi/sk_image.h"
#include "capi/sk_rect.h"
#include "capi/sk_resources.h"
#include "capi/sk_svg_image.h"
#include "capi/sk_svg_types.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_rect.h"

#include <cstdio>
#include <fstream>
#include <iterator>
#include <vector>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[svg-image-capi-smoke] FAIL: %s\n", message);
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

}  // namespace

int main() {
    bool ok = true;

    reskia_svg_image_info_t null_info{};
    ok &= check(!SkSVGImage_LoadImage(nullptr, nullptr, nullptr, nullptr, &null_info),
                "SkSVGImage_LoadImage null input");
    ok &= check(null_info.image == 0 && null_info.dst == 0,
                "SkSVGImage_LoadImage null output cleared");

    reskia_svg_preserve_aspect_ratio_t *par = SkSVGPreserveAspectRatio_new(0x05, 0);
    ok &= check(par != nullptr &&
                SkSVGPreserveAspectRatio_align(par) == 0x05 &&
                SkSVGPreserveAspectRatio_scale(par) == 0,
                "SkSVGPreserveAspectRatio accessors");
    SkSVGPreserveAspectRatio_set(par, 0x10, 1);
    ok &= check(SkSVGPreserveAspectRatio_align(par) == 0x10 &&
                SkSVGPreserveAspectRatio_scale(par) == 1,
                "SkSVGPreserveAspectRatio_set");
    SkSVGPreserveAspectRatio_set(par, 0x05, 0);

    const std::vector<uint8_t> png = read_png_fixture();
    ok &= check(!png.empty(), "read png fixture");
    const char *fixture_name = "reskia_svg_image_fixture.png";
    const char *fixture_path = "/tmp/reskia_svg_image_fixture.png";
    ok &= check(write_png_fixture(fixture_path, png), "write png fixture");

    reskia_skresources_resource_provider_t *provider =
            FileResourceProvider_Make("/tmp", RESKIA_SKRESOURCES_IMAGE_DECODE_STRATEGY_LAZY_DECODE);
    reskia_svg_iri_t *iri = SkSVGIRI_new(1, fixture_name);
    const sk_rect_t view_port_handle = SkRect_MakeXYWH(0.0f, 0.0f, 4.0f, 4.0f);
    auto *view_port = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(view_port_handle));

    reskia_svg_image_info_t image_info{};
    if (provider != nullptr && iri != nullptr && view_port != nullptr) {
        reskia_skresources_image_asset_t *direct_asset =
                ResourceProvider_loadImageAsset(provider, "", fixture_name, "fixture");
        if (direct_asset != nullptr) {
            ImageAsset_release(direct_asset);
            ok &= check(SkSVGImage_LoadImage(provider, iri, view_port, par, &image_info),
                        "SkSVGImage_LoadImage fixture");
            auto *image = reinterpret_cast<reskia_image_t *>(static_sk_image_get_ptr(image_info.image));
            auto *dst = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(image_info.dst));
            ok &= check(image != nullptr && SkImage_width(image) > 0 && SkImage_height(image) > 0,
                        "SkSVGImage_LoadImage image handle");
            ok &= check(dst != nullptr && SkRect_width(dst) == 4.0f && SkRect_height(dst) == 4.0f,
                        "SkSVGImage_LoadImage dst handle");
        } else {
            ok &= check(!SkSVGImage_LoadImage(provider, iri, view_port, par, &image_info),
                        "SkSVGImage_LoadImage undecodable fixture");
            ok &= check(image_info.image == 0 && image_info.dst == 0,
                        "SkSVGImage_LoadImage undecodable output cleared");
        }
    } else {
        ok &= check(false, "SkSVGImage_LoadImage setup");
    }

    static_sk_image_delete(image_info.image);
    static_sk_rect_delete(image_info.dst);
    static_sk_rect_delete(view_port_handle);
    SkSVGIRI_delete(iri);
    ResourceProvider_release(provider);
    SkSVGPreserveAspectRatio_delete(par);

    return ok ? 0 : 1;
}
