//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob.h"

#include "include/core/SkTextBlob.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_text_blob.h"

#include "../handles/static_sk_text_blob-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkTextBlob_release(reskia_text_blob_t *text_blob) {
    reinterpret_cast<SkTextBlob *>(text_blob)->unref();
}

const reskia_rect_t *SkTextBlob_bounds(reskia_text_blob_t *text_blob) {
    const SkTextBlob *t = reinterpret_cast<SkTextBlob *>(text_blob);
    return reinterpret_cast<const reskia_rect_t *>(&t->bounds());
}

uint32_t SkTextBlob_uniqueID(reskia_text_blob_t *text_blob) {
    return reinterpret_cast<SkTextBlob *>(text_blob)->uniqueID();
}

int SkTextBlob_getIntercepts(reskia_text_blob_t *text_blob, const float *bounds, float *intervals, const reskia_paint_t *paint) {
    return reinterpret_cast<SkTextBlob *>(text_blob)->getIntercepts(bounds, intervals, reinterpret_cast<const SkPaint *>(paint));
}

size_t SkTextBlob_serialize(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs, void *memory, size_t memory_size) {
    return reinterpret_cast<SkTextBlob *>(text_blob)->serialize(* reinterpret_cast<const SkSerialProcs *>(procs), memory, memory_size);
}

sk_data_t SkTextBlob_serializeToData(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkTextBlob *>(text_blob)->serialize(* reinterpret_cast<const SkSerialProcs *>(procs)));
}

bool SkTextBlob_unique(reskia_text_blob_t *text_blob) {
    return reinterpret_cast<SkTextBlob *>(text_blob)->unique();
}

void SkTextBlob_ref(reskia_text_blob_t *text_blob) {
    reinterpret_cast<SkTextBlob *>(text_blob)->ref();
}

void SkTextBlob_unref(reskia_text_blob_t *text_blob) {
    reinterpret_cast<SkTextBlob *>(text_blob)->unref();
}

void SkTextBlob_deref(reskia_text_blob_t *text_blob) {
    reinterpret_cast<SkTextBlob *>(text_blob)->deref();
}

bool SkTextBlob_refCntGreaterThan(reskia_text_blob_t *text_blob, int32_t threadIsolatedTestCnt) {
    return reinterpret_cast<SkTextBlob *>(text_blob)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_text_blob_t SkTextBlob_MakeFromText(const uint8_t *text, size_t byteLength, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromText(text, byteLength, * reinterpret_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromString(const char *string, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromString(string, * reinterpret_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosTextH(const uint8_t *text, size_t byteLength, const float *xpos, float constY, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromPosTextH(text, byteLength, xpos, constY, * reinterpret_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosText(const uint8_t *text, size_t byteLength, const reskia_point_t *pos, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromPosText(text, byteLength, reinterpret_cast<const SkPoint *>(pos), * reinterpret_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromRSXform(const uint8_t *text, size_t byteLength, const reskia_rsxform_t *xform, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromRSXform(text, byteLength, reinterpret_cast<const SkRSXform *>(xform), * reinterpret_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_text_blob_make(SkTextBlob::Deserialize(data, size, * reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
