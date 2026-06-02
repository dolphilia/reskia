//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_B_BOX_HIERARCHY_H
#define RAIA_SKIA_SK_B_BOX_HIERARCHY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_b_box_hierarchy_t reskia_b_box_hierarchy_t;
typedef struct reskia_b_box_hierarchy_metadata_t reskia_b_box_hierarchy_metadata_t;
typedef struct reskia_bbh_factory_t reskia_bbh_factory_t;
typedef struct reskia_rect_t reskia_rect_t;

/**
 * NULL is no-op.
 * Owned reference: releases the caller-held reference. (SkBBoxHierarchy *b_box_hierarchy)
 */
void SkBBoxHierarchy_release(reskia_b_box_hierarchy_t *b_box_hierarchy);
/**
 * N <= 0 is no-op.
 * hierarchy/rect are non-null when N > 0 (SkBBoxHierarchy *b_box_hierarchy, const SkRect *rect, int N)
 */
void SkBBoxHierarchy_insert(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, int N);
/**
 * N <= 0 is no-op.
 * hierarchy/rect/metadata are non-null when N > 0 (SkBBoxHierarchy *b_box_hierarchy, const SkRect *rect, const SkBBoxHierarchy::Metadata *metadata, int N)
 */
void SkBBoxHierarchy_insert_withMetadata(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, const reskia_b_box_hierarchy_metadata_t *metadata, int N);
/**
 * hierarchy/query and valid std::vector<int>* handle are non-null.
 * invalid input is no-op (SkBBoxHierarchy *b_box_hierarchy, const SkRect *query, std::vector<int> *results)
 */
void SkBBoxHierarchy_search(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *query, int results);
size_t SkBBoxHierarchy_bytesUsed(reskia_b_box_hierarchy_t *b_box_hierarchy); // NULL returns 0 (SkBBoxHierarchy *b_box_hierarchy) -> size_t
bool SkBBoxHierarchy_unique(reskia_b_box_hierarchy_t *b_box_hierarchy); // NULL returns false (SkBBoxHierarchy *b_box_hierarchy) -> bool
/**
 * NULL is no-op.
 * Retains the object by incrementing the reference count. (SkBBoxHierarchy *b_box_hierarchy)
 */
void SkBBoxHierarchy_ref(reskia_b_box_hierarchy_t *b_box_hierarchy);
/**
 * NULL is no-op.
 * Releases the object by decrementing the reference count. (SkBBoxHierarchy *b_box_hierarchy)
 */
void SkBBoxHierarchy_unref(reskia_b_box_hierarchy_t *b_box_hierarchy);

reskia_bbh_factory_t *SkRTreeFactory_new(); // caller-owned; release with SkRTreeFactory_delete
void SkRTreeFactory_delete(reskia_bbh_factory_t *factory); // NULL input is no-op
reskia_b_box_hierarchy_t *SkRTreeFactory_call(reskia_bbh_factory_t *factory); // owned result; release with SkBBoxHierarchy_release. NULL input returns NULL

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_B_BOX_HIERARCHY_H
