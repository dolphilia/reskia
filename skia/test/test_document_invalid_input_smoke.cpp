#include "capi/sk_document.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[document-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkDocument_release(nullptr);
    SkDocument_endPage(nullptr);
    SkDocument_close(nullptr);
    SkDocument_abort(nullptr);
    SkDocument_ref(nullptr);
    SkDocument_unref(nullptr);

    if (!check(SkDocument_beginPage(nullptr, 100.0f, 100.0f, nullptr) == nullptr, "beginPage null document")) {
        return 1;
    }
    if (!check(!SkDocument_unique(nullptr), "unique null document")) {
        return 2;
    }

    return 0;
}
