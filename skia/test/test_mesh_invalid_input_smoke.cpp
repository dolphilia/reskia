#include "capi/sk_mesh.h"
#include "capi/sk_meshes.h"

#include <cstdint>
#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[mesh-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkMesh_delete(nullptr);
    ok &= check(SkMesh_refSpec(nullptr) == 0, "refSpec null mesh");
    ok &= check(SkMesh_spec(nullptr) == nullptr, "spec null mesh");
    ok &= check(SkMesh_mode(nullptr) == -1, "mode null mesh");
    ok &= check(SkMesh_refVertexBuffer(nullptr) == 0, "refVertexBuffer null mesh");
    ok &= check(SkMesh_vertexBuffer(nullptr) == nullptr, "vertexBuffer null mesh");
    ok &= check(SkMesh_vertexOffset(nullptr) == 0, "vertexOffset null mesh");
    ok &= check(SkMesh_vertexCount(nullptr) == 0, "vertexCount null mesh");
    ok &= check(SkMesh_refIndexBuffer(nullptr) == 0, "refIndexBuffer null mesh");
    ok &= check(SkMesh_indexBuffer(nullptr) == nullptr, "indexBuffer null mesh");
    ok &= check(SkMesh_indexOffset(nullptr) == 0, "indexOffset null mesh");
    ok &= check(SkMesh_indexCount(nullptr) == 0, "indexCount null mesh");
    ok &= check(SkMesh_refUniforms(nullptr) == 0, "refUniforms null mesh");
    ok &= check(SkMesh_uniforms(nullptr) == nullptr, "uniforms null mesh");
    ok &= check(SkMesh_children(nullptr) == 0, "children null mesh");
    ok &= check(SkMesh_bounds(nullptr) == 0, "bounds null mesh");
    ok &= check(!SkMesh_isValid(nullptr), "isValid null mesh");

    ok &= check(SkMesh_Make(0, 0, 0, 0, 0, 0, 0, nullptr) == 0, "Make null bounds");
    ok &= check(SkMesh_MakeIndexed(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr) == 0, "MakeIndexed null bounds");

    const uint8_t byte = 0;
    ok &= check(SkMeshes_MakeIndexBuffer(nullptr, 1) == 0, "MakeIndexBuffer null data nonzero size");
    ok &= check(SkMeshes_MakeVertexBuffer(nullptr, 1) == 0, "MakeVertexBuffer null data nonzero size");
    ok &= check(SkMeshes_MakeIndexBuffer(&byte, 1) != 0, "MakeIndexBuffer valid data");
    ok &= check(SkMeshes_MakeVertexBuffer(&byte, 1) != 0, "MakeVertexBuffer valid data");
    ok &= check(SkMeshes_CopyIndexBuffer(nullptr) == 0, "CopyIndexBuffer null");
    ok &= check(SkMeshes_CopyVertexBuffer(nullptr) == 0, "CopyVertexBuffer null");

    return ok ? 0 : 1;
}
