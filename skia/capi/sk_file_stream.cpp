//
// Created by dolphilia on 2024/01/08.
//

#include "sk_file_stream.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_file_stream.h"
#include "../handles/static_sk_stream_asset.h"

#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_file_stream-internal.h"

namespace {

SkFILEStream *as_file_stream(reskia_file_stream_t *fileStream) {
    return reinterpret_cast<SkFILEStream *>(fileStream);
}

const SkFILEStream *as_file_stream(const reskia_file_stream_t *fileStream) {
    return reinterpret_cast<const SkFILEStream *>(fileStream);
}

bool has_buffer(uint8_t *buffer, size_t size) {
    return size == 0 || buffer != nullptr;
}

}  // namespace

extern "C" {

reskia_file_stream_t *SkFILEStream_new(const char path[]) {
    if (path == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(path));
}

reskia_file_stream_t *SkFILEStream_newFromFileHandle(reskia_file_t *file) {
    if (file == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(reinterpret_cast<FILE *>(file)));
}

reskia_file_stream_t *SkFILEStream_newFromFileHandleWithSize(reskia_file_t *file, size_t size) {
    if (file == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(reinterpret_cast<FILE *>(file), size));
}

void SkFILEStream_delete(reskia_file_stream_t *file_stream) {
    delete as_file_stream(file_stream);
}

bool SkFILEStream_isValid(reskia_file_stream_t *file_stream) {
    return file_stream != nullptr && as_file_stream(file_stream)->isValid();
}

void SkFILEStream_close(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return;
    }
    as_file_stream(file_stream)->close();
}

size_t SkFILEStream_read(reskia_file_stream_t *file_stream, uint8_t *buffer, size_t size) {
    if (file_stream == nullptr || !has_buffer(buffer, size)) {
        return 0;
    }
    return as_file_stream(file_stream)->read(buffer, size);
}

bool SkFILEStream_isAtEnd(reskia_file_stream_t *file_stream) {
    return file_stream == nullptr || as_file_stream(file_stream)->isAtEnd();
}

bool SkFILEStream_rewind(reskia_file_stream_t *file_stream) {
    return file_stream != nullptr && as_file_stream(file_stream)->rewind();
}

sk_stream_asset_t SkFILEStream_duplicate(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(as_file_stream(file_stream)->duplicate());
}

size_t SkFILEStream_getPosition(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return 0;
    }
    return as_file_stream(file_stream)->getPosition();
}

bool SkFILEStream_seek(reskia_file_stream_t *file_stream, size_t position) {
    return file_stream != nullptr && as_file_stream(file_stream)->seek(position);
}

bool SkFILEStream_move(reskia_file_stream_t *file_stream, long offset) {
    return file_stream != nullptr && as_file_stream(file_stream)->move(offset);
}

sk_stream_asset_t SkFILEStream_fork(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(as_file_stream(file_stream)->fork());
}

size_t SkFILEStream_getLength(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return 0;
    }
    return as_file_stream(file_stream)->getLength();
}

bool SkFILEStream_hasLength(reskia_file_stream_t *file_stream) {
    return file_stream != nullptr && as_file_stream(file_stream)->hasLength();
}

bool SkFILEStream_hasPosition(reskia_file_stream_t *file_stream) {
    return file_stream != nullptr && as_file_stream(file_stream)->hasPosition();
}

size_t SkFILEStream_skip(reskia_file_stream_t *file_stream, size_t size) {
    if (file_stream == nullptr) {
        return 0;
    }
    return as_file_stream(file_stream)->skip(size);
}

size_t SkFILEStream_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size) {
    if (file_stream == nullptr || !has_buffer(ptr, size)) {
        return 0;
    }
    return as_file_stream(file_stream)->peek(ptr, size);
}

bool SkFILEStream_readS8(reskia_file_stream_t *file_stream, int8_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readS8(i);
}

bool SkFILEStream_readS16(reskia_file_stream_t *file_stream, int16_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readS16(i);
}

bool SkFILEStream_readS32(reskia_file_stream_t *file_stream, int32_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readS32(i);
}

bool SkFILEStream_readU8(reskia_file_stream_t *file_stream, uint8_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readU8(i);
}

bool SkFILEStream_readU16(reskia_file_stream_t *file_stream, uint16_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readU16(i);
}

bool SkFILEStream_readU32(reskia_file_stream_t *file_stream, uint32_t *i) {
    return file_stream != nullptr && i != nullptr && as_file_stream(file_stream)->readU32(i);
}

bool SkFILEStream_readBool(reskia_file_stream_t *file_stream, bool *b) {
    return file_stream != nullptr && b != nullptr && as_file_stream(file_stream)->readBool(b);
}

bool SkFILEStream_readScalar(reskia_file_stream_t *file_stream, float *scalar) {
    return file_stream != nullptr && scalar != nullptr && as_file_stream(file_stream)->readScalar(scalar);
}

bool SkFILEStream_readPackedUInt(reskia_file_stream_t *file_stream, size_t *size) {
    return file_stream != nullptr && size != nullptr && as_file_stream(file_stream)->readPackedUInt(size);
}

const uint8_t * SkFILEStream_getMemoryBase(reskia_file_stream_t *file_stream) {
    if (file_stream == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const uint8_t *>(as_file_stream(file_stream)->getMemoryBase());
}

// static

sk_file_stream_t SkFILEStream_Make(const char path[]) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_file_stream_make(SkFILEStream::Make(path));
}

}
