//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REF_CNT_H
#define RAIA_SKIA_SK_REF_CNT_H

#ifdef __cplusplus
extern "C" {
#endif

void SkRefCnt_release(void * refCnt); // owned: caller が保持する参照を release する。NULL 入力では no-op。
bool SkRefCnt_unique(void * ref_cnt); // NULL 入力では false。
void SkRefCnt_ref(void * ref_cnt); // retained: 参照カウントを増やす。NULL 入力では no-op。
void SkRefCnt_unref(void * ref_cnt); // owned: 参照カウントを減らす。NULL 入力では no-op。

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REF_CNT_H
