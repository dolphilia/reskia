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

void SkTypeface_delete(reskia_typeface_t *typeface); // NULL 入力では no-op
sk_font_style_t SkTypeface_fontStyle(reskia_typeface_t *typeface); // NULL 入力では 0
bool SkTypeface_isBold(reskia_typeface_t *typeface); // NULL 入力では false
bool SkTypeface_isItalic(reskia_typeface_t *typeface); // NULL 入力では false
bool SkTypeface_isFixedPitch(reskia_typeface_t *typeface); // NULL 入力では false
/**
 * coordinates は NULL 許可。negative count/NULL typeface では -1
 */
int SkTypeface_getVariationDesignPosition(reskia_typeface_t *typeface, reskia_font_arguments_variation_position_coordinate_t *coordinates, int coordinateCount);
/**
 * parameters は NULL 許可。negative count/NULL typeface では -1
 */
int SkTypeface_getVariationDesignParameters(reskia_typeface_t *typeface, reskia_font_parameters_variation_axis_t *parameters, int parameterCount);
uint32_t SkTypeface_uniqueID(reskia_typeface_t *typeface); // NULL 入力では 0
sk_typeface_t SkTypeface_makeClone(reskia_typeface_t *typeface, const reskia_font_arguments_t *arguments); // arguments は非 NULL。invalid 入力や生成不能では 0
/**
 * stream は非 NULL。invalid 入力では no-op
 */
void SkTypeface_serialize(reskia_typeface_t *typeface, reskia_w_stream_t *stream, reskia_typeface_serialize_behavior_t behavior);
sk_data_t SkTypeface_serializeToData(reskia_typeface_t *typeface, reskia_typeface_serialize_behavior_t behavior); // invalid 入力や生成不能では 0
/**
 * count > 0 では uni/glyphs は count 要素以上、非 NULL。invalid 入力では no-op
 */
void SkTypeface_unicharsToGlyphs(reskia_typeface_t *typeface, const int32_t *uni, int count, uint16_t *glyphs);
/**
 * byteLength > 0 では text 非 NULL。glyphs は NULL 許可。invalid 入力では 0
 */
int SkTypeface_textToGlyphs(reskia_typeface_t *typeface, const void *text, size_t byteLength, reskia_typeface_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount);
uint16_t SkTypeface_unicharToGlyph(reskia_typeface_t *typeface, reskia_typeface_unichar_t unichar); // NULL 入力では 0
int SkTypeface_countGlyphs(reskia_typeface_t *typeface); // NULL 入力では 0
int SkTypeface_countTables(reskia_typeface_t *typeface); // NULL 入力では 0
int SkTypeface_getTableTags(reskia_typeface_t *typeface, uint32_t *tags); // tags は NULL 許可。NULL typeface では 0
size_t SkTypeface_getTableSize(reskia_typeface_t *typeface, uint32_t tag); // NULL 入力では 0
/**
 * length > 0 では data 非 NULL。invalid 入力では 0
 */
size_t SkTypeface_getTableData(reskia_typeface_t *typeface, uint32_t tag, size_t offset, size_t length, void *data);
sk_data_t SkTypeface_copyTableData(reskia_typeface_t *typeface, uint32_t tag); // NULL 入力や生成不能では 0
int SkTypeface_getUnitsPerEm(reskia_typeface_t *typeface); // NULL 入力では 0
/**
 * count == 0 では glyphs/adjustments NULL 許可。count > 0 では両方非 NULL
 */
bool SkTypeface_getKerningPairAdjustments(reskia_typeface_t *typeface, const uint16_t *glyphs, int count, int32_t *adjustments);
reskia_typeface_localized_strings_t *SkTypeface_createFamilyNameIterator(reskia_typeface_t *typeface); // NULL 入力では NULL。caller は iterator を unref する
void SkTypeface_getFamilyName(reskia_typeface_t *typeface, reskia_string_t *name); // name は非 NULL。invalid 入力では no-op
bool SkTypeface_getPostScriptName(reskia_typeface_t *typeface, reskia_string_t *name); // name は非 NULL。invalid 入力では false
int SkTypeface_getResourceName(reskia_typeface_t *typeface, reskia_string_t *resourceName); // resourceName は非 NULL。invalid 入力では -1
sk_stream_asset_t SkTypeface_openStream(reskia_typeface_t *typeface, int *ttcIndex); // ttcIndex は NULL 許可。NULL 入力や生成不能では 0
sk_stream_asset_t SkTypeface_openExistingStream(reskia_typeface_t *typeface, int *ttcIndex); // ttcIndex は NULL 許可。NULL 入力や生成不能では 0

// TODO
//std::unique_ptr<SkScalerContext> SkTypeface_createScalerContext(SkTypeface *typeface, const SkScalerContextEffects &effects, const SkDescriptor *descriptor);

sk_rect_t SkTypeface_getBounds(reskia_typeface_t *typeface); // NULL 入力では 0
void SkTypeface_filterRec(reskia_typeface_t *typeface, reskia_scaler_context_rec_t *rec); // rec は非 NULL。invalid 入力では no-op
void SkTypeface_getFontDescriptor(reskia_typeface_t *typeface, reskia_font_descriptor_t *desc, bool *isLocal); // desc/isLocal は非 NULL。invalid 入力では no-op
void *SkTypeface_internal_private_getCTFontRef(reskia_typeface_t *typeface); // NULL 入力では NULL

// static

bool SkTypeface_Equal(const reskia_typeface_t *facea, const reskia_typeface_t *faceb); // NULL 同士は true、片方 NULL は false
sk_typeface_t SkTypeface_MakeEmpty(); // 生成不能では 0
sk_typeface_t SkTypeface_MakeDeserialize(reskia_stream_t *stream, sk_font_mgr_t font_mgr); // stream は非 NULL。生成不能では 0

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
