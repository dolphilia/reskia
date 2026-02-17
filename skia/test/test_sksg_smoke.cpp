#include <cstdio>

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"
#include "modules/sksg/include/SkSGDraw.h"
#include "modules/sksg/include/SkSGGroup.h"
#include "modules/sksg/include/SkSGPaint.h"
#include "modules/sksg/include/SkSGRect.h"
#include "modules/sksg/include/SkSGScene.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[sksg-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_sksg_minimal() {
    auto root = sksg::Group::Make();
    if (!check(root != nullptr, "sksg::Group::Make")) {
        return false;
    }

    auto rect = sksg::Rect::Make(SkRect::MakeXYWH(8.0f, 8.0f, 48.0f, 48.0f));
    if (!check(rect != nullptr, "sksg::Rect::Make")) {
        return false;
    }

    auto color = sksg::Color::Make(SK_ColorRED);
    if (!check(color != nullptr, "sksg::Color::Make")) {
        return false;
    }

    auto draw = sksg::Draw::Make(rect, color);
    if (!check(draw != nullptr, "sksg::Draw::Make")) {
        return false;
    }
    root->addChild(draw);

    auto scene = sksg::Scene::Make(root);
    if (!check(scene != nullptr, "sksg::Scene::Make")) {
        return false;
    }

    sk_sp<SkSurface> surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(64, 64));
    if (!check(surface != nullptr, "SkSurfaces::Raster")) {
        return false;
    }

    SkCanvas* canvas = surface->getCanvas();
    if (!check(canvas != nullptr, "SkSurface::getCanvas")) {
        return false;
    }

    canvas->clear(SK_ColorTRANSPARENT);
    scene->revalidate();
    scene->render(canvas);
    return true;
}

}  // namespace

int main() {
    if (!smoke_sksg_minimal()) {
        return 1;
    }

    std::fprintf(stdout, "[sksg-smoke] PASS\n");
    return 0;
}
