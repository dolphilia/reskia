//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MASK_FILTER_H
#define RAIA_SKIA_SK_MASK_FILTER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_mask_filter_t reskia_mask_filter_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

void SkMaskFilter_delete(reskia_mask_filter_t *maskFilter); // owned: caller が保持する参照を release する (SkMaskFilter *maskFilter)
int SkMaskFilter_approximateFilteredBounds(reskia_mask_filter_t *mask_filter, const reskia_rect_t *src); // (SkMaskFilter *mask_filter, const SkRect *src) -> sk_rect_t
int SkMaskFilter_getFactory(reskia_mask_filter_t *mask_filter); // (SkMaskFilter *mask_filter) -> sk_flattenable_factory_t
const char *SkMaskFilter_getTypeName(reskia_mask_filter_t *mask_filter); // (SkMaskFilter *mask_filter) -> const char *
void SkMaskFilter_flatten(reskia_mask_filter_t *mask_filter, reskia_write_buffer_t *buffer); // (SkMaskFilter *mask_filter, SkWriteBuffer *buffer)
int SkMaskFilter_getFlattenableType(reskia_mask_filter_t *mask_filter); // (SkMaskFilter *mask_filter) -> SkMaskFilter::Type
int SkMaskFilter_serialize(reskia_mask_filter_t *mask_filter, const reskia_serial_procs_t *procs); // (SkMaskFilter *mask_filter, const SkSerialProcs *procs) -> sk_data_t
size_t SkMaskFilter_serialize_2(reskia_mask_filter_t *mask_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs); // (SkMaskFilter *mask_filter, void *memory, size_t memory_size, const SkSerialProcs *procs) -> size_t
bool SkMaskFilter_unique(reskia_mask_filter_t *mask_filter); // (SkMaskFilter *mask_filter) -> bool
void SkMaskFilter_ref(reskia_mask_filter_t *mask_filter); // retained: 参照カウントを増やす (SkMaskFilter *mask_filter)
void SkMaskFilter_unref(reskia_mask_filter_t *mask_filter); // owned: 参照カウントを減らす (SkMaskFilter *mask_filter)

// static

int SkMaskFilter_MakeBlur(int style, float sigma, bool respectCTM); // (SkBlurStyle style, SkScalar sigma, bool respectCTM) -> sk_mask_filter_t
int SkMaskFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_mask_filter_t
int SkMaskFilter_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char *SkMaskFilter_FactoryToName(int factory); // (sk_flattenable_factory_t factory) -> const char *
void SkMaskFilter_Register(const char name[], int factory); // (const char name[], sk_flattenable_factory_t factory)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MASK_FILTER_H
