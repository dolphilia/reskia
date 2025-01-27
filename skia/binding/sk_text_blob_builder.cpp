//
// Created by dolphilia on 2024/01/11.
//

#include "sk_text_blob_builder.h"

#include "include/core/SkTextBlob.h"

#include "../static/static_sk_text_blob.h"

#include "../static/static_sk_text_blob-internal.h"

extern "C" {

void *SkTextBlobBuilder_new() {
    return new SkTextBlobBuilder();
}

void SkTextBlobBuilder_delete(void *text_blob_builder) {
    delete static_cast<SkTextBlobBuilder *>(text_blob_builder);
}

sk_text_blob_t SkTextBlobBuilder_make(void *text_blob_builder) {
    return static_sk_text_blob_make(static_cast<SkTextBlobBuilder *>(text_blob_builder)->make());
}

const void * SkTextBlobBuilder_allocRun(void *text_blob_builder, const void *font, int count, float x, float y, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRun(* static_cast<const SkFont *>(font), count, x, y, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunPosH(void *text_blob_builder, const void *font, int count, float y, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunPosH(* static_cast<const SkFont *>(font), count, y, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunPos(void *text_blob_builder, const void *font, int count, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunPos(* static_cast<const SkFont *>(font), count, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunRSXform(void *text_blob_builder, const void *font, int count) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunRSXform(* static_cast<const SkFont *>(font), count);
}

const void * SkTextBlobBuilder_allocRunText(void *text_blob_builder, const void *font, int count, float x, float y, int textByteCount, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunText(* static_cast<const SkFont *>(font), count, x, y, textByteCount, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunTextPosH(void *text_blob_builder, const void *font, int count, float y, int textByteCount, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextPosH(* static_cast<const SkFont *>(font), count, y, textByteCount, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunTextPos(void *text_blob_builder, const void *font, int count, int textByteCount, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextPos(* static_cast<const SkFont *>(font), count, textByteCount, static_cast<const SkRect *>(bounds));
}

const void * SkTextBlobBuilder_allocRunTextRSXform(void *text_blob_builder, const void *font, int count, int textByteCount, const void *bounds) {
    return &static_cast<SkTextBlobBuilder *>(text_blob_builder)->allocRunTextRSXform(* static_cast<const SkFont *>(font), count, textByteCount, static_cast<const SkRect *>(bounds));
}

}
