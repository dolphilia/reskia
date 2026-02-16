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
typedef struct reskia_rect_t reskia_rect_t;

void SkBBoxHierarchy_delete(reskia_b_box_hierarchy_t *b_box_hierarchy); // owned: caller が保持する参照を release する (SkBBoxHierarchy *b_box_hierarchy)
void SkBBoxHierarchy_insert(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, int N); // borrowed: inputs are borrowed only (SkBBoxHierarchy *b_box_hierarchy, const SkRect *rect, int N)
void SkBBoxHierarchy_insert_2(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, const reskia_b_box_hierarchy_metadata_t *metadata, int N); // borrowed: inputs are borrowed only (SkBBoxHierarchy *b_box_hierarchy, const SkRect *rect, const SkBBoxHierarchy::Metadata *metadata, int N)
void SkBBoxHierarchy_search(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *query, int results); // borrowed: hierarchy/query are borrowed (SkBBoxHierarchy *b_box_hierarchy, const SkRect *query, std::vector<int> *results)
size_t SkBBoxHierarchy_bytesUsed(reskia_b_box_hierarchy_t *b_box_hierarchy); // (SkBBoxHierarchy *b_box_hierarchy) -> size_t
bool SkBBoxHierarchy_unique(reskia_b_box_hierarchy_t *b_box_hierarchy); // (SkBBoxHierarchy *b_box_hierarchy) -> bool
void SkBBoxHierarchy_ref(reskia_b_box_hierarchy_t *b_box_hierarchy); // retained: 参照カウントを増やす (SkBBoxHierarchy *b_box_hierarchy)
void SkBBoxHierarchy_unref(reskia_b_box_hierarchy_t *b_box_hierarchy); // owned: 参照カウントを減らす (SkBBoxHierarchy *b_box_hierarchy)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_B_BOX_HIERARCHY_H
