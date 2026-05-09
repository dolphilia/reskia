#include "capi/sk_i_rect.h"
#include "capi/sk_mask.h"
#include "capi/sk_mask_builder.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_mask.h"
#include "handles/static_sk_mask_builder.h"

#include <cstdint>
#include <cstdio>

namespace {

constexpr int kBWFormat = 0;
constexpr int kA8Format = 1;
constexpr int kARGB32Format = 3;
constexpr int kLCD16Format = 4;

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[mask-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkMask_delete(nullptr);
    SkMaskBuilder_delete(nullptr);
    SkMaskBuilder_FreeImage(nullptr);

    if (!check(SkMask_new(nullptr, nullptr, 0, kA8Format) == 0, "SkMask_new(nullptr bounds)")) {
        return 1;
    }
    if (!check(SkMask_new(nullptr, nullptr, 0, 99) == 0, "SkMask_new(invalid)")) {
        return 2;
    }
    if (!check(SkMask_fImage(nullptr) == nullptr, "SkMask_fImage(nullptr)")) {
        return 3;
    }
    const sk_i_rect_t null_bounds = SkMask_fBounds(nullptr);
    if (!check(static_sk_i_rect_get_ptr(null_bounds) != nullptr, "SkMask_fBounds(nullptr)")) {
        return 4;
    }
    static_sk_i_rect_delete(null_bounds);
    if (!check(SkMask_fRowBytes(nullptr) == 0, "SkMask_fRowBytes(nullptr)")) {
        return 5;
    }
    if (!check(SkMask_fFormat(nullptr) == -1, "SkMask_fFormat(nullptr)")) {
        return 6;
    }
    if (!check(SkMask_isEmpty(nullptr), "SkMask_isEmpty(nullptr)")) {
        return 7;
    }
    if (!check(SkMask_computeImageSize(nullptr) == 0, "SkMask_computeImageSize(nullptr)")) {
        return 8;
    }
    if (!check(SkMask_computeTotalImageSize(nullptr) == 0, "SkMask_computeTotalImageSize(nullptr)")) {
        return 9;
    }
    if (!check(SkMask_getAddr1(nullptr, 0, 0) == nullptr, "SkMask_getAddr1(nullptr)")) {
        return 10;
    }
    if (!check(SkMask_getAddr8(nullptr, 0, 0) == nullptr, "SkMask_getAddr8(nullptr)")) {
        return 11;
    }
    if (!check(SkMask_getAddrLCD16(nullptr, 0, 0) == nullptr, "SkMask_getAddrLCD16(nullptr)")) {
        return 12;
    }
    if (!check(SkMask_getAddr32(nullptr, 0, 0) == nullptr, "SkMask_getAddr32(nullptr)")) {
        return 13;
    }
    if (!check(SkMask_getAddr(nullptr, 0, 0) == nullptr, "SkMask_getAddr(nullptr)")) {
        return 14;
    }

    uint8_t pixels[4] = {1, 2, 3, 4};
    const sk_i_rect_t rect_handle = SkIRect_MakeXYWH(0, 0, 2, 2);
    const auto *rect = static_cast<const reskia_i_rect_t *>(static_sk_i_rect_get_ptr(rect_handle));
    const sk_mask_t mask_handle = SkMask_new(pixels, rect, 2, kA8Format);
    auto *mask = static_cast<reskia_mask_t *>(static_sk_mask_get_ptr(mask_handle));
    if (!check(mask != nullptr, "SkMask_new(valid)")) {
        static_sk_i_rect_delete(rect_handle);
        return 15;
    }
    if (!check(SkMask_fImage(mask) == pixels, "SkMask_fImage(valid)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 16;
    }
    if (!check(SkMask_fRowBytes(mask) == 2 && SkMask_fFormat(mask) == kA8Format, "SkMask fields(valid)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 17;
    }
    if (!check(SkMask_getAddr8(mask, 1, 1) == pixels + 3, "SkMask_getAddr8(valid)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 18;
    }
    if (!check(SkMask_getAddr8(mask, 2, 1) == nullptr, "SkMask_getAddr8(out of bounds)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 19;
    }
    if (!check(SkMask_getAddr1(mask, 0, 0) == nullptr, "SkMask_getAddr1(format mismatch)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 20;
    }

    if (!check(SkMaskBuilder_newWithImageBoundsRowBytesFormat(pixels, nullptr, 2, kA8Format) == nullptr, "SkMaskBuilder_newWithImageBoundsRowBytesFormat(nullptr bounds)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 21;
    }
    if (!check(SkMaskBuilder_newWithImageBoundsRowBytesFormat(pixels, rect, 2, 99) == nullptr, "SkMaskBuilder_newWithImageBoundsRowBytesFormat(invalid format)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 22;
    }
    if (!check(SkMaskBuilder_image(nullptr) == nullptr, "SkMaskBuilder_image(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 23;
    }
    if (!check(SkMaskBuilder_bounds(nullptr) == nullptr, "SkMaskBuilder_bounds(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 24;
    }
    if (!check(SkMaskBuilder_rowBytes(nullptr) == 0, "SkMaskBuilder_rowBytes(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 25;
    }
    if (!check(SkMaskBuilder_format(nullptr) == -1, "SkMaskBuilder_format(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 26;
    }
    if (!check(SkMaskBuilder_getAddr(nullptr, 0, 0) == nullptr, "SkMaskBuilder_getAddr(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 27;
    }
    if (!check(SkMaskBuilder_AllocImage(0, 0) == nullptr, "SkMaskBuilder_AllocImage(0)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 28;
    }
    if (!check(SkMaskBuilder_PrepareDestination(1, 1, nullptr) == 0, "SkMaskBuilder_PrepareDestination(nullptr)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 29;
    }

    auto *builder = SkMaskBuilder_newWithImageBoundsRowBytesFormat(pixels, rect, 2, kA8Format);
    if (!check(builder != nullptr, "SkMaskBuilder_newWithImageBoundsRowBytesFormat(valid)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 30;
    }
    if (!check(SkMaskBuilder_getAddr8(builder, 1, 1) == pixels + 3, "SkMaskBuilder_getAddr8(valid)")) {
        SkMaskBuilder_delete(builder);
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 31;
    }
    if (!check(SkMaskBuilder_getAddr32(builder, 0, 0) == nullptr, "SkMaskBuilder_getAddr32(format mismatch)")) {
        SkMaskBuilder_delete(builder);
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 32;
    }
    SkMaskBuilder_delete(builder);

    uint32_t argb[4] = {0, 1, 2, 3};
    auto *argb_builder = SkMaskBuilder_newWithImageBoundsRowBytesFormat(reinterpret_cast<uint8_t *>(argb), rect, 8, kARGB32Format);
    if (!check(argb_builder != nullptr && SkMaskBuilder_getAddr32(argb_builder, 1, 1) == argb + 3, "SkMaskBuilder_getAddr32(valid)")) {
        SkMaskBuilder_delete(argb_builder);
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 33;
    }
    SkMaskBuilder_delete(argb_builder);

    uint16_t lcd[4] = {0, 1, 2, 3};
    const sk_mask_t lcd_mask_handle = SkMask_new(reinterpret_cast<uint8_t *>(lcd), rect, 4, kLCD16Format);
    auto *lcd_mask = static_cast<reskia_mask_t *>(static_sk_mask_get_ptr(lcd_mask_handle));
    if (!check(lcd_mask != nullptr && SkMask_getAddrLCD16(lcd_mask, 1, 1) == lcd + 3, "SkMask_getAddrLCD16(valid)")) {
        static_sk_mask_delete(lcd_mask_handle);
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 34;
    }
    static_sk_mask_delete(lcd_mask_handle);

    uint8_t bw[2] = {0xff, 0x00};
    const sk_i_rect_t bw_rect_handle = SkIRect_MakeXYWH(0, 0, 8, 1);
    const auto *bw_rect = static_cast<const reskia_i_rect_t *>(static_sk_i_rect_get_ptr(bw_rect_handle));
    const sk_mask_t bw_mask_handle = SkMask_new(bw, bw_rect, 1, kBWFormat);
    auto *bw_mask = static_cast<reskia_mask_t *>(static_sk_mask_get_ptr(bw_mask_handle));
    if (!check(bw_mask != nullptr && SkMask_getAddr1(bw_mask, 7, 0) == bw, "SkMask_getAddr1(valid)")) {
        static_sk_mask_delete(bw_mask_handle);
        static_sk_i_rect_delete(bw_rect_handle);
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 35;
    }
    static_sk_mask_delete(bw_mask_handle);
    static_sk_i_rect_delete(bw_rect_handle);

    const sk_mask_builder_t prepared = SkMaskBuilder_PrepareDestination(1, 1, mask);
    if (!check(prepared != 0 && static_sk_mask_builder_get_ptr(prepared) != nullptr, "SkMaskBuilder_PrepareDestination(valid)")) {
        static_sk_mask_delete(mask_handle);
        static_sk_i_rect_delete(rect_handle);
        return 36;
    }
    static_sk_mask_builder_delete(prepared);

    static_sk_mask_delete(mask_handle);
    static_sk_i_rect_delete(rect_handle);
    return 0;
}
