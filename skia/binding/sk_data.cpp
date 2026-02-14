//
// Created by dolphilia on 2024/01/08.
//

#include "sk_data.h"

#include "include/core/SkData.h"

#include "../static/static_sk_data.h"

#include "../static/static_sk_data-internal.h"

extern "C" {

void SkData_delete(void *sk_data) {
    static_cast<SkData *>(sk_data)->unref();
}

size_t SkData_size(void *sk_data) {
    return static_cast<SkData *>(sk_data)->size();
}

bool SkData_isEmpty(void *sk_data) {
    return static_cast<SkData *>(sk_data)->isEmpty();
}

const void * SkData_data(void *sk_data) {
    return static_cast<SkData *>(sk_data)->data();
}

const uint8_t * SkData_bytes(void *sk_data) {
    return static_cast<SkData *>(sk_data)->bytes();
}

void * SkData_writable_data(void *sk_data) {
    return static_cast<SkData *>(sk_data)->writable_data();
}

size_t SkData_copyRange(void *sk_data, size_t offset, size_t length, void *buffer) {
    return static_cast<SkData *>(sk_data)->copyRange(offset, length, buffer);
}

bool SkData_equals(void *sk_data, const void *other) {
    return static_cast<SkData *>(sk_data)->equals(static_cast<const SkData *>(other));
}

bool SkData_unique(void *sk_data) {
    return static_cast<SkData *>(sk_data)->unique();
}

void SkData_ref(void *sk_data) {
    return static_cast<SkData *>(sk_data)->ref();
}

void SkData_unref(void *sk_data) {
    static_cast<SkData *>(sk_data)->unref();
}

void SkData_deref(void *sk_data) {
    static_cast<SkData *>(sk_data)->deref();
}

bool SkData_refCntGreaterThan(void *sk_data, unsigned int threadIsolatedTestCnt) {
    return static_cast<SkData *>(sk_data)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_data_t SkData_MakeWithCopy(const void *data, size_t length) {
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

sk_data_t SkData_MakeWithProc(const void *ptr, size_t length, void(*proc)(const void *ptr, void *context), void *ctx) {
    return static_sk_data_make(SkData::MakeWithProc(ptr, length, proc, ctx));
}

sk_data_t SkData_MakeWithoutCopy(const void *data, size_t length) {
    return static_sk_data_make(SkData::MakeWithoutCopy(data, length));
}

sk_data_t SkData_MakeFromMalloc(const void *data, size_t length) {
    return static_sk_data_make(SkData::MakeFromMalloc(data, length));
}

sk_data_t SkData_MakeFromFileName(const char path[]) {
    return static_sk_data_make(SkData::MakeFromFileName(path));
}

sk_data_t SkData_MakeFromFILE(void *f) {
    return static_sk_data_make(SkData::MakeFromFILE(static_cast<FILE *>(f)));
}

sk_data_t SkData_MakeFromFD(int fd) {
    return static_sk_data_make(SkData::MakeFromFD(fd));
}

sk_data_t SkData_MakeFromStream(void *stream, size_t size) {
    return static_sk_data_make(SkData::MakeFromStream(static_cast<SkStream *>(stream), size));
}

sk_data_t SkData_MakeSubset(const void *src, size_t offset, size_t length) {
    return static_sk_data_make(SkData::MakeSubset(static_cast<const SkData *>(src), offset, length));
}

sk_data_t SkData_MakeEmpty() {
    return static_sk_data_make(SkData::MakeEmpty());
}

}
