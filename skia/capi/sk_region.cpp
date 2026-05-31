//
// Created by dolphilia on 2024/01/10.
//

#include "sk_region.h"

#include "include/core/SkPathBuilder.h"
#include "include/core/SkRegion.h"

namespace {

SkRegion *as_region(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region);
}

const SkRegion *as_region(const reskia_region_t *region) {
    return reinterpret_cast<const SkRegion *>(region);
}

const SkIRect *as_irect(const reskia_i_rect_t *rect) {
    return reinterpret_cast<const SkIRect *>(rect);
}

const SkPath *as_path(const reskia_path_t *path) {
    return reinterpret_cast<const SkPath *>(path);
}

SkPath *as_path(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path);
}

SkPathBuilder *as_path_builder(reskia_path_builder_t *path_builder) {
    return reinterpret_cast<SkPathBuilder *>(path_builder);
}

bool is_valid_op(reskia_region_op_t op) {
    return op >= SkRegion::kDifference_Op && op <= SkRegion::kLastOp;
}

SkRegion::Op to_region_op(reskia_region_op_t op) {
    return static_cast<SkRegion::Op>(op);
}

} // namespace

extern "C" {

//SkRegion & operator=(const SkRegion &region)
reskia_region_t *SkRegion_new() {
    return reinterpret_cast<reskia_region_t *>(new SkRegion());
}

reskia_region_t *SkRegion_newCopy(const reskia_region_t *region) {
    const SkRegion *src = as_region(region);
    if (src == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_region_t *>(
            new SkRegion(*src));
}

reskia_region_t *SkRegion_newFromIRect(const reskia_i_rect_t *rect) {
    const SkIRect *src = as_irect(rect);
    if (src == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_region_t *>(
            new SkRegion(*src));
}

void SkRegion_delete(reskia_region_t *region) {
    delete as_region(region);
}

bool SkRegion_equals(reskia_region_t *region, const reskia_region_t *other) {
    const SkRegion *lhs = as_region(region);
    const SkRegion *rhs = as_region(other);
    if (lhs == nullptr || rhs == nullptr) {
        return false;
    }
    return *lhs == *rhs;
}

bool SkRegion_notEquals(reskia_region_t *region, const reskia_region_t *other) {
    const SkRegion *lhs = as_region(region);
    const SkRegion *rhs = as_region(other);
    if (lhs == nullptr || rhs == nullptr) {
        return false;
    }
    return *lhs != *rhs;
}

bool SkRegion_set(reskia_region_t *region, const reskia_region_t *src) {
    SkRegion *dst = as_region(region);
    const SkRegion *source = as_region(src);
    if (dst == nullptr || source == nullptr) {
        return false;
    }
    return dst->set(*source);
}

void SkRegion_swap(reskia_region_t *region, reskia_region_t *other) {
    SkRegion *lhs = as_region(region);
    SkRegion *rhs = as_region(other);
    if (lhs == nullptr || rhs == nullptr) {
        return;
    }
    lhs->swap(*rhs);
}

bool SkRegion_isEmpty(reskia_region_t *region) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return true;
    }
    return rgn->isEmpty();
}

bool SkRegion_isRect(reskia_region_t *region) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return false;
    }
    return rgn->isRect();
}

bool SkRegion_isComplex(reskia_region_t *region) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return false;
    }
    return rgn->isComplex();
}

const reskia_i_rect_t *SkRegion_getBounds(reskia_region_t *region) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_i_rect_t *>(&rgn->getBounds());
}

int SkRegion_computeRegionComplexity(reskia_region_t *region) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return 0;
    }
    return rgn->computeRegionComplexity();
}

bool SkRegion_addBoundaryPath(reskia_region_t *region, reskia_path_builder_t *path_builder) {
    const SkRegion *rgn = as_region(region);
    SkPathBuilder *builder = as_path_builder(path_builder);
    if (rgn == nullptr || builder == nullptr) {
        return false;
    }
    return rgn->addBoundaryPath(builder);
}

bool SkRegion_getBoundaryPath(reskia_region_t *region, reskia_path_t *path) {
    const SkRegion *rgn = as_region(region);
    SkPath *dst = as_path(path);
    if (rgn == nullptr || dst == nullptr) {
        return false;
    }
    SkPathBuilder builder;
    const bool result = rgn->addBoundaryPath(&builder);
    if (result) {
        *dst = builder.detach();
    }
    return result;
}

bool SkRegion_setEmpty(reskia_region_t *region) {
    SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return false;
    }
    return rgn->setEmpty();
}

bool SkRegion_setRect(reskia_region_t *region, const reskia_i_rect_t *rect) {
    SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(rect);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->setRect(*src);
}

bool SkRegion_setRects(reskia_region_t *region, const reskia_i_rect_t *rects, int count) {
    SkRegion *rgn = as_region(region);
    if (rgn == nullptr || count < 0 || (count > 0 && rects == nullptr)) {
        return false;
    }
    return rgn->setRects(reinterpret_cast<const SkIRect *>(rects), count);
}

bool SkRegion_setRegion(reskia_region_t *region, const reskia_region_t *region_2) {
    SkRegion *dst = as_region(region);
    const SkRegion *src = as_region(region_2);
    if (dst == nullptr || src == nullptr) {
        return false;
    }
    return dst->setRegion(*src);
}

