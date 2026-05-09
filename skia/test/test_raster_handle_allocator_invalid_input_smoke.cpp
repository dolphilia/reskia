#include "capi/sk_raster_handle_allocator.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[raster-handle-allocator-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkRasterHandleAllocator_delete(nullptr);
    SkRasterHandleAllocator_updateHandle(nullptr, nullptr, nullptr, nullptr);

    if (!check(!SkRasterHandleAllocator_allocHandle(nullptr, nullptr, nullptr), "allocHandle null")) {
        return 1;
    }
    if (!check(SkRasterHandleAllocator_MakeCanvas(nullptr, nullptr, nullptr, nullptr) == 0, "MakeCanvas null")) {
        return 2;
    }

    return 0;
}
