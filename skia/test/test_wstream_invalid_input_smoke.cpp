#include "capi/sk_dynamic_memory_w_stream.h"
#include "capi/sk_w_stream.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[wstream-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(!SkWStream_write(nullptr, nullptr, 1), "SkWStream_write(nullptr)")) {
        return 1;
    }
    if (!check(SkWStream_bytesWritten(nullptr) == 0, "SkWStream_bytesWritten(nullptr)")) {
        return 2;
    }
    if (!check(!SkWStream_writeText(nullptr, nullptr), "SkWStream_writeText(nullptr)")) {
        return 3;
    }
    if (!check(!SkWStream_write8(nullptr, 1), "SkWStream_write8(nullptr)")) {
        return 4;
    }
    if (!check(!SkWStream_writeStream(nullptr, nullptr, 1), "SkWStream_writeStream(nullptr)")) {
        return 5;
    }
    SkWStream_flush(nullptr);

    reskia_w_stream_t *null_stream = SkNullWStream_new();
    if (!check(null_stream != nullptr, "SkNullWStream_new")) {
        return 6;
    }
    if (!check(SkWStream_write(null_stream, nullptr, 0), "SkWStream_write(null_stream, nullptr, 0)")) {
        SkWStream_delete(null_stream);
        return 7;
    }
    if (!check(!SkWStream_write(null_stream, nullptr, 1), "SkWStream_write(null_stream, nullptr, 1)")) {
        SkWStream_delete(null_stream);
        return 8;
    }
    if (!check(SkWStream_writeText(null_stream, "ok"), "SkWStream_writeText(null_stream)")) {
        SkWStream_delete(null_stream);
        return 9;
    }
    if (!check(SkWStream_writeStream(null_stream, nullptr, 0), "SkWStream_writeStream(null_stream, nullptr, 0)")) {
        SkWStream_delete(null_stream);
        return 10;
    }
    SkWStream_delete(null_stream);

    if (!check(!SkDynamicMemoryWStream_write(nullptr, nullptr, 1), "SkDynamicMemoryWStream_write(nullptr)")) {
        return 11;
    }
    if (!check(SkDynamicMemoryWStream_bytesWritten(nullptr) == 0, "SkDynamicMemoryWStream_bytesWritten(nullptr)")) {
        return 12;
    }
    if (!check(!SkDynamicMemoryWStream_read(nullptr, nullptr, 0, 1), "SkDynamicMemoryWStream_read(nullptr)")) {
        return 13;
    }
    if (!check(!SkDynamicMemoryWStream_writeText(nullptr, nullptr), "SkDynamicMemoryWStream_writeText(nullptr)")) {
        return 14;
    }
    if (!check(SkDynamicMemoryWStream_detachAsData(nullptr) == 0, "SkDynamicMemoryWStream_detachAsData(nullptr)")) {
        return 15;
    }
    if (!check(SkDynamicMemoryWStream_detachAsStream(nullptr) == 0, "SkDynamicMemoryWStream_detachAsStream(nullptr)")) {
        return 16;
    }
    if (!check(!SkDynamicMemoryWStream_writeStream(nullptr, nullptr, 1), "SkDynamicMemoryWStream_writeStream(nullptr)")) {
        return 17;
    }
    SkDynamicMemoryWStream_copyTo(nullptr, nullptr);
    SkDynamicMemoryWStream_copyToAndReset(nullptr, nullptr);
    SkDynamicMemoryWStream_reset(nullptr);
    SkDynamicMemoryWStream_flush(nullptr);

    reskia_dynamic_memory_w_stream_t *dynamic_stream = SkDynamicMemoryWStream_new();
    if (!check(dynamic_stream != nullptr, "SkDynamicMemoryWStream_new")) {
        return 18;
    }
    const uint8_t bytes[] = {1, 2, 3};
    if (!check(SkDynamicMemoryWStream_write(dynamic_stream, bytes, sizeof(bytes)), "SkDynamicMemoryWStream_write")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 19;
    }
    if (!check(SkDynamicMemoryWStream_bytesWritten(dynamic_stream) == sizeof(bytes), "SkDynamicMemoryWStream_bytesWritten")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 20;
    }
    uint8_t copied[3] = {};
    if (!check(SkDynamicMemoryWStream_read(dynamic_stream, copied, 0, sizeof(copied)), "SkDynamicMemoryWStream_read")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 21;
    }
    if (!check(copied[0] == 1 && copied[1] == 2 && copied[2] == 3, "SkDynamicMemoryWStream_read contents")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 22;
    }
    if (!check(!SkDynamicMemoryWStream_read(dynamic_stream, nullptr, 0, 1), "SkDynamicMemoryWStream_read null buffer")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 23;
    }
    if (!check(SkDynamicMemoryWStream_writeStream(dynamic_stream, nullptr, 0), "SkDynamicMemoryWStream_writeStream null zero")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 24;
    }

    SkDynamicMemoryWStream_delete(dynamic_stream);
    return 0;
}
