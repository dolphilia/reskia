#include "capi/sk_blender.h"
#include "handles/static_sk_blender.h"
#include "handles/static_sk_data.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[blender-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    SkBlender_release(nullptr);
    SkBlender_ref(nullptr);
    SkBlender_unref(nullptr);
    SkBlender_flatten(nullptr, nullptr);
    SkBlender_Register(nullptr, 0);

    ok &= check(SkBlender_getFactory(nullptr) == 0, "getFactory null");
    ok &= check(SkBlender_getTypeName(nullptr) == nullptr, "getTypeName null");
    ok &= check(SkBlender_getFlattenableType(nullptr) == 0, "getFlattenableType null");
    ok &= check(SkBlender_serialize(nullptr, nullptr) == 0, "serialize null");
    ok &= check(SkBlender_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "serializeToMemory null zero");
    ok &= check(SkBlender_serializeToMemory(nullptr, nullptr, 8, nullptr) == 0, "serializeToMemory null nonzero");
    ok &= check(!SkBlender_unique(nullptr), "unique null");
    ok &= check(SkBlender_NameToFactory(nullptr) == 0, "NameToFactory null");
    ok &= check(SkBlender_FactoryToName(0) == nullptr, "FactoryToName zero");
    ok &= check(SkBlender_FactoryToName(999999) == nullptr, "FactoryToName invalid");
    ok &= check(SkBlender_Deserialize(0, nullptr, 0, nullptr) == 0, "Deserialize null");

    const sk_blender_t mode = SkBlender_Mode(3);
    ok &= check(mode != 0, "Mode returns handle");
    if (mode != 0) {
        auto *blender = static_cast<reskia_blender_t *>(static_sk_blender_get_ptr(mode));
        ok &= check(blender != nullptr, "static_sk_blender_get_ptr");
        if (blender != nullptr) {
            ok &= check(SkBlender_getTypeName(blender) != nullptr, "getTypeName valid");
            const sk_data_t serialized = SkBlender_serialize(blender, nullptr);
            ok &= check(serialized != 0, "serialize valid");
            if (serialized != 0) {
                static_sk_data_delete(serialized);
            }
            SkBlender_ref(blender);
            SkBlender_unref(blender);
        }
        static_sk_blender_delete(mode);
    }

    return ok ? 0 : 1;
}
