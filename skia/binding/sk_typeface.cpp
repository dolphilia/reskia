//
// Created by dolphilia on 2024/01/11.
//

#include "sk_typeface.h"

#include "include/core/SkTypeface.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkStream.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_stream_asset.h"
#include "../static/static_sk_typeface.h"
#include "../static/static_sk_font_style.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_font_mgr.h"

#include "../static/static_sk_font_mgr-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_typeface-internal.h"
#include "../static/static_sk_font_style-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_font_mgr.h"

extern "C" {

void SkTypeface_delete(void *typeface) {
    const SkTypeface* t = static_cast<SkTypeface *>(typeface);
    delete &t;
}

sk_font_style_t SkTypeface_fontStyle(void *typeface) {
    return static_sk_font_style_make(static_cast<SkTypeface *>(typeface)->fontStyle());
}

bool SkTypeface_isBold(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->isBold();
}

bool SkTypeface_isItalic(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->isItalic();
}

bool SkTypeface_isFixedPitch(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->isFixedPitch();
}

int SkTypeface_getVariationDesignPosition(void *typeface, void * coordinates, int coordinateCount) {
    return static_cast<SkTypeface *>(typeface)->getVariationDesignPosition(static_cast<SkFontArguments::VariationPosition::Coordinate *>(coordinates), coordinateCount);
}

int SkTypeface_getVariationDesignParameters(void *typeface, void * parameters, int parameterCount) {
    return static_cast<SkTypeface *>(typeface)->getVariationDesignParameters(static_cast<SkFontParameters::Variation::Axis *>(parameters), parameterCount);
}

SkTypefaceID SkTypeface_uniqueID(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->uniqueID();
}

sk_typeface_t SkTypeface_makeClone(void *typeface, const void *arguments) {
    return static_sk_typeface_make(static_cast<SkTypeface *>(typeface)->makeClone(* static_cast<const SkFontArguments *>(arguments)));
}

void SkTypeface_serialize(void *typeface, void *stream, int behavior) {
    static_cast<SkTypeface *>(typeface)->serialize(static_cast<SkWStream *>(stream), static_cast<SkTypeface::SerializeBehavior>(behavior));
}

sk_data_t SkTypeface_serialize_2(void *typeface, int behavior) {
    return static_sk_data_make(static_cast<SkTypeface *>(typeface)->serialize(static_cast<SkTypeface::SerializeBehavior>(behavior)));
}

void SkTypeface_unicharsToGlyphs(void *typeface, const void * uni, int count, void * glyphs) {
    static_cast<SkTypeface *>(typeface)->unicharsToGlyphs(static_cast<const SkUnichar *>(uni), count, static_cast<SkGlyphID *>(glyphs));
}

int SkTypeface_textToGlyphs(void *typeface, const void *text, size_t byteLength, int encoding, void * glyphs, int maxGlyphCount) {
    return static_cast<SkTypeface *>(typeface)->textToGlyphs(text, byteLength, static_cast<SkTextEncoding>(encoding), static_cast<SkGlyphID *>(glyphs), maxGlyphCount);
}

SkGlyphID SkTypeface_unicharToGlyph(void *typeface, SkUnichar unichar) {
    return static_cast<SkTypeface *>(typeface)->unicharToGlyph(unichar);
}

int SkTypeface_countGlyphs(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->countGlyphs();
}

int SkTypeface_countTables(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->countTables();
}

int SkTypeface_getTableTags(void *typeface, void * tags) {
    return static_cast<SkTypeface *>(typeface)->getTableTags(static_cast<SkFontTableTag *>(tags));
}

size_t SkTypeface_getTableSize(void *typeface, SkFontTableTag tag) {
    return static_cast<SkTypeface *>(typeface)->getTableSize(tag);
}

size_t SkTypeface_getTableData(void *typeface, SkFontTableTag tag, size_t offset, size_t length, void *data) {
    return static_cast<SkTypeface *>(typeface)->getTableData(tag, offset, length, data);
}

sk_data_t SkTypeface_copyTableData(void *typeface, SkFontTableTag tag) {
    return static_sk_data_make(static_cast<SkTypeface *>(typeface)->copyTableData(tag));
}

int SkTypeface_getUnitsPerEm(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->getUnitsPerEm();
}

bool SkTypeface_getKerningPairAdjustments(void *typeface, const void * glyphs, int count, void * adjustments) {
    return static_cast<SkTypeface *>(typeface)->getKerningPairAdjustments(static_cast<const SkGlyphID *>(glyphs), count, static_cast<int32_t *>(adjustments));
}

void * SkTypeface_createFamilyNameIterator(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->createFamilyNameIterator();
}

void SkTypeface_getFamilyName(void *typeface, void *name) {
    static_cast<SkTypeface *>(typeface)->getFamilyName(static_cast<SkString *>(name));
}

bool SkTypeface_getPostScriptName(void *typeface, void *name) {
    return static_cast<SkTypeface *>(typeface)->getPostScriptName(static_cast<SkString *>(name));
}

sk_stream_asset_t SkTypeface_openStream(void *typeface, int *ttcIndex) {
    return static_sk_stream_asset_make(static_cast<SkTypeface *>(typeface)->openStream(ttcIndex));
}

sk_stream_asset_t SkTypeface_openExistingStream(void *typeface, int *ttcIndex) {
    return static_sk_stream_asset_make(static_cast<SkTypeface *>(typeface)->openExistingStream(ttcIndex));
}

//@TODO
//std::unique_ptr<SkScalerContext> SkTypeface_createScalerContext(SkTypeface *typeface, const SkScalerContextEffects &effects, const SkDescriptor *descriptor) {
//    return typeface->createScalerContext(effects, descriptor);
//}

sk_rect_t SkTypeface_getBounds(void *typeface) {
    return static_sk_rect_make(static_cast<SkTypeface *>(typeface)->getBounds());
}

void SkTypeface_filterRec(void *typeface, void *rec) {
    static_cast<SkTypeface *>(typeface)->filterRec(static_cast<SkScalerContextRec *>(rec));
}

void SkTypeface_getFontDescriptor(void *typeface, void *desc, bool *isLocal) {
    static_cast<SkTypeface *>(typeface)->getFontDescriptor(static_cast<SkFontDescriptor *>(desc), isLocal);
}

void * SkTypeface_internal_private_getCTFontRef(void *typeface) {
    return static_cast<SkTypeface *>(typeface)->internal_private_getCTFontRef();
}

// static

bool SkTypeface_Equal(const void *facea, const void *faceb) {
    return SkTypeface::Equal(static_cast<const SkTypeface *>(facea), static_cast<const SkTypeface *>(faceb));
}

sk_typeface_t SkTypeface_MakeEmpty() {
    return static_sk_typeface_make(SkTypeface::MakeEmpty());
}

sk_typeface_t SkTypeface_MakeDeserialize(void *stream, sk_font_mgr_t font_mgr) {
    return static_sk_typeface_make(SkTypeface::MakeDeserialize(static_cast<SkStream *>(stream), static_sk_font_mgr_move(font_mgr)));
}

// TODO
// void SkTypeface_Register(SkTypeface::FactoryId id, sk_sp<SkTypeface>(*make)(std::unique_ptr<SkStreamAsset>, const SkFontArguments &)) {
//     SkTypeface::Register(id, make);
// }

#if !defined(SK_DISABLE_LEGACY_FONTMGR_REFDEFAULT)

sk_typeface_t SkTypeface_MakeDefault() {
    return static_sk_typeface_make(SkTypeface::MakeDefault());
}

sk_typeface_t SkTypeface_MakeFromName(const char familyName[], sk_font_style_t fontStyle) {
    return static_sk_typeface_make(SkTypeface::MakeFromName(familyName, static_sk_font_style_get(fontStyle)));
}

sk_typeface_t SkTypeface_MakeFromFile(const char path[], int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromFile(path, index));
}

sk_typeface_t SkTypeface_MakeFromStream(sk_stream_asset_t stream_asset, int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromStream(static_sk_stream_asset_move(stream_asset), index));
}

sk_typeface_t SkTypeface_MakeFromData(sk_data_t data, int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromData(static_sk_data_move(data), index));
}

sk_typeface_t SkTypeface_MakeDeserialize_2(void *stream) {
    return static_sk_typeface_make(SkTypeface::MakeDeserialize(static_cast<SkStream *>(stream)));
}

#endif

}