//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_PDF_H
#define RAIA_SKIA_SK_PDF_H

#include "../handles/static_sk_document.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_pdf_metadata_t reskia_pdf_metadata_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkPDF_SetNodeId(reskia_canvas_t *dst, int nodeID);
sk_document_t SkPDF_MakeDocument(reskia_w_stream_t *stream, const reskia_pdf_metadata_t *metadata);
sk_document_t SkPDF_MakeDocument_2(reskia_w_stream_t *stream);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PDF_H
