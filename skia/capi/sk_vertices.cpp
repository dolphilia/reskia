//
// Created by dolphilia on 2024/01/11.
//

#include "sk_vertices.h"

#include "include/core/SkVertices.h"

#include "../handles/static_sk_vertices.h"

#include "../handles/static_sk_vertices-internal.h"

#include <utility>

namespace {

bool is_valid_vertex_mode(reskia_vertices_vertex_mode_t mode) {
    return SkVertices::kTriangles_VertexMode <= mode && mode <= SkVertices::kLast_VertexMode;
}

sk_vertices_t make_vertices_handle(sk_sp<SkVertices> vertices) {
    if (!vertices) {
        return 0;
    }
    return static_sk_vertices_make(std::move(vertices));
}

bool can_make_vertices(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, int indexCount, const uint16_t *indices) {
    return is_valid_vertex_mode(mode) &&
           vertexCount > 0 &&
           positions != nullptr &&
           indexCount >= 0 &&
           (indexCount == 0 || indices != nullptr);
}

}  // namespace

extern "C" {

void SkVertices_release(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return;
    }
    reinterpret_cast<SkVertices *>(vertices)->unref();
}

uint32_t SkVertices_uniqueID(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkVertices *>(vertices)->uniqueID();
}

const reskia_rect_t *SkVertices_bounds(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<SkVertices *>(vertices)->bounds());
}

size_t SkVertices_approximateSize(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkVertices *>(vertices)->approximateSize();
}

bool SkVertices_unique(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return false;
    }
    return reinterpret_cast<SkVertices *>(vertices)->unique();
}

void SkVertices_ref(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return;
    }
    reinterpret_cast<SkVertices *>(vertices)->ref();
}

void SkVertices_unref(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return;
    }
    reinterpret_cast<SkVertices *>(vertices)->unref();
}

void SkVertices_deref(reskia_vertices_t *vertices) {
    if (vertices == nullptr) {
        return;
    }
    reinterpret_cast<SkVertices *>(vertices)->deref();
}

bool SkVertices_refCntGreaterThan(reskia_vertices_t *vertices, int32_t threadIsolatedTestCnt) {
    if (vertices == nullptr) {
        return false;
    }
    return reinterpret_cast<SkVertices *>(vertices)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_vertices_t SkVertices_MakeCopy(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors, int indexCount, const uint16_t *indices) {
    if (!can_make_vertices(mode, vertexCount, positions, indexCount, indices)) {
        return 0;
    }
    return make_vertices_handle(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, reinterpret_cast<const SkPoint *>(positions), reinterpret_cast<const SkPoint *>(texs), reinterpret_cast<const SkColor *>(colors), indexCount, indices));
}

sk_vertices_t SkVertices_MakeCopyWithoutIndices(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors) {
    if (!can_make_vertices(mode, vertexCount, positions, 0, nullptr)) {
        return 0;
    }
    return make_vertices_handle(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, reinterpret_cast<const SkPoint *>(positions), reinterpret_cast<const SkPoint *>(texs), reinterpret_cast<const SkColor *>(colors)));
}

}
