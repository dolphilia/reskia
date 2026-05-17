#include "capi/sk_codec.h"
#include "capi/sk_png_chunk_reader.h"

#include <cstdint>
#include <cstdio>

namespace {

constexpr int32_t kInvalidParameters = 5;
constexpr int32_t kInvalidInput = 6;

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[codec-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

struct ChunkReaderState {
    int calls = 0;
    int releases = 0;
};

bool read_chunk_continue(const char tag[4], const void *data, size_t length, void *user_data) {
    auto *state = static_cast<ChunkReaderState *>(user_data);
    if (state != nullptr) {
        state->calls += 1;
    }
    return tag != nullptr && data != nullptr && length == 3;
}

void release_chunk_reader_state(void *user_data) {
    auto *state = static_cast<ChunkReaderState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

}  // namespace

int main() {
    SkCodec_delete(nullptr);

    bool ok = true;
    ok &= check(SkCodec_getInfo(nullptr) == 0, "getInfo null");
    ok &= check(SkCodec_dimensions(nullptr) == 0, "dimensions null");
    ok &= check(SkCodec_bounds(nullptr) == 0, "bounds null");
    ok &= check(SkCodec_getICCProfile(nullptr) == nullptr, "getICCProfile null");
    ok &= check(SkCodec_getOrigin(nullptr) == -1, "getOrigin null");
    ok &= check(SkCodec_getScaledDimensions(nullptr, 1.0f) == 0, "getScaledDimensions null");
    ok &= check(!SkCodec_getValidSubset(nullptr, nullptr), "getValidSubset null");
    ok &= check(SkCodec_getEncodedFormat(nullptr) == -1, "getEncodedFormat null");

    ok &= check(SkCodec_getPixels(nullptr, nullptr, nullptr, 0, nullptr) == kInvalidParameters, "getPixels null");
    ok &= check(SkCodec_getPixelsWithoutOptions(nullptr, nullptr, nullptr, 0) == kInvalidParameters, "getPixelsWithoutOptions null");
    ok &= check(SkCodec_getPixelsFromPixmap(nullptr, nullptr, nullptr) == kInvalidParameters, "getPixelsFromPixmap null");
    ok &= check(SkCodec_getImage(nullptr, nullptr, nullptr) == 0, "getImage null");
    ok &= check(SkCodec_getImageDefault(nullptr) == 0, "getImageDefault null");
    ok &= check(!SkCodec_queryYUVAInfo(nullptr, nullptr, nullptr), "queryYUVAInfo null");
    ok &= check(SkCodec_getYUVAPlanes(nullptr, nullptr) == kInvalidInput, "getYUVAPlanes null");

    ok &= check(SkCodec_startIncrementalDecode(nullptr, nullptr, nullptr, 0, nullptr) == kInvalidParameters, "startIncrementalDecode null");
    ok &= check(SkCodec_startIncrementalDecodeWithoutOptions(nullptr, nullptr, nullptr, 0) == kInvalidParameters, "startIncrementalDecodeWithoutOptions null");
    ok &= check(SkCodec_incrementalDecode(nullptr, nullptr) == kInvalidParameters, "incrementalDecode null");
    ok &= check(SkCodec_startScanlineDecode(nullptr, nullptr, nullptr) == kInvalidParameters, "startScanlineDecode null");
    ok &= check(SkCodec_startScanlineDecodeWithoutOptions(nullptr, nullptr) == kInvalidParameters, "startScanlineDecodeWithoutOptions null");
    ok &= check(SkCodec_getScanlines(nullptr, nullptr, 0, 0) == 0, "getScanlines null");
    ok &= check(!SkCodec_skipScanlines(nullptr, 0), "skipScanlines null");
    ok &= check(SkCodec_getScanlineOrder(nullptr) == -1, "getScanlineOrder null");
    ok &= check(SkCodec_nextScanline(nullptr) == -1, "nextScanline null");
    ok &= check(SkCodec_outputScanline(nullptr, 0) == -1, "outputScanline null");
    ok &= check(SkCodec_getFrameCount(nullptr) == 0, "getFrameCount null");
    ok &= check(!SkCodec_getFrameInfo(nullptr, -1, nullptr), "getFrameInfo null");
    ok &= check(SkCodec_getFrameInfoList(nullptr) == 0, "getFrameInfoList null");
    ok &= check(SkCodec_getRepetitionCount(nullptr) == 0, "getRepetitionCount null");

    int32_t result = -1;
    ok &= check(SkCodec_MakeFromStream(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr, 0) == 0, "MakeFromStream rejects invalid stream");
    ok &= check(result == kInvalidInput, "MakeFromStream invalid stream result");
    result = -1;
    ok &= check(SkCodec_MakeFromStream(0, reinterpret_cast<reskia_codec_result_t *>(&result), nullptr, 99) == 0, "MakeFromStream rejects invalid policy");
    ok &= check(result == kInvalidParameters, "MakeFromStream invalid policy result");
    ok &= check(SkCodec_MakeFromData(0, nullptr) == 0, "MakeFromData rejects invalid data");

    ok &= check(!SkPngChunkReader_readChunk(nullptr, "abcd", nullptr, 0), "png chunk reader null read");
    auto *null_callback_reader = SkPngChunkReader_new(nullptr, nullptr, nullptr);
    ok &= check(null_callback_reader != nullptr, "png chunk reader new without callback");
    ok &= check(SkPngChunkReader_readChunk(null_callback_reader, "abcd", nullptr, 0), "png chunk reader null callback continues");
    SkPngChunkReader_release(null_callback_reader);

    ChunkReaderState chunk_state;
    auto *reader = SkPngChunkReader_new(read_chunk_continue, &chunk_state, release_chunk_reader_state);
    ok &= check(reader != nullptr, "png chunk reader new");
    const uint8_t payload[3] = {1, 2, 3};
    ok &= check(SkPngChunkReader_readChunk(reader, "rSkI", payload, sizeof(payload)), "png chunk reader callback");
    ok &= check(chunk_state.calls == 1, "png chunk reader callback count");
    SkPngChunkReader_retain(reader);
    SkPngChunkReader_release(reader);
    ok &= check(chunk_state.releases == 0, "png chunk reader retained release keeps alive");
    SkPngChunkReader_release(reader);
    ok &= check(chunk_state.releases == 1, "png chunk reader final release callback");

    return ok ? 0 : 1;
}
