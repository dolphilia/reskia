#include "capi/sk_auto_canvas_restore.h"
#include "capi/sk_b_box_hierarchy.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[auto-canvas-restore-bbox-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkAutoCanvasRestore_restore(nullptr);
    SkAutoCanvasRestore_delete(nullptr);

    void *restore_guard = SkAutoCanvasRestore_new(nullptr, true);
    if (!check(restore_guard != nullptr, "SkAutoCanvasRestore_new(nullptr)")) {
        return 1;
    }
    SkAutoCanvasRestore_restore(restore_guard);
    SkAutoCanvasRestore_restore(restore_guard);
    SkAutoCanvasRestore_delete(restore_guard);

    SkBBoxHierarchy_release(nullptr);
    SkBBoxHierarchy_insert(nullptr, nullptr, 1);
    SkBBoxHierarchy_insert(nullptr, nullptr, 0);
    SkBBoxHierarchy_insert_withMetadata(nullptr, nullptr, nullptr, 1);
    SkBBoxHierarchy_insert_withMetadata(nullptr, nullptr, nullptr, 0);
    SkBBoxHierarchy_search(nullptr, nullptr, 0);
    if (!check(SkBBoxHierarchy_bytesUsed(nullptr) == 0, "SkBBoxHierarchy_bytesUsed(nullptr)")) {
        return 2;
    }
    if (!check(!SkBBoxHierarchy_unique(nullptr), "SkBBoxHierarchy_unique(nullptr)")) {
        return 3;
    }
    SkBBoxHierarchy_ref(nullptr);
    SkBBoxHierarchy_unref(nullptr);
    if (!check(SkRTreeFactory_call(nullptr) == nullptr, "SkRTreeFactory_call(nullptr)")) {
        return 4;
    }
    auto *factory = SkRTreeFactory_new();
    if (!check(factory != nullptr, "SkRTreeFactory_new")) {
        return 5;
    }
    auto *hierarchy = SkRTreeFactory_call(factory);
    if (!check(hierarchy != nullptr, "SkRTreeFactory_call(valid)")) {
        SkRTreeFactory_delete(factory);
        return 6;
    }
    SkBBoxHierarchy_release(hierarchy);
    SkRTreeFactory_delete(factory);

    return 0;
}
