//
// Created by dolphilia on 2024/01/05.
//

#include "sk_b_box_hierarchy.h"

#include "include/core/SkBBHFactory.h"

#include "../handles/static_std_vector_int_ptr.h"

#include "../handles/static_std_vector_int_ptr-internal.h"

#include <vector>

extern "C" {

void SkBBoxHierarchy_release(reskia_b_box_hierarchy_t *b_box_hierarchy) {
    if (b_box_hierarchy == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->unref();
}

void SkBBoxHierarchy_insert(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, int N) {
    if (b_box_hierarchy == nullptr || N <= 0 || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->insert(reinterpret_cast<const SkRect *>(rect), N);
}

void SkBBoxHierarchy_insert_withMetadata(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *rect, const reskia_b_box_hierarchy_metadata_t *metadata, int N) {
    if (b_box_hierarchy == nullptr || N <= 0 || rect == nullptr || metadata == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->insert(reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkBBoxHierarchy::Metadata *>(metadata), N);
}

void SkBBoxHierarchy_search(reskia_b_box_hierarchy_t *b_box_hierarchy, const reskia_rect_t *query, int results) {
    std::vector<int> *result_vector = static_int_vector_ptr_get_entity(results);
    if (b_box_hierarchy == nullptr || query == nullptr || result_vector == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->search(*reinterpret_cast<const SkRect *>(query), result_vector);
}

size_t SkBBoxHierarchy_bytesUsed(reskia_b_box_hierarchy_t *b_box_hierarchy) {
    if (b_box_hierarchy == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->bytesUsed();
}

bool SkBBoxHierarchy_unique(reskia_b_box_hierarchy_t *b_box_hierarchy) {
    if (b_box_hierarchy == nullptr) {
        return false;
    }
    return reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->unique();
}

void SkBBoxHierarchy_ref(reskia_b_box_hierarchy_t *b_box_hierarchy) {
    if (b_box_hierarchy == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->ref();
}

void SkBBoxHierarchy_unref(reskia_b_box_hierarchy_t *b_box_hierarchy) {
    if (b_box_hierarchy == nullptr) {
        return;
    }
    reinterpret_cast<SkBBoxHierarchy *>(b_box_hierarchy)->unref();
}

}
