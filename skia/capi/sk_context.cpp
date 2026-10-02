#include "sk_context.h"

#include "include/core/RasterContext.h"
#include "include/core/SkContext.h"
#include "include/core/SkContextOptions.h"

extern "C" {

reskia_context_options_t SkContextOptions_default(void) {
    const SkContextOptions options;
    return {options.fTypefaceCacheCountLimit,
            options.fResourceCacheTotalByteLimit,
            options.fResourceCacheSingleAllocationByteLimit,
            options.fFontCacheCountLimit,
            options.fFontCacheLimit};
}

reskia_context_t *SkContexts_MakeRaster(const reskia_context_options_t *options) {
    SkContextOptions native;
    if (options) {
        if (options->typeface_cache_count_limit < 0 || options->font_cache_count_limit < 0) {
            return nullptr;
        }
        native.fTypefaceCacheCountLimit = options->typeface_cache_count_limit;
        native.fResourceCacheTotalByteLimit = options->resource_cache_total_byte_limit;
        native.fResourceCacheSingleAllocationByteLimit = options->resource_cache_single_allocation_byte_limit;
        native.fFontCacheCountLimit = options->font_cache_count_limit;
        native.fFontCacheLimit = options->font_cache_limit;
    }
    return reinterpret_cast<reskia_context_t *>(SkContexts::MakeRaster(native).release());
}

void SkContext_delete(reskia_context_t *context) {
    delete reinterpret_cast<SkContext *>(context);
}

}
