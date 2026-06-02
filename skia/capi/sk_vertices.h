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

void SkVertices_release(reskia_vertices_t *vertices); // Owned reference: releases the caller-held reference. No-op for NULL input.
uint32_t SkVertices_uniqueID(reskia_vertices_t *vertices); // Returns 0 for NULL input.
const reskia_rect_t *SkVertices_bounds(reskia_vertices_t *vertices); // Borrowed pointer; do not free. Returns NULL for NULL input.
size_t SkVertices_approximateSize(reskia_vertices_t *vertices); // Returns 0 for NULL input.

bool SkVertices_unique(reskia_vertices_t *vertices); // Returns false for NULL input.
void SkVertices_ref(reskia_vertices_t *vertices); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkVertices_unref(reskia_vertices_t *vertices); // Releases the object by decrementing the reference count. No-op for NULL input.
void SkVertices_deref(reskia_vertices_t *vertices); // No-op for NULL input.
bool SkVertices_refCntGreaterThan(reskia_vertices_t *vertices, int32_t threadIsolatedTestCnt); // Returns false for NULL input.

// static

/**
 * positions must contain at least vertexCount elements and be non-NULL.
 * texs and colors may be NULL. indices must be non-NULL when indexCount is greater than 0.
 * Returns 0 for invalid input or creation failure.
 */
sk_vertices_t SkVertices_MakeCopy(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors, int indexCount, const uint16_t *indices);
/**
 * positions must contain at least vertexCount elements and be non-NULL.
 * texs and colors may be NULL. Returns 0 for invalid input or creation failure.
 */
sk_vertices_t SkVertices_MakeCopyWithoutIndices(reskia_vertices_vertex_mode_t mode, int vertexCount, const reskia_point_t *positions, const reskia_point_t *texs, const reskia_color_t *colors);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_VERTICES_H
