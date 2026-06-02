//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_H
#define RAIA_SKIA_SK_REF_CNT_H

#ifdef __cplusplus
extern "C" {
#endif

void SkRefCnt_release(void * refCnt); // owned: releases the caller-held reference. No-op for NULL input.
bool SkRefCnt_unique(void * ref_cnt); // Returns false for NULL input.
void SkRefCnt_ref(void * ref_cnt); // retained: increments the reference count. No-op for NULL input.
void SkRefCnt_unref(void * ref_cnt); // owned: decrements the reference count. No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_H
