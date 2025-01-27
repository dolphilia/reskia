//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_VERTICES_H
#define RAIA_SKIA_SK_VERTICES_H

#include "include/core/SkVertices.h"
#include "../static/static_sk_vertices.h"

extern "C" {

void SkVertices_delete(SkVertices *vertices); // (SkVertices *vertices)
uint32_t SkVertices_uniqueID(SkVertices *vertices); // (SkVertices *vertices) -> uint32_t
const SkRect * SkVertices_bounds(SkVertices *vertices); // (SkVertices *vertices) -> const SkRect *
size_t SkVertices_approximateSize(SkVertices *vertices); // (SkVertices *vertices) -> size_t

// SkVerticesPriv SkVertices_priv(SkVertices *vertices); // (SkVertices *vertices) -> SkVerticesPriv
// const SkVerticesPriv SkVertices_priv_2(SkVertices *vertices); // (SkVertices *vertices) -> const SkVerticesPriv

bool SkVertices_unique(SkVertices *vertices); // (SkVertices *vertices) -> bool
void SkVertices_ref(SkVertices *vertices); // (SkVertices *vertices)
void SkVertices_unref(SkVertices *vertices); // (SkVertices *vertices)
void SkVertices_deref(SkVertices *vertices); // (SkVertices *vertices)
bool SkVertices_refCntGreaterThan(SkVertices *vertices, int32_t threadIsolatedTestCnt); // (SkVertices *vertices, int32_t threadIsolatedTestCnt) -> bool

// static

sk_vertices_t SkVertices_MakeCopy(SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[], int indexCount, const uint16_t indices[]); // (SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[], int indexCount, const uint16_t indices[]) -> sk_vertices_t
sk_vertices_t SkVertices_MakeCopy_2(SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[]); // (SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[]) -> sk_vertices_t

}

#endif //RAIA_SKIA_SK_VERTICES_H
