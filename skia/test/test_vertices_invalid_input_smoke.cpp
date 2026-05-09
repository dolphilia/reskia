#include "capi/sk_vertices.h"
#include "handles/static_sk_vertices.h"

#include "include/core/SkPoint.h"

#include <cstdint>
#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[vertices-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkVertices_release(nullptr);
    SkVertices_ref(nullptr);
    SkVertices_unref(nullptr);
    SkVertices_deref(nullptr);

    if (!check(SkVertices_uniqueID(nullptr) == 0, "SkVertices_uniqueID(nullptr)")) {
        return 1;
    }
    if (!check(SkVertices_bounds(nullptr) == nullptr, "SkVertices_bounds(nullptr)")) {
        return 2;
    }
    if (!check(SkVertices_approximateSize(nullptr) == 0, "SkVertices_approximateSize(nullptr)")) {
        return 3;
    }
    if (!check(!SkVertices_unique(nullptr), "SkVertices_unique(nullptr)")) {
        return 4;
    }
    if (!check(!SkVertices_refCntGreaterThan(nullptr, 0), "SkVertices_refCntGreaterThan(nullptr)")) {
        return 5;
    }
    if (!check(SkVertices_MakeCopy(0, 0, nullptr, nullptr, nullptr, 0, nullptr) == 0, "SkVertices_MakeCopy(empty)")) {
        return 6;
    }
    if (!check(SkVertices_MakeCopy(99, 3, nullptr, nullptr, nullptr, 0, nullptr) == 0, "SkVertices_MakeCopy(invalid mode)")) {
        return 7;
    }
    if (!check(SkVertices_MakeCopy(0, 3, nullptr, nullptr, nullptr, 0, nullptr) == 0, "SkVertices_MakeCopy(null positions)")) {
        return 8;
    }

    SkPoint positions[3] = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {0.0f, 1.0f},
    };
    SkPoint texs[3] = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {0.0f, 1.0f},
    };
    reskia_color_t colors[3] = {0xff000000, 0xffffffff, 0xff00ff00};
    uint16_t indices[3] = {0, 1, 2};

    const auto *position_input = reinterpret_cast<const reskia_point_t *>(positions);
    const auto *tex_input = reinterpret_cast<const reskia_point_t *>(texs);

    if (!check(SkVertices_MakeCopy(0, 3, position_input, nullptr, nullptr, 3, nullptr) == 0, "SkVertices_MakeCopy(null indices)")) {
        return 9;
    }
    if (!check(SkVertices_MakeCopy(0, 3, position_input, nullptr, nullptr, -1, indices) == 0, "SkVertices_MakeCopy(negative indices)")) {
        return 10;
    }

    const sk_vertices_t vertices_handle = SkVertices_MakeCopy(0, 3, position_input, tex_input, colors, 3, indices);
    auto *vertices = static_cast<reskia_vertices_t *>(static_sk_vertices_get_ptr(vertices_handle));
    if (!check(vertices_handle != 0 && vertices != nullptr, "SkVertices_MakeCopy(valid)")) {
        return 11;
    }
    if (!check(SkVertices_uniqueID(vertices) != 0, "SkVertices_uniqueID(valid)")) {
        static_sk_vertices_delete(vertices_handle);
        return 12;
    }
    if (!check(SkVertices_bounds(vertices) != nullptr, "SkVertices_bounds(valid)")) {
        static_sk_vertices_delete(vertices_handle);
        return 13;
    }
    if (!check(SkVertices_approximateSize(vertices) > 0, "SkVertices_approximateSize(valid)")) {
        static_sk_vertices_delete(vertices_handle);
        return 14;
    }
    if (!check(SkVertices_refCntGreaterThan(vertices, 0), "SkVertices_refCntGreaterThan(valid)")) {
        static_sk_vertices_delete(vertices_handle);
        return 15;
    }
    SkVertices_ref(vertices);
    SkVertices_unref(vertices);
    static_sk_vertices_delete(vertices_handle);

    const sk_vertices_t no_indices_handle = SkVertices_MakeCopyWithoutIndices(0, 3, position_input, nullptr, nullptr);
    if (!check(no_indices_handle != 0 && static_sk_vertices_get_ptr(no_indices_handle) != nullptr, "SkVertices_MakeCopyWithoutIndices(valid)")) {
        return 16;
    }
    static_sk_vertices_delete(no_indices_handle);
    return 0;
}
