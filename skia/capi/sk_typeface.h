//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TYPEFACE_H
#define RAIA_SKIA_SK_TYPEFACE_H

#include <stddef.h>
#include <stdint.h>

#include "reskia_callback.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"

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
typedef int32_t reskia_typeface_serialize_behavior_t; // SkTypeface::SerializeBehavior
typedef int32_t reskia_typeface_text_encoding_t; // SkTextEncoding
typedef int32_t reskia_typeface_unichar_t; // SkUnichar
typedef uint32_t reskia_typeface_factory_id_t; // SkTypeface::FactoryId / SkFourByteTag
typedef sk_typeface_t (*reskia_typeface_factory_make_proc_t)(sk_stream_asset_t stream_asset, const reskia_font_arguments_t *arguments, void *user_data);

#ifdef __cplusplus
extern "C" {
#endif

void SkTypeface_delete(reskia_typeface_t *typeface); // No-op for NULL input.
sk_font_style_t SkTypeface_fontStyle(reskia_typeface_t *typeface); // Returns 0 for NULL input.
bool SkTypeface_isBold(reskia_typeface_t *typeface); // Returns false for NULL input.
bool SkTypeface_isItalic(reskia_typeface_t *typeface); // Returns false for NULL input.
bool SkTypeface_isFixedPitch(reskia_typeface_t *typeface); // Returns false for NULL input.
bool SkTypeface_isSyntheticBold(reskia_typeface_t *typeface); // Returns false for NULL input.
bool SkTypeface_isSyntheticOblique(reskia_typeface_t *typeface); // Returns false for NULL input.
/**
 * coordinates may be NULL.
 * Returns -1 for a negative count or NULL typeface.
 */
int SkTypeface_getVariationDesignPosition(reskia_typeface_t *typeface, reskia_font_arguments_variation_position_coordinate_t *coordinates, int coordinateCount);
/**
 * parameters may be NULL.
 * Returns -1 for a negative count or NULL typeface.
 */
int SkTypeface_getVariationDesignParameters(reskia_typeface_t *typeface, reskia_font_parameters_variation_axis_t *parameters, int parameterCount);
uint32_t SkTypeface_uniqueID(reskia_typeface_t *typeface); // Returns 0 for NULL input.
sk_typeface_t SkTypeface_makeClone(reskia_typeface_t *typeface, const reskia_font_arguments_t *arguments); // arguments must be non-NULL. Returns 0 for invalid input or creation failure.
/**
 * stream must be non-NULL.
 * No-op for invalid input.
 */
void SkTypeface_serialize(reskia_typeface_t *typeface, reskia_w_stream_t *stream, reskia_typeface_serialize_behavior_t behavior);
sk_data_t SkTypeface_serializeToData(reskia_typeface_t *typeface, reskia_typeface_serialize_behavior_t behavior); // Returns 0 for invalid input or creation failure.
/**
 * uni and glyphs must contain at least count elements and be non-NULL when count is greater than 0.
 * No-op for invalid input.
 */
void SkTypeface_unicharsToGlyphs(reskia_typeface_t *typeface, const int32_t *uni, int count, uint16_t *glyphs);
/**
 * text must be non-NULL when byteLength is greater than 0.
 * glyphs may be NULL. Returns 0 for invalid input.
 */
int SkTypeface_textToGlyphs(reskia_typeface_t *typeface, const void *text, size_t byteLength, reskia_typeface_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount);
uint16_t SkTypeface_unicharToGlyph(reskia_typeface_t *typeface, reskia_typeface_unichar_t unichar); // Returns 0 for NULL input.
int SkTypeface_countGlyphs(reskia_typeface_t *typeface); // Returns 0 for NULL input.
int SkTypeface_countTables(reskia_typeface_t *typeface); // Returns 0 for NULL input.
int SkTypeface_readTableTags(reskia_typeface_t *typeface, uint32_t *tags, size_t tagCount); // tags may be NULL. Returns 0 for NULL typeface.
size_t SkTypeface_getTableSize(reskia_typeface_t *typeface, uint32_t tag); // Returns 0 for NULL input.
/**
 * data must be non-NULL when length is greater than 0.
 * Returns 0 for invalid input.
 */
size_t SkTypeface_getTableData(reskia_typeface_t *typeface, uint32_t tag, size_t offset, size_t length, void *data);
sk_data_t SkTypeface_copyTableData(reskia_typeface_t *typeface, uint32_t tag); // Returns 0 for NULL input or creation failure.
int SkTypeface_getUnitsPerEm(reskia_typeface_t *typeface); // Returns 0 for NULL input.
/**
 * glyphs and adjustments may be NULL when count is 0.
 * Both must be non-NULL when count is greater than 0.
 */
bool SkTypeface_getKerningPairAdjustments(reskia_typeface_t *typeface, const uint16_t *glyphs, int count, int32_t *adjustments);
reskia_typeface_localized_strings_t *SkTypeface_createFamilyNameIterator(reskia_typeface_t *typeface); // Returns NULL for NULL input. The caller must unref the iterator.
void SkTypeface_getFamilyName(reskia_typeface_t *typeface, reskia_string_t *name); // name must be non-NULL. No-op for invalid input.
bool SkTypeface_getPostScriptName(reskia_typeface_t *typeface, reskia_string_t *name); // name must be non-NULL. Returns false for invalid input.
int SkTypeface_getResourceName(reskia_typeface_t *typeface, reskia_string_t *resourceName); // resourceName must be non-NULL. Returns -1 for invalid input.
sk_stream_asset_t SkTypeface_openStream(reskia_typeface_t *typeface, int *ttcIndex); // ttcIndex may be NULL. Returns 0 for NULL input or creation failure.
sk_stream_asset_t SkTypeface_openExistingStream(reskia_typeface_t *typeface, int *ttcIndex); // ttcIndex may be NULL. Returns 0 for NULL input or creation failure.
sk_rect_t SkTypeface_getBounds(reskia_typeface_t *typeface); // Returns 0 for NULL input.
void SkTypeface_filterRec(reskia_typeface_t *typeface, reskia_scaler_context_rec_t *rec); // rec must be non-NULL. No-op for invalid input.
void SkTypeface_getFontDescriptor(reskia_typeface_t *typeface, reskia_font_descriptor_t *desc, bool *isLocal); // desc and isLocal must be non-NULL. No-op for invalid input.
void *SkTypeface_internal_private_getCTFontRef(reskia_typeface_t *typeface); // Returns NULL for NULL input.

// static

bool SkTypeface_Equal(const reskia_typeface_t *facea, const reskia_typeface_t *faceb); // Returns true when both inputs are NULL and false when only one is NULL.
sk_typeface_t SkTypeface_MakeEmpty(); // Returns 0 on creation failure.
sk_typeface_t SkTypeface_MakeDeserialize(reskia_stream_t *stream, sk_font_mgr_t font_mgr); // stream must be non-NULL. Returns 0 on creation failure.

/**
 * Installs/replaces the process-global Reskia typeface factory for one factory id.
 * The first successful call fixes the id for the process; later calls must use the same id.
 * make receives a transferred stream asset handle; it must consume/delete it before returning.
 * NULL callback or a different id returns false and does not replace the current registration.
 */
bool SkTypeface_Register(reskia_typeface_factory_id_t id, reskia_typeface_factory_make_proc_t make, void *user_data, reskia_callback_release_proc_t release_proc);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TYPEFACE_H
