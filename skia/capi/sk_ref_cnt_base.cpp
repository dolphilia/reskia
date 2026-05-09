//
// Created by dolphilia on 2024/01/10.
//

#include "sk_ref_cnt_base.h"

#include "include/core/SkRefCnt.h"

extern "C" {

reskia_ref_cnt_base_t *SkRefCntBase_new() {
    return reinterpret_cast<reskia_ref_cnt_base_t *>(new SkRefCntBase());
}

void SkRefCntBase_release(reskia_ref_cnt_base_t *ref_cnt_base) {
    if (ref_cnt_base == nullptr) {
        return;
    }
    reinterpret_cast<SkRefCntBase *>(ref_cnt_base)->unref();
}

bool SkRefCntBase_unique(reskia_ref_cnt_base_t *ref_cnt_base) {
    if (ref_cnt_base == nullptr) {
        return false;
    }
    return reinterpret_cast<SkRefCntBase *>(ref_cnt_base)->unique();
}

void SkRefCntBase_ref(reskia_ref_cnt_base_t *ref_cnt_base) {
    if (ref_cnt_base == nullptr) {
        return;
    }
    reinterpret_cast<SkRefCntBase *>(ref_cnt_base)->ref();
}

void SkRefCntBase_unref(reskia_ref_cnt_base_t *ref_cnt_base) {
    if (ref_cnt_base == nullptr) {
        return;
    }
    reinterpret_cast<SkRefCntBase *>(ref_cnt_base)->unref();
}

}
