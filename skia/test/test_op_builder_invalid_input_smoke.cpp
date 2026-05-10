#include "capi/sk_op_builder.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[op-builder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkOpBuilder_delete(nullptr);
    SkOpBuilder_add(nullptr, nullptr, 0);
    SkOpBuilder_add(nullptr, nullptr, -1);
    SkOpBuilder_add(nullptr, nullptr, 5);
    ok &= check(!SkOpBuilder_resolve(nullptr, nullptr), "resolve null builder and result");

    return ok ? 0 : 1;
}
