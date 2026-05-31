// Compatibility symbols for prebuilt Skia module archives built before the
// SkSpan primary API transition.
#define SK_SUPPORT_UNSPANNED_APIS 1

#include "include/core/SkFont.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/effects/SkDashPathEffect.h"

SkPathBuilder& SkPathBuilder::addPath(const SkPath& src) {
    return this->addPath(src, SkPath::kAppend_AddPathMode);
}

SkPathBuilder& SkPathBuilder::addPath(const SkPath& src, SkPath::AddPathMode mode) {
    return this->addPath(src, SkMatrix::I(), mode);
}

sk_sp<SkPathEffect> SkDashPathEffect_MakeUnspannedCompat(
        const SkScalar intervals[], int count, SkScalar phase) asm("__ZN16SkDashPathEffect4MakeEPKfif");
sk_sp<SkPathEffect> SkDashPathEffect_MakeUnspannedCompat(
        const SkScalar intervals[], int count, SkScalar phase) {
    return intervals ? SkDashPathEffect::Make({intervals, static_cast<size_t>(count)}, phase) : nullptr;
}

SkPath SkPath_PolygonUnspannedCompat(const SkPoint pts[],
                                     int count,
                                     bool isClosed,
                                     SkPathFillType fillType,
                                     bool isVolatile) asm("__ZN6SkPath7PolygonEPK7SkPointib14SkPathFillTypeb");
SkPath SkPath_PolygonUnspannedCompat(const SkPoint pts[],
                                     int count,
                                     bool isClosed,
                                     SkPathFillType fillType,
                                     bool isVolatile) {
    return SkPath::Polygon({pts, static_cast<size_t>(count)}, isClosed, fillType, isVolatile);
}

void SkFont_getWidthsBoundsUnspannedCompat(const SkFont* font,
                                           const SkGlyphID glyphs[],
                                           int count,
                                           SkScalar widths[],
                                           SkRect bounds[],
                                           const SkPaint* paint)
        asm("__ZNK6SkFont15getWidthsBoundsEPKtiPfP6SkRectPK7SkPaint");
void SkFont_getWidthsBoundsUnspannedCompat(const SkFont* font,
                                           const SkGlyphID glyphs[],
                                           int count,
                                           SkScalar widths[],
                                           SkRect bounds[],
                                           const SkPaint* paint) {
    const auto span_count = static_cast<size_t>(count);
    font->getWidthsBounds(
            {glyphs, span_count},
            {widths, widths ? span_count : 0},
            {bounds, bounds ? span_count : 0},
            paint);
}

void SkFont_getPathsUnspannedCompat(
        const SkFont* font,
        const SkGlyphID glyphIDs[],
        int count,
        void (*glyphPathProc)(const SkPath* pathOrNull, const SkMatrix& mx, void* ctx),
        void* ctx) asm("__ZNK6SkFont8getPathsEPKtiPFvPK6SkPathRK8SkMatrixPvES8_");
void SkFont_getPathsUnspannedCompat(
        const SkFont* font,
        const SkGlyphID glyphIDs[],
        int count,
        void (*glyphPathProc)(const SkPath* pathOrNull, const SkMatrix& mx, void* ctx),
        void* ctx) {
    font->getPaths({glyphIDs, static_cast<size_t>(count)}, glyphPathProc, ctx);
}
