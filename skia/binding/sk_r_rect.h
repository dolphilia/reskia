//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_R_RECT_H
#define RAIA_SKIA_SK_R_RECT_H

#include <stddef.h>

#include "../static/static_sk_point.h"
#include "../static/static_sk_r_rect.h"
#include "../static/static_sk_string.h"

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_vector_t reskia_vector_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkRRect & operator=(const SkRRect &rrect)
reskia_r_rect_t *SkRRect_new(); // () -> SkRRect *
reskia_r_rect_t *SkRRect_new_2(const reskia_r_rect_t *rrect); // (const SkRRect *rrect) -> SkRRect *
void SkRRect_delete(reskia_r_rect_t *rrect); // (SkRRect *rrect)
int SkRRect_getType(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> SkRRect::Type
int SkRRect_type(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> SkRRect::Type
bool SkRRect_isEmpty(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
bool SkRRect_isRect(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
bool SkRRect_isOval(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
bool SkRRect_isSimple(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
bool SkRRect_isNinePatch(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
bool SkRRect_isComplex(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
float SkRRect_width(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> SkScalar
float SkRRect_height(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> SkScalar
sk_point_t SkRRect_getSimpleRadii(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> sk_point_t
void SkRRect_setEmpty(reskia_r_rect_t *rrect); // (SkRRect *rrect)
void SkRRect_setRect(reskia_r_rect_t *rrect, const reskia_rect_t *rect); // (SkRRect *rrect, const SkRect *rect)
void SkRRect_setOval(reskia_r_rect_t *rrect, const reskia_rect_t *oval); // (SkRRect *rrect, const SkRect *oval)
void SkRRect_setRectXY(reskia_r_rect_t *rrect, const reskia_rect_t *rect, float xRad, float yRad); // (SkRRect *rrect, const SkRect *rect, SkScalar xRad, SkScalar yRad)
void SkRRect_setNinePatch(reskia_r_rect_t *rrect, const reskia_rect_t *rect, float leftRad, float topRad, float rightRad, float bottomRad); // (SkRRect *rrect, const SkRect *rect, SkScalar leftRad, SkScalar topRad, SkScalar rightRad, SkScalar bottomRad)
void SkRRect_setRectRadii(reskia_r_rect_t *rrect, const reskia_rect_t *rect, const reskia_vector_t *radii); // (SkRRect *rrect, const SkRect *rect, const SkVector radii[4])
const reskia_rect_t *SkRRect_rect(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> const SkRect *
sk_point_t SkRRect_radii(reskia_r_rect_t *rrect, int corner); // (SkRRect *rrect, SkRRect::Corner corner) -> sk_point_t
const reskia_rect_t *SkRRect_getBounds(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> const SkRect *
void SkRRect_inset(reskia_r_rect_t *rrect, float dx, float dy, reskia_r_rect_t *dst); // (SkRRect *rrect, SkScalar dx, SkScalar dy, SkRRect *dst)
void SkRRect_inset_2(reskia_r_rect_t *rrect, float dx, float dy); // (SkRRect *rrect, SkScalar dx, SkScalar dy)
void SkRRect_outset(reskia_r_rect_t *rrect, float dx, float dy, reskia_r_rect_t *dst); // (SkRRect *rrect, SkScalar dx, SkScalar dy, SkRRect *dst)
void SkRRect_outset_2(reskia_r_rect_t *rrect, float dx, float dy); // (SkRRect *rrect, SkScalar dx, SkScalar dy)
void SkRRect_offset(reskia_r_rect_t *rrect, float dx, float dy); // (SkRRect *rrect, SkScalar dx, SkScalar dy)
sk_r_rect_t SkRRect_makeOffset(reskia_r_rect_t *rrect, float dx, float dy); // (SkRRect *rrect, SkScalar dx, SkScalar dy) -> sk_r_rect_t
bool SkRRect_contains(reskia_r_rect_t *rrect, const reskia_rect_t *rect); // (SkRRect *rrect, const SkRect *rect) -> bool
bool SkRRect_isValid(reskia_r_rect_t *rrect); // (SkRRect *rrect) -> bool
size_t SkRRect_writeToMemory(reskia_r_rect_t *rrect, void *buffer); // (SkRRect *rrect, void *buffer) -> size_t
size_t SkRRect_readFromMemory(reskia_r_rect_t *rrect, const void *buffer, size_t length); // (SkRRect *rrect, const void *buffer, size_t length) -> size_t
bool SkRRect_transform(reskia_r_rect_t *rrect, const reskia_matrix_t *matrix, reskia_r_rect_t *dst); // (SkRRect *rrect, const SkMatrix *matrix, SkRRect *dst) -> bool
void SkRRect_dump(reskia_r_rect_t *rrect, bool asHex); // (SkRRect *rrect, bool asHex)
sk_string_t SkRRect_dumpToString(reskia_r_rect_t *rrect, bool asHex); // (SkRRect *rrect, bool asHex) -> sk_string_t
void SkRRect_dump_2(reskia_r_rect_t *rrect); // (SkRRect *rrect)
void SkRRect_dumpHex(reskia_r_rect_t *rrect); // (SkRRect *rrect)

// static

sk_r_rect_t SkRRect_MakeEmpty(); // () -> sk_r_rect_t
sk_r_rect_t SkRRect_MakeRect(const reskia_rect_t *r); // (const SkRect *r) -> sk_r_rect_t
sk_r_rect_t SkRRect_MakeOval(const reskia_rect_t *oval); // (const SkRect *oval) -> sk_r_rect_t
sk_r_rect_t SkRRect_MakeRectXY(const reskia_rect_t *rect, float xRad, float yRad); // (const SkRect *rect, SkScalar xRad, SkScalar yRad) -> sk_r_rect_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_R_RECT_H
