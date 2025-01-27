//
// Created by dolphilia on 2024/01/10.
//

#include "sk_ref_cnt.h"

#include "include/core/SkRefCnt.h"

extern "C" {

void SkRefCnt_delete(void * refCnt) {
    delete static_cast<SkRefCnt *>(refCnt);
}

bool SkRefCnt_unique(void * ref_cnt) {
    return static_cast<SkRefCnt *>(ref_cnt)->unique();
}

void SkRefCnt_ref(void * ref_cnt) {
    static_cast<SkRefCnt *>(ref_cnt)->ref();
}

void SkRefCnt_unref(void * ref_cnt) {
    static_cast<SkRefCnt *>(ref_cnt)->unref();
}

}