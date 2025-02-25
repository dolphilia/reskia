//
// Created by dolphilia on 25/02/05.
//

#include "static_sk_mesh_specification_attribute.h"

#include "static_sk_mesh_specification_attribute-internal.h"

static std::set<int> static_sk_mesh_specification_attribute_available_keys;
static std::map<int , SkSpan<const SkMeshSpecification::Attribute>> static_sk_mesh_specification_attribute;
static int static_sk_mesh_specification_attribute_index = 0;

int static_sk_mesh_specification_attribute_make(SkSpan<const SkMeshSpecification::Attribute> value) {
    int key;
    if (!static_sk_mesh_specification_attribute_available_keys.empty()) {
        auto it = static_sk_mesh_specification_attribute_available_keys.begin();
        key = *it;
        static_sk_mesh_specification_attribute_available_keys.erase(it);
    } else {
        key = static_sk_mesh_specification_attribute_index++;
    }
    static_sk_mesh_specification_attribute[key] = value;
    return key;
}

void static_sk_mesh_specification_attribute_set(int key, SkSpan<const SkMeshSpecification::Attribute> value) {
    static_sk_mesh_specification_attribute[key] = value;
}

SkSpan<const SkMeshSpecification::Attribute> static_sk_mesh_specification_attribute_get_entity(int key) {
    return static_sk_mesh_specification_attribute[key];
}

extern "C" {

void static_sk_mesh_specification_attribute_delete(int key) {
    static_sk_mesh_specification_attribute.erase(key);
    static_sk_mesh_specification_attribute_available_keys.insert(key);
}

const void * static_sk_mesh_specification_attribute_get_ptr(int key, int index) {
    return &static_sk_mesh_specification_attribute[key][index];
}

}