//
// Created by dolphilia on 2024/01/08.
//

#include "sk_document.h"

#include "include/core/SkDocument.h"

extern "C" {

void SkDocument_delete(reskia_document_t *document) {
    reinterpret_cast<SkDocument *>(document)->unref();
}

reskia_canvas_t * SkDocument_beginPage(reskia_document_t *document, float width, float height, const reskia_rect_t *content) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkDocument*>(document)->beginPage(width, height, reinterpret_cast<const SkRect *>(content)));
}

void SkDocument_endPage(reskia_document_t *document) {
    reinterpret_cast<SkDocument*>(document)->endPage();
}

void SkDocument_close(reskia_document_t *document) {
    reinterpret_cast<SkDocument*>(document)->close();
}

void SkDocument_abort(reskia_document_t *document) {
    reinterpret_cast<SkDocument*>(document)->abort();
}

bool SkDocument_unique(reskia_document_t *document) {
    return reinterpret_cast<SkDocument*>(document)->unique();
}

void SkDocument_ref(reskia_document_t *document) {
    reinterpret_cast<SkDocument*>(document)->ref();
}

void SkDocument_unref(reskia_document_t *document) {
    reinterpret_cast<SkDocument*>(document)->unref();
}

}
