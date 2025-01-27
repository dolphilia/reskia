//
// Created by dolphilia on 2024/01/11.
//

#include "sk_vertices.h"

#include "include/core/SkVertices.h"

#include "../static/static_sk_vertices.h"

#include "../static/static_sk_vertices-internal.h"

extern "C" {

void SkVertices_delete(void * vertices) {
    const SkVertices * v = static_cast<SkVertices *>(vertices);
    delete &v;
}

uint32_t SkVertices_uniqueID(void *vertices) {
    return static_cast<SkVertices *>(vertices)->uniqueID();
}

const void * SkVertices_bounds(void *vertices) {
    return &static_cast<SkVertices *>(vertices)->bounds();
}

size_t SkVertices_approximateSize(void *vertices) {
    return static_cast<SkVertices *>(vertices)->approximateSize();
}

//SkVerticesPriv SkVertices_priv(SkVertices *vertices) {
//    return vertices->priv();
//}

//const SkVerticesPriv SkVertices_priv_2(SkVertices *vertices) {
//    return vertices->priv();
//}

bool SkVertices_unique(void *vertices) {
    return static_cast<SkVertices *>(vertices)->unique();
}

void SkVertices_ref(void *vertices) {
    static_cast<SkVertices *>(vertices)->ref();
}

void SkVertices_unref(void *vertices) {
    static_cast<SkVertices *>(vertices)->unref();
}

void SkVertices_deref(void *vertices) {
    static_cast<SkVertices *>(vertices)->deref();
}

bool SkVertices_refCntGreaterThan(void *vertices, int32_t threadIsolatedTestCnt) {
    return static_cast<SkVertices *>(vertices)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_vertices_t SkVertices_MakeCopy(int mode, int vertexCount, const void * positions, const void * texs, const void * colors, int indexCount, const void * indices) {
    return static_sk_vertices_make(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, static_cast<const SkPoint *>(positions), static_cast<const SkPoint *>(texs), static_cast<const SkColor *>(colors), indexCount, static_cast<const uint16_t *>(indices)));
}

sk_vertices_t SkVertices_MakeCopy_2(int mode, int vertexCount, const void * positions, const void * texs, const void * colors) {
    return static_sk_vertices_make(SkVertices::MakeCopy(static_cast<SkVertices::VertexMode>(mode), vertexCount, static_cast<const SkPoint *>(positions), static_cast<const SkPoint *>(texs), static_cast<const SkColor *>(colors)));
}

}
