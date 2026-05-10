#include "capi/sk_shader.h"
#include "capi/sk_shaders.h"
#include "handles/static_sk_shader.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[shader-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    SkShader_release(nullptr);
    SkShader_ref(nullptr);
    SkShader_unref(nullptr);
    SkShader_flatten(nullptr, nullptr);
    SkShader_Register(nullptr, 0);

    ok &= check(!SkShader_isOpaque(nullptr), "isOpaque null");
    ok &= check(SkShader_isAImage(nullptr, nullptr, nullptr) == nullptr, "isAImage null");
    ok &= check(!SkShader_isAImageWithoutLocalMatrixAndTileModes(nullptr), "isAImage no args null");
    ok &= check(SkShader_makeWithLocalMatrix(nullptr, nullptr) == 0, "makeWithLocalMatrix null");
    ok &= check(SkShader_makeWithColorFilter(nullptr, 0) == 0, "makeWithColorFilter null");
    ok &= check(SkShader_makeWithWorkingColorSpace(nullptr, 0) == 0, "makeWithWorkingColorSpace null");
    ok &= check(SkShader_getFactory(nullptr) == 0, "getFactory null");
    ok &= check(SkShader_getTypeName(nullptr) == nullptr, "getTypeName null");
    ok &= check(SkShader_getFlattenableType(nullptr) == 0, "getFlattenableType null");
    ok &= check(SkShader_serialize(nullptr, nullptr) == 0, "serialize null");
    ok &= check(SkShader_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "serializeToMemory null");
    ok &= check(!SkShader_unique(nullptr), "unique null");
    ok &= check(SkShader_NameToFactory(nullptr) == 0, "NameToFactory null");
    ok &= check(SkShader_FactoryToName(0) == nullptr, "FactoryToName null factory");
    ok &= check(SkShader_Deserialize(0, nullptr, 0, nullptr) == 0, "Deserialize null");

    const sk_shader_t empty = SkShaders_Empty();
    ok &= check(empty != 0, "Empty returns handle");
    static_sk_shader_delete(empty);

    const sk_shader_t color = SkShaders_Color(0xff336699u);
    ok &= check(color != 0, "Color returns handle");
    static_sk_shader_delete(color);

    ok &= check(SkShaders_ColorWithColor4fAndColorSpace(nullptr, 0) == 0, "ColorWithColor4fAndColorSpace null color");
    ok &= check(SkShaders_Blend(0, 0, 0) == 0, "Blend null shaders");
    ok &= check(SkShaders_BlendWithBlender(0, 0, 0) == 0, "BlendWithBlender null shaders");
    ok &= check(SkShaders_CoordClamp(0, nullptr) == 0, "CoordClamp null subset");

    return ok ? 0 : 1;
}
