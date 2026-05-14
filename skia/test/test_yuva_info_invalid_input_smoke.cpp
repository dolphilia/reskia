#include <cstdio>
#include <cstdint>
#include <tuple>

#include "include/core/SkColor.h"
#include "include/core/SkSize.h"
#include "include/core/SkYUVAInfo.h"

#include "capi/sk_i_size.h"
#include "capi/sk_yuva_info.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_yuva_info.h"
#include "handles/static_std_tuple_int_int.h"
#include "handles/static_std_tuple_int_int-internal.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", message);
        return false;
    }
    return true;
}

bool check_tuple(tuple_int_int_t handle, int expected_x, int expected_y, const char *message) {
    if (handle == 0) {
        std::fprintf(stderr, "FAILED: %s (null handle)\n", message);
        return false;
    }
    const std::tuple<int, int> value = static_tuple_int_int_get_entity(handle);
    const int x = std::get<0>(value);
    const int y = std::get<1>(value);
    static_tuple_int_int_delete(handle);
    return check(x == expected_x && y == expected_y, message);
}

}  // namespace

int main() {
    bool ok = true;

    SkYUVAInfo_delete(nullptr);
    ok &= check(SkYUVAInfo_newCopy(nullptr) == nullptr, "copy rejects null");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(0, 1, 1, 0, 1, 0, 0) == nullptr, "constructor rejects invalid dimensions handle");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(SkISize_Make(2, 2), 99, 1, 0, 1, 0, 0) == nullptr, "constructor rejects invalid plane config");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(SkISize_Make(2, 2), 1, 99, 0, 1, 0, 0) == nullptr, "constructor rejects invalid subsampling");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(SkISize_Make(2, 2), 1, 1, 99, 1, 0, 0) == nullptr, "constructor rejects invalid color space");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(SkISize_Make(2, 2), 1, 1, 0, 0, 0, 0) == nullptr, "constructor rejects invalid origin");
    ok &= check(SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(SkISize_Make(2, 2), 1, 1, 0, 1, 1, 0) == nullptr, "constructor rejects invalid siting");

    ok &= check(!SkYUVAInfo_equals(nullptr, nullptr), "equals rejects null");
    ok &= check(!SkYUVAInfo_notEquals(nullptr, nullptr), "notEquals rejects null");
    ok &= check(SkYUVAInfo_planeConfig(nullptr) == -1, "planeConfig null");
    ok &= check(SkYUVAInfo_subsampling(nullptr) == -1, "subsampling null");
    ok &= check(SkYUVAInfo_planeSubsamplingFactors(nullptr, 0) == 0, "planeSubsamplingFactors null");
    ok &= check(SkYUVAInfo_dimensions(nullptr) == 0, "dimensions null");
    ok &= check(SkYUVAInfo_width(nullptr) == 0, "width null");
    ok &= check(SkYUVAInfo_height(nullptr) == 0, "height null");
    ok &= check(SkYUVAInfo_yuvColorSpace(nullptr) == -1, "yuvColorSpace null");
    ok &= check(SkYUVAInfo_sitingX(nullptr) == -1, "sitingX null");
    ok &= check(SkYUVAInfo_sitingY(nullptr) == -1, "sitingY null");
    ok &= check(SkYUVAInfo_origin(nullptr) == -1, "origin null");
    ok &= check(SkYUVAInfo_originMatrix(nullptr) == 0, "originMatrix null");
    ok &= check(!SkYUVAInfo_hasAlpha(nullptr), "hasAlpha null");
    ok &= check(SkYUVAInfo_planeDimensions(nullptr, nullptr) == 0, "planeDimensions rejects null");
    size_t plane_sizes[4] = {1, 1, 1, 1};
    ok &= check(SkYUVAInfo_computeTotalBytes(nullptr, nullptr, plane_sizes) == 0, "computeTotalBytes rejects null info and row bytes");
    ok &= check(plane_sizes[0] == 0 && plane_sizes[1] == 0 && plane_sizes[2] == 0 && plane_sizes[3] == 0, "computeTotalBytes clears sizes on null");
    ok &= check(SkYUVAInfo_numPlanes(nullptr) == 0, "numPlanes null");
    ok &= check(SkYUVAInfo_numChannelsInPlane(nullptr, 0) == 0, "numChannelsInPlane null");
    ok &= check(SkYUVAInfo_makeSubsampling(nullptr, 1) == 0, "makeSubsampling rejects null");
    ok &= check(SkYUVAInfo_makeDimensions(nullptr, 0) == 0, "makeDimensions rejects null");
    ok &= check(!SkYUVAInfo_isValid(nullptr), "isValid null");

    ok &= check(SkYUVAInfo_SubsamplingFactors(99) == 0, "static subsampling rejects invalid enum");
    ok &= check(SkYUVAInfo_PlaneSubsamplingFactors(99, 1, 0) == 0, "static plane subsampling rejects invalid config");
    ok &= check(SkYUVAInfo_PlaneSubsamplingFactors(1, 99, 0) == 0, "static plane subsampling rejects invalid subsampling");
    ok &= check(SkYUVAInfo_PlaneSubsamplingFactors(1, 1, 3) == 0, "static plane subsampling rejects out of range plane");
    SkISize null_plane_dimensions[4] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}};
    ok &= check(SkYUVAInfo_PlaneDimensions(0, 1, 1, 1, reinterpret_cast<reskia_i_size_t *>(null_plane_dimensions)) == 0, "static plane dimensions rejects invalid size handle");
    ok &= check(null_plane_dimensions[0].isEmpty() && null_plane_dimensions[1].isEmpty() && null_plane_dimensions[2].isEmpty() && null_plane_dimensions[3].isEmpty(), "static plane dimensions clears output");
    ok &= check(SkYUVAInfo_PlaneDimensions(SkISize_Make(2, 2), 1, 1, 0, reinterpret_cast<reskia_i_size_t *>(null_plane_dimensions)) == 0, "static plane dimensions rejects invalid origin");
    ok &= check(SkYUVAInfo_NumPlanes(99) == 0, "num planes rejects invalid config");
    ok &= check(SkYUVAInfo_NumChannelsInPlane(99, 0) == 0, "num channels rejects invalid config");
    reskia_yuva_location_t locations[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    ok &= check(!SkYUVAInfo_GetYUVALocations(99, nullptr, locations), "locations rejects invalid input");
    ok &= check(locations[0].plane == -1 && locations[1].plane == -1 && locations[2].plane == -1 && locations[3].plane == -1, "locations clears output");
    ok &= check(!SkYUVAInfo_toYUVALocations(nullptr, nullptr, locations), "instance locations rejects null input");
    ok &= check(locations[0].plane == -1 && locations[1].plane == -1 && locations[2].plane == -1 && locations[3].plane == -1, "instance locations clears output");
    ok &= check(!SkYUVAInfo_HasAlpha(99), "has alpha rejects invalid config");

    const sk_i_size_t size = SkISize_Make(4, 2);
    reskia_yuva_info_t *info = SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(
            size,
            1,  // SkYUVAInfo::PlaneConfig::kY_U_V
            1,  // SkYUVAInfo::Subsampling::k444
            0,  // kJPEG_Full_SkYUVColorSpace
            1,  // kTopLeft_SkEncodedOrigin
            0,  // SkYUVAInfo::Siting::kCentered
            0);
    ok &= check(info != nullptr, "valid info created");
    ok &= check(SkYUVAInfo_isValid(info), "valid info is valid");
    ok &= check(SkYUVAInfo_width(info) == 4 && SkYUVAInfo_height(info) == 2, "valid dimensions");
    ok &= check(SkYUVAInfo_numPlanes(info) == 3, "valid plane count");
    ok &= check(SkYUVAInfo_numChannelsInPlane(info, 0) == 1, "valid channels");
    ok &= check_tuple(SkYUVAInfo_SubsamplingFactors(1), 1, 1, "valid subsampling factors");
    ok &= check_tuple(SkYUVAInfo_planeSubsamplingFactors(info, 1), 1, 1, "valid instance plane subsampling factors");
    ok &= check(SkYUVAInfo_planeSubsamplingFactors(info, -1) == 0, "instance plane subsampling rejects negative");
    ok &= check(SkYUVAInfo_planeSubsamplingFactors(info, 3) == 0, "instance plane subsampling rejects out of range");

    SkISize plane_dimensions[4] = {};
    ok &= check(SkYUVAInfo_planeDimensions(info, reinterpret_cast<reskia_i_size_t *>(plane_dimensions)) == 3, "instance plane dimensions valid");
    ok &= check(plane_dimensions[0].width() == 4 && plane_dimensions[0].height() == 2, "instance plane dimensions output");
    const size_t row_bytes[4] = {4, 4, 4, 0};
    size_t valid_plane_sizes[4] = {};
    ok &= check(SkYUVAInfo_computeTotalBytes(info, row_bytes, valid_plane_sizes) == 24, "compute total bytes valid");
    ok &= check(valid_plane_sizes[0] == 8 && valid_plane_sizes[1] == 8 && valid_plane_sizes[2] == 8 && valid_plane_sizes[3] == 0, "plane sizes valid");
    ok &= check(SkYUVAInfo_computeTotalBytes(info, nullptr, valid_plane_sizes) == 0, "computeTotalBytes rejects null row bytes");

    const sk_yuva_info_t subsampled = SkYUVAInfo_makeSubsampling(info, 2);
    ok &= check(subsampled != 0, "makeSubsampling valid");
    static_sk_yuva_info_delete(subsampled);
    ok &= check(SkYUVAInfo_makeSubsampling(info, 99) == 0, "makeSubsampling rejects invalid enum");
    const sk_i_size_t new_size = SkISize_Make(8, 4);
    const sk_yuva_info_t resized = SkYUVAInfo_makeDimensions(info, new_size);
    ok &= check(resized != 0, "makeDimensions valid");
    static_sk_yuva_info_delete(resized);
    ok &= check(SkYUVAInfo_makeDimensions(info, 0) == 0, "makeDimensions rejects invalid size handle");

    const uint32_t flags[4] = {
            kGray_SkColorChannelFlag,
            kGray_SkColorChannelFlag,
            kGray_SkColorChannelFlag,
            0,
    };
    ok &= check(SkYUVAInfo_GetYUVALocations(1, flags, locations), "locations valid");
    ok &= check(locations[0].plane == 0 && locations[1].plane == 1 && locations[2].plane == 2 && locations[3].plane == -1, "locations output valid");
    ok &= check(SkYUVAInfo_toYUVALocations(info, flags, locations), "instance locations valid");
    ok &= check(locations[0].plane == 0 && locations[1].plane == 1 && locations[2].plane == 2 && locations[3].plane == -1, "instance locations output valid");
    ok &= check(!SkYUVAInfo_HasAlpha(1), "has alpha false");
    ok &= check(SkYUVAInfo_HasAlpha(7), "has alpha true");

    SkYUVAInfo_delete(info);
    static_sk_i_size_delete(size);
    static_sk_i_size_delete(new_size);

    return ok ? 0 : 1;
}
