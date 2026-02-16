//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_VERTICES_H
#define RAIA_SKIA_SK_VERTICES_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_vertices.h"

typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_vertices_t reskia_vertices_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_vertices_vertex_mode_t; // SkVertices::VertexMode

#ifdef __cplusplus
extern "C" {
#endif

void SkVertices_release(reskia_vertices_t *vertices); // owned: caller が保持する参照を release する (SkVertices *vertices)
uint32_t SkVertices_uniqueID(reskia_vertices_t *vertices); // (SkVertices *vertices) -> uint32_t
const reskia_rect_t *SkVertices_bounds(reskia_vertices_t *vertices); // borrowed: 解放不要の借用ポインタ (SkVertices *vertices) -> const SkRect *
size_t SkVertices_approximateSize(reskia_vertices_t *vertices); // (SkVertices *vertices) -> size_t

// SkVerticesPriv SkVertices_priv(SkVertices *vertices); // (SkVertices *vertices) -> SkVerticesPriv
// const SkVerticesPriv SkVertices_priv_2(SkVertices *vertices); // (SkVertices *vertices) -> const SkVerticesPriv

bool SkVertices_unique(reskia_vertices_t *vertices); // (SkVertices *vertices) -> bool
void SkVertices_ref(reskia_vertices_t *vertices); // retained: 参照カウントを増やす (SkVertices *vertices)
void SkVertices_unref(reskia_vertices_t *vertices); // owned: 参照カウントを減らす (SkVertices *vertices)
void SkVertices_deref(reskia_vertices_t *vertices); // (SkVertices *vertices)
bool SkVertices_refCntGreaterThan(reskia_vertices_t *vertices, int32_t threadIsolatedTestCnt); // (SkVertices *vertices, int32_t threadIsolatedTestCnt) -> bool

// static

sk_vertices_t SkVertices_MakeCopy(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors, int indexCount, const uint16_t *indices); // (SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[], int indexCount, const uint16_t indices[]) -> sk_vertices_t
sk_vertices_t SkVertices_MakeCopy_2(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors); // (SkVertices::VertexMode mode, int vertexCount, const SkPoint positions[], const SkPoint texs[], const SkColor colors[]) -> sk_vertices_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_VERTICES_H
