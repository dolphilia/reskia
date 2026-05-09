//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob_builder.h"

#include "include/core/SkTextBlob.h"

#include <utility>

#include "../handles/static_sk_text_blob.h"

#include "../handles/static_sk_text_blob-internal.h"

namespace {

SkTextBlobBuilder *as_builder(reskia_text_blob_builder_t *text_blob_builder) {
    return reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder);
}

const SkFont *as_font(const reskia_font_t *font) {
    return reinterpret_cast<const SkFont *>(font);
}

const SkRect *as_bounds(const reskia_rect_t *bounds) {
    return reinterpret_cast<const SkRect *>(bounds);
}

sk_text_blob_t make_text_blob_handle(sk_sp<SkTextBlob> blob) {
    if (!blob) {
        return 0;
    }
    return static_sk_text_blob_make(std::move(blob));
}

bool has_run_inputs(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count) {
    return text_blob_builder != nullptr && font != nullptr && count > 0;
}

bool has_text_run_inputs(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount) {
    return has_run_inputs(text_blob_builder, font, count) && textByteCount >= 0;
}

} // namespace

extern "C" {

reskia_text_blob_builder_t *SkTextBlobBuilder_new() {
    return reinterpret_cast<reskia_text_blob_builder_t *>(new SkTextBlobBuilder());
}

void SkTextBlobBuilder_delete(reskia_text_blob_builder_t *text_blob_builder) {
    delete as_builder(text_blob_builder);
}

sk_text_blob_t SkTextBlobBuilder_make(reskia_text_blob_builder_t *text_blob_builder) {
    SkTextBlobBuilder *builder = as_builder(text_blob_builder);
    if (builder == nullptr) {
        return 0;
    }
    return make_text_blob_handle(builder->make());
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRun(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, const reskia_rect_t *bounds) {
    if (!has_run_inputs(text_blob_builder, font, count)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRun(*as_font(font), count, x, y, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, const reskia_rect_t *bounds) {
    if (!has_run_inputs(text_blob_builder, font, count)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunPosH(*as_font(font), count, y, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, const reskia_rect_t *bounds) {
    if (!has_run_inputs(text_blob_builder, font, count)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunPos(*as_font(font), count, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count) {
    if (!has_run_inputs(text_blob_builder, font, count)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunRSXform(*as_font(font), count));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunText(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, int textByteCount, const reskia_rect_t *bounds) {
    if (!has_text_run_inputs(text_blob_builder, font, count, textByteCount)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunText(*as_font(font), count, x, y, textByteCount, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, int textByteCount, const reskia_rect_t *bounds) {
    if (!has_text_run_inputs(text_blob_builder, font, count, textByteCount)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunTextPosH(*as_font(font), count, y, textByteCount, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds) {
    if (!has_text_run_inputs(text_blob_builder, font, count, textByteCount)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunTextPos(*as_font(font), count, textByteCount, as_bounds(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds) {
    if (!has_text_run_inputs(text_blob_builder, font, count, textByteCount)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(
            &as_builder(text_blob_builder)->allocRunTextRSXform(*as_font(font), count, textByteCount, as_bounds(bounds)));
}

}
