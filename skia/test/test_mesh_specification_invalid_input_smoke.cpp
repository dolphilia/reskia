#include "capi/sk_mesh_specification.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[mesh-specification-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkMeshSpecification_delete(nullptr);
    ok &= check(SkMeshSpecification_attributes(nullptr) == 0, "attributes null spec");
    ok &= check(SkMeshSpecification_uniformSize(nullptr) == 0, "uniformSize null spec");
    ok &= check(SkMeshSpecification_uniforms(nullptr) == 0, "uniforms null spec");
    ok &= check(SkMeshSpecification_children(nullptr) == 0, "children null spec");
    ok &= check(SkMeshSpecification_findChild(nullptr, nullptr) == nullptr, "findChild null spec and name");
    ok &= check(SkMeshSpecification_findUniform(nullptr, nullptr) == nullptr, "findUniform null spec and name");
    ok &= check(SkMeshSpecification_findAttribute(nullptr, nullptr) == nullptr, "findAttribute null spec and name");
    ok &= check(SkMeshSpecification_findVarying(nullptr, nullptr) == nullptr, "findVarying null spec and name");
    ok &= check(SkMeshSpecification_stride(nullptr) == 0, "stride null spec");

    ok &= check(SkMeshSpecification_Make(nullptr, 0, nullptr, nullptr, nullptr) == 0, "Make null inputs");
    ok &= check(SkMeshSpecification_MakeWithColorSpace(nullptr, 0, nullptr, nullptr, nullptr, nullptr) == 0, "MakeWithColorSpace null inputs");
    ok &= check(SkMeshSpecification_MakeWithColorSpaceAndAlphaType(nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0) == 0, "MakeWithColorSpaceAndAlphaType null inputs");

    return ok ? 0 : 1;
}
