#include "capi/sk_stream_asset.h"
#include "capi/sk_stream_memory.h"
#include "capi/sk_stream_rewindable.h"
#include "capi/sk_stream_seekable.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[stream-derived-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(!SkStreamAsset_hasLength(nullptr), "SkStreamAsset_hasLength(nullptr)")) {
        return 1;
    }
    if (!check(SkStreamAsset_getLength(nullptr) == 0, "SkStreamAsset_getLength(nullptr)")) {
        return 2;
    }
    if (!check(SkStreamAsset_duplicate(nullptr) == 0, "SkStreamAsset_duplicate(nullptr)")) {
        return 3;
    }
    if (!check(SkStreamAsset_read(nullptr, nullptr, 4) == 0, "SkStreamAsset_read(nullptr)")) {
        return 4;
    }
    if (!check(SkStreamAsset_isAtEnd(nullptr), "SkStreamAsset_isAtEnd(nullptr)")) {
        return 5;
    }
    if (!check(!SkStreamAsset_readU8(nullptr, nullptr), "SkStreamAsset_readU8(nullptr)")) {
        return 6;
    }
    if (!check(SkStreamAsset_getMemoryBase(nullptr) == nullptr, "SkStreamAsset_getMemoryBase(nullptr)")) {
        return 7;
    }
    if (!check(SkStreamAsset_MakeFromFile(nullptr) == 0, "SkStreamAsset_MakeFromFile(nullptr)")) {
        return 8;
    }

    if (!check(SkStreamSeekable_duplicate(nullptr) == 0, "SkStreamSeekable_duplicate(nullptr)")) {
        return 9;
    }
    if (!check(!SkStreamSeekable_hasPosition(nullptr), "SkStreamSeekable_hasPosition(nullptr)")) {
        return 10;
    }
    if (!check(SkStreamSeekable_getPosition(nullptr) == 0, "SkStreamSeekable_getPosition(nullptr)")) {
        return 11;
    }
    if (!check(!SkStreamSeekable_seek(nullptr, 0), "SkStreamSeekable_seek(nullptr)")) {
        return 12;
    }
    if (!check(SkStreamSeekable_read(nullptr, nullptr, 4) == 0, "SkStreamSeekable_read(nullptr)")) {
        return 13;
    }
    if (!check(SkStreamSeekable_isAtEnd(nullptr), "SkStreamSeekable_isAtEnd(nullptr)")) {
        return 14;
    }
    if (!check(!SkStreamSeekable_readU8(nullptr, nullptr), "SkStreamSeekable_readU8(nullptr)")) {
        return 15;
    }
    if (!check(SkStreamSeekable_getMemoryBase(nullptr) == nullptr, "SkStreamSeekable_getMemoryBase(nullptr)")) {
        return 16;
    }
    if (!check(SkStreamSeekable_MakeFromFile(nullptr) == 0, "SkStreamSeekable_MakeFromFile(nullptr)")) {
        return 17;
    }

    if (!check(!SkStreamRewindable_rewind(nullptr), "SkStreamRewindable_rewind(nullptr)")) {
        return 18;
    }
    if (!check(SkStreamRewindable_duplicate(nullptr) == 0, "SkStreamRewindable_duplicate(nullptr)")) {
        return 19;
    }
    if (!check(SkStreamRewindable_read(nullptr, nullptr, 4) == 0, "SkStreamRewindable_read(nullptr)")) {
        return 20;
    }
    if (!check(SkStreamRewindable_isAtEnd(nullptr), "SkStreamRewindable_isAtEnd(nullptr)")) {
        return 21;
    }
    if (!check(!SkStreamRewindable_readU8(nullptr, nullptr), "SkStreamRewindable_readU8(nullptr)")) {
        return 22;
    }
    if (!check(SkStreamRewindable_fork(nullptr) == 0, "SkStreamRewindable_fork(nullptr)")) {
        return 23;
    }
    if (!check(SkStreamRewindable_getMemoryBase(nullptr) == nullptr, "SkStreamRewindable_getMemoryBase(nullptr)")) {
        return 24;
    }
    if (!check(SkStreamRewindable_MakeFromFile(nullptr) == 0, "SkStreamRewindable_MakeFromFile(nullptr)")) {
        return 25;
    }

    if (!check(SkStreamMemory_getMemoryBase(nullptr) == nullptr, "SkStreamMemory_getMemoryBase(nullptr)")) {
        return 26;
    }
    if (!check(SkStreamMemory_duplicate(nullptr) == 0, "SkStreamMemory_duplicate(nullptr)")) {
        return 27;
    }
    if (!check(!SkStreamMemory_hasLength(nullptr), "SkStreamMemory_hasLength(nullptr)")) {
        return 28;
    }
    if (!check(SkStreamMemory_read(nullptr, nullptr, 4) == 0, "SkStreamMemory_read(nullptr)")) {
        return 29;
    }
    if (!check(SkStreamMemory_isAtEnd(nullptr), "SkStreamMemory_isAtEnd(nullptr)")) {
        return 30;
    }
    if (!check(!SkStreamMemory_readU8(nullptr, nullptr), "SkStreamMemory_readU8(nullptr)")) {
        return 31;
    }
    if (!check(SkStreamMemory_MakeFromFile(nullptr) == 0, "SkStreamMemory_MakeFromFile(nullptr)")) {
        return 32;
    }

    SkStreamAsset_delete(nullptr);
    SkStreamSeekable_delete(nullptr);
    SkStreamRewindable_delete(nullptr);
    SkStreamMemory_delete(nullptr);
    return 0;
}
