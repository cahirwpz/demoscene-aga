#ifndef __STD_RANDOM_H__
#define __STD_RANDOM_H__

#include "std/types.h"

/* Don't pass zero or else... it doesn't work. */
static inline int32_t RandomInt32(int32_t *i) {
  int32_t a = *i;
  a ^= (a << 13);
  a ^= (a >> 17);
  a ^= (a << 5);
  *i = a;
  return a;
}

/* Returns a value in [0.0, 1.0) */
static inline float RandomFloat(int32_t *i) {
  union {
    int32_t n;
    float f;
  } h;
  h.n = RandomInt32(i);
  h.n &= ~0x7fffff;
  h.n |= 0x3f800000;
  return h.f - 1.0;
}

#endif
