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
#include "../static/static_sk_mesh_result.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_rect.h"

#include "../static/static_sk_mesh_vertex_buffer-internal.h"
#include "../static/static_sk_mesh_index_buffer-internal.h"
#include "../static/static_sk_mesh_child_ptr-internal.h"
#include "../static/static_sk_mesh_specification-internal.h"
#include "../static/static_sk_mesh_result-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_rect-internal.h"

extern "C" {

void SkMesh_delete(reskia_mesh_t * mesh) {
    delete reinterpret_cast<SkMesh *>(mesh);
}

sk_mesh_specification_t SkMesh_refSpec(reskia_mesh_t * mesh) {
    return static_sk_mesh_specification_make(reinterpret_cast<SkMesh *>(mesh)->refSpec());
}

reskia_mesh_specification_t * SkMesh_spec(reskia_mesh_t * mesh) {
    return reinterpret_cast<reskia_mesh_specification_t *>(reinterpret_cast<SkMesh *>(mesh)->spec());
}

reskia_mesh_mode_t SkMesh_mode(reskia_mesh_t * mesh) {
    return static_cast<reskia_mesh_mode_t>(reinterpret_cast<SkMesh *>(mesh)->mode());
}

sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(reskia_mesh_t * mesh) {
    return static_sk_mesh_vertex_buffer_make(reinterpret_cast<SkMesh *>(mesh)->refVertexBuffer());
}

reskia_mesh_vertex_buffer_t * SkMesh_vertexBuffer(reskia_mesh_t * mesh) {
    return reinterpret_cast<reskia_mesh_vertex_buffer_t *>(reinterpret_cast<SkMesh *>(mesh)->vertexBuffer());
}

size_t SkMesh_vertexOffset(reskia_mesh_t * mesh) {
    return reinterpret_cast<SkMesh *>(mesh)->vertexOffset();
}

size_t SkMesh_vertexCount(reskia_mesh_t * mesh) {
    return reinterpret_cast<SkMesh *>(mesh)->vertexCount();
}

sk_mesh_index_buffer_t SkMesh_refIndexBuffer(reskia_mesh_t * mesh) {
    return static_sk_mesh_index_buffer_make(reinterpret_cast<SkMesh *>(mesh)->refIndexBuffer());
}

reskia_mesh_index_buffer_t * SkMesh_indexBuffer(reskia_mesh_t * mesh) {
    return reinterpret_cast<reskia_mesh_index_buffer_t *>(reinterpret_cast<SkMesh *>(mesh)->indexBuffer());
}

size_t SkMesh_indexOffset(reskia_mesh_t * mesh) {
    return reinterpret_cast<SkMesh *>(mesh)->indexOffset();
}

size_t SkMesh_indexCount(reskia_mesh_t * mesh) {
    return reinterpret_cast<SkMesh *>(mesh)->indexCount();
}

const_sk_data_t SkMesh_refUniforms(reskia_mesh_t * mesh) {
    return static_const_sk_data_make(reinterpret_cast<SkMesh *>(mesh)->refUniforms());
}

const reskia_data_t * SkMesh_uniforms(reskia_mesh_t * mesh) {
    return reinterpret_cast<const reskia_data_t *>(reinterpret_cast<SkMesh *>(mesh)->uniforms());
}

const_sk_mesh_child_ptr_t SkMesh_children(reskia_mesh_t * mesh) {
    return static_const_sk_mesh_child_ptr_make(reinterpret_cast<SkMesh *>(mesh)->children());
}

sk_rect_t SkMesh_bounds(reskia_mesh_t * mesh) {
    return static_sk_rect_make(reinterpret_cast<SkMesh *>(mesh)->bounds());
}

bool SkMesh_isValid(reskia_mesh_t * mesh) {
    return reinterpret_cast<SkMesh *>(mesh)->isValid();
}

// static

sk_mesh_result_t SkMesh_Make(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds) {
    return static_sk_mesh_result_make(SkMesh::Make(static_sk_mesh_specification_get_entity(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_get_entity(vBuffer), vertexCount, vertexOffset, static_const_sk_data_get_entity(uniforms), static_sk_mesh_child_ptr_get_entity(children), * reinterpret_cast<const SkRect *>(bounds)));
}

sk_mesh_result_t SkMesh_MakeIndexed(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds) {
    return static_sk_mesh_result_make(SkMesh::MakeIndexed(static_sk_mesh_specification_get_entity(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_get_entity(vBuffer), vertexCount, vertexOffset, static_sk_mesh_index_buffer_get_entity(iBuffer), indexCount, indexOffset, static_const_sk_data_get_entity(uniforms), static_sk_mesh_child_ptr_get_entity(children), * reinterpret_cast<const SkRect *>(bounds)));
}

}
