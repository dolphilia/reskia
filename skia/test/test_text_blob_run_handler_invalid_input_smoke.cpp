#include "capi/sk_text_blob_builder_run_handler.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[text-blob-run-handler-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    SkTextBlobBuilderRunHandler_delete(nullptr);
    SkTextBlobBuilderRunHandler_beginLine(nullptr);
    SkTextBlobBuilderRunHandler_runInfo(nullptr, nullptr);
    SkTextBlobBuilderRunHandler_commitRunInfo(nullptr);
    SkTextBlobBuilderRunHandler_commitRunBuffer(nullptr, nullptr);
    SkTextBlobBuilderRunHandler_commitLine(nullptr);

    ok &= check(SkTextBlobBuilderRunHandler_makeBlob(nullptr) == 0, "makeBlob null");
    ok &= check(SkTextBlobBuilderRunHandler_endPoint(nullptr) == 0, "endPoint null");
    ok &= check(SkTextBlobBuilderRunHandler_runBuffer(nullptr, nullptr) == 0, "runBuffer null");

    SkTextBlobBuilderRunHandler *handler = SkTextBlobBuilderRunHandler_new(nullptr, 0);
    ok &= check(handler != nullptr, "new null text");
    if (handler != nullptr) {
        ok &= check(SkTextBlobBuilderRunHandler_makeBlob(handler) == 0, "makeBlob empty");
        SkTextBlobBuilderRunHandler_delete(handler);
    }

    return ok ? 0 : 1;
}
