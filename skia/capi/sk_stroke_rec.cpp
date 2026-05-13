//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stroke_rec.h"

#include <cmath>

#include "include/core/SkStrokeRec.h"

#include "../handles/static_sk_stroke_rec.h"

#include "../handles/static_sk_stroke_rec-internal.h"

namespace {

bool is_valid_init_style(reskia_stroke_rec_init_style_t style) {
    return style >= SkStrokeRec::kHairline_InitStyle && style <= SkStrokeRec::kFill_InitStyle;
}

bool is_valid_paint_style(reskia_stroke_rec_paint_style_t style) {
    return style >= SkPaint::kFill_Style && style < SkPaint::kStyleCount;
}

bool is_valid_cap(reskia_stroke_rec_cap_t cap) {
    return cap >= SkPaint::kButt_Cap && cap < SkPaint::kCapCount;
}

bool is_valid_join(reskia_stroke_rec_join_t join) {
    return join >= SkPaint::kMiter_Join && join < SkPaint::kJoinCount;
}

} // namespace

extern "C" {

void SkStrokeRec_delete(reskia_stroke_rec_t *stroke_rec) {
    delete reinterpret_cast<SkStrokeRec *>(stroke_rec);
}

sk_stroke_rec_t SkStrokeRec_static(reskia_stroke_rec_init_style_t style) {
    if (!is_valid_init_style(style)) {
        return 0;
    }
    return static_sk_stroke_rec_make(SkStrokeRec(static_cast<SkStrokeRec::InitStyle>(style)));
}

sk_stroke_rec_t SkStrokeRec_staticWithPaintStyleAndResScale(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style, float resScale) {
    if (paint == nullptr || !is_valid_paint_style(style)) {
        return 0;
    }
    return static_sk_stroke_rec_make(SkStrokeRec(* reinterpret_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style), resScale));
}

sk_stroke_rec_t SkStrokeRec_staticWithPaintAndResScale(const reskia_paint_t *paint, float resScale) {
    if (paint == nullptr) {
        return 0;
    }
    return static_sk_stroke_rec_make(SkStrokeRec(* reinterpret_cast<const SkPaint *>(paint), resScale));
}

reskia_stroke_rec_style_t SkStrokeRec_getStyle(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0;
    }
    return static_cast<reskia_stroke_rec_style_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getStyle());
}

float SkStrokeRec_getWidth(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getWidth();
}

float SkStrokeRec_getMiter(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getMiter();
}

reskia_stroke_rec_cap_t SkStrokeRec_getCap(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0;
    }
    return static_cast<reskia_stroke_rec_cap_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getCap());
}

reskia_stroke_rec_join_t SkStrokeRec_getJoin(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0;
    }
    return static_cast<reskia_stroke_rec_join_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getJoin());
}

bool SkStrokeRec_isHairlineStyle(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->isHairlineStyle();
}

bool SkStrokeRec_isFillStyle(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->isFillStyle();
}

void SkStrokeRec_setFillStyle(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setFillStyle();
}

void SkStrokeRec_setHairlineStyle(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setHairlineStyle();
}

void SkStrokeRec_setStrokeStyle(reskia_stroke_rec_t *stroke_rec, float width, bool strokeAndFill) {
    if (stroke_rec == nullptr) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setStrokeStyle(width, strokeAndFill);
}

void SkStrokeRec_setStrokeParams(reskia_stroke_rec_t *stroke_rec, reskia_stroke_rec_cap_t cap, reskia_stroke_rec_join_t join, float miterLimit) {
    if (stroke_rec == nullptr || !is_valid_cap(cap) || !is_valid_join(join)) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setStrokeParams(static_cast<SkPaint::Cap>(cap), static_cast<SkPaint::Join>(join), miterLimit);
}

float SkStrokeRec_getResScale(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getResScale();
}

void SkStrokeRec_setResScale(reskia_stroke_rec_t *stroke_rec, float rs) {
    if (stroke_rec == nullptr || rs <= 0.0f || !std::isfinite(rs)) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setResScale(rs);
}

bool SkStrokeRec_needToApply(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->needToApply();
}

bool SkStrokeRec_applyToPath(reskia_stroke_rec_t *stroke_rec, reskia_path_t *dst, const reskia_path_t *src) {
    if (stroke_rec == nullptr || dst == nullptr || src == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->applyToPath(reinterpret_cast<SkPath *>(dst), * reinterpret_cast<const SkPath *>(src));
}

void SkStrokeRec_applyToPaint(reskia_stroke_rec_t *stroke_rec, reskia_paint_t *paint) {
    if (stroke_rec == nullptr || paint == nullptr) {
        return;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->applyToPaint(reinterpret_cast<SkPaint *>(paint));
}

float SkStrokeRec_getInflationRadius(reskia_stroke_rec_t *stroke_rec) {
    if (stroke_rec == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getInflationRadius();
}

bool SkStrokeRec_hasEqualEffect(reskia_stroke_rec_t *stroke_rec, const reskia_stroke_rec_t *other) {
    if (stroke_rec == nullptr || other == nullptr) {
        return false;
    }
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->hasEqualEffect(* reinterpret_cast<const SkStrokeRec *>(other));
}

// static

float SkStrokeRec_GetInflationRadius(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style) {
    if (paint == nullptr || !is_valid_paint_style(style)) {
        return 0.0f;
    }
    return SkStrokeRec::GetInflationRadius(* reinterpret_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style));
}

float SkStrokeRec_GetInflationRadiusWithJoinMiterCapAndStrokeWidth(reskia_stroke_rec_join_t join, float miterLimit, reskia_stroke_rec_cap_t cap, float strokeWidth) {
    if (!is_valid_join(join) || !is_valid_cap(cap)) {
        return 0.0f;
    }
    return SkStrokeRec::GetInflationRadius(static_cast<SkPaint::Join>(join), miterLimit, static_cast<SkPaint::Cap>(cap), strokeWidth);
}

}
