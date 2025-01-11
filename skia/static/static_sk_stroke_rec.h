//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_STROKE_REC_H
#define RAIA_SKIA_STATIC_SK_STROKE_REC_H

#include <set>
#include <map>
#include "include/core/SkStrokeRec.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_stroke_rec_t;
void static_sk_stroke_rec_delete(int key);
void * static_sk_stroke_rec_get_ptr(int key); // -> SkStrokeRec *
#ifdef __cplusplus
}
#endif

int static_sk_stroke_rec_make(SkStrokeRec value);
SkStrokeRec static_sk_stroke_rec_get(int key);
void static_sk_stroke_rec_set(int key, SkStrokeRec value);

#endif //RAIA_SKIA_STATIC_SK_STROKE_REC_H
