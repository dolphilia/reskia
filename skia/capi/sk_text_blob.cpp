//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob.h"

#include "include/core/SkTextBlob.h"
#include "include/core/SkSerialProcs.h"

#include <utility>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_text_blob.h"

#include "../handles/static_sk_text_blob-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

SkTextBlob *as_text_blob(reskia_text_blob_t *text_blob) {
    return reinterpret_cast<SkTextBlob *>(text_blob);
}

const SkTextBlob *as_text_blob(const reskia_text_blob_t *text_blob) {
    return reinterpret_cast<const SkTextBlob *>(text_blob);
}

const SkFont *as_font(const reskia_font_t *font) {
    return reinterpret_cast<const SkFont *>(font);
}

const SkPaint *as_paint(const reskia_paint_t *paint) {
    return reinterpret_cast<const SkPaint *>(paint);
}

const SkSerialProcs &serial_procs_or_default(const reskia_serial_procs_t *procs) {
    static const SkSerialProcs defaultProcs;
    if (procs == nullptr) {
        return defaultProcs;
    }
    return *reinterpret_cast<const SkSerialProcs *>(procs);
}

const SkDeserialProcs &deserial_procs_or_default(const reskia_deserial_procs_t *procs) {
    static const SkDeserialProcs defaultProcs;
    if (procs == nullptr) {
        return defaultProcs;
    }
    return *reinterpret_cast<const SkDeserialProcs *>(procs);
}

bool is_valid_text_encoding(reskia_text_blob_text_encoding_t encoding) {
    return encoding >= static_cast<int32_t>(SkTextEncoding::kUTF8) &&
           encoding <= static_cast<int32_t>(SkTextEncoding::kGlyphID);
}

SkTextEncoding to_text_encoding(reskia_text_blob_text_encoding_t encoding) {
    return static_cast<SkTextEncoding>(encoding);
}

sk_text_blob_t make_text_blob_handle(sk_sp<SkTextBlob> blob) {
    if (!blob) {
        return 0;
    }
    return static_sk_text_blob_make(std::move(blob));
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

bool has_text_input(const void *text, size_t byteLength) {
    return byteLength == 0 || text != nullptr;
}

} // namespace

extern "C" {

void SkTextBlob_release(reskia_text_blob_t *text_blob) {
    SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return;
    }
    blob->unref();
}

const reskia_rect_t *SkTextBlob_bounds(reskia_text_blob_t *text_blob) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_rect_t *>(&blob->bounds());
}

uint32_t SkTextBlob_uniqueID(reskia_text_blob_t *text_blob) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return 0;
    }
    return blob->uniqueID();
}

int SkTextBlob_getIntercepts(reskia_text_blob_t *text_blob, const float *bounds, float *intervals, const reskia_paint_t *paint) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr || bounds == nullptr) {
        return 0;
    }
    return blob->getIntercepts(bounds, intervals, as_paint(paint));
}

size_t SkTextBlob_serialize(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs, void *memory, size_t memory_size) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr || (memory_size > 0 && memory == nullptr)) {
        return 0;
    }
    return blob->serialize(serial_procs_or_default(procs), memory, memory_size);
}

sk_data_t SkTextBlob_serializeToData(reskia_text_blob_t *text_blob, const reskia_serial_procs_t *procs) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return 0;
    }
    return make_data_handle(blob->serialize(serial_procs_or_default(procs)));
}

bool SkTextBlob_unique(reskia_text_blob_t *text_blob) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return false;
    }
    return blob->unique();
}

void SkTextBlob_ref(reskia_text_blob_t *text_blob) {
    SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return;
    }
    blob->ref();
}

void SkTextBlob_unref(reskia_text_blob_t *text_blob) {
    SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return;
    }
    blob->unref();
}

void SkTextBlob_deref(reskia_text_blob_t *text_blob) {
    SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return;
    }
    blob->deref();
}

bool SkTextBlob_refCntGreaterThan(reskia_text_blob_t *text_blob, int32_t threadIsolatedTestCnt) {
    const SkTextBlob *blob = as_text_blob(text_blob);
    if (blob == nullptr) {
        return false;
    }
    return blob->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_text_blob_t SkTextBlob_MakeFromText(const uint8_t *text, size_t byteLength, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    const SkFont *sourceFont = as_font(font);
    if (!has_text_input(text, byteLength) || sourceFont == nullptr || !is_valid_text_encoding(encoding)) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::MakeFromText(text, byteLength, *sourceFont, to_text_encoding(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromString(const char *string, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    const SkFont *sourceFont = as_font(font);
    if (string == nullptr || sourceFont == nullptr || !is_valid_text_encoding(encoding)) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::MakeFromString(string, *sourceFont, to_text_encoding(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosTextH(const uint8_t *text, size_t byteLength, const float *xpos, float constY, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    const SkFont *sourceFont = as_font(font);
    if (!has_text_input(text, byteLength) || (byteLength > 0 && xpos == nullptr) ||
        sourceFont == nullptr || !is_valid_text_encoding(encoding)) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::MakeFromPosTextH(text, byteLength, xpos, constY, *sourceFont, to_text_encoding(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromPosText(const uint8_t *text, size_t byteLength, const reskia_point_t *pos, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    const SkFont *sourceFont = as_font(font);
    if (!has_text_input(text, byteLength) || (byteLength > 0 && pos == nullptr) ||
        sourceFont == nullptr || !is_valid_text_encoding(encoding)) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::MakeFromPosText(text, byteLength, reinterpret_cast<const SkPoint *>(pos), *sourceFont, to_text_encoding(encoding)));
}

sk_text_blob_t SkTextBlob_MakeFromRSXform(const uint8_t *text, size_t byteLength, const reskia_rsxform_t *xform, const reskia_font_t *font, reskia_text_blob_text_encoding_t encoding) {
    const SkFont *sourceFont = as_font(font);
    if (!has_text_input(text, byteLength) || (byteLength > 0 && xform == nullptr) ||
        sourceFont == nullptr || !is_valid_text_encoding(encoding)) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::MakeFromRSXform(text, byteLength, reinterpret_cast<const SkRSXform *>(xform), *sourceFont, to_text_encoding(encoding)));
}

sk_text_blob_t SkTextBlob_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (size > 0 && data == nullptr) {
        return 0;
    }
    return make_text_blob_handle(SkTextBlob::Deserialize(data, size, deserial_procs_or_default(procs)));
}

}
