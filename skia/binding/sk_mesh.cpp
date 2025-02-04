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

void SkMesh_delete(void * mesh) {
    delete static_cast<SkMesh *>(mesh);
}

sk_mesh_specification_t SkMesh_refSpec(void * mesh) {
    return static_sk_mesh_specification_make(static_cast<SkMesh *>(mesh)->refSpec());
}

void * SkMesh_spec(void * mesh) {
    return static_cast<SkMesh *>(mesh)->spec();
}

int SkMesh_mode(void * mesh) {
    return static_cast<int>(static_cast<SkMesh *>(mesh)->mode());
}

sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(void * mesh) {
    return static_sk_mesh_vertex_buffer_make(static_cast<SkMesh *>(mesh)->refVertexBuffer());
}

void * SkMesh_vertexBuffer(void * mesh) {
    return static_cast<SkMesh *>(mesh)->vertexBuffer();
}

size_t SkMesh_vertexOffset(void * mesh) {
    return static_cast<SkMesh *>(mesh)->vertexOffset();
}

size_t SkMesh_vertexCount(void * mesh) {
    return static_cast<SkMesh *>(mesh)->vertexCount();
}

sk_mesh_index_buffer_t SkMesh_refIndexBuffer(void * mesh) {
    return static_sk_mesh_index_buffer_make(static_cast<SkMesh *>(mesh)->refIndexBuffer());
}

void * SkMesh_indexBuffer(void * mesh) {
    return static_cast<SkMesh *>(mesh)->indexBuffer();
}

size_t SkMesh_indexOffset(void * mesh) {
    return static_cast<SkMesh *>(mesh)->indexOffset();
}

size_t SkMesh_indexCount(void * mesh) {
    return static_cast<SkMesh *>(mesh)->indexCount();
}

const_sk_data_t SkMesh_refUniforms(void * mesh) {
    return static_const_sk_data_make(static_cast<SkMesh *>(mesh)->refUniforms());
}

const void * SkMesh_uniforms(void * mesh) {
    return static_cast<SkMesh *>(mesh)->uniforms();
}

const_sk_mesh_child_ptr_t SkMesh_children(void * mesh) {
    return static_const_sk_mesh_child_ptr_make(static_cast<SkMesh *>(mesh)->children());
}

sk_rect_t SkMesh_bounds(void * mesh) {
    return static_sk_rect_make(static_cast<SkMesh *>(mesh)->bounds());
}

bool SkMesh_isValid(void * mesh) {
    return static_cast<SkMesh *>(mesh)->isValid();
}

// static

sk_mesh_result_t SkMesh_Make(sk_mesh_specification_t spec, int mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const void * bounds) {
    return static_sk_mesh_result_make(SkMesh::Make(static_sk_mesh_specification_move(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_move(vBuffer), vertexCount, vertexOffset, static_const_sk_data_move(uniforms), static_sk_mesh_child_ptr_get(children), * static_cast<const SkRect *>(bounds)));
}

sk_mesh_result_t SkMesh_MakeIndexed(sk_mesh_specification_t spec, int mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const void * bounds) {
    return static_sk_mesh_result_make(SkMesh::MakeIndexed(static_sk_mesh_specification_move(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_move(vBuffer), vertexCount, vertexOffset, static_sk_mesh_index_buffer_move(iBuffer), indexCount, indexOffset, static_const_sk_data_move(uniforms), static_sk_mesh_child_ptr_get(children), * static_cast<const SkRect *>(bounds)));
}

}