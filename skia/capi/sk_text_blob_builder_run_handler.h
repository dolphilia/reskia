//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TEXT_BLOB_BUILDER_RUN_HANDLER_H
#define RAIA_SKIA_SK_TEXT_BLOB_BUILDER_RUN_HANDLER_H

#include "../modules/skshaper/include/SkShaper.h"
#include "../handles/static_sk_text_blob.h"
#include "../handles/static_sk_shaper_run_handler_buffer.h"
#include "../handles/static_sk_point.h"

extern "C" {
SkTextBlobBuilderRunHandler *SkTextBlobBuilderRunHandler_new(const char *utf8Text, sk_point_t offset);
void SkTextBlobBuilderRunHandler_delete(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler is no-op.
sk_text_blob_t SkTextBlobBuilderRunHandler_makeBlob(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler/result returns 0.
sk_point_t SkTextBlobBuilderRunHandler_endPoint(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler returns 0.
void SkTextBlobBuilderRunHandler_beginLine(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler is no-op.
void SkTextBlobBuilderRunHandler_runInfo(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler, const SkTextBlobBuilderRunHandler::RunInfo *run_info); // handler/run_info are required.
void SkTextBlobBuilderRunHandler_commitRunInfo(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler is no-op.
sk_shaper_run_handler_buffer_t SkTextBlobBuilderRunHandler_runBuffer(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler, const SkTextBlobBuilderRunHandler::RunInfo *run_info); // handler/run_info are required.
void SkTextBlobBuilderRunHandler_commitRunBuffer(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler, const SkTextBlobBuilderRunHandler::RunInfo *run_info); // handler/run_info are required.
void SkTextBlobBuilderRunHandler_commitLine(SkTextBlobBuilderRunHandler *text_blob_builder_run_handler); // NULL handler is no-op.
}

#endif //RAIA_SKIA_SK_TEXT_BLOB_BUILDER_RUN_HANDLER_H
