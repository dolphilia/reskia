//
// Created by dolphilia on 25/02/04.
//

#ifndef STATIC_SK_MESH_CPECIFICATION_H
#define STATIC_SK_MESH_CPECIFICATION_H
#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_mesh_specification_t;
void static_sk_mesh_specification_delete(int key);
void *static_sk_mesh_specification_get(int key); // -> SkMesh::IndexBuffer *
#ifdef __cplusplus
}
#endif
#endif //STATIC_SK_MESH_CPECIFICATION_H
