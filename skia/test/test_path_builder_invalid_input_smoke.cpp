#include "capi/sk_path_builder.h"
#include "handles/static_sk_path.h"
#include "handles/static_sk_rect.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[path-builder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    SkPathBuilder_delete(nullptr);
    SkPathBuilder_incReserve(nullptr, 1, 1);
    SkPathBuilder_incReservePoints(nullptr, 1);

    ok &= check(SkPathBuilder_newFromPath(nullptr) == nullptr, "newFromPath null");
    ok &= check(SkPathBuilder_newCopy(nullptr) == nullptr, "newCopy null");
    ok &= check(SkPathBuilder_fillType(nullptr) == 0, "fillType null");
    ok &= check(SkPathBuilder_computeBounds(nullptr) == 0, "computeBounds null");
    ok &= check(SkPathBuilder_snapshot(nullptr) == 0, "snapshot null");
    ok &= check(SkPathBuilder_detach(nullptr) == 0, "detach null");
    ok &= check(SkPathBuilder_setFillType(nullptr, 0) == nullptr, "setFillType null");
    ok &= check(SkPathBuilder_setIsVolatile(nullptr, true) == nullptr, "setIsVolatile null");
    ok &= check(SkPathBuilder_reset(nullptr) == nullptr, "reset null");
    ok &= check(SkPathBuilder_moveToPoint(nullptr, 1.0f, 2.0f) == nullptr, "moveToPoint null");
    ok &= check(SkPathBuilder_lineToPoint(nullptr, 3.0f, 4.0f) == nullptr, "lineToPoint null");
    ok &= check(SkPathBuilder_quadToPointArray(nullptr, nullptr) == nullptr, "quadToPointArray null builder");
    ok &= check(SkPathBuilder_conicToPointArray(nullptr, nullptr, 1.0f) == nullptr, "conicToPointArray null builder");
    ok &= check(SkPathBuilder_cubicToPointArray(nullptr, nullptr) == nullptr, "cubicToPointArray null builder");
    ok &= check(SkPathBuilder_polylineTo(nullptr, nullptr, 1) == nullptr, "polylineTo null builder");
    ok &= check(SkPathBuilder_polylineToFromList(nullptr, nullptr) == nullptr, "polylineToFromList null builder");
    ok &= check(SkPathBuilder_arcTo(nullptr, nullptr, 0.0f, 90.0f, false) == nullptr, "arcTo null builder");
    ok &= check(SkPathBuilder_addArc(nullptr, nullptr, 0.0f, 90.0f) == nullptr, "addArc null builder");
    ok &= check(SkPathBuilder_addRect(nullptr, nullptr, 0, 0) == nullptr, "addRect null builder");
    ok &= check(SkPathBuilder_addRectWithDirection(nullptr, nullptr, 0) == nullptr, "addRectWithDirection null builder");
    ok &= check(SkPathBuilder_addOval(nullptr, nullptr, 0, 0) == nullptr, "addOval null builder");
    ok &= check(SkPathBuilder_addOvalWithDirection(nullptr, nullptr, 0) == nullptr, "addOvalWithDirection null builder");
    ok &= check(SkPathBuilder_addRRect(nullptr, nullptr, 0, 0) == nullptr, "addRRect null builder");
    ok &= check(SkPathBuilder_addRRectWithDirection(nullptr, nullptr, 0) == nullptr, "addRRectWithDirection null builder");
    ok &= check(SkPathBuilder_addPolygon(nullptr, nullptr, 1, true) == nullptr, "addPolygon null builder");
    ok &= check(SkPathBuilder_addPolygonFromList(nullptr, nullptr, true) == nullptr, "addPolygonFromList null builder");
    ok &= check(SkPathBuilder_addPath(nullptr, nullptr) == nullptr, "addPath null builder");
    ok &= check(SkPathBuilder_offset(nullptr, 1.0f, 1.0f) == nullptr, "offset null");
    ok &= check(SkPathBuilder_toggleInverseFillType(nullptr) == nullptr, "toggleInverseFillType null");

    reskia_path_builder_t *builder = SkPathBuilder_new();
    ok &= check(builder != nullptr, "new builder");
    if (builder != nullptr) {
        ok &= check(SkPathBuilder_quadToPointArray(builder, nullptr) == builder, "quadToPointArray null pts no-op");
        ok &= check(SkPathBuilder_conicToPointArray(builder, nullptr, 1.0f) == builder, "conicToPointArray null pts no-op");
        ok &= check(SkPathBuilder_cubicToPointArray(builder, nullptr) == builder, "cubicToPointArray null pts no-op");
        ok &= check(SkPathBuilder_polylineTo(builder, nullptr, 2) == builder, "polylineTo null pts no-op");
        ok &= check(SkPathBuilder_polylineTo(builder, nullptr, 0) == builder, "polylineTo zero count no-op");
        ok &= check(SkPathBuilder_polylineToFromList(builder, nullptr) == builder, "polylineToFromList null list no-op");
        ok &= check(SkPathBuilder_arcTo(builder, nullptr, 0.0f, 90.0f, false) == builder, "arcTo null oval no-op");
        ok &= check(SkPathBuilder_addArc(builder, nullptr, 0.0f, 90.0f) == builder, "addArc null oval no-op");
        ok &= check(SkPathBuilder_addRect(builder, nullptr, 0, 0) == builder, "addRect null rect no-op");
        ok &= check(SkPathBuilder_addRectWithDirection(builder, nullptr, 0) == builder, "addRectWithDirection null rect no-op");
        ok &= check(SkPathBuilder_addOval(builder, nullptr, 0, 0) == builder, "addOval null rect no-op");
        ok &= check(SkPathBuilder_addOvalWithDirection(builder, nullptr, 0) == builder, "addOvalWithDirection null rect no-op");
        ok &= check(SkPathBuilder_addRRect(builder, nullptr, 0, 0) == builder, "addRRect null rrect no-op");
        ok &= check(SkPathBuilder_addRRectWithDirection(builder, nullptr, 0) == builder, "addRRectWithDirection null rrect no-op");
        ok &= check(SkPathBuilder_addPolygon(builder, nullptr, 2, true) == builder, "addPolygon null pts no-op");
        ok &= check(SkPathBuilder_addPolygon(builder, nullptr, 0, true) == builder, "addPolygon zero count no-op");
        ok &= check(SkPathBuilder_addPolygonFromList(builder, nullptr, true) == builder, "addPolygonFromList null list no-op");
        ok &= check(SkPathBuilder_addPath(builder, nullptr) == builder, "addPath null path no-op");

        ok &= check(SkPathBuilder_moveToPoint(builder, 1.0f, 2.0f) == builder, "moveToPoint valid");
        ok &= check(SkPathBuilder_lineToPoint(builder, 3.0f, 4.0f) == builder, "lineToPoint valid");
        const sk_rect_t bounds = SkPathBuilder_computeBounds(builder);
        ok &= check(bounds != 0, "computeBounds valid");
        if (bounds != 0) {
            static_sk_rect_delete(bounds);
        }
        const sk_path_t snapshot = SkPathBuilder_snapshot(builder);
        ok &= check(snapshot != 0, "snapshot valid");
        if (snapshot != 0) {
            auto *path = static_cast<const reskia_path_t *>(static_sk_path_get_ptr(snapshot));
            reskia_path_builder_t *from_path = SkPathBuilder_newFromPath(path);
            ok &= check(from_path != nullptr, "newFromPath valid");
            SkPathBuilder_delete(from_path);
            static_sk_path_delete(snapshot);
        }
        reskia_path_builder_t *copy = SkPathBuilder_newCopy(builder);
        ok &= check(copy != nullptr, "newCopy valid");
        SkPathBuilder_delete(copy);
        const sk_path_t detached = SkPathBuilder_detach(builder);
        ok &= check(detached != 0, "detach valid");
        if (detached != 0) {
            static_sk_path_delete(detached);
        }
        SkPathBuilder_delete(builder);
    }

    return ok ? 0 : 1;
}
