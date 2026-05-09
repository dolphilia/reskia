#include "capi/sk_ref_cnt.h"
#include "capi/sk_ref_cnt_base.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[ref-cnt-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkRefCnt_release(nullptr);
    SkRefCnt_ref(nullptr);
    SkRefCnt_unref(nullptr);
    if (!check(!SkRefCnt_unique(nullptr), "SkRefCnt_unique(nullptr)")) {
        return 1;
    }

    SkRefCntBase_release(nullptr);
    SkRefCntBase_ref(nullptr);
    SkRefCntBase_unref(nullptr);
    if (!check(!SkRefCntBase_unique(nullptr), "SkRefCntBase_unique(nullptr)")) {
        return 2;
    }

    reskia_ref_cnt_base_t *base = SkRefCntBase_new();
    if (!check(base != nullptr, "SkRefCntBase_new")) {
        return 3;
    }
    if (!check(SkRefCntBase_unique(base), "SkRefCntBase_unique(new)")) {
        SkRefCntBase_release(base);
        return 4;
    }
    SkRefCntBase_ref(base);
    if (!check(!SkRefCntBase_unique(base), "SkRefCntBase_unique(after ref)")) {
        SkRefCntBase_unref(base);
        SkRefCntBase_release(base);
        return 5;
    }
    SkRefCntBase_unref(base);
    if (!check(SkRefCntBase_unique(base), "SkRefCntBase_unique(after unref)")) {
        SkRefCntBase_release(base);
        return 6;
    }
    SkRefCntBase_release(base);

    return 0;
}
