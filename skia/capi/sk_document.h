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

void SkDocument_delete(reskia_document_t *document); // owned: caller が保持する参照を release する (SkDocument *document)
reskia_canvas_t * SkDocument_beginPage(reskia_document_t *document, float width, float height, const reskia_rect_t *content); // borrowed: 解放不要の借用ポインタ (SkDocument *document, SkScalar width, SkScalar height, const SkRect *content) -> SkCanvas *
void SkDocument_endPage(reskia_document_t *document); // (SkDocument *document)
void SkDocument_close(reskia_document_t *document); // (SkDocument *document)
void SkDocument_abort(reskia_document_t *document); // (SkDocument *document)
bool SkDocument_unique(reskia_document_t *document); // (SkDocument *document) -> bool
void SkDocument_ref(reskia_document_t *document); // retained: 参照カウントを増やす (SkDocument *document)
void SkDocument_unref(reskia_document_t *document); // owned: 参照カウントを減らす (SkDocument *document)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DOCUMENT_H
