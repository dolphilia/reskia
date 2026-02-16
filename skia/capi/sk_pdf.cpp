//
// Created by dolphilia on 2024/01/13.
//

#include "sk_pdf.h"

#include "include/docs/SkPDFDocument.h"

extern "C" {

void SkPDF_SetNodeId(reskia_canvas_t *dst, int nodeID) {
    SkPDF::SetNodeId(reinterpret_cast<SkCanvas *>(dst), nodeID);
}

sk_document_t SkPDF_MakeDocument(reskia_w_stream_t *stream, const reskia_pdf_metadata_t *metadata) {
    return static_sk_document_make(SkPDF::MakeDocument(
        reinterpret_cast<SkWStream *>(stream),
        *reinterpret_cast<const SkPDF::Metadata *>(metadata)));
}

sk_document_t SkPDF_MakeDocument_2(reskia_w_stream_t *stream) {
    return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream)));
}

}
