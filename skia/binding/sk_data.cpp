//
// Created by dolphilia on 2024/01/08.
//

#include "sk_data.h"

#include "include/core/SkData.h"

#include "../static/static_sk_data.h"

#include "../static/static_sk_data-internal.h"

extern "C" {

void SkData_delete(reskia_data_t *sk_data) {
    reinterpret_cast<SkData *>(sk_data)->unref();
}

size_t SkData_size(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->size();
}

bool SkData_isEmpty(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->isEmpty();
}

const uint8_t * SkData_data(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->bytes();
}

const uint8_t * SkData_bytes(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->bytes();
}

uint8_t * SkData_writable_data(reskia_data_t *sk_data) {
    return reinterpret_cast<uint8_t *>(reinterpret_cast<SkData *>(sk_data)->writable_data());
}

size_t SkData_copyRange(reskia_data_t *sk_data, size_t offset, size_t length, uint8_t *buffer) {
    return reinterpret_cast<SkData *>(sk_data)->copyRange(offset, length, buffer);
}

bool SkData_equals(reskia_data_t *sk_data, const reskia_data_t *other) {
    return reinterpret_cast<SkData *>(sk_data)->equals(reinterpret_cast<const SkData *>(other));
}

bool SkData_unique(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->unique();
}

void SkData_ref(reskia_data_t *sk_data) {
    return reinterpret_cast<SkData *>(sk_data)->ref();
}

void SkData_unref(reskia_data_t *sk_data) {
    reinterpret_cast<SkData *>(sk_data)->unref();
}

void SkData_deref(reskia_data_t *sk_data) {
    reinterpret_cast<SkData *>(sk_data)->deref();
}

bool SkData_refCntGreaterThan(reskia_data_t *sk_data, int32_t threadIsolatedTestCnt) {
    return reinterpret_cast<SkData *>(sk_data)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_data_t SkData_MakeWithCopy(const uint8_t *data, size_t length) {
    return static_sk_data_make(SkData::MakeWithCopy(data, length));
}

sk_data_t SkData_MakeUninitialized(size_t length) {
    return static_sk_data_make(SkData::MakeUninitialized(length));
}

sk_data_t SkData_MakeZeroInitialized(size_t length) {
    return static_sk_data_make(SkData::MakeZeroInitialized(length));
}

sk_data_t SkData_MakeWithCString(const char cstr[]) {
    return static_sk_data_make(SkData::MakeWithCString(cstr));
}

sk_data_t SkData_MakeWithProc(const uint8_t *ptr, size_t length, void(*proc)(const void *ptr, void *context), void *ctx) {
    return static_sk_data_make(SkData::MakeWithProc(ptr, length, proc, ctx));
}

sk_data_t SkData_MakeWithoutCopy(const uint8_t *data, size_t length) {
    return static_sk_data_make(SkData::MakeWithoutCopy(data, length));
}

sk_data_t SkData_MakeFromMalloc(const uint8_t *data, size_t length) {
    return static_sk_data_make(SkData::MakeFromMalloc(data, length));
}

sk_data_t SkData_MakeFromFileName(const char path[]) {
    return static_sk_data_make(SkData::MakeFromFileName(path));
}

sk_data_t SkData_MakeFromFILE(reskia_file_t *f) {
    return static_sk_data_make(SkData::MakeFromFILE(reinterpret_cast<FILE *>(f)));
}

sk_data_t SkData_MakeFromFD(int fd) {
    return static_sk_data_make(SkData::MakeFromFD(fd));
}

sk_data_t SkData_MakeFromStream(reskia_stream_t *stream, size_t size) {
    return static_sk_data_make(SkData::MakeFromStream(reinterpret_cast<SkStream *>(stream), size));
}

sk_data_t SkData_MakeSubset(const reskia_data_t *src, size_t offset, size_t length) {
    return static_sk_data_make(SkData::MakeSubset(reinterpret_cast<const SkData *>(src), offset, length));
}

sk_data_t SkData_MakeEmpty() {
    return static_sk_data_make(SkData::MakeEmpty());
}

}
