#include "capi/sk_file_stream.h"
#include "capi/sk_file_w_stream.h"

#include <cstdint>
#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[file-stream-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(SkFILEStream_new(nullptr) == nullptr, "FILEStream new null path");
    ok &= check(SkFILEStream_newFromFileHandle(nullptr) == nullptr, "FILEStream new null file");
    ok &= check(SkFILEStream_newFromFileHandleWithSize(nullptr, 0) == nullptr, "FILEStream new null file with size");
    SkFILEStream_delete(nullptr);
    SkFILEStream_close(nullptr);
    ok &= check(!SkFILEStream_isValid(nullptr), "FILEStream isValid null");
    ok &= check(SkFILEStream_read(nullptr, nullptr, 0) == 0, "FILEStream read null stream");
    ok &= check(SkFILEStream_isAtEnd(nullptr), "FILEStream isAtEnd null");
    ok &= check(!SkFILEStream_rewind(nullptr), "FILEStream rewind null");
    ok &= check(SkFILEStream_duplicate(nullptr) == 0, "FILEStream duplicate null");
    ok &= check(SkFILEStream_getPosition(nullptr) == 0, "FILEStream getPosition null");
    ok &= check(!SkFILEStream_seek(nullptr, 0), "FILEStream seek null");
    ok &= check(!SkFILEStream_move(nullptr, 0), "FILEStream move null");
    ok &= check(SkFILEStream_fork(nullptr) == 0, "FILEStream fork null");
    ok &= check(SkFILEStream_getLength(nullptr) == 0, "FILEStream getLength null");
    ok &= check(!SkFILEStream_hasLength(nullptr), "FILEStream hasLength null");
    ok &= check(!SkFILEStream_hasPosition(nullptr), "FILEStream hasPosition null");
    ok &= check(SkFILEStream_skip(nullptr, 1) == 0, "FILEStream skip null");
    ok &= check(SkFILEStream_peek(nullptr, nullptr, 0) == 0, "FILEStream peek null stream");
    ok &= check(!SkFILEStream_readS8(nullptr, nullptr), "FILEStream readS8 null");
    ok &= check(!SkFILEStream_readS16(nullptr, nullptr), "FILEStream readS16 null");
    ok &= check(!SkFILEStream_readS32(nullptr, nullptr), "FILEStream readS32 null");
    ok &= check(!SkFILEStream_readU8(nullptr, nullptr), "FILEStream readU8 null");
    ok &= check(!SkFILEStream_readU16(nullptr, nullptr), "FILEStream readU16 null");
    ok &= check(!SkFILEStream_readU32(nullptr, nullptr), "FILEStream readU32 null");
    ok &= check(!SkFILEStream_readBool(nullptr, nullptr), "FILEStream readBool null");
    ok &= check(!SkFILEStream_readScalar(nullptr, nullptr), "FILEStream readScalar null");
    ok &= check(!SkFILEStream_readPackedUInt(nullptr, nullptr), "FILEStream readPackedUInt null");
    ok &= check(SkFILEStream_getMemoryBase(nullptr) == nullptr, "FILEStream getMemoryBase null");
    ok &= check(SkFILEStream_Make(nullptr) == 0, "FILEStream Make null path");

    reskia_file_stream_t *missing = SkFILEStream_new("/__reskia_missing_file_stream_invalid_input__");
    ok &= check(missing != nullptr, "FILEStream new missing path returns object");
    ok &= check(!SkFILEStream_isValid(missing), "FILEStream missing path invalid");
    uint8_t byte = 0;
    ok &= check(SkFILEStream_read(missing, nullptr, 1) == 0, "FILEStream read null buffer nonzero size");
    ok &= check(SkFILEStream_peek(missing, nullptr, 1) == 0, "FILEStream peek null buffer nonzero size");
    SkFILEStream_delete(missing);

    ok &= check(SkFILEWStream_new(nullptr) == nullptr, "FILEWStream new null path");
    SkFILEWStream_delete(nullptr);
    SkFILEWStream_flush(nullptr);
    SkFILEWStream_fsync(nullptr);
    ok &= check(!SkFILEWStream_isValid(nullptr), "FILEWStream isValid null");
    ok &= check(!SkFILEWStream_write(nullptr, &byte, 1), "FILEWStream write null stream");
    ok &= check(SkFILEWStream_bytesWritten(nullptr) == 0, "FILEWStream bytesWritten null");
    ok &= check(!SkFILEWStream_write8(nullptr, 1), "FILEWStream write8 null");
    ok &= check(!SkFILEWStream_write16(nullptr, 1), "FILEWStream write16 null");
    ok &= check(!SkFILEWStream_write32(nullptr, 1), "FILEWStream write32 null");
    ok &= check(!SkFILEWStream_writeText(nullptr, "x"), "FILEWStream writeText null stream");
    ok &= check(!SkFILEWStream_newline(nullptr), "FILEWStream newline null");
    ok &= check(!SkFILEWStream_writeDecAsText(nullptr, 1), "FILEWStream writeDecAsText null");
    ok &= check(!SkFILEWStream_writeBigDecAsText(nullptr, 1, 1), "FILEWStream writeBigDecAsText null");
    ok &= check(!SkFILEWStream_writeHexAsText(nullptr, 1, 1), "FILEWStream writeHexAsText null");
    ok &= check(!SkFILEWStream_writeScalarAsText(nullptr, 1.0f), "FILEWStream writeScalarAsText null");
    ok &= check(!SkFILEWStream_writeBool(nullptr, true), "FILEWStream writeBool null");
    ok &= check(!SkFILEWStream_writeScalar(nullptr, 1.0f), "FILEWStream writeScalar null");
    ok &= check(!SkFILEWStream_writePackedUInt(nullptr, 1), "FILEWStream writePackedUInt null");
    ok &= check(!SkFILEWStream_writeStream(nullptr, nullptr, 0), "FILEWStream writeStream null");

    reskia_file_w_stream_t *invalid_output = SkFILEWStream_new("/__reskia_missing_dir__/out.bin");
    ok &= check(invalid_output != nullptr, "FILEWStream new invalid path returns object");
    ok &= check(!SkFILEWStream_isValid(invalid_output), "FILEWStream invalid path invalid");
    ok &= check(!SkFILEWStream_write(invalid_output, nullptr, 1), "FILEWStream write null buffer nonzero size");
    ok &= check(!SkFILEWStream_writeText(invalid_output, nullptr), "FILEWStream writeText null text");
    ok &= check(!SkFILEWStream_writeStream(invalid_output, nullptr, 0), "FILEWStream writeStream null input");
    SkFILEWStream_delete(invalid_output);

    ok &= check(SkFILEWStream_SizeOfPackedUInt(0) > 0, "FILEWStream SizeOfPackedUInt");
    return ok ? 0 : 1;
}
