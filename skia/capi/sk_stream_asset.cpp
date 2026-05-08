//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_asset.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_stream_asset.h"

#include "../handles/static_sk_stream_asset-internal.h"

extern "C" {

void SkStreamAsset_delete(reskia_stream_asset_t *stream_asset) {
    delete reinterpret_cast<SkStreamAsset *>(stream_asset);
}

bool SkStreamAsset_hasLength(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->hasLength();
}

size_t SkStreamAsset_getLength(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->getLength();
}

sk_stream_asset_t SkStreamAsset_duplicate(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(reinterpret_cast<SkStreamAsset *>(stream_asset)->duplicate());
}

sk_stream_asset_t SkStreamAsset_fork(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(reinterpret_cast<SkStreamAsset *>(stream_asset)->fork());
}

bool SkStreamAsset_hasPosition(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->hasPosition();
}

size_t SkStreamAsset_getPosition(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->getPosition();
}

bool SkStreamAsset_seek(reskia_stream_asset_t *stream_asset, size_t position) {
    if (stream_asset == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->seek(position);
}

bool SkStreamAsset_move(reskia_stream_asset_t *stream_asset, long offset) {
    if (stream_asset == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->move(offset);
}

bool SkStreamAsset_rewind(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->rewind();
}

size_t SkStreamAsset_read(reskia_stream_asset_t *stream_asset, void *buffer, size_t size) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->read(buffer, size);
}

size_t SkStreamAsset_skip(reskia_stream_asset_t *stream_asset, size_t size) {
    if (stream_asset == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->skip(size);
}

size_t SkStreamAsset_peek(reskia_stream_asset_t *stream_asset, void *buffer, size_t size) {
    if (stream_asset == nullptr || (buffer == nullptr && size > 0)) {
        return 0;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->peek(buffer, size);
}

bool SkStreamAsset_isAtEnd(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return true;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->isAtEnd();
}

bool SkStreamAsset_readS8(reskia_stream_asset_t *stream_asset, int8_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readS8(i);
}

bool SkStreamAsset_readS16(reskia_stream_asset_t *stream_asset, int16_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readS16(i);
}

bool SkStreamAsset_readS32(reskia_stream_asset_t *stream_asset, int32_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readS32(i);
}

bool SkStreamAsset_readU8(reskia_stream_asset_t *stream_asset, uint8_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readU8(i);
}

bool SkStreamAsset_readU16(reskia_stream_asset_t *stream_asset, uint16_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readU16(i);
}

bool SkStreamAsset_readU32(reskia_stream_asset_t *stream_asset, uint32_t *i) {
    if (stream_asset == nullptr || i == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readU32(i);
}

bool SkStreamAsset_readBool(reskia_stream_asset_t *stream_asset, bool *b) {
    if (stream_asset == nullptr || b == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readBool(b);
}

bool SkStreamAsset_readScalar(reskia_stream_asset_t *stream_asset, float *v) {
    if (stream_asset == nullptr || v == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readScalar(v);
}

bool SkStreamAsset_readPackedUInt(reskia_stream_asset_t *stream_asset, size_t *size) {
    if (stream_asset == nullptr || size == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->readPackedUInt(size);
}

const void *SkStreamAsset_getMemoryBase(reskia_stream_asset_t *stream_asset) {
    if (stream_asset == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkStreamAsset *>(stream_asset)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamAsset_MakeFromFile(const char path[]) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_stream_asset_make(SkStreamAsset::MakeFromFile(path));
}

}
