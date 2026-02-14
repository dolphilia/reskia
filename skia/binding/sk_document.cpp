//
// Created by dolphilia on 2024/01/08.
//

#include "sk_document.h"

#include "include/core/SkDocument.h"

extern "C" {

void SkDocument_delete(void *document) {
    static_cast<SkDocument *>(document)->unref();
}

void * SkDocument_beginPage(void * document, float width, float height, const void *content) {
    return static_cast<SkDocument*>(document)->beginPage(width, height, static_cast<const SkRect *>(content));
}

void SkDocument_endPage(void *document) {
    static_cast<SkDocument*>(document)->endPage();
}

void SkDocument_close(void *document) {
    static_cast<SkDocument*>(document)->close();
}

void SkDocument_abort(void *document) {
    static_cast<SkDocument*>(document)->abort();
}

bool SkDocument_unique(void *document) {
    return static_cast<SkDocument*>(document)->unique();
}

void SkDocument_ref(void *document) {
    static_cast<SkDocument*>(document)->ref();
}

void SkDocument_unref(void *document) {
    static_cast<SkDocument*>(document)->unref();
}

}
