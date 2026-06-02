//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DOCUMENT_H
#define RAIA_SKIA_SK_DOCUMENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_document_t reskia_document_t;
typedef struct reskia_rect_t reskia_rect_t;

void SkDocument_release(reskia_document_t *document); // Owned reference: releases the caller-held reference. No-op for NULL input.
/**
 * Borrowed pointer; do not free. content may be NULL.
 * Returns NULL for NULL document.
 */
reskia_canvas_t * SkDocument_beginPage(reskia_document_t *document, float width, float height, const reskia_rect_t *content);
void SkDocument_endPage(reskia_document_t *document); // No-op for NULL input.
void SkDocument_close(reskia_document_t *document); // No-op for NULL input.
void SkDocument_abort(reskia_document_t *document); // No-op for NULL input.
bool SkDocument_unique(reskia_document_t *document); // Returns false for NULL input.
void SkDocument_ref(reskia_document_t *document); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkDocument_unref(reskia_document_t *document); // Releases the object by decrementing the reference count. No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DOCUMENT_H
