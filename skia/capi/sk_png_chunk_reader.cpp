#include "sk_png_chunk_reader.h"

#include "include/codec/SkPngChunkReader.h"

namespace {

class ReskiaPngChunkReader final : public SkPngChunkReader {
public:
    ReskiaPngChunkReader(
            reskia_png_chunk_reader_read_chunk_proc_t read_chunk,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : read_chunk_(read_chunk)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaPngChunkReader() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    bool readChunk(const char tag[], const void *data, size_t length) override {
        if (read_chunk_ == nullptr) {
            return true;
        }
        return read_chunk_(tag, data, length, user_data_);
    }

private:
    reskia_png_chunk_reader_read_chunk_proc_t read_chunk_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

SkPngChunkReader *to_reader(reskia_png_chunk_reader_t *reader) {
    return reinterpret_cast<SkPngChunkReader *>(reader);
}

} // namespace

extern "C" {

reskia_png_chunk_reader_t *SkPngChunkReader_new(
        reskia_png_chunk_reader_read_chunk_proc_t read_chunk,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_png_chunk_reader_t *>(
            new ReskiaPngChunkReader(read_chunk, user_data, release_proc));
}

void SkPngChunkReader_retain(reskia_png_chunk_reader_t *reader) {
    SkPngChunkReader *native = to_reader(reader);
    if (native != nullptr) {
        native->ref();
    }
}

void SkPngChunkReader_release(reskia_png_chunk_reader_t *reader) {
    SkPngChunkReader *native = to_reader(reader);
    if (native != nullptr) {
        native->unref();
    }
}

bool SkPngChunkReader_readChunk(
        reskia_png_chunk_reader_t *reader,
        const char tag[4],
        const void *data,
        size_t length) {
    SkPngChunkReader *native = to_reader(reader);
    if (native == nullptr) {
        return false;
    }
    return native->readChunk(tag, data, length);
}

} // extern "C"
