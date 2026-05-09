#include "capi/sk_drawable.h"
#include "capi/sk_flattenable.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[drawable-flattenable-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkFlattenable_release(nullptr);
    SkFlattenable_flatten(nullptr, nullptr);
    SkFlattenable_ref(nullptr);
    SkFlattenable_unref(nullptr);

    if (!check(SkFlattenable_getFactory(nullptr) == 0, "SkFlattenable_getFactory(nullptr)")) {
        return 1;
    }
    if (!check(SkFlattenable_getTypeName(nullptr) == nullptr, "SkFlattenable_getTypeName(nullptr)")) {
        return 2;
    }
    if (!check(SkFlattenable_getFlattenableType(nullptr) == -1, "SkFlattenable_getFlattenableType(nullptr)")) {
        return 3;
    }
    if (!check(SkFlattenable_serialize(nullptr, nullptr) == 0, "SkFlattenable_serialize(nullptr)")) {
        return 4;
    }
    if (!check(SkFlattenable_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkFlattenable_serializeToMemory(nullptr)")) {
        return 5;
    }
    if (!check(!SkFlattenable_unique(nullptr), "SkFlattenable_unique(nullptr)")) {
        return 6;
    }
    if (!check(SkFlattenable_NameToFactory(nullptr) == 0, "SkFlattenable_NameToFactory(nullptr)")) {
        return 7;
    }
    if (!check(SkFlattenable_NameToFactory("__reskia_missing_flattenable__") == 0, "SkFlattenable_NameToFactory(missing)")) {
        return 8;
    }
    if (!check(SkFlattenable_FactoryToName(0) == nullptr, "SkFlattenable_FactoryToName(0)")) {
        return 9;
    }
    SkFlattenable_Register(nullptr, 0);

    uint8_t data[1] = {0};
    if (!check(SkFlattenable_Deserialize(-1, data, sizeof(data), nullptr) == 0, "SkFlattenable_Deserialize(invalid type)")) {
        return 10;
    }
    if (!check(SkFlattenable_Deserialize(0, nullptr, sizeof(data), nullptr) == 0, "SkFlattenable_Deserialize(null data)")) {
        return 11;
    }
    if (!check(SkFlattenable_Deserialize(0, data, 0, nullptr) == 0, "SkFlattenable_Deserialize(empty data)")) {
        return 12;
    }

    SkDrawable_release(nullptr);
    SkDrawable_draw(nullptr, nullptr, nullptr);
    SkDrawable_drawAt(nullptr, nullptr, 0.0f, 0.0f);
    SkDrawable_notifyDrawingChanged(nullptr);
    SkDrawable_flatten(nullptr, nullptr);
    SkDrawable_ref(nullptr);
    SkDrawable_unref(nullptr);

    if (!check(SkDrawable_snapGpuDrawHandler(nullptr, 0, nullptr, nullptr, nullptr) == 0, "SkDrawable_snapGpuDrawHandler(nullptr)")) {
        return 13;
    }
    if (!check(SkDrawable_makePictureSnapshot(nullptr) == 0, "SkDrawable_makePictureSnapshot(nullptr)")) {
        return 14;
    }
    if (!check(SkDrawable_getGenerationID(nullptr) == 0, "SkDrawable_getGenerationID(nullptr)")) {
        return 15;
    }
    if (!check(SkDrawable_getBounds(nullptr) == 0, "SkDrawable_getBounds(nullptr)")) {
        return 16;
    }
    if (!check(SkDrawable_approximateBytesUsed(nullptr) == 0, "SkDrawable_approximateBytesUsed(nullptr)")) {
        return 17;
    }
    if (!check(SkDrawable_getFlattenableType(nullptr) == -1, "SkDrawable_getFlattenableType(nullptr)")) {
        return 18;
    }
    if (!check(SkDrawable_getFactory(nullptr) == 0, "SkDrawable_getFactory(nullptr)")) {
        return 19;
    }
    if (!check(SkDrawable_getTypeName(nullptr) == nullptr, "SkDrawable_getTypeName(nullptr)")) {
        return 20;
    }
    if (!check(SkDrawable_serialize(nullptr, nullptr) == 0, "SkDrawable_serialize(nullptr)")) {
        return 21;
    }
    if (!check(SkDrawable_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkDrawable_serializeToMemory(nullptr)")) {
        return 22;
    }
    if (!check(!SkDrawable_unique(nullptr), "SkDrawable_unique(nullptr)")) {
        return 23;
    }
    if (!check(SkDrawable_GetFlattenableType() == 2, "SkDrawable_GetFlattenableType()")) {
        return 24;
    }
    if (!check(SkDrawable_Deserialize(nullptr, sizeof(data), nullptr) == 0, "SkDrawable_Deserialize(null data)")) {
        return 25;
    }
    if (!check(SkDrawable_Deserialize(data, 0, nullptr) == 0, "SkDrawable_Deserialize(empty data)")) {
        return 26;
    }
    if (!check(SkDrawable_NameToFactory(nullptr) == 0, "SkDrawable_NameToFactory(nullptr)")) {
        return 27;
    }
    if (!check(SkDrawable_NameToFactory("__reskia_missing_drawable__") == 0, "SkDrawable_NameToFactory(missing)")) {
        return 28;
    }
    if (!check(SkDrawable_FactoryToName(0) == nullptr, "SkDrawable_FactoryToName(0)")) {
        return 29;
    }
    SkDrawable_Register(nullptr, 0);
    return 0;
}
