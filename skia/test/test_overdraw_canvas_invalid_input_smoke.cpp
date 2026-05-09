#include "capi/sk_overdraw_canvas.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[overdraw-canvas-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkOverdrawCanvas_new(nullptr) == nullptr, "SkOverdrawCanvas_new(nullptr)")) {
        return 1;
    }

    SkOverdrawCanvas_delete(nullptr);
    SkOverdrawCanvas_onDrawTextBlob(nullptr, nullptr, 0.0f, 0.0f, nullptr);
    SkOverdrawCanvas_onDrawGlyphRunList(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawPatch(nullptr, nullptr, nullptr, nullptr, 0, nullptr);
    SkOverdrawCanvas_onDrawPaint(nullptr, nullptr);
    SkOverdrawCanvas_onDrawBehind(nullptr, nullptr);
    SkOverdrawCanvas_onDrawRect(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawRegion(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawOval(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawArc(nullptr, nullptr, 0.0f, 0.0f, false, nullptr);
    SkOverdrawCanvas_onDrawDRRect(nullptr, nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawRRect(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawPoints(nullptr, 0, 0, nullptr, nullptr);
    SkOverdrawCanvas_onDrawVerticesObject(nullptr, nullptr, 0, nullptr);
    SkOverdrawCanvas_onDrawPath(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawImage2(nullptr, nullptr, 0.0f, 0.0f, nullptr, nullptr);
    SkOverdrawCanvas_onDrawImageRect2(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0);
    SkOverdrawCanvas_onDrawImageLattice2(nullptr, nullptr, nullptr, nullptr, 0, nullptr);
    SkOverdrawCanvas_onDrawAtlas2(nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawDrawable(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawPicture(nullptr, nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawAnnotation(nullptr, nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawShadowRec(nullptr, nullptr, nullptr);
    SkOverdrawCanvas_onDrawEdgeAAQuad(nullptr, nullptr, nullptr, 0, nullptr, 0);
    SkOverdrawCanvas_onDrawEdgeAAImageSet2(nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    return 0;
}
