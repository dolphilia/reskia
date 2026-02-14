//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_H
#define RAIA_SKIA_SK_REF_CNT_H

#ifdef __cplusplus
extern "C" {
#endif

void SkRefCnt_delete(void * refCnt); // owned: caller が保持する参照を release する (SkRefCnt* refCnt)
bool SkRefCnt_unique(void * ref_cnt); // (SkRefCnt* ref_cnt) -> bool
void SkRefCnt_ref(void * ref_cnt); // retained: 参照カウントを増やす (SkRefCnt* ref_cnt)
void SkRefCnt_unref(void * ref_cnt); // owned: 参照カウントを減らす (SkRefCnt* ref_cnt)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_H
