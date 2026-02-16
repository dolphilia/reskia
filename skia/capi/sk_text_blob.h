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

void SkTextBlob_release(reskia_text_blob_t *text_blob); // owned: caller が保持する参照を release する (SkTextBlob *text_blob)
const reskia_rect_t *SkTextBlob_bounds(reskia_text_blob_t *text_blob); // borrowed: 解放不要の借用ポインタ (SkTextBlob *text_blob) -> const SkRect *
uint32_t SkTextBlob_uniqueID(reskia_text_blob_t *text_blob); // (SkTextBlob *text_blob) -> uint32_t
int SkTextBlob_getIntercepts(reskia_text_blob_t *text_blob, const float *bounds, float *intervals, const reskia_paint_t *paint); // (SkTextBlob *text_blob, const SkScalar bounds[2], SkScalar intervals[], const SkPaint *paint) -> int
size_t SkTextBlob_serialize(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs, void *memory, size_t memory_size); // (SkTextBlob *text_blob, const SkSerialProcs *procs, void *memory, size_t memory_size) -> size_t
sk_data_t SkTextBlob_serializeToData(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs); // (SkTextBlob *text_blob, const SkSerialProcs *procs) -> sk_data_t
bool SkTextBlob_unique(reskia_text_blob_t *text_blob); // (SkTextBlob *text_blob) -> bool
void SkTextBlob_ref(reskia_text_blob_t *text_blob); // retained: 参照カウントを増やす (SkTextBlob *text_blob)
void SkTextBlob_unref(reskia_text_blob_t *text_blob); // owned: 参照カウントを減らす (SkTextBlob *text_blob)
void SkTextBlob_deref(reskia_text_blob_t *text_blob); // (SkTextBlob *text_blob)
bool SkTextBlob_refCntGreaterThan(reskia_text_blob_t *text_blob, int threadIsolatedTestCnt); // (SkTextBlob *text_blob, int32_t threadIsolatedTestCnt) -> bool

// static

sk_text_blob_t SkTextBlob_MakeFromText(const uint8_t *text, size_t byteLength, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding); // (const void *text, size_t byteLength, const SkFont *font, SkTextEncoding encoding) -> sk_text_blob_t
sk_text_blob_t SkTextBlob_MakeFromString(const char *string, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding); // (const char *string, const SkFont *font, SkTextEncoding encoding) -> sk_text_blob_t
sk_text_blob_t SkTextBlob_MakeFromPosTextH(const uint8_t *text, size_t byteLength, const float *xpos, float constY, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding); // (const void *text, size_t byteLength, const SkScalar xpos[], SkScalar constY, const SkFont *font, SkTextEncoding encoding) -> sk_text_blob_t
sk_text_blob_t SkTextBlob_MakeFromPosText(const uint8_t *text, size_t byteLength, const reskia_point_t *pos, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding); // (const void *text, size_t byteLength, const SkPoint pos[], const SkFont *font, SkTextEncoding encoding) -> sk_text_blob_t
sk_text_blob_t SkTextBlob_MakeFromRSXform(const uint8_t *text, size_t byteLength, const reskia_rsxform_t *xform, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding); // (const void *text, size_t byteLength, const SkRSXform xform[], const SkFont *font, SkTextEncoding encoding) -> sk_text_blob_t
sk_text_blob_t SkTextBlob_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_text_blob_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TEXT_BLOB_H
