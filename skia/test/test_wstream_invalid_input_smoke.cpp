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
    if (!check(!SkNullWStream_write(nullptr, nullptr, 1), "SkNullWStream_write(nullptr)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    if (!check(SkNullWStream_bytesWritten(nullptr) == 0, "SkNullWStream_bytesWritten(nullptr)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    SkNullWStream_flush(nullptr);
    if (!check(SkNullWStream_write(null_stream, nullptr, 0), "SkNullWStream_write(null_stream, nullptr, 0)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    if (!check(!SkNullWStream_write(null_stream, nullptr, 1), "SkNullWStream_write(null_stream, nullptr, 1)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    const uint8_t direct_bytes[] = {1, 2, 3};
    if (!check(SkNullWStream_write(null_stream, direct_bytes, sizeof(direct_bytes)), "SkNullWStream_write(null_stream, bytes)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    if (!check(SkNullWStream_bytesWritten(null_stream) == sizeof(direct_bytes), "SkNullWStream_bytesWritten(null_stream)")) {
        SkWStream_delete(null_stream);
        return 6;
    }
    SkNullWStream_flush(null_stream);
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
    if (!check(!SkDynamicMemoryWStream_writeToStream(nullptr, nullptr), "SkDynamicMemoryWStream_writeToStream(nullptr)")) {
        return 18;
    }
    if (!check(!SkDynamicMemoryWStream_writeToAndReset(nullptr, nullptr), "SkDynamicMemoryWStream_writeToAndReset(nullptr)")) {
        return 19;
    }
    if (!check(!SkDynamicMemoryWStream_writeToAndResetDynamicStream(nullptr, nullptr), "SkDynamicMemoryWStream_writeToAndResetDynamicStream(nullptr)")) {
        return 20;
    }
    SkDynamicMemoryWStream_copyTo(nullptr, nullptr);
    SkDynamicMemoryWStream_copyToAndReset(nullptr, nullptr);
    SkDynamicMemoryWStream_prependToAndReset(nullptr, nullptr);
    SkDynamicMemoryWStream_reset(nullptr);
    SkDynamicMemoryWStream_padToAlign4(nullptr);
    SkDynamicMemoryWStream_flush(nullptr);
    if (!check(!SkDynamicMemoryWStream_write8(nullptr, 1), "SkDynamicMemoryWStream_write8(nullptr)")) {
        return 21;
    }
    if (!check(!SkDynamicMemoryWStream_write16(nullptr, 1), "SkDynamicMemoryWStream_write16(nullptr)")) {
        return 22;
    }
    if (!check(!SkDynamicMemoryWStream_write32(nullptr, 1), "SkDynamicMemoryWStream_write32(nullptr)")) {
        return 23;
    }
    if (!check(!SkDynamicMemoryWStream_newline(nullptr), "SkDynamicMemoryWStream_newline(nullptr)")) {
        return 24;
    }
    if (!check(!SkDynamicMemoryWStream_writeDecAsText(nullptr, 1), "SkDynamicMemoryWStream_writeDecAsText(nullptr)")) {
        return 25;
    }
    if (!check(!SkDynamicMemoryWStream_writeBigDecAsText(nullptr, 1, 1), "SkDynamicMemoryWStream_writeBigDecAsText(nullptr)")) {
        return 26;
    }
    if (!check(!SkDynamicMemoryWStream_writeHexAsText(nullptr, 1, 1), "SkDynamicMemoryWStream_writeHexAsText(nullptr)")) {
        return 27;
    }
    if (!check(!SkDynamicMemoryWStream_writeScalarAsText(nullptr, 1.0f), "SkDynamicMemoryWStream_writeScalarAsText(nullptr)")) {
        return 28;
    }
    if (!check(!SkDynamicMemoryWStream_writeBool(nullptr, true), "SkDynamicMemoryWStream_writeBool(nullptr)")) {
        return 29;
    }
    if (!check(!SkDynamicMemoryWStream_writeScalar(nullptr, 1.0f), "SkDynamicMemoryWStream_writeScalar(nullptr)")) {
        return 30;
    }
    if (!check(!SkDynamicMemoryWStream_writePackedUInt(nullptr, 1), "SkDynamicMemoryWStream_writePackedUInt(nullptr)")) {
        return 31;
    }

    reskia_dynamic_memory_w_stream_t *dynamic_stream = SkDynamicMemoryWStream_new();
    if (!check(dynamic_stream != nullptr, "SkDynamicMemoryWStream_new")) {
        return 32;
    }
    const uint8_t bytes[] = {1, 2, 3};
    if (!check(SkDynamicMemoryWStream_write(dynamic_stream, bytes, sizeof(bytes)), "SkDynamicMemoryWStream_write")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 33;
    }
    if (!check(SkDynamicMemoryWStream_bytesWritten(dynamic_stream) == sizeof(bytes), "SkDynamicMemoryWStream_bytesWritten")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 34;
    }
    uint8_t copied[3] = {};
    if (!check(SkDynamicMemoryWStream_read(dynamic_stream, copied, 0, sizeof(copied)), "SkDynamicMemoryWStream_read")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 35;
    }
    if (!check(copied[0] == 1 && copied[1] == 2 && copied[2] == 3, "SkDynamicMemoryWStream_read contents")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 36;
    }
    if (!check(!SkDynamicMemoryWStream_read(dynamic_stream, nullptr, 0, 1), "SkDynamicMemoryWStream_read null buffer")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 37;
    }
    if (!check(SkDynamicMemoryWStream_writeStream(dynamic_stream, nullptr, 0), "SkDynamicMemoryWStream_writeStream null zero")) {
        SkDynamicMemoryWStream_delete(dynamic_stream);
        return 38;
    }

    SkDynamicMemoryWStream_delete(dynamic_stream);
    return 0;
}
