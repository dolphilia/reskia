//
// Created by dolphilia on 2024/01/11.
//

#include "sk_w_stream.h"

#include "include/core/SkStream.h"

extern "C" {

reskia_w_stream_t *SkNullWStream_new() {
    return reinterpret_cast<reskia_w_stream_t *>(new SkNullWStream());
}

bool SkNullWStream_write(reskia_w_stream_t *w_stream, const void *buffer, size_t size) {
    if (w_stream == nullptr || (buffer == nullptr && size > 0)) {
        return false;
    }
    return reinterpret_cast<SkNullWStream *>(w_stream)->write(buffer, size);
}

void SkNullWStream_flush(reskia_w_stream_t *w_stream) {
    if (w_stream == nullptr) {
        return;
    }
    reinterpret_cast<SkNullWStream *>(w_stream)->flush();
}

size_t SkNullWStream_bytesWritten(reskia_w_stream_t *w_stream) {
    if (w_stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkNullWStream *>(w_stream)->bytesWritten();
}

void SkWStream_delete(reskia_w_stream_t *w_stream) {
    delete reinterpret_cast<SkWStream *>(w_stream);
}

bool SkWStream_write(reskia_w_stream_t *w_stream, const void *buffer, size_t size) {
    if (w_stream == nullptr || (buffer == nullptr && size > 0)) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->write(buffer, size);
}

void SkWStream_flush(reskia_w_stream_t *w_stream) {
    if (w_stream == nullptr) {
        return;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->flush();
}

size_t SkWStream_bytesWritten(reskia_w_stream_t *w_stream) {
    if (w_stream == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->bytesWritten();
}

bool SkWStream_write8(reskia_w_stream_t *w_stream, uint32_t value) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->write8(value);
}

bool SkWStream_write16(reskia_w_stream_t *w_stream, uint32_t value) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->write16(value);
}

bool SkWStream_write32(reskia_w_stream_t *w_stream, uint32_t v) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->write32(v);
}

bool SkWStream_writeText(reskia_w_stream_t *w_stream, const char text[]) {
    if (w_stream == nullptr || text == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeText(text);
}

bool SkWStream_newline(reskia_w_stream_t *w_stream) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->newline();
}

bool SkWStream_writeDecAsText(reskia_w_stream_t *w_stream, int32_t i) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeDecAsText(i);
}

bool SkWStream_writeBigDecAsText(reskia_w_stream_t *w_stream, int64_t i, int minDigits) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeBigDecAsText(i, minDigits);
}

bool SkWStream_writeHexAsText(reskia_w_stream_t *w_stream, uint32_t i, int minDigits) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeHexAsText(i, minDigits);
}

bool SkWStream_writeScalarAsText(reskia_w_stream_t *w_stream, float v) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeScalarAsText(v);
}

bool SkWStream_writeBool(reskia_w_stream_t *w_stream, bool v) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeBool(v);
}

bool SkWStream_writeScalar(reskia_w_stream_t *w_stream, float v) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeScalar(v);
}

bool SkWStream_writePackedUInt(reskia_w_stream_t *w_stream, size_t size) {
    if (w_stream == nullptr) {
        return false;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writePackedUInt(size);
}

bool SkWStream_writeStream(reskia_w_stream_t *w_stream, reskia_stream_t *input, size_t length) {
    if (w_stream == nullptr || (input == nullptr && length > 0)) {
        return false;
    }
    if (input == nullptr) {
        return true;
    }
    return reinterpret_cast<SkWStream *>(w_stream)->writeStream(reinterpret_cast<SkStream *>(input), length);
}

// static

int SkWStream_SizeOfPackedUInt(size_t value) {
    return SkWStream::SizeOfPackedUInt(value);
}

}
