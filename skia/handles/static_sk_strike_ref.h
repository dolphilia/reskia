//
// Created by dolphilia on 2026/06/02.
//

#ifndef RAIA_SKIA_STATIC_SK_STRIKE_REF_H
#define RAIA_SKIA_STATIC_SK_STRIKE_REF_H

#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_strike_ref_t;
void static_sk_strike_ref_delete(int key);
void *static_sk_strike_ref_get_ptr(int key); // -> SkStrikeRef *
#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_STATIC_SK_STRIKE_REF_H
