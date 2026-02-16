//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_BASE_H
#define RAIA_SKIA_SK_REF_CNT_BASE_H

typedef struct reskia_ref_cnt_base_t reskia_ref_cnt_base_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_ref_cnt_base_t *SkRefCntBase_new(); // owned: 呼び出し側が解放責務を持つ新規オブジェクト
void SkRefCntBase_delete(reskia_ref_cnt_base_t *ref_cnt_base); // owned: caller が保持する参照を release する
bool SkRefCntBase_unique(reskia_ref_cnt_base_t *ref_cnt_base);
void SkRefCntBase_ref(reskia_ref_cnt_base_t *ref_cnt_base); // retained: 参照カウントを増やす
void SkRefCntBase_unref(reskia_ref_cnt_base_t *ref_cnt_base); // owned: 参照カウントを減らす

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_BASE_H
