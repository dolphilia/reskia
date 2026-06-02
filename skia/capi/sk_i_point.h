//
// Created by dolphilia on 25/01/29.
//

#ifndef SK_I_POINT_H
#define SK_I_POINT_H

#include "../handles/static_sk_i_point.h"

#ifdef __cplusplus
extern "C" {
#endif


void SkIPoint_delete(void * i_point); // NULL i_point is no-op.
int SkIPoint_x(void * i_point); // NULL i_point returns 0.
int SkIPoint_y(void * i_point); // NULL i_point returns 0.
bool SkIPoint_isZero(void * i_point); // NULL i_point returns true.
void SkIPoint_set(void * i_point, int x, int y); // NULL i_point is no-op.
bool SkIPoint_equals(void * i_point, int x, int y); // NULL i_point returns false.

// static

sk_i_point_t SkIPoint_Make(int x, int y); // Returns a caller-owned SkIPoint handle.

#ifdef __cplusplus
}
#endif

#endif //SK_I_POINT_H
