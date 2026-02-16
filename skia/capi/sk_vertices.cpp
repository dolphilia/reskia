//
// Created by dolphilia on 2024/01/11.
//

#include "sk_vertices.h"

#include "include/core/SkVertices.h"

#include "../handles/static_sk_vertices.h"

#include "../handles/static_sk_vertices-internal.h"

extern "C" {

void SkVertices_release(reskia_vertices_t *vertices) {
    reinterpret_cast<SkVertices *>(vertices)->unref();
}

uint32_t SkVertices_uniqueID(reskia_vertices_t *vertices) {
    return reinterpret_cast<SkVertices *>(vertices)->uniqueID();
}

const reskia_rect_t *SkVertices_bounds(reskia_vertices_t *vertices) {
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<SkVertices *>(vertices)->bounds());
}

size_t SkVertices_approximateSize(reskia_vertices_t *vertices) {
    return reinterpret_cast<SkVertices *>(vertices)->approximateSize();
}

//SkVerticesPriv SkVertices_priv(SkVertices *vertices) {
//    return vertices->priv();
//}

//const SkVerticesPriv SkVertices_priv_2(SkVertices *vertices) {
//    return vertices->priv();
//}

bool SkVertices_unique(reskia_vertices_t *vertices) {
    return reinterpret_cast<SkVertices *>(vertices)->unique();
}

void SkVertices_ref(reskia_vertices_t *vertices) {
    reinterpret_cast<SkVertices *>(vertices)->ref();
}

void SkVertices_unref(reskia_vertices_t *vertices) {
    reinterpret_cast<SkVertices *>(vertices)->unref();
}

void SkVertices_deref(reskia_vertices_t *vertices) {
    reinterpret_cast<SkVertices *>(vertices)->deref();
}

bool SkVertices_refCntGreaterThan(reskia_vertices_t *vertices, int32_t threadIsolatedTestCnt) {
    return reinterpret_cast<SkVertices *>(vertices)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_vertices_t SkVertices_MakeCopy(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors, int indexCount, const uint16_t *indices) {
    return static_sk_vertices_make(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, reinterpret_cast<const SkPoint *>(positions), reinterpret_cast<const SkPoint *>(texs), reinterpret_cast<const SkColor *>(colors), indexCount, indices));
}

sk_vertices_t SkVertices_MakeCopy_2(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors) {
    return static_sk_vertices_make(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, reinterpret_cast<const SkPoint *>(positions), reinterpret_cast<const SkPoint *>(texs), reinterpret_cast<const SkColor *>(colors)));
}

}
