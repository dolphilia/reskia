//
// Created by dolphilia on 25/02/05.
//

#include "static_sk_mesh_specification_attribute.h"

#include "handle_table.hpp"
#include "static_sk_mesh_specification_attribute-internal.h"

static reskia::static_registry::HandleTable<SkSpan<const SkMeshSpecification::Attribute>>
    static_sk_mesh_specification_attribute;

int static_sk_mesh_specification_attribute_make(SkSpan<const SkMeshSpecification::Attribute> value) {
    return static_sk_mesh_specification_attribute.create(value);
}

void static_sk_mesh_specification_attribute_set(int key, SkSpan<const SkMeshSpecification::Attribute> value) {
    static_sk_mesh_specification_attribute.set(key, value);
}

SkSpan<const SkMeshSpecification::Attribute> static_sk_mesh_specification_attribute_get_entity(int key) {
    SkSpan<const SkMeshSpecification::Attribute>* entity = static_sk_mesh_specification_attribute.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_mesh_specification_attribute_delete(int key) {
    static_sk_mesh_specification_attribute.erase(key);
}

const void * static_sk_mesh_specification_attribute_get_ptr(int key, int index) {
    SkSpan<const SkMeshSpecification::Attribute>* entity = static_sk_mesh_specification_attribute.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
