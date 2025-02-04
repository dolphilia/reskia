#ifndef STATIC_SK_MESH_CHILD_PTR_INTERNAL_H
#define STATIC_SK_MESH_CHILD_PTR_INTERNAL_H
#include <set>
#include <map>
#include "include/core/SkMesh.h"
int static_sk_span_sk_mesh_make(SkSpan<SkMesh::ChildPtr> value);
SkSpan<SkMesh::ChildPtr> static_sk_span_sk_mesh_get(int key);
void static_sk_span_sk_mesh_set(int key, SkSpan<SkMesh::ChildPtr> value);
//
int static_sk_span_const_sk_mesh_make(SkSpan<const SkMesh::ChildPtr> value);
SkSpan<const SkMesh::ChildPtr> static_sk_span_const_sk_mesh_get(int key);
void static_sk_span_const_sk_mesh_set(int key, SkSpan<const SkMesh::ChildPtr> value);
#endif // STATIC_SK_MESH_CHILD_PTR_INTERNAL_H
