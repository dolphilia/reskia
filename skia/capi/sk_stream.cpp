//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkStream_delete(reskia_stream_t *stream) {
    delete reinterpret_cast<SkStream *>(stream);
}

size_t SkStream_read(reskia_stream_t *stream, void *buffer, size_t size) {
    if (stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStream *>(stream)->read(buffer, size);
}

size_t SkStream_skip(reskia_stream_t *stream, size_t size) {
    if (stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStream *>(stream)->skip(size);
}

size_t SkStream_peek(reskia_stream_t *stream, void *buffer, size_t size) {
    if (stream == nullptr || (buffer == nullptr && size > 0)) {
        return 0;
    }
    return reinterpret_cast<SkStream *>(stream)->peek(buffer, size);
}

bool SkStream_isAtEnd(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return true;
    }
    return reinterpret_cast<SkStream *>(stream)->isAtEnd();
}

bool SkStream_readS8(reskia_stream_t *stream, int8_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readS8(i);
}

bool SkStream_readS16(reskia_stream_t *stream, int16_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readS16(i);
}

bool SkStream_readS32(reskia_stream_t *stream, int32_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readS32(i);
}

bool SkStream_readS64(reskia_stream_t *stream, int64_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readS64(i);
}

bool SkStream_readU8(reskia_stream_t *stream, uint8_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readU8(i);
}

bool SkStream_readU16(reskia_stream_t *stream, uint16_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readU16(i);
}

bool SkStream_readU32(reskia_stream_t *stream, uint32_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readU32(i);
}

bool SkStream_readU64(reskia_stream_t *stream, uint64_t *i) {
    if (stream == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readU64(i);
}

bool SkStream_readBool(reskia_stream_t *stream, bool *b) {
    if (stream == nullptr || b == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readBool(b);
}

bool SkStream_readScalar(reskia_stream_t *stream, float *v) {
    if (stream == nullptr || v == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readScalar(v);
}

bool SkStream_readPackedUInt(reskia_stream_t *stream, size_t *size) {
    if (stream == nullptr || size == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->readPackedUInt(size);
}

bool SkStream_rewind(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->rewind();
}

sk_stream_t SkStream_duplicate(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return static_sk_stream_make(reinterpret_cast<SkStream *>(stream)->duplicate());
}

sk_stream_t SkStream_fork(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return static_sk_stream_make(reinterpret_cast<SkStream *>(stream)->fork());
}

bool SkStream_hasPosition(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->hasPosition();
}

size_t SkStream_getPosition(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStream *>(stream)->getPosition();
}

bool SkStream_seek(reskia_stream_t *stream, size_t size) {
    if (stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->seek(size);
}

bool SkStream_move(reskia_stream_t *stream, long i) {
    if (stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->move(i);
}

bool SkStream_hasLength(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStream *>(stream)->hasLength();
}

size_t SkStream_getLength(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStream *>(stream)->getLength();
}

const void * SkStream_getMemoryBase(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkStream *>(stream)->getMemoryBase();
}

sk_data_t SkStream_getData(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return static_const_sk_data_make(reinterpret_cast<SkStream *>(stream)->getData());
}

// static

sk_stream_asset_t SkStream_MakeFromFile(const char path[]) { // static
    if (path == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(SkStream::MakeFromFile(path));
}

}
