//
// Created by dolphilia on 2024/01/10.
//

#include "sk_ref_cnt_base.h"

#include "include/core/SkRefCnt.h"

extern "C" {

void *SkRefCntBase_new() {
    return new SkRefCntBase();
}

void SkRefCntBase_delete(void *ref_cnt_base) {
    delete static_cast<SkRefCntBase *>(ref_cnt_base);
}

bool SkRefCntBase_unique(void *ref_cnt_base) {
    return static_cast<SkRefCntBase *>(ref_cnt_base)->unique();
}

void SkRefCntBase_ref(void *ref_cnt_base) {
    static_cast<SkRefCntBase *>(ref_cnt_base)->ref();
}

void SkRefCntBase_unref(void *ref_cnt_base) {
    static_cast<SkRefCntBase *>(ref_cnt_base)->unref();
}

}