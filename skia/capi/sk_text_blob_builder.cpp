//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob_builder.h"

#include "include/core/SkTextBlob.h"

#include "../handles/static_sk_text_blob.h"

#include "../handles/static_sk_text_blob-internal.h"

extern "C" {

reskia_text_blob_builder_t *SkTextBlobBuilder_new() {
    return reinterpret_cast<reskia_text_blob_builder_t *>(new SkTextBlobBuilder());
}

void SkTextBlobBuilder_delete(reskia_text_blob_builder_t *text_blob_builder) {
    delete reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder);
}

sk_text_blob_t SkTextBlobBuilder_make(reskia_text_blob_builder_t *text_blob_builder) {
    return static_sk_text_blob_make(reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->make());
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRun(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRun(* reinterpret_cast<const SkFont *>(font), count, x, y, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunPosH(* reinterpret_cast<const SkFont *>(font), count, y, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunPos(* reinterpret_cast<const SkFont *>(font), count, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunRSXform(* reinterpret_cast<const SkFont *>(font), count));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunText(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, int textByteCount, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunText(* reinterpret_cast<const SkFont *>(font), count, x, y, textByteCount, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, int textByteCount, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextPosH(* reinterpret_cast<const SkFont *>(font), count, y, textByteCount, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextPos(* reinterpret_cast<const SkFont *>(font), count, textByteCount, reinterpret_cast<const SkRect *>(bounds)));
}

const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds) {
    return reinterpret_cast<const reskia_text_blob_builder_run_buffer_t *>(&reinterpret_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextRSXform(* reinterpret_cast<const SkFont *>(font), count, textByteCount, reinterpret_cast<const SkRect *>(bounds)));
}

}
