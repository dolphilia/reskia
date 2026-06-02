//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_BASE_H
#define RAIA_SKIA_SK_REF_CNT_BASE_H

typedef struct reskia_ref_cnt_base_t reskia_ref_cnt_base_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_ref_cnt_base_t *SkRefCntBase_new(); // owned: new object that the caller is responsible for releasing.
void SkRefCntBase_release(reskia_ref_cnt_base_t *ref_cnt_base); // owned: releases the caller-held reference. No-op for NULL input.
bool SkRefCntBase_unique(reskia_ref_cnt_base_t *ref_cnt_base); // Returns false for NULL input.
void SkRefCntBase_ref(reskia_ref_cnt_base_t *ref_cnt_base); // retained: increments the reference count. No-op for NULL input.
void SkRefCntBase_unref(reskia_ref_cnt_base_t *ref_cnt_base); // owned: decrements the reference count. No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_BASE_H
