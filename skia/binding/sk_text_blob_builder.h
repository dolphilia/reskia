//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TEXT_BLOB_BUILDER_H
#define RAIA_SKIA_SK_TEXT_BLOB_BUILDER_H

typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_text_blob_builder_run_buffer_t reskia_text_blob_builder_run_buffer_t;
typedef struct reskia_text_blob_builder_t reskia_text_blob_builder_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_text_blob_builder_t *SkTextBlobBuilder_new(); // () -> SkTextBlobBuilder *
void SkTextBlobBuilder_delete(reskia_text_blob_builder_t *text_blob_builder); // (SkTextBlobBuilder *text_blob_builder)
int SkTextBlobBuilder_make(reskia_text_blob_builder_t *text_blob_builder); // (SkTextBlobBuilder *text_blob_builder) -> sk_text_blob_t
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRun(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, SkScalar x, SkScalar y, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, SkScalar y, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunText(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float x, float y, int textByteCount, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, SkScalar x, SkScalar y, int textByteCount, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPosH(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, float y, int textByteCount, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, SkScalar y, int textByteCount, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextPos(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, int textByteCount, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *
const reskia_text_blob_builder_run_buffer_t *SkTextBlobBuilder_allocRunTextRSXform(reskia_text_blob_builder_t *text_blob_builder, const reskia_font_t *font, int count, int textByteCount, const reskia_rect_t *bounds); // (SkTextBlobBuilder *text_blob_builder, const SkFont *font, int count, int textByteCount, const SkRect *bounds) -> const SkTextBlobBuilder::RunBuffer *

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TEXT_BLOB_BUILDER_H
