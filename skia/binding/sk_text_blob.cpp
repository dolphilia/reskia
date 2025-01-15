//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob.h"

#include "include/core/SkTextBlob.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_text_blob.h"

#include "../static/static_sk_text_blob-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkTextBlob_delete(void *text_blob) {
    const SkTextBlob *t = static_cast<SkTextBlob *>(text_blob);
    delete &t;
}

const void * SkTextBlob_bounds(void *text_blob) {
    const SkTextBlob *t = static_cast<SkTextBlob *>(text_blob);
    return &t->bounds();
}

uint32_t SkTextBlob_uniqueID(void *text_blob) {
    return static_cast<SkTextBlob *>(text_blob)->uniqueID();
}

int SkTextBlob_getIntercepts(void *text_blob, const void * bounds, void * intervals, const void *paint) {
    return static_cast<SkTextBlob *>(text_blob)->getIntercepts(static_cast<const SkScalar *>(bounds), static_cast<SkScalar *>(intervals), static_cast<const SkPaint *>(paint));
}

size_t SkTextBlob_serialize(void *text_blob, const void *procs, void *memory, size_t memory_size) {
    return static_cast<SkTextBlob *>(text_blob)->serialize(* static_cast<const SkSerialProcs *>(procs), memory, memory_size);
}

sk_data_t SkTextBlob_serialize_2(void *text_blob, const void *procs) {
    return static_sk_data_make(static_cast<SkTextBlob *>(text_blob)->serialize(* static_cast<const SkSerialProcs *>(procs)));
}

bool SkTextBlob_unique(void *text_blob) {
    return static_cast<SkTextBlob *>(text_blob)->unique();
}

void SkTextBlob_ref(void *text_blob) {
    static_cast<SkTextBlob *>(text_blob)->ref();
}

void SkTextBlob_unref(void *text_blob) {
    static_cast<SkTextBlob *>(text_blob)->unref();
}

void SkTextBlob_deref(void *text_blob) {
    static_cast<SkTextBlob *>(text_blob)->deref();
}

bool SkTextBlob_refCntGreaterThan(void *text_blob, int32_t threadIsolatedTestCnt) {
    return static_cast<SkTextBlob *>(text_blob)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_text_blob_t SkTextBlob_MakeFromText(const void *text, size_t byteLength, const void *font, int encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromText(text, byteLength, * static_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromString(const char *string, const void *font, int encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromString(string, * static_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosTextH(const void *text, size_t byteLength, const void * xpos, float constY, const void *font, int encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromPosTextH(text, byteLength, static_cast<const SkScalar *>(xpos), constY, * static_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosText(const void *text, size_t byteLength, const void * pos, const void *font, int encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromPosText(text, byteLength, static_cast<const SkPoint *>(pos), * static_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromRSXform(const void *text, size_t byteLength, const void * xform, const void *font, int encoding) {
    return static_sk_text_blob_make(SkTextBlob::MakeFromRSXform(text, byteLength, static_cast<const SkRSXform *>(xform), * static_cast<const SkFont *>(font), static_cast<SkTextEncoding>(encoding)));
}

sk_text_blob_t SkTextBlob_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_text_blob_make(SkTextBlob::Deserialize(data, size, * static_cast<const SkDeserialProcs *>(procs)));
}

}
