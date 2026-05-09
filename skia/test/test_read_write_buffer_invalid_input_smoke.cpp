#include "capi/sk_read_buffer.h"
#include "capi/sk_write_buffer.h"

#include <cstdint>
#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[read-write-buffer-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkReadBuffer_delete(nullptr);
    if (!check(SkReadBuffer_newWithDataAndSize(nullptr, 4) == nullptr, "constructor rejects null data with size")) {
        return 1;
    }
    SkReadBuffer_setTypefaceArray(nullptr, nullptr, 0);
    SkReadBuffer_setFactoryPlayback(nullptr, nullptr, 0);
    SkReadBuffer_setDeserialProcs(nullptr, nullptr);
    SkReadBuffer_setAllowSkSL(nullptr, true);
    SkReadBuffer_setMemory(nullptr, nullptr, 4);
    SkReadBuffer_setVersion(nullptr, 1);

    if (!check(!SkReadBuffer_isVersionLT(nullptr, 1), "isVersionLT null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_isVersionLT(nullptr, 0), "isVersionLT invalid version")) {
        return 1;
    }
    if (!check(SkReadBuffer_getVersion(nullptr) == 0, "getVersion null")) {
        return 1;
    }
    if (!check(SkReadBuffer_size(nullptr) == 0, "size null")) {
        return 1;
    }
    if (!check(SkReadBuffer_offset(nullptr) == 0, "offset null")) {
        return 1;
    }
    if (!check(SkReadBuffer_eof(nullptr), "eof null")) {
        return 1;
    }
    if (!check(SkReadBuffer_skip(nullptr, 4) == nullptr, "skip null")) {
        return 1;
    }
    if (!check(SkReadBuffer_skipCount(nullptr, 1, 4) == nullptr, "skipCount null")) {
        return 1;
    }
    if (!check(SkReadBuffer_available(nullptr) == 0, "available null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readBool(nullptr), "readBool null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readColor(nullptr) == 0, "readColor null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readInt(nullptr) == 0, "readInt null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readScalar(nullptr) == 0, "readScalar null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readUInt(nullptr) == 0, "readUInt null")) {
        return 1;
    }
    if (!check(SkReadBuffer_read32(nullptr) == 0, "read32 null")) {
        return 1;
    }
    if (!check(SkReadBuffer_peekByte(nullptr) == 0, "peekByte null")) {
        return 1;
    }
    SkReadBuffer_readString(nullptr, nullptr);
    SkReadBuffer_readColor4f(nullptr, nullptr);
    SkReadBuffer_readPoint(nullptr, nullptr);
    if (!check(SkReadBuffer_readPointValue(nullptr) == 0, "readPointValue null")) {
        return 1;
    }
    SkReadBuffer_readPoint3(nullptr, nullptr);
    SkReadBuffer_read(nullptr, nullptr);
    SkReadBuffer_readMatrix(nullptr, nullptr);
    SkReadBuffer_readIRect(nullptr, nullptr);
    SkReadBuffer_readRect(nullptr, nullptr);
    if (!check(SkReadBuffer_readRectValue(nullptr) == 0, "readRectValue null")) {
        return 1;
    }
    SkReadBuffer_readRRect(nullptr, nullptr);
    SkReadBuffer_readRegion(nullptr, nullptr);
    SkReadBuffer_readPath(nullptr, nullptr);
    if (!check(SkReadBuffer_readPaint(nullptr) == 0, "readPaint null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readRawFlattenable(nullptr) == nullptr, "readRawFlattenable null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readFlattenable(nullptr, 0) == nullptr, "readFlattenable null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readColorFilter(nullptr) == 0, "readColorFilter null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readImageFilter(nullptr) == 0, "readImageFilter null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readBlender(nullptr) == 0, "readBlender null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readMaskFilter(nullptr) == 0, "readMaskFilter null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readPathEffect(nullptr) == 0, "readPathEffect null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readShader(nullptr) == 0, "readShader null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readPad32(nullptr, nullptr, 0), "readPad32 null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readByteArray(nullptr, nullptr, 0), "readByteArray null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readColorArray(nullptr, nullptr, 0), "readColorArray null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readColor4fArray(nullptr, nullptr, 0), "readColor4fArray null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readIntArray(nullptr, nullptr, 0), "readIntArray null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readPointArray(nullptr, nullptr, 0), "readPointArray null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_readScalarArray(nullptr, nullptr, 0), "readScalarArray null")) {
        return 1;
    }
    if (!check(SkReadBuffer_skipByteArray(nullptr, nullptr) == nullptr, "skipByteArray null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readByteArrayAsData(nullptr) == 0, "readByteArrayAsData null")) {
        return 1;
    }
    if (!check(SkReadBuffer_getArrayCount(nullptr) == 0, "getArrayCount null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readImage(nullptr) == 0, "readImage null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readTypeface(nullptr) == 0, "readTypeface null")) {
        return 1;
    }
    if (!check(SkReadBuffer_getDeserialProcs(nullptr) == nullptr, "getDeserialProcs null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_allowSkSL(nullptr), "allowSkSL null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_validate(nullptr, true), "validate null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_isValid(nullptr), "isValid null")) {
        return 1;
    }
    if (!check(!SkReadBuffer_validateIndex(nullptr, 0, 1), "validateIndex null")) {
        return 1;
    }
    if (!check(SkReadBuffer_checkInt(nullptr, 0, 1) == 0, "checkInt null")) {
        return 1;
    }
    if (!check(SkReadBuffer_checkInt(nullptr, 2, 1) == 0, "checkInt invalid range")) {
        return 1;
    }
    if (!check(SkReadBuffer_checkFilterQuality(nullptr) == -1, "checkFilterQuality null")) {
        return 1;
    }
    if (!check(SkReadBuffer_readSampling(nullptr) == 0, "readSampling null")) {
        return 1;
    }

    reskia_read_buffer_t *readBuffer = SkReadBuffer_new();
    if (!check(readBuffer != nullptr, "SkReadBuffer_new")) {
        return 1;
    }
    SkReadBuffer_setTypefaceArray(readBuffer, nullptr, 0);
    SkReadBuffer_setFactoryPlayback(readBuffer, nullptr, 0);
    SkReadBuffer_setDeserialProcs(readBuffer, nullptr);
    if (!check(SkReadBuffer_readFlattenable(readBuffer, -1) == nullptr, "readFlattenable invalid type")) {
        SkReadBuffer_delete(readBuffer);
        return 1;
    }
    SkReadBuffer_delete(readBuffer);

    SkWriteBuffer_delete(nullptr);
    SkWriteBuffer_writePad32(nullptr, nullptr, 0);
    SkWriteBuffer_writeByteArray(nullptr, nullptr, 0);
    SkWriteBuffer_writeDataAsByteArray(nullptr, nullptr);
    SkWriteBuffer_writeBool(nullptr, false);
    SkWriteBuffer_writeScalar(nullptr, 0);
    SkWriteBuffer_writeScalarArray(nullptr, nullptr, 0);
    SkWriteBuffer_writeInt(nullptr, 0);
    SkWriteBuffer_writeIntArray(nullptr, nullptr, 0);
    SkWriteBuffer_writeUInt(nullptr, 0);
    SkWriteBuffer_write32(nullptr, 0);
    SkWriteBuffer_writeString(nullptr, 0);
    SkWriteBuffer_writeFlattenable(nullptr, nullptr);
    SkWriteBuffer_writeColor(nullptr, 0);
    SkWriteBuffer_writeColorArray(nullptr, nullptr, 0);
    SkWriteBuffer_writeColor4f(nullptr, nullptr);
    SkWriteBuffer_writeColor4fArray(nullptr, nullptr, 0);
    SkWriteBuffer_writePoint(nullptr, nullptr);
    SkWriteBuffer_writePointArray(nullptr, nullptr, 0);
    SkWriteBuffer_writePoint3(nullptr, nullptr);
    SkWriteBuffer_write(nullptr, nullptr);
    SkWriteBuffer_writeMatrix(nullptr, nullptr);
    SkWriteBuffer_writeIRect(nullptr, nullptr);
    SkWriteBuffer_writeRect(nullptr, nullptr);
    SkWriteBuffer_writeRegion(nullptr, nullptr);
    SkWriteBuffer_writeSampling(nullptr, nullptr);
    SkWriteBuffer_writePath(nullptr, nullptr);
    SkWriteBuffer_writeImage(nullptr, nullptr);
    SkWriteBuffer_writeTypeface(nullptr, nullptr);
    SkWriteBuffer_writePaint(nullptr, nullptr);
    if (!check(SkWriteBuffer_writeStream(nullptr, nullptr, 0) == 0, "writeStream null")) {
        return 1;
    }
    if (!check(SkWriteBuffer_serialProcs(nullptr) == nullptr, "serialProcs null")) {
        return 1;
    }

    return 0;
}
