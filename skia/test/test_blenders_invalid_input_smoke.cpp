#include "capi/sk_blenders.h"
#include "handles/static_sk_blender.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[blenders-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    const sk_blender_t arithmetic = SkBlenders_Arithmetic(0.0f, 1.0f, 0.0f, 0.0f, false);
    const bool ok = check(arithmetic != 0, "Arithmetic returns handle");
    static_sk_blender_delete(arithmetic);
    return ok ? 0 : 1;
}
