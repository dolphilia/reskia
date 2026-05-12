//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TEXT_BLOB_H
#define RAIA_SKIA_SK_TEXT_BLOB_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_text_blob.h"

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_text_blob_t reskia_text_blob_t;
typedef int32_t reskia_text_blob_text_encoding_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTextBlob_release(reskia_text_blob_t *text_blob); // owned: caller が保持する参照を release する。NULL text_blob は no-op。
const reskia_rect_t *SkTextBlob_bounds(reskia_text_blob_t *text_blob); // borrowed: 解放不要の借用ポインタ。NULL text_blob returns NULL.
uint32_t SkTextBlob_uniqueID(reskia_text_blob_t *text_blob); // (SkTextBlob *text_blob) -> uint32_t. NULL text_blob returns 0.
/**
 * bounds[2] is required.
 * intervals/paint may be NULL. Invalid input returns 0.
 */
int SkTextBlob_getIntercepts(reskia_text_blob_t *text_blob, const float *bounds, float *intervals, const reskia_paint_t *paint);
/**
 * procs may be NULL for default procs.
 * memory_size > 0 requires memory. Invalid input returns 0.
 */
size_t SkTextBlob_serialize(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs, void *memory, size_t memory_size);
/**
 * procs may be NULL for default procs. NULL/missing data returns 0.
 */
sk_data_t SkTextBlob_serializeToData(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs);
bool SkTextBlob_unique(reskia_text_blob_t *text_blob); // (SkTextBlob *text_blob) -> bool. NULL text_blob returns false.
void SkTextBlob_ref(reskia_text_blob_t *text_blob); // retained: 参照カウントを増やす。NULL text_blob は no-op。
void SkTextBlob_unref(reskia_text_blob_t *text_blob); // owned: 参照カウントを減らす。NULL text_blob は no-op。
void SkTextBlob_deref(reskia_text_blob_t *text_blob); // NULL text_blob is no-op.
bool SkTextBlob_refCntGreaterThan(reskia_text_blob_t *text_blob, int threadIsolatedTestCnt); // NULL text_blob returns false.

// static

/**
 * byteLength == 0 permits NULL text.
 * byteLength > 0 requires readable text bytes.
 * font and valid SkTextEncoding range are required. Failed creation returns 0.
 */
sk_text_blob_t SkTextBlob_MakeFromText(const uint8_t *text, size_t byteLength, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding);
/**
 * string/font are non-null.
 * encoding must be in SkTextEncoding range. Failed creation returns 0.
 */
sk_text_blob_t SkTextBlob_MakeFromString(const char *string, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding);
/**
 * byteLength == 0 permits NULL text/xpos.
 * byteLength > 0 requires readable text bytes and xpos entries.
 * font and valid SkTextEncoding range are required.
 */
sk_text_blob_t SkTextBlob_MakeFromPosTextH(const uint8_t *text, size_t byteLength, const float *xpos, float constY, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding);
/**
 * byteLength == 0 permits NULL text/pos.
 * byteLength > 0 requires readable text bytes and position entries.
 * font and valid SkTextEncoding range are required.
 */
sk_text_blob_t SkTextBlob_MakeFromPosText(const uint8_t *text, size_t byteLength, const reskia_point_t *pos, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding);
/**
 * byteLength == 0 permits NULL text/xform.
 * byteLength > 0 requires readable text bytes and xform entries.
 * font and valid SkTextEncoding range are required.
 */
sk_text_blob_t SkTextBlob_MakeFromRSXform(const uint8_t *text, size_t byteLength, const reskia_rsxform_t *xform, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding);
/**
 * size > 0 requires data.
 * procs may be NULL for default procs. Failed creation returns 0.
 */
sk_text_blob_t SkTextBlob_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TEXT_BLOB_H
