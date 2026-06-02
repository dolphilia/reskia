#ifndef STATIC_SK_STRIKE_REF_INTERNAL_H
#define STATIC_SK_STRIKE_REF_INTERNAL_H

#include "include/core/SkStrikeRef.h"

int static_sk_strike_ref_make(SkStrikeRef value);
SkStrikeRef static_sk_strike_ref_get_entity(int key);
void static_sk_strike_ref_set(int key, SkStrikeRef value);

#endif // STATIC_SK_STRIKE_REF_INTERNAL_H
