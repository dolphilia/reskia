//
// Created by dolphilia on 2024/01/11.
//

#include "sk_typeface.h"

#include "include/core/SkTypeface.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkStream.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_font_mgr.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_font_mgr.h"

extern "C" {

void SkTypeface_delete(reskia_typeface_t *typeface) {
    reinterpret_cast<SkTypeface *>(typeface)->unref();
}

sk_font_style_t SkTypeface_fontStyle(reskia_typeface_t *typeface) {
    return static_sk_font_style_make(reinterpret_cast<SkTypeface *>(typeface)->fontStyle());
}

bool SkTypeface_isBold(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->isBold();
}

bool SkTypeface_isItalic(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->isItalic();
}

bool SkTypeface_isFixedPitch(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->isFixedPitch();
}

int SkTypeface_getVariationDesignPosition(reskia_typeface_t *typeface, reskia_font_arguments_variation_position_coordinate_t *coordinates, int coordinateCount) {
    return reinterpret_cast<SkTypeface *>(typeface)->getVariationDesignPosition(reinterpret_cast<SkFontArguments::VariationPosition::Coordinate *>(coordinates), coordinateCount);
}

int SkTypeface_getVariationDesignParameters(reskia_typeface_t *typeface, reskia_font_parameters_variation_axis_t *parameters, int parameterCount) {
    return reinterpret_cast<SkTypeface *>(typeface)->getVariationDesignParameters(reinterpret_cast<SkFontParameters::Variation::Axis *>(parameters), parameterCount);
}

uint32_t SkTypeface_uniqueID(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->uniqueID();
}

sk_typeface_t SkTypeface_makeClone(reskia_typeface_t *typeface, const reskia_font_arguments_t *arguments) {
    return static_sk_typeface_make(reinterpret_cast<SkTypeface *>(typeface)->makeClone(* reinterpret_cast<const SkFontArguments *>(arguments)));
}

void SkTypeface_serialize(reskia_typeface_t *typeface, reskia_w_stream_t *stream, reskia_typeface_serialize_behavior_t behavior) {
    reinterpret_cast<SkTypeface *>(typeface)->serialize(reinterpret_cast<SkWStream *>(stream), static_cast<SkTypeface::SerializeBehavior>(behavior));
}

sk_data_t SkTypeface_serializeToData(reskia_typeface_t *typeface, reskia_typeface_serialize_behavior_t behavior) {
    return static_sk_data_make(reinterpret_cast<SkTypeface *>(typeface)->serialize(static_cast<SkTypeface::SerializeBehavior>(behavior)));
}

void SkTypeface_unicharsToGlyphs(reskia_typeface_t *typeface, const int32_t *uni, int count, uint16_t *glyphs) {
    reinterpret_cast<SkTypeface *>(typeface)->unicharsToGlyphs(reinterpret_cast<const SkUnichar *>(uni), count, reinterpret_cast<SkGlyphID *>(glyphs));
}

int SkTypeface_textToGlyphs(reskia_typeface_t *typeface, const void *text, size_t byteLength, reskia_typeface_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount) {
    return reinterpret_cast<SkTypeface *>(typeface)->textToGlyphs(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkGlyphID *>(glyphs), maxGlyphCount);
}

uint16_t SkTypeface_unicharToGlyph(reskia_typeface_t *typeface, reskia_typeface_unichar_t unichar) {
    return reinterpret_cast<SkTypeface *>(typeface)->unicharToGlyph(static_cast<SkUnichar>(unichar));
}

int SkTypeface_countGlyphs(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->countGlyphs();
}

int SkTypeface_countTables(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->countTables();
}

int SkTypeface_getTableTags(reskia_typeface_t *typeface, uint32_t *tags) {
    return reinterpret_cast<SkTypeface *>(typeface)->getTableTags(reinterpret_cast<SkFontTableTag *>(tags));
}

size_t SkTypeface_getTableSize(reskia_typeface_t *typeface, uint32_t tag) {
    return reinterpret_cast<SkTypeface *>(typeface)->getTableSize(static_cast<SkFontTableTag>(tag));
}

size_t SkTypeface_getTableData(reskia_typeface_t *typeface, uint32_t tag, size_t offset, size_t length, void *data) {
    return reinterpret_cast<SkTypeface *>(typeface)->getTableData(static_cast<SkFontTableTag>(tag), offset, length, data);
}

sk_data_t SkTypeface_copyTableData(reskia_typeface_t *typeface, uint32_t tag) {
    return static_sk_data_make(reinterpret_cast<SkTypeface *>(typeface)->copyTableData(static_cast<SkFontTableTag>(tag)));
}

int SkTypeface_getUnitsPerEm(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->getUnitsPerEm();
}

bool SkTypeface_getKerningPairAdjustments(reskia_typeface_t *typeface, const uint16_t *glyphs, int count, int32_t *adjustments) {
    return reinterpret_cast<SkTypeface *>(typeface)->getKerningPairAdjustments(reinterpret_cast<const SkGlyphID *>(glyphs), count, adjustments);
}

reskia_typeface_localized_strings_t *SkTypeface_createFamilyNameIterator(reskia_typeface_t *typeface) {
    return reinterpret_cast<reskia_typeface_localized_strings_t *>(reinterpret_cast<SkTypeface *>(typeface)->createFamilyNameIterator());
}

void SkTypeface_getFamilyName(reskia_typeface_t *typeface, reskia_string_t *name) {
    reinterpret_cast<SkTypeface *>(typeface)->getFamilyName(reinterpret_cast<SkString *>(name));
}

bool SkTypeface_getPostScriptName(reskia_typeface_t *typeface, reskia_string_t *name) {
    return reinterpret_cast<SkTypeface *>(typeface)->getPostScriptName(reinterpret_cast<SkString *>(name));
}

sk_stream_asset_t SkTypeface_openStream(reskia_typeface_t *typeface, int *ttcIndex) {
    return static_sk_stream_asset_make(reinterpret_cast<SkTypeface *>(typeface)->openStream(ttcIndex));
}

sk_stream_asset_t SkTypeface_openExistingStream(reskia_typeface_t *typeface, int *ttcIndex) {
    return static_sk_stream_asset_make(reinterpret_cast<SkTypeface *>(typeface)->openExistingStream(ttcIndex));
}

//@TODO
//std::unique_ptr<SkScalerContext> SkTypeface_createScalerContext(SkTypeface *typeface, const SkScalerContextEffects &effects, const SkDescriptor *descriptor) {
//    return typeface->createScalerContext(effects, descriptor);
//}

sk_rect_t SkTypeface_getBounds(reskia_typeface_t *typeface) {
    return static_sk_rect_make(reinterpret_cast<SkTypeface *>(typeface)->getBounds());
}

void SkTypeface_filterRec(reskia_typeface_t *typeface, reskia_scaler_context_rec_t *rec) {
    reinterpret_cast<SkTypeface *>(typeface)->filterRec(reinterpret_cast<SkScalerContextRec *>(rec));
}

void SkTypeface_getFontDescriptor(reskia_typeface_t *typeface, reskia_font_descriptor_t *desc, bool *isLocal) {
    reinterpret_cast<SkTypeface *>(typeface)->getFontDescriptor(reinterpret_cast<SkFontDescriptor *>(desc), isLocal);
}

void *SkTypeface_internal_private_getCTFontRef(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface)->internal_private_getCTFontRef();
}