bool SkRegion_setPath(reskia_region_t *region, const reskia_path_t *path, const reskia_region_t *clip) {
    SkRegion *rgn = as_region(region);
    const SkPath *srcPath = as_path(path);
    const SkRegion *srcClip = as_region(clip);
    if (rgn == nullptr || srcPath == nullptr || srcClip == nullptr) {
        return false;
    }
    return rgn->setPath(*srcPath, *srcClip);
}

bool SkRegion_intersects(reskia_region_t *region, const reskia_i_rect_t *rect) {
    const SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(rect);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->intersects(*src);
}

bool SkRegion_intersectsRegion(reskia_region_t *region, const reskia_region_t *other) {
    const SkRegion *rgn = as_region(region);
    const SkRegion *src = as_region(other);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->intersects(*src);
}

bool SkRegion_contains(reskia_region_t *region, int32_t x, int32_t y) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return false;
    }
    return rgn->contains(x, y);
}

bool SkRegion_containsIRect(reskia_region_t *region, const reskia_i_rect_t *other) {
    const SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(other);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->contains(*src);
}

bool SkRegion_containsRegion(reskia_region_t *region, const reskia_region_t *other) {
    const SkRegion *rgn = as_region(region);
    const SkRegion *src = as_region(other);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->contains(*src);
}

bool SkRegion_quickContains(reskia_region_t *region, const reskia_i_rect_t *r) {
    const SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(r);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->quickContains(*src);
}

bool SkRegion_quickReject(reskia_region_t *region, const reskia_i_rect_t *rect) {
    const SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(rect);
    if (rgn == nullptr || src == nullptr) {
        return false;
    }
    return rgn->quickReject(*src);
}

bool SkRegion_quickRejectRegion(reskia_region_t *region, const reskia_region_t *rgn) {
    const SkRegion *region_1 = as_region(region);
    const SkRegion *region_2 = as_region(rgn);
    if (region_1 == nullptr || region_2 == nullptr) {
        return false;
    }
    return region_1->quickReject(*region_2);
}

void SkRegion_translate(reskia_region_t *region, int dx, int dy) {
    SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return;
    }
    rgn->translate(dx, dy);
}

void SkRegion_translateToRegion(reskia_region_t *region, int dx, int dy, reskia_region_t *dst) {
    const SkRegion *src = as_region(region);
    SkRegion *destination = as_region(dst);
    if (src == nullptr || destination == nullptr) {
        return;
    }
    src->translate(dx, dy, destination);
}

bool SkRegion_op(reskia_region_t *region, const reskia_i_rect_t *rect, reskia_region_op_t op) {
    SkRegion *rgn = as_region(region);
    const SkIRect *src = as_irect(rect);
    if (rgn == nullptr || src == nullptr || !is_valid_op(op)) {
        return false;
    }
    return rgn->op(*src, to_region_op(op));
}

bool SkRegion_opWithRegion(reskia_region_t *region, const reskia_region_t *rgn, reskia_region_op_t op) {
    SkRegion *region_1 = as_region(region);
    const SkRegion *region_2 = as_region(rgn);
    if (region_1 == nullptr || region_2 == nullptr || !is_valid_op(op)) {
        return false;
    }
    return region_1->op(*region_2, to_region_op(op));
}

bool SkRegion_opWithIRectAndRegion(reskia_region_t *region, const reskia_i_rect_t *rect, const reskia_region_t *rgn, reskia_region_op_t op) {
    SkRegion *dst = as_region(region);
    const SkIRect *srcRect = as_irect(rect);
    const SkRegion *srcRegion = as_region(rgn);
    if (dst == nullptr || srcRect == nullptr || srcRegion == nullptr || !is_valid_op(op)) {
        return false;
    }
    return dst->op(*srcRect, *srcRegion, to_region_op(op));
}

bool SkRegion_opWithRegionAndIRect(reskia_region_t *region, const reskia_region_t *rgn, const reskia_i_rect_t *rect, reskia_region_op_t op) {
    SkRegion *dst = as_region(region);
    const SkRegion *srcRegion = as_region(rgn);
    const SkIRect *srcRect = as_irect(rect);
    if (dst == nullptr || srcRegion == nullptr || srcRect == nullptr || !is_valid_op(op)) {
        return false;
    }
    return dst->op(*srcRegion, *srcRect, to_region_op(op));
}

bool SkRegion_op_5(reskia_region_t *region, const reskia_region_t *rgna, const reskia_region_t *rgnb, reskia_region_op_t op) {
    SkRegion *dst = as_region(region);
    const SkRegion *region_a = as_region(rgna);
    const SkRegion *region_b = as_region(rgnb);
    if (dst == nullptr || region_a == nullptr || region_b == nullptr || !is_valid_op(op)) {
        return false;
    }
    return dst->op(*region_a, *region_b, to_region_op(op));
}

size_t SkRegion_writeToMemory(reskia_region_t *region, void *buffer) {
    const SkRegion *rgn = as_region(region);
    if (rgn == nullptr) {
        return 0;
    }
    return rgn->writeToMemory(buffer);
}

size_t SkRegion_readFromMemory(reskia_region_t *region, const void *buffer, size_t length) {
    SkRegion *rgn = as_region(region);
    if (rgn == nullptr || buffer == nullptr) {
        return 0;
    }
    return rgn->readFromMemory(buffer, length);
}

}
