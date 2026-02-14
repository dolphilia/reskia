//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_BASE_H
#define RAIA_SKIA_SK_REF_CNT_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

void *SkRefCntBase_new(); // owned: 呼び出し側が解放責務を持つ新規オブジェクト
void SkRefCntBase_delete(void *ref_cnt_base); // owned: caller が保持する参照を release する
bool SkRefCntBase_unique(void *ref_cnt_base);
void SkRefCntBase_ref(void *ref_cnt_base); // retained: 参照カウントを増やす
void SkRefCntBase_unref(void *ref_cnt_base); // owned: 参照カウントを減らす

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_BASE_H
