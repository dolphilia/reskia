#include <cstdio>

#include "capi/sk_canvas.h"
#include "capi/sk_dynamic_memory_w_stream.h"
#include "capi/sk_svg_canvas.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[svg-canvas-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_svg_canvas() {
    if (!check(SkSVGCanvas_Make(0.0f, 0.0f, 16.0f, 16.0f, nullptr, 0) == nullptr,
               "SkSVGCanvas_Make null stream")) {
        return false;
    }

    reskia_dynamic_memory_w_stream_t *stream = SkDynamicMemoryWStream_new();
    if (!check(stream != nullptr, "SkDynamicMemoryWStream_new")) {
        return false;
    }

    reskia_canvas_t *canvas = SkSVGCanvas_Make(
            0.0f, 0.0f, 64.0f, 32.0f,
            reinterpret_cast<reskia_w_stream_t *>(stream),
            RESKIA_SVG_CANVAS_NO_PRETTY_XML_FLAG);
    if (!check(canvas != nullptr, "SkSVGCanvas_Make")) {
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    SkCanvas_clearColor(canvas, 0xff336699);
    SkCanvas_delete(canvas);

    const size_t bytes_written = SkDynamicMemoryWStream_bytesWritten(stream);
    SkDynamicMemoryWStream_delete(stream);
    return check(bytes_written > 0, "SVG canvas wrote bytes after delete");
}

}  // namespace

int main() {
    return smoke_svg_canvas() ? 0 : 1;
}
