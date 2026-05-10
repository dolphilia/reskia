//
// Created by dolphilia on 25/02/04.
//

#include "sk_mesh.h"

#include "include/core/SkImage.h"
#include "include/core/SkMesh.h"

#include "../handles/static_sk_mesh_vertex_buffer.h"
#include "../handles/static_sk_mesh_index_buffer.h"
#include "../handles/static_sk_mesh_child_ptr.h"
#include "../handles/static_sk_mesh_specification.h"
#include "../handles/static_sk_mesh_result.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_rect.h"

#include "../handles/static_sk_mesh_vertex_buffer-internal.h"
#include "../handles/static_sk_mesh_index_buffer-internal.h"
#include "../handles/static_sk_mesh_child_ptr-internal.h"
#include "../handles/static_sk_mesh_specification-internal.h"
#include "../handles/static_sk_mesh_result-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_rect-internal.h"

namespace {

SkMesh *as_mesh(reskia_mesh_t *mesh) {
    return reinterpret_cast<SkMesh *>(mesh);
}

const SkMesh *as_mesh(const reskia_mesh_t *mesh) {
    return reinterpret_cast<const SkMesh *>(mesh);
}

}  // namespace

extern "C" {

void SkMesh_delete(reskia_mesh_t * mesh) {
    delete as_mesh(mesh);
}

sk_mesh_specification_t SkMesh_refSpec(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_sk_mesh_specification_make(as_mesh(mesh)->refSpec());
}

reskia_mesh_specification_t * SkMesh_spec(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_mesh_specification_t *>(as_mesh(mesh)->spec());
}

reskia_mesh_mode_t SkMesh_mode(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return -1;
    }
    return static_cast<reskia_mesh_mode_t>(as_mesh(mesh)->mode());
}

sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_sk_mesh_vertex_buffer_make(as_mesh(mesh)->refVertexBuffer());
}

reskia_mesh_vertex_buffer_t * SkMesh_vertexBuffer(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_mesh_vertex_buffer_t *>(as_mesh(mesh)->vertexBuffer());
}

size_t SkMesh_vertexOffset(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return as_mesh(mesh)->vertexOffset();
}

size_t SkMesh_vertexCount(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return as_mesh(mesh)->vertexCount();
}

sk_mesh_index_buffer_t SkMesh_refIndexBuffer(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_sk_mesh_index_buffer_make(as_mesh(mesh)->refIndexBuffer());
}

reskia_mesh_index_buffer_t * SkMesh_indexBuffer(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_mesh_index_buffer_t *>(as_mesh(mesh)->indexBuffer());
}

size_t SkMesh_indexOffset(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return as_mesh(mesh)->indexOffset();
}

size_t SkMesh_indexCount(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return as_mesh(mesh)->indexCount();
}

const_sk_data_t SkMesh_refUniforms(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_const_sk_data_make(as_mesh(mesh)->refUniforms());
}

const reskia_data_t * SkMesh_uniforms(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_data_t *>(as_mesh(mesh)->uniforms());
}

const_sk_mesh_child_ptr_t SkMesh_children(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_const_sk_mesh_child_ptr_make(as_mesh(mesh)->children());
}

sk_rect_t SkMesh_bounds(reskia_mesh_t * mesh) {
    if (mesh == nullptr) {
        return 0;
    }
    return static_sk_rect_make(as_mesh(mesh)->bounds());
}

bool SkMesh_isValid(reskia_mesh_t * mesh) {
    return mesh != nullptr && as_mesh(mesh)->isValid();
}

// static

sk_mesh_result_t SkMesh_Make(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds) {
    if (bounds == nullptr) {
        return 0;
    }
    return static_sk_mesh_result_make(SkMesh::Make(static_sk_mesh_specification_get_entity(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_get_entity(vBuffer), vertexCount, vertexOffset, static_const_sk_data_get_entity(uniforms), static_sk_mesh_child_ptr_get_entity(children), * reinterpret_cast<const SkRect *>(bounds)));
}

sk_mesh_result_t SkMesh_MakeIndexed(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds) {
    if (bounds == nullptr) {
        return 0;
    }
    return static_sk_mesh_result_make(SkMesh::MakeIndexed(static_sk_mesh_specification_get_entity(spec), static_cast<SkMesh::Mode>(mode), static_sk_mesh_vertex_buffer_get_entity(vBuffer), vertexCount, vertexOffset, static_sk_mesh_index_buffer_get_entity(iBuffer), indexCount, indexOffset, static_const_sk_data_get_entity(uniforms), static_sk_mesh_child_ptr_get_entity(children), * reinterpret_cast<const SkRect *>(bounds)));
}

}
