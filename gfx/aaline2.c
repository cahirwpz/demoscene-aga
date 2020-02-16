#include "gfx/pixbuf.h"
#include "std/debug.h"
#include "std/fastmath.h"

static inline void AddPixel(uint8_t *p, uint8_t c) {
  uint16_t d = *p + c;

  if (d >= 256)
    d = 255;

  *p = d;
}

void DrawLineAA(PixBufT *canvas, int xs, int ys, int xe, int ye) {
  uint8_t *pixels;
  int dx, dy, step, stride;

  if (ys > ye) {
    swapr(xs, xe);
    swapr(ys, ye);
  }

  /*  quarters:
   *
   *  \ 1 | 3 /
   *   \  |  /
   *    \ | /
   *  0  \|/  2
   * -----x-----
   *  2  /|\  0
   *    / | \
   *   /  |  \
   *  / 3 | 1 \
   *
   */

  if (xs < xe) {
    dx = xe - xs;
    step = 1;
  } else {
    dx = xs - xe;
    step = -1;
  }

  dy = ye - ys;

  stride = canvas->width;
  pixels = canvas->data + ys * stride + xs;

  /* (xs, ys, xe, ye) unused from now on */

  if (dx < dy) {
    int dg2 = dx * 2;
    int dg = dg2 - dy;
    int dg1 = dg - dy;

    int twovdu = 0;
    float invD = 0.5 * FastInvSqrt(dx * dx + dy * dy);
    float invD2du = 2.0 * (dx * invD);

    do {
      float d = twovdu * invD;

      AddPixel(pixels, d * 128.0f);
      AddPixel(pixels - stride, (invD2du - d) * 128.0f);
      AddPixel(pixels + stride, (invD2du + d) * 128.0f);

      if (dg > 0) {
        twovdu = dg + dx;
        pixels += step;
        dg += dg1;
      } else {
        twovdu = dg - dx;
        dg += dg2;
      }

      pixels += stride;
    } while (--dy > 0);
  } else {
    int dg2 = dy * 2;
    int dg = dg2 - dx;
    int dg1 = dg - dx;

    int twovdu = 0;
    float invD = 0.5 * FastInvSqrt(dx * dx + dy * dy);
    float invD2du = 2.0 * (dy * invD);

    do {
      float d = twovdu * invD;

      AddPixel(pixels, d * 128.0f);
      AddPixel(pixels - step, (invD2du - d) * 128.0f);
      AddPixel(pixels + step, (invD2du + d) * 128.0f);

      if (dg > 0) {
        twovdu = dg + dy;
        pixels += stride;
        dg += dg1;
      } else {
        twovdu = dg - dy;
        dg += dg2;
      }

      pixels += step;
    } while (--dx > 0);
  }
}
