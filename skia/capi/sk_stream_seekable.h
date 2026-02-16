//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STREAM_SEEKABLE_H
#define RAIA_SKIA_SK_STREAM_SEEKABLE_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_stream_seekable_t reskia_stream_seekable_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStreamSeekable_delete(reskia_stream_seekable_t *stream_seekable); // Deletes the SkStreamSeekable object and releases its resources.
int SkStreamSeekable_duplicate(reskia_stream_seekable_t *stream_seekable); // Creates a duplicate of the given SkStreamSeekable object.
bool SkStreamSeekable_hasPosition(reskia_stream_seekable_t *stream_seekable); // Checks if the stream supports position querying.
size_t SkStreamSeekable_getPosition(reskia_stream_seekable_t *stream_seekable); // Returns the current position in the stream.
bool SkStreamSeekable_seek(reskia_stream_seekable_t *stream_seekable, size_t position); // Moves the read position to the specified offset.
bool SkStreamSeekable_move(reskia_stream_seekable_t *stream_seekable, long offset); // Moves the read position by the specified offset relative to the current position.
int SkStreamSeekable_fork(reskia_stream_seekable_t *stream_seekable); // Creates a forked copy of the current stream at its current position.
bool SkStreamSeekable_rewind(reskia_stream_seekable_t *stream_seekable); // Resets the read position to the beginning of the stream.
size_t SkStreamSeekable_read(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size); // Reads up to `size` bytes from the stream into `buffer`.
size_t SkStreamSeekable_skip(reskia_stream_seekable_t *stream_seekable, size_t size); // Skips over the specified number of bytes in the stream.
size_t SkStreamSeekable_peek(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size); // Reads `size` bytes into `buffer` without advancing the read position.
bool SkStreamSeekable_isAtEnd(reskia_stream_seekable_t *stream_seekable); // Checks if the stream has reached its end.
bool SkStreamSeekable_readS8(reskia_stream_seekable_t *stream_seekable, int8_t *i); // Reads an 8-bit signed integer from the stream.
bool SkStreamSeekable_readS16(reskia_stream_seekable_t *stream_seekable, int16_t *i); // Reads a 16-bit signed integer from the stream.
bool SkStreamSeekable_readS32(reskia_stream_seekable_t *stream_seekable, int32_t *i); // Reads a 32-bit signed integer from the stream.
bool SkStreamSeekable_readU8(reskia_stream_seekable_t *stream_seekable, uint8_t *i); // Reads an 8-bit unsigned integer from the stream.
bool SkStreamSeekable_readU16(reskia_stream_seekable_t *stream_seekable, uint16_t *i); // Reads a 16-bit unsigned integer from the stream.
bool SkStreamSeekable_readU32(reskia_stream_seekable_t *stream_seekable, uint32_t *i); // Reads a 32-bit unsigned integer from the stream.
bool SkStreamSeekable_readBool(reskia_stream_seekable_t *stream_seekable, bool *b); // Reads a boolean value from the stream.
bool SkStreamSeekable_readScalar(reskia_stream_seekable_t *stream_seekable, float *v); // Reads a scalar value from the stream.
bool SkStreamSeekable_readPackedUInt(reskia_stream_seekable_t *stream_seekable, size_t *size); // Reads a packed unsigned integer from the stream.
bool SkStreamSeekable_hasLength(reskia_stream_seekable_t *stream_seekable); // Checks if the stream has a known length.
size_t SkStreamSeekable_getLength(reskia_stream_seekable_t *stream_seekable); // Returns the total length of the stream.
const void * SkStreamSeekable_getMemoryBase(reskia_stream_seekable_t *stream_seekable); // Returns a pointer to the stream's memory base if available.

// static

int SkStreamSeekable_MakeFromFile(const char path[]); // Creates a SkStreamSeekable object from the specified file.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STREAM_SEEKABLE_H
