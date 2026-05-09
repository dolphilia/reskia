#include <cstdio>
#include <cstdint>

#include "capi/sk_image_info.h"
#include "capi/sk_pixmap.h"
#include "capi/sk_pixmap_utils.h"
#include "handles/static_sk_color_4f.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_image_info.h"

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

    SkPixmap_delete(nullptr);
    ok &= check(SkPixmap_newWithImageInfoAddressAndRowBytes(nullptr, nullptr, 0) == nullptr, "newWithImageInfo rejects null info");
    SkPixmap_reset(nullptr);
    SkPixmap_resetWithImageInfoAddressAndRowBytes(nullptr, nullptr, nullptr, 0);
    ok &= check(!SkPixmap_resetFromMask(nullptr, nullptr), "resetFromMask rejects null input");
    SkPixmap_setColorSpace(nullptr, 0);
    ok &= check(!SkPixmap_extractSubset(nullptr, nullptr, nullptr), "extractSubset rejects null input");

    ok &= check(SkPixmap_info(nullptr) == nullptr, "info null");
    ok &= check(SkPixmap_rowBytes(nullptr) == 0, "rowBytes null");
    ok &= check(SkPixmap_addr(nullptr) == nullptr, "addr null");
    ok &= check(SkPixmap_width(nullptr) == 0, "width null");
    ok &= check(SkPixmap_height(nullptr) == 0, "height null");
    ok &= check(SkPixmap_dimensions(nullptr) == 0, "dimensions null");
    ok &= check(SkPixmap_colorType(nullptr) == -1, "colorType null");
    ok &= check(SkPixmap_alphaType(nullptr) == -1, "alphaType null");
    ok &= check(SkPixmap_colorSpace(nullptr) == nullptr, "colorSpace null");
    ok &= check(SkPixmap_refColorSpace(nullptr) == 0, "refColorSpace null");
    ok &= check(!SkPixmap_isOpaque(nullptr), "isOpaque null");
    ok &= check(SkPixmap_bounds(nullptr) == 0, "bounds null");
    ok &= check(SkPixmap_rowBytesAsPixels(nullptr) == 0, "rowBytesAsPixels null");
    ok &= check(SkPixmap_shiftPerPixel(nullptr) == 0, "shiftPerPixel null");
    ok &= check(SkPixmap_computeByteSize(nullptr) == 0, "computeByteSize null");
    ok &= check(!SkPixmap_computeIsOpaque(nullptr), "computeIsOpaque null");
    ok &= check(SkPixmap_getColor(nullptr, 0, 0) == 0, "getColor null");
    ok &= check(SkPixmap_getColor4f(nullptr, 0, 0) == 0, "getColor4f null");
    ok &= check(SkPixmap_getAlphaf(nullptr, 0, 0) == 0.0f, "getAlphaf null");
    ok &= check(SkPixmap_addrAt(nullptr, 0, 0) == nullptr, "addrAt null");
    ok &= check(SkPixmap_addr8(nullptr) == nullptr, "addr8 null");
    ok &= check(SkPixmap_addr16(nullptr) == nullptr, "addr16 null");
    ok &= check(SkPixmap_addr32(nullptr) == nullptr, "addr32 null");
    ok &= check(SkPixmap_addr64(nullptr) == nullptr, "addr64 null");
    ok &= check(SkPixmap_addrF16(nullptr) == nullptr, "addrF16 null");
    ok &= check(SkPixmap_addr8At(nullptr, 0, 0) == nullptr, "addr8At null");
    ok &= check(SkPixmap_addr16At(nullptr, 0, 0) == nullptr, "addr16At null");
    ok &= check(SkPixmap_addr32At(nullptr, 0, 0) == nullptr, "addr32At null");
    ok &= check(SkPixmap_addr64At(nullptr, 0, 0) == nullptr, "addr64At null");
    ok &= check(SkPixmap_addrF16At(nullptr, 0, 0) == nullptr, "addrF16At null");
    ok &= check(SkPixmap_writable_addr(nullptr) == nullptr, "writable_addr null");
    ok &= check(SkPixmap_writable_addrAt(nullptr, 0, 0) == nullptr, "writable_addrAt null");
    ok &= check(SkPixmap_writable_addr8(nullptr, 0, 0) == nullptr, "writable_addr8 null");
    ok &= check(SkPixmap_writable_addr16(nullptr, 0, 0) == nullptr, "writable_addr16 null");
    ok &= check(SkPixmap_writable_addr32(nullptr, 0, 0) == nullptr, "writable_addr32 null");
    ok &= check(SkPixmap_writable_addr64(nullptr, 0, 0) == nullptr, "writable_addr64 null");
    ok &= check(SkPixmap_writable_addrF16(nullptr, 0, 0) == nullptr, "writable_addrF16 null");
    ok &= check(!SkPixmap_readPixels(nullptr, nullptr, nullptr, 0), "readPixels rejects null input");
    ok &= check(!SkPixmap_readPixelsWithSourceOffset(nullptr, nullptr, nullptr, 0, 0, 0), "readPixels offset rejects null input");
    ok &= check(!SkPixmap_readPixelsToPixmapWithSourceOffset(nullptr, nullptr, 0, 0), "readPixels pixmap offset rejects null input");
    ok &= check(!SkPixmap_readPixelsToPixmap(nullptr, nullptr), "readPixels pixmap rejects null input");
    ok &= check(!SkPixmap_scalePixels(nullptr, nullptr, nullptr), "scalePixels rejects null input");
    ok &= check(!SkPixmap_erase(nullptr, 0, nullptr), "erase rejects null input");
    ok &= check(!SkPixmap_eraseColor(nullptr, 0), "eraseColor rejects null input");
    ok &= check(!SkPixmap_eraseColor4fWithSubset(nullptr, nullptr, nullptr), "eraseColor4f rejects null input");
    ok &= check(!SkPixmapUtils_Orient(nullptr, nullptr, 1), "Orient rejects null pixmaps");
    ok &= check(!SkPixmapUtils_Orient(nullptr, nullptr, 99), "Orient rejects invalid origin");
    ok &= check(SkPixmapUtils_SwapWidthHeight(nullptr) == 0, "SwapWidthHeight rejects null info");

    const sk_image_info_t info_handle = SkImageInfo_MakeN32Premul(1, 1);
    auto *info = static_cast<const reskia_image_info_t *>(static_sk_image_info_get_ptr(info_handle));
    uint32_t pixels[1] = {0xff112233u};
    reskia_pixmap_t *pixmap = SkPixmap_newWithImageInfoAddressAndRowBytes(info, pixels, sizeof(uint32_t));

    ok &= check(pixmap != nullptr, "newWithImageInfo creates pixmap");
    ok &= check(SkPixmap_width(pixmap) == 1, "width valid");
    ok &= check(SkPixmap_height(pixmap) == 1, "height valid");
    ok &= check(SkPixmap_addr(pixmap) == pixels, "addr valid");
    ok &= check(SkPixmap_addrAt(pixmap, 0, 0) == pixels, "addrAt valid");
    ok &= check(SkPixmap_addrAt(pixmap, 1, 0) == nullptr, "addrAt out of bounds");
    ok &= check(SkPixmap_addr32(pixmap) == pixels, "addr32 valid");
    ok &= check(SkPixmap_addr8(pixmap) == nullptr, "addr8 rejects 32-bit pixmap");
    ok &= check(SkPixmap_writable_addr32(pixmap, 0, 0) == pixels, "writable_addr32 valid");
    ok &= check(SkPixmap_writable_addr32(pixmap, -1, 0) == nullptr, "writable_addr32 out of bounds");

    const sk_i_size_t dimensions = SkPixmap_dimensions(pixmap);
    ok &= check(dimensions != 0, "dimensions valid");
    static_sk_i_size_delete(dimensions);

    const sk_i_rect_t bounds = SkPixmap_bounds(pixmap);
    ok &= check(bounds != 0, "bounds valid");
    static_sk_i_rect_delete(bounds);

    const sk_color_4f_t color4f = SkPixmap_getColor4f(pixmap, 0, 0);
    ok &= check(color4f != 0, "getColor4f valid");
    static_sk_color_4f_delete(color4f);

    uint32_t dst_pixels[1] = {0};
    ok &= check(SkPixmap_readPixels(pixmap, info, dst_pixels, sizeof(uint32_t)), "readPixels valid");
    ok &= check(SkPixmap_eraseColor(pixmap, 0xff000000u), "eraseColor valid");

    const sk_image_info_t swapped = SkPixmapUtils_SwapWidthHeight(info);
    ok &= check(swapped != 0, "SwapWidthHeight valid");
    static_sk_image_info_delete(swapped);

    SkPixmap_delete(pixmap);
    static_sk_image_info_delete(info_handle);

    return ok ? 0 : 1;
}
