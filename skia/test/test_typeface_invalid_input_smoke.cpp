#include "capi/sk_typeface.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_font_style.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_typeface.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[typeface-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkTypeface_delete(nullptr);

    if (!check(SkTypeface_fontStyle(nullptr) == 0, "SkTypeface_fontStyle(nullptr)")) {
        return 1;
    }
    if (!check(!SkTypeface_isBold(nullptr), "SkTypeface_isBold(nullptr)")) {
        return 2;
    }
    if (!check(!SkTypeface_isItalic(nullptr), "SkTypeface_isItalic(nullptr)")) {
        return 3;
    }
    if (!check(!SkTypeface_isFixedPitch(nullptr), "SkTypeface_isFixedPitch(nullptr)")) {
        return 4;
    }
    if (!check(SkTypeface_getVariationDesignPosition(nullptr, nullptr, 0) == -1, "SkTypeface_getVariationDesignPosition(nullptr)")) {
        return 5;
    }
    if (!check(SkTypeface_getVariationDesignParameters(nullptr, nullptr, 0) == -1, "SkTypeface_getVariationDesignParameters(nullptr)")) {
        return 6;
    }
    if (!check(SkTypeface_uniqueID(nullptr) == 0, "SkTypeface_uniqueID(nullptr)")) {
        return 7;
    }
    if (!check(SkTypeface_makeClone(nullptr, nullptr) == 0, "SkTypeface_makeClone(nullptr)")) {
        return 8;
    }
    SkTypeface_serialize(nullptr, nullptr, 0);
    if (!check(SkTypeface_serializeToData(nullptr, 0) == 0, "SkTypeface_serializeToData(nullptr)")) {
        return 9;
    }
    if (!check(SkTypeface_textToGlyphs(nullptr, nullptr, 0, 0, nullptr, 0) == 0, "SkTypeface_textToGlyphs(nullptr)")) {
        return 10;
    }
    if (!check(SkTypeface_unicharToGlyph(nullptr, 0) == 0, "SkTypeface_unicharToGlyph(nullptr)")) {
        return 11;
    }
    if (!check(SkTypeface_countGlyphs(nullptr) == 0, "SkTypeface_countGlyphs(nullptr)")) {
        return 12;
    }
    if (!check(SkTypeface_countTables(nullptr) == 0, "SkTypeface_countTables(nullptr)")) {
        return 13;
    }
    if (!check(SkTypeface_getTableTags(nullptr, nullptr) == 0, "SkTypeface_getTableTags(nullptr)")) {
        return 14;
    }
    if (!check(SkTypeface_getTableSize(nullptr, 0) == 0, "SkTypeface_getTableSize(nullptr)")) {
        return 15;
    }
    if (!check(SkTypeface_getTableData(nullptr, 0, 0, 0, nullptr) == 0, "SkTypeface_getTableData(nullptr)")) {
        return 16;
    }
    if (!check(SkTypeface_copyTableData(nullptr, 0) == 0, "SkTypeface_copyTableData(nullptr)")) {
        return 17;
    }
    if (!check(SkTypeface_getUnitsPerEm(nullptr) == 0, "SkTypeface_getUnitsPerEm(nullptr)")) {
        return 18;
    }
    if (!check(!SkTypeface_getKerningPairAdjustments(nullptr, nullptr, 0, nullptr), "SkTypeface_getKerningPairAdjustments(nullptr)")) {
        return 19;
    }
    if (!check(SkTypeface_createFamilyNameIterator(nullptr) == nullptr, "SkTypeface_createFamilyNameIterator(nullptr)")) {
        return 20;
    }
    SkTypeface_getFamilyName(nullptr, nullptr);
    if (!check(!SkTypeface_getPostScriptName(nullptr, nullptr), "SkTypeface_getPostScriptName(nullptr)")) {
        return 21;
    }
    if (!check(SkTypeface_openStream(nullptr, nullptr) == 0, "SkTypeface_openStream(nullptr)")) {
        return 22;
    }
    if (!check(SkTypeface_openExistingStream(nullptr, nullptr) == 0, "SkTypeface_openExistingStream(nullptr)")) {
        return 23;
    }
    if (!check(SkTypeface_getBounds(nullptr) == 0, "SkTypeface_getBounds(nullptr)")) {
        return 24;
    }
    SkTypeface_filterRec(nullptr, nullptr);
    SkTypeface_getFontDescriptor(nullptr, nullptr, nullptr);
    if (!check(SkTypeface_internal_private_getCTFontRef(nullptr) == nullptr, "SkTypeface_internal_private_getCTFontRef(nullptr)")) {
        return 25;
    }
    if (!check(SkTypeface_Equal(nullptr, nullptr), "SkTypeface_Equal(nullptr, nullptr)")) {
        return 26;
    }

    if (!check(SkTypeface_MakeDeserialize(nullptr, 0) == 0, "SkTypeface_MakeDeserialize(nullptr)")) {
        return 27;
    }
    if (!check(SkTypeface_MakeFromFile(nullptr, 0) == 0, "SkTypeface_MakeFromFile(nullptr)")) {
        return 28;
    }
    if (!check(SkTypeface_MakeFromStream(0, 0) == 0, "SkTypeface_MakeFromStream(0)")) {
        return 29;
    }
    if (!check(SkTypeface_MakeFromData(0, 0) == 0, "SkTypeface_MakeFromData(0)")) {
        return 30;
    }
    if (!check(SkTypeface_MakeDeserializeWithoutFontMgr(nullptr) == 0, "SkTypeface_MakeDeserializeWithoutFontMgr(nullptr)")) {
        return 31;
    }

    const sk_typeface_t typeface_handle = SkTypeface_MakeEmpty();
    auto *typeface = static_cast<reskia_typeface_t *>(static_sk_typeface_get_ptr(typeface_handle));
    if (!check(typeface_handle != 0 && typeface != nullptr, "SkTypeface_MakeEmpty()")) {
        return 32;
    }
    if (!check(SkTypeface_uniqueID(typeface) != 0, "SkTypeface_uniqueID(valid)")) {
        static_sk_typeface_delete(typeface_handle);
        return 33;
    }

    const sk_font_style_t style_handle = SkTypeface_fontStyle(typeface);
    if (!check(style_handle != 0 && static_sk_font_style_get_ptr(style_handle) != nullptr, "SkTypeface_fontStyle(valid)")) {
        static_sk_typeface_delete(typeface_handle);
        return 34;
    }
    static_sk_font_style_delete(style_handle);

    const uint8_t text[] = {'A'};
    if (!check(SkTypeface_textToGlyphs(typeface, text, sizeof(text), 0, nullptr, 0) == 1, "SkTypeface_textToGlyphs(count only)")) {
        static_sk_typeface_delete(typeface_handle);
        return 35;
    }
    if (!check(SkTypeface_textToGlyphs(typeface, nullptr, 1, 0, nullptr, 0) == 0, "SkTypeface_textToGlyphs(null text with bytes)")) {
        static_sk_typeface_delete(typeface_handle);
        return 36;
    }

    uint16_t glyph = 0;
    int32_t adjustment = 0;
    SkTypeface_unicharsToGlyphs(typeface, nullptr, 1, &glyph);
    if (!check(!SkTypeface_getKerningPairAdjustments(typeface, &glyph, 1, nullptr), "SkTypeface_getKerningPairAdjustments(null output)")) {
        static_sk_typeface_delete(typeface_handle);
        return 37;
    }
    SkTypeface_getKerningPairAdjustments(typeface, &glyph, 1, &adjustment);

    if (!check(SkTypeface_getTableData(typeface, 0, 0, 1, nullptr) == 0, "SkTypeface_getTableData(null data with length)")) {
        static_sk_typeface_delete(typeface_handle);
        return 38;
    }

    const sk_rect_t bounds_handle = SkTypeface_getBounds(typeface);
    if (!check(bounds_handle != 0 && static_sk_rect_get_ptr(bounds_handle) != nullptr, "SkTypeface_getBounds(valid)")) {
        static_sk_typeface_delete(typeface_handle);
        return 39;
    }
    static_sk_rect_delete(bounds_handle);

    const sk_data_t data_handle = SkTypeface_serializeToData(typeface, 99);
    if (!check(data_handle == 0, "SkTypeface_serializeToData(invalid behavior)")) {
        static_sk_typeface_delete(typeface_handle);
        return 40;
    }

    static_sk_typeface_delete(typeface_handle);
    return 0;
}