// static

bool SkTypeface_Equal(const reskia_typeface_t *facea, const reskia_typeface_t *faceb) {
    return SkTypeface::Equal(reinterpret_cast<const SkTypeface *>(facea), reinterpret_cast<const SkTypeface *>(faceb));
}

sk_typeface_t SkTypeface_MakeEmpty() {
    return static_sk_typeface_make(SkTypeface::MakeEmpty());
}

sk_typeface_t SkTypeface_MakeDeserialize(reskia_stream_t *stream, sk_font_mgr_t font_mgr) {
    return static_sk_typeface_make(SkTypeface::MakeDeserialize(reinterpret_cast<SkStream *>(stream), static_sk_font_mgr_get_entity(font_mgr)));
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
    return static_sk_typeface_make(SkTypeface::MakeFromName(familyName, static_sk_font_style_get_entity(fontStyle)));
}

sk_typeface_t SkTypeface_MakeFromFile(const char path[], int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromFile(path, index));
}

sk_typeface_t SkTypeface_MakeFromStream(sk_stream_asset_t stream_asset, int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromStream(static_sk_stream_asset_take_entity(stream_asset), index));
}

sk_typeface_t SkTypeface_MakeFromData(sk_data_t data, int index) {
    return static_sk_typeface_make(SkTypeface::MakeFromData(static_sk_data_get_entity(data), index));
}

sk_typeface_t SkTypeface_MakeDeserializeWithoutFontMgr(reskia_stream_t *stream) {
    return static_sk_typeface_make(SkTypeface::MakeDeserialize(reinterpret_cast<SkStream *>(stream)));
}

#endif

}
