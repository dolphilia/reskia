#include <cstdio>
#include <cstdint>
#include <vector>

#include "include/core/SkPixmap.h"

#include "capi/sk_i_size.h"
#include "capi/sk_yuva_info.h"
#include "capi/sk_yuva_pixmap_info.h"
#include "capi/sk_yuva_pixmaps.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_yuva_pixmap_info.h"
#include "handles/static_sk_yuva_pixmaps.h"
#include "handles/static_std_tuple_int_sk_yuva_pixmap_info_data_type.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkYUVAPixmapInfo_delete(nullptr);
    ok &= check(SkYUVAPixmapInfo_newWithInfoColorTypesAndRowBytes(nullptr, nullptr, nullptr) == nullptr, "pixmap info rejects null color type constructor input");
    ok &= check(SkYUVAPixmapInfo_newWithInfoDataTypeAndRowBytes(nullptr, 0, nullptr) == nullptr, "pixmap info rejects null yuva info");
    ok &= check(SkYUVAPixmapInfo_newWithInfoDataTypeAndRowBytes(nullptr, 99, nullptr) == nullptr, "pixmap info rejects invalid data type");
    ok &= check(SkYUVAPixmapInfo_newCopy(nullptr) == nullptr, "pixmap info copy rejects null");
    ok &= check(!SkYUVAPixmapInfo_equals(nullptr, nullptr), "pixmap info equals rejects null");
    ok &= check(!SkYUVAPixmapInfo_notEquals(nullptr, nullptr), "pixmap info notEquals rejects null");
    ok &= check(SkYUVAPixmapInfo_yuvaInfo(nullptr) == nullptr, "yuvaInfo null");
    ok &= check(SkYUVAPixmapInfo_yuvColorSpace(nullptr) == -1, "yuvColorSpace null");
    ok &= check(SkYUVAPixmapInfo_numPlanes(nullptr) == 0, "numPlanes null");
    ok &= check(SkYUVAPixmapInfo_dataType(nullptr) == -1, "dataType null");
    ok &= check(SkYUVAPixmapInfo_rowBytes(nullptr, 0) == 0, "rowBytes null");
    ok &= check(SkYUVAPixmapInfo_planeInfo(nullptr, 0) == nullptr, "planeInfo null");
    size_t null_plane_sizes[4] = {1, 1, 1, 1};
    ok &= check(SkYUVAPixmapInfo_computeTotalBytes(nullptr, null_plane_sizes) == 0, "computeTotalBytes null");
    ok &= check(null_plane_sizes[0] == 0 && null_plane_sizes[1] == 0 && null_plane_sizes[2] == 0 && null_plane_sizes[3] == 0, "computeTotalBytes clears sizes on null");
    ok &= check(!SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(nullptr, nullptr, nullptr), "initPixmaps rejects null");
    ok &= check(!SkYUVAPixmapInfo_isValid(nullptr), "isValid null");
    ok &= check(!SkYUVAPixmapInfo_isSupported(nullptr, nullptr), "isSupported null");
    ok &= check(SkYUVAPixmapInfo_DefaultColorTypeForDataType(99, 1) == -1, "default color type rejects invalid data type");
    ok &= check(SkYUVAPixmapInfo_NumChannelsAndDataType(-1) == 0, "num channels rejects invalid color type");

    SkYUVAPixmaps_delete(nullptr);
    ok &= check(SkYUVAPixmaps_newCopy(nullptr) == nullptr, "pixmaps copy rejects null");
    ok &= check(!SkYUVAPixmaps_isValid(nullptr), "pixmaps isValid null");
    ok &= check(SkYUVAPixmaps_yuvaInfo(nullptr) == nullptr, "pixmaps yuvaInfo null");
    ok &= check(SkYUVAPixmaps_dataType(nullptr) == -1, "pixmaps dataType null");
    ok &= check(SkYUVAPixmaps_pixmapsInfo(nullptr) == 0, "pixmaps info null");
    ok &= check(SkYUVAPixmaps_numPlanes(nullptr) == 0, "pixmaps numPlanes null");
    ok &= check(SkYUVAPixmaps_planes(nullptr) == nullptr, "planes null");
    ok &= check(SkYUVAPixmaps_plane(nullptr, 0) == nullptr, "plane null");
    reskia_yuva_location_t null_locations[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    ok &= check(!SkYUVAPixmaps_toYUVALocations(nullptr, null_locations), "pixmaps toYUVALocations null");
    ok &= check(null_locations[0].plane == -1 && null_locations[1].plane == -1 && null_locations[2].plane == -1 && null_locations[3].plane == -1, "pixmaps toYUVALocations clears output");
    ok &= check(!SkYUVAPixmaps_ownsStorage(nullptr), "ownsStorage null");
    ok &= check(SkYUVAPixmaps_RecommendedRGBAColorType(99) == -1, "recommended color type rejects invalid data type");
    ok &= check(SkYUVAPixmaps_Allocate(nullptr) == 0, "allocate rejects null");
    ok &= check(SkYUVAPixmaps_FromData(nullptr, 0) == 0, "from data rejects null");
    ok &= check(SkYUVAPixmaps_MakeCopy(nullptr) == 0, "make copy rejects null");
    ok &= check(SkYUVAPixmaps_FromExternalMemory(nullptr, nullptr) == 0, "from external memory rejects null");
    ok &= check(SkYUVAPixmaps_FromExternalPixmaps(nullptr, nullptr) == 0, "from external pixmaps rejects null");

    const sk_i_size_t size = SkISize_Make(2, 2);
    reskia_yuva_info_t *yuva_info = SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(
            size,
            1,  // SkYUVAInfo::PlaneConfig::kY_U_V
            1,  // SkYUVAInfo::Subsampling::k444
            0,  // first SkYUVColorSpace value
            1,  // kTopLeft_SkEncodedOrigin
            0,  // SkYUVAInfo::Siting::kCentered
            0);
    ok &= check(yuva_info != nullptr, "valid yuva info created");
    ok &= check(SkYUVAInfo_isValid(yuva_info), "yuva info valid");

    reskia_yuva_pixmap_info_t *info = SkYUVAPixmapInfo_newWithInfoDataTypeAndRowBytes(yuva_info, 0, nullptr);
    ok &= check(info != nullptr, "valid pixmap info created");
    ok &= check(SkYUVAPixmapInfo_isValid(info), "pixmap info valid");
    ok &= check(SkYUVAPixmapInfo_numPlanes(info) == 3, "pixmap info plane count");
    ok &= check(SkYUVAPixmapInfo_dataType(info) == 0, "pixmap info data type");
    ok &= check(SkYUVAPixmapInfo_rowBytes(info, 0) > 0, "rowBytes valid");
    ok &= check(SkYUVAPixmapInfo_rowBytes(info, -1) == 0, "rowBytes negative index");
    ok &= check(SkYUVAPixmapInfo_planeInfo(info, 0) != nullptr, "planeInfo valid");
    ok &= check(SkYUVAPixmapInfo_planeInfo(info, 3) == nullptr, "planeInfo out of range");

    size_t plane_sizes[4] = {};
    const size_t total_bytes = SkYUVAPixmapInfo_computeTotalBytes(info, plane_sizes);
    ok &= check(total_bytes > 0, "computeTotalBytes valid");
    ok &= check(plane_sizes[0] > 0 && plane_sizes[1] > 0 && plane_sizes[2] > 0, "plane sizes valid");

    SkPixmap planes[4];
    std::vector<std::uint8_t> memory(total_bytes);
    ok &= check(SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(info, memory.data(), reinterpret_cast<reskia_pixmap_t *>(planes)), "initPixmaps valid");
    ok &= check(!SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(info, nullptr, reinterpret_cast<reskia_pixmap_t *>(planes)), "initPixmaps rejects null memory");

    const sk_yuva_pixmaps_t allocated = SkYUVAPixmaps_Allocate(info);
    ok &= check(allocated != 0, "allocate valid");
    auto *allocated_ptr = static_cast<reskia_yuva_pixmaps_t *>(static_sk_yuva_pixmaps_get_ptr(allocated));
    ok &= check(SkYUVAPixmaps_isValid(allocated_ptr), "allocated pixmaps valid");
    ok &= check(SkYUVAPixmaps_numPlanes(allocated_ptr) == 3, "allocated plane count");
    ok &= check(SkYUVAPixmaps_plane(allocated_ptr, 0) != nullptr, "allocated plane valid");
    ok &= check(SkYUVAPixmaps_plane(allocated_ptr, -1) == nullptr, "allocated plane negative");
    ok &= check(SkYUVAPixmaps_plane(allocated_ptr, 3) == nullptr, "allocated plane out of range");
    reskia_yuva_location_t locations[4] = {};
    ok &= check(SkYUVAPixmaps_toYUVALocations(allocated_ptr, locations), "allocated toYUVALocations valid");
    ok &= check(locations[0].plane == 0 && locations[1].plane == 1 && locations[2].plane == 2 && locations[3].plane == -1, "allocated toYUVALocations output");
    const sk_yuva_pixmap_info_t allocated_info = SkYUVAPixmaps_pixmapsInfo(allocated_ptr);
    ok &= check(allocated_info != 0, "allocated pixmapsInfo valid");
    static_sk_yuva_pixmap_info_delete(allocated_info);
    const sk_yuva_pixmaps_t copied = SkYUVAPixmaps_MakeCopy(allocated_ptr);
    ok &= check(copied != 0, "make copy valid");
    static_sk_yuva_pixmaps_delete(copied);
    static_sk_yuva_pixmaps_delete(allocated);

    const sk_yuva_pixmaps_t external = SkYUVAPixmaps_FromExternalMemory(info, memory.data());
    ok &= check(external != 0, "external memory valid");
    static_sk_yuva_pixmaps_delete(external);

    const sk_yuva_pixmaps_t external_pixmaps = SkYUVAPixmaps_FromExternalPixmaps(yuva_info, reinterpret_cast<const reskia_pixmap_t *>(planes));
    ok &= check(external_pixmaps != 0, "external pixmaps valid");
    static_sk_yuva_pixmaps_delete(external_pixmaps);

    const tuple_int_sk_yuva_pixmap_info_data_type_t tuple_handle = SkYUVAPixmapInfo_NumChannelsAndDataType(1);
    ok &= check(tuple_handle != 0, "num channels valid");
    static_tuple_int_sk_yuva_pixmap_info_data_type_delete(tuple_handle);

    SkYUVAPixmapInfo_delete(info);
    SkYUVAInfo_delete(yuva_info);
    static_sk_i_size_delete(size);

    return ok ? 0 : 1;
}
