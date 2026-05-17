#ifndef RAIA_SKIA_SK_PNG_CHUNK_READER_H
#define RAIA_SKIA_SK_PNG_CHUNK_READER_H

#include <stddef.h>
#include <stdbool.h>

#include "reskia_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_png_chunk_reader_t reskia_png_chunk_reader_t;

/**
 * tag/data are borrowed and valid only during the callback.
 * Return true to continue decoding, false to report a chunk read error.
 */
typedef bool (*reskia_png_chunk_reader_read_chunk_proc_t)(
        const char tag[4],
        const void *data,
        size_t length,
        void *user_data);

reskia_png_chunk_reader_t *SkPngChunkReader_new(reskia_png_chunk_reader_read_chunk_proc_t read_chunk, void *user_data, reskia_callback_release_proc_t release_proc);
void SkPngChunkReader_retain(reskia_png_chunk_reader_t *reader);
void SkPngChunkReader_release(reskia_png_chunk_reader_t *reader);
bool SkPngChunkReader_readChunk(reskia_png_chunk_reader_t *reader, const char tag[4], const void *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PNG_CHUNK_READER_H
