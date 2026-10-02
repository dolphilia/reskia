#ifndef RESKIA_SK_CONTEXT_H
#define RESKIA_SK_CONTEXT_H

#include <stddef.h>

typedef struct reskia_context_t reskia_context_t;
typedef struct reskia_context_options_t {
    int typeface_cache_count_limit;
    size_t resource_cache_total_byte_limit;
    size_t resource_cache_single_allocation_byte_limit;
    int font_cache_count_limit;
    size_t font_cache_limit;
} reskia_context_options_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_context_options_t SkContextOptions_default(void);
// Owned context. NULL options use defaults; negative cache counts return NULL.
reskia_context_t *SkContexts_MakeRaster(const reskia_context_options_t *options);
void SkContext_delete(reskia_context_t *context); // NULL is a no-op.

#ifdef __cplusplus
}
#endif
#endif
