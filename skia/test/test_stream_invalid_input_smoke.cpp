#include "capi/sk_memory_stream.h"
#include "capi/sk_stream.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[stream-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkStream_read(nullptr, nullptr, 4) == 0, "SkStream_read(nullptr)")) {
        return 1;
    }
    if (!check(SkStream_peek(nullptr, nullptr, 4) == 0, "SkStream_peek(nullptr)")) {
        return 2;
    }
    if (!check(SkStream_isAtEnd(nullptr), "SkStream_isAtEnd(nullptr)")) {
        return 3;
    }
    if (!check(!SkStream_readU8(nullptr, nullptr), "SkStream_readU8(nullptr)")) {
        return 4;
    }
    if (!check(!SkStream_rewind(nullptr), "SkStream_rewind(nullptr)")) {
        return 5;
    }
    if (!check(SkStream_duplicate(nullptr) == 0, "SkStream_duplicate(nullptr)")) {
        return 6;
    }
    if (!check(SkStream_getMemoryBase(nullptr) == nullptr, "SkStream_getMemoryBase(nullptr)")) {
        return 7;
    }
    if (!check(SkStream_MakeFromFile(nullptr) == 0, "SkStream_MakeFromFile(nullptr)")) {
        return 8;
    }

    if (!check(SkMemoryStream_newWithDataAndCopyFlag(nullptr, 1, true) == nullptr, "SkMemoryStream_newWithDataAndCopyFlag(nullptr, 1)")) {
        return 9;
    }
    if (!check(SkMemoryStream_getAtPos(nullptr) == nullptr, "SkMemoryStream_getAtPos(nullptr)")) {
        return 11;
    }
    if (!check(SkMemoryStream_read(nullptr, nullptr, 4) == 0, "SkMemoryStream_read(nullptr)")) {
        return 12;
    }
    if (!check(SkMemoryStream_isAtEnd(nullptr), "SkMemoryStream_isAtEnd(nullptr)")) {
        return 13;
    }
    if (!check(SkMemoryStream_peek(nullptr, nullptr, 4) == 0, "SkMemoryStream_peek(nullptr)")) {
        return 14;
    }
    if (!check(!SkMemoryStream_readU8(nullptr, nullptr), "SkMemoryStream_readU8(nullptr)")) {
        return 15;
    }
    if (!check(SkMemoryStream_duplicate(nullptr) == 0, "SkMemoryStream_duplicate(nullptr)")) {
        return 16;
    }
    if (!check(SkMemoryStream_MakeCopy(nullptr, 1) == 0, "SkMemoryStream_MakeCopy(nullptr, 1)")) {
        return 17;
    }
    if (!check(SkMemoryStream_MakeDirect(nullptr, 1) == 0, "SkMemoryStream_MakeDirect(nullptr, 1)")) {
        return 18;
    }

    SkMemoryStream_setMemory(nullptr, nullptr, 0, true);
    SkMemoryStream_setMemoryOwned(nullptr, nullptr, 0);
    SkMemoryStream_setData(nullptr, 0);
    SkMemoryStream_skipToAlign4(nullptr);

    const uint8_t bytes[] = {10, 20, 30, 40};
    reskia_memory_stream_t *memory_stream = SkMemoryStream_newWithDataAndCopyFlag(bytes, sizeof(bytes), true);
    if (!check(memory_stream != nullptr, "SkMemoryStream_newWithDataAndCopyFlag")) {
        return 19;
    }
    if (!check(SkMemoryStream_getLength(memory_stream) == sizeof(bytes), "SkMemoryStream_getLength")) {
        SkMemoryStream_delete(memory_stream);
        return 20;
    }
    if (!check(SkMemoryStream_read(memory_stream, nullptr, 1) == 1, "SkMemoryStream_read null buffer skips")) {
        SkMemoryStream_delete(memory_stream);
        return 21;
    }
    uint8_t value = 0;
    if (!check(SkMemoryStream_readU8(memory_stream, &value) && value == 20, "SkMemoryStream_readU8")) {
        SkMemoryStream_delete(memory_stream);
        return 22;
    }
    if (!check(SkMemoryStream_rewind(memory_stream), "SkMemoryStream_rewind")) {
        SkMemoryStream_delete(memory_stream);
        return 23;
    }
    uint8_t peeked[2] = {};
    if (!check(SkMemoryStream_peek(memory_stream, peeked, sizeof(peeked)) == sizeof(peeked), "SkMemoryStream_peek")) {
        SkMemoryStream_delete(memory_stream);
        return 24;
    }
    if (!check(peeked[0] == 10 && peeked[1] == 20, "SkMemoryStream_peek contents")) {
        SkMemoryStream_delete(memory_stream);
        return 25;
    }

    auto *base_stream = reinterpret_cast<reskia_stream_t *>(memory_stream);
    if (!check(SkStream_read(base_stream, nullptr, 1) == 1, "SkStream_read base skip")) {
        SkMemoryStream_delete(memory_stream);
        return 26;
    }
    if (!check(SkStream_getMemoryBase(base_stream) != nullptr, "SkStream_getMemoryBase base")) {
        SkMemoryStream_delete(memory_stream);
        return 27;
    }

    const sk_memory_stream_t copied = SkMemoryStream_MakeCopy(bytes, sizeof(bytes));
    if (!check(copied != 0 && static_sk_memory_stream_get_ptr(copied) != nullptr, "SkMemoryStream_MakeCopy")) {
        SkMemoryStream_delete(memory_stream);
        return 28;
    }

    static_sk_memory_stream_delete(copied);
    SkMemoryStream_delete(memory_stream);
    return 0;
}
