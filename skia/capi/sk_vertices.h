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

void SkVertices_release(reskia_vertices_t *vertices); // owned: caller が保持する参照を release する。NULL 入力では no-op
uint32_t SkVertices_uniqueID(reskia_vertices_t *vertices); // NULL 入力では 0
const reskia_rect_t *SkVertices_bounds(reskia_vertices_t *vertices); // borrowed: 解放不要。NULL 入力では NULL
size_t SkVertices_approximateSize(reskia_vertices_t *vertices); // NULL 入力では 0

// SkVerticesPriv SkVertices_priv(SkVertices *vertices); // (SkVertices *vertices) -> SkVerticesPriv
// const SkVerticesPriv SkVertices_priv_2(SkVertices *vertices); // (SkVertices *vertices) -> const SkVerticesPriv

bool SkVertices_unique(reskia_vertices_t *vertices); // NULL 入力では false
void SkVertices_ref(reskia_vertices_t *vertices); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkVertices_unref(reskia_vertices_t *vertices); // owned: 参照カウントを減らす。NULL 入力では no-op
void SkVertices_deref(reskia_vertices_t *vertices); // NULL 入力では no-op
bool SkVertices_refCntGreaterThan(reskia_vertices_t *vertices, int32_t threadIsolatedTestCnt); // NULL 入力では false

// static

/**
 * positions は vertexCount 要素以上、非 NULL。texs/colors は NULL 許可。indices は indexCount > 0 で非 NULL。invalid 入力や生成不能では 0
 */
sk_vertices_t SkVertices_MakeCopy(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors, int indexCount, const uint16_t *indices);
/**
 * positions は vertexCount 要素以上、非 NULL。texs/colors は NULL 許可。invalid 入力や生成不能では 0
 */
sk_vertices_t SkVertices_MakeCopyWithoutIndices(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_VERTICES_H
