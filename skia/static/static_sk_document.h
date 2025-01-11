//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_STATIC_SK_DOCUMENT_H
#define RAIA_SKIA_STATIC_SK_DOCUMENT_H

#include <set>
#include <map>
#include "include/docs/SkPDFDocument.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_document_t;
void static_sk_document_delete(int key);
SkDocument *static_sk_document_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_document_make(sk_sp<SkDocument> value);
void static_sk_document_set(int key, sk_sp<SkDocument> value);
sk_sp<SkDocument> static_sk_document_move(int key);

#endif //RAIA_SKIA_STATIC_SK_DOCUMENT_H
