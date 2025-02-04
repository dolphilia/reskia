//
// Created by dolphilia on 25/02/04.
//

#include "sk_mesh.h"

#include "include/core/SkImage.h"
#include "include/core/SkMesh.h"

#include "../static/static_sk_mesh_vertex_buffer.h"
#include "../static/static_sk_mesh_index_buffer.h"
#include "../static/static_sk_mesh_child_ptr.h"
#include "../static/static_sk_mesh_specification.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_rect.h"

#include "../static/static_sk_mesh_vertex_buffer-internal.h"
#include "../static/static_sk_mesh_index_buffer-internal.h"
#include "../static/static_sk_mesh_child_ptr-internal.h"
#include "../static/static_sk_mesh_specification-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_rect-internal.h"

extern "C" {

SkMesh::Result SkMesh_Make(sk_sp<SkMeshSpecification> spec, SkMesh::Mode mode, sk_sp<SkMesh::VertexBuffer> vBuffer, size_t vertexCount, size_t vertexOffset, sk_sp<const SkData> uniforms, SkSpan<SkMesh::ChildPtr> children, const SkRect& bounds) {
    return SkMesh::Make(spec, mode, vBuffer, vertexCount, vertexOffset, uniforms, children, bounds);
}

SkMesh::Result SkMesh_MakeIndexed(sk_sp<SkMeshSpecification> spec, SkMesh::Mode mode, sk_sp<SkMesh::VertexBuffer> vBuffer, size_t vertexCount, size_t vertexOffset, sk_sp<SkMesh::IndexBuffer> iBuffer, size_t indexCount, size_t indexOffset, sk_sp<const SkData> uniforms, SkSpan<SkMesh::ChildPtr> children, const SkRect& bounds) {
    return SkMesh::MakeIndexed(spec, mode, vBuffer, vertexCount, vertexOffset, iBuffer, indexCount, indexOffset, uniforms, children, bounds);
}

sk_mesh_specification_t SkMesh_refSpec(SkMesh * mesh) {
    return static_sk_mesh_specification_make(mesh->refSpec());
}

SkMeshSpecification* SkMesh_spec(SkMesh * mesh) {
    return mesh->spec();
}

SkMesh::Mode SkMesh_mode(SkMesh * mesh) {
    return mesh->mode();
}

sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(SkMesh * mesh) {
    return static_sk_mesh_vertex_buffer_make(mesh->refVertexBuffer());
}

SkMesh::VertexBuffer* SkMesh_vertexBuffer(SkMesh * mesh) {
    return mesh->vertexBuffer();
}

size_t SkMesh_vertexOffset(SkMesh * mesh) {
    return mesh->vertexOffset();
}

size_t SkMesh_vertexCount(SkMesh * mesh) {
    return mesh->vertexCount();
}

sk_mesh_index_buffer_t SkMesh_refIndexBuffer(SkMesh * mesh) {
    return static_sk_mesh_index_buffer_make(mesh->refIndexBuffer());
}

SkMesh::IndexBuffer* SkMesh_indexBuffer(SkMesh * mesh) {
    return mesh->indexBuffer();
}

size_t SkMesh_indexOffset(SkMesh * mesh) {
    return mesh->indexOffset();
}

size_t SkMesh_indexCount(SkMesh * mesh) {
    return mesh->indexCount();
}

const_sk_data_t SkMesh_refUniforms(SkMesh * mesh) {
    return static_const_sk_data_make(mesh->refUniforms());
}

const SkData* SkMesh_uniforms(SkMesh * mesh) {
    return mesh->uniforms();
}

const_sk_mesh_child_ptr_t SkMesh_children(SkMesh * mesh) {
    return static_sk_span_const_sk_mesh_make(mesh->children());
}

sk_rect_t SkMesh_bounds(SkMesh * mesh) {
    return static_sk_rect_make(mesh->bounds());
}

bool SkMesh_isValid(SkMesh * mesh) {
    return mesh->isValid();
}

}