//
// Created by dolphilia on 2024/01/05.
//

#include "sk_b_box_hierarchy.h"

#include "include/core/SkBBHFactory.h"

#include "../static/static_std_vector_int_ptr.h"

#include "../static/static_std_vector_int_ptr-internal.h"

extern "C" {

void SkBBoxHierarchy_delete(void *b_box_hierarchy) {
    delete static_cast<SkBBoxHierarchy *>(b_box_hierarchy);
}

void SkBBoxHierarchy_insert(void *b_box_hierarchy, const void *rect, int N) {
    static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->insert(static_cast<const SkRect *>(rect), N);
}

void SkBBoxHierarchy_insert_2(void *b_box_hierarchy, const void *rect, const void * metadata, int N) {
    static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->insert(static_cast<const SkRect *>(rect), static_cast<const SkBBoxHierarchy::Metadata *>(metadata), N);
}

void SkBBoxHierarchy_search(void *b_box_hierarchy, const void *query, vector_int_ptr_t results) {
    static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->search(* static_cast<const SkRect *>(query), static_int_vector_ptr_move(results));
}

size_t SkBBoxHierarchy_bytesUsed(void *b_box_hierarchy) {
    return static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->bytesUsed();
}

bool SkBBoxHierarchy_unique(void *b_box_hierarchy) {
    return static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->unique();
}

void SkBBoxHierarchy_ref(void *b_box_hierarchy) {
    static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->ref();
}

void SkBBoxHierarchy_unref(void *b_box_hierarchy) {
    static_cast<SkBBoxHierarchy *>(b_box_hierarchy)->unref();
}

}