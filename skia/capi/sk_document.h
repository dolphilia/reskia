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

void SkDocument_release(reskia_document_t *document); // owned: caller が保持する参照を release する。NULL 入力では no-op
/**
 * borrowed: 解放不要の借用ポインタ。content は NULL 許可。NULL document では NULL
 */
reskia_canvas_t * SkDocument_beginPage(reskia_document_t *document, float width, float height, const reskia_rect_t *content);
void SkDocument_endPage(reskia_document_t *document); // NULL 入力では no-op
void SkDocument_close(reskia_document_t *document); // NULL 入力では no-op
void SkDocument_abort(reskia_document_t *document); // NULL 入力では no-op
bool SkDocument_unique(reskia_document_t *document); // NULL 入力では false
void SkDocument_ref(reskia_document_t *document); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkDocument_unref(reskia_document_t *document); // owned: 参照カウントを減らす。NULL 入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DOCUMENT_H
