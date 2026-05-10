#include "capi/sk_open_type_svg_decoder.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[open-type-svg-decoder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    SkOpenTypeSVGDecoder_delete(nullptr);

    ok &= check(SkOpenTypeSVGDecoder_approximateSize(nullptr) == 0, "approximateSize null");
    ok &= check(!SkOpenTypeSVGDecoder_render(nullptr, nullptr, 1000, 0, 0, 0), "render null decoder and canvas");

    return ok ? 0 : 1;
}
