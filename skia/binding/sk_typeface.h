//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TYPEFACE_H
#define RAIA_SKIA_SK_TYPEFACE_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_font_arguments_variation_position_coordinate_t reskia_font_arguments_variation_position_coordinate_t;
typedef struct reskia_font_descriptor_t reskia_font_descriptor_t;
typedef struct reskia_font_parameters_variation_axis_t reskia_font_parameters_variation_axis_t;
typedef struct reskia_scaler_context_rec_t reskia_scaler_context_rec_t;
typedef struct reskia_stream_asset_t reskia_stream_asset_t;
typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_typeface_localized_strings_t reskia_typeface_localized_strings_t;
typedef struct reskia_typeface_t reskia_typeface_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTypeface_delete(reskia_typeface_t *typeface); // (SkTypeface *typeface)
int SkTypeface_fontStyle(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> sk_font_style_t
bool SkTypeface_isBold(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> bool
bool SkTypeface_isItalic(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> bool
bool SkTypeface_isFixedPitch(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> bool
int SkTypeface_getVariationDesignPosition(reskia_typeface_t *typeface, reskia_font_arguments_variation_position_coordinate_t *coordinates, int coordinateCount); // (SkTypeface *typeface, SkFontArguments::VariationPosition::Coordinate coordinates[], int coordinateCount) -> int
int SkTypeface_getVariationDesignParameters(reskia_typeface_t *typeface, reskia_font_parameters_variation_axis_t *parameters, int parameterCount); // (SkTypeface *typeface, SkFontParameters::Variation::Axis parameters[], int parameterCount) -> int
uint32_t SkTypeface_uniqueID(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> SkTypefaceID
int SkTypeface_makeClone(reskia_typeface_t *typeface, const reskia_font_arguments_t *arguments); // (SkTypeface *typeface, const SkFontArguments *arguments) -> sk_typeface_t
void SkTypeface_serialize(reskia_typeface_t *typeface, reskia_w_stream_t *stream, int behavior); // (SkTypeface *typeface, SkWStream *stream, SkTypeface::SerializeBehavior behavior)
int SkTypeface_serialize_2(reskia_typeface_t *typeface, int behavior); // (SkTypeface *typeface, SkTypeface::SerializeBehavior behavior) -> sk_data_t
void SkTypeface_unicharsToGlyphs(reskia_typeface_t *typeface, const int32_t *uni, int count, uint16_t *glyphs); // (SkTypeface *typeface, const SkUnichar uni[], int count, SkGlyphID glyphs[])
int SkTypeface_textToGlyphs(reskia_typeface_t *typeface, const void *text, size_t byteLength, int encoding, uint16_t *glyphs, int maxGlyphCount); // (SkTypeface *typeface, const void *text, size_t byteLength, SkTextEncoding encoding, SkGlyphID glyphs[], int maxGlyphCount) -> int
uint16_t SkTypeface_unicharToGlyph(reskia_typeface_t *typeface, int32_t unichar); // (SkTypeface *typeface, SkUnichar unichar) -> SkGlyphID
int SkTypeface_countGlyphs(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> int
int SkTypeface_countTables(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> int
int SkTypeface_getTableTags(reskia_typeface_t *typeface, uint32_t *tags); // (SkTypeface *typeface, SkFontTableTag tags[]) -> int
size_t SkTypeface_getTableSize(reskia_typeface_t *typeface, uint32_t tag); // (SkTypeface *typeface, SkFontTableTag tag) -> size_t
size_t SkTypeface_getTableData(reskia_typeface_t *typeface, uint32_t tag, size_t offset, size_t length, void *data); // (SkTypeface *typeface, SkFontTableTag tag, size_t offset, size_t length, void *data) -> size_t
int SkTypeface_copyTableData(reskia_typeface_t *typeface, uint32_t tag); // (SkTypeface *typeface, SkFontTableTag tag) -> sk_data_t
int SkTypeface_getUnitsPerEm(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> int
bool SkTypeface_getKerningPairAdjustments(reskia_typeface_t *typeface, const uint16_t *glyphs, int count, int32_t *adjustments); // (SkTypeface *typeface, const SkGlyphID glyphs[], int count, int32_t adjustments[]) -> bool
reskia_typeface_localized_strings_t *SkTypeface_createFamilyNameIterator(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> SkTypeface::LocalizedStrings *
void SkTypeface_getFamilyName(reskia_typeface_t *typeface, reskia_string_t *name); // (SkTypeface *typeface, SkString *name)
bool SkTypeface_getPostScriptName(reskia_typeface_t *typeface, reskia_string_t *name); // (SkTypeface *typeface, SkString *name) -> bool
int SkTypeface_openStream(reskia_typeface_t *typeface, int *ttcIndex); // (SkTypeface *typeface, int *ttcIndex) -> sk_stream_asset_t
int SkTypeface_openExistingStream(reskia_typeface_t *typeface, int *ttcIndex); // (SkTypeface *typeface, int *ttcIndex) -> sk_stream_asset_t

// TODO
//std::unique_ptr<SkScalerContext> SkTypeface_createScalerContext(SkTypeface *typeface, const SkScalerContextEffects &effects, const SkDescriptor *descriptor);

int SkTypeface_getBounds(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> sk_rect_t
void SkTypeface_filterRec(reskia_typeface_t *typeface, reskia_scaler_context_rec_t *rec); // (SkTypeface *typeface, SkScalerContextRec *rec)
void SkTypeface_getFontDescriptor(reskia_typeface_t *typeface, reskia_font_descriptor_t *desc, bool *isLocal); // (SkTypeface *typeface, SkFontDescriptor *desc, bool *isLocal)
void *SkTypeface_internal_private_getCTFontRef(reskia_typeface_t *typeface); // (SkTypeface *typeface) -> void *

// static

bool SkTypeface_Equal(const reskia_typeface_t *facea, const reskia_typeface_t *faceb); // (const SkTypeface *facea, const SkTypeface *faceb) -> bool
int SkTypeface_MakeEmpty(); // () -> sk_typeface_t
int SkTypeface_MakeDeserialize(reskia_stream_t *stream, int font_mgr); // (SkStream *stream, sk_font_mgr_t font_mgr) -> sk_typeface_t

// TODO
//void SkTypeface_Register(SkTypeface::FactoryId id, sk_sp<SkTypeface>(*make)(std::unique_ptr<SkStreamAsset>, const SkFontArguments &)); // (SkTypeface::FactoryId id, sk_sp<SkTypeface>(*make)(std::unique_ptr<SkStreamAsset>, const SkFontArguments &))

#if !defined(SK_DISABLE_LEGACY_FONTMGR_REFDEFAULT)

int SkTypeface_MakeDefault(); // () -> sk_typeface_t
int SkTypeface_MakeFromName(const char familyName[], int fontStyle); // (const char familyName[], sk_font_style_t fontStyle) -> sk_typeface_t
int SkTypeface_MakeFromFile(const char path[], int index); // (const char path[], int index) -> sk_typeface_t
int SkTypeface_MakeFromStream(int stream_asset, int index); // (sk_stream_asset_t stream_asset, int index) -> sk_typeface_t
int SkTypeface_MakeFromData(int data, int index); // (sk_data_t data, int index) -> sk_typeface_t
int SkTypeface_MakeDeserialize_2(reskia_stream_t *stream); // (SkStream *stream) -> sk_typeface_t

#endif

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TYPEFACE_H
